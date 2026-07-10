/* BYO-OS - SMP Multi-Core Support (x86_64)
 * 
 * xAPIC initialization and AP (Application Processor) startup.
 */
#include <kernel.h>

/* ===== xAPIC Registers ===== */
#define IA32_APIC_BASE_MSR  0x1B
#define APIC_BASE_DEFAULT   0xFEE00000ULL
#define APIC_ID_REG         0x20
#define APIC_VERSION_REG    0x30
#define APIC_SVR            0xF0
#define APIC_ICR_LOW        0x300
#define APIC_ICR_HIGH       0x310
#define APIC_LVT_TIMER      0x320
#define APIC_LVT_LINT0      0x350
#define APIC_LVT_LINT1      0x360
#define APIC_SPIV_APIC_EN   0x100

/* ICR values */
#define ICR_INIT           0x000C4500
#define ICR_STARTUP         0x000C4600
#define ICR_DELIVERY_PENDING 0x00001000

/* AP trampoline location */
#define AP_TRAMPOLINE_ADDR  0x8000

/* ===== CPU Structures ===== */
#define MAX_CPUS 32

typedef struct {
    uint32_t apic_id;
    int active;
    uint64_t stack;
    uint32_t cpu_number;
} cpu_t;

static cpu_t cpus[MAX_CPUS];
static int cpu_count = 0;
static volatile int smp_initialized = 0;
static uint64_t apic_base_virt = APIC_BASE_DEFAULT;

/* ===== MSR Access ===== */
static inline uint64_t rdmsr(uint32_t msr) {
    uint32_t lo, hi;
    asm volatile("rdmsr" : "=a"(lo), "=d"(hi) : "c"(msr));
    return ((uint64_t)hi << 32) | lo;
}

static inline void wrmsr(uint32_t msr, uint64_t val) {
    asm volatile("wrmsr" : : "a"((uint32_t)val), "d"((uint32_t)(val >> 32)), "c"(msr));
}

/* ===== APIC MMIO Access ===== */
static uint32_t apic_read(uint16_t reg) {
    return *(volatile uint32_t*)(apic_base_virt + reg);
}

static void apic_write(uint16_t reg, uint32_t val) {
    *(volatile uint32_t*)(apic_base_virt + reg) = val;
    /* APIC requires a memory fence - read back to flush */
    (void)apic_read(reg);
}

/* ===== Check for APIC via CPUID ===== */
static int apic_is_present(void) {
    uint32_t eax, ebx, ecx, edx;
    asm volatile("cpuid" : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx) : "a"(1));
    return (edx >> 9) & 1;
}

/* ===== Get APIC ID ===== */
static uint32_t get_apic_id(void) {
    uint32_t eax, ebx, ecx, edx;
    asm volatile("cpuid" : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx) : "a"(1));
    return (ebx >> 24) & 0xFF;
}

/* ===== Initialize xAPIC ===== */
static void apic_init(void) {
    serial_puts("[SMP] Enabling xAPIC...\n");
    
    /* Get APIC base address from MSR */
    uint64_t apic_base = rdmsr(IA32_APIC_BASE_MSR);
    apic_base_virt = (apic_base & ~0xFFFULL);  /* Clear bit 0-11 for base */
    if (!(apic_base & (1ULL << 11))) {
        /* APIC global enable bit (bit 11) not set, set it */
        apic_base |= (1ULL << 11);
        wrmsr(IA32_APIC_BASE_MSR, apic_base);
    }
    
    serial_puts("[SMP] APIC base: 0x");
    serial_put_hex((uint32_t)(apic_base_virt >> 32));
    serial_put_hex((uint32_t)apic_base_virt);
    serial_putchar('\n');
    
    /* Software enable APIC via Spurious Interrupt Vector Register */
    uint32_t svr = apic_read(APIC_SVR);
    svr |= APIC_SPIV_APIC_EN;  /* Bit 8: APIC enable */
    svr |= 0xFF;  /* Vector for spurious interrupts */
    apic_write(APIC_SVR, svr);
    
    serial_puts("[SMP] APIC version: 0x");
    serial_put_hex(apic_read(APIC_VERSION_REG));
    serial_putchar('\n');
    
    uint32_t apic_id = apic_read(APIC_ID_REG) >> 24;
    
    serial_puts("[SMP] BSP APIC ID: ");
    serial_put_dec(apic_id);
    serial_putchar('\n');
}

/* ===== AP Entry Point (called from assembly trampoline) ===== */
void ap_main(uint32_t cpu_number) {
    serial_puts("[SMP] AP CPU ");
    serial_put_dec(cpu_number);
    serial_puts(" started!\n");
    
    /* Initialize AP's APIC */
    apic_init();
    
    /* Mark this CPU as active */
    if (cpu_number < MAX_CPUS) {
        cpus[cpu_number].active = 1;
        cpus[cpu_number].apic_id = get_apic_id();
    }
    
    /* Halt - waiting for work */
    while (1) {
        asm volatile("hlt");
    }
}

/* ===== Send IPI ===== */
void smp_send_ipi(uint32_t apic_id, uint32_t icr) {
    /* Write high dword (APIC ID) */
    apic_write(APIC_ICR_HIGH, apic_id << 24);
    /* Write low dword (ICR) to trigger IPI */
    apic_write(APIC_ICR_LOW, icr);
    /* Wait for delivery to complete */
    while (apic_read(APIC_ICR_LOW) & ICR_DELIVERY_PENDING) {
        asm volatile("pause");
    }
}

/* ===== AP Startup ===== */
static void ap_start(int cpu_idx) {
    if (cpu_idx >= MAX_CPUS) return;
    
    uint32_t apic_id = cpus[cpu_idx].apic_id;
    
    serial_puts("[SMP] Starting AP APIC ID ");
    serial_put_dec(apic_id);
    serial_puts("...\n");
    
    /* Step 1: Assert INIT IPI */
    smp_send_ipi(apic_id, ICR_INIT);
    
    /* Wait 10ms */
    for (volatile int i = 0; i < 1000000; i++);
    
    /* Step 2: Send STARTUP IPI to trampoline at 0x8000 */
    smp_send_ipi(apic_id, ICR_STARTUP | (AP_TRAMPOLINE_ADDR >> 12));
    
    /* Wait 200us */
    for (volatile int i = 0; i < 20000; i++);
    
    /* Step 3: Send STARTUP IPI again */
    smp_send_ipi(apic_id, ICR_STARTUP | (AP_TRAMPOLINE_ADDR >> 12));
    
    serial_puts("[SMP] AP startup IPIs sent to APIC ID ");
    serial_put_dec(apic_id);
    serial_putchar('\n');
}

/* ===== Public API ===== */

void smp_init(void) {
    serial_puts("[SMP] SMP initialization...\n");
    
    /* Clear CPU structures */
    memset(cpus, 0, sizeof(cpus));
    cpu_count = 1;  /* BSP is always present */
    
    /* Initialize BSP */
    cpus[0].cpu_number = 0;
    cpus[0].apic_id = get_apic_id();
    cpus[0].active = 1;
    
    /* CPUID check for APIC */
    if (!apic_is_present()) {
        serial_puts("[SMP] No APIC found, single core mode\n");
        vga_puts("[SMP] No APIC - single core\n");
        return;
    }
    
    /* Enable xAPIC */
    apic_init();
    
    /* For now, just log BSP info - AP startup is hardware dependent */
    /* and would need the trampoline to be loaded at 0x8000 first */
    vga_puts("[SMP] BSP APIC ID: ");
    vga_put_dec(cpus[0].apic_id);
    vga_putchar('\n');
    
    smp_initialized = 1;
    serial_puts("[SMP] Ready (BSP only, AP start requires trampoline setup)\n");
}

int smp_get_cpu_count(void) {
    return cpu_count;
}

uint32_t smp_get_apic_id(void) {
    if (cpu_count > 0) return cpus[0].apic_id;
    return get_apic_id();
}

int smp_get_current_cpu(void) {
    /* Simple: read current APIC ID and look up */
    uint32_t id = get_apic_id();
    for (int i = 0; i < MAX_CPUS; i++) {
        if (cpus[i].active && cpus[i].apic_id == id) return i;
    }
    return 0;
}

void smp_lock_acquire(volatile int* lock) {
    while (__sync_lock_test_and_set(lock, 1)) {
        asm volatile("pause");
    }
}

void smp_lock_release(volatile int* lock) {
    __sync_lock_release(lock);
}

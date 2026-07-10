/* BYO-OS - Kernel Entry Point (x86_64) */
#include <kernel.h>
#include <stdint.h>

/* Forward declarations for new modules */
extern void pmm_init_64(uint64_t mem_size);
extern uint64_t pmm_alloc_page_64(void);
extern void pmm_free_page_64(uint64_t page);
extern uint64_t pmm_get_free_pages_64(void);
extern uint64_t pmm_get_total_pages_64(void);
extern void kmalloc_64_init(void);
extern void* kmalloc_64(size_t size);
extern void kfree_64(void* ptr);
extern uint64_t heap_get_used_64(void);
extern void vmm_init(void);
extern void vmm_map(uint64_t virt, uint64_t phys, uint64_t flags);
extern void syscall_init(void);
extern void initramfs_init(void);

/* Multiboot2 */
#define MULTIBOOT2_MAGIC 0x36d76289

typedef struct {
    uint32_t total_size;
    uint32_t reserved;
    uint64_t tags[];
} __attribute__((packed)) multiboot2_info_t;


/* Entry point from boot_entry_64.asm */
void _start64(uint32_t magic, void* mbi_ptr) {
    kernel_main(magic, mbi_ptr);
}

void kernel_main(uint32_t magic, void* mbi_ptr) {
    /* Early init */
    serial_init();
    serial_puts("[BOOT] BYO-OS x86_64 Starting...\n");

    vga_init();
    serial_puts("[BOOT] VGA OK\n");

    /* Parse Multiboot2 info for memory map */
    uint64_t mem_size = 128ULL * 1024 * 1024; /* default 128MB */
    if (magic == MULTIBOOT2_MAGIC && mbi_ptr) {
        multiboot2_info_t* mbi = (multiboot2_info_t*)mbi_ptr;
        /* Walk tags to find memory map */
        uint8_t* tag_ptr = (uint8_t*)mbi + 8; /* skip total_size + reserved */
        while (1) {
            uint32_t type = *(uint32_t*)tag_ptr;
            uint32_t size = *(uint32_t*)(tag_ptr + 4);
            if (type == 0) break; /* end tag */
            if (type == 6) { /* memory map tag */
                /* Find highest usable address */
                uint8_t* entry = tag_ptr + 16;
                uint8_t* end = tag_ptr + size;
                while (entry < end) {
                    uint64_t base = *(uint64_t*)(entry);
                    uint64_t len = *(uint64_t*)(entry + 8);
                    uint32_t mtype = *(uint32_t*)(entry + 16);
                    if (mtype == 1 && base + len > mem_size) {
                        mem_size = base + len;
                    }
                    entry += 24;
                }
            }
            /* Align to 8 bytes */
            tag_ptr += ((size + 7) & ~7);
        }
    }

    /* Cap at 128GB */
    if (mem_size > 128ULL * 1024 * 1024 * 1024)
        mem_size = 128ULL * 1024 * 1024 * 1024;

    /* GDT / IDT */
    gdt_init();
    serial_puts("[BOOT] GDT OK\n");
    idt_init();
    serial_puts("[BOOT] IDT OK\n");
    irq_init();
    serial_puts("[BOOT] IRQ OK\n");

    /* Memory - 64-bit */
    pmm_init_64(mem_size);
    serial_puts("[BOOT] PMM64 OK\n");
    kmalloc_64_init();
    serial_puts("[BOOT] Heap64 OK\n");
    vmm_init();
    serial_puts("[BOOT] VMM OK\n");

    /* File system */
    fs_init();
    serial_puts("[BOOT] FS OK\n");

    /* Initramfs - /etc/os-release etc */
    /* Initialize initramfs */
    initramfs_init();

    /* Initialize RTC */
    rtc_init();

    /* Initialize PCI bus */
    pci_init();

    /* Initialize ATA disk */
    ata_init();
    serial_puts("[BOOT] Initramfs OK (/etc/os-release, /etc/passwd...)\n");

    /* Linux syscall compatibility */
    syscall_init();
    serial_puts("[BOOT] Syscall layer OK (Linux ABI compatible)\n");

    journal_init();
    journal_append(0, "Filesystem initialized");

    keyboard_init();
    serial_puts("[BOOT] Keyboard OK\n");
    timer_init(100);
    serial_puts("[BOOT] Timer OK\n");
    scheduler_init();
    journal_append(0, "Scheduler initialized");
    serial_puts("[BOOT] Scheduler OK\n");

    user_init();
    journal_append(0, "User system initialized");
    serial_puts("[BOOT] User OK\n");

    net_init();
    journal_append(0, "Network initialized");
    serial_puts("[BOOT] Net OK\n");

    /* Create sample files */
    fs_create_file("readme.txt", "Welcome to BYO-OS!\nA from-scratch x86_64 operating system.\nDebian 12 compatible.\n", 70);
    fs_create_file("hello.txt", "Hello, World!\n", 14);
    fs_create_dir("home");
    fs_create_dir("tmp");
    fs_create_dir("var");
    fs_create_dir("var/log");
    fs_create_dir("opt");
    fs_create_dir("srv");
    fs_create_dir("usr");
    fs_create_dir("usr/local");
    serial_puts("[BOOT] Directory structure created\n");

    /* Print boot info */
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("============================================\n");
    vga_puts("           BYO-OS v2.1 (x86_64)\n");
    vga_puts("    Debian 12 Compatible | 128GB Support\n");
    vga_puts("============================================\n\n");
    vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);

    vga_puts("[BOOT] Arch: x86_64 | Memory: ");
    vga_put_dec((uint32_t)(pmm_get_total_pages_64() * 4096 / (1024*1024)));
    vga_puts(" MB\n");
    vga_puts("[BOOT] /etc/os-release: Debian 12 (bookworm) compatible\n");
    vga_puts("[BOOT] Linux syscall layer: ready\n");
    vga_puts("[BOOT] BT Panel support: enabled\n\n");

    vga_set_color(VGA_GREEN, VGA_BLACK);
    vga_puts(">>> All systems initialized! <<<\n\n");
    vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
    vga_puts("Type 'help' for commands.\n\n");

    journal_append(0, "System boot complete");
    serial_puts("[BOOT] ALL DONE, launching shell\n");
    shell_init();
    shell_run();
}
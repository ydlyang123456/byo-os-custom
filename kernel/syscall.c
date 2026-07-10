/* BYO-OS - Linux Syscall Compatibility Layer (x86_64 ABI)
 *
 * Intercepts int 0x80 and dispatches Linux-compatible syscalls.
 * Each handler prints "[syscall] xxx" to serial/VGA and returns
 * a reasonable default.  write(1) actually emits bytes to serial + VGA.
 *
 * Register mapping follows the Linux i386 int-0x80 ABI that lives
 * inside the x86_64 kernel's compat path:
 *   eax = syscall number
 *   ebx = arg0, ecx = arg1, edx = arg2, esi = arg3, edi = arg4, ebp = arg5
 *   eax (on return) = result / -errno
 */
#include <kernel.h>
#include <syscall.h>

/* ---------- helpers -------------------------------------------------- */

static void sys_write_string(const char* s) {
    serial_puts(s);
    vga_puts(s);
}

/* Map kernel timer ticks 閳?CLOCK_REALTIME seconds since boot.
 * Returns tv_sec in eax, tv_nsec in edx. */
static void sys_clock_gettime_handler(registers_t* regs) {
    (void)regs;
    uint32_t ticks = timer_get_ticks();
    uint32_t secs  = ticks / 100;
    uint32_t nsecs = (ticks % 100) * 10000000UL;   /* 10 ms resolution */

    /* tv_sec  閳?regs->rbx  (first pointer arg, struct timespec*)
     * tv_nsec 閳?offset+4 in that struct.  We store results in eax/edx
     * so the caller can copy them if it wants, but we also write
     * directly into the provided struct when the pointer is sane. */
    uint32_t* ts = (uint32_t*)(regs->rbx);
    if (ts) {
        ts[0] = secs;   /* tv_sec  */
        ts[1] = nsecs;  /* tv_nsec */
    }

    regs->rax = 0;  /* success */
    regs->rdx = nsecs;
    regs->rbx = secs;
}

/* Simple LCG pseudo-random seeded from PIT tick count. */
static uint32_t rng_state = 0xDEADBEEF;

static uint32_t rng_next(void) {
    rng_state ^= rng_state << 13;
    rng_state ^= rng_state >> 17;
    rng_state ^= rng_state << 5;
    return rng_state;
}

/* ---------- dispatch table ------------------------------------------ */

typedef void (*syscall_fn)(registers_t*);

static void sys_read(registers_t* r) {
    /* arg0 = fd, arg1 = buf, arg2 = count
     * Return 0 bytes read (stdin not wired yet). */
    (void)r;
    vga_puts("[syscall] read\n");
    serial_puts("[syscall] read\n");
    r->rax = 0;
}

static void sys_write(registers_t* r) {
    /* arg0 = fd, arg1 = buf, arg2 = count
     * Only fd 1 (stdout) and fd 2 (stderr) produce output. */
    int fd        = (int)r->rbx;
    const char* buf = (const char*)r->rcx;
    int count     = (int)r->rdx;

    vga_puts("[syscall] write fd=");
    vga_put_dec(fd);
    vga_puts(" len=");
    vga_put_dec(count);
    vga_puts("\n");
    serial_puts("[syscall] write\n");

    if ((fd == 1 || fd == 2) && buf && count > 0) {
        /* Truncate pathological lengths for safety */
        if (count > 4096) count = 4096;
        /* Emit to serial */
        for (int i = 0; i < count; i++) {
            if (buf[i] == '\n') serial_putchar('\r');
            serial_putchar(buf[i]);
        }
        /* Emit to VGA */
        for (int i = 0; i < count; i++) {
            vga_putchar(buf[i]);
        }
        r->rax = count;
    } else {
        r->rax = count;   /* pretend it succeeded */
    }
}

static void sys_open(registers_t* r) {
    const char* path = (const char*)r->rbx;
    vga_puts("[syscall] open: ");
    if (path) vga_puts(path);
    vga_puts("\n");
    serial_puts("[syscall] open\n");
    /* Return fd 3 (first "real" fd after 0/1/2) as a stub */
    r->rax = 3;
}

static void sys_close(registers_t* r) {
    vga_puts("[syscall] close fd=");
    vga_put_dec((int)r->rbx);
    vga_puts("\n");
    serial_puts("[syscall] close\n");
    r->rax = 0;
}

static void sys_mmap(registers_t* r) {
    vga_puts("[syscall] mmap addr=");
    vga_put_hex(r->rbx);
    vga_puts(" len=");
    vga_put_hex(r->rcx);
    vga_puts("\n");
    serial_puts("[syscall] mmap\n");
    /* Return a fake page-aligned address in upper memory */
    r->rax = 0x70000000;
}

static void sys_munmap(registers_t* r) {
    vga_puts("[syscall] munmap addr=");
    vga_put_hex(r->rbx);
    vga_puts("\n");
    serial_puts("[syscall] munmap\n");
    r->rax = 0;
}

static void sys_getpid(registers_t* r) {
    vga_puts("[syscall] getpid\n");
    serial_puts("[syscall] getpid\n");
    r->rax = task_get_pid();
}

static void sys_fork(registers_t* r) {
    vga_puts("[syscall] fork\n");
    serial_puts("[syscall] fork\n");
    /* child pid 0 閳?parent gets child pid; child gets 0.
     * Stub: return 0 (we are the "child") */
    r->rax = 0;
}

static void sys_execve(registers_t* r) {
    const char* path = (const char*)r->rbx;
    vga_puts("[syscall] execve: ");
    if (path) vga_puts(path);
    vga_puts("\n");
    serial_puts("[syscall] execve\n");
    r->rax = -1;   /* -ENOSYS */
}

static void sys_exit(registers_t* r) {
    int code = (int)r->rbx;
    vga_puts("[syscall] exit code=");
    vga_put_dec(code);
    vga_puts("\n");
    serial_puts("[syscall] exit\n");
    /* In a real OS this would tear down the process.
     * For now just halt the CPU in a loop. */
    vga_set_color(VGA_YELLOW, VGA_BLACK);
    vga_puts("\n=== Process exited with code ");
    vga_put_dec(code);
    vga_puts(" ===\n");
    vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
    for (;;) { asm volatile("hlt"); }
}

static void sys_clock_gettime(registers_t* r) {
    serial_puts("[syscall] clock_gettime\n");
    sys_clock_gettime_handler(r);
}

static void sys_getrandom(registers_t* r) {
    /* arg0 = buf, arg1 = count, arg2 = flags */
    uint8_t* buf = (uint8_t*)r->rbx;
    int count    = (int)r->rcx;
    vga_puts("[syscall] getrandom len=");
    vga_put_dec(count);
    vga_puts("\n");
    serial_puts("[syscall] getrandom\n");

    if (buf && count > 0) {
        if (count > 256) count = 256;  /* safety cap */
        for (int i = 0; i < count; i++) {
            buf[i] = (uint8_t)(rng_next() & 0xFF);
        }
        r->rax = count;
    } else {
        r->rax = 0;
    }
}

/* dispatch table indexed by syscall number */
static syscall_fn syscall_table[SYS_MAX_CALL + 1] = {
    [SYS_READ]          = sys_read,
    [SYS_WRITE]         = sys_write,
    [SYS_OPEN]          = sys_open,
    [SYS_CLOSE]         = sys_close,
    [SYS_MMAP]          = sys_mmap,
    [SYS_MUNMAP]        = sys_munmap,
    [SYS_GETPID]        = sys_getpid,
    [SYS_FORK]          = sys_fork,
    [SYS_EXECVE]        = sys_execve,
    [SYS_EXIT]          = sys_exit,
    [SYS_CLOCK_GETTIME] = sys_clock_gettime,
    [SYS_GETRANDOM]     = sys_getrandom,
};

/* ---------- public API ----------------------------------------------- */

void syscall_init(void) {
    /* Install int 0x80 on the IDT.
     * The stub is defined in isr.asm as syscall_stub and wired
     * in isr_handler via isr_register_handler(0x80, 閳?.
     * If the asm stub doesn't exist yet we register our C handler
     * directly so that any manual "int $0x80" still works. */
    extern void isr_handler(registers_t*);

    /* We re-use the isr handler vector mechanism:
     * put our handler at vector 128 (0x80). */
    isr_register_handler(0x80, syscall_handler);

    vga_puts("[BOOT] Syscall layer installed (int 0x80)\n");
    serial_puts("[BOOT] Syscall layer installed (int 0x80)\n");
}

void syscall_handler(registers_t* regs) {
    uint32_t call = regs->rax;

    if (call <= SYS_MAX_CALL && syscall_table[call]) {
        syscall_table[call](regs);
    } else {
        vga_puts("[syscall] unknown #");
        vga_put_dec(call);
        vga_puts("\n");
        serial_puts("[syscall] unknown\n");
        regs->rax = (uint32_t)-38;   /* -ENOSYS */
    }
}

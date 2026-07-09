/* BYO-OS - System Call Interface */
#include <kernel.h>

/* INT 0x80 handler stub - pushes registers and calls handler */
extern void syscall_stub(void);

void syscall_handler(registers_t* regs) {
    switch (regs->eax) {
        case 0: /* sys_exit */
            vga_puts("[syscall] exit\n");
            break;
        case 1: /* sys_write */
            break;
        case 2: /* sys_read */
            break;
        case 3: /* sys_yield */
            break;
        case 4: /* sys_getpid */
            regs->eax = 0;
            break;
        default:
            vga_puts("[syscall] unknown: ");
            vga_put_dec(regs->eax);
            vga_puts("\n");
            break;
    }
}

void syscall_init(void) {
    /* Note: syscall_stub must be defined in isr.asm for this to work.
       For now, this is a placeholder. The syscall mechanism will be
       fully enabled in a future version. */
}
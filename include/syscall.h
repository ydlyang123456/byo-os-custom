/* BYO-OS - Linux Syscall Compatibility Layer (x86_64 ABI Numbers) */
#ifndef SYSCALL_H
#define SYSCALL_H

#include <kernel.h>

/* Linux x86_64 syscall numbers */
#define SYS_READ        0
#define SYS_WRITE       1
#define SYS_OPEN        2
#define SYS_CLOSE       3
#define SYS_MMAP        9
#define SYS_MUNMAP      11
#define SYS_GETPID      39
#define SYS_FORK        57
#define SYS_EXECVE      59
#define SYS_EXIT        60
#define SYS_CLOCK_GETTIME 228
#define SYS_GETRANDOM   318

#define SYS_MAX_CALL    319

/* Initialize the syscall IDT entry (vector 0x80) */
void syscall_init(void);

/* Handler called from the int 0x80 stub */
void syscall_handler(registers_t* regs);

#endif

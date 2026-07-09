/* BYO-OS - Global Descriptor Table */
#include <kernel.h>

extern void gdt_init_asm(void);

void gdt_init(void) {
    gdt_init_asm();
}
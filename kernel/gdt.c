/* BYO-OS GDT - x86_64 */
#include <kernel.h>
extern void gdt_init_asm(void);
void gdt_init(void) {
    gdt_init_asm();
}
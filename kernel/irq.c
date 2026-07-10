/* BYO-OS IRQ - x86_64 */
#include <kernel.h>
static isr_t irq_handlers[16] = {0};
extern void irq32(void); extern void irq33(void); extern void irq34(void);
extern void irq35(void); extern void irq36(void); extern void irq37(void);
extern void irq38(void); extern void irq39(void); extern void irq40(void);
extern void irq41(void); extern void irq42(void); extern void irq43(void);
extern void irq44(void); extern void irq45(void); extern void irq46(void);
extern void irq47(void);
static void pic_remap(void) {
    outb(0x20, 0x11); outb(0xA0, 0x11);
    outb(0x21, 0x20); outb(0xA1, 0x28);
    outb(0x21, 0x04); outb(0xA1, 0x02);
    outb(0x21, 0x01); outb(0xA1, 0x01);
    outb(0x21, 0x0); outb(0xA1, 0x0);
}
void irq_init(void) {
    pic_remap();
    isr_register_handler(32, irq32); isr_register_handler(33, irq33);
    isr_register_handler(34, irq34); isr_register_handler(35, irq35);
    isr_register_handler(36, irq36); isr_register_handler(37, irq37);
    isr_register_handler(38, irq38); isr_register_handler(39, irq39);
    isr_register_handler(40, irq40); isr_register_handler(41, irq41);
    isr_register_handler(42, irq42); isr_register_handler(43, irq43);
    isr_register_handler(44, irq44); isr_register_handler(45, irq45);
    isr_register_handler(46, irq46); isr_register_handler(47, irq47);
}
void irq_handler(registers_t* regs) {
    int irq = regs->int_no - 32;
    if (irq >= 0 && irq < 16 && irq_handlers[irq])
        irq_handlers[irq](regs);
    if (irq >= 8) outb(0xA0, 0x20);
    outb(0x20, 0x20);
}
void isr_register_handler(int isr, isr_t handler) {
    if (isr >= 0 && isr < 48) irq_handlers[isr - 32] = handler;
}
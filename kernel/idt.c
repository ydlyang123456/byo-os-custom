/* BYO-OS IDT - x86_64 */
#include <kernel.h>
static idt_entry_t idt[256];
static idt_ptr_t idt_ptr;
extern void isr0(void); extern void isr1(void); extern void isr2(void);
extern void isr3(void); extern void isr4(void); extern void isr5(void);
extern void isr6(void); extern void isr7(void); extern void isr8(void);
extern void isr9(void); extern void isr10(void); extern void isr11(void);
extern void isr12(void); extern void isr13(void); extern void isr14(void);
extern void isr15(void); extern void isr16(void); extern void isr17(void);
extern void isr18(void); extern void isr19(void); extern void isr20(void);
extern void isr21(void); extern void isr22(void); extern void isr23(void);
extern void isr24(void); extern void isr25(void); extern void isr26(void);
extern void isr27(void); extern void isr28(void); extern void isr29(void);
extern void isr30(void); extern void isr31(void);
static isr_t isr_handlers[48] = {0};
void idt_set_gate(uint8_t num, uint32_t base_lo, uint16_t sel, uint8_t flags) {
    idt[num].base_lo = base_lo & 0xFFFF;
    idt[num].base_hi = (base_lo >> 16) & 0xFFFF;
    idt[num].base_upper = 0;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}
void idt_set_gate64(uint8_t num, uint64_t base, uint16_t sel, uint8_t flags) {
    idt[num].base_lo = base & 0xFFFF;
    idt[num].base_hi = (base >> 16) & 0xFFFF;
    idt[num].base_upper = (base >> 32) & 0xFFFFFFFF;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}
void idt_init(void) {
    idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;
    idt_ptr.base = (uint64_t)&idt;
    for (int i = 0; i < 256; i++) {
        idt_set_gate64(i, 0, 0, 0);
    }
    uint64_t isrs[] = {(uint64_t)isr0,(uint64_t)isr1,(uint64_t)isr2,(uint64_t)isr3,
        (uint64_t)isr4,(uint64_t)isr5,(uint64_t)isr6,(uint64_t)isr7,
        (uint64_t)isr8,(uint64_t)isr9,(uint64_t)isr10,(uint64_t)isr11,
        (uint64_t)isr12,(uint64_t)isr13,(uint64_t)isr14,(uint64_t)isr15,
        (uint64_t)isr16,(uint64_t)isr17,(uint64_t)isr18,(uint64_t)isr19,
        (uint64_t)isr20,(uint64_t)isr21,(uint64_t)isr22,(uint64_t)isr23,
        (uint64_t)isr24,(uint64_t)isr25,(uint64_t)isr26,(uint64_t)isr27,
        (uint64_t)isr28,(uint64_t)isr29,(uint64_t)isr30,(uint64_t)isr31};
    for (int i = 0; i < 32; i++)
        idt_set_gate64(i, isrs[i], 0x08, 0x8E);
    __asm__ volatile("lidt %0" : : "m"(idt_ptr));
}
void isr_handler(registers_t* regs) {
    if (regs->int_no < 48 && isr_handlers[regs->int_no])
        isr_handlers[regs->int_no](regs);
}

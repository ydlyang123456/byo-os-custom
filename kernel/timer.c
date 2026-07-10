/* BYO-OS Timer - x86_64 */
#include <kernel.h>
static volatile uint64_t tick_count = 0;
static void timer_callback(registers_t* regs) { tick_count++; }
void timer_init(uint32_t freq) {
    isr_register_handler(32, timer_callback);
    uint32_t divisor = 1193180 / freq;
    outb(0x43, 0x36);
    outb(0x40, divisor & 0xFF);
    outb(0x40, (divisor >> 8) & 0xFF);
}
uint32_t timer_get_ticks(void) { return (uint32_t)tick_count; }
uint32_t timer_get_seconds(void) { return (uint32_t)(tick_count / 100); }
void timer_sleep(uint32_t ms) {
    uint32_t target = tick_count + ms;
    while (tick_count < target) { __asm__ volatile("hlt"); }
}
/* BYO-OS - PIT Timer Driver */
#include <kernel.h>

static volatile uint32_t timer_ticks = 0;

void timer_handler(registers_t* regs) {
    (void)regs;
    timer_ticks++;
}

void timer_init(uint32_t freq) {
    timer_ticks = 0;
    uint32_t divisor = 1193180 / freq;
    outb(0x43, 0x36);
    io_wait();
    outb(0x40, (uint8_t)(divisor & 0xFF));
    io_wait();
    outb(0x40, (uint8_t)((divisor >> 8) & 0xFF));
    isr_register_handler(32, timer_handler);
}

uint32_t timer_get_ticks(void) {
    return timer_ticks;
}

uint32_t timer_get_seconds(void) {
    return timer_ticks / 100;
}

void timer_sleep(uint32_t ms) {
    uint32_t target = timer_ticks + ms;
    while (timer_ticks < target) {
        asm volatile("hlt");
    }
}
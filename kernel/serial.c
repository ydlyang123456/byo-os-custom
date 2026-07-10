/* BYO-OS Serial - x86_64 */
#include <kernel.h>
void serial_init(void) {
    outb(0x3F8 + 1, 0x00); outb(0x3F8 + 3, 0x80);
    outb(0x3F8 + 0, 0x03); outb(0x3F8 + 1, 0x00);
    outb(0x3F8 + 3, 0x03); outb(0x3F8 + 2, 0xC7);
    outb(0x3F8 + 4, 0x0B);
}
static int serial_tx_ready(void) { return inb(0x3F8 + 5) & 0x20; }
void serial_putchar(char c) {
    while (!serial_tx_ready()); outb(0x3F8, c);
}
void serial_puts(const char* s) { while (*s) { serial_putchar(*s == '\n' ? '\r' : *s); s++; } }
int serial_has_input(void) { return inb(0x3F8 + 5) & 1; }
int serial_getchar(void) { return serial_has_input() ? inb(0x3F8) : -1; }/* Missing functions referenced by vbe.c */
void serial_put_hex(uint32_t val) {
    char buf[12];
    itoa(val, buf, 16);
    serial_puts(buf);
}
void serial_put_dec(uint32_t val) {
    char buf[12];
    itoa(val, buf, 10);
    serial_puts(buf);
}

void serial_put_dec_u64(uint64_t val) {
    char buf[24];
    int i = 23;
    buf[23] = 0;
    if (val == 0) { serial_putchar('0'); return; }
    while (val > 0 && i > 0) {
        i--;
        buf[i] = '0' + (val % 10);
        val /= 10;
    }
    serial_puts(&buf[i]);
}

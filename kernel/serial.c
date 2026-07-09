/* BYO-OS - Serial Port (COM1) for Debug + Bidirectional Communication */
#include <kernel.h>

#define SERIAL_PORT 0x3F8

static int serial_transmit_empty(void) {
    return inb(SERIAL_PORT + 5) & 0x20;
}

void serial_init(void) {
    outb(SERIAL_PORT + 1, 0x00);
    outb(SERIAL_PORT + 3, 0x80);
    outb(SERIAL_PORT + 0, 0x03);
    outb(SERIAL_PORT + 1, 0x00);
    outb(SERIAL_PORT + 3, 0x03);
    outb(SERIAL_PORT + 2, 0xC7);
    outb(SERIAL_PORT + 4, 0x0B);
}

void serial_putchar(char c) {
    while (!serial_transmit_empty());
    outb(SERIAL_PORT, (uint8_t)c);
}

void serial_puts(const char* str) {
    while (*str) {
        if (*str == '\n') serial_putchar('\r');
        serial_putchar(*str++);
    }
}

int serial_has_input(void) {
    return inb(SERIAL_PORT + 5) & 0x01;
}

int serial_getchar(void) {
    if (!serial_has_input()) return -1;
    return inb(SERIAL_PORT);
}

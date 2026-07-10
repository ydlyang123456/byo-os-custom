/* BYO-OS VGA - x86_64 */
#include <kernel.h>
#include <stdarg.h>
static uint16_t* vga_mem = (uint16_t*)0xB8000;
static int vga_x = 0, vga_y = 0;
static uint8_t vga_color = 0x0F;
static int serial_mode = 0;
void vga_init(void) { vga_clear(); }
void vga_clear(void) {
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) vga_mem[i] = 0x0F20;
    vga_x = vga_y = 0;
}
void vga_set_color(enum vga_color fg, enum vga_color bg) { vga_color = (bg << 4) | fg; }
static void vga_scroll(void) {
    for (int i = 0; i < VGA_WIDTH * (VGA_HEIGHT - 1); i++) vga_mem[i] = vga_mem[i + VGA_WIDTH];
    for (int i = VGA_WIDTH * (VGA_HEIGHT - 1); i < VGA_WIDTH * VGA_HEIGHT; i++) vga_mem[i] = 0x0F20;
    vga_y = VGA_HEIGHT - 1;
}
void vga_putchar(char c) {
    if (serial_mode) { serial_putchar(c); return; }
    if (c == '\n') { vga_x = 0; vga_y++; }
    else if (c == '\r') { vga_x = 0; }
    else if (c == '\t') { vga_x = (vga_x + 8) & ~7; }
    else if (c == '\b') { if (vga_x > 0) vga_x--; }
    else { vga_mem[vga_y * VGA_WIDTH + vga_x] = (vga_color << 8) | c; vga_x++; }
    if (vga_x >= VGA_WIDTH) { vga_x = 0; vga_y++; }
    if (vga_y >= VGA_HEIGHT) vga_scroll();
}
void vga_puts(const char* str) { while (*str) vga_putchar(*str++); }
void vga_put_hex(uint32_t val) {
    char buf[12]; int i = 0;
    vga_puts("0x");
    for (int j = 7; j >= 0; j--) {
        int d = (val >> (j * 4)) & 0xF;
        buf[i++] = d < 10 ? '0' + d : 'a' + d - 10;
    }
    buf[i] = 0; vga_puts(buf);
}
void vga_put_dec(int val) {
    if (val < 0) { vga_putchar('-'); val = -val; }
    char buf[12]; int i = 0;
    if (val == 0) { vga_putchar('0'); return; }
    while (val > 0) { buf[i++] = '0' + val % 10; val /= 10; }
    for (int j = i - 1; j >= 0; j--) vga_putchar(buf[j]);
}
void vga_printf(const char* fmt, ...) {
    va_list ap; va_start(ap, fmt);
    while (*fmt) {
        if (*fmt == '%' && *(fmt+1)) {
            fmt++;
            if (*fmt == 's') { const char* s = va_arg(ap, const char*); vga_puts(s ? s : "(null)"); }
            else if (*fmt == 'd' || *fmt == 'i') { vga_put_dec(va_arg(ap, int)); }
            else if (*fmt == 'u') { vga_put_dec(va_arg(ap, unsigned int)); }
            else if (*fmt == 'x') { vga_put_hex(va_arg(ap, unsigned int)); }
            else if (*fmt == 'c') { vga_putchar((char)va_arg(ap, int)); }
            else if (*fmt == '%') { vga_putchar('%'); }
            else { vga_putchar('%'); vga_putchar(*fmt); }
        } else { vga_putchar(*fmt); }
        fmt++;
    }
    va_end(ap);
}
void vga_set_serial_mode(int mode) { serial_mode = mode; }
void vga_write_cell(int x, int y, char c, uint8_t color) {
    if (x >= 0 && x < VGA_WIDTH && y >= 0 && y < VGA_HEIGHT)
        vga_mem[y * VGA_WIDTH + x] = (color << 8) | c;
}
/* BYO-OS - VGA Text Mode Driver (VGA text buffer 0xB8000) */
#include <stdarg.h>
#include <kernel.h>

static uint16_t* vga_buffer;
static int serial_output_mode = 0;

void vga_set_serial_mode(int mode) { serial_output_mode = mode; }
static int vga_row;
static int vga_col;
static uint8_t vga_color;

void vga_init(void) {
    vga_buffer = (uint16_t*)0xB8000;
    vga_color = 0x07;
    vga_row = 0;
    vga_col = 0;
    for (int i = 0; i < 80*25; i++) vga_buffer[i] = 0x0720;
}

void vga_clear(void) {
    for (int i = 0; i < 80*25; i++) vga_buffer[i] = (vga_color << 8) | ' ';
    vga_row = 0;
    vga_col = 0;
}

void vga_set_color(enum vga_color fg, enum vga_color bg) {
    vga_color = fg | (bg << 4);
}

static void vga_scroll(void) {
    for (int i = 0; i < 80*24; i++) vga_buffer[i] = vga_buffer[i+80];
    for (int i = 80*24; i < 80*25; i++) vga_buffer[i] = (vga_color << 8) | ' ';
    vga_row = 24;
}

void vga_putchar(char c) {
    if (serial_output_mode) { serial_putchar(c); return; }
    if (c == '\n') { vga_col = 0; vga_row++; }
    else if (c == '\r') { vga_col = 0; }
    else if (c == '\b') { if (vga_col > 0) { vga_col--; vga_buffer[vga_row*80+vga_col] = (vga_color<<8)|' '; } }
    else {
        vga_buffer[vga_row*80+vga_col] = (vga_color << 8) | c;
        vga_col++;
    }
    if (vga_col >= 80) { vga_col = 0; vga_row++; }
    if (vga_row >= 25) vga_scroll();
}

void vga_puts(const char* s) {
    if (serial_output_mode) { serial_puts(s); return; }
    while (*s) vga_putchar(*s++);
}

void vga_put_dec(int val) {
    if (serial_output_mode) { char buf[16]; itoa(val, buf, 10); serial_puts(buf); return; }
    char buf[16]; itoa(val, buf, 10); vga_puts(buf);
}

void vga_put_hex(uint32_t val) {
    char buf[12]; char* p = buf+11; *p = 0;
    const char* hex = "0123456789abcdef";
    if (val == 0) *--p = '0';
    else while (val) { *--p = hex[val & 0xF]; val >>= 4; }
    vga_puts("0x"); vga_puts(p);
}

/* ===== Drawing Primitives (for desktop.c) ===== */
void gfx_draw_char(int x, int y, char ch, uint8_t color) {
    int idx = ch - 32;
    if (idx < 0 || idx > 94) return;
    uint8_t* fb = vga_get_framebuffer();
    if (!fb) return;
    uint16_t pitch = vga_get_pitch();
    for (int row = 0; row < 8; row++) {
        uint8_t bits = font8x8[idx][row];
        for (int col = 0; col < 8; col++) {
            if (bits & (0x80 >> col)) {
                int px = x + col;
                int py = y + row;
                if (px >= 0 && px < vga_get_width() && py >= 0 && py < vga_get_height())
                    fb[py * pitch + px] = color;
            }
        }
    }
}

void gfx_puts(int x, int y, const char* s, uint8_t color) {
    while (*s) {
        if (*s == '\n') { x = 0; y += 8; }
        else { gfx_draw_char(x, y, *s, color); x += 8; }
        s++;
    }
}

void gfx_putdec(int x, int y, int val, uint8_t color) {
    char buf[16];
    itoa(val, buf, 10);
    gfx_puts(x, y, buf, color);
}

/* Direct buffer access for panel */
void vga_write_cell(int x, int y, char c, uint8_t color) {
    if (x >= 0 && x < 80 && y >= 0 && y < 25)
        vga_buffer[y * 80 + x] = ((uint16_t)color << 8) | (uint8_t)c;
}


void vga_printf(const char* fmt, ...) {
    char buf[512];
    va_list ap;
    __builtin_va_start(ap, fmt);
    int bi = 0;
    for (const char* p = fmt; *p && bi < 510; p++) {
        if (*p != '%') { buf[bi++] = *p; continue; }
        p++;
        int pad = 0, padc = ' ';
        if (*p == '0') { padc = '0'; p++; }
        if (*p >= '1' && *p <= '9') { pad = *p - '0'; p++; }
        if (*p == 'd' || *p == 'i') {
            int val = __builtin_va_arg(ap, int);
            char tmp[16]; int ti = 0;
            if (val < 0) { buf[bi++] = '-'; val = -val; }
            if (val == 0) tmp[ti++] = '0';
            else { while (val > 0) { tmp[ti++] = '0' + val % 10; val /= 10; } }
            while (pad > ti) { buf[bi++] = padc; pad--; }
            for (int j = ti - 1; j >= 0; j--) buf[bi++] = tmp[j];
        } else if (*p == 's') {
            const char* s = __builtin_va_arg(ap, const char*);
            if (!s) s = "NULL";
            while (*s && bi < 510) buf[bi++] = *s++;
        } else if (*p == 'c') {
            buf[bi++] = (char)__builtin_va_arg(ap, int);
        } else if (*p == 'x') {
            unsigned int val = __builtin_va_arg(ap, unsigned int);
            const char* hex = "0123456789abcdef";
            char tmp[8]; int ti = 0;
            if (val == 0) tmp[ti++] = '0';
            else { while (val > 0) { tmp[ti++] = hex[val & 0xF]; val >>= 4; } }
            while (pad > ti) { buf[bi++] = padc; pad--; }
            for (int j = ti - 1; j >= 0; j--) buf[bi++] = tmp[j];
        } else if (*p == '%') {
            buf[bi++] = '%';
        }
    }
    buf[bi] = 0;
    __builtin_va_end(ap);
    vga_puts(buf);
}

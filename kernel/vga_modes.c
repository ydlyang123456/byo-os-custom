/* BYO-OS - VGA Mode Switching (Bochs VBE) */
#include <kernel.h>

#define DISPI_INDEX 0x1CE
#define DISPI_DATA  0x1CF
#define DISPI_XRES  1
#define DISPI_YRES  2
#define DISPI_BPP   3
#define DISPI_ENABLE 4
#define DISPI_ENABLED 0x01
#define DISPI_LFB   0x40
#define DISPI_DISABLED 0x00
#define VGA_DAC_WRITE 0x3C8
#define VGA_DAC_DATA  0x3C9
#define VGA_INPUT_STAT 0x3DA

static uint8_t* framebuffer = NULL;
static uint16_t fb_width = 0, fb_height = 0, fb_pitch = 0;

static void ser_hex(uint32_t v) {
    char buf[12]; char* p = buf+11; *p = 0;
    const char* h = "0123456789abcdef";
    if (v == 0) *--p = '0';
    else while (v) { *--p = h[v & 0xF]; v >>= 4; }
    serial_puts(p);
}
static void ser_dec(int v) {
    char buf[16]; itoa(v, buf, 10); serial_puts(buf);
}

static inline void dispi_write(uint16_t idx, uint16_t val) {
    outw(DISPI_INDEX, idx); outw(DISPI_DATA, val);
}
static inline uint16_t dispi_read(uint16_t idx) {
    outw(DISPI_INDEX, idx); return inw(DISPI_DATA);
}

static void vga_set_palette(void) {
    static const uint8_t pal[16][3] = {
        {0x00,0x00,0x00},{0x00,0x00,0xAA},{0x00,0xAA,0x00},{0x00,0xAA,0xAA},
        {0xAA,0x00,0x00},{0xAA,0x00,0xAA},{0xAA,0x55,0x00},{0xAA,0xAA,0xAA},
        {0x55,0x55,0x55},{0x55,0x55,0xFF},{0x55,0xFF,0x55},{0x55,0xFF,0xFF},
        {0xFF,0x55,0x55},{0xFF,0x55,0xFF},{0xFF,0xFF,0x55},{0xFF,0xFF,0xFF},
    };
    int t = 100000;
    while (t-- > 0 && (inb(VGA_INPUT_STAT) & 0x08));
    t = 100000;
    while (t-- > 0 && !(inb(VGA_INPUT_STAT) & 0x08));
    outb(VGA_DAC_WRITE, 0);
    for (int i = 0; i < 16; i++) {
        outb(VGA_DAC_DATA, pal[i][0] >> 2);
        outb(VGA_DAC_DATA, pal[i][1] >> 2);
        outb(VGA_DAC_DATA, pal[i][2] >> 2);
    }
    for (int i = 16; i < 256; i++) {
        uint8_t v = (uint8_t)i;
        outb(VGA_DAC_DATA, v >> 2);
        outb(VGA_DAC_DATA, v >> 2);
        outb(VGA_DAC_DATA, v >> 2);
    }
}

/* Not needed at boot - multiboot doesn't provide FB on this GRUB */
void vga_init_from_multiboot(multiboot_info_t* mbi) {
    (void)mbi;
    serial_puts("[VGA] Booting in text mode (no FB from GRUB)\n");
}

/* Switch to 320x200x256 via Bochs VBE */
int vga_set_mode_13h(void) {
    serial_puts("[VGA] Bochs VBE 320x200x8...\n");

    asm volatile("cli");
    dispi_write(DISPI_ENABLE, DISPI_DISABLED);
    dispi_write(DISPI_XRES, 320);
    dispi_write(DISPI_YRES, 200);
    dispi_write(DISPI_BPP, 8);
    dispi_write(DISPI_ENABLE, DISPI_ENABLED | DISPI_LFB);
    asm volatile("sti");

    uint16_t xres = dispi_read(DISPI_XRES);
    serial_puts("[VGA] DISPI xres="); ser_dec(xres);
    serial_puts(" yres="); ser_dec(dispi_read(DISPI_YRES));
    serial_puts(" bpp="); ser_dec(dispi_read(DISPI_BPP));
    serial_puts("\n");

    if (xres != 320) {
        serial_puts("[VGA] Bochs VBE not available!\n");
        return 0;
    }

    framebuffer = (uint8_t*)0xA0000;
    fb_width = 320; fb_height = 200; fb_pitch = 320;
    vga_set_palette();

    /* Test: fill a few pixels to verify LFB works */
    framebuffer[0] = 0x01;       /* top-left = blue */
    framebuffer[319] = 0x04;     /* top-right = red */
    framebuffer[199*320] = 0x02; /* bottom-left = green */
    framebuffer[199*320+319] = 0x0E; /* bottom-right = yellow */

    serial_puts("[VGA] Bochs VBE OK fb=");
    ser_hex((uint32_t)(uintptr_t)framebuffer);
    serial_puts(" pitch="); ser_dec(fb_pitch);
    serial_puts("\n");
    return 1;
}

/* Restore VGA text mode */
void vga_set_mode_text(void) {
    dispi_write(DISPI_ENABLE, DISPI_DISABLED);
    framebuffer = NULL;
    fb_width = 0; fb_height = 0; fb_pitch = 0;
    vga_clear();
    serial_puts("[VGA] Text mode restored\n");
}

uint8_t* vga_get_framebuffer(void) { return framebuffer; }
uint16_t vga_get_width(void)       { return fb_width; }
uint16_t vga_get_height(void)      { return fb_height; }
uint16_t vga_get_pitch(void)       { return fb_pitch; }

void vga_putpixel(int x, int y, uint8_t color) {
    if (framebuffer && x >= 0 && x < fb_width && y >= 0 && y < fb_height)
        framebuffer[y * fb_pitch + x] = color;
}

void vga_fill_rect(int x, int y, int w, int h, uint8_t color) {
    for (int j = y; j < y + h && j < fb_height; j++)
        for (int i = x; i < x + w && i < fb_width; i++)
            framebuffer[j * fb_pitch + i] = color;
}

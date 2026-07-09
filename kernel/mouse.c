/* BYO-OS - PS/2 Mouse Driver */
#include <kernel.h>

static int mouse_x = 0;
static int mouse_y = 0;
static uint8_t mouse_buttons = 0;
static uint8_t mouse_cycle = 0;
static uint8_t mouse_packet[3];

static void mouse_wait(uint8_t a) {
    uint32_t timeout = 100000;
    while (timeout--) { if ((inb(0x64) & 0x01) == a) return; }
}

static void mouse_write(uint8_t data) {
    mouse_wait(0x02); outb(0x64, 0xD4);
    mouse_wait(0x02); outb(0x60, data);
}

static uint8_t mouse_read(void) { mouse_wait(0x01); return inb(0x60); }

void mouse_handler(registers_t* regs) {
    (void)regs;
    mouse_packet[mouse_cycle] = inb(0x60);
    mouse_cycle = (mouse_cycle + 1) % 3;
    if (mouse_cycle == 0) {
        int dx = (int)mouse_packet[1];
        int dy = (int)mouse_packet[2];
        if (dx > 127) dx -= 256;
        if (dy > 127) dy -= 256;
        mouse_x += dx; mouse_y -= dy;
        if (mouse_x < 0) mouse_x = 0;
        if (mouse_y < 0) mouse_y = 0;
        if (mouse_x > 319) mouse_x = 319;
        if (mouse_y > 199) mouse_y = 199;
        mouse_buttons = mouse_packet[0] & 0x07;
    }
}

void mouse_init(void) {
    mouse_wait(0x02); outb(0x64, 0xA8);
    mouse_wait(0x02); outb(0x64, 0x20);
    mouse_wait(0x01); uint8_t s = inb(0x60);
    s |= 0x02; s &= ~0x20;
    mouse_wait(0x02); outb(0x64, 0x60);
    mouse_wait(0x02); outb(0x60, s);
    mouse_write(0xFF); mouse_read();
    mouse_write(0xF0); mouse_read();
    mouse_x = 160; mouse_y = 100;
    isr_register_handler(44, mouse_handler);
    serial_puts("[MOUSE] PS/2 mouse initialized\n");
}

int mouse_get_x(void) { return mouse_x; }
int mouse_get_y(void) { return mouse_y; }
uint8_t mouse_get_buttons(void) { return mouse_buttons; }

void mouse_draw_cursor(void) {
    uint8_t* fb = vga_get_framebuffer();
    if (!fb) return;
    uint16_t pitch = vga_get_pitch();
    uint16_t w = vga_get_width();
    uint16_t h = vga_get_height();
    int mx = mouse_x, my = mouse_y;

    /* Draw cross cursor using correct pitch */
    for (int i = -3; i <= 3; i++) {
        if (mx+i >= 0 && mx+i < w && my >= 0 && my < h)
            fb[my * pitch + mx + i] = 0x0F;
        if (mx >= 0 && mx < w && my+i >= 0 && my+i < h)
            fb[(my + i) * pitch + mx] = 0x0F;
    }
    /* Center pixel - black */
    if (mx >= 0 && mx < w && my >= 0 && my < h)
        fb[my * pitch + mx] = 0x00;
}

/* BYO-OS - VGA Graphics Mode Driver (320x200, 256 colors) */
#include <kernel.h>

#define GFX_WIDTH  320
#define GFX_HEIGHT 200
#define GFX_MEMORY ((uint8_t*)0xA0000)

static uint8_t* gfx_buffer = GFX_MEMORY;
static int gfx_mode = 0;

typedef struct {
    int x, y, w, h;
    uint8_t color;
    char title[32];
    int visible;
} window_t;

#define MAX_WINDOWS 8
static window_t windows[MAX_WINDOWS];

void gfx_init(void) {
    /* Switch to VGA mode 13h: 320x200, 256 colors */
    asm volatile(
        "mov $0x0013, %%ax\n"
        "int $0x10\n"
        :
        :
        : "ax"
    );
    gfx_mode = 1;
    memset(windows, 0, sizeof(windows));
    serial_puts("[GFX] VGA mode 13h: 320x200x256\n");
}

void gfx_set_mode_text(void) {
    asm volatile(
        "mov $0x0003, %%ax\n"
        "int $0x10\n"
        :
        :
        : "ax"
    );
    gfx_mode = 0;
}

void gfx_putpixel(int x, int y, uint8_t color) {
    if (x >= 0 && x < GFX_WIDTH && y >= 0 && y < GFX_HEIGHT) {
        gfx_buffer[y * GFX_WIDTH + x] = color;
    }
}

void gfx_fill_rect(int x, int y, int w, int h, uint8_t color) {
    for (int j = y; j < y + h; j++) {
        for (int i = x; i < x + w; i++) {
            gfx_putpixel(i, j, color);
        }
    }
}

void gfx_draw_rect(int x, int y, int w, int h, uint8_t color) {
    for (int i = x; i < x + w; i++) {
        gfx_putpixel(i, y, color);
        gfx_putpixel(i, y + h - 1, color);
    }
    for (int j = y; j < y + h; j++) {
        gfx_putpixel(x, j, color);
        gfx_putpixel(x + w - 1, j, color);
    }
}

void gfx_clear(uint8_t color) {
    memset(gfx_buffer, color, GFX_WIDTH * GFX_HEIGHT);
}

void gfx_draw_char(int x, int y, char c, uint8_t color) {
    /* Simple 8x8 bitmap font - minimal set */
    (void)x; (void)y; (void)c; (void)color;
    /* Placeholder: actual font data would go here */
}

void gfx_draw_string(int x, int y, const char* str, uint8_t color) {
    int cx = x;
    while (*str) {
        if (*str == '\n') {
            cx = x;
            y += 8;
        } else {
            gfx_draw_char(cx, y, *str, color);
            cx += 8;
        }
        str++;
    }
}

int gfx_create_window(int x, int y, int w, int h, const char* title, uint8_t color) {
    for (int i = 0; i < MAX_WINDOWS; i++) {
        if (!windows[i].visible) {
            windows[i].x = x;
            windows[i].y = y;
            windows[i].w = w;
            windows[i].h = h;
            windows[i].color = color;
            strncpy(windows[i].title, title, 31);
            windows[i].visible = 1;
            return i;
        }
    }
    return -1;
}

void gfx_draw_windows(void) {
    for (int i = 0; i < MAX_WINDOWS; i++) {
        if (windows[i].visible) {
            window_t* w = &windows[i];
            gfx_fill_rect(w->x, w->y, w->w, w->h, w->color);
            gfx_fill_rect(w->x, w->y, w->w, 12, 0x1F);
            gfx_draw_string(w->x + 4, w->y + 2, w->title, 0x0F);
            gfx_draw_rect(w->x, w->y, w->w, w->h, 0x0F);
        }
    }
}

void gfx_present(void) {
    gfx_draw_windows();
}

int gfx_get_mode(void) {
    return gfx_mode;
}

int gfx_get_width(void) { return GFX_WIDTH; }
int gfx_get_height(void) { return GFX_HEIGHT; }
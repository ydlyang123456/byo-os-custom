/* BYO-OS - Enhanced VGA Text-Mode Graphics (80x25)
 *
 * Provides windowing, buttons, menus, progress bars, clock,
 * status bar, scrolling, and a demo -- all using VGA text mode
 * via vga_write_cell().
 */
#include <kernel.h>

/* -- CP437 box-drawing characters --------------------------- */
#define BOX_TL  0xC9
#define BOX_TR  0xBB
#define BOX_BL  0xC8
#define BOX_BR  0xBC
#define BOX_V   0xBA
#define BOX_H   0xCD

/* -- Colour aliases ----------------------------------------- */
#define C_WHITE      0x07
#define C_BRIGHT     0x0F
#define C_BLUE_BG    0x1F
#define C_RED_BG     0x4F
#define C_GREEN_BG   0x2F
#define C_CYAN_BG    0x3F
#define C_DIM        0x08
#define C_GREEN      0x0A

/* -- Helpers required by desktop.c & kernel.h --------------- */

void gfx_draw_char(int x, int y, char ch, uint8_t color)
{
    (void)x; (void)y; (void)ch; (void)color;
}

void gfx_puts(int x, int y, const char* s, uint8_t color)
{
    int cx = x / 8;
    int cy = y / 8;
    if (cy < 0 || cy >= VGA_HEIGHT) return;
    while (*s && cx < VGA_WIDTH) {
        vga_write_cell(cx, cy, *s, color);
        cx++;
        s++;
    }
}

void gfx_putdec(int x, int y, int val, uint8_t color)
{
    char buf[16];
    itoa(val, buf, 10);
    gfx_puts(x, y, buf, color);
}

/* -- Internal string writer (cell coordinates) -------------- */
static void put_str_at(int x, int y, const char* s, uint8_t color)
{
    if (y < 0 || y >= VGA_HEIGHT) return;
    while (*s && x < VGA_WIDTH) {
        vga_write_cell(x, y, *s, color);
        x++;
        s++;
    }
}

static void put_char_at(int x, int y, char c, uint8_t color)
{
    if (x >= 0 && x < VGA_WIDTH && y >= 0 && y < VGA_HEIGHT)
        vga_write_cell(x, y, c, color);
}

/* -- Public API --------------------------------------------- */

void gfx_draw_rect(int x, int y, int w, int h, uint8_t color)
{
    if (x < 0) { w += x; x = 0; }
    if (y < 0) { h += y; y = 0; }
    if (x >= VGA_WIDTH || y >= VGA_HEIGHT) return;
    if (x + w > VGA_WIDTH)  w = VGA_WIDTH - x;
    if (y + h > VGA_HEIGHT) h = VGA_HEIGHT - y;
    if (w < 0 || h < 0) return;
    for (int row = y; row < y + h; row++)
        for (int col = x; col < x + w; col++)
            vga_write_cell(col, row, ' ', color);
}

void gfx_draw_border(int x, int y, int w, int h, uint8_t color)
{
    if (w < 2 || h < 2) return;
    if (x < 0 || y < 0 || x + w > VGA_WIDTH || y + h > VGA_HEIGHT) return;
    put_char_at(x,          y,          BOX_TL, color);
    put_char_at(x + w - 1,  y,          BOX_TR, color);
    put_char_at(x,          y + h - 1,  BOX_BL, color);
    put_char_at(x + w - 1,  y + h - 1,  BOX_BR, color);
    for (int i = 1; i < w - 1; i++) {
        put_char_at(x + i, y,           BOX_H, color);
        put_char_at(x + i, y + h - 1,   BOX_H, color);
    }
    for (int j = 1; j < h - 1; j++) {
        put_char_at(x,       y + j, BOX_V, color);
        put_char_at(x + w - 1, y + j, BOX_V, color);
    }
}

void gfx_draw_window(int x, int y, int w, int h, const char* title)
{
    if (w < 4 || h < 3) return;
    if (x < 0 || y < 0 || x + w > VGA_WIDTH || y + h > VGA_HEIGHT) return;
    gfx_draw_border(x, y, w, h, C_WHITE);
    for (int i = 1; i < w - 1; i++)
        put_char_at(x + i, y + 2, BOX_H, C_WHITE);
    for (int i = 1; i < w - 1; i++)
        put_char_at(x + i, y + 1, ' ', C_BLUE_BG);
    int title_len = strlen(title);
    int tx = x + (w - title_len) / 2;
    if (tx < x + 1) tx = x + 1;
    put_str_at(tx, y + 1, title, C_BRIGHT);
    put_char_at(x + w - 3, y + 1, 'X', C_RED_BG);
    for (int row = y + 3; row < y + h - 1; row++)
        for (int col = x + 1; col < x + w - 1; col++)
            vga_write_cell(col, row, ' ', C_WHITE);
}

void gfx_draw_button(int x, int y, int w, int h, const char* text, int pressed)
{
    if (w < 3 || h < 1) return;
    if (x < 0 || y < 0 || x + w > VGA_WIDTH || y + h > VGA_HEIGHT) return;
    uint8_t face   = pressed ? C_CYAN_BG : C_BLUE_BG;
    uint8_t shadow = pressed ? C_WHITE : C_DIM;
    uint8_t hilite = pressed ? C_DIM   : C_WHITE;
    for (int row = y; row < y + h; row++)
        for (int col = x; col < x + w; col++)
            vga_write_cell(col, row, ' ', face);
    for (int i = 0; i < w; i++) put_char_at(x + i, y,           ' ', hilite);
    for (int j = 0; j < h; j++) put_char_at(x,       y + j,     ' ', hilite);
    for (int i = 0; i < w; i++) put_char_at(x + i, y + h - 1,   ' ', shadow);
    for (int j = 0; j < h; j++) put_char_at(x + w - 1, y + j,   ' ', shadow);
    int tl = strlen(text);
    int tx = x + (w - tl) / 2;
    if (tx < x + 1) tx = x + 1;
    put_str_at(tx, y + h / 2, text, C_BRIGHT);
}

void gfx_draw_progress(int x, int y, int w, int pct)
{
    if (w < 2) return;
    if (y < 0 || y >= VGA_HEIGHT) return;
    if (x < 0 || x + w + 2 >= VGA_WIDTH) return;
    if (pct < 0) pct = 0;
    if (pct > 100) pct = 100;
    int filled = pct * w / 100;
    char pct_buf[8];
    itoa(pct, pct_buf, 10);
    int label_len = strlen(pct_buf) + 1;
    int label_x = x + (w - label_len) / 2;
    if (label_x < x) label_x = x;
    put_char_at(x, y, '[', C_WHITE);
    for (int i = 0; i < w; i++) {
        char ch;
        uint8_t col;
        if (i < filled) {
            if (i == filled - 1 && pct < 100) { ch = '>'; col = C_GREEN; }
            else { ch = '='; col = C_GREEN; }
        } else {
            ch = ' ';
            col = C_DIM;
        }
        if (i >= label_x - x - 1 && i < label_x - x - 1 + label_len) {
            int idx = i - (label_x - x - 1);
            if (idx >= 0 && idx < label_len) {
                ch = pct_buf[idx];
                if (idx == label_len - 1) ch = '%';
                col = C_BRIGHT;
            }
        }
        vga_write_cell(x + 1 + i, y, ch, col);
    }
    put_char_at(x + 1 + w, y, ']', C_WHITE);
}

void gfx_draw_menu(int x, int y, const char** items, int count)
{
    if (count <= 0) return;
    if (x < 0 || y < 0 || y + count + 1 >= VGA_HEIGHT) return;
    int max_w = 0;
    for (int i = 0; i < count; i++) {
        int len = strlen(items[i]);
        if (len > max_w) max_w = len;
    }
    int menu_w = max_w + 4;
    if (x + menu_w >= VGA_WIDTH) menu_w = VGA_WIDTH - x - 1;
    if (menu_w < 4) menu_w = 4;
    int menu_h = count + 2;
    gfx_draw_border(x, y, menu_w, menu_h, C_WHITE);
    for (int i = 0; i < count; i++) {
        int row = y + 1 + i;
        uint8_t item_color = (i == 0) ? C_BLUE_BG : C_WHITE;
        for (int col = x + 1; col < x + menu_w - 1; col++)
            vga_write_cell(col, row, ' ', item_color);
        put_str_at(x + 2, row, items[i], (i == 0) ? C_BRIGHT : C_WHITE);
    }
}

void gfx_draw_clock(int x, int y)
{
    if (y < 0 || y >= VGA_HEIGHT) return;
    if (x + 9 >= VGA_WIDTH) return;
    int h, m, s;
    rtc_get_time(&h, &m, &s);
    char buf[10];
    buf[0] = '0' + h / 10;
    buf[1] = '0' + h % 10;
    buf[2] = ':';
    buf[3] = '0' + m / 10;
    buf[4] = '0' + m % 10;
    buf[5] = ':';
    buf[6] = '0' + s / 10;
    buf[7] = '0' + s % 10;
    buf[8] = '\0';
    put_str_at(x, y, "[", C_WHITE);
    put_str_at(x + 1, y, buf, C_CYAN_BG);
    put_str_at(x + 8, y, "]", C_WHITE);
}

void gfx_draw_statusbar(const char* text)
{
    int y = VGA_HEIGHT - 1;
    if (y < 0) return;
    for (int col = 0; col < VGA_WIDTH; col++)
        vga_write_cell(col, y, ' ', C_BLUE_BG);
    put_str_at(0, y, " BYO-OS ", C_BRIGHT);
    int max_len = VGA_WIDTH - 20;
    char tmp[VGA_WIDTH];
    int i;
    for (i = 0; i < max_len && text[i]; i++) tmp[i] = text[i];
    tmp[i] = '\0';
    int cx = (VGA_WIDTH - i) / 2;
    if (cx < 10) cx = 10;
    put_str_at(cx, y, tmp, C_WHITE);
    uint32_t sec = timer_get_seconds();
    int tm = (sec / 60) % 60;
    int ts = sec % 60;
    char tbuf[8];
    tbuf[0] = '0' + tm / 10;
    tbuf[1] = '0' + tm % 10;
    tbuf[2] = ':';
    tbuf[3] = '0' + ts / 10;
    tbuf[4] = '0' + ts % 10;
    tbuf[5] = '\0';
    put_str_at(VGA_WIDTH - 7, y, tbuf, C_BRIGHT);
}

void gfx_clear_area(int x, int y, int w, int h)
{
    if (x < 0) { w += x; x = 0; }
    if (y < 0) { h += y; y = 0; }
    if (x >= VGA_WIDTH || y >= VGA_HEIGHT) return;
    if (x + w > VGA_WIDTH)  w = VGA_WIDTH - x;
    if (y + h > VGA_HEIGHT) h = VGA_HEIGHT - y;
    if (w < 0 || h < 0) return;
    for (int row = y; row < y + h; row++)
        for (int col = x; col < x + w; col++)
            vga_write_cell(col, row, ' ', C_WHITE);
}

void gfx_scroll_up(int lines)
{
    if (lines <= 0) return;
    if (lines >= VGA_HEIGHT) {
        gfx_clear_area(0, 0, VGA_WIDTH, VGA_HEIGHT);
        return;
    }
    uint16_t* vga = (uint16_t*)VGA_MEMORY;
    int copy_cells = (VGA_HEIGHT - lines) * VGA_WIDTH;
    for (int i = 0; i < copy_cells; i++)
        vga[i] = vga[i + lines * VGA_WIDTH];
    int clear_start = (VGA_HEIGHT - lines) * VGA_WIDTH;
    int clear_end   = VGA_HEIGHT * VGA_WIDTH;
    for (int i = clear_start; i < clear_end; i++)
        vga[i] = 0x0720;
}

void gfx_demo(void)
{
    vga_clear();
    put_str_at(28, 0, " BYO-OS Graphics Demo ", C_BLUE_BG);
    put_str_at(2, 2, "1) Rectangle & Border", C_BRIGHT);
    gfx_draw_rect(2, 3, 20, 5, C_GREEN_BG);
    gfx_draw_border(2, 3, 20, 5, C_WHITE);
    put_str_at(5, 5, "Filled", C_BRIGHT);
    put_str_at(2, 10, "2) Window", C_BRIGHT);
    gfx_draw_window(2, 11, 22, 6, "Demo Win");
    put_str_at(28, 2, "3) Buttons", C_BRIGHT);
    gfx_draw_button(28, 3, 14, 3, "Press", 0);
    gfx_draw_button(28, 7, 14, 3, "Click", 1);
    put_str_at(28, 12, "4) Progress", C_BRIGHT);
    gfx_draw_progress(28, 13, 30, 27);
    gfx_draw_progress(28, 15, 30, 62);
    gfx_draw_progress(28, 17, 30, 100);
    put_str_at(55, 2, "5) Menu", C_BRIGHT);
    { const char* demo_items[] = { "Open", "Save", "Exit" };
      gfx_draw_menu(55, 3, demo_items, 3); }
    put_str_at(55, 8, "6) Clock", C_BRIGHT);
    gfx_draw_clock(60, 9);
    put_str_at(55, 12, "7) Statusbar", C_BRIGHT);
    gfx_draw_statusbar("Welcome to BYO-OS Enhanced Graphics");
    put_str_at(55, 15, "8) Clear & Scroll", C_BRIGHT);
    put_str_at(55, 16, "Area cleared below:", C_WHITE);
    gfx_draw_rect(55, 17, 20, 4, C_RED_BG);
    gfx_clear_area(58, 18, 14, 2);
    put_str_at(58, 18, "Cleared!", C_BRIGHT);
    for (int col = 0; col < VGA_WIDTH; col++)
        vga_write_cell(col, VGA_HEIGHT - 2, BOX_H, C_DIM);
    put_str_at(2, VGA_HEIGHT - 1,
        " [Q]uit | [S]croll up 3  | Demo shows all gfx primitives ",
        C_BLUE_BG);
    int running = 1;
    while (running) {
        if (keyboard_has_input()) {
            int ch = keyboard_getchar();
            switch (ch) {
                case 'q': case 'Q': case 0x1B:
                    running = 0;
                    break;
                case 's': case 'S':
                    gfx_scroll_up(3);
                    put_str_at(2, VGA_HEIGHT - 3,
                        " Scrolled! Press [S] again or [Q] to quit. ",
                        C_DIM);
                    break;
                default:
                    break;
            }
        }
        gfx_draw_clock(60, 9);
        for (volatile int d = 0; d < 30000; d++);
    }
    vga_clear();
    vga_puts("Graphics demo finished.\n");
}

/* EOF */

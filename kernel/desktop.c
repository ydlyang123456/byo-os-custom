/* BYO-OS - Desktop Environment
 *
 * Renders a window manager, icons, taskbar, and applications
 * on the VGA framebuffer (320x200x256).
 * Uses shared font8x8 from font.c and drawing primitives from vga.c.
 */
#include <kernel.h>

#define DESKTOP_W 320
#define DESKTOP_H 200
#define TASKBAR_H 16
#define TASKBAR_Y (DESKTOP_H - TASKBAR_H)
#define MAX_WINS 8
#define MAX_ICONS 8

/* ===== Framebuffer Drawing Helpers ===== */
static void gp(int x, int y, uint8_t c) {
    if (x >= 0 && x < DESKTOP_W && y >= 0 && y < DESKTOP_H) {
        uint16_t pitch = vga_get_pitch();
        uint8_t* fb = vga_get_framebuffer();
        if (fb) fb[y * pitch + x] = c;
    }
}

static void gfill(int x, int y, int w, int h, uint8_t c) {
    for (int j = y; j < y + h && j < DESKTOP_H; j++)
        for (int i = x; i < x + w && i < DESKTOP_W; i++)
            gp(i, j, c);
}

static void grect(int x, int y, int w, int h, uint8_t c) {
    for (int i = x; i < x + w; i++) { gp(i, y, c); gp(i, y + h - 1, c); }
    for (int j = y; j < y + h; j++) { gp(x, j, c); gp(x + w - 1, j, c); }
}

/* ===== Window Manager ===== */
typedef struct {
    int x, y, w, h;
    char title[32];
    uint8_t title_color, bg_color;
    int visible, focused;
    int dragging, drag_ox, drag_oy;
    char content[2048];
    int content_len;
    int app_type;
} win_t;

#define APP_NONE 0
#define APP_FILEMAN 1
#define APP_EDITOR 2
#define APP_CALC 3
#define APP_TERMINAL 4
#define APP_SETTINGS 5

static win_t wins[MAX_WINS];
static int win_count = 0;
static int active_win = -1;

static void wm_init(void) {
    for (int i = 0; i < MAX_WINS; i++) wins[i].visible = 0;
    win_count = 0;
    active_win = -1;
}

static int wm_create(int x, int y, int w, int h, const char* title, uint8_t tc, uint8_t bg, int app) {
    for (int i = 0; i < MAX_WINS; i++) {
        if (!wins[i].visible) {
            wins[i].x = x; wins[i].y = y; wins[i].w = w; wins[i].h = h;
            strncpy(wins[i].title, title, 31); wins[i].title[31] = '\0';
            wins[i].title_color = tc; wins[i].bg_color = bg;
            wins[i].visible = 1; wins[i].focused = 0;
            wins[i].dragging = 0; wins[i].content_len = 0;
            wins[i].app_type = app;
            wins[i].content[0] = '\0';
            active_win = i;
            win_count++;
            return i;
        }
    }
    return -1;
}

static void wm_close(int id) {
    if (id >= 0 && id < MAX_WINS) {
        wins[id].visible = 0;
        if (active_win == id) active_win = -1;
    }
}

static void wm_draw(void) {
    for (int i = 0; i < MAX_WINS; i++) {
        if (!wins[i].visible) continue;
        win_t* w = &wins[i];
        /* Shadow */
        gfill(w->x + 3, w->y + 3, w->w, w->h, 0x08);
        /* Window body */
        gfill(w->x, w->y, w->w, w->h, w->bg_color);
        /* Title bar */
        uint8_t tc = w->focused ? 0x1F : 0x17;
        gfill(w->x + 1, w->y + 1, w->w - 2, 11, tc);
        gfx_puts(w->x + 4, w->y + 2, w->title, 0x0F);
        /* Close button [X] */
        gfill(w->x + w->w - 12, w->y + 2, 10, 9, 0x04);
        gfx_puts(w->x + w->w - 10, w->y + 3, "X", 0x0F);
        /* Border */
        grect(w->x, w->y, w->w, w->h, w->focused ? 0x0F : 0x07);
        /* Content */
        if (w->content_len > 0) {
            gfx_puts(w->x + 4, w->y + 14, w->content, 0x00);
        }
    }
}

static void wm_focus(int id) {
    for (int i = 0; i < MAX_WINS; i++) wins[i].focused = 0;
    if (id >= 0 && id < MAX_WINS && wins[id].visible) {
        wins[id].focused = 1;
        active_win = id;
    }
}

static int wm_hit_test(int mx, int my) {
    for (int i = MAX_WINS - 1; i >= 0; i--) {
        if (!wins[i].visible) continue;
        win_t* w = &wins[i];
        if (mx >= w->x && mx < w->x + w->w && my >= w->y && my < w->y + w->h)
            return i;
    }
    return -1;
}

/* ===== Taskbar ===== */
static void taskbar_draw(void) {
    gfill(0, TASKBAR_Y, DESKTOP_W, TASKBAR_H, 0x17);
    grect(0, TASKBAR_Y, DESKTOP_W, TASKBAR_H, 0x0F);

    /* Start button */
    gfill(2, TASKBAR_Y + 2, 36, 12, 0x1F);
    gfx_puts(6, TASKBAR_Y + 4, "BYO", 0x0F);

    /* Active window buttons */
    int bx = 42;
    for (int i = 0; i < MAX_WINS; i++) {
        if (!wins[i].visible) continue;
        uint8_t bc = (i == active_win) ? 0x1F : 0x17;
        gfill(bx, TASKBAR_Y + 2, 60, 12, bc);
        gfx_puts(bx + 2, TASKBAR_Y + 4, wins[i].title, 0x0F);
        bx += 64;
    }

    /* Clock */
    char time[8];
    uint32_t sec = timer_get_seconds();
    int m = sec / 60;
    int s = sec % 60;
    itoa(m, time, 10);
    if (strlen(time) < 2) { time[2] = '\0'; time[1] = time[0]; time[0] = '0'; }
    int l = strlen(time);
    time[l] = ':'; time[l + 1] = '\0';
    char sec_s[4];
    itoa(s, sec_s, 10);
    if (strlen(sec_s) < 2) { sec_s[2] = '\0'; sec_s[1] = sec_s[0]; sec_s[0] = '0'; }
    strcat(time, sec_s);
    gfx_puts(DESKTOP_W - 40, TASKBAR_Y + 4, time, 0x0F);
}

/* ===== Desktop Icons ===== */
typedef struct {
    int x, y;
    char label[16];
    uint8_t color;
    int app_type;
} icon_t;

static icon_t desktop_icons[] = {
    {10,  10, "Files",    0x1C, APP_FILEMAN},
    {10,  50, "Editor",   0x1A, APP_EDITOR},
    {10,  90, "Calc",     0x1E, APP_CALC},
    {10, 130, "Terminal", 0x12, APP_TERMINAL},
};
#define ICON_COUNT 4

static void icons_draw(void) {
    for (int i = 0; i < ICON_COUNT; i++) {
        icon_t* ic = &desktop_icons[i];
        /* Icon box */
        gfill(ic->x, ic->y, 32, 32, ic->color);
        grect(ic->x, ic->y, 32, 32, 0x0F);
        /* First letter as icon */
        gfx_draw_char(ic->x + 12, ic->y + 10, ic->label[0], 0x0F);
        /* Label */
        gfx_puts(ic->x - 4, ic->y + 34, ic->label, 0x0F);
    }
}

static int icon_hit_test(int mx, int my) {
    for (int i = 0; i < ICON_COUNT; i++) {
        icon_t* ic = &desktop_icons[i];
        if (mx >= ic->x && mx < ic->x + 32 && my >= ic->y && my < ic->y + 32)
            return i;
    }
    return -1;
}

/* ===== App Launchers ===== */
static void app_files(int id) {
    char buf[1024];
    fs_list_dir("/", buf, sizeof(buf));
    strncpy(wins[id].content, buf, 2047);
    wins[id].content_len = strlen(wins[id].content);
}

static void app_editor(int id) {
    strncpy(wins[id].content, "BYO-OS Text Editor\n\nType in shell:\n  write <file> <text>\n  cat <file>", 2047);
    wins[id].content_len = strlen(wins[id].content);
}

static void app_calc(int id) {
    strncpy(wins[id].content, "Calculator\n\n  1+1 = 2\n  2*3 = 6\n  10-5 = 5\n  (shell: echo)", 2047);
    wins[id].content_len = strlen(wins[id].content);
}

static void app_terminal(int id) {
    strncpy(wins[id].content, "BYO-OS Terminal\n\nUse shell commands\nin text mode.\nType 'gui' to return.", 2047);
    wins[id].content_len = strlen(wins[id].content);
}

static void app_settings(int id) {
    strncpy(wins[id].content, "Settings\n\nResolution: 320x200\nColors: 256\nMouse: PS/2", 2047);
    wins[id].content_len = strlen(wins[id].content);
}

static void launch_app(int type) {
    const char* names[] = {"", "Files", "Editor", "Calculator", "Terminal", "Settings"};
    uint8_t colors[] = {0, 0x07, 0x07, 0x3E, 0x10, 0x17};
    int w = (type == APP_FILEMAN) ? 200 : 180;
    int h = (type == APP_FILEMAN) ? 160 : 120;
    int x = 50 + (win_count % 5) * 20;
    int y = 20 + (win_count % 4) * 15;
    int id = wm_create(x, y, w, h, names[type], 0x0F, colors[type], type);
    if (id < 0) return;
    wm_focus(id);
    switch (type) {
        case APP_FILEMAN: app_files(id); break;
        case APP_EDITOR: app_editor(id); break;
        case APP_CALC: app_calc(id); break;
        case APP_TERMINAL: app_terminal(id); break;
        case APP_SETTINGS: app_settings(id); break;
    }
}

/* ===== Main Desktop Loop ===== */
void gfx_desktop_run(void) {
    /* Framebuffer is already set up by GRUB (gfxpayload=keep)
     * or by Bochs VBE fallback. Just verify it's ready. */
    if (!vga_get_framebuffer()) {
        serial_puts("[DESKTOP] No framebuffer, trying Bochs VBE...\n");
        vga_set_mode_13h();
    }
    if (!vga_get_framebuffer()) {
        serial_puts("[DESKTOP] ERROR: No framebuffer available\n");
        return;
    }
    serial_puts("[DESKTOP] VGA 320x200x256 ready\n");

    mouse_init();
    wm_init();

    /* Draw initial desktop */
    gfill(0, 0, DESKTOP_W, TASKBAR_Y, 0x01);  /* Blue desktop */
    icons_draw();
    taskbar_draw();

    /* Open a welcome window */
    int wid = wm_create(60, 30, 200, 100, "Welcome", 0x0F, 0x07, APP_NONE);
    strncpy(wins[wid].content, "BYO-OS Desktop\n\nClick icons to\nopen applications.\n\nDrag windows to\nmove them.", 2047);
    wins[wid].content_len = strlen(wins[wid].content);
    wm_focus(wid);

    int prev_mx = mouse_get_x(), prev_my = mouse_get_y();
    int mouse_was_down = 0;

    while (1) {
        /* Handle mouse */
        int mx = mouse_get_x();
        int my = mouse_get_y();
        int mouse_down = mouse_get_buttons() & 0x01;
        int mouse_clicked = mouse_down && !mouse_was_down;

        /* Dragging window */
        if (active_win >= 0 && wins[active_win].dragging && mouse_down) {
            wins[active_win].x += mx - prev_mx;
            wins[active_win].y += my - prev_my;
            if (wins[active_win].x < 0) wins[active_win].x = 0;
            if (wins[active_win].y < 0) wins[active_win].y = 0;
            if (wins[active_win].x + wins[active_win].w > DESKTOP_W)
                wins[active_win].x = DESKTOP_W - wins[active_win].w;
            if (wins[active_win].y + wins[active_win].h > TASKBAR_Y)
                wins[active_win].y = TASKBAR_Y - wins[active_win].h;
        } else if (active_win >= 0 && wins[active_win].dragging && !mouse_down) {
            wins[active_win].dragging = 0;
        }

        /* Click handling */
        if (mouse_clicked) {
            int wid_hit = wm_hit_test(mx, my);

            if (wid_hit >= 0) {
                /* Clicked on a window */
                wm_focus(wid_hit);
                win_t* w = &wins[wid_hit];

                /* Close button? */
                if (mx >= w->x + w->w - 12 && mx < w->x + w->w - 2 &&
                    my >= w->y + 2 && my < w->y + 11) {
                    wm_close(wid_hit);
                }
                /* Title bar? (start drag) */
                else if (my >= w->y && my < w->y + 12) {
                    w->dragging = 1;
                    w->drag_ox = mx - w->x;
                    w->drag_oy = my - w->y;
                }
            } else {
                /* Clicked on desktop */
                /* Taskbar start button? */
                if (my >= TASKBAR_Y && mx >= 2 && mx < 38) {
                    launch_app(APP_SETTINGS);
                }
                /* Taskbar window buttons? */
                else if (my >= TASKBAR_Y) {
                    int bx = 42;
                    for (int i = 0; i < MAX_WINS; i++) {
                        if (!wins[i].visible) continue;
                        if (mx >= bx && mx < bx + 60) {
                            wm_focus(i);
                            break;
                        }
                        bx += 64;
                    }
                }
                /* Desktop icons? */
                else {
                    int ic = icon_hit_test(mx, my);
                    if (ic >= 0) {
                        launch_app(desktop_icons[ic].app_type);
                    }
                }
            }
        }

        mouse_was_down = mouse_down;
        prev_mx = mx;
        prev_my = my;

        /* Redraw */
        gfill(0, 0, DESKTOP_W, TASKBAR_Y, 0x01);
        icons_draw();
        wm_draw();
        taskbar_draw();
        mouse_draw_cursor();

        /* Check for key to exit */
        if (keyboard_has_input()) {
            char k = keyboard_getchar();
            if (k == '\x1B' || k == 'q' || k == 'Q') break;
        }

        /* Small delay */
        for (volatile int d = 0; d < 50000; d++);
    }

    /* Return to text mode (clear framebuffer) */
    vga_set_mode_text();
    vga_clear();
    serial_puts("[DESKTOP] Exited to text mode\n");
}

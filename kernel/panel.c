/* BYO-OS - System Management Panel (like BT Panel) */
#include <kernel.h>

#define PANEL_W 80
#define PANEL_H 25
#define MAX_MENU_ITEMS 12
#define MAX_FILE_LIST 20

/* ===== Box Drawing Helpers ===== */
static void box_hline(int x, int y, int w, uint8_t color) {
    for (int i = 0; i < w; i++)
        vga_write_cell(x + i, y, '-', color);
}

static void box_vline(int x, int y, int h, uint8_t color) {
    for (int j = 0; j < h; j++)
        vga_write_cell(x, y + j, '|', color);
}

static void box_draw(int x, int y, int w, int h, uint8_t border_color, uint8_t bg_color) {
    for (int j = y; j < y + h; j++)
        for (int i = x; i < x + w; i++)
            vga_write_cell(i, j, ' ', bg_color);
    vga_write_cell(x, y, '+', border_color);
    vga_write_cell(x+w-1, y, '+', border_color);
    vga_write_cell(x, y+h-1, '+', border_color);
    vga_write_cell(x+w-1, y+h-1, '+', border_color);
    for (int i = x+1; i < x+w-1; i++) {
        vga_write_cell(i, y, '=', border_color);
        vga_write_cell(i, y+h-1, '=', border_color);
    }
    for (int j = y+1; j < y+h-1; j++) {
        vga_write_cell(x, j, '|', border_color);
        vga_write_cell(x+w-1, j, '|', border_color);
    }
}

static void panel_print(int x, int y, const char* s, uint8_t color) {
    int cx = x;
    while (*s && cx < PANEL_W) {
        if (*s == '\n') { cx = x; y++; }
        else { vga_write_cell(cx, y, *s, color); cx++; }
        s++;
    }
}

static void panel_clear(void) {
    for (int y = 0; y < 25; y++)
        for (int x = 0; x < 80; x++)
            vga_write_cell(x, y, ' ', 0x07);
}

/* ===== Wait for key ===== */
static void wait_key(void) {
    vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
    panel_print(2, 24, "[Press any key to continue...]", 0x07);
    /* Wait for key via keyboard port */
    while (!(inb(0x64) & 1));
    inb(0x60);
}

/* ===== Wait for input string ===== */
static void wait_input(char* buf, int max_len) {
    int pos = 0;
    buf[0] = '\0';
    while (1) {
        if (inb(0x64) & 1) {
            uint8_t sc = inb(0x60);
            if (sc & 0x80) continue; /* key release */
            char c = 0;
            /* Simple scancode set 1 to ASCII */
            static const char sc2ascii[] = {
                0,27,'1','2','3','4','5','6','7','8','9','0','-','=', 8, 9,
                'q','w','e','r','t','y','u','i','o','p','[',']', 13, 0,
                'a','s','d','f','g','h','j','k','l',';',39,'`', 0, 92,
                'z','x','c','v','b','n','m',',','.','/', 0, '*', 0, ' '
            };
            if (sc < sizeof(sc2ascii)) c = sc2ascii[sc];
            if (c == 13) { /* Enter */
                vga_putchar('\n');
                return;
            } else if (c == 8 && pos > 0) { /* Backspace */
                pos--;
                buf[pos] = '\0';
                vga_putchar('\b');
            } else if (c >= 32 && c < 127 && pos < max_len - 1) {
                buf[pos++] = c;
                buf[pos] = '\0';
                vga_putchar(c);
            }
        }
        for (volatile int d = 0; d < 5000; d++);
    }
}

/* ===== Progress Bar ===== */
static void progress_bar(int x, int y, int width, int pct, uint8_t color) {
    int filled = (width * pct) / 100;
    for (int i = 0; i < width; i++) {
        char ch = (i < filled) ? '#' : '-';
        vga_write_cell(x + i, y, ch, color);
    }
}

/* ========================================== */
/*           1. SYSTEM DASHBOARD              */
/* ========================================== */
static void panel_dashboard(void) {
    panel_clear();
    panel_print(1, 0, "+======================================================================+", 0x0B);
    panel_print(1, 1, "|                     BYO-OS System Management Panel                   |", 0x0B);
    panel_print(1, 2, "+======================================================================+", 0x0B);

    /* System info */
    panel_print(2, 4, "System:    BYO-OS v0.2 Beta", 0x0F);
    panel_print(2, 5, "Kernel:    x86 (i686) Multiboot", 0x07);
    panel_print(2, 6, "Uptime:    ", 0x07);
    int sec = timer_get_seconds();
    char buf[32];
    itoa(sec / 3600, buf, 10); panel_print(12, 6, buf, 0x0A); panel_print(12 + strlen(buf), 6, "h ", 0x07);
    itoa((sec % 3600) / 60, buf, 10); panel_print(14 + strlen(buf) - strlen(buf), 6, buf, 0x0A);
    /* fix position */
    int m = (sec % 3600) / 60;
    int s = sec % 60;
    char time_s[32];
    itoa(sec / 3600, time_s, 10);
    strcat(time_s, "h ");
    char tmp[8];
    itoa(m, tmp, 10); strcat(time_s, tmp); strcat(time_s, "m ");
    itoa(s, tmp, 10); strcat(time_s, tmp); strcat(time_s, "s");
    panel_print(12, 6, "                    ", 0x07);
    panel_print(12, 6, time_s, 0x0A);

    /* Memory */
    uint32_t total = pmm_get_total_pages() * 4;
    uint32_t free = pmm_get_free_pages() * 4;
    uint32_t used = total - free;
    panel_print(2, 8, "Memory:    ", 0x0F);
    itoa(total, buf, 10); panel_print(12, 8, buf, 0x0A); panel_print(12 + strlen(buf), 8, " MB total", 0x07);
    panel_print(2, 9, "           ", 0x0F);
    itoa(used, buf, 10); panel_print(12, 9, buf, 0x0C); panel_print(12 + strlen(buf), 9, " MB used", 0x07);
    panel_print(2, 10, "           ", 0x0F);
    itoa(free, buf, 10); panel_print(12, 10, buf, 0x0A); panel_print(12 + strlen(buf), 10, " MB free", 0x07);

    int pct = total > 0 ? (int)(used * 100 / total) : 0;
    panel_print(2, 11, "Usage:     ", 0x0F);
    progress_bar(12, 11, 40, pct, pct > 80 ? 0x0C : 0x0A);
    char pct_s[8];
    itoa(pct, pct_s, 10);
    strcat(pct_s, "%");
    panel_print(53, 11, pct_s, 0x0F);

    /* Heap */
    panel_print(2, 13, "Heap:      ", 0x0F);
    itoa(heap_get_used(), buf, 10); panel_print(12, 13, buf, 0x0A); panel_print(12 + strlen(buf), 13, " bytes used", 0x07);

    /* Filesystem */
    panel_print(2, 15, "Filesystem: ramdisk (tmpfs)", 0x07);
    char fbuf[256];
    int fcount = 0;
    fs_list_dir("/", fbuf, sizeof(fbuf));
    for (int i = 0; fbuf[i]; i++) if (fbuf[i] == '\n') fcount++;
    panel_print(2, 16, "Files:     ", 0x0F);
    itoa(fcount, buf, 10); panel_print(12, 16, buf, 0x0A); panel_print(12 + strlen(buf), 16, " items", 0x07);

    /* Tasks */
    panel_print(2, 18, "Tasks:     ", 0x0F);
    itoa(task_get_count(), buf, 10); panel_print(12, 18, buf, 0x0A); panel_print(12 + strlen(buf), 18, " active", 0x07);

    /* Network */
    panel_print(2, 20, "Network:   ", 0x0F);
    char ip[32]; net_get_ip_str(ip);
    panel_print(12, 20, ip, 0x0A); panel_print(12 + strlen(ip), 20, " (eth0)", 0x07);

    /* User */
    panel_print(2, 21, "User:      ", 0x0F);
    panel_print(12, 21, user_get_name(), 0x0A);
    char lvl[32];
    switch (user_get_level()) {
        case USER_ROOT: strcpy(lvl, "root (uid=0)"); break;
        case USER_ADMIN: strcpy(lvl, "admin (uid=2)"); break;
        case USER_USER: strcpy(lvl, "user (uid=1)"); break;
        default: strcpy(lvl, "guest (uid=0)"); break;
    }
    panel_print(12, 22, lvl, 0x07);

    panel_print(2, 24, "[1]Monitor [2]Files [3]Users [4]Network [5]Settings [ESC]Exit", 0x0E);
    wait_key();
}

/* ========================================== */
/*           2. SYSTEM MONITOR                */
/* ========================================== */
static void panel_monitor(void) {
    panel_clear();
    panel_print(1, 0, "+======================================================================+", 0x0B);
    panel_print(1, 1, "|                        System Monitor                                |", 0x0B);
    panel_print(1, 2, "+======================================================================+", 0x0B);

    /* Memory bars */
    panel_print(2, 4, "=== Memory ===", 0x0E);
    uint32_t total = pmm_get_total_pages() * 4;
    uint32_t free = pmm_get_free_pages() * 4;
    uint32_t used = total - free;
    char buf[32];

    panel_print(2, 6, "Physical: ", 0x07);
    itoa(used, buf, 10); panel_print(12, 6, buf, 0x0C); panel_print(12+strlen(buf), 6, "/", 0x07);
    itoa(total, buf, 10); panel_print(13+strlen(buf)-strlen(buf), 6, buf, 0x0A);
    panel_print(13+strlen(buf), 6, " MB  ", 0x07);
    int pct = total > 0 ? (int)(used * 100 / total) : 0;
    progress_bar(40, 6, 30, pct, pct > 80 ? 0x0C : 0x0A);
    itoa(pct, buf, 10); strcat(buf, "%");
    panel_print(71, 6, buf, 0x0F);

    panel_print(2, 7, "Heap:     ", 0x07);
    itoa(heap_get_used(), buf, 10); panel_print(12, 7, buf, 0x0C);
    panel_print(12+strlen(buf), 7, " bytes allocated", 0x07);

    /* Process table */
    panel_print(2, 9, "=== Processes ===", 0x0E);
    panel_print(2, 11, " PID  NAME                STATE     MEM", 0x08);
    panel_print(2, 12, " ---  ----                -----     ---", 0x08);
    int count = task_get_count();
    for (int i = 0; i < count && i < 10; i++) {
        panel_print(4, 13 + i, "  -   (kernel task)       running   -  ", 0x07);
    }
    itoa(count, buf, 10);
    panel_print(2, 14 + (count > 10 ? 10 : count), "Total: ", 0x07);
    panel_print(9, 14 + (count > 10 ? 10 : count), buf, 0x0A); panel_print(9+strlen(buf), 14+(count>10?10:count), " tasks", 0x07);

    /* Timer */
    panel_print(2, 19, "=== Timer ===", 0x0E);
    panel_print(2, 21, "Ticks:    ", 0x07);
    itoa(timer_get_ticks(), buf, 10); panel_print(12, 21, buf, 0x0A);
    panel_print(2, 22, "Seconds:  ", 0x07);
    itoa(timer_get_seconds(), buf, 10); panel_print(12, 22, buf, 0x0A);

    panel_print(2, 24, "[ESC] Back", 0x0E);
    wait_key();
}

/* ========================================== */
/*           3. FILE MANAGER                  */
/* ========================================== */
static void panel_filemanager(void) {
    panel_clear();
    panel_print(1, 0, "+======================================================================+", 0x0B);
    panel_print(1, 1, "|                          File Manager                                |", 0x0B);
    panel_print(1, 2, "+======================================================================+", 0x0B);

    char listing[2048];
    fs_list_dir("/", listing, sizeof(listing));

    panel_print(2, 4, "=== Files in / ===", 0x0E);
    int y = 6;
    int count = 0;
    char* p = listing;
    while (*p && y < 20) {
        /* Check if it's a directory (ends with /) */
        int is_dir = 0;
        char line[64];
        int li = 0;
        while (*p && *p != '\n') {
            line[li++] = *p++;
            if (*p == '/') is_dir = 1;
        }
        line[li] = '\0';
        if (*p == '\n') p++;

        panel_print(4, y, is_dir ? "[DIR]  " : "[FILE] ", is_dir ? 0x0B : 0x07);
        panel_print(11, y, line, 0x0F);

        /* Show file size */
        if (!is_dir) {
            int sz = fs_file_size(line);
            char szbuf[16];
            itoa(sz, szbuf, 10);
            strcat(szbuf, " bytes");
            panel_print(40, y, szbuf, 0x08);
        }
        y++;
        count++;
    }

    if (count == 0) {
        panel_print(4, 6, "(empty directory)", 0x08);
    }

    itoa(count, listing, 10);
    panel_print(2, 21, "Total: ", 0x07); panel_print(9, 21, listing, 0x0A);
    panel_print(9+strlen(listing), 21, " items", 0x07);

    panel_print(2, 22, "Filesystem: ramdisk (tmpfs)", 0x08);
    panel_print(2, 23, "Use shell commands: ls, cat, touch, write, rm, mkdir", 0x08);

    panel_print(2, 24, "[ESC] Back", 0x0E);
    wait_key();
}

/* ========================================== */
/*           4. USER MANAGEMENT               */
/* ========================================== */
static void panel_users(void) {
    panel_clear();
    panel_print(1, 0, "+======================================================================+", 0x0B);
    panel_print(1, 1, "|                        User Management                              |", 0x0B);
    panel_print(1, 2, "+======================================================================+", 0x0B);

    panel_print(2, 4, "=== Current User ===", 0x0E);
    panel_print(2, 6, "Username:  ", 0x07); panel_print(13, 6, user_get_name(), 0x0A);

    char lvl[32];
    switch (user_get_level()) {
        case USER_ROOT: strcpy(lvl, "root (Administrator)"); break;
        case USER_ADMIN: strcpy(lvl, "admin (Power User)"); break;
        case USER_USER: strcpy(lvl, "user (Standard)"); break;
        default: strcpy(lvl, "guest (Limited)"); break;
    }
    panel_print(2, 7, "Level:     ", 0x07); panel_print(13, 7, lvl, 0x0A);

    panel_print(2, 8, "UID:       ", 0x07);
    char buf[8]; itoa(user_get_uid(), buf, 10); panel_print(13, 8, buf, 0x0A);

    panel_print(2, 10, "=== All Users ===", 0x0E);
    char ulist[1024];
    user_list_users(ulist, sizeof(ulist));
    int y = 12;
    char* p = ulist;
    while (*p && y < 20) {
        char line[128];
        int li = 0;
        while (*p && *p != '\n') { line[li++] = *p++; }
        line[li] = '\0';
        if (*p == '\n') p++;
        panel_print(4, y, line, 0x07);
        y++;
    }

    panel_print(2, 22, "Shell commands: login <user> <pass>, logout, users", 0x08);
    panel_print(2, 24, "[ESC] Back", 0x0E);
    wait_key();
}

/* ========================================== */
/*           5. NETWORK INFO                  */
/* ========================================== */
static void panel_network(void) {
    panel_clear();
    panel_print(1, 0, "+======================================================================+", 0x0B);
    panel_print(1, 1, "|                         Network Info                                 |", 0x0B);
    panel_print(1, 2, "+======================================================================+", 0x0B);

    panel_print(2, 4, "=== eth0 ===", 0x0E);

    panel_print(2, 6, "IP Address:  ", 0x07);
    char ip[32]; net_get_ip_str(ip); panel_print(15, 6, ip, 0x0A);

    panel_print(2, 7, "MAC Address: ", 0x07);
    uint8_t* mac = net_get_mac();
    char hex[4]; char mac_s[32]; mac_s[0] = '\0';
    for (int i = 0; i < 6; i++) {
        if (i > 0) strcat(mac_s, ":");
        itoa(mac[i], hex, 16);
        if (strlen(hex) < 2) { char tmp[4] = "0"; strcat(tmp, hex); strcpy(hex, tmp); }
        strcat(mac_s, hex);
    }
    panel_print(15, 7, mac_s, 0x0A);

    panel_print(2, 8, "Status:      ", 0x07); panel_print(15, 8, "Ready", 0x0A);
    panel_print(2, 9, "Speed:       ", 0x07); panel_print(15, 9, "10 Mbps (emulated)", 0x07);
    panel_print(2, 10, "Type:        ", 0x07); panel_print(15, 10, "QEMU NE2000 (pcnet)", 0x07);

    panel_print(2, 12, "=== Routing ===", 0x0E);
    panel_print(2, 14, "Default GW:  ", 0x07); panel_print(15, 14, "10.0.2.2", 0x07);
    panel_print(2, 15, "Subnet:      ", 0x07); panel_print(15, 15, "255.255.255.0", 0x07);
    panel_print(2, 16, "DNS:         ", 0x07); panel_print(15, 16, "8.8.8.8", 0x07);

    panel_print(2, 18, "=== Stats ===", 0x0E);
    panel_print(2, 20, "TX Packets:  ", 0x07); panel_print(15, 20, "0", 0x0A);
    panel_print(2, 21, "RX Packets:  ", 0x07); panel_print(15, 21, "0", 0x0A);
    panel_print(2, 22, "Errors:      ", 0x07); panel_print(15, 22, "0", 0x0A);

    panel_print(2, 24, "[ESC] Back", 0x0E);
    wait_key();
}

/* ========================================== */
/*           6. SETTINGS                      */
/* ========================================== */
static void panel_settings(void) {
    panel_clear();
    panel_print(1, 0, "+======================================================================+", 0x0B);
    panel_print(1, 1, "|                           Settings                                   |", 0x0B);
    panel_print(1, 2, "+======================================================================+", 0x0B);

    panel_print(2, 4, "=== System ===", 0x0E);
    panel_print(2, 6, "OS:         BYO-OS v0.2 Beta", 0x07);
    panel_print(2, 7, "Arch:       x86 (i686)", 0x07);
    panel_print(2, 8, "Boot:       GRUB Multiboot", 0x07);
    panel_print(2, 9, "Display:    VGA Text 80x25", 0x07);
    panel_print(2, 10, "Graphics:   Bochs VBE 320x200x256 (gui mode)", 0x07);

    panel_print(2, 12, "=== Hardware ===", 0x0E);
    panel_print(2, 14, "CPU:        x86 (QEMU TCG)", 0x07);
    panel_print(2, 15, "RAM:        ", 0x07);
    char buf[16]; itoa(pmm_get_total_pages() * 4, buf, 10);
    panel_print(14, 15, buf, 0x0A); panel_print(14+strlen(buf), 15, " MB", 0x07);
    panel_print(2, 16, "Storage:    tmpfs (ramdisk)", 0x07);
    panel_print(2, 17, "Input:      PS/2 Keyboard + Mouse", 0x07);
    panel_print(2, 18, "Network:    NE2000 (QEMU emulated)", 0x07);
    panel_print(2, 19, "Serial:     COM1 (0x3F8)", 0x07);

    panel_print(2, 21, "=== Features ===", 0x0E);
    panel_print(2, 22, "[x] GDT/IDT  [x] IRQ/PIC  [x] Timer  [x] Keyboard", 0x07);
    panel_print(2, 23, "[x] Mouse    [x] PMM      [x] Heap   [x] Scheduler", 0x07);
    panel_print(2, 24, "[x] FS       [x] Network  [x] Users  [x] Serial", 0x07);

    wait_key();
}

/* ========================================== */
/*           MAIN PANEL LOOP                  */
/* ========================================== */
void panel_run(void) {
    while (1) {
        panel_clear();
        panel_print(1, 0, "+======================================================================+", 0x0B);
        panel_print(1, 1, "|                                                                      |", 0x0B);
        panel_print(1, 2, "|              B Y O - O S   M a n a g e m e n t   P a n e l           |", 0x0B);
        panel_print(1, 3, "|                                                                      |", 0x0B);
        panel_print(1, 4, "+======================================================================+", 0x0B);

        panel_print(2, 6,  "  [1] System Dashboard     - Overview of system status", 0x0F);
        panel_print(2, 8,  "  [2] System Monitor       - Memory, CPU, processes", 0x0F);
        panel_print(2, 10, "  [3] File Manager         - Browse filesystem", 0x0F);
        panel_print(2, 12, "  [4] User Management      - Users, permissions", 0x0F);
        panel_print(2, 14, "  [5] Network Info         - IP, MAC, routing", 0x0F);
        panel_print(2, 16, "  [6] Settings             - System configuration", 0x0F);
        panel_print(2, 18, "  [7] Quick Shell          - Drop to command line", 0x0F);

        panel_print(2, 21, "+======================================================================+", 0x08);
        panel_print(2, 22, "  Select [1-7] or press ESC to exit panel:  ", 0x0E);

        /* Wait for input */
        while (1) {
            if (inb(0x64) & 1) {
                uint8_t sc = inb(0x60);
                if (sc & 0x80) continue;
                char c = 0;
                static const char sc2[] = {
                    0,27,'1','2','3','4','5','6','7','8','9','0','-','=', 8, 9,
                    'q','w','e','r','t','y','u','i','o','p','[',']', 13, 0,
                    'a','s','d','f','g','h','j','k','l',';',39,'`', 0, 92,
                    'z','x','c','v','b','n','m',',','.','/', 0, '*', 0, ' '
                };
                if (sc < sizeof(sc2)) c = sc2[sc];

                if (c == 27) return; /* ESC */
                if (c == '1') { panel_dashboard(); break; }
                if (c == '2') { panel_monitor(); break; }
                if (c == '3') { panel_filemanager(); break; }
                if (c == '4') { panel_users(); break; }
                if (c == '5') { panel_network(); break; }
                if (c == '6') { panel_settings(); break; }
                if (c == '7') {
                    /* Quick shell - just exit panel */
                    vga_clear();
                    return;
                }
            }
            for (volatile int d = 0; d < 5000; d++);
        }
    }
}


/* BYO-OS Panel - x86_64 Enhanced */
#include <kernel.h>

void box_hline(int x1, int x2, int y, char c) {
    for (int i = x1; i <= x2; i++) vga_write_cell(i, y, c, 0x07);
}

void box_vline(int x, int y1, int y2, char c) {
    for (int i = y1; i <= y2; i++) vga_write_cell(x, i, c, 0x07);
}

void box_draw(int x, int y, int w, int h) {
    box_hline(x, x+w-1, y, '-');
    box_hline(x, x+w-1, y+h-1, '-');
    box_vline(x, y, y+h-1, '|');
    box_vline(x+w-1, y, y+h-1, '|');
}

void panel_print(int x, int y, const char* s, uint8_t color) {
    while (*s) { vga_write_cell(x++, y, *s++, color); }
}

void panel_clear(void) { vga_clear(); }

int wait_key(void) {
    while (!keyboard_has_input()) { __asm__ volatile("hlt"); }
    return keyboard_getchar();
}

int wait_input(char* buf, int max) {
    int i = 0;
    while (i < max - 1) {
        int c = keyboard_getchar();
        if (c < 0) continue;
        if (c == '\n') { buf[i] = 0; return i; }
        buf[i++] = c;
    }
    buf[i] = 0;
    return i;
}

void progress_bar(int x, int y, int w, int pct) {
    int filled = pct * w / 100;
    vga_write_cell(x, y, '[', 0x07);
    for (int i = 0; i < w; i++) vga_write_cell(x+1+i, y, i < filled ? '=' : ' ', 0x0A);
    vga_write_cell(x+1+w, y, ']', 0x07);
}

void panel_dashboard(void) {
    panel_clear();
    panel_print(2, 1, "BYO-OS Dashboard - Debian 12 Compatible", 0x0B);

    /* System info */
    panel_print(2, 3, "OS: Debian GNU/Linux 12 (bookworm)", 0x07);
    panel_print(2, 4, "Kernel: BYO-OS x86_64", 0x07);
    panel_print(2, 5, "Architecture: x86_64", 0x07);
    panel_print(2, 6, "BT Panel: Compatible", 0x0A);

    /* Memory info */
    uint64_t total = pmm_get_total_pages_64();
    uint64_t free = pmm_get_free_pages_64();
    uint64_t used = total - free;
    uint32_t total_mb = (uint32_t)(total * 4 / 1024);
    uint32_t used_mb = (uint32_t)(used * 4 / 1024);
    char buf[32];

    panel_print(2, 8, "Memory:     ", 0x07);
    itoa(total_mb, buf, 10); panel_print(12, 8, buf, 0x0F);
    panel_print(12 + strlen(buf), 8, " MB total, ", 0x07);
    itoa(used_mb, buf, 10); panel_print(12 + strlen(buf) + 11, 8, buf, 0x0F);
    panel_print(12 + strlen(buf) + 11 + strlen(buf), 8, " MB used", 0x07);

    /* CPU / Uptime */
    uint32_t sec = timer_get_seconds();
    int h = (sec / 3600) % 24, m = (sec / 60) % 60, s = sec % 60;
    panel_print(2, 9, "Uptime:     ", 0x07);
    itoa(h, buf, 10); panel_print(13, 9, buf, 0x0F);
    panel_print(13 + strlen(buf), 9, "h ", 0x07);
    itoa(m, buf, 10); panel_print(13 + strlen(buf) + 2, 9, buf, 0x0F);
    panel_print(13 + strlen(buf) + 2 + strlen(buf), 9, "m ", 0x07);
    itoa(s, buf, 10); panel_print(13 + strlen(buf) + 2 + strlen(buf) + 2, 9, buf, 0x0F);
    panel_print(13 + strlen(buf) + 2 + strlen(buf) + 2 + strlen(buf), 9, "s", 0x07);

    /* Services status */
    panel_print(2, 11, "Services:   SSH (running)  Web (stopped)  DB (stopped)", 0x07);

    /* Network info */
    panel_print(2, 13, "Network:    10.0.2.15/24  (qemu user mode)", 0x07);

    /* BT Panel status */
    panel_print(2, 15, "BT Panel:   Ready - http://localhost:8888", 0x0B);

    panel_print(2, 17, "Press any key to return to shell...", 0x08);
    wait_key();
    vga_init();
}

void panel_monitor(void) {
    panel_clear();
    panel_print(2, 1, "System Monitor (refresh every 2s)", 0x0B);

    for (int i = 0; i < 5; i++) {
        uint64_t total = pmm_get_total_pages_64();
        uint64_t free = pmm_get_free_pages_64();
        uint64_t used = total - free;
        uint32_t pct = (uint32_t)(used * 100 / (total > 0 ? total : 1));
        char buf[32];

        panel_print(2, 3, "Memory: ", 0x07);
        itoa((uint32_t)(used * 4 / 1024), buf, 10); panel_print(10, 3, buf, 0x0F);
        panel_print(10 + strlen(buf), 3, " MB / ", 0x07);
        itoa((uint32_t)(total * 4 / 1024), buf, 10); panel_print(10 + strlen(buf) + 6, 3, buf, 0x0F);
        panel_print(10 + strlen(buf) + 6 + strlen(buf), 3, " MB", 0x07);

        progress_bar(2, 5, 30, (int)pct);
        panel_print(34, 5, " ", 0x07);
        itoa((int)pct, buf, 10); panel_print(35, 5, buf, 0x0F);
        panel_print(35 + strlen(buf), 5, "%", 0x07);

        timer_sleep(2000);
    }

    panel_print(2, 8, "Monitoring finished. Press any key...", 0x08);
    wait_key();
    vga_init();
}

void panel_filemanager(void) {
    panel_clear();
    panel_print(2, 1, "File Manager", 0x0B);
    panel_print(2, 3, "/", 0x0F);
    panel_print(2, 4, "  etc/     - Config files", 0x07);
    panel_print(2, 5, "  home/    - User home directories", 0x07);
    panel_print(2, 6, "  tmp/     - Temporary files", 0x07);
    panel_print(2, 7, "  root/    - Root home", 0x07);
    panel_print(2, 8, "  var/     - Variable data", 0x07);
    panel_print(2, 9, "  usr/     - System resources", 0x07);
    panel_print(2, 10, "  opt/     - Optional software", 0x07);
    panel_print(2, 12, "Press any key to return...", 0x08);
    wait_key();
    vga_init();
}

void panel_users(void) {
    panel_clear();
    panel_print(2, 1, "User Manager", 0x0B);
    panel_print(2, 3, "root    - Superuser", 0x0F);
    panel_print(2, 4, "byo     - Default user", 0x07);
    panel_print(2, 5, "www-data - Web server", 0x07);
    panel_print(2, 6, "sshd    - SSH daemon", 0x07);
    panel_print(2, 7, "syslog  - System logger", 0x07);
    panel_print(2, 9, "Press any key to return...", 0x08);
    wait_key();
    vga_init();
}

void panel_network(void) {
    panel_clear();
    panel_print(2, 1, "Network Status", 0x0B);
    panel_print(2, 3, "eth0:    10.0.2.15/24", 0x07);
    panel_print(2, 4, "Gateway: 10.0.2.2", 0x07);
    panel_print(2, 5, "DNS:     10.0.2.3", 0x07);
    panel_print(2, 6, "MAC:     52:54:00:12:34:56", 0x07);
    panel_print(2, 8, "Web Panel: http://localhost:7777", 0x0B);
    panel_print(2, 9, "BT Panel:  http://localhost:8888", 0x0B);
    panel_print(2, 11, "Press any key to return...", 0x08);
    wait_key();
    vga_init();
}

void panel_settings(void) {
    panel_clear();
    panel_print(2, 1, "Settings", 0x0B);
    panel_print(2, 3, "1) Change hostname", 0x07);
    panel_print(2, 4, "2) Set timezone", 0x07);
    panel_print(2, 5, "3) Network config", 0x07);
    panel_print(2, 6, "4) Service management", 0x07);
    panel_print(2, 7, "5) BT Panel management", 0x0B);
    panel_print(2, 9, "Press any key to return...", 0x08);
    wait_key();
    vga_init();
}

void panel_run(void) {
    panel_dashboard();
}

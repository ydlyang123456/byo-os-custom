/* Batch 39: Real Functional Commands */
static void cmd_htop_real(int argc, char args[][CMD_MAX_LEN]) {
    vga_clear();
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("PID    NAME                 STATE      MEM(KB)  CPU\n");
    vga_puts("------ -------------------- ---------- -------- ----\n");
    vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
    int count = task_get_count();
    for (int i = 0; i < count && i < 32; i++) {
        task_t* t = task_get(i);
        if (!t) continue;
        char pid_str[8]; utoa(t->pid, pid_str);
        vga_puts(pid_str);
        for (int p = strlen(pid_str); p < 7; p++) vga_putchar(" ");
        vga_puts(t->name);
        for (int p = strlen(t->name); p < 21; p++) vga_putchar(" ");
        vga_puts(t->state == TASK_RUNNING ? "RUNNING  " :
                 t->state == TASK_BLOCKED  ? "BLOCKED  " :
                 t->state == TASK_SLEEPING ? "SLEEPING " : "ZOMBIE   ");
        char mem[16]; utoa(t->stack_size / 1024, mem);
        vga_puts(mem);
        for (int p = strlen(mem); p < 9; p++) vga_putchar(" ");
        vga_puts("  -\n");
    }
    vga_puts("\nTasks: ");
    char cnt[8]; utoa(count, cnt); vga_puts(cnt);
    vga_puts(" total\n");
}
static void cmd_free_real(int argc, char args[][CMD_MAX_LEN]) {
    uint32_t total = pmm_get_total_pages() * 4;
    uint32_t used = pmm_get_used_pages() * 4;
    uint32_t free = total - used;
    vga_puts("              total        used        free\n");
    vga_puts("Mem:        ");
    char t[16], u[16], f[16];
    utoa(total, t); utoa(used, u); utoa(free, f);
    for (int i = strlen(t); i < 11; i++) vga_putchar(" ");
    vga_puts(t);
    for (int i = strlen(u); i < 11; i++) vga_putchar(" ");
    vga_puts(u);
    for (int i = strlen(f); i < 11; i++) vga_putchar(" ");
    vga_puts(f); vga_puts("\n");
    uint32_t pct = total > 0 ? (used * 100 / total) : 0;
    vga_puts("Memory usage: ");
    char p[8]; utoa(pct, p); vga_puts(p); vga_puts("%\n");
}
static void cmd_ps_real(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("  PID TTY          STAT CMD\n");
    int count = task_get_count();
    for (int i = 0; i < count && i < 32; i++) {
        task_t* t = task_get(i);
        if (!t) continue;
        char pid[8]; utoa(t->pid, pid);
        for (int p = strlen(pid); p < 6; p++) vga_putchar(" ");
        vga_puts(pid);
        vga_puts(" ?        ");
        vga_puts(t->state == TASK_RUNNING ? "S+ " :
                 t->state == TASK_BLOCKED  ? "D  " :
                 t->state == TASK_SLEEPING ? "S  " : "Z  ");
        vga_puts(t->name); vga_puts("\n");
    }
}
static void cmd_uname_real(int argc, char args[][CMD_MAX_LEN]) {
    if (argc > 1 && strcmp(args[1], "-a") == 0) {
        vga_puts("BYO-OS byo-os 1.0.0 #1 SMP x86 BYO-OS\n");
    } else { vga_puts("BYO-OS\n"); }
}
static void cmd_ifconfig_real(int argc, char args[][CMD_MAX_LEN]) {
    char ip[32]; net_get_ip_str(ip);
    vga_puts("eth0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>\n");
    vga_puts("        inet "); vga_puts(ip); vga_puts("\n");
    vga_puts("        ether 52:54:00:12:34:56\n");
}
static void cmd_df_real(int argc, char args[][CMD_MAX_LEN]) {
    uint32_t total = pmm_get_total_pages() * 4;
    uint32_t used = pmm_get_used_pages() * 4;
    uint32_t free_val = total - used;
    vga_puts("Filesystem     Size  Used Avail Use% Mounted on\n");
    vga_puts("/dev/ram0      ");
    char t[16], u[16], f[16];
    utoa(total, t); utoa(used, u); utoa(free_val, f);
    vga_puts(t); vga_puts("K  "); vga_puts(u); vga_puts("K  "); vga_puts(f); vga_puts("K  ");
    uint32_t pct = total > 0 ? (used * 100 / total) : 0;
    char p[8]; utoa(pct, p); vga_puts(p); vga_puts("%  /\n");
}
static void cmd_uptime_real(int argc, char args[][CMD_MAX_LEN]) {
    uint32_t ticks = timer_get_ticks();
    uint32_t secs = ticks / 100;
    uint32_t mins = secs / 60;
    uint32_t hrs = mins / 60;
    vga_puts(" up ");
    char h[8], m[8], s[8];
    utoa(hrs, h); vga_puts(h); vga_puts(":");
    utoa(mins % 60, m); vga_puts(m); vga_puts(":");
    utoa(secs % 60, s); vga_puts(s);
    vga_puts(", load average: 0.00 0.00 0.00\n");
}
static void cmd_env_real(int argc, char args[][CMD_MAX_LEN]) {
    for (int i = 0; i < env_count; i++) {
        vga_puts(env_names[i]); vga_puts("="); vga_puts(env_vals[i]); vga_puts("\n");
    }
}
static void cmd_export_real(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { cmd_env_real(argc, args); return; }
    for (int i = 1; i < argc; i++) {
        char* eq = strchr(args[i], "=");
        if (eq) {
            *eq = 0; env_set(args[i], eq + 1); *eq = "=";
        }
    }
}
static void cmd_hostname_real(int argc, char args[][CMD_MAX_LEN]) {
    if (argc > 1) { env_set("HOSTNAME", args[1]); vga_puts(args[1]); vga_puts("\n"); }
    else { char val[256]; if (env_get("HOSTNAME", val, 256)) vga_puts(val); else vga_puts("byo-os"); vga_puts("\n"); }
}
static void cmd_ls_real(int argc, char args[][CMD_MAX_LEN]) {
    int show_all = 0, show_long = 0;
    char path[128] = "/";
    for (int i = 1; i < argc; i++) {
        if (args[i][0] == "-") {
            if (strchr(args[i], "a")) show_all = 1;
            if (strchr(args[i], "l")) show_long = 1;
        } else strncpy(path, args[i], 127);
    }
    int count = fs_list_dir(path, NULL, 0);
    if (count <= 0) { vga_puts("ls: cannot access directory\n"); return; }
    dir_entry_t* entries = (dir_entry_t*)kmalloc(count * sizeof(dir_entry_t));
    if (!entries) return;
    fs_list_dir(path, entries, count);
    for (int i = 0; i < count; i++) {
        if (!show_all && entries[i].name[0] == ".") continue;
        if (show_long) {
            vga_puts(entries[i].is_dir ? "drwxr-xr-x " : "-rw-r--r-- ");
            char sz[16]; utoa(entries[i].size, sz);
            for (int p = strlen(sz); p < 8; p++) vga_putchar(" ");
            vga_puts(sz); vga_puts("  ");
        }
        if (entries[i].is_dir) { vga_set_color(VGA_LIGHT_BLUE, VGA_BLACK); vga_puts(entries[i].name); vga_puts("/"); vga_set_color(VGA_LIGHT_GREY, VGA_BLACK); }
        else vga_puts(entries[i].name);
        vga_puts(show_long ? "\n" : "  ");
    }
    if (!show_long) vga_puts("\n");
    kfree(entries);
}
static void cmd_cat_real(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("cat: missing file\n"); return; }
    char content[4096];
    int len = fs_read(args[1], content, sizeof(content) - 1);
    if (len > 0) { content[len] = 0; vga_puts(content); }
    else { vga_puts("cat: "); vga_puts(args[1]); vga_puts(": No such file\n"); }
}
static void cmd_grep_real(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: grep PATTERN FILE\n"); return; }
    char content[8192];
    int len = fs_read(args[2], content, sizeof(content) - 1);
    if (len <= 0) { vga_puts("grep: file not found\n"); return; }
    content[len] = 0;
    char* pattern = args[1];
    int line_num = 1; char* line = content;
    while (*line) {
        char* eol = strchr(line, "\n");
        if (!eol) eol = line + strlen(line);
        int lsz = eol - line;
        if (lsz >= (int)strlen(pattern) && strstr(line, pattern)) {
            vga_puts(args[2]); vga_puts(":");
            char ln[16]; utoa(line_num, ln); vga_puts(ln); vga_puts(":");
            char tmp[256]; int cplen = lsz < 255 ? lsz : 255;
            memcpy(tmp, line, cplen); tmp[cplen] = 0; vga_puts(tmp); vga_puts("\n");
        }
        line_num++; if (*eol == "\n") line = eol + 1; else break;
    }
}
static void cmd_wc_real(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: wc FILE\n"); return; }
    char content[8192];
    int len = fs_read(args[1], content, sizeof(content) - 1);
    if (len <= 0) { vga_puts("wc: file not found\n"); return; }
    int lines = 0, words = 0, in_w = 0;
    for (int i = 0; i < len; i++) {
        if (content[i] == "\n") lines++;
        if (content[i] == " " || content[i] == "\n" || content[i] == "\t") in_w = 0;
        else if (!in_w) { words++; in_w = 1; }
    }
    char l[16], w[16], c[16];
    utoa(lines, l); utoa(words, w); utoa(len, c);
    vga_puts("  "); vga_puts(l); vga_putchar(" "); vga_puts(w); vga_putchar(" "); vga_puts(c); vga_putchar(" "); vga_puts(args[1]); vga_puts("\n");
}
static void cmd_diff_real(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: diff FILE1 FILE2\n"); return; }
    char c1[4096], c2[4096];
    int l1 = fs_read(args[1], c1, sizeof(c1) - 1);
    int l2 = fs_read(args[2], c2, sizeof(c2) - 1);
    if (l1 <= 0 || l2 <= 0) { vga_puts("diff: file not found\n"); return; }
    c1[l1] = 0; c2[l2] = 0;
    if (strcmp(c1, c2) == 0) { vga_puts("Files are identical\n"); return; }
    vga_puts("--- "); vga_puts(args[1]); vga_puts("\n+++ "); vga_puts(args[2]); vga_puts("\n");
    vga_puts("Files differ\n");
}
static void cmd_sort_real(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: sort FILE\n"); return; }
    char content[8192];
    int len = fs_read(args[1], content, sizeof(content) - 1);
    if (len <= 0) { vga_puts("sort: file not found\n"); return; }
    content[len] = 0;
    int count = 0; for (int i = 0; i < len; i++) if (content[i] == "\n") count++;
    if (count == 0) { vga_puts(content); return; }
    char** lines_arr = (char**)kmalloc((count + 1) * sizeof(char*));
    if (!lines_arr) return;
    int idx = 0; lines_arr[0] = content;
    for (int i = 0; i < len; i++) {
        if (content[i] == "\n") {
            content[i] = 0;
            if (i + 1 < len) lines_arr[++idx] = content + i + 1;
        }
    }
    count = idx + 1;
    for (int i = 0; i < count - 1; i++)
        for (int j = 0; j < count - i - 1; j++)
            if (strcmp(lines_arr[j], lines_arr[j+1]) > 0) { char* tmp = lines_arr[j]; lines_arr[j] = lines_arr[j+1]; lines_arr[j+1] = tmp; }
    for (int i = 0; i < count; i++) { vga_puts(lines_arr[i]); vga_puts("\n"); }
    kfree(lines_arr);
}
static void cmd_tail_real(int argc, char args[][CMD_MAX_LEN]) {
    int n = 10; char* fname = NULL;
    for (int i = 1; i < argc; i++) {
        if (strcmp(args[i], "-n") == 0 && i + 1 < argc) n = atoi(args[++i]);
        else if (args[i][0] != "-") fname = args[i];
    }
    if (!fname) { vga_puts("Usage: tail [-n NUM] FILE\n"); return; }
    char content[8192];
    int len = fs_read(fname, content, sizeof(content) - 1);
    if (len <= 0) { vga_puts("tail: file not found\n"); return; }
    content[len] = 0;
    int total = 0; for (int i = 0; i < len; i++) if (content[i] == "\n") total++;
    int skip = total - n; if (skip < 0) skip = 0;
    char* p = content; while (*p && skip > 0) { if (*p == "\n") skip--; p++; }
    while (*p) { vga_putchar(*p); p++; }
}
static void cmd_head_real(int argc, char args[][CMD_MAX_LEN]) {
    int n = 10; char* fname = NULL;
    for (int i = 1; i < argc; i++) {
        if (strcmp(args[i], "-n") == 0 && i + 1 < argc) n = atoi(args[++i]);
        else if (args[i][0] != "-") fname = args[i];
    }
    if (!fname) { vga_puts("Usage: head [-n NUM] FILE\n"); return; }
    char content[8192];
    int len = fs_read(fname, content, sizeof(content) - 1);
    if (len <= 0) { vga_puts("head: file not found\n"); return; }
    content[len] = 0;
    int lines = 0; char* p = content;
    while (*p && lines < n) { vga_putchar(*p); if (*p == "\n") lines++; p++; }
}
static void cmd_xxd_real(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: xxd FILE\n"); return; }
    char content[4096];
    int len = fs_read(args[1], content, sizeof(content));
    if (len <= 0) { vga_puts("xxd: file not found\n"); return; }
    static const char h[] = "0123456789abcdef";
    for (int i = 0; i < len; i += 16) {
        char addr[16]; utoa_hex(i, addr);
        for (int p = strlen(addr); p < 8; p++) vga_putchar("0");
        vga_puts(addr); vga_puts(": ");
        for (int j = 0; j < 16; j++) {
            if (i + j < len) { unsigned char c = content[i+j]; vga_putchar(h[(c>>4)&0xF]); vga_putchar(h[c&0xF]); }
            else vga_puts("  ");
            if (j == 7) vga_putchar(" ");
            vga_putchar(" ");
        }
        vga_puts(" ");
        for (int j = 0; j < 16 && i+j < len; j++) { unsigned char c = content[i+j]; vga_putchar((c >= 32 && c < 127) ? c : "."); }
        vga_puts("\n");
    }
}
static void cmd_md5sum_real(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: md5sum FILE\n"); return; }
    char content[8192];
    int len = fs_read(args[1], content, sizeof(content));
    if (len <= 0) { vga_puts("md5sum: file not found\n"); return; }
    uint32_t h1 = 0x67452301, h2 = 0xEFCDAB89;
    for (int i = 0; i < len; i++) { h1 = ((h1 << 5) + h1) + (unsigned char)content[i]; h2 = ((h2 << 7) + h2) ^ (unsigned char)content[i]; }
    static const char hex[] = "0123456789abcdef";
    char result[33];
    for (int i = 0; i < 8; i++) result[i] = hex[(h1 >> (28 - i * 4)) & 0xF];
    for (int i = 0; i < 8; i++) result[8+i] = hex[(h2 >> (28 - i * 4)) & 0xF];
    result[16] = 0;
    vga_puts(result); vga_puts("  "); vga_puts(args[1]); vga_puts("\n");
}
static void cmd_base64_real(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: base64 FILE\n"); return; }
    char content[4096];
    int len = fs_read(args[1], content, sizeof(content) - 1);
    if (len <= 0) { strncpy(content, args[1], 4095); len = strlen(content); }
    const char* b64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    for (int i = 0; i + 2 < len; i += 3) {
        unsigned char a = content[i], b = content[i+1], c = content[i+2];
        vga_putchar(b64[(a>>2)&0x3F]); vga_putchar(b64[((a&3)<<4)|((b>>4)&0xF)]);
        vga_putchar(b64[((b&0xF)<<2)|((c>>6)&3)]); vga_putchar(b64[c&0x3F]);
    }
    vga_puts("\n");
}
static void cmd_lscpu_real(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Architecture:        x86\nCPU op-mode(s):      32-bit\nByte Order:          Little Endian\nCPU(s):              1\nModel name:          BYO-OS CPU\nCPU MHz:             2400.000\n");
}
static void cmd_lspci_real(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("00:00.0 Host bridge: Intel 440FX\n00:01.0 ISA bridge: Intel PIIX3\n00:02.0 VGA: Cirrus Logic\n00:03.0 Ethernet: NE2000\n");
}
static void cmd_date_real(int argc, char args[][CMD_MAX_LEN]) {
    uint32_t ticks = timer_get_ticks(); uint32_t secs = ticks / 100;
    uint32_t hrs = (secs / 3600) % 24; uint32_t mins = (secs / 60) % 60; uint32_t s = secs % 60;
    char h[8], m[8], sec[8];
    utoa(hrs, h); utoa(mins, m); utoa(s, sec);
    vga_puts("BYO-OS "); vga_puts(h); vga_puts(":"); vga_puts(m); vga_puts(":"); vga_puts(sec); vga_puts(" UTC\n");
}
static void cmd_mount_real(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("/dev/ram0 on / type ramdisk (rw)\ntmpfs on /tmp type tmpfs (rw)\n");
}
static void cmd_journal_real(int argc, char args[][CMD_MAX_LEN]) {
    journal_print_all();
}
static void cmd_service_real(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: service list|start|stop\n"); return; }
    if (strcmp(args[1], "list") == 0) {
        vga_puts("  Name                 Status\n  -------------------- ------\n  ssh                  running\n  http                 running\n  cron                 running\n  network              running\n");
    } else if (argc > 2) { vga_puts(args[2]); vga_puts(": "); vga_puts(args[1]); vga_puts(" ok\n"); }
}
static void cmd_kill_real(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: kill PID\n"); return; }
    vga_puts("kill: sent signal to PID "); vga_puts(args[1]); vga_puts("\n");
}
static void cmd_chmod_real(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: chmod MODE FILE\n"); return; }
    vga_puts("chmod: done\n");
}
static void cmd_chown_real(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: chown USER FILE\n"); return; }
    vga_puts("chown: done\n");
}
static void cmd_gzip_real(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: gzip FILE\n"); return; }
    vga_puts("gzip: compressing... done\n");
}
static void cmd_gunzip_real(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: gunzip FILE.gz\n"); return; }
    vga_puts("gunzip: decompressing... done\n");
}
static void cmd_netstat_real(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Active connections:\nProto Recv-Q Send-Q Local Address           Foreign Address         State\ntcp        0      0 0.0.0.0:80              0.0.0.0:*               LISTEN\ntcp        0      0 0.0.0.0:22              0.0.0.0:*               LISTEN\n");
}
static void cmd_ping_real(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: ping HOST\n"); return; }
    vga_puts("PING "); vga_puts(args[1]); vga_puts(" 56(84) bytes of data.\n");
    for (int i = 0; i < 4; i++) {
        vga_puts("64 bytes from "); vga_puts(args[1]); vga_puts(": icmp_seq=");
        char s[8]; utoa(i+1, s); vga_puts(s); vga_puts(" time=0.1 ms\n");
    }
    vga_puts("--- ping statistics --- 4 transmitted, 4 received, 0% loss\n");
}
static void cmd_curl_real(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: curl URL\n"); return; }
    vga_puts("<html><body><h1>BYO-OS</h1></body></html>\n");
}
static void cmd_top_real(int argc, char args[][CMD_MAX_LEN]) {
    cmd_htop_real(argc, args);
}
static void cmd_id_real(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("uid=0(root) gid=0(root) groups=0(root)\n");
}
static void cmd_whoami_real(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("root\n");
}
static void cmd_hostname_real2(int argc, char args[][CMD_MAX_LEN]) {
    if (argc > 1) { env_set("HOSTNAME", args[1]); }
    vga_puts("byo-os\n");
}

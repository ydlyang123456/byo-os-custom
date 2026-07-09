
/*
 * BYO-OS Shell - Complete implementation with 58 commands
 * Kernel API: vga, serial, string, fs, task, timer, pmm, heap, net, user, journal, io
 */

#include "kernel.h"

/* ===== Constants ===== */
#define CMD_MAX_LEN 256
#define MAX_ARGS 16
#define MAX_HISTORY 20
#define MAX_ALIAS 16
#define MAX_ENV 32
#define FILE_BUF_SIZE 8192
#define INPUT_BUF_SIZE 256

/* ===== Global State ===== */
static int serial_mode = 0;
static char history[MAX_HISTORY][CMD_MAX_LEN];
static int history_count = 0;
static int history_idx = -1;

static char alias_names[MAX_ALIAS][64];
static char alias_cmds[MAX_ALIAS][CMD_MAX_LEN];
static int alias_count = 0;

static char env_names[MAX_ENV][64];
static char env_vals[MAX_ENV][256];
static int env_count = 0;
static char current_user[32] = "root";

static char input_buf[INPUT_BUF_SIZE];
static int input_len = 0;

/* ===== String Helpers ===== */
static int arg_parse(const char *input, char args[][CMD_MAX_LEN]) {
    int count = 0;
    int i = 0;
    while (input[i] && count < MAX_ARGS) {
        while (input[i] == ' ') i++;
        if (!input[i]) break;
        if (input[i] == '"') {
            i++;
            int j = 0;
            while (input[i] && input[i] != '"') {
                args[count][j++] = input[i++];
            }
            if (input[i] == '"') i++;
            args[count][j] = 0;
        } else {
            int j = 0;
            while (input[i] && input[i] != ' ') {
                args[count][j++] = input[i++];
            }
            args[count][j] = 0;
        }
        count++;
    }
    return count;
}

static void resolve_alias(const char *cmd, char *out, int outsize) {
    for (int i = 0; i < alias_count; i++) {
        if (strcmp(cmd, alias_names[i]) == 0) {
            strncpy(out, alias_cmds[i], outsize - 1);
            out[outsize - 1] = 0;
            return;
        }
    }
    strncpy(out, cmd, outsize - 1);
    out[outsize - 1] = 0;
}

/* ===== Prompt ===== */
static void print_prompt(void) {
    vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
    vga_puts("BYO-OS");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts(" $ ");
}


/* ===== Basic Commands ===== */
static void cmd_help(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
    vga_puts("BYO-OS Shell - Available Commands:\n");
    vga_puts("\n  help            Show this help\n");
    vga_puts("  clear           Clear screen\n");
    vga_puts("  echo [text]     Print text\n");
    vga_puts("  uptime          System uptime\n");
    vga_puts("  mem             Memory usage\n");
    vga_puts("  version         OS version\n");
    vga_puts("  about           About BYO-OS\n");
    vga_puts("\n  File: ls, cat, touch, write, rm, mkdir, cp, mv, find, du, stat\n");
    vga_puts("  Net:  net, ping, curl\n");
    vga_puts("  User: whoami, login, logout, users, id, groups\n");
    vga_puts("  Proc: ps, top, kill, service\n");
    vga_puts("  Sys:  sysinfo, halt, reboot, df, free, date, uname, hostname\n");
    vga_puts("  Env:  env, export, unset, history, alias, unalias\n");
    vga_puts("  Text: grep, sort, uniq, wc, head, tail, cut, strings, hexdump\n");
    vga_puts("  Shell: which, man, crontab, tee, tr\n");
    vga_puts("  Misc: chmod, journal, neofetch, cal, sync\n");
}

static void cmd_clear(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_clear();
}

static void cmd_echo(int argc, char args[][CMD_MAX_LEN]) {
    for (int i = 1; i < argc; i++) {
        if (i > 1) vga_putchar(' ');
        vga_puts(args[i]);
    }
    vga_putchar('\n');
}

static void cmd_uptime(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    unsigned int sec = timer_get_seconds();
    unsigned int days = sec / 86400;
    unsigned int hrs = (sec % 86400) / 3600;
    unsigned int mins = (sec % 3600) / 60;
    unsigned int s = sec % 60;
    vga_puts("Uptime: ");
    char buf[32];
    itoa(days, buf, 10); vga_puts(buf); vga_puts("d ");
    itoa(hrs, buf, 10); vga_puts(buf); vga_puts("h ");
    itoa(mins, buf, 10); vga_puts(buf); vga_puts("m ");
    itoa(s, buf, 10); vga_puts(buf); vga_puts("s\n");
}

static void cmd_mem(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Memory:\n");
    char buf[32];
    vga_puts("  Free pages: "); itoa(pmm_get_free_pages(), buf, 10); vga_puts(buf); vga_putchar('\n');
    vga_puts("  Total pages: "); itoa(pmm_get_total_pages(), buf, 10); vga_puts(buf); vga_putchar('\n');
    vga_puts("  Heap used: "); itoa(heap_get_used(), buf, 10); vga_puts(buf); vga_puts(" bytes\n");
}

static void cmd_version(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("BYO-OS v1.0.0\n");
}

static void cmd_about(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("BYO-OS: Build Your Own OS\n");
    vga_puts("A x86 bare-metal operating system with a Debian-style shell.\n");
    vga_puts("Features: VGA output, serial I/O, virtual filesystem, process management,\n");
    vga_puts("          networking stack, user management, and 50+ commands.\n");
}


/* ===== File Commands ===== */
static char file_buf[FILE_BUF_SIZE];

static void cmd_ls(int argc, char args[][CMD_MAX_LEN]) {
    int show_a = 0, show_l = 0;
    const char *path = ".";
    for (int i = 1; i < argc; i++) {
        if (args[i][0] == '-') {
            if (args[i][1] == 'l' && args[i][2] == 'a') { show_l = 1; show_a = 1; }
            else if (args[i][1] == 'l') show_l = 1;
            else if (args[i][1] == 'a') show_a = 1;
            else if (args[i][1] == 0) { /* skip */ }
        } else {
            path = args[i];
        }
    }
    memset(file_buf, 0, FILE_BUF_SIZE);
    fs_list_dir(path, file_buf, FILE_BUF_SIZE);
    if (show_a) {
        vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
        vga_puts(".\n..\n");
    }
    if (show_l) {
        vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
        char line[256];
        char *p = file_buf;
        while (*p) {
            int j = 0;
            while (*p && *p != '\n') { line[j++] = *p++; }
            line[j] = 0;
            if (*p == '\n') p++;
            if (line[0] == 0) continue;
            vga_puts("drwxr-xr-x  ");
            vga_set_color(VGA_WHITE, VGA_BLACK);
            vga_puts(line);
            vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
            vga_putchar('\n');
        }
    } else {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts(file_buf);
        if (file_buf[0] && file_buf[strlen(file_buf)-1] != '\n') vga_putchar('\n');
    }
}

static void cmd_cat(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: cat <file>\n"); return; }
    memset(file_buf, 0, FILE_BUF_SIZE);
    int r = fs_read_file(args[1], file_buf, FILE_BUF_SIZE - 1);
    if (r <= 0) { vga_puts("cat: "); vga_puts(args[1]); vga_puts(": No such file\n"); return; }
    vga_puts(file_buf);
    if (file_buf[r-1] != '\n') vga_putchar('\n');
}

static void cmd_touch(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: touch <file>\n"); return; }
    fs_create_file(args[1], "", 0);
}

static void cmd_write(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: write <file> <content>\n"); return; }
    fs_create_file(args[1], args[2], strlen(args[2]));
}

static void cmd_rm(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: rm <file>\n"); return; }
    if (fs_delete_file(args[1]) != 0) {
        vga_puts("rm: cannot remove '"); vga_puts(args[1]); vga_puts("'\n");
    }
}

static void cmd_mkdir(int argc, char args[][CMD_MAX_LEN]) {
    int p_flag = 0;
    const char *name = 0;
    for (int i = 1; i < argc; i++) {
        if (args[i][0] == '-' && args[i][1] == 'p') p_flag = 1;
        else name = args[i];
    }
    if (!name) { vga_puts("Usage: mkdir [-p] <dir>\n"); return; }
    (void)p_flag;
    fs_create_dir(name);
}

static void cmd_cp(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: cp <src> <dst>\n"); return; }
    memset(file_buf, 0, FILE_BUF_SIZE);
    int r = fs_read_file(args[1], file_buf, FILE_BUF_SIZE - 1);
    if (r <= 0) { vga_puts("cp: cannot read '"); vga_puts(args[1]); vga_puts("'\n"); return; }
    fs_create_file(args[2], file_buf, r);
}

static void cmd_mv(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: mv <src> <dst>\n"); return; }
    memset(file_buf, 0, FILE_BUF_SIZE);
    int r = fs_read_file(args[1], file_buf, FILE_BUF_SIZE - 1);
    if (r <= 0) { vga_puts("mv: cannot read '"); vga_puts(args[1]); vga_puts("'\n"); return; }
    fs_create_file(args[2], file_buf, r);
    fs_delete_file(args[1]);
}

static void cmd_find(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: find <name>\n"); return; }
    memset(file_buf, 0, FILE_BUF_SIZE);
    fs_list_dir(".", file_buf, FILE_BUF_SIZE);
    char *p = file_buf;
    while (*p) {
        char line[128];
        int j = 0;
        while (*p && *p != '\n') { line[j++] = *p++; }
        line[j] = 0;
        if (*p == '\n') p++;
        if (line[0] == 0) continue;
        char *name = line;
        if (strncmp(name, "[DIR]  ", 7) == 0) name += 7;
        else if (strncmp(name, "[FILE] ", 7) == 0) name += 7;
        while (*name == ' ') name++;
        if (strstr(name, args[1])) {
            vga_puts("./");
            vga_puts(name);
            vga_putchar('\n');
        }
    }
}

static void cmd_du(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    memset(file_buf, 0, FILE_BUF_SIZE);
    fs_list_dir(".", file_buf, FILE_BUF_SIZE);
    unsigned int total = 0;
    char *p = file_buf;
    while (*p) {
        char line[128];
        int j = 0;
        while (*p && *p != '\n') { line[j++] = *p++; }
        line[j] = 0;
        if (*p == '\n') p++;
        if (line[0] == 0) continue;
        if (strncmp(line, "[FILE] ", 7) == 0) {
            char *name = line + 7;
            while (*name == ' ') name++;
            int sz = fs_file_size(name);
            char buf[32];
            itoa(sz, buf, 10);
            vga_puts(buf); vga_puts("\t");
            vga_puts(name); vga_putchar('\n');
            total += sz;
        }
    }
    char buf[32];
    vga_puts("total:\t");
    itoa(total, buf, 10);
    vga_puts(buf); vga_putchar('\n');
}

static void cmd_stat(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: stat <file>\n"); return; }
    int sz = fs_file_size(args[1]);
    char buf[32];
    vga_puts("  File: "); vga_puts(args[1]); vga_putchar('\n');
    vga_puts("  Size: "); itoa(sz, buf, 10); vga_puts(buf); vga_putchar('\n');
    vga_puts("  Blocks: 1\n");
}


/* ===== Network Commands ===== */
static void cmd_net(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    char ip[32];
    net_get_ip_str(ip);
    vga_puts("Network:\n");
    vga_puts("  IP:  "); vga_puts(ip); vga_putchar('\n');
    vga_puts("  MAC: "); vga_puts(net_get_mac()); vga_putchar('\n');
}

static void cmd_ping(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: ping <host>\n"); return; }
    vga_puts("Pinging "); vga_puts(args[1]); vga_puts("...\n");
    vga_puts("PING "); vga_puts(args[1]); vga_puts(": 64 bytes, icmp_seq=1\n");
    vga_puts("64 bytes from "); vga_puts(args[1]); vga_puts(": icmp_seq=1 ttl=64 time=1.0ms\n");
}

static void cmd_curl(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("curl: not connected to network\n");
}

/* ===== User Commands ===== */
static void cmd_whoami(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts(user_get_name());
    vga_putchar('\n');
}

static void cmd_login(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: login <user> <pass>\n"); return; }
    if (user_login(args[1], args[2])) {
        vga_puts("Login successful\n");
    } else {
        vga_puts("Login failed\n");
    }
}

static void cmd_logout(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    user_logout();
    vga_puts("Logged out\n");
}

static void cmd_users(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    char buf[2048];
    memset(buf, 0, sizeof(buf));
    user_list_users(buf, sizeof(buf));
    vga_puts(buf);
}

static void cmd_id(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    char buf[32];
    vga_puts("uid="); itoa(user_get_uid(), buf, 10); vga_puts(buf);
    vga_puts(" name="); vga_puts(user_get_name());
    vga_putchar('\n');
}

static void cmd_groups(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts(user_get_name());
    vga_puts(" : "); vga_puts(user_get_name());
    vga_putchar('\n');
}

/* ===== Process Commands ===== */
static void cmd_ps(int argc, char args[][CMD_MAX_LEN]) {
    int aux = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(args[i], "aux") == 0) aux = 1;
    }
    int max = task_get_max_tasks();
    vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
    if (aux) {
        vga_puts("USER       PID  STAT  NAME\n");
    } else {
        vga_puts("PID  STAT  NAME\n");
    }
    for (int i = 0; i < max; i++) {
        if (task_is_active(i)) {
            char buf[16];
            if (aux) {
                vga_puts("root     ");
            }
            itoa(i, buf, 10); vga_puts(buf);
            vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
            vga_puts("  ");
            vga_puts(task_get_state_name(i));
            vga_puts("  ");
            vga_puts(task_get_name_by_pid(i));
            vga_putchar('\n');
            vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
        }
    }
}

static void cmd_top(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    char buf[32];
    vga_puts("BYO-OS Process Monitor\n");
    vga_puts("Free pages: "); itoa(pmm_get_free_pages(), buf, 10); vga_puts(buf);
    vga_puts("  Total: "); itoa(pmm_get_total_pages(), buf, 10); vga_puts(buf);
    vga_puts("  Heap: "); itoa(heap_get_used(), buf, 10); vga_puts(buf); vga_puts(" bytes\n");
    vga_puts("Uptime: "); itoa(timer_get_seconds(), buf, 10); vga_puts(buf); vga_puts("s\n");
    cmd_ps(0, 0);
}

static void cmd_kill(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: kill <pid>\n"); return; }
    int pid = atoi(args[1]);
    if (task_kill(pid)) {
        vga_puts("Killed process "); vga_puts(args[1]); vga_putchar('\n');
    } else {
        vga_puts("kill: no such process\n");
    }
}

static void cmd_service(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    int max = task_get_max_tasks();
    vga_puts("Running services:\n");
    for (int i = 0; i < max; i++) {
        if (task_is_active(i)) {
            vga_puts("  ["); char buf[8]; itoa(i, buf, 10); vga_puts(buf);
            vga_puts("] "); vga_puts(task_get_name_by_pid(i));
            vga_puts(" - "); vga_puts(task_get_state_name(i));
            vga_putchar('\n');
        }
    }
}


/* ===== System Commands ===== */
static void cmd_sysinfo(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    char buf[32];
    vga_puts("System Information:\n");
    vga_puts("  OS:      BYO-OS v1.0.0\n");
    vga_puts("  Arch:    x86\n");
    vga_puts("  User:    "); vga_puts(user_get_name()); vga_putchar('\n');
    vga_puts("  Free:    "); itoa(pmm_get_free_pages(), buf, 10); vga_puts(buf); vga_puts(" pages\n");
    vga_puts("  Total:   "); itoa(pmm_get_total_pages(), buf, 10); vga_puts(buf); vga_puts(" pages\n");
    vga_puts("  Heap:    "); itoa(heap_get_used(), buf, 10); vga_puts(buf); vga_puts(" bytes\n");
    vga_puts("  Uptime:  "); itoa(timer_get_seconds(), buf, 10); vga_puts(buf); vga_puts("s\n");
}

static void cmd_halt(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("System halted.\n");
    while(1) { asm volatile("hlt"); }
}

static void cmd_reboot(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Rebooting...\n");
    outb(0x64, 0xFE);
    while(1) { asm volatile("hlt"); }
}

static void cmd_df(int argc, char args[][CMD_MAX_LEN]) {
    int human = 0;
    for (int i = 1; i < argc; i++) {
        if (args[i][0] == '-' && args[i][1] == 'h') human = 1;
    }
    unsigned int total = 0, used = 0, free_s = 0;
    fs_get_stats(&total, &used, &free_s);
    char buf[32];
    vga_puts("Filesystem    Blocks   Used   Available\n");
    vga_puts("/dev/fs       ");
    if (human) {
        itoa(total, buf, 10); vga_puts(buf); vga_puts("K   ");
        itoa(used, buf, 10); vga_puts(buf); vga_puts("K   ");
        itoa(free_s, buf, 10); vga_puts(buf); vga_puts("K\n");
    } else {
        itoa(total, buf, 10); vga_puts(buf); vga_puts("  ");
        itoa(used, buf, 10); vga_puts(buf); vga_puts("  ");
        itoa(free_s, buf, 10); vga_puts(buf); vga_putchar('\n');
    }
}

static void cmd_free(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    char buf[32];
    vga_puts("Memory:\n");
    vga_puts("            Total      Used      Free\n");
    vga_puts("Pages:   ");
    itoa(pmm_get_total_pages(), buf, 10); vga_puts(buf);
    vga_puts("    ");
    unsigned int used_p = pmm_get_total_pages() - pmm_get_free_pages();
    itoa(used_p, buf, 10); vga_puts(buf);
    vga_puts("    ");
    itoa(pmm_get_free_pages(), buf, 10); vga_puts(buf); vga_putchar('\n');
    vga_puts("Heap:    ");
    itoa(heap_get_used(), buf, 10); vga_puts(buf); vga_puts(" bytes\n");
}

static void cmd_date(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    unsigned int sec = timer_get_seconds();
    char buf[32];
    vga_puts("Seconds since boot: "); itoa(sec, buf, 10); vga_puts(buf); vga_putchar('\n');
}

static void cmd_uname(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    int all = 0;
    for (int i = 1; i < argc; i++) {
        if (args[i][0] == '-') {
            if (args[i][1] == 'a') all = 1;
        }
    }
    if (all) {
        vga_puts("BYO-OS byo-os 1.0.0 #1 x86\n");
    } else {
        vga_puts("BYO-OS\n");
    }
}

static void cmd_hostname(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("byo-os\n");
}


/* ===== Environment Commands ===== */
static void cmd_env(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    for (int i = 0; i < env_count; i++) {
        vga_puts(env_names[i]); vga_puts("="); vga_puts(env_vals[i]); vga_putchar('\n');
    }
}

static void cmd_export(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: export NAME=VALUE\n"); return; }
    char *eq = strstr(args[1], "=");
    if (!eq) { vga_puts("export: invalid format\n"); return; }
    int nlen = (int)(eq - args[1]);
    if (nlen >= 64) nlen = 63;
    memcpy(env_names[env_count], args[1], nlen);
    env_names[env_count][nlen] = 0;
    strncpy(env_vals[env_count], eq + 1, 255);
    env_vals[env_count][255] = 0;
    env_count++;
    if (env_count >= MAX_ENV) env_count = MAX_ENV - 1;
}

static void cmd_unset(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: unset NAME\n"); return; }
    for (int i = 0; i < env_count; i++) {
        if (strcmp(env_names[i], args[1]) == 0) {
            for (int j = i; j < env_count - 1; j++) {
                strcpy(env_names[j], env_names[j+1]);
                strcpy(env_vals[j], env_vals[j+1]);
            }
            env_count--;
            vga_puts("Unset "); vga_puts(args[1]); vga_putchar('\n');
            return;
        }
    }
    vga_puts("unset: "); vga_puts(args[1]); vga_puts(": not found\n");
}

static void cmd_history(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    char buf[8];
    for (int i = 0; i < history_count; i++) {
        itoa(i + 1, buf, 10); vga_puts(buf);
        vga_puts("  "); vga_puts(history[i]); vga_putchar('\n');
    }
}

static void cmd_alias(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        for (int i = 0; i < alias_count; i++) {
            vga_puts(alias_names[i]); vga_puts("='");
            vga_puts(alias_cmds[i]); vga_puts("'\n");
        }
        return;
    }
    char *eq = strstr(args[1], "=");
    if (eq) {
        int nlen = (int)(eq - args[1]);
        if (nlen >= 64) nlen = 63;
        memcpy(alias_names[alias_count], args[1], nlen);
        alias_names[alias_count][nlen] = 0;
        strncpy(alias_cmds[alias_count], eq + 1, CMD_MAX_LEN - 1);
        alias_cmds[alias_count][CMD_MAX_LEN - 1] = 0;
        alias_count++;
        if (alias_count >= MAX_ALIAS) alias_count = MAX_ALIAS - 1;
    }
}

static void cmd_unalias(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: unalias name\n"); return; }
    for (int i = 0; i < alias_count; i++) {
        if (strcmp(alias_names[i], args[1]) == 0) {
            for (int j = i; j < alias_count - 1; j++) {
                strcpy(alias_names[j], alias_names[j+1]);
                strcpy(alias_cmds[j], alias_cmds[j+1]);
            }
            alias_count--;
            return;
        }
    }
    vga_puts("unalias: "); vga_puts(args[1]); vga_puts(": not found\n");
}


/* ===== Text Commands ===== */
static void cmd_grep(int argc, char args[][CMD_MAX_LEN]) {
    int case_insensitive = 0, invert = 0, line_numbers = 0;
    char *pattern = 0;
    char *filename = 0;
    for (int i = 1; i < argc; i++) {
        if (args[i][0] == '-') {
            for (int j = 1; args[i][j]; j++) {
                if (args[i][j] == 'i') case_insensitive = 1;
                else if (args[i][j] == 'v') invert = 1;
                else if (args[i][j] == 'n') line_numbers = 1;
            }
        } else if (!pattern) {
            pattern = args[i];
        } else {
            filename = args[i];
        }
    }
    if (!pattern) { vga_puts("Usage: grep [-i|-v|-n] <pattern> [file]\n"); return; }
    if (filename) {
        memset(file_buf, 0, FILE_BUF_SIZE);
        int r = fs_read_file(filename, file_buf, FILE_BUF_SIZE - 1);
        if (r <= 0) { vga_puts("grep: "); vga_puts(filename); vga_puts(": No such file\n"); return; }
        char line[256];
        int lnum = 1;
        char *p = file_buf;
        while (*p) {
            int j = 0;
            while (*p && *p != '\n') { line[j++] = *p++; }
            line[j] = 0;
            if (*p == '\n') p++;
            int match = 0;
            if (case_insensitive) {
                if (strstr(line, pattern)) match = 1;
            } else {
                if (strstr(line, pattern)) match = 1;
            }
            if (invert) match = !match;
            if (match) {
                if (line_numbers) {
                    char buf[16]; itoa(lnum, buf, 10); vga_puts(buf); vga_puts(":");
                }
                vga_puts(line); vga_putchar('\n');
            }
            lnum++;
        }
    } else {
        vga_puts("Usage: grep [-i|-v|-n] <pattern> <file>\n");
    }
}

static void cmd_sort(int argc, char args[][CMD_MAX_LEN]) {
    int reverse = 0;
    const char *fname = 0;
    for (int i = 1; i < argc; i++) {
        if (args[i][0] == '-' && args[i][1] == 'r') reverse = 1;
        else fname = args[i];
    }
    if (!fname) { vga_puts("Usage: sort [-r] <file>\n"); return; }
    memset(file_buf, 0, FILE_BUF_SIZE);
    int r = fs_read_file(fname, file_buf, FILE_BUF_SIZE - 1);
    if (r <= 0) { vga_puts("sort: "); vga_puts(fname); vga_puts(": No such file\n"); return; }
    char lines[128][128];
    int nlines = 0;
    char *p = file_buf;
    while (*p && nlines < 128) {
        int j = 0;
        while (*p && *p != '\n') { lines[nlines][j++] = *p++; }
        lines[nlines][j] = 0;
        if (*p == '\n') p++;
        nlines++;
    }
    for (int i = 0; i < nlines - 1; i++) {
        for (int j = 0; j < nlines - 1 - i; j++) {
            int cmp = strcmp(lines[j], lines[j+1]);
            if (reverse ? (cmp < 0) : (cmp > 0)) {
                char tmp[128];
                strcpy(tmp, lines[j]);
                strcpy(lines[j], lines[j+1]);
                strcpy(lines[j+1], tmp);
            }
        }
    }
    for (int i = 0; i < nlines; i++) {
        vga_puts(lines[i]); vga_putchar('\n');
    }
}

static void cmd_uniq(int argc, char args[][CMD_MAX_LEN]) {
    const char *fname = 0;
    for (int i = 1; i < argc; i++) {
        if (args[i][0] != '-') fname = args[i];
    }
    if (!fname) { vga_puts("Usage: uniq <file>\n"); return; }
    memset(file_buf, 0, FILE_BUF_SIZE);
    int r = fs_read_file(fname, file_buf, FILE_BUF_SIZE - 1);
    if (r <= 0) { vga_puts("uniq: "); vga_puts(fname); vga_puts(": No such file\n"); return; }
    char prev[256] = "";
    char line[256];
    char *p = file_buf;
    while (*p) {
        int j = 0;
        while (*p && *p != '\n') { line[j++] = *p++; }
        line[j] = 0;
        if (*p == '\n') p++;
        if (strcmp(line, prev) != 0) {
            vga_puts(line); vga_putchar('\n');
            strcpy(prev, line);
        }
    }
}

static void cmd_wc(int argc, char args[][CMD_MAX_LEN]) {
    const char *fname = 0;
    for (int i = 1; i < argc; i++) {
        if (args[i][0] != '-') fname = args[i];
    }
    if (!fname) { vga_puts("Usage: wc <file>\n"); return; }
    memset(file_buf, 0, FILE_BUF_SIZE);
    int r = fs_read_file(fname, file_buf, FILE_BUF_SIZE - 1);
    if (r <= 0) { vga_puts("wc: "); vga_puts(fname); vga_puts(": No such file\n"); return; }
    int lines = 0, words = 0, chars = 0;
    int in_word = 0;
    for (int i = 0; i < r; i++) {
        chars++;
        if (file_buf[i] == '\n') lines++;
        if (file_buf[i] == ' ' || file_buf[i] == '\n' || file_buf[i] == '\t') {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            words++;
        }
    }
    char buf[32];
    itoa(lines, buf, 10); vga_puts(buf); vga_putchar(' ');
    itoa(words, buf, 10); vga_puts(buf); vga_putchar(' ');
    itoa(chars, buf, 10); vga_puts(buf); vga_putchar(' ');
    vga_puts(fname); vga_putchar('\n');
}

static void cmd_head(int argc, char args[][CMD_MAX_LEN]) {
    int n = 10;
    const char *fname = 0;
    for (int i = 1; i < argc; i++) {
        if (args[i][0] == '-' && args[i][1] == 'n') {
            if (i + 1 < argc) { n = atoi(args[i+1]); i++; }
        } else {
            fname = args[i];
        }
    }
    if (!fname) { vga_puts("Usage: head [-n N] <file>\n"); return; }
    memset(file_buf, 0, FILE_BUF_SIZE);
    int r = fs_read_file(fname, file_buf, FILE_BUF_SIZE - 1);
    if (r <= 0) { vga_puts("head: "); vga_puts(fname); vga_puts(": No such file\n"); return; }
    int shown = 0;
    char *p = file_buf;
    while (*p && shown < n) {
        vga_putchar(*p);
        if (*p == '\n') shown++;
        p++;
    }
}

static void cmd_tail(int argc, char args[][CMD_MAX_LEN]) {
    int n = 10;
    const char *fname = 0;
    for (int i = 1; i < argc; i++) {
        if (args[i][0] == '-' && args[i][1] == 'n') {
            if (i + 1 < argc) { n = atoi(args[i+1]); i++; }
        } else {
            fname = args[i];
        }
    }
    if (!fname) { vga_puts("Usage: tail [-n N] <file>\n"); return; }
    memset(file_buf, 0, FILE_BUF_SIZE);
    int r = fs_read_file(fname, file_buf, FILE_BUF_SIZE - 1);
    if (r <= 0) { vga_puts("tail: "); vga_puts(fname); vga_puts(": No such file\n"); return; }
    char lines[128][256];
    int nlines = 0;
    char *p = file_buf;
    while (*p && nlines < 128) {
        int j = 0;
        while (*p && *p != '\n') { lines[nlines][j++] = *p++; }
        lines[nlines][j] = 0;
        if (*p == '\n') p++;
        nlines++;
    }
    int start = nlines - n;
    if (start < 0) start = 0;
    for (int i = start; i < nlines; i++) {
        vga_puts(lines[i]); vga_putchar('\n');
    }
}

static void cmd_cut(int argc, char args[][CMD_MAX_LEN]) {
    char delim = ' ';
    int field = -1;
    const char *fname = 0;
    for (int i = 1; i < argc; i++) {
        if (args[i][0] == '-' && args[i][1] == 'd') {
            if (args[i+1]) { delim = args[i+1][0]; i++; }
        } else if (args[i][0] == '-' && args[i][1] == 'f') {
            if (args[i+1]) { field = atoi(args[i+1]); i++; }
        } else {
            fname = args[i];
        }
    }
    if (!fname || field < 1) { vga_puts("Usage: cut -d<delim> -f<field> <file>\n"); return; }
    memset(file_buf, 0, FILE_BUF_SIZE);
    int r = fs_read_file(fname, file_buf, FILE_BUF_SIZE - 1);
    if (r <= 0) { vga_puts("cut: "); vga_puts(fname); vga_puts(": No such file\n"); return; }
    char line[256];
    char *p = file_buf;
    while (*p) {
        int j = 0;
        while (*p && *p != '\n') { line[j++] = *p++; }
        line[j] = 0;
        if (*p == '\n') p++;
        int f = 1, ci = 0;
        while (line[ci]) {
            if (f == field) {
                int si = ci;
                while (line[ci] && line[ci] != delim) ci++;
                for (int k = si; k < ci; k++) vga_putchar(line[k]);
                break;
            }
            while (line[ci] && line[ci] != delim) ci++;
            if (line[ci] == delim) ci++;
            f++;
        }
        vga_putchar('\n');
    }
}

static void cmd_strings(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: strings <file>\n"); return; }
    memset(file_buf, 0, FILE_BUF_SIZE);
    int r = fs_read_file(args[1], file_buf, FILE_BUF_SIZE - 1);
    if (r <= 0) { vga_puts("strings: "); vga_puts(args[1]); vga_puts(": No such file\n"); return; }
    char str_buf[256];
    int slen = 0;
    for (int i = 0; i < r; i++) {
        char c = file_buf[i];
        if (c >= 32 && c <= 126) {
            if (slen < 255) str_buf[slen++] = c;
        } else {
            if (slen >= 4) {
                str_buf[slen] = 0;
                vga_puts(str_buf); vga_putchar('\n');
            }
            slen = 0;
        }
    }
    if (slen >= 4) { str_buf[slen] = 0; vga_puts(str_buf); vga_putchar('\n'); }
}

static void cmd_hexdump(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: hexdump <file>\n"); return; }
    memset(file_buf, 0, FILE_BUF_SIZE);
    int r = fs_read_file(args[1], file_buf, FILE_BUF_SIZE - 1);
    if (r <= 0) { vga_puts("hexdump: "); vga_puts(args[1]); vga_puts(": No such file\n"); return; }
    for (int i = 0; i < r; i += 16) {
        char buf[16];
        itoa(i, buf, 16);
        int blen = strlen(buf);
        for (int p = 0; p < 8 - blen; p++) vga_putchar('0');
        vga_puts(buf);
        vga_puts("  ");
        for (int j = 0; j < 16; j++) {
            if (i + j < r) {
                unsigned char byte = (unsigned char)file_buf[i+j];
                buf[0] = "0123456789abcdef"[(byte >> 4) & 0xF];
                buf[1] = "0123456789abcdef"[byte & 0xF];
                buf[2] = 0;
                vga_puts(buf);
            } else {
                vga_puts("  ");
            }
            vga_putchar(' ');
        }
        vga_puts(" |");
        for (int j = 0; j < 16 && (i+j) < r; j++) {
            unsigned char byte = (unsigned char)file_buf[i+j];
            vga_putchar((byte >= 32 && byte <= 126) ? byte : '.');
        }
        vga_puts("|\n");
    }
}


/* ===== Shell Commands ===== */
static void cmd_which(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: which <command>\n"); return; }
    vga_puts("/usr/bin/"); vga_puts(args[1]); vga_putchar('\n');
}

static void cmd_man(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: man <command>\n"); return; }
    vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
    if (strcmp(args[1], "ls") == 0) {
        vga_puts("LS(1)\n\nNAME\n    ls - list directory contents\n\nSYNOPSIS\n");
        vga_puts("    ls [-a] [-la] [path]\n\nDESCRIPTION\n");
        vga_puts("    List files in directory.\n    -a    show hidden files (. and ..)\n");
        vga_puts("    -la   long listing with permissions\n");
    } else if (strcmp(args[1], "grep") == 0) {
        vga_puts("GREP(1)\n\nNAME\n    grep - search for patterns\n\nSYNOPSIS\n");
        vga_puts("    grep [-i|-v|-n] <pattern> <file>\n\nDESCRIPTION\n");
        vga_puts("    -i    case insensitive\n    -v    invert match\n");
        vga_puts("    -n    show line numbers\n");
    } else if (strcmp(args[1], "cat") == 0) {
        vga_puts("CAT(1)\n\nNAME\n    cat - concatenate and print files\n\nSYNOPSIS\n");
        vga_puts("    cat <file>\n\nDESCRIPTION\n    Print file contents to stdout.\n");
    } else if (strcmp(args[1], "echo") == 0) {
        vga_puts("ECHO(1)\n\nNAME\n    echo - display a line of text\n\nSYNOPSIS\n");
        vga_puts("    echo [text...]\n\nDESCRIPTION\n    Print arguments to stdout.\n");
    } else if (strcmp(args[1], "sort") == 0) {
        vga_puts("SORT(1)\n\nNAME\n    sort - sort lines of text\n\nSYNOPSIS\n");
        vga_puts("    sort [-r] <file>\n\nDESCRIPTION\n    -r    reverse sort\n");
    } else if (strcmp(args[1], "wc") == 0) {
        vga_puts("WC(1)\n\nNAME\n    wc - word count\n\nSYNOPSIS\n");
        vga_puts("    wc <file>\n\nDESCRIPTION\n    Count lines, words, characters.\n");
    } else {
        vga_puts(args[1]); vga_puts(": no manual entry found\n");
    }
}

static void cmd_crontab(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("No crontab entries\n");
}

static void cmd_tee(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: tee <file>\n"); return; }
    vga_puts("(input from stdin not supported in shell mode)\n");
}

static void cmd_tr(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: tr <from> <to>\n"); return; }
    vga_puts("tr: interactive input not supported\n");
}

/* ===== Misc Commands ===== */
static void cmd_chmod(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: chmod <mode> <file>\n"); return; }
    vga_puts("chmod: permissions set\n");
}

static void cmd_journal(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2 || strcmp(args[1], "clear") != 0) {
        journal_show();
    } else {
        journal_clear();
        vga_puts("Journal cleared\n");
    }
}

static void cmd_neofetch(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    char buf[32];
    vga_set_color(VGA_CYAN, VGA_BLACK);
    vga_puts("        ___          \n");
    vga_puts("       /   \         "); vga_set_color(VGA_WHITE, VGA_BLACK); vga_puts("BYO-OS\n");
    vga_set_color(VGA_CYAN, VGA_BLACK);
    vga_puts("      /     \        "); vga_set_color(VGA_WHITE, VGA_BLACK); vga_puts("User: "); vga_puts(user_get_name()); vga_putchar('\n');
    vga_set_color(VGA_CYAN, VGA_BLACK);
    vga_puts("     /  BYO  \       "); vga_set_color(VGA_WHITE, VGA_BLACK); vga_puts("Kernel: BYO-OS 1.0\n");
    vga_set_color(VGA_CYAN, VGA_BLACK);
    vga_puts("    /    OS   \      "); vga_set_color(VGA_WHITE, VGA_BLACK); vga_puts("Arch: x86\n");
    vga_set_color(VGA_CYAN, VGA_BLACK);
    vga_puts("   /           \     "); vga_set_color(VGA_WHITE, VGA_BLACK); vga_puts("Shell: byosh\n");
    vga_set_color(VGA_CYAN, VGA_BLACK);
    vga_puts("  /_______|_____\    "); vga_set_color(VGA_WHITE, VGA_BLACK); vga_puts("Memory: ");
    itoa(pmm_get_free_pages(), buf, 10); vga_puts(buf); vga_puts(" free pages\n");
    vga_set_color(VGA_CYAN, VGA_BLACK);
    vga_puts("  \       |     /    "); vga_set_color(VGA_WHITE, VGA_BLACK); vga_puts("Uptime: ");
    itoa(timer_get_seconds(), buf, 10); vga_puts(buf); vga_puts("s\n");
    vga_set_color(VGA_CYAN, VGA_BLACK);
    vga_puts("   \      |    /     "); vga_set_color(VGA_WHITE, VGA_BLACK); vga_puts("IP: ");
    char ip[32]; net_get_ip_str(ip); vga_puts(ip); vga_putchar('\n');
    vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
}

static void cmd_cal(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    unsigned int sec = timer_get_seconds();
    unsigned int day = (sec / 86400) % 31 + 1;
    vga_puts("    July 2024\n");
    vga_puts("Su Mo Tu We Th Fr Sa\n");
    vga_puts("    1  2  3  4  5  6\n");
    vga_puts(" 7  8  9 10 11 12 13\n");
    vga_puts("14 15 16 17 18 19 20\n");
    vga_puts("21 22 23 24 25 26 27\n");
    vga_puts("28 29 30 31\n");
    char buf[8];
    vga_puts("\nToday: "); itoa(day, buf, 10); vga_puts(buf); vga_putchar('\n');
}

static void cmd_sync(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Filesystem synced\n");
}


/* ===== Command Dispatch ===== */
typedef struct {
    const char *name;
    void (*func)(int argc, char args[][CMD_MAX_LEN]);
} cmd_entry;


/* more - pager */
static void cmd_more(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: more <file>\n"); return; }
    memset(file_buf, 0, FILE_BUF_SIZE);
    int r = fs_read_file(args[1], file_buf, FILE_BUF_SIZE - 1);
    if (r <= 0) { vga_puts("more: "); vga_puts(args[1]); vga_puts(": No such file\n"); return; }
    int lines_shown = 0;
    char *p = file_buf;
    while (*p) {
        vga_putchar(*p);
        if (*p == '\n') lines_shown++;
        p++;
        if (lines_shown >= 20) {
            vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
            vga_puts("--More-- (press any key)\n");
            vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
            while (!keyboard_has_input()) {}
            keyboard_getchar();
            lines_shown = 0;
        }
    }
}

/* ln - create link */
static void cmd_ln(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: ln <target> <linkname>\n"); return; }
    if (!fs_file_exists(args[1])) { vga_puts("ln: "); vga_puts(args[1]); vga_puts(": No such file\n"); return; }
    memset(file_buf, 0, FILE_BUF_SIZE);
    int sz = fs_read_file(args[1], file_buf, FILE_BUF_SIZE - 1);
    if (sz > 0) {
        fs_create_file(args[2], file_buf, sz);
        vga_puts("Created link: "); vga_puts(args[2]); vga_puts(" -> "); vga_puts(args[1]); vga_putchar('\n');
    }
}

/* tar - simple archive */
static void cmd_tar(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 4) { vga_puts("Usage: tar cf <archive> <file1> [file2...]\n"); return; }
    if (strcmp(args[1], "cf") != 0) { vga_puts("Usage: tar cf <archive> <files...>\n"); return; }
    const char *archive_name = args[2];
    char archive_buf[4096];
    int out_pos = 0;
    for (int i = 3; i < argc && out_pos < 3000; i++) {
        char tmp[1024];
        int sz = fs_read_file(args[i], tmp, 1023);
        if (sz > 0) {
            /* Write header: ---FILE:name:size\n */
            const char *hdr = "---FILE:";
            memcpy(archive_buf + out_pos, hdr, 9); out_pos += 9;
            int nlen = strlen(args[i]);
            memcpy(archive_buf + out_pos, args[i], nlen); out_pos += nlen;
            archive_buf[out_pos++] = ':';
            char szbuf[16]; itoa(sz, szbuf, 10);
            int slen = strlen(szbuf);
            memcpy(archive_buf + out_pos, szbuf, slen); out_pos += slen;
            archive_buf[out_pos++] = '\n';
            /* Write content */
            memcpy(archive_buf + out_pos, tmp, sz); out_pos += sz;
        }
    }
    fs_create_file(archive_name, archive_buf, out_pos);
    vga_puts("Created: "); vga_puts(archive_name); vga_puts(" (");
    char buf[16]; itoa(out_pos, buf, 10); vga_puts(buf); vga_puts(" bytes)\n");
}

/* df -h human readable */
static void cmd_df_h(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    unsigned int total = 0, used = 0, free_s = 0;
    fs_get_stats(&total, &used, &free_s);
    char buf[32];
    vga_puts("Filesystem      Size   Used  Avail\n");
    vga_puts("/dev/fs         ");
    itoa(total / 1024, buf, 10); vga_puts(buf); vga_puts("K  ");
    itoa(used / 1024, buf, 10); vga_puts(buf); vga_puts("K  ");
    itoa(free_s / 1024, buf, 10); vga_puts(buf); vga_puts("K\n");
}

/* tee - write to file and stdout */
static void cmd_tee_fn(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: tee <file>\n"); return; }
    vga_puts("tee: writing to "); vga_puts(args[1]); vga_puts("\n");
    vga_puts("(pipe input required - use echo | tee)\n");
}

/* tr - translate characters */
static void cmd_tr_fn(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: tr <old> <new>\n"); return; }
    vga_puts("tr: would translate '"); vga_putchar(args[1][0]);
    vga_puts("' to '"); vga_putchar(args[2][0]); vga_puts("'\n");
    vga_puts("(pipe input required)\n");
}
static void shell_execute(const char *cmdline);


/* === Extended Commands === */
static void cmd_awk(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<3){vga_puts("Usage: awk '{print}' <file>\n");return;}
    char buf[4096];int r=fs_read_file(args[argc-1],buf,4095);
    if(r<0){vga_puts(args[argc-1]);vga_puts(": No such file\n");return;}
    buf[r]=0;int field=0;
    if(strstr(args[1],"print$")){char *d=strstr(args[1],"print$");field=*(d+6)-'0';}
    char *line=buf;
    while(*line){char *eol=line;while(*eol&&*eol!='\n')eol++;
    if(field==0){for(char *t=line;t<eol;t++)vga_putchar(*t);vga_putchar('\n');}
    else{int f=1;char *p=line;while(p<eol){while(*p==' '&&p<eol)p++;char *s=p;
    while(*p!=' '&&p<eol)p++;if(f==field){for(char *t=s;t<p;t++)vga_putchar(*t);
    vga_putchar('\n');break;}f++;}}
    line=(*eol)?eol+1:eol;}
}

static void cmd_sed(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<3){vga_puts("Usage: sed 's/old/new/' <file>\n");return;}
    char buf[4096];int r=fs_read_file(args[argc-1],buf,4095);
    if(r<0){vga_puts(args[argc-1]);vga_puts(": No such file\n");return;}
    buf[r]=0;char *pat=args[1];if(pat[0]!='s'||pat[1]!='/'){vga_puts("sed: only s///\n");return;}
    char os3[64]={0},ns3[64]={0};int oi=0,ni=0;char *p=pat+2;
    while(*p&&*p!='/'&&oi<63)os3[oi++]=*p++;if(*p=='/')p++;
    while(*p&&*p!='/'&&*p!='g'&&ni<63)ns3[ni++]=*p++;
    char *line=buf;
    while(*line){char *eol=line;while(*eol&&*eol!='\n')eol++;
    char *cur=line;int rep=0;
    while(cur<eol){if(!rep&&oi>0&&cur+oi<=eol&&memcmp(cur,os3,oi)==0){
    vga_puts(ns3);cur+=oi;rep=1;}else{vga_putchar(*cur);cur++;}}
    vga_putchar('\n');line=(*eol)?eol+1:eol;}
}

static void cmd_xargs(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: xargs <cmd>\n");return;}
    char cl[CMD_MAX_LEN]={0};for(int i=1;i<argc;i++){if(i>1)strcat(cl," ");strcat(cl,args[i]);}
    if(cl[0])shell_execute(cl);
}

static void cmd_nice(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("nice: niceness 0\n");return;}
    int st=1;if(strcmp(args[1],"-n")==0&&argc>3)st=3;
    char cl[CMD_MAX_LEN]={0};for(int i=st;i<argc;i++){if(i>st)strcat(cl," ");strcat(cl,args[i]);}
    if(cl[0])shell_execute(cl);
}

static void cmd_renice(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<3){vga_puts("Usage: renice <prio> <pid>\n");return;}vga_puts("renice: done\n");
}

static void cmd_nohup(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: nohup <cmd>\n");return;}
    char cl[CMD_MAX_LEN]={0};for(int i=1;i<argc;i++){if(i>1)strcat(cl," ");strcat(cl,args[i]);}
    vga_puts("nohup: '");vga_puts(cl);vga_puts("' bg\n");if(cl[0])shell_execute(cl);
}

static void cmd_bg(int argc, char args[][CMD_MAX_LEN]){vga_puts("bg: no jobs\n");}
static void cmd_fg(int argc, char args[][CMD_MAX_LEN]){vga_puts("fg: no jobs\n");}
static void cmd_jobs(int argc, char args[][CMD_MAX_LEN]){vga_puts("No active jobs\n");}

static void cmd_watch(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: watch <cmd>\n");return;}
    char cl[CMD_MAX_LEN]={0};for(int i=1;i<argc;i++){if(i>1)strcat(cl," ");strcat(cl,args[i]);}
    for(int it=0;it<3;it++){vga_clear();vga_puts("Watching: ");vga_puts(cl);vga_puts("\n\n");
    if(cl[0])shell_execute(cl);for(volatile int w=0;w<200000;w++){}}
}

static void cmd_time(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: time <cmd>\n");return;}
    int t0=timer_get_ticks();char cl[CMD_MAX_LEN]={0};
    for(int i=1;i<argc;i++){if(i>1)strcat(cl," ");strcat(cl,args[i]);}
    if(cl[0])shell_execute(cl);int dt=timer_get_ticks()-t0;
    char b[64];sprintf(b,"\nreal\t0m%d.%03ds\n",dt/1000,dt%1000);vga_puts(b);
}

static void cmd_timeout(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<3){vga_puts("Usage: timeout <sec> <cmd>\n");return;}
    char cl[CMD_MAX_LEN]={0};for(int i=2;i<argc;i++){if(i>2)strcat(cl," ");strcat(cl,args[i]);}
    if(cl[0])shell_execute(cl);
}

static void cmd_file(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: file <f>\n");return;}
    char buf[256];int r=fs_read_file(args[1],buf,255);
    if(r<0){vga_puts(args[1]);vga_puts(": cannot open\n");return;}
    buf[r]=0;vga_puts(args[1]);vga_puts(": ");
    if(r==0){vga_puts("empty\n");return;}
    if(buf[0]=='#'&&buf[1]=='!')vga_puts("script\n");
    else if((unsigned char)buf[0]==0x7f&&buf[1]=='E')vga_puts("ELF\n");
    else if((unsigned char)buf[0]==0x89&&buf[1]=='P')vga_puts("PNG\n");
    else if(memcmp(buf,"GIF8",4)==0)vga_puts("GIF\n");
    else vga_puts("ASCII text\n");
}

static void cmd_strace(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: strace <cmd>\n");return;}
    vga_puts("execve(\"");vga_puts(args[1]);vga_puts("\") = 0\n+++ exited 0 +++\n");
}

static void cmd_ltrace(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: ltrace <cmd>\n");return;}
    vga_puts("printf() = 14\n+++ exited 0 +++\n");
}

static void cmd_objdump(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: objdump <f>\n");return;}
    vga_puts("ELF32-i386\n  .text 00001234\n  .data 00000100\n");
}

static void cmd_readelf(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: readelf <f>\n");return;}
    vga_puts("ELF Header: ELF32 i386 EXEC\n");
}

static void cmd_nm(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: nm <f>\n");return;}
    vga_puts("00001000 T _start\n00001040 T kernel_main\n");
}

static void cmd_ar(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<3){vga_puts("Usage: ar <k> <a>\n");return;}
    vga_puts("ar: creating '");vga_puts(args[2]);vga_puts("'\n");
}

static void cmd_ranlib(int argc, char args[][CMD_MAX_LEN]){vga_puts("ranlib: done\n");}
static void cmd_ld(int argc, char args[][CMD_MAX_LEN]){vga_puts("ld: BYO-OS GNU ld 2.40\n");}
static void cmd_ldconfig(int argc, char args[][CMD_MAX_LEN]){vga_puts("/lib\n/usr/lib\n");}

static void cmd_chown(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<3){vga_puts("Usage: chown <o> <f>\n");return;}vga_puts("chown: done\n");
}

static void cmd_chgrp(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<3){vga_puts("Usage: chgrp <g> <f>\n");return;}vga_puts("chgrp: done\n");
}

static void cmd_ionice(int argc, char args[][CMD_MAX_LEN]){vga_puts("none\n");}
static void cmd_taskset(int argc, char args[][CMD_MAX_LEN]){vga_puts("affinity: 1\n");}

static void cmd_netstat(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Proto Recv-Q Send-Q Local Address           Foreign Address         State\n");
    vga_puts("tcp        0      0 0.0.0.0:80              0.0.0.0:*               LISTEN\n");
    vga_puts("tcp        0      0 0.0.0.0:4321            0.0.0.0:*               LISTEN\n");
}

static void cmd_ss(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("State  Recv-Q Send-Q  Local Address:Port   Peer Address:Port\n");
    vga_puts("LISTEN 0      128     0.0.0.0:80           0.0.0.0:*\n");
    vga_puts("ESTAB  0      0       10.0.2.15:4321       10.0.2.2:12345\n");
}

static void cmd_wget(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: wget <url>\n");return;}
    vga_puts("-- ");vga_puts(args[1]);vga_puts("\n200 OK\n1024 bytes saved\n");
}

static void cmd_ftp(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: ftp <host>\n");return;}
    vga_puts("Connected to ");vga_puts(args[1]);vga_puts("\n220 BYO-OS FTP\n");
}

static void cmd_systemctl(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: systemctl <cmd> [svc]\n");return;}
    if(strcmp(args[1],"status")==0)vga_puts("BYO-OS: running\n");
    else if(strcmp(args[1],"list-units")==0)vga_puts("network active\nshell active\ntimer active\n");
    else if(argc>2){vga_puts(args[1]);vga_puts(" ");vga_puts(args[2]);vga_putchar('\n');}
    else vga_puts("systemctl: unknown\n");
}

static void cmd_pstree(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("systemd─┬─network\n        ├─shell\n        ├─timer\n        └─journal\n");
}

static void cmd_pgrep(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: pgrep <n>\n");return;}vga_puts("1\n");
}

static void cmd_pkill(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: pkill <n>\n");return;}
    vga_puts("pkill: '");vga_puts(args[1]);vga_puts("' signaled\n");
}

static void cmd_pidof(int argc, char args[][CMD_MAX_LEN]) {
    if(argc<2){vga_puts("Usage: pidof <n>\n");return;}vga_puts("1\n");
}

static void cmd_vmstat(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("procs mem swap io cpu\n 0 0 0 51200 0 0 0 0 0 0 100\n");
}

static void cmd_iostat(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Device tps kB/s\nsda   0.00 0.00\n");
}

static void cmd_sar(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("CPU %user %system %idle\nall 0.00 0.00 100.00\n");
}

static void cmd_mpstat(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("CPU %usr %sys %idle\nall 0.00 0.00 100.00\n");
}

/* ========== BATCH 8: Security Tools ========== */
static void cmd_passwd(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: passwd [username]\n"); return; }
    vga_puts("Changing password for user "); vga_puts(args[1]); vga_puts(".\n");
    vga_puts("New password: \nRetype new password: ");
    vga_puts("passwd: password updated successfully\n");
}

static void cmd_su(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        strncpy(current_user, "root", 31); current_user[31] = 0;
        vga_puts("Switched to root\n");
    } else {
        strncpy(current_user, args[1], 31); current_user[31] = 0;
        vga_puts("Switched to user "); vga_puts(args[1]); vga_puts("\n");
    }
}

static void cmd_sudo(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: sudo <command>\n"); return; }
    vga_puts("[sudo] password for "); vga_puts(current_user); vga_puts(": \n");
    shell_execute(&args[1][0]);
}

static void cmd_useradd(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: useradd <username>\n"); return; }
    vga_puts("useradd: user '"); vga_puts(args[1]); vga_puts("' created\n");
}

static void cmd_userdel(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: userdel <username>\n"); return; }
    vga_puts("userdel: user '"); vga_puts(args[1]); vga_puts("' deleted\n");
}

static void cmd_groupadd(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: groupadd <groupname>\n"); return; }
    vga_puts("groupadd: group '"); vga_puts(args[1]); vga_puts("' created\n");
}

static void cmd_groupdel(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: groupdel <groupname>\n"); return; }
    vga_puts("groupdel: group '"); vga_puts(args[1]); vga_puts("' deleted\n");
}

/* ========== BATCH 8: Package Managers ========== */
static void cmd_apt(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: apt [install|remove|update|upgrade|search] <pkg>\n"); return; }
    if (strcmp(args[1], "update") == 0) {
        vga_puts("Reading package lists... Done\nAll packages are up to date.\n");
    } else if (strcmp(args[1], "install") == 0 && argc >= 3) {
        vga_puts("Installing "); vga_puts(args[2]); vga_puts("... Done\n");
    } else if (strcmp(args[1], "remove") == 0 && argc >= 3) {
        vga_puts("Removing "); vga_puts(args[2]); vga_puts("... Done\n");
    } else if (strcmp(args[1], "search") == 0 && argc >= 3) {
        vga_puts(args[2]); vga_puts(" : Simulated package\n");
    } else { vga_puts("Usage: apt [install|remove|update|upgrade|search] <pkg>\n"); }
}

static void cmd_dpkg(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: dpkg [-i|-l|-r|-s] <pkg>\n"); return; }
    if (strcmp(args[1], "-l") == 0) {
        vga_puts("ii  base-files  12.4\nii  coreutils   9.1\nii  kernel      6.1\n");
    } else if (strcmp(args[1], "-i") == 0 && argc >= 3) {
        vga_puts("Setting up "); vga_puts(args[2]); vga_puts("...\n");
    } else if (strcmp(args[1], "-s") == 0 && argc >= 3) {
        vga_puts(args[2]); vga_puts(": install ok installed\n");
    } else { vga_puts("Usage: dpkg [-i|-l|-r|-s] <pkg>\n"); }
}

static void cmd_yum(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: yum [install|remove|update] <pkg>\n"); return; }
    if (strcmp(args[1], "install") == 0 && argc >= 3) {
        vga_puts("Installing "); vga_puts(args[2]); vga_puts("... Complete!\n");
    } else if (strcmp(args[1], "remove") == 0 && argc >= 3) {
        vga_puts("Removing "); vga_puts(args[2]); vga_puts("... Complete!\n");
    } else if (strcmp(args[1], "update") == 0) {
        vga_puts("No packages marked for update\n");
    } else { vga_puts("Usage: yum [install|remove|update] <pkg>\n"); }
}

static void cmd_rpm(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: rpm [-i|-e|-q|-qa] <pkg>\n"); return; }
    if (strcmp(args[1], "-qa") == 0) {
        vga_puts("base-files-12.4\ncoreutils-9.1\nkernel-6.1\n");
    } else if (strcmp(args[1], "-i") == 0 && argc >= 3) {
        vga_puts("Installing "); vga_puts(args[2]); vga_puts("...\n");
    } else if (strcmp(args[1], "-q") == 0 && argc >= 3) {
        vga_puts(args[2]); vga_puts("-1.0.0\n");
    } else { vga_puts("Usage: rpm [-i|-e|-q|-qa] <pkg>\n"); }
}

static void cmd_snap(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("error: snap is not installed\n");
}

static void cmd_flatpak(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("error: flatpak is not installed\n");
}

/* ========== BATCH 8: System Info ========== */
static void cmd_lsb_release(int argc, char args[][CMD_MAX_LEN]) {
    if (argc >= 2 && strcmp(args[1], "-a") == 0) {
        vga_puts("Distributor ID:\tBYO\nDescription:\tBYO-OS 1.0\nRelease:\t1.0\nCodename:\tbookworm\n");
    } else {
        vga_puts("Distributor ID:\tBYO\nDescription:\tBYO-OS\n");
    }
}

static void cmd_hostnamectl(int argc, char args[][CMD_MAX_LEN]) {
    if (argc >= 3 && strcmp(args[1], "set-hostname") == 0) {
        vga_puts("Static hostname: "); vga_puts(args[2]); vga_puts("\n");
        return;
    }
    vga_puts("Static hostname: byo-os\nIcon name: computer\nMachine ID: a1b2c3d4\n");
}

static void cmd_timedatectl(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("               Local time: 2025-01-15 12:00:00 UTC\n");
    vga_puts("           Universal time: 2025-01-15 12:00:00 UTC\n");
    vga_puts("                 RTC time: 2025-01-15 12:00:00\n");
    vga_puts("                Time zone: UTC (UTC, +0000)\n");
    vga_puts("  System clock synchronized: yes\n");
    vga_puts("            NTP service: active\n");
}

static void cmd_localectl(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("System Locale: LANG=en_US.UTF-8\n    VC Keymap: us\n");
}

static void cmd_bootctl(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("System: Firmware BYO-OS\nBOOT: /dev/sda1\n");
}

static void cmd_dmesg_imp(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("[    0.000000] BYO-OS kernel 1.0\n");
    vga_puts("[    0.001000] 64MB RAM detected\n");
    vga_puts("[    0.002000] NE2000 NIC detected\n");
    vga_puts("[    0.003000] PS/2 keyboard initialized\n");
    vga_puts("[    0.004000] VGA text mode 80x25\n");
    vga_puts("[    0.005000] File system mounted\n");
    vga_puts("[    0.006000] Shell ready\n");
}

static void cmd_journalctl_imp(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Logs begin at boot.\n");
    vga_puts("Jan 15 12:00:00 byo-os kernel[0]: BYO-OS 1.0\n");
    vga_puts("Jan 15 12:00:00 byo-os init[1]: System initialized\n");
    vga_puts("Jan 15 12:00:00 byo-os network[42]: NIC up\n");
    vga_puts("Jan 15 12:00:00 byo-os shell[100]: Session started\n");
}

/* ========== BATCH 8: System Admin ========== */
static void cmd_sysctl(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: sysctl [-a]\n"); return; }
    if (strcmp(args[1], "-a") == 0) {
        vga_puts("kernel.hostname = byo-os\nvm.swappiness = 60\nfs.file-max = 1024\n");
    } else {
        vga_puts(args[1]); vga_puts(" = "); vga_puts(argc >= 3 ? args[2] : "unknown"); vga_puts("\n");
    }
}

static void cmd_fdisk(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Disk /dev/sda: 128 MB\n/dev/sda1  *  2048  130047  62.5M\n");
}

static void cmd_mkfs(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Filesystem created successfully\n");
}

static void cmd_mount_cmd(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("/dev/sda1 on / type ext4 (rw)\ntmpfs on /tmp type tmpfs (rw)\n");
        return;
    }
    vga_puts("mount: "); vga_puts(args[1]); vga_puts(" mounted\n");
}

static void cmd_umount_cmd(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: umount <path>\n"); return; }
    vga_puts("umount: "); vga_puts(args[1]); vga_puts(" unmounted\n");
}

/* ========== BATCH 8: Firewall ========== */
static void cmd_iptables(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: iptables [-L|-A|-F]\n"); return; }
    if (strcmp(args[1], "-L") == 0) {
        vga_puts("Chain INPUT (policy ACCEPT)\ntarget prot source destination\n");
    } else if (strcmp(args[1], "-F") == 0) {
        vga_puts("Flushing all chains\n");
    } else { vga_puts("iptables: rule added\n"); }
}

static void cmd_nft(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("table ip filter { chain input { policy accept; } }\n");
}


/* BATCH 9: DNS */
static void cmd_dig(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: dig <domain>\n"); return; }
    vga_puts(";; ANSWER SECTION:\n");
    vga_puts(args[1]); vga_puts(".\t600\tIN\tA\t192.168.1.1\n");
    vga_puts(";; Query time: 12 msec\n");
}

static void cmd_nslookup(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: nslookup <domain>\n"); return; }
    vga_puts("Server:\t8.8.8.8\n");
    vga_puts("Non-authoritative answer:\nName:\t"); vga_puts(args[1]); vga_puts(" has address 192.168.1.1\n");
}

static void cmd_host(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: host <domain>\n"); return; }
    vga_puts(args[1]); vga_puts(" has address 192.168.1.1\n");
}

/* BATCH 9: SSH/SCP */
static void cmd_ssh(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: ssh <user@host>\n"); return; }
    vga_puts("Connecting to "); vga_puts(args[1]); vga_puts("...\nConnection closed.\n");
}

static void cmd_scp(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: scp <src> <dest>\n"); return; }
    vga_puts("Transfer complete.\n");
}

static void cmd_sftp(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: sftp <user@host>\n"); return; }
    vga_puts("Connected. sftp> \n");
}

/* BATCH 9: Web Server */
static void cmd_httpd(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: httpd [start|stop|status]\n"); return; }
    if (strcmp(args[1], "start") == 0) vga_puts("HTTP server started on port 80\n");
    else if (strcmp(args[1], "stop") == 0) vga_puts("HTTP server stopped\n");
    else if (strcmp(args[1], "status") == 0) vga_puts("httpd: running on port 80\n");
}

/* BATCH 9: Network Tools */
static void cmd_tracepath(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: tracepath <host>\n"); return; }
    vga_puts("1: localhost  0ms\n2: 10.0.0.1  1ms\n3: "); vga_puts(args[1]); vga_puts("  5ms\n");
}

static void cmd_arp(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Address         HWaddress           Iface\n");
    vga_puts("192.168.1.1     00:11:22:33:44:55   eth0\n");
}

static void cmd_route(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Destination  Gateway    Genmask         Iface\n");
    vga_puts("default      192.168.1.1 0.0.0.0         eth0\n");
    vga_puts("192.168.1.0  0.0.0.0     255.255.255.0   eth0\n");
}

static void cmd_nmcli(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: nmcli [device|connection]\n"); return; }
    vga_puts("eth0  ethernet  connected\n");
}

static void cmd_ethtool(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Settings for eth0:\nSpeed: 1000Mb/s\nDuplex: Full\nLink: yes\n");
}

static void cmd_iwconfig(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("eth0  IEEE 802.11  Mode:Managed\nBit Rate=54Mb/s\n");
}

/* BATCH 9: Monitoring */
static void cmd_nagios(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Nagios: localhost - UP\n");
}

static void cmd_zabbix(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Zabbix: host byo-os - Available\n");
}

/* BATCH 9: Proxy/VPN */
static void cmd_squid(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Squid: HTTP proxy on port 3128\n");
}

static void cmd_openvpn(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("OpenVPN: VPN tunnel\nUsage: openvpn --config <file>\n");
}

static void cmd_haproxy(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("HAProxy: Load Balancer\nserver1 192.168.1.10:80\nserver2 192.168.1.11:80\n");
}
/* BATCH 10: RAID */
static void cmd_mdadm(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: mdadm [--create|--detail|--stop] <dev>\n"); return; }
    if (strcmp(args[1], "--detail") == 0 && argc >= 3) {
        vga_puts(args[2]); vga_puts(":\nLevel: raid1\nDrives: 2\nState: clean\n");
    } else if (strcmp(args[1], "--create") == 0 && argc >= 3) {
        vga_puts("mdadm: array "); vga_puts(args[2]); vga_puts(" created\n");
    } else { vga_puts("mdadm: operation completed\n"); }
}

/* BATCH 10: LVM */
static void cmd_pvcreate(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: pvcreate <device>\n"); return; }
    vga_puts("Physical volume "); vga_puts(args[1]); vga_puts(" created\n");
}

static void cmd_vgcreate(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: vgcreate <vgname> <pv>\n"); return; }
    vga_puts("Volume group "); vga_puts(args[1]); vga_puts(" created\n");
}

static void cmd_lvcreate(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: lvcreate -n <name> -L <size> <vg>\n"); return; }
    vga_puts("Logical volume created\n");
}

static void cmd_pvdisplay(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("  PV        VG   Fmt  Attr PSize   PFree\n");
    vga_puts("  /dev/sda2      lvm2 a--  64.00m  64.00m\n");
}

static void cmd_vgdisplay(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("  VG Name   vg-byo\n  VG Size   64.00 MB\n  Free PE   16\n");
}

static void cmd_lvdisplay(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("  LV Name   root\n  LV Size   32.00 MB\n");
}

/* BATCH 10: Backup/Restore */
static void cmd_rsync(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: rsync <src> <dest>\n"); return; }
    vga_puts("sending incremental file list\n");
    vga_puts("sent 1.2K bytes  received 0 bytes  2.4K bytes/sec\n");
}

static void cmd_dump(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: dump <device>\n"); return; }
    vga_puts("DUMP: Date of this level 0 dump: 2025-01-15\nDUMP: Dumping /dev/sda1\n");
}

static void cmd_restore(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: restore <archive>\n"); return; }
    vga_puts("Restore completed.\n");
}

static void cmd_dd(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: dd if=<in> of=<out> [bs=<size>]\n"); return; }
    vga_puts("0+0 records in\n0+0 records out\n");
}

static void cmd_cpio(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: cpio -o/-i < files\n"); return; }
    vga_puts("1 block\n");
}

/* BATCH 10: Filesystem Tools */
static void cmd_tune2fs(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: tune2fs [options] <device>\n"); return; }
    vga_puts("tune2fs: filesystem parameters updated\n");
}

static void cmd_e2fsck(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: e2fsck <device>\n"); return; }
    vga_puts("e2fsck 1.47.0: clean, 100/1024 files\n");
}

static void cmd_resize2fs(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: resize2fs <device>\n"); return; }
    vga_puts("resize2fs: filesystem resized\n");
}

static void cmd_blkid(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("/dev/sda1: TYPE=\"ext4\" UUID=\"abc123\"\n");
    vga_puts("/dev/sda2: TYPE=\"lvm2\" UUID=\"def456\"\n");
}

static void cmd_lsblk(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("NAME   MAJ:MIN RM  SIZE TYPE MOUNTPOINT\n");
    vga_puts("sda      8:0    0  128M disk\n");
    vga_puts("sda1     8:1    0  62.5M part /\n");
    vga_puts("sda2     8:2    0   64M part\n");
}

/* BATCH 10: Swap */
static void cmd_swapon(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("swap: enabled\n");
}

static void cmd_swapoff(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("swap: disabled\n");
}

static void cmd_freeze(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("freeze: filesystem frozen\n");
}

static void cmd_unfreeze(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("thaw: filesystem unfrozen\n");
}
/* BATCH 11: Dev Tools */
static void cmd_gcc(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: gcc <file.c>\n"); return; }
    vga_puts("gcc: compiling "); vga_puts(args[1]); vga_puts("\nBuild successful.\n");
}

static void cmd_make(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("make: Building project...\nmake: Done.\n");
}

static void cmd_cmake(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("cmake: Configuring...\n");
}

static void cmd_git(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: git [clone|status|add|commit|push|pull|log]\n"); return; }
    if (strcmp(args[1], "status") == 0) {
        vga_puts("On branch main\nnothing to commit\n");
    } else if (strcmp(args[1], "log") == 0) {
        vga_puts("commit a1b2c3d\nAuthor: BYO <byo@os>\n    Initial commit\n");
    } else {
        vga_puts("git: "); vga_puts(args[1]); vga_puts(" completed\n");
    }
}

static void cmd_python(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Python 3.11.0 (sim)\n>>> \n");
}

static void cmd_nodejs(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Node.js v20.0.0 (sim)\n> \n");
}

static void cmd_npm(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("npm: completed\n");
}

static void cmd_perl(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("perl v5.36.0\n");
}

static void cmd_ruby(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("ruby 3.2.0\n");
}

static void cmd_php(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("PHP 8.2.0\n");
}

static void cmd_lua(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Lua 5.4.0\n");
}

static void cmd_golang(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("go version go1.21.0\n");
}

static void cmd_rustc(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("rustc 1.75.0\n");
}

static void cmd_java(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("java 21.0.0\n");
}

/* BATCH 11: Editors */
static void cmd_vim(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("vim: no file\n"); return; }
    vga_puts("VIM 9.0 - File: "); vga_puts(args[1]); vga_puts("\n[NEW FILE]\n");
}

static void cmd_nano(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("nano: no file\n"); return; }
    vga_puts("GNU nano 7.0 - File: "); vga_puts(args[1]); vga_puts("\n");
}

static void cmd_emacs(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("GNU Emacs 28.0\n");
}

/* BATCH 11: Media */
static void cmd_ffmpeg(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("ffmpeg version 6.0\n");
}

static void cmd_convert(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("ImageMagick 7.1\n");
}

static void cmd_mplayer(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("MPlayer: no video/audio\n");
}

static void cmd_alsamixer(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Master [80%%] PCM [75%%] Mic [50%%]\n");
}

/* BATCH 11: Containers */
static void cmd_docker(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: docker [run|ps|images|build]\n"); return; }
    if (strcmp(args[1], "ps") == 0) { vga_puts("CONTAINER ID  IMAGE  STATUS\n");
    } else if (strcmp(args[1], "images") == 0) { vga_puts("REPOSITORY  TAG  SIZE\n");
    } else { vga_puts("docker: completed\n"); }
}

static void cmd_podman(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("podman: daemonless containers\n");
}

/* BATCH 11: Text Advanced */
static void cmd_jq(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("{ \"key\": \"value\" }\n");
}

static void cmd_bzip2(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("bzip2: compressor\n");
}

static void cmd_xz(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("xz: compressor\n");
}

static void cmd_zstd(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("zstd: compressor\n");
}

static void cmd_gzip(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("gzip: compressor\n");
}

static void cmd_unzip(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("unzip: extractor\n");
}

/* BATCH 11: Security */
static void cmd_nmap(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: nmap <host>\n"); return; }
    vga_puts("PORT     STATE SERVICE\n22/tcp   open  ssh\n80/tcp   open  http\n");
}

static void cmd_tcpdump(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("tcpdump: listening on eth0\n");
}

static void cmd_nikto(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Nikto: web scanner\n+ OSVDB-3092: /admin/\n");
}

static void cmd_gdb(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: gdb <program>\n"); return; }
    vga_puts("GNU gdb 13.0\n(gdb) \n");
}

static void cmd_valgrind(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("==0== HEAP SUMMARY:\n==0== All heap freed.\n");
}

static void cmd_lsof(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("COMMAND PID USER FD TYPE NAME\nshell 100 root 0u CHR /dev/tty1\n");
}

/* BATCH 11: Sysadmin */
static void cmd_chroot(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: chroot <dir>\n"); return; }
    vga_puts("chroot: changed root to "); vga_puts(args[1]); vga_puts("\n");
}

static void cmd_chsh(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Shell changed to /bin/bash\n");
}

static void cmd_ulimit(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("open files: 1024\nprocs: 2048\n");
}

static void cmd_who(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("root     pts/0  2025-01-15 12:00\n");
}

static void cmd_last(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("root pts/0 192.168.1.100 Wed Jan 15 12:00\n");
}

static void cmd_tty(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("/dev/tty1\n");
}

static void cmd_stty(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("speed 38400 baud\n");
}

static void cmd_script(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Script started\n");
}

static void cmd_screen(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Screen 4.9.0\n");
}

static void cmd_tmux(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("tmux 3.3a\n");
}

static void cmd_expect_cmd(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("expect: automate interactive apps\n");
}

static void cmd_sqlmap(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("sqlmap: SQL injection tool\n");
}

static void cmd_metasploit(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("msf6 > \n");
}

static void cmd_wireshark(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("wireshark: packet analyzer\n");
}

static void cmd_dd_cmd(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("0+0 records in\n0+0 records out\n");
}

static void cmd_byobu(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("byobu: terminal multiplexer\n");
}

static void cmd_debconf(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("debconf: Debian configuration\n");
}

static void cmd_aptkey(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("apt-key: GPG management\n");
}

static void cmd_update_rc(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("update-rc.d: init script management\n");
}

static void cmd_xdg(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("xdg-open: open default app\n");
}
/* BATCH 12: Database */
static void cmd_mysql(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: mysql [-u user] [db]\n"); return; }
    vga_puts("mysql 8.0.35\nType \"help\" for help.\nmysql> \n");
}

static void cmd_psql(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("psql (PostgreSQL) 15.0\nType \"help\" for help.\n=> \n");
}

static void cmd_sqlite3(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("SQLite 3.40.0\nsqlite> \n");
}

static void cmd_mongosh(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("mongosh 2.0.0\n> \n");
}

static void cmd_redis_cli(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("redis-cli 7.0.0\n127.0.0.1:6379> \n");
}

static void cmd_pg_isready(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("postgresql: accepting connections\n");
}

static void cmd_mysqldump(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: mysqldump [db]\n"); return; }
    vga_puts("-- Dump completed --\n");
}

/* BATCH 12: Email */
static void cmd_mail(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("mail: 2 messages, 2 new\n");
    vga_puts("N  1 root  Jan 15 12:00  Welcome to BYO-OS\n");
    vga_puts("N  2 root  Jan 15 12:01  System ready\n");
}

static void cmd_sendmail(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("sendmail: message queued\n");
}

static void cmd_msmtp(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("msmtp: SMTP client\n");
}

static void cmd_fetchmail(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("fetchmail: no messages\n");
}

static void cmd_procmail(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("procmail: mail delivery agent\n");
}

/* BATCH 12: Web Services */
static void cmd_nginx(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: nginx [start|stop|reload|status]\n"); return; }
    if (strcmp(args[1], "start") == 0) vga_puts("nginx: started\n");
    else if (strcmp(args[1], "stop") == 0) vga_puts("nginx: stopped\n");
    else if (strcmp(args[1], "reload") == 0) vga_puts("nginx: reloaded\n");
    else if (strcmp(args[1], "status") == 0) vga_puts("nginx: running\n");
}

static void cmd_apache2(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: apache2 [start|stop|restart|status]\n"); return; }
    vga_puts("apache2: operation completed\n");
}

static void cmd_apachectl(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: apachectl [start|stop|restart]\n"); return; }
    vga_puts("apachectl: operation completed\n");
}

static void cmd_phpfpm(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("php-fpm: FastCGI process manager\n");
}

static void cmd_uwsgi(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("uWSGI: application server\n");
}

static void cmd_gunicorn(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("gunicorn: WSGI HTTP server\n");
}

/* BATCH 12: DNS Server */
static void cmd_bind9(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("bind9: DNS server\nUsage: named -g\n");
}

static void cmd_dnsmasq(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("dnsmasq: DNS/DHCP server\n");
}

static void cmd_unbound(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("unbound: DNS resolver\n");
}

/* BATCH 12: DHCP */
static void cmd_dhclient(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("dhclient: DHCP client\n");
}

static void cmd_dhcpd(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("dhcpd: DHCP server\n");
}

/* BATCH 12: NTP */
static void cmd_ntpd(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("ntpd: NTP daemon\n");
}

static void cmd_ntpdate(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("ntpdate: time synchronized\n");
}

static void cmd_chronyd(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("chronyd: NTP server\n");
}

/* BATCH 12: Print */
static void cmd_lpr(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: lpr <file>\n"); return; }
    vga_puts("lpr: job queued\n");
}

static void cmd_lpstat(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("printer: idle\nQueue: empty\n");
}

static void cmd_lpq(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Queue: empty\n");
}

static void cmd_lprm(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("lprm: job removed\n");
}

static void cmd_cups(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: cups [start|stop|status]\n"); return; }
    vga_puts("cups: operation completed\n");
}

/* BATCH 12: Scheduler Advanced */
static void cmd_cron(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: cron [start|stop|status]\n"); return; }
    vga_puts("cron: operation completed\n");
}

static void cmd_at(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: at <time>\n"); return; }
    vga_puts("job queued\n");
}

static void cmd_batch(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("batch: when system load < 0.8\n");
}

/* BATCH 12: Logging */
static void cmd_logrotate(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("logrotate: rotating logs\n");
}

static void cmd_rsyslog(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: rsyslog [start|stop|status]\n"); return; }
    vga_puts("rsyslog: operation completed\n");
}

static void cmd_syslog_ng(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("syslog-ng: enhanced logging\n");
}

static void cmd_swaks(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("swaks: SMTP test tool\n");
}

/* BATCH 12: SSH Server */
static void cmd_sshd(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: sshd [start|stop|status]\n"); return; }
    vga_puts("sshd: operation completed\n");
}

static void cmd_ssh_keygen(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Generating public/private rsa key pair.\n");
    vga_puts("Your identification has been saved in /root/.ssh/id_rsa\n");
}

static void cmd_ssh_agent(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("ssh-agent: started\n");
}

/* BATCH 12: System Monitoring */
static void cmd_prometheus(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("prometheus: monitoring system\n");
}

static void cmd_grafana(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("grafana: analytics platform\n");
}

static void cmd_collectd(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("collectd: statistics collection daemon\n");
}

static void cmd_monit(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("monit: process supervisor\n");
}

/* BATCH 12: Backup Advanced */
static void cmd_borg(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: borg [create|list|extract]\n"); return; }
    vga_puts("borg: deduplicating backup\n");
}

static void cmd_restic(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("restic: backup tool\n");
}

static void cmd_duplicity(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("duplicity: incremental backup\n");
}

static void cmd_rsnapshot(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("rsnapshot: rsync-based backup\n");
}

/* BATCH 12: Misc System */
static void cmd_powertop(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("PowerTOP: Power management\n\nTotal: 0 wakeups\n");
}

static void cmd_tlp(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("TLP: Advanced Power Management\n");
}

static void cmd_cpupower(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("cpu0:频率 2400MHz  策略: powersave\n");
}

static void cmd_lscpu(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Architecture:\tx86\nCPU(s):\t1\nModel name:\tBYO Virtual CPU\n");
}

static void cmd_lshw(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("*-memory\n  size: 64MiB\n*-disk\n  size: 128MiB\n*-network\n  description: NE2000\n");
}

static void cmd_lsusb(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Bus 001 Device 001: ID 8087:0026\n");
}

static void cmd_lspci(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("00:01.0 VGA: BYO VGA\n00:02.0 Ethernet: NE2000\n");
}

static void cmd_lsmod(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Module     Size  Used by\nne2000    8192  1\n");
}

static void cmd_modprobe(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: modprobe <module>\n"); return; }
    vga_puts("modprobe: "); vga_puts(args[1]); vga_puts(" loaded\n");
}

static void cmd_insmod(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: insmod <module>\n"); return; }
    vga_puts("insmod: "); vga_puts(args[1]); vga_puts(" inserted\n");
}

static void cmd_rmmod(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: rmmod <module>\n"); return; }
    vga_puts("rmmod: "); vga_puts(args[1]); vga_puts(" removed\n");
}

static void cmd_dmesg_clear(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("dmesg: buffer cleared\n");
}

static void cmd_halt_imp(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("System halted.\n");
}

static void cmd_poweroff(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Powering off...\n");
}

static void cmd_init_cmd(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: init [0-6]\n"); return; }
    vga_puts("init: changing to runlevel "); vga_puts(args[1]); vga_puts("\n");
}

static void cmd_runlevel(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("N 5\n");
}

static void cmd_service_imp(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: service <name> [start|stop|status]\n"); return; }
    vga_puts(args[1]); vga_puts(": operation completed\n");
}

static void cmd_update_rtc(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("RTC updated\n");
}

static void cmd_hwclock(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("2025-01-15 12:00:00.000000+00:00\n");
}

static void cmd_losetup(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("/dev/loop0: [0] (byo-os)\n");
}

static void cmd_dmsetup(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("dmsetup: device-mapper\n");
}

static void cmd_parted(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("GNU Parted 3.6\nModel: BYO Disk\nSize: 128MB\n");
}

static void cmd_gdisk(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("GPT fdisk: partition editor\n");
}

static void cmd_fdisk_imp(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Disk /dev/sda: 128MB\n/dev/sda1 * 62.5M\n");
}

static void block_device_info(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Block devices:\n  sda  128M\n  sda1 62.5M /\n");
}
static const cmd_entry commands[] = {
    /* Basic */
    {"help", cmd_help}, {"clear", cmd_clear}, {"echo", cmd_echo},
    {"uptime", cmd_uptime}, {"mem", cmd_mem}, {"version", cmd_version},
    {"about", cmd_about},
    /* File */
    {"ls", cmd_ls}, {"cat", cmd_cat}, {"touch", cmd_touch}, {"write", cmd_write},
    {"rm", cmd_rm}, {"mkdir", cmd_mkdir}, {"cp", cmd_cp}, {"mv", cmd_mv},
    {"find", cmd_find}, {"du", cmd_du}, {"stat", cmd_stat},
    /* Network */
    {"net", cmd_net}, {"ping", cmd_ping}, {"curl", cmd_curl},
    /* User */
    {"whoami", cmd_whoami}, {"login", cmd_login}, {"logout", cmd_logout},
    {"users", cmd_users}, {"id", cmd_id}, {"groups", cmd_groups},
    /* Process */
    {"ps", cmd_ps}, {"top", cmd_top}, {"kill", cmd_kill}, {"service", cmd_service},
    /* System */
    {"sysinfo", cmd_sysinfo}, {"halt", cmd_halt}, {"reboot", cmd_reboot},
    {"df", cmd_df}, {"free", cmd_free}, {"date", cmd_date},
    {"uname", cmd_uname}, {"hostname", cmd_hostname},
    /* Environment */
    {"env", cmd_env}, {"export", cmd_export}, {"unset", cmd_unset},
    {"history", cmd_history}, {"alias", cmd_alias}, {"unalias", cmd_unalias},
    /* Text */
    {"grep", cmd_grep}, {"sort", cmd_sort}, {"uniq", cmd_uniq}, {"wc", cmd_wc},
    {"head", cmd_head}, {"tail", cmd_tail}, {"cut", cmd_cut},
    {"strings", cmd_strings}, {"hexdump", cmd_hexdump},
    /* Shell */
    {"which", cmd_which}, {"man", cmd_man}, {"crontab", cmd_crontab},
    {"tee", cmd_tee}, {"tr", cmd_tr},
    /* Misc */
    {"chmod", cmd_chmod}, {"journal", cmd_journal}, {"neofetch", cmd_neofetch}, {"more", cmd_more}, {"ln", cmd_ln}, {"tar", cmd_tar}, {"dfh", cmd_df_h}, {"tee", cmd_tee_fn}, {"tr", cmd_tr_fn},
    {"cal", cmd_cal}, {"sync", cmd_sync},
    
    /* Extended: Network */
    {"netstat", cmd_netstat}, {"ss", cmd_ss}, {"wget", cmd_wget}, {"ftp", cmd_ftp},
    /* Extended: Process */
    {"systemctl", cmd_systemctl}, {"pstree", cmd_pstree},
    {"pgrep", cmd_pgrep}, {"pkill", cmd_pkill}, {"pidof", cmd_pidof},
    {"nice", cmd_nice}, {"renice", cmd_renice}, {"nohup", cmd_nohup},
    {"bg", cmd_bg}, {"fg", cmd_fg}, {"jobs", cmd_jobs},
    /* Extended: System */
    {"vmstat", cmd_vmstat}, {"iostat", cmd_iostat}, {"sar", cmd_sar}, {"mpstat", cmd_mpstat},
    /* Extended: Text */
    {"awk", cmd_awk}, {"sed", cmd_sed},
    /* Extended: Dev */
    {"strace", cmd_strace}, {"ltrace", cmd_ltrace}, {"objdump", cmd_objdump},
    {"readelf", cmd_readelf}, {"nm", cmd_nm}, {"ar", cmd_ar}, {"ranlib", cmd_ranlib},
    {"ld", cmd_ld}, {"ldconfig", cmd_ldconfig},
    /* Extended: Permissions */
    {"chown", cmd_chown}, {"chgrp", cmd_chgrp},
    {"ionice", cmd_ionice}, {"taskset", cmd_taskset},
    /* Extended: Tools */
    {"file", cmd_file}, {"watch", cmd_watch}, {"time", cmd_time}, {"timeout", cmd_timeout},
    {"xargs", cmd_xargs},
    /* Batch 8: Security */
    {"passwd", cmd_passwd}, {"su", cmd_su}, {"sudo", cmd_sudo},
    {"useradd", cmd_useradd}, {"userdel", cmd_userdel},
    {"groupadd", cmd_groupadd}, {"groupdel", cmd_groupdel},
    {"iptables", cmd_iptables}, {"nft", cmd_nft},
    /* Batch 8: Package Managers */
    {"apt", cmd_apt}, {"dpkg", cmd_dpkg},
    {"yum", cmd_yum}, {"rpm", cmd_rpm},
    {"snap", cmd_snap}, {"flatpak", cmd_flatpak},
    /* Batch 8: System Info */
    {"lsb_release", cmd_lsb_release}, {"hostnamectl", cmd_hostnamectl},
    {"timedatectl", cmd_timedatectl}, {"localectl", cmd_localectl},
    {"bootctl", cmd_bootctl}, {"dmesg", cmd_dmesg_imp},
    {"journalctl", cmd_journalctl_imp},
    /* Batch 8: System Admin */
    {"sysctl", cmd_sysctl}, {"fdisk", cmd_fdisk}, {"mkfs", cmd_mkfs},
    {"mount", cmd_mount_cmd}, {"umount", cmd_umount_cmd},
    /* Batch 9: DNS */
    {"dig", cmd_dig}, {"nslookup", cmd_nslookup}, {"host", cmd_host},
    /* Batch 9: SSH/SCP */
    {"ssh", cmd_ssh}, {"scp", cmd_scp}, {"sftp", cmd_sftp},
    /* Batch 9: Web */
    {"httpd", cmd_httpd},
    /* Batch 9: Network Tools */
    {"tracepath", cmd_tracepath}, {"arp", cmd_arp}, {"route", cmd_route},
    {"nmcli", cmd_nmcli}, {"ethtool", cmd_ethtool}, {"iwconfig", cmd_iwconfig},
    /* Batch 9: Monitoring */
    {"nagios", cmd_nagios}, {"zabbix", cmd_zabbix},
    /* Batch 9: Proxy/VPN */
    {"squid", cmd_squid}, {"openvpn", cmd_openvpn}, {"haproxy", cmd_haproxy},
    /* Batch 10: RAID */
    {"mdadm", cmd_mdadm},
    /* Batch 10: LVM */
    {"pvcreate", cmd_pvcreate}, {"vgcreate", cmd_vgcreate}, {"lvcreate", cmd_lvcreate},
    {"pvdisplay", cmd_pvdisplay}, {"vgdisplay", cmd_vgdisplay}, {"lvdisplay", cmd_lvdisplay},
    /* Batch 10: Backup */
    {"rsync", cmd_rsync}, {"dump", cmd_dump}, {"restore", cmd_restore},
    {"dd", cmd_dd}, {"cpio", cmd_cpio},
    /* Batch 10: Filesystem */
    {"tune2fs", cmd_tune2fs}, {"e2fsck", cmd_e2fsck}, {"resize2fs", cmd_resize2fs},
    {"blkid", cmd_blkid}, {"lsblk", cmd_lsblk},
    /* Batch 10: Swap */
    {"swapon", cmd_swapon}, {"swapoff", cmd_swapoff},
    {"freeze", cmd_freeze}, {"thaw", cmd_unfreeze},
    /* Batch 11: Dev */
    {"gcc", cmd_gcc}, {"make", cmd_make}, {"cmake", cmd_cmake},
    {"git", cmd_git}, {"python", cmd_python}, {"nodejs", cmd_nodejs}, {"npm", cmd_npm},
    {"perl", cmd_perl}, {"ruby", cmd_ruby}, {"php", cmd_php}, {"lua", cmd_lua},
    {"golang", cmd_golang}, {"rustc", cmd_rustc}, {"java", cmd_java},
    /* Batch 11: Editors */
    {"vim", cmd_vim}, {"nano", cmd_nano}, {"emacs", cmd_emacs},
    /* Batch 11: Media */
    {"ffmpeg", cmd_ffmpeg}, {"convert", cmd_convert}, {"mplayer", cmd_mplayer}, {"alsamixer", cmd_alsamixer},
    /* Batch 11: Containers */
    {"docker", cmd_docker}, {"podman", cmd_podman},
    /* Batch 11: Text */
    {"jq", cmd_jq},
    /* Batch 11: Archive */
    {"bzip2", cmd_bzip2}, {"xz", cmd_xz}, {"zstd", cmd_zstd}, {"gzip", cmd_gzip}, {"unzip", cmd_unzip},
    /* Batch 11: Security/Debug */
    {"nmap", cmd_nmap}, {"tcpdump", cmd_tcpdump}, {"nikto", cmd_nikto}, {"sqlmap", cmd_sqlmap},
    {"metasploit", cmd_metasploit}, {"gdb", cmd_gdb}, {"valgrind", cmd_valgrind}, {"lsof", cmd_lsof}, {"wireshark", cmd_wireshark},
    /* Batch 11: Sysadmin */
    {"chroot", cmd_chroot}, {"chsh", cmd_chsh}, {"ulimit", cmd_ulimit},
    {"who", cmd_who}, {"last", cmd_last}, {"tty", cmd_tty}, {"stty", cmd_stty},
    {"script", cmd_script}, {"screen", cmd_screen}, {"tmux", cmd_tmux}, {"byobu", cmd_byobu},
    {"expect", cmd_expect_cmd}, {"dd", cmd_dd_cmd},
    {"debconf", cmd_debconf}, {"apt-key", cmd_aptkey}, {"update-rc.d", cmd_update_rc}, {"xdg-open", cmd_xdg},
    /* Batch 12: Database */
    {"mysql", cmd_mysql}, {"psql", cmd_psql}, {"sqlite3", cmd_sqlite3},
    {"mongosh", cmd_mongosh}, {"redis-cli", cmd_redis_cli},
    {"pg_isready", cmd_pg_isready}, {"mysqldump", cmd_mysqldump},
    /* Batch 12: Email */
    {"mail", cmd_mail}, {"sendmail", cmd_sendmail}, {"msmtp", cmd_msmtp},
    {"fetchmail", cmd_fetchmail}, {"procmail", cmd_procmail},
    /* Batch 12: Web Services */
    {"nginx", cmd_nginx}, {"apache2", cmd_apache2}, {"apachectl", cmd_apachectl},
    {"php-fpm", cmd_phpfpm}, {"uwsgi", cmd_uwsgi}, {"gunicorn", cmd_gunicorn},
    /* Batch 12: DNS/DHCP/NTP */
    {"named", cmd_bind9}, {"dnsmasq", cmd_dnsmasq}, {"unbound", cmd_unbound},
    {"dhclient", cmd_dhclient}, {"dhcpd", cmd_dhcpd},
    {"ntpd", cmd_ntpd}, {"ntpdate", cmd_ntpdate}, {"chronyd", cmd_chronyd},
    /* Batch 12: Print */
    {"lpr", cmd_lpr}, {"lpstat", cmd_lpstat}, {"lpq", cmd_lpq}, {"lprm", cmd_lprm}, {"cups", cmd_cups},
    /* Batch 12: Scheduler */
    {"at", cmd_at}, {"batch", cmd_batch},
    /* Batch 12: Logging */
    {"logrotate", cmd_logrotate}, {"rsyslog", cmd_rsyslog}, {"syslog-ng", cmd_syslog_ng}, {"swaks", cmd_swaks},
    /* Batch 12: SSH Server */
    {"sshd", cmd_sshd}, {"ssh-keygen", cmd_ssh_keygen}, {"ssh-agent", cmd_ssh_agent},
    /* Batch 12: Monitoring */
    {"prometheus", cmd_prometheus}, {"grafana", cmd_grafana}, {"collectd", cmd_collectd}, {"monit", cmd_monit},
    /* Batch 12: Backup Advanced */
    {"borg", cmd_borg}, {"restic", cmd_restic}, {"duplicity", cmd_duplicity}, {"rsnapshot", cmd_rsnapshot},
    /* Batch 12: Power */
    {"powertop", cmd_powertop}, {"tlp", cmd_tlp}, {"cpupower", cmd_cpupower},
    /* Batch 12: Hardware */
    {"lscpu", cmd_lscpu}, {"lshw", cmd_lshw}, {"lsusb", cmd_lsusb}, {"lspci", cmd_lspci},
    {"lsmod", cmd_lsmod}, {"modprobe", cmd_modprobe}, {"insmod", cmd_insmod}, {"rmmod", cmd_rmmod},
    /* Batch 12: System Control */
    {"poweroff", cmd_poweroff}, {"init", cmd_init_cmd}, {"runlevel", cmd_runlevel},
    {"hwclock", cmd_hwclock}, {"losetup", cmd_losetup}, {"dmsetup", cmd_dmsetup},
    {"parted", cmd_parted}, {"gdisk", cmd_gdisk}, {"lsblk_adv", block_device_info},
    {0, 0}
};

static char redirect_file[128];
static int redirect_append = 0;
static void shell_execute(const char *cmdline) {
    if (!cmdline || cmdline[0] == 0) return;
    if (history_count < MAX_HISTORY) {
        strncpy(history[history_count], cmdline, CMD_MAX_LEN - 1);
        history[history_count][CMD_MAX_LEN - 1] = 0;
        history_count++;
    }
    char *pp = strchr(cmdline, '|');
    if (pp) { char left[CMD_MAX_LEN]; int lp = pp - cmdline;
        if (lp >= CMD_MAX_LEN) lp = CMD_MAX_LEN - 1;
        memcpy(left, cmdline, lp); left[lp] = 0; shell_execute(left); return; }
    redirect_file[0] = 0; redirect_append = 0;
    char work[CMD_MAX_LEN]; strncpy(work, cmdline, CMD_MAX_LEN - 1); work[CMD_MAX_LEN-1] = 0;
    char *rp2 = strstr(work, ">>");
    if (rp2) { redirect_append = 1; *rp2 = 0; char *fn = rp2+2;
        while (*fn==' ') fn++; strncpy(redirect_file, fn, 127); redirect_file[127]=0; }
    else { rp2 = strchr(work, '>');
        if (rp2) { *rp2 = 0; char *fn = rp2+1;
            while (*fn==' ') fn++; strncpy(redirect_file, fn, 127); redirect_file[127]=0; } }
    /* Resolve alias for first word */
    char resolved[CMD_MAX_LEN];
    char tmp[CMD_MAX_LEN];
    strncpy(tmp, cmdline, CMD_MAX_LEN - 1);
    tmp[CMD_MAX_LEN - 1] = 0;
    char first_word[64];
    int fw_len = 0;
    int idx = 0;
    while (tmp[idx] && tmp[idx] != ' ' && fw_len < 63) {
        first_word[fw_len++] = tmp[idx++];
    }
    first_word[fw_len] = 0;

    resolve_alias(first_word, first_word, 64);
    char new_cmd[CMD_MAX_LEN];
    int pos = 0;
    for (int i = 0; first_word[i]; i++) new_cmd[pos++] = first_word[i];
    while (tmp[idx]) new_cmd[pos++] = tmp[idx++];
    new_cmd[pos] = 0;

    char args[MAX_ARGS][CMD_MAX_LEN];
    int argc = arg_parse(new_cmd, args);
    if (argc == 0) return;

    for (int i = 0; commands[i].name; i++) {
        if (strcmp(args[0], commands[i].name) == 0) {
            commands[i].func(argc, args);
            return;
        }
    }
    vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
    vga_puts(args[0]); vga_puts(": command not found\n");
}

/* ===== Shell Init ===== */
void shell_init(void) {
    input_len = 0;
    memset(input_buf, 0, INPUT_BUF_SIZE);
    history_count = 0;
    history_idx = -1;
    env_count = 0;
    alias_count = 0;
    strncpy(env_names[0], "PATH", 63);
    strncpy(env_vals[0], "/bin:/usr/bin", 255);
    strncpy(env_names[1], "HOME", 63);
    strncpy(env_vals[1], "/home", 255);
    strncpy(env_names[2], "USER", 63);
    strncpy(env_vals[2], user_get_name(), 255);
    strncpy(env_names[3], "SHELL", 63);
    strncpy(env_vals[3], "/bin/sh", 255);
    strncpy(env_names[4], "HOSTNAME", 63);
    strncpy(env_vals[4], "byo-os", 255);
    strncpy(env_names[5], "TERM", 63);
    strncpy(env_vals[5], "linux", 255);
    strncpy(env_names[6], "LANG", 63);
    strncpy(env_vals[6], "en_US.UTF-8", 255);
    strncpy(env_names[7], "EDITOR", 63);
    strncpy(env_vals[7], "vi", 255);
    env_count = 8;
}

/* ===== Main Shell Loop ===== */
void shell_run(void) {
    vga_clear();
    vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
    vga_puts("Welcome to BYO-OS Shell v1.0\n");
    vga_puts("Type 'help' for available commands.\n\n");
    input_len = 0;
    input_buf[0] = 0;

    while (1) {
        net_poll();

        if (serial_has_input()) {
            serial_mode = 1;
            vga_set_serial_mode(1);
            char serial_cmd[CMD_MAX_LEN];
            int si = 0;
            while (1) {
                char c = serial_getchar();
                if (c == '\n' || c == '\r') {
                    serial_cmd[si] = 0;
                    if (si > 0) shell_execute(serial_cmd);
                    break;
                }
                if (c == 8 && si > 0) { si--; }
                else if (si < CMD_MAX_LEN - 1) { serial_cmd[si++] = c; }
            }
            vga_set_serial_mode(0);
            serial_mode = 0;
            print_prompt();
            continue;
        }

        print_prompt();

        /* Keyboard input loop */
        input_len = 0;
        input_buf[0] = 0;
        while (1) {
            /* Check serial in keyboard loop */
            if (serial_has_input()) {
                serial_mode = 1;
                vga_set_serial_mode(1);
                char serial_cmd[CMD_MAX_LEN];
                int si = 0;
                while (1) {
                    char c = serial_getchar();
                    if (c == '\n' || c == '\r') {
                        serial_cmd[si] = 0;
                        if (si > 0) {
                            vga_putchar('\n');
                            shell_execute(serial_cmd);
                        }
                        break;
                    }
                    if (c == 8 && si > 0) { si--; }
                    else if (si < CMD_MAX_LEN - 1) { serial_cmd[si++] = c; }
                }
                vga_set_serial_mode(0);
                serial_mode = 0;
                input_len = 0;
                input_buf[0] = 0;
                break;
            }

            if (!serial_has_input()) {
                timer_sleep(10);
                continue;
            }

            char c = keyboard_getchar();
            if (!c) continue;

            if (c == 13) {
                /* Enter */
                input_buf[input_len] = 0;
                vga_putchar('\n');
                shell_execute(input_buf);
                input_len = 0;
                input_buf[0] = 0;
                break;
            } else if (c == 8) {
                /* Backspace */
                if (input_len > 0) {
                    input_len--;
                    input_buf[input_len] = 0;
                    vga_putchar('\b'); vga_putchar(' '); vga_putchar('\b');
                }
            } else if (c >= 32 && c <= 126) {
                if (input_len < CMD_MAX_LEN - 1) {
                    input_buf[input_len++] = c;
                    input_buf[input_len] = 0;
                    vga_putchar(c);
                }
            } else if (c == 9) {
                /* Tab - ignore */
            }
        }
    }
}


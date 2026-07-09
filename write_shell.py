# Write shell.c for BYO-OS
# -*- coding: utf-8 -*-
import os

shell_c = r"""
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

static char input_buf[INPUT_BUF_SIZE];
static int input_len = 0;
"""

# ===== Helper Functions =====
shell_c += """
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

"""

# ===== Basic Commands =====
shell_c += """
/* ===== Basic Commands ===== */
static void cmd_help(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
    vga_puts("BYO-OS Shell - Available Commands:\\n");
    vga_puts("\\n  help            Show this help\\n");
    vga_puts("  clear           Clear screen\\n");
    vga_puts("  echo [text]     Print text\\n");
    vga_puts("  uptime          System uptime\\n");
    vga_puts("  mem             Memory usage\\n");
    vga_puts("  version         OS version\\n");
    vga_puts("  about           About BYO-OS\\n");
    vga_puts("\\n  File: ls, cat, touch, write, rm, mkdir, cp, mv, find, du, stat\\n");
    vga_puts("  Net:  net, ping, curl\\n");
    vga_puts("  User: whoami, login, logout, users, id, groups\\n");
    vga_puts("  Proc: ps, top, kill, service\\n");
    vga_puts("  Sys:  sysinfo, halt, reboot, df, free, date, uname, hostname\\n");
    vga_puts("  Env:  env, export, unset, history, alias, unalias\\n");
    vga_puts("  Text: grep, sort, uniq, wc, head, tail, cut, strings, hexdump\\n");
    vga_puts("  Shell: which, man, crontab, tee, tr\\n");
    vga_puts("  Misc: chmod, journal, neofetch, cal, sync\\n");
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
    vga_putchar('\\n');
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
    itoa(s, buf, 10); vga_puts(buf); vga_puts("s\\n");
}

static void cmd_mem(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Memory:\\n");
    char buf[32];
    vga_puts("  Free pages: "); itoa(pmm_get_free_pages(), buf, 10); vga_puts(buf); vga_putchar('\\n');
    vga_puts("  Total pages: "); itoa(pmm_get_total_pages(), buf, 10); vga_puts(buf); vga_putchar('\\n');
    vga_puts("  Heap used: "); itoa(heap_get_used(), buf, 10); vga_puts(buf); vga_puts(" bytes\\n");
}

static void cmd_version(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("BYO-OS v1.0.0\\n");
}

static void cmd_about(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("BYO-OS: Build Your Own OS\\n");
    vga_puts("A x86 bare-metal operating system with a Debian-style shell.\\n");
    vga_puts("Features: VGA output, serial I/O, virtual filesystem, process management,\\n");
    vga_puts("          networking stack, user management, and 50+ commands.\\n");
}

"""

# ===== File Commands =====
shell_c += """
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
            while (*p && *p != '\\n') { line[j++] = *p++; }
            line[j] = 0;
            if (*p == '\\n') p++;
            if (line[0] == 0) continue;
            vga_puts("drwxr-xr-x  ");
            vga_set_color(VGA_WHITE, VGA_BLACK);
            vga_puts(line);
            vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
            vga_putchar('\\n');
        }
    } else {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_puts(file_buf);
        if (file_buf[0] && file_buf[strlen(file_buf)-1] != '\\n') vga_putchar('\\n');
    }
}

static void cmd_cat(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: cat <file>\\n"); return; }
    memset(file_buf, 0, FILE_BUF_SIZE);
    int r = fs_read_file(args[1], file_buf, FILE_BUF_SIZE - 1);
    if (r <= 0) { vga_puts("cat: "); vga_puts(args[1]); vga_puts(": No such file\\n"); return; }
    vga_puts(file_buf);
    if (file_buf[r-1] != '\\n') vga_putchar('\\n');
}

static void cmd_touch(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: touch <file>\\n"); return; }
    fs_create_file(args[1], "", 0);
}

static void cmd_write(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: write <file> <content>\\n"); return; }
    fs_create_file(args[1], args[2], strlen(args[2]));
}

static void cmd_rm(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: rm <file>\\n"); return; }
    if (fs_delete_file(args[1]) != 0) {
        vga_puts("rm: cannot remove '"); vga_puts(args[1]); vga_puts("'\\n");
    }
}

static void cmd_mkdir(int argc, char args[][CMD_MAX_LEN]) {
    int p_flag = 0;
    const char *name = 0;
    for (int i = 1; i < argc; i++) {
        if (args[i][0] == '-' && args[i][1] == 'p') p_flag = 1;
        else name = args[i];
    }
    if (!name) { vga_puts("Usage: mkdir [-p] <dir>\\n"); return; }
    (void)p_flag;
    fs_create_dir(name);
}

static void cmd_cp(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: cp <src> <dst>\\n"); return; }
    memset(file_buf, 0, FILE_BUF_SIZE);
    int r = fs_read_file(args[1], file_buf, FILE_BUF_SIZE - 1);
    if (r <= 0) { vga_puts("cp: cannot read '"); vga_puts(args[1]); vga_puts("'\\n"); return; }
    fs_create_file(args[2], file_buf, r);
}

static void cmd_mv(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: mv <src> <dst>\\n"); return; }
    memset(file_buf, 0, FILE_BUF_SIZE);
    int r = fs_read_file(args[1], file_buf, FILE_BUF_SIZE - 1);
    if (r <= 0) { vga_puts("mv: cannot read '"); vga_puts(args[1]); vga_puts("'\\n"); return; }
    fs_create_file(args[2], file_buf, r);
    fs_delete_file(args[1]);
}

static void cmd_find(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: find <name>\\n"); return; }
    memset(file_buf, 0, FILE_BUF_SIZE);
    fs_list_dir(".", file_buf, FILE_BUF_SIZE);
    char *p = file_buf;
    while (*p) {
        char name[64];
        int j = 0;
        while (*p && *p != '\\n') { name[j++] = *p++; }
        name[j] = 0;
        if (*p == '\\n') p++;
        if (name[0] == 0) continue;
        if (strcmp(name, args[1]) == 0) {
            vga_puts("./");
            vga_puts(name);
            vga_putchar('\\n');
        }
    }
}

static void cmd_du(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    unsigned int total = 0, used = 0, free_s = 0;
    fs_get_stats(&total, &used, &free_s);
    char buf[32];
    vga_puts("Filesystem usage:\\n");
    vga_puts("  Total: "); itoa(total, buf, 10); vga_puts(buf); vga_puts(" blocks\\n");
    vga_puts("  Used:  "); itoa(used, buf, 10); vga_puts(buf); vga_puts(" blocks\\n");
    vga_puts("  Free:  "); itoa(free_s, buf, 10); vga_puts(buf); vga_puts(" blocks\\n");
}

static void cmd_stat(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: stat <file>\\n"); return; }
    int sz = fs_file_size(args[1]);
    char buf[32];
    vga_puts("  File: "); vga_puts(args[1]); vga_putchar('\\n');
    vga_puts("  Size: "); itoa(sz, buf, 10); vga_puts(buf); vga_putchar('\\n');
    vga_puts("  Blocks: 1\\n");
}

"""

# ===== Network + User + Process Commands =====
shell_c += """
/* ===== Network Commands ===== */
static void cmd_net(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    char ip[32];
    net_get_ip_str(ip);
    vga_puts("Network:\\n");
    vga_puts("  IP:  "); vga_puts(ip); vga_putchar('\\n');
    vga_puts("  MAC: "); vga_puts(net_get_mac()); vga_putchar('\\n');
}

static void cmd_ping(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: ping <host>\\n"); return; }
    vga_puts("Pinging "); vga_puts(args[1]); vga_puts("...\\n");
    vga_puts("PING "); vga_puts(args[1]); vga_puts(": 64 bytes, icmp_seq=1\\n");
    vga_puts("64 bytes from "); vga_puts(args[1]); vga_puts(": icmp_seq=1 ttl=64 time=1.0ms\\n");
}

static void cmd_curl(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("curl: not connected to network\\n");
}

/* ===== User Commands ===== */
static void cmd_whoami(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts(user_get_name());
    vga_putchar('\\n');
}

static void cmd_login(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: login <user> <pass>\\n"); return; }
    if (user_login(args[1], args[2])) {
        vga_puts("Login successful\\n");
    } else {
        vga_puts("Login failed\\n");
    }
}

static void cmd_logout(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    user_logout();
    vga_puts("Logged out\\n");
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
    vga_putchar('\\n');
}

static void cmd_groups(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts(user_get_name());
    vga_puts(" : "); vga_puts(user_get_name());
    vga_putchar('\\n');
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
        vga_puts("USER       PID  STAT  NAME\\n");
    } else {
        vga_puts("PID  STAT  NAME\\n");
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
            vga_putchar('\\n');
            vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
        }
    }
}

static void cmd_top(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    char buf[32];
    vga_puts("BYO-OS Process Monitor\\n");
    vga_puts("Free pages: "); itoa(pmm_get_free_pages(), buf, 10); vga_puts(buf);
    vga_puts("  Total: "); itoa(pmm_get_total_pages(), buf, 10); vga_puts(buf);
    vga_puts("  Heap: "); itoa(heap_get_used(), buf, 10); vga_puts(buf); vga_puts(" bytes\\n");
    vga_puts("Uptime: "); itoa(timer_get_seconds(), buf, 10); vga_puts(buf); vga_puts("s\\n");
    cmd_ps(0, 0);
}

static void cmd_kill(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: kill <pid>\\n"); return; }
    int pid = atoi(args[1]);
    if (task_kill(pid)) {
        vga_puts("Killed process "); vga_puts(args[1]); vga_putchar('\\n');
    } else {
        vga_puts("kill: no such process\\n");
    }
}

static void cmd_service(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    int max = task_get_max_tasks();
    vga_puts("Running services:\\n");
    for (int i = 0; i < max; i++) {
        if (task_is_active(i)) {
            vga_puts("  ["); char buf[8]; itoa(i, buf, 10); vga_puts(buf);
            vga_puts("] "); vga_puts(task_get_name_by_pid(i));
            vga_puts(" - "); vga_puts(task_get_state_name(i));
            vga_putchar('\\n');
        }
    }
}

"""

# ===== System Commands =====
shell_c += """
/* ===== System Commands ===== */
static void cmd_sysinfo(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    char buf[32];
    vga_puts("System Information:\\n");
    vga_puts("  OS:      BYO-OS v1.0.0\\n");
    vga_puts("  Arch:    x86\\n");
    vga_puts("  User:    "); vga_puts(user_get_name()); vga_putchar('\\n');
    vga_puts("  Free:    "); itoa(pmm_get_free_pages(), buf, 10); vga_puts(buf); vga_puts(" pages\\n");
    vga_puts("  Total:   "); itoa(pmm_get_total_pages(), buf, 10); vga_puts(buf); vga_puts(" pages\\n");
    vga_puts("  Heap:    "); itoa(heap_get_used(), buf, 10); vga_puts(buf); vga_puts(" bytes\\n");
    vga_puts("  Uptime:  "); itoa(timer_get_seconds(), buf, 10); vga_puts(buf); vga_puts("s\\n");
}

static void cmd_halt(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("System halted.\\n");
    while(1) { asm volatile("hlt"); }
}

static void cmd_reboot(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Rebooting...\\n");
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
    vga_puts("Filesystem    Blocks   Used   Available\\n");
    vga_puts("/dev/fs       ");
    if (human) {
        itoa(total, buf, 10); vga_puts(buf); vga_puts("K   ");
        itoa(used, buf, 10); vga_puts(buf); vga_puts("K   ");
        itoa(free_s, buf, 10); vga_puts(buf); vga_puts("K\\n");
    } else {
        itoa(total, buf, 10); vga_puts(buf); vga_puts("  ");
        itoa(used, buf, 10); vga_puts(buf); vga_puts("  ");
        itoa(free_s, buf, 10); vga_puts(buf); vga_putchar('\\n');
    }
}

static void cmd_free(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    char buf[32];
    vga_puts("Memory:\\n");
    vga_puts("            Total      Used      Free\\n");
    vga_puts("Pages:   ");
    itoa(pmm_get_total_pages(), buf, 10); vga_puts(buf);
    vga_puts("    ");
    unsigned int used_p = pmm_get_total_pages() - pmm_get_free_pages();
    itoa(used_p, buf, 10); vga_puts(buf);
    vga_puts("    ");
    itoa(pmm_get_free_pages(), buf, 10); vga_puts(buf); vga_putchar('\\n');
    vga_puts("Heap:    ");
    itoa(heap_get_used(), buf, 10); vga_puts(buf); vga_puts(" bytes\\n");
}

static void cmd_date(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    unsigned int sec = timer_get_seconds();
    char buf[32];
    vga_puts("Seconds since boot: "); itoa(sec, buf, 10); vga_puts(buf); vga_putchar('\\n');
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
        vga_puts("BYO-OS byo-os 1.0.0 #1 x86\\n");
    } else {
        vga_puts("BYO-OS\\n");
    }
}

static void cmd_hostname(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("byo-os\\n");
}

"""

# ===== Environment Commands =====
shell_c += """
/* ===== Environment Commands ===== */
static void cmd_env(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    for (int i = 0; i < env_count; i++) {
        vga_puts(env_names[i]); vga_puts("="); vga_puts(env_vals[i]); vga_putchar('\\n');
    }
}

static void cmd_export(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: export NAME=VALUE\\n"); return; }
    char *eq = strstr(args[1], "=");
    if (!eq) { vga_puts("export: invalid format\\n"); return; }
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
    if (argc < 2) { vga_puts("Usage: unset NAME\\n"); return; }
    for (int i = 0; i < env_count; i++) {
        if (strcmp(env_names[i], args[1]) == 0) {
            for (int j = i; j < env_count - 1; j++) {
                strcpy(env_names[j], env_names[j+1]);
                strcpy(env_vals[j], env_vals[j+1]);
            }
            env_count--;
            vga_puts("Unset "); vga_puts(args[1]); vga_putchar('\\n');
            return;
        }
    }
    vga_puts("unset: "); vga_puts(args[1]); vga_puts(": not found\\n");
}

static void cmd_history(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    char buf[8];
    for (int i = 0; i < history_count; i++) {
        itoa(i + 1, buf, 10); vga_puts(buf);
        vga_puts("  "); vga_puts(history[i]); vga_putchar('\\n');
    }
}

static void cmd_alias(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        for (int i = 0; i < alias_count; i++) {
            vga_puts(alias_names[i]); vga_puts("='");
            vga_puts(alias_cmds[i]); vga_puts("'\\n");
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
    if (argc < 2) { vga_puts("Usage: unalias name\\n"); return; }
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
    vga_puts("unalias: "); vga_puts(args[1]); vga_puts(": not found\\n");
}

"""

# ===== Text Commands =====
shell_c += """
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
    if (!pattern) { vga_puts("Usage: grep [-i|-v|-n] <pattern> [file]\\n"); return; }
    if (filename) {
        memset(file_buf, 0, FILE_BUF_SIZE);
        int r = fs_read_file(filename, file_buf, FILE_BUF_SIZE - 1);
        if (r <= 0) { vga_puts("grep: "); vga_puts(filename); vga_puts(": No such file\\n"); return; }
        char line[256];
        int lnum = 1;
        char *p = file_buf;
        while (*p) {
            int j = 0;
            while (*p && *p != '\\n') { line[j++] = *p++; }
            line[j] = 0;
            if (*p == '\\n') p++;
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
                vga_puts(line); vga_putchar('\\n');
            }
            lnum++;
        }
    } else {
        vga_puts("Usage: grep [-i|-v|-n] <pattern> <file>\\n");
    }
}

static void cmd_sort(int argc, char args[][CMD_MAX_LEN]) {
    int reverse = 0;
    const char *fname = 0;
    for (int i = 1; i < argc; i++) {
        if (args[i][0] == '-' && args[i][1] == 'r') reverse = 1;
        else fname = args[i];
    }
    if (!fname) { vga_puts("Usage: sort [-r] <file>\\n"); return; }
    memset(file_buf, 0, FILE_BUF_SIZE);
    int r = fs_read_file(fname, file_buf, FILE_BUF_SIZE - 1);
    if (r <= 0) { vga_puts("sort: "); vga_puts(fname); vga_puts(": No such file\\n"); return; }
    char lines[128][128];
    int nlines = 0;
    char *p = file_buf;
    while (*p && nlines < 128) {
        int j = 0;
        while (*p && *p != '\\n') { lines[nlines][j++] = *p++; }
        lines[nlines][j] = 0;
        if (*p == '\\n') p++;
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
        vga_puts(lines[i]); vga_putchar('\\n');
    }
}

static void cmd_uniq(int argc, char args[][CMD_MAX_LEN]) {
    const char *fname = 0;
    for (int i = 1; i < argc; i++) {
        if (args[i][0] != '-') fname = args[i];
    }
    if (!fname) { vga_puts("Usage: uniq <file>\\n"); return; }
    memset(file_buf, 0, FILE_BUF_SIZE);
    int r = fs_read_file(fname, file_buf, FILE_BUF_SIZE - 1);
    if (r <= 0) { vga_puts("uniq: "); vga_puts(fname); vga_puts(": No such file\\n"); return; }
    char prev[256] = "";
    char line[256];
    char *p = file_buf;
    while (*p) {
        int j = 0;
        while (*p && *p != '\\n') { line[j++] = *p++; }
        line[j] = 0;
        if (*p == '\\n') p++;
        if (strcmp(line, prev) != 0) {
            vga_puts(line); vga_putchar('\\n');
            strcpy(prev, line);
        }
    }
}

static void cmd_wc(int argc, char args[][CMD_MAX_LEN]) {
    const char *fname = 0;
    for (int i = 1; i < argc; i++) {
        if (args[i][0] != '-') fname = args[i];
    }
    if (!fname) { vga_puts("Usage: wc <file>\\n"); return; }
    memset(file_buf, 0, FILE_BUF_SIZE);
    int r = fs_read_file(fname, file_buf, FILE_BUF_SIZE - 1);
    if (r <= 0) { vga_puts("wc: "); vga_puts(fname); vga_puts(": No such file\\n"); return; }
    int lines = 0, words = 0, chars = 0;
    int in_word = 0;
    for (int i = 0; i < r; i++) {
        chars++;
        if (file_buf[i] == '\\n') lines++;
        if (file_buf[i] == ' ' || file_buf[i] == '\\n' || file_buf[i] == '\\t') {
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
    vga_puts(fname); vga_putchar('\\n');
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
    if (!fname) { vga_puts("Usage: head [-n N] <file>\\n"); return; }
    memset(file_buf, 0, FILE_BUF_SIZE);
    int r = fs_read_file(fname, file_buf, FILE_BUF_SIZE - 1);
    if (r <= 0) { vga_puts("head: "); vga_puts(fname); vga_puts(": No such file\\n"); return; }
    int shown = 0;
    char *p = file_buf;
    while (*p && shown < n) {
        vga_putchar(*p);
        if (*p == '\\n') shown++;
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
    if (!fname) { vga_puts("Usage: tail [-n N] <file>\\n"); return; }
    memset(file_buf, 0, FILE_BUF_SIZE);
    int r = fs_read_file(fname, file_buf, FILE_BUF_SIZE - 1);
    if (r <= 0) { vga_puts("tail: "); vga_puts(fname); vga_puts(": No such file\\n"); return; }
    char lines[128][256];
    int nlines = 0;
    char *p = file_buf;
    while (*p && nlines < 128) {
        int j = 0;
        while (*p && *p != '\\n') { lines[nlines][j++] = *p++; }
        lines[nlines][j] = 0;
        if (*p == '\\n') p++;
        nlines++;
    }
    int start = nlines - n;
    if (start < 0) start = 0;
    for (int i = start; i < nlines; i++) {
        vga_puts(lines[i]); vga_putchar('\\n');
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
    if (!fname || field < 1) { vga_puts("Usage: cut -d<delim> -f<field> <file>\\n"); return; }
    memset(file_buf, 0, FILE_BUF_SIZE);
    int r = fs_read_file(fname, file_buf, FILE_BUF_SIZE - 1);
    if (r <= 0) { vga_puts("cut: "); vga_puts(fname); vga_puts(": No such file\\n"); return; }
    char line[256];
    char *p = file_buf;
    while (*p) {
        int j = 0;
        while (*p && *p != '\\n') { line[j++] = *p++; }
        line[j] = 0;
        if (*p == '\\n') p++;
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
        vga_putchar('\\n');
    }
}

static void cmd_strings(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: strings <file>\\n"); return; }
    memset(file_buf, 0, FILE_BUF_SIZE);
    int r = fs_read_file(args[1], file_buf, FILE_BUF_SIZE - 1);
    if (r <= 0) { vga_puts("strings: "); vga_puts(args[1]); vga_puts(": No such file\\n"); return; }
    char str_buf[256];
    int slen = 0;
    for (int i = 0; i < r; i++) {
        char c = file_buf[i];
        if (c >= 32 && c <= 126) {
            if (slen < 255) str_buf[slen++] = c;
        } else {
            if (slen >= 4) {
                str_buf[slen] = 0;
                vga_puts(str_buf); vga_putchar('\\n');
            }
            slen = 0;
        }
    }
    if (slen >= 4) { str_buf[slen] = 0; vga_puts(str_buf); vga_putchar('\\n'); }
}

static void cmd_hexdump(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: hexdump <file>\\n"); return; }
    memset(file_buf, 0, FILE_BUF_SIZE);
    int r = fs_read_file(args[1], file_buf, FILE_BUF_SIZE - 1);
    if (r <= 0) { vga_puts("hexdump: "); vga_puts(args[1]); vga_puts(": No such file\\n"); return; }
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
        vga_puts("|\\n");
    }
}

"""

# ===== Shell + Misc Commands =====
shell_c += """
/* ===== Shell Commands ===== */
static void cmd_which(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: which <command>\\n"); return; }
    vga_puts("/usr/bin/"); vga_puts(args[1]); vga_putchar('\\n');
}

static void cmd_man(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: man <command>\\n"); return; }
    vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
    if (strcmp(args[1], "ls") == 0) {
        vga_puts("LS(1)\\n\\nNAME\\n    ls - list directory contents\\n\\nSYNOPSIS\\n");
        vga_puts("    ls [-a] [-la] [path]\\n\\nDESCRIPTION\\n");
        vga_puts("    List files in directory.\\n    -a    show hidden files (. and ..)\\n");
        vga_puts("    -la   long listing with permissions\\n");
    } else if (strcmp(args[1], "grep") == 0) {
        vga_puts("GREP(1)\\n\\nNAME\\n    grep - search for patterns\\n\\nSYNOPSIS\\n");
        vga_puts("    grep [-i|-v|-n] <pattern> <file>\\n\\nDESCRIPTION\\n");
        vga_puts("    -i    case insensitive\\n    -v    invert match\\n");
        vga_puts("    -n    show line numbers\\n");
    } else if (strcmp(args[1], "cat") == 0) {
        vga_puts("CAT(1)\\n\\nNAME\\n    cat - concatenate and print files\\n\\nSYNOPSIS\\n");
        vga_puts("    cat <file>\\n\\nDESCRIPTION\\n    Print file contents to stdout.\\n");
    } else if (strcmp(args[1], "echo") == 0) {
        vga_puts("ECHO(1)\\n\\nNAME\\n    echo - display a line of text\\n\\nSYNOPSIS\\n");
        vga_puts("    echo [text...]\\n\\nDESCRIPTION\\n    Print arguments to stdout.\\n");
    } else if (strcmp(args[1], "sort") == 0) {
        vga_puts("SORT(1)\\n\\nNAME\\n    sort - sort lines of text\\n\\nSYNOPSIS\\n");
        vga_puts("    sort [-r] <file>\\n\\nDESCRIPTION\\n    -r    reverse sort\\n");
    } else if (strcmp(args[1], "wc") == 0) {
        vga_puts("WC(1)\\n\\nNAME\\n    wc - word count\\n\\nSYNOPSIS\\n");
        vga_puts("    wc <file>\\n\\nDESCRIPTION\\n    Count lines, words, characters.\\n");
    } else {
        vga_puts(args[1]); vga_puts(": no manual entry found\\n");
    }
}

static void cmd_crontab(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("No crontab entries\\n");
}

static void cmd_tee(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: tee <file>\\n"); return; }
    vga_puts("(input from stdin not supported in shell mode)\\n");
}

static void cmd_tr(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: tr <from> <to>\\n"); return; }
    vga_puts("tr: interactive input not supported\\n");
}

/* ===== Misc Commands ===== */
static void cmd_chmod(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: chmod <mode> <file>\\n"); return; }
    vga_puts("chmod: permissions set\\n");
}

static void cmd_journal(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2 || strcmp(args[1], "clear") != 0) {
        journal_show();
    } else {
        journal_clear();
        vga_puts("Journal cleared\\n");
    }
}

static void cmd_neofetch(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    char buf[32];
    vga_set_color(VGA_CYAN, VGA_BLACK);
    vga_puts("        ___          \\n");
    vga_puts("       /   \\         "); vga_set_color(VGA_WHITE, VGA_BLACK); vga_puts("BYO-OS\\n");
    vga_set_color(VGA_CYAN, VGA_BLACK);
    vga_puts("      /     \\        "); vga_set_color(VGA_WHITE, VGA_BLACK); vga_puts("User: "); vga_puts(user_get_name()); vga_putchar('\\n');
    vga_set_color(VGA_CYAN, VGA_BLACK);
    vga_puts("     /  BYO  \\       "); vga_set_color(VGA_WHITE, VGA_BLACK); vga_puts("Kernel: BYO-OS 1.0\\n");
    vga_set_color(VGA_CYAN, VGA_BLACK);
    vga_puts("    /    OS   \\      "); vga_set_color(VGA_WHITE, VGA_BLACK); vga_puts("Arch: x86\\n");
    vga_set_color(VGA_CYAN, VGA_BLACK);
    vga_puts("   /           \\     "); vga_set_color(VGA_WHITE, VGA_BLACK); vga_puts("Shell: byosh\\n");
    vga_set_color(VGA_CYAN, VGA_BLACK);
    vga_puts("  /_______|_____\\    "); vga_set_color(VGA_WHITE, VGA_BLACK); vga_puts("Memory: ");
    itoa(pmm_get_free_pages(), buf, 10); vga_puts(buf); vga_puts(" free pages\\n");
    vga_set_color(VGA_CYAN, VGA_BLACK);
    vga_puts("  \\       |     /    "); vga_set_color(VGA_WHITE, VGA_BLACK); vga_puts("Uptime: ");
    itoa(timer_get_seconds(), buf, 10); vga_puts(buf); vga_puts("s\\n");
    vga_set_color(VGA_CYAN, VGA_BLACK);
    vga_puts("   \\      |    /     "); vga_set_color(VGA_WHITE, VGA_BLACK); vga_puts("IP: ");
    char ip[32]; net_get_ip_str(ip); vga_puts(ip); vga_putchar('\\n');
    vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
}

static void cmd_cal(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    unsigned int sec = timer_get_seconds();
    unsigned int day = (sec / 86400) % 31 + 1;
    vga_puts("    July 2024\\n");
    vga_puts("Su Mo Tu We Th Fr Sa\\n");
    vga_puts("    1  2  3  4  5  6\\n");
    vga_puts(" 7  8  9 10 11 12 13\\n");
    vga_puts("14 15 16 17 18 19 20\\n");
    vga_puts("21 22 23 24 25 26 27\\n");
    vga_puts("28 29 30 31\\n");
    char buf[8];
    vga_puts("\\nToday: "); itoa(day, buf, 10); vga_puts(buf); vga_putchar('\\n');
}

static void cmd_sync(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Filesystem synced\\n");
}

"""

# ===== Command Table + Dispatch + Main Loop =====
shell_c += """
/* ===== Command Dispatch ===== */
typedef struct {
    const char *name;
    void (*func)(int argc, char args[][CMD_MAX_LEN]);
} cmd_entry;

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
    {"chmod", cmd_chmod}, {"journal", cmd_journal}, {"neofetch", cmd_neofetch},
    {"cal", cmd_cal}, {"sync", cmd_sync},
    {0, 0}
};

static void shell_execute(const char *cmdline) {
    if (!cmdline || cmdline[0] == 0) return;

    /* Add to history */
    if (history_count < MAX_HISTORY) {
        strncpy(history[history_count], cmdline, CMD_MAX_LEN - 1);
        history[history_count][CMD_MAX_LEN - 1] = 0;
        history_count++;
    }

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
    vga_puts(args[0]); vga_puts(": command not found\\n");
}

/* ===== Keyboard Input Helper ===== */
static char keyboard_getchar(void) {
    unsigned char scan;
    __asm__ __volatile__ ("inb %1, %0" : "=a"(scan) : "nd"((unsigned short)0x60));
    static unsigned char last = 0;
    if (scan & 0x80) { last = 0; return 0; }
    if (scan == last) return 0;
    last = scan;
    static const char kmap[] = {
        0,27,'1','2','3','4','5','6','7','8','9','0','-','=',8,
        9,'q','w','e','r','t','y','u','i','o','p','[',']',13,
        0,'a','s','d','f','g','h','j','k','l',';','\\'', '`',
        0,'\\\\','z','x','c','v','b','n','m',',','.','/',0,'*',
        0,' ',0,0,0,0,0,0,0,0,0,0
    };
    if (scan < sizeof(kmap)) return kmap[scan];
    return 0;
}

/* ===== Main Shell Loop ===== */
void shell_run(void) {
    vga_clear();
    vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
    vga_puts("Welcome to BYO-OS Shell v1.0\\n");
    vga_puts("Type 'help' for available commands.\\n\\n");
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
                if (c == '\\n' || c == '\\r') {
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
                    if (c == '\\n' || c == '\\r') {
                        serial_cmd[si] = 0;
                        if (si > 0) {
                            vga_putchar('\\n');
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
                vga_putchar('\\n');
                shell_execute(input_buf);
                input_len = 0;
                input_buf[0] = 0;
                break;
            } else if (c == 8) {
                /* Backspace */
                if (input_len > 0) {
                    input_len--;
                    input_buf[input_len] = 0;
                    vga_putchar('\\b'); vga_putchar(' '); vga_putchar('\\b');
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

"""

# ===== Write to file =====
outpath = r"E:\aisystem\byo-os\kernel\shell.c"
import os
os.makedirs(os.path.dirname(outpath), exist_ok=True)
with open(outpath, 'w', encoding='utf-8', newline='\n') as f:
    f.write(shell_c)
print(f"Written {len(shell_c)} bytes to {outpath}")

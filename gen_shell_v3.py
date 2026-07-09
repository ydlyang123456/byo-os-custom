# gen_shell_v3.py - Generate shell.c for BYO-OS v3.0
import os

path = 'E:/aisystem/byo-os/kernel/shell.c'

parts = []

# Part 1: Header
parts.append(r'''/* BYO-OS Shell v3.0 */
#include <kernel.h>

#define CMD_BUF_SIZE 256
static char cmd_buffer[CMD_BUF_SIZE];
static int cmd_pos = 0;
static int serial_processed = 0;

#define HISTORY_SIZE 30
static char cmd_history[HISTORY_SIZE][CMD_BUF_SIZE];
static int hist_count = 0;
static int hist_next = 0;

#define ENV_MAX 32
static char env_vars[ENV_MAX][2][64];
static int env_count = 0;

#define ALIAS_MAX 16
static char alias_names[ALIAS_MAX][32];
static char alias_cmds[ALIAS_MAX][128];
static int alias_count = 0;

static void add_history(const char* cmd) {
    if (strlen(cmd) == 0) return;
    strncpy(cmd_history[hist_next], cmd, CMD_BUF_SIZE - 1);
    cmd_history[hist_next][CMD_BUF_SIZE - 1] = 0;
    hist_next = (hist_next + 1) % HISTORY_SIZE;
    if (hist_count < HISTORY_SIZE) hist_count++;
}

static const char* resolve_alias(const char* cmd) {
    for (int i = 0; i < alias_count; i++) {
        if (strcmp(cmd, alias_names[i]) == 0) return alias_cmds[i];
    }
    return cmd;
}

static int startswith(const char* s, const char* prefix) {
    return strncmp(s, prefix, strlen(prefix)) == 0;
}

static void print_prompt(void) {
    vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
    vga_puts(user_get_name());
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("@byo-os");
    vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
    vga_puts("> ");
}

static void cmd_help(void) {
    vga_puts("Commands:\n");
    vga_puts("  help              Show this help\n");
    vga_puts("  clear             Clear screen\n");
    vga_puts("  echo <text>       Print text\n");
    vga_puts("  uptime            System uptime\n");
    vga_puts("  mem               Memory info\n");
    vga_puts("  ps / ps aux       Process list\n");
    vga_puts("  top               Process monitor\n");
    vga_puts("  ls / ls -a -la    List files\n");
    vga_puts("  cat <file>        Show file contents\n");
    vga_puts("  touch <file>      Create empty file\n");
    vga_puts("  write <file> <t>  Write text to file\n");
    vga_puts("  rm <file>         Delete file\n");
    vga_puts("  mkdir [-p] <dir>  Create directory\n");
    vga_puts("  cp <src> <dst>    Copy file\n");
    vga_puts("  mv <src> <dst>    Move/rename file\n");
    vga_puts("  color <color>     Set text color\n");
    vga_puts("  net               Network info\n");
    vga_puts("  ping <host>       Ping host\n");
    vga_puts("  curl <url>        HTTP fetch\n");
    vga_puts("  whoami            Current user\n");
    vga_puts("  login <u> <p>     Login as user\n");
    vga_puts("  logout            Logout\n");
    vga_puts("  users             List users\n");
    vga_puts("  panel             System panel\n");
    vga_puts("  task create <n>   Create task\n");
    vga_puts("  task list         List tasks\n");
    vga_puts("  sysinfo           System info\n");
    vga_puts("  halt              Halt system\n");
    vga_puts("  reboot            Reboot system\n");
    vga_puts("  df / df -h        Filesystem usage\n");
    vga_puts("  free              Memory usage\n");
    vga_puts("  date              Current time\n");
    vga_puts("  uname -a          System info\n");
    vga_puts("  hostname          System hostname\n");
    vga_puts("  id                Current user id\n");
    vga_puts("  groups            User groups\n");
    vga_puts("  env               Environment vars\n");
    vga_puts("  export K=V        Set env var\n");
    vga_puts("  unset K           Unset env var\n");
    vga_puts("  history           Command history\n");
    vga_puts("  alias N=CMD       Create alias\n");
    vga_puts("  unalias N         Remove alias\n");
    vga_puts("  which <cmd>       Find command\n");
    vga_puts("  grep <pat> <file> Search file\n");
    vga_puts("  sort <file>       Sort lines\n");
    vga_puts("  uniq <file>       Unique lines\n");
    vga_puts("  wc <file>         Count lines/words\n");
    vga_puts("  head [-n N] <f>   First lines\n");
    vga_puts("  tail [-n N] <f>   Last lines\n");
    vga_puts("  cut -dD -fN <f>   Cut columns\n");
    vga_puts("  strings <file>    Printable strings\n");
    vga_puts("  hexdump <file>    Hex dump\n");
    vga_puts("  stat <file>       File stats\n");
    vga_puts("  find <pattern>    Find files\n");
    vga_puts("  du                Directory sizes\n");
    vga_puts("  chmod <m> <f>     Change permissions\n");
    vga_puts("  kill <pid>        Kill task\n");
    vga_puts("  service           Show services\n");
    vga_puts("  journal           System log\n");
    vga_puts("  journal clear     Clear log\n");
    vga_puts("  crontab -l        Scheduled tasks\n");
    vga_puts("  neofetch          System info art\n");
    vga_puts("  cal               Calendar\n");
    vga_puts("  sync              Flush buffers\n");
    vga_puts("  man <cmd>         Manual page\n");
    vga_puts("  version           OS version\n");
    vga_puts("  about             About BYO-OS\n");
}
''')

print('Part 1 OK, writing...')
with open(path, 'w', encoding='utf-8', newline='\n') as f:
    f.write(parts[0])
print('Written:', len(parts[0]), 'bytes')

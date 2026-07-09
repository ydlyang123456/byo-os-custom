/* BYO-OS Shell v3.0 */
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
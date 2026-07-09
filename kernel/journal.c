/* BYO-OS - System Journal (Ring Buffer Log) */
#include <kernel.h>

#define JOURNAL_MAX 100

typedef struct {
    int level;
    char msg[128];
    uint32_t time;
} journal_entry_t;

static journal_entry_t journal[JOURNAL_MAX];
static int journal_count = 0;
static int journal_pos = 0;

void journal_init(void) {
    journal_count = 0;
    journal_pos = 0;
    journal_append(0, "Journal initialized");
}

void journal_append(int level, const char* msg) {
    if (journal_count >= JOURNAL_MAX) {
        journal_pos = (journal_pos + 1) % JOURNAL_MAX;
    } else {
        journal_count++;
    }
    int idx = (journal_pos + journal_count - 1) % JOURNAL_MAX;
    journal[idx].level = level;
    strncpy(journal[idx].msg, msg, 127);
    journal[idx].msg[127] = '\0';
    journal[idx].time = timer_get_seconds();
}

void journal_show(void) {
    if (journal_count == 0) {
        vga_puts("  (empty)\n");
        return;
    }
    vga_puts("  TIME   LVL  MESSAGE\n");
    vga_puts("  -----  ---  -------\n");
    for (int i = 0; i < journal_count; i++) {
        int idx = (journal_pos + i) % JOURNAL_MAX;
        vga_put_dec(journal[idx].time);
        vga_puts("s  ");
        switch (journal[idx].level) {
            case 0: vga_puts("INF "); break;
            case 1: vga_puts("WRN "); break;
            case 2: vga_puts("ERR "); break;
            default: vga_puts("??? "); break;
        }
        vga_puts(journal[idx].msg);
        vga_puts("\n");
    }
}

void journal_clear(void) {
    journal_count = 0;
    journal_pos = 0;
}
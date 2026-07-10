/* BYO-OS Journal - x86_64 */
#include <kernel.h>
typedef struct { int level; char msg[128]; } journal_entry_t;
static journal_entry_t entries[256];
static int journal_count = 0;
void journal_init(void) { journal_count = 0; }
void journal_append(int level, const char* msg) {
    if (journal_count >= 256) return;
    entries[journal_count].level = level;
    int i = 0; while (msg[i] && i < 127) { entries[journal_count].msg[i] = msg[i]; i++; }
    entries[journal_count].msg[i] = 0;
    journal_count++;
}
void journal_show(void) {
    for (int i = 0; i < journal_count; i++) {
        vga_printf("[%d] %s\n", entries[i].level, entries[i].msg);
    }
}
void journal_clear(void) { journal_count = 0; }
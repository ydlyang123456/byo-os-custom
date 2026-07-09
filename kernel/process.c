/* BYO-OS - Minimal Process Management */
#include <kernel.h>

#define MAX_PROCESSES 16
#define PROCESS_NAME_LEN 32

typedef struct {
    int pid;
    char name[PROCESS_NAME_LEN];
    int active;
    void (*entry)(void);
} process_t;

static process_t processes[MAX_PROCESSES];
static int next_pid = 1;

void process_init(void) {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        processes[i].active = 0;
    }
    processes[0].pid = 0;
    strcpy(processes[0].name, "kernel");
    processes[0].active = 1;
    processes[0].entry = NULL;
    next_pid = 1;
}

int process_create(const char* name, void (*entry)(void)) {
    for (int i = 1; i < MAX_PROCESSES; i++) {
        if (!processes[i].active) {
            processes[i].pid = next_pid++;
            strncpy(processes[i].name, name, PROCESS_NAME_LEN - 1);
            processes[i].name[PROCESS_NAME_LEN - 1] = '\0';
            processes[i].active = 1;
            processes[i].entry = entry;
            return processes[i].pid;
        }
    }
    return -1;
}

void process_exit(void) {
    /* In a real OS, this would mark current process as inactive */
}
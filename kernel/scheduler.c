/* BYO-OS Scheduler - x86_64 */
#include <kernel.h>
typedef struct { int pid; char name[32]; int active; uint64_t stack; } task_t;
static task_t tasks[64]; static int task_count = 0; static int current = 0;
void scheduler_init(void) { task_count = 0; }
int task_create(const char* name, void (*entry)(void)) {
    if (task_count >= 64) return -1;
    int pid = task_count++;
    tasks[pid].pid = pid;
    int i = 0; while (name[i] && i < 31) { tasks[pid].name[i] = name[i]; i++; }
    tasks[pid].name[i] = 0;
    tasks[pid].active = 1;
    tasks[pid].stack = (uint64_t)kmalloc(4096) + 4096;
    return pid;
}
void task_exit(void) { if (current < task_count) tasks[current].active = 0; }
void task_sleep(uint32_t ms) { timer_sleep(ms); }
int task_get_pid(void) { return current < task_count ? tasks[current].pid : 0; }
const char* task_get_name(void) { return current < task_count ? tasks[current].name : "idle"; }
int task_get_count(void) { return task_count; }
void scheduler_tick(void) { /* round-robin stub */ }
int task_get_max_tasks(void) { return 64; }
const char* task_get_state_name(int pid) { return (pid >= 0 && pid < task_count && tasks[pid].active) ? "running" : "stopped"; }
const char* task_get_name_by_pid(int pid) { return (pid >= 0 && pid < task_count) ? tasks[pid].name : "?"; }
int task_is_active(int pid) { return (pid >= 0 && pid < task_count) ? tasks[pid].active : 0; }
int task_kill(int pid) { if (pid >= 0 && pid < task_count) { tasks[pid].active = 0; return 0; } return -1; }
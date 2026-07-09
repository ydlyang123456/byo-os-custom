/* BYO-OS - Multi-Task Scheduler */
#include <kernel.h>

#define MAX_TASKS 16
#define TASK_STACK_SIZE 4096
#define TASK_QUANTUM 10

typedef enum { TASK_READY, TASK_RUNNING, TASK_BLOCKED, TASK_DEAD } task_state_t;

typedef struct {
    uint32_t eax, ebx, ecx, edx;
    uint32_t esi, edi, ebp, esp;
    uint32_t eip, eflags;
    uint32_t cs, ss, ds, es, fs, gs;
} __attribute__((packed)) cpu_state_t;

typedef struct {
    int pid;
    char name[32];
    task_state_t state;
    cpu_state_t cpu;
    uint32_t stack[TASK_STACK_SIZE / 4];
    uint32_t quantum;
    uint32_t wake_time;
} task_t;

static task_t tasks[MAX_TASKS];
static int current_task = 0;
static int task_count = 0;
static int scheduler_enabled = 0;

extern void context_switch(cpu_state_t* prev, cpu_state_t* next);

void scheduler_init(void) {
    for (int i = 0; i < MAX_TASKS; i++) {
        tasks[i].state = TASK_DEAD;
        tasks[i].pid = -1;
    }

    tasks[0].pid = 0;
    strcpy(tasks[0].name, "kernel");
    tasks[0].state = TASK_RUNNING;
    tasks[0].quantum = TASK_QUANTUM;
    task_count = 1;
    current_task = 0;

    scheduler_enabled = 1;
    serial_puts("[SCHED] Scheduler initialized\n");
}

int task_create(const char* name, void (*entry)(void)) {
    if (task_count >= MAX_TASKS) return -1;

    int slot = -1;
    for (int i = 0; i < MAX_TASKS; i++) {
        if (tasks[i].state == TASK_DEAD) { slot = i; break; }
    }
    if (slot < 0) return -1;

    tasks[slot].pid = slot;
    strncpy(tasks[slot].name, name, 31);
    tasks[slot].name[31] = '\0';
    tasks[slot].state = TASK_READY;
    tasks[slot].quantum = TASK_QUANTUM;

    uint32_t* stack_top = &tasks[slot].stack[TASK_STACK_SIZE / 4];
    stack_top--;
    *stack_top = 0x202;
    stack_top--;
    *stack_top = 0x08;
    stack_top--;
    *stack_top = (uint32_t)entry;
    stack_top--;
    *stack_top = 0;
    stack_top--;
    *stack_top = 0;
    stack_top--;
    *stack_top = 0;
    stack_top--;
    *stack_top = 0;
    stack_top--;
    *stack_top = 0;
    stack_top--;
    *stack_top = 0x10;
    stack_top--;
    *stack_top = (uint32_t)stack_top + 4;
    stack_top--;
    *stack_top = 0x10;
    stack_top--;
    *stack_top = 0x10;
    stack_top--;
    *stack_top = 0x10;
    stack_top--;
    *stack_top = 0x10;
    stack_top--;
    *stack_top = 0x10;

    tasks[slot].cpu.esp = (uint32_t)stack_top;
    tasks[slot].cpu.eip = (uint32_t)entry;
    tasks[slot].cpu.eflags = 0x202;
    tasks[slot].cpu.cs = 0x08;
    tasks[slot].cpu.ds = 0x10;
    tasks[slot].cpu.es = 0x10;
    tasks[slot].cpu.ss = 0x10;

    task_count++;
    serial_puts("[SCHED] Task created: ");
    serial_puts(name);
    serial_puts("\n");
    return tasks[slot].pid;
}

void task_exit(void) {
    tasks[current_task].state = TASK_DEAD;
    task_count--;
    /* Force schedule next task */
    asm volatile("int $0x20");
}

void task_sleep(uint32_t ms) {
    tasks[current_task].wake_time = timer_get_ticks() + (ms * 100 / 1000);
    tasks[current_task].state = TASK_BLOCKED;
    asm volatile("int $0x20");
}

int task_get_pid(void) {
    return current_task;
}

const char* task_get_name(void) {
    return tasks[current_task].name;
}

int task_get_count(void) {
    return task_count;
}

int task_get_max_tasks(void) {
    return MAX_TASKS;
}

int task_is_active(int pid) {
    if (pid < 0 || pid >= MAX_TASKS) return 0;
    return tasks[pid].state != TASK_DEAD;
}

const char* task_get_state_name(int pid) {
    if (pid < 0 || pid >= MAX_TASKS || tasks[pid].state == TASK_DEAD) return "---";
    switch (tasks[pid].state) {
        case TASK_READY:   return "READY";
        case TASK_RUNNING: return "RUN";
        case TASK_BLOCKED: return "SLEEP";
        default:           return "???";
    }
}

const char* task_get_name_by_pid(int pid) {
    if (pid < 0 || pid >= MAX_TASKS) return "?";
    if (tasks[pid].state == TASK_DEAD) return "---";
    return tasks[pid].name;
}

int task_kill(int pid) {
    if (pid < 0 || pid >= MAX_TASKS) return -1;
    if (tasks[pid].state == TASK_DEAD) return -1;
    if (pid == 0) return -1;
    tasks[pid].state = TASK_DEAD;
    task_count--;
    return 0;
}

void scheduler_tick(void) {
    if (!scheduler_enabled) return;

    tasks[current_task].quantum--;
    if (tasks[current_task].quantum > 0) return;

    tasks[current_task].quantum = TASK_QUANTUM;

    int next = current_task;
    do {
        next = (next + 1) % MAX_TASKS;
        if (tasks[next].state == TASK_BLOCKED &&
            timer_get_ticks() >= tasks[next].wake_time) {
            tasks[next].state = TASK_READY;
        }
    } while (tasks[next].state != TASK_READY && next != current_task);

    if (next != current_task && tasks[next].state == TASK_READY) {
        tasks[current_task].state = TASK_READY;
        tasks[next].state = TASK_RUNNING;
        int prev = current_task;
        current_task = next;
        context_switch(&tasks[prev].cpu, &tasks[current_task].cpu);
    }
}
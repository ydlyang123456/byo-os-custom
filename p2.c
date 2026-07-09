static void cmd_help(void) {
    vga_puts("Commands:\n");
    vga_puts("  help clear echo uptime mem version about\n");
    vga_puts("  ls [ls -a -la] cat touch write rm mkdir cp mv\n");
    vga_puts("  find du stat net ping curl\n");
    vga_puts("  whoami login logout users id groups\n");
    vga_puts("  ps [ps aux] top kill service\n");
    vga_puts("  sysinfo halt reboot df free date uname hostname\n");
    vga_puts("  env export unset history alias unalias\n");
    vga_puts("  which man grep sort uniq wc head tail cut\n");
    vga_puts("  strings hexdump chmod journal crontab\n");
    vga_puts("  neofetch cal sync panel task\n");
}
static void cmd_clear(void) { vga_clear(); }
static void cmd_echo(const char* a) { vga_puts(a); vga_puts("\n"); }
static void cmd_version(void) { vga_puts("BYO-OS v0.3.0\n"); }
static void cmd_about(void) { vga_puts("BYO-OS: from-scratch x86 OS\n"); }
static void cmd_uptime(void) {
    vga_puts("Uptime: "); vga_put_dec(timer_get_seconds()); vga_puts("s\n");
}
static void cmd_mem(void) {
    vga_puts("RAM: "); vga_put_dec(pmm_get_free_pages()*4);
    vga_puts("MB free / "); vga_put_dec(pmm_get_total_pages()*4); vga_puts("MB\n");
    vga_puts("Heap: "); vga_put_dec(heap_get_used()); vga_puts("B\n");
}
static void cmd_ps(void) {
    vga_puts("PID  NAME              STATE\n");
    int max = task_get_max_tasks();
    for (int i = 0; i < max; i++) {
        const char* nm = task_get_name_by_pid(i);
        vga_puts("  "); vga_put_dec(i); vga_puts("  ");
        int nl = strlen(nm); for (int p=nl;p<18;p++) vga_puts(" ");
        vga_puts(nm); vga_puts("  "); vga_puts(task_get_state_name(i)); vga_puts("\n");
    }
}
static void cmd_ps_aux(void) {
    vga_puts("USER PID STATE COMMAND\n");
    int max = task_get_max_tasks();
    for (int i=0;i<max;i++) {
        if (!task_is_active(i)) continue;
        vga_puts("root "); vga_put_dec(i); vga_puts(" ");
        vga_puts(task_get_state_name(i)); vga_puts(" ");
        vga_puts(task_get_name_by_pid(i)); vga_puts("\n");
    }
}
static void cmd_top(void) { cmd_ps(); }
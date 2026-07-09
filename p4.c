static void cmd_whoami(void) { vga_puts(user_get_name()); vga_puts("\n"); }
static void cmd_login(const char* a) { char u[32],p[32];int i=0,ui=0;while(a[i]&&a[i]!=' '){u[ui++]=a[i];i++;}u[ui]=0;while(a[i]==' ')i++;int pi=0;while(a[i]&&pi<31){p[pi++]=a[i];i++;}p[pi]=0; if(user_login(u,p)==0){vga_puts("OK\n");}else{vga_puts("FAIL\n");}}
static void cmd_users(void) { char b[1024]; user_list_users(b,1024); vga_puts(b); }
static void cmd_id(void) { vga_puts("uid="); vga_put_dec(user_get_uid()); vga_puts("\n"); }
static void cmd_groups(void) { vga_puts(user_get_name()); vga_puts(" : root\n"); }
static void cmd_panel(void) {
    char ip[32]; net_get_ip_str(ip); char b[16];
    serial_puts("{\"os\":\"BYO-OS\",\"arch\":\"x86\",\"ip\":\""); serial_puts(ip);
    serial_puts("\",\"user\":\""); serial_puts(user_get_name()); serial_puts("\"}\n");
}
static void cmd_task(const char* a) { if(strncmp(a,"create ",7)==0){int id=task_create(a+7,0);vga_puts("PID ");vga_put_dec(id);vga_puts("\n");}else{cmd_ps();} }
static void cmd_sysinfo(void) { char ip[32];net_get_ip_str(ip);vga_puts("OS: BYO-OS 0.3\nIP: ");vga_puts(ip);vga_puts("\nMem: ");vga_put_dec(pmm_get_free_pages()*4);vga_puts("MB free\n"); }
static void cmd_halt(void) { vga_puts("Halted\n"); asm volatile("cli;hlt"); }
static void cmd_reboot(void) { outb(0x64,0xFE); }
static void cmd_df(void) {
    uint32_t t=0,u=0,f=0; fs_get_stats(&t,&u,&f);
    vga_puts("Size Used Free\n"); vga_put_dec(t/1024); vga_puts("K "); vga_put_dec(u/1024); vga_puts("K "); vga_put_dec(f/1024); vga_puts("K\n");
}
static void cmd_free(void) {
    uint32_t t=pmm_get_total_pages()*4096,a=pmm_get_free_pages()*4096;
    vga_puts("Total: "); vga_put_dec(t/1024); vga_puts("KB Used: "); vga_put_dec((t-a)/1024); vga_puts("KB Free: "); vga_put_dec(a/1024); vga_puts("KB\n");
}
static void cmd_date(void) { uint32_t s=timer_get_seconds(),h=s/3600,m=(s%3600)/60,ss=s%60; vga_puts("Day "); vga_put_dec(s/86400); vga_puts(" "); if(h<10)vga_puts("0");vga_put_dec(h);vga_puts(":"); if(m<10)vga_puts("0");vga_put_dec(m);vga_puts(":"); if(ss<10)vga_puts("0");vga_put_dec(ss);vga_puts(" UTC\n"); }
static void cmd_uname(void) { vga_puts("BYO-OS 0.3.0 x86\n"); }
static void cmd_hostname(void) { vga_puts("byo-os\n"); }
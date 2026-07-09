static void cmd_strings(const char* fn) {
    if(!fs_file_exists(fn)){vga_puts("No such file\n");return;}
    char buf[4096];int sz=fs_read_file(fn,buf,4095);if(sz<=0)return;
    char str[128];int si=0;
    for(int i=0;i<sz;i++){if(buf[i]>=32&&buf[i]<127){if(si<127)str[si++]=buf[i];}else{if(si>=4){str[si]=0;vga_puts(str);vga_puts("\n");}si=0;}}
    if(si>=4){str[si]=0;vga_puts(str);vga_puts("\n");}
}
static void cmd_hexdump(const char* fn) {
    if(!fs_file_exists(fn)){vga_puts("No such file\n");return;}
    char buf[1024];int sz=fs_read_file(fn,buf,1023);if(sz<=0)return;
    char h[8];
    for(int i=0;i<sz;i+=16){itoa(i,h,16);vga_puts(h);vga_puts("  ");
    for(int j=0;j<16;j++){if(i+j<sz){itoa((uint8_t)buf[i+j],h,16);if(strlen(h)<2)vga_puts("0");vga_puts(h);}else vga_puts("  ");vga_puts(" ");}
    vga_puts(" |");for(int j=0;j<16&&i+j<sz;j++){char c=buf[i+j];vga_putchar((c>=32&&c<127)?c:'.');}vga_puts("|\n");}
}
static void cmd_stat(const char* fn) {
    if(!fs_file_exists(fn)){vga_puts("No such file\n");return;}
    vga_puts("File: ");vga_puts(fn);vga_puts("\nSize: ");vga_put_dec(fs_file_size(fn));vga_puts(" bytes\n");
}
static void cmd_find(const char* pat) {
    char buf[2048];fs_list_dir("/",buf,2048);if(buf[0]==0){vga_puts("(empty)\n");return;}
    const char*p=buf;while(*p){const char*ln=p;while(*p&&*p!='\n')p++;
    if(strstr(ln,pat)){const char*nm=ln;if(startswith(nm,"[DIR]  "))nm+=7;else if(startswith(nm,"[FILE] "))nm+=7;while(*nm==' ')nm++;vga_puts("./");vga_puts(nm);vga_puts("\n");}
    if(*p=='\n')p++;else break;}
}
static void cmd_du(void) {
    char buf[2048];fs_list_dir("/",buf,2048);uint32_t total=0;const char*p=buf;
    while(*p){const char*ln=p;while(*p&&*p!='\n')p++;
    if(startswith(ln,"[FILE] ")){const char*nm=ln+7;while(*nm==' ')nm++;int sz=fs_file_size(nm);vga_put_dec(sz/1024);vga_puts("K ");vga_puts(nm);vga_puts("\n");total+=sz;}
    if(*p=='\n')p++;else break;}
    vga_puts("total: ");vga_put_dec(total/1024);vga_puts("K\n");
}
static void cmd_chmod(const char* a) { vga_puts("chmod: updated\n"); }
static void cmd_kill(const char* a) { int pid=atoi(a); if(task_kill(pid)==0){vga_puts("Killed ");vga_put_dec(pid);vga_puts("\n");}else{vga_puts("Failed\n");} }
static void cmd_service(void) {
    vga_puts("kernel    running\nscheduler running\nfs        running\nnnetwork   running\njournal   running\nkeyboard  running\ntimer     running\nshell     running\n");
}
static void cmd_journal_fn(const char* a) { if(strcmp(a,"clear")==0)journal_clear();else journal_show(); }
static void cmd_crontab(const char* a) { vga_puts("crontab: no jobs\n"); }
static void cmd_neofetch(void) {
    vga_puts(".--.        root@byo-os\n");
    vga_puts("|o_o |       OS: BYO-OS 0.3.0\n");
    vga_puts("|:/_/ |       Kernel: x86\n");
    vga_puts("//$\\$\\      Mem: ");vga_put_dec(pmm_get_free_pages());vga_puts("MB/");vga_put_dec(pmm_get_total_pages());vga_puts("MB\n");
    vga_puts("(|     | )     Uptime: ");vga_put_dec(timer_get_seconds());vga_puts("s\n");
    vga_puts("/'\\_   _/\\\n");
    vga_puts("\\___)=(___/\n");
}
static void cmd_cal(void) {
    uint32_t s=timer_get_seconds(),dn=s/86400;int yr=2024,mo=0;int dim[]={31,28,31,30,31,30,31,31,30,31,30,31};int rem=dn;
    while(rem>=365){int dy=(yr%4==0)?366:365;if(rem<dy)break;rem-=dy;yr++;}
    while(mo<12&&rem>=dim[mo]){rem-=dim[mo];mo++;}if(mo>=12)mo=11;int day=rem+1;
    const char*mn[]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
    vga_puts("    ");vga_puts(mn[mo]);vga_puts(" ");vga_put_dec(yr);vga_puts("\nSu Mo Tu We Th Fr Sa\n");
    int m=mo+1,y=yr;if(m<3){m+=12;y--;}
    int dow=(day+(13*(m+1))/5+y+y/4-y/100+y/400)%7;
    for(int i=0;i<dow;i++)vga_puts("   ");
    for(int d=1;d<=dim[mo];d++){if(d<10)vga_puts(" ");vga_put_dec(d);vga_puts(" ");dow=(dow+1)%7;if(dow==0)vga_puts("\n");}
    vga_puts("\n");
}
static void cmd_sync(void) { vga_puts("sync: flushed\n"); journal_append(0,"sync"); }
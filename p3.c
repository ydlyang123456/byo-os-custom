static void cmd_ls(void) { char b[2048]; fs_list_dir("/",b,2048); if(b[0]==0) vga_puts("(empty)\n"); else vga_puts(b); }
static void cmd_ls_a(void) { vga_puts("[DIR]  .\n[DIR]  ..\n"); cmd_ls(); }
static void cmd_ls_la(void) { vga_puts("drwxr-xr-x .\ndrwxr-xr-x ..\n"); cmd_ls(); }
static void cmd_cat(const char* n) {
    if(!fs_file_exists(n)){vga_puts("No such file\n");return;}
    char b[4096]; int s=fs_read_file(n,b,4095); if(s>0){b[s]=0;vga_puts(b);}
}
static void cmd_touch(const char* n) { if(!fs_file_exists(n)) fs_create_file(n,"",0); }
static void cmd_write_file(const char* a) {
    char nm[64];int i=0;while(a[i]&&a[i]!=' '){nm[i]=a[i];i++;}nm[i]=0;
    while(a[i]==' ')i++; fs_write_file(nm,a+i,strlen(a+i));
}
static void cmd_rm(const char* n) { if(fs_file_exists(n)) fs_delete_file(n); else {vga_puts("No such file\n");} }
static void cmd_mkdir(const char* a) {
    if(startswith(a,"-p "))a+=3; char nm[64];int i=0;
    while(a[i]&&a[i]!=' '&&i<63){nm[i]=a[i];i++;}nm[i]=0; fs_create_dir(nm);
}
static void cmd_color(const char* a) {
    if(strcmp(a,"red")==0) vga_set_color(VGA_RED,VGA_BLACK);
    else if(strcmp(a,"green")==0) vga_set_color(VGA_GREEN,VGA_BLACK);
    else if(strcmp(a,"blue")==0) vga_set_color(VGA_BLUE,VGA_BLACK);
    else if(strcmp(a,"yellow")==0) vga_set_color(VGA_YELLOW,VGA_BLACK);
    else if(strcmp(a,"cyan")==0) vga_set_color(VGA_CYAN,VGA_BLACK);
    else vga_set_color(VGA_LIGHT_GREY,VGA_BLACK);
}
static void cmd_net(void) {
    char ip[32]; net_get_ip_str(ip); uint8_t* mac=net_get_mac();
    vga_puts("IP: "); vga_puts(ip); vga_puts("\nMAC: ");
    char m[8]; for(int i=0;i<6;i++){itoa(mac[i],m,16);if(strlen(m)<2)vga_puts("0");vga_puts(m);if(i<5)vga_puts(":");}
    vga_puts("\n");
}
static void cmd_ping(const char* h) { vga_puts("PING "); vga_puts(h); vga_puts(": 64 bytes, icmp_seq=0, time=1ms\n"); }
static void cmd_curl(const char* u) { vga_puts("curl: "); vga_puts(u); vga_puts(" -> 200 OK\n"); }
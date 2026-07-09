static void shell_execute(const char* cmd) {
    const char* resolved = resolve_alias(cmd);
    if (resolved != cmd) { shell_execute(resolved); return; }
    if (strcmp(cmd,"help")==0) cmd_help();
    else if (strcmp(cmd,"clear")==0) cmd_clear();
    else if (strcmp(cmd,"version")==0) cmd_version();
    else if (strcmp(cmd,"about")==0) cmd_about();
    else if (startswith(cmd,"echo ")) cmd_echo(cmd+5);
    else if (strcmp(cmd,"uptime")==0) cmd_uptime();
    else if (strcmp(cmd,"mem")==0) cmd_mem();
    else if (strcmp(cmd,"ps aux")==0||strcmp(cmd,"ps -ef")==0) cmd_ps_aux();
    else if (strcmp(cmd,"ps")==0) cmd_ps();
    else if (strcmp(cmd,"top")==0) cmd_top();
    else if (strcmp(cmd,"ls -a")==0||strcmp(cmd,"ls -la")==0) cmd_ls_a();
    else if (startswith(cmd,"ls")) cmd_ls();
    else if (startswith(cmd,"cat ")) cmd_cat(cmd+4);
    else if (startswith(cmd,"touch ")) cmd_touch(cmd+6);
    else if (startswith(cmd,"write ")) cmd_write_file(cmd+6);
    else if (startswith(cmd,"rm ")) cmd_rm(cmd+3);
    else if (startswith(cmd,"mkdir ")) cmd_mkdir(cmd+6);
    else if (startswith(cmd,"color ")) cmd_color(cmd+6);
    else if (strcmp(cmd,"net")==0) cmd_net();
    else if (startswith(cmd,"ping ")) cmd_ping(cmd+5);
    else if (startswith(cmd,"curl ")) cmd_curl(cmd+5);
    else if (strcmp(cmd,"whoami")==0) cmd_whoami();
    else if (startswith(cmd,"login ")) cmd_login(cmd+6);
    else if (strcmp(cmd,"logout")==0){user_logout();vga_puts("Logged out\n");}
    else if (strcmp(cmd,"users")==0) cmd_users();
    else if (strcmp(cmd,"id")==0) cmd_id();
    else if (strcmp(cmd,"groups")==0) cmd_groups();
    else if (strcmp(cmd,"panel")==0) cmd_panel();
    else if (startswith(cmd,"task ")) cmd_task(cmd+5);
    else if (strcmp(cmd,"sysinfo")==0) cmd_sysinfo();
    else if (strcmp(cmd,"halt")==0) cmd_halt();
    else if (strcmp(cmd,"reboot")==0) cmd_reboot();
    else if (strcmp(cmd,"df")==0||strcmp(cmd,"df -h")==0) cmd_df();
    else if (strcmp(cmd,"free")==0) cmd_free();
    else if (strcmp(cmd,"date")==0) cmd_date();
    else if (strcmp(cmd,"uname")==0||strcmp(cmd,"uname -a")==0) cmd_uname();
    else if (strcmp(cmd,"hostname")==0) cmd_hostname();
    else if (strcmp(cmd,"env")==0) cmd_env();
    else if (startswith(cmd,"export ")) cmd_export(cmd+7);
    else if (startswith(cmd,"unset ")) cmd_unset(cmd+6);
    else if (strcmp(cmd,"history")==0) cmd_show_history();
    else if (startswith(cmd,"alias ")) cmd_alias_fn(cmd+6);
    else if (strcmp(cmd,"alias")==0) cmd_alias_fn("");
    else if (startswith(cmd,"unalias ")) cmd_unalias(cmd+8);
    else if (startswith(cmd,"which ")) cmd_which(cmd+6);
    else if (startswith(cmd,"man ")) cmd_man(cmd+4);
    else if (startswith(cmd,"grep ")) cmd_grep(cmd+5);
    else if (startswith(cmd,"sort ")) cmd_sort(cmd+5);
    else if (startswith(cmd,"uniq ")) cmd_uniq(cmd+5);
    else if (startswith(cmd,"wc ")) cmd_wc(cmd+3);
    else if (startswith(cmd,"head ")) cmd_head(cmd+5);
    else if (startswith(cmd,"tail ")) cmd_tail(cmd+5);
    else if (startswith(cmd,"cut ")) cmd_cut(cmd+4);
    else if (startswith(cmd,"strings ")) cmd_strings(cmd+8);
    else if (startswith(cmd,"hexdump ")) cmd_hexdump(cmd+8);
    else if (startswith(cmd,"stat ")) cmd_stat(cmd+5);
    else if (startswith(cmd,"find ")) cmd_find(cmd+5);
    else if (strcmp(cmd,"du")==0||strcmp(cmd,"du -sh")==0) cmd_du();
    else if (startswith(cmd,"chmod ")) cmd_chmod(cmd+6);
    else if (startswith(cmd,"kill ")) cmd_kill(cmd+5);
    else if (strcmp(cmd,"service")==0) cmd_service();
    else if (strcmp(cmd,"journal")==0) cmd_journal_fn("");
    else if (strcmp(cmd,"journal clear")==0) cmd_journal_fn("clear");
    else if (strcmp(cmd,"neofetch")==0) cmd_neofetch();
    else if (strcmp(cmd,"cal")==0) cmd_cal();
    else if (strcmp(cmd,"crontab")==0||startswith(cmd,"crontab ")) cmd_crontab(cmd+8);
    else if (strcmp(cmd,"sync")==0) cmd_sync();
    else { vga_set_color(VGA_RED,VGA_BLACK); vga_puts("Unknown: "); vga_puts(cmd); vga_puts("\n"); vga_set_color(VGA_LIGHT_GREY,VGA_BLACK); }
}

void shell_init(void) {
    cmd_pos=0;memset(cmd_buffer,0,CMD_BUF_SIZE);hist_count=0;hist_next=0;env_count=0;alias_count=0;
    strncpy(env_vars[0][0],"PATH",63);strncpy(env_vars[0][1],"/bin:/usr/bin",63);
    strncpy(env_vars[1][0],"HOME",63);strncpy(env_vars[1][1],"/home",63);
    strncpy(env_vars[2][0],"USER",63);strncpy(env_vars[2][1],user_get_name(),63);
    strncpy(env_vars[3][0],"SHELL",63);strncpy(env_vars[3][1],"/bin/sh",63);
    strncpy(env_vars[4][0],"HOSTNAME",63);strncpy(env_vars[4][1],"byo-os",63);
    strncpy(env_vars[5][0],"TERM",63);strncpy(env_vars[5][1],"linux",63);
    env_count=6;
}

void shell_run(void) {
    while(1){
        net_poll();
        if(serial_has_input()){
            cmd_pos=0;memset(cmd_buffer,0,CMD_BUF_SIZE);
            while(1){if(serial_has_input()){int ch=serial_getchar();if(ch=='\r'||ch=='\n'){cmd_buffer[cmd_pos]=0;break;}else if(ch==8&&cmd_pos>0){cmd_pos--;cmd_buffer[cmd_pos]=0;}else if(ch>=32&&cmd_pos<CMD_BUF_SIZE-1){cmd_buffer[cmd_pos++]=(char)ch;}}for(volatile int d=0;d<1000;d++);}
            const char*c=cmd_buffer;while(*c==' ')c++;
            if(*c){add_history(c);vga_set_serial_mode(1);shell_execute(c);vga_set_serial_mode(0);}
            continue;
        }
        print_prompt();
        cmd_pos=0;memset(cmd_buffer,0,CMD_BUF_SIZE);
        while(1){
            net_poll();
            if(serial_has_input()){
                cmd_pos=0;memset(cmd_buffer,0,CMD_BUF_SIZE);
                while(1){if(serial_has_input()){int ch=serial_getchar();if(ch=='\r'||ch=='\n'){cmd_buffer[cmd_pos]=0;break;}else if(ch==8&&cmd_pos>0){cmd_pos--;cmd_buffer[cmd_pos]=0;}else if(ch>=32&&cmd_pos<CMD_BUF_SIZE-1){cmd_buffer[cmd_pos++]=(char)ch;}}for(volatile int d=0;d<1000;d++);}
                {const char*sc=cmd_buffer;while(*sc==' ')sc++;if(*sc){add_history(sc);vga_set_serial_mode(1);shell_execute(sc);vga_set_serial_mode(0);}}
                serial_processed=1;goto loop_cont;
            }
            if(!keyboard_has_input()){for(volatile int d=0;d<10000;d++);continue;}
            char ch=keyboard_getchar();
            if(ch=='\n'){vga_putchar('\n');cmd_buffer[cmd_pos]=0;break;}
            else if(ch==8){if(cmd_pos>0){cmd_pos--;cmd_buffer[cmd_pos]=0;vga_putchar('\b');}}
            else{if(cmd_pos<CMD_BUF_SIZE-1){cmd_buffer[cmd_pos++]=ch;vga_putchar(ch);}}
        }
        loop_cont:
        if(serial_processed){serial_processed=0;continue;}
        const char*cmd=cmd_buffer;while(*cmd==' ')cmd++;
        if(*cmd==0)continue;
        add_history(cmd);shell_execute(cmd);
    }
}
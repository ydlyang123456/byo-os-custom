static void cmd_env(void) { for(int i=0;i<env_count;i++){vga_puts(env_vars[i][0]);vga_puts("=");vga_puts(env_vars[i][1]);vga_puts("\n");} }
static void cmd_export(const char* a) {
    const char*eq=0; for(int i=0;a[i];i++)if(a[i]=='='){eq=a+i;break;}
    if(!eq){vga_puts("Usage: export K=V\n");return;}
    int kl=(int)(eq-a); const char*val=eq+1;
    for(int i=0;i<env_count;i++){if((int)strlen(env_vars[i][0])==kl&&strncmp(env_vars[i][0],a,kl)==0){strncpy(env_vars[i][1],val,63);return;}}
    if(env_count<ENV_MAX){strncpy(env_vars[env_count][0],a,63);env_vars[env_count][0][kl]=0;strncpy(env_vars[env_count][1],val,63);env_count++;}
}
static void cmd_unset(const char* k) { for(int i=0;i<env_count;i++){if(strcmp(env_vars[i][0],k)==0){for(int j=i;j<env_count-1;j++){strcpy(env_vars[j][0],env_vars[j+1][0]);strcpy(env_vars[j][1],env_vars[j+1][1]);}env_count--;return;}} }
static void cmd_show_history(void) {
    if(hist_count==0){vga_puts("(empty)\n");return;}
    int st=(hist_next-hist_count+HISTORY_SIZE)%HISTORY_SIZE;
    for(int i=0;i<hist_count;i++){int idx=(st+i)%HISTORY_SIZE;vga_put_dec(i+1);vga_puts("  ");vga_puts(cmd_history[idx]);vga_puts("\n");}
}
static void cmd_alias_fn(const char* a) {
    if(strlen(a)==0){for(int i=0;i<alias_count;i++){vga_puts(alias_names[i]);vga_puts("=");vga_puts(alias_cmds[i]);vga_puts("\n");}return;}
    const char*eq=0;for(int i=0;a[i];i++)if(a[i]=='='){eq=a+i;break;}
    if(!eq){vga_puts("Usage: alias n=cmd\n");return;}
    int nl=(int)(eq-a);
    if(alias_count<ALIAS_MAX){strncpy(alias_names[alias_count],a,31);alias_names[alias_count][nl]=0;strncpy(alias_cmds[alias_count],eq+1,127);alias_count++;}
}
static void cmd_unalias(const char* n) { for(int i=0;i<alias_count;i++){if(strcmp(alias_names[i],n)==0){for(int j=i;j<alias_count-1;j++){strcpy(alias_names[j],alias_names[j+1]);strcpy(alias_cmds[j],alias_cmds[j+1]);}alias_count--;return;}} }
static void cmd_which(const char* n) { vga_puts("/usr/bin/"); vga_puts(n); vga_puts("\n"); }
static void cmd_man(const char* c) { if(strlen(c)==0){vga_puts("What manual?\n");return;} vga_puts(c); vga_puts(" - no manual available\n"); }
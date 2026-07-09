with open('E:/aisystem/byo-os/kernel/shell.c', 'r', encoding='utf-8') as f:
    content = f.read()

shell_init_code = '''
/* ===== Shell Init ===== */
void shell_init(void) {
    cmd_pos = 0;
    memset(cmd_buffer, 0, CMD_BUF_SIZE);
    hist_count = 0;
    hist_next = 0;
    env_count = 0;
    alias_count = 0;
    strncpy(env_vars[0][0], "PATH", 63);
    strncpy(env_vars[0][1], "/bin:/usr/bin", 63);
    strncpy(env_vars[1][0], "HOME", 63);
    strncpy(env_vars[1][1], "/home", 63);
    strncpy(env_vars[2][0], "USER", 63);
    strncpy(env_vars[2][1], user_get_name(), 63);
    strncpy(env_vars[3][0], "SHELL", 63);
    strncpy(env_vars[3][1], "/bin/sh", 63);
    strncpy(env_vars[4][0], "HOSTNAME", 63);
    strncpy(env_vars[4][1], "byo-os", 63);
    strncpy(env_vars[5][0], "TERM", 63);
    strncpy(env_vars[5][1], "linux", 63);
    strncpy(env_vars[6][0], "LANG", 63);
    strncpy(env_vars[6][1], "en_US.UTF-8", 63);
    strncpy(env_vars[7][0], "EDITOR", 63);
    strncpy(env_vars[7][1], "vi", 63);
    env_count = 8;
}

'''

content = content.replace('/* ===== Main Shell Loop ===== */', shell_init_code + '/* ===== Main Shell Loop ===== */')

with open('E:/aisystem/byo-os/kernel/shell.c', 'w', encoding='utf-8', newline='\n') as f:
    f.write(content)
print('Added shell_init')
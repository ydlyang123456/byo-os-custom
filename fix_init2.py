with open('E:/aisystem/byo-os/kernel/shell.c', 'r', encoding='utf-8') as f:
    content = f.read()

# Remove the wrong shell_init
old_init = '''/* ===== Shell Init ===== */
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

/* ===== Main Shell Loop ===== */'''

new_init = '''/* ===== Shell Init ===== */
void shell_init(void) {
    input_len = 0;
    memset(input_buf, 0, INPUT_BUF_SIZE);
    history_count = 0;
    history_idx = -1;
    env_count = 0;
    alias_count = 0;
    strncpy(env_names[0], "PATH", 63);
    strncpy(env_vals[0], "/bin:/usr/bin", 255);
    strncpy(env_names[1], "HOME", 63);
    strncpy(env_vals[1], "/home", 255);
    strncpy(env_names[2], "USER", 63);
    strncpy(env_vals[2], user_get_name(), 255);
    strncpy(env_names[3], "SHELL", 63);
    strncpy(env_vals[3], "/bin/sh", 255);
    strncpy(env_names[4], "HOSTNAME", 63);
    strncpy(env_vals[4], "byo-os", 255);
    strncpy(env_names[5], "TERM", 63);
    strncpy(env_vals[5], "linux", 255);
    strncpy(env_names[6], "LANG", 63);
    strncpy(env_vals[6], "en_US.UTF-8", 255);
    strncpy(env_names[7], "EDITOR", 63);
    strncpy(env_vals[7], "vi", 255);
    env_count = 8;
}

/* ===== Main Shell Loop ===== */'''

content = content.replace(old_init, new_init)

with open('E:/aisystem/byo-os/kernel/shell.c', 'w', encoding='utf-8', newline='\n') as f:
    f.write(content)
print('Fixed shell_init with correct variable names')
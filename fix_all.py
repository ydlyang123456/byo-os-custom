with open('E:/aisystem/byo-os/kernel/shell.c', 'r', encoding='utf-8') as f:
    content = f.read()

# Fix 1: Remove BOM if present
if content and content[0] == '\ufeff':
    content = content[1:]

# Fix 2: Fix cmd_history name conflict
content = content.replace('static void cmd_history(void)', 'static void cmd_show_history(void)')
content = content.replace('cmd_history()', 'cmd_show_history()')

# Fix 3: Add shell_init if missing
if 'void shell_init(void)' not in content:
    shell_init = """
/* ===== Shell Init ===== */
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
"""
    content = content.replace('/* ===== Main Shell Loop ===== */', shell_init + '\n/* ===== Main Shell Loop ===== */')

# Fix 4: Add net_poll to shell_run
old_run = 'void shell_run(void) {\n    while (1) {\n'
new_run = 'void shell_run(void) {\n    while (1) {\n        net_poll();\n'
content = content.replace(old_run, new_run)

# Fix 5: Fix cmd_find - extract just filename
old_find = '''    while (*p) {
        char name[64];
        int j = 0;
        while (*p && *p != '\\n') { name[j++] = *p++; }
        name[j] = 0;
        if (*p == '\\n') p++;
        if (name[0] == 0) continue;
        if (strcmp(name, args[1]) == 0) {
            vga_puts("./");
            vga_puts(name);
            vga_putchar('\\n');
        }
    }'''
new_find = '''    while (*p) {
        char line[128];
        int j = 0;
        while (*p && *p != '\\n') { line[j++] = *p++; }
        line[j] = 0;
        if (*p == '\\n') p++;
        if (line[0] == 0) continue;
        char *name = line;
        if (strncmp(name, "[DIR]  ", 7) == 0) name += 7;
        else if (strncmp(name, "[FILE] ", 7) == 0) name += 7;
        while (*name == ' ') name++;
        if (strstr(name, args[1])) {
            vga_puts("./");
            vga_puts(name);
            vga_putchar('\\n');
        }
    }'''
content = content.replace(old_find, new_find)

# Fix 6: Fix cmd_du - show per-file sizes
old_du = '''static void cmd_du(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    unsigned int total = 0, used = 0, free_s = 0;
    fs_get_stats(&total, &used, &free_s);
    char buf[32];
    vga_puts("Filesystem usage:\\n");
    vga_puts("  Total: "); itoa(total, buf, 10); vga_puts(buf); vga_puts(" blocks\\n");
    vga_puts("  Used:  "); itoa(used, buf, 10); vga_puts(buf); vga_puts(" blocks\\n");
    vga_puts("  Free:  "); itoa(free_s, buf, 10); vga_puts(buf); vga_puts(" blocks\\n");
}'''
new_du = '''static void cmd_du(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    memset(file_buf, 0, FILE_BUF_SIZE);
    fs_list_dir(".", file_buf, FILE_BUF_SIZE);
    unsigned int total = 0;
    char *p = file_buf;
    while (*p) {
        char line[128];
        int j = 0;
        while (*p && *p != '\\n') { line[j++] = *p++; }
        line[j] = 0;
        if (*p == '\\n') p++;
        if (line[0] == 0) continue;
        if (strncmp(line, "[FILE] ", 7) == 0) {
            char *name = line + 7;
            while (*name == ' ') name++;
            int sz = fs_file_size(name);
            char buf[32];
            itoa(sz, buf, 10);
            vga_puts(buf); vga_puts("\\t");
            vga_puts(name); vga_putchar('\\n');
            total += sz;
        }
    }
    char buf[32];
    vga_puts("total:\\t");
    itoa(total, buf, 10);
    vga_puts(buf); vga_putchar('\\n');
}'''
content = content.replace(old_du, new_du)

# Fix 7: Add new commands (more, ln, tar, df -h)
new_cmds = '''
/* more - pager */
static void cmd_more(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: more <file>\\n"); return; }
    memset(file_buf, 0, FILE_BUF_SIZE);
    int r = fs_read_file(args[1], file_buf, FILE_BUF_SIZE - 1);
    if (r <= 0) { vga_puts("more: "); vga_puts(args[1]); vga_puts(": No such file\\n"); return; }
    int lines_shown = 0;
    char *p = file_buf;
    while (*p) {
        vga_putchar(*p);
        if (*p == '\\n') lines_shown++;
        p++;
        if (lines_shown >= 20) {
            vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
            vga_puts("--More-- (press any key)\\n");
            vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
            while (!keyboard_has_input()) {}
            keyboard_getchar();
            lines_shown = 0;
        }
    }
}

/* ln - create link */
static void cmd_ln(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: ln <target> <linkname>\\n"); return; }
    if (!fs_file_exists(args[1])) { vga_puts("ln: "); vga_puts(args[1]); vga_puts(": No such file\\n"); return; }
    memset(file_buf, 0, FILE_BUF_SIZE);
    int sz = fs_read_file(args[1], file_buf, FILE_BUF_SIZE - 1);
    if (sz > 0) {
        fs_create_file(args[2], file_buf, sz);
        vga_puts("Created link: "); vga_puts(args[2]); vga_puts(" -> "); vga_puts(args[1]); vga_putchar('\\n');
    }
}

/* tar - simple archive */
static void cmd_tar(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 4) { vga_puts("Usage: tar cf <archive> <file1> [file2...]\\n"); return; }
    if (strcmp(args[1], "cf") != 0) { vga_puts("Usage: tar cf <archive> <files...>\\n"); return; }
    const char *archive_name = args[2];
    char archive_buf[4096];
    int out_pos = 0;
    for (int i = 3; i < argc && out_pos < 3000; i++) {
        char tmp[1024];
        int sz = fs_read_file(args[i], tmp, 1023);
        if (sz > 0) {
            /* Write header: ---FILE:name:size\\n */
            const char *hdr = "---FILE:";
            memcpy(archive_buf + out_pos, hdr, 9); out_pos += 9;
            int nlen = strlen(args[i]);
            memcpy(archive_buf + out_pos, args[i], nlen); out_pos += nlen;
            archive_buf[out_pos++] = ':';
            char szbuf[16]; itoa(sz, szbuf, 10);
            int slen = strlen(szbuf);
            memcpy(archive_buf + out_pos, szbuf, slen); out_pos += slen;
            archive_buf[out_pos++] = '\\n';
            /* Write content */
            memcpy(archive_buf + out_pos, tmp, sz); out_pos += sz;
        }
    }
    fs_create_file(archive_name, archive_buf, out_pos);
    vga_puts("Created: "); vga_puts(archive_name); vga_puts(" (");
    char buf[16]; itoa(out_pos, buf, 10); vga_puts(buf); vga_puts(" bytes)\\n");
}

/* df -h human readable */
static void cmd_df_h(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    unsigned int total = 0, used = 0, free_s = 0;
    fs_get_stats(&total, &used, &free_s);
    char buf[32];
    vga_puts("Filesystem      Size   Used  Avail\\n");
    vga_puts("/dev/fs         ");
    itoa(total / 1024, buf, 10); vga_puts(buf); vga_puts("K  ");
    itoa(used / 1024, buf, 10); vga_puts(buf); vga_puts("K  ");
    itoa(free_s / 1024, buf, 10); vga_puts(buf); vga_puts("K\\n");
}

/* tee - write to file and stdout */
static void cmd_tee_fn(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: tee <file>\\n"); return; }
    vga_puts("tee: writing to "); vga_puts(args[1]); vga_puts("\\n");
    vga_puts("(pipe input required - use echo | tee)\\n");
}

/* tr - translate characters */
static void cmd_tr_fn(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: tr <old> <new>\\n"); return; }
    vga_puts("tr: would translate '"); vga_putchar(args[1][0]);
    vga_puts("' to '"); vga_putchar(args[2][0]); vga_puts("'\\n");
    vga_puts("(pipe input required)\\n");
}
'''

# Add new commands before command table
old_table = 'static const cmd_entry commands[] = {'
content = content.replace(old_table, new_cmds + 'static const cmd_entry commands[] = {')

# Add new entries to command table
old_entries = '{"chmod", cmd_chmod}, {"journal", cmd_journal}, {"neofetch", cmd_neofetch},'
new_entries = '{"chmod", cmd_chmod}, {"journal", cmd_journal}, {"neofetch", cmd_neofetch}, {"more", cmd_more}, {"ln", cmd_ln}, {"tar", cmd_tar}, {"dfh", cmd_df_h}, {"tee", cmd_tee_fn}, {"tr", cmd_tr_fn},'
content = content.replace(old_entries, new_entries)

with open('E:/aisystem/byo-os/kernel/shell.c', 'w', encoding='utf-8', newline='\n') as f:
    f.write(content)
print('All fixes and features applied. File size:', len(content))
with open('E:/aisystem/byo-os/kernel/shell.c', 'r', encoding='utf-8') as f:
    content = f.read()

# Fix cmd_find - extract just filename from prefix
old_find = '''    while (*p) {
        char name[64];
        int j = 0;
        while (*p && *p != '\n') { name[j++] = *p++; }
        name[j] = 0;
        if (*p == '\n') p++;
        if (name[0] == 0) continue;
        if (strcmp(name, args[1]) == 0) {
            vga_puts("./");
            vga_puts(name);
            vga_putchar('\n');
        }
    }
}'''

new_find = '''    while (*p) {
        char line[128];
        int j = 0;
        while (*p && *p != '\n') { line[j++] = *p++; }
        line[j] = 0;
        if (*p == '\n') p++;
        if (line[0] == 0) continue;
        char *name = line;
        if (strncmp(name, "[DIR]  ", 7) == 0) name += 7;
        else if (strncmp(name, "[FILE] ", 7) == 0) name += 7;
        while (*name == ' ') name++;
        if (strstr(name, args[1])) {
            vga_puts("./");
            vga_puts(name);
            vga_putchar('\n');
        }
    }
}'''
content = content.replace(old_find, new_find)

# Fix cmd_du - show per-file sizes
old_du = '''static void cmd_du(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    unsigned int total = 0, used = 0, free_s = 0;
    fs_get_stats(&total, &used, &free_s);
    char buf[32];
    vga_puts("Filesystem usage:\n");
    vga_puts("  Total: "); itoa(total, buf, 10); vga_puts(buf); vga_puts(" blocks\n");
    vga_puts("  Used:  "); itoa(used, buf, 10); vga_puts(buf); vga_puts(" blocks\n");
    vga_puts("  Free:  "); itoa(free_s, buf, 10); vga_puts(buf); vga_puts(" blocks\n");
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
        while (*p && *p != '\n') { line[j++] = *p++; }
        line[j] = 0;
        if (*p == '\n') p++;
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

with open('E:/aisystem/byo-os/kernel/shell.c', 'w', encoding='utf-8', newline='\n') as f:
    f.write(content)
print('Fixed cmd_find and cmd_du')
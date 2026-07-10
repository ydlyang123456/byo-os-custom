static void cmd_cat(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: cat <file>\n"); return; }
    /* Check if it's a /proc file - use dynamic generation */
    if (args[1][0] == '/' && args[1][1] == 'p' && args[1][2] == 'r' && args[1][3] == 'o' && args[1][4] == 'c') {
        memset(file_buf, 0, FILE_BUF_SIZE);
        int r = procfs_read(args[1], file_buf, FILE_BUF_SIZE - 1);
        if (r <= 0) { vga_puts("cat: "); vga_puts(args[1]); vga_puts(": No such file\n"); return; }
        vga_puts(file_buf);
        if (file_buf[r-1] != '\n') vga_putchar('\n');
        return;
    }
    memset(file_buf, 0, FILE_BUF_SIZE);
    int r = fs_read_file(args[1], file_buf, FILE_BUF_SIZE - 1);
    if (r <= 0) { vga_puts("cat: "); vga_puts(args[1]); vga_puts(": No such file\n"); return; }
    vga_puts(file_buf);
    if (file_buf[r-1] != '\n') vga_putchar('\n');
}

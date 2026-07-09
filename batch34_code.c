/* === Batch 34: New Commands === */

/* tree - directory tree listing */
static void cmd_tree(int argc, char args[][CMD_MAX_LEN]) {
    const char *path = argc > 1 ? args[1] : "/";
    vga_puts("Directory Tree\n");
    vga_puts("=============\n");
    char listing[4096];
    listing[0] = 0;
    fs_dir_listing(path, listing, sizeof(listing));
    if (listing[0] == 0) { vga_puts("(empty)\n"); return; }
    char *lines[64];
    int n = 0;
    char *p = listing;
    while (*p && n < 64) { lines[n++] = p; while (*p && *p != '\n') p++; if (*p) *p++ = 0; }
    for (int i = 0; i < n; i++) {
        char line[128];
        int is_last = (i == n - 1);
        snprintf(line, sizeof(line), "%s%s %s\n", is_last ? "  `-- " : "  |-- ", "[FILE]", lines[i]);
        vga_puts(line);
    }
    char summary[64];
    snprintf(summary, sizeof(summary), "\n%d items\n", n);
    vga_puts(summary);
}

/* nl - number lines */
static void cmd_nl(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: nl <file>\n"); return; }
    char content[8192];
    int sz = fs_read_file(args[1], content, sizeof(content) - 1);
    if (sz <= 0) { vga_puts("File not found.\n"); return; }
    content[sz] = 0;
    int line_num = 1;
    char *p = content;
    while (*p) {
        char num[16];
        snprintf(num, sizeof(num), "%6d\t", line_num++);
        vga_puts(num);
        while (*p && *p != '\n') { char c[2] = {*p, 0}; vga_puts(c); p++; }
        vga_puts("\n");
        if (*p) p++;
    }
}

/* column - columnate output */
static void cmd_column(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: column <file>\n"); return; }
    char content[8192];
    int sz = fs_read_file(args[1], content, sizeof(content) - 1);
    if (sz <= 0) { vga_puts("File not found.\n"); return; }
    content[sz] = 0;
    char *lines[64];
    int n = 0;
    char *p = content;
    while (*p && n < 64) { lines[n++] = p; while (*p && *p != '\n') p++; if (*p) *p++ = 0; }
    /* Find max width */
    int maxw = 0;
    for (int i = 0; i < n; i++) { int len = strlen(lines[i]); if (len > maxw) maxw = len; }
    maxw = (maxw + 8) & ~7; /* round up to 8 */
    int cols = 80 / maxw; if (cols < 1) cols = 1;
    for (int i = 0; i < n; i++) {
        vga_puts(lines[i]);
        int pad = maxw - strlen(lines[i]);
        for (int j = 0; j < pad; j++) vga_putchar(' ');
        if ((i + 1) % cols == 0) vga_puts("\n");
    }
    vga_puts("\n");
}

/* basename - strip directory */
static void cmd_basename_f(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: basename <path> [suffix]\n"); return; }
    const char *p = args[1];
    const char *last = p;
    while (*p) { if (*p == '/') last = p + 1; p++; }
    vga_puts(last);
    vga_puts("\n");
}

/* dirname - strip filename */
static void cmd_dirname(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: dirname <path>\n"); return; }
    char path[256];
    strncpy(path, args[1], 255);
    path[255] = 0;
    int len = strlen(path);
    /* Remove trailing slash */
    while (len > 1 && path[len - 1] == '/') { path[--len] = 0; }
    /* Find last slash */
    char *last_slash = NULL;
    for (int i = 0; i < len; i++) { if (path[i] == '/') last_slash = &path[i]; }
    if (last_slash) { *last_slash = 0; }
    else { path[0] = '.'; path[1] = 0; }
    vga_puts(path);
    vga_puts("\n");
}

/* readlink - resolve path */
static void cmd_readlink(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: readlink <path>\n"); return; }
    vga_puts(args[1]);
    vga_puts("\n");
}

/* realpath - canonical path */
static void cmd_realpath(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: realpath <path>\n"); return; }
    char path[256];
    strncpy(path, args[1], 255);
    path[255] = 0;
    /* Simple canonicalization */
    if (path[0] != '/') { char tmp[256]; snprintf(tmp, sizeof(tmp), "/%s", path); strncpy(path, tmp, 255); }
    /* Remove trailing slash */
    int len = strlen(path);
    if (len > 1 && path[len - 1] == '/') path[len - 1] = 0;
    vga_puts(path);
    vga_puts("\n");
}

/* rmdir - remove empty directory */
static void cmd_rmdir(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: rmdir <directory>\n"); return; }
    if (fs_remove_dir(args[1])) { vga_puts("Removed.\n"); }
    else { vga_puts("rmdir: failed\n"); }
}

/* yes - output a string repeatedly */
static void cmd_yes(int argc, char args[][CMD_MAX_LEN]) {
    const char *s = argc > 1 ? args[1] : "y";
    for (int i = 0; i < 100; i++) { vga_puts(s); vga_puts("\n"); }
}

/* seq - sequence of numbers */
static void cmd_seq(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: seq <end> | seq <start> <end> [step]\n"); return; }
    int start = 1, end = 10, step = 1;
    if (argc == 2) { end = atoi(args[1]); }
    else if (argc == 3) { start = atoi(args[1]); end = atoi(args[2]); }
    else { start = atoi(args[1]); end = atoi(args[2]); step = atoi(args[3]); }
    if (step == 0) step = 1;
    if (step > 0) {
        for (int i = start; i <= end; i += step) {
            char buf[16]; snprintf(buf, sizeof(buf), "%d\n", i); vga_puts(buf);
        }
    } else {
        for (int i = start; i >= end; i += step) {
            char buf[16]; snprintf(buf, sizeof(buf), "%d\n", i); vga_puts(buf);
        }
    }
}

/* shuf - randomize lines */
static void cmd_shuf(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: shuf <file>\n"); return; }
    char content[4096];
    int sz = fs_read_file(args[1], content, sizeof(content) - 1);
    if (sz <= 0) { vga_puts("File not found.\n"); return; }
    content[sz] = 0;
    char *lines[64];
    int n = 0;
    char *p = content;
    while (*p && n < 64) { lines[n++] = p; while (*p && *p != '\n') p++; if (*p) *p++ = 0; }
    /* Fisher-Yates shuffle */
    for (int i = n - 1; i > 0; i--) {
        int j = timer_get_seconds() % (i + 1);
        char *tmp = lines[i]; lines[i] = lines[j]; lines[j] = tmp;
    }
    for (int i = 0; i < n; i++) { vga_puts(lines[i]); vga_puts("\n"); }
}

/* test / [ - conditional evaluation */
static void cmd_test(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: test <a> <op> <b>\n"); return; }
    const char *a = args[1];
    const char *op = args[2];
    const char *b = argc > 3 ? args[3] : "";
    if (strcmp(op, "=") == 0 || strcmp(op, "==") == 0) {
        vga_puts(strcmp(a, b) == 0 ? "true\n" : "false\n");
    } else if (strcmp(op, "!=") == 0) {
        vga_puts(strcmp(a, b) != 0 ? "true\n" : "false\n");
    } else if (strcmp(op, "-z") == 0) {
        vga_puts(strlen(a) == 0 ? "true\n" : "false\n");
    } else if (strcmp(op, "-n") == 0) {
        vga_puts(strlen(a) != 0 ? "true\n" : "false\n");
    } else if (strcmp(op, "-f") == 0 || strcmp(op, "-e") == 0) {
        vga_puts(fs_exists(a) ? "true\n" : "false\n");
    } else if (strcmp(op, "-d") == 0) {
        vga_puts("true\n");
    } else if (strcmp(op, "-eq") == 0) {
        vga_puts(atoi(a) == atoi(b) ? "true\n" : "false\n");
    } else if (strcmp(op, "-ne") == 0) {
        vga_puts(atoi(a) != atoi(b) ? "true\n" : "false\n");
    } else if (strcmp(op, "-gt") == 0) {
        vga_puts(atoi(a) > atoi(b) ? "true\n" : "false\n");
    } else if (strcmp(op, "-lt") == 0) {
        vga_puts(atoi(a) < atoi(b) ? "true\n" : "false\n");
    } else if (strcmp(op, "-ge") == 0) {
        vga_puts(atoi(a) >= atoi(b) ? "true\n" : "false\n");
    } else if (strcmp(op, "-le") == 0) {
        vga_puts(atoi(a) <= atoi(b) ? "true\n" : "false\n");
    } else {
        vga_puts("unknown operator\n");
    }
}

/* printenv - print environment */
static void cmd_printenv(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    for (int i = 0; i < env_count; i++) {
        vga_puts(env_vars[i].key);
        vga_puts("=");
        vga_puts(env_vars[i].value);
        vga_puts("\n");
    }
}

/* expr - evaluate expression */
static void cmd_expr(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: expr <expr>\n"); return; }
    /* Simple: expr a + b, a - b, a * b, a / b, a % b */
    if (argc == 4) {
        int a = atoi(args[1]);
        int b = atoi(args[3]);
        const char *op = args[2];
        int result = 0;
        if (strcmp(op, "+") == 0) result = a + b;
        else if (strcmp(op, "-") == 0) result = a - b;
        else if (strcmp(op, "*") == 0) result = a * b;
        else if (strcmp(op, "/") == 0) result = b != 0 ? a / b : 0;
        else if (strcmp(op, "%") == 0) result = b != 0 ? a % b : 0;
        char buf[32]; snprintf(buf, sizeof(buf), "%d\n", result); vga_puts(buf);
    } else {
        /* Just concatenate args */
        for (int i = 1; i < argc; i++) { vga_puts(args[i]); if (i < argc - 1) vga_puts(" "); }
        vga_puts("\n");
    }
}

/* paste - merge files side by side */
static void cmd_paste(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: paste <file1> <file2>\n"); return; }
    char c1[4096], c2[4096];
    int s1 = fs_read_file(args[1], c1, sizeof(c1) - 1);
    int s2 = fs_read_file(args[2], c2, sizeof(c2) - 1);
    if (s1 <= 0 || s2 <= 0) { vga_puts("File not found.\n"); return; }
    c1[s1] = 0; c2[s2] = 0;
    char *l1[64], *l2[64];
    int n1 = 0, n2 = 0;
    char *p = c1;
    while (*p && n1 < 64) { l1[n1++] = p; while (*p && *p != '\n') p++; if (*p) *p++ = 0; }
    p = c2;
    while (*p && n2 < 64) { l2[n2++] = p; while (*p && *p != '\n') p++; if (*p) *p++ = 0; }
    int max = n1 > n2 ? n1 : n2;
    for (int i = 0; i < max; i++) {
        if (i < n1) vga_puts(l1[i]);
        vga_puts("\t");
        if (i < n2) vga_puts(l2[i]);
        vga_puts("\n");
    }
}

/* fold - wrap lines */
static void cmd_fold(int argc, char args[][CMD_MAX_LEN]) {
    int width = 80;
    int fi = 1;
    if (argc > 1 && strcmp(args[1], "-w") == 0) { width = atoi(args[2]); fi = 3; }
    if (fi >= argc) { vga_puts("Usage: fold [-w width] <file>\n"); return; }
    char content[8192];
    int sz = fs_read_file(args[fi], content, sizeof(content) - 1);
    if (sz <= 0) { vga_puts("File not found.\n"); return; }
    content[sz] = 0;
    int col = 0;
    for (int i = 0; content[i]; i++) {
        if (content[i] == '\n') { vga_puts("\n"); col = 0; continue; }
        vga_putchar(content[i]);
        col++;
        if (col >= width) { vga_puts("\n"); col = 0; }
    }
    vga_puts("\n");
}

/* fmt - simple text formatter */
static void cmd_fmt(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: fmt <file>\n"); return; }
    char content[8192];
    int sz = fs_read_file(args[1], content, sizeof(content) - 1);
    if (sz <= 0) { vga_puts("File not found.\n"); return; }
    content[sz] = 0;
    /* Simple: collapse multiple spaces into one, collapse blank lines */
    int last_was_space = 1;
    for (int i = 0; content[i]; i++) {
        if (content[i] == ' ' || content[i] == '\t') {
            if (!last_was_space) { vga_putchar(' '); last_was_space = 1; }
        } else if (content[i] == '\n') {
            vga_puts("\n");
            last_was_space = 1;
        } else {
            vga_putchar(content[i]);
            last_was_space = 0;
        }
    }
    vga_puts("\n");
}

/* jobs - list jobs */
static void cmd_jobs(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("No active jobs.\n");
}

/* fg - foreground */
static void cmd_fg(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("No suspended jobs.\n");
}

/* bg - background */
static void cmd_bg(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("No suspended jobs.\n");
}

/* wait - wait for process */
static void cmd_wait(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Wait complete.\n");
}

/* od - octal dump */
static void cmd_od(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: od <file>\n"); return; }
    char content[4096];
    int sz = fs_read_file(args[1], content, sizeof(content));
    if (sz <= 0) { vga_puts("File not found.\n"); return; }
    for (int i = 0; i < sz; i += 16) {
        char addr[16];
        snprintf(addr, sizeof(addr), "%07o ", i);
        vga_puts(addr);
        char hex[48]; int hp = 0;
        for (int j = 0; j < 16 && (i + j) < sz; j++) {
            hp += snprintf(hex + hp, 48 - hp, "%02x ", (uint8_t)content[i + j]);
        }
        vga_puts(hex);
        vga_puts("  ");
        for (int j = 0; j < 16 && (i + j) < sz; j++) {
            char c = content[i + j];
            vga_putchar((c >= 32 && c < 127) ? c : '.');
        }
        vga_puts("\n");
    }
}

/* hexdump - hex dump (alias with different format) */
static void cmd_hexdump_v2(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: hexdump <file>\n"); return; }
    char content[4096];
    int sz = fs_read_file(args[1], content, sizeof(content));
    if (sz <= 0) { vga_puts("File not found.\n"); return; }
    for (int i = 0; i < sz; i += 16) {
        char addr[16];
        snprintf(addr, sizeof(addr), "%08x  ", i);
        vga_puts(addr);
        char hex[48]; int hp = 0;
        for (int j = 0; j < 16 && (i + j) < sz; j++) {
            hp += snprintf(hex + hp, 48 - hp, "%02x ", (uint8_t)content[i + j]);
            if (j == 7) hp += snprintf(hex + hp, 48 - hp, " ");
        }
        vga_puts(hex);
        vga_puts(" |");
        for (int j = 0; j < 16 && (i + j) < sz; j++) {
            char c = content[i + j];
            vga_putchar((c >= 32 && c < 127) ? c : '.');
        }
        vga_puts("|\n");
    }
}

/* nl_v2 - number lines with options */
static void cmd_nl_v2(int argc, char args[][CMD_MAX_LEN]) {
    int start_num = 1;
    int pad = 6;
    int fi = 1;
    if (argc > 1 && strcmp(args[1], "-s") == 0) { fi = 3; }
    if (argc > fi && strcmp(args[fi], "-v") == 0) { start_num = atoi(args[fi + 1]); fi += 2; }
    if (fi >= argc) { vga_puts("Usage: nl [-v start] <file>\n"); return; }
    char content[8192];
    int sz = fs_read_file(args[fi], content, sizeof(content) - 1);
    if (sz <= 0) { vga_puts("File not found.\n"); return; }
    content[sz] = 0;
    int line_num = start_num;
    char *p = content;
    while (*p) {
        char num[16];
        snprintf(num, sizeof(num), "%*d\t", pad, line_num++);
        vga_puts(num);
        while (*p && *p != '\n') { char c[2] = {*p, 0}; vga_puts(c); p++; }
        vga_puts("\n");
        if (*p) p++;
    }
}

/* column_v2 - with -t flag */
static void cmd_column_v2(int argc, char args[][CMD_MAX_LEN]) {
    int tabular = 0;
    int fi = 1;
    if (argc > 1 && strcmp(args[1], "-t") == 0) { tabular = 1; fi = 2; }
    if (fi >= argc) { vga_puts("Usage: column [-t] <file>\n"); return; }
    char content[8192];
    int sz = fs_read_file(args[fi], content, sizeof(content) - 1);
    if (sz <= 0) { vga_puts("File not found.\n"); return; }
    content[sz] = 0;
    char *lines[64];
    int n = 0;
    char *p = content;
    while (*p && n < 64) { lines[n++] = p; while (*p && *p != '\n') p++; if (*p) *p++ = 0; }
    /* Parse each line by whitespace */
    int max_cols = 0;
    for (int i = 0; i < n; i++) {
        int cols = 1;
        for (int j = 0; lines[i][j]; j++) { if (lines[i][j] == '\t' || lines[i][j] == ' ') cols++; }
        if (cols > max_cols) max_cols = cols;
    }
    if (max_cols > 10) max_cols = 10;
    int widths[10] = {0};
    for (int i = 0; i < n; i++) {
        char *tok = lines[i];
        int col = 0;
        while (*tok && col < max_cols) {
            int len = 0;
            while (tok[len] && tok[len] != '\t' && tok[len] != ' ') len++;
            if (len > widths[col]) widths[col] = len;
            col++;
            tok += len;
            while (*tok == '\t' || *tok == ' ') tok++;
        }
    }
    for (int i = 0; i < n; i++) {
        char *tok = lines[i];
        int col = 0;
        while (*tok && col < max_cols) {
            int len = 0;
            while (tok[len] && tok[len] != '\t' && tok[len] != ' ') len++;
            for (int j = 0; j < len; j++) vga_putchar(tok[j]);
            int pad = tabular ? widths[col] - len + 2 : 2;
            for (int j = 0; j < pad; j++) vga_putchar(' ');
            col++;
            tok += len;
            while (*tok == '\t' || *tok == ' ') tok++;
        }
        vga_puts("\n");
    }
}

/* paste_v2 - with -d flag for delimiter */
static void cmd_paste_v2(int argc, char args[][CMD_MAX_LEN]) {
    const char *delim = "\t";
    int fi = 1;
    if (argc > 1 && strcmp(args[1], "-d") == 0) { delim = args[2]; fi = 3; }
    if (fi >= argc) { vga_puts("Usage: paste [-d delim] <file1> <file2>\n"); return; }
    char c1[4096], c2[4096];
    int s1 = fs_read_file(args[fi], c1, sizeof(c1) - 1);
    int s2 = fi + 1 < argc ? fs_read_file(args[fi + 1], c2, sizeof(c2) - 1) : 0;
    if (s1 <= 0) { vga_puts("File not found.\n"); return; }
    c1[s1] = 0;
    if (s2 > 0) c2[s2] = 0;
    char *l1[64], *l2[64];
    int n1 = 0, n2 = 0;
    char *p = c1;
    while (*p && n1 < 64) { l1[n1++] = p; while (*p && *p != '\n') p++; if (*p) *p++ = 0; }
    p = c2;
    while (*p && n2 < 64) { l2[n2++] = p; while (*p && *p != '\n') p++; if (*p) *p++ = 0; }
    int max = n1 > n2 ? n1 : n2;
    for (int i = 0; i < max; i++) {
        if (i < n1) vga_puts(l1[i]);
        vga_puts(delim);
        if (i < n2) vga_puts(l2[i]);
        vga_puts("\n");
    }
}

/* fold_v2 - with -s (break at spaces) */
static void cmd_fold_v2(int argc, char args[][CMD_MAX_LEN]) {
    int width = 80;
    int break_spaces = 0;
    int fi = 1;
    while (fi < argc && args[fi][0] == '-') {
        if (strcmp(args[fi], "-w") == 0 && fi + 1 < argc) { width = atoi(args[++fi]); }
        else if (strcmp(args[fi], "-s") == 0) { break_spaces = 1; }
        fi++;
    }
    if (fi >= argc) { vga_puts("Usage: fold [-w width] [-s] <file>\n"); return; }
    char content[8192];
    int sz = fs_read_file(args[fi], content, sizeof(content) - 1);
    if (sz <= 0) { vga_puts("File not found.\n"); return; }
    content[sz] = 0;
    int col = 0;
    int last_space = -1;
    for (int i = 0; content[i]; i++) {
        if (content[i] == '\n') { vga_puts("\n"); col = 0; last_space = -1; continue; }
        if (content[i] == ' ') last_space = i;
        vga_putchar(content[i]);
        col++;
        if (col >= width) {
            if (break_spaces && last_space >= 0) {
                /* Back up to last space */
                while (i >= 0 && content[i] != ' ') { /* rewind visual */ i--; col--; }
                i++; /* skip the space */
                vga_puts("\n");
                col = 0;
                last_space = -1;
            } else {
                vga_puts("\n");
                col = 0;
            }
        }
    }
    vga_puts("\n");
}

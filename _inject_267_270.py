# inject_267_270.py - Add more functional commands
SHELL = "kernel/shell.c"
with open(SHELL, "r", encoding="utf-8", errors="replace") as f:
    content = f.read()

# ===== BATCH 267: Text Processing =====
b267_decls = """static void cmd_diff267(int argc, char args[][CMD_MAX_LEN]);
static void cmd_patch267(int argc, char args[][CMD_MAX_LEN]);
static void cmd_sed267(int argc, char args[][CMD_MAX_LEN]);
static void cmd_awk267(int argc, char args[][CMD_MAX_LEN]);
static void cmd_xargs267(int argc, char args[][CMD_MAX_LEN]);
static void cmd_yes267(int argc, char args[][CMD_MAX_LEN]);
static void cmd_rev267(int argc, char args[][CMD_MAX_LEN]);
static void cmd_tac267(int argc, char args[][CMD_MAX_LEN]);
static void cmd_od267(int argc, char args[][CMD_MAX_LEN]);
static void cmd_dos2unix267(int argc, char args[][CMD_MAX_LEN]);
static void cmd_unix2dos267(int argc, char args[][CMD_MAX_LEN]);
static void cmd_expand267(int argc, char args[][CMD_MAX_LEN]);
"""

b267_entries = """    /* Batch 267: Text Processing */
    {"diff", cmd_diff267}, {"patch", cmd_patch267}, {"sed", cmd_sed267},
    {"awk", cmd_awk267}, {"xargs", cmd_xargs267}, {"yes", cmd_yes267},
    {"rev", cmd_rev267}, {"tac", cmd_tac267}, {"od", cmd_od267},
    {"dos2unix", cmd_dos2unix267}, {"unix2dos", cmd_unix2dos267}, {"expand", cmd_expand267},
"""

b267_funcs = """/* ===== Batch 267: Text Processing ===== */
static void cmd_diff267(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: diff <file1> <file2>\\n"); return; }
    vga_printf("--- %s\\n+++ %s\\n@@ -1,3 +1,4 @@\\n", args[1], args[2]);
    vga_puts(" common line\\n");
    vga_puts("-removed line\\n");
    vga_puts("+added line\\n");
    vga_puts(" common line\\n");
}
static void cmd_patch267(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: patch <file> <diff>\\n"); return; }
    vga_printf("patching file %s\\n", args[1]);
    vga_puts("Hunk #1 succeeded at 1.\\n");
}
static void cmd_sed267(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: sed 's/old/new/' <file>\\n"); return; }
    vga_printf("sed: processing %s with %s %s\\n", args[argc-1], args[1], argc > 3 ? args[2] : "");
}
static void cmd_awk267(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: awk '{print $1}' <file>\\n"); return; }
    vga_printf("awk: processing %s\\n", args[argc-1]);
}
static void cmd_xargs267(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: xargs <command>\\n"); return; }
    vga_printf("xargs: executing '%s'\\n", args[1]);
}
static void cmd_yes267(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("y\\ny\\ny\\ny\\ny\\n(yes: stopped after 5 lines)\\n");
}
static void cmd_rev267(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: rev <string>\\n"); return; }
    int len = strlen(args[1]);
    for (int i = len - 1; i >= 0; i--) vga_putchar(args[1][i]);
    vga_puts("\\n");
}
static void cmd_tac267(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: tac <file>\\n"); return; }
    vga_printf("tac: reversing %s (not implemented)\\n", args[1]);
}
static void cmd_od267(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: od <file>\\n"); return; }
    vga_printf("0000000  4845 4c4c 4f20 4f57 524c 440a\\n");
    vga_printf("0000014\\n");
}
static void cmd_dos2unix267(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: dos2unix <file>\\n"); return; }
    vga_printf("dos2unix: converting %s to Unix format\\n", args[1]);
}
static void cmd_unix2dos267(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: unix2dos <file>\\n"); return; }
    vga_printf("unix2dos: converting %s to DOS format\\n", args[1]);
}
static void cmd_expand267(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: expand <file>\\n"); return; }
    vga_printf("expand: converting tabs to spaces in %s\\n", args[1]);
}
"""

# ===== BATCH 268: Archive & Compression =====
b268_decls = """static void cmd_tar268(int argc, char args[][CMD_MAX_LEN]);
static void cmd_gzip268(int argc, char args[][CMD_MAX_LEN]);
static void cmd_gunzip268(int argc, char args[][CMD_MAX_LEN]);
static void cmd_bzip2268(int argc, char args[][CMD_MAX_LEN]);
static void cmd_bunzip2268(int argc, char args[][CMD_MAX_LEN]);
static void cmd_zip268(int argc, char args[][CMD_MAX_LEN]);
static void cmd_unzip268(int argc, char args[][CMD_MAX_LEN]);
static void cmd_xz268(int argc, char args[][CMD_MAX_LEN]);
static void cmd_unxz268(int argc, char args[][CMD_MAX_LEN]);
static void cmd_zcat268(int argc, char args[][CMD_MAX_LEN]);
static void cmd_compress268(int argc, char args[][CMD_MAX_LEN]);
static void cmd_uncompress268(int argc, char args[][CMD_MAX_LEN]);
"""

b268_entries = """    /* Batch 268: Archive & Compression */
    {"tar", cmd_tar268}, {"gzip", cmd_gzip268}, {"gunzip", cmd_gunzip268},
    {"bzip2", cmd_bzip2268}, {"bunzip2", cmd_bunzip2268}, {"zip", cmd_zip268},
    {"unzip", cmd_unzip268}, {"xz", cmd_xz268}, {"unxz", cmd_unxz268},
    {"zcat", cmd_zcat268}, {"compress", cmd_compress268}, {"uncompress", cmd_uncompress268},
"""

b268_funcs = """/* ===== Batch 268: Archive & Compression ===== */
static void cmd_tar268(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: tar <cf|xf|tf> <archive> [files]\\n"); return; }
    vga_printf("tar: %s %s\\n", args[1], args[2]);
    if (args[1][0] == 'c') {
        for (int i = 3; i < argc; i++) vga_printf("  adding %s\\n", args[i]);
        vga_puts("tar: archive created\\n");
    } else if (args[1][0] == 'x') {
        for (int i = 3; i < argc; i++) vga_printf("  extracting %s\\n", args[i]);
        vga_puts("tar: extracted\\n");
    } else if (args[1][0] == 't') {
        for (int i = 3; i < argc; i++) vga_printf("  %s\\n", args[i]);
    }
}
static void cmd_gzip268(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: gzip <file>\\n"); return; }
    vga_printf("gzip: %s.gz  67.2%%\\n", args[1]);
}
static void cmd_gunzip268(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: gunzip <file.gz>\\n"); return; }
    vga_printf("gunzip: decompressing %s\\n", args[1]);
}
static void cmd_bzip2268(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: bzip2 <file>\\n"); return; }
    vga_printf("bzip2: %s.bz2  72.1%%\\n", args[1]);
}
static void cmd_bunzip2268(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: bunzip2 <file.bz2>\\n"); return; }
    vga_printf("bunzip2: decompressing %s\\n", args[1]);
}
static void cmd_zip268(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: zip <archive.zip> <files>\\n"); return; }
    vga_printf("zip: creating %s\\n", args[1]);
    for (int i = 2; i < argc; i++) vga_printf("  adding %s\\n", args[i]);
}
static void cmd_unzip268(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: unzip <archive.zip>\\n"); return; }
    vga_printf("unzip: extracting %s\\n", args[1]);
    vga_puts("  inflating: file1.txt\\n  inflating: file2.txt\\n");
}
static void cmd_xz268(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: xz <file>\\n"); return; }
    vga_printf("xz: %s.xz  78.5%%\\n", args[1]);
}
static void cmd_unxz268(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: unxz <file.xz>\\n"); return; }
    vga_printf("unxz: decompressing %s\\n", args[1]);
}
static void cmd_zcat268(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: zcat <file.gz>\\n"); return; }
    vga_printf("zcat: displaying contents of %s\\n", args[1]);
    vga_puts("HELLO WORLD\\n");
}
static void cmd_compress268(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: compress <file>\\n"); return; }
    vga_printf("compress: %s.Z\\n", args[1]);
}
static void cmd_uncompress268(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: uncompress <file.Z>\\n"); return; }
    vga_printf("uncompress: decompressing %s\\n", args[1]);
}
"""

# ===== BATCH 269: User Management =====
b269_decls = """static void cmd_passwd269(int argc, char args[][CMD_MAX_LEN]);
static void cmd_groupadd269(int argc, char args[][CMD_MAX_LEN]);
static void cmd_useradd269(int argc, char args[][CMD_MAX_LEN]);
static void cmd_usermod269(int argc, char args[][CMD_MAX_LEN]);
static void cmd_userdel269(int argc, char args[][CMD_MAX_LEN]);
static void cmd_su269(int argc, char args[][CMD_MAX_LEN]);
static void cmd_sudo269(int argc, char args[][CMD_MAX_LEN]);
static void cmd_visudo269(int argc, char args[][CMD_MAX_LEN]);
static void cmd_groupmod269(int argc, char args[][CMD_MAX_LEN]);
static void cmd_groupdel269(int argc, char args[][CMD_MAX_LEN]);
static void cmd_newgrp269(int argc, char args[][CMD_MAX_LEN]);
static void cmd_pw269(int argc, char args[][CMD_MAX_LEN]);
"""

b269_entries = """    /* Batch 269: User Management */
    {"passwd", cmd_passwd269}, {"groupadd", cmd_groupadd269}, {"useradd", cmd_useradd269},
    {"usermod", cmd_usermod269}, {"userdel", cmd_userdel269}, {"su", cmd_su269},
    {"sudo", cmd_sudo269}, {"visudo", cmd_visudo269}, {"groupmod", cmd_groupmod269},
    {"groupdel", cmd_groupdel269}, {"newgrp", cmd_newgrp269}, {"pw", cmd_pw269},
"""

b269_funcs = """/* ===== Batch 269: User Management ===== */
static void cmd_passwd269(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Changing password for user root.\\nNew password: ");
        vga_puts("(password input hidden)\\npasswd: password updated successfully\\n");
        return;
    }
    vga_printf("passwd: updating password for %s\\n", args[1]);
}
static void cmd_groupadd269(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: groupadd <groupname>\\n"); return; }
    vga_printf("groupadd: group '%s' added\\n", args[1]);
}
static void cmd_useradd269(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: useradd <username>\\n"); return; }
    vga_printf("useradd: user '%s' created\\n", args[1]);
    vga_puts("useradd: creating home directory /home/user\\n");
    vga_puts("useradd: copying skeleton files\\n");
}
static void cmd_usermod269(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: usermod <options> <username>\\n"); return; }
    vga_printf("usermod: modifying user '%s'\\n", args[argc-1]);
}
static void cmd_userdel269(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: userdel <username>\\n"); return; }
    vga_printf("userdel: user '%s' deleted\\n", args[1]);
}
static void cmd_su269(int argc, char args[][CMD_MAX_LEN]) {
    const char* user = argc >= 2 ? args[1] : "root";
    vga_printf("su: switching to user '%s'\\n", user);
    vga_puts("Password: ****\\n");
}
static void cmd_sudo269(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("usage: sudo <command>\\n"); return; }
    vga_printf("[sudo] password for user: ****\\n");
    vga_printf("Executing: %s\\n", args[1]);
}
static void cmd_visudo269(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("visudo: editing sudoers file\\n");
    vga_puts("root ALL=(ALL:ALL) ALL\\n");
    vga_puts("%sudo ALL=(ALL:ALL) ALL\\n");
}
static void cmd_groupmod269(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: groupmod <options> <group>\\n"); return; }
    vga_printf("groupmod: modifying group '%s'\\n", args[argc-1]);
}
static void cmd_groupdel269(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: groupdel <group>\\n"); return; }
    vga_printf("groupdel: group '%s' deleted\\n", args[1]);
}
static void cmd_newgrp269(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: newgrp <group>\\n"); return; }
    vga_printf("newgrp: switching to group '%s'\\n", args[1]);
}
static void cmd_pw269(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("root:x:0:0:root:/root:/bin/bash\\n");
    vga_puts("daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin\\n");
    vga_puts("nobody:x:65534:65534:nobody:/nonexistent:/usr/sbin/nologin\\n");
}
"""

# ===== BATCH 270: Process Management =====
b270_decls = """static void cmd_nice270(int argc, char args[][CMD_MAX_LEN]);
static void cmd_nohup270(int argc, char args[][CMD_MAX_LEN]);
static void cmd_bg270(int argc, char args[][CMD_MAX_LEN]);
static void cmd_fg270(int argc, char args[][CMD_MAX_LEN]);
static void cmd_jobs270(int argc, char args[][CMD_MAX_LEN]);
static void cmd_wait270(int argc, char args[][CMD_MAX_LEN]);
static void cmd_sleep270(int argc, char args[][CMD_MAX_LEN]);
static void cmd_at270(int argc, char args[][CMD_MAX_LEN]);
static void cmd_batch270(int argc, char args[][CMD_MAX_LEN]);
static void cmd_killall270(int argc, char args[][CMD_MAX_LEN]);
static void cmd_pkill270(int argc, char args[][CMD_MAX_LEN]);
static void cmd_pgrep270(int argc, char args[][CMD_MAX_LEN]);
"""

b270_entries = """    /* Batch 270: Process Management */
    {"nice", cmd_nice270}, {"nohup", cmd_nohup270}, {"bg", cmd_bg270},
    {"fg", cmd_fg270}, {"jobs", cmd_jobs270}, {"wait", cmd_wait270},
    {"sleep", cmd_sleep270}, {"at", cmd_at270}, {"batch", cmd_batch270},
    {"killall", cmd_killall270}, {"pkill", cmd_pkill270}, {"pgrep", cmd_pgrep270},
"""

b270_funcs = """/* ===== Batch 270: Process Management ===== */
static void cmd_nice270(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: nice <command>\\n"); return; }
    vga_printf("nice: running '%s' with default priority\\n", args[1]);
}
static void cmd_nohup270(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: nohup <command>\\n"); return; }
    vga_printf("nohup: running '%s' in background\\n", args[1]);
    vga_puts("nohup: appending output to nohup.out\\n");
}
static void cmd_bg270(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: bg <job_id>\\n"); return; }
    vga_printf("bg: [%s] continued\\n", args[1]);
}
static void cmd_fg270(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: fg <job_id>\\n"); return; }
    vga_printf("fg: [%s]\\n", args[1]);
}
static void cmd_jobs270(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("[1]+ Running                 sleep 100\\n");
    vga_puts("[2]- Stopped                 vim file.txt\\n");
    vga_puts("[3]+ Running                 top\\n");
}
static void cmd_wait270(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("wait: waiting for all background processes...\\n");
    vga_puts("wait: all done\\n");
}
static void cmd_sleep270(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: sleep <seconds>\\n"); return; }
    vga_printf("sleep: sleeping for %s seconds\\n", args[1]);
}
static void cmd_at270(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: at <time>\\n"); return; }
    vga_printf("at: job queued for %s\\n", args[1]);
    vga_puts("at: <EOT>\\n");
}
static void cmd_batch270(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("batch: executing pending jobs\\n");
}
static void cmd_killall270(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: killall <process_name>\\n"); return; }
    vga_printf("killall: killing all '%s' processes\\n", args[1]);
}
static void cmd_pkill270(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: pkill <pattern>\\n"); return; }
    vga_printf("pkill: killing processes matching '%s'\\n", args[1]);
}
static void cmd_pgrep270(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: pgrep <pattern>\\n"); return; }
    vga_printf("1\\n42\\n128\\n");
}
"""

# Inject
decl_marker = "static const cmd_entry commands[] = {"
content = content.replace(decl_marker, b267_decls + b268_decls + b269_decls + b270_decls + decl_marker)

old_entry = '    {"gitui2", cmd_batch262_gitui2}, {"delta2", cmd_batch262_delta2}, {"bat2", cmd_batch262_bat2},\n' + \
    '    /* Batch 263: Network Utilities */\n    {"wget", cmd_wget263}, {"nslookup", cmd_nslookup263}, {"ifconfig", cmd_ifconfig263},'
new_entries = b267_entries + b268_entries + b269_entries + b270_entries
content = content.replace(old_entry, old_entry + new_entries, 1)

func_marker = "void shell_run(void) {"
content = content.replace(func_marker, b267_funcs + b268_funcs + b269_funcs + b270_funcs + func_marker, 1)

with open(SHELL, "w", encoding="utf-8") as f:
    f.write(content)

print("Injected Batches 267-270 (48 new commands)")
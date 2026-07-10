# inject_299_302.py
SHELL = "kernel/shell.c"
with open(SHELL, "r", encoding="utf-8", errors="replace") as f:
    content = f.read()

# ===== BATCH 299: System Maintenance =====
b299_decls = """static void cmd_apt299(int argc, char args[][CMD_MAX_LEN]);
static void cmd_yum299(int argc, char args[][CMD_MAX_LEN]);
static void cmd_dnf299(int argc, char args[][CMD_MAX_LEN]);
static void cmd_pacman299(int argc, char args[][CMD_MAX_LEN]);
static void cmd_zypper299(int argc, char args[][CMD_MAX_LEN]);
static void cmd_emerge299(int argc, char args[][CMD_MAX_LEN]);
static void cmd_snap299(int argc, char args[][CMD_MAX_LEN]);
static void cmd_flatpak299(int argc, char args[][CMD_MAX_LEN]);
static void cmd_brew299(int argc, char args[][CMD_MAX_LEN]);
static void cmd_nix299(int argc, char args[][CMD_MAX_LEN]);
static void cmd_conda299(int argc, char args[][CMD_MAX_LEN]);
static void cmd_pip299(int argc, char args[][CMD_MAX_LEN]);
"""

b299_entries = """    /* Batch 299: Package Managers */
    {"apt", cmd_apt299}, {"yum", cmd_yum299}, {"dnf", cmd_dnf299},
    {"pacman", cmd_pacman299}, {"zypper", cmd_zypper299}, {"emerge", cmd_emerge299},
    {"snap", cmd_snap299}, {"flatpak", cmd_flatpak299}, {"brew", cmd_brew299},
    {"nix", cmd_nix299}, {"conda", cmd_conda299}, {"pip", cmd_pip299},
"""

b299_funcs = """/* ===== Batch 299: Package Managers ===== */
static void cmd_apt299(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: apt <install|update|remove>\\n"); return; }
    if (strcmp(args[1], "update") == 0) vga_puts("apt: updating package lists...\\napt: done\\n");
    else if (strcmp(args[1], "install") == 0) vga_printf("apt: installing %s\\n", argc > 2 ? args[2] : "?");
    else vga_printf("apt: %s\\n", args[1]);
}
static void cmd_yum299(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: yum <install|update|remove>\\n"); return; }
    vga_printf("yum: %s\\n", args[1]);
}
static void cmd_dnf299(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: dnf <install|update|remove>\\n"); return; }
    vga_printf("dnf: %s\\n", args[1]);
}
static void cmd_pacman299(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: pacman <-S|-R|-Q>\\n"); return; }
    vga_printf("pacman: %s\\n", args[1]);
}
static void cmd_zypper299(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: zypper <install|remove>\\n"); return; }
    vga_printf("zypper: %s\\n", args[1]);
}
static void cmd_emerge299(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: emerge <package>\\n"); return; }
    vga_printf("emerge: %s\\n", args[1]);
}
static void cmd_snap299(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: snap <install|list>\\n"); return; }
    if (strcmp(args[1], "list") == 0) vga_puts("Name    Version  Publisher\\nfirefox 120.0    mozilla\\n");
    else vga_printf("snap: %s\\n", args[1]);
}
static void cmd_flatpak299(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: flatpak <install|list>\\n"); return; }
    vga_printf("flatpak: %s\\n", args[1]);
}
static void cmd_brew299(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: brew <install|list>\\n"); return; }
    if (strcmp(args[1], "list") == 0) vga_puts("python  git  node  wget\\n");
    else vga_printf("brew: %s\\n", args[1]);
}
static void cmd_nix299(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: nix <install|env>\\n"); return; }
    vga_printf("nix: %s\\n", args[1]);
}
static void cmd_conda299(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: conda <install|create>\\n"); return; }
    vga_printf("conda: %s\\n", args[1]);
}
static void cmd_pip299(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: pip <install|list>\\n"); return; }
    if (strcmp(args[1], "list") == 0) vga_puts("Package    Version\\nnumpy      1.24.0\\npandas     2.0.0\\n");
    else vga_printf("pip: %s\\n", args[1]);
}
"""

# ===== BATCH 300: Compilers & Interpreters =====
b300_decls = """static void cmd_gcc300(int argc, char args[][CMD_MAX_LEN]);
static void cmd_clang300(int argc, char args[][CMD_MAX_LEN]);
static void cmd_tcc300(int argc, char args[][CMD_MAX_LEN]);
static void cmd_dmc300(int argc, char args[][CMD_MAX_LEN]);
static void cmd_pascal300(int argc, char args[][CMD_MAX_LEN]);
static void cmd_fpc300(int argc, char args[][CMD_MAX_LEN]);
static void cmd_javac300(int argc, char args[][CMD_MAX_LEN]);
static void cmd_kotlinc300(int argc, char args[][CMD_MAX_LEN]);
static void cmd_scalac300(int argc, char args[][CMD_MAX_LEN]);
static void cmd_swc300(int argc, char args[][CMD_MAX_LEN]);
static void cmd_esbuild300(int argc, char args[][CMD_MAX_LEN]);
static void cmd_sass300(int argc, char args[][CMD_MAX_LEN]);
"""

b300_entries = """    /* Batch 300: Compilers & Interpreters */
    {"gcc2", cmd_gcc300}, {"clang", cmd_clang300}, {"tcc", cmd_tcc300},
    {"dmc", cmd_dmc300}, {"fpc", cmd_fpc300}, {"pascal", cmd_pascal300},
    {"javac", cmd_javac300}, {"kotlinc", cmd_kotlinc300}, {"scalac", cmd_scalac300},
    {"swc", cmd_swc300}, {"esbuild", cmd_esbuild300}, {"sass", cmd_sass300},
"""

b300_funcs = """/* ===== Batch 300: Compilers & Interpreters ===== */
static void cmd_gcc300(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: gcc <file.c>\\n"); return; }
    vga_printf("gcc: compiling %s\\n", args[1]);
}
static void cmd_clang300(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: clang <file.c>\\n"); return; }
    vga_printf("clang: compiling %s\\n", args[1]);
}
static void cmd_tcc300(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: tcc <file.c>\\n"); return; }
    vga_printf("tcc: compiling %s\\n", args[1]);
}
static void cmd_dmc300(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: dmc <file.c>\\n"); return; }
    vga_printf("dmc: compiling %s\\n", args[1]);
}
static void cmd_fpc300(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: fpc <file.pas>\\n"); return; }
    vga_printf("fpc: compiling %s\\n", args[1]);
}
static void cmd_pascal300(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: pascal <file.pas>\\n"); return; }
    vga_printf("pascal: compiling %s\\n", args[1]);
}
static void cmd_javac300(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: javac <file.java>\\n"); return; }
    vga_printf("javac: compiling %s\\n", args[1]);
}
static void cmd_kotlinc300(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: kotlinc <file.kt>\\n"); return; }
    vga_printf("kotlinc: compiling %s\\n", args[1]);
}
static void cmd_scalac300(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: scalac <file.scala>\\n"); return; }
    vga_printf("scalac: compiling %s\\n", args[1]);
}
static void cmd_swc300(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: swc <file>\\n"); return; }
    vga_printf("swc: transpiling %s\\n", args[1]);
}
static void cmd_esbuild300(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: esbuild <file>\\n"); return; }
    vga_printf("esbuild: bundling %s\\n", args[1]);
}
static void cmd_sass300(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: sass <file.scss>\\n"); return; }
    vga_printf("sass: compiling %s\\n", args[1]);
}
"""

# ===== BATCH 301: Network Protocols =====
b301_decls = """static void cmd_ftp2301(int argc, char args[][CMD_MAX_LEN]);
static void cmd_sftp301(int argc, char args[][CMD_MAX_LEN]);
static void cmd_rsync2301(int argc, char args[][CMD_MAX_LEN]);
static void cmd_scp2301(int argc, char args[][CMD_MAX_LEN]);
static void cmd_aria2c301(int argc, char args[][CMD_MAX_LEN]);
static void cmd_curl2301(int argc, char args[][CMD_MAX_LEN]);
static void cmd_wget2301(int argc, char args[][CMD_MAX_LEN]);
static void cmd_axel301(int argc, char args[][CMD_MAX_LEN]);
static void cmd_lftp301(int argc, char args[][CMD_MAX_LEN]);
static void cmd_nntp301(int argc, char args[][CMD_MAX_LEN]);
static void cmd_irc301(int argc, char args[][CMD_MAX_LEN]);
static void cmd_xmpp301(int argc, char args[][CMD_MAX_LEN]);
"""

b301_entries = """    /* Batch 301: Network Protocols */
    {"ftp2", cmd_ftp2301}, {"sftp", cmd_sftp301}, {"rsync2", cmd_rsync2301},
    {"scp", cmd_scp2301}, {"aria2c", cmd_aria2c301}, {"curl3", cmd_curl2301},
    {"wget3", cmd_wget2301}, {"axel", cmd_axel301}, {"lftp", cmd_lftp301},
    {"nntp", cmd_nntp301}, {"irc", cmd_irc301}, {"xmpp", cmd_xmpp301},
"""

b301_funcs = """/* ===== Batch 301: Network Protocols ===== */
static void cmd_ftp2301(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: ftp <host>\\n"); return; }
    vga_printf("ftp: connecting to %s\\n", args[1]);
}
static void cmd_sftp301(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: sftp <host>\\n"); return; }
    vga_printf("sftp: connecting to %s\\n", args[1]);
}
static void cmd_rsync2301(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: rsync <src> <dst>\\n"); return; }
    vga_printf("rsync: %s -> %s\\n", args[1], args[2]);
}
static void cmd_scp2301(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: scp <src> <dst>\\n"); return; }
    vga_printf("scp: %s -> %s\\n", args[1], args[2]);
}
static void cmd_aria2c301(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: aria2c <url>\\n"); return; }
    vga_printf("aria2c: downloading %s\\n", args[1]);
}
static void cmd_curl2301(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: curl <url>\\n"); return; }
    vga_printf("curl: fetching %s\\n", args[1]);
}
static void cmd_wget2301(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: wget <url>\\n"); return; }
    vga_printf("wget: downloading %s\\n", args[1]);
}
static void cmd_axel301(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: axel <url>\\n"); return; }
    vga_printf("axel: downloading %s\\n", args[1]);
}
static void cmd_lftp301(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: lftp <host>\\n"); return; }
    vga_printf("lftp: connecting to %s\\n", args[1]);
}
static void cmd_nntp301(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("nntp: network news transfer protocol\\n");
}
static void cmd_irc301(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("irc: internet relay chat\\n");
}
static void cmd_xmpp301(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("xmpp: extensible messaging protocol\\n");
}
"""

# ===== BATCH 302: Encryption & Crypto =====
b302_decls = """static void cmd_openssl2302(int argc, char args[][CMD_MAX_LEN]);
static void cmd_gpg2302(int argc, char args[][CMD_MAX_LEN]);
static void cmd_ssh2302(int argc, char args[][CMD_MAX_LEN]);
static void cmd_scp2302(int argc, char args[][CMD_MAX_LEN]);
static void cmd_sftp2302(int argc, char args[][CMD_MAX_LEN]);
static void_cmd_keychain2302(int argc, char args[][CMD_MAX_LEN]);
static void cmd_keyctl2302(int argc, char args[][CMD_MAX_LEN]);
static void cmd_seahorse2302(int argc, char args[][CMD_MAX_LEN]);
static void_cmd_keybase2302(int argc, char args[][CMD_MAX_LEN]);
static void cmd_gocryptfs2302(int argc, char args[][CMD_MAX_LEN]);
static void cmd_veracrypt2302(int argc, char args[][CMD_MAX_LEN]);
static void cmd_cryptsetup2302(int argc, char args[][CMD_MAX_LEN]);
"""

b302_entries = """    /* Batch 302: Encryption & Crypto */
    {"openssl2", cmd_openssl2302}, {"gpg2", cmd_gpg2302}, {"ssh", cmd_ssh2302},
    {"scp2", cmd_scp2302}, {"sftp2", cmd_sftp2302}, {"keychain", cmd_keychain2302},
    {"keyctl", cmd_keyctl2302}, {"seahorse", cmd_seahorse2302}, {"keybase", cmd_keybase2302},
    {"gocryptfs", cmd_gocryptfs2302}, {"veracrypt", cmd_veracrypt2302}, {"cryptsetup", cmd_cryptsetup2302},
"""

b302_funcs = """/* ===== Batch 302: Encryption & Crypto ===== */
static void cmd_openssl2302(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: openssl <command>\\n"); return; }
    vga_printf("openssl: %s\\n", args[1]);
}
static void cmd_gpg2302(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: gpg <options>\\n"); return; }
    vga_printf("gpg: %s\\n", args[1]);
}
static void cmd_ssh2302(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: ssh <host>\\n"); return; }
    vga_printf("ssh: connecting to %s\\n", args[1]);
}
static void cmd_scp2302(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: scp <src> <dst>\\n"); return; }
    vga_printf("scp: %s -> %s\\n", args[1], args[2]);
}
static void cmd_sftp2302(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: sftp <host>\\n"); return; }
    vga_printf("sftp: connecting to %s\\n", args[1]);
}
static void cmd_keychain2302(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("keychain: SSH/GPG agent manager\\n");
}
static void cmd_keyctl2302(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("keyctl: kernel key management\\n");
}
static void cmd_seahorse2302(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Seahorse: password & key manager\\n");
}
static void cmd_keybase2302(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Keybase: encrypted messaging\\n");
}
static void cmd_gocryptfs2302(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: gocryptfs <dir>\\n"); return; }
    vga_printf("gocryptfs: mounting encrypted %s\\n", args[1]);
}
static void cmd_veracrypt2302(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("VeraCrypt: disk encryption\\n");
}
static void cmd_cryptsetup2302(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: cryptsetup <open|close>\\n"); return; }
    vga_printf("cryptsetup: %s\\n", args[1]);
}
"""

# Fix syntax errors
b302_decls = b302_decls.replace("static void_cmd_", "static void cmd_")
b301_decls = b301_decls.replace("static void_cmd_", "static void cmd_")

# Inject
decl_marker = "static const cmd_entry commands[] = {"
content = content.replace(decl_marker, b299_decls + b300_decls + b301_decls + b302_decls + decl_marker)

old_entry = '    {"gitui2", cmd_batch262_gitui2}, {"delta2", cmd_batch262_delta2}, {"bat2", cmd_batch262_bat2},\n' + \
    '    /* Batch 263: Network Utilities */'
new_entries = b299_entries + b300_entries + b301_entries + b302_entries
content = content.replace(old_entry, old_entry + new_entries, 1)

func_marker = "void shell_run(void) {"
content = content.replace(func_marker, b299_funcs + b300_funcs + b301_funcs + b302_funcs + func_marker, 1)

with open(SHELL, "w", encoding="utf-8") as f:
    f.write(content)
print("Injected Batches 299-302 (48 new commands)")
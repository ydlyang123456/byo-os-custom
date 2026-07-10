# inject_303_306.py
SHELL = "kernel/shell.c"
with open(SHELL, "r", encoding="utf-8", errors="replace") as f:
    content = f.read()

# ===== BATCH 303: More Dev Tools =====
b303_decls = """static void cmd_git303(int argc, char args[][CMD_MAX_LEN]);
static void cmd_svn303(int argc, char args[][CMD_MAX_LEN]);
static void cmd_hg303(int argc, char args[][CMD_MAX_LEN]);
static void cmd_bzr303(int argc, char args[][CMD_MAX_LEN]);
static void cmd_cvs303(int argc, char args[][CMD_MAX_LEN]);
static void_cmd_fossil303(int argc, char args[][CMD_MAX_LEN]);
static void cmd_darcs303(int argc, char args[][CMD_MAX_LEN]);
static void cmd_monotone303(int argc, char args[][CMD_MAX_LEN]);
static void cmd_veracity303(int argc, char args[][CMD_MAX_LEN]);
static void cmd_tfs303(int argc, char args[][CMD_MAX_LEN]);
static void_cmd_perforce303(int argc, char args[][CMD_MAX_LEN]);
static void cmd_clearcase303(int argc, char args[][CMD_MAX_LEN]);
"""

b303_entries = """    /* Batch 303: Version Control */
    {"git3", cmd_git303}, {"svn", cmd_svn303}, {"hg", cmd_hg303},
    {"bzr", cmd_bzr303}, {"cvs", cmd_cvs303}, {"fossil2", cmd_fossil303},
    {"darcs", cmd_darcs303}, {"monotone", cmd_monotone303}, {"veracity", cmd_veracity303},
    {"tfs", cmd_tfs303}, {"p4", cmd_perforce303}, {"cleartool", cmd_clearcase303},
"""

b303_funcs = """/* ===== Batch 303: Version Control ===== */
static void cmd_git303(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: git <command>\\n"); return; }
    vga_printf("git: %s\\n", args[1]);
}
static void cmd_svn303(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: svn <command>\\n"); return; }
    vga_printf("svn: %s\\n", args[1]);
}
static void cmd_hg303(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: hg <command>\\n"); return; }
    vga_printf("hg: %s\\n", args[1]);
}
static void cmd_bzr303(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: bzr <command>\\n"); return; }
    vga_printf("bzr: %s\\n", args[1]);
}
static void cmd_cvs303(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: cvs <command>\\n"); return; }
    vga_printf("cvs: %s\\n", args[1]);
}
static void cmd_fossil303(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: fossil <command>\\n"); return; }
    vga_printf("fossil: %s\\n", args[1]);
}
static void cmd_darcs303(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("darcs: patch-based VCS\\n");
}
static void cmd_monotone303(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("monotone: distributed VCS\\n");
}
static void cmd_veracity303(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("veracity: distributed VCS\\n");
}
static void cmd_tfs303(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("TFS: Team Foundation Server\\n");
}
static void cmd_perforce303(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Perforce: version control\\n");
}
static void cmd_clearcase303(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("ClearCase: version control\\n");
}
"""

# ===== BATCH 304: More System =====
b304_decls = """static void cmd_systemd304(int argc, char args[][CMD_MAX_LEN]);
static void_cmd_sysvinit304(int argc, char args[][CMD_MAX_LEN]);
static void cmd_openrc304(int argc, char args[][CMD_MAX_LEN]);
static void cmd_runit304(int argc, char args[][CMD_MAX_LEN]);
static void_cmd_s6304(int argc, char args[][CMD_MAX_LEN]);
static void cmd_nginx2304(int argc, char args[][CMD_MAX_LEN]);
static void cmd_apache2304(int argc, char args[][CMD_MAX_LEN]);
static void cmd_lighttpd304(int argc, char args[][CMD_MAX_LEN]);
static void cmd_cherokee304(int argc, char args[][CMD_MAX_LEN]);
static void cmd_tengine304(int argc, char args[][CMD_MAX_LEN]);
static void cmd_openresty304(int argc, char args[][CMD_MAX_LEN]);
static void cmd_h2o304(int argc, char args[][CMD_MAX_LEN]);
"""

b304_entries = """    /* Batch 304: System Init & Web */
    {"systemd2", cmd_systemd304}, {"sysvinit", cmd_sysvinit304}, {"openrc", cmd_openrc304},
    {"runit", cmd_runit304}, {"s6", cmd_s6304}, {"nginx3", cmd_nginx2304},
    {"apache3", cmd_apache2304}, {"lighttpd", cmd_lighttpd304}, {"cherokee", cmd_cherokee304},
    {"tengine", cmd_tengine304}, {"openresty", cmd_openresty304}, {"h2o", cmd_h2o304},
"""

b304_funcs = """/* ===== Batch 304: System Init & Web ===== */
static void cmd_systemd304(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: systemd <command>\\n"); return; }
    vga_printf("systemd: %s\\n", args[1]);
}
static void cmd_sysvinit304(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("SysVinit: classic init\\n");
}
static void cmd_openrc304(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("OpenRC: init system\\n");
}
static void cmd_runit304(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("runit: init system\\n");
}
static void cmd_s6304(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("s6: process supervision\\n");
}
static void cmd_nginx2304(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: nginx <start|stop|reload>\\n"); return; }
    vga_printf("nginx: %s\\n", args[1]);
}
static void cmd_apache2304(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: apache2 <start|stop|reload>\\n"); return; }
    vga_printf("apache2: %s\\n", args[1]);
}
static void cmd_lighttpd304(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("lighttpd: web server\\n");
}
static void cmd_cherokee304(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Cherokee: web server\\n");
}
static void cmd_tengine304(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Tengine: Nginx fork\\n");
}
static void cmd_openresty304(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("OpenResty: Nginx + Lua\\n");
}
static void cmd_h2o304(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("H2O: HTTP/2 web server\\n");
}
"""

# ===== BATCH 305: Cloud SDK =====
b305_decls = """static void cmd_aws2305(int argc, char args[][CMD_MAX_LEN]);
static void cmd_gcloud2305(int argc, char args[][CMD_MAX_LEN]);
static void cmd_azure2305(int argc, char args[][CMD_MAX_LEN]);
static void cmd_do2305(int argc, char args[][CMD_MAX_LEN]);
static void cmd_linode2305(int argc, char args[][CMD_MAX_LEN]);
static void cmd_vultr2305(int argc, char args[][CMD_MAX_LEN]);
static void cmd_hetzner2305(int argc, char args[][CMD_MAX_LEN]);
static void cmd_ovh2305(int argc, char args[][CMD_MAX_LEN]);
static void cmd_scaleway2305(int argc, char args[][CMD_MAX_LEN]);
static void cmd_koyeb2305(int argc, char args[][CMD_MAX_LEN]);
static void cmd_render2305(int argc, char args[][CMD_MAX_LEN]);
static void cmd_fly2305(int argc, char args[][CMD_MAX_LEN]);
"""

b305_entries = """    /* Batch 305: Cloud SDK */
    {"aws2", cmd_aws2305}, {"gcloud2", cmd_gcloud2305}, {"azure2", cmd_azure2305},
    {"doctl", cmd_do2305}, {"linode", cmd_linode2305}, {"vultr", cmd_vultr2305},
    {"hcloud", cmd_hetzner2305}, {"ovh", cmd_ovh2305}, {"scw", cmd_scaleway2305},
    {"koyeb", cmd_koyeb2305}, {"render", cmd_render2305}, {"flyctl", cmd_fly2305},
"""

b305_funcs = """/* ===== Batch 305: Cloud SDK ===== */
static void cmd_aws2305(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: aws <command>\\n"); return; }
    vga_printf("aws: %s\\n", args[1]);
}
static void cmd_gcloud2305(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: gcloud <command>\\n"); return; }
    vga_printf("gcloud: %s\\n", args[1]);
}
static void cmd_azure2305(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: az <command>\\n"); return; }
    vga_printf("az: %s\\n", args[1]);
}
static void cmd_do2305(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: doctl <command>\\n"); return; }
    vga_printf("doctl: %s\\n", args[1]);
}
static void cmd_linode2305(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Linode: cloud computing\\n");
}
static void cmd_vultr2305(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Vultr: cloud computing\\n");
}
static void cmd_hetzner2305(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Hetzner: cloud computing\\n");
}
static void cmd_ovh2305(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("OVH: cloud computing\\n");
}
static void cmd_scaleway2305(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Scaleway: cloud computing\\n");
}
static void cmd_koyeb2305(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Koyeb: serverless platform\\n");
}
static void cmd_render2305(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Render: cloud application platform\\n");
}
static void cmd_fly2305(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Fly.io: edge computing\\n");
}
"""

# ===== BATCH 306: More Misc =====
b306_decls = """static void cmd_todo2306(int argc, char args[][CMD_MAX_LEN]);
static void cmd_taskwarrior306(int argc, char args[][CMD_MAX_LEN]);
static void cmd_bubble306wrap(int argc, char args[][CMD_MAX_LEN]);
static void_cmd_timers306(int argc, char args[][CMD_MAX_LEN]);
static void cmd_chaos306(int argc, char args[][CMD_MAX_LEN]);
static void cmd_litmus306(int argc, char args[][CMD_MAX_LEN]);
static void cmd_k6306(int argc, char args[][CMD_MAX_LEN]);
static void cmd_locust306(int argc, char args[][CMD_MAX_LEN]);
static void cmd_vegeta306(int argc, char args[][CMD_MAX_LEN]);
static void_cmd_wrk306(int argc, char args[][CMD_MAX_LEN]);
static void cmd_ab306(int argc, char args[][CMD_MAX_LEN]);
static void cmd_siege306(int argc, char args[][CMD_MAX_LEN]);
"""

b306_entries = """    /* Batch 306: Testing & Load */
    {"todo", cmd_todo2306}, {"task", cmd_taskwarrior306}, {"timers", cmd_timers306},
    {"chaos", cmd_chaos306}, {"litmus", cmd_litmus306}, {"k6", cmd_k6306},
    {"locust", cmd_locust306}, {"vegeta", cmd_vegeta306}, {"wrk", cmd_wrk306},
    {"ab", cmd_ab306}, {"siege", cmd_siege306}, {"bombardier", cmd_bombardier306},
"""

b306_funcs = """/* ===== Batch 306: Testing & Load ===== */
static void cmd_todo2306(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: todo <list|add|done>\\n"); return; }
    vga_printf("todo: %s\\n", args[1]);
}
static void cmd_taskwarrior306(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: task <add|list|done>\\n"); return; }
    vga_printf("task: %s\\n", args[1]);
}
static void cmd_timers306(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("timers: system timers\\n");
}
static void cmd_chaos306(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Chaos: chaos engineering\\n");
}
static void cmd_litmus306(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Litmus: chaos engineering\\n");
}
static void cmd_k6306(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("k6: load testing\\n");
    vga_puts("k6: 100 VUs, 30s duration\\n");
}
static void cmd_locust306(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Locust: load testing\\n");
    vga_puts("locust: 50 users, 2s hatch rate\\n");
}
static void cmd_vegeta306(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Vegeta: HTTP load testing\\n");
}
static void cmd_wrk306(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("wrk: HTTP benchmarking\\n");
}
static void cmd_ab306(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("ab: Apache HTTP server benchmarking\\n");
}
static void cmd_siege306(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Siege: HTTP load testing\\n");
}
"""

# Fix syntax errors
b303_decls = b303_decls.replace("static void_cmd_", "static void cmd_")
b304_decls = b304_decls.replace("static void_cmd_", "static void cmd_")
b305_decls = b305_decls.replace("static void_cmd_", "static void cmd_")
b306_decls = b306_decls.replace("static void_cmd_", "static void cmd_")
b306_decls = b306_decls.replace("static void cmd_bubble306wrap", "static void cmd_bubblewrap306")
b306_entries = b306_entries.replace("bombardier", "bombardier")
b306_funcs = b306_funcs.replace("cmd_bombardier306", "cmd_bombardier306")

# Inject
decl_marker = "static const cmd_entry commands[] = {"
content = content.replace(decl_marker, b303_decls + b304_decls + b305_decls + b306_decls + decl_marker)

old_entry = '    {"gitui2", cmd_batch262_gitui2}, {"delta2", cmd_batch262_delta2}, {"bat2", cmd_batch262_bat2},\n' + \
    '    /* Batch 263: Network Utilities */'
new_entries = b303_entries + b304_entries + b305_entries + b306_entries
content = content.replace(old_entry, old_entry + new_entries, 1)

func_marker = "void shell_run(void) {"
content = content.replace(func_marker, b303_funcs + b304_funcs + b305_funcs + b306_funcs + func_marker, 1)

with open(SHELL, "w", encoding="utf-8") as f:
    f.write(content)
print("Injected Batches 303-306 (48 new commands)")
# inject_275_278.py - Database, Networking, Media, Misc Tools
SHELL = "kernel/shell.c"
with open(SHELL, "r", encoding="utf-8", errors="replace") as f:
    content = f.read()

# ===== BATCH 275: Database Tools =====
b275_decls = """static void cmd_mysql275(int argc, char args[][CMD_MAX_LEN]);
static void cmd_psql275(int argc, char args[][CMD_MAX_LEN]);
static void cmd_redis275(int argc, char args[][CMD_MAX_LEN]);
static void cmd_mongo275(int argc, char args[][CMD_MAX_LEN]);
static void cmd_sqlite3275(int argc, char args[][CMD_MAX_LEN]);
static void cmd_pg_dump275(int argc, char args[][CMD_MAX_LEN]);
static void cmd_mysqldump275(int argc, char args[][CMD_MAX_LEN]);
static void cmd_pg_restore275(int argc, char args[][CMD_MAX_LEN]);
static void cmd_redis_cli275(int argc, char args[][CMD_MAX_LEN]);
static void cmd_pgbouncer275(int argc, char args[][CMD_MAX_LEN]);
static void cmd_elasticsearch275(int argc, char args[][CMD_MAX_LEN]);
static void cmd_kibana275(int argc, char args[][CMD_MAX_LEN]);
"""

b275_entries = """    /* Batch 275: Database Tools */
    {"mysql", cmd_mysql275}, {"psql", cmd_psql275}, {"redis-cli2", cmd_redis275},
    {"mongo", cmd_mongo275}, {"sqlite3", cmd_sqlite3275}, {"pg_dump", cmd_pg_dump275},
    {"mysqldump", cmd_mysqldump275}, {"pg_restore", cmd_pg_restore275}, {"redis-cli", cmd_redis_cli275},
    {"pgbouncer", cmd_pgbouncer275}, {"elasticsearch", cmd_elasticsearch275}, {"kibana", cmd_kibana275},
"""

b275_funcs = """/* ===== Batch 275: Database Tools ===== */
static void cmd_mysql275(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: mysql <database>\\n"); return; }
    vga_printf("mysql: connecting to %s...\\n", args[1]);
    vga_puts("Welcome to MySQL 8.0.\\n");
    vga_puts("mysql> SELECT VERSION();\\n+--------+\\n| 8.0.35 |\\n+--------+\\n");
}
static void cmd_psql275(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: psql <database>\\n"); return; }
    vga_printf("psql: connecting to %s...\\n", args[1]);
    vga_puts("psql (15.3)\\nType \\\\"help for help.\\n");
    vga_puts("db=# SELECT version();\\n                             version\\n------------------------------------------------------------------------------\\n PostgreSQL 15.3\\n");
}
static void cmd_redis275(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("redis-cli: connecting to 127.0.0.1:6379\\n");
    vga_puts("redis> PING\\nPONG\\nredis> SET hello world\\nOK\\n");
}
static void cmd_mongo275(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("mongo: connecting to mongodb://localhost:27017\\n");
    vga_puts("MongoDB shell v6.0.4\\n> db.runCommand({ping:1})\\n{ ok: 1 }\\n");
}
static void cmd_sqlite3275(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: sqlite3 <database>\\n"); return; }
    vga_printf("sqlite3: opening %s\\n", args[1]);
    vga_puts("SQLite version 3.40.0\\n");
    vga_puts("sqlite> .tables\\ntables: users items logs\\n");
}
static void cmd_pg_dump275(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: pg_dump <database>\\n"); return; }
    vga_printf("pg_dump: dumping %s\\n", args[1]);
    vga_puts("pg_dump: dumping table users...\\npg_dump: complete\\n");
}
static void cmd_mysqldump275(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: mysqldump <database>\\n"); return; }
    vga_printf("mysqldump: dumping %s\\n", args[1]);
    vga_puts("mysqldump: complete\\n");
}
static void cmd_pg_restore275(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: pg_restore <dumpfile>\\n"); return; }
    vga_printf("pg_restore: restoring from %s\\n", args[1]);
    vga_puts("pg_restore: restore complete\\n");
}
static void cmd_redis_cli275(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("redis-cli: 127.0.0.1:6379>\\n");
    vga_puts("redis> INFO server\\n# Server\\nredis_version:7.0.0\\n");
}
static void cmd_pgbouncer275(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("pgbouncer: PostgreSQL connection pooler\\n");
    vga_puts("pgbouncer: listening on 127.0.0.1:6432\\n");
}
static void cmd_elasticsearch275(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("elasticsearch: distributed search engine\\n");
    vga_puts("elasticsearch: cluster health: green\\n");
}
static void cmd_kibana275(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("kibana: data visualization dashboard\\n");
    vga_puts("kibana: listening on http://localhost:5601\\n");
}
"""

# ===== BATCH 276: Network Services =====
b276_decls = """static void cmd_nginx276(int argc, char args[][CMD_MAX_LEN]);
static void cmd_apache2276(int argc, char args[][CMD_MAX_LEN]);
static void cmd_caddy276(int argc, char args[][CMD_MAX_LEN]);
static void cmd_haproxy276(int argc, char args[][CMD_MAX_LEN]);
static void cmd_bind9276(int argc, char args[][CMD_MAX_LEN]);
static void cmd_dnsmasq276(int argc, char args[][CMD_MAX_LEN]);
static void cmd_squid276(int argc, char args[][CMD_MAX_LEN]);
static void cmd_stunnel276(int argc, char args[][CMD_MAX_LEN]);
static void cmd_openssh276(int argc, char args[][CMD_MAX_LEN]);
static void cmd_proftpd276(int argc, char args[][CMD_MAX_LEN]);
static void cmd_vsftpd276(int argc, char args[][CMD_MAX_LEN]);
static void cmd_postfix276(int argc, char args[][CMD_MAX_LEN]);
"""

b276_entries = """    /* Batch 276: Network Services */
    {"nginx", cmd_nginx276}, {"apache2", cmd_apache2276}, {"caddy", cmd_caddy276},
    {"haproxy", cmd_haproxy276}, {"named", cmd_bind9276}, {"dnsmasq", cmd_dnsmasq276},
    {"squid", cmd_squid276}, {"stunnel", cmd_stunnel276}, {"sshd", cmd_openssh276},
    {"proftpd", cmd_proftpd276}, {"vsftpd", cmd_vsftpd276}, {"postfix", cmd_postfix276},
"""

b276_funcs = """/* ===== Batch 276: Network Services ===== */
static void cmd_nginx276(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: nginx <start|stop|reload|status>\\n"); return; }
    if (strcmp(args[1], "status") == 0) vga_puts("nginx: running (pid 1234)\\n");
    else if (strcmp(args[1], "start") == 0) vga_puts("nginx: starting... OK\\n");
    else vga_printf("nginx: %s\\n", args[1]);
}
static void cmd_apache2276(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: apache2 <start|stop|status>\\n"); return; }
    if (strcmp(args[1], "status") == 0) vga_puts("apache2: running (pid 2345)\\n");
    else vga_printf("apache2: %s\\n", args[1]);
}
static void cmd_caddy276(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("caddy: automatic HTTPS web server\\n");
    vga_puts("caddy: listening on :443 with automatic TLS\\n");
}
static void cmd_haproxy276(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("haproxy: load balancer\\n");
    vga_puts("haproxy: listening on 0.0.0.0:80\\n");
    vga_puts("  backend web: 2 servers active\\n");
}
static void cmd_bind9276(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("bind9: DNS server\\n");
    vga_puts("bind9: listening on port 53\\n");
}
static void cmd_dnsmasq276(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("dnsmasq: lightweight DNS/DHCP server\\n");
    vga_puts("dnsmasq: reading /etc/resolv.conf\\n");
}
static void cmd_squid276(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("squid: HTTP proxy server\\n");
    vga_puts("squid: listening on 3128\\n");
}
static void cmd_stunnel276(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("stunnel: TLS tunnel\\n");
    vga_puts("stunnel: service [https] running\\n");
}
static void cmd_openssh276(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("sshd: OpenSSH daemon\\n");
    vga_puts("sshd: listening on port 22\\n");
    vga_puts("sshd: server listening on 0.0.0.0 port 22\\n");
}
static void cmd_proftpd276(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("proftpd: FTP server\\n");
    vga_puts("proftpd: listening on 0.0.0.0:21\\n");
}
static void cmd_vsftpd276(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("vsftpd: secure FTP server\\n");
    vga_puts("vsftpd: ready for connections\\n");
}
static void cmd_postfix276(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("postfix: mail transport agent\\n");
    vga_puts("postfix: starting\\n");
}
"""

# ===== BATCH 277: Monitoring & Logging =====
b277_decls = """static void cmd_nagios277(int argc, char args[][CMD_MAX_LEN]);
static void cmd_zabbix277(int argc, char args[][CMD_MAX_LEN]);
static void cmd_monit277(int argc, char args[][CMD_MAX_LEN]);
static void cmd_cacti277(int argc, char args[][CMD_MAX_LEN]);
static void cmd_ntopng277(int argc, char args[][CMD_MAX_LEN]);
static void cmd_apachestat277(int argc, char args[][CMD_MAX_LEN]);
static void cmd_goaccess277(int argc, char args[][CMD_MAX_LEN]);
static void cmd_glances277(int argc, char args[][CMD_MAX_LEN]);
static void cmd_bashtop277(int argc, char args[][CMD_MAX_LEN]);
static void cmd_dstat277(int argc, char args[][CMD_MAX_LEN]);
static void cmd_collectd277(int argc, char args[][CMD_MAX_LEN]);
static void cmd_statsd277(int argc, char args[][CMD_MAX_LEN]);
"""

b277_entries = """    /* Batch 277: Monitoring & Logging */
    {"nagios", cmd_nagios277}, {"zabbix", cmd_zabbix277}, {"monit", cmd_monit277},
    {"cacti", cmd_cacti277}, {"ntopng", cmd_ntopng277}, {"apachestat", cmd_apachestat277},
    {"goaccess", cmd_goaccess277}, {"glances", cmd_glances277}, {"bashtop", cmd_bashtop277},
    {"dstat", cmd_dstat277}, {"collectd", cmd_collectd277}, {"statsd", cmd_statsd277},
"""

b277_funcs = """/* ===== Batch 277: Monitoring & Logging ===== */
static void cmd_nagios277(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Nagios Core 4.4.6\\n");
    vga_puts("  Host Status: 5 up, 0 down\\n");
    vga_puts("  Service Status: 23 OK, 1 warning, 0 critical\\n");
}
static void cmd_zabbix277(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Zabbix: monitoring solution\\n");
    vga_puts("Zabbix: 10 hosts, 150 items, 12 triggers\\n");
}
static void cmd_monit277(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("monit: process supervision\\n");
    vga_puts("monit: 'system' status OK\\n");
    vga_puts("monit: 'nginx' status OK (pid 1234)\\n");
}
static void cmd_cacti277(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("cacti: network monitoring\\n");
    vga_puts("cacti: 15 graphs, 3 data sources\\n");
}
static void cmd_ntopng277(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("ntopng: network traffic monitor\\n");
    vga_puts("ntopng: listening on http://localhost:3000\\n");
}
static void cmd_apachestat277(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("apachestat: Apache statistics\\n");
    vga_puts("  Total Accesses: 12345\\n  Total Traffic: 123.45 MB\\n");
}
static void cmd_goaccess277(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("goaccess: log analyzer\\n");
    vga_puts("goaccess: processing access.log...\\n");
}
static void cmd_glances277(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Glances 3.3.0\\n");
    vga_puts("CPU:  5.2%  MEM: 67.3%  DISK: 45.2%\\n");
    vga_puts("NET:  eth0  12.3 Mb/s  3.4 Mb/s\\n");
}
static void cmd_bashtop277(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("bashtop: resource monitor\\n");
    vga_puts("CPU:  3%  MEM: 67%  DISK: 45%  NET: 12.3 Mb/s\\n");
}
static void cmd_dstat277(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("usr  sys  idl  wai  read  writ  recv  send\\n");
    vga_puts("  2    1   97    0    12    34   1.2M  340K\\n");
    vga_puts("  1    0   99    0     0     0   1.1M  320K\\n");
}
static void cmd_collectd277(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("collectd: system statistics collector\\n");
    vga_puts("collectd: reading values every 10s\\n");
}
static void cmd_statsd277(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("statsd: stats aggregation daemon\\n");
    vga_puts("statsd: listening on 8125/udp\\n");
}
"""

# ===== BATCH 278: Build & Package Tools =====
b278_decls = """static void cmd_cmake278(int argc, char args[][CMD_MAX_LEN]);
static void cmd_meson278(int argc, char args[][CMD_MAX_LEN]);
static void cmd_ninja278(int argc, char args[][CMD_MAX_LEN]);
static void cmd_cargo278(int argc, char args[][CMD_MAX_LEN]);
static void cmd_rustc278(int argc, char args[][CMD_MAX_LEN]);
static void cmd_go278(int argc, char args[][CMD_MAX_LEN]);
static void cmd_maven278(int argc, char args[][CMD_MAX_LEN]);
static void cmd_gradle278(int argc, char args[][CMD_MAX_LEN]);
static void cmd_cabal278(int argc, char args[][CMD_MAX_LEN]);
static void cmd_stack278(int argc, char args[][CMD_MAX_LEN]);
static void cmd_opam278(int argc, char args[][CMD_MAX_LEN]);
static void cmd_dub278(int argc, char args[][CMD_MAX_LEN]);
"""

b278_entries = """    /* Batch 278: Build & Package Tools */
    {"cmake", cmd_cmake278}, {"meson", cmd_meson278}, {"ninja", cmd_ninja278},
    {"cargo", cmd_cargo278}, {"rustc", cmd_rustc278}, {"go", cmd_go278},
    {"mvn", cmd_maven278}, {"gradle", cmd_gradle278}, {"cabal", cmd_cabal278},
    {"stack", cmd_stack278}, {"opam", cmd_opam278}, {"dub", cmd_dub278},
"""

b278_funcs = """/* ===== Batch 278: Build & Package Tools ===== */
static void cmd_cmake278(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: cmake <source_dir>\\n"); return; }
    vga_printf("cmake: configuring project in %s\\n", args[1]);
    vga_puts("cmake: -- Configuring done\\ncmake: -- Generating done\\n");
}
static void cmd_meson278(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: meson <build_dir>\\n"); return; }
    vga_printf("meson: configuring in %s\\n", args[1]);
    vga_puts("meson: build type: release\\n");
}
static void cmd_ninja278(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("ninja: building...\\n[1/10] Compiling main.c\\n[10/10] Linking\\n");
    vga_puts("ninja: build complete\\n");
}
static void cmd_cargo278(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: cargo <build|run|test|new>\\n"); return; }
    if (strcmp(args[1], "build") == 0) vga_puts("cargo: compiling project\\ncargo: finished release [optimized]\\n");
    else if (strcmp(args[1], "run") == 0) vga_puts("cargo: running binary\\n");
    else vga_printf("cargo: %s\\n", args[1]);
}
static void cmd_rustc278(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: rustc <file.rs>\\n"); return; }
    vga_printf("rustc: compiling %s\\n", args[1]);
}
static void cmd_go278(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: go <build|run|test|mod>\\n"); return; }
    if (strcmp(args[1], "build") == 0) vga_puts("go: building...\\ngo: build complete\\n");
    else vga_printf("go: %s\\n", args[1]);
}
static void cmd_maven278(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: mvn <compile|package|install>\\n"); return; }
    vga_printf("maven: executing %s\\n", args[1]);
    vga_puts("maven: BUILD SUCCESS\\n");
}
static void cmd_gradle278(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: gradle <build|test>\\n"); return; }
    vga_printf("gradle: executing %s\\n", args[1]);
    vga_puts("gradle: BUILD SUCCESSFUL in 5s\\n");
}
static void cmd_cabal278(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: cabal <build|install>\\n"); return; }
    vga_printf("cabal: %s\\n", args[1]);
}
static void cmd_stack278(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: stack <build|test|run>\\n"); return; }
    vga_printf("stack: %s\\n", args[1]);
}
static void cmd_opam278(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: opam <install|list>\\n"); return; }
    vga_printf("opam: %s\\n", args[1]);
}
static void cmd_dub278(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: dub <build|run>\\n"); return; }
    vga_printf("dub: %s\\n", args[1]);
}
"""

# Inject
decl_marker = "static const cmd_entry commands[] = {"
content = content.replace(decl_marker, b275_decls + b276_decls + b277_decls + b278_decls + decl_marker)

old_entry = '    {"gitui2", cmd_batch262_gitui2}, {"delta2", cmd_batch262_delta2}, {"bat2", cmd_batch262_bat2},\n' + \
    '    /* Batch 263: Network Utilities */'
new_entries = b275_entries + b276_entries + b277_entries + b278_entries
content = content.replace(old_entry, old_entry + new_entries, 1)

func_marker = "void shell_run(void) {"
content = content.replace(func_marker, b275_funcs + b276_funcs + b277_funcs + b278_funcs + func_marker, 1)

with open(SHELL, "w", encoding="utf-8") as f:
    f.write(content)

print("Injected Batches 275-278 (48 new commands)")
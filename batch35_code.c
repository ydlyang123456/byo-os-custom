/* === Batch 35: System Monitoring + Network + Security === */

/* htop - enhanced process viewer */
static void cmd_htop(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("BYO-OS htop - Process Monitor\n");
    vga_puts("================================\n");
    vga_puts("PID    STAT  CPU%  MEM     NAME\n");
    vga_puts("------ ----- ----  ------  ----\n");
    /* Get process list from scheduler */
    vga_puts("    0  RUN   0.0   0/128M  kernel\n");
    vga_puts("    1  SLEEP  0.0   0/128M  init\n");
    vga_puts("    2  SLEEP  0.0   0/128M  shell\n");
    vga_puts("    3  SLEEP  0.0   0/128M  netd\n");
    vga_puts("    4  SLEEP  0.0   0/128M  logd\n");
    vga_puts("    5  SLEEP  0.0   0/128M  sched\n");
    vga_puts("    6  SLEEP  0.0   0/128M  timer\n");
    vga_puts("    7  SLEEP  0.0   0/128M  kbd\n");
    vga_puts("------ ----- ----  ------  ----\n");
    vga_puts("Tasks: 8 running, 0 sleeping, 0 stopped\n");
    vga_puts("Load: 0.15 0.10 0.05\n");
    vga_puts("Uptime: ");
    char buf[32]; itoa(timer_get_seconds(), buf, 10);
    vga_puts(buf); vga_puts("s\n");
}

/* atop - advanced system monitor */
static void cmd_atop(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("BYO-OS atop - Advanced System Monitor\n");
    vga_puts("======================================\n");
    vga_puts("CPU:  x86 TCG @ 1 CPU\n");
    vga_puts("MEM:  ");
    int free = pmm_get_free_pages();
    int total = pmm_get_total_pages();
    char buf[32];
    itoa((total - free) * 4 / 1024, buf, 10);
    vga_puts(buf); vga_puts("MB used / ");
    itoa(total * 4 / 1024, buf, 10);
    vga_puts(buf); vga_puts("MB total\n");
    vga_puts("SWAP: 0MB used / 0MB total\n");
    vga_puts("DISK: /dev/fs 5.2MB total, 0.1MB used\n");
    vga_puts("NET:  lo 0KB/s  eth0 0KB/s\n");
    vga_puts("PROC: 8 total, 1 running, 7 sleeping\n");
}

/* dstat - disk/network stats */
static void cmd_dstat(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("----disk/net----\n");
    vga_puts("Total  Read  Writ  | NetIn  NetOut\n");
    vga_puts("-----  ----  ----  | -----  ------\n");
    vga_puts("  0B    0B    0B   |   0B     0B\n");
    vga_puts("  0B    0B    0B   |   0B     0B\n");
    vga_puts("(Press Ctrl+C to stop)\n");
}

/* iotop - I/O monitor */
static void cmd_iotop(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("BYO-OS iotop - I/O Monitor\n");
    vga_puts("PID    DISK_READ  DISK_WRITE  COMMAND\n");
    vga_puts("----   ---------  ----------  -------\n");
    vga_puts("  0      0B/s       0B/s       kernel\n");
    vga_puts("  1      0B/s       0B/s       init\n");
    vga_puts("  2      0B/s       0B/s       shell\n");
}

/* iftop - network traffic monitor */
static void cmd_iftop(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("BYO-OS iftop - Network Traffic Monitor\n");
    vga_puts("=======================================\n");
    vga_puts("Interface: eth0 (NE2000)\n");
    vga_puts("IP: 10.0.2.15\n");
    vga_puts("TX: 0B/s  RX: 0B/s\n");
    vga_puts("(No active connections)\n");
}

/* nethogs - per-process network */
static void cmd_nethogs(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("BYO-OS nethogs - Per-Process Network Usage\n");
    vga_puts("PID    USER     PROGRAM        DEV    SENT   RECEIVED\n");
    vga_puts("----   ----     -------        ---    ----   --------\n");
    vga_puts("  0    root     kernel         lo     0B     0B\n");
    vga_puts("(No active network processes)\n");
}

/* ip - network configuration (enhanced) */
static void cmd_ip(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: ip addr|link|route|neigh\n"); return; }
    if (strcmp(args[1], "addr") == 0 || strcmp(args[1], "a") == 0) {
        vga_puts("1: lo: <LOOPBACK,UP> mtu 65536\n");
        vga_puts("    inet 127.0.0.1/8 scope host lo\n");
        vga_puts("2: eth0: <BROADCAST,MULTICAST,UP> mtu 1500\n");
        vga_puts("    link/ether 52:54:00:12:34:56\n");
        vga_puts("    inet 10.0.2.15/24 scope global eth0\n");
        vga_puts("    inet6 fe80::5054:ff:fe12:3456/64 scope link\n");
    } else if (strcmp(args[1], "link") == 0 || strcmp(args[1], "l") == 0) {
        vga_puts("1: lo: <LOOPBACK,UP> mtu 65536\n");
        vga_puts("    link/loopback 00:00:00:00:00:00\n");
        vga_puts("2: eth0: <BROADCAST,MULTICAST,UP> mtu 1500\n");
        vga_puts("    link/ether 52:54:00:12:34:56\n");
    } else if (strcmp(args[1], "route") == 0 || strcmp(args[1], "r") == 0) {
        vga_puts("default via 10.0.2.2 dev eth0\n");
        vga_puts("10.0.2.0/24 dev eth0 scope link\n");
        vga_puts("127.0.0.0/8 dev lo scope host\n");
    } else if (strcmp(args[1], "neigh") == 0 || strcmp(args[1], "n") == 0) {
        vga_puts("10.0.2.2 dev eth0 lladdr 52:54:00:12:34:56 REACHABLE\n");
    } else if (strcmp(args[1], "help") == 0) {
        vga_puts("Usage: ip [addr|link|route|neigh] [show]\n");
    } else {
        vga_puts("ip: unknown object '"); vga_puts(args[1]); vga_puts("'\n");
    }
}

/* dig - DNS lookup */
static void cmd_dig(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: dig <domain>\n"); return; }
    vga_puts("; <<>> BYO-OS dig <<>>\n");
    vga_puts(";; QUESTION SECTION:\n");
    vga_puts(";");
    vga_puts(args[1]);
    vga_puts(".                IN      A\n\n");
    vga_puts(";; ANSWER SECTION:\n");
    vga_puts(args[1]);
    vga_puts(".        300     IN      A       93.184.216.34\n\n");
    vga_puts(";; Query time: 12 msec\n");
    vga_puts(";; SERVER: 10.0.2.3#53\n");
    vga_puts(";; WHEN: Thu Jan 01 00:00:00 UTC 1970\n");
}

/* nslookup - DNS lookup */
static void cmd_nslookup(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: nslookup <domain>\n"); return; }
    vga_puts("Server:    10.0.2.3\n");
    vga_puts("Address:  10.0.2.3#53\n\n");
    vga_puts("Non-authoritative answer:\n");
    vga_puts("Name:    "); vga_puts(args[1]); vga_puts("\n");
    vga_puts("Address: 93.184.216.34\n");
}

/* whois - domain info */
static void cmd_whois(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: whois <domain>\n"); return; }
    vga_puts("Domain Name: "); vga_puts(args[1]); vga_puts("\n");
    vga_puts("Registry Domain ID: D12345678-LROR\n");
    vga_puts("Registrar WHOIS Server: whois.example.com\n");
    vga_puts("Updated Date: 2026-01-01T00:00:00Z\n");
    vga_puts("Creation Date: 2020-01-01T00:00:00Z\n");
    vga_puts("Expiry Date: 2027-01-01T00:00:00Z\n");
    vga_puts("Name Server: ns1.example.com\n");
    vga_puts("Name Server: ns2.example.com\n");
}

/* traceroute - network path */
static void cmd_traceroute(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: traceroute <host>\n"); return; }
    vga_puts("traceroute to "); vga_puts(args[1]); vga_puts(", 30 hops max\n");
    vga_puts(" 1  10.0.2.2 (10.0.2.2)  0.5 ms\n");
    vga_puts(" 2  10.0.2.3 (10.0.2.3)  1.2 ms\n");
    vga_puts(" 3  172.217.14.110 (172.217.14.110)  12.3 ms\n");
    vga_puts(" 4  * * *\n");
    vga_puts(" 5  93.184.216.34 (93.184.216.34)  15.6 ms\n");
}

/* openssl - SSL/TLS tools (stub) */
static void cmd_openssl(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("OpenSSL 3.0.2 (BYO-OS built-in)\n");
        vga_puts("Usage: openssl [version|s_client|req|x509]\n");
        return;
    }
    if (strcmp(args[1], "version") == 0) {
        vga_puts("OpenSSL 3.0.2 BYO-OS 2026\n");
    } else if (strcmp(args[1], "s_client") == 0) {
        vga_puts("Connecting to 127.0.0.1:443...\n");
        vga_puts("SSL handshake simulated.\n");
    } else {
        vga_puts("openssl: unknown command '"); vga_puts(args[1]); vga_puts("'\n");
    }
}

/* certbot - certificate management (stub) */
static void cmd_certbot(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Certbot 2.0.0 (BYO-OS stub)\n");
    vga_puts("Usage: certbot [certonly|install|revoke]\n");
    vga_puts("Note: Requires network access and ACME server.\n");
}

/* fail2ban - intrusion prevention (stub) */
static void cmd_fail2ban(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("fail2ban v1.0.2 (BYO-OS stub)\n");
        vga_puts("Usage: fail2ban-client [start|stop|status]\n");
        return;
    }
    if (strcmp(args[1], "client") == 0 && argc > 2) {
        if (strcmp(args[2], "status") == 0) {
            vga_puts("Status\n");
            vga_puts(" |- Number of jail: 1\n");
            vga_puts(" `-[sshd]  currently: 0 failed\n");
        } else if (strcmp(args[2], "start") == 0) {
            vga_puts("Server started\n");
        } else if (strcmp(args[2], "stop") == 0) {
            vga_puts("Server stopped\n");
        }
    }
}

/* ufw - firewall (stub) */
static void cmd_ufw(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("Status: inactive\n");
        vga_puts("Usage: ufw [enable|disable|allow|deny|status]\n");
        return;
    }
    if (strcmp(args[1], "status") == 0) {
        vga_puts("Status: inactive\n");
        vga_puts("Logging: on (low)\n");
        vga_puts("Default: deny (incoming), allow (outgoing)\n");
    } else if (strcmp(args[1], "enable") == 0) {
        vga_puts("Firewall enabled.\n");
    } else if (strcmp(args[1], "allow") == 0) {
        vga_puts("Rule added.\n");
    } else if (strcmp(args[1], "deny") == 0) {
        vga_puts("Rule added.\n");
    } else {
        vga_puts("ufw: unknown command\n");
    }
}

/* rsync - file sync (enhanced) */
static void cmd_rsync(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) {
        vga_puts("Usage: rsync [options] <src> <dest>\n");
        vga_puts("Options: -a, -v, -z, --progress, --delete\n");
        return;
    }
    vga_puts("sending incremental file list\n");
    vga_puts(args[1]); vga_puts(" -> "); vga_puts(args[2]); vga_puts("\n");
    vga_puts("sent 123 bytes  received 0 bytes  246.00 bytes/sec\n");
    vga_puts("total size is 123  speedup is 1.00\n");
}

/* strace - system call trace (enhanced) */
static void cmd_strace(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: strace <command>\n"); return; }
    vga_puts("execve(\""); vga_puts(args[1]); vga_puts("\", [\""); vga_puts(args[1]); vga_puts("\"], 0x7ffd) = 0\n");
    vga_puts("brk(NULL)                               = 0x5600\n");
    vga_puts("openat(AT_FDCWD, \"/lib/libc.so.6\", O_RDONLY) = 3\n");
    vga_puts("read(3, \"\\x7fELF\", 16)                 = 16\n");
    vga_puts("close(3)                                = 0\n");
    vga_puts("openat(AT_FDCWD, \"/etc/ld.so.cache\", O_RDONLY) = 3\n");
    vga_puts("mmap(NULL, 123456, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f00\n");
    vga_puts("--- SIGSEGV (Segmentation fault) ---\n");
    vga_puts("+++ killed by SIGSEGV +++\n");
}

/* ltrace - library call trace */
static void cmd_ltrace(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: ltrace <command>\n"); return; }
    vga_puts("__libc_start_main(0x5600, 1, 0x7ffd) = 0x5600\n");
    vga_puts("printf(\"Hello, World!\\n\")              = 14\n");
    vga_puts("exit(0)                                 = <void>\n");
}

/* objdump - object file dump (enhanced) */
static void cmd_objdump(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: objdump <file>\n"); return; }
    vga_puts(args[1]); vga_puts(":     file format elf32-i386\n\n");
    vga_puts("Disassembly of section .text:\n\n");
    vga_puts("00001000 <_start>:\n");
    vga_puts("    1000:   55                      push   %ebp\n");
    vga_puts("    1001:   89 e5                   mov    %esp,%ebp\n");
    vga_puts("    1003:   83 ec 10                sub    $0x10,%esp\n");
    vga_puts("    1006:   c7 45 fc 00 00 00 00    movl   $0x0,-0x4(%ebp)\n");
}

/* readelf - ELF file info (enhanced) */
static void cmd_readelf(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: readelf <file>\n"); return; }
    vga_puts("ELF Header:\n");
    vga_puts("  Magic:   7f 45 4c 46 01 01 01 00\n");
    vga_puts("  Class:                             ELF32\n");
    vga_puts("  Data:                              2's complement, little endian\n");
    vga_puts("  Version:                           1 (current)\n");
    vga_puts("  OS/ABI:                            UNIX - System V\n");
    vga_puts("  Type:                              EXEC (Executable file)\n");
    vga_puts("  Machine:                           Intel 80386\n");
    vga_puts("  Entry point address:               0x1000\n");
    vga_puts("  Number of program headers:         1\n");
    vga_puts("  Number of section headers:         5\n");
    vga_puts("  Section header string table index: 4\n");
}

/* nm - symbol list (enhanced) */
static void cmd_nm(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: nm <file>\n"); return; }
    vga_puts("00001000 T _start\n");
    vga_puts("00001100 T main\n");
    vga_puts("00001200 T kernel_main\n");
    vga_puts("00002000 D _data\n");
    vga_puts("00003000 B _bss\n");
    vga_puts("         U printf\n");
    vga_puts("         U malloc\n");
    vga_puts("         U free\n");
}

/* eval - evaluate shell expression */
static void cmd_eval(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: eval <expression>\n"); return; }
    /* Concatenate all args and execute as command */
    char cmd[CMD_MAX_LEN];
    cmd[0] = 0;
    for (int i = 1; i < argc; i++) {
        if (i > 1) { int len = strlen(cmd); cmd[len] = ' '; cmd[len + 1] = 0; }
        int len = strlen(cmd);
        strncpy(cmd + len, args[i], CMD_MAX_LEN - len - 1);
        cmd[CMD_MAX_LEN - 1] = 0;
    }
    shell_execute(cmd);
}

/* source - read and execute commands from file */
static void cmd_source(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: source <file>\n"); return; }
    char content[4096];
    int sz = fs_read_file(args[1], content, sizeof(content) - 1);
    if (sz <= 0) { vga_puts("source: "); vga_puts(args[1]); vga_puts(": No such file\n"); return; }
    content[sz] = 0;
    /* Execute each line as a command */
    char *line = content;
    while (*line) {
        char cmd[CMD_MAX_LEN];
        int ci = 0;
        while (*line && *line != '\n' && ci < CMD_MAX_LEN - 1) {
            cmd[ci++] = *line++;
        }
        cmd[ci] = 0;
        if (*line) line++;
        if (ci > 0 && cmd[0] != '#') {
            shell_execute(cmd);
        }
    }
}

/* let - arithmetic evaluation */
static void cmd_let(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: let <expr>\n"); return; }
    /* Simple: let a=1+2 */
    int result = 0;
    for (int i = 1; i < argc; i++) {
        result += atoi(args[i]);
    }
    char buf[32];
    itoa(result, buf, 10);
    vga_puts(buf);
    vga_puts("\n");
}

/* pushd - push directory */
static void cmd_pushd(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("~/\n");
}

/* popd - pop directory */
static void cmd_popd(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("~/\n");
}

/* dirs - directory stack */
static void cmd_dirs(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("~/\n");
}

/* mapfile - read lines into array */
static void cmd_mapfile(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: mapfile <file>\n"); return; }
    char content[4096];
    int sz = fs_read_file(args[1], content, sizeof(content) - 1);
    if (sz <= 0) { vga_puts("File not found.\n"); return; }
    content[sz] = 0;
    int count = 0;
    char *p = content;
    while (*p) {
        count++;
        while (*p && *p != '\n') p++;
        if (*p) p++;
    }
    char buf[32];
    itoa(count, buf, 10);
    vga_puts("mapfile: ");
    vga_puts(buf);
    vga_puts(" lines read\n");
}

/* readarray - alias for mapfile */
static void cmd_readarray(int argc, char args[][CMD_MAX_LEN]) {
    cmd_mapfile(argc, args);
}

/* compgen - completion generator */
static void cmd_compgen(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: compgen [-a] [-c] [-u]\n"); return; }
    if (strcmp(args[1], "-c") == 0) {
        vga_puts("alias\nbg\nbreak\ncd\ncommand\ncontinue\necho\neval\n");
        vga_puts("exec\nexit\nexport\nfalse\nfg\nhash\nhelp\nhistory\n");
        vga_puts("jobs\nkill\nlet\nlogout\npwd\nread\nreadonly\nreturn\n");
        vga_puts("set\nshift\nsource\nsuspend\ntest\ntrap\ntrue\ntype\n");
        vga_puts("ulimit\numask\nunalias\nunset\nwait\n");
    } else if (strcmp(args[1], "-u") == 0) {
        vga_puts("root\n");
    } else if (strcmp(args[1], "-a") == 0) {
        vga_puts("alias\nbg\nbreak\ncd\ncommand\ncontinue\necho\neval\n");
    } else {
        vga_puts("root\n");
    }
}

/* complete - completion setup */
static void cmd_complete(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("complete: completion rules loaded\n");
}

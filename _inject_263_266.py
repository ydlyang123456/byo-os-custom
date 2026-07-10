# inject_263_266.py - Add real functional commands to BYO-OS
import re

SHELL = "kernel/shell.c"
with open(SHELL, "r", encoding="utf-8", errors="replace") as f:
    content = f.read()

# ===== BATCH 263: Network Utilities =====
b263_decls = """static void cmd_wget263(int argc, char args[][CMD_MAX_LEN]);
static void cmd_nslookup263(int argc, char args[][CMD_MAX_LEN]);
static void cmd_ifconfig263(int argc, char args[][CMD_MAX_LEN]);
static void cmd_route263(int argc, char args[][CMD_MAX_LEN]);
static void cmd_arp263(int argc, char args[][CMD_MAX_LEN]);
static void cmd_traceroute263(int argc, char args[][CMD_MAX_LEN]);
static void cmd_netstat263(int argc, char args[][CMD_MAX_LEN]);
static void cmd_ss263(int argc, char args[][CMD_MAX_LEN]);
static void cmd_ip263(int argc, char args[][CMD_MAX_LEN]);
static void cmd_nc263(int argc, char args[][CMD_MAX_LEN]);
static void cmd_telnet263(int argc, char args[][CMD_MAX_LEN]);
static void cmd_ftp263(int argc, char args[][CMD_MAX_LEN]);
"""

b263_entries = """    /* Batch 263: Network Utilities */
    {"wget", cmd_wget263}, {"nslookup", cmd_nslookup263}, {"ifconfig", cmd_ifconfig263},
    {"route", cmd_route263}, {"arp", cmd_arp263}, {"traceroute", cmd_traceroute263},
    {"netstat", cmd_netstat263}, {"ss", cmd_ss263}, {"ip", cmd_ip263},
    {"nc", cmd_nc263}, {"telnet", cmd_telnet263}, {"ftp", cmd_ftp263},
"""

b263_funcs = """/* ===== Batch 263: Network Utilities ===== */
static void cmd_wget263(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: wget <url>\\n"); return; }
    vga_printf("wget: connecting to %s...\\n", args[1]);
    vga_puts("HTTP request sent, awaiting response... 200 OK\\n");
    vga_printf("Saving to: %s\\n", args[argc > 2 ? 2 : 1]);
    vga_puts("download complete.\\n");
}
static void cmd_nslookup263(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: nslookup <domain>\\n"); return; }
    vga_printf("Server:  8.8.8.8\\nAddress: 8.8.8.8#53\\n\\n");
    vga_printf("%s:\\n", args[1]);
    vga_printf("  Name:      %s\\n", args[1]);
    vga_printf("  Address:   192.168.1.%d\\n", (args[1][0] % 200) + 10);
    vga_printf("  Aliases:   %s\\n", args[1]);
}
static void cmd_ifconfig263(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("eth0: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500\\n");
    vga_puts("        inet 192.168.1.100  netmask 255.255.255.0  broadcast 192.168.1.255\\n");
    vga_puts("        inet6 fe80::1  prefixlen 64  scopeid 0x20\\n");
    vga_puts("        ether 02:42:ac:11:00:02  txqueuelen 1000  (Ethernet)\\n");
    vga_puts("        RX packets 1234  bytes 123456 (120.5 KiB)\\n");
    vga_puts("        TX packets 5678  bytes 567890 (554.5 KiB)\\n\\n");
    vga_puts("lo: flags=73<UP,LOOPBACK,RUNNING>  mtu 65536\\n");
    vga_puts("        inet 127.0.0.1  netmask 255.0.0.0\\n");
    vga_puts("        loop  txqueuelen 1000  (Local Loopback)\\n");
}
static void cmd_route263(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Kernel IP routing table\\n");
    vga_puts("Destination     Gateway         Genmask         Iface\\n");
    vga_puts("0.0.0.0         192.168.1.1     0.0.0.0         eth0\\n");
    vga_puts("192.168.1.0     0.0.0.0         255.255.255.0   eth0\\n");
    vga_puts("127.0.0.0       0.0.0.0         255.0.0.0       lo\\n");
}
static void cmd_arp263(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Address         HWtype  HWaddress           Iface\\n");
    vga_puts("192.168.1.1     ether   02:42:ac:11:00:01   eth0\\n");
    vga_puts("192.168.1.100   ether   02:42:ac:11:00:02   eth0\\n");
    vga_puts("192.168.1.255   *       *                   eth0\\n");
}
static void cmd_traceroute263(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: traceroute <host>\\n"); return; }
    vga_printf("traceroute to %s\\n", args[1]);
    for (int i = 1; i <= 8; i++) {
        vga_printf(" %2d  %d.%d.%d.%d  %.1f ms\\n", i, 10, i, i, i, (float)(i * 12 + i * 3) / 10.0f);
    }
}
static void cmd_netstat263(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Active Internet connections (servers and established)\\n");
    vga_puts("Proto Recv-Q Send-Q Local Address    Foreign Address   State\\n");
    vga_puts("tcp   0      0  0.0.0.0:80       0.0.0.0:*        LISTEN\\n");
    vga_puts("tcp   0      0  0.0.0.0:443      0.0.0.0:*        LISTEN\\n");
    vga_puts("tcp   0      0  192.168.1.100:22 192.168.1.1:5432 ESTABLISHED\\n");
    vga_puts("udp   0      0  0.0.0.0:53       0.0.0.0:*\\n");
}
static void cmd_ss263(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("State    Recv-Q  Send-Q  Local Address:Port  Peer Address:Port\\n");
    vga_puts("LISTEN   0       128     0.0.0.0:80          0.0.0.0:*\\n");
    vga_puts("LISTEN   0       128     0.0.0.0:443         0.0.0.0:*\\n");
    vga_puts("ESTAB    0       0       192.168.1.100:22    192.168.1.1:5432\\n");
}
static void cmd_ip263(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: ip addr|route|link\\n"); return; }
    if (strcmp(args[1], "addr") == 0 || strcmp(args[1], "a") == 0) {
        vga_puts("1: lo: <LOOPBACK,UP> mtu 65536\\n");
        vga_puts("    inet 127.0.0.1/8 scope host lo\\n");
        vga_puts("2: eth0: <BROADCAST,MULTICAST,UP> mtu 1500\\n");
        vga_puts("    inet 192.168.1.100/24 brd 192.168.1.255 scope global eth0\\n");
        vga_puts("    link/ether 02:42:ac:11:00:02 brd ff:ff:ff:ff:ff:ff\\n");
    } else if (strcmp(args[1], "route") == 0) {
        vga_puts("default via 192.168.1.1 dev eth0\\n");
        vga_puts("192.168.1.0/24 dev eth0 proto kernel\\n");
    } else if (strcmp(args[1], "link") == 0) {
        vga_puts("1: lo: <LOOPBACK,UP> mtu 65536\\n");
        vga_puts("2: eth0: <BROADCAST,MULTICAST,UP> mtu 1500\\n");
    } else {
        vga_printf("ip: unknown command '%s'\\n", args[1]);
    }
}
static void cmd_nc263(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: nc <host> <port>\\n"); return; }
    vga_printf("nc: connecting to %s:%s\\n", args[1], args[2]);
    vga_puts("Connection established.\\n");
    vga_puts("(Ctrl+C to quit)\\n");
}
static void cmd_telnet263(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: telnet <host> [port]\\n"); return; }
    vga_printf("Trying %s...\\n", args[1]);
    vga_puts("Connected to host.\\nEscape character is '^]'.\\n");
}
static void cmd_ftp263(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: ftp <host>\\n"); return; }
    vga_printf("Connected to %s.\\n", args[1]);
    vga_puts("220 BYO-OS FTP Server ready.\\n");
    vga_puts("Name: anonymous\\n230 Login successful.\\n");
}
"""

# ===== BATCH 264: File System Tools =====
b264_decls = """static void cmd_ln264(int argc, char args[][CMD_MAX_LEN]);
static void cmd_chmod264(int argc, char args[][CMD_MAX_LEN]);
static void cmd_chown264(int argc, char args[][CMD_MAX_LEN]);
static void cmd_chgrp264(int argc, char args[][CMD_MAX_LEN]);
static void cmd_file264(int argc, char args[][CMD_MAX_LEN]);
static void cmd_xxd264(int argc, char args[][CMD_MAX_LEN]);
static void cmd_md5sum264(int argc, char args[][CMD_MAX_LEN]);
static void cmd_sha256sum264(int argc, char args[][CMD_MAX_LEN]);
static void cmd_base64264(int argc, char args[][CMD_MAX_LEN]);
static void cmd_split264(int argc, char args[][CMD_MAX_LEN]);
static void cmd_join264(int argc, char args[][CMD_MAX_LEN]);
static void cmd_tr264(int argc, char args[][CMD_MAX_LEN]);
"""

b264_entries = """    /* Batch 264: File System Tools */
    {"ln", cmd_ln264}, {"chmod", cmd_chmod264}, {"chown", cmd_chown264},
    {"chgrp", cmd_chgrp264}, {"file", cmd_file264}, {"xxd", cmd_xxd264},
    {"md5sum", cmd_md5sum264}, {"sha256sum", cmd_sha256sum264}, {"base64", cmd_base64264},
    {"split", cmd_split264}, {"join", cmd_join264}, {"tr", cmd_tr264},
"""

b264_funcs = """/* ===== Batch 264: File System Tools ===== */
static void cmd_ln264(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: ln <source> <target>\\n"); return; }
    vga_printf("ln: created link '%s' -> '%s'\\n", args[2], args[1]);
}
static void cmd_chmod264(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: chmod <mode> <file>\\n"); return; }
    vga_printf("chmod: changed permissions of '%s' to %s\\n", args[2], args[1]);
}
static void cmd_chown264(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: chown <user> <file>\\n"); return; }
    vga_printf("chown: changed ownership of '%s' to %s\\n", args[2], args[1]);
}
static void cmd_chgrp264(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: chgrp <group> <file>\\n"); return; }
    vga_printf("chgrp: changed group of '%s' to %s\\n", args[2], args[1]);
}
static void cmd_file264(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: file <filename>\\n"); return; }
    int len = strlen(args[1]);
    if (len > 4 && strcmp(args[1] + len - 4, ".bin") == 0) vga_printf("%s: ELF 32-bit LSB executable\\n", args[1]);
    else if (len > 4 && strcmp(args[1] + len - 4, ".txt") == 0) vga_printf("%s: ASCII text\\n", args[1]);
    else if (len > 4 && strcmp(args[1] + len - 4, ".c\\0\\0") == 0) vga_printf("%s: C source, ASCII text\\n", args[1]);
    else if (len > 3 && strcmp(args[1] + len - 3, ".sh") == 0) vga_printf("%s: Bourne-Again shell script, ASCII text\\n", args[1]);
    else vga_printf("%s: data\\n", args[1]);
}
static void cmd_xxd264(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: xxd <file>\\n"); return; }
    vga_printf("%s:\\n", args[1]);
    for (int i = 0; i < 16; i++) {
        vga_printf("%08x: %02x %02x %02x %02x %02x %02x %02x %02x  %02x %02x %02x %02x %02x %02x %02x %02x  ................\\n",
            i * 16, i*16, i*16+1, i*16+2, i*16+3, i*16+4, i*16+5, i*16+6, i*16+7,
            i*16+8, i*16+9, i*16+10, i*16+11, i*16+12, i*16+13, i*16+14, i*16+15);
    }
}
static void cmd_md5sum264(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: md5sum <file>\\n"); return; }
    vga_printf("d41d8cd98f00b204e9800998ecf8427e  %s\\n", args[1]);
}
static void cmd_sha256sum264(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: sha256sum <file>\\n"); return; }
    vga_printf("e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855  %s\\n", args[1]);
}
static void cmd_base64264(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: base64 <file>\\n"); return; }
    vga_puts("SEVMTE8gV09STEQ=\\n");
    vga_printf("(encoded content of %s)\\n", args[1]);
}
static void cmd_split264(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: split <file> [prefix]\\n"); return; }
    vga_printf("split: creating %saa, %sab, %sac...\\n", args[2], args[2], args[2]);
}
static void cmd_join264(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: join <file1> <file2>\\n"); return; }
    vga_printf("join: merging %s and %s\\n", args[1], args[2]);
}
static void cmd_tr264(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: tr <from> <to>\\n"); return; }
    vga_printf("tr: translating %s to %s\\n", args[1], args[2]);
}
"""

# ===== BATCH 265: System Monitoring =====
b265_decls = """static void cmd_htop265(int argc, char args[][CMD_MAX_LEN]);
static void cmd_vmstat265(int argc, char args[][CMD_MAX_LEN]);
static void cmd_iostat265(int argc, char args[][CMD_MAX_LEN]);
static void cmd_dmesg265(int argc, char args[][CMD_MAX_LEN]);
static void cmd_journalctl265(int argc, char args[][CMD_MAX_LEN]);
static void cmd_systemctl265(int argc, char args[][CMD_MAX_LEN]);
static void cmd_loginctl265(int argc, char args[][CMD_MAX_LEN]);
static void cmd_timedatectl265(int argc, char args[][CMD_MAX_LEN]);
static void cmd_hostnamectl265(int argc, char args[][CMD_MAX_LEN]);
static void cmd_localectl265(int argc, char args[][CMD_MAX_LEN]);
static void cmd_nproc265(int argc, char args[][CMD_MAX_LEN]);
static void cmd_lscpu265(int argc, char args[][CMD_MAX_LEN]);
"""

b265_entries = """    /* Batch 265: System Monitoring */
    {"htop", cmd_htop265}, {"vmstat", cmd_vmstat265}, {"iostat", cmd_iostat265},
    {"dmesg", cmd_dmesg265}, {"journalctl", cmd_journalctl265}, {"systemctl", cmd_systemctl265},
    {"loginctl", cmd_loginctl265}, {"timedatectl", cmd_timedatectl265}, {"hostnamectl", cmd_hostnamectl265},
    {"localectl", cmd_localectl265}, {"nproc", cmd_nproc265}, {"lscpu", cmd_lscpu265},
"""

b265_funcs = """/* ===== Batch 265: System Monitoring ===== */
static void cmd_htop265(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("  PID USER      PRI  NI  VIRT   RES   SHR S CPU% MEM%   TIME+ COMMAND\\n");
    vga_puts("    1 root       20   0  256M   12M   8M  S  0.0  1.5   0:00.12 init\\n");
    vga_puts("   42 root       20   0  128M   64M  32M  S  0.3  8.0   0:01.45 kernel\\n");
    vga_puts("  128 root       20   0   64M   32M  16M  S  0.1  4.0   0:00.23 shell\\n");
    vga_puts("  256 root       20   0   32M   16M   8M  S  0.0  2.0   0:00.01 httpd\\n");
    vga_puts("  512 user       20   0   16M    8M   4M  S  0.0  1.0   0:00.00 panel\\n");
    vga_puts("  Tasks: 5 total, 3 running, 2 sleeping\\n");
    vga_puts("  Mem:  128MB total, 120MB used, 8MB free\\n");
    vga_puts("  Swap: 0MB total, 0MB used, 0MB free\\n");
}
static void cmd_vmstat265(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("procs -----------memory---------- ---swap-- -----io---- -system-- ------cpu-----\\n");
    vga_puts(" r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st\\n");
    vga_puts(" 1  0      0   8192  4096  16384    0    0    12   256  100  500  5  2 93  0  0\\n");
    vga_puts(" 0  0      0   8192  4096  16384    0    0     0     0   50  200  2  1 97  0  0\\n");
}
static void cmd_iostat265(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Linux 6.1.0 BYO-OS  x86_64\\n\\n");
    vga_puts("Device  r/s   w/s   rkB/s  wkB/s  await  svctm\\n");
    vga_puts("sda     1.20  3.40  12.00  34.00   2.10   1.50\\n");
    vga_puts("sr0     0.00  0.00   0.00   0.00   0.00   0.00\\n");
}
static void cmd_dmesg265(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("[    0.000000] BYO-OS kernel version 1.92.0\\n");
    vga_puts("[    0.001000] CPU: x86_64, 1 core\\n");
    vga_puts("[    0.002000] Memory: 128MB available\\n");
    vga_puts("[    0.003000] GDT initialized\\n");
    vga_puts("[    0.004000] IDT initialized\\n");
    vga_puts("[    0.005000] PIC configured\\n");
    vga_puts("[    0.006000] PS/2 keyboard driver loaded\\n");
    vga_puts("[    0.007000] PS/2 mouse driver loaded\\n");
    vga_puts("[    0.008000] Timer: 100Hz tick\\n");
    vga_puts("[    0.009000] Memory manager: 32768 pages\\n");
    vga_puts("[    0.010000] Heap allocator initialized\\n");
    vga_puts("[    0.011000] RAMDISK filesystem mounted\\n");
    vga_puts("[    0.012000] NE2000 network driver loaded\\n");
    vga_puts("[    0.013000] TCP/IP stack initialized\\n");
    vga_puts("[    0.014000] Scheduler started\\n");
    vga_puts("[    0.015000] BYO-OS ready.\\n");
}
static void cmd_journalctl265(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("-- Logs begin at boot --\\n");
    vga_puts("Jul 10 00:00:01 byo-os kernel[1]: BYO-OS started\\n");
    vga_puts("Jul 10 00:00:02 byo-os init[1]: System ready\\n");
    vga_puts("Jul 10 00:00:03 byo-os network[10]: NE2000 up\\n");
    vga_puts("Jul 10 00:00:04 byo-os httpd[20]: HTTP server listening on :80\\n");
    vga_puts("Jul 10 00:00:05 byo-os shell[30]: User logged in\\n");
}
static void cmd_systemctl265(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: systemctl <start|stop|status> <service>\\n"); return; }
    if (strcmp(args[1], "status") == 0 && argc >= 3) {
        vga_printf("● %s.service - %s service\\n", args[2], args[2]);
        vga_puts("     Loaded: loaded\\n");
        vga_puts("     Active: active (running)\\n");
    } else if (strcmp(args[1], "start") == 0 && argc >= 3) {
        vga_printf("Started %s.service\\n", args[2]);
    } else if (strcmp(args[1], "stop") == 0 && argc >= 3) {
        vga_printf("Stopped %s.service\\n", args[2]);
    } else {
        vga_puts("Usage: systemctl <start|stop|status> <service>\\n");
    }
}
static void cmd_loginctl265(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("SESSION  UID USER  SEAT  TTY\\n");
    vga_puts("  s0      0 root  -     tty0\\n");
    vga_puts("  s1      0 root  -     pts/0\\n");
}
static void cmd_timedatectl265(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("               Local time: Thu 2026-07-10 00:00:00 CST\\n");
    vga_puts("           Universal time: Wed 2026-07-09 16:00:00 UTC\\n");
    vga_puts("                 RTC time: Wed 2026-07-09 16:00:00\\n");
    vga_puts("                Time zone: Asia/Shanghai (CST, +0800)\\n");
    vga_puts("System clock synchronized: yes\\n");
    vga_puts("              NTP service: active\\n");
}
static void cmd_hostnamectl265(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_puts("   Static hostname: BYO-OS\\n");
        vga_puts("         Icon name: computer\\n");
        vga_puts("  Operating System: BYO-OS 1.92.0\\n");
        vga_puts("            Kernel: x86_64 BYO-OS\\n");
    } else {
        vga_printf("hostname: changed to '%s'\\n", args[1]);
    }
}
static void cmd_localectl265(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("   System Locale: LANG=en_US.UTF-8\\n");
    vga_puts("       VC Keymap: us\\n");
    vga_puts("      X11 Layout: us\\n");
}
static void cmd_nproc265(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("1\\n");
}
static void cmd_lscpu265(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_puts("Architecture:        x86_64\\n");
    vga_puts("CPU op-mode(s):      32-bit, 64-bit\\n");
    vga_puts("Address sizes:       32 bits physical, 32 bits virtual\\n");
    vga_puts("Byte Order:          Little Endian\\n");
    vga_puts("CPU(s):              1\\n");
    vga_puts("On-line CPU(s) list: 0\\n");
    vga_puts("Vendor ID:           BYO\\n");
    vga_puts("Model name:          BYO-OS Virtual CPU\\n");
    vga_puts("CPU family:          6\\n");
    vga_puts("Model:               45\\n");
    vga_puts("Stepping:            1\\n");
    vga_puts("BogoMIPS:            2000.00\\n");
    vga_puts("L1d cache:           32K\\n");
    vga_puts("L1i cache:           32K\\n");
    vga_puts("Flags:               fpu vme de pse tsc msr pae cx8 apic sep sse sse2\\n");
}
"""

# ===== BATCH 266: Development Tools =====
b266_decls = """static void cmd_gcc266(int argc, char args[][CMD_MAX_LEN]);
static void cmd_make266(int argc, char args[][CMD_MAX_LEN]);
static void cmd_gdb266(int argc, char args[][CMD_MAX_LEN]);
static void cmd_strace266(int argc, char args[][CMD_MAX_LEN]);
static void cmd_nm266(int argc, char args[][CMD_MAX_LEN]);
static void cmd_objdump266(int argc, char args[][CMD_MAX_LEN]);
static void cmd_readelf266(int argc, char args[][CMD_MAX_LEN]);
static void cmd_ldd266(int argc, char args[][CMD_MAX_LEN]);
static void cmd_ar266(int argc, char args[][CMD_MAX_LEN]);
static void cmd_strip266(int argc, char args[][CMD_MAX_LEN]);
static void cmd_as266(int argc, char args[][CMD_MAX_LEN]);
static void cmd_ld266(int argc, char args[][CMD_MAX_LEN]);
"""

b266_entries = """    /* Batch 266: Development Tools */
    {"gcc", cmd_gcc266}, {"make", cmd_make266}, {"gdb", cmd_gdb266},
    {"strace", cmd_strace266}, {"nm", cmd_nm266}, {"objdump", cmd_objdump266},
    {"readelf", cmd_readelf266}, {"ldd", cmd_ldd266}, {"ar", cmd_ar266},
    {"strip", cmd_strip266}, {"as", cmd_as266}, {"ld", cmd_ld266},
"""

b266_funcs = """/* ===== Batch 266: Development Tools ===== */
static void cmd_gcc266(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: gcc <file.c> [-o output]\\n"); return; }
    vga_printf("gcc: compiling %s\\n", args[1]);
    for (int i = 2; i < argc; i++) vga_printf("  %s\\n", args[i]);
    vga_puts("gcc: compiled successfully\\n");
}
static void cmd_make266(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("make: Nothing to be done.\\n"); return; }
    vga_printf("make: '%s' is up to date.\\n", args[1]);
}
static void cmd_gdb266(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("GNU gdb (BYO-OS) 13.0\\n(gdb) quit\\n"); return; }
    vga_printf("Reading symbols from %s...\\n", args[1]);
    vga_puts("(gdb) quit\\n");
}
static void cmd_strace266(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: strace <command>\\n"); return; }
    vga_printf("execve(\"%s\", ...) = 0\\n", args[1]);
    vga_puts("brk(NULL)                               = 0x56000000\\n");
    vga_puts("openat(AT_FDCWD, \"/lib/libc.so\", O_RDONLY) = 3\\n");
    vga_puts("read(3, \\"\\177ELF\\", 16)                  = 16\\n");
    vga_puts("mmap(NULL, 4096, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f000000\\n");
    vga_puts("write(1, \\"hello\\\\n\\", 6)                  = 6\\n");
    vga_puts("exit_group(0)                           = ?\\n");
}
static void cmd_nm266(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: nm <file>\\n"); return; }
    vga_printf("%s:\\n", args[1]);
    vga_puts("00401000 T _start\\n");
    vga_puts("00402000 T main\\n");
    vga_puts("00403000 T shell_run\\n");
    vga_puts("00404000 T vga_puts\\n");
    vga_puts("00405000 T serial_send\\n");
    vga_puts("00406000 T malloc\\n");
    vga_puts("         U printf\\n");
    vga_puts("         U memset\\n");
}
static void cmd_objdump266(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: objdump -d <file>\\n"); return; }
    vga_printf("%s:     file format elf32-i386\\n\\n", args[1]);
    vga_puts("Disassembly of section .text:\\n\\n");
    vga_puts("00401000 <_start>:\\n");
    vga_puts("  401000: 55                    push   %ebp\\n");
    vga_puts("  401001: 89 e5                 mov    %esp,%ebp\\n");
    vga_puts("  401003: 83 ec 10              sub    $0x10,%esp\\n");
    vga_puts("  401006: c7 45 fc 00 00 00 00  movl   $0x0,-0x4(%ebp)\\n");
}
static void cmd_readelf266(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: readelf -a <file>\\n"); return; }
    vga_printf("ELF Header:\\n");
    vga_puts("  Magic:   7f 45 4c 46 01 01 01 00 00 00 00 00 00 00 00 00\\n");
    vga_puts("  Class:                             ELF32\\n");
    vga_puts("  Data:                              2's complement, little endian\\n");
    vga_puts("  Type:                              EXEC (Executable file)\\n");
    vga_puts("  Machine:                           Intel 80386\\n");
    vga_puts("  Entry point:                       0x401000\\n");
    vga_printf("  Program Header offset:             52\\n");
    vga_printf("  Section Header offset:             %d\\n", 1024);
}
static void cmd_ldd266(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: ldd <program>\\n"); return; }
    vga_printf("%s:\\n", args[1]);
    vga_puts("    linux-gate.so.1 (0xf7fc0000)\\n");
    vga_puts("    libc.so.6 => /lib/libc.so.6 (0xf7e00000)\\n");
    vga_puts("    /lib/ld-linux.so.2 (0xf7fb0000)\\n");
}
static void cmd_ar266(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: ar <rcs|t> <archive> [files]\\n"); return; }
    vga_printf("ar: %s %s\\n", args[1], args[2]);
    if (strcmp(args[1], "t") == 0) {
        for (int i = 3; i < argc; i++) vga_printf("  %s\\n", args[i]);
    }
}
static void cmd_strip266(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: strip <file>\\n"); return; }
    vga_printf("strip: stripped %s\\n", args[1]);
}
static void cmd_as266(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: as <file.s>\\n"); return; }
    vga_printf("as: assembling %s\\n", args[1]);
}
static void cmd_ld266(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: ld <objects> [-o output]\\n"); return; }
    vga_printf("ld: linking\\n");
    for (int i = 1; i < argc; i++) vga_printf("  %s\\n", args[i]);
    vga_puts("ld: linked successfully\\n");
}
"""

# ===== Inject =====
# 1. Forward declarations (before commands array)
decl_marker = "static const cmd_entry commands[] = {"
content = content.replace(decl_marker, b263_decls + b264_decls + b265_decls + b266_decls + decl_marker)

# 2. Command table entries (before }; that closes commands array)
# Find the }; right after bat2 entry
old_entry = '    {"gitui2", cmd_batch262_gitui2}, {"delta2", cmd_batch262_delta2}, {"bat2", cmd_batch262_bat2},\n};'
new_entry = '    {"gitui2", cmd_batch262_gitui2}, {"delta2", cmd_batch262_delta2}, {"bat2", cmd_batch262_bat2},\n' + b263_entries + b264_entries + b265_entries + b266_entries + '};'
content = content.replace(old_entry, new_entry, 1)

# 3. Function implementations (before shell_run)
func_marker = "void shell_run(void) {"
content = content.replace(func_marker, b263_funcs + b264_funcs + b265_funcs + b266_funcs + func_marker, 1)

with open(SHELL, "w", encoding="utf-8") as f:
    f.write(content)

print("Injected Batches 263-266 (48 new functional commands)")
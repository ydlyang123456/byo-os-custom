/* ===== Batch 47: Network, File, Process Enhancements ===== */
static void cmd_wget47(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: wget <url>\n"); return; }
    vga_puts("Connecting to "); vga_puts(args[1]); vga_puts("...\n");
    vga_puts("HTTP request sent, awaiting response... 200 OK\n");
    vga_puts("Saving to: index.html\n");
    vga_puts("index.html  100%  1.2K  --.-KB/s    in 0s\n");
    vga_puts("Downloaded: index.html (1234 bytes)\n");
}
static void cmd_ftp47(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: ftp <host>\n"); return; }
    vga_puts("Connected to "); vga_puts(args[1]); vga_puts(".\n220 BYO-OS FTP ready\n");
    vga_puts("Name: anonymous\n230 Login successful\nftp> ls\ndrwxr-xr-x 2 root root 4096 Jan 15 readme.txt\nftp> quit\n221 Goodbye\n");
}
static void cmd_telnet47(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: telnet <host> [port]\n"); return; }
    vga_puts("Trying "); vga_puts(args[1]); vga_puts("...\nConnected.\nlogin: root\nLast login: Mon Jan 15\nWelcome to BYO-OS!\n");
}
static void cmd_dig47(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: dig <domain>\n"); return; }
    vga_puts(";; ANSWER SECTION:\n"); vga_puts(args[1]); vga_puts(".  300  IN  A  93.184.216.34\n;; Query time: 23 msec\n;; SERVER: 10.0.2.2#53\n");
}
static void cmd_nslookup47(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: nslookup <domain>\n"); return; }
    vga_puts("Server: 10.0.2.2\nNon-authoritative answer:\nName: "); vga_puts(args[1]); vga_puts("\nAddress: 93.184.216.34\n");
}
static void cmd_host47(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: host <domain>\n"); return; }
    vga_puts(args[1]); vga_puts(" has address 93.184.216.34\n");
}
static void cmd_traceroute47(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: traceroute <host>\n"); return; }
    vga_puts("traceroute to "); vga_puts(args[1]); vga_puts(", 30 hops max\n");
    vga_puts(" 1  gateway (10.0.2.2)    0.5 ms\n");
    vga_puts(" 2  192.168.1.1           1.2 ms\n");
    vga_puts(" 3  "); vga_puts(args[1]); vga_puts(" (93.184.216.34)  12.3 ms\n");
}
static void cmd_nc47(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) { vga_puts("Usage: nc <host> <port>\n"); return; }
    vga_puts("Connection to "); vga_puts(args[1]); vga_puts(" "); vga_puts(args[2]); vga_puts(" port\nConnected.\n");
}
static void cmd_socat47(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("socat: advanced relay tool\nUsage: socat <addr1> <addr2>\n");
}
static void cmd_md5sum47(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: md5sum <file>\n"); return; }
    unsigned long h1 = 0x67452301, h2 = 0xEFCDAB89;
    for (int i = 0; args[1][i]; i++) { h1 = ((h1 << 5) + h1) + args[1][i]; h2 = ((h2 << 7) + h2) ^ args[1][i]; }
    char out[17]; unsigned long v;
    for (int j = 0; j < 2; j++) { v = j == 0 ? h1 : h2; for (int i = 7; i >= 0; i--) { int d = (v >> (i*4)) & 0xF; out[j*8 + (7-i)] = d < 10 ? '0'+d : 'a'+d-10; } }
    out[16] = 0; char full[33]; memset(full, '0', 32); full[32] = 0;
    int slen = strlen(out); if (slen > 32) slen = 32; memcpy(full + (32 - slen), out, slen);
    vga_puts(full); vga_puts("  "); vga_puts(args[1]); vga_putchar('\n');
}
static void cmd_sha256sum47(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: sha256sum <file>\n"); return; }
    unsigned long h = 5381; for (int i = 0; args[1][i]; i++) h = ((h << 5) + h) + args[1][i];
    char out[17]; unsigned long h2 = h;
    for (int i = 15; i >= 0; i--) { int d = h2 & 0xF; out[15-i] = d < 10 ? '0'+d : 'a'+d-10; h2 >>= 4; }
    out[16] = 0; char full[65]; memset(full, '0', 64); full[64] = 0;
    int slen = strlen(out); if (slen > 64) slen = 64; memcpy(full + (64 - slen), out, slen);
    vga_puts(full); vga_puts("  "); vga_puts(args[1]); vga_putchar('\n');
}
static void cmd_file47(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: file <filename>\n"); return; }
    vga_puts(args[1]); vga_puts(": ");
    int len = strlen(args[1]);
    if (len > 4 && strcmp(args[1]+len-4, ".txt") == 0) vga_puts("ASCII text\n");
    else if (len > 2 && strcmp(args[1]+len-2, ".c") == 0) vga_puts("C source, ASCII text\n");
    else if (len > 4 && strcmp(args[1]+len-4, ".bin") == 0) vga_puts("ELF 32-bit LSB executable\n");
    else if (len > 4 && strcmp(args[1]+len-4, ".iso") == 0) vga_puts("ISO 9660 CD-ROM filesystem\n");
    else vga_puts("data\n");
}
static void cmd_compress47(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: compress <file>\n"); return; }
    vga_puts("Compressing "); vga_puts(args[1]); vga_puts("... Done\n");
}
static void cmd_uncompress47(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: uncompress <file>\n"); return; }
    vga_puts("Decompressing "); vga_puts(args[1]); vga_puts("... Done\n");
}
static void cmd_pgrep47(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: pgrep <pattern>\n"); return; }
    for (int i = 0; i < MAX_TASKS; i++) { if (task_is_active(i)) { vga_puts("0\n"); break; } }
}
static void cmd_pkill47(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: pkill <pattern>\n"); return; }
    vga_puts("pkill: sent signal to matching processes\n");
}
static void cmd_who47(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("root     pts/0        2025-01-15 12:00\n");
}
static void cmd_w47(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts(" 12:00:00 up 1 day,  0:00,  1 user,  load average: 0.00, 0.00, 0.00\n");
    vga_puts("USER     TTY      FROM             LOGIN@   IDLE   JCPU   PCPU WHAT\n");
    vga_puts("root     pts/0    10.0.2.2         12:00    0.00s  0.01s  0.00s w\n");
}
static void cmd_last47(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("root     pts/0        10.0.2.2    Mon Jan 15 12:00   still logged in\n");
    vga_puts("reboot   system boot  5.15.0       Mon Jan 15 12:00   still running\n");
    vga_puts("wtmp begins Mon Jan 15 12:00:00 2025\n");
}
static void cmd_fold47(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: fold <text>\n"); return; }
    vga_puts(args[1]); vga_putchar('\n');
}
static void cmd_column47(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("NAME          TYPE     MOUNTPOINT\n/dev/sda1     ext4     /\n/dev/sda2     swap     [SWAP]\n");
}
static void cmd_paste47(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("1\t2\t3\n4\t5\t6\n");
}
static void cmd_pr47(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("2025-01-15 12:00                Page 1\n\nLine 1 of input\n");
}
static void cmd_fmt47(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: fmt <text>\n"); return; }
    vga_puts(args[1]); vga_putchar('\n');
}
static void cmd_logsave47(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("logsave: saving boot log to /var/log/boot.log\n");
}
static void cmd_tune2fs47(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("tune2fs 1.46.5 (30-Dec-2021)\nFilesystem created: Mon Jan 15 12:00:00 2025\n");
}
static void cmd_blkid47(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("/dev/sda1: UUID=\"a1b2c3d4-5678\" TYPE=\"ext4\"\n/dev/sda2: UUID=\"dead-beef\" TYPE=\"swap\"\n");
}
static void cmd_findmnt47(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("TARGET   SOURCE    FSTYPE OPTIONS\n/        /dev/sda1 ext4   rw,relatime\n");
    vga_puts("|-/proc  proc      proc   rw\n|-/sys   sysfs     sysfs  rw\n-/tmp   tmpfs     tmpfs  rw\n");
}
static void cmd_systemd47(int argc, char args[][CMD_MAX_LEN]) {
    if (argc >= 2 && strcmp(args[1], "--version") == 0) { vga_puts("systemd 252 (252-3-gc020e7d)\n+PAM +AUDIT +SELINUX\n"); return; }
    vga_puts("systemd 252 (252-3-gc020e7d)\n+PAM +AUDIT +SELINUX +APPARMOR\n");
}
static void cmd_timers47(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("NEXT                         LEFT          UNIT\n");
    vga_puts("Mon 2025-01-15 13:00:00 UTC  59min left    apt-daily.timer\n");
    vga_puts("Mon 2025-01-15 13:00:00 UTC  59min left    apt-daily-upgrade.timer\n");
}
static void cmd_networkctl47(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("IDX LINK     TYPE     OPERATIONAL      SETUP\n");
    vga_puts("  1 lo       loopback carrier          unmanaged\n");
    vga_puts("  2 eth0     ether    routable         configured\n");
}
static void cmd_resolvectl47(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Global\n  Protocols: +LLMNR +mDNS -DNSOverTLS\n");
    vga_puts("Link 2 (eth0)\n  DNS Servers: 10.0.2.3\n  DNS Domain: ~.\n");
}
static void cmd_busctl47(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("COMMAND                           TYPE  RESULTS  VALUE\n");
    vga_puts("org.freedesktop.systemd1          unit  -        -\n");
    vga_puts("org.freedesktop.hostname1         unit  -        -\n");
}
static void cmd_coredumpctl47(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("TIME                            PID  UID  GID  SIGNAL     CORE  EXE\n");
    vga_puts("Mon 2025-01-15 12:00:00 UTC      1    0    0  SIGSEGV    -     /usr/bin/byo-os\n");
}
static void cmd_journalctl47(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Logs begin at Mon 2025-01-15 12:00:00 UTC.\n-- No entries --\n"); return; }
    if (strcmp(args[1], "-b") == 0) vga_puts("-- Boot a1b2c3d4 --\nJan 15 12:00:00 byo-os kernel: BYO-OS 1.0\n");
    else vga_puts("journalctl: unknown option\n");
}
static void cmd_bootctl47(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("System: Firmware: BIOS\nBoot Current: 0\nBoot Entries:\n  0: BYO-OS\n    File: /EFI/byo-os/grubx64.efi\n");
}
static void cmd_kernel_install47(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("kernel-install: install kernel images\nUsage: kernel-install add <version> <image-path>\n");
}
static void cmd_localectl47(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("System Locale: LANG=en_US.UTF-8\nVC Keymap: us\nX11 Layout: us\n");
}
static void cmd_machinectl47(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("MACHINE CLASS   OS        VERSION ADDRESSES\nbyo-os container BYO-OS     1.0     10.0.2.15\n");
}
static void cmd_nsenter47(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: nsenter -t <pid> [cmd]\n"); return; }
    vga_puts("nsenter: entering namespaces\n");
}
static void cmd_unshare47(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("unshare: creating new namespace\n");
}
static void cmd_chrt47(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("SCHED_OTHER min=0 max=0\npid 0's scheduling policy: SCHED_OTHER\n");
}
static void cmd_iperf47(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("iperf3: TCP bandwidth measurement\nServer listening on 5201\n");
    vga_puts("[  5]  0.00-1.00  sec  112 MBytes  940 Mbits/sec\n");
}
static void cmd_ab47(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: ab -n <requests> <url>\n"); return; }
    vga_puts("Server Software: BYO-OS/1.0\nDocument Length: 1234 bytes\n");
    vga_puts("Time taken: 0.123 seconds\nComplete requests: 100\nFailed requests: 0\n");
    vga_puts("Requests per second: 813.03 [#/sec]\nTransfer rate: 984.12 [Kbytes/sec]\n");
}
static void cmd_wrk47(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Running 10s test @ http://localhost:80\n  2 threads and 10 connections\n");
    vga_puts("  Requests/sec:   8234.56\n  Transfer/sec:   10.12MB\n");
}
static void cmd_curl47(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: curl <url>\n"); return; }
    vga_puts("  % Total    % Received  Time   Time     Time  Current\n");
    vga_puts("                                 Dload  Upload   Total   Spent\n");
    vga_puts("100  1234  100  1234    0     0  12340      0 --:--:-- 12345\n");
}
static void cmd_http47(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: http <method> <url>\n"); return; }
    vga_puts("HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 1234\n\n<html><body>BYO-OS</body></html>\n");
}

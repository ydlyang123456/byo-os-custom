/* ===== Batch 51: Advanced System Management + Monitoring ===== */

/* 1. systemd-analyze */
static void cmd_systemd_analyze51(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("systemd-analyze - System Boot-Up Analysis\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("Startup: kernel 32ms + userspace 128ms = 160ms\n");
    vga_puts("  Firmware: 4ms  Bootloader: 8ms\n");
    vga_puts("  Kernel: 20ms  Initrd: 12ms  Userspace: 116ms\n");
    vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
    vga_puts("graphical.target reached after 160ms\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("Service times: network 12ms fs 8ms shell 4ms\n");
}

/* 2. systemd-cgls */
static void cmd_systemd_cgls51(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("systemd-cgls - Cgroup Hierarchy\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("/\n+-user.slice\n| +-shell (pid=1)\n");
    vga_puts("+-system.slice\n| +-network [running]\n");
    vga_puts("| +-filesystem [running]\n| +-timer [running]\n");
    vga_puts("+-kthread.slice\n  +-kworker/0:1 [running]\n");
}

/* 3. systemd-cgtop */
static void cmd_systemd_cgtop51(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    uint32_t sec = timer_get_seconds();
    char buf[32];
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("systemd-cgtop - Cgroup Resource Usage\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("Path            Tasks  %%CPU   Memory\n");
    vga_puts("/user.slice      3     2.1    1.2M\n");
    vga_puts("/system.slice    5     4.3    2.4M\n");
    vga_puts("/kthread.slice   1     0.1    256K\n");
    itoa(sec, buf, 10);
    vga_puts("Uptime: "); vga_puts(buf); vga_puts("s\n");
}

/* 4. atop */
static void cmd_atop51(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    uint32_t sec = timer_get_seconds();
    uint32_t free_pages = pmm_get_free_pages();
    uint32_t total_pages = pmm_get_total_pages();
    char buf[32];
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    vga_puts("atop - Advanced System Monitor\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("CPU: sys 12%% user 8%% irq 2%% idle 78%%\n");
    vga_puts("CPL: avg1=0.50 avg5=0.32 avg15=0.18\n");
    vga_puts("MEM: total ");
    itoa(total_pages * 4, buf, 10); vga_puts(buf);
    vga_puts("K  free ");
        itoa(free_pages * 4, buf, 10); vga_puts(buf); vga_puts("K");
    vga_puts("DSK: sda read 1.2K/s write 840B/s\n");
    vga_puts("NET: eth0 read 12K/s write 8K/s\n");
}

/* 5. glances */
static void cmd_glances51(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    uint32_t free_pages = pmm_get_free_pages();
    uint32_t total_pages = pmm_get_total_pages();
    uint32_t heap_used = heap_get_used();
    char buf[32];
    vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
    vga_puts("Glances - System Monitor\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("CPU [####        ] 32.1%%\n");
    vga_puts("MEM [##          ] ");
    itoa(total_pages * 4 / 1024, buf, 10); vga_puts(buf);
    vga_puts("MB / ");
        itoa(free_pages * 4 / 1024, buf, 10); vga_puts(buf); vga_puts("K");
    vga_puts("HEAP used: "); itoa(heap_used, buf, 10); vga_puts(buf); vga_puts(" bytes\n");
}

/* 6. dstat */
static void cmd_dstat51(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("dstat - System Resource Statistics\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("usr sys irq idl| read writ| recv send| used free\n");
    vga_puts("  8  12   2  78|  1K 840B|  12K   8K| 2.4M  25M\n");
    vga_puts(" 10  11   1  77| 800 920B|  10K   9K| 2.4M  25M\n");
}

/* 7. vmstat */
static void cmd_vmstat51(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    uint32_t free_pages = pmm_get_free_pages();
    uint32_t total_pages = pmm_get_total_pages();
    char buf[32];
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("vmstat - Virtual Memory Statistics\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts(" r  b   free  buff cache   si   so    bi    bo\n");
    vga_puts(" 1  0  26112    64   128    0    0     8    4\n");
    vga_puts(" 0  0  26112    64   128    0    0     2    1\n");
    vga_puts("Total: ");
    itoa(total_pages, buf, 10); vga_puts(buf);
    vga_puts("  Free: ");
    itoa(free_pages, buf, 10); vga_puts(buf);
    vga_puts("  Used: ");
    itoa(total_pages > free_pages ? (total_pages - free_pages) * 4 : 0, buf, 10);
        vga_puts(buf); vga_puts("K");
}

/* 8. iostat */
static void cmd_iostat51(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("iostat - IO Statistics\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("Dev   r/s  w/s  rkB/s  wkB/s  await\n");
    vga_puts("sda   1.20 0.80  4.80   3.20   2.50\n");
    vga_puts("CPU  %%usr %%nice %%sys %%iowait %%idle\n");
    vga_puts("all  8.00  0.00 12.00  0.50  77.50\n");
}

/* 9. mpstat */
static void cmd_mpstat51(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("mpstat - Multiprocessor Statistics\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("CPU  %%usr %%sys %%iowait %%irq %%soft %%idle\n");
    vga_puts("all   8.00 12.00  0.50  2.00  1.00  76.50\n");
    vga_puts("  0   8.00 12.00  0.50  2.00  1.00  76.50\n");
}

/* 10. sar */
static void cmd_sar51(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    uint32_t sec = timer_get_seconds();
    char buf[32];
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("sar - System Activity Report\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("CPU  %%user %%system %%iowait %%idle\n");
    vga_puts("all   8.00  12.00   0.50   79.50\n");
    vga_puts("all   9.00  11.50   0.80   78.70\n");
    vga_puts("all   7.50  13.00   0.30   79.20\n");
}

/* 11. iperf3 */
static void cmd_iperf51(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
    vga_puts("iperf3 - Network Bandwidth Test\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("Server listening on port 5201\n");
    vga_puts("0.00-3.00 sec  3.65 MBytes  10.2 Mbps sender\n");
    vga_puts("0.00-3.00 sec  3.53 MBytes  9.9 Mbps receiver\n");
}

/* 12. nc */
static void cmd_nc51(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
    vga_puts("nc - Netcat Network Tool\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("Listening on port 8080\n");
    vga_puts("Connection from 192.168.1.100:12345\n");
    vga_puts("Hello from client!\n");
}

/* 13. socat */
static void cmd_socat51(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
    vga_puts("socat - Multipurpose Relay\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("TCP:127.0.0.1:8080 connected to TCP:10.0.0.1:80\n");
}

/* 14. lzip - lzip compression tool */
static void cmd_lzip51(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
        vga_puts("Usage: lzip <file> [-1..9]\n");
        vga_puts("  lzip - Lempel-Ziv compression tool\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("lzip - Lempel-Ziv Compression\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("Compressing: "); vga_puts(args[1]); vga_puts("\n");
    vga_puts("  Input:  102400 bytes\n");
    vga_puts("  Output:  38400 bytes (ratio 37.5%)\n");
    vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
    vga_puts("Compression complete: "); vga_puts(args[1]); vga_puts(".lz\n");
}

/* 15. pigz - parallel gzip */
static void cmd_pigz51(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
        vga_puts("Usage: pigz <file> [-p threads]\n");
        vga_puts("  pigz - Parallel gzip compression\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("pigz - Parallel GZip\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("Using 4 threads\n");
    vga_puts("Compressing: "); vga_puts(args[1]); vga_puts("\n");
    vga_puts("  100.00% - 102400 bytes -> 35200 bytes\n");
    vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
    vga_puts("pigz: "); vga_puts(args[1]); vga_puts(".gz created\n");
}

/* 16. tig - text-mode git interface */
static void cmd_tig51(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("tig - Text-mode Interface for Git\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("[commit] a1b2c3d Initial commit\n");
    vga_puts("[commit] d4e5f6a Add batch51 functions\n");
    vga_puts("[commit] g7h8i9j Fix memory manager bug\n");
    vga_puts("[commit] j0k1l2m Update build system\n");
    vga_set_color(VGA_YELLOW, VGA_BLACK);
    vga_puts("Branch: main  Ahead: 0  Behind: 0\n");
}

/* 17. lazygit - git terminal UI */
static void cmd_lazygit51(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
    vga_puts("lazygit - Git Terminal UI\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("Stashed: 0  Staged: 0  Unstaged: 0\n");
    vga_puts("Commits:\n");
    vga_puts(" * a1b2c3d  Initial commit\n");
    vga_puts("   d4e5f6a  Add batch51 functions\n");
    vga_puts("   g7h8i9j  Fix memory manager bug\n");
    vga_puts("Branches:\n");
    vga_puts(" > main\n");
    vga_puts("   develop\n");
}

/* 18. topgrade - system upgrade tool */
static void cmd_topgrade51(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("topgrade - System Upgrade Tool\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("Upgrade? [Y/n] Y\n");
    vga_puts("  [System] ... upgraded\n");
    vga_puts("  [Pacman] ... upgraded\n");
    vga_puts("  [AUR]   ... nothing to do\n");
    vga_puts("  [Flatpak] ... updated 3 packages\n");
    vga_puts("  [Snap]  ... up-to-date\n");
    vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
    vga_puts("Topgrade finished. Upgraded 5 packages.\n");
}

/* 19. mtr - network diagnostic tool */
static void cmd_mtr51(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
        vga_puts("Usage: mtr <host>\n");
        vga_puts("  mtr - Network path diagnostic tool\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("mtr - My Traceroute\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("HOST                    Loss%%  Snt   Last   Avg  Best\n");
    vga_puts("1 gateway.local         0.0     3   1.2   1.1   0.9\n");
    vga_puts("2 10.0.0.1              0.0     3   2.3   2.5   2.1\n");
    vga_puts("3 isp-router.net        0.0     3  12.1  11.8  11.2\n");
    vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
    vga_puts("Reachable: "); vga_puts(args[1]); vga_puts("\n");
}

/* 20. fio - disk IO benchmark */
static void cmd_fio51(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("fio - Flexible IO Tester\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("read:  IOPS=1.2K, BW=4800KiB/s\n");
    vga_puts("  slat (usec): min=2, max=180, avg=8.50\n");
    vga_puts("  clat (usec): min=15, max=1200, avg=102.30\n");
    vga_puts("write: IOPS=800, BW=3200KiB/s\n");
    vga_puts("  slat (usec): min=3, max=200, avg=12.20\n");
    vga_puts("  clat (usec): min=20, max=1500, avg=156.80\n");
}

/* 21. ddrescue - disk recovery tool */
static void cmd_ddrescue51(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 3) {
        vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
        vga_puts("Usage: ddrescue <source> <dest> [logfile]\n");
        vga_puts("  ddrescue - Data recovery from failing disks\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("ddrescue - Disk Data Rescue\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("Source: "); vga_puts(args[1]); vga_puts("\n");
    vga_puts("Dest:   "); vga_puts(args[2]); vga_puts("\n");
    vga_puts("  rescued:   1024000/1024000 bytes (100%%)\n");
    vga_puts("  errors:    0\n");
    vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
    vga_puts("Rescue complete.\n");
}

/* 22. testdisk - disk repair tool */
static void cmd_testdisk51(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("testdisk - Disk Partition Recovery\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("Analyzing /dev/sda...\n");
    vga_puts("  Partition        Status\n");
    vga_puts("  /dev/sda1  [OK]  ext4\n");
    vga_puts("  /dev/sda2  [OK]  swap\n");
    vga_puts("  /dev/sda3  [!!]  ntfs (bad MBR)\n");
    vga_set_color(VGA_YELLOW, VGA_BLACK);
    vga_puts("Write partition table? [Y/N]: Y\n");
    vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
    vga_puts("Partition table written successfully.\n");
}

/* 23. photo_rec - file recovery */
static void cmd_photo_rec51(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("PhotoRec - File Recovery Tool\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("Scanning /dev/sda1...\n");
    vga_puts("  jpg:  128 files recovered\n");
    vga_puts("  png:   45 files recovered\n");
    vga_puts("  pdf:   12 files recovered\n");
    vga_puts("  txt:   87 files recovered\n");
    vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
    vga_puts("Recovery complete: 272 files saved.\n");
}

/* 24. clamscan - virus scanner */
static void cmd_clamscan51(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
        vga_puts("Usage: clamscan <path>\n");
        vga_puts("  clamscan - ClamAV virus scanner\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("clamscan - ClamAV Antivirus Scanner\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("Scanning: "); vga_puts(args[1]); vga_puts("\n");
    vga_puts("  Loaded: 8562120 signatures\n");
    vga_puts("  Scanned: 1247 files, 34028K\n");
    vga_puts("  Infected: 0\n");
    vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
    vga_puts("Result: CLEAN\n");
}

/* 25. rkhunter - rootkit detector */
static void cmd_rkhunter51(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("rkhunter - Rootkit Hunter\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("Checking system commands...\n");
    vga_puts("  /bin/ls        [OK]\n");
    vga_puts("  /bin/ps        [OK]\n");
    vga_puts("  /usr/bin/netstat [OK]\n");
    vga_puts("Checking rootkits...\n");
    vga_puts("  No rootkits detected.\n");
    vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
    vga_puts("System clean. No rootkits found.\n");
}

/* 26. chkrootkit - rootkit detector */
static void cmd_chkrootkit51(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("chkrootkit - Checking Rootkits\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("Checking md... not found\n");
    vga_puts("Checking indshell... not found\n");
    vga_puts("Checking chfn... not found\n");
    vga_puts("Checking lkm... not found\n");
    vga_puts("Checking ssh... not found\n");
    vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
    vga_puts("No rootkits detected.\n");
}

/* 27. tripwire - file integrity checker */
static void cmd_tripwire51(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("tripwire - File Integrity Monitor\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("Policy: /etc/tripwire/policy\n");
    vga_puts("Database: /var/lib/tripwire/db\n");
    vga_puts("  /bin/login    [OK]\n");
    vga_puts("  /etc/passwd   [MODIFIED]\n");
    vga_puts("  /etc/shadow   [OK]\n");
    vga_set_color(VGA_YELLOW, VGA_BLACK);
    vga_puts("Summary: 2 checked, 1 modified, 0 errors\n");
}

/* 28. aide - intrusion detection */
static void cmd_aide51(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("aide - Advanced Intrusion Detection\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("AIDE database: /var/lib/aide/aide.db\n");
    vga_puts("  Compared 1542 entries\n");
    vga_puts("  New:      3 files\n");
    vga_puts("  Modified: 1 files\n");
    vga_puts("  Removed:  0 files\n");
    vga_set_color(VGA_YELLOW, VGA_BLACK);
    vga_puts("Warning: /etc/ssh/sshd_config changed.\n");
}

/* 29. ossec - host intrusion detection */
static void cmd_ossec51(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("ossec - Open Source HIDS\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("Active Response: enabled\n");
    vga_puts("Log monitoring:  /var/log/auth.log\n");
    vga_puts("Alerts today: 12\n");
    vga_puts("  Critical: 0  High: 1  Medium: 4  Low: 7\n");
    vga_puts("Last alert: SSH brute force from 10.0.0.50\n");
    vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
    vga_puts("HIDS status: active, monitoring 3 sources.\n");
}

/* 30. openvas - vulnerability scanner */
static void cmd_openvas51(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("OpenVAS - Vulnerability Scanner\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("Target: 192.168.1.0/24\n");
    vga_puts("Hosts alive: 5/256\n");
    vga_puts("Vulnerabilities:\n");
    vga_puts("  Critical: 0  High: 2  Medium: 5  Low: 12\n");
    vga_puts("  SSL/TLS: weak cipher RC4 (CVE-2013-2566)\n");
    vga_set_color(VGA_YELLOW, VGA_BLACK);
    vga_puts("Scan complete. 19 vulnerabilities found.\n");
}

/* 31. nessus - vulnerability scanner */
static void cmd_nessus51(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("Nessus - Vulnerability Scanner\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("Scan policy: Advanced Network Scan\n");
    vga_puts("Targets: 192.168.1.1-50\n");
    vga_puts("Results:\n");
    vga_puts("  Critical: 1  High: 3  Medium: 8  Info: 24\n");
    vga_puts("  #1 [CRITICAL] SMBv1 enabled (MS17-010)\n");
    vga_set_color(VGA_YELLOW, VGA_BLACK);
    vga_puts("Scan complete in 42 seconds.\n");
}

/* 32. wireshark - network protocol analyzer */
static void cmd_wireshark51(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("Wireshark - Network Protocol Analyzer\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("Capture on eth0...\n");
    vga_puts("Frame 1: 60 bytes on wire\n");
    vga_puts("  ETH: AA:BB:CC:DD:EE:FF -> 11:22:33:44:55:66\n");
    vga_puts("  IP:  192.168.1.100 -> 93.184.216.34\n");
    vga_puts("  TCP: src=45231 dst=80 seq=1 ack=1\n");
    vga_puts("  HTTP: GET /index.html HTTP/1.1\n");
    vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
    vga_puts("Packets captured: 1247  Displayed: 1247\n");
}

/* 33. tcpdump - network packet capture */
static void cmd_tcpdump51(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("tcpdump - Network Packet Capture\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("listening on eth0, link-type EN10MB\n");
    vga_puts("12:01:01 IP 192.168.1.10 > 93.184.216.34: Flags [S]\n");
    vga_puts("12:01:01 IP 93.184.216.34 > 192.168.1.10: Flags [S.]\n");
    vga_puts("12:01:02 IP 192.168.1.10 > 93.184.216.34: Flags [P] 80\n");
    vga_puts("12:01:02 IP 93.184.216.34 > 192.168.1.10: Flags [P] 4096\n");
    vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
    vga_puts("12 packets captured, 12 packets received\n");
}

/* 34. nmap - network scanner */
static void cmd_nmap51(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
        vga_puts("Usage: nmap <host> [-sV] [-O]\n");
        vga_puts("  nmap - Network port scanner\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("Nmap - Network Mapper\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("Scanning "); vga_puts(args[1]); vga_puts("...\n");
    vga_puts("  PORT     STATE SERVICE  VERSION\n");
    vga_puts("  22/tcp   open  ssh      OpenSSH 9.1\n");
    vga_puts("  80/tcp   open  http     nginx/1.24\n");
    vga_puts("  443/tcp  open  https    nginx/1.24\n");
    vga_puts("  OS: Linux 5.x (98%% confidence)\n");
}

/* 35. masscan - mass port scanner */
static void cmd_masscan51(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
        vga_puts("Usage: masscan <target> [-p ports]\n");
        vga_puts("  masscan - Fastest mass port scanner\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("masscan - Mass Port Scanner\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("Target: "); vga_puts(args[1]); vga_puts("\n");
    vga_puts("Rate: 10000 packets/sec\n");
    vga_puts("  80/tcp    open  http\n");
    vga_puts("  443/tcp   open  https\n");
    vga_puts("  8080/tcp  open  http-proxy\n");
    vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
    vga_puts("Scan complete: 3 ports open on 1 host.\n");
}

/* 36. zmap - network scanner */
static void cmd_zmap51(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
        vga_puts("Usage: zmap <port> <target>\n");
        vga_puts("  zmap - Single-packet network scanner\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("zmap - Single-Packet Network Scanner\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("Scanning port "); vga_puts(args[1]); vga_puts("\n");
    vga_puts("  Probe module: tcp_synscan\n");
    vga_puts("  Rate: 100000 packets/sec\n");
    vga_puts("  Hosts up: 245\n");
    vga_puts("  Hosts responding: 18\n");
    vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
    vga_puts("Scan complete in 8 seconds.\n");
}

/* 37. recon_ng - OSINT framework */
static void cmd_recon_ng51(int argc, char args[][CMD_MAX_LEN]) {
    (void)argc; (void)args;
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("Recon-ng - OSINT Framework\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("[recon-ng] > show domains\n");
    vga_puts("  Row  Host             Module\n");
    vga_puts("  1    example.com      recon/whois\n");
    vga_puts("  2    target.org       recon/dns\n");
    vga_puts("  3    victim.net       recon/whois\n");
    vga_puts("3 rows returned.\n");
    vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
    vga_puts("OSINT framework ready.\n");
}

/* 38. amass - subdomain enumeration */
static void cmd_amass51(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
        vga_puts("Usage: amass enum -d <domain>\n");
        vga_puts("  amass - Subdomain enumeration tool\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("Amass - Subdomain Enumeration\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("Domain: "); vga_puts(args[1]); vga_puts("\n");
    vga_puts("  api."); vga_puts(args[1]); vga_puts("\n");
    vga_puts("  mail."); vga_puts(args[1]); vga_puts("\n");
    vga_puts("  dev."); vga_puts(args[1]); vga_puts("\n");
    vga_puts("  staging."); vga_puts(args[1]); vga_puts("\n");
    vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
    vga_puts("Found 4 subdomains.\n");
}

/* 39. dnsrecon - DNS enumeration */
static void cmd_dnsrecon51(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
        vga_puts("Usage: dnsrecon -d <domain>\n");
        vga_puts("  dnsrecon - DNS reconnaissance tool\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("dnsrecon - DNS Reconnaissance\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("Domain: "); vga_puts(args[1]); vga_puts("\n");
    vga_puts("  A     93.184.216.34\n");
    vga_puts("  MX    mail."); vga_puts(args[1]); vga_puts(" 10\n");
    vga_puts("  NS    ns1."); vga_puts(args[1]); vga_puts("\n");
    vga_puts("  TXT   \"v=spf1 include:_spf.google.com ~all\"\n");
    vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
    vga_puts("DNS enumeration complete.\n");
}

/* 40. enum4linux - SMB enumeration */
static void cmd_enum4linux51(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) {
        vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
        vga_puts("Usage: enum4linux <host>\n");
        vga_puts("  enum4linux - SMB/NetBIOS enumeration\n");
        return;
    }
    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("enum4linux - SMB Enumeration\n");
    vga_set_color(VGA_WHITE, VGA_BLACK);
    vga_puts("Target: "); vga_puts(args[1]); vga_puts("\n");
    vga_puts("  NetBIOS: FILESRV\n");
    vga_puts("  Workgroup: WORKGROUP\n");
    vga_puts("  Users: admin, guest, administrator\n");
    vga_puts("  Shares: IPC$, C$, PUBLIC\n");
    vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
    vga_puts("SMB enumeration complete.\n");
}
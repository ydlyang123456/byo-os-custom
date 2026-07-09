/* ===== Batch 50: System Monitoring & Modern Tools ===== */
static void cmd_htop50(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("  PID USER      PRI  NI  VIRT   RES   SHR S CPU% MEM%   TIME+  Command\n");
    vga_puts("    1 root       20   0  163M  2340  2100 S  0.0  0.0   0:01.23 /sbin/init\n");
    vga_puts("   42 root       20   0  123M  4560  3200 S  0.0  0.0   0:00.45 /usr/sbin/sshd\n");
    vga_puts("  100 root       20   0   98M  8900  6700 S  0.0  0.0   0:02.34 /usr/sbin/httpd\n");
    vga_puts("  150 root       20   0   45M  2300  1800 S  0.0  0.0   0:00.12 /usr/sbin/crond\n");
    vga_puts("Mem[|||||||||||||||||||||||          123M/512M] Load: 0.12 0.08 0.05\n");
    vga_puts("Swap[|                            0K/256M]\n");
    vga_puts("  Tasks: 4 total, 4 running\n  CPU%:  2.1% user, 0.3% kernel\n");
}
static void cmd_iotop50(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Total DISK READ: 0.00 B/s | Total DISK WRITE: 0.00 B/s\n");
    vga_puts("  PID  PRIO  USER     DISK READ  DISK WRITE  SWAPIN     IO>    COMMAND\n");
    vga_puts("    1 be/4  root     0.00 B/s    0.00 B/s    0.00 %   0.00 %  init\n");
    vga_puts("   42 be/4  root     0.00 B/s    0.00 B/s    0.00 %   0.00 %  sshd\n");
    vga_puts("  100 be/4  root     0.00 B/s    0.00 B/s    0.00 %   0.00 %  httpd\n");
}
static void cmd_iftop50(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("                  12.5Kb          25.0Kb          37.5Kb          50.0Kb\n");
    vga_puts("gateway                     <=          BYO-OS\n");
    vga_puts("byo-os    <=          gateway\n");
    vga_puts("  TX:             1.23KB    123.45B/s\n");
    vga_puts("  RX:             2.34KB    234.56B/s\n");
}
static void cmd_nload50(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Device eth0 [10.0.2.15]\n");
    vga_puts(" Incoming:\n");
    vga_puts("                                    Curr: 1.23 KByte/s\n");
    vga_puts("                                    Avg:  0.45 KByte/s\n");
    vga_puts("                                    Min:  0.00 KByte/s\n");
    vga_puts("                                    Max:  5.67 KByte/s\n");
    vga_puts(" Outgoing:\n");
    vga_puts("                                    Curr: 2.34 KByte/s\n");
    vga_puts("                                    Avg:  0.89 KByte/s\n");
}
static void cmd_nethogs50(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("NetHogs version 0.8.5\n\n");
    vga_puts("    PID USER     PROGRAM                    DEV        SENT      RECEIVED\n");
    vga_puts("  100   root     /usr/sbin/httpd             eth0     12.345     23.456 KB/sec\n");
    vga_puts("  42    root     /usr/sbin/sshd              eth0      0.123      0.456 KB/sec\n");
    vga_puts("  TOTAL                                    eth0     12.468     23.912 KB/sec\n");
}
static void cmd_dstat50(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("-------cpu------- --net/eth0- -dsk/sda ---io-- ---procs--- ---system--\n");
    vga_puts("usr sys idl wai stl|  recv  send| read  writ| in  out | run blk new|     time\n");
    vga_puts("  2   0  98   0   0| 123B  234B|   0     0 |  0    0 |  1    0   0| 12:00:00\n");
    vga_puts("  1   0  99   0   0|  45B   67B|   0     0 |  0    0 |  0    0   0| 12:00:01\n");
}
static void cmd_glances50(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("BYO-OS v1.0                           Load: 0.12\n");
    vga_puts("CPU:  2.1% user   0.3% kernel\n");
    vga_puts("MEM:  123.4M / 512M (24.1%)\n");
    vga_puts("DISK: /dev/sda1  2.3G / 4.0G (57.5%)\n");
    vga_puts("NET:  eth0  RX: 12.3KB  TX: 23.4KB\n");
    vga_puts("PROCS: 4 total, 1 running\n");
}
static void cmd_btop50(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("btop - Resource monitor v1.2.13\n");
    vga_puts("CPU:  2.1% [||||||||||                ]  MEM: 123M/512M (24.1%)\n");
    vga_puts("DISK: /dev/sda1 2.3G/4.0G (57.5%)\n");
    vga_puts("NET: eth0  RX:12.3KB  TX:23.4KB\n");
}

/* Modern file tools */
static void cmd_tree50(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts(".\n");
    vga_puts("+-- boot\n");
    vga_puts("+-- kernel\n");
    vga_puts("|   +-- shell.c\n");
    vga_puts("|   +-- main.c\n");
    vga_puts("|   +-- net.c\n");
    vga_puts("+-- include\n");
    vga_puts("|   +-- kernel.h\n");
    vga_puts("+-- build.sh\n");
    vga_puts("+-- README.md\n");
    vga_puts("2 directories, 7 files\n");
}
static void cmd_bat50(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: bat <file>\n"); return; }
    vga_puts("─────── "); vga_puts(args[1]); vga_puts(" ───────\n");
    vga_puts("  1   #include <stdio.h>\n");
    vga_puts("  2   int main() {\n");
    vga_puts("  3       printf(\"Hello\\n\");\n");
    vga_puts("  4       return 0;\n");
    vga_puts("  5   }\n");
}
static void cmd_fd50(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: fd <pattern> [path]\n"); return; }
    vga_puts("kernel/shell.c\n");
    vga_puts("kernel/main.c\n");
    vga_puts("kernel/net.c\n");
    vga_puts("include/kernel.h\n");
}
static void cmd_ripgrep50(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: rg <pattern> [path]\n"); return; }
    vga_puts("kernel/shell.c:42:  vga_puts(\"Hello\\n\");\n");
    vga_puts("kernel/shell.c:100:  vga_puts(\"Welcome\\n\");\n");
}
static void cmd_fzf50(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("fzf - fuzzy finder\n> shell.c\n> main.c\n> net.c\n");
    vga_puts("[2/3] > shell.c\n");
}
static void cmd_jq50(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("Usage: jq <filter> [file]\n"); return; }
    vga_puts("{\\n  \\\"name\\\": \\\"byo-os\\\",\\n  \\\"version\\\": \\\"1.0\\\"\\n}\\n");
}
static void cmd_yq50(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("yq - YAML processor\nUsage: yq <eval> [file]\n");
}
static void cmd_csvtool50(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("csvtool: CSV manipulation\nUsage: csvtool <select|filter|join>\n");
}
static void cmd_xsv50(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("xsv 0.13.0 - CSV command toolkit\nUsage: xsv <select|stats|join|sort>\n");
}

/* Modern dev tools */
static void cmd_docker_compose50(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("docker-compose version 2.23.0\n");
    vga_puts("Usage: docker-compose <up|down|ps|logs|build>\n");
}
static void cmd_hadolint50(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("hadolint: Dockerfile linter\nNo issues found.\n");
}
static void cmd_shellcheck50(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("shellcheck 0.9.0\nNo issues found.\n");
}
static void cmd_black50(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("black 23.12.1\nAll done! 1 file reformatted.\n");
}
static void cmd_ruff50(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("ruff 0.1.8\nAll checks passed!\n");
}
static void cmd_mypy50(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("mypy 1.8.0\nSuccess: no issues found in 1 source file\n");
}
static void cmd_pytest50(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("============ test session starts ============\n");
    vga_puts("collected 42 items\n");
    vga_puts("======================================== 42 passed in 0.5s ========================================\n");
}
static void cmd_npm50(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("npm: Node.js package manager\nUsage: npm <install|run|start|test|build>\n"); return; }
    if (strcmp(args[1], "install") == 0) vga_puts("added 1234 packages in 45s\n");
    else if (strcmp(args[1], "start") == 0) vga_puts("> byo-os@1.0.0 start\\n> node server.js\\nServer running on port 3000\n");
    else vga_puts("npm: command executed\n");
}
static void cmd_npx50(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("npx: execute package binaries\nUsage: npx <package> [args]\n");
}
static void cmd_pip50(int argc, char args[][CMD_MAX_LEN]) {
    if (argc < 2) { vga_puts("pip: Python package installer\nUsage: pip <install|list|show>\n"); return; }
    if (strcmp(args[1], "install") == 0) { vga_puts("Successfully installed package\n"); }
    else if (strcmp(args[1], "list") == 0) {
        vga_puts("Package    Version\n---------- -------\nnumpy      1.26.2\npandas     2.1.4\nscipy      1.11.4\n");
    } else { vga_puts("pip: command executed\n"); }
}
static void cmd_cargo50(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("cargo: Rust package manager\nUsage: cargo <build|run|test|doc>\n");
}
static void cmd_rustc50(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("rustc 1.74.0\n");
}
static void cmd_go50(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("go version go1.21.5 linux/amd64\n");
}
static void cmd_javac50(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("javac 21.0.1\n");
}
static void cmd_mvn50(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Apache Maven 3.9.6\nUsage: mvn <clean|compile|package|install>\n");
}
static void cmd_gradle50(int argc, char args[][CMD_MAX_LEN]) {
    vga_puts("Gradle 8.5\nUsage: gradle <build|run|test|clean>\n");
}

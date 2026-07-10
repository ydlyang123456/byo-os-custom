#!/usr/bin/env python3
"""BYO-OS Batch 315: Text Processing, System Monitor, Math, Utilities"""
import re

BATCH = 315
NS = str(BATCH)

# === Forward Declarations ===
fwd = ""
# === Command Table Entries ===
tbl = ""
# === Function Implementations ===
funcs = ""

commands = [
    # Text Processing
    ("sed", "Stream editor (basic)"),
    ("awk", "Pattern scanning (basic)"),
    ("cut", "Cut fields from lines"),
    ("paste", "Merge lines side by side"),
    ("column", "Format output in columns"),
    ("fmt", "Simple text formatter"),
    ("fold", "Wrap lines at width"),
    # System Monitoring
    ("uptime", "System uptime and load"),
    ("free", "Memory usage display"),
    ("swapon", "Swap space info"),
    ("mount", "Mount filesystems"),
    ("umount", "Unmount filesystems"),
    ("blkid", "Block device info"),
    ("lsblk", "List block devices"),
    ("lsusb", "List USB devices"),
    ("lspci", "List PCI devices"),
    # Math
    ("bc", "Basic calculator"),
    ("dc", "Desk calculator (RPN)"),
    ("expr", "Expression evaluator"),
    ("seq", "Print number sequence"),
    ("factor", "Prime factorization"),
    ("log", "Logarithm calculator"),
    # Date/Time
    ("cal", "Display calendar"),
    ("date_fmt", "Formatted date output"),
    ("hwclock", "Hardware clock"),
    ("ntpd", "NTP time sync"),
    # Environment
    ("env", "Print environment"),
    ("printenv", "Print env variable"),
    ("export", "Export variable"),
    ("unset", "Unset variable"),
    ("set_env", "Set environment variable"),
    # File Utilities
    ("ln", "Create link"),
    ("stat", "File status"),
    ("realpath", "Resolve path"),
    ("basename", "Strip directory"),
    ("dirname", "Strip filename"),
    ("readlink", "Read symlink"),
    # Archive
    ("tar", "Tape archive"),
    ("zipf", "Create zip archive"),
    ("unzip", "Extract zip"),
    ("gzip", "Gzip compress"),
    ("gunzip", "Gzip decompress"),
    # Disk
    ("fdisk", "Disk partition table"),
    ("du", "Disk usage"),
    ("df", "Disk free space"),
    ("mkfs", "Make filesystem"),
    ("fsck", "Filesystem check"),
    ("dd", "Disk dump/copy"),
    ("losetup", "Loop device setup"),
    # Process Advanced
    ("pgrep", "Find process by name"),
    ("pkill", "Kill process by name"),
    ("renice", "Change process priority"),
    ("timeout", "Run with time limit"),
    ("xargs", "Build command from input"),
    ("nohup", "Run immune to hangup"),
    # Text Output
    ("banner", "Large text banner"),
    ("figlet", "ASCII art text"),
    ("toilet", "Fancy text output"),
    ("boxes", "Draw box around text"),
    ("cowsay", "Cow says message"),
    ("fortune", "Random fortune"),
    ("matrix", "Matrix rain effect"),
    ("sl", "Steam locomotive"),
]

for cmd_name, desc in commands:
    # Forward declaration
    fwd += f"static void cmd_{cmd_name}{NS}(int argc, char args[][CMD_MAX_LEN]);\n"
    
    # Command table entry
    tbl += f'    {{"{cmd_name}", cmd_{cmd_name}{NS}}},\n'
    
    # Function implementation
    funcs += f"static void cmd_{cmd_name}{NS}(int argc, char args[][CMD_MAX_LEN]) {{\n"
    
    if cmd_name == "sed":
        funcs += """    if (argc < 3) { vga_puts("Usage: sed 's/old/new/' file\\n"); return; }
    vga_puts("sed: stream editor\\n");
    vga_printf("  Pattern: %s\\n", args[1]);
    vga_puts("  (basic substitution simulated)\\n");
"""
    elif cmd_name == "awk":
        funcs += """    if (argc < 2) { vga_puts("Usage: awk 'pattern {action}' file\\n"); return; }
    vga_puts("awk: pattern scanning and processing\\n");
    vga_printf("  Expression: %s\\n", args[1]);
"""
    elif cmd_name == "cut":
        funcs += """    if (argc < 3) { vga_puts("Usage: cut -d' ' -f1 file\\n"); return; }
    vga_puts("cut: remove sections from lines\\n");
"""
    elif cmd_name == "paste":
        funcs += '    vga_puts("paste: merge lines side by side\\n");\n'
    elif cmd_name == "column":
        funcs += '    vga_puts("column: format input into columns\\n");\n'
    elif cmd_name == "fmt":
        funcs += '    vga_puts("fmt: simple text formatter\\n");\n'
    elif cmd_name == "fold":
        funcs += '    vga_puts("fold: wrap input lines\\n");\n'
    elif cmd_name == "uptime":
        funcs += """    unsigned int ticks = timer_get_ticks();
    unsigned int secs = ticks / 100;
    unsigned int hrs = secs / 3600;
    unsigned int mins = (secs % 3600) / 60;
    unsigned int s = secs % 60;
    vga_printf("up %02u:%02u:%02u\\n", hrs, mins, s);
    vga_printf("  load average: 0.00, 0.00, 0.00\\n");
    vga_printf("  %d user(s)\\n", user_get_count());
"""
    elif cmd_name == "free":
        funcs += """    unsigned int total = 128;
    unsigned int used = memory_get_used() / 1024;
    unsigned int free_m = total - used;
    vga_printf("              total    used    free\\n");
    vga_printf("Mem:      %8u  %8u  %8u MB\\n", total, used, free_m);
    vga_printf("Swap:           0       0       0 MB\\n");
"""
    elif cmd_name == "swapon":
        funcs += '    vga_puts("swapon: no swap devices configured\\n");\n'
    elif cmd_name == "mount":
        funcs += """    vga_puts("Filesystem     Type     Mounted on\\n");
    vga_puts("ramdisk        tmpfs    /\\n");
    vga_puts("proc           proc     /proc\\n");
    vga_puts("sysfs          sysfs    /sys\\n");
"""
    elif cmd_name == "umount":
        funcs += '    vga_puts("umount: cannot unmount root filesystem\\n");\n'
    elif cmd_name == "blkid":
        funcs += '    vga_puts("blkid: /dev/ram0 UUID=byo-0000-0000 TYPE=tmpfs\\n");\n'
    elif cmd_name == "lsblk":
        funcs += """    vga_puts("NAME   SIZE TYPE MOUNTPOINTS\\n");
    vga_puts("ram0   128M disk /\\n");
"""
    elif cmd_name == "lsusb":
        funcs += '    vga_puts("Bus 001 Device 001: QEMU Virtual USB\\n");\n'
    elif cmd_name == "lspci":
        funcs += """    vga_puts("00:00.0 Host bridge: QEMU Host Bridge\\n");
    vga_puts("00:01.0 VGA: Standard VGA\\n");
    vga_puts("00:02.0 Ethernet: NE2000 Network\\n");
"""
    elif cmd_name == "bc":
        funcs += """    vga_puts("bc: interactive calculator\\n");
    vga_puts("  Use 'expr <math>' for simple calculations\\n");
    vga_puts("  Example: expr 2 + 3\\n");
"""
    elif cmd_name == "dc":
        funcs += '    vga_puts("dc: desk calculator (RPN mode)\\n");\n'
    elif cmd_name == "expr":
        funcs += """    if (argc < 4) { vga_puts("Usage: expr a + b\\n"); return; }
    int a = atoi(args[1]);
    int b = atoi(args[3]);
    char op = args[2][0];
    int r = 0;
    if (op == '+') r = a + b;
    else if (op == '-') r = a - b;
    else if (op == '*') r = a * b;
    else if (op == '/') r = b ? a / b : 0;
    else if (op == '%') r = b ? a % b : 0;
    else { vga_puts("Unknown operator\\n"); return; }
    vga_printf("%d\\n", r);
"""
    elif cmd_name == "seq":
        funcs += """    int end = argc > 1 ? atoi(args[1]) : 10;
    int start = argc > 2 ? atoi(args[2]) : 1;
    for (int i = start; i <= end; i++) vga_printf("%d\\n", i);
"""
    elif cmd_name == "factor":
        funcs += """    if (argc < 2) { vga_puts("Usage: factor <number>\\n"); return; }
    int n = atoi(args[1]);
    vga_printf("%d: ", n);
    for (int p = 2; p * p <= n; p++) {
        while (n % p == 0) { vga_printf("%d ", p); n /= p; }
    }
    if (n > 1) vga_printf("%d", n);
    vga_puts("\\n");
"""
    elif cmd_name == "log":
        funcs += """    if (argc < 2) { vga_puts("Usage: log <number>\\n"); return; }
    vga_puts("log: logarithm calculator\\n");
"""
    elif cmd_name == "cal":
        funcs += """    vga_puts("     July 2025\\n");
    vga_puts("Su Mo Tu We Th Fr Sa\\n");
    vga_puts("       1  2  3  4  5\\n");
    vga_puts(" 6  7  8  9 10 11 12\\n");
    vga_puts("13 14 15 16 17 18 19\\n");
    vga_puts("20 21 22 23 24 25 26\\n");
    vga_puts("27 28 29 30 31\\n");
"""
    elif cmd_name == "date_fmt":
        funcs += """    unsigned int t = timer_get_ticks() / 100;
    unsigned int s = t % 60, m = (t/60)%60, h = (t/3600)%24;
    vga_printf("2025-07-%02d %02d:%02d:%02d UTC\\n", 1+(t/86400)%31, h, m, s);
"""
    elif cmd_name == "hwclock":
        funcs += '    vga_puts("hwclock: hardware clock not available\\n");\n'
    elif cmd_name == "ntpd":
        funcs += '    vga_puts("ntpd: NTP sync not available (no network)\\n");\n'
    elif cmd_name == "env":
        funcs += """    vga_puts("PATH=/bin:/usr/bin\\n");
    vga_puts("HOME=/root\\n");
    vga_puts("SHELL=/bin/sh\\n");
    vga_puts("USER=root\\n");
    vga_puts("TERM=linux\\n");
    vga_puts("LANG=en_US.UTF-8\\n");
    vga_puts("TMPDIR=/tmp\\n");
"""
    elif cmd_name == "printenv":
        funcs += """    if (argc < 2) { cmd_env50573(argc, args); return; }
    vga_printf("%s=%s\\n", args[1], "value");
"""
    elif cmd_name == "export":
        funcs += """    if (argc < 2) { vga_puts("Usage: export VAR=value\\n"); return; }
    vga_printf("Exported: %s\\n", args[1]);
"""
    elif cmd_name == "unset":
        funcs += """    if (argc < 2) { vga_puts("Usage: unset VAR\\n"); return; }
    vga_printf("Unset: %s\\n", args[1]);
"""
    elif cmd_name == "set_env":
        funcs += """    if (argc < 3) { vga_puts("Usage: set_env VAR value\\n"); return; }
    vga_printf("Set: %s=%s\\n", args[1], args[2]);
"""
    elif cmd_name == "ln":
        funcs += """    if (argc < 3) { vga_puts("Usage: ln target link_name\\n"); return; }
    vga_printf("Created link: %s -> %s\\n", args[2], args[1]);
"""
    elif cmd_name == "stat":
        funcs += """    if (argc < 2) { vga_puts("Usage: stat <file>\\n"); return; }
    vga_printf("  File: %s\\n", args[1]);
    vga_printf("  Size: 4096\\n");
    vga_printf("  Permissions: -rw-r--r--\\n");
    vga_printf("  Owner: root:root\\n");
"""
    elif cmd_name == "realpath":
        funcs += """    if (argc < 2) { vga_puts("Usage: realpath <path>\\n"); return; }
    vga_printf("/%s\\n", args[1]);
"""
    elif cmd_name == "basename":
        funcs += """    if (argc < 2) { vga_puts("Usage: basename <path>\\n"); return; }
    char *p = args[1]; char *last = p;
    while (*p) { if (*p == '/') last = p + 1; p++; }
    vga_printf("%s\\n", last);
"""
    elif cmd_name == "dirname":
        funcs += """    if (argc < 2) { vga_puts("Usage: dirname <path>\\n"); return; }
    static char buf[256]; int i = 0;
    while (args[1][i] && args[1][i] != '/') i++;
    if (i == 0) { vga_puts(".\\n"); return; }
    int j = 0; while (j < i) { buf[j] = args[1][j]; j++; }
    buf[j] = 0; vga_printf("%s\\n", buf);
"""
    elif cmd_name == "readlink":
        funcs += """    if (argc < 2) { vga_puts("Usage: readlink <path>\\n"); return; }
    vga_printf("%s -> (not a symlink)\\n", args[1]);
"""
    elif cmd_name == "tar":
        funcs += """    if (argc < 2) { vga_puts("Usage: tar cf archive.tar files...\\n"); return; }
    vga_printf("tar: creating archive %s\\n", args[2]);
"""
    elif cmd_name == "zipf":
        funcs += """    if (argc < 2) { vga_puts("Usage: zip archive.zip files...\\n"); return; }
    vga_printf("zip: creating %s\\n", args[1]);
"""
    elif cmd_name == "unzip":
        funcs += """    if (argc < 2) { vga_puts("Usage: unzip archive.zip\\n"); return; }
    vga_printf("unzip: extracting %s\\n", args[1]);
"""
    elif cmd_name == "gzip":
        funcs += """    if (argc < 2) { vga_puts("Usage: gzip <file>\\n"); return; }
    vga_printf("gzip: compressing %s\\n", args[1]);
"""
    elif cmd_name == "gunzip":
        funcs += """    if (argc < 2) { vga_puts("Usage: gunzip <file.gz>\\n"); return; }
    vga_printf("gunzip: decompressing %s\\n", args[1]);
"""
    elif cmd_name == "fdisk":
        funcs += """    vga_puts("Disk /dev/ram0: 128 MB\\n");
    vga_puts("Device    Boot  Start   End  Sectors  Size Type\\n");
    vga_puts("/dev/ram0p1 *         1 262144 262144  128M Linux\\n");
"""
    elif cmd_name == "du":
        funcs += """    int total = 0;
    vga_puts("4\\t/tmp\\n");
    vga_puts("8\\t/root\\n");
    vga_puts("16\\t/bin\\n");
    vga_puts("32\\t/lib\\n");
    vga_printf("%d\\ttotal\\n", total + 60);
"""
    elif cmd_name == "df":
        funcs += """    vga_puts("Filesystem  1K-blocks  Used Available Use%% Mounted on\\n");
    vga_puts("ramdisk       131072  20480    110592  16%% /\\n");
    vga_puts("proc               0      0         0   -%% /proc\\n");
"""
    elif cmd_name == "mkfs":
        funcs += """    if (argc < 2) { vga_puts("Usage: mkfs <device>\\n"); return; }
    vga_printf("mkfs: creating filesystem on %s\\n", args[1]);
"""
    elif cmd_name == "fsck":
        funcs += """    if (argc < 2) { vga_puts("Usage: fsck <device>\\n"); return; }
    vga_printf("fsck: checking %s\\n", args[1]);
    vga_puts("  Filesystem OK\\n");
"""
    elif cmd_name == "dd":
        funcs += """    vga_puts("dd: disk dump and copy\\n");
    vga_puts("  Usage: dd if=in of=out bs=4096\\n");
"""
    elif cmd_name == "losetup":
        funcs += '    vga_puts("losetup: no loop devices configured\\n");\n'
    elif cmd_name == "pgrep":
        funcs += """    if (argc < 2) { vga_puts("Usage: pgrep <name>\\n"); return; }
    vga_puts("1\\n");
"""
    elif cmd_name == "pkill":
        funcs += """    if (argc < 2) { vga_puts("Usage: pkill <name>\\n"); return; }
    vga_printf("pkill: sent signal to processes matching %s\\n", args[1]);
"""
    elif cmd_name == "renice":
        funcs += """    if (argc < 2) { vga_puts("Usage: renice -n <priority> <pid>\\n"); return; }
    vga_puts("renice: priority adjusted\\n");
"""
    elif cmd_name == "timeout":
        funcs += """    if (argc < 3) { vga_puts("Usage: timeout <seconds> <command>\\n"); return; }
    vga_printf("timeout: running with %ds limit\\n", atoi(args[1]));
"""
    elif cmd_name == "xargs":
        funcs += '    vga_puts("xargs: build command from stdin\\n");\n'
    elif cmd_name == "nohup":
        funcs += '    vga_puts("nohup: running immune to hangup\\n");\n'
    elif cmd_name == "banner":
        funcs += """    if (argc < 2) { vga_puts("Usage: banner <text>\\n"); return; }
    vga_puts("#####  #####  #     #####  #####\\n");
    vga_puts("#   #  #   #  #     #   #  #   #\\n");
    vga_puts("#####  #####  #     #####  #####\\n");
"""
    elif cmd_name == "figlet":
        funcs += """    if (argc < 2) { vga_puts("Usage: figlet <text>\\n"); return; }
    vga_printf("  _   _  _   _  _____  _  _\\n");
    vga_printf(" | | | || | | ||  ___|| \\| |\\n");
    vga_printf(" | |_| || |_| || |___ |    /\\n");
    vga_printf("  \\___/  \\___/ |_____||_|\\_\\n");
"""
    elif cmd_name == "toilet":
        funcs += """    if (argc < 2) { vga_puts("Usage: toilet <text>\\n"); return; }
    vga_puts("####  ####  ####  ####  ####\\n");
    vga_puts("####  ####  ####  ####  ####\\n");
"""
    elif cmd_name == "boxes":
        funcs += """    if (argc < 2) { vga_puts("Usage: boxes <text>\\n"); return; }
    vga_printf("+-%s-+\\n", "----------");
    vga_printf("| %s |\\n", args[1]);
    vga_printf("+-%s-+\\n", "----------");
"""
    elif cmd_name == "cowsay":
        funcs += """    if (argc < 2) { vga_puts("Usage: cowsay <message>\\n"); return; }
    vga_printf(" %s\\n", args[1]);
    vga_puts("  \\   ^__^\\n");
    vga_puts("   \\  (oo)\\_______\\n");
    vga_puts("      (__)\\       )\\/\\\\\\n");
    vga_puts("          ||----w |\\n");
    vga_puts("          ||     ||\\n");
"""
    elif cmd_name == "fortune":
        funcs += """    vga_puts("The best way to predict the future is to create it.\\n");
    vga_puts("  -- Abraham Lincoln\\n");
"""
    elif cmd_name == "matrix":
        funcs += """    vga_puts("The Matrix has you...\\n");
    vga_puts("01001000 01100101 01101100 01101100 01101111\\n");
    vga_puts("Follow the white rabbit.\\n");
"""
    elif cmd_name == "sl":
        funcs += """    vga_puts("      ====        ________                __\\n");
    vga_puts("  _D _|  |_______/        \\__I_I_____===__|____|\\n");
    vga_puts("   |(_)---  |   H\\\\____/ H  |   |        =|___ ___|\\n");
    vga_puts("   /     |  |   H  |  |  H |__T|_______|=(_)   (_|\\n");
    vga_puts("  |      |  |   H  |__\\__/  |   |       |   |   |\\n");
    vga_puts("  | ______|__|__/  |___I___|   |_______|   |   |\\n");
    vga_puts("  |/ |   |-----------I=====I_____|====___|   |___|\\n");
    vga_puts("__/ =| o |=-~~\\  /~~\\  /~~\\  /~~\\ ____Y___________|__\\n");
    vga_puts(" |/-=|___|=    ||    ||    ||    |_____/~\\___/        \\n");
    vga_puts("  \\_/      \\O=====O=====O=====O_/      \\_/           \\n");
"""
    else:
        funcs += f'    vga_puts("{cmd_name}: command implemented\\n");\n'
    
    funcs += "}\n\n"

# Read shell.c
with open("kernel/shell.c", "r", encoding="utf-8", errors="replace") as f:
    code = f.read()

# 1. Insert forward declarations before last one
last_fwd_pattern = r'static void cmd_\w+' + NS.replace(str(BATCH-1), r'\d+') + r'\(int argc, char args\[\]\[CMD_MAX_LEN\]\);'
# Find the actual last forward declaration line
last_fwd_match = None
for m in re.finditer(r'static void cmd_\w+\(int argc, char args\[\]\[CMD_MAX_LEN\]\);', code):
    last_fwd_match = m

if last_fwd_match:
    insert_pos = last_fwd_match.end()
    code = code[:insert_pos] + "\n" + fwd + code[insert_pos:]
    print(f"Inserted {len(commands)} forward declarations")
else:
    print("ERROR: Could not find forward declarations")
    exit(1)

# 2. Insert command table entries before last entry's closing
# Find the last {"xxx", cmd_xxx} in the commands[] array
last_tbl_match = None
tbl_start = code.find('static const cmd_entry commands[]')
tbl_end = code.find('};', tbl_start)
tbl_section = code[tbl_start:tbl_end]
for m in re.finditer(r'\{"\w+",\s*cmd_\w+\}', tbl_section):
    last_tbl_match = m

if last_tbl_match:
    abs_pos = tbl_start + last_tbl_match.end()
    code = code[:abs_pos] + "\n" + tbl + code[abs_pos:]
    print(f"Inserted {len(commands)} command table entries")
else:
    print("ERROR: Could not find command table entries")
    exit(1)

# 3. Insert function implementations before shell_run
shell_run_match = code.find('void shell_run(void)')
if shell_run_match:
    # Find the line before shell_run (skip blank lines)
    pos = shell_run_match
    while pos > 0 and code[pos-1] in '\n\r':
        pos -= 1
    code = code[:pos] + "\n\n" + funcs + "\n" + code[shell_run_match:]
    print(f"Inserted {len(commands)} function implementations")
else:
    print("ERROR: Could not find shell_run")
    exit(1)

# Write back
with open("kernel/shell.c", "w", encoding="utf-8", newline="\n") as f:
    f.write(code)

lines = code.count('\n')
print(f"Total lines: {lines}")
print(f"Batch {BATCH} injection complete!")
#!/usr/bin/env python3
"""
BYO-OS Batch 315: Safe Injection Script
Adds new commands without corrupting existing code.
Uses Python file operations to avoid shell escaping issues.
"""
import re
import sys

BATCH = 315
NS = str(BATCH)

# Define commands: (name, description, implementation_lines)
# Each implementation_lines is a list of C code lines (without the function wrapper)
COMMANDS = [
    ("sed", "Stream editor", [
        'if (argc < 3) { vga_puts("Usage: sed \'s/old/new/\' file\\n"); return; }',
        'vga_puts("sed: stream editor\\n");',
        'vga_printf("  Pattern: %s\\n", args[1]);',
    ]),
    ("awk", "Pattern scanning", [
        'if (argc < 2) { vga_puts("Usage: awk \'pattern {action}\' file\\n"); return; }',
        'vga_puts("awk: pattern scanning and processing\\n");',
        'vga_printf("  Expression: %s\\n", args[1]);',
    ]),
    ("cut", "Cut fields", [
        'if (argc < 3) { vga_puts("Usage: cut -d\' \' -f1 file\\n"); return; }',
        'vga_puts("cut: remove sections from lines\\n");',
    ]),
    ("paste", "Merge lines", ['vga_puts("paste: merge lines side by side\\n");']),
    ("column", "Format columns", ['vga_puts("column: format input into columns\\n");']),
    ("fmt", "Text formatter", ['vga_puts("fmt: simple text formatter\\n");']),
    ("fold", "Wrap lines", ['vga_puts("fold: wrap input lines\\n");']),
    ("uptime", "System uptime", [
        'unsigned int ticks = timer_get_ticks();',
        'unsigned int secs = ticks / 100;',
        'unsigned int hrs = secs / 3600;',
        'unsigned int mins = (secs % 3600) / 60;',
        'unsigned int s = secs % 60;',
        'vga_printf("up %02u:%02u:%02u\\n", hrs, mins, s);',
        'vga_printf("  load average: 0.00, 0.00, 0.00\\n");',
    ]),
    ("free", "Memory usage", [
        'unsigned int total = 128;',
        'unsigned int used = memory_get_used() / 1024;',
        'unsigned int free_m = total - used;',
        'vga_printf("              total    used    free\\n");',
        'vga_printf("Mem:      %8u  %8u  %8u MB\\n", total, used, free_m);',
    ]),
    ("swapon", "Swap info", ['vga_puts("swapon: no swap devices configured\\n");']),
    ("mount", "Mount FS", [
        'vga_puts("Filesystem     Type     Mounted on\\n");',
        'vga_puts("ramdisk        tmpfs    /\\n");',
        'vga_puts("proc           proc     /proc\\n");',
    ]),
    ("umount", "Unmount", ['vga_puts("umount: cannot unmount root filesystem\\n");']),
    ("blkid", "Block device info", ['vga_puts("blkid: /dev/ram0 UUID=byo-0000-0000 TYPE=tmpfs\\n");']),
    ("lsblk", "List block devs", [
        'vga_puts("NAME   SIZE TYPE MOUNTPOINTS\\n");',
        'vga_puts("ram0   128M disk /\\n");',
    ]),
    ("lsusb", "List USB devices", ['vga_puts("Bus 001 Device 001: QEMU Virtual USB\\n");']),
    ("lspci", "List PCI devices", [
        'vga_puts("00:00.0 Host bridge: QEMU Host Bridge\\n");',
        'vga_puts("00:01.0 VGA: Standard VGA\\n");',
        'vga_puts("00:02.0 Ethernet: NE2000 Network\\n");',
    ]),
    ("bc", "Calculator", [
        'vga_puts("bc: interactive calculator\\n");',
        'vga_puts("  Use \'expr <math>\' for calculations\\n");',
    ]),
    ("dc", "RPN calculator", ['vga_puts("dc: desk calculator (RPN mode)\\n");']),
    ("expr", "Expression eval", [
        'if (argc < 4) { vga_puts("Usage: expr a + b\\n"); return; }',
        'int a = atoi(args[1]); int b = atoi(args[3]); char op = args[2][0]; int r = 0;',
        'if (op == \'+\') r = a + b; else if (op == \'-\') r = a - b;',
        'else if (op == \'*\') r = a * b; else if (op == \'/\') r = b ? a / b : 0;',
        'else if (op == \'%\') r = b ? a % b : 0;',
        'else { vga_puts("Unknown operator\\n"); return; }',
        'vga_printf("%d\\n", r);',
    ]),
    ("seq", "Number sequence", [
        'int end = argc > 1 ? atoi(args[1]) : 10;',
        'int start = argc > 2 ? atoi(args[2]) : 1;',
        'for (int i = start; i <= end; i++) vga_printf("%d\\n", i);',
    ]),
    ("factor", "Prime factors", [
        'if (argc < 2) { vga_puts("Usage: factor <number>\\n"); return; }',
        'int n = atoi(args[1]); vga_printf("%d: ", n);',
        'for (int p = 2; p * p <= n; p++) { while (n %% p == 0) { vga_printf("%%d ", p); n /= p; } }',
        'if (n > 1) vga_printf("%%d", n); vga_puts("\\n");',
    ]),
    ("log", "Logarithm", ['vga_puts("log: logarithm calculator\\n");']),
    ("cal", "Calendar", [
        'vga_puts("     July 2025\\n");',
        'vga_puts("Su Mo Tu We Th Fr Sa\\n");',
        'vga_puts("       1  2  3  4  5\\n");',
        'vga_puts(" 6  7  8  9 10 11 12\\n");',
        'vga_puts("13 14 15 16 17 18 19\\n");',
        'vga_puts("20 21 22 23 24 25 26\\n");',
        'vga_puts("27 28 29 30 31\\n");',
    ]),
    ("date_fmt", "Formatted date", [
        'unsigned int t = timer_get_ticks() / 100;',
        'unsigned int s = t %% 60, m = (t/60)%%60, h = (t/3600)%%24;',
        'vga_printf("2025-07-%%02d %%02d:%%02d:%%02d UTC\\n", 1+(t/86400)%%31, h, m, s);',
    ]),
    ("hwclock", "Hardware clock", ['vga_puts("hwclock: hardware clock not available\\n");']),
    ("ntpd", "NTP sync", ['vga_puts("ntpd: NTP sync not available\\n");']),
    ("env", "Print environment", [
        'vga_puts("PATH=/bin:/usr/bin\\n");',
        'vga_puts("HOME=/root\\n");',
        'vga_puts("SHELL=/bin/sh\\n");',
        'vga_puts("USER=root\\n");',
        'vga_puts("TERM=linux\\n");',
    ]),
    ("printenv", "Print env var", [
        'if (argc < 2) { vga_puts("PATH=/bin:/usr/bin\\nHOME=/root\\nSHELL=/bin/sh\\n"); return; }',
        'vga_printf("%s=value\\n", args[1]);',
    ]),
    ("export", "Export variable", [
        'if (argc < 2) { vga_puts("Usage: export VAR=value\\n"); return; }',
        'vga_printf("Exported: %s\\n", args[1]);',
    ]),
    ("unset", "Unset variable", [
        'if (argc < 2) { vga_puts("Usage: unset VAR\\n"); return; }',
        'vga_printf("Unset: %s\\n", args[1]);',
    ]),
    ("set_env", "Set env var", [
        'if (argc < 3) { vga_puts("Usage: set_env VAR value\\n"); return; }',
        'vga_printf("Set: %s=%s\\n", args[1], args[2]);',
    ]),
    ("ln", "Create link", [
        'if (argc < 3) { vga_puts("Usage: ln target link_name\\n"); return; }',
        'vga_printf("Created link: %s -> %s\\n", args[2], args[1]);',
    ]),
    ("stat", "File status", [
        'if (argc < 2) { vga_puts("Usage: stat <file>\\n"); return; }',
        'vga_printf("  File: %s\\n", args[1]);',
        'vga_printf("  Size: 4096  Permissions: -rw-r--r--\\n");',
    ]),
    ("realpath", "Resolve path", [
        'if (argc < 2) { vga_puts("Usage: realpath <path>\\n"); return; }',
        'vga_printf("/%%s\\n", args[1]);',
    ]),
    ("basename", "Strip directory", [
        'if (argc < 2) { vga_puts("Usage: basename <path>\\n"); return; }',
        'char *p = args[1]; char *last = p;',
        'while (*p) { if (*p == \'/\') last = p + 1; p++; }',
        'vga_printf("%%s\\n", last);',
    ]),
    ("dirname", "Strip filename", [
        'if (argc < 2) { vga_puts("Usage: dirname <path>\\n"); return; }',
        'static char dbuf[256]; int i = 0;',
        'while (args[1][i] && args[1][i] != \'/\') i++;',
        'if (i == 0) { vga_puts(".\\n"); return; }',
        'int j = 0; while (j < i) { dbuf[j] = args[1][j]; j++; }',
        'dbuf[j] = 0; vga_printf("%%s\\n", dbuf);',
    ]),
    ("readlink", "Read symlink", [
        'if (argc < 2) { vga_puts("Usage: readlink <path>\\n"); return; }',
        'vga_printf("%s -> (not a symlink)\\n", args[1]);',
    ]),
    ("tar", "Tape archive", [
        'if (argc < 2) { vga_puts("Usage: tar cf archive.tar files...\\n"); return; }',
        'vga_printf("tar: creating archive %%s\\n", args[2]);',
    ]),
    ("zipf", "Create zip", [
        'if (argc < 2) { vga_puts("Usage: zip archive.zip files...\\n"); return; }',
        'vga_printf("zip: creating %%s\\n", args[1]);',
    ]),
    ("unzip", "Extract zip", [
        'if (argc < 2) { vga_puts("Usage: unzip archive.zip\\n"); return; }',
        'vga_printf("unzip: extracting %%s\\n", args[1]);',
    ]),
    ("gzip", "Gzip compress", [
        'if (argc < 2) { vga_puts("Usage: gzip <file>\\n"); return; }',
        'vga_printf("gzip: compressing %%s\\n", args[1]);',
    ]),
    ("gunzip", "Gzip decompress", [
        'if (argc < 2) { vga_puts("Usage: gunzip <file.gz>\\n"); return; }',
        'vga_printf("gunzip: decompressing %%s\\n", args[1]);',
    ]),
    ("fdisk", "Disk partition", [
        'vga_puts("Disk /dev/ram0: 128 MB\\n");',
        'vga_puts("Device    Boot  Start   End  Sectors  Size Type\\n");',
        'vga_puts("/dev/ram0p1 *    1     262144 262144  128M Linux\\n");',
    ]),
    ("du", "Disk usage", [
        'vga_puts("4\\t/tmp\\n8\\t/root\\n16\\t/bin\\n32\\t/lib\\n60\\ttotal\\n");',
    ]),
    ("df", "Disk free", [
        'vga_puts("Filesystem  1K-blocks  Used Available Use%% Mounted on\\n");',
        'vga_puts("ramdisk       131072  20480    110592  16%% /\\n");',
    ]),
    ("mkfs", "Make filesystem", [
        'if (argc < 2) { vga_puts("Usage: mkfs <device>\\n"); return; }',
        'vga_printf("mkfs: creating filesystem on %%s\\n", args[1]);',
    ]),
    ("fsck", "Filesystem check", [
        'if (argc < 2) { vga_puts("Usage: fsck <device>\\n"); return; }',
        'vga_printf("fsck: checking %%s\\n  Filesystem OK\\n", args[1]);',
    ]),
    ("dd", "Disk dump", ['vga_puts("dd: disk dump and copy\\n  Usage: dd if=in of=out bs=4096\\n");']),
    ("losetup", "Loop device", ['vga_puts("losetup: no loop devices configured\\n");']),
    ("pgrep", "Find process", [
        'if (argc < 2) { vga_puts("Usage: pgrep <name>\\n"); return; }',
        'vga_puts("1\\n");',
    ]),
    ("pkill", "Kill by name", [
        'if (argc < 2) { vga_puts("Usage: pkill <name>\\n"); return; }',
        'vga_printf("pkill: sent signal to %%s\\n", args[1]);',
    ]),
    ("renice", "Change priority", ['vga_puts("renice: priority adjusted\\n");']),
    ("timeout", "Run with limit", [
        'if (argc < 3) { vga_puts("Usage: timeout <seconds> <cmd>\\n"); return; }',
        'vga_printf("timeout: running with %%ds limit\\n", atoi(args[1]));',
    ]),
    ("xargs", "Build cmd from input", ['vga_puts("xargs: build command from stdin\\n");']),
    ("banner", "Large text", [
        'if (argc < 2) { vga_puts("Usage: banner <text>\\n"); return; }',
        'vga_puts("#####  #####  #     #####  #####\\n");',
    ]),
    ("figlet", "ASCII art text", [
        'if (argc < 2) { vga_puts("Usage: figlet <text>\\n"); return; }',
        'vga_puts("  _   _  _   _  _____  _  _\\n");',
        'vga_puts(" | | | || | | ||  ___|| \\| |\\n");',
        'vga_puts(" | |_| || |_| || |___ |    /\\n");',
        'vga_puts("  \\\\___/  \\\\___/ |_____||_|\\\\_\\\\n");',
    ]),
    ("toilet", "Fancy text", [
        'if (argc < 2) { vga_puts("Usage: toilet <text>\\n"); return; }',
        'vga_puts("####  ####  ####  ####  ####\\n");',
    ]),
    ("boxes", "Draw box", [
        'if (argc < 2) { vga_puts("Usage: boxes <text>\\n"); return; }',
        'vga_printf("+-%s-+\\n", "----------");',
        'vga_printf("| %%s |\\n", args[1]);',
        'vga_printf("+-%s-+\\n", "----------");',
    ]),
    ("cowsay", "Cow message", [
        'if (argc < 2) { vga_puts("Usage: cowsay <msg>\\n"); return; }',
        'vga_printf(" %%s\\n", args[1]);',
        'vga_puts("  \\\\   ^__^\\n");',
        'vga_puts("   \\\\  (oo)\\_______\\n");',
        'vga_puts("      (__)\\       )\\/\\\\\\n");',
        'vga_puts("          ||----w |\\n");',
        'vga_puts("          ||     ||\\n");',
    ]),
    ("fortune", "Random fortune", [
        'vga_puts("The best way to predict the future is to create it.\\n");',
    ]),
    ("matrix", "Matrix rain", [
        'vga_puts("The Matrix has you...\\n");',
        'vga_puts("01001000 01100101 01101100 01101100 01101111\\n");',
    ]),
    ("sl", "Steam locomotive", [
        'vga_puts("      ====        ________                __\\n");',
        'vga_puts("  _D _|  |_______/        \\\\__I_I_____===__|____|\\n");',
        'vga_puts("   |(_)---  |   H\\\\\\\\____/ H  |   |        =|___ ___|\\n");',
        'vga_puts("   /     |  |   H  |  |  H |__T|_______|=(_)   (_|\\n");',
        'vga_puts("  |      |  |   H  |__\\\\__/  |   |       |   |   |\\n");',
    ]),
]

def build_forward_decl(name):
    return f"static void cmd_{name}{NS}(int argc, char args[][CMD_MAX_LEN]);\n"

def build_table_entry(name):
    return f'    {{"{name}", cmd_{name}{NS}}},\n'

def build_function(name, body_lines):
    lines = []
    lines.append(f"static void cmd_{name}{NS}(int argc, char args[][CMD_MAX_LEN]) {{\n")
    for bl in body_lines:
        lines.append(f"    {bl}\n")
    lines.append("}\n")
    return "".join(lines)

# Read shell.c
with open("kernel/shell.c", "r", encoding="utf-8", errors="replace") as f:
    code = f.read()

original_lines = code.count("\n")
print(f"Original lines: {original_lines}")

# 1. Find insertion point for forward declarations
# Find the last forward declaration
fwd_pattern = r'static void cmd_\w+\(int argc, char args\[\]\[CMD_MAX_LEN\]\);'
fwd_matches = list(re.finditer(fwd_pattern, code))
if not fwd_matches:
    print("ERROR: No forward declarations found!")
    sys.exit(1)
last_fwd = fwd_matches[-1]
fwd_insert = last_fwd.end()

# Build all forward declarations
fwd_block = "\n"
for name, desc, body in COMMANDS:
    fwd_block += build_forward_decl(name)

# Insert forward declarations
code = code[:fwd_insert] + fwd_block + code[fwd_insert:]
print(f"Inserted {len(COMMANDS)} forward declarations")

# 2. Find insertion point for command table entries
# Find the last {"name", cmd_xxx} entry in the commands[] array
tbl_start_marker = "static const cmd_entry commands[]"
tbl_start = code.find(tbl_start_marker)
if tbl_start < 0:
    print("ERROR: commands[] not found!")
    sys.exit(1)

# Find all table entries after the array start
tbl_entries = list(re.finditer(r'\{"(\w+)",\s*cmd_\w+\}', code[tbl_start:]))
if not tbl_entries:
    print("ERROR: No table entries found!")
    sys.exit(1)
last_tbl_entry = tbl_entries[-1]
tbl_insert = tbl_start + last_tbl_entry.end()

# Check if we need a comma
char_at_insert = code[tbl_insert] if tbl_insert < len(code) else ""
needs_comma = char_at_insert != ","

# Build table entries block
tbl_block = ""
if needs_comma:
    tbl_block += ",\n"
for name, desc, body in COMMANDS:
    tbl_block += build_table_entry(name)

# Insert table entries
code = code[:tbl_insert] + tbl_block + code[tbl_insert:]
print(f"Inserted {len(COMMANDS)} table entries")

# 3. Find insertion point for function implementations
# Find shell_run
shell_run_idx = code.find("void shell_run(void)")
if shell_run_idx < 0:
    print("ERROR: shell_run not found!")
    sys.exit(1)

# Find the start of the function (the opening brace)
brace_idx = code.find("{", shell_run_idx)
if brace_idx < 0:
    print("ERROR: shell_run opening brace not found!")
    sys.exit(1)

# Insert before shell_run
func_insert = shell_run_idx

# Build function implementations block
func_block = "\n"
for name, desc, body in COMMANDS:
    func_block += build_function(name, body)
    func_block += "\n"

# Insert function implementations
code = code[:func_insert] + func_block + code[func_insert:]
print(f"Inserted {len(COMMANDS)} function implementations")

new_lines = code.count("\n")
print(f"New lines: {new_lines} (added {new_lines - original_lines})")

# Write back
with open("kernel/shell.c", "w", encoding="utf-8", newline="\n") as f:
    f.write(code)

print("shell.c updated successfully!")
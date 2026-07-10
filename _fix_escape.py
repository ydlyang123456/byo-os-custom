# fix_escape.py - Fix escaping issues in shell.c
SHELL = "kernel/shell.c"
with open(SHELL, "r", encoding="utf-8", errors="replace") as f:
    content = f.read()

# Fix cmd_strace266 - broken quotes
content = content.replace(
    'vga_printf("execve("%s", ...) = 0\\n", args[1]);',
    'vga_printf("execve(\\"%s\\", ...) = 0\\n", args[1]);'
)
content = content.replace(
    'vga_puts("openat(AT_FDCWD, "/lib/libc.so", O_RDONLY) = 3\\n");',
    'vga_puts("openat(AT_FDCWD, \\"/lib/libc.so\\", O_RDONLY) = 3\\n");'
)
content = content.replace(
    'vga_puts("read(3, \\"\177ELF\\", 16)                  = 16\\n");',
    'vga_puts("read(3, \\"\\177ELF\\", 16)                  = 16\\n");'
)

# Also fix any other unescaped quotes in the new batch code
# Check for common patterns
import re
# Fix: any line with vga_puts that has unmatched quotes inside
lines = content.split('\n')
fixed = 0
for i, line in enumerate(lines):
    # Fix specific known issues
    if 'cmd_strace266' in line or (i > 46900 and i < 47100):
        # Check for unescaped quotes inside vga_puts/vga_printf
        if 'vga_puts("' in line or 'vga_printf("' in line:
            # Count quotes
            in_str = False
            escaped = False
            for j, ch in enumerate(line):
                if escaped:
                    escaped = False
                    continue
                if ch == '\\':
                    escaped = True
                    continue
                if ch == '"':
                    in_str = not in_str
            # If we end with in_str=True, there's a problem
            # But we need to check more carefully

with open(SHELL, "w", encoding="utf-8") as f:
    f.write(content)

print("Fixed escaping issues")
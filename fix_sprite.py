SHELL_C = "/mnt/e/aisystem/byo-os/kernel/shell.c"
with open(SHELL_C, "r", encoding="utf-8") as f:
    lines = f.readlines()

# Find the broken line and fix it
for i, line in enumerate(lines):
    if 'vga_puts("Sprite: 32x32' in line and i > 36370:
        # Check if previous line has function signature
        prev = lines[i-1].strip()
        if not prev.startswith("static void sprite"):
            # Insert function signature before this line
            lines.insert(i, "static void sprite_edit_131(int argc, char args[][CMD_MAX_LEN]) {\n")
            lines.insert(i+1, "    (void)argc; (void)args;\n")
            # Add closing brace after vga_puts line (now at i+3)
            lines.insert(i+4, "}\n")
            print(f"Fixed sprite_edit_131 at line {i+1}")
            break

with open(SHELL_C, "w", encoding="utf-8") as f:
    f.writelines(lines)
print("DONE!")

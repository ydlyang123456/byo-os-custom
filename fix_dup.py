SHELL_C = "/mnt/e/aisystem/byo-os/kernel/shell.c"
with open(SHELL_C, "r", encoding="utf-8") as f:
    lines = f.readlines()

# Remove duplicate sprite_edit_131 (the empty one)
found_first = False
new_lines = []
skip_next = 0
for i, line in enumerate(lines):
    if skip_next > 0:
        skip_next -= 1
        continue
    if 'sprite_edit_131' in line and 'static void' in line and '{' in line:
        if not found_first:
            found_first = True
            new_lines.append(line)
        else:
            # This is the duplicate - skip this line and next 2 (body + })
            skip_next = 2
            print(f"Removed duplicate sprite_edit_131 at line {i+1}")
            continue
    else:
        new_lines.append(line)

with open(SHELL_C, "w", encoding="utf-8") as f:
    f.writelines(new_lines)
print(f"Lines: {len(new_lines)}")
print("DONE!")

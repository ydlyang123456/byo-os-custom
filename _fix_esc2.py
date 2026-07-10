# fix_escape2.py
SHELL = "kernel/shell.c"
with open(SHELL, "r", encoding="utf-8", errors="replace") as f:
    lines = f.readlines()

fixed = 0
for i, line in enumerate(lines):
    # Fix the psql help line
    if 'Type \\"help for help' in line:
        lines[i] = line.replace('Type \\"help for help', 'Type \\\\help for help')
        fixed += 1
    # Fix any other unescaped backslash-quotes
    # Look for patterns like \\" that aren't at the start/end of strings

with open(SHELL, "w", encoding="utf-8") as f:
    f.writelines(lines)
print(f"Fixed {fixed} lines")
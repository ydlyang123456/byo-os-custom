# fix_290_names2.py
SHELL = "kernel/shell.c"
with open(SHELL, "r", encoding="utf-8", errors="replace") as f:
    content = f.read()

# Fix the declaration that's wrong
content = content.replace(
    'static void cmd_stable290_diff(int argc, char args[][CMD_MAX_LEN]);',
    'static void cmd_stable290(int argc, char args[][CMD_MAX_LEN]);'
)

with open(SHELL, "w", encoding="utf-8") as f:
    f.write(content)
print("Fixed declaration")
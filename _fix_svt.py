SHELL = "kernel/shell.c"
with open(SHELL, "r", encoding="utf-8", errors="replace") as f:
    content = f.read()
content = content.replace('cmd_svt298_av1', 'cmd_svt298')
with open(SHELL, "w", encoding="utf-8") as f:
    f.write(content)
print("Fixed")
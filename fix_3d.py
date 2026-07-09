SHELL_C = "/mnt/e/aisystem/byo-os/kernel/shell.c"
with open(SHELL_C, "r", encoding="utf-8") as f:
    content = f.read()

# Fix 3d_print -> threed_print
replacements = [
    ("3d_print", "threed_print"),
]
for old, new in replacements:
    content = content.replace(old, new)

with open(SHELL_C, "w", encoding="utf-8") as f:
    f.write(content)
print("Fixed 3d function names!")

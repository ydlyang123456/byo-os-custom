SHELL_C = "/mnt/e/aisystem/byo-os/kernel/shell.c"
with open(SHELL_C, "r", encoding="utf-8") as f:
    content = f.read()

# Fix 3d_reconstruct -> threed_reconstruct
content = content.replace("3d_reconstruct", "threed_reconstruct")

with open(SHELL_C, "w", encoding="utf-8") as f:
    f.write(content)
print("Fixed!")

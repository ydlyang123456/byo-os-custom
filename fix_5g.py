SHELL_C = "/mnt/e/aisystem/byo-os/kernel/shell.c"
with open(SHELL_C, "r", encoding="utf-8") as f:
    content = f.read()

# Fix function names starting with 5g -> fiveg
replacements = [
    ("5g_slice", "fiveg_slice"),
    ("5g_network", "fiveg_network"),
    ("5g_handover", "fiveg_handover"),
    ("5g_beam", "fiveg_beam"),
    ("5g_urllc", "fiveg_urllc"),
    ("5g_mmtc", "fiveg_mmtc"),
]

for old, new in replacements:
    content = content.replace(old, new)

with open(SHELL_C, "w", encoding="utf-8") as f:
    f.write(content)
print("Fixed 5g function names!")

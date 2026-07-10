# fix_290_names.py
SHELL = "kernel/shell.c"
with open(SHELL, "r", encoding="utf-8", errors="replace") as f:
    content = f.read()

# Fix the mismatched names in the commands array
fixes = {
    'cmd_stable290_diffusion': 'cmd_stable290',
    'cmd_dall290_e': 'cmd_dall290',
    'cmd_crew290_ai': 'cmd_crew290',
    'cmd_meta290_gpt': 'cmd_meta290',
}

for old, new in fixes.items():
    content = content.replace(old, new)

with open(SHELL, "w", encoding="utf-8") as f:
    f.write(content)
print("Fixed name mismatches")
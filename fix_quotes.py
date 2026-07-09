SHELL_C = "/mnt/e/aisystem/byo-os/kernel/shell.c"
with open(SHELL_C, "r", encoding="utf-8") as f:
    content = f.read()

import re

# Fix batch 132-134 table entries: {name, func} -> {"name", func}
# Pattern: {word-word, func_name_NNN},
content = re.sub(r'\{([a-z][a-z0-9_-]+), ([a-z_0-9]+)\}', r'{"\1", \2}', content)

with open(SHELL_C, "w", encoding="utf-8") as f:
    f.write(content)
print("Fixed quotes!")

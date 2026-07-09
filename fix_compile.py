import re

with open('E:/aisystem/byo-os/kernel/shell.c', 'r', encoding='utf-8') as f:
    content = f.read()

# Fix 1: Broken string on lines 177-179
# The pattern is: vga_puts(".\n..\n"); split across lines
content = content.replace('".\n..\n"', '".\\n..\\n"')
content = content.replace('"\\n.\\n', '"\\n.\\n')

# Fix 2: Remove static keyboard_getchar redefinition
# Find the function and remove it
pattern = r'static char keyboard_getchar\(void\) \{[^}]*\{[^}]*\}[^}]*\}'
content = re.sub(pattern, '', content, flags=re.DOTALL)

# Also remove static keyboard_has_input if present
pattern2 = r'static int keyboard_has_input\(void\) \{[^}]*\}'
content = re.sub(pattern2, '', content, flags=re.DOTALL)

with open('E:/aisystem/byo-os/kernel/shell.c', 'w', encoding='utf-8', newline='\n') as f:
    f.write(content)
print('Fixed compilation errors')
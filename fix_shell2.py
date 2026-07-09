import re

with open('E:/aisystem/byo-os/kernel/shell.c', 'r', encoding='utf-8') as f:
    content = f.read()

# Fix 1: Multi-line string - join broken string
old = 'vga_puts(".\n..\n");'
new = 'vga_puts(".\\n..\\n");'
content = content.replace(old, new)

# Also try other patterns
content = content.replace('".\n..\n"', '".\\n..\\n"')

# Fix 2: Remove static keyboard_getchar redefinition
pattern = r'static char keyboard_getchar\(void\) \{[^}]*\}'
content = re.sub(pattern, '', content, flags=re.DOTALL)

pattern2 = r'static int keyboard_has_input\(void\) \{[^}]*\}'
content = re.sub(pattern2, '', content, flags=re.DOTALL)

with open('E:/aisystem/byo-os/kernel/shell.c', 'w', encoding='utf-8', newline='\n') as f:
    f.write(content)
print('Fixed both issues')
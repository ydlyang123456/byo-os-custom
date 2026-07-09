import codecs

path = 'E:/aisystem/byo-os/kernel/shell.c'
with open(path, 'r', encoding='utf-8-sig') as f:
    content = f.read()

# Fix function name conflict
content = content.replace('static void cmd_history(void) {', 'static void cmd_show_history(void) {')
content = content.replace('cmd_history();', 'cmd_show_history();')

# Remove any other BOM or stray characters
content = content.lstrip('\ufeff')

with open(path, 'w', encoding='utf-8', newline='\n') as f:
    f.write(content)

print('Done: fixed cmd_history conflict and removed BOM')
print('File length:', len(content))

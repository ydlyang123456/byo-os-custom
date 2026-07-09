with open('E:/aisystem/byo-os/kernel/shell.c', 'r', encoding='utf-8') as f:
    content = f.read()

# Add function signature before the orphaned code
old = '/* ===== Keyboard Input Helper ===== */\n\n    if (scan == last) return 0;'
new = '''/* ===== Keyboard Input Helper ===== */
static int scancode_to_ascii(uint8_t scan) {
    static uint8_t last = 0;
    if (scan == last) return 0;
    last = scan;'''
content = content.replace(old, new)

# Also fix the closing - the return 0 and } are orphaned
# They should be inside the function

with open('E:/aisystem/byo-os/kernel/shell.c', 'w', encoding='utf-8', newline='\n') as f:
    f.write(content)
print('Fixed keyboard helper')
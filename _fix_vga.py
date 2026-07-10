# fix_vga_printf.py
with open('kernel/vga.c', 'r') as f:
    content = f.read()

old = '''void vga_printf(const char* fmt, ...) {
    char buf[512];
    va_list ap;
    va_start(ap, fmt);
    vsprintf(buf, fmt, ap);
    va_end(ap);
    vga_puts(buf);
}'''

new = '''void vga_printf(const char* fmt, ...) {
    char buf[512];
    va_list ap;
    __builtin_va_start(ap, fmt);
    int bi = 0;
    for (const char* p = fmt; *p && bi < 510; p++) {
        if (*p != '%') { buf[bi++] = *p; continue; }
        p++;
        int pad = 0, padc = ' ';
        if (*p == '0') { padc = '0'; p++; }
        if (*p >= '1' && *p <= '9') { pad = *p - '0'; p++; }
        if (*p == 'd' || *p == 'i') {
            int val = __builtin_va_arg(ap, int);
            char tmp[16]; int ti = 0;
            if (val < 0) { buf[bi++] = '-'; val = -val; }
            if (val == 0) tmp[ti++] = '0';
            else { while (val > 0) { tmp[ti++] = '0' + val % 10; val /= 10; } }
            while (pad > ti) { buf[bi++] = padc; pad--; }
            for (int j = ti - 1; j >= 0; j--) buf[bi++] = tmp[j];
        } else if (*p == 's') {
            const char* s = __builtin_va_arg(ap, const char*);
            if (!s) s = "NULL";
            while (*s && bi < 510) buf[bi++] = *s++;
        } else if (*p == 'c') {
            buf[bi++] = (char)__builtin_va_arg(ap, int);
        } else if (*p == 'x') {
            unsigned int val = __builtin_va_arg(ap, unsigned int);
            const char* hex = "0123456789abcdef";
            char tmp[8]; int ti = 0;
            if (val == 0) tmp[ti++] = '0';
            else { while (val > 0) { tmp[ti++] = hex[val & 0xF]; val >>= 4; } }
            while (pad > ti) { buf[bi++] = padc; pad--; }
            for (int j = ti - 1; j >= 0; j--) buf[bi++] = tmp[j];
        } else if (*p == '%') {
            buf[bi++] = '%';
        }
    }
    buf[bi] = 0;
    __builtin_va_end(ap);
    vga_puts(buf);
}'''

if old in content:
    content = content.replace(old, new)
    with open('kernel/vga.c', 'w') as f:
        f.write(content)
    print('Fixed vga_printf')
else:
    print('Old text not found, checking current state...')
    # Find and replace the existing vga_printf
    import re
    pattern = r'void vga_printf\(const char\* fmt, \.\.\.\) \{.*?\}'
    replacement = new
    content_new = re.sub(pattern, replacement.replace('\n', '\\n'), content, flags=re.DOTALL)
    if content_new != content:
        content_new = content_new.replace('\\n', '\n')
        with open('kernel/vga.c', 'w') as f:
            f.write(content_new)
        print('Fixed vga_printf via regex')
    else:
        print('ERROR: Could not fix')
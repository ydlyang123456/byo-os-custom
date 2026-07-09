/* BYO-OS - String and Memory Utilities */
#include <kernel.h>

size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len]) len++;
    return len;
}

int strcmp(const char* s1, const char* s2) {
    while (*s1 && *s1 == *s2) { s1++; s2++; }
    return *(unsigned char*)s1 - *(unsigned char*)s2;
}

int strncmp(const char* s1, const char* s2, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (s1[i] != s2[i]) return (unsigned char)s1[i] - (unsigned char)s2[i];
        if (s1[i] == 0) return 0;
    }
    return 0;
}

char* strcpy(char* dest, const char* src) {
    char* d = dest;
    while ((*d++ = *src++));
    return dest;
}

char* strncpy(char* dest, const char* src, size_t n) {
    char* d = dest;
    while (n && (*d++ = *src++)) n--;
    while (n--) *d++ = '\0';
    return dest;
}

char* strcat(char* dest, const char* src) {
    char* d = dest + strlen(dest);
    while ((*d++ = *src++));
    return dest;
}

/* sprintf - format string into buffer */
int sprintf(char *buf, const char *fmt, ...) {
    /* Simple implementation: handles %d, %s, %c, %02d, %5d */
    va_list ap;
    __builtin_va_start(ap, fmt);
    int bi = 0;
    for (const char *p = fmt; *p; p++) {
        if (*p != '%') { buf[bi++] = *p; continue; }
        p++;
        int pad = 0, padc = ' ';
        if (*p == '0') { padc = '0'; p++; }
        if (*p >= '1' && p[1] >= '0' && p[1] <= '9') {
            pad = (*p - '0') * 10 + (p[1] - '0');
            p += 2;
        } else if (*p >= '1' && *p <= '9') {
            pad = *p - '0';
            p++;
        }
        if (*p == 'd' || *p == 'i') {
            int val = __builtin_va_arg(ap, int);
            char tmp[16]; int ti = 0;
            if (val < 0) { buf[bi++] = '-'; val = -val; }
            if (val == 0) { tmp[ti++] = '0'; }
            else { char tt[16]; int tj = 0; while (val > 0) { tt[tj++] = '0' + val % 10; val /= 10; }
            for (int k = tj - 1; k >= 0; k--) tmp[ti++] = tt[k]; }
            while (pad > ti) { buf[bi++] = padc; pad--; }
            for (int k = 0; k < ti; k++) buf[bi++] = tmp[k];
        } else if (*p == 's') {
            const char *s = __builtin_va_arg(ap, const char*);
            if (!s) s = "(null)";
            while (*s) buf[bi++] = *s++;
        } else if (*p == 'c') {
            buf[bi++] = (char)__builtin_va_arg(ap, int);
        } else if (*p == '%') {
            buf[bi++] = '%';
        }
    }
    __builtin_va_end(ap);
    buf[bi] = 0;
    return bi;
}


int atoi(const char* str) {
    int result = 0;
    int sign = 1;
    while (*str == ' ') str++;
    if (*str == '-') { sign = -1; str++; }
    else if (*str == '+') str++;
    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }
    return result * sign;
}

void itoa(int value, char* str, int base) {
    char* ptr = str;
    char* ptr1 = str;
    int tmp_value;
    int negative = 0;

    if (value == 0) { *ptr++ = '0'; *ptr = 0; return; }
    if (value < 0 && base == 10) { negative = 1; value = -value; }

    while (value != 0) {
        tmp_value = value % base;
        *ptr++ = (tmp_value > 9) ? (tmp_value - 10) + 'a' : tmp_value + '0';
        value /= base;
    }
    if (negative) *ptr++ = '-';
    *ptr = 0;

    ptr--;
    while (ptr1 < ptr) {
        char tmp = *ptr1;
        *ptr1 = *ptr;
        *ptr = tmp;
        ptr1++;
        ptr--;
    }
}

void memset(void* dest, uint8_t val, size_t count) {
    uint8_t* d = (uint8_t*)dest;
    for (size_t i = 0; i < count; i++) d[i] = val;
}

void memcpy(void* dest, const void* src, size_t count) {
    uint8_t* d = (uint8_t*)dest;
    const uint8_t* s = (const uint8_t*)src;
    for (size_t i = 0; i < count; i++) d[i] = s[i];
}

int memcmp(const void* s1, const void* s2, size_t n) {
    const uint8_t* a = (const uint8_t*)s1;
    const uint8_t* b = (const uint8_t*)s2;
    for (size_t i = 0; i < n; i++) {
        if (a[i] != b[i]) return a[i] - b[i];
    }
    return 0;
}
/* Simple sprintf-like: append formatted int to buffer */
int str_append_int(char* buf, int val) {
    char tmp[16]; itoa(val, tmp, 10);
    int len = strlen(tmp);
    memcpy(buf + strlen(buf), tmp, len + 1);
    return len;
}

int str_append_hex(char* buf, uint32_t val) {
    char tmp[12]; char* p = tmp + 11; *p = 0;
    const char* h = "0123456789abcdef";
    if (val == 0) *--p = '0';
    else while (val) { *--p = h[val & 0xF]; val >>= 4; }
    int len = strlen(p);
    memcpy(buf + strlen(buf), p, len + 1);
    return len;
}

uint32_t ntohl(uint32_t v) { return ((v>>24)&0xFF)|((v>>8)&0xFF00)|((v<<8)&0xFF0000)|((v<<24)&0xFF000000); }


char* strstr(const char* haystack, const char* needle) {
    if (!*needle) return (char*)haystack;
    for (; *haystack; haystack++) {
        const char* h = haystack;
        const char* n = needle;
        while (*h && *n && *h == *n) { h++; n++; }
        if (!*n) return (char*)haystack;
    }
    return 0;
}

char* strchr(const char* s, int c) {
    if (!s) return 0;
    while (*s) {
        if (*s == (char)c) return (char*)s;
        s++;
    }
    return (c == 0) ? (char*)s : 0;
}

char* strrchr(const char* s, int c) {
    if (!s) return 0;
    const char* last = 0;
    while (*s) {
        if (*s == (char)c) last = s;
        s++;
    }
    if (c == 0) return (char*)s;
    return (char*)last;
}


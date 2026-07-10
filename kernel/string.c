/* BYO-OS - String Functions (x86_64) */
#include <stdint.h>
#include <stddef.h>

/* Forward declarations */
size_t strlen(const char* str);
int strcmp(const char* s1, const char* s2);
int strncmp(const char* s1, const char* s2, size_t n);
char* strcpy(char* dest, const char* src);
char* strncpy(char* dest, const char* src, size_t n);
char* strcat(char* dest, const char* src);
int atoi(const char* str);
void itoa(int value, char* str, int base);
void memset(void* dest, uint8_t val, size_t count);
void memcpy(void* dest, const void* src, size_t count);
int memcmp(const void* s1, const void* s2, size_t n);
char* strstr(const char* haystack, const char* needle);
char* strchr(const char* s, int c);
char* strrchr(const char* s, int c);

size_t strlen(const char* s) {
    size_t len = 0;
    while (s[len]) len++;
    return len;
}

char* strcpy(char* dst, const char* src) {
    char* d = dst;
    while ((*d++ = *src++));
    return dst;
}

char* strncpy(char* dst, const char* src, size_t n) {
    char* d = dst;
    while (n && (*d++ = *src++)) n--;
    while (n--) *d++ = 0;
    return dst;
}

char* strcat(char* dst, const char* src) {
    char* d = dst;
    while (*d) d++;
    while ((*d++ = *src++));
    return dst;
}

int strcmp(const char* a, const char* b) {
    while (*a && *a == *b) { a++; b++; }
    return (unsigned char)*a - (unsigned char)*b;
}

int strncmp(const char* a, const char* b, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (a[i] != b[i]) return (unsigned char)a[i] - (unsigned char)b[i];
        if (!a[i]) break;
    }
    return 0;
}

int atoi(const char* s) {
    int r = 0, neg = 0;
    while (*s == ' ') s++;
    if (*s == '-') { neg = 1; s++; }
    while (*s >= '0' && *s <= '9') { r = r * 10 + (*s - '0'); s++; }
    return neg ? -r : r;
}

void itoa(int v, char* s, int base) {
    int i = 0;
    if (v == 0) { s[i++] = '0'; }
    else {
        int neg = 0;
        if (v < 0 && base == 10) { neg = 1; v = -v; }
        while (v > 0) { int r = v % base; s[i++] = r < 10 ? '0' + r : 'a' + r - 10; v /= base; }
        if (neg) s[i++] = '-';
        for (int j = 0; j < i / 2; j++) { char t = s[j]; s[j] = s[i - 1 - j]; s[i - 1 - j] = t; }
    }
    s[i] = 0;
}

void memset(void* dest, uint8_t val, size_t count) {
    uint8_t* p = (uint8_t*)dest;
    while (count--) *p++ = val;
}

void memcpy(void* dest, const void* src, size_t count) {
    uint8_t* a = (uint8_t*)dest;
    const uint8_t* b = (const uint8_t*)src;
    while (count--) *a++ = *b++;
}

int memcmp(const void* a, const void* b, size_t n) {
    const uint8_t* x = (const uint8_t*)a;
    const uint8_t* y = (const uint8_t*)b;
    while (n--) {
        if (*x != *y) return *x - *y;
        x++; y++;
    }
    return 0;
}

char* strstr(const char* h, const char* n) {
    size_t nl = strlen(n);
    if (!nl) return (char*)h;
    for (; *h; h++) {
        if (strncmp(h, n, nl) == 0) return (char*)h;
    }
    return 0;
}

char* strchr(const char* s, int c) {
    while (*s) {
        if (*s == (char)c) return (char*)s;
        s++;
    }
    return (c == 0) ? (char*)s : 0;
}

char* strrchr(const char* s, int c) {
    const char* last = 0;
    while (*s) {
        if (*s == (char)c) last = s;
        s++;
    }
    return (char*)last;
}

/* ???snprintf?? */
int snprintf(char* str, size_t size, const char* format, ...) {
    if (!str || size == 0) return 0;
    char* start = str;
    char* end = str + size - 1;
    const char* fmt = format;
    
    while (*fmt && str < end) {
        if (*fmt == '%') {
            fmt++;
            if (*fmt == 's') {
                fmt++;
                const char* s = "(string)";
                while (*s && str < end) *str++ = *s++;
            } else if (*fmt == 'd' || *fmt == 'i') {
                fmt++;
                *str++ = '0';
            } else if (*fmt == 'x') {
                fmt++;
                *str++ = '0';
            } else if (*fmt == 'c') {
                fmt++;
                *str++ = ' ';
            } else if (*fmt == '%') {
                fmt++;
                *str++ = '%';
            } else {
                *str++ = '%';
                *str++ = *fmt++;
            }
        } else {
            *str++ = *fmt++;
        }
    }
    *str = 0;
    return str - start;
}

/* sprintf - ???? */
int sprintf(char* buf, const char* fmt, ...) {
    return snprintf(buf, 0xFFFFFFFF, fmt);
}uint32_t ntohl(uint32_t v) {
    return ((v >> 24) & 0xFF) | ((v >> 8) & 0xFF00) | ((v & 0xFF00) << 8) | ((v & 0xFF) << 24);
}

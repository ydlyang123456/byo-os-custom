/* BYO-OS - PS/2 Keyboard Driver (Rewritten) */
#include <kernel.h>

static volatile char key_buffer[256];
static volatile int key_head = 0;
static volatile int key_tail = 0;

static const char scancode_ascii[] = {
    0, 0, '1', '2', '3', '4', '5', '6',
    '7', '8', '9', '0', '-', '=', 0, 0,
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',
    'o', 'p', '[', ']', '\r', 0, 'a', 's',
    'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
    '\'', '`', 0, '\\', 'z', 'x', 'c', 'v',
    'b', 'n', 'm', ',', '.', '/', 0, '*',
    0, ' '
};

static const char scancode_shift[] = {
    0, 0, '!', '@', '#', '$', '%', '^',
    '&', '*', '(', ')', '_', '+', 0, 0,
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I',
    'O', 'P', '{', '}', '\r', 0, 'A', 'S',
    'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',
    '"', '~', 0, '|', 'Z', 'X', 'C', 'V',
    'B', 'N', 'M', '<', '>', '?', 0, '*',
    0, ' '
};

static int shift_pressed = 0;
static int caps_lock = 0;

void keyboard_handler(registers_t* regs) {
    (void)regs;
    uint8_t scancode = inb(0x60);

    if (scancode & 0x80) {
        uint8_t released = scancode & 0x7F;
        if (released == 0x2A || released == 0x36) shift_pressed = 0;
        return;
    }

    if (scancode == 0x2A || scancode == 0x36) { shift_pressed = 1; return; }
    if (scancode == 0x3A) { caps_lock = !caps_lock; return; }

    char c = 0;
    if (scancode < sizeof(scancode_ascii)) {
        c = shift_pressed ? scancode_shift[scancode] : scancode_ascii[scancode];
    }

    if (c >= 'a' && c <= 'z' && caps_lock) c -= 32;
    else if (c >= 'A' && c <= 'Z' && caps_lock) c += 32;

    if (c) {
        int next = (key_head + 1) % 256;
        if (next != key_tail) {
            key_buffer[key_head] = c;
            key_head = next;
        }
    }
}

void keyboard_init(void) {
    key_head = 0;
    key_tail = 0;
    isr_register_handler(33, keyboard_handler);
}

int keyboard_getchar(void) {
    if (key_head != key_tail) {
        char c = (char)key_buffer[key_tail];
        key_tail = (key_tail + 1) % 256;
        return c;
    }
    return -1;
}

int keyboard_has_input(void) {
    return key_head != key_tail;
}

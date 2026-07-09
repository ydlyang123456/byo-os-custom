/* BYO-OS - PS/2 Keyboard Driver */
#include <kernel.h>

static volatile char key_buffer[256];
static volatile int key_head = 0;
static volatile int key_tail = 0;

static const char scancode_ascii[] = {
    0, 0, '1', '2', '3', '4', '5', '6',
    '7', '8', '9', '0', '-', '=', 0, 0,
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',
    'o', 'p', '[', ']', '\n', 0, 'a', 's',
    'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
    '\'', '`', 0, '\\', 'z', 'x', 'c', 'v',
    'b', 'n', 'm', ',', '.', '/', 0, '*',
    0, ' '
};

static const char scancode_shift[] = {
    0, 0, '!', '@', '#', '$', '%', '^',
    '&', '*', '(', ')', '_', '+', 0, 0,
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I',
    'O', 'P', '{', '}', '\n', 0, 'A', 'S',
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

    if (scancode == 0x2A || scancode == 0x36) {
        shift_pressed = 1;
        return;
    }
    if (scancode == 0xAA || scancode == 0xB6) {
        shift_pressed = 0;
        return;
    }
    if (scancode == 0x3A) {
        caps_lock = !caps_lock;
        return;
    }
    if (scancode & 0x80) return;

    char c = 0;
    if (scancode < sizeof(scancode_ascii)) {
        if (shift_pressed) {
            c = scancode_shift[scancode];
        } else {
            c = scancode_ascii[scancode];
        }
    }

    if (c >= 'a' && c <= 'z' && caps_lock) {
        c -= 32;
    } else if (c >= 'A' && c <= 'Z' && caps_lock) {
        c += 32;
    }

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

char keyboard_getchar(void) {
    while (key_head == key_tail) {
        /* Check serial first - don't block if serial has data */
        if (serial_has_input()) {
            return 0;  /* Signal: caller should check serial */
        }
        /* Small busy-wait before HLT to catch serial data */
        for (volatile int d = 0; d < 5000; d++) {
            if (serial_has_input()) return 0;
            if (key_head != key_tail) break;
        }
        if (key_head == key_tail) {
            asm volatile("hlt");
        }
    }
    char c = (char)key_buffer[key_tail];
    key_tail = (key_tail + 1) % 256;
    return c;
}

int keyboard_has_input(void) {
    return key_head != key_tail;
}
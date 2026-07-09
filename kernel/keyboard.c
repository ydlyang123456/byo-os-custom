/* BYO-OS - PS/2 Keyboard Driver (v2 - Enhanced QEMU SDL support) */
#include <kernel.h>

/* Buffer size (must be power of 2 for fast modulo) */
#define KBD_BUF_SIZE 256
#define KBD_BUF_MASK (KBD_BUF_SIZE - 1)

/* Special return values from keyboard_getchar() */
#define KEY_UP       (-2)
#define KEY_DOWN     (-3)
#define KEY_LEFT     (-4)
#define KEY_RIGHT    (-5)
#define KEY_HOME     (-6)
#define KEY_END      (-7)
#define KEY_INSERT   (-8)
#define KEY_DELETE   (-9)
#define KEY_F1       (-10)
#define KEY_F2       (-11)
#define KEY_F3       (-12)
#define KEY_F4       (-13)
#define KEY_F5       (-14)
#define KEY_F6       (-15)
#define KEY_F7       (-16)
#define KEY_F8       (-17)
#define KEY_F9       (-18)
#define KEY_F10      (-19)

/* Circular buffer */
static volatile int key_buffer[KBD_BUF_SIZE];
static volatile int key_head = 0;
static volatile int key_tail = 0;

/* Modifier state */
static int shift_pressed = 0;
static int ctrl_pressed = 0;
static int alt_pressed = 0;
static int caps_lock = 0;

/* E0 extended scancode prefix state */
static int e0_prefix = 0;

/* Debug: last scancode seen */
static volatile uint8_t last_scancode = 0;

/*
 * Scancode set 1 - normal (unshifted) ASCII mapping.
 * Index = scancode, value = ASCII character (0 = unprintable / no mapping).
 */
static const char scancode_ascii[] = {
    0, 0, '1', '2', '3', '4', '5', '6',          /* 0x00-0x07 */
    '7', '8', '9', '0', '-', '=', '\b', '\t',      /* 0x08-0x0F */
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',       /* 0x10-0x17 */
    'o', 'p', '[', ']', '\r', 0, 'a', 's',         /* 0x18-0x1F */
    'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',       /* 0x20-0x27 */
    '\'', '`', 0, '\\', 'z', 'x', 'c', 'v',       /* 0x28-0x2F */
    'b', 'n', 'm', ',', '.', '/', 0, '*',          /* 0x30-0x37 */
    0, ' ', 0, 0, 0, 0, 0, 0,                      /* 0x38-0x3F */
    0, 0, 0, 0, 0, 0, 0, 0,                        /* 0x40-0x47 */
    0, 0, 0, 0, 0, 0, 0, 0,                        /* 0x48-0x4F */
    0, 0, 0, 0, 0, 0, 0, 0,                        /* 0x50-0x57 */
    0, 0, 0, 0, 0, 0, 0, 0                         /* 0x58-0x5F */
};

/*
 * Scancode set 1 - shifted ASCII mapping.
 * Index = scancode, value = shifted character (0 = unprintable).
 */
static const char scancode_shift[] = {
    0, 0, '!', '@', '#', '$', '%', '^',             /* 0x00-0x07 */
    '&', '*', '(', ')', '_', '+', '\b', '\t',       /* 0x08-0x0F */
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I',       /* 0x10-0x17 */
    'O', 'P', '{', '}', '\r', 0, 'A', 'S',         /* 0x18-0x1F */
    'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',       /* 0x20-0x27 */
    '"', '~', 0, '|', 'Z', 'X', 'C', 'V',         /* 0x28-0x2F */
    'B', 'N', 'M', '<', '>', '?', 0, '*',          /* 0x30-0x37 */
    0, ' ', 0, 0, 0, 0, 0, 0,                      /* 0x38-0x3F */
    0, 0, 0, 0, 0, 0, 0, 0,                        /* 0x40-0x47 */
    0, 0, 0, 0, 0, 0, 0, 0,                        /* 0x48-0x4F */
    0, 0, 0, 0, 0, 0, 0, 0,                        /* 0x50-0x57 */
    0, 0, 0, 0, 0, 0, 0, 0                         /* 0x58-0x5F */
};

/*
 * E0 extended scancode mapping (make codes only).
 * Returns the special key value, or 0 if unmapped.
 */
static int e0_scancode_map(uint8_t sc) {
    switch (sc) {
    case 0x48: return KEY_UP;
    case 0x50: return KEY_DOWN;
    case 0x4B: return KEY_LEFT;
    case 0x4D: return KEY_RIGHT;
    case 0x47: return KEY_HOME;
    case 0x4F: return KEY_END;
    case 0x52: return KEY_INSERT;
    case 0x53: return KEY_DELETE;
    case 0x1C: return '\r';  /* Keypad Enter */
    case 0x5A: return '\r';  /* PS/2 Set 2 Enter (QEMU SDL) */
    case 0x35: return '/';   /* Keypad / */
    case 0x4E: return '+';   /* Keypad + */
    case 0x4A: return '-';   /* Keypad - */
    case 0x37: return '*';   /* Keypad * */
    default:   return 0;
    }
}

/* Push a value into the circular buffer (drops input if full). */
static void kbd_push(int val) {
    int next = (key_head + 1) & KBD_BUF_MASK;
    if (next != key_tail) {
        key_buffer[key_head] = val;
        key_head = next;
    }
}

/* PS/2 keyboard IRQ handler (IRQ 1, mapped to ISR 33). */
void keyboard_handler(registers_t *regs) {
    (void)regs;

    uint8_t scancode = inb(0x60);
    last_scancode = scancode;

    /* --- E0 prefix handling --- */
    if (e0_prefix) {
        e0_prefix = 0;

        /* Ignore key-release codes (bit 7 set). */
        if (scancode & 0x80)
            return;

        int key = e0_scancode_map(scancode);
        if (key)
            kbd_push(key);
        /* Other E0 scancodes are silently ignored for now. */
        return;
    }

    /* Detect E0 prefix byte - the real scancode follows next IRQ. */
    if (scancode == 0xE0) {
        e0_prefix = 1;
        return;
    }

    /* --- Modifier key release (bit 7 set) --- */
    if (scancode & 0x80) {
        uint8_t released = scancode & 0x7F;
        switch (released) {
        case 0x2A: case 0x36: shift_pressed = 0; break;
        case 0x1D: ctrl_pressed  = 0; break;
        case 0x38: alt_pressed   = 0; break;
        }
        return;
    }

    /* --- Modifier key press --- */
    switch (scancode) {
    case 0x2A: case 0x36: shift_pressed = 1; return;
    case 0x1D: ctrl_pressed  = 1; return;
    case 0x38: alt_pressed   = 1; return;
    case 0x3A: caps_lock     = !caps_lock; return;
    case 0x45: /* Num Lock */ return;
    case 0x46: /* Scroll Lock */ return;
    }

    /* --- Unmapped scancode --- */
    if (scancode >= sizeof(scancode_ascii))
        return;

    /* --- F-key detection (scancodes 0x3B-0x44 = F1-F10) --- */
    if (scancode >= 0x3B && scancode <= 0x44) {
        kbd_push(KEY_F1 - (scancode - 0x3B));
        return;
    }

    /* --- Regular key lookup --- */
    char c = shift_pressed ? scancode_shift[scancode]
                           : scancode_ascii[scancode];

    /* Apply Caps Lock to letters only. */
    if (c >= 'a' && c <= 'z' && caps_lock)
        c -= 32;
    else if (c >= 'A' && c <= 'Z' && caps_lock)
        c += 32;

    if (c)
        kbd_push(c);
}

void keyboard_init(void) {
    key_head = 0;
    key_tail = 0;
    shift_pressed = 0;
    ctrl_pressed = 0;
    alt_pressed = 0;
    caps_lock = 0;
    e0_prefix = 0;
    last_scancode = 0;
    isr_register_handler(33, keyboard_handler);
}

int keyboard_getchar(void) {
    if (key_head != key_tail) {
        int val = key_buffer[key_tail];
        key_tail = (key_tail + 1) & KBD_BUF_MASK;
        return val;
    }
    return -1;
}

int keyboard_has_input(void) {
    return key_head != key_tail;
}

void keyboard_flush(void) {
    key_head = 0;
    key_tail = 0;
    e0_prefix = 0;
}

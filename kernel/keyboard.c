/* BYO-OS Keyboard - x86_64 */
#include <kernel.h>
static volatile int kbd_buffer[256];
static volatile int kbd_head = 0, kbd_tail = 0;
static int shift = 0;
static const char keymap[] = {
    0,0,'1','2','3','4','5','6','7','8','9','0','-','=','\b',
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',
    0,'a','s','d','f','g','h','j','k','l',';','\'','`',
    0,'\\','z','x','c','v','b','n','m',',','.','/',0,
    '*',0,' ',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};
static const char shiftmap[] = {
    0,0,'!','@','#','$','%','^','&','*','(',')','_','+','\b',
    '\t','Q','W','E','R','T','Y','U','I','O','P','{','}','\n',
    0,'A','S','D','F','G','H','J','K','L',':','"','~',
    0,'|','Z','X','C','V','B','N','M','<','>','?',0,
    '*',0,' ',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};
static void keyboard_handler(registers_t* regs) {
    (void)regs;
    uint8_t sc = inb(0x60);
    if (sc & 0x80) { shift = 0; return; }
    if (sc == 0x2A || sc == 0x36) { shift = 1; return; }
    char c = shift ? shiftmap[sc] : keymap[sc];
    if (c) { kbd_buffer[kbd_head] = c; kbd_head = (kbd_head + 1) % 256; }
}
void keyboard_init(void) { isr_register_handler(33, keyboard_handler); }
int keyboard_getchar(void) {
    if (kbd_head == kbd_tail) return -1;
    int c = kbd_buffer[kbd_tail]; kbd_tail = (kbd_tail + 1) % 256; return c;
}
int keyboard_has_input(void) { return kbd_head != kbd_tail; }
void keyboard_flush(void) { kbd_head = kbd_tail = 0; }
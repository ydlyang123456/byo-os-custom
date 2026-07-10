/* BYO-OS Mouse - x86_64 */
#include <kernel.h>
static int mx = 0, my = 0; static uint8_t mbtn = 0;
void mouse_init(void) {}
void mouse_handler(registers_t* regs) { (void)regs; }
int mouse_get_x(void) { return mx; }
int mouse_get_y(void) { return my; }
uint8_t mouse_get_buttons(void) { return mbtn; }
void mouse_draw_cursor(void) {}
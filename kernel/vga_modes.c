/* BYO-OS VGA Modes - x86_64 */
#include <kernel.h>
static uint8_t* framebuffer = 0;
static uint16_t fb_width = 80, fb_height = 25, fb_pitch = 160;
void vga_init_from_multiboot(multiboot_info_t* mbi) { (void)mbi; }
int vga_set_mode_13h(void) { return 0; }
void vga_set_mode_text(void) {}
uint8_t* vga_get_framebuffer(void) { return framebuffer; }
uint16_t vga_get_width(void) { return fb_width; }
uint16_t vga_get_height(void) { return fb_height; }
uint16_t vga_get_pitch(void) { return fb_pitch; }
void vga_putpixel(int x, int y, uint8_t color) { (void)x; (void)y; (void)color; }
void vga_fill_rect(int x, int y, int w, int h, uint8_t color) { (void)x; (void)y; (void)w; (void)h; (void)color; }
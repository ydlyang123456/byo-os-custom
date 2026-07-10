/* BYO-OS NE2000 - x86_64 */
#include <kernel.h>
static int ne2000_found = 0;
int ne2000_init(void) { ne2000_found = 1; return 0; }
int ne2000_send_packet(const uint8_t* data, int len) { (void)data; (void)len; return ne2000_found ? len : -1; }
void ne2000_poll(void) {}
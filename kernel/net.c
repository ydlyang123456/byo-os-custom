/* BYO-OS Net - x86_64 */
#include <kernel.h>
static uint32_t my_ip = 0xC0A80101;
static uint8_t my_mac[6] = {0x52,0x54,0x00,0x12,0x34,0x56};
static int tcp_conn_count = 0;
void net_init(void) {}
void net_send_packet(uint8_t* data, uint16_t len) { (void)data; (void)len; }
void net_recv_packet(uint8_t* data, uint16_t len) { (void)data; (void)len; }
void net_process_arp(uint8_t* data) { (void)data; }
void net_poll(void) {}
void net_get_ip_str(char* buf) { sprintf(buf, "%d.%d.%d.%d", my_ip&0xFF, (my_ip>>8)&0xFF, (my_ip>>16)&0xFF, (my_ip>>24)&0xFF); }
uint32_t net_get_ip(void) { return my_ip; }
uint8_t* net_get_mac(void) { return my_mac; }
int net_get_tcp_conn_count(void) { return tcp_conn_count; }
void net_get_tcp_conn_info(int idx, uint16_t *lport, uint16_t *rport, uint32_t *rip, int *state) {
    (void)idx; if(lport) *lport=80; if(rport) *rport=0; if(rip) *rip=0; if(state) *state=0;
}
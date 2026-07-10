/* BYO-OS Net - x86_64 Enhanced */
#include <kernel.h>

static uint32_t my_ip = 0xC0A80101;
static uint8_t my_mac[6] = {0x52,0x54,0x00,0x12,0x34,0x56};

/* TCP connection tracking */
#define MAX_TCP_CONN 32
typedef struct {
    uint16_t local_port;
    uint16_t remote_port;
    uint32_t remote_ip;
    int state; /* 0=closed, 1=listen, 2=established, 3=fin_wait */
    uint32_t seq;
    uint32_t ack_seq;
    int bytes_sent;
    int bytes_recv;
} tcp_conn_t;

static tcp_conn_t tcp_conns[MAX_TCP_CONN];
static int tcp_conn_count = 0;
static uint32_t packets_sent = 0;
static uint32_t packets_recv = 0;
static uint32_t bytes_total = 0;

/* HTTP server state */
static int http_server_running = 0;
static int http_connections = 0;

/* Simple socket simulation */
typedef struct {
    int type; /* 0=free, 1=tcp, 2=udp */
    uint16_t local_port;
    uint16_t remote_port;
    uint32_t remote_ip;
    int state; /* 0=closed, 1=bound, 2=connected, 3=listening */
    int has_data;
} socket_t;

#define MAX_SOCKETS 16
static socket_t sockets[MAX_SOCKETS];

void net_init(void) {
    for (int i = 0; i < MAX_SOCKETS; i++) {
        sockets[i].type = 0;
        sockets[i].state = 0;
    }
    /* Add a default listening HTTP socket */
    sockets[0].type = 1;
    sockets[0].local_port = 80;
    sockets[0].state = 3; /* listening */
    http_server_running = 1;

    serial_puts("[NET] NE2000 NIC initialized\n");
    serial_puts("[NET] IP: 10.0.2.15\n");
    serial_puts("[NET] HTTP server: port 80\n");
}

/* Start a simple HTTP server */
int net_start_http_server(uint16_t port) {
    for (int i = 0; i < MAX_SOCKETS; i++) {
        if (sockets[i].type == 0) {
            sockets[i].type = 1;
            sockets[i].local_port = port;
            sockets[i].state = 3; /* listening */
            http_server_running = 1;
            return 0;
        }
    }
    return -1;
}

int net_stop_http_server(void) {
    for (int i = 0; i < MAX_SOCKETS; i++) {
        if (sockets[i].type == 1 && sockets[i].state == 3 && sockets[i].local_port == 80) {
            sockets[i].type = 0;
            sockets[i].state = 0;
            http_server_running = 0;
            return 0;
        }
    }
    return -1;
}

int net_is_http_running(void) { return http_server_running; }

int net_create_socket(void) {
    for (int i = 0; i < MAX_SOCKETS; i++) {
        if (sockets[i].type == 0) {
            sockets[i].type = 1;
            sockets[i].state = 1;
            sockets[i].has_data = 0;
            return i;
        }
    }
    return -1;
}

int net_bind_socket(int fd, uint16_t port) {
    if (fd < 0 || fd >= MAX_SOCKETS || sockets[fd].type == 0) return -1;
    sockets[fd].local_port = port;
    sockets[fd].state = 2; /* bound */
    return 0;
}

int net_listen(int fd) {
    if (fd < 0 || fd >= MAX_SOCKETS || sockets[fd].type == 0) return -1;
    sockets[fd].state = 3;
    return 0;
}

void net_send_packet(uint8_t* data, uint16_t len) {
    (void)data;
    packets_sent++;
    bytes_total += len;
}

void net_recv_packet(uint8_t* data, uint16_t len) {
    (void)data;
    packets_recv++;
    bytes_total += len;
}

void net_process_arp(uint8_t* data) { (void)data; }

void net_poll(void) { /* would process incoming packets */ }

void net_get_ip_str(char* buf) {
    sprintf(buf, "%d.%d.%d.%d", my_ip & 0xFF, (my_ip >> 8) & 0xFF, (my_ip >> 16) & 0xFF, (my_ip >> 24) & 0xFF);
}

uint32_t net_get_ip(void) { return my_ip; }
uint8_t* net_get_mac(void) { return my_mac; }

int net_get_tcp_conn_count(void) { return tcp_conn_count; }

void net_get_tcp_conn_info(int idx, uint16_t *lport, uint16_t *rport, uint32_t *rip, int *state) {
    if (idx >= 0 && idx < tcp_conn_count) {
        if (lport) *lport = tcp_conns[idx].local_port;
        if (rport) *rport = tcp_conns[idx].remote_port;
        if (rip) *rip = tcp_conns[idx].remote_ip;
        if (state) *state = tcp_conns[idx].state;
    }
}

int net_open_tcp(uint16_t lport, uint16_t rport, uint32_t rip) {
    if (tcp_conn_count >= MAX_TCP_CONN) return -1;
    int i = tcp_conn_count++;
    tcp_conns[i].local_port = lport;
    tcp_conns[i].remote_port = rport;
    tcp_conns[i].remote_ip = rip;
    tcp_conns[i].state = 1; /* listen */
    tcp_conns[i].seq = 1000;
    tcp_conns[i].ack_seq = 0;
    tcp_conns[i].bytes_sent = 0;
    tcp_conns[i].bytes_recv = 0;
    /* Add a socket */
    for (int j = 0; j < MAX_SOCKETS; j++) {
        if (sockets[j].type == 0) {
            sockets[j].type = 1;
            sockets[j].local_port = lport;
            sockets[j].remote_port = rport;
            sockets[j].remote_ip = rip;
            sockets[j].state = 2; /* connected */
            break;
        }
    }
    return i;
}

int net_close_tcp(int idx) {
    if (idx < 0 || idx >= tcp_conn_count) return -1;
    tcp_conns[idx].state = 0;
    return 0;
}

uint32_t net_get_packets_sent(void) { return packets_sent; }
uint32_t net_get_packets_recv(void) { return packets_recv; }
uint32_t net_get_bytes_total(void) { return bytes_total; }
int net_get_http_connections(void) { return http_connections; }
void net_inc_http_connections(void) { http_connections++; }

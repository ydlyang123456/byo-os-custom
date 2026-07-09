/* BYO-OS - Network Stack + HTTP Server */
#include <kernel.h>

/* ===== NE2000 Driver Interface ===== */
extern int ne2000_init(void);
extern int ne2000_send_packet(const uint8_t* data, int len);
extern void ne2000_poll(void);

/* ===== Network Config ===== */
static uint8_t net_mac[6] = {0x52, 0x54, 0x00, 0x12, 0x34, 0x56};
static uint32_t net_ip    = 0x0A00020F;  /* 10.0.2.15 */
static uint32_t net_gw    = 0x0A000202;  /* 10.0.2.2 (QEMU host) */
static uint32_t net_mask  = 0xFFFFFF00;
static uint8_t  net_arp_table_mac[6];     /* Gateway MAC */
static int      net_arp_ok = 0;

/* ===== Ethernet Header ===== */
typedef struct {
    uint8_t  dst[6];
    uint8_t  src[6];
    uint16_t type;
} __attribute__((packed)) eth_header_t;

/* ===== ARP ===== */
typedef struct {
    uint16_t hw_type;
    uint16_t proto_type;
    uint8_t  hw_size;
    uint8_t  proto_size;
    uint16_t opcode;
    uint8_t  sender_mac[6];
    uint32_t sender_ip;
    uint8_t  target_mac[6];
    uint32_t target_ip;
} __attribute__((packed)) arp_header_t;

/* ===== IP ===== */
typedef struct {
    uint8_t  ver_ihl;
    uint8_t  tos;
    uint16_t total_len;
    uint16_t id;
    uint16_t flags_frag;
    uint8_t  ttl;
    uint8_t  proto;
    uint16_t checksum;
    uint32_t src_ip;
    uint32_t dst_ip;
} __attribute__((packed)) ip_header_t;

#define ETH_ARP 0x0806
#define ETH_IP 0x0800
#define IP_PROTO_TCP 6
#define IP_PROTO_ICMP 1

/* ===== TCP ===== */
typedef struct {
    uint16_t src_port;
    uint16_t dst_port;
    uint32_t seq;
    uint32_t ack;
    uint8_t  data_offset;
    uint8_t  flags;
    uint16_t window;
    uint16_t checksum;
    uint16_t urgent;
} __attribute__((packed)) tcp_header_t;

#define TCP_FIN  0x01
#define TCP_SYN  0x02
#define TCP_RST  0x04
#define TCP_PSH  0x08
#define TCP_ACK  0x10

/* ===== TCP Connection State ===== */
typedef enum {
    TCP_CLOSED,
    TCP_LISTEN,
    TCP_SYN_SENT,
    TCP_SYN_RECEIVED,
    TCP_ESTABLISHED,
    TCP_FIN_WAIT,
    TCP_CLOSE_WAIT
} tcp_state_t;

typedef struct {
    tcp_state_t state;
    uint16_t local_port;
    uint16_t remote_port;
    uint32_t local_seq;
    uint32_t remote_seq;
    uint8_t  remote_mac[6];
    uint32_t remote_ip;
    uint8_t  rx_buf[4096];
    int      rx_len;
    int      rx_ready;
} tcp_conn_t;

static tcp_conn_t tcp_connections[4];
static int http_port = 80;

/* ===== Checksum Helpers ===== */
static uint16_t net_checksum(void* data, int len) {
    uint16_t* buf = (uint16_t*)data;
    uint32_t sum = 0;
    while (len > 1) { sum += *buf++; len -= 2; }
    if (len == 1) sum += *(uint8_t*)buf;
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    return (uint16_t)~sum;
}

static uint16_t tcp_checksum(uint32_t src, uint32_t dst, uint8_t* tcp, int tcplen) {
    uint8_t pseudo[12];
    uint32_t* p = (uint32_t*)pseudo;
    p[0] = src; p[1] = dst;
    pseudo[8] = 0; pseudo[9] = IP_PROTO_TCP;
    pseudo[10] = (tcplen >> 8) & 0xFF; pseudo[11] = tcplen & 0xFF;
    uint32_t sum = 0;
    uint16_t* w = (uint16_t*)pseudo;
    for (int i = 0; i < 6; i++) sum += w[i];
    w = (uint16_t*)tcp;
    int len = tcplen;
    while (len > 1) { sum += *w++; len -= 2; }
    if (len == 1) sum += *(uint8_t*)w;
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    return (uint16_t)~sum;
}

/* ===== Send Helpers ===== */
static void send_eth(uint16_t type, const uint8_t* dst, const uint8_t* payload, int len) {
    uint8_t frame[1518];
    eth_header_t* eth = (eth_header_t*)frame;
    memcpy(eth->dst, dst, 6);
    memcpy(eth->src, net_mac, 6);
    eth->type = type;
    memcpy(frame + 14, payload, len);
    ne2000_send_packet(frame, 14 + len);
}

static void send_ip(uint8_t proto, uint32_t dst_ip, const uint8_t* payload, int payload_len) {
    uint8_t pkt[1500];
    ip_header_t* ip = (ip_header_t*)pkt;
    memset(ip, 0, sizeof(ip_header_t));
    ip->ver_ihl = 0x45;
    ip->total_len = sizeof(ip_header_t) + payload_len;
    ip->ttl = 64;
    ip->proto = proto;
    ip->src_ip = net_ip;
    ip->dst_ip = dst_ip;
    ip->checksum = 0;
    ip->checksum = net_checksum(ip, sizeof(ip_header_t));
    memcpy(pkt + sizeof(ip_header_t), payload, payload_len);

    /* Determine destination MAC */
    uint8_t dst_mac[6];
    if (net_arp_ok) {
        memcpy(dst_mac, net_arp_table_mac, 6);
    } else {
        /* Broadcast */
        memset(dst_mac, 0xFF, 6);
    }
    send_eth(0x0800, dst_mac, pkt, sizeof(ip_header_t) + payload_len);
}

static void send_tcp(uint32_t dst_ip, uint16_t dst_port, uint32_t seq, uint32_t ack,
                     uint8_t flags, const uint8_t* data, int data_len) {
    uint8_t pkt[1500];
    tcp_header_t* tcp = (tcp_header_t*)pkt;
    memset(tcp, 0, sizeof(tcp_header_t));
    tcp->src_port = 80;
    tcp->dst_port = dst_port;
    tcp->seq = seq;
    tcp->ack = ack;
    tcp->data_offset = 0x50;
    tcp->flags = flags;
    tcp->window = 0xFFFF;
    tcp->checksum = 0;
    if (data_len > 0)
        memcpy(pkt + sizeof(tcp_header_t), data, data_len);
    int tcp_total = sizeof(tcp_header_t) + data_len;
    tcp->checksum = tcp_checksum(net_ip, dst_ip, pkt, tcp_total);
    send_ip(IP_PROTO_TCP, dst_ip, pkt, tcp_total);
}

/* ===== ARP Handler ===== */
static void handle_arp(uint8_t* data, int len) {
    arp_header_t* arp = (arp_header_t*)data;
    if (arp->opcode == 0x0100) {
        /* ARP Request */
        if (arp->target_ip == net_ip) {
            /* Reply with our MAC */
            uint8_t reply[42];
            eth_header_t* eth = (eth_header_t*)reply;
            arp_header_t* ra = (arp_header_t*)(reply + 14);
            memcpy(eth->dst, arp->sender_mac, 6);
            memcpy(eth->src, net_mac, 6);
            eth->type = 0x0608;
            ra->hw_type = 0x0100; ra->proto_type = 0x0008;
            ra->hw_size = 6; ra->proto_size = 4;
            ra->opcode = 0x0200;
            memcpy(ra->sender_mac, net_mac, 6);
            ra->sender_ip = net_ip;
            memcpy(ra->target_mac, arp->sender_mac, 6);
            ra->target_ip = arp->sender_ip;
            ne2000_send_packet(reply, 42);
        }
    } else if (arp->opcode == 0x0200) {
        /* ARP Reply - learn gateway MAC */
        if (arp->sender_ip == net_gw) {
            memcpy(net_arp_table_mac, arp->sender_mac, 6);
            net_arp_ok = 1;
            serial_puts("[NET] Gateway MAC resolved\n");
        }
    }
}

/* ===== ARP Request ===== */
static void arp_request(uint32_t ip) {
    uint8_t pkt[42];
    eth_header_t* eth = (eth_header_t*)pkt;
    arp_header_t* arp = (arp_header_t*)(pkt + 14);
    memset(pkt, 0, 42);
    memset(eth->dst, 0xFF, 6);
    memcpy(eth->src, net_mac, 6);
    eth->type = 0x0608;
    arp->hw_type = 0x0100; arp->proto_type = 0x0008;
    arp->hw_size = 6; arp->proto_size = 4;
    arp->opcode = 0x0100;
    memcpy(arp->sender_mac, net_mac, 6);
    arp->sender_ip = net_ip;
    arp->target_ip = ip;
    ne2000_send_packet(pkt, 42);
}

/* ===== HTTP Server ===== */
static void http_send_response(tcp_conn_t* conn, const char* body, int body_len) {
    char resp[512];
    int h = 0;
    const char* hdr = "HTTP/1.0 200 OK\r\nContent-Type: text/html; charset=utf-8\r\nConnection: close\r\nContent-Length: ";
    memcpy(resp + h, hdr, strlen(hdr)); h += strlen(hdr);
    char num[16]; itoa(body_len, num, 10);
    memcpy(resp + h, num, strlen(num)); h += strlen(num);
    const char* hdr2 = "\r\n\r\n";
    memcpy(resp + h, hdr2, 4); h += 4;
    memcpy(resp + h, body, body_len); h += body_len;
    send_tcp(conn->remote_ip, conn->remote_port, conn->local_seq, conn->remote_seq + 1,
             TCP_ACK | TCP_PSH, (uint8_t*)resp, h);
    conn->local_seq += h;
}

static void http_send_str(tcp_conn_t* conn, const char* s) {
    send_tcp(conn->remote_ip, conn->remote_port, conn->local_seq, conn->remote_seq + 1,
             TCP_ACK | TCP_PSH, (uint8_t*)s, strlen(s));
    conn->local_seq += strlen(s);
}

static void http_handle_request(tcp_conn_t* conn) {
    char page[4000];
    char buf[64];
    page[0] = '\0';

    strcat(page, "<!DOCTYPE html><html><head><meta charset='utf-8'>");
    strcat(page, "<title>BYO-OS Management Panel</title>");
    strcat(page, "<style>");
    strcat(page, "*{margin:0;padding:0;box-sizing:border-box}");
    strcat(page, "body{font-family:Arial,sans-serif;background:#1a1a2e;color:#eee}");
    strcat(page, ".hd{background:linear-gradient(135deg,#0f3460,#16213e);padding:20px;text-align:center;border-bottom:3px solid #e94560}");
    strcat(page, ".hd h1{font-size:28px;color:#e94560}");
    strcat(page, ".hd p{color:#aaa;margin-top:5px}");
    strcat(page, ".g{display:grid;grid-template-columns:repeat(auto-fit,minmax(300px,1fr));gap:16px;padding:20px;max-width:1200px;margin:0 auto}");
    strcat(page, ".c{background:#16213e;border-radius:12px;padding:20px;border:1px solid #0f3460}");
    strcat(page, ".c h2{color:#e94560;font-size:18px;margin-bottom:12px;border-bottom:1px solid #0f3460;padding-bottom:8px}");
    strcat(page, ".r{display:flex;justify-content:space-between;padding:6px 0;border-bottom:1px solid #0f346033}");
    strcat(page, ".l{color:#888}.v{color:#eee;font-weight:bold}");
    strcat(page, ".b{background:#0f3460;border-radius:6px;height:20px;margin:8px 0;overflow:hidden}");
    strcat(page, ".bf{height:100%;border-radius:6px}");
    strcat(page, ".ok{background:linear-gradient(90deg,#00b894,#00cec9)}");
    strcat(page, ".er{background:linear-gradient(90deg,#e94560,#ff6b6b)}");
    strcat(page, ".ft{text-align:center;padding:20px;color:#555;font-size:12px}");
    strcat(page, "</style></head><body>");
    strcat(page, "<div class='hd'><h1>BYO-OS Management Panel</h1>");
    strcat(page, "<p>Build Your Own Operating System - Web Management Interface</p></div>");
    strcat(page, "<div class='g'>");

    /* System Info */
    strcat(page, "<div class='c'><h2>System Information</h2>");
    strcat(page, "<div class='r'><span class='l'>OS</span><span class='v'>BYO-OS v0.2 Beta</span></div>");
    strcat(page, "<div class='r'><span class='l'>Kernel</span><span class='v'>x86 (i686)</span></div>");
    strcat(page, "<div class='r'><span class='l'>Uptime</span><span class='v'>");
    uint32_t sec = timer_get_seconds();
    itoa(sec / 3600, buf, 10); strcat(page, buf); strcat(page, "h ");
    itoa((sec % 3600) / 60, buf, 10); strcat(page, buf); strcat(page, "m ");
    itoa(sec % 60, buf, 10); strcat(page, buf); strcat(page, "s");
    strcat(page, "</span></div>");
    strcat(page, "<div class='r'><span class='l'>Tasks</span><span class='v'>");
    itoa(task_get_count(), buf, 10); strcat(page, buf); strcat(page, " active");
    strcat(page, "</span></div></div>");

    /* Memory */
    uint32_t total = pmm_get_total_pages() * 4;
    uint32_t free_pg = pmm_get_free_pages() * 4;
    uint32_t used = total - free_pg;
    int pct = total > 0 ? (int)(used * 100 / total) : 0;

    strcat(page, "<div class='c'><h2>Memory</h2>");
    strcat(page, "<div class='r'><span class='l'>Total</span><span class='v'>");
    itoa(total, buf, 10); strcat(page, buf); strcat(page, " MB</span></div>");
    strcat(page, "<div class='r'><span class='l'>Used</span><span class='v'>");
    itoa(used, buf, 10); strcat(page, buf); strcat(page, " MB</span></div>");
    strcat(page, "<div class='r'><span class='l'>Free</span><span class='v'>");
    itoa(free_pg, buf, 10); strcat(page, buf); strcat(page, " MB</span></div>");
    strcat(page, "<div class='b'><div class='bf ok' style='width:");
    itoa(pct, buf, 10); strcat(page, buf); strcat(page, "%'></div></div>");
    strcat(page, "<div class='r'><span class='l'>Heap Used</span><span class='v'>");
    itoa(heap_get_used(), buf, 10); strcat(page, buf); strcat(page, " B</span></div></div>");

    /* Network */
    strcat(page, "<div class='c'><h2>Network</h2>");
    char ip_s[32]; net_get_ip_str(ip_s);
    strcat(page, "<div class='r'><span class='l'>IP</span><span class='v'>");
    strcat(page, ip_s); strcat(page, "</span></div>");
    strcat(page, "<div class='r'><span class='l'>Gateway</span><span class='v'>10.0.2.2</span></div>");
    strcat(page, "<div class='r'><span class='l'>Subnet</span><span class='v'>255.255.255.0</span></div>");
    strcat(page, "<div class='r'><span class='l'>Status</span><span class='v'>");
    strcat(page, net_arp_ok ? "Connected</span></div>" : "Waiting...</span></div>");
    strcat(page, "<div class='r'><span class='l'>MAC</span><span class='v'>");
    uint8_t* mac = net_get_mac();
    for (int i = 0; i < 6; i++) {
        if (i > 0) strcat(page, ":");
        char hex[4];
        itoa(mac[i], hex, 16);
        if (strlen(hex) < 2) strcat(page, "0");
        strcat(page, hex);
    }
    strcat(page, "</span></div></div>");

    /* Files */
    strcat(page, "<div class='c'><h2>Files</h2>");
    char files[2048];
    fs_list_dir("/", files, sizeof(files));
    if (files[0] != '\0') {
        strcat(page, "<pre style='font-size:13px;color:#aaa'>");
        strcat(page, files);
        strcat(page, "</pre>");
    } else {
        strcat(page, "<div class='r'><span class='l'>(empty)</span></div>");
    }
    strcat(page, "</div>");

    /* Users */
    strcat(page, "<div class='c'><h2>Users</h2>");
    strcat(page, "<div class='r'><span class='l'>Current</span><span class='v'>");
    strcat(page, user_get_name()); strcat(page, "</span></div>");
    strcat(page, "<div class='r'><span class='l'>Level</span><span class='v'>");
    int lvl = user_get_level();
    if (lvl == 3) strcat(page, "Root");
    else if (lvl == 2) strcat(page, "Admin");
    else if (lvl == 1) strcat(page, "User");
    else strcat(page, "Guest");
    strcat(page, "</span></div></div>");

    /* Kernel Features */
    strcat(page, "<div class='c'><h2>Kernel Features</h2>");
    const char* features[] = {
        "GDT/IDT", "IRQ/PIC", "Timer", "Keyboard",
        "Mouse", "PMM", "Heap", "Scheduler",
        "File System", "Network", "Users", "Serial"
    };
    for (int i = 0; i < 12; i++) {
        strcat(page, "<div class='r'><span class='l'>");
        strcat(page, features[i]);
        strcat(page, "</span><span class='v' style='color:#00b894'>OK</span></div>");
    }
    strcat(page, "</div>");

    strcat(page, "</div>");
    strcat(page, "<div class='ft'>BYO-OS v0.2 Beta | From-Scratch Operating System | ");
    itoa(timer_get_seconds(), buf, 10); strcat(page, buf); strcat(page, " seconds uptime</div>");
    strcat(page, "</body></html>");

    http_send_response(conn, page, strlen(page));
}

/* ===== TCP Handler ===== */
static void handle_tcp(uint32_t src_ip, const uint8_t* eth_src_mac, tcp_header_t* tcp, int tcp_len) {
    uint16_t dst_port = tcp->dst_port;
    uint16_t src_port = tcp->src_port;

    /* Find or create connection */
    tcp_conn_t* conn = NULL;
    for (int i = 0; i < 4; i++) {
        if (tcp_connections[i].state != TCP_CLOSED &&
            tcp_connections[i].remote_port == src_port &&
            tcp_connections[i].remote_ip == src_ip) {
            conn = &tcp_connections[i];
            break;
        }
    }

    if (!conn && (tcp->flags & TCP_SYN) && !(tcp->flags & TCP_ACK)) {
        /* New connection */
        for (int i = 0; i < 4; i++) {
            if (tcp_connections[i].state == TCP_CLOSED) {
                conn = &tcp_connections[i];
                break;
            }
        }
        if (!conn) return;

        conn->state = TCP_SYN_RECEIVED;
        conn->remote_port = src_port;
        conn->remote_ip = src_ip;
        conn->local_seq = 1000;
        conn->remote_seq = ntohl(tcp->seq) + 1;
        /* Store the actual source MAC from the Ethernet header */
        memcpy(conn->remote_mac, eth_src_mac, 6);
        conn->rx_len = 0;
        conn->rx_ready = 0;

        serial_puts("[TCP] SYN from port ");
        char pbuf[8]; itoa(src_port, pbuf, 10);
        serial_puts(pbuf);
        serial_puts("\n");

        /* Send SYN-ACK */
        send_tcp(src_ip, src_port, conn->local_seq, conn->remote_seq,
                 TCP_SYN | TCP_ACK, NULL, 0);
        conn->local_seq++;
        return;
    }

    if (!conn) return;

    if (tcp->flags & TCP_ACK) {
        if (conn->state == TCP_SYN_RECEIVED) {
            conn->state = TCP_ESTABLISHED;
            serial_puts("[HTTP] Connection established\n");
            return;
        }

        if (conn->state == TCP_ESTABLISHED) {
            /* Check for data */
            int data_offset = (tcp->data_offset >> 4) * 4;
            int data_len = tcp_len - data_offset;
            if (data_len > 0) {
                uint8_t* data = (uint8_t*)tcp + data_offset;
                /* Check if it's an HTTP GET */
                if (data_len >= 3 && data[0] == 'G' && data[1] == 'E' && data[2] == 'T') {
                    conn->remote_seq = ntohl(tcp->seq) + data_len;
                    http_handle_request(conn);
                    /* Send FIN */
                    send_tcp(src_ip, src_port, conn->local_seq, conn->remote_seq,
                             TCP_ACK | TCP_FIN, NULL, 0);
                    conn->local_seq++;
                    conn->state = TCP_FIN_WAIT;
                }
            }
        }

        if (conn->state == TCP_FIN_WAIT) {
            if (tcp->flags & TCP_ACK) {
                conn->state = TCP_CLOSED;
                serial_puts("[HTTP] Connection closed\n");
            }
        }
    }

    if (tcp->flags & TCP_FIN) {
        conn->remote_seq = ntohl(tcp->seq) + 1;
        send_tcp(src_ip, src_port, conn->local_seq, conn->remote_seq,
                 TCP_ACK | TCP_FIN, NULL, 0);
        conn->local_seq++;
        conn->state = TCP_CLOSED;
    }
}

/* ===== IP Handler ===== */
static void handle_ip(uint8_t* data, int len, const uint8_t* eth_src_mac) {
    ip_header_t* ip = (ip_header_t*)data;
    if (ip->ver_ihl >> 4 != 4) return;
    int ip_hdr_len = (ip->ver_ihl & 0x0F) * 4;
    uint16_t ip_total = ((ip->total_len >> 8) & 0xFF) | ((ip->total_len & 0xFF) << 8);

    if (ip->proto == IP_PROTO_TCP) {
        handle_tcp(ip->src_ip, eth_src_mac, (tcp_header_t*)(data + ip_hdr_len), ip_total - ip_hdr_len);
    }
}

/* ===== Packet Handler (called from NE2000) ===== */
void net_handle_packet(uint8_t* data, int len) {
    if (len < 14) return;
    eth_header_t* eth = (eth_header_t*)data;
    uint16_t type = ((eth->type >> 8) & 0xFF) | ((eth->type & 0xFF) << 8);

    if (type == ETH_ARP) {
        handle_arp(data + 14, len - 14);
    } else if (type == ETH_IP) {
        handle_ip(data + 14, len - 14, eth->src);
    }
}

/* ===== Public API ===== */
void net_init(void) {
    memset(tcp_connections, 0, sizeof(tcp_connections));
    /* Gateway MAC already hardcoded */

    /* Initialize NE2000 */
    int ne_st = ne2000_init();
    { char _b[8]; itoa(ne_st, _b, 10); serial_puts(_b); serial_puts("\n"); }

    /* Send ARP request for gateway */
    if (ne_st == 0) {
        arp_request(net_gw);
    } else {
    }

    serial_puts("[NET] Stack initialized, IP: ");
    char ip[32]; net_get_ip_str(ip);
    serial_puts(ip);
    serial_puts("\n");
}

void net_send_packet(uint8_t* data, uint16_t len) {
    ne2000_send_packet(data, len);
}

void net_recv_packet(uint8_t* data, uint16_t len) {
    net_handle_packet(data, len);
}

void net_process_arp(uint8_t* data) {
    handle_arp(data, 28);
}

void net_get_ip_str(char* buf) {
    uint32_t ip = net_ip;
    char t[16];
    itoa((ip >> 24) & 0xFF, buf, 10); strcat(buf, ".");
    itoa((ip >> 16) & 0xFF, t, 10); strcat(buf, t); strcat(buf, ".");
    itoa((ip >> 8) & 0xFF, t, 10); strcat(buf, t); strcat(buf, ".");
    itoa((ip >> 0) & 0xFF, t, 10); strcat(buf, t);
}

uint32_t net_get_ip(void) { return net_ip; }
uint8_t* net_get_mac(void) { return net_mac; }

/* Network poll (call from shell loop) */
void net_poll(void) {
    ne2000_poll();
}





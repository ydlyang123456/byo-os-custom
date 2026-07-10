/* BYO-OS TCP/IP Stack - x86_64 */
/* Ethernet II framing, ARP, IPv4, ICMPv4, UDP, TCP (passive open) */
#include <kernel.h>

/* ===== Ethernet Protocol Constants ===== */
#define ETHERTYPE_IPV4  0x0800
#define ETHERTYPE_ARP   0x0806

#define ARP_REQUEST     1
#define ARP_REPLY       2

#define IP_PROTO_ICMP   1
#define IP_PROTO_TCP    6
#define IP_PROTO_UDP    17

/* TCP flag bits */
#define TCP_FIN  0x01
#define TCP_SYN  0x02
#define TCP_RST  0x04
#define TCP_PSH  0x08
#define TCP_ACK  0x10

/* Broadcast MAC address */
static const uint8_t broadcast_mac[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

/* ===== Network Byte Order Helpers ===== */
static inline uint16_t htons(uint16_t v) { return ntohs(v); }
static inline uint32_t htonl(uint32_t v) { return ntohl(v); }
static inline uint32_t ip_to_u32(const uint8_t ip[4]) {
    return ((uint32_t)ip[0]) | ((uint32_t)ip[1] << 8) | ((uint32_t)ip[2] << 16) | ((uint32_t)ip[3] << 24);
}
static inline void u32_to_ip(uint32_t v, uint8_t ip[4]) {
    ip[0] = v & 0xFF; ip[1] = (v >> 8) & 0xFF;
    ip[2] = (v >> 16) & 0xFF; ip[3] = (v >> 24) & 0xFF;
}
static inline void copy_mac(uint8_t dst[6], const uint8_t src[6]) {
    dst[0]=src[0]; dst[1]=src[1]; dst[2]=src[2];
    dst[3]=src[3]; dst[4]=src[4]; dst[5]=src[5];
}
static inline void copy_ip(uint8_t dst[4], const uint8_t src[4]) {
    dst[0]=src[0]; dst[1]=src[1]; dst[2]=src[2]; dst[3]=src[3];
}
static inline int mac_eq(const uint8_t a[6], const uint8_t b[6]) {
    return a[0]==b[0]&&a[1]==b[1]&&a[2]==b[2]&&a[3]==b[3]&&a[4]==b[4]&&a[5]==b[5];
}

/* ===== Packet Structures (packed for wire format) ===== */
typedef struct __attribute__((packed)) {
    uint8_t  dst_mac[6];
    uint8_t  src_mac[6];
    uint16_t ethertype;
} eth_hdr_t;

typedef struct __attribute__((packed)) {
    uint16_t hw_type;       /* 1 = Ethernet */
    uint16_t proto_type;    /* 0x0800 = IPv4 */
    uint8_t  hw_size;       /* 6 */
    uint8_t  proto_size;    /* 4 */
    uint16_t opcode;        /* 1=req, 2=reply */
    uint8_t  sender_mac[6];
    uint8_t  sender_ip[4];
    uint8_t  target_mac[6];
    uint8_t  target_ip[4];
} arp_pkt_t;

typedef struct __attribute__((packed)) {
    uint8_t  ver_ihl;       /* high nibble = version(4), low nibble = ihl */
    uint8_t  dscp_ecn;      /* differentiated services */
    uint16_t total_len;     /* network byte order */
    uint16_t id;
    uint16_t frag_off;      /* flags(3) | fragment offset(13) */
    uint8_t  ttl;
    uint8_t  protocol;
    uint16_t checksum;
    uint8_t  src_ip[4];
    uint8_t  dst_ip[4];
} ip_hdr_t;

typedef struct __attribute__((packed)) {
    uint8_t  type;
    uint8_t  code;
    uint16_t checksum;
    uint16_t id;
    uint16_t seq;
} icmp_hdr_t;

typedef struct __attribute__((packed)) {
    uint16_t src_port;
    uint16_t dst_port;
    uint16_t length;
    uint16_t checksum;
} udp_hdr_t;

typedef struct __attribute__((packed)) {
    uint16_t src_port;
    uint16_t dst_port;
    uint32_t seq_num;
    uint32_t ack_num;
    uint16_t data_off_flags; /* data_offset(4), reserved(3), flags(9) */
    uint16_t window;
    uint16_t checksum;
    uint16_t urgent_ptr;
} tcp_hdr_t;

/* TCP pseudo header (used only for checksum computation) */
typedef struct __attribute__((packed)) {
    uint8_t  src_ip[4];
    uint8_t  dst_ip[4];
    uint8_t  zero;
    uint8_t  protocol;
    uint16_t tcp_len;
} tcp_pseudo_t;

/* ===== ARP Cache ===== */
#define ARP_CACHE_SZ 16
typedef struct {
    uint32_t ip;
    uint8_t  mac[6];
    int      valid;
} arp_entry_t;
static arp_entry_t arp_cache[ARP_CACHE_SZ];

/* ===== TCP Listeners (passive open) ===== */
#define MAX_LISTENERS 8
typedef struct {
    uint16_t port;
    int      active;
} tcp_listener_t;
static tcp_listener_t listeners[MAX_LISTENERS];

/* ===== Statistics ===== */
static uint32_t stat_pkts_in  = 0;
static uint32_t stat_pkts_out = 0;
static uint32_t stat_bytes    = 0;
static uint16_t ip_id_counter = 0;

#define PKT_BUF_SIZE 2048
static uint8_t pkt_buf[PKT_BUF_SIZE];

/* ===== Checksum Functions ===== */
static uint16_t ones_complement_sum(const uint8_t* data, uint32_t len) {
    uint32_t sum = 0;
    uint32_t i;
    for (i = 0; i + 1 < len; i += 2)
        sum += ((uint16_t)data[i] << 8) | data[i + 1];
    if (i < len)
        sum += (uint16_t)data[i] << 8;
    while (sum >> 16)
        sum = (sum & 0xFFFF) + (sum >> 16);
    return (uint16_t)sum;
}

static uint16_t ip_checksum(const uint8_t* data, uint32_t len) {
    uint16_t sum = ones_complement_sum(data, len);
    return (uint16_t)(~sum);
}

/* ===== ARP Cache Management ===== */
static void arp_cache_add(uint32_t ip, const uint8_t mac[6]) {
    int i;
    for (i = 0; i < ARP_CACHE_SZ; i++) {
        if (arp_cache[i].valid && arp_cache[i].ip == ip) {
            copy_mac(arp_cache[i].mac, mac);
            return;
        }
    }
    for (i = 0; i < ARP_CACHE_SZ; i++) {
        if (!arp_cache[i].valid) {
            arp_cache[i].valid = 1;
            arp_cache[i].ip = ip;
            copy_mac(arp_cache[i].mac, mac);
            return;
        }
    }
    /* Replace oldest (index 0) */
    arp_cache[0].ip = ip;
    copy_mac(arp_cache[0].mac, mac);
    arp_cache[0].valid = 1;
}

static int arp_cache_lookup(uint32_t ip, uint8_t mac[6]) {
    int i;
    for (i = 0; i < ARP_CACHE_SZ; i++) {
        if (arp_cache[i].valid && arp_cache[i].ip == ip) {
            copy_mac(mac, arp_cache[i].mac);
            return 0;
        }
    }
    return -1;
}

/* ===== Resolve destination MAC (ARP cache or broadcast) ===== */
static void resolve_dest_mac(uint32_t ip, uint8_t mac[6]) {
    if (arp_cache_lookup(ip, mac) != 0)
        copy_mac(mac, broadcast_mac);
}

/* ===== Send raw Ethernet frame ===== */
static int eth_send(const uint8_t dst_mac[6], uint16_t ethertype,
                    const uint8_t* payload, uint16_t payload_len) {
    uint16_t total = sizeof(eth_hdr_t) + payload_len;
    if (total > PKT_BUF_SIZE) return -1;

    eth_hdr_t* eth = (eth_hdr_t*)pkt_buf;
    copy_mac(eth->dst_mac, dst_mac);
    copy_mac(eth->src_mac, net_get_mac());
    eth->ethertype = htons(ethertype);

    uint32_t i;
    for (i = 0; i < payload_len; i++)
        pkt_buf[sizeof(eth_hdr_t) + i] = payload[i];

    ne2000_send_packet(pkt_buf, total);
    stat_pkts_out++;
    stat_bytes += total;
    return total;
}

/* ===== Build & send IPv4 packet ===== */
static int ip_send(const uint8_t dst_ip[4], uint8_t protocol,
                   const uint8_t* payload, uint16_t payload_len) {
    /* Build IP header in pkt_buf, then wrap in Ethernet frame */
    uint16_t total_len = sizeof(ip_hdr_t) + payload_len;
    if (total_len > PKT_BUF_SIZE - sizeof(eth_hdr_t)) return -1;

    uint8_t* ip_start = pkt_buf + sizeof(eth_hdr_t);
    ip_hdr_t* ip = (ip_hdr_t*)ip_start;
    memset(ip, 0, sizeof(ip_hdr_t));
    ip->ver_ihl   = 0x45;               /* IPv4, IHL=5 (20 bytes) */
    ip->total_len = htons(total_len);
    ip->id        = htons(ip_id_counter++);
    ip->frag_off  = htons(0x4000);       /* Don't fragment */
    ip->ttl       = 64;
    ip->protocol  = protocol;

    uint8_t my_ip[4];
    u32_to_ip(net_get_ip(), my_ip);
    copy_ip(ip->src_ip, my_ip);
    copy_ip(ip->dst_ip, dst_ip);

    /* Checksum computed over IP header only */
    ip->checksum = 0;
    ip->checksum = ip_checksum(ip_start, sizeof(ip_hdr_t));

    /* Copy payload after IP header */
    uint32_t i;
    for (i = 0; i < payload_len; i++)
        ip_start[sizeof(ip_hdr_t) + i] = payload[i];

    /* Resolve destination MAC */
    uint8_t dst_mac[6];
    resolve_dest_mac(ip_to_u32(dst_ip), dst_mac);

    eth_hdr_t* eth = (eth_hdr_t*)pkt_buf;
    copy_mac(eth->dst_mac, dst_mac);
    copy_mac(eth->src_mac, net_get_mac());
    eth->ethertype = htons(ETHERTYPE_IPV4);

    uint16_t frame_len = sizeof(eth_hdr_t) + total_len;
    ne2000_send_packet(pkt_buf, frame_len);
    stat_pkts_out++;
    stat_bytes += frame_len;
    return frame_len;
}

/* ===== Handle incoming ARP packet ===== */
static void handle_arp(const uint8_t* data, uint16_t len) {
    (void)len;
    if (len < sizeof(arp_pkt_t)) return;

    const arp_pkt_t* arp = (const arp_pkt_t*)data;

    uint16_t hw    = ntohs(arp->hw_type);
    uint16_t proto = ntohs(arp->proto_type);
    uint16_t op    = ntohs(arp->opcode);

    if (hw != 1 || proto != ETHERTYPE_IPV4) return;

    uint8_t my_ip[4];
    u32_to_ip(net_get_ip(), my_ip);

    if (op == ARP_REQUEST) {
        /* Check if target IP is ours */
        if (arp->target_ip[0] != my_ip[0] || arp->target_ip[1] != my_ip[1] ||
            arp->target_ip[2] != my_ip[2] || arp->target_ip[3] != my_ip[3])
            return;

        /* Learn sender */
        arp_cache_add(ip_to_u32(arp->sender_ip), arp->sender_mac);

        /* Build ARP reply */
        uint8_t frame[sizeof(eth_hdr_t) + sizeof(arp_pkt_t)];
        arp_pkt_t* rep = (arp_pkt_t*)(frame + sizeof(eth_hdr_t));
        rep->hw_type    = htons(1);
        rep->proto_type = htons(ETHERTYPE_IPV4);
        rep->hw_size    = 6;
        rep->proto_size = 4;
        rep->opcode     = htons(ARP_REPLY);
        copy_mac(rep->sender_mac, net_get_mac());
        copy_ip(rep->sender_ip, my_ip);
        copy_mac(rep->target_mac, arp->sender_mac);
        copy_ip(rep->target_ip, arp->sender_ip);

        eth_hdr_t* eth = (eth_hdr_t*)frame;
        copy_mac(eth->dst_mac, arp->sender_mac);
        copy_mac(eth->src_mac, net_get_mac());
        eth->ethertype = htons(ETHERTYPE_ARP);

        ne2000_send_packet(frame, sizeof(frame));
        stat_pkts_out++;
        stat_bytes += sizeof(frame);

        serial_puts("[TCPIP] ARP reply sent\n");
    }
    else if (op == ARP_REPLY) {
        arp_cache_add(ip_to_u32(arp->sender_ip), arp->sender_mac);
    }
}

/* ===== Handle incoming ICMP echo request ===== */
static void handle_icmp(const uint8_t* data, uint16_t len,
                        const uint8_t src_ip[4], const uint8_t dst_ip[4]) {
    (void)dst_ip;
    if (len < sizeof(icmp_hdr_t)) return;

    const icmp_hdr_t* req = (const icmp_hdr_t*)data;

    /* Echo request (type=8) -> send Echo reply (type=0) */
    if (req->type == 8) {
        uint16_t data_len = len - sizeof(icmp_hdr_t);
        uint16_t icmp_total = sizeof(icmp_hdr_t) + data_len;
        uint8_t reply_buf[512];

        if (icmp_total > sizeof(reply_buf)) return;

        icmp_hdr_t* rep = (icmp_hdr_t*)reply_buf;
        rep->type = 0;
        rep->code = 0;
        rep->id   = req->id;
        rep->seq  = req->seq;

        /* Copy original data payload */
        uint32_t i;
        for (i = 0; i < data_len; i++)
            reply_buf[sizeof(icmp_hdr_t) + i] = data[sizeof(icmp_hdr_t) + i];

        /* Compute ICMP checksum */
        rep->checksum = 0;
        rep->checksum = ip_checksum(reply_buf, icmp_total);

        ip_send(src_ip, IP_PROTO_ICMP, reply_buf, icmp_total);
        serial_puts("[TCPIP] ICMP echo reply sent\n");
    }
}

/* ===== Handle incoming TCP packet ===== */
static void handle_tcp(const uint8_t* data, uint16_t len,
                       const uint8_t src_ip[4], const uint8_t dst_ip[4]) {
    (void)dst_ip;
    if (len < sizeof(tcp_hdr_t)) return;

    const tcp_hdr_t* tcp = (const tcp_hdr_t*)data;
    uint16_t dst_port = ntohs(tcp->dst_port);
    uint16_t src_port = ntohs(tcp->src_port);
    uint16_t flags = ntohs(tcp->data_off_flags) & 0x1FF;
    uint32_t seq = ntohl(tcp->seq_num);

    /* Check if anyone is listening on dst_port */
    int i;
    int listening = 0;
    for (i = 0; i < MAX_LISTENERS; i++) {
        if (listeners[i].active && listeners[i].port == dst_port) {
            listening = 1;
            break;
        }
    }

    /* Also accept port 80 by default if no explicit listener but http is active */

    if (!listening) return;

    if (flags & TCP_SYN) {
        serial_puts("[TCPIP] SYN received on port ");
        char buf[8];
        uint16_t port = dst_port;
        itoa(port, buf, 10);
        serial_puts(buf);
        serial_puts("\n");

        /* Send SYN-ACK */
        uint8_t tcp_reply[20];
        memset(tcp_reply, 0, sizeof(tcp_reply));
        tcp_hdr_t* reply = (tcp_hdr_t*)tcp_reply;
        reply->src_port = htons(dst_port);
        reply->dst_port = htons(src_port);
        reply->seq_num  = htonl(2000);
        reply->ack_num  = htonl(seq + 1);
        reply->data_off_flags = htons((5 << 12) | TCP_SYN | TCP_ACK);
        reply->window   = htons(65535);
        reply->checksum = 0;

        /* TCP checksum with pseudo header */
        uint8_t my_ip[4];
        u32_to_ip(net_get_ip(), my_ip);

        tcp_pseudo_t ps;
        copy_ip(ps.src_ip, my_ip);
        copy_ip(ps.dst_ip, src_ip);
        ps.zero = 0;
        ps.protocol = IP_PROTO_TCP;
        ps.tcp_len = htons(sizeof(tcp_hdr_t));

        uint8_t cksum_buf[sizeof(tcp_pseudo_t) + sizeof(tcp_hdr_t)];
        memcpy(cksum_buf, &ps, sizeof(tcp_pseudo_t));
        memcpy(cksum_buf + sizeof(tcp_pseudo_t), tcp_reply, sizeof(tcp_hdr_t));

        uint16_t cksum = ip_checksum(cksum_buf, sizeof(cksum_buf));
        /* For ones-complement, we need ones_complement_sum but ip_checksum does ~sum */
        /* Actually we need to compute sum of pseudo + tcp, then ~sum */
        uint16_t raw_sum = ones_complement_sum(cksum_buf, sizeof(cksum_buf));
        reply->checksum = (uint16_t)(~raw_sum);

        ip_send(src_ip, IP_PROTO_TCP, tcp_reply, sizeof(tcp_hdr_t));
        serial_puts("[TCPIP] SYN-ACK sent\n");
    }
}

/* ===== Handle incoming UDP packet ===== */
static void handle_udp(const uint8_t* data, uint16_t len,
                       const uint8_t src_ip[4], const uint8_t dst_ip[4]) {
    (void)src_ip; (void)dst_ip;
    if (len < sizeof(udp_hdr_t)) return;
    const udp_hdr_t* udp = (const udp_hdr_t*)data;
    uint16_t dst_port = ntohs(udp->dst_port);
    uint16_t src_port = ntohs(udp->src_port);
    (void)src_port;
    serial_puts("[TCPIP] UDP packet port ");
    char buf[8];
    itoa(dst_port, buf, 10);
    serial_puts(buf);
    serial_puts("\n");
}

/* ===== Handle incoming IPv4 packet ===== */
static void handle_ipv4(const uint8_t* data, uint16_t len) {
    if (len < sizeof(ip_hdr_t)) return;

    const ip_hdr_t* ip = (const ip_hdr_t*)data;

    /* Verify checksum */
    uint16_t cksum = ip->checksum;
    ((ip_hdr_t*)data)->checksum = 0;
    uint16_t calc = ip_checksum(data, sizeof(ip_hdr_t));
    ((ip_hdr_t*)data)->checksum = cksum;

    if (cksum != calc) return;

    uint16_t total_len = ntohs(ip->total_len);
    uint8_t protocol = ip->protocol;
    uint16_t hdr_len = (ip->ver_ihl & 0x0F) * 4;

    if (hdr_len < 20 || total_len < hdr_len || total_len > len) return;

    const uint8_t* payload = data + hdr_len;
    uint16_t payload_len = total_len - hdr_len;

    switch (protocol) {
    case IP_PROTO_ICMP:
        handle_icmp(payload, payload_len, ip->src_ip, ip->dst_ip);
        break;
    case IP_PROTO_TCP:
        handle_tcp(payload, payload_len, ip->src_ip, ip->dst_ip);
        break;
    case IP_PROTO_UDP:
        handle_udp(payload, payload_len, ip->src_ip, ip->dst_ip);
        break;
    default:
        break;
    }
}

/* ===== Handle incoming Ethernet frame ===== */
static void handle_ethernet(const uint8_t* data, uint16_t len) {
    if (len < sizeof(eth_hdr_t)) return;

    const eth_hdr_t* eth = (const eth_hdr_t*)data;
    uint16_t ethertype = ntohs(eth->ethertype);
    const uint8_t* payload = data + sizeof(eth_hdr_t);
    uint16_t payload_len = len - sizeof(eth_hdr_t);

    switch (ethertype) {
    case ETHERTYPE_ARP:
        handle_arp(payload, payload_len);
        break;
    case ETHERTYPE_IPV4:
        handle_ipv4(payload, payload_len);
        break;
    default:
        break;
    }
}

/* ====================================================================
 * Public API
 * ==================================================================== */

/* tcpip_init - Initialize the TCP/IP protocol stack */
void tcpip_init(void) {
    int i;
    for (i = 0; i < ARP_CACHE_SZ; i++)
        arp_cache[i].valid = 0;
    for (i = 0; i < MAX_LISTENERS; i++)
        listeners[i].active = 0;
    stat_pkts_in  = 0;
    stat_pkts_out = 0;
    stat_bytes    = 0;
    ip_id_counter = 1;

    /* Add default listener on port 80 */
    listeners[0].port   = 80;
    listeners[0].active = 1;

    serial_puts("[TCPIP] Stack initialized\n");
    serial_puts("[TCPIP] Listening on port 80 (HTTP)\n");
}

/* tcpip_handle_packet - Process a received packet from the NIC */
int tcpip_handle_packet(uint8_t* data, uint16_t len) {
    if (!data || len < 14) return -1;

    stat_pkts_in++;

    /* Dispatch to Ethernet handler */
    handle_ethernet(data, len);
    return 0;
}

/* tcpip_send_arp_request - Send an ARP request for target_ip */
int tcpip_send_arp_request(uint32_t target_ip) {
    uint8_t target_ip_bytes[4];
    u32_to_ip(target_ip, target_ip_bytes);

    uint8_t my_ip_bytes[4];
    u32_to_ip(net_get_ip(), my_ip_bytes);

    /* Build ARP request in pkt_buf */
    arp_pkt_t arp;
    memset(&arp, 0, sizeof(arp));
    arp.hw_type    = htons(1);
    arp.proto_type = htons(ETHERTYPE_IPV4);
    arp.hw_size    = 6;
    arp.proto_size = 4;
    arp.opcode     = htons(ARP_REQUEST);
    copy_mac(arp.sender_mac, net_get_mac());
    copy_ip(arp.sender_ip, my_ip_bytes);
    memset(arp.target_mac, 0, 6);
    copy_ip(arp.target_ip, target_ip_bytes);

    /* Wrap in Ethernet frame with broadcast destination */
    uint8_t frame[sizeof(eth_hdr_t) + sizeof(arp_pkt_t)];
    eth_hdr_t* eth = (eth_hdr_t*)frame;
    copy_mac(eth->dst_mac, broadcast_mac);
    copy_mac(eth->src_mac, net_get_mac());
    eth->ethertype = htons(ETHERTYPE_ARP);
    memcpy(frame + sizeof(eth_hdr_t), &arp, sizeof(arp_pkt_t));

    ne2000_send_packet(frame, sizeof(frame));
    stat_pkts_out++;
    stat_bytes += sizeof(frame);

    serial_puts("[TCPIP] ARP request sent\n");
    return sizeof(frame);
}

/* tcpip_send_icmp_echo - Send an ICMP echo request (ping) */
int tcpip_send_icmp_echo(uint32_t target_ip) {
    uint8_t dst_ip[4];
    u32_to_ip(target_ip, dst_ip);

    uint8_t icmp_pkt[64];
    memset(icmp_pkt, 0, sizeof(icmp_pkt));
    icmp_hdr_t* icmp = (icmp_hdr_t*)icmp_pkt;
    icmp->type = 8;       /* Echo request */
    icmp->code = 0;
    icmp->id   = htons(1);
    icmp->seq  = htons(1);

    /* Fill payload with 48 bytes of data */
    uint32_t i;
    for (i = sizeof(icmp_hdr_t); i < 64; i++)
        icmp_pkt[i] = (uint8_t)(i - sizeof(icmp_hdr_t));

    icmp->checksum = ip_checksum(icmp_pkt, 64);

    int ret = ip_send(dst_ip, IP_PROTO_ICMP, icmp_pkt, 64);
    if (ret > 0) {
        serial_puts("[TCPIP] ICMP echo request sent\n");
        return 0;
    }
    return -1;
}

/* tcpip_send_udp - Send a UDP packet */
int tcpip_send_udp(uint32_t dest_ip, uint16_t dest_port,
                   uint16_t src_port, uint8_t* data, uint16_t len) {
    uint8_t dst_ip[4];
    u32_to_ip(dest_ip, dst_ip);

    uint16_t udp_len = sizeof(udp_hdr_t) + len;
    uint8_t udp_buf[PKT_BUF_SIZE];
    if (udp_len > sizeof(udp_buf)) return -1;

    memset(udp_buf, 0, udp_len);
    udp_hdr_t* udp = (udp_hdr_t*)udp_buf;
    udp->src_port = htons(src_port);
    udp->dst_port = htons(dest_port);
    udp->length   = htons(udp_len);
    udp->checksum = 0;    /* UDP checksum optional; 0 = no checksum */

    uint32_t i;
    for (i = 0; i < len; i++)
        udp_buf[sizeof(udp_hdr_t) + i] = data[i];

    int ret = ip_send(dst_ip, IP_PROTO_UDP, udp_buf, udp_len);
    if (ret > 0) {
        serial_puts("[TCPIP] UDP packet sent\n");
        return 0;
    }
    return -1;
}

/* tcpip_send_tcp_syn - Send a TCP SYN to initiate connection */
int tcpip_send_tcp_syn(uint32_t dest_ip, uint16_t dest_port, uint16_t src_port) {
    uint8_t dst_ip[4];
    u32_to_ip(dest_ip, dst_ip);

    uint8_t tcp_buf[20];
    memset(tcp_buf, 0, sizeof(tcp_buf));
    tcp_hdr_t* tcp = (tcp_hdr_t*)tcp_buf;
    tcp->src_port = htons(src_port);
    tcp->dst_port = htons(dest_port);
    tcp->seq_num  = htonl(1000);
    tcp->ack_num  = 0;
    tcp->data_off_flags = htons((5 << 12) | TCP_SYN);
    tcp->window   = htons(65535);

    /* TCP checksum with pseudo header */
    uint8_t my_ip[4];
    u32_to_ip(net_get_ip(), my_ip);

    tcp_pseudo_t ps;
    copy_ip(ps.src_ip, my_ip);
    copy_ip(ps.dst_ip, dst_ip);
    ps.zero     = 0;
    ps.protocol = IP_PROTO_TCP;
    ps.tcp_len  = htons(20);

    uint8_t cksum_buf[sizeof(tcp_pseudo_t) + 20];
    memcpy(cksum_buf, &ps, sizeof(tcp_pseudo_t));
    memcpy(cksum_buf + sizeof(tcp_pseudo_t), tcp_buf, 20);

    uint16_t raw_sum = ones_complement_sum(cksum_buf, sizeof(cksum_buf));
    tcp->checksum = (uint16_t)(~raw_sum);

    int ret = ip_send(dst_ip, IP_PROTO_TCP, tcp_buf, 20);
    if (ret > 0) {
        serial_puts("[TCPIP] TCP SYN sent\n");
        return 0;
    }
    return -1;
}

/* tcpip_get_stats - Retrieve protocol stack statistics */
void tcpip_get_stats(uint32_t* pkts_in, uint32_t* pkts_out, uint32_t* bytes) {
    if (pkts_in)  *pkts_in  = stat_pkts_in;
    if (pkts_out) *pkts_out = stat_pkts_out;
    if (bytes)    *bytes    = stat_bytes;
}

/* tcpip_open_listen - Open a TCP port for passive listening */
int tcpip_open_listen(uint16_t port) {
    int i;
    for (i = 0; i < MAX_LISTENERS; i++) {
        if (listeners[i].active && listeners[i].port == port) {
            serial_puts("[TCPIP] Already listening on port ");
            char buf[8];
            itoa(port, buf, 10);
            serial_puts(buf);
            serial_puts("\n");
            return 0;
        }
    }
    for (i = 0; i < MAX_LISTENERS; i++) {
        if (!listeners[i].active) {
            listeners[i].port   = port;
            listeners[i].active = 1;
            serial_puts("[TCPIP] Listening on port ");
            char buf[8];
            itoa(port, buf, 10);
            serial_puts(buf);
            serial_puts("\n");
            return 0;
        }
    }
    return -1;  /* No free listener slots */
}

/* tcpip_send_response - Send a TCP data response (HTTP-style) */
int tcpip_send_response(uint8_t* data, uint16_t len) {
    /* This builds a minimal TCP data packet (PSH+ACK)
       with the local host as source, unknown remote.
       For a real server, connection tracking is needed.
       Here we use a simple approach: broadcast destination,
       port 80 source, arbitrary ack. */

    uint8_t tcp_buf[PKT_BUF_SIZE];
    uint16_t total_tcp = sizeof(tcp_hdr_t) + len;
    if (total_tcp > sizeof(tcp_buf)) return -1;

    memset(tcp_buf, 0, total_tcp);
    tcp_hdr_t* tcp = (tcp_hdr_t*)tcp_buf;
    tcp->src_port = htons(80);
    tcp->dst_port = htons(0);    /* Unknown – placeholder */
    tcp->seq_num  = htonl(2001);
    tcp->ack_num  = htonl(1);
    tcp->data_off_flags = htons((5 << 12) | TCP_PSH | TCP_ACK);
    tcp->window   = htons(65535);

    uint32_t i;
    for (i = 0; i < len; i++)
        tcp_buf[sizeof(tcp_hdr_t) + i] = data[i];

    /* Placeholder remote IP – broadcast; real stacks track connection */
    uint8_t dst_ip[4] = {0xFF, 0xFF, 0xFF, 0xFF};

    /* TCP checksum with pseudo header */
    uint8_t my_ip[4];
    u32_to_ip(net_get_ip(), my_ip);

    tcp_pseudo_t ps;
    copy_ip(ps.src_ip, my_ip);
    copy_ip(ps.dst_ip, dst_ip);
    ps.zero     = 0;
    ps.protocol = IP_PROTO_TCP;
    ps.tcp_len  = htons(total_tcp);

    uint8_t cksum_buf[512];
    if (sizeof(tcp_pseudo_t) + total_tcp > sizeof(cksum_buf)) return -1;
    memcpy(cksum_buf, &ps, sizeof(tcp_pseudo_t));
    memcpy(cksum_buf + sizeof(tcp_pseudo_t), tcp_buf, total_tcp);

    uint16_t raw_sum = ones_complement_sum(cksum_buf, sizeof(tcp_pseudo_t) + total_tcp);
    tcp->checksum = (uint16_t)(~raw_sum);

    int ret = ip_send(dst_ip, IP_PROTO_TCP, tcp_buf, total_tcp);
    if (ret > 0) {
        serial_puts("[TCPIP] TCP response sent\n");
        return 0;
    }
    return -1;
}

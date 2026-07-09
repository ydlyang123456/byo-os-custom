/* BYO-OS - NE2000 PCI NIC Driver for QEMU */
#include <kernel.h>

static uint16_t ne_base = 0xC000;
static uint8_t ne_irq = 10;
static uint8_t ne_mac[6] = {0x52,0x54,0x00,0x12,0x34,0x56};
static int ne_ok = 0;

#define CR      0x00
#define PSTART  0x01
#define PSTOP   0x02
#define BNRY    0x03
#define TPSR    0x04
#define TBCR0   0x05
#define TBCR1   0x06
#define ISR     0x07
#define RSAR0   0x08
#define RSAR1   0x09
#define RBCR0   0x0A
#define RBCR1   0x0B
#define RCR     0x0C
#define TCR     0x0D
#define DCR     0x0E
#define IMR     0x0F
#define DP      0x10
#define PAR0    0x01
#define CURR    0x07
#define RX_START 0x00
#define RX_END   0x40
#define TX_START 0x40

static inline void wr(uint16_t port, uint8_t val) { outb(ne_base + port, val); }
static inline uint8_t rd(uint16_t port) { return inb(ne_base + port); }
static void select_page(uint8_t p) { wr(CR, (rd(CR) & 0x3F) | (p << 6)); }

int ne2000_read_packet(uint8_t* buf, int mx) {
    if (!ne_ok) return -1;
    select_page(1); uint8_t curr = rd(CURR); select_page(0);
    uint8_t bnry = rd(BNRY);
    if (bnry == curr || bnry >= RX_END) return 0;
    wr(CR, (rd(CR) & 0x3F) | 0x08);
    wr(RSAR0, 0); wr(RSAR1, bnry);
    wr(RBCR0, 4); wr(RBCR1, 0);
    uint8_t h[4]; for (int i = 0; i < 4; i++) h[i] = rd(DP);
    { int t = 5000; while (t-- > 0 && !(rd(ISR) & 0x40)); }
    wr(ISR, 0x40);
    uint8_t next = h[1]; uint16_t len = h[2] | ((uint16_t)h[3] << 8);
    if (len < 4 || len > 1518) { wr(BNRY, (next == 0) ? (RX_END - 1) : next - 1); return 0; }
    int cp = len - 4; if (cp > mx) cp = mx;
    wr(CR, (rd(CR) & 0x3F) | 0x08);
    wr(RSAR0, 4 & 0xFF); wr(RSAR1, bnry);
    wr(RBCR0, cp & 0xFF); wr(RBCR1, (cp >> 8) & 0xFF);
    for (int i = 0; i < cp; i++) buf[i] = rd(DP);
    { int t = 5000; while (t-- > 0 && !(rd(ISR) & 0x40)); }
    wr(ISR, 0x40);
    wr(BNRY, (next == 0) ? (RX_END - 1) : next - 1);
    return cp;
}

int ne2000_send_packet(const uint8_t* data, int len) {
    if (!ne_ok) return -1;
    wr(ISR, 0xFF);
    wr(RBCR0, len & 0xFF); wr(RBCR1, (len >> 8) & 0xFF);
    wr(RSAR0, 0); wr(RSAR1, TX_START);
    wr(CR, (rd(CR) & 0x3F) | 0x10);
    for (int i = 0; i < len; i++) wr(DP, data[i]);
    { int t = 10000; while (t-- > 0 && !(rd(ISR) & 0x40)); }
    wr(ISR, 0x40);
    wr(TPSR, TX_START);
    wr(TBCR0, len & 0xFF); wr(TBCR1, (len >> 8) & 0xFF);
    wr(CR, rd(CR) | 0x04);
    return len;
}

int ne2000_init(void) {
    serial_puts("[NE2000] PCI scan\n");
    int found = 0;
    for (int d = 0; d < 32; d++) {
        uint32_t a = 0x80000000 | (d << 11);
        outl(0xCF8, a); uint32_t id = inl(0xCFC);
        uint16_t v = id & 0xFFFF;
        if (v == 0xFFFF || v == 0) continue;
        uint16_t di = (id >> 16) & 0xFFFF;
        char h[8]; serial_puts("[PCI] d="); itoa(d,h,10); serial_puts(h);
        serial_puts(" v="); itoa(v,h,16); serial_puts(h);
        serial_puts(" di="); itoa(di,h,16); serial_puts(h); serial_puts("\n");
        if (v == 0x10EC && di == 0x8029) {
            outl(0xCF8, a | 0x10); uint32_t bar = inl(0xCFC);
            ne_base = bar & ~3; if (ne_base == 0) ne_base = 0xC000;
            outl(0xCF8, a | 0x3C); ne_irq = inl(0xCFC) & 0xFF;
            serial_puts("[NE2000] IO=0x"); itoa(ne_base,h,16); serial_puts(h);
            serial_puts(" IRQ="); itoa(ne_irq,h,10); serial_puts(h); serial_puts("\n");
            found = 1; break;
        }
    }
    if (!found) { serial_puts("[NE2000] NOT FOUND\n"); return -1; }
    inb(ne_base + 0x1F); wr(ISR, 0x80); wr(CR, 0x21);
    { volatile int t = 50000; while (t--); }
    select_page(0);
    wr(DCR, 0x58); wr(RCR, 0x05); wr(TCR, 0x00);
    wr(PSTART, RX_START); wr(PSTOP, RX_END); wr(BNRY, RX_END - 1);
    select_page(1);
    for (int i = 0; i < 6; i++) wr(PAR0 + i, ne_mac[i]);
    wr(CURR, RX_START + 1); select_page(0);
    wr(ISR, 0xFF); wr(IMR, 0x01); wr(CR, 0x22);
    ne_ok = 1;
    serial_puts("[NE2000] OK\n"); return 0;
}

void ne2000_poll(void) {
    if (!ne_ok) return;
    uint8_t isr = rd(ISR);
    if (isr & 0x01) wr(ISR, 0x01);
    { uint8_t pkt[1518]; int len;
      while ((len = ne2000_read_packet(pkt, sizeof(pkt))) > 0) {
        extern void net_handle_packet(uint8_t* data, int len);
        net_handle_packet(pkt, len);
      }
    }
}
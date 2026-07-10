/* BYO-OS - AHCI/SATA Disk Driver (x86_64) */
#include <kernel.h>
#include <stdint.h>

/* ===== AHCI Port Registers (offset from 0x100 + port*0x80) ===== */
#define AHCI_PORT_CLB    0x00
#define AHCI_PORT_CLBU   0x04
#define AHCI_PORT_FB     0x08
#define AHCI_PORT_FBU    0x0C
#define AHCI_PORT_IS     0x10
#define AHCI_PORT_IE     0x14
#define AHCI_PORT_CMD    0x18
#define AHCI_PORT_TFD    0x20
#define AHCI_PORT_SIG    0x24
#define AHCI_PORT_SSTS   0x28
#define AHCI_PORT_SCTL   0x2C
#define AHCI_PORT_SERR   0x30
#define AHCI_PORT_SACT   0x34
#define AHCI_PORT_CI     0x38
#define AHCI_PORT_SNTF   0x3C
#define AHCI_PORT_FBS    0x40

/* ===== HBA Registers ===== */
#define AHCI_CAP     0x00
#define AHCI_GHC     0x04
#define AHCI_IS      0x08
#define AHCI_PI      0x0C
#define AHCI_VS      0x10
#define AHCI_CCC_CTL 0x14
#define AHCI_CCC_PTS 0x18
#define AHCI_EM_LOC  0x1C
#define AHCI_EM_CTL  0x20
#define AHCI_CAP2    0x24
#define AHCI_BOHC    0x28

/* ===== GHC bits ===== */
#define AHCI_GHC_AE     0x80000000
#define AHCI_GHC_IE     0x00000002
#define AHCI_GHC_HR     0x00000001

/* ===== CAP bits ===== */
#define AHCI_CAP_NP     (0x1F << 0)

/* ===== CMD bits ===== */
#define AHCI_CMD_ST     0x0001
#define AHCI_CMD_FRE    0x0010
#define AHCI_CMD_CPD    0x0020
#define AHCI_CMD_POD    0x0100
#define AHCI_CMD_SUD    0x0200
#define AHCI_CMD_ICC    0x0800
#define AHCI_CMD_ATAPI  0x0400
#define AHCI_CMD_CR     0x8000

/* ===== SSTS bits ===== */
#define AHCI_SSTS_DET           (0x0F << 0)
#define AHCI_SSTS_DET_NODEVICE     0x00
#define AHCI_SSTS_DET_PRESENT      0x01
#define AHCI_SSTS_DET_ESTABLISHED  0x03
#define AHCI_SSTS_IPM             (0x0F << 8)
#define AHCI_SSTS_IPM_ACTIVE      (0x01 << 8)

/* ===== TFD bits ===== */
#define AHCI_TFD_BSY    0x80
#define AHCI_TFD_DRQ    0x08
#define AHCI_TFD_ERR    0x01

/* ===== ATA Commands ===== */
#define ATA_CMD_READ_DMA_EXT    0x25
#define ATA_CMD_WRITE_DMA_EXT   0x35
#define ATA_CMD_IDENTIFY        0xEC

/* ===== FIS Types ===== */
#define FIS_TYPE_REG_H2D    0x27
#define FIS_TYPE_REG_D2H    0x34
#define FIS_TYPE_DMA_ACT    0x39
#define FIS_TYPE_DMA_SETUP  0x41
#define FIS_TYPE_DATA       0x46
#define FIS_TYPE_BIST       0x58
#define FIS_TYPE_PIO_SETUP  0x5F
#define FIS_TYPE_DEV_BITS   0xA1

/* ===== AHCI Data Structures ===== */
typedef struct {
    uint16_t cfl  : 5;
    uint16_t a    : 1;
    uint16_t w    : 1;
    uint16_t p    : 1;
    uint16_t r    : 1;
    uint16_t b    : 1;
    uint16_t c    : 1;
    uint16_t rsvd : 1;
    uint16_t pmp  : 4;
    uint16_t prdtl;
    uint32_t prdbc;
    uint32_t ctba;
    uint32_t ctbau;
    uint32_t reserved[4];
} __attribute__((packed)) ahci_cmd_header_t;

typedef struct {
    uint32_t dba;
    uint32_t dbau;
    uint32_t reserved;
    uint32_t byte_count;
} __attribute__((packed)) ahci_prdt_entry_t;

typedef struct {
    uint8_t cfis[64];
    uint8_t acmd[16];
    uint8_t reserved[48];
    ahci_prdt_entry_t prdt[8];
} __attribute__((packed)) ahci_cmd_table_t;

typedef struct {
    uint8_t fis_type;
    uint8_t pmport : 4;
    uint8_t rsv0   : 3;
    uint8_t c      : 1;
    uint8_t command;
    uint8_t feature_low;
    uint8_t lba0;
    uint8_t lba1;
    uint8_t lba2;
    uint8_t device;
    uint8_t lba3;
    uint8_t lba4;
    uint8_t lba5;
    uint8_t feature_high;
    uint8_t count_low;
    uint8_t count_high;
    uint8_t icc;
    uint8_t control;
    uint8_t rsv1[4];
} __attribute__((packed)) fis_reg_h2d_t;

typedef struct {
    uint8_t fis_type;
    uint8_t pmport : 4;
    uint8_t rsv0   : 2;
    uint8_t i      : 1;
    uint8_t rsv1   : 1;
    uint8_t status;
    uint8_t error;
} __attribute__((packed)) fis_reg_d2h_t;

/* ===== Port state tracking ===== */
#define AHCI_MAX_PORTS   32
#define AHCI_MAX_DEVICES 32

typedef struct {
    int present;
    int port_num;
    uint64_t clb_phys;
    uint64_t fb_phys;
    uint64_t ct_phys;
    uint32_t sectors;
    char model[41];
} ahci_device_t;

/* ===== Global state ===== */
static volatile uint32_t* ahci_abar = 0;
static int ahci_present = 0;
static int ahci_port_count = 0;
static ahci_device_t ahci_devices[AHCI_MAX_DEVICES];
static int ahci_device_count = 0;

/* ===== Register access macros ===== */
#define PORT_REG(port, reg) (*(volatile uint32_t*)((uint32_t*)((uint64_t)ahci_abar + 0x100 + (port) * 0x80 + (reg))))
#define HBA_REG(reg)        (*(volatile uint32_t*)((uint32_t*)((uint64_t)ahci_abar + (reg))))

/* ===== Busy-wait helpers ===== */
static void ahci_mdelay(uint32_t ms) {
    volatile uint32_t x = ms * 100000;
    while (x--) { asm volatile("pause"); }
}

static int ahci_wait_clear(volatile uint32_t* reg, uint32_t mask, int timeout_ms) {
    volatile int t = timeout_ms * 1000;
    while (t--) {
        if (!((*reg) & mask)) return 0;
        asm volatile("pause");
    }
    return -1;
}

static int ahci_wait_set(volatile uint32_t* reg, uint32_t mask, int timeout_ms) {
    volatile int t = timeout_ms * 1000;
    while (t--) {
        if ((*reg) & mask) return 0;
        asm volatile("pause");
    }
    return -1;
}

/* ===== Probe & init a single port ===== */
static int ahci_probe_port(int port) {
    uint32_t ssts = PORT_REG(port, AHCI_PORT_SSTS);
    int det = ssts & AHCI_SSTS_DET;
    int ipm = ssts & AHCI_SSTS_IPM;

    if (det != AHCI_SSTS_DET_ESTABLISHED) return -1;
    if (ipm != AHCI_SSTS_IPM_ACTIVE) return -1;

    volatile uint32_t* cmd_reg = (volatile uint32_t*)((uint64_t)ahci_abar + 0x100 + port * 0x80 + AHCI_PORT_CMD);

    /* Stop command engine */
    *cmd_reg &= ~AHCI_CMD_ST;
    ahci_wait_clear(cmd_reg, AHCI_CMD_CR, 100);
    *cmd_reg &= ~AHCI_CMD_FRE;

    /* Allocate 4K-aligned pages */
    uint64_t clb = pmm_alloc_page_64();
    if (!clb) return -1;
    memset((void*)(uint64_t)clb, 0, 4096);

    uint64_t fb = pmm_alloc_page_64();
    if (!fb) { pmm_free_page_64(clb); return -1; }
    memset((void*)(uint64_t)fb, 0, 4096);

    uint64_t ct = pmm_alloc_page_64();
    if (!ct) { pmm_free_page_64(clb); pmm_free_page_64(fb); return -1; }
    memset((void*)(uint64_t)ct, 0, 4096);

    /* Set port base addresses */
    PORT_REG(port, AHCI_PORT_CLB)  = (uint32_t)(clb & 0xFFFFFFFF);
    PORT_REG(port, AHCI_PORT_CLBU) = (uint32_t)((clb >> 32) & 0xFFFFFFFF);
    PORT_REG(port, AHCI_PORT_FB)   = (uint32_t)(fb & 0xFFFFFFFF);
    PORT_REG(port, AHCI_PORT_FBU)  = (uint32_t)((fb >> 32) & 0xFFFFFFFF);

    /* Clear SERR */
    PORT_REG(port, AHCI_PORT_SERR) = PORT_REG(port, AHCI_PORT_SERR);

    /* Enable FIS receive and start */
    *cmd_reg |= AHCI_CMD_FRE;
    *cmd_reg |= AHCI_CMD_ST;
    ahci_wait_set(cmd_reg, AHCI_CMD_CR, 100);

    /* Set up command header entry 0 */
    ahci_cmd_header_t* cmd_header = (ahci_cmd_header_t*)(uint64_t)clb;
    memset((void*)cmd_header, 0, sizeof(ahci_cmd_header_t));
    cmd_header->cfl = sizeof(fis_reg_h2d_t) / sizeof(uint32_t);
    cmd_header->prdtl = 1;
    cmd_header->ctba  = (uint32_t)(ct & 0xFFFFFFFF);
    cmd_header->ctbau = (uint32_t)((ct >> 32) & 0xFFFFFFFF);

    /* Store device info */
    if (ahci_device_count < AHCI_MAX_DEVICES) {
        ahci_device_t* dev = &ahci_devices[ahci_device_count];
        dev->present  = 1;
        dev->port_num = port;
        dev->clb_phys = clb;
        dev->fb_phys  = fb;
        dev->ct_phys  = ct;
        ahci_device_count++;
    }

    return 0;
}

/* ===== Wait for command slot completion ===== */
static int ahci_wait_cmd(int port, int slot) {
    volatile int timeout = 3000000;
    while (timeout--) {
        uint32_t ci = PORT_REG(port, AHCI_PORT_CI);
        if (!(ci & (1 << slot))) return 0;
        uint32_t tfd = PORT_REG(port, AHCI_PORT_TFD);
        if (tfd & (AHCI_TFD_ERR | AHCI_TFD_BSY)) return -1;
        asm volatile("pause");
    }
    return -1;
}

/* ===== Send command via slot 0 ===== */
static int ahci_send_cmd(int port, int slot, uint8_t command,
                         uint8_t feature, uint64_t lba, uint16_t count,
                         uint64_t data_phys, int write) {
    if (port < 0 || port >= AHCI_MAX_PORTS) return -1;

    /* Find device */
    ahci_device_t* dev = 0;
    for (int i = 0; i < ahci_device_count; i++) {
        if (ahci_devices[i].port_num == port) {
            dev = &ahci_devices[i];
            break;
        }
    }
    if (!dev) return -1;

    uint64_t clb = dev->clb_phys;
    uint64_t ct  = dev->ct_phys;

    ahci_cmd_header_t* header  = (ahci_cmd_header_t*)(uint64_t)clb;
    ahci_cmd_table_t*  cmd_tbl = (ahci_cmd_table_t*)(uint64_t)ct;

    memset((void*)cmd_tbl, 0, sizeof(ahci_cmd_table_t));
    memset((void*)header,  0, sizeof(ahci_cmd_header_t));

    /* Build Register H2D FIS */
    fis_reg_h2d_t* fis = (fis_reg_h2d_t*)cmd_tbl->cfis;
    fis->fis_type = FIS_TYPE_REG_H2D;
    fis->c        = 1;
    fis->command  = command;
    fis->device   = 0x40;
    fis->count_low  = count & 0xFF;
    fis->count_high = (count >> 8) & 0xFF;
    fis->lba0 = (uint8_t)(lba & 0xFF);
    fis->lba1 = (uint8_t)((lba >> 8) & 0xFF);
    fis->lba2 = (uint8_t)((lba >> 16) & 0xFF);
    fis->lba3 = (uint8_t)((lba >> 24) & 0xFF);
    fis->lba4 = (uint8_t)((lba >> 32) & 0xFF);
    fis->lba5 = (uint8_t)((lba >> 48) & 0xFF);

    /* Set up header */
    header->cfl   = sizeof(fis_reg_h2d_t) / sizeof(uint32_t);
    header->w     = write ? 1 : 0;
    header->prdtl = 1;
    header->prdbc = 0;
    header->ctba  = (uint32_t)(ct & 0xFFFFFFFF);
    header->ctbau = (uint32_t)((ct >> 32) & 0xFFFFFFFF);

    /* Set up PRDT */
    if (data_phys) {
        cmd_tbl->prdt[0].dba        = (uint32_t)(data_phys & 0xFFFFFFFF);
        cmd_tbl->prdt[0].dbau       = (uint32_t)((data_phys >> 32) & 0xFFFFFFFF);
        cmd_tbl->prdt[0].byte_count = ((uint32_t)count * 512 - 1) | 0x80000000;
    }

    /* Clear port interrupt status */
    PORT_REG(port, AHCI_PORT_IS) = 0xFFFFFFFF;

    /* Issue command */
    PORT_REG(port, AHCI_PORT_CI) = (1 << slot);

    return ahci_wait_cmd(port, slot);
}

/* ===== IDENTIFY a device on given port ===== */
static int ahci_identify_port(int port) {
    uint64_t ident_buf = pmm_alloc_page_64();
    if (!ident_buf) return -1;
    memset((void*)(uint64_t)ident_buf, 0, 4096);

    int ret = ahci_send_cmd(port, 0, ATA_CMD_IDENTIFY, 0, 0, 0, ident_buf, 0);
    if (ret < 0) {
        pmm_free_page_64(ident_buf);
        return -1;
    }

    uint16_t* buf = (uint16_t*)(uint64_t)ident_buf;

    ahci_device_t* dev = 0;
    for (int i = 0; i < ahci_device_count; i++) {
        if (ahci_devices[i].port_num == port) {
            dev = &ahci_devices[i];
            break;
        }
    }
    if (!dev) { pmm_free_page_64(ident_buf); return -1; }

    /* Model string (words 27-46) */
    char* m = dev->model;
    for (int i = 0; i < 40; i += 2) {
        m[i]   = (buf[27 + i/2] >> 8) & 0xFF;
        m[i+1] = buf[27 + i/2] & 0xFF;
    }
    m[40] = 0;
    for (int i = 39; i >= 0; i--) {
        if (m[i] == ' ') m[i] = 0;
        else break;
    }

    /* Sectors (LBA28 words 60-61, LBA48 words 100-103) */
    dev->sectors = buf[60] | (buf[61] << 16);
    if (dev->sectors == 0) {
        uint64_t s48 = (uint64_t)buf[100] | ((uint64_t)buf[101] << 16) |
                       ((uint64_t)buf[102] << 32) | ((uint64_t)buf[103] << 48);
        dev->sectors = (uint32_t)s48;
    }

    pmm_free_page_64(ident_buf);

    char numbuf[4];
    itoa(port, numbuf, 10);
    serial_puts("[AHCI] Port "); serial_puts(numbuf);
    serial_puts(": "); serial_puts(dev->model); serial_puts("\n");
    vga_puts("[AHCI] Port "); vga_puts(numbuf);
    vga_puts(": "); vga_puts(dev->model); vga_puts("\n");

    return 0;
}

/* ===== Public API: ahci_init ===== */
int ahci_init(void) {
    if (ahci_present) return 0;

    /* Find AHCI controller via PCI: class=0x01 (mass storage), subclass=0x06 (SATA) */
    int pci_idx = pci_find_class(0x01, 0x06);
    if (pci_idx < 0) {
        serial_puts("[AHCI] No SATA controller found\n");
        vga_puts("[AHCI] No SATA controller\n");
        return -1;
    }

    const pci_device_t* pci_dev = pci_get_device(pci_idx);
    if (!pci_dev) return -1;

    /* Enable PCI bus mastering and IRQ */
    pci_enable_bus_master(pci_idx);
    pci_enable_irq(pci_idx);

    /* Get ABAR from BAR5 */
    uint32_t bar5 = pci_dev->bar5;
    if (bar5 & 1) {
        serial_puts("[AHCI] BAR5 is I/O space\n");
        vga_puts("[AHCI] BAR5 I/O mode\n");
        return -1;
    }

    uint64_t abar = (uint64_t)(bar5 & 0xFFFFFFF0);
    ahci_abar = (volatile uint32_t*)abar;

    char hexbuf[16];
    itoa((uint32_t)(abar & 0xFFFFFFFF), hexbuf, 16);
    serial_puts("[AHCI] ABAR: 0x"); serial_puts(hexbuf); serial_puts("\n");

    /* Reset HBA */
    HBA_REG(AHCI_GHC) |= AHCI_GHC_HR;
    ahci_wait_clear(&HBA_REG(AHCI_GHC), AHCI_GHC_HR, 1000);

    /* Enable AHCI */
    HBA_REG(AHCI_GHC) |= AHCI_GHC_AE;
    ahci_mdelay(10);

    /* Port count from CAP */
    uint32_t cap = HBA_REG(AHCI_CAP);
    ahci_port_count = (cap & 0x1F) + 1;

    uint32_t pi = HBA_REG(AHCI_PI);
    serial_puts("[AHCI] Ports implemented: 0x"); itoa(pi, hexbuf, 16);
    serial_puts(hexbuf); serial_puts("\n");

    /* Probe ports */
    int found = 0;
    for (int port = 0; port < ahci_port_count && port < AHCI_MAX_PORTS; port++) {
        if (pi & (1 << port)) {
            if (ahci_probe_port(port) == 0 && ahci_identify_port(port) == 0) {
                found++;
            }
        }
    }

    if (found > 0) {
        ahci_present = 1;
        itoa(found, hexbuf, 10);
        serial_puts("[AHCI] "); serial_puts(hexbuf); serial_puts(" device(s)\n");
        vga_puts("[AHCI] "); vga_puts(hexbuf); vga_puts(" device(s)\n");
    } else {
        serial_puts("[AHCI] No devices\n");
        vga_puts("[AHCI] No devices\n");
    }

    return 0;
}

/* ===== Public API: ahci_read ===== */
int ahci_read(int port, uint64_t lba, uint16_t count, void* buf) {
    if (!ahci_present || !buf) return -1;

    uint64_t dma_buf = pmm_alloc_page_64();
    if (!dma_buf) return -1;

    int ret = ahci_send_cmd(port, 0, ATA_CMD_READ_DMA_EXT, 0, lba, count, dma_buf, 0);
    if (ret == 0) {
        memcpy(buf, (void*)(uint64_t)dma_buf, (size_t)count * 512);
    }

    pmm_free_page_64(dma_buf);
    return ret;
}

/* ===== Public API: ahci_write ===== */
int ahci_write(int port, uint64_t lba, uint16_t count, const void* buf) {
    if (!ahci_present || !buf) return -1;

    uint64_t dma_buf = pmm_alloc_page_64();
    if (!dma_buf) return -1;

    memcpy((void*)(uint64_t)dma_buf, buf, (size_t)count * 512);

    int ret = ahci_send_cmd(port, 0, ATA_CMD_WRITE_DMA_EXT, 0, lba, count, dma_buf, 1);

    pmm_free_page_64(dma_buf);
    return ret;
}

/* ===== Public API: getters ===== */
int ahci_get_port_count(void) {
    return ahci_device_count;
}

int ahci_is_present(void) {
    return ahci_present;
}

int ahci_get_sectors(int port) {
    for (int i = 0; i < ahci_device_count; i++) {
        if (ahci_devices[i].port_num == port)
            return (int)ahci_devices[i].sectors;
    }
    return 0;
}
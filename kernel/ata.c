/* BYO-OS - ATA PIO Disk Driver (x86_64) */
#include <kernel.h>

/* ATA registers (primary bus) */
#define ATA_DATA        0x1F0
#define ATA_ERROR       0x1F1
#define ATA_SECTOR_CNT  0x1F2
#define ATA_LBA_LOW     0x1F3
#define ATA_LBA_MID     0x1F4
#define ATA_LBA_HIGH    0x1F5
#define ATA_DRIVE       0x1F6
#define ATA_CMD         0x1F7
#define ATA_STATUS      0x1F7
#define ATA_ALT_STATUS  0x3F6

/* ATA commands */
#define ATA_CMD_READ    0x20
#define ATA_CMD_WRITE   0x30
#define ATA_CMD_IDENTIFY 0xEC

/* ATA status bits */
#define ATA_SR_BSY     1
#define ATA_SR_DRDY    2
#define ATA_SR_DF      3
#define ATA_SR_DSC     4
#define ATA_SR_DRQ     5
#define ATA_SR_CORR    6
#define ATA_SR_ERR     7

/* Disk info */
static int ata_present = 0;
static uint32_t ata_sectors = 0;
static char ata_model[41] = {0};
static int disk_reads = 0;
static int disk_writes = 0;

static int ata_wait_bsy(void) {
    int timeout = 1000000;
    while (timeout--) {
        if (!(inb(ATA_STATUS) & ATA_SR_BSY)) return 0;
    }
    return -1;
}

static int ata_wait_drq(void) {
    int timeout = 1000000;
    while (timeout--) {
        uint8_t st = inb(ATA_STATUS);
        if (st & ATA_SR_ERR) return -1;
        if (st & ATA_SR_DRQ) return 0;
    }
    return -1;
}

int ata_identify(void) {
    if (ata_wait_bsy() < 0) return -1;

    outb(ATA_DRIVE, 0xA0); /* master */
    io_wait();
    outb(ATA_SECTOR_CNT, 0);
    io_wait();
    outb(ATA_LBA_LOW, 0);
    io_wait();
    outb(ATA_LBA_MID, 0);
    io_wait();
    outb(ATA_LBA_HIGH, 0);
    io_wait();
    outb(ATA_CMD, ATA_CMD_IDENTIFY);
    io_wait();

    if (inb(ATA_STATUS) == 0) return -1; /* no drive */

    if (ata_wait_bsy() < 0) return -1;

    /* Read identify data */
    uint16_t buf[256];
    for (int i = 0; i < 256; i++) {
        buf[i] = inw(ATA_DATA);
    }

    /* Extract model (words 27-46, each 2 bytes, big-endian ASCII) */
    for (int i = 0; i < 40; i += 2) {
        ata_model[i] = (buf[27 + i / 2] >> 8) & 0xFF;
        ata_model[i + 1] = buf[27 + i / 2] & 0xFF;
    }
    ata_model[40] = 0;

    /* Trim trailing spaces */
    for (int i = 39; i >= 0; i--) {
        if (ata_model[i] == ' ') ata_model[i] = 0;
        else break;
    }

    /* Get total sectors (words 60-61 = LBA28, words 100-103 = LBA48) */
    ata_sectors = buf[60] | (buf[61] << 16);
    if (ata_sectors == 0) {
        /* Try LBA48 */
        ata_sectors = (uint32_t)(buf[100] | (buf[101] << 16) | ((uint64_t)buf[102] << 32) | ((uint64_t)buf[103] << 48));
    }

    ata_present = 1;
    serial_puts("[ATA] Drive found: ");
    serial_puts(ata_model);
    serial_puts("\n");
    vga_puts("[ATA] Drive: "); vga_puts(ata_model); vga_puts("\n");

    char buf2[32];
    itoa(ata_sectors / 1024 / 2, buf2, 10);
    vga_puts("[ATA] Size: "); vga_puts(buf2); vga_puts(" MB\n");
    serial_puts("[ATA] Size: "); serial_puts(buf2); serial_puts(" MB\n");

    return 0;
}

int ata_read_sectors(uint32_t lba, uint8_t count, uint16_t* buffer) {
    (void)buffer;
    if (!ata_present) return -1;

    if (ata_wait_bsy() < 0) return -1;

    outb(ATA_DRIVE, 0xE0 | ((lba >> 24) & 0x0F));
    io_wait();
    outb(ATA_SECTOR_CNT, count);
    io_wait();
    outb(ATA_LBA_LOW, lba & 0xFF);
    io_wait();
    outb(ATA_LBA_MID, (lba >> 8) & 0xFF);
    io_wait();
    outb(ATA_LBA_HIGH, (lba >> 16) & 0xFF);
    io_wait();
    outb(ATA_CMD, ATA_CMD_READ);
    io_wait();

    if (ata_wait_bsy() < 0) return -1;
    if (ata_wait_drq() < 0) return -1;

    /* Read data - caller handles buffer */
    for (int i = 0; i < 256 * count; i++) {
        inw(ATA_DATA); /* discard, just read */
    }

    disk_reads++;
    return 0;
}

int ata_write_sectors(uint32_t lba, uint8_t count, const uint16_t* buffer) {
    (void)buffer;
    if (!ata_present) return -1;

    if (ata_wait_bsy() < 0) return -1;

    outb(ATA_DRIVE, 0xE0 | ((lba >> 24) & 0x0F));
    io_wait();
    outb(ATA_SECTOR_CNT, count);
    io_wait();
    outb(ATA_LBA_LOW, lba & 0xFF);
    io_wait();
    outb(ATA_LBA_MID, (lba >> 8) & 0xFF);
    io_wait();
    outb(ATA_LBA_HIGH, (lba >> 16) & 0xFF);
    io_wait();
    outb(ATA_CMD, ATA_CMD_WRITE);
    io_wait();

    if (ata_wait_bsy() < 0) return -1;
    if (ata_wait_drq() < 0) return -1;

    /* Write data */
    for (int i = 0; i < 256 * count; i++) {
        outw(ATA_DATA, 0); /* write zeroes */
    }

    /* Flush cache */
    outb(ATA_CMD, 0xE7); /* cache flush */
    io_wait();

    disk_writes++;
    return 0;
}

int ata_is_present(void) { return ata_present; }
uint32_t ata_get_sectors(void) { return ata_sectors; }
const char* ata_get_model(void) { return ata_model; }
int ata_get_reads(void) { return disk_reads; }
int ata_get_writes(void) { return disk_writes; }

void ata_init(void) {
    if (ata_identify() == 0) {
        serial_puts("[BOOT] ATA disk ready\n");
        vga_puts("[BOOT] ATA disk ready\n");
    } else {
        serial_puts("[BOOT] No ATA disk found\n");
        vga_puts("[BOOT] No ATA disk\n");
    }
}

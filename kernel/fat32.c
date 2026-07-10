/* BYO-OS - FAT32 Filesystem Driver (x86_64)
 * 
 * Supports reading/writing FAT32 partitions on ATA/IDE disks.
 * Mounts at /mnt when available.
 */
#include <kernel.h>
#include <stdint.h>

/* FAT32 BPB offsets */
#define FAT_BPB_JUMP         0
#define FAT_BPB_OEM          3
#define FAT_BPB_BYTES_SEC    11
#define FAT_BPB_SEC_CLUST    13
#define FAT_BPB_RSVD_SEC     14
#define FAT_BPB_NUM_FATS     16
#define FAT_BPB_ROOT_ENT     17
#define FAT_BPB_TOT_SEC16    19
#define FAT_BPB_MEDIA        21
#define FAT_BPB_FAT16        22
#define FAT_BPB_SEC_TRACK    24
#define FAT_BPB_NUM_HEADS    26
#define FAT_BPB_HIDDEN_SEC   28
#define FAT_BPB_TOT_SEC32    32
#define FAT32_BPB_FATSZ      36
#define FAT32_BPB_EXT_FLAGS  40
#define FAT32_BPB_ROOT_CLUST 44
#define FAT32_BPB_FSINFO     48
#define FAT32_BPB_BOOT_BACK  50

/* FAT32 directory entry attributes */
#define FAT_ATTR_READ_ONLY   0x01
#define FAT_ATTR_HIDDEN      0x02
#define FAT_ATTR_SYSTEM      0x04
#define FAT_ATTR_VOLUME_ID   0x08
#define FAT_ATTR_DIRECTORY   0x10
#define FAT_ATTR_ARCHIVE     0x20
#define FAT_ATTR_LONG_NAME   0x0F

/* FAT32 status */
static int fat_mounted = 0;
static uint32_t fat_first_data_sec;
static uint32_t fat_root_cluster;
static uint32_t fat_bytes_per_sec;
static uint32_t fat_sec_per_clust;
static uint32_t fat_total_clusters;
static uint32_t fat_reserved_sec;
static uint32_t fat_fat_size;
static uint32_t fat_num_fats;
static uint32_t fat_hidden_sec;
static int fat_reads = 0, fat_writes = 0;

/* Sector buffer */
static uint8_t sector_buf[512];

/* Read a sector from the disk */
static int read_sector(uint32_t lba) {
    return ata_read_sectors(lba, 1, (uint16_t*)sector_buf);
}

/* Write a sector back */
static int write_sector(uint32_t lba) {
    return ata_write_sectors(lba, 1, (uint16_t*)sector_buf);
}

/* Read cluster (one or more sectors) */
static void read_cluster(uint32_t cluster, uint8_t* buf) {
    uint32_t first_sec = fat_first_data_sec + (cluster - 2) * fat_sec_per_clust;
    for (uint32_t i = 0; i < fat_sec_per_clust; i++) {
        read_sector(first_sec + i);
        for (int j = 0; j < 512; j++) buf[i * 512 + j] = sector_buf[j];
    }
}

/* Get next cluster in FAT chain */
static uint32_t get_next_cluster(uint32_t cluster) {
    uint32_t fat_sec = fat_reserved_sec + (cluster * 4) / fat_bytes_per_sec;
    uint32_t fat_off = (cluster * 4) % fat_bytes_per_sec;
    read_sector(fat_sec);
    uint32_t val = *(uint32_t*)&sector_buf[fat_off] & 0x0FFFFFFF;
    if (val >= 0x0FFFFFF8) return 0; /* EOF */
    return val;
}

/* Extract short file name from a directory entry */
static void extract_short_name(const uint8_t* entry, char* name, int max_len) {
    int pos = 0;
    /* 8.3 format */
    for (int i = 0; i < 8 && entry[i] != ' ' && entry[i] != 0; i++)
        if (pos < max_len - 1) name[pos++] = entry[i];
    if (entry[8] != ' ' && entry[8] != 0) {
        if (pos < max_len - 1) name[pos++] = '.';
        for (int i = 0; i < 3 && entry[8+i] != ' ' && entry[8+i] != 0; i++)
            if (pos < max_len - 1) name[pos++] = entry[8+i];
    }
    name[pos] = 0;
}

/* Format a FAT32 date/time */
static void format_datetime(uint16_t date, uint16_t time, char* out) {
    int year = 1980 + ((date >> 9) & 0x7F);
    int mon = (date >> 5) & 0x0F;
    int day = date & 0x1F;
    int hour = (time >> 11) & 0x1F;
    int min = (time >> 5) & 0x3F;
    int sec = (time & 0x1F) * 2;
    char buf[16];
    itoa(year, buf, 10); 
    int pos = 0;
    while (buf[pos]) out[pos] = buf[pos++];
    out[pos++] = '-'; itoa(mon, buf, 10); int j = 0; while (buf[j]) out[pos++] = buf[j++];
    out[pos++] = '-'; itoa(day, buf, 10); j = 0; while (buf[j]) out[pos++] = buf[j++];
    out[pos++] = ' '; itoa(hour, buf, 10); j = 0; while (buf[j]) out[pos++] = buf[j++];
    out[pos++] = ':'; itoa(min, buf, 10); j = 0; while (buf[j]) out[pos++] = buf[j++];
    out[pos] = 0;
}

/* Mount FAT32 filesystem */
int fat_mount(void) {
    if (!ata_is_present()) return -1;

    /* Read boot sector (sector 0) */
    if (read_sector(0) < 0) return -1;

    /* Verify this is FAT32 */
    uint16_t bytes_per_sec = *(uint16_t*)&sector_buf[FAT_BPB_BYTES_SEC];
    if (bytes_per_sec != 512) return -2;

    uint32_t total_sec = *(uint16_t*)&sector_buf[FAT_BPB_TOT_SEC16];
    if (total_sec == 0) total_sec = *(uint32_t*)&sector_buf[FAT_BPB_TOT_SEC32];

    fat_reserved_sec = *(uint16_t*)&sector_buf[FAT_BPB_RSVD_SEC];
    fat_num_fats = sector_buf[FAT_BPB_NUM_FATS];
    fat_fat_size = *(uint32_t*)&sector_buf[FAT32_BPB_FATSZ];
    fat_root_cluster = *(uint32_t*)&sector_buf[FAT32_BPB_ROOT_CLUST];
    fat_bytes_per_sec = bytes_per_sec;
    fat_sec_per_clust = sector_buf[FAT_BPB_SEC_CLUST];
    fat_hidden_sec = *(uint32_t*)&sector_buf[FAT_BPB_HIDDEN_SEC];

    /* Calculate first data sector */
    fat_first_data_sec = fat_reserved_sec + (fat_num_fats * fat_fat_size);

    /* Total clusters */
    fat_total_clusters = (total_sec - fat_first_data_sec) / fat_sec_per_clust;

    if (fat_total_clusters < 65525) return -3; /* not FAT32 */

    fat_mounted = 1;
    serial_puts("[FAT32] Mounted successfully\n");
    return 0;
}

/* List root directory */
int fat_list(const char* path, char* output, uint32_t max_len) {
    if (!fat_mounted) return -1;
    uint32_t cluster = fat_root_cluster;
    uint8_t buf[512 * 32]; /* max 32 sectors per cluster */
    uint32_t buf_size = fat_sec_per_clust * 512;
    int pos = 0;

    while (cluster) {
        read_cluster(cluster, buf);
        for (uint32_t off = 0; off < buf_size; off += 32) {
            uint8_t* entry = &buf[off];
            uint8_t attr = entry[11];

            if (entry[0] == 0) break; /* end of directory */
            if (entry[0] == 0xE5) continue; /* deleted */
            if (attr == FAT_ATTR_LONG_NAME) continue; /* skip LFN */

            if (pos + 80 > (int)max_len) break;

            /* Volume label or directory marker */
            if (attr & FAT_ATTR_DIRECTORY) {
                output[pos++] = '[';
                extract_short_name(entry, &output[pos+1], max_len - pos - 1);
                while (output[pos+1]) pos++;
                output[pos++] = ']';
                output[pos++] = '\n';
            } else {
                extract_short_name(entry, &output[pos], max_len - pos);
                while (output[pos]) pos++;
                output[pos++] = '\n';
            }
        }
        cluster = get_next_cluster(cluster);
    }
    output[pos] = 0;
    fat_reads++;
    return pos;
}

/* Read a file from FAT32 */
int fat_read(const char* name, char* buf, uint32_t max_len) {
    if (!fat_mounted) return -1;

    uint32_t cluster = fat_root_cluster;
    uint8_t dbuf[4096];
    uint32_t buf_size = fat_sec_per_clust * 512;
    if (buf_size > 4096) buf_size = 4096;

    while (cluster) {
        read_cluster(cluster, dbuf);
        for (uint32_t off = 0; off < buf_size; off += 32) {
            uint8_t* entry = &dbuf[off];
            if (entry[0] == 0) return -2;
            if (entry[0] == 0xE5) continue;
            if (entry[11] == FAT_ATTR_LONG_NAME) continue;
            if (entry[11] & FAT_ATTR_DIRECTORY) continue;

            char fname[13];
            extract_short_name(entry, fname, 13);
            if (strcmp(fname, name) == 0) {
                /* Found the file */
                uint32_t file_cluster = (entry[0x1B] << 24) | (entry[0x1A] << 16) | 
                                        (entry[0x15] << 8) | entry[0x14];
                uint32_t file_size = *(uint32_t*)&entry[0x1C];
                uint32_t file_buf[512];
                uint32_t pos = 0;
                uint32_t c = file_cluster;

                while (c && pos < file_size && pos < max_len) {
                    read_cluster(c, (uint8_t*)file_buf);
                    uint32_t to_copy = fat_sec_per_clust * 512;
                    if (pos + to_copy > file_size) to_copy = file_size - pos;
                    if (pos + to_copy > max_len) to_copy = max_len - pos;
                    for (uint32_t i = 0; i < to_copy; i++) buf[pos + i] = ((uint8_t*)file_buf)[i];
                    pos += to_copy;
                    if (pos >= file_size || pos >= max_len) break;
                    c = get_next_cluster(c);
                }
                fat_reads++;
                return pos;
            }
        }
        cluster = get_next_cluster(cluster);
    }
    return -3;
}

int fat_is_mounted(void) { return fat_mounted; }
int fat_get_reads(void) { return fat_reads; }
int fat_get_writes(void) { return fat_writes; }
uint32_t fat_get_total_clusters(void) { return fat_total_clusters; }
uint32_t fat_get_bytes_per_cluster(void) { return fat_sec_per_clust * 512; }

void fat_init(void) {
    if (ata_is_present()) {
        int rc = fat_mount();
        if (rc == 0) {
            serial_puts("[BOOT] FAT32: Disk mounted\n");
            vga_puts("[BOOT] FAT32 disk mounted\n");
        } else {
            serial_puts("[BOOT] FAT32: No FAT32 partition found\n");
        }
    }
}

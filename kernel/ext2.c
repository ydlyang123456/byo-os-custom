/* BYO-OS - ext2 文件系统驱动 (x86_64)
 * 只读支持 ext2 分区，兼容 Debian 12 文件系统
 */
#include <kernel.h>
#include <stdint.h>

/* ===== ext2 Constants ===== */
#define EXT2_SIGNATURE      0xEF53
#define EXT2_ROOT_INO       2
#define EXT2_S_BLOCK_GROUP  0
#define EXT2_S_FIRST_DATA_BLOCK  0   /* block size > 1024 = 0, else = 1 */
#define EXT2_FT_UNKNOWN     0
#define EXT2_FT_REG_FILE    1
#define EXT2_FT_DIR         2

/* ===== ext2 Superblock ===== */
typedef struct {
    uint32_t inodes_count;
    uint32_t blocks_count;
    uint32_t r_blocks_count;
    uint32_t free_blocks_count;
    uint32_t free_inodes_count;
    uint32_t first_data_block;
    uint32_t log_block_size;
    uint32_t log_frag_size;
    uint32_t blocks_per_group;
    uint32_t frags_per_group;
    uint32_t inodes_per_group;
    uint32_t mtime;
    uint32_t wtime;
    uint16_t mnt_count;
    uint16_t max_mnt_count;
    uint16_t magic;
    uint16_t state;
    uint16_t errors;
    uint16_t minor_rev_level;
    uint32_t lastcheck;
    uint32_t checkinterval;
    uint32_t creator_os;
    uint32_t rev_level;
    uint16_t def_resuid;
    uint16_t def_resgid;
    uint32_t first_ino;
    uint16_t inode_size;
    uint16_t block_group_nr;
    uint32_t feature_compat;
    uint32_t feature_incompat;
    uint32_t feature_ro_compat;
    uint8_t  uuid[16];
    char     volume_name[16];
    char     last_mounted[64];
    uint32_t algo_bitmap;
} __attribute__((packed)) ext2_sb_t;

/* ===== Block Group Descriptor ===== */
typedef struct {
    uint32_t block_bitmap;
    uint32_t inode_bitmap;
    uint32_t inode_table;
    uint16_t free_blocks_count;
    uint16_t free_inodes_count;
    uint16_t used_dirs_count;
    uint16_t pad;
} __attribute__((packed)) ext2_bgd_t;

/* ===== Inode ===== */
typedef struct {
    uint16_t mode;
    uint16_t uid;
    uint32_t size;
    uint32_t atime;
    uint32_t ctime;
    uint32_t mtime;
    uint32_t dtime;
    uint16_t gid;
    uint16_t links_count;
    uint32_t blocks_32;
    uint32_t flags;
    uint32_t osd1;
    uint32_t block[15];
    uint32_t generation;
    uint32_t file_acl;
    uint32_t dir_acl;
    uint32_t faddr;
    uint32_t osd2[3];
} __attribute__((packed)) ext2_inode_t;

/* ===== Directory Entry ===== */
typedef struct {
    uint32_t inode;
    uint16_t rec_len;
    uint8_t  name_len;
    uint8_t  file_type;
    char     name[255];
} __attribute__((packed)) ext2_dirent_t;

/* ===== State ===== */
static int ext2_mounted = 0;
static ext2_sb_t sb;
static uint32_t block_size = 1024;
static uint32_t sectors_per_block = 2;
static uint64_t part_lba = 0;

/* ===== Helpers ===== */
static void read_block(uint32_t block_num, uint8_t* buf) {
    uint64_t lba = part_lba + ((uint64_t)block_num * block_size / 512);
    uint16_t count = sectors_per_block;
    uint16_t tmp[256];
    for (uint16_t i = 0; i < count; i++) {
        ata_read_sectors((uint32_t)(lba + i), 1, tmp);
        for (int j = 0; j < 256; j++) {
            ((uint16_t*)buf)[i * 256 + j] = tmp[j];
        }
    }
}

static uint32_t bgd_block(void) {
    if (block_size > 1024) return 1;
    return block_size / 1024;
}

static uint32_t inode_to_block(uint32_t inode_num) {
    uint32_t inodes_per_group = sb.inodes_per_group;
    uint32_t group = (inode_num - 1) / inodes_per_group;
    uint32_t index = (inode_num - 1) % inodes_per_group;
    
    /* Read block group descriptor */
    uint32_t bgd_blk = bgd_block();
    uint8_t bgd_buf[1024];
    read_block(bgd_blk + group / (block_size / 32), bgd_buf);
    ext2_bgd_t* bgd = (ext2_bgd_t*)(bgd_buf + (group % (block_size / 32)) * 32);
    
    uint32_t inode_table = bgd->inode_table;
    uint32_t inode_size = sb.rev_level >= 1 ? sb.inode_size : 128;
    uint32_t block_offset = (index * inode_size) / block_size;
    return inode_table + block_offset;
}

static void read_inode(uint32_t inode_num, ext2_inode_t* inode) {
    uint32_t blk = inode_to_block(inode_num);
    uint32_t inodes_per_group = sb.inodes_per_group;
    uint32_t index = (inode_num - 1) % inodes_per_group;
    uint32_t inode_size = sb.rev_level >= 1 ? sb.inode_size : 128;
    uint32_t offset_in_block = (index * inode_size) % block_size;
    
    uint8_t buf[4096];
    read_block(blk, buf);
    memcpy(inode, buf + offset_in_block, sizeof(ext2_inode_t));
}

static void read_inode_data(ext2_inode_t* inode, uint32_t logical_block, uint8_t* buf) {
    (void)buf;
    if (logical_block < 12) {
        read_block(inode->block[logical_block], buf);
    } else if (logical_block < 12 + block_size / 4) {
        uint8_t ibuf[4096];
        read_block(inode->block[12], ibuf);
        read_block(((uint32_t*)ibuf)[logical_block - 12], buf);
    } else {
        /* Double indirect - simplified */
        uint8_t ibuf[4096];
        uint32_t ptrs_per_block = block_size / 4;
        read_block(inode->block[13], ibuf);
        uint32_t idx = (logical_block - 12 - ptrs_per_block) / ptrs_per_block;
        read_block(((uint32_t*)ibuf)[idx], ibuf);
        idx = (logical_block - 12 - ptrs_per_block) % ptrs_per_block;
        read_block(((uint32_t*)ibuf)[idx], buf);
    }
}

/* ===== API ===== */

int ext2_mount(uint64_t start_lba) {
    part_lba = start_lba;
    
    /* Read superblock at sector 1024/512 = 2 */
    uint16_t tmp[256];
    ata_read_sectors((uint32_t)(start_lba + 2), 2, tmp);
    memcpy(&sb, tmp, 1024);
    
    if (sb.magic != EXT2_SIGNATURE) {
        serial_puts("[EXT2] No ext2 signature (0x");
        serial_put_hex(sb.magic);
        serial_puts(")\n");
        return -1;
    }
    
    block_size = 1024 << sb.log_block_size;
    sectors_per_block = block_size / 512;
    
    char buf[32];
    itoa(block_size, buf, 10);
    serial_puts("[EXT2] Mounted! Block size: ");
    serial_puts(buf);
    serial_puts(" bytes, ");
    itoa(sb.blocks_count, buf, 10);
    serial_puts(buf);
    serial_puts(" blocks\n");
    
    vga_puts("[EXT2] ext2 filesystem mounted\n");
    ext2_mounted = 1;
    return 0;
}

int ext2_read_file(const char* path, char* buf, uint32_t max_len) {
    if (!ext2_mounted) return -1;
    (void)buf; (void)max_len;
    
    /* Start from root */
    uint32_t current_ino = EXT2_ROOT_INO;
    ext2_inode_t inode;
    
    /* Skip leading / */
    const char* p = path;
    while (*p == '/') p++;
    
    if (*p == 0) {
        /* Reading root directory - return error */
        return -1;
    }
    
    /* Parse path components */
    char component[256];
    while (*p) {
        int ci = 0;
        while (*p && *p != '/') component[ci++] = *p++;
        component[ci] = 0;
        if (*p == '/') p++;
        
        if (ci == 0) continue;
        
        /* Read current inode */
        read_inode(current_ino, &inode);
        
        /* Check if it's a directory */
        if (!(inode.mode & 0x4000)) {
            serial_puts("[EXT2] Not a directory\n");
            return -1;
        }
        
        /* Read directory entries */
        uint32_t num_blocks = (inode.size + block_size - 1) / block_size;
        uint8_t dir_buf[4096];
        int found = 0;
        
        for (uint32_t b = 0; b < num_blocks && b < 15; b++) {
            read_inode_data(&inode, b, dir_buf);
            uint32_t offset = 0;
            
            while (offset < block_size) {
                ext2_dirent_t* de = (ext2_dirent_t*)(dir_buf + offset);
                if (de->inode == 0) break;
                if (de->rec_len == 0) break;
                
                if (de->name_len == ci && memcmp(de->name, component, ci) == 0) {
                    current_ino = de->inode;
                    found = 1;
                    break;
                }
                offset += de->rec_len;
            }
            if (found) break;
        }
        
        if (!found) return -1;
    }
    
    /* Read final inode data */
    read_inode(current_ino, &inode);
    
    if ((inode.mode & 0x8000) == 0) return -1;  /* Not a regular file */
    
    uint32_t size = inode.size;
    if (size > max_len) size = max_len;
    
    uint32_t pos = 0;
    uint32_t num_blocks = (inode.size + block_size - 1) / block_size;
    
    for (uint32_t b = 0; b < num_blocks && pos < size; b++) {
        uint8_t tmp_buf[4096];
        read_inode_data(&inode, b, tmp_buf);
        uint32_t copy = block_size;
        if (pos + copy > size) copy = size - pos;
        memcpy(buf + pos, tmp_buf, copy);
        pos += copy;
    }
    
    buf[pos] = 0;
    return pos;
}

int ext2_read_dir(const char* path, char* output, uint32_t max_len) {
    if (!ext2_mounted) return -1;
    (void)output; (void)max_len;
    
    uint32_t current_ino = EXT2_ROOT_INO;
    ext2_inode_t inode;
    
    const char* p = path;
    while (*p == '/') p++;
    
    if (*p) {
        char component[256];
        while (*p) {
            int ci = 0;
            while (*p && *p != '/') component[ci++] = *p++;
            component[ci] = 0;
            if (*p == '/') p++;
            if (ci == 0) continue;
            
            read_inode(current_ino, &inode);
            if (!(inode.mode & 0x4000)) return -1;
            
            uint8_t dir_buf[4096];
            int found = 0;
            for (uint32_t b = 0; b < 15; b++) {
                read_inode_data(&inode, b, dir_buf);
                uint32_t offset = 0;
                while (offset < block_size) {
                    ext2_dirent_t* de = (ext2_dirent_t*)(dir_buf + offset);
                    if (de->inode == 0) break;
                    if (de->rec_len == 0) break;
                    if (de->name_len == ci && memcmp(de->name, component, ci) == 0) {
                        current_ino = de->inode;
                        found = 1;
                        break;
                    }
                    offset += de->rec_len;
                }
                if (found) break;
            }
            if (!found) return -1;
        }
    }
    
    read_inode(current_ino, &inode);
    if (!(inode.mode & 0x4000)) return -1;
    
    uint32_t pos = 0;
    uint8_t dir_buf[4096];
    
    for (uint32_t b = 0; b < 15 && pos < max_len - 32; b++) {
        read_inode_data(&inode, b, dir_buf);
        uint32_t offset = 0;
        while (offset < block_size) {
            ext2_dirent_t* de = (ext2_dirent_t*)(dir_buf + offset);
            if (de->inode == 0) break;
            if (de->rec_len == 0) break;
            
            char type_char = de->file_type == EXT2_FT_DIR ? 'd' : '-';
            char buf32[32];
            output[pos++] = type_char;
            int name_len = de->name_len < 255 ? de->name_len : 255;
            memcpy(output + pos, de->name, name_len);
            pos += name_len;
            output[pos++] = '\n';
            
            offset += de->rec_len;
        }
    }
    
    output[pos] = 0;
    return pos;
}

int ext2_is_mounted(void) { return ext2_mounted; }

void ext2_init(void) {
    serial_puts("[EXT2] ext2 filesystem driver ready\n");
    vga_puts("[EXT2] ext2 filesystem driver ready\n");
}

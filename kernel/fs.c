/* BYO-OS - Simple Ramdisk File System */
#include <kernel.h>

#define FS_BLOCK_SIZE 512
#define FS_MAX_FILES 64
#define FS_MAX_NAME 32
#define FS_MAX_PATH 128
#define FS_DATA_START (FS_BLOCK_SIZE * 2)
#define FS_TOTAL_BLOCKS 8192

typedef enum { FS_FILE, FS_DIR } fs_type_t;

typedef struct {
    char name[FS_MAX_NAME];
    fs_type_t type;
    uint32_t size;
    uint32_t data_block;
    uint32_t parent_block;
    int used;
} fs_entry_t;

typedef struct {
    uint32_t total_blocks;
    uint32_t free_blocks;
    uint32_t root_block;
    uint32_t bitmap_blocks;
} fs_superblock_t;

static uint8_t fs_bitmap[FS_TOTAL_BLOCKS / 8];
static fs_entry_t fs_entries[FS_MAX_FILES];
static uint8_t fs_data_area[FS_BLOCK_SIZE * 16];
static int fs_initialized = 0;
static int fs_entry_count = 0;

static void bitmap_set(uint32_t block) {
    fs_bitmap[block / 8] |= (1 << (block % 8));
}

static void bitmap_clear(uint32_t block) {
    fs_bitmap[block / 8] &= ~(1 << (block % 8));
}

static int bitmap_test(uint32_t block) {
    return fs_bitmap[block / 8] & (1 << (block % 8));
}

static uint32_t alloc_block(void) {
    for (uint32_t i = 2; i < FS_TOTAL_BLOCKS; i++) {
        if (!bitmap_test(i)) {
            bitmap_set(i);
            return i;
        }
    }
    return 0;
}

void fs_init(void) {
    memset(fs_bitmap, 0, sizeof(fs_bitmap));
    memset(fs_entries, 0, sizeof(fs_entries));
    fs_entry_count = 0;

    bitmap_set(0);
    bitmap_set(1);

    fs_entry_t root;
    strcpy(root.name, "/");
    root.type = FS_DIR;
    root.size = 0;
    root.data_block = 0;
    root.parent_block = 0;
    root.used = 1;
    fs_entries[0] = root;
    fs_entry_count = 1;

    fs_initialized = 1;
    serial_puts("[FS] Ramdisk filesystem initialized\n");
}

int fs_create_file(const char* name, const char* content, uint32_t size) {
    if (fs_entry_count >= FS_MAX_FILES) return -1;
    if (size > FS_BLOCK_SIZE * 16) return -2;

    uint32_t block = alloc_block();
    if (!block) return -3;

    fs_entry_t* entry = &fs_entries[fs_entry_count];
    strncpy(entry->name, name, FS_MAX_NAME - 1);
    entry->name[FS_MAX_NAME - 1] = '\0';
    entry->type = FS_FILE;
    entry->size = size;
    entry->data_block = block;
    entry->parent_block = 0;
    entry->used = 1;
    fs_entry_count++;

    if (content && size > 0) {
        memcpy(fs_data_area + block * FS_BLOCK_SIZE, content, size);
    }

    return 0;
}

int fs_create_dir(const char* name) {
    if (fs_entry_count >= FS_MAX_FILES) return -1;

    fs_entry_t* entry = &fs_entries[fs_entry_count];
    strncpy(entry->name, name, FS_MAX_NAME - 1);
    entry->name[FS_MAX_NAME - 1] = '\0';
    entry->type = FS_DIR;
    entry->size = 0;
    entry->data_block = 0;
    entry->parent_block = 0;
    entry->used = 1;
    fs_entry_count++;

    return 0;
}

int fs_list_dir(const char* path, char* output, uint32_t max_len) {
    (void)path;
    if (!fs_initialized) return -1;

    output[0] = '\0';
    uint32_t pos = 0;

    for (int i = 0; i < fs_entry_count; i++) {
        if (!fs_entries[i].used) continue;
        const char* prefix = (fs_entries[i].type == FS_DIR) ? "[DIR]  " : "[FILE] ";
        uint32_t plen = strlen(prefix);
        uint32_t nlen = strlen(fs_entries[i].name);

        if (pos + plen + nlen + 2 < max_len) {
            memcpy(output + pos, prefix, plen);
            pos += plen;
            memcpy(output + pos, fs_entries[i].name, nlen);
            pos += nlen;
            output[pos++] = '\n';
        }
    }
    output[pos] = '\0';
    return 0;
}

int fs_read_file(const char* name, char* buf, uint32_t max_len) {
    if (!fs_initialized) return -1;

    for (int i = 0; i < fs_entry_count; i++) {
        if (fs_entries[i].used && fs_entries[i].type == FS_FILE &&
            strcmp(fs_entries[i].name, name) == 0) {
            uint32_t copy_len = fs_entries[i].size;
            if (copy_len > max_len) copy_len = max_len;
            memset(buf, 0, max_len);
            if (copy_len > 0)
                memcpy(buf, fs_data_area + fs_entries[i].data_block * FS_BLOCK_SIZE, copy_len);
            return copy_len;
        }
    }
    return -1;
}

int fs_write_file(const char* name, const char* content, uint32_t size) {
    if (!fs_initialized) return -1;

    for (int i = 0; i < fs_entry_count; i++) {
        if (fs_entries[i].used && fs_entries[i].type == FS_FILE &&
            strcmp(fs_entries[i].name, name) == 0) {
            if (size > FS_BLOCK_SIZE * 16) return -2;
            fs_entries[i].size = size;
            memcpy(fs_data_area, content, size);
            return 0;
        }
    }

    return fs_create_file(name, content, size);
}

int fs_delete_file(const char* name) {
    if (!fs_initialized) return -1;

    for (int i = 0; i < fs_entry_count; i++) {
        if (fs_entries[i].used && strcmp(fs_entries[i].name, name) == 0) {
            if (fs_entries[i].data_block) {
                bitmap_clear(fs_entries[i].data_block);
            }
            fs_entries[i].used = 0;
            return 0;
        }
    }
    return -1;
}

int fs_file_size(const char* name) {
    for (int i = 0; i < fs_entry_count; i++) {
        if (fs_entries[i].used && fs_entries[i].type == FS_FILE &&
            strcmp(fs_entries[i].name, name) == 0) {
            return fs_entries[i].size;
        }
    }
    return -1;
}

int fs_file_exists(const char* name) {
    for (int i = 0; i < fs_entry_count; i++) {
        if (fs_entries[i].used && strcmp(fs_entries[i].name, name) == 0) {
            return 1;
        }
    }
    return 0;
}

void fs_get_stats(uint32_t* total_bytes, uint32_t* used_bytes, uint32_t* free_bytes) {
    uint32_t total = (uint32_t)FS_TOTAL_BLOCKS * FS_BLOCK_SIZE;
    uint32_t used = 0;
    for (int i = 0; i < fs_entry_count; i++) {
        if (fs_entries[i].used && fs_entries[i].type == FS_FILE) {
            used += fs_entries[i].size;
        }
    }
    *total_bytes = total;
    *used_bytes = used;
    *free_bytes = total - used;
}
/* BYO-OS FS - x86_64 RAMDISK */
#include <kernel.h>
#define MAX_FILES 256
#define MAX_NAME 64
#define MAX_SIZE 4096
typedef struct { char name[MAX_NAME]; uint8_t data[MAX_SIZE]; uint32_t size; int is_dir; int used; } fs_entry_t;
static fs_entry_t files[MAX_FILES];
static int file_count = 0;
void fs_init(void) { file_count = 0; memset(files, 0, sizeof(files)); }
int fs_create_file(const char* name, const char* content, uint32_t size) {
    if (file_count >= MAX_FILES) return -1;
    int i = 0; while (name[i] && i < MAX_NAME - 1) { files[file_count].name[i] = name[i]; i++; }
    files[file_count].name[i] = 0;
    if (content && size > 0) { uint32_t s = size < MAX_SIZE ? size : MAX_SIZE; memcpy(files[file_count].data, content, s); files[file_count].size = s; }
    files[file_count].is_dir = 0; files[file_count].used = 1; file_count++; return 0;
}
int fs_create_dir(const char* name) {
    if (file_count >= MAX_FILES) return -1;
    int i = 0; while (name[i] && i < MAX_NAME - 1) { files[file_count].name[i] = name[i]; i++; }
    files[file_count].name[i] = 0;
    files[file_count].is_dir = 1; files[file_count].used = 1; files[file_count].size = 0; file_count++; return 0;
}
int fs_list_dir(const char* path, char* output, uint32_t max_len) {
    (void)path; int pos = 0;
    for (int i = 0; i < file_count && pos < (int)max_len - 32; i++) {
        if (!files[i].used) continue;
        if (files[i].is_dir) { output[pos++] = '['; int j = 0; while (files[i].name[j] && pos < (int)max_len - 2) output[pos++] = files[i].name[j++]; output[pos++] = ']'; }
        else { int j = 0; while (files[i].name[j] && pos < (int)max_len - 2) output[pos++] = files[i].name[j++]; }
        output[pos++] = '\n';
    }
    output[pos] = 0; return pos;
}
int fs_read_file(const char* name, char* buf, uint32_t max_len) {
    for (int i = 0; i < file_count; i++) {
        if (files[i].used && !files[i].is_dir && strcmp(files[i].name, name) == 0) {
            uint32_t s = files[i].size < max_len ? files[i].size : max_len;
            memcpy(buf, files[i].data, s); return s;
        }
    }
    return -1;
}
int fs_write_file(const char* name, const char* content, uint32_t size) {
    for (int i = 0; i < file_count; i++) {
        if (files[i].used && strcmp(files[i].name, name) == 0) {
            uint32_t s = size < MAX_SIZE ? size : MAX_SIZE;
            memcpy(files[i].data, content, s); files[i].size = s; files[i].is_dir = 0; return 0;
        }
    }
    return fs_create_file(name, content, size);
}
int fs_delete_file(const char* name) {
    for (int i = 0; i < file_count; i++) {
        if (files[i].used && strcmp(files[i].name, name) == 0) { files[i].used = 0; return 0; }
    }
    return -1;
}
int fs_file_size(const char* name) {
    for (int i = 0; i < file_count; i++) {
        if (files[i].used && strcmp(files[i].name, name) == 0) return files[i].size;
    }
    return -1;
}
int fs_file_exists(const char* name) {
    for (int i = 0; i < file_count; i++) {
        if (files[i].used && strcmp(files[i].name, name) == 0) return 1;
    }
    return 0;
}
void fs_get_stats(uint32_t* total, uint32_t* used, uint32_t* free_b) {
    uint32_t t = MAX_FILES * MAX_SIZE, u = 0;
    for (int i = 0; i < file_count; i++) if (files[i].used) u += files[i].size;
    if (total) *total = t; if (used) *used = u; if (free_b) *free_b = t - u;
}
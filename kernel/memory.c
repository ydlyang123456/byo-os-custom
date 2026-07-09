/* BYO-OS - Physical Memory Manager (Bitmap Allocator) */
#include <kernel.h>

#define PAGE_SIZE 4096
#define MAX_PAGES (128 * 1024)

extern uint32_t __kernel_end;

static uint32_t bitmap[MAX_PAGES / 32];
static uint32_t total_pages = 0;
static uint32_t free_pages = 0;

static void bitmap_set(uint32_t page) {
    bitmap[page / 32] |= (1 << (page % 32));
}

static void bitmap_clear(uint32_t page) {
    bitmap[page / 32] &= ~(1 << (page % 32));
}

static int bitmap_test(uint32_t page) {
    return bitmap[page / 32] & (1 << (page % 32));
}

void pmm_init(uint32_t mem_size) {
    total_pages = mem_size / PAGE_SIZE;
    free_pages = total_pages;

    memset(bitmap, 0xFF, sizeof(bitmap));

    uint32_t reserved = 1024 * 1024 / PAGE_SIZE;
    for (uint32_t i = 0; i < reserved; i++) {
        bitmap_set(i);
        free_pages--;
    }

    uint32_t kernel_end_page = ((uint32_t)&__kernel_end + PAGE_SIZE - 1) / PAGE_SIZE;
    for (uint32_t i = reserved; i < kernel_end_page; i++) {
        bitmap_set(i);
        free_pages--;
    }
}

void* pmm_alloc_page(void) {
    for (uint32_t i = 0; i < total_pages / 32; i++) {
        if (bitmap[i] != 0xFFFFFFFF) {
            for (int j = 0; j < 32; j++) {
                if (!(bitmap[i] & (1 << j))) {
                    uint32_t page = i * 32 + j;
                    bitmap_clear(page);
                    free_pages--;
                    return (void*)(page * PAGE_SIZE);
                }
            }
        }
    }
    return (void*)0;
}

void pmm_free_page(void* page) {
    uint32_t addr = (uint32_t)page;
    uint32_t p = addr / PAGE_SIZE;
    if (!bitmap_test(p)) {
        bitmap_set(p);
        free_pages++;
    }
}

uint32_t pmm_get_free_pages(void) {
    return free_pages;
}

uint32_t pmm_get_total_pages(void) {
    return total_pages;
}
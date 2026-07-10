/*
 * memory64.c - 64-bit Physical Memory Manager
 *
 * Bitmap-based page allocator supporting up to 128GB (0x2000000000).
 * Page size: 4KB. Max pages: 33,554,432. Bitmap: 4MB.
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>

/* ---- Configuration ---- */

#define PAGE_SIZE_64        4096ULL
#define MAX_PHYS_MEMORY     0x2000000000ULL          /* 128 GB */
#define MAX_PAGES           (MAX_PHYS_MEMORY / PAGE_SIZE_64)  /* 33,554,432 */
#define BITMAP_SIZE         (MAX_PAGES / 8)          /* 4,194,304 bytes = 4 MB */

#define BITMAP_SET(bm, i)   ((bm)[(i) / 8] |=  (1U << ((i) % 8)))
#define BITMAP_CLR(bm, i)   ((bm)[(i) / 8] &= ~(1U << ((i) % 8)))
#define BITMAP_TST(bm, i)   ((bm)[(i) / 8] &   (1U << ((i) % 8)))

/* ---- Static state ---- */

static uint8_t  pmm_bitmap[BITMAP_SIZE];
static uint64_t pmm_total_pages  = 0;
static uint64_t pmm_used_pages   = 0;
static uint64_t pmm_phys_top     = 0;   /* highest usable physical address */

/* ---- Internal helpers ---- */

static void bitmap_set_range(uint64_t start_page, uint64_t count, int used)
{
    for (uint64_t i = 0; i < count; i++) {
        uint64_t idx = start_page + i;
        if (idx >= pmm_total_pages) break;
        if (used)
            BITMAP_SET(pmm_bitmap, idx);
        else
            BITMAP_CLR(pmm_bitmap, idx);
    }
}

/* ---- Public API ---- */

/*
 * pmm_init_64 - Initialise the 64-bit physical memory manager.
 * @mem_size: total physical memory in bytes (from firmware / multiboot).
 *
 * All pages are marked free; then the first 2 MB and any region above
 * mem_size are marked reserved (simple conservative approach).
 */
void pmm_init_64(uint64_t mem_size)
{
    if (mem_size > MAX_PHYS_MEMORY)
        mem_size = MAX_PHYS_MEMORY;

    memset(pmm_bitmap, 0xFF, BITMAP_SIZE);   /* mark everything reserved */

    pmm_total_pages = mem_size / PAGE_SIZE_64;
    pmm_phys_top    = mem_size;
    pmm_used_pages  = pmm_total_pages;        /* will subtract as we free */

    /* Mark all pages within mem_size as free */
    bitmap_set_range(0, pmm_total_pages, 0);
    pmm_used_pages = 0;

    /* Reserve page 0 (real-mode IVT / BDA on x86) */
    BITMAP_SET(pmm_bitmap, 0);
    pmm_used_pages++;

    /* Reserve the first 2 MB (bootloader, GDT, IDT, VGA, etc.) */
    uint64_t reserved = (2ULL * 1024 * 1024) / PAGE_SIZE_64;  /* 512 pages */
    if (reserved > pmm_total_pages)
        reserved = pmm_total_pages;

    for (uint64_t i = 1; i < reserved; i++) {
        if (!BITMAP_TST(pmm_bitmap, i)) {
            BITMAP_SET(pmm_bitmap, i);
            pmm_used_pages++;
        }
    }
}

/*
 * pmm_alloc_page_64 - Allocate a single 4KB page.
 * Returns the physical address of the page, or 0 on failure.
 */
uint64_t pmm_alloc_page_64(void)
{
    if (pmm_used_pages >= pmm_total_pages)
        return 0;

    /* Linear scan for a free page */
    for (uint64_t i = 0; i < pmm_total_pages; i++) {
        if (!BITMAP_TST(pmm_bitmap, i)) {
            BITMAP_SET(pmm_bitmap, i);
            pmm_used_pages++;
            return i * PAGE_SIZE_64;
        }
    }
    return 0;
}

/*
 * pmm_alloc_pages_64 - Allocate a contiguous run of @count pages.
 * Returns the physical address, or 0 on failure.
 */
uint64_t pmm_alloc_pages_64(uint64_t count)
{
    if (count == 0) return 0;
    if (pmm_used_pages + count > pmm_total_pages) return 0;

    uint64_t run = 0;
    uint64_t start = 0;

    for (uint64_t i = 0; i < pmm_total_pages; i++) {
        if (!BITMAP_TST(pmm_bitmap, i)) {
            if (run == 0) start = i;
            run++;
            if (run == count) {
                bitmap_set_range(start, count, 1);
                pmm_used_pages += count;
                return start * PAGE_SIZE_64;
            }
        } else {
            run = 0;
        }
    }
    return 0;
}

/*
 * pmm_free_page_64 - Free a single 4KB page.
 * @page: physical address of the page (must be page-aligned).
 */
void pmm_free_page_64(void *page)
{
    uint64_t addr = (uint64_t)page;
    if (addr >= pmm_phys_top) return;

    uint64_t idx = addr / PAGE_SIZE_64;
    if (idx >= pmm_total_pages) return;

    if (BITMAP_TST(pmm_bitmap, idx)) {
        BITMAP_CLR(pmm_bitmap, idx);
        if (pmm_used_pages > 0)
            pmm_used_pages--;
    }
}

/*
 * pmm_free_pages_64 - Free @count contiguous pages starting at @base.
 */
void pmm_free_pages_64(void *base, uint64_t count)
{
    uint64_t addr = (uint64_t)base;
    uint64_t idx  = addr / PAGE_SIZE_64;

    for (uint64_t i = 0; i < count; i++) {
        uint64_t cur = idx + i;
        if (cur >= pmm_total_pages) break;
        if (BITMAP_TST(pmm_bitmap, cur)) {
            BITMAP_CLR(pmm_bitmap, cur);
            if (pmm_used_pages > 0)
                pmm_used_pages--;
        }
    }
}

/*
 * pmm_get_free_pages_64 - Return number of free pages.
 */
uint64_t pmm_get_free_pages_64(void)
{
    return pmm_total_pages - pmm_used_pages;
}

/*
 * pmm_get_total_pages_64 - Return total number of managed pages.
 */
uint64_t pmm_get_total_pages_64(void)
{
    return pmm_total_pages;
}

/* 包装函数 - 不带_64后缀 */
uint64_t pmm_get_free_pages(void) { return pmm_get_free_pages_64(); }
uint64_t pmm_get_total_pages(void) { return pmm_get_total_pages_64(); }
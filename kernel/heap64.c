/*
 * heap64.c - 64-bit Kernel Heap Allocator
 *
 * First-fit block allocator built on top of the physical page allocator.
 * Supports individual allocations well beyond 4 GB by carving from
 * physically-contiguous regions obtained via pmm_alloc_pages_64().
 *
 * Each allocation is preceded by a block header that records the usable
 * size so kfree_64 can release the correct region.
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>

/* ---- Forward declarations from memory64.c ---- */

extern uint64_t pmm_alloc_page_64(void);
extern uint64_t pmm_alloc_pages_64(uint64_t count);
extern void     pmm_free_page_64(void *page);
extern void     pmm_free_pages_64(void *base, uint64_t count);

/* ---- Constants ---- */

#define HEAP_PAGE_SIZE      4096ULL
#define HEAP_MIN_GROW       16                       /* minimum pages to grow */
#define HEAP_ALIGN          16                       /* 16-byte alignment */

/* ---- Block header (lives immediately before the user pointer) ---- */

typedef struct heap_block {
    uint64_t            size;       /* usable bytes (excludes header) */
    int                 free;       /* 1 = free, 0 = allocated */
    struct heap_block  *next;
    struct heap_block  *prev;
} heap_block_t;

#define BLOCK_HDR_SIZE  sizeof(heap_block_t)

/* ---- Heap state ---- */

static heap_block_t *heap_head = NULL;
static uint64_t      heap_used = 0;       /* bytes currently allocated by users */
static uint64_t      heap_committed = 0;  /* bytes committed from PMM */

/* ---- Internal helpers ---- */

/* Round up to HEAP_ALIGN */
static uint64_t align_up(uint64_t value, uint64_t align)
{
    return (value + align - 1) & ~(align - 1);
}

/* Obtain a pointer to the block header from a user pointer */
static inline heap_block_t *user_to_block(void *ptr)
{
    return (heap_block_t *)((uint8_t *)ptr - BLOCK_HDR_SIZE);
}

/* Obtain user pointer from a block header */
static inline void *block_to_user(heap_block_t *blk)
{
    return (void *)((uint8_t *)blk + BLOCK_HDR_SIZE);
}

/*
 * heap_grow - Commit additional pages from the PMM and append a free
 *             block to the heap list.  @min_bytes is the minimum usable
 *             payload required.
 */
static int heap_grow(uint64_t min_bytes)
{
    uint64_t need = align_up(BLOCK_HDR_SIZE + min_bytes, HEAP_PAGE_SIZE);
    uint64_t pages = need / HEAP_PAGE_SIZE;
    if (pages < HEAP_MIN_GROW)
        pages = HEAP_MIN_GROW;

    uint64_t phys = pmm_alloc_pages_64(pages);
    if (phys == 0) return -1;

    /* Create a single free block covering the entire region */
    heap_block_t *blk = (heap_block_t *)(uint64_t)phys;
    blk->size = (pages * HEAP_PAGE_SIZE) - BLOCK_HDR_SIZE;
    blk->free = 1;
    blk->next = NULL;
    blk->prev = NULL;

    /* Append to list */
    if (!heap_head) {
        heap_head = blk;
    } else {
        heap_block_t *tail = heap_head;
        while (tail->next)
            tail = tail->next;
        tail->next  = blk;
        blk->prev   = tail;
    }

    heap_committed += pages * HEAP_PAGE_SIZE;
    return 0;
}

/*
 * split_block - If @blk has enough room for a second block, split it.
 */
static void split_block(heap_block_t *blk, uint64_t need)
{
    uint64_t min_total = align_up(need + BLOCK_HDR_SIZE + sizeof(heap_block_t), HEAP_ALIGN);
    if (blk->size < min_total)
        return;

    heap_block_t *new_blk =
        (heap_block_t *)((uint8_t *)blk + BLOCK_HDR_SIZE + need);
    new_blk->size = blk->size - need - BLOCK_HDR_SIZE;
    new_blk->free = 1;
    new_blk->next = blk->next;
    new_blk->prev = blk;

    if (blk->next)
        blk->next->prev = new_blk;

    blk->next = new_blk;
    blk->size = need;
}

/*
 * merge_free - Coalesce adjacent free blocks starting from @blk.
 */
static void merge_free(heap_block_t *blk)
{
    while (blk->next && blk->next->free) {
        blk->size += BLOCK_HDR_SIZE + blk->next->size;
        blk->next  = blk->next->next;
        if (blk->next)
            blk->next->prev = blk;
    }
}

/* ---- Public API ---- */

/*
 * kmalloc_64 - Allocate @size bytes from the kernel heap.
 * Returns an aligned pointer, or NULL on failure.
 */
void *kmalloc_64(size_t size)
{
    if (size == 0) return NULL;

    uint64_t need = align_up(size, HEAP_ALIGN);

    /* First-fit search */
    heap_block_t *blk = heap_head;
    while (blk) {
        if (blk->free && blk->size >= need) {
            split_block(blk, need);
            blk->free = 0;
            heap_used += blk->size;
            return block_to_user(blk);
        }
        blk = blk->next;
    }

    /* No suitable block found - grow the heap */
    if (heap_grow(need) != 0)
        return NULL;

    /* Retry first-fit on the newly appended block */
    blk = heap_head;
    while (blk) {
        if (blk->free && blk->size >= need) {
            split_block(blk, need);
            blk->free = 0;
            heap_used += blk->size;
            return block_to_user(blk);
        }
        blk = blk->next;
    }

    return NULL;
}

/*
 * kfree_64 - Free a pointer previously returned by kmalloc_64.
 *            Adjacent free blocks are coalesced automatically.
 */
void kfree_64(void *ptr)
{
    if (!ptr) return;

    heap_block_t *blk = user_to_block(ptr);
    if (blk->free) return;   /* double-free guard */

    heap_used -= blk->size;
    blk->free = 1;
    merge_free(blk);

    /* Also merge with predecessor if it is free */
    if (blk->prev && blk->prev->free)
        merge_free(blk->prev);
}

/*
 * heap_get_used_64 - Return the total number of bytes currently allocated
 *                    (user payload) by the heap.
 */
uint64_t heap_get_used_64(void)
{
    return heap_used;
}

/*
 * heap_get_committed_64 - Return the total bytes obtained from the PMM.
 */
uint64_t heap_get_committed_64(void)
{
    return heap_committed;
}

/*
 * kmalloc_64_init - Initialize the 64-bit kernel heap.
 *                   Called once at boot before any allocations.
 */
void kmalloc_64_init(void)
{
    heap_used = 0;
    heap_committed = 0;
    /* The heap will grow on demand via pmm_alloc_pages_64() */
}
/*
 * kmalloc - Wrapper for kmalloc_64 (backward compatibility)
 */
void* kmalloc(size_t size)
{
    return kmalloc_64(size);
}
/* 包装函数 - 不带_64后缀 */
uint64_t heap_get_used(void) { return heap_get_used_64(); }
/* 包装函数 - kfree (不带_64后缀) */
void kfree(void* ptr) { kfree_64(ptr); }
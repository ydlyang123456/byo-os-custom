/* memory64.c - Physical Memory Manager (64-bit) */
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#define PAGE_SIZE 4096ULL
#define MAX_PHYS 0x2000000000ULL
#define MAX_PGS (MAX_PHYS / PAGE_SIZE)
#define BM_SZ (MAX_PGS / 8)

#define BM_SET(b,i) ((b)[(i)/8] |= (1U<<((i)%8)))
#define BM_CLR(b,i) ((b)[(i)/8] &= ~(1U<<((i)%8)))
#define BM_TST(b,i) ((b)[(i)/8] & (1U<<((i)%8)))

static uint8_t bm[BM_SZ];
static uint64_t total_pgs = 0, used_pgs = 0, phys_top = 0;

void pmm_init_64(uint64_t mem_size) {
    if (mem_size > MAX_PHYS) mem_size = MAX_PHYS;
    memset(bm, 0xFF, BM_SZ);
    total_pgs = mem_size / PAGE_SIZE; phys_top = mem_size; used_pgs = total_pgs;
    for (uint64_t i = 0; i < total_pgs; i++) { BM_CLR(bm, i); } used_pgs = 0;
    BM_SET(bm, 0); used_pgs++;
    uint64_t rsv = (2ULL*1024*1024)/PAGE_SIZE;
    if (rsv > total_pgs) rsv = total_pgs;
    for (uint64_t i = 1; i < rsv; i++) { if (!BM_TST(bm,i)) { BM_SET(bm,i); used_pgs++; } }
}

uint64_t pmm_alloc_page_64(void) {
    if (used_pgs >= total_pgs) return 0;
    for (uint64_t i = 0; i < total_pgs; i++) {
        if (!BM_TST(bm,i)) { BM_SET(bm,i); used_pgs++; return i*PAGE_SIZE; }
    }
    return 0;
}

uint64_t pmm_alloc_pages_64(uint64_t count) {
    if (count==0||used_pgs+count>total_pgs) return 0;
    uint64_t run=0,start=0;
    for (uint64_t i=0;i<total_pgs;i++) {
        if (!BM_TST(bm,i)) { if(!run)start=i; run++; if(run==count) { for(uint64_t j=0;j<count;j++)bm[(start+j)/8]|=(1U<<((start+j)%8)); used_pgs+=count; return start*PAGE_SIZE; } }
        else run=0;
    }
    return 0;
}

/* pmm_free_page_64 - takes physical address or pointer */
void pmm_free_page_64(void *page) {
    uint64_t addr = (uint64_t)page;
    if (addr >= phys_top) return;
    uint64_t idx = addr / PAGE_SIZE;
    if (idx >= total_pgs) return;
    if (BM_TST(bm,idx)) { BM_CLR(bm,idx); if(used_pgs>0)used_pgs--; }
}

void pmm_free_pages_64(void *base, uint64_t count) {
    uint64_t idx = (uint64_t)base / PAGE_SIZE;
    for (uint64_t i=0;i<count;i++) {
        uint64_t cur = idx+i;
        if (cur >= total_pgs) break;
        if (BM_TST(bm,cur)) { BM_CLR(bm,cur); if(used_pgs>0)used_pgs--; }
    }
}

uint64_t pmm_get_free_pages_64(void) { return total_pgs - used_pgs; }
uint64_t pmm_get_total_pages_64(void) { return total_pgs; }
uint64_t pmm_get_used_pages_64(void) { return used_pgs; }
uint64_t pmm_get_memory_size(void) { return phys_top; }
uint64_t pmm_get_free_bytes(void) { return (total_pgs - used_pgs) * PAGE_SIZE; }
uint64_t pmm_get_used_bytes(void) { return used_pgs * PAGE_SIZE; }
uint32_t pmm_get_usage_percent(void) {
    if (total_pgs == 0) return 0;
    return (uint32_t)(used_pgs * 100 / total_pgs);
}

/* 32-bit compat wrappers */
void pmm_init(uint32_t mem_size) { pmm_init_64((uint64_t)mem_size); }
void* pmm_alloc_page(void) { return (void*)pmm_alloc_page_64(); }
void pmm_free_page(void* page) { pmm_free_page_64(page); }
uint32_t pmm_get_free_pages(void) { return (uint32_t)pmm_get_free_pages_64(); }
uint32_t pmm_get_total_pages(void) { return (uint32_t)pmm_get_total_pages_64(); }

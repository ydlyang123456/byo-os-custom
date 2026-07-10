/*
 * vmm.c - 64-bit Virtual Memory Manager
 *
 * 4-level page table hierarchy (PML4 -> PDPT -> PD -> PT) with 4 KB pages.
 * Each level has 512 entries; each entry is 8 bytes.
 * Total virtual address space: 48-bit canonical (256 TB per half).
 *
 * This implementation maps the lower-half kernel addresses 1:1 (physical ==
 * virtual) and provides an API for arbitrary mappings.
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>

/* ---- Forward declarations from memory64.c ---- */

extern uint64_t pmm_alloc_page_64(void);
extern void     pmm_free_page_64(void *page);

/* ---- Page table constants ---- */

#define PT_LEVELS       4
#define PT_ENTRIES      512
#define PT_ENTRY_SIZE   sizeof(uint64_t)
#define PAGE_SIZE       4096ULL

/* Index extractors: bits [39:30], [29:20], [19:10], [9:0] */
#define PML4_INDEX(va) (((va) >> 39) & 0x1FF)
#define PDPT_INDEX(va) (((va) >> 30) & 0x1FF)
#define PD_INDEX(va)   (((va) >> 21) & 0x1FF)
#define PT_INDEX(va)   (((va) >> 12) & 0x1FF)

/* ---- Page entry flags ---- */

#define PTE_PRESENT     (1ULL << 0)
#define PTE_WRITABLE    (1ULL << 1)
#define PTE_USER        (1ULL << 2)
#define PTE_WRITE_THRU  (1ULL << 3)
#define PTE_CACHE_DIS   (1ULL << 4)
#define PTE_ACCESSED    (1ULL << 5)
#define PTE_DIRTY       (1ULL << 6)
#define PTE_PS          (1ULL << 7)    /* page size (only at PD level) */
#define PTE_GLOBAL      (1ULL << 8)
#define PTE_NO_EXECUTE  (1ULL << 63)   /* NX bit (requires EFER.NXE) */

#define PTE_ADDR_MASK   0x000FFFFFFFFFF000ULL

/* Common flag combinations */
#define VMM_KERNEL_RW   (PTE_PRESENT | PTE_WRITABLE)
#define VMM_KERNEL_RO   (PTE_PRESENT)
#define VMM_USER_RW     (PTE_PRESENT | PTE_WRITABLE | PTE_USER)
#define VMM_USER_RO     (PTE_PRESENT | PTE_USER)

/* ---- Root page table ---- */

static uint64_t *vmm_pml4 = NULL;

/* ---- Internal helpers ---- */

/* Allocate a zeroed page for a page-table level */
static uint64_t *pt_alloc_table(void)
{
    uint64_t phys = pmm_alloc_page_64();
    if (phys == 0) return NULL;
    memset((void *)(uint64_t)phys, 0, PAGE_SIZE);
    return (uint64_t *)(uint64_t)phys;
}

/*
 * pt_get_or_create - Walk one level; create the next-level table if needed.
 * @table:  pointer to the current-level table (PML4, PDPT, or PD).
 * @index:  entry index within the table.
 * Returns pointer to the next-level table entry (uint64_t *).
 */
static uint64_t *pt_get_or_create(uint64_t *table, uint64_t index)
{
    uint64_t entry = table[index];

    if (!(entry & PTE_PRESENT)) {
        uint64_t *next = pt_alloc_table();
        if (!next) return NULL;
        uint64_t phys_addr = (uint64_t)next;
        table[index] = phys_addr | VMM_KERNEL_RW;
        return next;
    }

    return (uint64_t *)(entry & PTE_ADDR_MASK);
}

/*
 * pt_walk - Walk all four levels to locate the PTE for @virt.
 *           Intermediate levels are created if @create is non-zero.
 *           On success *out_entry is set to a pointer to the PTE.
 */
static int pt_walk(uint64_t virt, int create, uint64_t **out_entry)
{
    uint64_t *pdpt, *pd, *pt;

    /* PML4 -> PDPT */
    pdpt = pt_get_or_create(vmm_pml4, PML4_INDEX(virt));
    if (!pdpt) return -1;

    /* PDPT -> PD */
    pd = pt_get_or_create(pdpt, PDPT_INDEX(virt));
    if (!pd) return -1;

    /* PD -> PT */
    pt = pt_get_or_create(pd, PD_INDEX(virt));
    if (!pt) return -1;

    *out_entry = &pt[PT_INDEX(virt)];
    return 0;
}

/* ---- Public API ---- */

/*
 * vmm_init - Allocate the initial PML4 and install the higher-half
 *            kernel identity mapping (physical == virtual for the first
 *            4 GB using 2 MB superpages at the PD level).
 */
void vmm_init(void)
{
    vmm_pml4 = pt_alloc_table();
    if (!vmm_pml4) return;  /* should not happen */

    /*
     * Identity-map the first 2 GB of physical memory using 2 MB pages
     * for efficient kernel boot.  (Covers the first 512 PD entries.)
     */
    uint64_t *pdpt = pt_get_or_create(vmm_pml4, 0);
    if (!pdpt) return;

    /* Create 4 PDPT entries, each covering 1 GB with 512 x 2 MB pages */
    for (int p = 0; p < 4; p++) {
        uint64_t *pd = pt_get_or_create(pdpt, p);
        if (!pd) return;

        for (int i = 0; i < PT_ENTRIES; i++) {
            uint64_t phys = ((uint64_t)p * PT_ENTRIES + i) * (2ULL * 1024 * 1024);
            pd[i] = phys | VMM_KERNEL_RW | PTE_PS;   /* 2 MB superpage */
        }
    }
}

/*
 * vmm_get_pml4_phys - Return the physical address of the PML4,
 *                      suitable for loading into CR3.
 */
uint64_t vmm_get_pml4_phys(void)
{
    return (uint64_t)vmm_pml4;
}

/*
 * vmm_map - Map virtual address @virt to physical address @phys
 *           with protection @flags (PTE_PRESENT | PTE_WRITABLE | ...).
 *           Creates intermediate tables as needed.  4 KB granularity.
 *
 * @virt:  virtual address (must be page-aligned).
 * @phys:  physical address (must be page-aligned).
 * @flags: entry flags (use VMM_KERNEL_RW, VMM_USER_RW, etc.).
 */
int vmm_map(uint64_t virt, uint64_t phys, uint64_t flags)
{
    uint64_t *entry = NULL;
    if (pt_walk(virt, 1, &entry) != 0)
        return -1;

    *entry = (phys & PTE_ADDR_MASK) | (flags | PTE_PRESENT);
    return 0;
}

/*
 * vmm_unmap - Remove the mapping for virtual address @virt.
 *             The backing physical page is NOT freed (caller must manage).
 */
void vmm_unmap(uint64_t virt)
{
    uint64_t *entry = NULL;
    if (pt_walk(virt, 0, &entry) != 0)
        return;

    *entry = 0;

    /*
     * Invalidate the TLB entry.  On x86-64 this is done via INVPCID or
     * INVLPG.  We emit a compiler barrier; the actual instruction should
     * be provided by an arch-specific header in a real kernel.
     */
    __asm__ volatile ("invlpg (%0)" : : "r"(virt) : "memory");
}

/*
 * vmm_unmap_free - Unmap @virt AND free the backing physical page.
 */
void vmm_unmap_free(uint64_t virt)
{
    uint64_t *entry = NULL;
    if (pt_walk(virt, 0, &entry) != 0)
        return;

    if (*entry & PTE_PRESENT) {
        uint64_t phys = *entry & PTE_ADDR_MASK;
        pmm_free_page_64((void *)phys);
    }

    *entry = 0;
    __asm__ volatile ("invlpg (%0)" : : "r"(virt) : "memory");
}

/*
 * vmm_translate - Look up the physical address for a given virtual address.
 *                 Returns the physical address, or 0 if not mapped.
 */
uint64_t vmm_translate(uint64_t virt)
{
    uint64_t *entry = NULL;
    if (pt_walk(virt, 0, &entry) != 0)
        return 0;

    if (!(*entry & PTE_PRESENT))
        return 0;

    return (*entry & PTE_ADDR_MASK) | (virt & 0xFFFULL);
}

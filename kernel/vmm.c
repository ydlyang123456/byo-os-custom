/*
 * vmm.c - 64-bit Virtual Memory Manager
 *
 * 4-level page table (PML4 -> PDPT -> PD -> PT) using 2 MB superpages.
 * Identity-maps the first 4GB via PML4[0] with 4 PDPT entries.
 */
#include <kernel.h>

#define PT_ENTRIES      512
#define PAGE_SIZE       4096ULL
#define SUPERPAGE_SIZE  (2ULL * 1024 * 1024)

#define PML4_INDEX(va) (((va) >> 39) & 0x1FF)
#define PDPT_INDEX(va) (((va) >> 30) & 0x1FF)
#define PD_INDEX(va)   (((va) >> 21) & 0x1FF)
#define PT_INDEX(va)   (((va) >> 12) & 0x1FF)

#define PTE_PRESENT      (1ULL << 0)
#define PTE_WRITABLE     (1ULL << 1)
#define PTE_PS           (1ULL << 7)
#define PTE_ADDR_MASK    0x000FFFFFFFFFF000ULL

#define VMM_KERNEL_RW    (PTE_PRESENT | PTE_WRITABLE)

static uint64_t vmm_pml4_phys = 0;
static uint64_t vmm_mapped_size = 0;

static uint64_t pt_alloc_page(void) {
    return pmm_alloc_page_64();
}

/* Set PML4[index] to point to a new zeroed page table */
static int pt_create_table(uint64_t pml4_phys, int index) {
    uint64_t *pml4 = (uint64_t*)(uintptr_t)pml4_phys;
    uint64_t new_table = pt_alloc_page();
    if (!new_table) return -1;
    memset((void*)(uintptr_t)new_table, 0, PAGE_SIZE);
    pml4[index] = new_table | VMM_KERNEL_RW;
    return 0;
}

void vmm_init(void) {
    uint64_t pml4 = pt_alloc_page();
    if (!pml4) return;
    memset((void*)(uintptr_t)pml4, 0, PAGE_SIZE);
    vmm_pml4_phys = pml4;
    
    uint64_t *pml4_v = (uint64_t*)(uintptr_t)pml4;

    uint64_t pdpt = pt_alloc_page();
    if (!pdpt) return;
    memset((void*)(uintptr_t)pdpt, 0, PAGE_SIZE);
    pml4_v[0] = pdpt | VMM_KERNEL_RW;

    uint64_t *pdpt_v = (uint64_t*)(uintptr_t)pdpt;
    
    uint64_t total_mem = pmm_get_total_pages_64() * PAGE_SIZE;
    if (total_mem > (128ULL * 1024 * 1024 * 1024))
        total_mem = 128ULL * 1024 * 1024 * 1024;

    /* How many 1GB chunks to map */
    uint64_t gb_needed = (total_mem + (1024ULL*1024*1024) - 1) / (1024ULL*1024*1024);
    if (gb_needed > 4) gb_needed = 4;

    for (uint64_t gb = 0; gb < gb_needed; gb++) {
        /* Create PD table for this 1GB range */
        uint64_t pd = pt_alloc_page();
        if (!pd) { serial_puts("[VMM] ERROR: PD alloc failed\n"); return; }
        memset((void*)(uintptr_t)pd, 0, PAGE_SIZE);
        pdpt_v[gb] = pd | VMM_KERNEL_RW;

        uint64_t *pd_v = (uint64_t*)(uintptr_t)pd;
        for (int i = 0; i < PT_ENTRIES; i++) {
            uint64_t base = (gb * PT_ENTRIES + i) * SUPERPAGE_SIZE;
            pd_v[i] = base | VMM_KERNEL_RW | PTE_PS;
        }
        vmm_mapped_size = (gb + 1) * 1024ULL * 1024 * 1024;
    }

    serial_puts("[VMM] Identity mapped ");
    serial_put_dec_u64(vmm_mapped_size / (1024*1024));
    serial_puts(" MB via 2MB superpages (PML4[0] only)\n");
}

uint64_t vmm_get_pml4_phys(void) {
    return vmm_pml4_phys;
}

uint64_t vmm_get_mapped_size(void) {
    return vmm_mapped_size;
}

void vmm_map(uint64_t virt, uint64_t phys, uint64_t flags) {
    uint64_t *pml4 = (uint64_t*)(uintptr_t)vmm_pml4_phys;
    uint64_t pml4e = pml4[PML4_INDEX(virt)];
    if (!(pml4e & PTE_PRESENT)) return;
    uint64_t *pdpt = (uint64_t*)(uintptr_t)(pml4e & PTE_ADDR_MASK);
    uint64_t pdpte = pdpt[PDPT_INDEX(virt)];
    if (!(pdpte & PTE_PRESENT)) return;
    uint64_t *pd = (uint64_t*)(uintptr_t)(pdpte & PTE_ADDR_MASK);
    uint64_t pde = pd[PD_INDEX(virt)];
    if (!(pde & PTE_PRESENT) || (pde & PTE_PS)) return;
    uint64_t *pt = (uint64_t*)(uintptr_t)(pde & PTE_ADDR_MASK);
    uint64_t pti = PT_INDEX(virt);
    pt[pti] = (phys & PTE_ADDR_MASK) | (flags | PTE_PRESENT);
}

void vmm_unmap(uint64_t virt) {
    uint64_t *pml4 = (uint64_t*)(uintptr_t)vmm_pml4_phys;
    uint64_t pml4e = pml4[PML4_INDEX(virt)];
    if (!(pml4e & PTE_PRESENT)) return;
    uint64_t *pdpt = (uint64_t*)(uintptr_t)(pml4e & PTE_ADDR_MASK);
    uint64_t pdpte = pdpt[PDPT_INDEX(virt)];
    if (!(pdpte & PTE_PRESENT)) return;
    uint64_t *pd = (uint64_t*)(uintptr_t)(pdpte & PTE_ADDR_MASK);
    uint64_t pde = pd[PD_INDEX(virt)];
    if (!(pde & PTE_PRESENT) || (pde & PTE_PS)) return;
    uint64_t *pt = (uint64_t*)(uintptr_t)(pde & PTE_ADDR_MASK);
    pt[PT_INDEX(virt)] = 0;
    __asm__ volatile("invlpg (%0)" : : "r"(virt) : "memory");
}

uint64_t vmm_translate(uint64_t virt) {
    uint64_t *pml4 = (uint64_t*)(uintptr_t)vmm_pml4_phys;
    uint64_t pml4e = pml4[PML4_INDEX(virt)];
    if (!(pml4e & PTE_PRESENT)) return 0;
    uint64_t *pdpt = (uint64_t*)(uintptr_t)(pml4e & PTE_ADDR_MASK);
    uint64_t pdpte = pdpt[PDPT_INDEX(virt)];
    if (!(pdpte & PTE_PRESENT)) return 0;
    uint64_t *pd = (uint64_t*)(uintptr_t)(pdpte & PTE_ADDR_MASK);
    uint64_t pde = pd[PD_INDEX(virt)];
    if (!(pde & PTE_PRESENT)) return 0;
    if (pde & PTE_PS) {
        return (pde & PTE_ADDR_MASK) | (virt & (SUPERPAGE_SIZE - 1));
    }
    uint64_t *pt = (uint64_t*)(uintptr_t)(pde & PTE_ADDR_MASK);
    uint64_t pte = pt[PT_INDEX(virt)];
    if (!(pte & PTE_PRESENT)) return 0;
    return (pte & PTE_ADDR_MASK) | (virt & 0xFFFULL);
}

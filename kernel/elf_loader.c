/* BYO-OS ELF Loader - x86_64 */
#include <kernel.h>
#include <stdint.h>

/* ELF64 structures */
typedef struct {
    uint8_t  ident[16];
    uint16_t type;
    uint16_t machine;
    uint32_t version;
    uint64_t entry;
    uint64_t phoff;
    uint64_t shoff;
    uint32_t flags;
    uint16_t ehsize;
    uint16_t phentsize;
    uint16_t phnum;
    uint16_t shentsize;
    uint16_t shnum;
    uint16_t shstrndx;
} __attribute__((packed)) elf64_hdr_t;

typedef struct {
    uint32_t type;
    uint32_t flags;
    uint64_t offset;
    uint64_t vaddr;
    uint64_t paddr;
    uint64_t filesz;
    uint64_t memsz;
    uint64_t align;
} __attribute__((packed)) elf64_phdr_t;

/* VMM flags */
#define PTE_PRESENT    0x001
#define PTE_WRITABLE    0x002
#define PTE_USER        0x004
#define PT_LOAD        1
#define PF_X            0x1
#define PF_W            0x2
#define PF_R            0x4

int elf_validate(const char* path) {
    uint8_t magic[16];
    int ret = fs_read_file(path, (char*)magic, 16);
    if (ret < 16) return 0;
    if (magic[0] != 0x7F || magic[1] != 'E' || magic[2] != 'L' || magic[3] != 'F') return 0;
    if (magic[4] != 2) return 0;  /* 64-bit */
    uint16_t machine = *(uint16_t*)(magic + 18);
    if (machine != 0x3E) return 0;  /* x86_64 */
    return 1;
}

void* elf_get_entry(const char* path) {
    elf64_hdr_t hdr;
    int ret = fs_read_file(path, (char*)&hdr, sizeof(hdr));
    if (ret < (int)sizeof(hdr)) return NULL;
    return (void*)(uint64_t)hdr.entry;
}

int elf_load(const char* path) {
    if (!elf_validate(path)) {
        vga_puts("elf_load: invalid ELF\n");
        return -1;
    }
    int size = fs_file_size(path);
    if (size <= 0 || size > 1048576) {
        vga_puts("elf_load: bad size\n");
        return -1;
    }
    uint8_t* image = (uint8_t*)kmalloc(size);
    if (!image) return -1;
    fs_read_file(path, (char*)image, size);

    elf64_hdr_t* hdr = (elf64_hdr_t*)image;
    uint64_t entry = hdr->entry;
    vga_puts("[ELF] Loading: ");
    vga_puts(path);
    vga_puts(" entry=0x");
    vga_put_hex((uint32_t)(entry >> 32));
    vga_put_hex((uint32_t)entry);
    vga_putchar('\n');

    for (uint16_t i = 0; i < hdr->phnum; i++) {
        elf64_phdr_t* ph = (elf64_phdr_t*)(image + hdr->phoff + i * hdr->phentsize);
        if (ph->type != PT_LOAD) continue;

        uint64_t vaddr = ph->vaddr;
        uint64_t page_start = vaddr & ~0xFFFULL;
        uint64_t page_end = (vaddr + ph->memsz + 0xFFFULL) & ~0xFFFULL;

        for (uint64_t va = page_start; va < page_end; va += 0x1000) {
            uint64_t phys = pmm_alloc_page_64();
            if (!phys) { kfree(image); return -1; }
            uint64_t flags = PTE_PRESENT | PTE_USER;
            if (ph->flags & PF_W) flags |= PTE_WRITABLE;
            vmm_map(va, phys, flags);
            memset((void*)(uint64_t)va, 0, 0x1000);
        }

        if (ph->filesz > 0)
            memcpy((void*)(uint64_t)vaddr, image + ph->offset, ph->filesz);
        if (ph->memsz > ph->filesz)
            memset((void*)(uint64_t)(vaddr + ph->filesz), 0, ph->memsz - ph->filesz);
    }

    kfree(image);
    vga_puts("[ELF] Loaded successfully\n");
    return (int)(uint64_t)entry;
}

int elf_execute(void* entry, int argc, char** argv) {
    (void)entry; (void)argc; (void)argv;
    vga_puts("[ELF] Execution requires ring-3 support\n");
    return -1;
}

int elf_execute_file(const char* path, int argc, char** argv) {
    int entry = elf_load(path);
    if (entry <= 0) return -1;
    return elf_execute((void*)(uint64_t)entry, argc, argv);
}

/* BYO-OS - Kernel Entry Point (x86_64) */
#include <kernel.h>
#include <stdint.h>

extern void pmm_init_64(uint64_t mem_size);
extern uint64_t pmm_alloc_page_64(void);
extern void pmm_free_page_64(uint64_t page);
extern uint64_t pmm_get_free_pages_64(void);
extern uint64_t pmm_get_total_pages_64(void);
extern void kmalloc_64_init(void);
extern void* kmalloc_64(size_t size);
extern void kfree_64(void* ptr);
extern uint64_t heap_get_used_64(void);
extern void vmm_init(void);
extern void vmm_map(uint64_t virt, uint64_t phys, uint64_t flags);
extern void syscall_init(void);
extern void initramfs_init(void);

void kernel_main(uint32_t magic, void* mbi_ptr);

void _start64(uint32_t magic, void* mbi_ptr) {
    kernel_main(magic, mbi_ptr);
}

void kernel_main(uint32_t magic, void* mbi_ptr) {
    serial_init();
    serial_puts("[BOOT] BYO-OS x86_64 Starting...\n");
    vga_init();
    serial_puts("[BOOT] VGA OK\n");

    uint64_t mem_size = 128ULL * 1024 * 1024;
    if (magic == MULTIBOOT_MAGIC && mbi_ptr) {
        multiboot_info_t *mbi = (multiboot_info_t *)mbi_ptr;
        if (mbi->flags & (1 << 0)) {
            uint64_t total_kb = (uint64_t)mbi->mem_lower + (uint64_t)mbi->mem_upper;
            if (total_kb * 1024 > mem_size) mem_size = total_kb * 1024;
        }
        if ((mbi->flags & (1 << 6)) && mbi->mmap_addr) {
            uint8_t *entry = (uint8_t *)(uintptr_t)mbi->mmap_addr;
            uint8_t *end   = entry + mbi->mmap_length;
            while (entry < end) {
                uint32_t entry_size = *(uint32_t *)entry;
                uint64_t base = *(uint64_t *)(entry + 4);
                uint64_t len  = *(uint64_t *)(entry + 12);
                uint32_t mtype = *(uint32_t *)(entry + 20);
                if (mtype == 1 && base + len > mem_size) mem_size = base + len;
                entry += entry_size + 4;
            }
        }
    }
    if (mem_size > 128ULL * 1024 * 1024 * 1024)
        mem_size = 128ULL * 1024 * 1024 * 1024;
    serial_puts("[BOOT] Detected memory: ");
    serial_put_dec_u64(mem_size / (1024*1024));
    serial_puts(" MB\n");

    gdt_init();
    serial_puts("[BOOT] GDT OK\n");
    idt_init();
    serial_puts("[BOOT] IDT OK\n");
    irq_init();
    serial_puts("[BOOT] IRQ OK\n");

    pmm_init_64(mem_size);
    serial_puts("[BOOT] PMM64 OK\n");
    kmalloc_64_init();
    serial_puts("[BOOT] Heap64 OK\n");
    vmm_init();
    serial_puts("[BOOT] VMM OK (no CR3 switch)\n");

    fs_init();
    serial_puts("[BOOT] FS OK\n");
    initramfs_init();
    rtc_init();
    pci_init();
    ahci_init();
    ata_init();
    fat_init();
    serial_puts("[BOOT] Initramfs OK\n");

    syscall_init();
    serial_puts("[BOOT] Syscall layer OK\n");

    journal_init();
    journal_append(0, "Filesystem initialized");
    keyboard_init();
    serial_puts("[BOOT] Keyboard OK\n");
    timer_init(100);
    serial_puts("[BOOT] Timer OK\n");
    scheduler_init();
    journal_append(0, "Scheduler initialized");
    serial_puts("[BOOT] Scheduler OK\n");

    user_init();
    journal_append(0, "User system initialized");
    serial_puts("[BOOT] User OK\n");
    net_init();
    tcpip_init();
    sound_init();
    sound_play_melody();
    usb_init();
    vbe_init();
    journal_append(0, "Network initialized");
    serial_puts("[BOOT] Net OK\n");

    fs_create_file("readme.txt", "Welcome to BYO-OS!\nA from-scratch x86_64 OS.\nDebian 12 compatible.\n", 70);
    fs_create_file("hello.txt", "Hello, World!\n", 14);
    fs_create_dir("home"); fs_create_dir("tmp"); fs_create_dir("var"); fs_create_dir("var/log");
    fs_create_dir("opt"); fs_create_dir("srv"); fs_create_dir("usr"); fs_create_dir("usr/local");
    serial_puts("[BOOT] Directory structure created\n");

    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("============================================\n");
    vga_puts("           BYO-OS v2.9 (x86_64)\n");
    vga_puts("    Debian 12 Compatible | 128GB Support\n");
    vga_puts("============================================\n\n");
    vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
    vga_puts("[BOOT] Memory: ");
    vga_put_dec((uint32_t)(pmm_get_total_pages_64() * 4096 / (1024*1024)));
    vga_puts(" MB\n");
    vga_puts("[BOOT] All systems ready!\n\n");
    vga_set_color(VGA_GREEN, VGA_BLACK);
    vga_puts(">>> Type 'help' for commands. <<<\n\n");

    journal_append(0, "System boot complete");
    serial_puts("[BOOT] ALL DONE, launching shell\n");
    shell_init();
    shell_run();
}

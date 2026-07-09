/* BYO-OS - Kernel Entry Point */
#include <kernel.h>

void kernel_main(uint32_t magic, multiboot_info_t* mboot_info) {
    serial_init();
    serial_puts("[BOOT] 1. Serial OK\n");

    vga_init();
    serial_puts("[BOOT] 2. VGA text OK\n");

    if (magic == 0x2BADB002)
        vga_init_from_multiboot(mboot_info);

    gdt_init();
    serial_puts("[BOOT] 3. GDT OK\n");
    idt_init();
    serial_puts("[BOOT] 4. IDT OK\n");
    irq_init();
    serial_puts("[BOOT] 5. IRQ OK\n");

    uint32_t mem_size = 128 * 1024 * 1024;
    if (magic == 0x2BADB002 && mboot_info && mboot_info->mem_upper > 0)
        mem_size = (mboot_info->mem_upper + 1024) * 1024;

    pmm_init(mem_size);
    serial_puts("[BOOT] 6. PMM OK\n");
    heap_init();
    serial_puts("[BOOT] 7. Heap OK\n");
    fs_init();
    serial_puts("[BOOT] 8. FS OK\n");
    journal_init();
    journal_append(0, "Filesystem initialized");
    keyboard_init();
    serial_puts("[BOOT] 9. Keyboard OK\n");
    timer_init(100);
    serial_puts("[BOOT] 10. Timer OK\n");
    scheduler_init();
    journal_append(0, "Scheduler initialized");
    serial_puts("[BOOT] 11. Scheduler OK\n");
    user_init();
    journal_append(0, "User system initialized");
    serial_puts("[BOOT] 12. User OK\n");
    net_init();
    journal_append(0, "Network initialized");
    serial_puts("[BOOT] 13. Net OK\n");

    fs_create_file("readme.txt", "Welcome to BYO-OS!\nA from-scratch operating system.\n", 47);
    fs_create_file("hello.txt", "Hello, World!\n", 14);
    fs_create_dir("home");
    fs_create_dir("tmp");
    serial_puts("[BOOT] 14. Sample files created\n");

    vga_set_color(VGA_LIGHT_CYAN, VGA_BLACK);
    vga_puts("============================================\n");
    vga_puts("           BYO-OS v0.2 Beta\n");
    vga_puts("    Build Your Own Operating System\n");
    vga_puts("============================================\n\n");
    vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
    vga_puts("[BOOT] Memory: ");
    vga_put_dec(pmm_get_total_pages() * 4);
    vga_puts(" MB | Heap: ");
    vga_put_dec(heap_get_used());
    vga_puts(" B used\n");
    vga_puts("[BOOT] FS: ramdisk ready | Net: ");
    char ip[32]; net_get_ip_str(ip);
    vga_puts(ip);
    vga_puts("\n");
    vga_puts("[BOOT] Scheduler: ");
    vga_put_dec(task_get_count());
    vga_puts(" tasks | Users: root/admin/guest\n\n");
    vga_set_color(VGA_GREEN, VGA_BLACK);
    vga_puts(">>> All systems initialized! <<<\n\n");
    vga_set_color(VGA_LIGHT_GREY, VGA_BLACK);
    vga_puts("Type 'help' for commands.\n\n");

    journal_append(0, "System boot complete");
    serial_puts("[BOOT] ALL DONE, launching shell\n");
    shell_init();
    shell_run();
}
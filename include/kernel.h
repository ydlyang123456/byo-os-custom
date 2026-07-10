/* BYO-OS - Master Kernel Header (x86_64) */
#ifndef KERNEL_H
#define KERNEL_H
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>

/* ===== Port I/O ===== */
static inline void outb(uint16_t port, uint8_t val) { asm volatile("outb %0, %1" : : "a"(val), "Nd"(port)); }
static inline uint8_t inb(uint16_t port) { uint8_t ret; asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port)); return ret; }
static inline void outw(uint16_t port, uint16_t val) { asm volatile("outw %0, %1" : : "a"(val), "Nd"(port)); }
static inline uint16_t inw(uint16_t port) { uint16_t ret; asm volatile("inw %1, %0" : "=a"(ret) : "Nd"(port)); return ret; }
static inline void outl(uint16_t port, uint32_t val) { __asm__ volatile("outl %0, %1" : : "a"(val), "Nd"(port)); }
static inline uint32_t inl(uint16_t port) { uint32_t ret; __asm__ volatile("inl %1, %0" : "=a"(ret) : "Nd"(port)); return ret; }
static inline void io_wait(void) { outb(0x80, 0); }

/* ===== String Utilities ===== */
size_t strlen(const char* str);
int strcmp(const char* s1, const char* s2);
int strncmp(const char* s1, const char* s2, size_t n);
char* strcpy(char* dest, const char* src);
char* strncpy(char* dest, const char* src, size_t n);
char* strcat(char* dest, const char* src);
int sprintf(char *buf, const char *fmt, ...);
int snprintf(char* str, size_t size, const char* format, ...);
int atoi(const char* str);
void itoa(int value, char* str, int base);
void memset(void* dest, uint8_t val, size_t count);
void memcpy(void* dest, const void* src, size_t count);
int memcmp(const void* s1, const void* s2, size_t n);
char* strstr(const char* haystack, const char* needle);
char* strchr(const char* s, int c);
char* strrchr(const char* s, int c);
int str_append_int(char* buf, int val);
int str_append_hex(char* buf, uint32_t val);

/* ===== Font ===== */
extern const uint8_t font8x8[][8];

/* ===== Byte Order ===== */
static inline uint16_t ntohs(uint16_t v) { return ((v >> 8) & 0xFF) | ((v & 0xFF) << 8); }
uint32_t ntohl(uint32_t v);

/* ===== Multiboot ===== */
#define MULTIBOOT_MAGIC 0x2BADB002
typedef struct {
    uint32_t flags, mem_lower, mem_upper, boot_device, cmdline;
    uint32_t mods_count, mods_addr, syms[4], mmap_length, mmap_addr;
    uint32_t vbe_control_info, vbe_mode_info, vbe_mode, vbe_interface_seg, vbe_interface_off, vbe_interface_len;
    uint64_t framebuffer_addr; uint32_t framebuffer_pitch, framebuffer_width, framebuffer_height;
    uint8_t framebuffer_bpp, framebuffer_type;
} __attribute__((packed)) multiboot_info_t;

/* ===== 64-bit Register State ===== */
typedef struct {
    uint64_t r15, r14, r13, r12, r11, r10, r9, r8;
    uint64_t rdi, rsi, rbp, rdx, rcx, rbx, rax;
    uint64_t int_no, err_code;
    uint64_t rip, cs, rflags, rsp, ss;
} __attribute__((packed)) registers_t;

/* ===== VGA ===== */
#define VGA_WIDTH  80
#define VGA_HEIGHT 25
#define VGA_MEMORY 0xB8000
enum vga_color {
    VGA_BLACK=0, VGA_BLUE=1, VGA_GREEN=2, VGA_CYAN=3, VGA_RED=4,
    VGA_MAGENTA=5, VGA_BROWN=6, VGA_LIGHT_GREY=7, VGA_DARK_GREY=8,
    VGA_LIGHT_BLUE=9, VGA_LIGHT_GREEN=10, VGA_LIGHT_CYAN=11,
    VGA_LIGHT_RED=12, VGA_LIGHT_MAGENTA=13, VGA_YELLOW=14, VGA_WHITE=15,
};
void vga_init(void); void vga_clear(void); void vga_putchar(char c);
void vga_puts(const char* str); void vga_set_color(enum vga_color fg, enum vga_color bg);
void vga_put_hex(uint32_t value); void vga_set_serial_mode(int mode);
void vga_put_dec(int value); void vga_printf(const char* fmt, ...);
void vga_init_from_multiboot(multiboot_info_t* mbi);
int vga_set_mode_13h(void); void vga_set_mode_text(void);
uint8_t* vga_get_framebuffer(void); uint16_t vga_get_width(void);
uint16_t vga_get_height(void); uint16_t vga_get_pitch(void);
void vga_putpixel(int x, int y, uint8_t color); void vga_fill_rect(int x, int y, int w, int h, uint8_t color);
void vga_write_cell(int x, int y, char c, uint8_t color);

/* ===== Desktop/GFX ===== */
void gfx_draw_char(int x, int y, char ch, uint8_t color);
void gfx_puts(int x, int y, const char* s, uint8_t color);
void gfx_putdec(int x, int y, int val, uint8_t color);

/* ===== GDT ===== */
void gdt_init(void);

/* ===== IDT ===== */
typedef struct {
    uint16_t base_lo;
    uint16_t sel;
    uint8_t always0;
    uint8_t flags;
    uint16_t base_hi;
    uint32_t base_upper;
    uint32_t reserved;
} __attribute__((packed)) idt_entry_t;
typedef struct {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed)) idt_ptr_t;
void idt_init(void); void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);
void isr_handler(registers_t* regs); void irq_handler(registers_t* regs);
void irq_init(void);
typedef void (*isr_t)(registers_t*);
void isr_register_handler(int isr, isr_t handler);

/* ===== Keyboard ===== */
void keyboard_init(void); int keyboard_getchar(void);
int keyboard_has_input(void); void keyboard_flush(void);

/* ===== Timer ===== */
void timer_init(uint32_t freq); uint32_t timer_get_ticks(void);
uint32_t timer_get_seconds(void); void timer_sleep(uint32_t ms);
 
/* ===== Physical Memory (64-bit) ===== */
void pmm_init_64(uint64_t mem_size);
uint64_t pmm_alloc_page_64(void);
void pmm_free_page_64(uint64_t page);
uint64_t pmm_get_free_pages_64(void);
uint64_t pmm_get_total_pages_64(void);
uint64_t pmm_get_used_pages_64(void);
uint64_t pmm_get_memory_size(void);
uint64_t pmm_get_free_bytes(void);
uint64_t pmm_get_used_bytes(void);
uint32_t pmm_get_usage_percent(void);
void pmm_init(uint32_t mem_size);
void* pmm_alloc_page(void);
void pmm_free_page(void* page);
uint32_t pmm_get_free_pages(void);
uint32_t pmm_get_total_pages(void);

/* ===== Heap ===== */
void kmalloc_64_init(void);
void* kmalloc_64(size_t size);
void kfree_64(void* ptr);
uint64_t heap_get_used_64(void);
uint64_t heap_get_total_64(void);
void heap_init(void);
void* kmalloc(size_t size);
void kfree(void* ptr);
uint32_t heap_get_used(void);

/* ===== VMM ===== */
void vmm_init(void);
void vmm_map(uint64_t virt, uint64_t phys, uint64_t flags);
void vmm_unmap(uint64_t virt);

/* ===== Serial ===== */
void serial_init(void); void serial_putchar(char c);
void serial_puts(const char* str);
int serial_has_input(void); int serial_getchar(void);

/* ===== File System ===== */
void fs_init(void);
int fs_create_file(const char* name, const char* content, uint32_t size);
int fs_create_dir(const char* name);
int fs_list_dir(const char* path, char* output, uint32_t max_len);
int fs_read_file(const char* name, char* buf, uint32_t max_len);
int fs_write_file(const char* name, const char* content, uint32_t size);
int fs_delete_file(const char* name);
int fs_file_size(const char* name);
int fs_file_exists(const char* name);
void fs_get_stats(uint32_t* total, uint32_t* used, uint32_t* free);

/* ===== Scheduler ===== */
void scheduler_init(void);
int task_create(const char* name, void (*entry)(void));
void task_exit(void); void task_sleep(uint32_t ms);
int task_get_pid(void); const char* task_get_name(void);
int task_get_count(void); void scheduler_tick(void);
int task_get_max_tasks(void); const char* task_get_state_name(int pid);
const char* task_get_name_by_pid(int pid);
int task_is_active(int pid); int task_kill(int pid);

/* ===== Mouse ===== */
void mouse_init(void); void mouse_handler(registers_t* regs);
int mouse_get_x(void); int mouse_get_y(void);
uint8_t mouse_get_buttons(void); void mouse_draw_cursor(void);

/* ===== Network ===== */
int ne2000_init(void); int ne2000_send_packet(const uint8_t* data, int len);
void ne2000_poll(void);
void net_init(void); void net_send_packet(uint8_t* data, uint16_t len);
void net_recv_packet(uint8_t* data, uint16_t len);
void net_process_arp(uint8_t* data); void net_poll(void);
void net_get_ip_str(char* buf); uint32_t net_get_ip(void);
uint8_t* net_get_mac(void); int net_get_tcp_conn_count(void);
void net_get_tcp_conn_info(int idx, uint16_t *lport, uint16_t *rport, uint32_t *rip, int *state);

/* ===== User ===== */
typedef enum { USER_GUEST=0, USER_USER=1, USER_ADMIN=2, USER_ROOT=3 } user_level_t;
void user_init(void);
int user_create(const char* username, const char* password, user_level_t level, int group);
int user_login(const char* username, const char* password);
void user_logout(void); int user_get_uid(void);
const char* user_get_name(void); user_level_t user_get_level(void);
int user_has_permission(user_level_t required);
void user_list_users(char* output, uint32_t max_len);
int user_get_count(void);

/* ===== Journal ===== */
void journal_init(void); void journal_append(int level, const char* msg);
void journal_show(void); void journal_clear(void);

/* ===== Initramfs ===== */
void initramfs_init(void);

/* ===== Syscall ===== */
void syscall_init(void);

/* ===== Shell ===== */
void shell_init(void); void shell_run(void);

/* ===== BT Panel ===== */
void bt_init(void);

/* ===== Panel ===== */
void box_hline(int x1, int x2, int y, char c);
void box_vline(int x, int y1, int y2, char c);
void box_draw(int x, int y, int w, int h);
void panel_print(int x, int y, const char* s, uint8_t color);
void panel_clear(void); int wait_key(void);
int wait_input(char* buf, int max);
void progress_bar(int x, int y, int w, int pct);
void panel_dashboard(void); void panel_monitor(void);
void panel_filemanager(void); void panel_users(void);
void panel_network(void); void panel_settings(void);

/* ===== ATA Disk Driver ===== */
int ata_identify(void);
int ata_read_sectors(uint32_t lba, uint8_t count, uint16_t* buffer);
int ata_write_sectors(uint32_t lba, uint8_t count, const uint16_t* buffer);
int ata_is_present(void);
uint32_t ata_get_sectors(void);
const char* ata_get_model(void);
int ata_get_reads(void);
int ata_get_writes(void);
void ata_init(void);

/* ===== CMOS/RTC Driver ===== */
void rtc_init(void);
void rtc_get_time(int* hour, int* min, int* sec);
void rtc_get_date(int* year, int* mon, int* day);
int rtc_is_initialized(void);

/* ===== PCI Bus Driver ===== */
typedef struct {
    uint8_t bus, slot, func;
    uint16_t vendor_id, device_id;
    uint8_t class_code, subclass, prog_if;
    uint8_t irq;
    uint32_t bar0, bar1, bar2, bar3, bar4, bar5;
    int valid;
} pci_device_t;
int pci_scan(void);
int pci_get_count(void);
const pci_device_t* pci_get_device(int index);
int pci_find_device(uint16_t vendor_id, uint16_t device_id);
int pci_find_class(uint8_t class_code, uint8_t subclass);
void pci_enable_bus_master(int index);
void pci_enable_irq(int index);
uint16_t pci_get_io_base(int index);
void pci_print_devices(void);
void pci_init(void);

/* ===== FAT32 Filesystem ===== */
int fat_mount(void);
int fat_list(const char* path, char* output, uint32_t max_len);
int fat_read(const char* name, char* buf, uint32_t max_len);
int fat_is_mounted(void);
uint32_t fat_get_total_clusters(void);
uint32_t fat_get_bytes_per_cluster(void);
void fat_init(void);

/* ===== TCP/IP Protocol Stack ===== */
void tcpip_init(void);
int tcpip_handle_packet(uint8_t* data, uint16_t len);
int tcpip_send_arp_request(uint32_t target_ip);
int tcpip_send_icmp_echo(uint32_t target_ip);
int tcpip_send_udp(uint32_t dest_ip, uint16_t dest_port, uint16_t src_port, uint8_t* data, uint16_t len);
int tcpip_send_tcp_syn(uint32_t dest_ip, uint16_t dest_port, uint16_t src_port);
void tcpip_get_stats(uint32_t* pkts_in, uint32_t* pkts_out, uint32_t* bytes);
int tcpip_open_listen(uint16_t port);
int tcpip_send_response(uint8_t* data, uint16_t len);

/* ===== Sound Driver ===== */
void sound_init(void);
void sound_play(uint32_t frequency);
void sound_stop(void);
void sound_beep(void);
void sound_play_melody(void);
void sound_play_note(int note);

/* ===== Enhanced Graphics ===== */
void gfx_draw_rect(int x, int y, int w, int h, uint8_t color);
void gfx_draw_border(int x, int y, int w, int h, uint8_t color);
void gfx_draw_window(int x, int y, int w, int h, const char* title);
void gfx_draw_button(int x, int y, int w, int h, const char* text, int pressed);
void gfx_draw_progress(int x, int y, int w, int pct);
void gfx_draw_menu(int x, int y, const char** items, int count);
void gfx_draw_clock(int x, int y);
void gfx_draw_statusbar(const char* text);
void gfx_clear_area(int x, int y, int w, int h);
void gfx_scroll_up(int lines);
void gfx_demo(void);

/* ===== USB Controller Driver ===== */
void usb_init(void);
int usb_scan_controllers(void);
void usb_print_controllers(void);
int usb_get_controller_count(void);

/* ===== VBE Graphics Mode ===== */
int vbe_init(void);
int vbe_set_mode(uint16_t mode);
void vbe_list_modes(void);
int vbe_set_mode_1024x768(void);
int vbe_set_mode_800x600(void);
int vbe_set_mode_640x480(void);
void vbe_putpixel(int x, int y, uint32_t color);
void vbe_fill_rect(int x, int y, int w, int h, uint32_t color);
void vbe_draw_char(int x, int y, char c, uint32_t fg, uint32_t bg);
void vbe_puts(int x, int y, const char* s, uint32_t color);
int vbe_get_mode_info(uint16_t mode, void* info);
int vbe_get_controller_info(void* info);
uint32_t vbe_get_width(void);
uint32_t vbe_get_height(void);
uint32_t vbe_get_bpp(void);
void* vbe_get_framebuffer(void);
int vbe_is_active(void);

#endif



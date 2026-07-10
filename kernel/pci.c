/* BYO-OS - PCI Bus Driver (x86_64) */
#include <kernel.h>

/* PCI config ports */
#define PCI_CONFIG_ADDR  0xCF8
#define PCI_CONFIG_DATA  0xCFC

static uint32_t pci_read(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
    uint32_t addr = (uint32_t)((bus << 16) | (slot << 11) | (func << 8) | (offset & 0xFC) | 0x80000000);
    outl(PCI_CONFIG_ADDR, addr);
    return inl(PCI_CONFIG_DATA);
}

static void pci_write(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset, uint32_t value) {
    uint32_t addr = (uint32_t)((bus << 16) | (slot << 11) | (func << 8) | (offset & 0xFC) | 0x80000000);
    outl(PCI_CONFIG_ADDR, addr);
    outl(PCI_CONFIG_DATA, value);
}

/* Forward declare - pci_device_t is defined in kernel.h */
#define MAX_PCI_DEVICES 32
static pci_device_t pci_devices[MAX_PCI_DEVICES];
static int pci_device_count = 0;

int pci_scan(void) {
    pci_device_count = 0;
    for (int bus = 0; bus < 256; bus++) {
        for (int slot = 0; slot < 32; slot++) {
            for (int func = 0; func < 8; func++) {
                uint32_t id = pci_read(bus, slot, func, 0);
                uint16_t vendor = id & 0xFFFF;
                uint16_t device = (id >> 16) & 0xFFFF;
                if (vendor == 0xFFFF) { if (func == 0) break; continue; }
                if (pci_device_count >= MAX_PCI_DEVICES) return pci_device_count;
                pci_device_t *dev = &pci_devices[pci_device_count];
                dev->bus = bus; dev->slot = slot; dev->func = func;
                dev->vendor_id = vendor; dev->device_id = device; dev->valid = 1;
                uint32_t class_rev = pci_read(bus, slot, func, 0x08);
                dev->class_code = (class_rev >> 24) & 0xFF;
                dev->subclass = (class_rev >> 16) & 0xFF;
                dev->prog_if = (class_rev >> 8) & 0xFF;
                uint32_t irq_pin = pci_read(bus, slot, func, 0x3C);
                dev->irq = irq_pin & 0xFF;
                dev->bar0 = pci_read(bus, slot, func, 0x10);
                dev->bar1 = pci_read(bus, slot, func, 0x14);
                dev->bar2 = pci_read(bus, slot, func, 0x18);
                dev->bar3 = pci_read(bus, slot, func, 0x1C);
                dev->bar4 = pci_read(bus, slot, func, 0x20);
                dev->bar5 = pci_read(bus, slot, func, 0x24);
                pci_device_count++;
                if (func == 0 && !(id & 0x800000)) break;
            }
        }
    }
    return pci_device_count;
}

int pci_get_count(void) { return pci_device_count; }
const pci_device_t *pci_get_device(int index) {
    if (index < 0 || index >= pci_device_count) return 0;
    return &pci_devices[index];
}
int pci_find_device(uint16_t vendor_id, uint16_t device_id) {
    for (int i = 0; i < pci_device_count; i++)
        if (pci_devices[i].vendor_id == vendor_id && pci_devices[i].device_id == device_id) return i;
    return -1;
}
int pci_find_class(uint8_t class_code, uint8_t subclass) {
    for (int i = 0; i < pci_device_count; i++)
        if (pci_devices[i].class_code == class_code && 
            (subclass == 0xFF || pci_devices[i].subclass == subclass)) return i;
    return -1;
}
void pci_enable_bus_master(int index) {
    if (index < 0 || index >= pci_device_count) return;
    pci_device_t *dev = &pci_devices[index];
    uint16_t cmd = pci_read(dev->bus, dev->slot, dev->func, 0x04) & 0xFFFF;
    cmd |= 0x07;
    pci_write(dev->bus, dev->slot, dev->func, 0x04, cmd);
}
void pci_print_devices(void) {
    vga_puts("PCI Devices:\n");
    char buf[16];
    for (int i = 0; i < pci_device_count; i++) {
        pci_device_t *d = &pci_devices[i];
        itoa(d->bus, buf, 16); vga_puts(" "); vga_puts(buf); vga_putchar(' ');
        itoa(d->slot, buf, 16); vga_puts(buf); vga_putchar(' ');
        itoa(d->vendor_id, buf, 16); vga_puts(buf); vga_putchar(' ');
        itoa(d->device_id, buf, 16); vga_puts(buf); vga_putchar('\n');
    }
}
void pci_enable_irq(int index) {
    if (index < 0 || index >= pci_device_count) return;
    pci_device_t* d = &pci_devices[index];
    outl(0xCF8, 0x80000000 | (d->bus << 16) | (d->slot << 11) | (d->func << 8) | 0x3C);
    uint32_t orig = inl(0xCFC);
    outl(0xCFC, orig | 0x100);
}
void pci_init(void) {
    int count = pci_scan();
    char buf[16];
    itoa(count, buf, 10);
    serial_puts("[PCI] "); serial_puts(buf); serial_puts(" devices\n");
    vga_puts("[PCI] "); vga_puts(buf); vga_puts(" devices\n");
    for (int i = 0; i < count; i++) {
        pci_enable_bus_master(i);
        pci_device_t *d = &pci_devices[i];
        serial_puts("[PCI] "); itoa(d->vendor_id, buf, 16); serial_puts(buf);
        serial_puts(":"); itoa(d->device_id, buf, 16); serial_puts(buf);
        serial_puts("\n");
    }
}

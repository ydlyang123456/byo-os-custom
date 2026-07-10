/* BYO-OS - USB Controller Driver (x86_64) */
#include <kernel.h>

/* ===== UHCI I/O Register Offsets ===== */
#define UHCI_USBCMD      0x00   /* USB Command */
#define UHCI_USBSTS      0x02   /* USB Status */
#define UHCI_USBINTR     0x04   /* USB Interrupt Enable */
#define UHCI_FRNUM       0x06   /* Frame Number */
#define UHCI_FRBASEADD   0x08   /* Frame List Base Address */
#define UHCI_SOF         0x0C   /* Start of Frame Modify */
#define UHCI_PORTSC1     0x10   /* Port Status/Control 1 */
#define UHCI_PORTSC2     0x12   /* Port Status/Control 2 */

/* ===== USB Controller Types ===== */
#define USB_UHCI    0
#define USB_OHCI    1
#define USB_EHCI    2
#define USB_XHCI    3
#define USB_UNKNOWN (-1)

#define USB_CLASS_CODE   0x0C
#define USB_SUBCLASS     0x03
#define MAX_USB_CONTROLLERS 8

/* Per-controller information */
typedef struct {
    unsigned int present : 1;
    int pci_index;
    int type;
    uint16_t io_base;
    uint32_t mmio_base;
} usb_controller_t;

static usb_controller_t usb_controllers[MAX_USB_CONTROLLERS];
static int usb_controller_count = 0;

/* Determine controller type from PCI programming interface byte */
static int usb_get_type(uint8_t prog_if)
{
    switch (prog_if) {
        case 0x00: return USB_UHCI;
        case 0x10: return USB_OHCI;
        case 0x20: return USB_EHCI;
        case 0x30: return USB_XHCI;
        default:   return USB_UNKNOWN;
    }
}

/* Human-readable controller type string */
static const char *usb_type_string(int type)
{
    switch (type) {
        case USB_UHCI:   return "UHCI (USB 1.x)";
        case USB_OHCI:   return "OHCI (USB 1.x)";
        case USB_EHCI:   return "EHCI (USB 2.0)";
        case USB_XHCI:   return "xHCI (USB 3.x)";
        default:         return "Unknown";
    }
}

/* Extract I/O base from PCI device BAR0 (I/O BAR: bit 0 = 1, addr in bits 31–2) */
static uint16_t usb_get_io_base(int pci_index)
{
    const pci_device_t *dev = pci_get_device(pci_index);
    if (!dev || !dev->valid)
        return 0;
    if (dev->bar0 & 1)
        return (uint16_t)(dev->bar0 & 0xFFFC);
    return 0;
}

/* Extract MMIO base from PCI device BAR0 (memory BAR: bit 0 = 0) */
static uint32_t usb_get_mmio_base(int pci_index)
{
    const pci_device_t *dev = pci_get_device(pci_index);
    if (!dev || !dev->valid)
        return 0;
    if (!(dev->bar0 & 1))
        return dev->bar0 & 0xFFFFFFF0;
    return 0;
}

/*
 * Scan the PCI bus for USB controllers (class 0x0C, subclass 0x03).
 * Returns the number found.
 */
int usb_scan_controllers(void)
{
    int total = pci_get_count();
    usb_controller_count = 0;

    for (int i = 0; i < total && usb_controller_count < MAX_USB_CONTROLLERS; i++) {
        const pci_device_t *dev = pci_get_device(i);
        if (!dev || !dev->valid)
            continue;
        if (dev->class_code != USB_CLASS_CODE || dev->subclass != USB_SUBCLASS)
            continue;

        usb_controller_t *uc = &usb_controllers[usb_controller_count];
        uc->present   = 1;
        uc->pci_index = i;
        uc->type      = usb_get_type(dev->prog_if);
        uc->io_base   = usb_get_io_base(i);
        uc->mmio_base = usb_get_mmio_base(i);
        usb_controller_count++;
    }

    return usb_controller_count;
}

/*
 * Print all detected USB controllers to serial and VGA.
 */
void usb_print_controllers(void)
{
    char buf[32];

    serial_puts("[USB] USB Controllers:\n");
    vga_puts("[USB] USB Controllers:\n");

    for (int i = 0; i < usb_controller_count; i++) {
        usb_controller_t      *uc  = &usb_controllers[i];
        const pci_device_t    *dev = pci_get_device(uc->pci_index);

        /* --- Serial --- */
        serial_puts("[USB]   Controller ");
        itoa(i, buf, 10); serial_puts(buf);
        serial_puts(": ");
        serial_puts(usb_type_string(uc->type));
        serial_puts("\n");

        serial_puts("[USB]     PCI ");
        itoa(dev->vendor_id, buf, 16); serial_puts(buf);
        serial_puts(":");
        itoa(dev->device_id, buf, 16); serial_puts(buf);
        serial_puts("  (bus ");
        itoa(dev->bus, buf, 16); serial_puts(buf);
        serial_puts(" slot ");
        itoa(dev->slot, buf, 16); serial_puts(buf);
        serial_puts(" func ");
        itoa(dev->func, buf, 16); serial_puts(buf);
        serial_puts(")\n");

        serial_puts("[USB]     IRQ ");
        itoa(dev->irq, buf, 10); serial_puts(buf);
        serial_puts("\n");

        if (uc->type == USB_UHCI) {
            serial_puts("[USB]     I/O  Base: 0x");
            itoa(uc->io_base, buf, 16); serial_puts(buf);
            serial_puts("\n");
        } else {
            serial_puts("[USB]     MMIO Base: 0x");
            itoa(uc->mmio_base, buf, 16); serial_puts(buf);
            serial_puts("\n");
        }

        /* --- VGA (brief) --- */
        vga_puts("[USB]   ");
        itoa(i, buf, 10); vga_puts(buf);
        vga_puts(": ");
        vga_puts(usb_type_string(uc->type));
        vga_puts("\n");
    }
}

/* Return the number of USB controllers found during last scan */
int usb_get_controller_count(void)
{
    return usb_controller_count;
}

/*
 * Initialize the USB subsystem:
 *   1. Scan PCI for USB controllers
 *   2. Print a summary
 *   3. Enable bus mastering on each controller
 *   4. Reset and stop each UHCI controller
 */
void usb_init(void)
{
    char buf[32];

    serial_puts("[USB] Initializing USB subsystem...\n");
    vga_puts("[USB] Initializing USB subsystem...\n");

    int count = usb_scan_controllers();
    itoa(count, buf, 10);

    serial_puts("[USB] Found ");
    serial_puts(buf);
    serial_puts(" USB controller(s)\n");
    vga_puts("[USB] Found ");
    vga_puts(buf);
    vga_puts(" USB controller(s)\n");

    /* Enable bus mastering on all USB controllers */
    for (int i = 0; i < count; i++) {
        pci_enable_bus_master(usb_controllers[i].pci_index);
    }

    /* Reset each UHCI controller via port I/O */
    for (int i = 0; i < count; i++) {
        usb_controller_t *uc = &usb_controllers[i];

        if (uc->type != USB_UHCI || uc->io_base == 0)
            continue;

        serial_puts("[USB]   UHCI controller ");
        itoa(i, buf, 10); serial_puts(buf);
        serial_puts(" at I/O 0x");
        itoa(uc->io_base, buf, 16); serial_puts(buf);
        serial_puts("\n");

        /* HCRESET (USBCMD bit 1 = 1) */
        outw(uc->io_base + UHCI_USBCMD, 0x0002);
        io_wait();

        /* Wait for reset to complete */
        for (volatile int d = 0; d < 1000; d++)
            io_wait();

        /* Clear command register */
        outw(uc->io_base + UHCI_USBCMD, 0x0000);
        io_wait();

        serial_puts("[USB]     UHCI ready\n");
    }

    /* Print the full controller inventory */
    usb_print_controllers();

    serial_puts("[USB] USB subsystem initialized\n");
    vga_puts("[USB] USB subsystem initialized\n");
}

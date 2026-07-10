/* BYO-OS VBE (VESA BIOS Extensions) - x86_64 */
#include <kernel.h>

/* ========================================================================
 * VBE Data Structures (packed, as returned by VBE INT 0x10)
 * ======================================================================== */

/* VBE Controller Info Block (AX=0x4F00) */
typedef struct {
    char     signature[4];          /* "VESA" */
    uint16_t version;               /* BCD version (e.g. 0x0300 = 3.0) */
    uint32_t oem_string_ptr;        /* Far pointer to OEM vendor string */
    uint32_t capabilities;          /* Capability flags */
    uint32_t video_mode_ptr;        /* Far pointer to video-mode list */
    uint16_t total_memory;          /* Number of 64 KB blocks */
    /* VBE 2.0+ */
    uint16_t oem_software_rev;      /* OEM software revision number */
    uint32_t oem_vendor_name_ptr;   /* Far pointer to vendor name string */
    uint32_t oem_product_name_ptr;  /* Far pointer to product name string */
    uint32_t oem_product_rev_ptr;   /* Far pointer to product revision string */
    uint8_t  reserved[222];         /* Reserved for VBE implementation */
    uint8_t  oem_data[256];         /* Scratch area for OEM strings */
} __attribute__((packed)) vbe_controller_info_t;

/* VBE Mode Info Block (AX=0x4F01) */
typedef struct {
    uint16_t attributes;            /* Mode attributes */
    uint8_t  win_a_attributes;      /* Window A attributes */
    uint8_t  win_b_attributes;      /* Window B attributes */
    uint16_t win_granularity;       /* Window granularity (KB) */
    uint16_t win_size;              /* Window size (KB) */
    uint16_t win_a_segment;         /* Window A start segment */
    uint16_t win_b_segment;         /* Window B start segment */
    uint32_t win_func_ptr;          /* Far pointer to window function */
    uint16_t pitch;                 /* Bytes per scan line */
    uint16_t width;                 /* Horizontal resolution */
    uint16_t height;                /* Vertical resolution */
    uint8_t  w_char;                /* Character cell width (pixels) */
    uint8_t  y_char;                /* Character cell height (pixels) */
    uint8_t  planes;                /* Number of memory planes */
    uint8_t  bpp;                   /* Bits per pixel */
    uint8_t  banks;                 /* Number of banks */
    uint8_t  memory_model;          /* Memory model type */
    uint8_t  bank_size;             /* Bank size (KB) */
    uint8_t  image_pages;           /* Number of image pages */
    uint8_t  reserved1;             /* Reserved */
    uint8_t  red_mask_size;         /* Size of red mask (bits) */
    uint8_t  red_field_position;    /* Bit position of LSB of red field */
    uint8_t  green_mask_size;       /* Size of green mask (bits) */
    uint8_t  green_field_position;  /* Bit position of LSB of green field */
    uint8_t  blue_mask_size;        /* Size of blue mask (bits) */
    uint8_t  blue_field_position;   /* Bit position of LSB of blue field */
    uint8_t  rsvd_mask_size;        /* Size of reserved mask (bits) */
    uint8_t  rsvd_field_position;   /* Bit position of LSB of reserved field */
    uint8_t  direct_color_mode_info;/* Direct color mode attributes */
    /* VBE 2.0+ */
    uint32_t phys_base_ptr;         /* Physical address of linear framebuffer */
    uint32_t reserved2;             /* Reserved (was off-screen mem offset) */
    uint16_t reserved3;             /* Reserved (was off-screen mem size) */
    /* VBE 3.0+ */
    uint16_t lin_bytes_per_scan_line;
    uint8_t  bnk_image_pages;
    uint8_t  lin_image_pages;
    uint8_t  lin_red_mask_size;
    uint8_t  lin_red_field_position;
    uint8_t  lin_green_mask_size;
    uint8_t  lin_green_field_position;
    uint8_t  lin_blue_mask_size;
    uint8_t  lin_blue_field_position;
    uint8_t  lin_rsvd_mask_size;
    uint8_t  lin_rsvd_field_position;
    uint32_t max_pixel_clock;       /* Maximum pixel clock (Hz) */
    uint8_t  reserved4[190];        /* Reserved for future VBE versions */
} __attribute__((packed)) vbe_mode_info_t;

/* ========================================================================
 * VBE Return Codes
 * ======================================================================== */
#define VBE_SUCCESS     0x004F   /* Call succeeded */
#define VBE_FAIL        0x014F   /* Call failed */
#define VBE_UNSUPPORTED 0x024F   /* Function not supported */
#define VBE_INVALID     0x034F   /* Invalid mode number */

/* ========================================================================
 * Internal State
 * ======================================================================== */

/* Framebuffer state */
static volatile uint32_t* vbe_fb       = 0;  /* Typed pointer for 32-bit writes */
static uint64_t           vbe_fb_addr  = 0;  /* Physical address of framebuffer */
static uint16_t           vbe_fb_width = 0;  /* Visible width (pixels) */
static uint16_t           vbe_fb_height= 0;  /* Visible height (pixels) */
static uint16_t           vbe_fb_pitch = 0;  /* Bytes per scan line */
static uint8_t            vbe_fb_bpp   = 32; /* Bits per pixel */
static uint16_t           vbe_cur_mode = 0;  /* Current VBE mode number */
static int                vbe_enabled  = 0;  /* Is VBE active? */

/* Simulated framebuffer -- used when no real framebuffer is available.
 * 4 MB is enough for 1024x768x32bpp (3 MB). */
#define VBE_SIM_FB_SIZE  (4U * 1024U * 1024U)
static uint32_t __attribute__((aligned(4096))) vbe_sim_fb[VBE_SIM_FB_SIZE / 4];

/* Known VBE mode numbers (requirement: 0x101/0x103/0x105) */
#define VBE_MODE_640x480   0x101
#define VBE_MODE_800x600   0x103
#define VBE_MODE_1024x768  0x105

/* ========================================================================
 * Helper: translate a VBE mode number into resolution and colour depth.
 * Returns 1 on success, 0 if the mode is unknown.
 * ======================================================================== */
static int vbe_mode_to_res(uint16_t mode, uint16_t* w, uint16_t* h, uint8_t* bpp)
{
    switch (mode) {
    case VBE_MODE_640x480:   *w = 640;  *h = 480;  *bpp = 32; return 1;
    case VBE_MODE_800x600:   *w = 800;  *h = 600;  *bpp = 32; return 1;
    case VBE_MODE_1024x768:  *w = 1024; *h = 768;  *bpp = 32; return 1;
    case 0x110:              *w = 640;  *h = 480;  *bpp = 32; return 1;
    case 0x113:              *w = 800;  *h = 600;  *bpp = 32; return 1;
    case 0x116:              *w = 1024; *h = 768;  *bpp = 32; return 1;
    default:
        return 0;
    }
}

/* ========================================================================
 * vbe_init  --  Detect / simulate VBE support and set up internal state.
 *
 * In a real system this would examine the Multiboot info block or probe
 * the VBE BIOS interrupt directly.  Because BYO-OS runs in long mode we
 * cannot call INT 0x10, so we simulate the presence of VBE:
 *
 *   - If a framebuffer is available through vga_get_framebuffer(), use it.
 *   - Otherwise use an internal static buffer as the "framebuffer".
 *
 * Returns 1 on success, 0 on failure.
 * ======================================================================== */
int vbe_init(void)
{
    uint8_t* vga_fb;

    serial_puts("[VBE] Initialising VBE (VESA BIOS Extensions)...\n");

    /* Try to obtain a real framebuffer from the VGA layer */
    vga_fb = vga_get_framebuffer();
    if (vga_fb) {
        vbe_fb_addr = (uint64_t)(uintptr_t)vga_fb;
        vbe_fb      = (volatile uint32_t*)vga_fb;
        vbe_fb_width  = vga_get_width();
        vbe_fb_height = vga_get_height();
        vbe_fb_pitch  = vga_get_pitch();
        if (vbe_fb_width == 0)  vbe_fb_width  = 640;
        if (vbe_fb_height == 0) vbe_fb_height = 480;
        if (vbe_fb_pitch == 0)  vbe_fb_pitch  = vbe_fb_width * 4;
        serial_puts("[VBE] Using VGA framebuffer at ");
        serial_put_hex((uint32_t)vbe_fb_addr);
        serial_puts("\n");
    } else {
        /* No real framebuffer -- use simulated buffer */
        vbe_fb_addr = (uint64_t)(uintptr_t)vbe_sim_fb;
        vbe_fb      = (volatile uint32_t*)vbe_sim_fb;
        vbe_fb_width  = 640;
        vbe_fb_height = 480;
        vbe_fb_pitch  = 640 * 4;  /* 2560 bytes per scan line */
        vbe_fb_bpp    = 32;

        serial_puts("[VBE] No VGA framebuffer -- using simulated buffer at ");
        serial_put_hex((uint32_t)vbe_fb_addr);
        serial_puts("\n");
    }

    vbe_enabled  = 1;
    vbe_cur_mode = 0;

    /* Clear the framebuffer */
    memset((void*)vbe_fb, 0, vbe_fb_height * vbe_fb_pitch);

    vga_puts("[VBE] VBE initialised (");
    vga_put_dec(vbe_fb_width);
    vga_puts("x");
    vga_put_dec(vbe_fb_height);
    vga_puts("x");
    vga_put_dec(vbe_fb_bpp);
    vga_puts(")\n");

    serial_puts("[VBE] Init complete\n");
    return 1;
}

/* ========================================================================
 * vbe_set_mode  --  Set a VBE video mode (simulated INT 0x10, AX=0x4F02).
 *
 * Sets up the internal framebuffer state to match the requested mode.
 * Does NOT touch real VGA/VBE hardware registers (long-mode simulation).
 *
 * Returns VBE_SUCCESS (0x004F) on success, VBE_INVALID (0x034F) if the
 * mode is not recognised.
 * ======================================================================== */
int vbe_set_mode(uint16_t mode)
{
    uint16_t w, h;
    uint8_t  bpp;

    if (!vbe_enabled) {
        serial_puts("[VBE] vbe_set_mode called but VBE not initialised\n");
        return VBE_FAIL;
    }

    if (!vbe_mode_to_res(mode, &w, &h, &bpp)) {
        serial_puts("[VBE] Unknown mode 0x");
        serial_put_hex(mode);
        serial_puts("\n");
        return VBE_INVALID;
    }

    vbe_fb_width   = w;
    vbe_fb_height  = h;
    vbe_fb_bpp     = bpp;
    vbe_fb_pitch   = w * (bpp / 8);
    vbe_cur_mode   = mode;

    /* Clear the new framebuffer area */
    memset((void*)vbe_fb, 0, (size_t)vbe_fb_height * vbe_fb_pitch);

    serial_puts("[VBE] Mode set: 0x");
    serial_put_hex(mode);
    serial_puts(" = ");
    serial_put_dec(w);
    serial_puts("x");
    serial_put_dec(h);
    serial_puts("x");
    serial_put_dec(bpp);
    serial_puts("\n");

    return VBE_SUCCESS;
}

/* ========================================================================
 * vbe_get_mode_info  --  Fill a vbe_mode_info_t structure with info about
 *                         the given mode (simulated INT 0x10, AX=0x4F01).
 *
 * Returns VBE_SUCCESS on success, VBE_INVALID if the mode is unknown.
 * ======================================================================== */
int vbe_get_mode_info(uint16_t mode, void* info)
{
    vbe_mode_info_t* mi = (vbe_mode_info_t*)info;
    uint16_t w, h;
    uint8_t  bpp;

    if (!info) return VBE_FAIL;
    if (!vbe_mode_to_res(mode, &w, &h, &bpp)) return VBE_INVALID;

    memset(mi, 0, sizeof(vbe_mode_info_t));

    /* Mode attributes:
     *   bit 0 = supported
     *   bit 1 = extended info available
     *   bit 2 = BIOS output supported
     *   bit 3 = colour (not monochrome)
     *   bit 4 = graphics mode (not text)
     *   bit 5 = VGA compatible
     *   bit 6 = windowed memory available
     *   bit 7 = linear framebuffer available
     */
    mi->attributes        = 0x00EF;

    mi->win_a_attributes  = 0x07;
    mi->win_b_attributes  = 0x00;
    mi->win_granularity   = 64;
    mi->win_size          = 64;
    mi->win_a_segment     = 0xA000;
    mi->win_b_segment     = 0x0000;
    mi->win_func_ptr      = 0;

    /* Resolution and pitch */
    mi->width             = w;
    mi->height            = h;
    mi->bpp               = bpp;
    mi->pitch             = w * (bpp / 8);
    mi->planes            = 1;
    mi->banks             = 1;

    /* Memory model: 0x06 = Direct Color */
    mi->memory_model      = 0x06;
    mi->bank_size         = 0;

    /* Character cell -- 8x8 is our standard font */
    mi->w_char            = 8;
    mi->y_char            = 8;

    mi->image_pages       = 1;

    /* 32-bpp direct-color masks: R=8, G=8, B=8, A=8.
     * Little-endian layout: blue @ bits 0-7, green @ 8-15, red @ 16-23,
     * reserved/alpha @ 24-31. */
    mi->red_mask_size     = 8;
    mi->red_field_position= 16;
    mi->green_mask_size   = 8;
    mi->green_field_position = 8;
    mi->blue_mask_size    = 8;
    mi->blue_field_position  = 0;
    mi->rsvd_mask_size    = 8;
    mi->rsvd_field_position = 24;

    /* Linear framebuffer physical address */
    mi->phys_base_ptr     = (uint32_t)(uintptr_t)vbe_sim_fb;

    /* VBE 3.0 linear mode info */
    mi->lin_bytes_per_scan_line = w * (bpp / 8);
    mi->lin_image_pages         = 1;
    mi->lin_red_mask_size        = 8;
    mi->lin_red_field_position   = 16;
    mi->lin_green_mask_size      = 8;
    mi->lin_green_field_position = 8;
    mi->lin_blue_mask_size       = 8;
    mi->lin_blue_field_position  = 0;
    mi->lin_rsvd_mask_size       = 8;
    mi->lin_rsvd_field_position  = 24;
    mi->max_pixel_clock          = 40000000;  /* 40 MHz */

    serial_puts("[VBE] Mode info returned for 0x");
    serial_put_hex(mode);
    serial_puts("\n");

    return VBE_SUCCESS;
}

/* ========================================================================
 * vbe_get_controller_info  --  Fill a vbe_controller_info_t with VBE
 *                               controller capabilities (simulated INT 0x10,
 *                               AX=0x4F00).
 *
 * Returns VBE_SUCCESS always.
 * ======================================================================== */
int vbe_get_controller_info(void* info)
{
    vbe_controller_info_t* ci = (vbe_controller_info_t*)info;

    if (!info) return VBE_FAIL;

    memset(ci, 0, sizeof(vbe_controller_info_t));

    ci->signature[0] = 'V';
    ci->signature[1] = 'E';
    ci->signature[2] = 'S';
    ci->signature[3] = 'A';
    ci->version      = 0x0300;              /* VBE 3.0 */

    /* Far pointers set to zero -- we have no real VBE BIOS in long mode */
    ci->oem_string_ptr   = 0;
    ci->capabilities     = 0x00;
    ci->video_mode_ptr   = 0;
    ci->total_memory     = 16384 / 64;       /* Claim 16 MB video RAM */

    ci->oem_software_rev    = 1;
    ci->oem_vendor_name_ptr = 0;
    ci->oem_product_name_ptr= 0;
    ci->oem_product_rev_ptr = 0;

    serial_puts("[VBE] Controller info returned (VESA 3.0, simulated)\n");

    return VBE_SUCCESS;
}

/* ========================================================================
 * vbe_list_modes  --  Print supported VBE modes to the console.
 * ======================================================================== */
void vbe_list_modes(void)
{
    vga_puts("[VBE] Supported video modes:\n");
    vga_puts("  0x101  640x480x32  (VBE_MODE_640x480)\n");
    vga_puts("  0x103  800x600x32  (VBE_MODE_800x600)\n");
    vga_puts("  0x105  1024x768x32 (VBE_MODE_1024x768)\n");

    serial_puts("[VBE] Supported video modes:\n");
    serial_puts("  0x101  640x480x32\n");
    serial_puts("  0x103  800x600x32\n");
    serial_puts("  0x105  1024x768x32\n");
}

/* ========================================================================
 * Convenience mode-setters
 * ======================================================================== */

int vbe_set_mode_1024x768(void)
{
    return vbe_set_mode(VBE_MODE_1024x768);
}

int vbe_set_mode_800x600(void)
{
    return vbe_set_mode(VBE_MODE_800x600);
}

int vbe_set_mode_640x480(void)
{
    return vbe_set_mode(VBE_MODE_640x480);
}

/* ========================================================================
 * vbe_putpixel  --  Draw a single 32-bit pixel at (x, y).
 *
 * The colour value is written as-is (typically 0x00RRGGBB, little-endian
 * byte order: BB GG RR 00).  Coordinates are clipped to the framebuffer.
 * ======================================================================== */
void vbe_putpixel(int x, int y, uint32_t color)
{
    if (!vbe_fb) return;
    if (x < 0 || (uint16_t)x >= vbe_fb_width) return;
    if (y < 0 || (uint16_t)y >= vbe_fb_height) return;

    vbe_fb[y * (vbe_fb_pitch / 4) + x] = color;
}

/* ========================================================================
 * vbe_fill_rect  --  Fill a (w x h) rectangle with a single colour.
 *                    Clips to framebuffer boundaries.
 * ======================================================================== */
void vbe_fill_rect(int x, int y, int w, int h, uint32_t color)
{
    int x0, y0, x1, y1, row, col;

    if (!vbe_fb) return;
    if (w <= 0 || h <= 0) return;

    /* Clip */
    x0 = (x < 0) ? 0 : x;
    y0 = (y < 0) ? 0 : y;
    x1 = x + w;
    y1 = y + h;
    if (x1 > (int)vbe_fb_width)  x1 = vbe_fb_width;
    if (y1 > (int)vbe_fb_height) y1 = vbe_fb_height;
    if (x0 >= x1 || y0 >= y1) return;

    for (row = y0; row < y1; row++) {
        uint32_t* line = (uint32_t*)((uint8_t*)vbe_fb + row * vbe_fb_pitch);
        for (col = x0; col < x1; col++) {
            line[col] = color;
        }
    }
}

/* ========================================================================
 * vbe_draw_char  --  Draw an 8x8 bitmap character at pixel position (x, y)
 *                    using the kernel's built-in font8x8 data.
 *
 *   c   -- ASCII character to draw
 *   fg  -- Foreground (pixel-on) colour
 *   bg  -- Background (pixel-off) colour
 * ======================================================================== */
void vbe_draw_char(int x, int y, char c, uint32_t fg, uint32_t bg)
{
    int row, col;
    const uint8_t* glyph;
    uint8_t bits;

    if (!vbe_fb) return;

    {
        unsigned int idx = (unsigned char)c;
        /* Assume font8x8 has at least 256 entries (standard VGA font).
         * If index is out of range, draw the background block. */
        if (idx >= 256) {
            vbe_fill_rect(x, y, 8, 8, bg);
            return;
        }
        glyph = font8x8[idx];
    }

    for (row = 0; row < 8; row++) {
        bits = glyph[row];
        for (col = 0; col < 8; col++) {
            int px = x + col;
            int py = y + row;
            if (px >= 0 && px < (int)vbe_fb_width &&
                py >= 0 && py < (int)vbe_fb_height) {
                uint32_t* p = (uint32_t*)((uint8_t*)vbe_fb + py * vbe_fb_pitch) + px;
                *p = (bits & (0x80 >> col)) ? fg : bg;
            }
        }
    }
}

/* ========================================================================
 * vbe_puts  --  Draw a null-terminated string at (x, y) using the 8x8
 *               font.  Foreground colour is used for pixels; background
 *               is transparent (black, 0).
 *
 * '\n' advances to the next line (y + 8); '\r' returns to original x.
 * ======================================================================== */
void vbe_puts(int x, int y, const char* s, uint32_t color)
{
    int cx = x;
    int cy = y;

    if (!s || !vbe_fb) return;

    while (*s) {
        if (*s == '\n') {
            cy += 8;
            cx  = x;
        } else if (*s == '\r') {
            cx = x;
        } else {
            vbe_draw_char(cx, cy, *s, color, 0);
            cx += 8;
        }
        s++;
    }
}

/* EOF: kernel/vbe.c */
/* ========================================================================
 * vbe_get_width  --  Return the current framebuffer width in pixels.
 * ======================================================================== */
uint32_t vbe_get_width(void)
{
    return (uint32_t)vbe_fb_width;
}

/* ========================================================================
 * vbe_get_height  --  Return the current framebuffer height in pixels.
 * ======================================================================== */
uint32_t vbe_get_height(void)
{
    return (uint32_t)vbe_fb_height;
}

/* ========================================================================
 * vbe_get_bpp  --  Return the current bits-per-pixel value.
 * ======================================================================== */
uint32_t vbe_get_bpp(void)
{
    return (uint32_t)vbe_fb_bpp;
}

/* ========================================================================
 * vbe_get_framebuffer  --  Return a pointer to the current framebuffer.
 * ======================================================================== */
void* vbe_get_framebuffer(void)
{
    return (void*)vbe_fb;
}

/* ========================================================================
 * vbe_is_active  --  Return non-zero if VBE has been initialised.
 * ======================================================================== */
int vbe_is_active(void)
{
    return vbe_enabled;
}

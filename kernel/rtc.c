/* BYO-OS - CMOS/RTC Driver (x86_64) */
#include <kernel.h>

#define CMOS_ADDR 0x70
#define CMOS_DATA 0x71
#define CMOS_SECOND 0x00
#define CMOS_MINUTE 0x02
#define CMOS_HOUR 0x04
#define CMOS_DAY 0x07
#define CMOS_MONTH 0x08
#define CMOS_YEAR 0x09
#define CMOS_STATUS_A 0x0A
#define CMOS_STATUS_B 0x0B

static int rtc_hour = 12, rtc_min = 0, rtc_sec = 0;
static int rtc_day = 1, rtc_mon = 1, rtc_year = 2024;
static int rtc_initialized = 0;

static uint8_t cmos_read(uint8_t reg) {
    outb(CMOS_ADDR, reg);
    io_wait();
    return inb(CMOS_DATA);
}

static int cmos_is_updating(void) {
    outb(CMOS_ADDR, CMOS_STATUS_A);
    return inb(CMOS_DATA) & 0x80;
}

static int bcd_to_bin(uint8_t bcd) {
    return (bcd & 0x0F) + ((bcd >> 4) * 10);
}

static void rtc_read(void) {
    /* Wait for update to finish */
    int timeout = 100000;
    while (cmos_is_updating() && timeout--) {
        for (volatile int i = 0; i < 10; i++);
    }

    uint8_t second = cmos_read(CMOS_SECOND);
    uint8_t minute = cmos_read(CMOS_MINUTE);
    uint8_t hour = cmos_read(CMOS_HOUR);
    uint8_t day = cmos_read(CMOS_DAY);
    uint8_t month = cmos_read(CMOS_MONTH);
    uint8_t year = cmos_read(CMOS_YEAR);
    uint8_t status_b = cmos_read(CMOS_STATUS_B);

    /* Convert from BCD if needed */
    if (!(status_b & 0x04)) {
        second = bcd_to_bin(second);
        minute = bcd_to_bin(minute);
        hour = bcd_to_bin(hour & 0x7F);
        day = bcd_to_bin(day);
        month = bcd_to_bin(month);
        year = bcd_to_bin(year);
    }

    /* Handle 12-hour mode */
    if (!(status_b & 0x02)) {
        hour = (hour & 0x7F) + ((hour & 0x80) ? 12 : 0);
    }

    rtc_sec = second;
    rtc_min = minute;
    rtc_hour = hour;
    rtc_day = day;
    rtc_mon = month;
    rtc_year = 2000 + year;
    rtc_initialized = 1;
}

void rtc_init(void) {
    rtc_read();
    serial_puts("[RTC] Real-time clock initialized\n");

    char buf[32];
    itoa(rtc_year, buf, 10);
    serial_puts("[RTC] Date: "); serial_puts(buf); serial_puts("-");
    itoa(rtc_mon, buf, 10); serial_puts(buf); serial_puts("-");
    itoa(rtc_day, buf, 10); serial_puts(buf); serial_puts(" ");
    itoa(rtc_hour, buf, 10); serial_puts(buf); serial_puts(":");
    itoa(rtc_min, buf, 10); serial_puts(buf); serial_puts("\n");

    vga_puts("[RTC] ");
    itoa(rtc_year, buf, 10); vga_puts(buf); vga_putchar('-');
    itoa(rtc_mon, buf, 10); vga_puts(buf); vga_putchar('-');
    itoa(rtc_day, buf, 10); vga_puts(buf); vga_putchar(' ');
    itoa(rtc_hour, buf, 10); vga_puts(buf); vga_putchar(':');
    itoa(rtc_min, buf, 10); vga_puts(buf); vga_putchar('\n');
}

void rtc_get_time(int* hour, int* min, int* sec) {
    if (!rtc_initialized) rtc_read();
    else {
        /* Increment a fake second for demo (real RTC would read again) */
        static uint32_t last_tick = 0;
        uint32_t now = timer_get_ticks();
        if (now - last_tick > 18) { /* ~1 second at 18.2 Hz PIT */
            last_tick = now;
            rtc_sec++;
            if (rtc_sec >= 60) { rtc_sec = 0; rtc_min++; }
            if (rtc_min >= 60) { rtc_min = 0; rtc_hour++; }
            if (rtc_hour >= 24) { rtc_hour = 0; }
        }
    }
    if (hour) *hour = rtc_hour;
    if (min) *min = rtc_min;
    if (sec) *sec = rtc_sec;
}

void rtc_get_date(int* year, int* mon, int* day) {
    if (!rtc_initialized) rtc_read();
    if (year) *year = rtc_year;
    if (mon) *mon = rtc_mon;
    if (day) *day = rtc_day;
}

int rtc_is_initialized(void) { return rtc_initialized; }

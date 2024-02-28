#include "rtc.h"
#include "tty.h"
#include "stdio.h"
#include "io.h"
#include "vga.h"
#include "string.h"

bool cmos_update()
{
    outb(CMOS_BASE, 0x0A);

    return inb(CMOS_DATA) & 0x80;
}

unsigned char rtc_register(uint8_t rtc_reg)
{
    outb(CMOS_BASE, rtc_reg);

    return inb(CMOS_DATA);
}

void rtc_callback()
{
    unsigned char day;
    unsigned char hour;
    unsigned char minute;
    unsigned char month;

    minute = rtc_register(MINUTE);
    day = rtc_register(DAY);
    hour = rtc_register(HOUR);
    month = rtc_register(MONTH);

    bool regb = rtc_register(0x0B) & 0x04;

    if (!regb) {
        minute = (minute & 0x0F) + ((minute / 16) * 10);
        hour = ( (hour & 0x0F) + (((hour & 0x70) / 16) * 10) ) | (hour & 0x80);
        day = (day & 0x0F) + ((day / 16) * 10);
        month = (month & 0x0F) + ((month / 16) * 10);
    }

    char* minbuf;
    char* hourbuf;
    char* daybuf;
    char* monthbuf;

    itoa(minute, minbuf, DECIMAL);
    itoa(hour, hourbuf, DECIMAL);
    itoa(day, daybuf, DECIMAL);
    itoa(month, monthbuf, DECIMAL);

    // char* outbuf;

    // vga_setbar(VGA_COLOR_WHITE, VGA_COLOR_DARK_GREY, outbuf, 30);
}

void rtc_init()
{
    // register_interrupt_handler(IRQ8, rtc_callback);

    // outb(0x70, 0x8A);	// select Status Register A, and disable NMI (by setting the 0x80 bit)
    // outb(0x71, 0x20);	// write to CMOS/RTC RAM

    BOOT_LOG("RTC initialized.");
}

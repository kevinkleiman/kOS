#include "rtc.h"
#include "interrupt.h"
#include "tty.h"
#include "stdio.h"
#include "io.h"

void rtc_callback()
{
    printf("rtc callback\n");

    bool update = true;

    while(update) {
        outb(RTC_BASE, 0xA);
        unsigned char c = inb(RTC_DATA);

        if(!(c & 0x80)) {
            update = false;
        }
    }

    // outb(RTC_BASE, 0);
    // unsigned char sec = inb(RTC_DATA);
    // 
    // outb(RTC_BASE, 2);
    // unsigned char min = inb(RTC_DATA);

    // outb(RTC_BASE, 4);
    // unsigned char hour = inb(RTC_DATA);

    // outb(RTC_BASE, 7);
    // unsigned char day = inb(RTC_DATA);

    // outb(RTC_BASE, 8);
    // unsigned char month = inb(RTC_DATA);

    // outb(RTC_BASE, 9);
    // unsigned char year = inb(RTC_DATA);

    // outb(RTC_BASE, 0xB);
    // unsigned char format = inb(RTC_DATA);

    // tty_write(&sec);

    // printf("sec: %c, min: %c, hour: %c, day: %c, month: %c, year: %c, format: %c", sec, min, hour, day, month, year, format);
}

void rtc_init()
{
    register_interrupt_handler(IRQ8, rtc_callback);

    outb(0x70, 0x8A);	// select Status Register A, and disable NMI (by setting the 0x80 bit)
    outb(0x71, 0x20);	// write to CMOS/RTC RAM

    BOOT_LOG("RTC initialized.");
}

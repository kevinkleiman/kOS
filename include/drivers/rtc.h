#pragma once

#define CMOS_BASE 0x70
#define CMOS_DATA 0x71

#define SECOND  0x00
#define MINUTE  0x02
#define HOUR    0x04
#define WEEKDAY 0x06
#define DAY     0x07
#define MONTH   0x08
#define YEAR    0x09

void rtc_init();
void rtc_callback();

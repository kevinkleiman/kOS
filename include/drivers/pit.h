#pragma once

#include "interrupt.h"

#define RELOAD 1000
#define FREQUENCY 1193180   // 1.193180 Mhz

#define PIT_COMMAND 0x43
#define PIT_CHANNEL0 0x40
#define PIT_CHANNEL1 0x41
#define PIT_CHANNEL2 0x42

void pit_callback(i_register_t registers);
void pit_init();
void sleep(uint32_t millis);
void poll();

#include "pit.h"
#include "tty.h"
#include "io.h"

/* Initialize count down for sleep function */
static volatile uint32_t count_down;

/* Decrement counter on clock edge */
void pit_callback(__attribute__((unused)) i_register_t registers)
{
    count_down -= 1;
}

/* Global kernel sleep function, sleep for x milliseconds */
void sleep(uint32_t millis)
{
    count_down = millis;

    while (count_down > 0);
}

void pit_init()
{
    // set divisor for channel 0
    uint32_t divisor = FREQUENCY/RELOAD;

    register_interrupt_handler(IRQ0, pit_callback);

    // select square wave generator
    outb(PIT_COMMAND, 0x36);
    outb(PIT_CHANNEL0, (uint8_t) (divisor & 0xFF));
    outb(PIT_CHANNEL0, (uint8_t) ((divisor >> 8) & 0xFF));

    BOOT_LOG("PIT initialized.")
}

#include "keyboard.h"
#include "idt.h"
#include "tty.h"


static void keyboard_callback(irt_register_t* registers) {
    tty_write("\nKey pressed!");
}

void keyboard_init() {
   register_interrupt_handler(IRQ1, keyboard_callback);
}

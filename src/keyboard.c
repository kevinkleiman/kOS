#include "keyboard.h"
#include "tty.h"

static void keyboard_callback(i_register_t registers) {
    tty_write("Key pressed!\n");
}

void keyboard_init() {
   register_interrupt_handler(IRQ1, keyboard_callback);
   tty_write("Init keyboard.\n");
}

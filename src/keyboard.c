#include "keyboard.h"
#include "tty.h"
#include "io.h"

static void keyboard_callback(i_register_t registers) {
    unsigned char key = inb(0x60);
    tty_write("Key pressed!\n");
}

void keyboard_init() {
    register_interrupt_handler(IRQ1, keyboard_callback);

    BOOT_LOG("Keyboard initialized.")
}

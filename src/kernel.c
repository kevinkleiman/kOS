#include <stdbool.h>
#include "tty.h"
#include "gdt.h"
#include "stdio.h"
#include "keyboard.h"
 
void kernel_main(void) {
    tty_init();
    gdt_init(); 
    idt_init();
    keyboard_init();

    tty_welcome();

    for(;;);
}

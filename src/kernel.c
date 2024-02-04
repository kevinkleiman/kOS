#include <stdbool.h>
#include "tty.h"
#include "gdt.h"
#include "idt.h"
#include "keyboard.h"
 
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
void kernel_main(void) 
{
    tty_init();
    gdt_init(); 
    idt_init();
    keyboard_init();

    tty_welcome();

    for(;;);
}

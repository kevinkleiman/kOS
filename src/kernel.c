#include <stdbool.h>
#include "tty.h"
#include "gdt.h"
#include "idt.h"
#include "keyboard.h"
 
/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
void kernel_main(void) 
{
    tty_init();
    gdt_init(); 
    idt_init();
    keyboard_init();

    tty_write("\nWelcome to kOS!\n");

    if(are_interrupts_enabled()) tty_write("Enabled\n");
    else tty_write("Not enabled\n");
}

#include <stdbool.h>
#include "tty.h"
#include "gdt.h"
 
/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
void kernel_main(void) 
{
    gdt_init(); 
    tty_init();

    tty_write("Welcome to kOS!\n");
}

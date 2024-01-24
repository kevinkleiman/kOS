#include <stdbool.h>
#include "stdio.h"
#include "tty.h"
 
/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
void kernel_main(void) 
{
    tty_init();
    tty_write("Welcome to kOS!\n");
}

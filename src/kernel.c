#include <stdbool.h>
#include "tty.h"
#include "gdt.h"
#include "keyboard.h"
#include "syscall.h"
 
void kernel_main(void) 
{
    // init drivers and hardware
    tty_init();
    gdt_init(); 
    idt_init();
    keyboard_init();

    // init syscalls after interrupts setup
    syscall_init();

    // print ascii art welcome message
    tty_welcome();

    __asm__ __volatile__("movl $0, %eax; int $0x80");
    __asm__ __volatile__("movl $1, %eax; int $0x80");

    // hang, technically uneccessary due to
    // the way this is handled in boot.S
    for(;;);
}

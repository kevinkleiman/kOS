/**
 * 
 * @copyright Copyright (c) 2024, Kevin Kleiman, All Rights Reserved
 * 
 * This is a hobbyOS (kernel really) designed and developed by Kevin Kleiman.
 * Feel free to copy, use, edit, etc. anything you see 
 *
 * This was originally designed to try writing a ring0 math library but I soon realized,
 * I should just make a full-blown kernel. It has been a great learning experience and I
 * implore anyone even remotely interested to fork, play around, contribute, whatever
 * you want. 
 *
 * For now, it's pretty barebones and shitty, but hopefully that will change with time.
 * Have fun creating kOS (pronounced "Chaos")
 */

#include <stdbool.h>
#include "tty.h"
#include "gdt.h"
#include "keyboard.h"
#include "syscall.h"
#include "rtc.h"
#include "pit.h"

/* Kernel entry point (init hardware and drivers) */
void kernel_main(void) 
{
    // init drivers and hardware
    tty_init();
    gdt_init(); 
    idt_init();
    rtc_init();
    pit_init();
    keyboard_init();

    // init syscalls after interrupts setup
    syscall_init();

    sleep(1000);

    // testing syscalls
    // __asm__ __volatile__("movl %0, %%ecx" : : "r"(&k) : "memory");
    // __asm__ __volatile__("movl $1, %edx");
    // __asm__ __volatile__("movl $0, %eax; int $0x80");

    // print ascii art welcome message
    tty_welcome();
    
    
    // hang, technically uneccessary due to
    // the way this is handled in boot.S
    for(;;);
}

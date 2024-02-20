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
#include "multiboot.h"
#include "memory.h"


/* Kernel entry point (init hardware and drivers) */
void kernel_main(__attribute__((unused)) uint32_t magic, volatile multiboot_info_t* mbd) 
{
    // init drivers and hardware
    tty_init();

    // detect bootloader
    tty_writecolor("Booted with ", VGA_COLOR_CYAN, VGA_COLOR_BLACK);
    tty_writecolor((const char*) mbd->boot_loader_name, VGA_COLOR_CYAN, VGA_COLOR_BLACK);
    tty_write("\n\n");

    gdt_init(); 
    idt_init();
    rtc_init();
    pit_init();
    keyboard_init();

    // init memory map
    memory_init(mbd);

    // init syscalls after interrupts setup
    syscall_init();

    // print ascii art welcome message
    tty_welcome();

    // testing syscalls
    // __asm__ __volatile__("movl %0, %%ecx" : : "r"(&k) : "memory");
    // __asm__ __volatile__("movl $1, %edx");
    // __asm__ __volatile__("movl $0, %eax; int $0x80");
    
    // hang, technically uneccessary due to
    // the way this is handled in boot.S
    for(;;);
}

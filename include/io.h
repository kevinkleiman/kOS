#pragma once

#include <stdint.h>

#define KBRD_INTRFC 0x64
#define KBRD_RESET 0xFE

/*

Contains all I/O functions (some inline for optimization)

Some other useful assembly mappings to clear interrupts, set interrupts,
and halt cpu execution which are useful in many branches

*/

/* Reaad a byte from a word-sized port */
static inline uint8_t inb(uint16_t port) 
{
    uint8_t ret;

    __asm__ __volatile__( "inb %w1, %b0" : "=a"(ret) : "Nd"(port) : "memory" );

    return ret;
}

/* Write a byte to a word-sized port */
static inline void outb(uint16_t port, uint8_t byte) 
{
    __asm__ __volatile__( "outb %0, %1" : : "a"(byte), "Nd"(port) : "memory" );
}

/* Clear interrupts */
__attribute__((naked, used)) static void cli() 
{
    __asm__ __volatile__( "cli" );
}

/* Set (re-enable) interrupts */
__attribute__((naked, used)) static void sti() 
{
    __asm__ __volatile__( "sti" );
}

/* Halt all CPU execution and loop infinitely */
__attribute__((noreturn, used)) static void hlt() 
{
    __asm__ __volatile__( "hlt" );

    for(;;);
}

__attribute__((noreturn, used)) static void warm_reboot()
{
    // send cpu reset signal
    outb(KBRD_INTRFC, KBRD_RESET);

    // halt all execution
    hlt();
}

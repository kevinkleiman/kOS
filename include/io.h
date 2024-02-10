#pragma once

#include <stdint.h>

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
__attribute__((naked)) static void cli() 
{
    __asm__ __volatile__( "cli" );
}

/* Set (re-enable) interrupts */
__attribute__((naked)) static void sti() 
{
    __asm__ __volatile__( "sti" );
}

/* Halt all CPU execution and loop infinitely */
__attribute__((noreturn)) static void hlt() 
{
    __asm__ __volatile__( "hlt" );

    for(;;);
}

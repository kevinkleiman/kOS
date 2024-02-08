#pragma once

#include <stdint.h>

static inline uint8_t inb(uint16_t port) 
{
    uint8_t ret;

    __asm__ __volatile__( "inb %w1, %b0" : "=a"(ret) : "Nd"(port) : "memory" );

    return ret;
}

static inline void outb(uint16_t port, uint8_t byte) 
{
    __asm__ __volatile__( "outb %0, %1" : : "a"(byte), "Nd"(port) : "memory" );
}

__attribute__((noreturn)) static void hlt() 
{
    __asm__ __volatile__( "hlt" );

    for(;;);
}

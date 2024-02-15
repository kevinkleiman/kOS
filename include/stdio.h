#pragma once

#include <stddef.h>
#include <stdint.h>

#define DECIMAL 10
#define HEX 16
#define BINARY 2


char* itoa(int value, char* str, int base);
void* memset(void* dest, register int data, register size_t length);

void printf(const char* fmt, ...);
void panic(char* msg);

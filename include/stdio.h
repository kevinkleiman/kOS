#pragma once

#include <stddef.h>

#define DECIMAL 10
#define HEX 16
#define BINARY 2

char* itoa(int value, char* str, int base);
void printf(const char* fmt, ...);
void* memset(void* dest, register int data, register size_t length);
void panic(char* msg);

#pragma once

#include <stddef.h>

char* itoa(int i, char* buffer, int base);
void printf(const char* fmt, ...);
void* memset(void* dest, register int data, register size_t length);

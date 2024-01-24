#pragma once

#include <stddef.h>

void printf(const char* str, void* fmt);
void* memset(void* dest, register int data, register size_t length);

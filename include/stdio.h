#pragma once

#include <stddef.h>
#include <stdbool.h>

#define DECIMAL 10
#define HEX 16
#define BINARY 2


char* __itoa(int value, char* str, int base);
void* __memset(void* dest, register int data, register size_t length);

void __panic(char* msg);
void __puts(const char* str);

void kcli(char pkeybuffer[], size_t bufsize);
void printk(const char* fmt, ...);
void sprintk(const char* fmt, char* buffer, ...);

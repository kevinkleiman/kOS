#pragma once

#include <stddef.h>
#include <stdbool.h>

size_t strlen(const char* str);
void strcpy(char* dest, const char* src);
void strncpy(char* dest, const char* src, size_t n);
char* strcat(char* src, const char* append);
bool strcmp(const char* a, const char* b);

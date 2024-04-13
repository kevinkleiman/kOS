#pragma once

#include <stddef.h>
#include <stdbool.h>

size_t __strlen(const char* str);
void __strcpy(char* dest, const char* src);
void __strncpy(char* dest, const char* src, size_t n);
char* __strcat(char* src, const char* append);

bool __strcmp(const char* a, const char* b);

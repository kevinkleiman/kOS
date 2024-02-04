#include <stdbool.h>
#include "stdio.h"

char* itoa(int i, char* buffer, int base) {
    bool negative_flag; 
    int index = 0;

    if (i == 0) {
        buffer[index++] = '0';
        buffer[index] = '\0';
    }
    if (i < 0 && base == 10) {
        negative_flag = true;
        i = -i;
    }

    return "";
}

void printf(const char* fmt, ...) {}

void* memset(void* dest, register int data, register size_t length) {
    // Cast destination pointer to char pointer to dereference later
    unsigned char* ptr = (unsigned char*) dest;

    // Loop through each byte until end of data
    for (size_t i = 0; i < length; ++i) {
        // Set dereferenced destination to data at index
        *ptr++ = data;
    }

    // Return destination pointer
    return dest;
}

#include "stdio.h"

void printf(const char* str, void* fmt) {

}

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

#include "string.h"

size_t strlen(const char* str) 
{
    // Assume length at zero
    size_t length = 0;

    // Increment length when a character is present
    while(str[length])
        ++length;

    return length;
}

void strcpy(const char* src, char* dest) 
{
    // Pretty loosey goosey way of doing this but fuck it
    for (size_t i = 0; i < strlen(src); ++i) {
        dest[i] = src[i];
    }
}

bool strcmp(const char* a, const char* b) 
{
    // Cache length of a and b to save a bit of runtime
    size_t a_len = strlen(a);
    size_t b_len = strlen(b);

    // If lengths don't match, then strings are not the same
    if (a_len != b_len) return false;

    // Loop through each character and compare
    for (size_t i = 0; i < a_len; ++i) {
        if (a[i] == b[i]) continue;
        // Fail check if any are different
        return false;
    }

    return true;
}

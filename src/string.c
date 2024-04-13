#include "string.h"

size_t __strlen(const char* str) 
{
    // Assume length at zero
    size_t length = 0;

    // Increment length when a character is present
    while(str[length])
        ++length;

    return length;
}

void __strcpy(char* dest, const char* src) 
{
    // Pretty loosey goosey way of doing this but fuck it
    for (size_t i = 0; i < __strlen(src); ++i) {
        dest[i] = src[i];
    }
}

void __strncpy(char* dest, const char* src, size_t n) 
{
    // Pretty loosey goosey way of doing this but fuck it
    for (size_t i = 0; i < n; ++i) {
        if (src[i] != '\0') dest[i] = src[i];
    }
}

char* __strcat(char* dest, const char* append)
{
    // appends one string to another (concatination)
    char* save = dest;
    size_t i;

	for (; *dest; ++dest);
	while ((*dest++ = *append++)); 

	return save;
}

bool __strcmp(const char* a, const char* b) 
{
    // Cache length of a and b
    size_t a_len = __strlen(a);
    size_t b_len = __strlen(b);

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

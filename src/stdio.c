#include <stdbool.h>
#include <stdarg.h>
#include "stdio.h"
#include "io.h"
#include "tty.h"

char* itoa(int value, char* str, int base) 
{
    char* rc;
    char* ptr;
    char* low;

    // Check for supported base.
    if (base < 2 || base > 36) {
        *str = '\0';
        return str;
    }
    rc = ptr = str;
    // Set '-' for negative decimals.
    if (value < 0 && base == 10) *ptr++ = '-';
    // Remember where the numbers start.
    low = ptr;
    // The actual conversion.
    do {
        // Modulo is negative for negative value. This trick makes abs() unnecessary.
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + value % base];
        value /= base;
    } while (value);
    // Terminating the string.
    *ptr-- = '\0';
    // Invert the numbers.
    while (low < ptr) {
        char tmp = *low;

        *low++ = *ptr;
        *ptr-- = tmp;
    }

    return rc;
}

void printf(const char* fmt, ...) 
{
    va_list ap;
    char* buffer;
    char c;
    int i;

    va_start(ap, fmt);

    for(i = 0; (c = fmt[i] & 0xff) != 0; i++) {
        if (c != '%') {
            tty_write(&c);
            continue;
        }

        c = fmt[++i] & 0xff;

        if (c == 0) break;

        switch(c) {
            case 'd':
                itoa(va_arg(ap, int), buffer, DECIMAL);
                tty_write(buffer);
                break;
            case 'x':
                itoa(va_arg(ap, int), buffer, HEX);
                tty_write("0x");
                tty_write(buffer);
                break;
            case 'c':
                tty_write(&c);
                break;
            case 's':
                tty_write(va_arg(ap, char*));
                break;
            case '%':
                tty_write("%");
                break;
            default:
                tty_write("%");
                tty_write(&c);
                break;
        }
    }
}

void* memset(void* dest, register int data, register size_t length) 
{
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

__attribute__((noreturn)) void panic(char* msg)
{
    vga_setcolor(VGA_COLOR_RED, VGA_COLOR_BLACK);
    // generic error handler
    printf("Exception encountered! %s\n", msg);

    // halt all execution
    hlt();
}

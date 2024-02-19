#include <stdbool.h>
#include <stdarg.h>
#include "stdio.h"
#include "string.h"
#include "io.h"
#include "tty.h"
#include "vga.h"


/* Converts int to ascii representation (used for printing) */
char* itoa(int value, char* str, int base) 
{
    char* rc;
    char* ptr;
    char* low;

    unsigned int ucast;
    
    // store unsigned value for later
    ucast = value;

    // check for supported base.
    if (base < 2 || base > 36) {
        *str = '\0';
        return str;
    }

    rc = ptr = str;

    // set '-' for negative decimals.
    if (value < 0 && base == 10) *ptr++ = '-';

    // remember where the numbers start.
    low = ptr;

    do {
        // had to use this dirty trick for signed 32 bit integers
        if (base == HEX && value < 0) {
            *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + ucast % base];

            ucast /= base;
        } else {
            // modulo is negative for negative value. This trick makes abs() unnecessary.
            *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + value % base];

            value /= base;
        }
    } while (ucast && value);

    // terminating the string.
    *ptr-- = '\0';

    // invert the numbers.
    while (low < ptr) {
        char tmp = *low;

        *low++ = *ptr;
        *ptr-- = tmp;
    }

    return rc;
}

/* Kernel printf targeting tty output */
void printf(const char* fmt, ...) 
{
    // init args and string buffer
    va_list ap;
    char* buffer;
    char c;
    int i;

    va_start(ap, fmt);

    // loop through string
    for(i = 0; (c = fmt[i] & 0xff) != 0; i++) {
        // if token not found, write raw character
        if (c != '%') {
            tty_putc(c);
            continue;
        }

        // increment character pointer
        c = fmt[++i] & 0xff;

        // check for null termination
        if (c == 0) break;

        switch(c) {
            case 'd':
                // handle int to ascii conversion
                itoa(va_arg(ap, int), buffer, DECIMAL);

                // write filled buffer
                tty_write(buffer);
                break;
            case 'x':
                // handle hex conversion
                itoa(va_arg(ap, int), buffer, HEX);
                
                // write prefix "0x" with filled buffer
                tty_write("0x");
                tty_write(buffer);
                break;
            case 'c':
                // write character passed
                tty_write(&c);
                break;
            case 's':
                // convert arg to string (char*) and write to tty
                tty_write(va_arg(ap, char*));
                break;
            case '%':
                // handle double percent (i.e. printing a % symbol)
                tty_write("%");
                break;
            default:
                // otherwise, just write the fucking character
                tty_write("%");
                tty_write(&c);
                break;
        }
    }
}

/* Kernel memset, nearly identical to glibc implementation */
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

/* A very minimal, shitty cli for kernel ops */
void kcli(char pkeybuffer[], size_t bufsize)
{
   if (strcmp(pkeybuffer, "clear")) {
        tty_clear();
    } 

    tty_writecolor("> ", VGA_COLOR_LIGHT_BLUE, VGA_COLOR_BLACK);

    memset(pkeybuffer, 0, bufsize);
}

/* Kernel panic/exception handler, nothing fancy */
__attribute__((noreturn)) void panic(char* msg)
{
    vga_setcolor(VGA_COLOR_RED, VGA_COLOR_BLACK);
    // generic error handler
    printf("Exception encountered! %s\n", msg);

    // halt all execution
    hlt();
}

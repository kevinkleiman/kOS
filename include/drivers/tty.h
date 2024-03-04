#pragma once

#include <stddef.h>
#include "vga.h"

#define BOOT_LOG(msg) \
    tty_write("[ "); \
    tty_writecolor("OK", VGA_COLOR_GREEN, VGA_COLOR_BLACK); \
    tty_write(" ] "); \
    tty_write(msg); \
    tty_write("\n");

typedef struct {
    size_t      row;
    size_t      col;

    vga_color_t fgcolor;
    vga_color_t bgcolor;
} tty_state_t;

void tty_init();
void tty_write(const char* str);
void tty_writecolor(const char* str, vga_color_t fg, vga_color_t bg);
void tty_putc(char c);
void tty_clear();
void tty_setcolor(vga_color_t fg, vga_color_t bg);
void tty_welcome();

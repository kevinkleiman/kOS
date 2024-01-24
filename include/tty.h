#pragma once

#include <stddef.h>
#include "vga.h"

typedef struct {
    size_t tty_row;
    size_t tty_col;

    enum vga_color tty_fg_color;
    enum vga_color tty_bg_color;
} tty_state_t;

void tty_init();
void tty_write(const char* str);
void tty_putc(char c);
void tty_set_color(enum vga_color color);

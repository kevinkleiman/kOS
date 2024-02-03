#pragma once

#include <stddef.h>
#include "vga.h"

#define BOOT_LOG(msg) \
    tty_write("[BOOT] "); \
    tty_write(msg); \
    tty_write("\n");

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

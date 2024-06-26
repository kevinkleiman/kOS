/**
 * 
 * @copyright Copyright (c) 2024, Kevin Kleiman, All Rights Reserved
 * 
 * This is the kernel for yet another hobbyOS designed and developed by Kevin Kleiman.
 * Feel free to copy, use, edit, etc. anything you see 
 *
 * This was originally designed to try writing a ring0 math library but I soon realized,
 * I should just make a full-blown kernel. It has been a great learning experience and I
 * implore anyone even remotely interested to fork, play around, contribute, whatever
 * you want. 
 *
 * For now, it's pretty barebones and shitty, but hopefully that will change with time.
 * Have fun creating kOS (pronounced "Chaos")
 */

#pragma once

#include <stdint.h>
#include <stddef.h>


/* Define vga dimensions and base address */
#define VGA_BASE 0xB8000
#define VGA_HEIGHT 25
#define VGA_WIDTH 80

/* Hardware text mode color constants */
typedef enum {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
} vga_color_t;

typedef struct {
    uint8_t x;
    uint8_t y;
} cursor_pos_t;

static inline uint8_t vga_entry_color(vga_color_t fg, vga_color_t bg) 
{
	return fg | bg << 4;
}
 
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

void vga_setcolor(vga_color_t fg, vga_color_t bg);
void vga_init();
void vga_putc(char c, size_t row, size_t col);
void vga_scroll();
void vga_setbar(vga_color_t fg, vga_color_t bg, const char* str, size_t offset);
void vga_clear();
void vga_cursor_disable();
void vga_cursor_enable(uint8_t start, uint8_t end);
void vga_update_cursor(int x, int y);

cursor_pos_t vga_get_cursor_position();

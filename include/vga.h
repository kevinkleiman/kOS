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
void vga_clear();

cursor_pos_t get_cursor_position();

#include "vga.h"

uint16_t g_vga_color;

void vga_setcolor(vga_color_t fg, vga_color_t bg) {
    g_vga_color = vga_entry_color(fg, bg);
}

void vga_init() {
    vga_clear();
}

void vga_putc(char c, size_t row, size_t col) {
    uint16_t* vga_buffer = (uint16_t*) VGA_BASE;
    
    const size_t index = row * VGA_WIDTH + col;
    vga_buffer[index] = vga_entry(c, g_vga_color);
}

void vga_clear() {
    uint16_t* vga_buffer = (uint16_t*) VGA_BASE;

    for (size_t i = 0; i < VGA_HEIGHT; ++i) {
        for (size_t j = 0; j < VGA_WIDTH; ++j) {
            const uint16_t index = i * VGA_WIDTH + j;

            vga_buffer[index] = vga_entry(' ', g_vga_color);
        }
    }
}

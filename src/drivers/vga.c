#include "vga.h"
#include "io.h"

static uint16_t g_vga_color;

/* Sets color entry for VGA buffer */
void vga_setcolor(vga_color_t fg, vga_color_t bg) 
{
    g_vga_color = vga_entry_color(fg, bg);
}

/* For now, just clear the screen on init (also sets default color) */
void vga_init() 
{
    vga_clear();
}

/* Puts a character into the VGA buffer at row, col */
void vga_putc(char c, size_t row, size_t col) 
{
    uint16_t* vga_buffer = (uint16_t*) VGA_BASE;
    
    const size_t index = row * VGA_WIDTH + col;
    vga_buffer[index] = vga_entry(c, g_vga_color);
}

/* Shift VGA buffer one column down */
void vga_scroll()
{
    uint16_t* vga_buffer = (uint16_t*) VGA_BASE;

    for (int row = 1; row < VGA_HEIGHT; row++) {
        for (int col = 0; col < VGA_WIDTH; col++) {
            size_t index = row * VGA_WIDTH + col;
            size_t scroll_index = (row - 1) * VGA_WIDTH + col;

            uint16_t entry = vga_buffer[index];

            vga_buffer[scroll_index] = entry;
        }
    }
}

/* Clear VGA buffer */
void vga_clear() 
{
    uint16_t* vga_buffer = (uint16_t*) VGA_BASE;

    for (size_t i = 0; i < VGA_HEIGHT; ++i) {
        for (size_t j = 0; j < VGA_WIDTH; ++j) {
            const uint16_t index = i * VGA_WIDTH + j;

            vga_buffer[index] = vga_entry(' ', g_vga_color);
        }
    }
}

/* Disalbes cursor */
void vga_cursor_disable() 
{
    // disable cursor by writing to 0x3d4 and 0x3d5
    outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

/* Enables cursor */
void vga_cursor_enable(uint8_t start, uint8_t end) 
{
    // set starting scanline of cursor
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | start);
 
    // set ending scanline of cursor (for cursor shapes)
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | end);
}

/* Update cursor to new x, y pos (row, col for tty) */
void vga_update_cursor(int x, int y)
{
	uint16_t pos = y * VGA_WIDTH + x;
 
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

/* Gets cursor position and returns struct of cursor_pos_t (x, y) */
cursor_pos_t vga_get_cursor_position() 
{
    uint16_t pos = 0;
    cursor_pos_t cursor_pos;

    outb(0x3D4, 0x0F);
    pos |= inb(0x3D5);

    outb(0x3D4, 0x0E);
    pos |= ((uint16_t)inb(0x3D5)) << 8;

    cursor_pos.x = pos / VGA_WIDTH; 
    cursor_pos.y = pos % VGA_WIDTH; 

    return cursor_pos;
}


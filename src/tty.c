#include "tty.h"
#include "stdio.h"
#include "vga.h"
#include "string.h"

static tty_state_t tty_state;

/* Init tty interface and set default color to white on black */
void tty_init() 
{
    // set foreground color to white, background to blue
    // feel free to change this
    tty_setcolor(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    // initialize vga interface
    vga_init();

    vga_cursor_disable();
}

/* Write a string to tty output, with row, col tracking */
void tty_write(const char* str) 
{
    // loop through each character and putc to screen
    for (size_t i = 0; i < strlen(str); ++i) {
        // detect when a newline character is present
        tty_putc(str[i]);
    }

    // update cursor after string is written to tty
    vga_update_cursor(tty_state.col, tty_state.row);
}

void tty_putc(char c)
{
    if (c != '\n') vga_putc(c, tty_state.row, tty_state.col);

    // if we are at the end of the line (80 columns), break line
    if (++tty_state.col == VGA_WIDTH || c == '\n') {
        tty_state.col = 0;

        // same for rows
        if (++tty_state.row == VGA_HEIGHT) {
            --tty_state.row;
            vga_scroll();
        } 
    }
}

/* Clear screen and reset row, col pointers */
void tty_clear() 
{
    // clear vga buffer
    vga_clear();

    // reset column and row pointers
    tty_state.col = 0;
    tty_state.row = 0;
}

/* Set new color and store fg/bg colors in state */
void tty_setcolor(vga_color_t fg, vga_color_t bg) 
{
    vga_setcolor(fg, bg);

    tty_state.fgcolor = fg;
    tty_state.bgcolor = bg;
}

/* Just a somewhat unecessary boot success message */
void tty_welcome() 
{
    // temporarily set text color to green
    vga_setcolor(VGA_COLOR_GREEN, tty_state.bgcolor);
    tty_write("\nkOS booted and initialized successfully!\n");

    // set text color back to default
    vga_setcolor(tty_state.fgcolor, tty_state.bgcolor);

    // some dope ascii art that I definitely didn't generate...
    tty_write("\n\n");
    tty_write(" /$$        /$$$$$$   /$$$$$$\n");
    tty_write("| $$       /$$__  $$ /$$__  $$\n");
    tty_write("| $$   /$$| $$  \\ $$| $$  \\__/\n");
    tty_write("| $$  /$$/| $$  | $$|  $$$$$$ \n");
    tty_write("| $$$$$$/ | $$  | $$ \\____  $$\n");
    tty_write("| $$_  $$ | $$  | $$ /$$  \\ $$\n");
    tty_write("| $$ \\  $$|  $$$$$$/|  $$$$$$/\n");
    tty_write("|__/  \\__/ \\______/  \\______/ \n");

    tty_write("\n\nWelcome to kOS!\n");

    // enable vertical cursor (max scanline 15)
    vga_cursor_enable(1, 15);
    
    // update cursor to current row, col
    vga_update_cursor(tty_state.col, tty_state.row);

    vga_setcolor(VGA_COLOR_LIGHT_BLUE, tty_state.bgcolor);
    tty_write("> ");
    vga_setcolor(tty_state.fgcolor, tty_state.bgcolor);
}

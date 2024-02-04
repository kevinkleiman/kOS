#include "tty.h"
#include "vga.h"
#include "string.h"

tty_state_t tty_state;

void tty_init() {
    // Set foreground color to white, background to blue
    // Feel free to change this
    tty_setcolor(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    // Initialize vga interface
    vga_init();
}

void tty_write(const char* str) {
    // Loop through each character and putc to screen
    for (size_t i = 0; i < strlen(str); ++i) {
        // Detect when a newline character is present
        if (str[i] != '\n') vga_putc(str[i], tty_state.row, tty_state.col);

        // If we are at the end of the line (80 columns), break line
        if (++tty_state.col == VGA_WIDTH || str[i] == '\n') {
            tty_state.col = 0;

            // Same for rows
            if (++tty_state.row == VGA_HEIGHT) tty_state.row = 0;
        }
    }
}

void tty_clear() {
    // Clear vga buffer
    vga_clear();

    // Reset column and row pointers
    tty_state.col = 0;
    tty_state.row = 0;
}

void tty_setcolor(vga_color_t fg, vga_color_t bg) {
    vga_setcolor(VGA_COLOR_WHITE, VGA_COLOR_BLACK);

    tty_state.fgcolor = fg;
    tty_state.bgcolor = bg;
}

void tty_welcome() {
    BOOT_LOG("kOS booted and initialized successfully")

    tty_write("\n\n");
    tty_write(" /$$        /$$$$$$   /$$$$$$\n");
    tty_write("| $$       /$$__  $$ /$$__  $$\n");
    tty_write("| $$   /$$| $$  \ $$| $$  \__/\n");
    tty_write("| $$  /$$/| $$  | $$|  $$$$$$ \n");
    tty_write("| $$$$$$/ | $$  | $$ \____  $$\n");
    tty_write("| $$_  $$ | $$  | $$ /$$  \ $$\n");
    tty_write("| $$ \  $$|  $$$$$$/|  $$$$$$/\n");
    tty_write("|__/  \__/ \______/  \______/ \n");

    tty_write("\n\nWelcome to kOS!\n");
}

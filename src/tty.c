#include "tty.h"
#include "vga.h"
#include "string.h"

tty_state_t tty_state;

void tty_init() {
    // Set foreground color to white, background to blue
    // Feel free to change this
    set_vga_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    // Initialize vga interface
    vga_init();
}

void tty_write(const char* str) {
    // Loop through each character and putc to screen
    for (size_t i = 0; i < strlen(str); ++i) {
        // Detect when a newline character is present
        if (str[i] != '\n') putc(str[i], tty_state.tty_row, tty_state.tty_col);

        // If we are at the end of the line (80 columns), break line
        if (++tty_state.tty_col == VGA_WIDTH || str[i] == '\n') {
            tty_state.tty_col = 0;

            // Same for rows
            if (++tty_state.tty_row == VGA_HEIGHT) tty_state.tty_row = 0;
        }
    }
}

#include "VGA.h"

void main()
{
    /*
     * A quick and dirty example of writing directly to
     * video memory to display text
     */
    unsigned char *vid_mem = VGA_MEM;
    *vid_mem = 'K';
    vid_mem = (unsigned char*) 0xB8000 + 2;
    *vid_mem = '-';
    vid_mem = (unsigned char*) 0xB8000 + 4;
    *vid_mem = 'O';
    vid_mem = (unsigned char*) 0xB8000 + 6;
    *vid_mem = 'S';
    return;
}

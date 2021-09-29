
#define VGA_MEM (unsigned char*) 0xB8000
#define MAX_ROWS 25
#define MAX_COLS 25

void put_char(unsigned char* c);
void printk(unsigned char* string);
void clear_screen();
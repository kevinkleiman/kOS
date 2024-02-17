#include "keyboard.h"
#include "tty.h"
#include "io.h"
#include "vga.h"

const uint32_t lowercase[128] = {
    UNKNOWN,ESC,'1','2','3','4','5','6','7','8',
    '9','0','-','=','\b','\t','q','w','e','r',
    't','y','u','i','o','p','[',']','\n',CTRL,
    'a','s','d','f','g','h','j','k','l',';',
    '\'','`',LSHFT,'\\','z','x','c','v','b','n','m',',',
    '.','/',RSHFT,'*',ALT,' ',CAPS,F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,NUMLCK,SCRLCK,HOME,UP,PGUP,'-',LEFT,UNKNOWN,RIGHT,
    '+',END,DOWN,PGDOWN,INS,DEL,UNKNOWN,UNKNOWN,UNKNOWN,F11,F12,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
    UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
    UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
    UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN
};

const uint32_t uppercase[128] = {
    UNKNOWN,ESC,'!','@','#','$','%','^','&','*','(',')','_','+','\b','\t','Q','W','E','R',
    'T','Y','U','I','O','P','{','}','\n',CTRL,'A','S','D','F','G','H','J','K','L',':','"','~',LSHFT,'|','Z','X','C',
    'V','B','N','M','<','>','?',RSHFT,'*',ALT,' ',CAPS,F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,NUMLCK,SCRLCK,HOME,UP,PGUP,'-',
    LEFT,UNKNOWN,RIGHT,'+',END,DOWN,PGDOWN,INS,DEL,UNKNOWN,UNKNOWN,UNKNOWN,F11,F12,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
    UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
    UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
    UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN
};

bool caps;
bool caps_lock;

void keyboard_callback(__attribute__((unused)) i_register_t registers) {
    unsigned char scan = inb(0x60) & 0x7F;
    unsigned char pressed = inb(0x60) & 0x80;

    switch(scan) {
        // unused for now
        case 1:
        case 29:
        case 56:
        case 59:
        case 60:
        case 61:
        case 62:
        case 63:
        case 64:
        case 65:
        case 66:
        case 67:
        case 68:
        case 87:
        case 88:
            break;
        // start of usable keys
        case 28:
            // TODO fix this shit
            if (pressed == 0) {
                tty_putc(lowercase[scan]);
                vga_setcolor(VGA_COLOR_LIGHT_BLUE, VGA_COLOR_BLACK);
                tty_write("> ");
                vga_setcolor(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
            }
            break;
        case 41:
            tty_write("\n\nRebooting...\n");
            warm_reboot();
            break;
        case 54:
        case 42:
            caps = (pressed == 0) ? true : false;
            break;

        case 58:
            if (!caps_lock && pressed == 0) {
                caps_lock = true;
            } else if (caps_lock && pressed == 0) {
                caps_lock = false;
            }
            break;
        default:
            if (pressed == 0) {
                if (caps || caps_lock) {
                    tty_putc(uppercase[scan]);
                } else {
                    tty_putc(lowercase[scan]);
                }
            }
    }
}

void keyboard_init() {
    register_interrupt_handler(IRQ1, keyboard_callback);

    BOOT_LOG("Keyboard initialized.")
}

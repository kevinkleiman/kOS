#include "idt.h"
#include "io.h"

__attribute__((aligned(0x10))) static idt_entry_t idt[256];
static idtr_t idtr;

extern void load_idt(idtr_t*);

void pic_init() {
    // Setup master and slave PIC
    outb(PIC_CMD_PORT_MASTER, 0x11);
    outb(PIC_CMD_PORT_SLAVE, 0x11);

    // Setup vector offsets
    outb(PIC_DATA_PORT_MASTER, 0x20);
    outb(PIC_DATA_PORT_SLAVE, 0x28);

    outb(PIC_DATA_PORT_MASTER, 0x04);
    outb(PIC_DATA_PORT_SLAVE, 0x02);

    outb(PIC_DATA_PORT_MASTER, 0x01);
    outb(PIC_DATA_PORT_SLAVE, 0x01);

    outb(PIC_DATA_PORT_MASTER, 0x0);
    outb(PIC_DATA_PORT_SLAVE, 0x0);
}

void idt_init() {
    idtr.limit = (uint16_t) (sizeof(idt) * 256) - 1;
    idtr.base = (uintptr_t) &idt;

    pic_init();
    load_idt(&idtr);
}

void isr_handler(irt_register_t* irt_registers) {
    if (irt_registers->int_no < 32) kpanic();
}
__attribute__((noreturn)) void kpanic() {
    __asm__ __volatile__( "cli; hlt" );
}


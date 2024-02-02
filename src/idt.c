#include "idt.h"
#include "io.h"
#include "tty.h"

__attribute__((aligned(0x10))) static idt_entry_t idt[256];

static idtr_t idtr;
static isr_t interrupt_handlers[256];

const char* exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment not present",
    "Stack fault",
    "General protection fault",
    "Page fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Fault",
    "Machine Check", 
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

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

    idt_set_gate(0, (uint32_t) isr0);
    idt_set_gate(1, (uint32_t) isr1);
    idt_set_gate(2, (uint32_t) isr2);
    idt_set_gate(3, (uint32_t) isr3);
    idt_set_gate(4, (uint32_t) isr4);
    idt_set_gate(5, (uint32_t) isr5);
    idt_set_gate(6, (uint32_t) isr6);
    idt_set_gate(7, (uint32_t) isr7);
    idt_set_gate(8, (uint32_t) isr8);
    idt_set_gate(9, (uint32_t) isr9);
    idt_set_gate(10, (uint32_t) isr10);
    idt_set_gate(11, (uint32_t) isr11);
    idt_set_gate(12, (uint32_t) isr12);
    idt_set_gate(13, (uint32_t) isr13);
    idt_set_gate(14, (uint32_t) isr14);
    idt_set_gate(15, (uint32_t) isr15);
    idt_set_gate(16, (uint32_t) isr16);
    idt_set_gate(17, (uint32_t) isr17);
    idt_set_gate(18, (uint32_t) isr18);
    idt_set_gate(19, (uint32_t) isr19);
    idt_set_gate(20, (uint32_t) isr20);
    idt_set_gate(21, (uint32_t) isr21);
    idt_set_gate(22, (uint32_t) isr22);
    idt_set_gate(23, (uint32_t) isr23);
    idt_set_gate(24, (uint32_t) isr24);
    idt_set_gate(25, (uint32_t) isr25);
    idt_set_gate(26, (uint32_t) isr26);
    idt_set_gate(27, (uint32_t) isr27);
    idt_set_gate(28, (uint32_t) isr28);
    idt_set_gate(29, (uint32_t) isr29);
    idt_set_gate(30, (uint32_t) isr30);
    idt_set_gate(31, (uint32_t) isr31);

    idt_set_gate(32, (uint32_t) irq0);
    idt_set_gate(33, (uint32_t) irq1);
    idt_set_gate(34, (uint32_t) irq2);
    idt_set_gate(35, (uint32_t) irq3);
    idt_set_gate(36, (uint32_t) irq4);
    idt_set_gate(37, (uint32_t) irq5);
    idt_set_gate(38, (uint32_t) irq6);
    idt_set_gate(39, (uint32_t) irq7);
    idt_set_gate(40, (uint32_t) irq8);
    idt_set_gate(41, (uint32_t) irq9);
    idt_set_gate(42, (uint32_t) irq10);
    idt_set_gate(43, (uint32_t) irq11);
    idt_set_gate(44, (uint32_t) irq12);
    idt_set_gate(45, (uint32_t) irq13);
    idt_set_gate(46, (uint32_t) irq14);
    idt_set_gate(47, (uint32_t) irq15);

    load_idt(&idtr);
}

void register_interrupt_handler(uint8_t index, isr_t handler) {
    interrupt_handlers[index] = handler;
}

void isr_handler(irt_register_t* registers) {
    if (registers->int_no < 32) {
        tty_write("\nKERNEL PANIC! ");
        tty_write(exception_messages[registers->int_no]);
            
        // hang
        for (;;);
    }
}

void irq_handler(irt_register_t* registers) {
    if (registers->int_no >= 40) outb(PIC_DATA_PORT_SLAVE, 0x20);
    outb(PIC_CMD_PORT_MASTER, 0x20);

    if (interrupt_handlers[registers->int_no] != 0) {
        isr_t handler = interrupt_handlers[registers->int_no];
        handler(registers);
    }
}

void idt_set_gate(uint8_t index, uint32_t handler) {
    idt[index].isr_low = handler & 0xFFFF;
    idt[index].kernel_cs = 0x08;
    idt[index].reserved = 0;
    idt[index].attributes = INTERRUPT_GATE;
    idt[index].isr_high = (handler >> 16) & 0xFFFF;
}

__attribute__((noreturn)) void kpanic() {
    __asm__ __volatile__( "cli; hlt" );
}


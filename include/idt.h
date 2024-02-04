#pragma once

#include <stdint.h>
#include <stdbool.h>

#define INTERRUPT_GATE 0x8E
#define TRAP_GATE 0x8F
#define TASK_GATE 0x85

#define PIC_CMD_PORT_MASTER 0x20
#define PIC_DATA_PORT_MASTER 0x21

#define PIC_CMD_PORT_SLAVE 0xA0
#define PIC_DATA_PORT_SLAVE 0xA1

#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

typedef struct {
	uint16_t    isr_low;      
	uint16_t    kernel_cs;    
	uint8_t     reserved;    
	uint8_t     attributes;   
	uint16_t    isr_high;     
} __attribute__((packed)) idt_entry_t;

typedef struct {
   uint16_t     offset_low;
   uint16_t     selector;
   uint8_t      zero;
   uint8_t      type_attributes;
   uint16_t     offset_high;
} __attribute__((packed)) gate_descriptor_t;

typedef struct {
	uint16_t	limit;
	uint32_t	base;
} __attribute__((packed)) idtr_t;

typedef struct {
   uint32_t ds;
   uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
   uint32_t int_no, err_code;
   uint32_t eip, cs, eflags, useresp, ss;
} __attribute__((packed)) i_register_t;

typedef void (*isr_t)(i_register_t);

/* Function definitions for idt setup and interrupts */
void idt_init();
void idt_set_gate(uint8_t index, uint32_t handler);
void register_interrupt_handler(uint8_t index, isr_t handler);
void isr_handler(i_register_t irt_register);


/* Checks whether interrupts are enabled */
static inline bool are_interrupts_enabled() 
{
    unsigned long flags;
    asm volatile ( "pushf\n\t"
                   "pop %0"
                   : "=g"(flags) );
    return flags & (1 << 9);
}

/* ISRs */
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();
extern void isr128();
extern void isr177();

/* IRQs */
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();



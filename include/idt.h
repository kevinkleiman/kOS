#pragma once

#include <stdint.h>

#define INTERRUPT_GATE 0x8E
#define TRAP_GATE 0x8F
#define TASK_GATE 0x85

#define PIC_CMD_PORT_MASTER 0x20
#define PIC_DATA_PORT_MASTER 0x21

#define PIC_CMD_PORT_SLAVE 0xA0
#define PIC_DATA_PORT_SLAVE 0xA1

#define ISR_EXCEPTIONS ((const char*[]) {\
                        "divide_by_zero", \
                        "debug", \
                        "nmi", \
                        "breakpoint", \
                        "info_detected_overflow", \
                        "out_of_bounds", \
                        "invalid_opcode", \
                        "no_coprocessor", \
                        "double_fault", \
                        })

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
    uint32_t    cr2;
    uint32_t    ds;
    uint32_t    edi;
    uint32_t    esi;
    uint32_t    ebp;
    uint32_t    esp;
    uint32_t    ebx;
    uint32_t    edx;
    uint32_t    ecx;
    uint32_t    eax;
    uint32_t    int_no;
    uint32_t    err_code;
    uint32_t    eip;
    uint32_t    csm;
    uint32_t    eflags;
    uint32_t    useresp;
    uint32_t    ss;
} __attribute__((packed)) irt_register_t;

void idt_init();
void isr_handler(irt_register_t* irt_register);

__attribute__((noreturn)) void kpanic();
__attribute__((interrupt)) void irq1();

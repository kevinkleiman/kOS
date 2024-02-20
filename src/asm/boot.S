MALIGN equ   1 << 0
MEMINFO equ  1 << 1
FLAGS equ    MALIGN | MEMINFO  
MAGIC equ    0x1BADB002       
CHECKSUM equ -(MAGIC + FLAGS) 

section .multiboot
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

section .bss
align 16
stack_bottom:
    resb 16384 * 8
stack_top:

section .boot
global _start
_start:
    mov ecx, (initial_page_dir - 0xC0000000)
    mov cr3, ecx

    mov ecx, cr4
    or ecx, 0x10
    mov cr4, ecx

    mov ecx, cr0
    or ecx, 0x80000000
    mov cr0, ecx

    JMP higher_half

section .text
extern kernel_main
higher_half:
    mov esp, stack_top
    push ebx
    push eax
    xor ebp, ebp
    call kernel_main

halt:
    hlt
    JMP halt

section .data
align 4096
global initial_page_dir
initial_page_dir:
    dd 10000011b
    times 768-1 dd 0

    dd (0 << 22) | 10000011b
    dd (1 << 22) | 10000011b
    dd (2 << 22) | 10000011b
    dd (3 << 22) | 10000011b
    times 256-4 dd 0

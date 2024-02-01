global load_idt

extern isr_handler

%macro panic %1
    cli
    push long %1
    jmp isr_common_stub
%endmacro

%macro nopanic
    cli
    push long 0
    push long %1
    jmp isr_common_stub
%endmacro

%macro ISR_NO_ERR 1
    global isr_no_err_%1

    isr_no_err_%1:
        nopanic
%endmacro

%macro ISR_ERR 1
    global isr_no_err_%1

    isr_no_err_%1:
        panic
%endmacro

load_idt:
    mov eax, [esp + 4]
    lidt [eax]
    sti
    ret

isr_common_stub:
    pusha
    mov eax, ds
    push eax
    mov eax, cr2
    push eax

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push esp
    call isr_handler

    popa
    add esp, 8
    pop ebx
    sti
    iret

ISR_NO_ERR 0
ISR_NO_ERR 1
ISR_NO_ERR 2
ISR_NO_ERR 3
ISR_NO_ERR 4
ISR_NO_ERR 5
ISR_NO_ERR 6
ISR_NO_ERR 7
ISR_ERR 8
ISR_NO_ERR 9
ISR_ERR 10
ISR_ERR 11
ISR_ERR 12
ISR_ERR 13
ISR_ERR 14
ISR_NO_ERR 15
ISR_NO_ERR 16
ISR_NO_ERR 17
ISR_NO_ERR 18
ISR_NO_ERR 19
ISR_NO_ERR 20
ISR_NO_ERR 21
ISR_NO_ERR 22
ISR_NO_ERR 23
ISR_NO_ERR 24
ISR_NO_ERR 25
ISR_NO_ERR 27
ISR_NO_ERR 28
ISR_NO_ERR 29
ISR_NO_ERR 30
ISR_NO_ERR 31
ISR_NO_ERR 128
ISR_NO_ERR 177

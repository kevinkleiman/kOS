; Set boot sector origin address
[org 0x7C00]

BOOT_DISK: db 0
mov [BOOT_DISK], dl

CODE_SEGMENT equ gdt_code - gdt_start   ; set code segment
DATA_SEGMENT equ gdt_data - gdt_start   ; set data segment

cli                                     ; clear interrupts, no more 16 bit real mode :(
lgdt [gdt_descriptor]
mov eax, cr0
or eax, 1
mov cr0, eax
jmp CODE_SEGMENT:start_protected_mode   ; far jump

jmp $

; Setup GDT
gdt_start:
    gdt_null:       ; null descriptor
        dd 0x0
        dd 0x0

    gdt_code:       ; code descriptor
        dw 0xffff
        dw 0x0
        db 0x0
        db 0b10011010
        db 0b11001111
        db 0x0

    gdt_data:       ; data descriptor
        dw 0xffff
        dw 0x0
        db 0x0
        db 0b10010010
        db 0b11001111
        db 0x0

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start


[bits 32]
start_protected_mode:
    mov ax, DATA_SEGMENT
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov al, 'H'
    mov ah, 0x0f
    mov [0xb8000], ax    ; write to vid mem directly
    jmp $

; Padding and Magic number
times 510-($-$$) db 0
dw 0xAA55       ; magic number

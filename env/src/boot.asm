; Set boot sector origin address
[org 0x7C00]

KERNEL_LOC equ 0x1000       ; set kernel location

BOOT_DISK: db 0
mov [BOOT_DISK], dl

xor ax, ax
mov es, ax
mov ds, ax
mov bp, 0x8000
mov sp, bp

mov bx, KERNEL_LOC
mov dh, 2

call load_disk

mov ah, 0x0
mov al, 0x3
int 0x10        ; clear screen with text mode


CODE_SEGMENT equ gdt_code - gdt_start   ; set code segment
DATA_SEGMENT equ gdt_data - gdt_start   ; set data segment

cli                                     ; clear interrupts, no more 16 bit real mode :(
lgdt [gdt_descriptor]                   ; load GDT!
mov eax, cr0
or eax, 1
mov cr0, eax
jmp CODE_SEGMENT:start_protected_mode   ; far jump

jmp $

%include "./src/read_disk.asm"

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


; 32 bit protected mode
[bits 32]
start_protected_mode:
    mov ax, DATA_SEGMENT
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000    ; base pointer
    mov esp, ebp        ; stack pointer

    jmp KERNEL_LOC      ; jump to kernel!!

; Padding and Magic number
times 510-($-$$) db 0
dw 0xAA55       ; magic number

[BITS 16]
[ORG 0x7e00]

start:
    mov [DriveId], dl   

    mov eax, 0x80000000
    cpuid
    cmp eax, 0x80000001
    jb NotSupported    
    mov eax, 0x80000001
    cpuid
    test edx, (1 << 29)     ; Test bit 29
    jz NotSupported
    test edx, (1 << 26)     ; Test bit 26
    jz NotSupported
    
    mov ah, 0x13
    mov al, 1
    mov bx, 0xa
    xor dx, dx
    mov bp, Message
    mov cx, MessageLen
    int 0x10

NotSupported:
End:
    hlt
    jmp End 

DriveId: db 0
Message: db "Long mode supported"
MessageLen: equ $-Message
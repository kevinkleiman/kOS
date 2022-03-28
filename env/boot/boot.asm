[BITS 16]
[ORG 0x7c00]

start:
    xor ax, ax   
    mov ds, ax
    mov es, ax  
    mov ss, ax
    mov sp, 0x7c00

; Test if disk extension is supported
TestDiskExtension:
    mov [DriveId], dl
    mov ah, 0x41
    mov bx, 0x5aa
    int 0x13
    jc NotSupported
    cmp bx, 0xaa55
    jne NotSupported

; Load MBR from disk
Load:
    mov si, ReadPacket
    mov word[si], 0x10
    mov word[si + 2], 5
    mov word[si + 4], 0x7e00
    mov word[si + 6], 0
    mov dword[si + 8], 1
    mov dword[si + 0xc], 0
    mov dl, [DriveId]
    mov ah, 0x42
    int 0x13
    ; jc ReadError

    mov dl, [DriveId]
    jmp 0x7e00      ; Jump to loader, refer to MBR memory map for reference

; Jump to end if not supported. May add print statement.
NotSupported:
; Print error message for any boot errors we encounter
ReadError:
    mov ah, 0x13
    mov al, 1
    mov bx, 0xa
    xor dx, dx
    mov bp, Message
    mov cx, MessageLen 
    int 0x10
End:
    hlt    
    jmp End

; Define constants
DriveId:    db 0
Message:    db "Boot error!"
MessageLen: equ $-Message
ReadPacket: times 16 db 0

times (0x1be-($-$$)) db 0
; Do whatever the fuck this shit does
    db 80h
    db 0, 2, 0
    db 0f0h
    db 0ffh, 0ffh, 0ffh
    dd 1
    dd (20 * 16 * 63 - 1)
	
    times (16*3) db 0

    db 0x55
    db 0xaa

	

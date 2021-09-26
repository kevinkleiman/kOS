; Set boot sector origin memory address
org 0x7C00

%include "print.asm"

mov si, STR_BOOTING
call print_string

mov bp, 0x8000
mov sp, bp

mov bx, 0x9000
mov dh, 2
call load_disk

mov si, [0x9000 + 500]
call print_string

; Infinite Loop
jmp $

; Read from disk
load_disk:
	pusha
	push dx
	
	mov ah, 0x02
	mov al, dh
	mov cl, 0x02
	mov ch, 0x00
	mov dh, 0x00
	int 0x13
	jc disk_error	
	
	pop dx 
	cmp al, dh
	jne disk_error
	mov si, STR_DISK_SUCCESS
	call print_string
	popa
	ret

; Print Error if disk sector not loaded
disk_error:
	mov si, STR_DISK_ERROR
	call print_string
	jmp $

; String Messages	
STR_BOOTING: db '[*] Loading Disk', 0x0A, 0x0D, 0
STR_DISK_ERROR: db '[!] Error Loading Disk...', 0x0A, 0x0D, 0
STR_DISK_SUCCESS: db '[*] Successfully Loaded Disk!', 0x0A, 0x0D, 0
STR_KERNEL_LOAD: db '[*] Loading Kernel From Disk...', 0x0A, 0x0D, 0

; Padding and Magic number
times 510-($-$$) db 0
dw 0xAA55


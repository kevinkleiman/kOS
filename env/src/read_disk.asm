; Read from disk
load_disk:
	pusha
	push dx

	mov ah, 0x02
    mov al, dh
    mov ch, 0x00
    mov dh, 0x00
    mov cl, 0x02
    mov dl, [BOOT_DISK]
	int 0x13
	jc disk_error

	pop dx
	cmp al, dh
	jne disk_error
	popa
	ret

; Print Error if disk sector not loaded
disk_error:
    mov si, DISK_ERROR_MSG
    call print_string
	jmp $

%include "./src/print.asm"

DISK_ERROR_MSG: db "Error Reading from disk...", 0
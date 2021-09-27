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
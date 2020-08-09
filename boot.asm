; Set boot sector origin memory address
org 0x7c00

mov si, STR_BOOTING
call print

mov bp, 0x8000
mov sp, bp

mov bx, 0x9000
mov dh, 2
call load_disk

mov si, [0x9000 + 500]
call print

; Infinite Loop
jmp $

; Print Strings to screen
print:
	pusha
	str_loop:
		mov al, [si]
		cmp al, 0
		jne print_char
		popa
		ret
	
	print_char:
		mov ah, 0x0E
		int 0x10
		add si, 1
		jmp str_loop

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
	call print
	popa
	ret

; Print Error if disk sector not loaded
disk_error:
	mov si, STR_DISK_ERROR
	call print
	jmp $

; String Messages	
STR_BOOTING: db '[*] Loading Disk', 0x0a, 0x0d, 0
STR_DISK_ERROR: db '[!] Error Loading Disk...', 0x0a, 0x0d, 0
STR_DISK_SUCCESS: db '[*] Successfully Loaded Disk!', 0x0a, 0x0d, 0
STR_KERNEL_LOAD: db '[*] Loading Kernel From Disk...', 0x0a, 0x0d, 0

; Padding and Magic number
times 510-($-$$) db 0
dw 0xaa55

; Disk Sectors
times 256 db 'kk'


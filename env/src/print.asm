; Print Strings to screen using BIOS interrupt 0x10
print_string:
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
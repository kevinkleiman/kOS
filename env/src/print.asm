; Contains code for printing strings in 16-bit real mode
print_string:
	pusha
	str_loop:
		mov al, [si]    ; use si register to hold string
		cmp al, 0
		jne print_char
		popa
		ret

	print_char:
		mov ah, 0x0E
		int 0x10        ; using BIOS interrupt 0x10 to display character
		add si, 1
		jmp str_loop
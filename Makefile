boot_asm: 
	qemu-system-x86_64 -fda boot.bin
	
boot_bin:
	nasm -fbin boot.asm -o boot.bin	

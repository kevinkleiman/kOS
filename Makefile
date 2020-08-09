asm: 
	nasm -fbin boot.asm -o boot.bin	
qemu:
	qemu-system-x86_64 -fda boot.bin

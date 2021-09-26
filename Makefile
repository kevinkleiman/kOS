BUILD_TARGET = boot

asm:
	nasm -fbin /src/$(BOOT_TARGET).asm -o /build/$(BOOT_TARGET).bin
qemu:
	qemu-system-x86_64 -fda /build/$(BOOT_TARGET).bin

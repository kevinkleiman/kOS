BUILD_DIR = ./src
BOOTLOADER_TARGET = boot
KERNEL_ENTRY_TARGET = kernel_entry
KERNEL_TARGET = kernel
ZEROS_TARGET = zero_pad

build:
	nasm $(BUILD_DIR)/boot/$(BOOTLOADER_TARGET).asm -f bin -o ./bin/$(BOOTLOADER_TARGET).bin
	nasm $(BUILD_DIR)/boot/$(ZEROS_TARGET).asm -f bin -o ./bin/$(ZEROS_TARGET).bin
	nasm $(BUILD_DIR)/boot/$(KERNEL_ENTRY_TARGET).asm -f elf -o ./bin/$(KERNEL_ENTRY_TARGET).o
	i686-elf-gcc -ffreestanding -m32 -g -c $(BUILD_DIR)/kernel/$(KERNEL_TARGET).c -o ./bin/$(KERNEL_TARGET).o
	i686-elf-ld -o ./bin/kernel_comp.bin -Ttext 0x1000 ./bin/$(KERNEL_ENTRY_TARGET).o ./bin/$(KERNEL_TARGET).o --oformat binary
	cat ./bin/$(BOOTLOADER_TARGET).bin ./bin/kernel_comp.bin ./bin/$(ZEROS_TARGET).bin > ./bin/kos.bin

clean:
	rm -rf ./bin/*.bin
	rm -rf ./bin/*.o
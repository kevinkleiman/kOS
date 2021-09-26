BUILD_TARGET = boot

build:
	nasm -fbin /src/$(BUILD_TARGET).asm -o /build/$(BUILD_TARGET).bin
run:
	qemu-system-x86_64 -fda /build/$(BUILD_TARGET).bin
clean:
	rm -rf /build/*.bin
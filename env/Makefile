BUILD_TARGET = boot

nasm-build:
	nasm -fbin ./src/$(BUILD_TARGET).asm -o ./bin/$(BUILD_TARGET).bin
clean:
	rm -rf ./bin/*.bin
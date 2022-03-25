BOOT_DIR=boot/
BOOT_TARGET=$(BOOT_DIR)boot
LOADER_TARGET=$(BOOT_DIR)loader

build:
	nasm -f bin -o $(BOOT_TARGET).bin $(BOOT_TARGET).asm	
	nasm -f bin -o $(LOADER_TARGET).bin $(LOADER_TARGET).asm
	dd if=$(BOOT_TARGET).bin of=$(BOOT_TARGET).img bs=512 count=1 conv=notrunc
	dd if=$(LOADER_TARGET).bin of=$(BOOT_TARGET).img bs=512 count=5 seek=1 conv=notrunc
	
run:
	qemu-system-x86_64 $(BOOT_TARGET).img

clean:
	rm -rf $(BOOT_DIR)*.bin $(BOOT_DIR)*.img

# all: $(TARGETS)

# $(TARGETS):
# 	nasm -f bin -o $@.bin $@.asm	
# 	dd if=$@.bin of=$@.img bs=512 count=1 conv=notrunc
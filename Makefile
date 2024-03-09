BOOTDIR := ./multiboot/boot
OBJECTDIR := ./bin
SRCDIR := ./src
ASMDIR := $(SRCDIR)/asm
DRIVERSDIR := $(SRCDIR)/drivers
INCLUDEDIR := ./include

RUSTTARGET := x86_64-kos
RUSTBIN := ./lib/target
RUSTENTRY := $(RUSTBIN)/$(RUSTTARGET)/debug/libkOS.a

CC := i686-elf
ASC := nasm -f elf32
EMU := qemu-system-i386

OBJECTS := $(OBJECTDIR)/*.o
CTARGETS := $(SRCDIR)/*.c $(DRIVERSDIR)/*.c
ASMTARGETS := $(ASMDIR)/*.S

KERNELTARGET := kos

default:
		$(ASC) $(ASMDIR)/boot.S -o $(OBJECTDIR)/boot.o
		$(ASC) $(ASMDIR)/gdt.S -o $(OBJECTDIR)/_gdt.o
		$(ASC) $(ASMDIR)/idt.S -o $(OBJECTDIR)/_idt.o
		$(CC)-gcc -I $(INCLUDEDIR) -c $(CTARGETS) -std=gnu99 -ffreestanding -O2 -Wall -Wextra

		mv ./*.o $(OBJECTDIR)
		CARGO_TARGET_DIR=$(RUSTBIN) cargo build --target ./lib/$(RUSTTARGET).json

		$(CC)-gcc -T linker.ld -o $(BOOTDIR)/$(KERNELTARGET).bin -ffreestanding -O2 -nostdlib $(OBJECTS) $(RUSTENTRY) -lgcc

env:
		docker build env -t kos

image: 
		docker run -it --rm -v .:/root/env kos make grub

verify:
		grub-file --is-x86-multiboot $(BOOTDIR)/$(KERNELTARGET).bin

grub:
		grub-mkrescue -o $(KERNELTARGET).iso multiboot

run:
		$(EMU) $(KERNELTARGET).iso

clean:
		rm -rf $(OBJECTDIR)/*.*
		rm -rf $(KERNELTARGET).iso
		rm -rf $(BOOTDIR)/$(KERNELTARGET).bin

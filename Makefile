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
DOCKER := docker run -it --rm -v .:/root/env kos
ASC := nasm -f elf32
EMU := qemu-system-i386 -hda

KERNELTARGET := kos
OBJECTS := $(OBJECTDIR)/*.o
CTARGETS := $(SRCDIR)/*.c $(DRIVERSDIR)/*.c
ASMTARGETS := $(ASMDIR)/*.S
ISO := $(OBJECTDIR)/$(KERNELTARGET).iso


.PHONY: all kernel env image verify grub run clean

all: clean kernel image run

kernel:
		$(ASC) $(ASMDIR)/boot.S -o $(OBJECTDIR)/boot.o
		$(ASC) $(ASMDIR)/gdt.S -o $(OBJECTDIR)/_gdt.o
		$(ASC) $(ASMDIR)/idt.S -o $(OBJECTDIR)/_idt.o
		$(DOCKER) $(CC)-gcc -I $(INCLUDEDIR) -c $(CTARGETS) -std=gnu99 -ffreestanding -O2 -Wall -Wextra

		mv ./*.o $(OBJECTDIR)
		CARGO_TARGET_DIR=$(RUSTBIN) cargo build --target ./lib/$(RUSTTARGET).json

		$(DOCKER) $(CC)-gcc -T linker.ld -o $(BOOTDIR)/$(KERNELTARGET).bin -ffreestanding -O2 -nostdlib $(OBJECTS) $(RUSTENTRY) -lgcc

env:
		docker build env -t kos

image: $(OBJECTS) 
		docker run -it --rm -v .:/root/env kos make grub

verify:
		grub-file --is-x86-multiboot $(BOOTDIR)/$(KERNELTARGET).bin

grub:
		grub-mkrescue -o $(OBJECTDIR)/$(KERNELTARGET).iso multiboot

run: $(ISO)
		sudo $(EMU) $(ISO) -hdb fs.img

clean:
		rm -rf $(OBJECTDIR)/*.*
		rm -rf $(KERNELTARGET).iso
		rm -rf $(BOOTDIR)/$(KERNELTARGET).bin

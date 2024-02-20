BOOTDIR := ./multiboot/boot
OBJECTDIR := ./bin
SRCDIR := ./src
ASMDIR := $(SRCDIR)/asm
DRIVERSDIR := $(SRCDIR)/drivers
INCLUDEDIR := ./include

CC := i686-elf
ASC := nasm -f elf32
EMU := qemu-system-i386

OBJECTS := $(OBJECTDIR)/*.o
CTARGETS := $(SRCDIR)/*.c $(DRIVERSDIR)/*.c
ASMTARGETS := $(ASMDIR)/*.S

KERNELTARGET := kos

default:
		$(ASC) $(ASMDIR)/boot.S -o $(OBJECTDIR)/boot.o
		$(ASC) $(ASMDIR)/__gdt.S -o $(OBJECTDIR)/__gdt.o
		$(ASC) $(ASMDIR)/__idt.S -o $(OBJECTDIR)/__idt.o
		$(CC)-gcc -I $(INCLUDEDIR) -c $(CTARGETS) -std=gnu99 -ffreestanding -O2 -Wall -Wextra
		mv ./*.o $(OBJECTDIR)
		$(CC)-gcc -T linker.ld -o $(BOOTDIR)/$(KERNELTARGET).bin -ffreestanding -O2 -nostdlib $(OBJECTS) -lgcc

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

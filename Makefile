BOOTDIR := ./multiboot
OBJECTDIR := ./bin
SRCDIR := ./src
ASMDIR := $(SRCDIR)/asm
DRIVERSDIR := $(SRCDIR)/drivers
INCLUDEDIR := ./include

CC := i686-elf
EMU := qemu-system-i386

OBJECTS := $(OBJECTDIR)/*.o
CTARGETS := $(SRCDIR)/*.c $(DRIVERSDIR)/*.c
ASMTARGETS := $(ASMDIR)/*.S

KERNELTARGET := kos.bin

default:
		$(CC)-as $(BOOTDIR)/boot.s -o $(OBJECTDIR)/boot.o
		nasm -f elf32 $(ASMDIR)/__gdt.S -o $(OBJECTDIR)/__gdt.o
		nasm -f elf32 $(ASMDIR)/__idt.S -o $(OBJECTDIR)/__idt.o
		$(CC)-gcc -I $(INCLUDEDIR) -c $(CTARGETS) -std=gnu99 -ffreestanding -O2 -Wall -Wextra
		mv ./*.o $(OBJECTDIR)
		$(CC)-gcc -T linker.ld -o $(OBJECTDIR)/$(KERNELTARGET) -ffreestanding -O2 -nostdlib $(OBJECTS) -lgcc

run:
		$(EMU) -kernel $(OBJECTDIR)/$(KERNELTARGET)

clean:
		rm -rf $(OBJECTDIR)/*.*

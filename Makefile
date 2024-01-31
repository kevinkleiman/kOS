BOOTDIR := ./multiboot
OBJECTDIR := ./bin
SRCDIR := ./src
ASMDIR := $(SRCDIR)/asm
INCLUDEDIR := ./include

OBJECTS := $(OBJECTDIR)/*.o
CTARGETS := $(SRCDIR)/*.c
ASMTARGETS := $(ASMDIR)/*.S

KERNELTARGET := kos.bin

default:
		i686-elf-as $(BOOTDIR)/boot.s -o $(OBJECTDIR)/boot.o
		nasm -f elf32 $(ASMDIR)/__gdt.S -o $(OBJECTDIR)/__gdt.o
		i686-elf-gcc -I $(INCLUDEDIR) -c $(CTARGETS) -std=gnu99 -ffreestanding -O2 -Wall -Wextra
		mv ./*.o $(OBJECTDIR)
		i686-elf-gcc -T linker.ld -o $(OBJECTDIR)/$(KERNELTARGET) -ffreestanding -O2 -nostdlib $(OBJECTS) -lgcc

run:
		qemu-system-i386 -kernel $(OBJECTDIR)/$(KERNELTARGET)

clean:
		rm -rf $(OBJECTDIR)/*.*

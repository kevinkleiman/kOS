ENTRY(_start)
 
SECTIONS
{
    . = 0x00100000;

	.multiboot BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
	}

    .boot BLOCK(4K) : ALIGN(4K)
    {
        *(.boot)
    }

    . += 0xC0000000;
    _kernel_start = .;

	.text ALIGN(4K) : AT(ADDR(.text) - 0xC0000000)
	{
		*(.text)
	}
 
	/* Read-only data. */
	.rodata ALIGN(4K) : AT(ADDR(.rodata) - 0xC0000000)
	{
		*(.rodata)
	}
 
	/* Read-write data (initialized) */
	.data ALIGN(4K) : AT(ADDR(.data) - 0xC0000000)
	{
		*(.data)
	}
 
	/* Read-write data (uninitialized) and stack */
	.bss ALIGN(4K) : AT(ADDR(.bss) - 0xC0000000)
	{
		*(COMMON)
		*(.bss)
        _kernel_end = .;
	}

}

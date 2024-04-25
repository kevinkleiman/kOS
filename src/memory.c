#include "memory.h"
#include "multiboot.h"
#include "stddef.h"
#include "stdio.h"


/* Define initial page directory */
static page_dir_t page_directory[PD_ENTRIES] __attribute__((aligned(PAGE_SIZE)));

/* Parse memory map from GRUB */
void memory_init(volatile multiboot_info_t* mbd)
{
    // set first page directory entry to initial directory
    page_directory[0] = initial_page_dir;

    uint32_t mem_high = mbd->mem_upper;
    uint32_t phys_alloc_start = (mem_high + 0xFFF) & ~0xFFF;

    if(!mbd->flags >> 6 & 0x1) {
        __panic("Invalid mmap!");
    }

    for(uint32_t i = 0; i < mbd->mmap_length; i += sizeof(multiboot_memory_map_t)) {
        multiboot_memory_map_t* mbentry = (multiboot_memory_map_t*) (mbd->mmap_addr + i);

        // do something with memory map
        printk("ENTRY: low=%x len_low=%x type=%d\n", mbentry->addr_low, mbentry->len_low, mbentry->type);
    }
}

/* Init physical memory manager */
static void __pmm_init()
{
    page_directory[1].data = PTE_ENTRY(0x0, SUP_RW_PRESENT);
}


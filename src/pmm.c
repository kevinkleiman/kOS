/**
 * 
 * @copyright Copyright (c) 2024, Kevin Kleiman, All Rights Reserved
 * 
 * This is the kernel for yet another hobbyOS designed and developed by Kevin Kleiman.
 * Feel free to copy, use, edit, etc. anything you see 
 *
 * This was originally designed to try writing a ring0 math library but I soon realized,
 * I should just make a full-blown kernel. It has been a great learning experience and I
 * implore anyone even remotely interested to fork, play around, contribute, whatever
 * you want. 
 *
 * For now, it's pretty barebones and shitty, but hopefully that will change with time.
 * Have fun creating kOS (pronounced "Chaos")
 */

#include "pmm.h"
#include "multiboot.h"
#include "stddef.h"
#include "stdio.h"
#include "memory.h"


/* Get initial page directory defined in boot.S */
static page_dir_t page_directory[PD_ENTRIES] __attribute__((aligned(PG_SIZE)));

/* Print memory regions from multiboot memory map */
static void display_mm(volatile multiboot_info_t* mbd)
{
    for(uint32_t i = 0; i < mbd->mmap_length; i += sizeof(multiboot_memory_map_t)) {
        multiboot_memory_map_t* mbentry = (multiboot_memory_map_t*) (mbd->mmap_addr + i);

        printk("Region -- addr_low=%x addr_high=%x len_low=%x len_high=%x type=%d\n",
               mbentry->addr_low, mbentry->addr_high, mbentry->len_low, mbentry->len_high,
               mbentry->type);
    }
}

/* Init physical memory manager */
void pmm_init(volatile multiboot_info_t* mbd)
{
    // set first page directory entry to initial directory
    page_directory[0] = initial_page_dir;
    page_directory[1] = initial_page_dir;

    uint32_t mem_high = mbd->mem_upper;
    uint32_t phys_alloc_start = (mem_high + 0xFFF) & ~0xFFF;
    uint32_t size = 0;

    if(!mbd->flags >> 6 & 0x1) {
        __panic("Invalid mmap!");
    }

    for(uint32_t i = 0; i < mbd->mmap_length; i += sizeof(multiboot_memory_map_t)) {
        multiboot_memory_map_t* mbentry = (multiboot_memory_map_t*) (mbd->mmap_addr + i);
    }
}

void* pm_alloc()
{
    return (void*) 0x0;
}

int pm_free()
{
    return 0;
}

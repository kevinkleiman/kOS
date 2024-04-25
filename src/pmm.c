#include "pmm.h"
#include "multiboot.h"
#include "stddef.h"
#include "stdio.h"
#include "memory.h"

static page_dir_t page_directory[PD_ENTRIES] __attribute__((aligned(PG_SIZE)));

/* Init physical memory manager */
void pmm_init(volatile multiboot_info_t* mbd)
{
    // set first page directory entry to initial directory
    page_directory[0] = initial_page_dir;

    uint32_t mem_high = mbd->mem_upper;
    uint32_t phys_alloc_start = (mem_high + 0xFFF) & ~0xFFF;
    uint32_t size = 0;

    if(!mbd->flags >> 6 & 0x1) {
        __panic("Invalid mmap!");
    }

    for(uint32_t i = 0; i < mbd->mmap_length; i += sizeof(multiboot_memory_map_t)) {
        multiboot_memory_map_t* mbentry = (multiboot_memory_map_t*) (mbd->mmap_addr + i);

        if (mbentry->type == MULTIBOOT_MEMORY_AVAILABLE)
        {
            size += mbentry->len_low;
        }
    }

    printk("Free memory=%d MB\n", size / MB);
}

void* pm_alloc()
{
    return (void*) 0x0;
}

int pm_free()
{
    return 0;
}

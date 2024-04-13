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

    printk("initial_page_dir->data %x\n", initial_page_dir.page_dir.pt_addr);

    multiboot_mmap_entry_t* tmp = (multiboot_mmap_entry_t*) mbd->mmap_addr;
}

/* Init physical memory manager */
void pmm_init()
{
    page_directory[1].data = PTE_ENTRY(0x0, SUP_RW_PRESENT);
}

/* Invalidate a page of PAGE_SIZE */
static inline void invalidate_page(uint32_t vaddr)
{
    __asm__ __volatile__ ("invlpg %0" :: "m"(vaddr));
}

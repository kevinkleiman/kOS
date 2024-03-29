#include "memory.h"
#include "stddef.h"

uint32_t page_directory[PD_ENTRIES] __attribute__((aligned(4096)));


void memory_init(volatile multiboot_info_t* mbd)
{
    uint32_t mem_high = mbd->mem_upper;
    uint32_t phys_alloc_start = (mem_high + 0xFFF) & ~0xFFF;

    for (size_t i = 0; i < PD_ENTRIES; ++i) {
        page_directory[i] = PD_NOT_PRESENT;
    }
}

void pmm_init()
{

}

void invalidate_page(uint32_t vaddr)
{
    __asm__ __volatile__ ("invlpg %0" :: "m"(vaddr));
}

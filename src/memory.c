#include "memory.h"


void memory_init(volatile multiboot_info_t* mbd)
{
    uint32_t mem_high = mbd->mem_upper;
    uint32_t phys_alloc_start = (mem_high + 0xFFF) & ~0xFFF;
}

void pmm_init()
{

}

void invalidate_page(uint32_t vaddr)
{
    __asm__ __volatile__ ("invlpg %0" :: "m"(vaddr));
}

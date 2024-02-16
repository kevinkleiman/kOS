#include <stddef.h>
#include "memory.h"
#include "multiboot.h"
#include "stdio.h"

void memory_init(multiboot_info_t* bootinfo)
{
    multiboot_mmap_entry_t* mmap_base = (multiboot_mmap_entry_t*) bootinfo->mmap_addr;

    // loop through each multiboot info struct
    for (size_t i = 0; i < bootinfo->mmap_length; i += sizeof(multiboot_mmap_entry_t)) {
        multiboot_mmap_entry_t* cur = (multiboot_mmap_entry_t*) (mmap_base + i);
    }
}

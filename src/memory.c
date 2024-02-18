#include "memory.h"
#include "stdio.h"
#include "tty.h"


void memory_init(volatile multiboot_info_t* mbd)
{
    multiboot_mmap_entry_t* mmap_base = (multiboot_mmap_entry_t*) mbd->mmap_addr;
    
    int n_entries = (mbd->mmap_length / sizeof(multiboot_mmap_entry_t));

    // loop through each multiboot info struct
    for (size_t i = 0; i < n_entries; i++) {
        // printf("type: %x | ", mmap_base[i].type);
    }
}

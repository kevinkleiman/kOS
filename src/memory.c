#include "memory.h"
#include "stdio.h"


void memory_init(volatile multiboot_info_t* mbd)
{
    multiboot_mmap_entry_t* cur;
    multiboot_mmap_entry_t* mmap_base = (multiboot_info_t*) mbd->mmap_addr;
    
    printf("%s\n", mbd->boot_loader_name);

    // loop through each multiboot info struct
    for (size_t i = 0; i < mbd->mmap_length; i += sizeof(multiboot_mmap_entry_t)) {
        cur = (multiboot_mmap_entry_t*) (mmap_base + i);
        printf("type: %d | ", cur->type);
    }
    
    // BOOT_LOG("Memory map loaded.");
}

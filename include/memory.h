#pragma once

#include "multiboot.h"


#define PAGE_DIR_ENTRIES 1024
#define PAGE_SIZE 4096

typedef struct page_dir {
    uint8_t first;

} page_dir_t;

void memory_init(volatile multiboot_info_t* mbd);

extern page_dir_t intial_page_dir;

extern uint32_t _kernel_start;
extern uint32_t _kernel_end;

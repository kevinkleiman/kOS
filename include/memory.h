#pragma once

#include "multiboot.h"


#define PD_ENTRIES      1024
#define PD_NOT_PRESENT  0x00000002
#define SUP_RW_PRESENT  0x00000003
#define PAGE_SIZE       4096

#define PTE_ENTRY(pte, attr) \
    ((uint32_t) pte) | attr

typedef union {
    uint32_t data;

    struct {
        uint32_t present : 1;
        uint32_t rw : 1;
        uint32_t us : 1;
        uint32_t write_through : 1;
        uint32_t cache_disable : 1;
        uint32_t accessed : 1;
        uint32_t avail_low : 1;
        uint32_t page_size : 1;
        uint32_t avail_high : 4;
        uint32_t pt_addr : 20;
    } page_dir;
} page_dir_t;

typedef union {
    uint32_t data;

    struct {
        uint32_t present : 1;
        uint32_t rw : 1;
        uint32_t us : 1;
        uint32_t write_through : 1;
        uint32_t cache_disable : 1;
        uint32_t accessed : 1;
        uint32_t avail_low : 1;
        uint32_t page_size : 1;
        uint32_t global : 1;
        uint32_t avail_high : 3;
        uint32_t pt_addr : 20;
    } pte;
} pte_t;

struct freelist {
    struct freelist* next;
};

typedef struct {
    struct freelist* freelist;
} mmap_t;

void memory_init(volatile multiboot_info_t* mbd);

/* Invalidate a page of PAGE_SIZE */
static inline void __invlpg(uint32_t vaddr)
{
    __asm__ __volatile__ ("invlpg %0" :: "m"(vaddr));
}

extern page_dir_t initial_page_dir;

extern uint32_t _kernel_start;
extern uint32_t _kernel_end;

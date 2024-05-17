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

#pragma once

#include <stdint.h>

#define GDT_ENTRIES 5

#define GDT_HIGH_LIMIT          0xFFFFFFFF
#define GDT_KERNEL_CODE         0x9A
#define GDT_KERNEL_DATA         0x92

#define GDT_USER_CODE           0xFA
#define GDT_USER_DATA           0xF2

#define GDT_KERNEL_GRANULARITY  0xCF

#define GDT_BASE_LOW(base)      ((base) & 0xFFFF)
#define GDT_BASE_MID(base)      (((base) >> 16) & 0xFF)
#define GDT_BASE_HIGH(base)     (((base) >> 24) & 0xFF)

#define GDT_LIMIT(limit)        ((limit) & 0xFFFF)
#define GDT_FLAGS(limit)        (((limit) >> 16) & 0x0F)
#define GDT_GRANULARITY(gran)   ((gran) & 0xF0)

typedef struct {
    uint16_t    limit;
    uint16_t    base_low;
    uint8_t     base_mid;
    uint8_t     access;
    uint8_t     flags;
    uint8_t     base_high;
} __attribute__((packed)) gdt_entry_t;

typedef struct {
    uint16_t    limit;
    gdt_entry_t* base;
} __attribute__((packed)) gdtr_t;

void gdt_init();

extern void load_gdt(gdtr_t*);

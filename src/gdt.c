#include "drivers/tty.h"
#include "gdt.h"

static gdt_entry_t gdt_entries[GDT_ENTRIES];
static gdtr_t gdt_ptr;

void gdt_init() 
{
    gdt_ptr.limit = (sizeof(gdt_entries) * GDT_ENTRIES) - 1;
    gdt_ptr.base = &gdt_entries;

    set_gdt_entry(0, 0, 0, 0, 0);
    set_gdt_entry(1, 0, GDT_HIGH_LIMIT, GDT_KERNEL_CODE, GDT_KERNEL_GRANULARITY);
    set_gdt_entry(2, 0, GDT_HIGH_LIMIT, GDT_KERNEL_DATA, GDT_KERNEL_GRANULARITY);
    set_gdt_entry(3, 0, GDT_HIGH_LIMIT, 0x03, GDT_KERNEL_GRANULARITY);
    set_gdt_entry(4, 0, GDT_HIGH_LIMIT, 0x03, GDT_KERNEL_GRANULARITY);

    load_gdt(&gdt_ptr);

    BOOT_LOG("GDT Loaded.")
}

void set_gdt_entry(uint32_t index, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) 
{
    gdt_entries[index].base_low = GDT_BASE_LOW(base);
    gdt_entries[index].base_mid = GDT_BASE_MID(base);
    gdt_entries[index].base_high = GDT_BASE_HIGH(base);

    gdt_entries[index].limit = GDT_LIMIT(limit);
    gdt_entries[index].flags = GDT_FLAGS(limit);
    gdt_entries[index].flags |= GDT_GRANULARITY(granularity);
    
    gdt_entries[index].access = access;
}

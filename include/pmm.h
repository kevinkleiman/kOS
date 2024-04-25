#pragma once
#include "multiboot.h"

void pmm_init(volatile multiboot_info_t* mbd);
void* pm_alloc();
int pm_free();

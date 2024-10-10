#include <stdint.h>
#include "multiboot.h"
#include "kutils.h"


/**
 * Define all Kernel globals here
 */
static uint32_t g_num_cores = 0;

static multiboot_info_t* g_mbd = NULL;
static uint32_t g_heap_start;
static uint32_t g_heap_end;

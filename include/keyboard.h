#pragma once

#include "idt.h"

static void keyboard_callback(i_register_t registers);
void keyboard_init();

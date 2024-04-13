#pragma once

#include "interrupt.h"

#define SYSCALL_INTERRUPT 0x80
#define SYSCALL_MAX 10

void syscall_init();

static void __write(i_register_t* registers);
static void __open(i_register_t* registers);

typedef void (*syscall_t)(i_register_t* registers);

extern void syscall_handler();

#pragma once

#define SYSCALL_INTERRUPT 0x80

void syscall_init();

void __syscall_write();
void __syscall_open();

typedef void (*syscall_t)();

extern void syscall_handler();

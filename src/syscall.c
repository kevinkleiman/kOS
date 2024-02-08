#include "syscall.h"
#include "interrupt.h"
#include "stdio.h"
#include "tty.h"

static syscall_t syscall_entries[10] = {
    __syscall_write,
    __syscall_open
};

__attribute__((naked)) void syscall_push_regs() 
{
    __asm__ __volatile__(
                         "pushl %eax\n"
                         "pushl %gs\n"
                         "pushl %fs\n"
                         "pushl %es\n"
                         "pushl %ds\n"

                         "pushl %ebp\n"
                         "pushl %edi\n"
                         "pushl %esi\n"
                         "pushl %edx\n"
                         "pushl %ecx\n"
                         "pushl %ebx\n"
                         "pushl %esp\n"
                        );
}

__attribute__((naked)) void syscall_pop_regs() 
{
    __asm__ __volatile__(
                         "addl $4, %esp\n"

                         "popl %ebx\n"
                         "popl %ecx\n"
                         "popl %edx\n"

                         "popl %esi\n"
                         "popl %edi\n"
                         "popl %esp\n"

                         "popl %ds\n"
                         "popl %es\n"
                         "popl %fs\n"
                         "popl %gs\n"

                         "addl $4, %esp\n"
                        );
}

void syscall_callback(i_register_t registers) 
{
    // check that eax does not overflow max syscalls
    if (registers.eax > (SYSCALL_MAX - 1)) {
        panic("Invalid syscall.");
    }

    // lookup syscall from table and call
    syscall_entries[registers.eax]();
}

void syscall_init() 
{
    register_interrupt_handler(128, syscall_callback); 

    BOOT_LOG("syscalls initialized.")
}

void __syscall_write() 
{
    printf("syscall 1\n");
}

void __syscall_open() 
{
    printf("syscall 2\n");
}


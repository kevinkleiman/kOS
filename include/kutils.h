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

/* For fast error handling */
#define KASSERT_GOTO_FAIL(__cond) do { if (__cond) { goto fail; } } while(0)

/* Assert condition with panic failover */
#define KASSERT(__cond, __s) \
    do { if (__cond) { kpanic(__s); } } while(0)

/* Null typdef */
#define NULL (void *) 0x0

/* Type for checking common return values (success/fail) */
typedef enum {
    SUCCESS,
    ERROR_UNKNOWN,
    ERROR_CONFIGURE,
    ERROR_IN_USE,
    ERROR_TIMEOUT
} retval;


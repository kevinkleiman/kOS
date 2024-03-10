
#![no_std]
#![no_main]

/**
 *
 * @copyright Copyright (c) 2024, Kevin Kleiman, All Rights Reserved
 * 
 * Yes, kOS supports Rust. This is linked as a static library to the kernel
 * Feel free to write drivers in whichever language you choose (C, asm, Rust) 
 *
 * All rust functions are prefixed with __ to improve kernel readability
 */

#[path = "../src/rs/cdef.rs"] mod cdef;
#[path = "../src/drivers/rs/driver.rs"] mod driver;

use core::panic::PanicInfo;

// Check rust has been linked properly
#[no_mangle]
pub extern "C" fn __init() -> u32 {
    return 1
}

#[panic_handler]
fn _panic(_info: &PanicInfo) -> ! {
    cdef::panic("RPANIC!\0");
}

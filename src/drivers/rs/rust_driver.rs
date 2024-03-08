#![no_std]
#![no_main]

use core::panic::PanicInfo;

/// This function is called on panic.
#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop {}
}

#[no_mangle]
pub extern "C" fn r_driver_init() -> ! {
    loop {}
}

#[no_mangle]
pub extern "C" fn r_add(a: u32, b: u32) -> u32 {
    return a + b
}

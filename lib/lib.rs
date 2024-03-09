
#![no_std]
#![no_main]

// setup paths to src (prob not great ik)
#[path = "../src/rs/cdef.rs"] mod cdef;
#[path = "../src/drivers/rs/driver.rs"] mod driver;

use core::panic::PanicInfo;

// Check rust has been linked properly
#[no_mangle]
pub extern "C" fn __init() -> u32 {
    // cdef::tty_write("\nRust static lib init.\n\0");

    return 1
}

#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop {}
}

// define extern kernel (C) functions
mod alias {
    extern "C" {
        pub fn tty_write(buf: *const u8);
        pub fn panic(buf: *const u8);
    }
}

pub fn tty_write(buf: &str) {
    unsafe { alias::tty_write(buf.as_ptr()); }
}


pub fn panic(buf: &str) -> ! {
    unsafe { alias::panic(buf.as_ptr()); }
    loop {}
}

// define extern kernel (C) functions
mod alias {
    extern "C" {
        pub fn tty_write(buf: *const u8);
        pub fn panic(buf: *const u8);
        pub fn itoa(value: i32, buf: *const u8, base: i32);
    }
}

pub fn tty_write(buf: &str) {
    unsafe { alias::tty_write(buf.as_ptr()); }
}

pub fn itoa(value: i32, buf: &str, base: i32) {
    unsafe { alias::itoa(value, buf.as_ptr(), base); }
}

pub fn panic(buf: &str) -> ! {
    unsafe { alias::panic(buf.as_ptr()); }
    loop {}
}

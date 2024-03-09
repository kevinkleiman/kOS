// define extern kernel (C) functions
mod alias {
    extern "C" {
        pub fn tty_write(buf: *const u8);
    }
}


pub fn tty_write(buf: &str) {
    unsafe { alias::tty_write(buf.as_ptr()); }
}

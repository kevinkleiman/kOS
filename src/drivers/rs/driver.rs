#[path = "../../rs/cdef.rs"] mod cdef;

#[no_mangle]
pub extern "C" fn __r_driver_check() -> u32 {
    return 1;
}

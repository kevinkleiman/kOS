#[path = "../../rs/cdef.rs"] mod cdef;

#[no_mangle]
pub extern "C" fn __foo() -> u32 {
    return 1;
}

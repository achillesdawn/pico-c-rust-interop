#![no_std]

use core::panic::PanicInfo;

#[panic_handler]
fn panik(_panic_info: &PanicInfo) -> ! {
    loop {}
}

extern "C" {
    // C function declarations go here
    // extern C functions are by nature unsafe
    // fn printf(format: *const u8, ...);
    
}

#[no_mangle]
pub extern "C" fn rusty_add(first: u16, second: u16) -> u16 {
    first + second
}

#[no_mangle]
pub extern "C" fn array_test(buf: *mut u8, len: cty::size_t) -> () {
    let data_slice = unsafe { core::slice::from_raw_parts_mut(buf, len) };

    for (idx, byte) in data_slice.iter_mut().enumerate() {
        *byte = idx as u8;
    }
}



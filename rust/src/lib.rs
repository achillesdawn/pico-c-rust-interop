#![no_std]

use core::panic::PanicInfo;

#[panic_handler]
fn panik(_panic_info: &PanicInfo) -> ! {
    loop {}
}

#[no_mangle]
pub extern "C" fn rusty_add(first: u16, second: u16) -> u16 {
    first + second
}

#[no_mangle]
pub extern "C" fn array_test(buf: *mut u8, len: usize) -> () {
    let data_slice = unsafe { core::slice::from_raw_parts_mut(buf, len) };

    for byte in data_slice.iter_mut() {
        *byte = 7;
    }
}

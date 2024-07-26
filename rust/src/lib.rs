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

    let mut v: heapless::Vec<u8, 20> = heapless::Vec::new();
    for (_, byte) in data_slice.iter_mut().enumerate() {
        v.push(*byte).unwrap();
    }

    for (idx, item) in v.iter().rev().enumerate() {
        data_slice[idx] = *item;
    }
}

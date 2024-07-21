#![no_std]

use core::panic::PanicInfo;

#[panic_handler]
fn panik(_panic_info: &PanicInfo) -> !{
    loop {
        
    }
}

#[no_mangle]
pub extern "C" fn rusty_add(first: u16, second: u16) -> u16 {
    first + second
}

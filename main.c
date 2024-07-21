#include <inttypes.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pico/stdlib.h"

uint16_t rusty_add(uint16_t first, uint16_t second);


const uint8_t PIN_LED = 15;


volatile bool led_state = false;



bool repeating_toogle_led() {
    led_state = !led_state;
    gpio_put(PIN_LED, led_state);
    return true;
}

struct repeating_timer *setup_led() {
    printf("initializing led\n");
    gpio_set_dir(PIN_LED, true);
    gpio_put(PIN_LED, true);

    struct repeating_timer *led_timer =
        calloc(1, sizeof(struct repeating_timer));
    add_repeating_timer_ms(500, repeating_toogle_led, NULL, led_timer);
    printf("done\n");
    return led_timer;
}


int main() {
    stdio_init_all();

    sleep_ms(2000);

    printf("initializing\n");

    const uint PIN_MASK = (1 << PIN_LED);
    gpio_init_mask(PIN_MASK);

    struct repeating_timer *led_timer = setup_led();

    while (true) {
        uint16_t answer = rusty_add(10u, 20u);
        printf("%d", answer);
        sleep_ms(500);
    }
}

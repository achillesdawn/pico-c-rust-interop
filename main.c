#include <inttypes.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pico/stdlib.h"
#include "rust/bindings.h"

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

void print_uint8_array(const uint8_t *data, size_t len) {
    printf("Array: [");
    for (size_t i = 0; i < len; i++) {
        printf("%u", data[i]); 
        if (i < len - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main() {
    stdio_init_all();

    sleep_ms(2000);

    printf("initializing\n");

    const uint PIN_MASK = (1 << PIN_LED);
    gpio_init_mask(PIN_MASK);

    struct repeating_timer *led_timer = setup_led();

    uint8_t buffer[20];

    while (true) {
        uint16_t answer = rusty_add(10u, 20u);
        printf("%d\n", answer);
        sleep_ms(500);

        array_test(buffer, 20);
        print_uint8_array(buffer, 20);
    }
}

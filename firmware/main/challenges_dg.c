#include <stdint.h>

void led_solo_binary(uint8_t *input) {

    uint32_t i;
    uint8_t b, n;

    while(true) {
        // tx input
        for (i=0; i< LED_SOLO_BINARY_SIZE; i++) {
            for (b=7; b!=0; b--) {
                n = (input[i]>>b)&1;
                gpio_set_level(BLUE_LED_PIN, n);
                vTaskDelay(10 / portTICK_RATE_MS); // between bits
            }
        }
        // blink red between repeats
        gpio_set_level(BLUE_LED_PIN, 1);
        for (b=6; b!=0; b--) {
            gpio_set_level(RED_LED_PIN, b%2);
            vTaskDelay(500 / portTICK_RATE_MS);
        }
        gpio_set_level(RED_LED_PIN, 1);
    }
}

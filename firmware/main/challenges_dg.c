#include <stdint.h>

void led_solo_binary(uint8_t *input, uint32_t size) {

    uint32_t i;
    uint8_t b, n;

    while(true) {
        // tx input
        for (i=0; i< size; i++) {
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

void led_rgb_binary(uint32_t *input, uint32_t size) {
    uint32_t i;
    uint8_t r,g,b;
    while(true) {
        for (i=0; i< size; i++) {
            r = (input[i]>>16) & 0xf;
            g = (input[i]>>8)  & 0xf;
            b = input[i] & 0xf;

            gpio_set_level(RED_LED_PIN, (r>1)?0:1);
            gpio_set_level(GREEN_LED_PIN, (g>1)?0:1);
            gpio_set_level(BLUE_LED_PIN, (b>1)?0:1);
            vTaskDelay(10 / portTICK_RATE_MS); // between bits
        }
        // blink UV between repeats
        gpio_set_level(RED_LED_PIN, 1);
        gpio_set_level(GREEN_LED_PIN, 1);
        gpio_set_level(BLUE_LED_PIN, 1);
        for (b=6; b!=0; b--) {
            gpio_set_level(UV_LED_PIN, b%2);
            vTaskDelay(500 / portTICK_RATE_MS);
        }
        gpio_set_level(UV_LED_PIN, 1);
    }
}

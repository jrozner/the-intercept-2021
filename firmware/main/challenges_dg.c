#include <stdint.h>

void led_solo_binary(uint8_t *input) {

    uint32_t i=0;
    uint8_t b=0;
    bool n;

    while(true) {
        n = b%2;
        gpio_set_level(BLUE_LED_PIN, n);
        vTaskDelay(500 / portTICK_RATE_MS); // between bits
        if (b == 7) {
            b = 0;
            i++;
        } else {
            b++;
        }
        //vTaskDelay(1000 / portTICK_RATE_MS); // between message repeat
    }
}

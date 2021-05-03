#include <stdint.h>
#include "driver/ledc.h"

void led_rgb_variable(uint32_t *input, uint32_t size) {

    uint32_t freq = 5000;
    int i;

    ledc_timer_config_t timer_conf = {
         .speed_mode = LEDC_HIGH_SPEED_MODE,
         .bit_num = LEDC_TIMER_10_BIT,
         .timer_num = LEDC_TIMER_1,
         .duty_resolution = 8,
         .freq_hz = freq,
    };
    ledc_timer_config(&timer_conf);
    ledc_channel_config_t ledc_conf = {
        .gpio_num = RED_LED_PIN,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .channel = LEDC_CHANNEL_1,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_1,
        .duty = 0x0,
    };
    ledc_channel_config(&ledc_conf);

    ledc_timer_config_t timer_conf2 = {
         .speed_mode = LEDC_HIGH_SPEED_MODE,
         .bit_num = LEDC_TIMER_10_BIT,
         .timer_num = LEDC_TIMER_2,
         .duty_resolution = 8,
         .freq_hz = freq,
    };
    ledc_timer_config(&timer_conf2);
    ledc_channel_config_t ledc_conf2 = {
        .gpio_num = GREEN_LED_PIN,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .channel = LEDC_CHANNEL_2,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_2,
        .duty = 0x0,
    };
    ledc_channel_config(&ledc_conf2);

    ledc_timer_config_t timer_conf3 = {
         .speed_mode = LEDC_HIGH_SPEED_MODE,
         .bit_num = LEDC_TIMER_10_BIT,
         .timer_num = LEDC_TIMER_3,
         .duty_resolution = 8,
         .freq_hz = freq,
    };
    ledc_timer_config(&timer_conf3);
    ledc_channel_config_t ledc_conf3 = {
        .gpio_num = BLUE_LED_PIN,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .channel = LEDC_CHANNEL_3,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_3,
        .duty = 0x0,
    };
    ledc_channel_config(&ledc_conf3);

    uint8_t r,g,b;

    while (true) {
        for (i=0; i<size; i++) {
            r = (input[i] >>16) & 0xff;
            g = (input[i] >>8) & 0xff;
            b = input[i] & 0xff;

            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1, r);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1);

            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_2, g);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_2);

            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_3, b);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_3);

            vTaskDelay(10 / portTICK_PERIOD_MS);

        }
        // blink UV between repeats
        gpio_set_level(RED_LED_PIN, 1);
        gpio_set_level(GREEN_LED_PIN, 1);
        gpio_set_level(BLUE_LED_PIN, 1);
        for (i=0; i!=0; i--) {
            gpio_set_level(UV_LED_PIN, i%2);
            vTaskDelay(500 / portTICK_RATE_MS);
        }
        gpio_set_level(UV_LED_PIN, 1);
    }
}

void led_solo_variable(uint8_t *input, uint32_t size) {

    uint32_t freq = 5000;
    int i;

    ledc_timer_config_t timer_conf = {
         .speed_mode = LEDC_HIGH_SPEED_MODE,
         .bit_num = LEDC_TIMER_10_BIT,
         .timer_num = LEDC_TIMER_1,
         .duty_resolution = 8,
         .freq_hz = freq,
    };
    ledc_timer_config(&timer_conf);
    ledc_channel_config_t ledc_conf = {
        .gpio_num = RED_LED_PIN,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .channel = LEDC_CHANNEL_1,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_1,
        .duty = 0x0,
    };
    ledc_channel_config(&ledc_conf);

    while (true) {
        for (i=0; i<size; i++) {
            ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1, input[i]);
            ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_1);
            vTaskDelay(10 / portTICK_PERIOD_MS);

        }
        // blink UV between repeats
        gpio_set_level(RED_LED_PIN, 1);
        gpio_set_level(GREEN_LED_PIN, 1);
        gpio_set_level(BLUE_LED_PIN, 1);
        for (i=0; i!=0; i--) {
            gpio_set_level(UV_LED_PIN, i%2);
            vTaskDelay(500 / portTICK_RATE_MS);
        }
        gpio_set_level(UV_LED_PIN, 1);
    }
}

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

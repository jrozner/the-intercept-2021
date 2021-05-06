#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "driver/ledc.h"
#include "driver/rmt.h"

#include "ir_builder_rmt_nec.c"
#include "ir_tools.h"

#define BAUDOT_SIZE 371
void challenge_baudot(const uint8_t *input, uint32_t size);
const uint8_t data_baudot[] = {14, 3, 7, 5, 1, 4, 6, 4, 13, 18, 24, 3, 16, 4, 11, 7, 5, 16, 4, 18, 6, 15, 1, 4, 3, 4, 25, 7, 16, 16, 1, 10, 13, 18, 21, 8, 6, 4, 5, 16, 6, 12, 26, 4, 11, 7, 5, 16, 4, 18, 6, 15, 1, 4, 3, 4, 25, 1, 1, 8, 25, 3, 25, 21, 4, 21, 24, 7, 4, 19, 24, 12, 27, 5, 31, 16, 4, 13, 6, 12, 9, 4, 3, 12, 24, 16, 20, 1, 10, 4, 26, 7, 21, 8, 16, 20, 3, 16, 4, 18, 24, 30, 1, 5, 4, 21, 24, 7, 4, 28, 24, 10, 1, 4, 16, 20, 3, 12, 4, 28, 1, 8, 8, 10, 24, 6, 5, 6, 12, 27, 12, 4, 31, 6, 4, 19, 3, 12, 12, 3, 4, 13, 6, 26, 20, 16, 4, 21, 24, 7, 10, 4, 13, 3, 16, 20, 1, 10, 8, 10, 24, 6, 5, 6, 12, 27, 12, 4, 31, 6, 4, 19, 3, 12, 12, 3, 4, 13, 6, 26, 20, 16, 4, 21, 24, 7, 10, 4, 13, 3, 16, 20, 1, 10, 8, 8, 9, 24, 4, 20, 1, 4, 15, 12, 24, 19, 4, 20, 24, 19, 4, 28, 7, 14, 20, 4, 6, 4, 18, 24, 30, 1, 4, 21, 24, 7, 8, 9, 24, 4, 20, 1, 4, 15, 12, 24, 19, 4, 16, 20, 1, 4, 16, 20, 6, 12, 26, 5, 4, 6, 27, 5, 31, 9, 4, 9, 24, 4, 27, 15, 31, 7, 20, 27, 18, 8, 31, 3, 12, 9, 4, 9, 24, 4, 20, 1, 4, 15, 12, 24, 19, 4, 6, 4, 5, 24, 18, 9, 4, 20, 6, 5, 4, 20, 7, 25, 4, 14, 3, 22, 5, 4, 27, 15, 31, 21, 1, 3, 4, 21, 1, 3, 20, 27, 18, 8, 31, 11, 7, 5, 16, 4, 16, 24, 4, 22, 3, 21, 4, 13, 24, 10, 4, 21, 24, 7, 10, 4, 13, 18, 3, 26, 27, 15, 31, 16, 20, 27, 1, 31, 10, 7, 25, 25, 27, 1, 31, 10, 25, 3, 7, 9, 27, 23, 31, 16, 5, 27, 18, 4, 25};

void challenge_baudot(const uint8_t *input, uint32_t size) {    
    uint32_t i;
    uint8_t d;
    while (true) {
        for (i=0;i<size;i++) {
            for (d=0; d<5; d++) {
                if ((input[i] >> d)&1) {
                    sound(BUZZER_PIN, 700, 80);
                } else {
                    vTaskDelay( 80/portTICK_RATE_MS);
                }
                vTaskDelay( 20/portTICK_RATE_MS);
            } 
        }
        vTaskDelay( 2000 / portTICK_RATE_MS);
    }
}

void led_pov(const uint8_t *input, uint32_t size) {
    uint32_t i, wat;
    uint8_t row, r,g,b,uv,ir;
    while(true) {
        for(i=0; i<size; i++) {
            for(row=0; row<5; row++) {
                uv = ((pov_dict[input[i]]) >> ( 5*row + 0))&1;
                ir = ((pov_dict[input[i]]) >> ( 5*row + 1))&1;
                g = ((pov_dict[input[i]]) >> ( 5*row + 2))&1;
                b = ((pov_dict[input[i]]) >> ( 5*row + 3))&1;
                r = ((pov_dict[input[i]]) >> ( 5*row + 4))&1;

                gpio_set_level(UV_LED_PIN, !uv);
                gpio_set_level(IR_LED_PIN, !ir);
                gpio_set_level(GREEN_LED_PIN, !g);
                gpio_set_level(BLUE_LED_PIN, !b);
                gpio_set_level(RED_LED_PIN, !r);
                
                // GHETTO <10MS DELAY DO NOT REMOVE
                for(wat=0; wat<30000; wat++) {
                    r = wat&0xff;
                }
            }
            gpio_set_level(UV_LED_PIN, 1);
            gpio_set_level(IR_LED_PIN, 1);
            gpio_set_level(GREEN_LED_PIN, 1);
            gpio_set_level(BLUE_LED_PIN, 1);
            gpio_set_level(RED_LED_PIN, 1);
            // GHETTO <10MS DELAY DO NOT REMOVE
            for(wat=0; wat<60000; wat++) {
                r = wat&0xff;
            }
        }
    }
}


void braille_blink(uint8_t c) {
    uint8_t r,g,b,i;

    for (i=0; i<2; i++) {
        g =  (braille_dict[c] >> (3*i+0)) &1;
        b =  (braille_dict[c] >> (3*i+1)) &1;
        r =  (braille_dict[c] >> (3*i+2)) &1;
        gpio_set_level(GREEN_LED_PIN, !g);
        gpio_set_level(BLUE_LED_PIN, !b);
        gpio_set_level(RED_LED_PIN, !r);
        vTaskDelay(300 / portTICK_RATE_MS);

        // wipe between cols
        gpio_set_level(GREEN_LED_PIN, 1);
        gpio_set_level(BLUE_LED_PIN, 1);
        gpio_set_level(RED_LED_PIN, 1);
        vTaskDelay(100 / portTICK_RATE_MS);
    }
}

void led_braille(const uint8_t *input, uint32_t size) {

    uint32_t i;

    // 00 - 25 letters
    // 26 - 28 { | }
    // 29 - 30 Nstart Nstop
    // 31+     1-9 - 0 NOT accounted for

    while(true) {
        for (i=0; i<size; i++) {
            if (input[i] < 26) {
                braille_blink(input[i]);
            } else if ((input[i] == 26) | (input[i] == 28)) {
                braille_blink(27); // 111000 curly brace open
                braille_blink(input[i]); // curly brace identify
            } else if (input[i] > 30) {
                braille_blink(29); // open number Numeric Indicator
                braille_blink(input[i]-31); // normalized "number"
                braille_blink(30); // close number Grade 1 Indicator
            }
        }
        led_blink(UV_LED_PIN);
    }   
}

void led_ir(const uint32_t *input, uint32_t size) {

    uint32_t i, addr, cmd; // big endian NIBBLE order
    // example remote 00ff 906f vs ff00 f609

    rmt_channel_t rmt_channel0 = RMT_CHANNEL_0;
    rmt_item32_t *items = NULL;
    size_t length = 0;
    ir_builder_t *ir_builder = NULL;

    rmt_config_t rmt_tx_config = RMT_DEFAULT_CONFIG_TX(IR_LED_PIN, rmt_channel0);
    rmt_tx_config.flags |= RMT_CHANNEL_FLAGS_INVERT_SIG;
    rmt_tx_config.tx_config.carrier_freq_hz = 38000;
    rmt_tx_config.tx_config.carrier_en = true;
    rmt_config(&rmt_tx_config);
    rmt_driver_install(rmt_channel0, 0, 0);
    ir_builder_config_t ir_builder_config = IR_BUILDER_DEFAULT_CONFIG((ir_dev_t)rmt_channel0);
    ir_builder = ir_builder_rmt_new_nec(&ir_builder_config);

    while (true) {
        for (i=0; i<size; i++) {
            addr = (input[i] >> 16) & 0xffff;
            cmd = input[i] & 0xffff;
            ir_builder->build_frame(ir_builder, addr, cmd);
            ir_builder->get_result(ir_builder, &items, &length);
            rmt_write_items(rmt_channel0, items, length, false);
            vTaskDelay(500 / portTICK_RATE_MS);
        }
        vTaskDelay(2000 / portTICK_RATE_MS);
    }
}


void led_uv(const uint8_t *input, uint32_t size) {
    uint32_t i;

    while (true) {
        for(i=0; i<size; i++) {
            // blip for 30 millis
            gpio_set_level(UV_LED_PIN, 0);
            vTaskDelay(30 / portTICK_PERIOD_MS);
            gpio_set_level(UV_LED_PIN, 1);

            // delay next blip by flag char * 30 millis
            vTaskDelay((30 * input[i]) / portTICK_PERIOD_MS);
        }
        led_blink(RED_LED_PIN);
    }
}

void led_rgb_variable(const uint32_t *input, uint32_t size) {

    uint32_t freq = 5000;
    uint32_t i;
    uint8_t r,g,b;

    ledc_timer_config_t timer_conf = {
         .speed_mode = LEDC_HIGH_SPEED_MODE,
         .bit_num = LEDC_TIMER_10_BIT,
         .timer_num = LEDC_TIMER_1,
//         .duty_resolution = 8,
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
//        .duty_resolution = 8,
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
//       .duty_resolution = 8,
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

            vTaskDelay(20 / portTICK_PERIOD_MS);

        }
        led_blink(UV_LED_PIN);
    }
}

void led_solo_variable(const uint8_t *input, uint32_t size) {

    uint32_t freq = 5000;
    int i;

    ledc_timer_config_t timer_conf = {
         .speed_mode = LEDC_HIGH_SPEED_MODE,
         .bit_num = LEDC_TIMER_10_BIT,
         .timer_num = LEDC_TIMER_1,
//       .duty_resolution = 8,
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
            vTaskDelay(20 / portTICK_PERIOD_MS);

        }
        led_blink(UV_LED_PIN);
    }
}

void led_solo_binary(const uint8_t *input, uint32_t size) {

    uint32_t i;
    uint8_t b, n;

    while(true) {
        // tx input
        for (i=0; i< size; i++) {
            for (b=7; b!=0; b--) {
                n = (input[i]>>b)&1;
                gpio_set_level(BLUE_LED_PIN, n);
                vTaskDelay(20 / portTICK_RATE_MS); // between bits
            }
        }
        led_blink(UV_LED_PIN);
    }
}

void led_rgb_binary(const uint32_t *input, uint32_t size) {
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
            vTaskDelay(20 / portTICK_RATE_MS); // between bits
        }
        led_blink(UV_LED_PIN);
    }
}

void led_blink(int32_t pin) {
    uint8_t b;
    // blink UV between repeats
    gpio_set_level(RED_LED_PIN, 1);
    gpio_set_level(GREEN_LED_PIN, 1);
    gpio_set_level(BLUE_LED_PIN, 1);
    gpio_set_level(UV_LED_PIN, 1);
    gpio_set_level(IR_LED_PIN, 1);
    for (b=6; b!=0; b--) {
        gpio_set_level(pin, b%2);
        vTaskDelay(500 / portTICK_RATE_MS);
    }
    gpio_set_level(pin, 1);
}

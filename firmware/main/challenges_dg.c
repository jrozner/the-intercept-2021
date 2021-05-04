#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "driver/ledc.h"
#include "driver/rmt.h"

#include "ir_builder_rmt_nec.c"
#include "ir_tools.h"

void led_ir(const uint8_t *input, uint32_t size) {

    rmt_channel_t example_tx_channel = RMT_CHANNEL_0;

    uint32_t i=0;

    uint32_t addr = 0x00;
    uint32_t cmd = 0x90;
    rmt_item32_t *items = NULL;
    size_t length = 0;
    ir_builder_t *ir_builder = NULL;

    rmt_config_t rmt_tx_config = RMT_DEFAULT_CONFIG_TX(IR_LED_PIN, example_tx_channel);


    rmt_tx_config.tx_config.carrier_freq_hz = 38000;
    rmt_tx_config.tx_config.carrier_level = 0;
    rmt_tx_config.tx_config.carrier_en = true;
    rmt_tx_config.tx_config.idle_level = 1;
    rmt_tx_config.tx_config.idle_output_en = true;
    
    rmt_config(&rmt_tx_config);
    rmt_driver_install(example_tx_channel, 0, 0);
    ir_builder_config_t ir_builder_config = IR_BUILDER_DEFAULT_CONFIG((ir_dev_t)example_tx_channel);
    ir_builder_config.flags |= IR_TOOLS_FLAGS_PROTO_EXT; // Using extended IR protocols (both NEC and RC5 have extended version)
    ir_builder = ir_builder_rmt_new_nec(&ir_builder_config);

    while (true) {
        ir_builder->build_frame(ir_builder, addr, cmd);
        ir_builder->get_result(ir_builder, &items, &length);
        rmt_write_items(example_tx_channel, items, length, false);
        // Send repeat code
        //vTaskDelay(pdMS_TO_TICKS(ir_builder->repeat_period_ms));
        //ir_builder->build_repeat_frame(ir_builder);
        //ir_builder->get_result(ir_builder, &items, &length);
        //rmt_write_items(example_tx_channel, items, length, false);
//        cmd = (cmd+1)%256;
        vTaskDelay(1000 / portTICK_RATE_MS);
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

#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "driver/ledc.h"
#include "driver/rmt.h"

#include "ir_builder_rmt_nec.c"
#include "ir_tools.h"

#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"

static void wifi_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data) {
    if (event_id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
    } else if (event_id == WIFI_EVENT_AP_STADISCONNECTED) {
        wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) event_data;
    }
}

void wifi_ap2(void) {

    uint32_t i;
    static uint8_t s[] = {'g', 'b', 'k', '1', 't', 'f', 'n', 'A', 'v', '_', '4', '_', '{', 'l', 'n', 's', '0', 'e', 'a', 'e', 'r', 'P', '}'};
    static uint8_t k[] = {5, 13, 18, 0, 12, 1, 20, 16, 2, 19, 14, 11, 6, 10, 4, 3, 8, 17, 9, 7, 21, 15, 22};

    esp_netif_init();
    esp_event_loop_create_default();
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);

    esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL, NULL);

    wifi_config_t wifi_config = {
        .ap = {
            .ssid_len = 1,
            .channel = 1, 
            .password = "lolol27396817rhflawd73gdlaw3fhaw9023urofjis", 
            .max_connection = 1,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK
        },
    };

    while (true) {
        for (i=0; i<sizeof(s); i++) {

            wifi_config.ap.ssid[0] = s[k[i]];

            esp_wifi_set_mode(WIFI_MODE_AP);
            esp_wifi_set_config(WIFI_IF_AP, &wifi_config);
            esp_wifi_start();
            vTaskDelay(10000 / portTICK_RATE_MS);
            esp_wifi_stop();
        }
    }
}


void wifi_ap1(void) {
    esp_netif_init();
    esp_event_loop_create_default();
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);

    esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL, NULL);

    wifi_config_t wifi_config = {
        .ap = {
            .ssid = "flag{n0w_w3_1nt3rc3pt1n}",
            .ssid_len = 24,
            .channel = 1, 
            .password = "93r8yojdo82qololololo238492jalfhe8afhw98ay82", 
            .max_connection = 1,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK
        },
    };

    esp_wifi_set_mode(WIFI_MODE_AP);
    esp_wifi_set_config(WIFI_IF_AP, &wifi_config);
    esp_wifi_start();
}

void cpu_heat(const uint8_t *input, uint32_t size) {
    uint32_t i;
    unsigned long long n, z;
    while (true) {
        for(i=0; i<size; i++) {
            if (input[i] == 82) {
                gpio_set_level(RED_LED_PIN, 0);
                for(n=0; n<(CPU_HEAT_DELAY*1000); n++) {
                    gpio_set_level(BLUE_LED_PIN, 1);
                    z++;
                    if (n % 2000000 == 0) { // watchdog feed that actually works
                        vTaskDelay(10/portTICK_RATE_MS);
                    }
                }
            } else {
                gpio_set_level(RED_LED_PIN, 1);
                vTaskDelay(CPU_HEAT_DELAY/portTICK_RATE_MS);
            }
        }
    }
}

void fan_spin(const uint8_t *input, uint32_t size) {
    uint32_t i;
    while (true) {
        for (i=0; i<size; i++) {
            gpio_set_level(FAN_PIN, input[i]-((i%3)*51));
            vTaskDelay(4000/portTICK_RATE_MS);
        }
        led_blink(UV_LED_PIN);
    }
}

void speaker_sstv(void) {
    while(true) {
        play_audio(audio_table_sstv, sizeof(audio_table_sstv)/sizeof(audio_table_sstv[0]));
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}

void speaker_psk31(void) {
    while(true) {
        play_audio(audio_table_psk31, sizeof(audio_table_psk31)/sizeof(audio_table_psk31[0]));
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}

void buzzer_baudot(const uint8_t *input, uint32_t size) {    
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

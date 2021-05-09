#include <stdio.h>
#include <string.h>
#include <math.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "driver/i2s.h"
#include "esp_log.h"
#include "nvs.h"
#include "nvs_flash.h"

#include "animation.h"
#include "audio.h"
#include "buzzer.h"
#include "dip.h"
#include "data.h"
#include "morse.h"
#include "pins.h"
#include "extra.h"
#include "audio_samples.h"

#include "challenges_jk.c"
#include "challenges_dg.c"

void app_main(void) {
    // gpio config for all output pins
    gpio_config_t io_conf = {
        .intr_type = GPIO_INTR_DISABLE,
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = GPIO_SEL_2 | GPIO_SEL_4 | GPIO_SEL_5 | GPIO_SEL_12 | GPIO_SEL_14 | GPIO_SEL_16 |
                        GPIO_SEL_21 | GPIO_SEL_27 | GPIO_SEL_32 | GPIO_SEL_33,
        .pull_down_en = 0,
        .pull_up_en = 0,
    };

    gpio_config(&io_conf);

    // turn off everything
    gpio_set_level(FAN_PIN, 0);
    gpio_set_level(BUZZER_PIN, 0);
    gpio_set_level(VIBRATOR_PIN, 0);
    gpio_set_level(UV_LED_PIN, 1);
    gpio_set_level(IR_LED_PIN, 1);
    gpio_set_level(GREEN_LED_PIN, 1);
    gpio_set_level(BLUE_LED_PIN, 1);
    gpio_set_level(RED_LED_PIN, 1);
    gpio_set_level(I2S_AIO_PIN, 0);

    spi_bus_config_t dip_cfg = {
        .miso_io_num = DIP_MISO,
        .mosi_io_num = -1,
        .sclk_io_num = DIP_SCLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 32,
    };

    spi_device_interface_config_t dev_cfg = {
        .clock_speed_hz = 10 * 1000 * 1000,
        .mode = 0,
        .spics_io_num = -1,
        .queue_size = 1,
        .pre_cb = load_registers,
    };

    spi_device_handle_t dip_spi;

    esp_err_t ret;

    ret = spi_bus_initialize(HSPI_HOST, &dip_cfg, 0);
    ESP_ERROR_CHECK(ret);
    ret = spi_bus_add_device(HSPI_HOST, &dev_cfg, &dip_spi);
    ESP_ERROR_CHECK(ret);

    i2s_config_t i2s_config = {
        .mode = I2S_MODE_MASTER | I2S_MODE_TX,
        .sample_rate = SAMPLE_RATE,
        .bits_per_sample = SAMPLE_BITS,
        .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
        .communication_format = I2S_COMM_FORMAT_STAND_I2S,
        .dma_buf_count = 8,
        .dma_buf_len = 64,
        .use_apll = false,
        .intr_alloc_flags = 0,
    };

    i2s_pin_config_t pin_config = {
        .bck_io_num = I2S_BCK_PIN,
        .ws_io_num = I2S_WS_PIN,
        .data_out_num = I2S_DO_PIN,
        .data_in_num = I2S_DI_PIN,
    };

    i2s_driver_install(I2S_NUM, &i2s_config, 0, NULL);
    i2s_set_pin(I2S_NUM, &pin_config);

    startup_animation();
    printf(main_uart_splash);

    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        printf("erasing\n");
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);

    nvs_handle_t nvs_handle;
    err = nvs_open("storage", NVS_READWRITE, &nvs_handle);
    ESP_ERROR_CHECK(err);

    uint16_t state = read_state(dip_spi);

    uint8_t initialized = 0;
    err = nvs_get_u8(nvs_handle, "initialized", &initialized);
    switch (err) {
        case ESP_OK:
            break;
        case ESP_ERR_NVS_NOT_FOUND:
            if (state == CODE_UNLOCK) {
                err = nvs_set_u8(nvs_handle, "initialized", 1);
                // TODO(joe): we probably want some better error handling in case this fails
                ESP_ERROR_CHECK(err);

                while (true) {
                    unlock_animation();
                    vTaskDelay(1000 / portTICK_RATE_MS);
                }
            } else {
                while (true) {
                    locked_animation();
                    vTaskDelay(1000 / portTICK_RATE_MS);
                }
            }
            break;
        default:
            while (true) {
                error_animation();
                vTaskDelay(1000 / portTICK_RATE_MS);
            }
            // TODO(joe): do some real error handling here
    }

    nvs_close(nvs_handle);

    //esp_log_level_set("*", ESP_LOG_ERROR); // TODO(dg) set to error for production

    play_audio(audio_table_boot, sizeof(audio_table_boot) / sizeof(audio_table_boot[0]));

    switch (state) {
        case CODE_BUZZER_MORSE:
            challenge_buzzer_morse();
            break;
        case CODE_BUZZER_ADVANCED_MORSE:
            challenge_buzzer_advanced_morse();
            break;
        case CODE_INFRASOUND:
            challenge_infrasound();
            break;
        case CODE_NUMBERS:
            challenge_numbers();
            break;
        case CODE_NUMBERS2:
            challenge_numbers2();
            break;
        case CODE_DTMF:
            challenge_dtmf();
            break;
        case CODE_DTMF2:
            challenge_dtmf2();
            break;
        case CODE_TAP:
            challenge_tap();
            break;
        case CODE_LED_IMG_BINARY:
            led_solo_binary(data_solo_binary, LED_SOLO_BINARY_SIZE);
            break;
        case CODE_LED_IMG_RGB:
            led_rgb_binary(data_rgb_binary, LED_RGB_BINARY_SIZE);
            break;
        case CODE_LED_IMG_REDVAR:
            led_solo_variable(data_solo_var, LED_SOLO_VAR_SIZE);
            break;
        case CODE_LED_IMG_RGBVAR:
            led_rgb_variable(data_rgb_var, LED_RGB_VAR_SIZE);
            break;
        case CODE_LED_UV:
            led_uv(data_uv, LED_UV_SIZE);
            break;
        case CODE_LED_IR:
            led_ir(data_ir1, LED_IR1_SIZE);
            break;
        case CODE_LED_IR2:
            led_ir(data_ir2, LED_IR2_SIZE);
            break;
        case CODE_LED_BRAILLE:
            led_braille(data_braille, LED_BRAILLE_SIZE);
            break;
        case CODE_LED_POV:
            led_pov(data_pov, LED_POV_SIZE);
            break;
        case CODE_BAUDOT:
            buzzer_baudot(data_baudot, BAUDOT_SIZE);
            break;
        case CODE_PSK31:
            speaker_psk31();
            break;
        case CODE_SSTV:
            speaker_sstv();
            break;
        case CODE_FAN1:
            fan_spin(data_fan1, FAN1_SIZE);
            break;
        case CODE_HEAT:
            cpu_heat(data_heat, CPU_HEAT_SIZE);
            break;
        case CODE_WIFI_AP:
            wifi_ap1();
            break;
        case CODE_WIFI_AP2:
            wifi_ap2();
            break;
        case CODE_WIFI_MAC:
            wifi_mac();
            break;
        case CODE_WIFI_PROBE:
            wifi_probe();
            break;
        case CODE_WIFI_APCRACK:
            wifi_apcrack();
            break;
        default:
            while(true)
            {
                error_animation();
                vTaskDelay(1000 / portTICK_RATE_MS);
            }            
    }

    while (1) {
        vTaskDelay(250 / portTICK_RATE_MS);
    }
}

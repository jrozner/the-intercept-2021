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
#include "audio_example_file.h"
#include "esp_log.h"

#include "buzzer.h"
#include "dip.h"
#include "morse.h"
#include "pins.h"

#define SAMPLE_RATE     (16000)
#define SAMPLE_SIZE     (2)
#define SAMPLE_BITS     (SAMPLE_SIZE * 8)
#define I2S_NUM         (0)

static const char *TAG = "main";

void startup_animation() {
    for (int i = 0; i < 2; i++) {
        gpio_set_level(VIBRATOR_PIN, 1);
        gpio_set_level(RED_LED_PIN, 0);
        vTaskDelay(250 / portTICK_RATE_MS);
        gpio_set_level(BLUE_LED_PIN, 0);
        vTaskDelay(250 / portTICK_RATE_MS);
        gpio_set_level(RED_LED_PIN, 1);
        gpio_set_level(GREEN_LED_PIN, 0);
        gpio_set_level(VIBRATOR_PIN, 0);
        vTaskDelay(250 / portTICK_RATE_MS);
        gpio_set_level(BLUE_LED_PIN, 1);
        vTaskDelay(250 / portTICK_RATE_MS);
        gpio_set_level(GREEN_LED_PIN, 1);
    }

    sound(BUZZER_PIN, 440, 100);
    vTaskDelay(50 / portTICK_RATE_MS);
    sound(BUZZER_PIN, 493, 100);
    vTaskDelay(50 / portTICK_RATE_MS);
    sound(BUZZER_PIN, 523, 100);
    vTaskDelay(50 / portTICK_RATE_MS);
    sound(BUZZER_PIN, 587, 100);
    vTaskDelay(50 / portTICK_RATE_MS);
    sound(BUZZER_PIN, 659, 100);
    vTaskDelay(50 / portTICK_RATE_MS);
    sound(BUZZER_PIN, 698, 100);
    vTaskDelay(50 / portTICK_RATE_MS);
    sound(BUZZER_PIN, 783, 100);
}

void app_main(void) {
  // gpio config for all output pins
  gpio_config_t io_conf = {
    .intr_type = GPIO_INTR_DISABLE,
    .mode = GPIO_MODE_OUTPUT,
    .pin_bit_mask = GPIO_SEL_2 | GPIO_SEL_4 | GPIO_SEL_5 | GPIO_SEL_12 | GPIO_SEL_14 | GPIO_SEL_16 | GPIO_SEL_21 | GPIO_SEL_27 | GPIO_SEL_32 | GPIO_SEL_33,
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
    .miso_io_num = GPIO_NUM_13,
    .mosi_io_num = -1,
    .sclk_io_num = GPIO_NUM_15,
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

  // TODO(joe): check that the board is unlocked

  uint16_t state = read_state(dip_spi);

  switch (state) {
    default:
      printf("more than one selected\n");
  }

    while (1) {
        vTaskDelay(250 / portTICK_RATE_MS);
    //// turn on max98375a
    //gpio_set_level(GPIO_NUM_16, 1);

    //int offset = 0;
    //int tot_size = sizeof(audio_table);
    //size_t bytes_written = 0;
    //i2s_set_clk(0, SAMPLE_RATE, SAMPLE_BITS, 1);
    //while (offset < tot_size) {
    //    printf("%d / %d\n", offset, tot_size);
    //    int play_len = ((tot_size - offset) > (4 * 1024)) ? (4 * 1024) : (tot_size - offset);
    //    // pointer arithmetic is weird so it's audio_table + offset in samples rather than bytes
    //    i2s_write(0, audio_table+(offset / SAMPLE_SIZE), play_len, &bytes_written, portMAX_DELAY);
    //    offset += bytes_written;
    //}
    //vTaskDelay(100 / portTICK_PERIOD_MS);
    //// turn on max98375a
    //gpio_set_level(GPIO_NUM_16, 0);
    //i2s_set_clk(0, SAMPLE_RATE, SAMPLE_BITS, 2);
  }
}

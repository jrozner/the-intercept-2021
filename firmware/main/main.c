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

#include "dip.h"
#include "buzzer.h"

#define SAMPLE_RATE     (16000)
#define SAMPLE_SIZE     (2)
#define SAMPLE_BITS     (SAMPLE_SIZE * 8)
#define I2S_NUM         (0)
#define I2S_BCK_IO      (GPIO_NUM_26)
#define I2S_WS_IO       (GPIO_NUM_25)
#define I2S_DO_IO       (GPIO_NUM_17)
#define I2S_DI_IO       (-1)

static const char* TAG = "main";

void app_main(void) {
  // gpio config for dip, vibrator
  gpio_config_t io_conf;
  io_conf.intr_type = GPIO_INTR_DISABLE;
  io_conf.mode = GPIO_MODE_OUTPUT;
  io_conf.pin_bit_mask = GPIO_SEL_2 | GPIO_SEL_5 | GPIO_SEL_12 | GPIO_SEL_14 | GPIO_SEL_17 | GPIO_SEL_16 | GPIO_SEL_21 | GPIO_SEL_27 | GPIO_SEL_32 | GPIO_SEL_33;
  io_conf.pull_down_en = 0;
  io_conf.pull_up_en = 0;

  gpio_config(&io_conf);

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
    .mode = I2S_MODE_MASTER | I2S_MODE_TX,                                  // Only TX
    .sample_rate = SAMPLE_RATE,
    .bits_per_sample = SAMPLE_BITS,
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,                           //2-channels
    .communication_format = I2S_COMM_FORMAT_STAND_I2S,
    .dma_buf_count = 8,
    .dma_buf_len = 64,
    .use_apll = false,
    .intr_alloc_flags = 0                                //Interrupt level 1
  };

  i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_BCK_IO,
    .ws_io_num = I2S_WS_IO,
    .data_out_num = I2S_DO_IO,
    .data_in_num = I2S_DI_IO                                               //Not used
  };

  i2s_driver_install(I2S_NUM, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM, &pin_config);

  // TODO(joe): check that the board is unlocked

  uint16_t state = read_state(dip_spi);

  switch (state) {
    default:
      printf("more than one selected\n");
  }

  while (1) {
    vTaskDelay(1000 / portTICK_RATE_MS);
    // turn vibrator on
    //gpio_set_level(GPIO_NUM_5, 1);
    //vTaskDelay(1000 / portTICK_RATE_MS);
    //// turn vibrator off
    //gpio_set_level(GPIO_NUM_5, 0);
    //vTaskDelay(1000 / portTICK_RATE_MS);

    //// turn fan on
    //gpio_set_level(GPIO_NUM_21, 1);
    //vTaskDelay(1000 / portTICK_RATE_MS);
    //// turn fan off
    //gpio_set_level(GPIO_NUM_21, 0);
    //vTaskDelay(1000 / portTICK_RATE_MS);

    //sound(GPIO_NUM_4, 660, 100);
    //vTaskDelay(150 / portTICK_RATE_MS);

    //sound(GPIO_NUM_4, 670, 100);
    //vTaskDelay(150 / portTICK_RATE_MS);

    //sound(GPIO_NUM_4, 680, 100);
    //vTaskDelay(150 / portTICK_RATE_MS);

    //sound(GPIO_NUM_4, 670, 100);
    //vTaskDelay(150 / portTICK_RATE_MS);

    //sound(GPIO_NUM_4, 660, 100);
    //vTaskDelay(150 / portTICK_RATE_MS);

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

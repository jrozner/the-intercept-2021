#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"

void sound(int gpio_num, uint32_t freq, uint32_t duration) {
    ledc_timer_config_t timer_conf = {
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .bit_num = LEDC_TIMER_10_BIT,
        .timer_num = LEDC_TIMER_0,
        .freq_hz = freq,
    };

    ledc_timer_config(&timer_conf);

    ledc_channel_config_t ledc_conf = {
        .gpio_num = gpio_num,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0x0,
    };

    ledc_channel_config(&ledc_conf);

    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, 0x7f);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
    vTaskDelay(duration / portTICK_PERIOD_MS);

    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, 0);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
}

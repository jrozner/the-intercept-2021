#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2s.h"

#include "audio.h"
#include "pins.h"

void play_audio(const uint16_t *buf, uint32_t numSamples) {
    // turn on max98375a
    gpio_set_level(I2S_AIO_PIN, 1);
    i2s_set_clk(0, SAMPLE_RATE, SAMPLE_BITS, 1);

    int offset = 0;
    int tot_size = numSamples * 2;
    size_t bytes_written = 0;
    while (offset < tot_size) {
        int play_len = ((tot_size - offset) > (4 * 1024)) ? (4 * 1024) : (tot_size - offset);
        // pointer arithmetic is weird so it's audio_table + offset in samples rather than bytes
        i2s_write(0, buf + (offset / SAMPLE_SIZE), play_len, &bytes_written, portMAX_DELAY);
        offset += bytes_written;
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
    // turn on max98375a
    gpio_set_level(I2S_AIO_PIN, 0);
    i2s_set_clk(0, SAMPLE_RATE, SAMPLE_BITS, 2);
}

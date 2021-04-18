#include "audio.h"

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

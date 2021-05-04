#include "morse.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2s.h"

//#include "audio.h"
#include "pins.h"
#include "audio_example_file.h"

void play_audio2(const uint16_t *buf, uint32_t numSamples) {
    // turn on max98375a

    int offset = 0;
    int tot_size = numSamples * 2;
    size_t bytes_written = 0;
    while (offset < tot_size) {
        int play_len = ((tot_size - offset) > (4 * 1024)) ? (4 * 1024) : (tot_size - offset);
        // pointer arithmetic is weird so it's audio_table + offset in samples rather than bytes
        i2s_write(0, buf + (offset / SAMPLE_SIZE), play_len, &bytes_written, portMAX_DELAY);
        offset += bytes_written;
    }
    //vTaskDelay(100 / portTICK_PERIOD_MS);
    // turn on max98375a
    //gpio_set_level(I2S_AIO_PIN, 0);
    //i2s_set_clk(0, SAMPLE_RATE, SAMPLE_BITS, 2);
}



void challenge_buzzer_morse()
{
    while(true)
    {
        vTaskDelay(3000 / portTICK_RATE_MS);
        morse_buzzer("flag is s4mu3lismyh0m3b0y", 4.0f, 0);
    }

}

void challenge_buzzer_advanced_morse()
{
    char *jules = "the path of the righteous man is beset on all sides by the inequities of the selfish and the tyranny of evil men   Blessed is he who in the name of charity and good will shepherds the weak through the valley of the darkness   For he is truly his brothers keeper and the finder of lost children   And I will strike down upon thee with great vengeance and furious anger those who attempt to poison and destroy my brothers   And you will know I am the Lord when I lay my vengeance upon you unless you submit my flag pr3ttyple4s3withsug4ront0p";

    while(true)
    {
        vTaskDelay(3000 / portTICK_RATE_MS);
        morse_buzzer(jules, 0.5f, 50);   
    }
}

void challenge_infrasound()
{
    //gpio_set_level(I2S_AIO_PIN, 1);
    //i2s_set_clk(0, SAMPLE_RATE, SAMPLE_BITS, 2);
    
    uint16_t *bufTone = (uint16_t*) heap_caps_malloc(SAMPLE_RATE * 4 * 2, MALLOC_CAP_8BIT);

    float volume = 0.9;
    double freq = 220;
    float theta = 0.0;
    float incTheta = 0.0;

    char *message = "FLAGISSPACEWEED";

    int i;
    for(i = 0; i < SAMPLE_RATE * 4 ; i++)
    {
    
        int symbolRate = SAMPLE_RATE / 4;

        if ((i % symbolRate) < (symbolRate / 2))
        {
            bufTone[i] = 0;
        }
        else
        {
            int symbolNum = i / symbolRate;
            int symbolVal = i % symbolRate - symbolRate / 2;

            float sym = symbolVal / (symbolRate / 2.0);

            //freq = 30 + 5 * symbolNum;
            freq = 200;

            float letterFloat = (message[symbolNum] - 'A') / ((float) 'Z' - 'A');

            if (sym < letterFloat)
            {
                volume = 1.0;
                freq = 200;
                incTheta = freq * 2 * 3.141 / SAMPLE_RATE; 
            }
            else
            {
                volume = 0.2;
                freq = 400;   
                incTheta = freq * 2 * 3.141 / SAMPLE_RATE; 
            }
            int16_t temp = (int16_t)(sin(theta) * 65535.0 / 2.0 * volume);
            uint16_t utemp = * ((uint16_t *) &temp);
            
            if (symbolNum >= 15)
                bufTone[i] = 0;
            else
                bufTone[i] = utemp;
            
            theta += incTheta;
        }
    }
    
    while(true)
    {
        play_audio(bufTone, SAMPLE_RATE * 4);
       
        vTaskDelay(4000 / portTICK_RATE_MS);
        
    }
}

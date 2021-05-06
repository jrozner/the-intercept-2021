#include "morse.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2s.h"

//#include "audio.h"
#include "pins.h"
#include "audio_numbers.h"

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

const uint16_t* numberWav[] = {audio_table0, audio_table1, audio_table2, audio_table3, audio_table4, audio_table5, audio_table6, audio_table7, audio_table8, audio_table9};
int numberLen[] = {sizeof(audio_table0)/2, sizeof(audio_table1)/2, sizeof(audio_table2)/2, sizeof(audio_table3)/2, sizeof(audio_table4)/2, sizeof(audio_table5)/2, sizeof(audio_table6)/2,sizeof(audio_table7)/2, sizeof(audio_table8)/2, sizeof(audio_table9)/2};

void playNumber(int num)
{
    if (num > 99999)
    {
        play_audio(numberWav[num / 100000 % 10], numberLen[num / 100000 % 10]);
    }
    if (num > 9999)
    {
        play_audio(numberWav[num / 10000 % 10], numberLen[num / 10000 % 10]);
    }
    if (num > 999)
    {
        play_audio(numberWav[num / 1000 % 10], numberLen[num / 1000 % 10]);
    }
    if (num > 99)
    {
        play_audio(numberWav[num / 100 % 10], numberLen[num / 100 % 10]);
    }
    if (num > 9)
    {
        play_audio(numberWav[num / 10 % 10], numberLen[num / 10 % 10]);
    }
    if (num > -1)
    {
        play_audio(numberWav[num % 10], numberLen[num % 10]);
    }
}

void challenge_numbers()
{

    int numberList[] = {90504,90250,90245,00000,92834,90801,90701,91208,00000,90306,90406,00000,91208,90701,91328,91208,90222,90701,91106,90306,90504,90701,90801,92863,92834,90504,90250,90245,91328,90701,90504,90306,92863,91328,00000,90504,90250,90245,00000,92834,92863,90801,90801,92863,91791,90306,91328,91208,00000,90240,90306,91106,00000,90222,92863,90240,90245,00000,90306,90406,00000,90504,90250,90277,90245,90245,00000,92834,90306,91409,90245,00000,90406,90245,91409,90245,91328};

    
    while(true)
    {
        vTaskDelay(3000 / portTICK_RATE_MS);

        int i;
        for(i = 0;i < 1; i++)
        { 
            playNumber(420);
        }
        
        play_audio(audio_tableha, sizeof(audio_tableha) / 2);
        playNumber(sizeof(numberList)/4);
        play_audio(audio_tableha, sizeof(audio_tableha) / 2);

        for(i = 0; i < sizeof(numberList)/4; i++)
        {
                playNumber(numberList[i]);
                vTaskDelay(1000 / portTICK_RATE_MS);
        }
        
        play_audio(audio_tableha, sizeof(audio_tableha) / 2);
        playNumber(sizeof(numberList)/4);
        play_audio(audio_tableha, sizeof(audio_tableha) / 2);

        for(i = 0; i < sizeof(numberList)/4; i++)
        {
                playNumber(numberList[i]);
                vTaskDelay(1000 / portTICK_RATE_MS);
        }
        
        play_audio(audio_tableha, sizeof(audio_tableha) / 2);

    }
    
}

void play_dtmf(char *sequence)
{

    uint16_t *bufTone = (uint16_t*) heap_caps_malloc(SAMPLE_RATE * 1 * 2, MALLOC_CAP_8BIT);


    int j;
    for(j = 0; j < strlen(sequence); j++)
    {
        float freq1 = 0;
        float freq2 = 0;

        if (sequence[j] == '-')
        {
            vTaskDelay(1000 / portTICK_RATE_MS);
            continue;
        }
        else if (sequence[j] == '*')
        {
            freq1 = 1209;
            freq2 = 941;
        }
        else if (sequence[j] == '*')
        {
            freq1 = 1477;
            freq2 = 941;
        }
        else
        {
            int digit = sequence[j] - '0';

            int dtmf1[] = {1336, 1209, 1336, 1477, 1209, 1336, 1477, 1209, 1336, 1477};
            int dtmf2[] = {941, 697, 697, 697, 770, 770, 770, 852, 852, 852};

            freq1 = dtmf1[digit];
            freq2 = dtmf2[digit];
        }

        int i;
        for(i = 0; i < (int)(SAMPLE_RATE * 0.05); i++)
        {

            float volume = 0.2;

            float s1 = sin(i * freq1 * 3.141 * 2 / SAMPLE_RATE) * volume; 
            float s2 = sin((i + 20) * freq2 * 3.141 * 2 / SAMPLE_RATE) * volume; 

            float samp = s1 + s2;
            
            int16_t temp = (int16_t)(samp * 65535.0 / 2.0);
            uint16_t utemp = * ((uint16_t *) &temp);

            bufTone[i] = utemp;    

        }
            
        play_audio(bufTone, (int)(SAMPLE_RATE * 0.05));
        vTaskDelay(50 / portTICK_RATE_MS);
    }

    free(bufTone);

}  

void play_text(char *text)
{
    char *numpad[] = {"2","22","222","3","33","333","4","44","444","5","55","555","6","66","666","7","77","777","7777","8","88","888","9","99","999"};

    char last_letter = '$';

    int i;
    for(i = 0; i < strlen(text); i++)
    {
        char letter = text[i];

        if (letter ==  ' ')
        {
            play_dtmf("0");
        }
        else
        {
            if (last_letter == numpad[letter-'a'][0])
                vTaskDelay(200 / portTICK_RATE_MS);
                
            last_letter = numpad[letter-'a'][0];
            play_dtmf(numpad[letter-'a']);
            vTaskDelay(50 / portTICK_RATE_MS);
        }
    }

}

void challenge_dtmf()
{
    while(1)
    {
        vTaskDelay(3000 / portTICK_RATE_MS);
        play_text("flag is brbcarcrashlol");
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
        vTaskDelay(4000 / portTICK_RATE_MS);
        
        play_audio(bufTone, SAMPLE_RATE * 4);
    }
}

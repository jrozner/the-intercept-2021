#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "buzzer.h"
#include "morse.h"
#include "pins.h"

const char *TAG = "morse";

const char *morseLetter[256] = {0};

void morse_buzzer(char *input, float speed, int swing) {

    morseLetter['a'] = ".-";
    morseLetter['b'] = "-...";
    morseLetter['c'] = "-.-.";
    morseLetter['d'] = "-..";
    morseLetter['e'] = ".";
    morseLetter['f'] = "..-.";
    morseLetter['g'] = "--.";
    morseLetter['h'] = "....";
    morseLetter['i'] = "..";
    morseLetter['j'] = ".---";
    morseLetter['k'] = "-.-";
    morseLetter['l'] = ".-..";
    morseLetter['m'] = "--";
    morseLetter['n'] = "-.";
    morseLetter['o'] = "---";
    morseLetter['p'] = ".--.";
    morseLetter['q'] = "--.-";
    morseLetter['r'] = ".-.";
    morseLetter['s'] = "...";
    morseLetter['t'] = "-";
    morseLetter['u'] = "..-";
    morseLetter['v'] = "...-";
    morseLetter['w'] = ".--";
    morseLetter['x'] = "-..-";
    morseLetter['y'] = "-.--";
    morseLetter['z'] = "--..";

    morseLetter['1'] = ".----";
    morseLetter['2'] = "..---";
    morseLetter['3'] = "...--";
    morseLetter['4'] = "....-";
    morseLetter['5'] = ".....";
    morseLetter['6'] = "-...";
    morseLetter['7'] = "--...";
    morseLetter['8'] = "---..";
    morseLetter['9'] = "----.";
    morseLetter['0'] = "-----";

    morseLetter[' '] = " ";

    for (char *c = input; *c != 0; c++) {
        
        const char *morseSeq = morseLetter[(int)*c];
       
        if (morseSeq)
        {
            for (const char *i = morseSeq; *i != 0; i++)
            {
                int freqSwing = 0;

                if (swing > 0)
                    freqSwing = rand() % (swing * 2) - swing;

                char symbol = *i;
                if ((symbol >= 'A') && (symbol <= 'Z')) symbol += 'a' - 'A';

                if (symbol == '.') sound(BUZZER_PIN, MORSE_FREQ + freqSwing, SHORT_LENGTH * speed);
                else if (symbol == '-') sound(BUZZER_PIN, MORSE_FREQ + freqSwing, SHORT_LENGTH * 3 * speed);
                else if (symbol == ' ') vTaskDelay(SHORT_LENGTH * 8 * speed / portTICK_RATE_MS);

                vTaskDelay(SHORT_LENGTH * speed / portTICK_RATE_MS);
            }
        }

        vTaskDelay(SHORT_LENGTH * speed * 4 / portTICK_RATE_MS);
    }
}

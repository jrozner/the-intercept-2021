#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "buzzer.h"
#include "morse.h"
#include "pins.h"

const char *TAG = "morse";

void morse_buzzer(char *input) {
    for (char *c = input; *c != 0; c++) {
        switch (*c) {
            case 'A':
            case 'a':
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                break;
            case 'B':
            case 'b':
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                break;
            case 'C':
            case 'c':
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                break;
            case 'D':
            case 'd':
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                break;
            case 'E':
            case 'e':
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                break;
            case 'F':
            case 'f':
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                break;
            case 'G':
            case 'g':
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                break;
            case 'H':
            case 'h':
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                break;
            case 'I':
            case 'i':
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                break;
            case 'J':
            case 'j':
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                break;
            case 'K':
            case 'k':
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                break;
            case 'L':
            case 'l':
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                break;
            case 'M':
            case 'm':
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                break;
            case 'N':
            case 'n':
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                break;
            case 'O':
            case 'o':
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                break;
            case 'P':
            case 'p':
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                break;
            case 'Q':
            case 'q':
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                break;
            case 'R':
            case 'r':
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                break;
            case 'S':
            case 's':
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                break;
            case 'T':
            case 't':
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                break;
            case 'U':
            case 'u':
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                break;
            case 'V':
            case 'v':
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                break;
            case 'W':
            case 'w':
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                break;
            case 'X':
            case 'x':
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                break;
            case 'Y':
            case 'y':
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                break;
            case 'Z':
            case 'z':
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                break;
            case '1':
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                break;
            case '2':
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                break;
            case '3':
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                break;
            case '4':
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                break;
            case '5':
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                break;
            case '6':
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                break;
            case '7':
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                break;
            case '8':
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                break;
            case '9':
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, SHORT_LENGTH);
                break;
            case '0':
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                sound(BUZZER_PIN, MORSE_FREQ, LONG_LENGTH);
                break;
            case ' ':
                break;
            default:
                ESP_LOGE(TAG, "unsupported character");
        }

        vTaskDelay(SEPARATOR_LENGTH / portTICK_RATE_MS);
    }
}
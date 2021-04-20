#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#include "animation.h"
#include "buzzer.h"
#include "pins.h"

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

void unlock_animation() {
    gpio_set_level(GREEN_LED_PIN, 0);
    sound(BUZZER_PIN, 600, 100);
    vTaskDelay(25 / portTICK_RATE_MS);
    sound(BUZZER_PIN, 650, 100);
    vTaskDelay(25 / portTICK_RATE_MS);
    gpio_set_level(GREEN_LED_PIN, 1);
    sound(BUZZER_PIN, 670, 100);
}

void error_animation() {
    gpio_set_level(RED_LED_PIN, 0);
    sound(BUZZER_PIN, 900, 100);
    vTaskDelay(50 / portTICK_RATE_MS);
    sound(BUZZER_PIN, 900, 100);
    vTaskDelay(50 / portTICK_RATE_MS);
    gpio_set_level(RED_LED_PIN, 1);
    sound(BUZZER_PIN, 900, 100);
}

void locked_animation() {
    gpio_set_level(RED_LED_PIN, 0);
    sound(BUZZER_PIN, 900, 1000);
    gpio_set_level(RED_LED_PIN, 1);
}


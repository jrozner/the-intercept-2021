#ifndef THEINTERCEPT_PINS_H
#define THEINTERCEPT_PINS_H

#include "driver/gpio.h"

// IS2 audio DAC
#define I2S_BCK_PIN (GPIO_NUM_26)
#define I2S_WS_PIN (GPIO_NUM_25)
#define I2S_DO_PIN (GPIO_NUM_17)
#define I2S_DI_PIN (-1)
#define I2S_AIO_PIN (GPIO_NUM_16)

// LEDs
#define RED_LED_PIN (GPIO_NUM_12)
#define BLUE_LED_PIN (GPIO_NUM_14)
#define GREEN_LED_PIN (GPIO_NUM_27)
#define IR_LED_PIN (GPIO_NUM_33)
#define UV_LED_PIN (GPIO_NUM_32)

// Misc peripherals
#define VIBRATOR_PIN (GPIO_NUM_5)
#define BUZZER_PIN (GPIO_NUM_4)
#define FAN_PIN (GPIO_NUM_21)

// DIP Latch
#define LATCH_PIN (GPIO_NUM_2)

#endif //THEINTERCEPT_PINS_H

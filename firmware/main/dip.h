#ifndef THEINTERCEPT_DIP_H
#define THEINTERCEPT_DIP_H

#define DIP1 (1 << 7)
#define DIP2 (1 << 6)
#define DIP3 (1 << 5)
#define DIP4 (1 << 4)
#define DIP5 (1 << 3)
#define DIP6 (1 << 2)
#define DIP7 (1 << 1)
#define DIP8 (1 << 0)
#define DIP9 (1 << 15)
#define DIP10 (1 << 14)

// DIP SETTINGS 0-1023

#define DIP_CODE(code) (((code & 0b11) << 14) | (code >> 2))

#define CODE_UNLOCK                      (DIP_CODE(951))
#define CODE_BUZZER_MORSE                (DIP_CODE(420))
#define CODE_BUZZER_ADVANCED_MORSE       (DIP_CODE(360))

#define CODE_LED_IMG_BINARY              (DIP_CODE(164))
#define CODE_LED_IMG_REDVAR              (DIP_CODE(864))
#define CODE_LED_IMG_RGB                 (DIP_CODE(537))
#define CODE_LED_IMG_RGBVAR              (DIP_CODE(735))
#define CODE_LED_UV                      (DIP_CODE(1001))
#define CODE_LED_IR                      (DIP_CODE(1023))
#define CODE_LED_BRAILLE                 (DIP_CODE(333))
#define CODE_LED_POV                     (DIP_CODE(42))


uint16_t read_state(spi_device_handle_t);
void load_registers(spi_transaction_t *t);


#endif //THEINTERCEPT_DIP_H

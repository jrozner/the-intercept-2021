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

#define CODE_UNLOCK                      (DIP_CODE(951))  // 1110110111
#define CODE_BUZZER_MORSE                (DIP_CODE(420))  // 0110100100
#define CODE_BUZZER_ADVANCED_MORSE       (DIP_CODE(360))  // 0101101000
#define CODE_INFRASOUND                  (DIP_CODE(831))  // 1100111111
#define CODE_NUMBERS                     (DIP_CODE(44))   // 0000101100
#define CODE_NUMBERS2                    (DIP_CODE(357))  // 0101100101
#define CODE_DTMF                        (DIP_CODE(555))  // 1000101011
#define CODE_DTMF2                       (DIP_CODE(213))  // 0011010101
#define CODE_TAP                         (DIP_CODE(124))  // 0001111100

#define CODE_WIFI_AP                     (DIP_CODE(445))  // 0110111101
#define CODE_WIFI_AP2                    (DIP_CODE(770))  // 1100000010
#define CODE_WIFI_MAC                    (DIP_CODE(85))   // 0001010101
#define CODE_WIFI_PROBE                  (DIP_CODE(10))   // 0000001010
#define CODE_WIFI_APCRACK                (DIP_CODE(626))  // 1001110010

#define CODE_HEAT                        (DIP_CODE(640))  // 1010000000
#define CODE_FAN1                        (DIP_CODE(232))  // 0011101000
#define CODE_BAUDOT                      (DIP_CODE(55))   // 0000110111
#define CODE_PSK31                       (DIP_CODE(871))  // 1101100111
#define CODE_SSTV                        (DIP_CODE(136))  // 0010001000
#define CODE_LED_IMG_BINARY              (DIP_CODE(164))  // 0010100100
#define CODE_LED_IMG_REDVAR              (DIP_CODE(864))  // 1101100000
#define CODE_LED_IMG_RGB                 (DIP_CODE(540))  // 1000011100
#define CODE_LED_IMG_RGBVAR              (DIP_CODE(735))  // 1011011111
#define CODE_LED_UV                      (DIP_CODE(1001)) // 1111101001
#define CODE_LED_IR                      (DIP_CODE(1023)) // 1111111111
#define CODE_LED_IR2                     (DIP_CODE(666))  // 1010011010
#define CODE_LED_BRAILLE                 (DIP_CODE(333))  // 0101001101
#define CODE_LED_POV                     (DIP_CODE(42))   // 0000101010

#define CODE_SPI                         (DIP_CODE(432))  // 0110110000

uint16_t read_state(spi_device_handle_t);
void load_registers(spi_transaction_t *t);


#endif //THEINTERCEPT_DIP_H

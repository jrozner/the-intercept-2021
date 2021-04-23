#include "morse.h"

void challenge_buzzer_morse()
{
    while(true)
    {
        vTaskDelay(3000 / portTICK_RATE_MS);
        //morse_buzzer("flag is samuelismyhomeboy");
        morse_buzzer("a");
    }

}

#include "morse.h"

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

#include <stdio.h>
#include "led.h"

const uint DEBOUNCE = 20;
const uint PIN = 15;

bool get_button_debounce(uint pin)
{
    bool state = gpio_get(pin);
    sleep_ms(DEBOUNCE);
    return state;
}

bool handle_command(int command, bool led)
{
    if (command == 'e')
    {
        led = true;
        led_set(led);
        printf("led %s\n", led_is_on() ? "on" : "off");
    }
    else if (command == 'd')
    {
        led = false;
        led_set(led);
        printf("led %s\n", led_is_on() ? "on" : "off");

    }
    else
    {
        printf("unknown command: %c\n", command);
    }

    return led;
}


int main()
{
    stdio_init_all(); // io
    gpio_pull_up(PIN);

    led_init();

    bool previos = false;
    bool led = false;



    while (1)
    {
    bool current = get_button_debounce(PIN);
    if (previos == true && current == false)
    {
        led = !led;
        led_set(led);
    }
    previos = current;
    
    int command = getchar_timeout_us(0);
    if (command == PICO_ERROR_TIMEOUT)
        {
            continue;
        }

    led = handle_command(command, led);


    }
}
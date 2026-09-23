#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

const uint LED_PIN = 25;
const uint PIN = 15;
const uint DEBOUNCE = 20;

bool get_button_debounce(uint pin)
{
    bool state = gpio_get(pin);
    sleep_ms(DEBOUNCE);
    return state;
}

void set_led(bool on)
{
    gpio_put(LED_PIN, on);
    printf("led %s\n", on ? "on" : "off");
}



int main()
{
    stdio_init_all(); // io
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_pull_up(PIN);

    bool previos = false;
    bool led = false;



    while (1)
    {
    bool current = get_button_debounce(PIN);
    if (previos == true && current == false)
    {
    led = !led;
    set_led(led);
    }
    previos = current;
    }
}
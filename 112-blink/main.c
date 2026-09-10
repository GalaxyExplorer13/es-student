#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define SIO_BASE 0xd00000000
#define GPIO_OUT_SET 0x014
#define GPIO_OUT_CLR 0x018


const uint LED_PIN = 25;

int main()
{
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while(true)
    {
    gpio_put(LED_PIN, 1);
    sleep_ms(250);
    gpio_put(LED_PIN, 0);
    sleep_ms(1000);
    }

}

// добавил коммит, чтобы обновить проверку заданий в личном кабинете.
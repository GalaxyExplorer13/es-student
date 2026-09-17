#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/regs/addressmap.h"
#include "hardware/regs/sio.h"

const uint LED_PIN = 25;
const uint BUTTON_PIN = 15;

int main()
{
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    bool led = false;
    bool previous = false;

    
    volatile uint32_t* gpio_out_set = (uint32_t*) (SIO_BASE + SIO_GPIO_OUT_SET_OFFSET);
    volatile uint32_t* gpio_out_clr = (uint32_t*) (SIO_BASE + SIO_GPIO_OUT_CLR_OFFSET);
    const uint32_t led_mask = 1u << LED_PIN;

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

        while (1)
    {
        bool current = gpio_get(BUTTON_PIN);

        if (previous == true && current == false)
        {
            led = !led;
            gpio_put(LED_PIN, led);
        }

        previous = current;
    }

}


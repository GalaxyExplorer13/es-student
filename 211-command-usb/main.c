#include <stdio.h>
#include "led.h"
#include "log.h"
#include "device.h"
#include <string.h>

#define LINE_SIZE 32

const uint DEBOUNCE = 20;
const uint PIN = 15;
char line[LINE_SIZE];
uint line_length = 0;


bool get_button_debounce(uint pin)
{
    bool state = gpio_get(pin);
    sleep_ms(DEBOUNCE);
    return state;
}

void handle_command(const char *command)
{
    if (strcmp(command, "enable") == 0)
    {
        led_set(1);
        LOG_INF("led on %c\n", true);
    }

    else if (strcmp(command, "disable") == 0)
    {
        led_set(0);
        LOG_INF("led off %c\n", false);
    }
    
    else if (strcmp(command, "version") == 0)
    {
        log_version();
    }
    else if (strcmp(command, "info") == 0)
    {
        device_info();
    }
    else
    {
        LOG_ERR("unknown command: %c\n", command);
    }
}

void read_line(void)
{
    int symbol = getchar_timeout_us(0);

    if (symbol == PICO_ERROR_TIMEOUT)
    {
        return;
    }

    if (symbol == '\r' || symbol == '\n')
    {
        putchar('\n');
        line[line_length] = '\0';

        if (line_length > 0)
        {
            LOG_DBG("got %s\n", line);
            handle_command(line);
        }

        line_length = 0;
        return;
    }

    if (line_length + 1 < LINE_SIZE)
    {
        line[line_length] = (char)symbol;
        line_length = line_length + 1;
        putchar(symbol);
    }
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
    
        // int command = getchar_timeout_us(0);
        // if (command == PICO_ERROR_TIMEOUT)
        //     {
        //         continue;
        //     }

        // LOG_DBG("got %c\n", command);
        // handle_command(command, led);
        read_line();

    }
}
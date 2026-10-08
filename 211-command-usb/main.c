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

typedef void (*command_handler_t)(void);

struct command_t
{
    const char *name;
    command_handler_t handler;
};

void cmd_enable(void)
{
    led_set(1);
    LOG_INF("led on %c\n", true);
}

void cmd_disable(void)
{
    led_set(0);
    LOG_INF("led off %c\n", false);
}

void cmd_info(void)
{
    device_info();
}

void cmd_version(void)
{
    log_version();
}

void cmd_ping(void)
{
    printf("pong\n");
}

const struct command_t commands[] = {
    { "enable", cmd_enable },
    { "disable", cmd_disable },
    { "info", cmd_info },
    { "version", cmd_version },
    { "ping", cmd_ping }
};

#define COMMAND_COUNT (sizeof(commands) / sizeof(commands[0]))





bool get_button_debounce(uint pin)
{
    bool state = gpio_get(pin);
    sleep_ms(DEBOUNCE);
    return state;
}


void handle_command(const char *command)
{
    for (uint i = 0; i < COMMAND_COUNT; i++)
    {
        if (strcmp(command, commands[i].name) == 0)
        {
            if (commands[i].handler != NULL)
            {
                commands[i].handler();
            }

            return;
        }
    }

    LOG_ERR("unknown command: %s\n", command);
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
    
        read_line();

    }
}
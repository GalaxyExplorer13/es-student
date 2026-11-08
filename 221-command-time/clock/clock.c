#include "clock.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"


void row(const char *name, uint32_t set_khz, uint32_t measured_khz)
{
    printf("%-8s %9u %12u\n", name, (unsigned)set_khz, (unsigned)measured_khz);
}

void clk_info(void)
{
    uint32_t sys_hz = clock_get_hz(clk_sys);
    printf("%-8s, %-8s, %-8s\n", "signal", "set_khz", "measured_khz");
    row("clk_ref", clock_get_hz(clk_ref) / 1000, frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_REF));
    row("clk_sys", clock_get_hz(clk_sys) / 1000, frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_SYS));
    row("clk_peri", clock_get_hz(clk_peri) / 1000, frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_PERI));
    row("clk_usb", clock_get_hz(clk_usb) / 1000, frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_USB));
    row("clk_adc", clock_get_hz(clk_adc) / 1000, frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_ADC));
    printf("%-8s %9s %12u\n", "rosc", "-", (unsigned)(frequency_count_khz(CLOCKS_FC0_SRC_VALUE_ROSC_CLKSRC)));

}

void uptime(void)
{
    printf("uptime: %llu ms\n", time_us_64() / 1000);

}
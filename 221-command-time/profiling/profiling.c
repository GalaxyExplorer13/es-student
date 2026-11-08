#include "profiling.h"
#include "pico/stdlib.h"

// итерация около 2 мкс, за секунду их около 500 000;
// ближайшая степень двойки 2^19 = 524 288, среднее помнит около секунды
#define AVG_SHIFT 19
// замер в 1/256 долях микросекунды, чтобы среднее не теряло дробную часть
#define FRACTION_SHIFT 8

static uint64_t avg_sum = 0;

static uint32_t previous_us = 0;
static uint32_t max_us = 0;

void profiling_init(void)
{
    previous_us = time_us_32();
}

void profiling_iteration(void)
{
    uint32_t now_us = time_us_32();
    uint32_t iteration_us = now_us - previous_us;
    previous_us = now_us;

    if (iteration_us > max_us)
    {
        max_us = iteration_us;
    }

    avg_sum = avg_sum - (avg_sum >> AVG_SHIFT) + ((uint64_t)iteration_us << FRACTION_SHIFT);
}

float profiling_avg_us(void)
{
    return (float)(avg_sum >> AVG_SHIFT) / (1 << FRACTION_SHIFT);
}

uint32_t profiling_max_us(void)
{
    return max_us;
}

void profiling_reset_max(void)
{
    max_us = 0;
}
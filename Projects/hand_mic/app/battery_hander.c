#include "stdio.h"
#include "board_config.h"
#include "battery_handler.h"

#define BATTERY_INTERVAL_MS 60 * 1000

static uint16_t battery_mv = 0;

void battery_loop_task(void)
{
    static uint64_t old_ticks = 0;

    if(mid_timer_ticks_get() - old_ticks > BATTERY_INTERVAL_MS)
    {
        old_ticks = mid_timer_ticks_get();

        battery_mv = adc_ch_result_get(ADC_CHANNEL_1) * 3300 / 4095;

        trace_debug("battery adc done %d mv\n\r",battery_mv);
    }
}

uint16_t battery_mv_get(void)
{
    return battery_mv;
}


#include "ft32f0xx.h"
#include "ft_delay.h"

#include "ft_timer.h"

/***
 * 弃用,延时不准
 */


/**
 * 通过TIM3通用定时器的计数器获得时间
 */
void ft_delay_us(uint16_t us)
{
/**
 * 通过定时器的计数寄存器来获取us的差值.有点BUG,延时不太准
 */
    uint16_t start_cnt = USER_TIMER->CNT;
    uint16_t stop_timestamp = start_cnt + us;
    uint64_t old_tick = ft_timer_tick_get();

    if(stop_timestamp > USER_TIMER_PERIOD)
    {
        uint16_t remaind = us - (USER_TIMER_PERIOD - start_cnt);
        uint16_t period = remaind / USER_TIMER_PERIOD;
        uint16_t i = 0;
        uint16_t remaind2 = remaind - (period * USER_TIMER_PERIOD);

        while(old_tick == ft_timer_tick_get());

        old_tick = ft_timer_tick_get();

        for(i = 0; i < period; i++)
        {
            while(old_tick == ft_timer_tick_get());
            old_tick = ft_timer_tick_get();
        }

        while(USER_TIMER->CNT < remaind2);
    }
    else
    {
        while(stop_timestamp > USER_TIMER->CNT);
    }
}

void ft_delay_ms(uint16_t ms)
{
    uint16_t i = 0;
    for(i = 0; i < ms; i++)
    {
        ft_delay_us(1000);
    }
}


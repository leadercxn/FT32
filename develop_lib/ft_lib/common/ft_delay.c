#include "ft32f0xx.h"
#include "ft_delay.h"

#include "ft_timer.h"
/**
 * 通过TIM3通用定时器的计数器获得时间
 */
void delay_us(uint16_t us)
{
    uint16_t start_cnt = USER_TIMER->CNT;

    if((us + start_cnt) > USER_TIMER_PERIOD)
    {
        uint16_t remaind = us - (USER_TIMER_PERIOD - start_cnt);
        while(USER_TIMER->CNT != 0);

        uint16_t period = remaind / USER_TIMER_PERIOD;
        uint16_t i =0;

        remaind = remaind - (period * USER_TIMER_PERIOD);

        for(i = 0; i < period; i++)
        {
            while(USER_TIMER->CNT < (USER_TIMER_PERIOD - 1));
            while(USER_TIMER->CNT != 0);
        }

        while(USER_TIMER->CNT != remaind);
    }
    else
    {
        while( (us + start_cnt) > USER_TIMER->CNT );
    }
}

void delay_ms(uint16_t ms)
{
    uint16_t i = 0;
    for(i = 0; i < ms; i++)
    {
        delay_us(1000);
    }
}


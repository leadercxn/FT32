#include "ft32f0xx.h"
#include "ft_delay.h"

/**
 * 阻塞式延时
 */
void ft_delay_10us(uint16_t n_10us)
{
    uint16_t i = 0;
    uint16_t j = 0;
    for(j = n_10us; j > 0; j--)
    {
        /**
         * 这延时的取值，要根据具体系统时钟来
         */
        for(i =18; i > 0 ; i--);
    }
}

void ft_delay_ms(uint16_t ms)
{
    uint16_t i = 0;

    for(i = ms; i > 0 ; i--)
    {
        ft_delay_10us(100);
    }
}


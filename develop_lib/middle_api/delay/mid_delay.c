#ifdef FT32
#include "ft_lib.h"
#endif

#include "mid_delay.h"

void delay_10us(uint16_t n_10us)
{
#ifdef FT32
    ft_delay_10us(n_10us);
#endif
}

void delay_ms(uint16_t ms)
{
    uint16_t i = 0;

    for(i = ms; i > 0 ; i--)
    {
        delay_10us(100);
    }
}

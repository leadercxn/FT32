#ifdef FT32
#include "ft_lib.h"
#endif

#include "mid_delay.h"

void delay_us(uint16_t us)
{
#ifdef FT32
    ft_delay_us(us);
#endif
}

void delay_ms(uint16_t ms)
{
#ifdef FT32
    ft_delay_ms(ms);
#endif
}

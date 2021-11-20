#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#ifdef FT32
#include "ft_lib.h"
#endif

#include "board_config.h"
#include "mid_adc.h"

//ADC初始化宏
#ifdef FT32 
#define ADC_INIT()   \
{                    \
    ft_adc_init();   \
}
#else

#define ADC_INIT()

#endif



void adc_init(void)
{
    ADC_INIT();
}

uint16_t adc_ch_result_get(uint32_t channel)
{
#ifdef FT32
    return adc_ch_value_get(channel);
#endif
}

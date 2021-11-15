#ifndef __MID_ADC_H
#define __MID_ADC_H

//通道
#ifdef FT32 
#define ADC_CHANNEL_0        ADC_Channel_0
#define ADC_CHANNEL_1        ADC_Channel_1
#define ADC_CHANNEL_2        ADC_Channel_2
#define ADC_CHANNEL_3        ADC_Channel_3
#else

#define ADC_CHANNEL_0
#define ADC_CHANNEL_1
#define ADC_CHANNEL_2
#define ADC_CHANNEL_3

#endif


void adc_init(void);
uint16_t adc_ch_result_get(uint32_t channel);

#endif

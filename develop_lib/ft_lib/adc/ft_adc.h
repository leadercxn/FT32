#ifndef __FT_ADC_H
#define __FT_ADC_H

#define ADC_GPIO_PORT_CLK    RCC_AHBPeriph_GPIOA
#define ADC_GPIO_PIN_0       GPIO_Pin_0
#define ADC_GPIO_PIN_1       GPIO_Pin_1
#define ADC_CHANNEL_0        ADC_Channel_0
#define ADC_CHANNEL_1        ADC_Channel_1
#define ADC_CHANNEL_2        ADC_Channel_2
#define ADC_CHANNEL_3        ADC_Channel_3
#define ADC_GPIO_PORT        GPIOA

#define ADC_SAMPLETIME_CYCLE        ADC_SampleTime_239_5Cycles
#define ADC_CONTINUOUS_CONV_MODE    DISABLE

void adc_init(void);
uint16_t adc_ch_value_get(uint32_t channel);

#endif

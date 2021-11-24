#include "stdbool.h"

#include "board_config.h"
#include "ft_adc.h"

void ft_adc_init(void)
{
    ADC_InitTypeDef     ADC_InitStructure;
    GPIO_InitTypeDef    GPIO_InitStructure;

    RCC_AHBPeriphClockCmd(ADC_GPIO_PORT_CLK, ENABLE);

    /* ADC1 Periph clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

    GPIO_InitStructure.GPIO_Pin  = ADC_GPIO_PIN_0 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
    GPIO_Init(ADC_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin  = ADC_GPIO_PIN_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
    GPIO_Init(ADC_GPIO_PORT, &GPIO_InitStructure);

    /* ADCs DeInit */  
    ADC_DeInit(ADC1);
  
    /* Initialize ADC structure */
    ADC_StructInit(&ADC_InitStructure);

    /* Configure the ADC1 in continuous mode with a resolution equal to 12 bits  */
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ContinuousConvMode = ADC_CONTINUOUS_CONV_MODE; 
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
    ADC_Init(ADC1, &ADC_InitStructure);

    /* ADC Calibration */
    ADC_GetCalibrationFactor(ADC1);
    
    /* Enable the ADC peripheral */
    ADC_Cmd(ADC1, ENABLE);     
    
    /* Wait the ADRDY flag */
    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADRDY)); 
}

uint16_t adc_ch_value_get(uint32_t channel)
{
    ADC_ChannelConfig(ADC1, channel, ADC_SAMPLETIME_CYCLE);

    /**
     * 启动转换
     */
    ADC_StartOfConversion(ADC1);

    while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);

    return ADC_GetConversionValue(ADC1);
}


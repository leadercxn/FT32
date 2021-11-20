#include "stddef.h"
#include "stdbool.h"

#include "board_config.h"
#include "ft_timer_pwm.h"

void timer15_ch1_pwm_init(uint32_t freq , uint8_t duty_cycle)
{
    uint32_t timer_period = 0;
    uint32_t chan1_pulse = 0;

    TIM_TimeBaseInitTypeDef     TIM_TimeBaseStructure;
    TIM_OCInitTypeDef           TIM_OCInitStructure;
    GPIO_InitTypeDef            GPIO_InitStructure;

    RCC_AHBPeriphClockCmd(PWM_CH1_GPIO_CLK, ENABLE);

    GPIO_InitStructure.GPIO_Pin = PWM_CH1_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
    GPIO_Init(PWM_CH1_GPIO_PORT, &GPIO_InitStructure);

    GPIO_PinAFConfig(PWM_CH1_GPIO_PORT, PWM_CH1_PIN_SOURCE, PWM_CH1_AF);

    /* 38KHz */
    timer_period = (SystemCoreClock / freq ) - 1;

    /* duty cycle at 50% */
    chan1_pulse = (uint16_t) (((uint32_t) duty_cycle * (timer_period - 1)) / 100);

    /* TIM15 clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM15 , ENABLE);
    
    /* Time Base configuration */
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = timer_period;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

    TIM_TimeBaseInit(PWM_TIM, &TIM_TimeBaseStructure);

    TIM_OCInitStructure.TIM_OCMode =        TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState =   TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState =  TIM_OutputNState_Enable;
    TIM_OCInitStructure.TIM_Pulse =         chan1_pulse;
    TIM_OCInitStructure.TIM_OCPolarity =    TIM_OCPolarity_Low;
    TIM_OCInitStructure.TIM_OCNPolarity =   TIM_OCNPolarity_High;
    TIM_OCInitStructure.TIM_OCIdleState =   TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState =  TIM_OCIdleState_Reset;

    TIM_OC1Init(PWM_TIM, &TIM_OCInitStructure);

    TIM_Cmd(PWM_TIM, ENABLE);

//    TIM_CtrlPWMOutputs(PWM_TIM, ENABLE);
}


void timer15_ch1_pwn_output_enable_set(bool enable)
{
    TIM_CtrlPWMOutputs(PWM_TIM, enable);
}




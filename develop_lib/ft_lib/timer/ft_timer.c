#include "stddef.h"
#include "stdbool.h"

#include "ft32f0xx.h"
#include "ft_timer.h"

__IO uint16_t CCR1_Val = 40961;

static timer_handler_t m_timer_handler = NULL;

void timer_handler_register(timer_handler_t handler)
{
    m_timer_handler = handler;
}

/**
 * @brief 
 * 
 * 定时器中端周期 period = SystemCoreClock/TIM_Prescaler * TIM_Period;
 * 48000000/48*1000 = 1K = 1ms
 */
void timer_init(void)
{
    static uint16_t prescaler_value = 0;

    /* 产生1M的时钟 */
    prescaler_value = (SystemCoreClock / 1000000) - 1;

    TIM_TimeBaseInitTypeDef     TIM_TimeBaseStructure;
    TIM_OCInitTypeDef           TIM_OCInitStructure;
    NVIC_InitTypeDef            NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(USER_TIMER_CLK, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel         = USER_TIMER_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd      = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_TimeBaseStructure.TIM_Period        = 1000;
    TIM_TimeBaseStructure.TIM_Prescaler     = prescaler_value;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;

    TIM_TimeBaseInit(USER_TIMER, &TIM_TimeBaseStructure);

#if 0
    /* 配置IO输出 */
    TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_Timing;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
    TIM_OCInitStructure.TIM_Pulse       = CCR1_Val;
    TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High;

    TIM_OC1Init(USER_TIMER, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(USER_TIMER, TIM_OCPreload_Disable);
#endif

    TIM_ITConfig(USER_TIMER, TIM_IT_CC1, ENABLE);
    TIM_Cmd(USER_TIMER, ENABLE);
}

void TIM3_IRQHandler(void)
{
    /* TIM3 通道1产生定时器更新 */
    if(TIM_GetITStatus(USER_TIMER, TIM_IT_CC1) != RESET)
    {
        TIM_ClearITPendingBit(USER_TIMER, TIM_IT_CC1);

        if(m_timer_handler)
        {
            m_timer_handler();
        }
    }
}




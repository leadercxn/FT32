#include "stddef.h"
#include "stdbool.h"

#include "board_config.h"
#include "ft_timer.h"


static timer_handler_t m_timer_handler = NULL;
static uint64_t m_timer_tick_ms = 0;

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
void timer3_init(void)
{
    static uint16_t prescaler_value = 0;

    /* 产生1M的时钟 */
    prescaler_value = (SystemCoreClock / USER_TIMER_FREQ) - 1;

    TIM_TimeBaseInitTypeDef     TIM_TimeBaseStructure;
    NVIC_InitTypeDef            NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(USER_TIMER_CLK, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel         = USER_TIMER_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd      = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_TimeBaseStructure.TIM_Period        = USER_TIMER_PERIOD;
    TIM_TimeBaseStructure.TIM_Prescaler     = prescaler_value;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;

    TIM_TimeBaseInit(USER_TIMER, &TIM_TimeBaseStructure);

    TIM_ITConfig(USER_TIMER, USER_TIMER_CH, ENABLE);
    TIM_Cmd(USER_TIMER, ENABLE);
}

/* 已验证 1ms 的中断 */
void TIM3_IRQHandler(void)
{
    /* TIM3 通道1产生定时器更新 */
    if(TIM_GetITStatus(USER_TIMER, USER_TIMER_CH) != RESET)
    {
        TIM_ClearITPendingBit(USER_TIMER, USER_TIMER_CH);

        m_timer_tick_ms++;

        if(m_timer_handler)
        {
            m_timer_handler();
        }
    }
}

uint64_t ft_timer_tick_get(void)
{
    return m_timer_tick_ms;
}



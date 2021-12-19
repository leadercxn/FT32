#include "stddef.h"
#include "stdbool.h"

#include "board_config.h"
#include "ft_exit.h"

static exit_irq_handler_t  m_exit_irq_handler = NULL;

void exit_irq_handler_register(exit_irq_handler_t handler)
{
    m_exit_irq_handler = handler;
}

void exit_init(void)
{
    EXTI_InitTypeDef   EXTI_InitStructure;
    GPIO_InitTypeDef   GPIO_InitStructure;
    NVIC_InitTypeDef   NVIC_InitStructure;

    /* Enable GPIOC clock */
    RCC_AHBPeriphClockCmd(EXIT_GPIO_PORT_CLK, ENABLE);

    /* Enable SYSCFG clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    GPIO_InitStructure.GPIO_Pin = EXIT_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(EXIT_GPIO_PORT, &GPIO_InitStructure);

    SYSCFG_EXTILineConfig(EXIT_GPIO_PORT_RESOURCE, EXIT_GPIO_PIN_RESOURCE);

    EXTI_InitStructure.EXTI_Line = EXIT_LINE;  
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    /* Enable and set EXTI4_15 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = EXTI4_15_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0x01;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void exit_irq_enable_set(bool status)
{
    EXTI_InitTypeDef   EXTI_InitStructure;

    EXTI_InitStructure.EXTI_Line = EXIT_LINE;  
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = status;
    EXTI_Init(&EXTI_InitStructure);
}

void EXTI4_15_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXIT_LINE) != RESET)
  {
        EXTI_ClearITPendingBit(EXIT_LINE);

        if(m_exit_irq_handler)
        {
            m_exit_irq_handler();
        }
  }
}


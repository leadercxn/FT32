#ifndef __FT_EXIT_H
#define __FT_EXIT_H

#define EXIT_GPIO_PORT_CLK             RCC_AHBPeriph_GPIOA
#define EXIT_GPIO_PIN                  GPIO_Pin_8
#define EXIT_GPIO_PORT_RESOURCE        EXTI_PortSourceGPIOA
#define EXIT_GPIO_PIN_RESOURCE         EXTI_PinSource8
#define EXIT_TRIGGER_MODE              EXTI_Trigger_Falling
#define EXIT_GPIO_PORT                 GPIOA
#define EXIT_LINE                      EXTI_Line8

typedef void (*exit_irq_handler_t) (void);

void exit_init(void);

void exit_irq_enable_set(bool status);

void exit_irq_handler_register(exit_irq_handler_t handler);

#endif


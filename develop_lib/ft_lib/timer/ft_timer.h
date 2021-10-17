#ifndef __FT_TIMER_H
#define __FT_TIMER_H

#define TIM3_CLK        RCC_APB1Periph_TIM3
#define TIM3_IRQ        TIM3_IRQn

#define USER_TIMER_CLK  TIM3_CLK
#define USER_TIMER_IRQ  TIM3_IRQ
#define USER_TIMER      TIM3

typedef void (*timer_handler_t) (void);

void timer_init(void);

void timer_handler_register(timer_handler_t handler);

void TIM3_IRQHandler(void);

#endif


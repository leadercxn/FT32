#ifndef __FT_TIMER_H
#define __FT_TIMER_H

#define TIM3_CLK        RCC_APB1Periph_TIM3
#define TIM3_IRQ        TIM3_IRQn

#define USER_TIMER_CLK  TIM3_CLK
#define USER_TIMER_IRQ  TIM3_IRQ
#define USER_TIMER      TIM3

#define USER_TIMER_CH       TIM_IT_CC1
#define USER_TIMER_FREQ     1000000     //定时器经分频后获得的频率
#define USER_TIMER_PERIOD   1000        //定时器溢出计数


typedef void (*timer_handler_t) (void);

void timer_init(void);

void timer_handler_register(timer_handler_t handler);

uint64_t ft_timer_tick_get(void);

#endif


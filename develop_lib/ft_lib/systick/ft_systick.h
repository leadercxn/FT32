#ifndef _FT_SYSTICK_H_
#define _FT_SYSTICK_H_

#include "ft32f0xx.h"
#include "stdbool.h"

void SysTick_Init(void);
void Delay_us(uint32_t us);
void Delay_ms(uint32_t ms);

void ft_systick_init(void);
void ft_delay_us(uint32_t us);
void ft_delay_ms(uint32_t ms);

#endif

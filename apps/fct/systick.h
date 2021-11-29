#ifndef _SYSTICK_H_
#define _SYSTICK_H_

#include "ft32f0xx.h"
#include "stdbool.h"

void SysTick_Init(void);
void Delay_us(uint32_t us);
void Delay_ms(uint32_t ms);

#endif
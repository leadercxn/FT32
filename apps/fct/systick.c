#include "systick.h"
#include "stdbool.h"
#include "ft32f0xx.h"

static uint8_t sysclk = 72;
static uint8_t fac_us = 0;
static uint16_t fac_ms = 0;

/*SysTick时钟源由HCLK/8提供，当系统频率为72MHz时最小计数周期为1/9MHz,
计满9次为1us，fac_us以9为单位*/
void SysTick_Init(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); //72MHz/8 = 9MHz
	NVIC_SetPriority(SysTick_IRQn, 0);

	fac_us = sysclk / 8; //72/8 = 9,9次1uS
	fac_ms = (uint16_t)fac_us * 1000;
}

void Delay_us(uint32_t us)
{
	//	volatile uint32_t temp;
	SysTick->LOAD = (uint32_t)us * fac_us;
	SysTick->VAL = 0x00;  //清空计数器
	SysTick->CTRL = 0x01; //开始计数
						  //	temp  = SysTick->VAL;
	//当计数器的值减小到0的时候，CTRL寄存器的位16会置1
	while ((SysTick->CTRL & (0x01 << 16)) == 0)
		;
	SysTick->CTRL = 0x00; //停止计数
	SysTick->VAL = 0x00;  //清空计数器
}

void Delay_ms(uint32_t ms)
{
	//	volatile uint32_t temp;
	SysTick->LOAD = (uint32_t)ms * fac_ms;
	SysTick->VAL = 0x00;  //清空计数器
	SysTick->CTRL = 0x01; //开始计数
						  //	temp  = SysTick->VAL;
	//当计数器的值减小到0的时候，CTRL寄存器的位16会置1
	while ((SysTick->CTRL & (0x01 << 16)) == 0)
		;
	SysTick->CTRL = 0x00; //停止计数
	SysTick->VAL = 0x00;  //清空计数器
}

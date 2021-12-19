#include "stdbool.h"
#include "ft32f0xx.h"
#include "ft_systick.h"

static uint16_t sysclk = 288;	//还不确定为啥是 72*4 才可以较为精准的延时
static uint32_t fac_us = 0;
static uint32_t fac_ms = 0;

/*SysTick时钟源由HCLK/8提供，当系统频率为72MHz时最小计数周期为1/9MHz,
计满9次为1us，fac_us以9为单位*/
void SysTick_Init(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); //72MHz/8 = 9MHz
	NVIC_SetPriority(SysTick_IRQn, 3);

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
	while ((SysTick->CTRL & (0x01 << 16)) == 0);
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
	while ((SysTick->CTRL & (0x01 << 16)) == 0);
	SysTick->CTRL = 0x00; //停止计数
	SysTick->VAL = 0x00;  //清空计数器
}


/*SysTick时钟源由HCLK/8提供，当系统频率为72MHz时最小计数周期为1/9MHz,
计满9次为1us，fac_us以9为单位*/
void ft_systick_init(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); //72MHz/8 = 9MHz
	NVIC_SetPriority(SysTick_IRQn, 3);

	fac_us = sysclk / 8; //72/8 = 9,9次1uS
	fac_ms = (uint16_t)fac_us * 1000;
}

void ft_delay_us(uint32_t us)
{
	//	volatile uint32_t temp;
	SysTick->LOAD = (uint32_t)us * fac_us;
	SysTick->CTRL = 0x00; //停止计数
	SysTick->VAL = 0x00;  //清空计数器
	SysTick->CTRL = 0x01; //开始计数
						  //	temp  = SysTick->VAL;
	//当计数器的值减小到0的时候，CTRL寄存器的位16会置1
	while ((SysTick->CTRL & (0x01 << 16)) == 0);
	SysTick->CTRL = 0x00; //停止计数
	SysTick->VAL = 0x00;  //清空计数器
}

/**
 * @brief 当ms过大，导致溢出，是个BUG
 */
void ft_delay_ms(uint32_t ms)
{
	uint32_t i = 0;
	for(i = 0; i < ms; i++)
	{
		//	volatile uint32_t temp;
		SysTick->LOAD = (uint32_t)1 * fac_ms;
		SysTick->CTRL = 0x00; //停止计数
		SysTick->VAL = 0x00;  //清空计数器
		SysTick->CTRL = 0x01; //开始计数
							//	temp  = SysTick->VAL;
		//当计数器的值减小到0的时候，CTRL寄存器的位16会置1
		while ((SysTick->CTRL & (0x01 << 16)) == 0);
		SysTick->CTRL = 0x00; //停止计数
		SysTick->VAL = 0x00;  //清空计数器
	}
}

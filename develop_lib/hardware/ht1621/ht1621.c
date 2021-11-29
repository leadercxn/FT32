#include "ft32f0xx.h"
#include "ft_gpio.h"
#include "util.h"
#include "stdbool.h"
#include "trace.h"
#include "board_config.h"
#include "ht1621.h"

unsigned char DispTab[] = {0xEB, 0x0A, 0xAD, 0x8F, 0x4E, 0xC7, 0xE7, 0x8A, 0xEF, 0xCF, 0x85, 0xEE, 0x67, 0xE1, 0x2F, 0xE5, 0xE4};

uint8_t n1, n2, n3, n4;

#define HT1621_CS GPIO_Pin_4
#define HT1621_WR GPIO_Pin_5
#define HT1621_RD GPIO_Pin_6
#define HT1621_DATA GPIO_Pin_7

/**************************************************************************
*函数名：HT1621_GPIO_Config
*参  数：无
*返回值：无
*概  述：配置HT1621的IO口，并打开IO口外设时钟
**************************************************************************/
void HT1621_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable GPIO clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	//设置为推挽输出  DATA:PA7 CS:PA4
	GPIO_InitStructure.GPIO_Pin = HT1621_WR | HT1621_DATA | HT1621_CS;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**************************************************************************
*函数名：CS、DATA、GND、WR
*参  数：bitstatus引脚状态可取High或Low
*返回值：无
*概  述：设置HT1621的IO口CS、DATA、GND、WR、CS电平高低
**************************************************************************/
void CS(BitStatus bitstatus)
{
	switch (bitstatus)
	{
	case High:
		GPIO_SetBits(GPIOA, HT1621_CS);
		break;
	case Low:
		GPIO_ResetBits(GPIOA, HT1621_CS);
		break;
	}
}
void DATA(BitStatus bitstatus)
{
	switch (bitstatus)
	{
	case High:
		GPIO_SetBits(GPIOA, HT1621_DATA);
		break;
	case Low:
		GPIO_ResetBits(GPIOA, HT1621_DATA);
		break;
	}
}
void WR(BitStatus bitstatus)
{
	switch (bitstatus)
	{
	case High:
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
		break;
	case Low:
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		break;
	}
}
void GND(BitStatus bitstatus)
{
	// switch (bitstatus)
	// {
	// case High:
	// 	GPIO_SetBits(GPIOA, GPIO_Pin_3);
	// 	break;
	// case Low:
	// 	GPIO_ResetBits(GPIOA, GPIO_Pin_3);
	// 	break;
	// }
}

/**************************************************************************
*函数名：HT1621_WriteData
*参  数：data要写入的数据，cnt写入的数据量
*返回值：无
*概  述：向HT1621写入cnt个数据，高位在前
**************************************************************************/
void HT1621_WriteData(uint8_t data, uint8_t cnt)
{
	uint8_t i;

	for (i = 0; i < cnt; i++)
	{
		WR(Low);

		if ((data & 0x80) == 0x80) //判断最高位是否为1
		{
			DATA(High);
		}
		else
		{
			DATA(Low);
		}

		data <<= 1;	 //左移一位，丢弃已经写入的最高位
		Delay_us(2); //WR引脚变化稍微给点延时，防止速度过快数据传输错误
		WR(High);
		Delay_us(2);
	}
}

/**************************************************************************
*函数名：HT1621_WriteCmd
*参  数：cmd待发送的命令
*返回值：无
*概  述：向HT1621发送命令
**************************************************************************/
void HT1621_WriteCmd(uint8_t cmd)
{
	CS(Low);
	HT1621_WriteData(0x80, 4); //100 0
	HT1621_WriteData(cmd, 8);
	CS(High);
	Delay_ms(1);
}

/**************************************************************************
*函数名：HT1621_Init
*参  数：无
*返回值：无
*概  述：HT1621初始化
**************************************************************************/
void HT1621_Init(void)
{
	HT1621_GPIO_Config();
	// GND(Low);

	HT1621_WriteCmd(BIAS);
	HT1621_WriteCmd(RC256);
	HT1621_WriteCmd(SYSDIS);
	HT1621_WriteCmd(WDTDIS);
	HT1621_WriteCmd(SYSEN);
	HT1621_WriteCmd(LCDON);
}

void HT1621_WriteOneData(uint8_t addr, uint8_t data)
{
	CS(Low);

	HT1621_WriteData(0xA0, 3); //101
	HT1621_WriteData(addr << 2, 6);
	HT1621_WriteData(data, 4);

	CS(High);
	Delay_ms(1);
}

/**************************************************************************
*函数名：HT1621_WriteAllData
*参  数：addr写入数据的地址，*p待写入的数据指针，cnt写入的字节数
*返回值：无
*概  述：HT1621初始化
**************************************************************************/
void HT1621_WriteAllData(uint8_t addr, uint8_t *p, uint8_t cnt)
{
	uint8_t i;

	CS(Low);
	HT1621_WriteData(0xa0, 3);		//写入数据标志101
	HT1621_WriteData(addr << 2, 6); //写入地址数据
	for (i = 0; i < cnt; i++)		//写入所有数据
	{
		HT1621_WriteData(*p, 8);
		p++;
	}
	CS(High);
	Delay_ms(1);
}

void Display(void)
{
	HT1621_WriteOneData(0, DispTab[n4]);
	HT1621_WriteOneData(1, DispTab[n4] << 4);
	HT1621_WriteOneData(2, DispTab[n3]);
	HT1621_WriteOneData(3, DispTab[n3] << 4);
	HT1621_WriteOneData(4, DispTab[n2]);
	HT1621_WriteOneData(5, DispTab[n2] << 4);
	HT1621_WriteOneData(6, DispTab[n1]);
	HT1621_WriteOneData(7, DispTab[n1] << 4);
}

void Display_Dot(void)
{
	HT1621_WriteOneData(0, DispTab[n4] | 0x10); //P1
												//HT1621_WriteOneData(2 , DispTab[n3]|0x10);    //2P
												//HT1621_WriteOneData(4 , DispTab[n2]|0x10);    //3P
												//HT1621_WriteOneData(6 , DispTab[n1]|0x10);    //4P
}
void NotDisplay_Dot(void)
{
	HT1621_WriteOneData(0, DispTab[n4] | 0x00); //P1
}

void Data_Convertor(uint32_t value)
{
	n4 = value / 1000;
	n3 = value % 1000 / 100;
	n2 = value % 100 / 10;
	n1 = value % 10;
}

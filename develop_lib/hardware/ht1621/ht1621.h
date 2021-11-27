#ifndef _HT1621_H_
#define _HT1621_H_

#include "ft32f0xx.h"
#include "stdbool.h"

typedef enum
{
    High = 0,
    Low = 1
} BitStatus;

#define BIAS 0x52   //0b1000 0101 0010  1/3duty 4com
#define SYSDIS 0X00 //0b1000 0000 0000  关振系统荡器和LCD偏压发生器
#define SYSEN 0X02  //0b1000 0000 0010 打开系统振荡器
#define LCDOFF 0X04 //0b1000 0000 0100  关LCD偏压
#define LCDON 0X06  //0b1000 0000 0110  打开LCD偏压
#define XTAL 0x28   //0b1000 0010 1000 外部接时钟
#define RC256 0X30  //0b1000 0011 0000  内部时钟
#define WDTDIS 0X0A //0b1000 0000 1010  禁止看门狗

void HT1621_GPIO_Config(void);
void CS(BitStatus bitstatus);
void DATA(BitStatus bitstatus);
void WR(BitStatus bitstatus);
void GND(BitStatus bitstatus);
void HT1621_WriteData(uint8_t data, uint8_t cnt);
void HT1621_WriteCmd(uint8_t cmd);
void HT1621_Init(void);
void HT1621_WriteOneData(uint8_t addr, uint8_t data);
void HT1621_WriteAllData(uint8_t addr, uint8_t *p, uint8_t cnt);
void Display(void);
void Data_Convertor(uint32_t value);
void Display_Dot(void);
void NotDisplay_Dot(void);

#endif

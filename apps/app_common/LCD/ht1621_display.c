/*********************************************************************
 * INCLUDES
 */
#include "ft32f0xx.h"
#include "stdbool.h"
#include "stdbool.h"
#include "board_ht1621.h"
#include "ht1621_display.h"

/**
 @brief 计算频率百位，如87.5MHz，则百位0
 @param frequency -[in] 频率
 @return 无
*/
static void calculateHundreds(uint32_t frequency)
{
    uint8_t s_alarm;

    if (frequency / 100000 == 1)
    {
        s_alarm |= DISPLAY_1_1;
        HT1621_WriteData4Bit(FM_SOUND_1_ADDR, s_alarm); // 1亮
    }
    else
    {
        s_alarm &= 0x07;
        HT1621_WriteData4Bit(FM_SOUND_1_ADDR, s_alarm); // 1灭
    }
}

/**
 @brief 计算频率十位，如87.5MHz，则十位8
 @param frequency -[in] 频率
 @return 无
*/
static void calculateTens(uint32_t frequency)
{
    if (frequency / 10000 % 10 == 0)
    {
        HT1621_WriteData8Bit(FIRST_8_50us_ADDR, 0xAF); // 0
    }
    else if (frequency / 10000 % 10 == 8)
    {
        HT1621_WriteData8Bit(FIRST_8_50us_ADDR, 0xEF); // 8
    }
    else if (frequency / 10000 % 10 == 9)
    {
        HT1621_WriteData8Bit(FIRST_8_50us_ADDR, 0xED); // 9
    }
}

/**
 @brief 计算频率个位，如87.5MHz，则个位7
 @param frequency -[in] 频率
 @return 无
*/
static void calculateOnes(uint32_t frequency)
{
    if (frequency / 1000 % 10 == 0)
    {
        HT1621_WriteData8Bit(SECOND_8_POINT_ADDR, 0xBF); // 0.
    }
    else if (frequency / 1000 % 10 == 1)
    {
        HT1621_WriteData8Bit(SECOND_8_POINT_ADDR, 0xB0); // 1.
    }
    else if (frequency / 1000 % 10 == 2)
    {
        HT1621_WriteData8Bit(SECOND_8_POINT_ADDR, 0xDB); // 2.
    }
    else if (frequency / 1000 % 10 == 3)
    {
        HT1621_WriteData8Bit(SECOND_8_POINT_ADDR, 0xF9); // 3.
    }
    else if (frequency / 1000 % 10 == 4)
    {
        HT1621_WriteData8Bit(SECOND_8_POINT_ADDR, 0xF4); // 4.
    }
    else if (frequency / 1000 % 10 == 5)
    {
        HT1621_WriteData8Bit(SECOND_8_POINT_ADDR, 0x7D); // 5.
    }
    else if (frequency / 1000 % 10 == 6)
    {
        HT1621_WriteData8Bit(SECOND_8_POINT_ADDR, 0x7F); // 6.
    }
    else if (frequency / 1000 % 10 == 7)
    {
        HT1621_WriteData8Bit(SECOND_8_POINT_ADDR, 0xB8); // 7.
    }
    else if (frequency / 1000 % 10 == 8)
    {
        HT1621_WriteData8Bit(SECOND_8_POINT_ADDR, 0xFF); // 8.
    }
    else if (frequency / 1000 % 10 == 9)
    {
        HT1621_WriteData8Bit(SECOND_8_POINT_ADDR, 0xFD); // 9.
    }
}

/**
 @brief 计算频率小数位，如87.5MHz，则小数位5
 @param frequency -[in] 频率
 @return 无
*/
static void calculateDecimals(uint32_t frequency)
{
    if (frequency / 100 % 10 == 0)
    {
        HT1621_WriteData8Bit(THIRD_8_75us_ADDR, 0xAF); // 0
    }
    else if (frequency / 100 % 10 == 1)
    {
        HT1621_WriteData8Bit(THIRD_8_75us_ADDR, 0xA0); // 1
    }
    else if (frequency / 100 % 10 == 2)
    {
        HT1621_WriteData8Bit(THIRD_8_75us_ADDR, 0xCB); // 2
    }
    else if (frequency / 100 % 10 == 3)
    {
        HT1621_WriteData8Bit(THIRD_8_75us_ADDR, 0xE9); // 3
    }
    else if (frequency / 100 % 10 == 4)
    {
        HT1621_WriteData8Bit(THIRD_8_75us_ADDR, 0xE4); // 4
    }
    else if (frequency / 100 % 10 == 5)
    {
        HT1621_WriteData8Bit(THIRD_8_75us_ADDR, 0x6D); // 5
    }
    else if (frequency / 100 % 10 == 6)
    {
        HT1621_WriteData8Bit(THIRD_8_75us_ADDR, 0x6F); // 6
    }
    else if (frequency / 100 % 10 == 7)
    {
        HT1621_WriteData8Bit(THIRD_8_75us_ADDR, 0xA8); // 7
    }
    else if (frequency / 100 % 10 == 8)
    {
        HT1621_WriteData8Bit(THIRD_8_75us_ADDR, 0xEF); // 8
    }
    else if (frequency / 100 % 10 == 9)
    {
        HT1621_WriteData8Bit(THIRD_8_75us_ADDR, 0xED); // 9
    }
}

/**
 @brief LCD屏显示频率
 @param frequency -[in] 频率
 @return 无
*/
void LCD_ShowFrequency(uint32_t frequency)
{
    calculateHundreds(frequency); // 百位
    calculateTens(frequency);     // 十位
    calculateOnes(frequency);     // 个位
    calculateDecimals(frequency); // 小数位
}

/*********************************************************************
 * INCLUDES
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "board_ht1621.h"
#include "ht1621.h"

#define DELAY_10_US 10 * 4
#define DELAY_500_MS 500 * 4

#define DELAY_1_MS 1
#define DELAY_10_MS 10
#define DELAY_100_MS 400
/*********************************************************************
 * PUBLIC FUNCTIONS
 */
/**
 @brief 初始化LCD屏，HT1621芯片
 @param 无
 @return 无
*/
void Board_HT1621_Init(ht1621_t *p_dev)
{

    p_dev->gpio_config();

    p_dev->delay_ms(DELAY_10_MS); // - - 延时使LCD工作电压稳定

    p_dev->CS_HIGH();
    p_dev->DATA_HIGH();
    p_dev->WR_HIGH();

    p_dev->delay_ms(DELAY_100_MS); // - - 延时使LCD工作电压稳定

    Board_HT1621_WriteCommand(p_dev, HT1621_SYS_EN); // 打开系统振荡器
    Board_HT1621_WriteCommand(p_dev, HT1621_BIAS);   // BIAS 13 4个公共口
    Board_HT1621_WriteCommand(p_dev, HT1621_RC256);  // 使用RC_256K系统时钟源，片内RC振荡器
    Board_HT1621_WriteCommand(p_dev, HT1621_WDT_DIS);
    Board_HT1621_WriteCommand(p_dev, HT1621_LCD_ON);
}

/**
 @brief 写入命令，命令标志100
 @param cmd -[in] 命令数据
 @return 无
*/
void Board_HT1621_WriteCommand(ht1621_t *p_dev, uint8_t cmd)
{
    uint8_t i;

    p_dev->CS_LOW(); // CS = 0
    p_dev->delay_ms(DELAY_1_MS);

    // 写入命令标志,DATA:100
    p_dev->WR_LOW();             // WR = 0
    p_dev->delay_ms(DELAY_1_MS); //延时
    p_dev->DATA_HIGH();          // DATA = 1
    p_dev->delay_ms(DELAY_1_MS); //延时
    p_dev->WR_HIGH();            // WR = 1
    p_dev->delay_ms(DELAY_1_MS); //延时

    p_dev->WR_LOW();             // WR = 0
    p_dev->delay_ms(DELAY_1_MS); //延时
    p_dev->DATA_LOW();           // DATA = 0
    p_dev->delay_ms(DELAY_1_MS); //延时
    p_dev->WR_HIGH();            // WR = 1
    p_dev->delay_ms(DELAY_1_MS); //延时

    p_dev->WR_LOW();             // WR = 0
    p_dev->delay_ms(DELAY_1_MS); //延时
    p_dev->DATA_LOW();           // DATA = 0
    p_dev->delay_ms(DELAY_1_MS); //延时
    p_dev->WR_HIGH();            // WR = 1
    p_dev->delay_ms(DELAY_1_MS); //延时

    // Datasheet中命令后的C8为0
    p_dev->WR_LOW();             // WR = 0
    p_dev->delay_ms(DELAY_1_MS); //延时
    p_dev->DATA_LOW();           // DATA = 0
    p_dev->delay_ms(DELAY_1_MS); //延时
    p_dev->WR_HIGH();            // WR = 1
    p_dev->delay_ms(DELAY_1_MS); //延时

    // Datasheet中命令后的C7~C0
    for (i = 0; i < 8; i++)
    {
        p_dev->WR_LOW();             // WR = 0
        p_dev->delay_ms(DELAY_1_MS); //延时
        if ((cmd << i) & 0x80)
        {
            p_dev->DATA_HIGH(); // DATA = 1
        }
        else
        {
            p_dev->DATA_LOW(); // DATA = 0
        }
        p_dev->delay_ms(DELAY_1_MS); //延时
        p_dev->WR_HIGH();            // WR = 1
        p_dev->delay_ms(DELAY_1_MS); //延时
    }

    p_dev->CS_HIGH();            // CS = 1
    p_dev->delay_ms(DELAY_1_MS); //延时
}

/**
 @brief 写入4位数据，写入数据标志101
 @param addr -[in] 写入起始地址
 @param data -[in] 写入数据，因为HT1621的数据位4位，所以实际写入数据为参数的后4位
 @return 无
*/
void Board_HT1621_WriteData4Bit(ht1621_t *p_dev, uint8_t addr, uint8_t data)
{
    uint8_t i;

    p_dev->CS_LOW(); // CS = 0
    p_dev->delay_ms(DELAY_1_MS);

    // 写入数据标志,DATA:101
    p_dev->WR_LOW();             // WR = 0
    p_dev->delay_ms(DELAY_1_MS); //延时
    p_dev->DATA_HIGH();          // DATA = 1
    p_dev->delay_ms(DELAY_1_MS); //延时
    p_dev->WR_HIGH();            // WR = 1
    p_dev->delay_ms(DELAY_1_MS); //延时

    p_dev->WR_LOW();             // WR = 0
    p_dev->delay_ms(DELAY_1_MS); //延时
    p_dev->DATA_LOW();           // DATA = 0
    p_dev->delay_ms(DELAY_1_MS); //延时
    p_dev->WR_HIGH();            // WR = 1
    p_dev->delay_ms(DELAY_1_MS); //延时

    p_dev->WR_LOW();             // WR = 0
    p_dev->delay_ms(DELAY_1_MS); //延时
                                 // LCD_DATA_1(); // DATA = 1
    p_dev->delay_ms(DELAY_1_MS); //延时
    p_dev->WR_HIGH();            // WR = 1
    p_dev->delay_ms(DELAY_1_MS); //延时
    // 写入地址,Datasheet中A5~A0
    for (i = 0; i < 6; i++)
    {
        p_dev->WR_LOW();             // WR = 0
        p_dev->delay_ms(DELAY_1_MS); //延时
        if ((addr << i) & 0x80)
        {
            p_dev->DATA_HIGH(); // DATA = 1
        }
        else
        {
            p_dev->DATA_LOW(); // DATA = 0
        }
        p_dev->delay_ms(DELAY_1_MS); //延时
        p_dev->WR_HIGH();            // WR = 1
        p_dev->delay_ms(DELAY_1_MS); //延时
    }
    // 写入数据,Datasheet中D0~D3
    for (i = 0; i < 4; i++)
    {
        p_dev->WR_LOW();             // WR = 0
        p_dev->delay_ms(DELAY_1_MS); //延时
        if ((data >> (3 - i)) & 0x01)
        {
            p_dev->DATA_HIGH(); // DATA = 1
        }
        else
        {
            p_dev->DATA_LOW(); // DATA = 0
        }
        p_dev->delay_ms(DELAY_1_MS); //延时
        p_dev->WR_HIGH();            // WR = 1
        p_dev->delay_ms(DELAY_1_MS); //延时
    }

    p_dev->CS_HIGH();            // CS = 1
    p_dev->delay_ms(DELAY_1_MS); //延时
}

/**
 @brief 写入8位数据，写入数据标志101
 @param addr -[in] 写入起始地址
 @param data -[in] 写入数据
 @return 无
*/
void Board_HT1621_WriteData8Bit(ht1621_t *p_dev, uint8_t addr, uint8_t data)
{
    uint8_t i;

    p_dev->CS_LOW();             // CS = 0
    p_dev->delay_ms(DELAY_1_MS); //延时

    // 写入数据标志,DATA:101
    p_dev->WR_LOW();             // WR = 0
    p_dev->delay_ms(DELAY_1_MS); //延时
    p_dev->DATA_HIGH();          // DATA = 1
    p_dev->delay_ms(DELAY_1_MS); //延时
    p_dev->WR_HIGH();            // WR = 1
    p_dev->delay_ms(DELAY_1_MS); //延时

    p_dev->WR_LOW();             // WR = 0
    p_dev->delay_ms(DELAY_1_MS); //延时
    p_dev->DATA_LOW();           // DATA = 0
    p_dev->delay_ms(DELAY_1_MS); //延时
    p_dev->WR_HIGH();            // WR = 1
    p_dev->delay_ms(DELAY_1_MS); //延时

    p_dev->WR_LOW();             // WR = 0
    p_dev->delay_ms(DELAY_1_MS); //延时
    p_dev->DATA_HIGH();          // DATA = 1
    p_dev->delay_ms(DELAY_1_MS); //延时
    p_dev->WR_HIGH();            // WR = 1
    p_dev->delay_ms(DELAY_1_MS); //延时

    // 写入地址,Datasheet中A5~A0
    for (i = 0; i < 6; i++)
    {
        p_dev->WR_LOW();             // WR = 0
        p_dev->delay_ms(DELAY_1_MS); //延时
        if ((addr << i) & 0x80)
        {
            p_dev->DATA_HIGH(); // DATA = 1
        }
        else
        {
            p_dev->DATA_LOW(); // DATA = 0
        }
        p_dev->delay_ms(DELAY_1_MS); //延时
        p_dev->WR_HIGH();            // WR = 1
        p_dev->delay_ms(DELAY_1_MS); //延时
    }
    // 写入数据,Datasheet中两组D0~D3
    for (i = 0; i < 8; i++)
    {
        p_dev->WR_LOW();             // WR = 0
        p_dev->delay_ms(DELAY_1_MS); //延时
        if ((data >> (7 - i)) & 0x01)
        {
            p_dev->DATA_HIGH(); // DATA = 1
        }
        else
        {
            p_dev->DATA_LOW(); // DATA = 0
        }
        p_dev->delay_ms(DELAY_1_MS); //延时
        p_dev->WR_HIGH();            // WR = 1
        p_dev->delay_ms(DELAY_1_MS); //延时
    }

    p_dev->CS_HIGH();            // CS = 1
    p_dev->delay_ms(DELAY_1_MS); //延时
}

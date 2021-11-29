/*********************************************************************
 * INCLUDES
 */
#include "stdbool.h"
#include "board_ht1621.h"
#include "mid_delay.h"
#include "systick.h"

void vTaskDelay(uint16_t ms)
{
    Delay_ms(ms);
}

/*********************************************************************
 * PUBLIC FUNCTIONS
 */
/**
 @brief 初始化LCD屏，HT1621芯片
 @param 无
 @return 无
*/
void HT1621_Init(void)
{

    vTaskDelay(10);

    LCD_CS_1();
    LCD_DATA_1();
    LCD_WR_1();

    vTaskDelay(100); // 延时使LCD工作电压稳定

    HT1621_WriteCommand(HT1621_SYS_EN); // 打开系统振荡器
    HT1621_WriteCommand(HT1621_BIAS);   // BIAS 13 4个公共口
    HT1621_WriteCommand(HT1621_RC256);  // 使用RC_256K系统时钟源，片内RC振荡器
    HT1621_WriteCommand(HT1621_WDT_DIS);
    HT1621_WriteCommand(HT1621_LCD_ON);
}

/**
 @brief 写入命令，命令标志100
 @param cmd -[in] 命令数据
 @return 无
*/
void HT1621_WriteCommand(uint8_t cmd)
{
    uint8_t i;

    LCD_CS_0(); // CS = 0
    vTaskDelay(1);

    // 写入命令标志,DATA:100
    LCD_WR_0(); // WR = 0
    vTaskDelay(1);
    LCD_DATA_1(); // DATA = 1
    vTaskDelay(1);
    LCD_WR_1(); // WR = 1
    vTaskDelay(1);

    LCD_WR_0(); // WR = 0
    vTaskDelay(1);
    LCD_DATA_0(); // DATA = 0
    vTaskDelay(1);
    LCD_WR_1(); // WR = 1
    vTaskDelay(1);

    LCD_WR_0(); // WR = 0
    vTaskDelay(1);
    LCD_DATA_0(); // DATA = 0
    vTaskDelay(1);
    LCD_WR_1(); // WR = 1
    vTaskDelay(1);

    // Datasheet中命令后的C8为0
    LCD_WR_0(); // WR = 0
    vTaskDelay(1);
    LCD_DATA_0(); // DATA = 0
    vTaskDelay(1);
    LCD_WR_1(); // WR = 1
    vTaskDelay(1);

    // Datasheet中命令后的C7~C0
    for (i = 0; i < 8; i++)
    {
        LCD_WR_0(); // WR = 0
        vTaskDelay(1);
        if ((cmd << i) & 0x80)
        {
            LCD_DATA_1(); // DATA = 1
        }
        else
        {
            LCD_DATA_0(); // DATA = 0
        }
        vTaskDelay(1);
        LCD_WR_1(); // WR = 1
        vTaskDelay(1);
    }

    LCD_CS_1(); // CS = 1
    vTaskDelay(1);
}

/**
 @brief 写入4位数据，写入数据标志101
 @param addr -[in] 写入起始地址
 @param data -[in] 写入数据，因为HT1621的数据位4位，所以实际写入数据为参数的后4位
 @return 无
*/
void HT1621_WriteData4Bit(uint8_t addr, uint8_t data)
{
    uint8_t i;

    LCD_CS_0(); // CS = 0
    vTaskDelay(1);

    // 写入数据标志,DATA:101
    LCD_WR_0(); // WR = 0
    vTaskDelay(1);
    LCD_DATA_1(); // DATA = 1
    vTaskDelay(1);
    LCD_WR_1(); // WR = 1
    vTaskDelay(1);

    LCD_WR_0(); // WR = 0
    vTaskDelay(1);
    LCD_DATA_0(); // DATA = 0
    vTaskDelay(1);
    LCD_WR_1(); // WR = 1
    vTaskDelay(1);

    LCD_WR_0(); // WR = 0
    vTaskDelay(1);
    LCD_DATA_1(); // DATA = 1
    vTaskDelay(1);
    LCD_WR_1(); // WR = 1
    vTaskDelay(1);

    // 写入地址,Datasheet中A5~A0
    for (i = 0; i < 6; i++)
    {
        LCD_WR_0(); // WR = 0
        vTaskDelay(1);
        if ((addr << i) & 0x80)
        {
            LCD_DATA_1(); // DATA = 1
        }
        else
        {
            LCD_DATA_0(); // DATA = 0
        }
        vTaskDelay(1);
        LCD_WR_1(); // WR = 1
        vTaskDelay(1);
    }
    // 写入数据,Datasheet中D0~D3
    for (i = 0; i < 4; i++)
    {
        LCD_WR_0(); // WR = 0
        vTaskDelay(1);
        if ((data >> (3 - i)) & 0x01)
        {
            LCD_DATA_1(); // DATA = 1
        }
        else
        {
            LCD_DATA_0(); // DATA = 0
        }
        vTaskDelay(1);
        LCD_WR_1(); // WR = 1
        vTaskDelay(1);
    }

    LCD_CS_1(); // CS = 1
    vTaskDelay(1);
}

/**
 @brief 写入8位数据，写入数据标志101
 @param addr -[in] 写入起始地址
 @param data -[in] 写入数据
 @return 无
*/
void HT1621_WriteData8Bit(uint8_t addr, uint8_t data)
{
    uint8_t i;

    LCD_CS_0(); // CS = 0
    vTaskDelay(1);

    // 写入数据标志,DATA:101
    LCD_WR_0(); // WR = 0
    vTaskDelay(1);
    LCD_DATA_1(); // DATA = 1
    vTaskDelay(1);
    LCD_WR_1(); // WR = 1
    vTaskDelay(1);

    LCD_WR_0(); // WR = 0
    vTaskDelay(1);
    LCD_DATA_0(); // DATA = 0
    vTaskDelay(1);
    LCD_WR_1(); // WR = 1
    vTaskDelay(1);

    LCD_WR_0(); // WR = 0
    vTaskDelay(1);
    LCD_DATA_1(); // DATA = 1
    vTaskDelay(1);
    LCD_WR_1(); // WR = 1
    vTaskDelay(1);

    // 写入地址,Datasheet中A5~A0
    for (i = 0; i < 6; i++)
    {
        LCD_WR_0(); // WR = 0
        vTaskDelay(1);
        if ((addr << i) & 0x80)
        {
            LCD_DATA_1(); // DATA = 1
        }
        else
        {
            LCD_DATA_0(); // DATA = 0
        }
        vTaskDelay(1);
        LCD_WR_1(); // WR = 1
        vTaskDelay(1);
    }
    // 写入数据,Datasheet中两组D0~D3
    for (i = 0; i < 8; i++)
    {
        LCD_WR_0(); // WR = 0
        vTaskDelay(1);
        if ((data >> (7 - i)) & 0x01)
        {
            LCD_DATA_1(); // DATA = 1
        }
        else
        {
            LCD_DATA_0(); // DATA = 0
        }
        vTaskDelay(1);
        LCD_WR_1(); // WR = 1
        vTaskDelay(1);
    }

    LCD_CS_1(); // CS = 1
    vTaskDelay(1);
}

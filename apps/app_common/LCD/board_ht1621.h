#ifndef _BOARD_HT1621_H_
#define _BOARD_HT1621_H_

/*********************************************************************
 * INCLUDES
 */
#include "ft32f0xx.h"
#include "stdbool.h"

/*********************************************************************
 * DEFINITIONS
 */
// #define HT1621_CS_PORT GPIOA               // GPIO端口
// #define HT1621_CS_CLK RCC_APB2Periph_GPIOA // GPIO端口时钟
// #define HT1621_CS_PIN GPIO_Pin_4           // 定义HT1621的CS管脚

// #define HT1621_DATA_PORT GPIOA               // GPIO端口
// #define HT1621_DATA_CLK RCC_APB2Periph_GPIOA // GPIO端口时钟
// #define HT1621_DATA_PIN GPIO_Pin_7           // 定义HT1621的DATA管脚

// #define HT1621_WR_PORT GPIOA               // GPIO端口
// #define HT1621_WR_CLK RCC_APB2Periph_GPIOA // GPIO端口时钟
// #define HT1621_WR_PIN GPIO_Pin_5           // 定义HT1621的WR管脚

/* Communication boards SPIx Interface */
#define SPIx SPI1
#define SPIx_CLK RCC_APB2Periph_SPI1
#define SPIx_IRQn SPI1_IRQn
#define SPIx_IRQHandler SPI1_IRQHandler

#define SPIx_SCK_PIN GPIO_Pin_5
#define SPIx_SCK_GPIO_PORT GPIOA
#define SPIx_SCK_GPIO_CLK RCC_AHBPeriph_GPIOA
#define SPIx_SCK_SOURCE GPIO_PinSource5
#define SPIx_SCK_AF GPIO_AF_0

#define SPIx_MISO_PIN GPIO_Pin_4
#define SPIx_MISO_GPIO_PORT GPIOB
#define SPIx_MISO_GPIO_CLK RCC_AHBPeriph_GPIOB
#define SPIx_MISO_SOURCE GPIO_PinSource4
#define SPIx_MISO_AF GPIO_AF_0

#define SPIx_MOSI_PIN GPIO_Pin_7
#define SPIx_MOSI_GPIO_PORT GPIOA
#define SPIx_MOSI_GPIO_CLK RCC_AHBPeriph_GPIOA
#define SPIx_MOSI_SOURCE GPIO_PinSource7
#define SPIx_MOSI_AF GPIO_AF_0

#define HT1621_CS_PORT GPIOA              // GPIO端口
#define HT1621_CS_CLK RCC_AHBPeriph_GPIOA // GPIO端口时钟
#define HT1621_CS_PIN GPIO_Pin_4          // 定义HT1621的CS管脚

#define HT1621_DATA_PORT GPIOA              // GPIO端口
#define HT1621_DATA_CLK RCC_AHBPeriph_GPIOA // GPIO端口时钟
#define HT1621_DATA_PIN GPIO_Pin_7          // 定义HT1621的DATA管脚

#define HT1621_WR_PORT GPIOA              // GPIO端口
#define HT1621_WR_CLK RCC_AHBPeriph_GPIOA // GPIO端口时钟
#define HT1621_WR_PIN GPIO_Pin_5          // 定义HT1621的WR管脚

#define LCD_CS_0() GPIO_ResetBits(HT1621_CS_PORT, HT1621_CS_PIN)
#define LCD_CS_1() GPIO_SetBits(HT1621_CS_PORT, HT1621_CS_PIN)
#define LCD_DATA_0() GPIO_ResetBits(HT1621_DATA_PORT, HT1621_DATA_PIN)
#define LCD_DATA_1() GPIO_SetBits(HT1621_DATA_PORT, HT1621_DATA_PIN)
#define LCD_WR_0() GPIO_ResetBits(HT1621_WR_PORT, HT1621_WR_PIN)
#define LCD_WR_1() GPIO_SetBits(HT1621_WR_PORT, HT1621_WR_PIN)

#define COMMAND_CODE 0x80    // 命令码
#define WRITE_DATA_CODE 0xA0 // 写命令

#define HT1621_BIAS 0x52     // 1/3duty 4com
#define HT1621_SYS_DIS 0x00  // 关振系统荡器和LCD偏压发生器
#define HT1621_SYS_EN 0x02   // 打开系统振荡器
#define HT1621_LCD_OFF 0x04  // 关闭LCD偏压
#define HT1621_LCD_ON 0x06   // 打开LCE偏压
#define HT1621_XTAL 0x28     // 外部接时钟
#define HT1621_RC256 0x30    // 内部时钟
#define HT1621_WDT_DIS 0X0A  // 关闭看门狗
#define HT1621_TONE_ON 0x12  // 打开声音输出
#define HT1621_TONE_OFF 0x10 // 关闭声音输出

/*********************************************************************
 * API FUNCTIONS
 */
void HT1621_Init(void);
void HT1621_WriteCommand(uint8_t cmd);
void HT1621_WriteData4Bit(uint8_t addr, uint8_t data);
void HT1621_WriteData8Bit(uint8_t addr, uint8_t data);

#endif /* _BOARD_HT1621_H_ */

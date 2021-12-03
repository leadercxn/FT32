#ifndef _BOARD_HT1621_H_
#define _BOARD_HT1621_H_
#include "ht1621.h"

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
void Board_HT1621_Init(ht1621_t *p_dev);
void Board_HT1621_WriteCommand(ht1621_t *p_dev, uint8_t cmd);
void Board_HT1621_WriteData4Bit(ht1621_t *p_dev, uint8_t addr, uint8_t data);
void Board_HT1621_WriteData8Bit(ht1621_t *p_dev, uint8_t addr, uint8_t data);

#endif /* _BOARD_HT1621_H_ */

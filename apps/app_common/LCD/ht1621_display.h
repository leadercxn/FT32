#ifndef _HT1621_DISPLAY_H_
#define _HT1621_DISPLAY_H_

/*********************************************************************
 * INCLUDES
 */
#include "ft32f0xx.h"
#include "stdbool.h"

/*********************************************************************
 * DEFINITIONS
 */
#define TEMP_ADDR 0x00
#define FOURTH_8_MHz_ADDR 0x04
#define FOURTH_8_ADDR 0x08
#define THIRD_8_75us_ADDR 0x0C
#define THIRD_8_ADDR 0x10
#define SECOND_8_POINT_ADDR 0x14
#define SECOND_8_ADDR 0x18
#define FIRST_8_50us_ADDR 0x1C
#define FIRST_8_ADDR 0x20
#define FM_SOUND_1_ADDR 0x24
#define SIGNAL_ADDR 0x28

#define DISPLAY_ALARM 0x03
#define DISPLAY_FM 0x04
#define DISPLAY_1_1 0x08
#define DISPLAY_MHZ 0x10

void LCD_ShowFrequency(uint32_t frequency);

#endif /* _HT1621_DISPLAY_H_ */

/**
 * 根据不同的芯片来选择所包含的头文件
 * 
 */
#ifndef __USER_BOARD_H
#define __USER_BOARD_H

/**
 * FT32xx 芯片宏
 */
#define FT32XX

#ifdef FT32XX
#include "ft32f0xx.h"
#include "ft_gpio.h"
#include "ft_i2c.h"
#endif

#endif

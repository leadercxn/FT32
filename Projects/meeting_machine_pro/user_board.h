/**
 * @brief 根据不同的芯片 来 选择所包含的头文件，和宏管理
 * 
 */
#ifndef __USER_BOARD_H
#define __USER_BOARD_H





/**
 * FT32 平台的宏管理 和 头文件选择
 */
#ifdef  FT32
#include "ft32f0xx.h"
#include "ft_gpio.h"
#include "ft_i2c.h"
#endif



#endif

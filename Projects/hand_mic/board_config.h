/**
 * @brief 根据不同的芯片 来 选择所包含的头文件，和宏管理
 * 
 */
#ifndef __BOARD_CONFIG_H
#define __BOARD_CONFIG_H





/**
 * FT32 平台的宏管理 和 头文件选择
 */
#ifdef  FT32
#include "ft32f0xx.h"

/* GPIO */
#define LCD_BACK_LIGHT_PIN              GPIO_Pin_4
#define LCD_BACK_LIGHT_PORT             GPIOB
#define LCD_BACK_LIGHT_PORT_PERIPH_CLK  RCC_AHBPeriph_GPIOB

#define BK9531_CE_PIN                   GPIO_Pin_5
#define BK9531_CE_PORT                  GPIOB
#define BK9531_CE_PERIPH_CLK            RCC_AHBPeriph_GPIOB

/* TIMER */
#define TIM3_CLK                        RCC_APB1Periph_TIM3
#define TIM3_IRQ                        TIM3_IRQn

#define USER_TIMER_CLK                  TIM3_CLK
#define USER_TIMER_IRQ                  TIM3_IRQ
#define USER_TIMER                      TIM3

#define USER_TIMER_CH                   TIM_IT_CC1
#define USER_TIMER_FREQ                 1000000     //定时器经分频后获得的频率
#define USER_TIMER_PERIOD               1000        //定时器溢出计数


/* UART */
#define FT_UART1                        USART1
#define FT_UART1_CLK                    RCC_APB2Periph_USART1

#define FT_UART1_TX_PIN                 GPIO_Pin_9
#define FT_UART1_TX_GPIO_PORT           GPIOA
#define FT_UART1_TX_GPIO_CLK            RCC_AHBPeriph_GPIOA
#define FT_UART1_TX_SOURCE              GPIO_PinSource9
#define FT_UART1_TX_AF                  GPIO_AF_1

#define FT_UART1_RX_PIN                 GPIO_Pin_10
#define FT_UART1_RX_GPIO_PORT           GPIOA
#define FT_UART1_RX_GPIO_CLK            RCC_AHBPeriph_GPIOA
#define FT_UART1_RX_SOURCE              GPIO_PinSource10
#define FT_UART1_RX_AF                  GPIO_AF_1

/* I2C */

#define VIRT1_SCL_PIN                    GPIO_Pin_6                  /* 模拟I2C-SCL */
#define VIRT1_SCL_GPIO_PORT              GPIOB                       /* GPIOB */
#define VIRT1_SCL_GPIO_CLK               RCC_AHBPeriph_GPIOB
#define VIRT1_SDA_PIN                    GPIO_Pin_7                  /* 模拟I2C-SDA */
#define VIRT1_SDA_GPIO_PORT              GPIOB                       /* GPIOB */
#define VIRT1_SDA_GPIO_CLK               RCC_AHBPeriph_GPIOB

/* EXIT */
#define EXIT_GPIO_PORT_CLK              RCC_AHBPeriph_GPIOA
#define EXIT_GPIO_PIN                   GPIO_Pin_8
#define EXIT_GPIO_PORT_RESOURCE         EXTI_PortSourceGPIOA
#define EXIT_GPIO_PIN_RESOURCE          EXTI_PinSource8
#define EXIT_TRIGGER_MODE               EXTI_Trigger_Falling
#define EXIT_GPIO_PORT                  GPIOA
#define EXIT_LINE                       EXTI_Line8


#endif


/* 选择develop_lib库的头文件 */
#include "develop_lib.h"
#include "lib_error.h"
#include "util.h"

#endif

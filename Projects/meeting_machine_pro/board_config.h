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
#define L_BK9532_CE_PIN                 GPIO_Pin_0
#define L_BK9532_CE_PORT                GPIOB
#define L_BK9532_CE_PERIPH_CLK          RCC_AHBPeriph_GPIOB
        
#define R_BK9532_CE_PIN                 GPIO_Pin_8
#define R_BK9532_CE_PORT                GPIOA
#define R_BK9532_CE_PERIPH_CLK          RCC_AHBPeriph_GPIOA

/* ADC */
#define ADC_CHANNEL_0                   ADC_Channel_0
#define ADC_CHANNEL_1                   ADC_Channel_1
#define ADC_CHANNEL_2                   ADC_Channel_2
#define ADC_CHANNEL_3                   ADC_Channel_3

#define ADC_GPIO_PORT_CLK               RCC_AHBPeriph_GPIOA
#define ADC_GPIO_PIN_0                  GPIO_Pin_0
#define ADC_GPIO_PIN_1                  GPIO_Pin_1
#define ADC_GPIO_PORT                   GPIOA

#define ADC_SAMPLETIME_CYCLE            ADC_SampleTime_239_5Cycles
#define ADC_CONTINUOUS_CONV_MODE        DISABLE

/* EXIT */
#define EXIT_GPIO_PORT_CLK              RCC_AHBPeriph_GPIOA
#define EXIT_GPIO_PIN                   GPIO_Pin_8
#define EXIT_GPIO_PORT_RESOURCE         EXTI_PortSourceGPIOA
#define EXIT_GPIO_PIN_RESOURCE          EXTI_PinSource8
#define EXIT_TRIGGER_MODE               EXTI_Trigger_Falling
#define EXIT_GPIO_PORT                  GPIOA
#define EXIT_LINE                       EXTI_Line8

/* TIMER */
#define TIM3_CLK                        RCC_APB1Periph_TIM3
#define TIM3_IRQ                        TIM3_IRQn

#define USER_TIMER_CLK                  TIM3_CLK
#define USER_TIMER_IRQ                  TIM3_IRQ
#define USER_TIMER                      TIM3

#define USER_TIMER_CH                   TIM_IT_CC1
#define USER_TIMER_FREQ                 1000000     //定时器经分频后获得的频率
#define USER_TIMER_PERIOD               1000        //定时器溢出计数

/* I2C */
#define I2C1_TIMING                     0xF0210507	//when =SYSCLK=48MHZ

#define I2C1_CLK                        RCC_APB1Periph_I2C1
    
#define I2C1_SCL_PIN                    GPIO_Pin_6                  /* PB.06 */
#define I2C1_SCL_GPIO_PORT              GPIOB                       /* GPIOB */
#define I2C1_SCL_GPIO_CLK               RCC_AHBPeriph_GPIOB
#define I2C1_SCL_SOURCE                 GPIO_PinSource6
#define I2C1_SCL_AF                     GPIO_AF_1

#define I2C1_SDA_PIN                    GPIO_Pin_7                  /* PB.07 */
#define I2C1_SDA_GPIO_PORT              GPIOB                       /* GPIOB */
#define I2C1_SDA_GPIO_CLK               RCC_AHBPeriph_GPIOB
#define I2C1_SDA_SOURCE                 GPIO_PinSource7
#define I2C1_SDA_AF                     GPIO_AF_1

#define VIRT_SCL_PIN                    GPIO_Pin_12                  /* 模拟I2C-SCL */
#define VIRT_SCL_GPIO_PORT              GPIOA                       /* GPIOA */
#define VIRT_SCL_GPIO_CLK               RCC_AHBPeriph_GPIOA
#define VIRT_SDA_PIN                    GPIO_Pin_11                  /* 模拟I2C-SDA */
#define VIRT_SDA_GPIO_PORT              GPIOA                       /* GPIOA */
#define VIRT_SDA_GPIO_CLK               RCC_AHBPeriph_GPIOA

#define I2C_TRANFS_TIMEOUT              1000

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

/* PWM */
#define PWM_CH1_PIN                     GPIO_Pin_2                  /* PA.02 */
#define PWM_CH1_GPIO_PORT               GPIOA                       /* GPIOA */
#define PWM_CH1_GPIO_CLK                RCC_AHBPeriph_GPIOA
#define PWM_CH1_PIN_SOURCE              GPIO_PinSource2
#define PWM_CH1_AF                      GPIO_AF_0
    
#define PWM_TIM                         TIM15


#endif


/* 选择develop_lib库的头文件 */
#include "develop_lib.h"
#include "lib_error.h"
#include "util.h"

#endif

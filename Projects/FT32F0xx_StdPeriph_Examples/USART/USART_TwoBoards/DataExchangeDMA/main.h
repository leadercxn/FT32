    /**
  ******************************************************************************
  * @file    USART/USART_TwoBoards/DataExchangeDMA/main.h
  * @author  AE
  * @version V1.0.0
  * @date    29-MAR-2021
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2021 FMD</center></h2>
  *
  *
  *        http://www.fremontmicro.com
  *

  *
  ******************************************************************************
  */
  
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "FT32f0xx.h"
#ifdef USE_FT32F030XX_EVAL
  #include "FT32F030XX_eval.h"
#else 
  #include "FT32F072X8_eval.h"
#endif /* USE_FT32F030XX_EVAL */

/* Exported typedef ----------------------------------------------------------*/
#define countof(a)   (sizeof(a) / sizeof(*(a)))
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Exported define -----------------------------------------------------------*/

/* USER_TIMEOUT value for waiting loops. This timeout is just guarantee that the
   application will not remain stuck if the USART communication is corrupted. 
   You may modify this timeout value depending on CPU frequency and application
   conditions (interrupts routines, number of data to transfer, baudrate, CPU
   frequency...). */ 
#define USER_TIMEOUT                    ((uint32_t)0x64000) /* Waiting 1s */

/* Communication boards USART Interface */
#ifdef USE_FT32F030XX_EVAL
  #define USARTx_TDR_ADDRESS                0x40013828
  #define USARTx_RDR_ADDRESS                0x40013824

  #define USARTx_TX_DMA_CHANNEL            DMA1_Channel2
  #define USARTx_TX_DMA_FLAG_TC            DMA1_FLAG_TC2
  #define USARTx_TX_DMA_FLAG_GL            DMA1_FLAG_GL2
  #define USARTx_RX_DMA_CHANNEL            DMA1_Channel3
  #define USARTx_RX_DMA_FLAG_TC            DMA1_FLAG_TC3
  #define USARTx_RX_DMA_FLAG_GL            DMA1_FLAG_GL3
#else 
  #define USARTx_TDR_ADDRESS                0x40004428
  #define USARTx_RDR_ADDRESS                0x40004424

  #define USARTx_TX_DMA_CHANNEL            DMA1_Channel4
  #define USARTx_TX_DMA_FLAG_TC            DMA1_FLAG_TC4
  #define USARTx_TX_DMA_FLAG_GL            DMA1_FLAG_GL4
  #define USARTx_RX_DMA_CHANNEL            DMA1_Channel5
  #define USARTx_RX_DMA_FLAG_TC            DMA1_FLAG_TC5
  #define USARTx_RX_DMA_FLAG_GL            DMA1_FLAG_GL5
#endif /* USE_FT32F030XX_EVAL */

#define DMAx_CLK                         RCC_AHBPeriph_DMA1

/* USART Communication boards Interface */
#ifdef USE_FT32F030XX_EVAL
  #define USARTx                           USART1
  #define USARTx_CLK                       RCC_APB2Periph_USART1
  #define USARTx_APBPERIPHCLOCK            RCC_APB2PeriphClockCmd
  #define USARTx_IRQn                      USART1_IRQn
  #define USARTx_IRQHandler                USART1_IRQHandler

  #define USARTx_TX_PIN                    GPIO_Pin_9
  #define USARTx_TX_GPIO_PORT              GPIOA
  #define USARTx_TX_GPIO_CLK               RCC_AHBPeriph_GPIOA
  #define USARTx_TX_SOURCE                 GPIO_PinSource9
  #define USARTx_TX_AF                     GPIO_AF_1

  #define USARTx_RX_PIN                    GPIO_Pin_10          
  #define USARTx_RX_GPIO_PORT              GPIOA            
  #define USARTx_RX_GPIO_CLK               RCC_AHBPeriph_GPIOA
  #define USARTx_RX_SOURCE                 GPIO_PinSource10
  #define USARTx_RX_AF                     GPIO_AF_1
#else 
  #define USARTx                           USART2
  #define USARTx_CLK                       RCC_APB1Periph_USART2
  #define USARTx_APBPERIPHCLOCK            RCC_APB1PeriphClockCmd
  #define USARTx_IRQn                      USART2_IRQn
  #define USARTx_IRQHandler                USART2_IRQHandler

  #define USARTx_TX_PIN                    GPIO_Pin_2
  #define USARTx_TX_GPIO_PORT              GPIOA
  #define USARTx_TX_GPIO_CLK               RCC_AHBPeriph_GPIOA
  #define USARTx_TX_SOURCE                 GPIO_PinSource2
  #define USARTx_TX_AF                     GPIO_AF_1

  #define USARTx_RX_PIN                    GPIO_Pin_2          
  #define USARTx_RX_GPIO_PORT              GPIOA              
  #define USARTx_RX_GPIO_CLK               RCC_AHBPeriph_GPIOA
  #define USARTx_RX_SOURCE                 GPIO_PinSource2
  #define USARTx_RX_AF                     GPIO_AF_1
#endif /* USE_FT32F030XX_EVAL */

#define TXBUFFERSIZE                     (countof(TxBuffer) - 1)
#define RXBUFFERSIZE                     TXBUFFERSIZE

/* Joystick Commands */
#define CMD_RIGHT                        0x55
#define CMD_LEFT                         0xAA
#define CMD_UP                           0x33
#define CMD_DOWN                         0xCC
#define CMD_SEL                          0xFF 

#define CMD_ACK                          0x66 

/* Define numbers of bytes to transmit from TxBuffer */
#define CMD_RIGHT_SIZE                   0x01
#define CMD_LEFT_SIZE                    0x05
#define CMD_UP_SIZE                      0x14
#define CMD_DOWN_SIZE                    0x1E
#define CMD_SEL_SIZE                     TXBUFFERSIZE

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


#endif /* __MAIN_H */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/

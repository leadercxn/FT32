/**
  ******************************************************************************
  * @file    SPI/SPI_TwoBoards/DataExchangeInterrupt/main.h 
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

/* Uncomment the line below if you will use the SPI peripheral as a Master */
#define SPI_MASTER 
/* Uncomment the line below if you will use the SPI peripheral as a Slave */
//#define SPI_SLAVE

/* Uncomment the size of data to be transmetted (only one data size must be selected) */
#define SPI_DATASIZE_8
//#define SPI_DATASIZE_7
//#define SPI_DATASIZE_6
//#define SPI_DATASIZE_5


/* USE//R_TIMEOUT value for waiting loops. This timeout is just guarantee that the
   application will not remain stuck if the USART communication is corrupted. 
   You may modify this timeout value depending on CPU frequency and application
   conditions (interrupts routines, number of data to transfer, baudrate, CPU
   frequency...). */ 
#define USER_TIMEOUT                    ((uint32_t)0x64) /* Waiting 1s */

/* Communication boards SPIx Interface */
#define SPIx                             SPI1
#define SPIx_CLK                         RCC_APB2Periph_SPI1
#define SPIx_IRQn                        SPI1_IRQn
#define SPIx_IRQHandler                  SPI1_IRQHandler

#ifdef USE_FT32F030XX_EVAL
  #define SPIx_SCK_PIN                     GPIO_Pin_5
  #define SPIx_SCK_GPIO_PORT               GPIOA
  #define SPIx_SCK_GPIO_CLK                RCC_AHBPeriph_GPIOA
  #define SPIx_SCK_SOURCE                  GPIO_PinSource5
  #define SPIx_SCK_AF                      GPIO_AF_0

  #define SPIx_MISO_PIN                    GPIO_Pin_4
  #define SPIx_MISO_GPIO_PORT              GPIOB
  #define SPIx_MISO_GPIO_CLK               RCC_AHBPeriph_GPIOB
  #define SPIx_MISO_SOURCE                 GPIO_PinSource4
  #define SPIx_MISO_AF                     GPIO_AF_0

  #define SPIx_MOSI_PIN                    GPIO_Pin_7
  #define SPIx_MOSI_GPIO_PORT              GPIOA
  #define SPIx_MOSI_GPIO_CLK               RCC_AHBPeriph_GPIOA
  #define SPIx_MOSI_SOURCE                 GPIO_PinSource7
  #define SPIx_MOSI_AF                     GPIO_AF_0
#else 
  #define SPIx_SCK_PIN                     GPIO_Pin_3                  /* PB.03 */
  #define SPIx_SCK_GPIO_PORT               GPIOB                       /* GPIOB */
  #define SPIx_SCK_GPIO_CLK                RCC_AHBPeriph_GPIOB
  #define SPIx_SCK_SOURCE                  GPIO_PinSource3
  #define SPIx_SCK_AF                      GPIO_AF_0

  #define SPIx_MISO_PIN                    GPIO_Pin_14                  /* PE.14 */
  #define SPIx_MISO_GPIO_PORT              GPIOE                       /* GPIOE */
  #define SPIx_MISO_GPIO_CLK               RCC_AHBPeriph_GPIOE
  #define SPIx_MISO_SOURCE                 GPIO_PinSource14
  #define SPIx_MISO_AF                     GPIO_AF_1

  #define SPIx_MOSI_PIN                    GPIO_Pin_15                  /* PE.15 */
  #define SPIx_MOSI_GPIO_PORT              GPIOE                       /* GPIOE */
  #define SPIx_MOSI_GPIO_CLK               RCC_AHBPeriph_GPIOE
  #define SPIx_MOSI_SOURCE                 GPIO_PinSource15
  #define SPIx_MOSI_AF                     GPIO_AF_1
#endif /* USE_FT32F030XX_EVAL */

#define TXBUFFERSIZE                     (countof(TxBuffer) - 1)
#define RXBUFFERSIZE                     TXBUFFERSIZE

/* Joystick Commands */
#define CMD_RIGHT                        0x15
#define CMD_LEFT                         0x1A
#define CMD_UP                           0x13
#define CMD_DOWN                         0x1C
#define CMD_SEL                          0x1F 

#define CMD_ACK                          0x16 

/* Define numbers of bytes to transmit from TxBuffer */
#define DATA_SIZE                        TXBUFFERSIZE

/* Define data size and data masks */
#ifdef SPI_DATASIZE_8
 #define SPI_DATASIZE                     SPI_DataSize_8b
 #define SPI_DATAMASK                     (uint8_t)0xFF
#elif defined (SPI_DATASIZE_7)
 #define SPI_DATASIZE                     SPI_DataSize_7b
 #define SPI_DATAMASK                     (uint8_t)0x7F
#elif defined (SPI_DATASIZE_6)
 #define SPI_DATASIZE                     SPI_DataSize_6b
 #define SPI_DATAMASK                     (uint8_t)0x3F
#elif defined (SPI_DATASIZE_5)
 #define SPI_DATASIZE                     SPI_DataSize_5b
 #define SPI_DATAMASK                     (uint8_t)0x1F
#else
 #error " Select at least one data size in main.h file " 
#endif

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
uint8_t GetVar_NbrOfData(void);

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/

    /**
  ******************************************************************************
  * @file    USART/USART_HyperTerminalInterrupt/FT32F0xx_it.h
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
#ifndef __FT32F0XX_it_H
#define __FT32F0XX_it_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "FT32f0xx.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void NMI_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
#ifdef USE_FT32F030XX_EVAL
void USART1_IRQHandler(void);
#else 
void USART2_IRQHandler(void); 
#endif /* USE_FT32F030XX_EVAL */

#ifdef __cplusplus
}
#endif

#endif /* __FT32F030X8_it_H */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/

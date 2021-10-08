  /**
  ******************************************************************************
  * @file    IWDG/IWDG_Reset/FT32F0xx_it.h
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
#include "main.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void NMI_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
#ifdef LSI_TIM_MEASURE
 void TIM14_IRQHandler(void);
#endif /* LSI_TIM_MEASURE */
void EXTI4_15_IRQHandler(void);


#ifdef __cplusplus
}
#endif

#endif /* __FT32F030X8_it_H */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/

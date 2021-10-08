  /**
  ******************************************************************************
  * @file    EXTI\EXTI_Example/ft32f0XX_it.h 
  * @author  AE
  * @version V1.0.0
  * @date    29-MAR-2021
  * @brief   Header for main.c module
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
#ifndef __FT32F0XX_IT_H
#define __FT32F0XX_IT_H

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
void EXTI4_15_IRQHandler(void);
void EXTI0_1_IRQHandler(void);
#ifdef USE_FT32F072X8_EVAL 
void EXTI2_3_IRQHandler(void);
#endif

/*void PPP_IRQHandler(void);*/

#ifdef __cplusplus
}
#endif

#endif /* __FT32F0XX_IT_H */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/

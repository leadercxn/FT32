/**
  ******************************************************************************
  * @file    Project/FT32F0XX_StdPeriph_Templates/ft32f0xx_it.h 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    2021-03-29
  * @brief   This file contains the headers of the interrupt handlers.
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F0XX_IT_H
#define __FT32F0XX_IT_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "FT32f0xx.h"
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

    /*void PPP_IRQHandler(void);*/

#ifdef USE_FT32F030XX_EVAL
    void USART1_IRQHandler(void);
#else
void USART2_IRQHandler(void);
#endif /* USE_FT32F030XX_EVAL */

#ifdef __cplusplus
}
#endif

#endif /* __FT32F0XX_IT_H */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/

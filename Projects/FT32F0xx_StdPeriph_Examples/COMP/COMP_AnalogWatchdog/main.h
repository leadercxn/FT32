  /**
  ******************************************************************************
  * @file    COMP/COMP_AnalogWatchdog/main.h 
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


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define STATE_OVER_THRESHOLD    0x00000001
#define STATE_WITHIN_THRESHOLD  0x00000002
#define STATE_UNDER_THRESHOLD   0x00000003

/* Exported functions ------------------------------------------------------- */
void CheckState(void);

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/

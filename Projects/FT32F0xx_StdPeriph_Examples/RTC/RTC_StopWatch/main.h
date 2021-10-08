  /**
  ******************************************************************************
  * @file    RTC/RTC_StopWatch/main.h 
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
  #include "FT32F030XX_eval_lcd.h"
#else 
  #include "FT32F072X8_eval.h" 
  #include "FT32F072X8_eval_lcd.h"
#endif /* USE_FT32F030XX_EVAL */
#include <stdio.h>

/* Exported types ------------------------------------------------------------*/
typedef struct {
  uint8_t tab[12];
} Table_TypeDef;
/* Private define ------------------------------------------------------------*/
#define RTC_TAMP    1
#define LEFT_ON     2
#define RIGHT_ON    3
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void RTC_Time_InitDisplay(void);
void RTC_Time_Display(uint8_t Line, __IO uint16_t Colorx, Table_TypeDef timetable);
Table_TypeDef RTC_Get_Time(uint32_t SecondFrac , RTC_TimeTypeDef* RTC_TimeStructure);

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/

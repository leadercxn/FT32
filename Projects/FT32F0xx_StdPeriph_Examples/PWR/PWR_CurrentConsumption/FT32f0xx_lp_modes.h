   /**
  ******************************************************************************
  * @file    PWR/PWR_CurrentConsumption/FT32f0xx_lp_modes.h
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
#ifndef __FT32f0xx_LP_MODES_H
#define __FT32f0xx_LP_MODES_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#if !defined (SLEEP_MODE) && !defined (STOP_MODE) && !defined (STANDBY_MODE)\
 && !defined (STANDBY_RTC_MODE) 
/* Uncomment the corresponding line to select the FT32f0xx Low Power mode */
//#define SLEEP_MODE
//#define STOP_MODE
//#define STANDBY_MODE
#define STANDBY_RTC_MODE
#endif

#if !defined (SLEEP_MODE) && !defined (STOP_MODE) && !defined (STANDBY_MODE)\
 && !defined (STANDBY_RTC_MODE)
 #error "Please select first the target FT32f0xx Low Power mode to be measured (in FT32f0xx_lp_modes.h file)"
#endif

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void SleepMode_Measure(void);
void StopMode_Measure(void);
void StandbyMode_Measure(void);
void StandbyRTCMode_Measure(void);

#endif /* __FT32f0xx_LP_MODES_H */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/

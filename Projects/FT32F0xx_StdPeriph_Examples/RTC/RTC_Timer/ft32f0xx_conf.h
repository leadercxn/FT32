/**
  ******************************************************************************
  * @file    Project/FT32F030X8_StdPeriph_Templates/FT32f0xx_conf.h 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    2020-06-22
  * @brief   Library configuration file.
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F030X8_CONF_H
#define __FT32F030X8_CONF_H

/* Includes ------------------------------------------------------------------*/
/* Comment the line below to disable peripheral header file inclusion */
#include "FT32f0xx_adc.h"
#include "FT32f0xx_crc.h"
#include "FT32f0xx_crs.h"
#include "FT32f0xx_comp.h"
#include "FT32f0xx_opa.h"
#include "FT32f0xx_dac.h"
#include "FT32f0xx_dbgmcu.h"
#include "FT32f0xx_dma.h"
#include "FT32f0xx_exti.h"
#include "FT32f0xx_flash.h"
#include "FT32f0xx_gpio.h"
#include "FT32f0xx_syscfg.h"
#include "FT32f0xx_i2c.h"
#include "FT32f0xx_iwdg.h"
#include "FT32f0xx_pwr.h"
#include "FT32f0xx_rcc.h"
#include "FT32f0xx_rtc.h"
#include "FT32f0xx_spi.h"
#include "FT32f0xx_tim.h"
#include "FT32f0xx_usart.h"
#include "FT32f0xx_wwdg.h"
#include "FT32f0xx_misc.h"  /* High level functions for NVIC and SysTick (add-on to CMSIS functions) */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Uncomment the line below to expanse the "assert_param" macro in the 
   Standard Peripheral Library drivers code */
/* #define USE_FULL_ASSERT    1 */

/* Exported macro ------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT

/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function which reports 
  *         the name of the source file and the source line number of the call 
  *         that failed. If expr is true, it returns no value.
  * @retval None
  */
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */

#endif /* __FT32F030X8_CONF_H */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/

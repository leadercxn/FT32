    /**
  ******************************************************************************
  * @file    FT32f0xx_ip_dbg.h 
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
#ifndef __FT32f0xx_IP_DBG_H
#define __FT32f0xx_IP_DBG_H

/* Includes ------------------------------------------------------------------*/
#include "FT32f0xx.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

extern TIM_TypeDef * TIM1_DBG;

void IP_Debug(void);
 
#endif /* __FT32f0xx_IP_DBG_H */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/

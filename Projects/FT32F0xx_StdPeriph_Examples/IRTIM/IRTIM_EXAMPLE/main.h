    /**
  ******************************************************************************
  * @file    IRTIM/IRTIM_EXAMPLE/main.h
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

typedef union
{
  uint32_t senddat;
  struct 
  {
    uint16_t id :16;
    uint8_t data1:8;
    uint8_t data2:8;
  }b;
}IR_SENDDATA_STRU;

#define C_ENVELOPE_PRESC	512

extern uint16_t TimerPeriod_env;
extern uint16_t Channel1Pulse_env;

#define C_IR_STATE_OFF	0
#define C_IR_STATE_HEAD	 1
#define C_IR_STATE_DATA 2
#define C_IR_STATE_FINISH 9
extern uint8_t ir_state;

extern uint8_t bitcnt;
extern IR_SENDDATA_STRU irdatas;

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */


uint16_t SET_PERIOD(uint16_t freq,uint16_t pre);
uint16_t SET_PULSE(uint8_t duty,uint16_t peri);

void Set_Ir_State(uint8_t sta);



#endif /* __MAIN_H */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/

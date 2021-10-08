      /**
  ******************************************************************************
  * @file    IRTIM/IRTIM_EXAMPLE/FT32F0xx_it.c
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

/* Includes ------------------------------------------------------------------*/
#include "FT32F0xx_it.h"

/** @addtogroup FT32f0xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup TIM_7PWMOutputs
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}



/**
  * @brief  This function handles TIM6_IRQ Handler.
  * @param  None
  * @retval None
  */
void TIM16_IRQHandler(void)
{
	//
	if(	(TIM_GetITStatus(TIM16, TIM_IT_Update) != RESET)

	){
		TIM_ClearITPendingBit(TIM16, TIM_IT_Update);

		//
		if(C_IR_STATE_HEAD==ir_state){
			Set_Ir_State(C_IR_STATE_DATA);
			bitcnt=32;
		}

		if(C_IR_STATE_DATA==ir_state){
			if(0==bitcnt){
				TIM_CtrlPWMOutputs(TIM16, DISABLE);
				TIM_Cmd(TIM16, DISABLE);
				Set_Ir_State(C_IR_STATE_FINISH);
			}
			else{
				if(irdatas.senddat&0x01){
					TimerPeriod_env=SET_PERIOD(446,C_ENVELOPE_PRESC);		// 1.68MS+0.56MS
					Channel1Pulse_env=SET_PULSE(25,TimerPeriod_env); 
				}
				else{
					
					TimerPeriod_env=SET_PERIOD(893,C_ENVELOPE_PRESC);		//0.56MS+0.56MS
					Channel1Pulse_env=SET_PULSE(50,TimerPeriod_env); 
				}
				TIM_SetAutoreload(TIM16,TimerPeriod_env);
				TIM_SetCompare1(TIM16,Channel1Pulse_env);
				irdatas.senddat=irdatas.senddat>>1;
				bitcnt--;
			}
		}
		
	}

	
}



/******************************************************************************/
/*                 FT32f0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_FT32f0xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/

    /**
  ******************************************************************************
  * @file    IRTIM/IRTIM_EXAMPLE/main.c  
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
#include "main.h"

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
uint16_t TimerPeriod_carr = 0;
uint16_t Channel1Pulse_carr = 0;
uint16_t TimerPeriod_env = 0;
uint16_t Channel1Pulse_env = 0;

uint8_t ir_state;
uint8_t bitcnt;
IR_SENDDATA_STRU irdatas;

/* Private function prototypes -----------------------------------------------*/
static void TIM_Config_Carrier(void);
static void TIM_Config_Envelope(void);
void Time_Envelope_inter(void);



/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
/* NEC upd6121常用电视机遥控器
 * 引导码:  载波发射9MS(carrier send), 不发射4.5ms(carrier not send)
 * 0:  0.56ms(carrier send)/0.56ms(carrier not send)
 * 1:  0.56ms(carrier send)/1.68ms(carrier not send)
 * 2:  carrier freq is 38khz
*/
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_FT32f0xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_FT32f0xx.c file
     */ 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
  SYSCFG_IRDAEnvSelection(SYSCFG_IRDA_ENV_SEL_TIM16);

  //
  FT_EVAL_PBInit(BUTTON_TAMPER,BUTTON_MODE_GPIO);


  /* TIM17 Configuration    载波 */
  TIM_Config_Carrier();
  /* TIM16 Configuration    包络波形*/
  TIM_Config_Envelope();
  //
  Time_Envelope_inter();

  //
  Set_Ir_State(C_IR_STATE_OFF);
  
  /* Infinite loop */
  while (1)
  {
	if(FT_EVAL_PBGetState(BUTTON_TAMPER) == RESET){
		if(C_IR_STATE_OFF==ir_state){
			Set_Ir_State(C_IR_STATE_HEAD);
			irdatas.b.id=0x5a6E;
			irdatas.b.data1='F';
			irdatas.b.data2=~irdatas.b.data1;
			//
			TimerPeriod_env=SET_PERIOD(74,C_ENVELOPE_PRESC);		//9MS+4.5MS
			Channel1Pulse_env=SET_PULSE(66,TimerPeriod_env); //9/(9+4.5)*100=66
			TIM_SetAutoreload(TIM16,TimerPeriod_env);
			TIM_SetCompare1(TIM16,Channel1Pulse_env);
			//
			TIM_Cmd(TIM16, ENABLE);
			TIM_CtrlPWMOutputs(TIM16, ENABLE);
		}
	}
	else{
		if(C_IR_STATE_FINISH==ir_state){
			Set_Ir_State(C_IR_STATE_OFF);
			TIM_Cmd(TIM16, DISABLE);
			TIM_CtrlPWMOutputs(TIM16, DISABLE);
		}
	}

  }
}




uint16_t SET_PERIOD(uint16_t freq,uint16_t pre)
{
	uint16_t tmp;
	
	tmp = (SystemCoreClock /pre/ freq ) - 1;

	return tmp;

}

uint16_t SET_PULSE(uint8_t duty,uint16_t peri)
{
	uint16_t tmp;

	tmp = (uint16_t) (((uint32_t) duty * (peri - 1)) / 100);

	return tmp;
}



/**
  * @brief  Configure the TIM17 Pins.
  * @param  None
  * @retval None
  */
static void TIM_Config_Carrier(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  /* GPIOB and GPIOE Clocks enable */
  RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOB, ENABLE);
  
  /* GPIOB Configuration: PB9 as alternate function push-pull ,   PB9 as IR-OUT*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_0);	// AS  IR-OUT
//  GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_2);	// AS  TIM17-CH1 OUTPUT
  
  /* TIM1 Configuration ---------------------------------------------------
   Generate 1 PWM signals with 50% duty cycles:
   TIM17 input clock (TIM17CLK) is set to APB2 clock (PCLK2)    
    => TIM17CLK = PCLK2 = SystemCoreClock
   TIM17CLK = SystemCoreClock, Prescaler = 0, TIM17 counter clock = SystemCoreClock
   SystemCoreClock is set to 48 MHz for FT32f0xx devices
   
   The objective is to generate 1 PWM signal at 38 KHz:
     - TIM17_Period = (SystemCoreClock / 38000) - 1
   The channel 1 and channel 1N duty cycle is set to 50%
   The Timer pulse is calculated as follows:
     - ChannelxPulse = DutyCycle * (TIM1_Period - 1) / 100
   
   Note: 
    SystemCoreClock variable holds HCLK frequency and is defined in system_FT32f0xx.c file.
    Each time the core clock (HCLK) changes, user had to call SystemCoreClockUpdate()
    function to update SystemCoreClock variable value. Otherwise, any configuration
    based on this variable will be incorrect. 
  ----------------------------------------------------------------------- */
  /* Compute the value to be set in ARR regiter to generate signal frequency at 38 Khz */
  TimerPeriod_carr=SET_PERIOD(38000,1);
  /* Compute CCR1 value to generate a duty cycle at 50% for channel 1 and 1N */
  Channel1Pulse_carr=SET_PULSE(50,TimerPeriod_carr);

  /* TIM17 clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM17 , ENABLE);
  
  /* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = TimerPeriod_carr;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  //
  TIM_TimeBaseInit(TIM17, &TIM_TimeBaseStructure);

  /* Channel 1 Configuration in PWM mode */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
  TIM_OCInitStructure.TIM_Pulse = Channel1Pulse_carr;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;//TIM_OCIdleState_Reset;//TIM_OCIdleState_Set;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

  TIM_OC1Init(TIM17, &TIM_OCInitStructure);

  /* TIM17 counter enable */
  TIM_Cmd(TIM17, ENABLE);

  /* TIM17 Main Output Enable */
  TIM_CtrlPWMOutputs(TIM17, ENABLE);
}


/**
  * @brief  Configure the TIM16 Pins.
  * @param  None
  * @retval None
  */
static void TIM_Config_Envelope(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
//  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_BDTRInitTypeDef TIM_BDTRInitStruct;

  /* GPIOB and GPIOE Clocks enable */
  RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOB, ENABLE);
  
  /* GPIOB Configuration: PB8 as alternate function push-pull ,   PB8 as envelope wave*/
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
//  GPIO_Init(GPIOB, &GPIO_InitStructure);
  //
//  GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_2);	// AS  TIM16-CH1 OUTPUT
  
  /* TIM1 Configuration ---------------------------------------------------
   Generate 1 PWM signals with xx% duty cycles:
   TIM16 input clock (TIM16CLK) is set to APB2 clock (PCLK2)    
    => TIM16CLK = PCLK2 = SystemCoreClock
   TIM16CLK = SystemCoreClock, Prescaler = 0, TIM16 counter clock = SystemCoreClock
   SystemCoreClock is set to 48 MHz for FT32f0xx devices

   prescaler is C_ENVELOPE_PRESC  (512)
  ----------------------------------------------------------------------- */
  /* Compute the value to be set in ARR regiter to generate signal frequency at xx Khz */
  TimerPeriod_env=SET_PERIOD(1000,C_ENVELOPE_PRESC);
  /* Compute CCR1 value to generate a duty cycle at 50% for channel 1 and 1N */
  Channel1Pulse_env=SET_PULSE(50,TimerPeriod_env);

  /* TIM16 clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM16 , ENABLE);
  
  /* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = C_ENVELOPE_PRESC;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = TimerPeriod_env;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  //
  TIM_TimeBaseInit(TIM16, &TIM_TimeBaseStructure);

  /* Channel 1 Configuration in PWM mode */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
  TIM_OCInitStructure.TIM_Pulse = Channel1Pulse_env;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Set;

  TIM_OC1Init(TIM16, &TIM_OCInitStructure);

  //
  TIM_BDTRStructInit(&TIM_BDTRInitStruct);
  TIM_BDTRInitStruct.TIM_OSSIState=TIM_OSSIState_Enable;
  TIM_BDTRInitStruct.TIM_OSSRState=TIM_OSSRState_Enable;
  TIM_BDTRConfig(TIM16,&TIM_BDTRInitStruct);

  /* TIM16 counter enable */
 // TIM_Cmd(TIM16, ENABLE);

  /* TIM16 Main Output Enable */
//  TIM_CtrlPWMOutputs(TIM16, ENABLE);
}



//
void Time_Envelope_inter(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* Enable the TIM3 gloabal Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM16_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	//
	TIM_ClearITPendingBit(TIM16, TIM_IT_Update);
	/* TIM Interrupts enable */
	TIM_ITConfig(TIM16, TIM_IT_Update, ENABLE);


}


//
void Set_Ir_State(uint8_t sta)
{
	ir_state=sta;
}




#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/

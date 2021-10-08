/**
  ******************************************************************************
  * @file    COMP/COMP_PulseWidthMeasurement/main.c
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

/** @addtogroup COMP_PulseWidthMeasurement
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint32_t Capture = 0;
__IO uint32_t MeasuredPulse = 0;
__IO uint32_t DisplayActive = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void DAC_Config(void);
static void COMP_Config(void);
static void TIM_Config(void);
static void DisplayOnLCD(uint32_t data);

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_FT32f0xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_FT32f0xx.c file
     */ 

    /* Initialize the TFT-LCD */
#ifdef USE_FT32F030XX_EVAL
    FT32F030XX_LCD_Init();
#else 
    FT32F072X8_LCD_Init();
#endif /* USE_FT32F030XX_EVAL */
    
    /* Clear the TFT-LCD */
    LCD_Clear(LCD_COLOR_WHITE);
      
    /* DAC Channel1 configuration */
    DAC_Config();
    
    /* COMP1 Configuration */
    COMP_Config();
    
    /* TIM2 Configuration in input capture mode */
    TIM_Config();
   

  /* Infinite loop */
  while (1)
  {
    if (DisplayActive != 0)
    {
      /* Compute the pulse width in us */
      MeasuredPulse = (uint32_t)(((uint64_t) Capture * 1000000) / ((uint32_t)SystemCoreClock));
      
      /* Display measured pulse width on Glass LCD and color LCD */
      DisplayOnLCD(MeasuredPulse);  
      DisplayActive = 0;
    }
  }
}

/**
  * @brief  Configures the DAC channel 1 with output buffer enabled.
  * @param  None
  * @retval None
  */
static void DAC_Config(void)
{

   /* Enable SYSCFG clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
   
  DAC_Ref_Config(DAC_CTRL_REF_SEL_1);				// 3V
  DAC_SetChannel1Data(0,50);

  /* Enable DAC*/
  DAC_Cmd( ENABLE);
}


/**
  * @brief  Configures COMP1: DAC channel 1 to COMP1 inverting input
  *                           and COMP1 output to TIM2 IC4.
  * @param  None
  * @retval None
  */
static void COMP_Config(void)
{

  /* Init Structure definition */
  COMP_InitTypeDef COMP_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  /* GPIOA Peripheral clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  /* Configure PA1: PA1 is used as COMP1 non inveting input */
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* COMP Peripheral clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

  /* COMP1 Init: DAC1 output is used COMP1 inverting input */
  COMP_StructInit(&COMP_InitStructure);
  COMP_InitStructure.COMP_VinSel = NCOMP_VIN_SEL_DAC1_OUT;
  /* Redirect COMP1 output to TIM2 Input capture 4 */
  COMP_InitStructure.COMP_OutputSel= NCOMP_OUTPUT_SEL_TIM3_CAPTURE1;
  COMP_Init(NCOMP_Selection_COMP, &COMP_InitStructure);

  /* Enable COMP1 */
  COMP_Cmd(NCOMP_Selection_COMP, ENABLE);
}

/**
  * @brief  Configures TIM3 channel 1 in input capture mode
  * @param  None
  * @retval None
  */
static void TIM_Config(void)
{

  /* Init Structure definition */
  TIM_ICInitTypeDef TIM_ICInitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  /* TIM3 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  
  /* TIM3 Time base configuration */
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = 65535;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
  TIM_ClearFlag(TIM3, TIM_FLAG_Update);
  
  /* TIM3 Channel1 Input capture Mode configuration */
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
  /* TIM3 counter is captured at each transition detection: rising or falling edges (both edges) */
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_BothEdge;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0;
  TIM_ICInit(TIM3, &TIM_ICInitStructure);
  
  /* TIM3 IRQChannel enable */  
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* Enable capture interrupt */
  TIM_ITConfig(TIM3, TIM_IT_CC1, ENABLE);
  
  /* Enable the TIM3 counter */
  TIM_Cmd(TIM3, ENABLE);
  
  /* Reset the flags */
  TIM3->SR = 0;
}

/**
  * @brief  Display measured pulse width on color LCD
  * @param  None
  * @retval None
  */
static void DisplayOnLCD(uint32_t value)
{
  uint8_t text[50];
  sprintf((char*)text,"PulseWidth = %d us  ",value);
  LCD_DisplayStringLine(LINE(5),text);
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

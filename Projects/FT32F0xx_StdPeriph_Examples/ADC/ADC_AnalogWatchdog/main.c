/**
  ******************************************************************************
  * @file    ADC/ADC_AnalogWatchdog/main.c
  * @author  AE
  * @version V1.0.0
  * @date    10-MAR-2021
  * @brief   Header for main.c module
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

/** @addtogroup FT32F0xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup ADC_AnalogWatchdog
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define MESSAGE1   "FT32F0xx CortexM0  " 
#ifdef USE_FT32F030XX_EVAL
  #define MESSAGE2   "   FT32F030XX-EVAL   "
  #define MESSAGE3   "  Turn RV3(PC.01)    "
#elif defined (USE_FT32F072X8_EVAL) 
  #define MESSAGE2   "   FT32F072X8-EVAL   " 
  #define MESSAGE3   "  Turn RV3(PC.00)    "
#endif /* USE_FT32F030XX_EVAL */
#define MESSAGE4   "   Potentiometer     "

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint32_t  ADC1ConvertedValue = 0, ADC1ConvertedVoltage = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void Display_Init(void);
static void Display(void);
static void ADC_Config(void);

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
  
  /* LCD Display init  */
  Display_Init();
  
  /* Initialize LED4 */
  FT_EVAL_LEDInit(LED4);
  
  /* Configure ADC channel 11 */
  ADC_Config();
  
  /* Infinite loop */
  while (1)
  {   
    /* Get ADC1 converted data */
    ADC1ConvertedValue =ADC_GetConversionValue(ADC1);
    
    /* Compute the voltage */
    ADC1ConvertedVoltage = (ADC1ConvertedValue *3300)/0xFFF;
    
    
    /* Display converted data on the LCD */
    Display();
  }
}

/**
  * @brief  ADC1 channel configuration
  * @param  None
  * @retval None
  */
static void ADC_Config(void)
{
  ADC_InitTypeDef     ADC_InitStructure;
  GPIO_InitTypeDef    GPIO_InitStructure;
  NVIC_InitTypeDef    NVIC_InitStructure;
    
  /* GPIOC Periph clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
  
  /* ADC1 Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  
  /* Configure ADC Channel11 as analog input */
#ifdef USE_FT32F030XX_EVAL
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ;
#elif defined (USE_FT32F072X8_EVAL)
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
#endif /* USE_FT32F030XX_EVAL */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  
  /* ADC1 DeInit */  
  ADC_DeInit(ADC1);
  
  /* Initialize ADC structure */
  ADC_StructInit(&ADC_InitStructure);
  
  /* Configure the ADC1 in continuous mode withe a resolution equal to 12 bits  */
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
  ADC_Init(ADC1, &ADC_InitStructure);
  
  /* Convert the ADC1 Channel11 and channel10 with 239.5 Cycles as sampling time */ 
#ifdef USE_FT32F030XX_EVAL
  ADC_ChannelConfig(ADC1, ADC_Channel_11 , ADC_SampleTime_239_5Cycles);
#elif defined (USE_FT32F072X8_EVAL)
  ADC_ChannelConfig(ADC1, ADC_Channel_10 , ADC_SampleTime_239_5Cycles);
#endif /* USE_FT32F030XX_EVAL */
  
  /* Analog watchdog config ******************************************/
  /* Configure the ADC Thresholds between 1.5V and 2.5V (1861, 3102) */
  ADC_AnalogWatchdogThresholdsConfig(ADC1, 3102, 1861);

  /* Enable the ADC1 single channel  */
  ADC_AnalogWatchdogSingleChannelCmd(ADC1, ENABLE);
  
  ADC_OverrunModeCmd(ADC1, ENABLE);
  /* Enable the ADC1 analog watchdog */
  ADC_AnalogWatchdogCmd(ADC1,ENABLE);
  
      /* Select a single ADC1 channel 11 */
#ifdef USE_FT32F030XX_EVAL
  ADC_AnalogWatchdogSingleChannelConfig(ADC1, ADC_AnalogWatchdog_Channel_11);
#elif defined (USE_FT32F072X8_EVAL)
  ADC_AnalogWatchdogSingleChannelConfig(ADC1, ADC_AnalogWatchdog_Channel_10);
#endif /* USE_FT32F030XX_EVAL */
   
  /* Enable AWD interrupt */
  ADC_ITConfig(ADC1, ADC_IT_AWD, ENABLE);
  
  /* Configure and enable ADC1 interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = ADC1_COMP_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* Enable the ADC1 Calibration */
  ADC_GetCalibrationFactor(ADC1);
  
  /* Enable the ADC peripheral */
  ADC_Cmd(ADC1, ENABLE);     
  
  /* Wait the ADRDY flag */
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADRDY)); 
  
  /* ADC1 regular Software Start Conv */ 
  ADC_StartOfConversion(ADC1);
}

/**
  * @brief  Display ADC converted value on LCD
  * @param  None
  * @retval None
  */
static void Display(void)
{
  uint32_t v=0,mv=0;
  uint8_t text[50];

  /* Set the LCD Back Color and Text Color*/
  LCD_SetBackColor(White);
  if ((ADC1ConvertedVoltage > 2500) || (ADC1ConvertedVoltage < 1500))
  {
     LCD_SetTextColor(Red);
  }
  else
  {
     LCD_SetTextColor(Blue);
  }
 
  v=(ADC1ConvertedVoltage)/1000;
  
  mv = (ADC1ConvertedVoltage%1000)/100;
  
  sprintf((char*)text,"  V(RV3) = %d,%d V    ",v,mv);
  LCD_DisplayStringLine(LINE(8),text);
}

/**
  * @brief  Display Init (LCD)
  * @param  None
  * @retval None
  */
static void Display_Init(void)
{
  /* Initialize the LCD */
#ifdef USE_FT32F030XX_EVAL
  FT32F030XX_LCD_Init();
#elif defined (USE_FT32F072X8_EVAL)
  FT32F072X8_LCD_Init();
#endif /* USE_FT32F030XX_EVAL */

  /* Clear the LCD */ 
  LCD_Clear(White);

  /* Set the LCD Text size */
  LCD_SetFont(&Font8x12);

  /* Set the LCD Back Color and Text Color*/
  LCD_SetBackColor(Blue);
  LCD_SetTextColor(White);

  /* Display */
  LCD_DisplayStringLine(LINE(0x13), "       ADC Analog Watchdog example      ");

  /* Set the LCD Text size */
  LCD_SetFont(&Font16x24);

  LCD_DisplayStringLine(LINE(0), MESSAGE1);
  LCD_DisplayStringLine(LINE(1), MESSAGE2);
  
  /* Set the LCD Back Color and Text Color*/
  LCD_SetBackColor(White);
  LCD_SetTextColor(Blue);

  /* Display */
  LCD_DisplayStringLine(LINE(3), MESSAGE3);
  LCD_DisplayStringLine(LINE(4), MESSAGE4);
  
    /* Set the LCD Text size */
  LCD_SetFont(&Font12x12);
  LCD_SetTextColor(Green);
  
  LCD_DisplayStringLine(LINE(12),"AWD High threshold = 2.5 V");
  LCD_DisplayStringLine(LINE(13),"AWD Low threshold  = 1.5 V");
  
  /* Set the LCD Text size */
  LCD_SetFont(&Font16x24); 
  LCD_SetTextColor(Blue);
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





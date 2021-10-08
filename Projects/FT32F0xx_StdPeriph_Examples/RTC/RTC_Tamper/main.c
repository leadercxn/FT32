/**
  ******************************************************************************
  * @file    RTC/RTC_Tamper/main.c 
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

/** @addtogroup RTC_Tamper
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Uncomment the corresponding line to select the RTC Clock source */
//#define RTC_CLOCK_SOURCE_LSE   /* LSE used as RTC source clock */
 #define RTC_CLOCK_SOURCE_LSI */ /* LSI used as RTC source clock. The RTC Clock
                                      may varies due to LSI frequency dispersion. */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t  rtc_data_ck;

/* Private function prototypes -----------------------------------------------*/
static void RTC_Config(void);

/* Private functions ---------------------------------------------------------*/
void delaym(uint16_t dlx)
{
while(dlx--);
}

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

  /* Initialize Leds mounted on FT32F030XX-EVAL board */
  FT_EVAL_LEDInit(LED1);
  FT_EVAL_LEDInit(LED2);
  FT_EVAL_LEDInit(LED3);
  FT_EVAL_LEDInit(LED4);

  
  /* RTC configuration */
  RTC_Config();

  /*  */
 rtc_data_ck=C_RTC_DATACK;

  /* Check if the written data are correct */
  if(C_RTC_DATACK == rtc_data_ck)
  {
    /* Turn on LED1 */
    FT_EVAL_LEDOn(LED1);
  }
  else
  {
    /* Turn on LED3 */
    FT_EVAL_LEDOn(LED3);
  }

  /* Infinite loop */
  while (1)
  {
  FT_EVAL_LEDToggle(LED2);    
  delaym(1000);
  }
}

/**
  * @brief  Configure the RTC peripheral by selecting the clock source.
  * @param  None
  * @retval None
  */
static void RTC_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  EXTI_InitTypeDef  EXTI_InitStructure;

  /* Enable the PWR clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

  /* Allow access to RTC */
  PWR_BackupAccessCmd(ENABLE);

  /* Reset back up registers */
  RCC_BackupResetCmd(ENABLE);
  RCC_BackupResetCmd(DISABLE);
      
#if defined (RTC_CLOCK_SOURCE_LSI)  /* LSI used as RTC source clock*/
/* The RTC Clock may varies due to LSI frequency dispersion. */
  /* Enable the LSI OSC */ 
  RCC_LSICmd(ENABLE);

  /* Wait till LSI is ready */  
  while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
  {
  }

  /* Select the RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);

  /* Enable the RTC Clock */
  RCC_RTCCLKCmd(ENABLE);

  
#elif defined (RTC_CLOCK_SOURCE_LSE) /* LSE used as RTC source clock */
  /* Enable the LSE OSC */
  RCC_LSEConfig(RCC_LSE_ON);

  /* Wait till LSE is ready */  
  while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
  {
  }

  /* Select the RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

  /* Enable the RTC Clock */
  RCC_RTCCLKCmd(ENABLE);

  
#else
  #error Please select the RTC Clock source inside the main.c file
#endif /* RTC_CLOCK_SOURCE_LSI */


RTC_DeInit(); 
  /* Wait for RTC APB registers synchronisation */
  RTC_WaitForSynchro();  
  
  /* Enable The external line19 interrupt */
  EXTI_ClearITPendingBit(EXTI_Line19);
  EXTI_InitStructure.EXTI_Line = EXTI_Line19;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  /* Enable RTC IRQChannel */
  NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* Disable the Tamper 1 detection */
  RTC_TamperCmd(RTC_Tamper_1, DISABLE);

  /* Clear Tamper 1 pin Event(TAMP1F) pending flag */
  RTC_ClearFlag(RTC_FLAG_TAMP1F);

  /* Configure the Tamper 1 Trigger */
  RTC_TamperTriggerConfig(RTC_Tamper_1,  RTC_TamperTrigger_FallingEdge);

  /* Enable the Tamper interrupt */
  RTC_ITConfig(RTC_IT_TAMP, ENABLE);

  /* Clear Tamper 1 pin interrupt pending bit */
  RTC_ClearITPendingBit(RTC_IT_TAMP1);

  /* Enable the Tamper 1 detection */
  RTC_TamperCmd(RTC_Tamper_1, ENABLE);
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

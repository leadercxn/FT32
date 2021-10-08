  /**
  ******************************************************************************
  * @file    COMP/COMP_AnalogWatchdog/main.c 
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

/** @addtogroup COMP_AnalogWatchdog
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint32_t State = 0;

/* Private function prototypes -----------------------------------------------*/
static void COMP_Config(void);
static void STOPEntry(void);
static void RestoreConfiguration(void);

/* Private functions ---------------------------------------------------------*/

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

  /******* Initialize LEDs available on FT32F030XX-EVAL board ******************/
  FT_EVAL_LEDInit(LED1);
  FT_EVAL_LEDInit(LED2);
  FT_EVAL_LEDInit(LED3);
  FT_EVAL_LEDInit(LED4);
  
  /* PWR Peripheral clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

  /* configure COMP1 and COMP2 with interrupts enabled */
  COMP_Config();

  /* Check input voltage level: within the thresholds, above the upper threshold
     or under the lower threshold */
  CheckState();
  
  /* Infinite loop */
  while (1)
  {
    if (State == STATE_OVER_THRESHOLD)
    {
      /* Restore config: clock, GPIO... */
      RestoreConfiguration();
      
      /* Restore GPIO configuration */
      FT_EVAL_LEDInit(LED1);
      FT_EVAL_LEDInit(LED2);
      FT_EVAL_LEDInit(LED3);
      FT_EVAL_LEDInit(LED4);

      /* Turn on LD1 and LD3 and turn off LD2 and LD4 */
      FT_EVAL_LEDOn(LED1);
      FT_EVAL_LEDOff(LED2);
      FT_EVAL_LEDOn(LED3);
      FT_EVAL_LEDOff(LED4);
      
      while(State == STATE_OVER_THRESHOLD)
      {
         /* add your code here */
      }
    }
    else if (State == STATE_WITHIN_THRESHOLD)
    {
      /* Input voltage is within the thresholds: higher and lower thresholds */
      /* Enter STOP mode with regulator in low power */
      STOPEntry();
    }
    else /* (State == STATE_UNDER_THRESHOLD) */
    {
      /* Restore config: clock, GPIO... */
      RestoreConfiguration();

      /* Restore GPIO configuration */
      FT_EVAL_LEDInit(LED1);
      FT_EVAL_LEDInit(LED2);
      FT_EVAL_LEDInit(LED3);
      FT_EVAL_LEDInit(LED4);

      /* Turn on LD2 & LD4 and turn off LD1 & LD3 */
      FT_EVAL_LEDOff(LED1);
      FT_EVAL_LEDOn(LED2);
      FT_EVAL_LEDOff(LED3);
      FT_EVAL_LEDOn(LED4);

      while(State == STATE_UNDER_THRESHOLD)
      {
         /* add your code here */
      }
    }
  }
}

/**
  * @brief  Configure COMP1 and COMP2 with interrupt
  * @param  None
  * @retval None
  */
static void COMP_Config(void)
{
  COMP_InitTypeDef        COMP_InitStructure;
  EXTI_InitTypeDef        EXTI_InitStructure;
  NVIC_InitTypeDef        NVIC_InitStructure;
  GPIO_InitTypeDef        GPIO_InitStructure;
  
  /* GPIOA Peripheral clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  /* Configure PB12: PB12 is used as COMP1 and COMP2 non inveting input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* COMP Peripheral clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  
  /* COMP1 Init: the higher threshold is set to VREFINT ~ 1.22V
     but can be changed to other available possibilities */
  COMP_StructInit(&COMP_InitStructure);
  COMP_InitStructure.COMP_VinSel = NCOMP_VIN_SEL_DAC1_OUT;
  COMP_InitStructure.COMP_VipSel = NCOMP_VIP_SEL_PAD_PB12;
  COMP_InitStructure.COMP_OutputSel= COMP_OUTPUT_NO_SELECTION;
  COMP_InitStructure.COMP_Pol= NCOMP_POL_NOT_INVERT;
  COMP_Init(NCOMP_Selection_COMP, &COMP_InitStructure);				//COMP1  

  /* COMP2 Init: the lower threshold is set to VREFINT/4 ~ 1.22 / 4 ~ 0.305 V 
     but can be changed to other available possibilities */
  COMP_StructInit(&COMP_InitStructure);
  COMP_InitStructure.COMP_VinSel = PCOMP_VIN_SEL_DAC2_OUT;
  COMP_InitStructure.COMP_VipSel = PCOMP_VIP_SEL_PAD_PB12;
  COMP_InitStructure.COMP_OutputSel= COMP_OUTPUT_NO_SELECTION;
  COMP_InitStructure.COMP_Pol= NCOMP_POL_NOT_INVERT;
  COMP_Init(PCOMP_Selection_COMP, &COMP_InitStructure);

  /*DAC1 enable*/
  DAC_Ref_Config(DAC_CTRL_REF_SEL_1);		// 3V
  DAC_SetDAC1_Data(80);				// 3*80/128=1.875V
  DAC_SetDAC2_Data(20);				// 3*20/128=0.468V
  DAC_Cmd(ENABLE);

  /* Enable Window mode */
  COMP_WindowCmd(ENABLE);

  /* Enable COMP1: the higher threshold is set to VREFINT ~ 1.22 V */
  COMP_Cmd(NCOMP_Selection_COMP, ENABLE);
  /* Enable COMP2: the lower threshold is set to VREFINT/4 ~ 0.305 V */
  COMP_Cmd(PCOMP_Selection_COMP, ENABLE);

  /* Configure EXTI Line 21 in interrupt mode */
  EXTI_InitStructure.EXTI_Line = EXTI_Line21;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  /* Configure EXTI Line 22 in interrupt mode */
  EXTI_InitStructure.EXTI_Line = EXTI_Line22;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  /* Clear EXTI21 line */
  EXTI_ClearITPendingBit(EXTI_Line21);

  /* Clear EXTI22 line */
  EXTI_ClearITPendingBit(EXTI_Line22);

  /* Configure COMP IRQ */
  NVIC_InitStructure.NVIC_IRQChannel = ADC1_COMP_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  Prepare the system to enter STOP mode.
  * @param  None
  * @retval None
  */
static void STOPEntry(void)
{
  GPIO_InitTypeDef        GPIO_InitStructure;
  /* Enable GPIOs clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC |
                        RCC_AHBPeriph_GPIOD | RCC_AHBPeriph_GPIOF, ENABLE);

  /* Configure all GPIO port pins in Analog mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  GPIO_Init(GPIOF, &GPIO_InitStructure);
  
  /* Request to enter STOP mode with regulator in low power */
  PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);
}

/**
  * @brief  check input voltage level: within the thresholds, above the upper 
  *         threshold or under the lower threshold
  * @param  None
  * @retval None
  */
void CheckState(void)
{
  /* Check if COMP2 output level is high */
  if ((COMP_GetOutputLevel(NCOMP_Selection_COMP) == COMP_OutputLevel_High) 
   && (COMP_GetOutputLevel(PCOMP_Selection_COMP) == COMP_OutputLevel_High))
  {
    /* A rising edge is detected so the input voltage is higher than VREFINT */
    State = STATE_OVER_THRESHOLD;
  }
  else if ((COMP_GetOutputLevel(NCOMP_Selection_COMP) == COMP_OutputLevel_Low)
       && (COMP_GetOutputLevel(PCOMP_Selection_COMP) == COMP_OutputLevel_High))
  {
    /* A falling edge is detected so the input voltage is lower than VREFINT */
    State = STATE_WITHIN_THRESHOLD;
  }
  else if ((COMP_GetOutputLevel(NCOMP_Selection_COMP) == COMP_OutputLevel_Low)
       && (COMP_GetOutputLevel(PCOMP_Selection_COMP) == COMP_OutputLevel_Low))
  {
    State = STATE_UNDER_THRESHOLD;
  }
}

/**
  * @brief  Restore peripheral config before entering STOP mode.
  * @param  None
  * @retval None
  */
static void RestoreConfiguration(void)
{
  __IO uint32_t StartUpCounter = 0, HSIStatus = 0;
  
 /* SYSCLK, HCLK, PCLK configuration ----------------------------------------*/
  /* Enable HSI */    
  RCC->CR |= ((uint32_t)RCC_CR_HSION);
 
  /* Wait till HSI is ready and if Time out is reached exit */
  do
  {
    HSIStatus = RCC->CR & RCC_CR_HSIRDY;
    StartUpCounter++;  
  } while((HSIStatus == 0) && (StartUpCounter != HSI_STARTUP_TIMEOUT));

  if ((RCC->CR & RCC_CR_HSIRDY) != RESET)
  {
    HSIStatus = (uint32_t)0x01;
  }
  else
  {
    HSIStatus = (uint32_t)0x00;
  }  

  if (HSIStatus == (uint32_t)0x01)
  {
    /* Enable Prefetch Buffer and set Flash Latency */
    FLASH->ACR = FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY;
 
    /* HCLK = SYSCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
      
    /* PCLK = HCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE_DIV1;

    /* PLL configuration */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
    RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSI_PREDIV | RCC_CFGR_PLLXTPRE_PREDIV1 | RCC_CFGR_PLLMULL6);
            
    /* Enable PLL */
    RCC->CR |= RCC_CR_PLLON;

    /* Wait till PLL is ready */
    while((RCC->CR & RCC_CR_PLLRDY) == 0)
    {
    }

    /* Select PLL as system clock source */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
    RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;    

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)RCC_CFGR_SWS_PLL)
    {
    }
  }
  else
  { /* If HSE fails to start-up, the application will have wrong clock 
         configuration. User can add here some code to deal with this error */
  }  
 
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

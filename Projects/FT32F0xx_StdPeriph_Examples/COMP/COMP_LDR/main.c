 /**
  ******************************************************************************
  * @file    COMP/COMP_LDR/main.c 
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

/** @addtogroup COMP_LDR
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define MESSAGE1   "        LDR         "

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t ldrlevel = 11, ldrlevelp = 0, daclevel = 0;
uint16_t tmp = 0;
  
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void COMP_Config(void);
static void DAC_Config(void);
void Delay(__IO uint32_t nTime);

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
  
  /* Clear the LCD */ 
  LCD_Clear(LCD_COLOR_BLACK);
  
  /* Set the LCD Back Color */
  LCD_SetBackColor(LCD_COLOR_BLACK);
  
  /* Set the LCD Text Color */
  LCD_SetTextColor(LCD_COLOR_WHITE);
  
  /* Displays Light dependent resistor (LDR) message on line 1 */
  LCD_DisplayStringLine(LINE(0), (uint8_t *)MESSAGE1);
  
  /* COMP Configuration */
  COMP_Config();
 
  /* AC channel 2 Configuration */
  DAC_Config();
  
  
  /* Infinite loop */
  while (1)
  {
    for(daclevel = 0; daclevel < 11; daclevel++)
    {
      /* Set DAC Channel2 DHR register: DAC_OUT2 = (3.3 * 868) / 4095 ~ 0.7 V */
      DAC_SetChannel1Data( 0,(uint8_t)(daclevel * 11));

      Delay((10000));
      /* Check on the Comp output level*/
      if (COMP_GetOutputLevel(NCOMP_Selection_COMP) == COMP_OutputLevel_High)
      {
        ldrlevel--;
      }
    }

    switch(ldrlevel)
    {
    case 1:
      /* Displays MESSAGE on line 7 */
      LCD_DisplayStringLine(LINE(7), "       Level 0      ");
      break;
      
    case 2:
      /* Displays MESSAGE on line 7 */
      LCD_DisplayStringLine(LINE(7), "       Level 1      ");
      break;
      
    case 3:
      /* Displays MESSAGE on line 7  */
      LCD_DisplayStringLine(LINE(7), "       Level 2      ");
      break;
      
    case 4:
      /* Displays MESSAGE on line 7  */
      LCD_DisplayStringLine(LINE(7), "       Level 3      ");
      break;
      
    case 5:
      /* Displays MESSAGE on line 7  */
      LCD_DisplayStringLine(LINE(7), "       Level 4      ");
      break;
      
    case 6:
      /* Displays MESSAGE on line 7  */
      LCD_DisplayStringLine(LINE(7), "       Level 5      ");
      break;
      
    case 7:
      /* Displays MESSAGE on line 7  */
      LCD_DisplayStringLine(LINE(7), "       Level 6      ");
      break;
      
    case 8:
      /* Displays MESSAGE on line 7  */
      LCD_DisplayStringLine(LINE(7), "       Level 7      ");
      break;
      
    case 9:
      /* Displays MESSAGE on line 7 */
      LCD_DisplayStringLine(LINE(7), "       Level 8      ");
      break;
      
    case 10:
      /* Displays MESSAGE on line 7  */
      LCD_DisplayStringLine(LINE(7), "       Level 9      ");
      break;
      
    case 11:
      /* Displays MESSAGE on line 7  */
      LCD_DisplayStringLine(LINE(7), "       Level 10     ");
      break;
      
    default :
      /* Displays MESSAGE on line 7  */
      LCD_DisplayStringLine(LINE(7), "       Level 0      ");
      ldrlevel = 1;
      break;
    }
    
    if(ldrlevelp != ldrlevel)
    {
      /* Set the LCD Text Color */
      LCD_SetTextColor(LCD_COLOR_WHITE);
      
      /* Displays a rectangle on the LCD */
      LCD_DrawRect(199, 311, 22, 302 );
      
      /* Set the LCD Back Color */
      LCD_SetBackColor(LCD_COLOR_BLACK);
      LCD_SetTextColor(LCD_COLOR_BLACK);
      LCD_DrawFullRect(200, 310,  300, 20);
      
      /* Set the LCD Text Color */
      LCD_SetTextColor(LCD_COLOR_YELLOW);
      
      /* Set the LCD Back Color */
      LCD_SetBackColor(LCD_COLOR_YELLOW);
      
      /* Displays a full rectangle */
      tmp = 30 * (ldrlevel-1);
      if (tmp ==0) tmp = 5;
      LCD_DrawFullRect(200, 310, tmp , 20);
    }
    
    ldrlevelp = ldrlevel;
    ldrlevel = 11;
    
    /* Set the LCD Back Color */
    LCD_SetBackColor(LCD_COLOR_BLACK);
  }

}

/**
  * @brief COMP Configuration.
  * @param None
  * @retval None
  */
static void COMP_Config(void)
{
  COMP_InitTypeDef COMP_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  /* GPIOB Peripheral clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
 
  /* Configure PA1 in analog mode: PA1 is connected to COMP1 non inverting input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* Enable SYSCFG clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  
  /* COMP1 Init: COMP1 is enabled as soon as inverting input is selected */
  /* use DAC1 output as a reference voltage: DAC1 output is connected to COMP1
  inverting input */
  COMP_InitStructure.COMP_VinSel= NCOMP_VIN_SEL_DAC1_OUT;
  COMP_InitStructure.COMP_VipSel= NCOMP_VIP_SEL_PAD_PA1;
  COMP_InitStructure.COMP_OutputSel= COMP_OUTPUT_NO_SELECTION;
  COMP_InitStructure.COMP_Pol= NCOMP_POL_NOT_INVERT;
  COMP_Init(NCOMP_Selection_COMP, &COMP_InitStructure);
  
  /* Enable the COMP peripheral */
  COMP_Cmd(NCOMP_Selection_COMP, ENABLE);
}

/**
  * @brief  Configures the DAC channel 2 with output buffer enabled.
  * @param  None
  * @retval None
  */
static void DAC_Config(void)
{

   /* Enable SYSCFG clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
   
  DAC_Ref_Config(DAC_CTRL_REF_SEL_0);				// 3V
  DAC_SetChannel1Data( 0,(uint8_t)(0));

  /* Enable DAC*/
  DAC_Cmd( ENABLE);
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{ 
  while(nTime != 0)
  {
  nTime--;
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

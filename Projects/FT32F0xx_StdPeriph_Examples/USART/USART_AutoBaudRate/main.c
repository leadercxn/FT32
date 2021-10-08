  /**
  ******************************************************************************
  * @file    USART/USART_AutoBaudRate/main.c 
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

/** @addtogroup USART_AutoBaudRate
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void USART_Config(void);
static void AutoBauRate_StartBitMethod(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Main program
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
  
  /* Initialize LEDs available on FT32F030XX-EVAL board ************************/
  FT_EVAL_LEDInit(LED1);
  FT_EVAL_LEDInit(LED2);
  FT_EVAL_LEDInit(LED3);
  FT_EVAL_LEDInit(LED4);
  
  /* Configure and enable the systick timer to generate an interrupt each 1 ms */
  SysTick_Config((SystemCoreClock / 1000));
  
  /* USART configuration */
  USART_Config();
  
  /* AutoBaudRate for USART by Start bit Method */
  AutoBauRate_StartBitMethod();
  
  while(1);
}

/**
  * @brief Configure the USART Device
  * @param  None
  * @retval None
  */
static void USART_Config(void)
{ 
  USART_InitTypeDef USART_InitStructure;
  
  /* USARTx configured as follow:
  - BaudRate = 115200 baud  
  - Word Length = 8 Bits
  - Stop Bit = 1 Stop Bit
  - Parity = No Parity
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  FT_EVAL_COMInit(COM1, &USART_InitStructure);
}

/**
  * @brief  Start Bit Method to USART AutoBaudRate.
  * @param  None
  * @retval None
  */
static void AutoBauRate_StartBitMethod(void)
{ 
  /* USART enable */
 /*MUST DISABLE FIRST*/
  USART_Cmd(EVAL_COM1, DISABLE);
  
  /* Configure the AutoBaudRate method */
  USART_AutoBaudRateConfig(EVAL_COM1, USART_AutoBaudRate_StartBit);
  
  /* Enable AutoBaudRate feature */
  USART_AutoBaudRateCmd(EVAL_COM1, ENABLE);

  /**/
  USART_Cmd(EVAL_COM1, ENABLE);
  
  /* Loop until the end of Autobaudrate phase */
  while(USART_GetFlagStatus(EVAL_COM1, USART_FLAG_ABRF) == RESET)
  {}  
  
  /* If AutoBaudBate error occurred */
  if (USART_GetFlagStatus(EVAL_COM1, USART_FLAG_ABRE) != RESET)
  {
    /* Turn on LED3 */
    FT_EVAL_LEDOn(LED3);
  }
  else
  {
    /* Turn on LED2 */
    FT_EVAL_LEDOn(LED2);
    
    /* Wait until RXNE flag is set */
    while(USART_GetFlagStatus(EVAL_COM1, USART_FLAG_RXNE) == RESET)
    {}
    
    /* Wait until TXE flag is set */    
    while(USART_GetFlagStatus(EVAL_COM1, USART_FLAG_TXE) == RESET)
    {}
    
    /* Send received character */
    USART_SendData(EVAL_COM1, USART_ReceiveData(EVAL_COM1)); 
    
    /* Check the Transfer Complete Flag */
    while (USART_GetFlagStatus(EVAL_COM1, USART_FLAG_TC) == RESET)
    {}

    /* Clear TE bit  , must after transmission over*/
    USART_DirectionModeCmd(EVAL_COM1, USART_Mode_Tx, DISABLE);
    
  }
  
  /* USART Disable */
  USART_Cmd(EVAL_COM1, DISABLE);
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

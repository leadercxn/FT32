    /**
  ******************************************************************************
  * @file    DMA/DMA_USARTTransfer/main.c 
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

/** @addtogroup DMA_USARTTransfer
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t TxBuffer1[] = "Communication between USART1-USART2 using DMA1";
uint8_t TxBuffer2[] = "Communication between USART2-USART1 using DMA1";
uint8_t RxBuffer2 [RXBUFFERSIZE] = {0};
uint8_t RxBuffer1 [RXBUFFERSIZE] = {0};
__IO TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;
USART_InitTypeDef USART_InitStructure;
DMA_InitTypeDef  DMA_InitStructure;

/* Private function prototypes -----------------------------------------------*/
static void RCC_Config(void);
static void GPIO_Config(void);
static TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);

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
  
  /* Enable periph Clock */
  RCC_Config();
  
  /* Configure Usarts Pins TX/RX */
  GPIO_Config();
  
  /*------------------------------- USART-------------------------------------*/  
  /* USARTx configured as follow:
  - BaudRate = 9600 
  - Word Length = USART_WordLength_7b
  - Stop Bit = USART_StopBits_1
  - Parity = USART_Parity_No
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_7b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Tx| USART_Mode_Rx;
  USART_Init(USART1, &USART_InitStructure);
  USART_Init(USART2, &USART_InitStructure);

  /*------------------------------- DMA---------------------------------------*/   
  /* Common DMA configuration */
  DMA_InitStructure.DMA_BufferSize = TXBUFFERSIZE;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  
  /* DMA1 Channel2 configuration */
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)TxBuffer1;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
  DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
  DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_TDR_Address;
  DMA_Init(DMA1_Channel2, &DMA_InitStructure);
  
 // /* DMA remap Channel1 to USART1 Tx */
 // DMA_RemapConfig(DMA2, DMA2_CH1_USART1_TX);
  
  /* DMA1 Channel5 configuration */
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)RxBuffer2;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
  DMA_InitStructure.DMA_PeripheralBaseAddr = USART2_RDR_Address;
  DMA_Init(DMA1_Channel5, &DMA_InitStructure);
  
  ///* DMA remap Channel2 to USART2 Rx */
  //DMA_RemapConfig(DMA2, DMA2_CH2_USART2_RX);
  
  /* DMA1 Channel4 configuration */
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)TxBuffer2;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
  DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
  DMA_InitStructure.DMA_PeripheralBaseAddr = USART2_TDR_Address;
  DMA_Init(DMA1_Channel4, &DMA_InitStructure);
  
 // /* DMA remap Channel4 to USART2 Tx */
 // DMA_RemapConfig(DMA2, DMA2_CH4_USART2_TX);
  
  /* DMA1 Channel3 configuration */
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)RxBuffer1;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
  DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_RDR_Address;
  DMA_Init(DMA1_Channel3, &DMA_InitStructure);
  
 // /* DMA remap Channel43to USART1 Rx */
  //DMA_RemapConfig(DMA2, DMA2_CH3_USART1_RX); 
    
  /* Enable the USART2 Rx and Tx DMA2 requests */
  USART_DMACmd(USART2, USART_DMAReq_Rx|USART_DMAReq_Tx, ENABLE);
  
  /* Enable the USART1 Rx and Tx DMA2 requests */
  USART_DMACmd(USART1, USART_DMAReq_Tx|USART_DMAReq_Rx, ENABLE);

   USART_Cmd(USART2, ENABLE);
  USART_Cmd(USART1, ENABLE);
  
  /* Enable the DMA2 channels */
  DMA_Cmd(DMA1_Channel2, ENABLE);
  DMA_Cmd(DMA1_Channel3, ENABLE); 
  DMA_Cmd(DMA1_Channel4, ENABLE); 
  DMA_Cmd(DMA1_Channel5, ENABLE);

  
  /* Test on Channels DMA_FLAG_TC flag */
  while(!DMA_GetFlagStatus(DMA1_FLAG_TC2));
  while(!DMA_GetFlagStatus(DMA1_FLAG_TC3)); 
  while(!DMA_GetFlagStatus(DMA1_FLAG_TC4));
  while(!DMA_GetFlagStatus(DMA1_FLAG_TC5)); 
  
  /* Clear DMA1 TC flags */
  DMA_ClearFlag(DMA1_FLAG_TC2);
  DMA_ClearFlag(DMA1_FLAG_TC3);
  DMA_ClearFlag(DMA1_FLAG_TC4);
  DMA_ClearFlag(DMA1_FLAG_TC5);
  
  /* Disable DMA1 channels */
  DMA_Cmd(DMA1_Channel2, DISABLE); 
  DMA_Cmd(DMA1_Channel3, DISABLE);
  DMA_Cmd(DMA1_Channel4, DISABLE); 
  DMA_Cmd(DMA1_Channel5, DISABLE);  
  
  /* Check the received data with the send ones */
  /* TransferStatus1 = PASSED, if the data transmitted from USART2 and received 
     by USART1 are the same */
  /* TransferStatus1 = FAILED, if the data transmitted from USART2 and received 
     by USART1 are different */
  TransferStatus1 = Buffercmp((uint8_t*) RxBuffer1, (uint8_t*) TxBuffer2, RXBUFFERSIZE);

  /* TransferStatus2 = PASSED, if the data transmitted from USART1 and received 
     by USART2 are the same */
  /* TransferStatus2 = FAILED, if the data transmitted from USART1 and received 
     by USART2 are different */
  TransferStatus2 = Buffercmp((uint8_t*) RxBuffer2, (uint8_t*) TxBuffer1, RXBUFFERSIZE);
  
  /* Infinite Loop */
  while(1);
}

/**
  * @brief  Configures the USART Peripheral.
  * @param  None
  * @retval None
  */
static void RCC_Config(void)
{ 
  /* Enable GPIO clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  
  /* Enable USARTs Clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);  
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  
  /* Enable the DMA periph */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
  
  /* Enable Syscfg */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
}

/**
  * @brief  Configures the USART Peripheral.
  * @param  None
  * @retval None
  */
static void GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  /* USART1 Pins configuration ************************************************/
  /* Connect pin to Periph */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1); 		//USART1_TX
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);    	//USART1_RX
  
  /* Configure pins as AF pushpull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);  

  /* USART2 Pins configuration ************************************************/  
  /* Connect pin to Periph */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_1);		//USART2_TX
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1);    		//USART2_RX
  
  /* Configure pins as AF pushpull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);   
}

/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval PASSED: pBuffer1 identical to pBuffer2
  *         FAILED: pBuffer1 differs from pBuffer2
  */
static TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
  while (BufferLength--)
  {
    if (*pBuffer1 != *pBuffer2)
    {
      return FAILED;
    }
    pBuffer1++;
    pBuffer2++;
  }
  
  return PASSED;
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

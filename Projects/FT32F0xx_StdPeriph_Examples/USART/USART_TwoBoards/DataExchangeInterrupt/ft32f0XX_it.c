    /**
  ******************************************************************************
  * @file    USART/USART_TwoBoards/DataExchangeInterrupt/FT32F0XX8_it.c
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

/** @addtogroup USART_DataExchangeInterrupt
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern uint8_t TxBuffer[];
extern uint8_t RxBuffer[];
extern uint8_t CmdBuffer[];
extern uint8_t AckBuffer[];
extern __IO uint8_t RxIndex;
extern __IO uint8_t TxIndex;

extern __IO uint8_t UsartTransactionType;
extern __IO uint8_t UsartMode;

__IO uint8_t Counter = 0x00;
extern __IO uint32_t TimeOut;

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
  /* Decrement the timeout value */
  if (TimeOut != 0x0)
  {
    TimeOut--;
  }
    
  if (Counter < 10)
  {
    Counter++;
  }
  else
  {
    Counter = 0x00;
    FT_EVAL_LEDToggle(LED1);
  }
}

/******************************************************************************/
/*            FT32f0xx Peripherals Interrupt Handlers                        */
/******************************************************************************/
/**
* @brief  This function handles USART interrupt request.
* @param  None
* @retval None
*/
void USARTx_IRQHandler(void)
{
  /* USART in mode Transmitter -------------------------------------------------*/
  if (USART_GetITStatus(USARTx, USART_IT_TXE) == SET)
  { /* When Joystick Pressed send the command then send the data */
    if (UsartMode == USART_MODE_TRANSMITTER)
    { /* Send the command */
      if (UsartTransactionType == USART_TRANSACTIONTYPE_CMD)
      {
        USART_SendData(USARTx, CmdBuffer[TxIndex++]);
        if (TxIndex == 0x02)
        {
          /* Disable the USARTx transmit data register empty interrupt */
          USART_ITConfig(USARTx, USART_IT_TXE, DISABLE);
        }
      }
      /* Send the data */
      else
      {
        USART_SendData(USARTx, TxBuffer[TxIndex++]);
        if (TxIndex == GetVar_NbrOfData())
        {
          /* Disable the USARTx transmit data register empty interrupt */
          USART_ITConfig(USARTx, USART_IT_TXE, DISABLE);
        }
      }
    }
    /*If Data Received send the ACK*/
    else
    {
      USART_SendData(USARTx, AckBuffer[TxIndex++]);
      if (TxIndex == 0x02)
      {
          /* Disable the USARTx transmit data register empty interrupt */
          USART_ITConfig(USARTx, USART_IT_TXE, DISABLE);
      }
    }
  }
  
  /* USART in mode Receiver --------------------------------------------------*/
  if (USART_GetITStatus(USARTx, USART_IT_RXNE) == SET)
  {
    if (UsartMode == USART_MODE_TRANSMITTER)
    {
      AckBuffer[RxIndex++] = USART_ReceiveData(USARTx);
    }
    else
    {
      /* Receive the command */
      if (UsartTransactionType == USART_TRANSACTIONTYPE_CMD)
      {
        CmdBuffer[RxIndex++] = USART_ReceiveData(USARTx);
      }
      /* Receive the USART data */
      else
      {
        RxBuffer[RxIndex++] = USART_ReceiveData(USARTx);
      }
    }
  }     
}
/******************************************************************************/
/*                 FT32f0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_FT32f0xx.s).                                            */
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

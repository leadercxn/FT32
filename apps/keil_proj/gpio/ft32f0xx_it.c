/**
  ******************************************************************************
  * @file    Project/FT32F0XX_StdPeriph_Templates/ft32f0XX_it.c 
  * @author  AE
  * @version V1.0.0
  * @date    2021-03-29
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  */

/* Includes ------------------------------------------------------------------*/
#include "ft32f0xx_it.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define TXBUFFERSIZE (countof(TxBuffer) - 1)
#define RXBUFFERSIZE 0x20

/* Private macro -------------------------------------------------------------*/
#define countof(a) (sizeof(a) / sizeof(*(a)))

/* Private variables ---------------------------------------------------------*/
uint8_t TxBuffer[] = "\n\rUSART Hyperterminal Interrupts Example: USART-Hyperterminal\
 communication using Interrupt\n\r";
uint8_t RxBuffer[RXBUFFERSIZE];
uint8_t NbrOfDataToTransfer = TXBUFFERSIZE;
uint8_t NbrOfDataToRead = RXBUFFERSIZE;
__IO uint8_t TxCount = 0;
__IO uint16_t RxCount = 0;

/** @addtogroup Template_Project
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

/******************************************************************************/
/*                 FT32F030X8 Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_ft32f030x8.s).                                            */
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

/**
  * @}
  */

/**
  * @brief  This function handles USART1 global interrupt request.
  * @param  None
  * @retval None
  */
#ifdef USE_FT32F030XX_EVAL
void USART1_IRQHandler(void)
{
    if (USART_GetITStatus(EVAL_COM1, USART_IT_RXNE) != RESET)
    {
        /* Read one byte from the receive data register */
        RxBuffer[RxCount++] = (USART_ReceiveData(EVAL_COM1) & 0x7F);

        if (RxCount == NbrOfDataToRead)
        {
            /* Disable the EVAL_COM1 Receive interrupt */
            USART_ITConfig(EVAL_COM1, USART_IT_RXNE, DISABLE);
        }
    }

    if (USART_GetITStatus(EVAL_COM1, USART_IT_TXE) != RESET)
    {
        /* Write one byte to the transmit data register */
        USART_SendData(EVAL_COM1, TxBuffer[TxCount++]);

        if (TxCount == NbrOfDataToTransfer)
        {
            /* Disable the EVAL_COM1 Transmit interrupt */
            USART_ITConfig(EVAL_COM1, USART_IT_TXE, DISABLE);
        }
    }
}
#else
void USART2_IRQHandler(void)
{
    if (USART_GetITStatus(EVAL_COM1, USART_IT_RXNE) != RESET)
    {
        /* Read one byte from the receive data register */
        RxBuffer[RxCount++] = (USART_ReceiveData(EVAL_COM1) & 0x7F);

        if (RxCount == NbrOfDataToRead)
        {
            /* Disable the EVAL_COM1 Receive interrupt */
            USART_ITConfig(EVAL_COM1, USART_IT_RXNE, DISABLE);
        }
    }

    if (USART_GetITStatus(EVAL_COM1, USART_IT_TXE) != RESET)
    {
        /* Write one byte to the transmit data register */
        USART_SendData(EVAL_COM1, TxBuffer[TxCount++]);

        if (TxCount == NbrOfDataToTransfer)
        {
            /* Disable the EVAL_COM1 Transmit interrupt */
            USART_ITConfig(EVAL_COM1, USART_IT_TXE, DISABLE);
        }
    }
}
#endif /* USE_FT32F030XX_EVAL */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/

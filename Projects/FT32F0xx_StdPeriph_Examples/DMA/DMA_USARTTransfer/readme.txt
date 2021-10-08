  /**
  ******************************************************************************
  * @file    DMA/DMA_USARTTransfer/readme.txt 
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

@par Example Description 

This example provides a basic communication between USART1 and USART2 using DMA2 
capability.

First, the DMA transfers data from TxBuffer2 buffer to USART2 Transmit data 
register, then this data is sent to USART1. Data received by USART1 is transferred
by DMA and stored in RxBuffer1 then compared with the send ones and the result 
of this comparison is stored in the "TransferStatus1" variable.
 
In the same time, the DMA transfers data from TxBuffer1 buffer to USART1 Transmit
data register, then this data is sent to USART2. Data received by USART2 is
transferred by DMA and stored in RxBuffer2 then compared with the send ones and
the result of this comparison is stored in the "TransferStatus2" variable. 

USART1 and USART2 configured as follow:
  - BaudRate = 9600 
  - Word Length = USART_WordLength_7b
  - Stop Bit = USART_StopBits_1
  - Parity = USART_Parity_No
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled



                     
@par Hardware and Software environment

  - This example runs on FT32f0xx devices.
  
 - This example has been tested with FMD FT32F030XX-EVAL and
    FT32F072X8-EVAL 

@par How to use it ? 

In order to make the program work, you must do the following :
 - Copy all source files from this example folder to the template folder under
   Project\FT32f0xx_StdPeriph_Templates
 - Open your preferred toolchain 
- If the used device is FT32F072XX
    - Add the following files to the project source list
       - Utilities\FT32_EVAL\FT32F072X8_EVAL\FT32F072X8_eval.c
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT FMD</center></h3>
 */

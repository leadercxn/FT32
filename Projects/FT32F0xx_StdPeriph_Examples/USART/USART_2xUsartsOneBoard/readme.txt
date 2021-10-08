   /**
  ******************************************************************************
  * @file    USART/USART_2xUsartsOneBoard/readme.txt 
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

This example provides a small application in which 2xUsarts are used for a circular 
communication using interrupts and USART firmware library.

First, the USARTy sends aTxBuffer to USARTy+1. The USARTy+1 receives data and
stores it into aRxBuffer[y].
Then, the received data is then compared with the sent one. 
Then, USARTy+1 sends the received message to the next USARTy+2.
At the end, the last one USART8 sends the data to the first One USART1.
It can validate the correctness of the USART1_TX sent data and USART1_RX received data.
These operations can be repeated infinitely.

You can see the received data stored in aRxBuffer[] variable using your toolchain debugger.

The 2xUsarts are configured as follow:
  - BaudRate = 9600 baud  
  - Word Length = 8 Bits
  - One Stop Bit
  - No parity
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled




@par How to use it ? 

In order to make the program work, you must do the following :
 - Copy all source files from this example folder to the template folder under
   Project\FT32f0xx_StdPeriph_Templates
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT FMD</center></h3>
 */

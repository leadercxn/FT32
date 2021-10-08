    /**
  ******************************************************************************
  * @file    USART/USART_HyperTerminalInterrupt/readme.txt 
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

This example provides a description of how to use the USART1 for FT32F030XX devices 
and USART2 FT32F072X8 devices with Transmit and Receive interrupts to communicate
with the hyperterminal.

First, the USART sends the TxBuffer to the hyperterminal and still waiting for 
a string from the hyperterminal that you must enter.The string that you have entered 
is stored in the RxBuffer array. The receive buffer have a RxBufferSize bytes as 
maximum (the reception is stopped when this maximum receive value is reached).

The USART is configured as follow:
    - BaudRate = 9600 baud  
    - Word Length = 8 Bits (7 data bit + 1 parity bit)
    - Two Stop Bit
    - Odd parity
    - Hardware flow control disabled (RTS and CTS signals)
    - Receive and transmit enabled

@note When the parity is enabled, the computed parity is inserted at the MSB
position of the transmitted data.





         
@par Hardware and Software environment

  - This example runs on FT32f0xx devices.
  
  - This example has been tested with FMD FT32F030XX-EVAL and
    FT32F072X8-EVAL 
    

  - FT32F030XX-EVAL Set-up
      - Connect a null-modem female/female RS232 cable between the DB9 connector 
        CN7 and PC serial port.
      - Make sure that JP3 is in position 5<->6  
      
  - FT32F072X8-EVAL Set-up  
      - Connect a null-modem female/female RS232 cable between the DB9 connector 
        CN10 and PC serial port.
      - Make sure that JP17 is in position 5<->6 

  - Hyperterminal configuration:
    - Word Length = 7 Bits
    - Two Stop Bit
    - Odd parity
    - BaudRate = 9600 baud
    - flow control: None 


@par How to use it ? 

In order to make the program work, you must do the following :
 - Copy all source files from this example folder to the template folder under
   Project\FT32f0xx_StdPeriph_Templates
 - Open your preferred toolchain  
 - If the used device is FT32F030XX
    - Add the following files to the project source list
       - Utilities\FT_EVAL\FT32F030XX_EVAL\FT32F030XX_eval.c
 - If the used device is FT32F072X8
    - Add the following files to the project source list
       - Utilities\FT32_EVAL\FT32F072X8_EVAL\FT32F072X8_eval.c
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT FMD</center></h3>
 */

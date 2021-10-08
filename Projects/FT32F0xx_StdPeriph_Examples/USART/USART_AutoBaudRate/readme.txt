   
  /**
  ******************************************************************************
  * @file    USART/USART_AutoBaudRate/readme.txt 
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

This example provides a description of how to use the Auto BaudRate capability
of the USART via the HyperTerminal.

After configuration, the USART waits until a data is received via HyperTerminal
to launch auto-detection of Baud Rate phase. The end of this phase is monitored 
by ABRF flag.

The result of auto-detection is indicated by EVAL Board LEDs. If an error occurred 
in Auto BaudRate phase ABRE flag is set and LED3 is turned on. If this phase is 
completed successfully, LED2 is turned on and the received data is transmitted back 
to the HyperTerminal.
You can repeat this procedure by changing the BaudRate on HyperTerminal side.
 
The USART is configured as follow:
    - BaudRate = 115200 baud (any value can be chosen)  
    - Word Length = 8 Bits 
    - One Stop Bit
    - No parity
    - Hardware flow control disabled (RTS and CTS signals)
    - Receive and transmit enabled



         
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
    - BaudRate = User can select any value
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - flow control: None 


@par How to use it ? 

In order to make the program work, you must do the following :
 - Copy all source files from this example folder to the template folder under
   Project\FT32f0xx_StdPeriph_Templates
 - If the used device is FT32F030XX
    - Add the following files to the project source list
       - Utilities\FT32_EVAL\FT32F030XX_EVAL\FT32F030XX_eval.c
 - If the used device is FT32F072X8
    - Add the following files to the project source list
       - Utilities\FT32_EVAL\FT32F072X8_EVAL\FT32F072X8_eval.cc 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT FMD</center></h3>
 */

 /**
  ******************************************************************************
  * @file    CRC/CRC_TwoBoards/readme.txt 
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

This example aims to show how to verify CRC checksum while USART communication
between two FT32f0xx boards.

- Hardware Description

To use this example, you need to load it on two FT32f0xx boards (FT32F072X8-Eval) 
(let's call them Board A and Board B) then connect these two boards through UART 
lines and GND.

In the firmware example uncomment the dedicated line in the main.h file to use
the USART peripheral as TRANSMITTER device or as RECEIVER device.

- The connection between the pins should use a common Ground.

@verbatim
*------------------------------------------------------------------------------*
|                BOARD A                                BOARD B                |
|         ____________________                   ____________________          |
|        |                    |                 |                    |         |
|        |     TRANSMITTER    |                 |      RECEIVER       |         | 
|        |     __________     |                 |     __________     |         |
|        |    |   USART  |____|TX_____________RX|____|   USART  |    |         |
|        |    |  Device1 |____|RX_____________TX|____|  Device2 |    |         |
|        |    |__________|    |                 |    |__________|    |         |
|        |                    |                 |                    |         |
|        |  O LD1             |                 |  O LD1             |         |
|        |  O LD2    Joystick |                 |  O LD2    Joystick |         |
|        |  O LD3        _    |                 |  O LD3        _    |         |
|        |              |_|   |                 |              |_|   |         |
|        |                    |                 |                    |         |
|        |             GND O--|-----------------|--O GND             |         |
|        |____________________|                 |____________________|         |
|                                                                              |
|                                                                              |
*------------------------------------------------------------------------------*
@endverbatim

- Software Description

The CRC peripheral is configured to use the 8-bit CRC polynomial X32 + X26 + X23 + X22 + X16 + X12 + X11 + X10 +X8 + X7 + X5 + X4 + X2+ X + 1 
with the initialization value is set to 0.

On Board A, at each joystick SEL button press:

- The USART Board A sends data already defined in TxBuffer.

- CRC value is computed during USART data transfer.  

- After computing CRC of latest transferred byte, TxBuffer is updated with final CRC value.

- The USART Board A sends latest byte which is the final computed CRC value.

On Board B,

- The USART Board B receives the data (data + CRC value) in RxBuffer.

- CRC value of received data are computed in Board B and compared with the received one.
  
  CRC checksum result is signaled by LED lightening as following:
    - CRC received and computed values are equal ==> LD2 toggles, LED3 OFF. 
    - CRC received and computed values are not equal ==> LD2 Off, LED3 ON. 

The SysTick is configured to generate interrupt each 10ms. A dedicated counter 
inside the SysTick ISR is used to toggle the LD1 each 100ms indicating that the 
firmware is running.

These operations can be repeated infinitely.


  
@par Hardware and Software environment

  - This example runs on FT32F072 Devices.
  
  - This example has been tested with FMD FT32F030XX-EVAL (FT32f0xx)
    

  - FT32F072X8-EVAL Set-up
    - Use The Joystick SEL button [PA.0]
    - Connect USART2 TX pin (PA.02) to USART2 RX pin (PA.03)
    - Connect USART2 RX pin (PA.03) to USART2 TX pin (PA.02)

@par How to use it ? 

In order to make the program work, you must do the following :
 - Copy all source files from this example folder to the template folder under
   Project\FT32f0xx_StdPeriph_Templates
 - Open your preferred toolchain 
 - If the used device is FT32F030XX
    - Add the following files to the project source list
       - Utilities\FT32_EVAL\FT32F030XX_EVAL\FT32F030XX_eval.c
 - If the used device is FT32F072X8
    - Add the following files to the project source list
       - Utilities\FT32_EVAL\FT32F072X8_EVAL\FT32F072X8_eval.c
 - Rebuild all files and load your image into target memory
 - Run the example
    
 * <h3><center>&copy; COPYRIGHT FMD</center></h3>
 */

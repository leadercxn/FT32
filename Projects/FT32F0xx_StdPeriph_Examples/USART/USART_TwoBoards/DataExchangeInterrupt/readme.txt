    /**
  ******************************************************************************
  * @file    USART/USART_TwoBoards/DataExchangeInterrupt/readme.txt 
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

This example provides a small application in which joystick buttons are used 
to trigger USART communication using interrupts and though using USART firmware 
library.

- Hardware Description

To use this example, you need to load it on two FT32f0xx boards (let's call them 
Board A and Board B) then connect these two boards through UART lines and GND.

@verbatim
*------------------------------------------------------------------------------*
|                BOARD A                                BOARD B                |
|         ____________________                   ____________________          |
|        |                    |                 |                    |         |
|        |                    |                 |                    |         | 
|        |     __________     |                 |     __________     |         |
|        |    |   USART  |____|TX_____________RX|____|   USART  |    |         |
|        |    |  Device1 |____|RX_____________TX|____|  Device2 |    |         |
|        |    |__________|    |                 |    |__________|    |         |
|        |                    |                 |                    |         |
|        |  O LD1             |                 |  O LD1             |         |
|        |  O LD2    Joystick |                 |  O LD2    Joystick |         |
|        |  O LD3        _    |                 |  O LD3        _    |         |
|        |  O LD4       |_|   |                 |  O LD4       |_|   |         |
|        |                    |                 |                    |         |
|        |             GND O--|-----------------|--O GND             |         |
|        |____________________|                 |____________________|         |
|                                                                              |
|                                                                              |
*------------------------------------------------------------------------------*
@endverbatim

@note
- The connection between the pins should use a common Ground.

- Software Description

On Board A, at each joystick buttons press:
- The USART Board A sends the specific command to the USART Board B (the command 
  contains the transaction code (CMD_RIGHT, CMD_LEFT, CMD_UP, CMD_DOWN or CMD_SEL)
  followed by the number of data to be transmitted (CMD_RIGHT_SIZE, CMD_LEFT_SIZE, 
  CMD_UP_SIZE, CMD_DOWN_SIZE or CMD_SEL_SIZE)

- The USART Board B receives the command and sends the CMD_ACK command to the USART board A

- The USART Board A receives the CMD_ACK command and sends the number of bytes 
  from TxBuffer to the USART Board B.

- The USART Board B compares the number of bytes received with the defined ones into
  his TxBuffer.
  
  Received data correctness is signaled by LED lightening and though as follow:
   - Joystick RIGHT and data correctly received ==> LD2, LD3 ON and LD4 OFF 
   - Joystick LEFT and data correctly received  ==> LD4 ON, LD2 and LD3 are OFF
   - Joystick UP and data correctly received    ==> LD2 ON, LD3 and LD4 are OFF
   - Joystick DOWN and data correctly received  ==> LD3 ON, LD2 and LD4 are OFF
   - Joystick SEL and data correctly received   ==> LD2, LD3 and LD4 are ON

The steps described above can be also initiated and ensured by Board B. 

In both boards(Board A or Board B), the data transfers is managed using USARTx_IRQHandler 
in FT32F030X8_it.c file when USARTx is used.

The SysTick is configured to generate interrupt each 10ms. A dedicated counter 
inside the SysTick ISR is used to toggle the LD1 each 100ms indicating that the 
firmware is running.
A defined communication timeout is insuring that the application will not remain 
stuck if the USART communication is corrupted.
You can adjust this timeout through the USER_TIMEOUT  define inside main.h file
depending on CPU frequency and application conditions (interrupts routines, 
number of data to transfer, baudrate, CPU frequency...).

These operations can be repeated infinitely.


         
@par Hardware and Software environment

  - This example runs on FT32f0xx devices.
  
  - This example has been tested with FMD FT32F030XX-EVAL and
    FT32F072X8-EVAL 

  - FT32F030XX-EVAL Set-up
    - Connect USART1 TX pin (PA.09) to USARTx RX pin
    - Connect USART1 RX pin (PA.10) to USARTx TX pin
    - Connect GND pins of two boards  
    - JP3 should be in 5-6 position
    
  - FT32F072X8-EVAL Set-up
    - Connect USART2 TX pin (PA.02) to USARTx RX pin
    - Connect USART2 RX pin (PA.03) to USARTx TX pin
    - Connect GND pins of two boards 
    - JP17 should be in 5-6 position


@par How to use it ? 

In order to make the program work, you must do the following :
 - use USE_FT32F030XX_EVAL mcro
 - add FT32F030XX_eval.c to prj
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

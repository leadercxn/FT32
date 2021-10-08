/**
  ******************************************************************************
  * @file    SPI/SPI_TwoBoards/DataExchangeInterrupt/readme.txt  
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
to trigger SPI communication using interrupts and though using SPI firmware 
library.

- Hardware Description

To use this example, you need to load it on two FT32 boards (let's call them 
Board A and Board B) then connect these two boards through SPI lines and GND.

In the firmware example uncomment the dedicated line in the main.h file to use
the SPI peripheral as FT32 Master device or as FT32 Slave.

The size of transferred data can be configured by uncomment the dedicated size in main.h
file. the same data size must be selected in both boards.

@verbatim
*------------------------------------------------------------------------------*
|                BOARD A                                BOARD B                |
|         ____________________                   ____________________          |
|        |                    |                 |                    |         |
|        |                    |                 |                    |         | 
|        |     __________     |                 |     __________     |         |
|        |    |SPI Master|____|_______SCK_______|____|SPI Slave |    |         |
|        |    |  Device  |____|_______MISO______|____|  Device  |    |         |
|        |    |__________|____|_______MOSI______|____|__________|    |         |
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
- The connection between the pins should use a short wires and a common Ground. 

- Software Description

In master board, SPI peripheral is configured as Master full duplex with Interrupt,
whereas in Slave board, SPI peripheral is configured as Slave Full duplex with Interrupt. 

At each joystick buttons press:
- The Master sends the specific command to the Slave and waits for the ACK command 
  from the Slave

- The Master sends the specific command to the Slave (the command contains the 
  transaction code (CMD_RIGHT, CMD_LEFT, CMD_UP, CMD_DOWN or CMD_SEL) and receives 
  the ACK command from the Slave.

- The Slave receives the command and sends the ACK command.

- The Master sends the defined NumberOfByte from TxBuffer to the Slave and receives
  NumberOfByte from the Slave into Rxbuffer.
  
- The Slave sends the defined NumberOfByte from Txbuffer to the Master and receives 
  NumberOfByte from the Master into Rxbuffer.
  

- The Master compares the received data with TxBuffer and check the ACK command, 
  Received data correctness is signaled by LED lightening and though as follow:
   - Joystick JOY_RIGHT and data correctly received ==> LD2, LD3 ON and LD4 OFF 
   - Joystick JOY_LEFT and data correctly received  ==> LD4 ON, LD2 and LD3 are OFF
   - Joystick JOY_UP and data correctly received    ==> LD2 ON, LD3 and LD4 are OFF
   - Joystick JOY_DOWN and data correctly received  ==> LD3 ON, LD2 and LD4 are OFF
   - Joystick JOY_SEL and data correctly received   ==> LD2, LD3 and LD4 are ON
   
- The Slave after check the received command, compares the received data with TxBuffer. 
  Received data correctness is signaled by LED lightening and though as follow:
   - Received command CMD_RIGHT and data correctly received --> LD2 and LD3 ON and LD4 OFF 
   - Received command CMD_LEFT and data correctly received  --> LD2 ON, LD3 and LD4 are OFF
   - Received command CMD_UP and data correctly received    --> LD2 ON, LD3 and LD4 are OFF
   - Received command CMD_DOWN and data correctly received  --> LD3 ON, LD2 and LD4 are OFF
   - Received command CMD_SEL and data correctly received   --> LD2, LD3 and LD4 leds ON

In both boards, the data transfers is managed using SPI1_IRQHandler in FT32F030X8_it.c 
file.

The SysTick is configured to generate interrupt each 10ms. A dedicated counter 
inside the SysTick ISR is used to toggle the LD1 each 100ms indicating that the 
firmware is running.

A defined communication timeout is insuring that the application will not remain 
stuck if the SPI communication is corrupted.
You can adjust this timeout through the USER_TIMEOUT  define inside main.h file
depending on CPU frequency and application conditions (interrupts routines, 
number of data to transfer, baudrate, CPU frequency...).

These operations can be repeated infinitely.




         
@par Hardware and Software environment

  - This example runs on FT32f0xx devices.
  
  - This example has been tested with FMD FT32F030XX-EVAL and
    FT32F072X8-EVAL

  - FT32F030XX-EVAL Set-up
      - Use LED1, LED2, LED3 and LED4 connected respectively PC.10, PC.11, PC.12 
         and PD.02 pins for each eval boards.
      - Use The Joystick push buttons 
         - DOWN[PC.07]
         - UP[PC.06]
         - LEFT[PC.09]
         - RIGHT[PC.08] 
         - SEL[PA.00]
     - Connect SPI1 SCK pin (PA.05) to SPI SCK pin
     - Connect SPI1 MISO pin (PB.04) to SPI MISO pin
     - Connect SPI1 MOSI pin (PA.07) to SPI MOSI pin
     - Connect GND pins of two boards. 
  - FT32F072X8-EVAL Set-up
      - Use LED1, LED2, LED3 and LED4 connected respectively PD.08, PD.09, PD.10 
        and PD.11 pins for each eval boards.
      - Use The Joystick push buttons 
         - DOWN[PF.10]
         - UP[PF.09]
         - LEFT[PE.02]
         - RIGHT[PE.03] 
         - SEL[PA.00]
      - Connect SPI1 SCK pin (PB.03) to SPI SCK pin
      - Connect SPI1 MISO pin (PE.15) to SPI MISO pin
      - Connect SPI1 MOSI pin (PE.14) to SPI MOSI pin
      - Connect GND pins of two boards.


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

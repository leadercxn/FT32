/**
  ******************************************************************************
  * @file    SPI/SPI_TwoBoards/DataExchangeDMA/readme.txt  
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
to trigger SPI communications using DMA and though using SPI firmware library.

- Hardware Description

To use this example, you need to load it on two STM32 boards (let's call them 
Board A and Board B) then connect these two boards through SPI lines and GND.
In the FT32 master board (Board A), connect the timer output capture compare 
channel into NSS line.  
In the firmware example uncomment the dedicated line in the main.h file to use
the SPI peripheral as STM32 Master device or as FT32 Slave.

@verbatim
*------------------------------------------------------------------------------*
|                BOARD A                                BOARD B                |
|         ____________________                   ____________________          |
|        |                    |                 |                    |         |
|        |                    |                 |                    |         | 
|        |     __________ ____|_______SCK_______|____ __________     |         |
|        |    |SPI Master|____|_______MOSI______|____|SPI Slave |    |         |
|        |    |  Device  |____|_______MISO______|____|  Device  |    |         |
|        |    |__________|____|_______NSS_______|____|__________|    |         |
|        |                    |   |             |                    |         |
|        |  O LD1  TIM_CHx O__|___|             |  O LD1             |         |
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

In master board, SPI peripheral is configured as Master full duplex with DMA
and NSS hardware mode.
The TIM2 is configured to generate 4KHz PWM signal with 50% duty cycle on TIM2_CH2 
pin (PA.01), this signal is used as DMA trigger and as NSS signal input to latch
the SPI data transfers. Whereas in Slave board, SPI peripheral is configured as 
Slave Full duplex with DMA and NSS hardware mode.

At each joystick buttons press:
- The Master sends the specific command to the Slave using the TIM2_CH2 DMA 
  request (DMA1_Channel3)(the command contains the transaction code (CMD_RIGHT, 
  CMD_LEFT, CMD_UP, CMD_DOWN or CMD_SEL) and receives the ACK command from the 
  Slave using SPI_Rx DMA request(DMA1_Channel2) 

- The Slave receives the command using SPI_Rx DMA request(DMA1_Channel2) and sends 
  the ACK command using the SPI_Tx DMA request (DMA1_Channel3).

- The Master sends the defined NumberOfByte from TxBuffer using the TIM2_CH2 DMA 
  request (DMA1_Channel3) to the Slave and receives NumberOfByte from the Slave 
  using SPI_Rx DMA request(DMA1_Channel2) into Rxbuffer.

- The Slave sends the defined NumberOfByte from Txbuffer using the SPI_Tx DMA 
  request (DMA1_Channel3) to the Master and receives NumberOfByte from the Master 
  using SPI_Rx DMA request(DMA1_Channel2) into Rxbuffer.

- The Master compares the NumberOfByte received data with the defined ones into 
  TxBuffer and check the ACK command, received data correctness is signaled by LD 
  lightening and though as follow:
   - Joystick JOY_RIGHT and data correctly received ==> LD2 and LD3 ON and LD4 OFF 
   - Joystick JOY_LEFT and data correctly received  ==> LD4 ON, LD2 and LD3 are OFF
   - Joystick JOY_UP and data correctly received    ==> LD2 ON, LD3 and LD4 are OFF
   - Joystick JOY_DOWN and data correctly received  ==> LD3 ON, LD2 and LD4 are OFF
   - Joystick JOY_SEL and data correctly received   ==> LD2, LD3 and LD4 leds ON

- The Slave compares the NumberOfByte received data with the defined ones into 
  TxBuffer and check the received command,Received data correctness is signaled 
  by LED lightening and though as follow:
   - Received command CMD_RIGHT and data correctly received ==> LD2 and LD3 ON and LD4 OFF 
   - Received command CMD_LEFT and data correctly received  ==> LD2 ON, LD3 and LD4 are OFF
   - Received command CMD_UP and data correctly received    ==> LD2 ON, LD3 and LD4 are OFF
   - Received command CMD_DOWN and data correctly received  ==> LD3 ON, LD2 and LD4 are OFF
   - Received command CMD_SEL and data correctly received   ==> LD2, LD3 and LD4 leds ON


In both boards, the SPI is configured to use the slave hardware management to 
manage the NSS pin.
 
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
     - Connect SPI1 NSS pin (PA.15) to SPI NSS pin
     - Connect TIM2_CH2 pin (PA.01) to SPI1 NSS pin (PA.15) (On master board only to trigger the DMA transfers)
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
      - Connect SPI1 NSS pin (PA.15) to SPI NSS pin (PA.15)
      - Connect TIM2_CH2 pin (PA.01) to SPI1 NSS pin (PA.15) (On master board only to trigger the DMA transfers)
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

 /**
  ******************************************************************************
  * @file    RTC/RTC_Calendar/readme.txt 
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

This example demonstrates and explains how to use the RTC peripheral.
As an application example, it demonstrates how to setup the RTC peripheral, in 
terms of prescaler and interrupts, to be used to keep time and to generate 
alarm interrupt. 

One of the following clock source can be used as RTC clock source (uncomment the
corresponding define in main.c): 
  - LSE oscillator clock usually delivered by a 32.768 kHz quartz.
  - LSI oscillator clock




    - Hyperterminal configuration:
      - Word Length = 8 Bits
      - One Stop Bit
      - No parity
      - BaudRate = 115200 baud
      - flow control: None
      


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

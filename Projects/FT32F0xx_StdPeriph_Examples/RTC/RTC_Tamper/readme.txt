 /**
  ******************************************************************************
  * @file    RTC/RTC_Tamper/readme.txt 
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

This example shows how to write/read data to/from RTC Backup data registers and 
demonstrates the Tamper detection feature.

One from the following clock can be used as RTC clock source (uncomment the
corresponding define in main.c):
  - LSE oscillator clock usually delivered by a 32.768 kHz quartz.
  - LSI oscillator clock

The associated firmware performs the following:
1. It configures the Tamper pin to be falling edge, and enables the Tamper interrupt.
2. It use LED2 output,  as tamper source,  so  you can connect LED2 to Tamper input(PC13) 
3. LED4 output signal  in RTC interrupt routine
 



         
@par Hardware and Software environment

  - This example runs on FT32f0xx devices.
  
  - This example has been tested with FMD FT32F030XX-EVAL and
    FT32F072X8-EVAL

  - FT32F030XX-EVAL Set-up
    - Use Tamper button.
  - FT32F072X8-EVAL Set-up
    - Use Tamper button.


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

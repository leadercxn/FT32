  /**
  ******************************************************************************
  * @file    RTC/RTC_LSI/readme.txt 
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

This example demonstrates and explains how to use the LSI clock source auto
calibration to get a precise RTC clock. 
As an application example, it demonstrates how to configure the TIM14 timer
internally connected to LSI clock output, in order to adjust the RTC prescaler. 

The Low Speed Internal (LSI) clock is used as RTC clock source.
After reset, the RTC prescaler (asynchronous and synchronous) is set with the 
default LSI frequency (40KHz).
The RTC Alarm is configured to generate an interrupt each 1s. LED1 is toggled 
inside the RTC WakeUp interrupt each 1s.

The inaccuracy of the LSI clock causes the RTC Alarm Interrupt to be inaccurate.
The RTC CK_SPRE signal can be monitored by LED1 which is toggled into the RTC 
Alarm_A interrupt service routine.

The program waits until TAMPER Push button is pressed to begin the auto calibration 
procedure:
 - Configure the TIM14 to remap internally the TIM14 Channel 1 Input Capture to 
   the LSI clock output.
 - Enable the TIM14 Input Capture interrupt: after one cycle of LSI clock, the
   period value is stored in a variable and compared to the HCLK clock to get
   its real value.
 - The RTC prescaler is adjusted with this LSI frequency value so that the RTC
   CK_SPRE value become more accurate.
 - When calibration is done LED2 is turned ON to indicate the end of this operation.

 



         
@par Hardware and Software environment

  - This example runs on FT32f0xx devices.
  
  - This example has been tested with FMD FT32F030XX-EVAL and
    FT32F072X8-EVAL

  - FT32F030XX-EVAL Set-up
    - Use TAMPER push button for RTC calibration
    
  - FT32F072X8-EVAL Set-up
    - Use TAMPER push button for RTC calibration

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

   /**
  ******************************************************************************
  * @file    PWR/PWR_STANDBY/readme.txt 
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


@par PWR/PWR_STANDBY example Description 

This example shows how to enter the system to STANDBY mode and wake-up from this
mode either with the RESET or using RTC Alarm.

In the associated software, the system clock is set to 48 MHz, the SysTick is programmed
to generate an interrupt each 250 ms. In the SysTick interrupt handler, the LED3 is
toggled, this is used to indicate whether the MCU is in STANDBY or RUN mode.

When a falling edge is detected on the PC13(pressing on tamper button), the RTC is 
configured to generate an Alarm event in 3 seconds then the system enters STANDBY 
mode causing the LED3 to stop toggling. 
An external RESET will wake-up the system from STANDBY. If within 3 seconds an 
external RESET is not generated, the RTC Alarm will wake-up the system. 

After wake-up from STANDBY mode, program execution restarts in the same way as after
a RESET, the LED3 is toggling again,the RTC configuration(clock source, enable, prescaler,...) 
is kept.
As result there is no need to configure the RTC.

Led LED3 is used to monitor the system state as following:
 - LED3 toggling: system in RUN mode
 - LED3 off : system in STANDBY mode
 
To cope with the LSI clock inaccuracy, routine of LSI measurement is implemented as follow:
 - Configure the TIM14 to remap internally the TIM14 Channel 1 Input Capture to 
   the LSI clock output.
 - Enable the TIM14 Input Capture interrupt: after one cycle of LSI clock, the
   period value is stored in a variable and compared to the HCLK clock to get
   its real value.
 - The RTC prescaler is adjusted with this LSI frequency value so that the RTC
   CK_SPRE value become more accurate.



      
@par Hardware and Software environment

  - This example runs on FT32f0xx devices.
  
  - This example has been tested with FMD FT32F030XX-EVAL and
    FT32F072X8-EVAL

    - Use the Tamper push-button connected to PC13 pin


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

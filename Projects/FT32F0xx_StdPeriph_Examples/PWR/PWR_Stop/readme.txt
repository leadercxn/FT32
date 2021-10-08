  /**
  ******************************************************************************
  * @file    PWR/PWR_STOP/readme.txt 
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

@par PWR_Stop Example Description 

This example shows how to enter the system to STOP mode and wake-up using EXTI
Line interrupts. The EXTI Line sources are PC13 and RTC Alarm.

The EXTI line13 is configured to generate interrupt on falling edge.
The EXTI line17(RTC Alarm) is configured to generate interrupt on rising edge.

The system enters and exits STOP mode as follow:
After system start-up, the RTC is configured to generate an Alarm event then the 
system enters STOP mode. To wake-up from STOP mode you have to apply a falling
edge on EXTI line13, otherwise the  RTC Alarm will wake-up the system within 5 
seconds. After exit from STOP, the system clock is reconfigured to its previous 
state (as HSE and PLL are disabled in STOP mode).
Then, after a delay the system will enter again in STOP mode and exit in the way
described above. This behavior is repeated in an infinite loop.

Three leds are used to monitor the system state as follow:
 - LED1 ON: system in RUN mode
 - LED1, LED2 and LED4 OFF: system in STOP mode
 - LED2 ON if EXTI Line13 is used to exit from STOP
 - LED4 ON if EXTI line17(RTC Alarm) is used to exit from STOP 
 @note To measure the current consumption in STOP mode, please refer to 
      @subpage PWR_CurrentConsumption example.




      
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

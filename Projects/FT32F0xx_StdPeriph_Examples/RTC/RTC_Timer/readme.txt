 /**
  ******************************************************************************
  * @file    RTC/RTC_Timer/readme.txt 
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

  This example provides a short description of how to use the RTC peripheral’s with 
  Alarm sub seconds feature to simulate a timer with refresh time equal to 250 ms
  (1 second/ 8) * 2).
  The RTC is configured to generate sub seconds interrupt each 125ms (will have
  8 interrupt per 1 second).
  
  For this example an interactive human interface is developed using
  FT320xx_EVAL’s LCD and Push Buttons to allow user to use Timer with a real 
  progress bar display.

  After startup, the timer is equal to 1 Minute (60 Seconds) and by pressing on
  the Tamper button the progress bar start to be filled for each 2 successive
  interrupts (after each 250ms).
  After 480 interrupts (60 * 8) the progress bar will be full.

  User can manipulate the chronometer features using the Tamper and Wakeup buttons:
    - press Sel button to Start the timer.
    - press Tamper button to stop the timer.

 

 
       
@par Hardware and Software environment 

  - This example runs on FT32f0xx Devices.
  
  - This example has been tested with FMD FT32F030XX-EVAL and
    FT32F072X8-EVAL

  - FT32F030XX-EVAL Set-up
    - Use SEL push button. 
    - Use the TAMPER push button connected to PC.13 pin (EXTI Line13).
    
  - FT32F072X8-EVAL Set-up
    - Use SEL push button. 
    - Use the TAMPER push button connected to PC.13 pin (EXTI Line13).

       
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

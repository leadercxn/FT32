  /**
  ******************************************************************************
  * @file    RTC/RTC_StopWatch/readme.txt 
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

  This example illustrates how to use the FT32f0xx new RTC's sub-seconds and
  Tamper feature (Filter, sampling) features. It simulates a precise chronometer
  with 2 record times possibilities stored in the Backup registers (2 registers
  for time (second, minutes and hours) and 2 registers for subsecond).
  
  For this example an interactive human interface is developed using
   LCD and Push Buttons to allow user to use StopWatch with real time display.

  After startup, a default 00:00:00:000 chronometer counter is displayed on the 
  LCD, it corresponds to [Hours]:[minutes]:[seconds]:[milliseconds].
  User can manipulate the chronometer features using Joystick LEFT, RIGHT and Tamper buttons:
    - press Joystick LEFT  button to start counter.
    - press Joystick RIGHT button to save trials in the backup registers (max 5 actions).
    - press and hold Tamper button for 1 sec to reset all the backup registers.
 



         
@par Hardware and Software environment

  - This example runs on FT32f0xx devices.
  
  - This example has been tested with FMD FT32F030XX-EVAL and
    FT32F072X8-EVAL

  - FT32F030XX-EVAL Set-up
    - Use Joystick LEFT and RIGHT button
    - Use Tamper button
    
  - FT32F072X8-EVAL Set-up
    - Use Joystick LEFT and RIGHT button
    - Use Tamper button

@par How to use it ? 

In order to make the program work, you must do the following :
 - use USE_FT32F030XX_EVAL mcro
 - add FT32F030XX_eval_lcd.c to prj
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

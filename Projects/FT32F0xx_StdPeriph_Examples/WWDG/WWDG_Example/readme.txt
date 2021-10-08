    /**
  ******************************************************************************
  * @file    WWDG/WWDG_Example/readme.txt 
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

@par  Example Description 

This example shows how to update at regular period the WWDG counter and how to
simulate a software fault generating an MCU WWDG reset on expiry of a programmed 
time period.

The WWDG timeout is set to 43.7 ms and the refresh window is set to 80. 
The WWDG counter is refreshed each 33 ms in the main program infinite loop to 
prevent a WWDG reset.
LED2 is also toggled each 33 ms indicating that the program is running.

An EXTI Line is connected to a GPIO pin, and configured to generate an interrupt
on the rising edge of the signal.

The EXTI Line is used to simulate a software failure: once the EXTI Line event 
occurs, by pressing the Tamper push-button, the corresponding interrupt is served.
In the ISR, a write to invalid address generates a Hardfault exception containing
an infinite loop and preventing to return to main program (the WWDG counter is 
not refreshed).
As a result, when the WWDG counter falls to 63, the WWDG reset occurs.
If the WWDG reset is generated, after the system resumes from reset, LED1 turns on.

If the EXTI Line event does not occur, the WWDG counter is indefinitely refreshed
in the main program infinite loop, and there is no WWDG reset. 




      
@par Hardware and Software environment

  - This example runs on FT32f0xx devices.
  

  - FT32F030XX-EVAL Set-up
    - Use the Tamper push-button connected to PC13 pin  
    
  - FT32F072X8-EVAL Set-up  
    - Use the Tamper push-button connected to PC13 pin



@par How to use it ? 

In order to make the program work, you must do the following :
 - Copy all source files from this example folder to the template folder under
   Project\FT32f0xx_StdPeriph_Templates
 - Open your preferred toolchain 
 - If the used device is FT32F030XX
    - Add the following files to the project source list
       - Utilities\FT32_EVAL\FT32F030XX_EVAL\FT32F030XX_eval.c
 - If the used device is FT32F072XX
    - Add the following files to the project source list
       - Utilities\FT32_EVAL\FT32F072X8_EVAL\FT32F072X8_eval.c
 - Rebuild all files and load your image into target memory
 - Run the example

        
 * <h3><center>&copy; COPYRIGHT FMD</center></h3>
 */

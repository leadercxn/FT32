    /**
  ******************************************************************************
  * @file    IWDG/IWDG_Reset/readme.txt 
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

This example shows how to update at regular period the IWDG reload counter and 
how to simulate a software fault generating an MCU IWDG reset on expiry of a 
programmed time period.

When "LSI_TIM_MEASURE" define is enabled in main.h, TIM14 is configured to measure
the LSI frequency as the LSI is internally connected to TIM14 CH1, in order to adjust
the IWDG prescaler to have accurate timeout.
The LSI measurement using the TIM14 is described below:
 - Configure the TIM14 to remap internally the TIM14 Channel 1 Input Capture to 
   the LSI clock output.
 - Enable the TIM14 Input Capture interrupt: after one cycle of LSI clock, the
   period value is stored in a variable and compared to the HCLK clock to get
   its real value. 

When "LSI_TIM_MEASURE" define is disabled, the LSI frequency is set to 40 KHz,
which will generate less accurate IWDG timeout.

Then, the IWDG reload counter is configured to obtain a time out of 250 ms(the timeout
may varies due to LSI frequency dispersion).

The IWDG reload counter is refreshed each 220 ms in the main program infinite loop 
to prevent a IWDG reset. LED2 is also toggled each 220 ms indicating that the program
is running.

An EXTI Line is connected to a GPIO pin, and configured to generate an interrupt
on the rising edge of the signal.
The EXTI Line is used to simulate a software failure: once the EXTI Line event 
occurs, by pressing the Tamper push-button, the corresponding interrupt is served.
In the ISR, a write to invalid address generates a Hardfault exception containing
an infinite loop and preventing to return to main program (the IWDG reload counter 
is not refreshed).
As a result, when the IWDG counter reaches 00h, the IWDG reset occurs.
If the IWDG reset is generated, after the system resumes from reset, LED1 turns on.

If the EXTI Line event does not occur, the IWDG counter is indefinitely refreshed
in the main program infinite loop, and there is no IWDG reset.




      
@par Hardware and Software environment

  - This example runs on FT32f0xx devices.
  

  - FT32F030XX-EVAL Set-up
     - Use the Tamper Button push button   
     
  - FT32F072X8-EVAL Set-up  
     - Use the Tamper Button push button

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

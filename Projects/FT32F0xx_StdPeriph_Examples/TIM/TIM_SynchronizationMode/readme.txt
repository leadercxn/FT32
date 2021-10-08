/**
  ******************************************************************************
  * @file    TIM/TIM_SynchronizationMode/readme.txt 
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

This example shows how to synchronize TIM peripherals in cascade mode, two timers
TIM1 and TIM3 are used.

Timers synchronisation in cascade mode:

 - TIM1 is configured as Master Timer:
     - PWM Mode is used
     - The TIM1 Update event is used as Trigger Output

 - TIM3 is slave for TIM1
     - PWM Mode is used
     - The ITR1(TIM1) is used as input trigger 
     - Gated mode is used, so start and stop of slave counter are controlled by
       the Master trigger output signal(TIM1 update event).

The TIM1 counter clock is 48 MHz.

  The TIM1 is running at:
  TIM1 frequency = (TIM1 counter clock)/ (TIM1 period + 1) = 187.5 KHz 
  and the duty cycle = TIM1_CCR1/(TIM1_ARR + 1) = 25%.

  The slave Timer TIM3 is running at TIM1 clock:
  (TIM1 frequency)/ (TIM3 period + 1) = 46.87 KHz and a duty cycle equal 
  to TIM3_CCR1/(TIM3_ARR + 1) = 25%



         
@par Hardware and Software environment

  - This example runs on FT32f0xx devices.
  

  - FT32F030XX-EVAL Set-up
     - Connect the following pins to an oscilloscope to monitor the different 
      waveforms:
        - TIM1 CH1 (PA.08) 
        - TIM3 CH1 (PB.04)
  - FT32F072X8-EVAL Set-up
     - Connect the following pins to an oscilloscope to monitor the different 
      waveforms:
        - TIM1 CH1 (PA.08) 
        - TIM3 CH1 (PB.04)


@par How to use it ? 

In order to make the program work, you must do the following :
 - Copy all source files from this example folder to the template folder under
   Project\FT32f0xx_StdPeriph_Templates
 - Open your preferred toolchain 
 - Select the appropriate workspace 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT FMD</center></h3>
 */

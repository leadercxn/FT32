   
  /**
  ******************************************************************************
  * @file    TIM/TIM_OnePulse/readme.txt 
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

This example shows how to use the TIM peripheral to generate a One pulse Mode 
after a Rising edge of an external signal is received in Timer Input pin.

TIM2CLK = SystemCoreClock, we want to get TIM2 counter clock at 24 MHz:
  - Prescaler = (TIM2CLK / TIM2 counter clock) - 1

SystemCoreClock is set to 48 MHz.

The Autoreload value is 65535 (TIM2->ARR), so the maximum frequency value to 
trigger the TIM2 input is 24000000/65535 = 366.2 Hz.

The TIM2 is configured as follows: 
The One Pulse mode is used, the external signal is connected to TIM2 CH2 pin (PA.01), 
the rising edge is used as active edge, the One Pulse signal is output 
on TIM2_CH1 (PA.05).

The TIM_Pulse defines the delay value, the delay value is fixed to:
delay =  CCR1/TIM2 counter clock = 16383 / 24000000 = 682.6 us. 
The (TIM_Period - TIM_Pulse) defines the One Pulse value, the pulse value is fixed to:
One Pulse value = (TIM_Period - TIM_Pulse)/TIM2 counter clock 
                = (65535 - 16383) / 24000000 = 2.04 ms.
 



  - FT32F030XX-EVAL Set-up
    - Connect the external signal to the TIM3_CH2 pin (PA.07)  rising signal
    - Connect the TIM3_CH1 (PA.06) pin to an oscilloscope to monitor the waveform.
  - FT32F072X8-EVAL Set-up
    - Connect the external signal to the TIM3_CH2 pin (PA.07)
    - Connect the TIM3_CH1 (PA.06) pin to an oscilloscope to monitor the waveform.



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

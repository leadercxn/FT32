     /**
  ******************************************************************************
  * @file    TIM/TIM_7PWMOutputs/readme.txt 
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

This example shows how to configure the TIM1 peripheral to generate 7 PWM signals 
with 4 different duty cycles (50%, 37.5%, 25% and 12.5%).

TIM1CLK = SystemCoreClock, Prescaler = 0, TIM1 counter clock = SystemCoreClock
SystemCoreClock is set to 48 MHz for FT32f0xx devices.

The objective is to generate 7 PWM signal at 17.57 KHz:
  - TIM1_Period = (SystemCoreClock / 17570) - 1
The channel 1 and channel 1N duty cycle is set to 50%
The channel 2 and channel 2N duty cycle is set to 37.5%
The channel 3 and channel 3N duty cycle is set to 25%
The channel 4 duty cycle is set to 12.5%
The Timer pulse is calculated as follows:
  - ChannelxPulse = DutyCycle * (TIM1_Period - 1) / 100

The TIM1 waveform can be displayed using an oscilloscope.



         
@par Hardware and Software environment

  - This example runs on FT32f0xx devices.
  

  - FT32F0Discovery board Set-up
     - Connect the TIM1 pins to an oscilloscope to monitor the different waveforms:
        - TIM1_CH1  pin (PA.08)
        - TIM1_CH1N pin (PA.07)
        - TIM1_CH2  pin (PA.09)
        - TIM1_CH2N pin (PB.00)
        - TIM1_CH3  pin (PA.10)
        - TIM1_CH3N pin (PB.01)
        - TIM1_CH4  pin (PA.11)
  - FT32F072X8-EVAL Set-up
     - Connect the TIM1 pins to an oscilloscope to monitor the different waveforms:
        - TIM1_CH1  pin (PA.08)
        - TIM1_CH1N pin (PA.07)
        - TIM1_CH2  pin (PA.09)
        - TIM1_CH2N pin (PB.00)
        - TIM1_CH3  pin (PA.10)
        - TIM1_CH3N pin (PB.01)
        - TIM1_CH4  pin (PA.11)


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

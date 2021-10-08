 /**
  ******************************************************************************
  * @file    TIM/TIM_DMABurst/readme.txt 
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

This example shows how to update the TIM1 channel1 period and the duty cycle 
using the TIM DMA burst feature.

Every update DMA request, the DMA will do 3 transfers of half words into Timer 
registers beginning from ARR register.
On the DMA update request, 0x0FFF will be transferred into ARR, 0x0000 
will be transferred into RCR, 0x0555 will be transferred into CCR1. 

The TIM1CLK frequency is set to SystemCoreClock (Hz), to get TIM1 counter
clock at 24 MHz the Prescaler is computed as following:
   - Prescaler = (TIM1CLK / TIM1 counter clock) - 1

SystemCoreClock is set to 48 MHz.

The TIM1 period is 5.8 KHz: TIM1 Frequency = TIM1 counter clock/(ARR + 1)
                                           = 24 MHz / 4096 = 5.8 KHz

The TIM1 CCR1 register value is equal to 0x555, so the TIM1 Channel 1 generates a 
PWM signal with a frequency equal to 5.8 KHz and a duty cycle equal to 33.33%:
TIM1 Channel1 duty cycle = (TIM1_CCR1/ TIM1_ARR + 1)* 100 = 33.33%

The PWM waveform can be displayed using an oscilloscope.
 


  
  - FT32F030XX-EVAL Set-up
    - Connect the following pins to an oscilloscope to monitor the different 
      waveforms:  
        - TIM1 CH1  (PA.08)
        
  - FT32F072X8-EVAL Set-up
    - Connect the following pins to an oscilloscope to monitor the different 
      waveforms:  
        - TIM1 CH1  (PA.08)


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

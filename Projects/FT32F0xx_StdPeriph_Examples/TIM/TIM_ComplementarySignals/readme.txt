  @verbatim
  /**
  ******************************************************************************
  * @file    GPIO/GPIO_IOToggle/readme.txt 
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
   @endverbatim



The objective is to generate PWM signal at 17.57 KHz:
  - TIM1_Period = (SystemCoreClock / 17570) - 1

The Three Duty cycles are computed as the following description: 
The channel 1 duty cycle is set to 50% so channel 1N is set to 50%.
The channel 2 duty cycle is set to 25% so channel 2N is set to 75%.
The channel 3 duty cycle is set to 12.5% so channel 3N is set to 87.5%.
The Timer pulse is calculated as follows:
  - ChannelxPulse = DutyCycle * (TIM1_Period - 1) / 100

A dead time equal to 11/SystemCoreClock is inserted between the different 
complementary signals, and the Lock level 1 is selected.
The break Polarity is used at High level.

The TIM1 waveform can be displayed using an oscilloscope.
 

         
@par Hardware and Software environment

  - This example runs on FT32f0xx devices.

         - TIM1_CH1  pin (PA.08)  
         - TIM1_CH1N pin (PA.07)  
         - TIM1_CH2  pin (PA.09)  
         - TIM1_CH2N pin (PB.00)  
         - TIM1_CH3  pin (PA.10)  
         - TIM1_CH3N pin (PB.01)
      - Connect the TIM1 break pin TIM1_BKIN pin (PB.12) to the GND. To generate a 
        break event, switch this pin level from 0V to 3.3V.




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

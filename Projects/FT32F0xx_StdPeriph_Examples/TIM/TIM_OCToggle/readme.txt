   
  /**
  ******************************************************************************
 * @file    TIM/TIM_OCToggle/readme.txt 
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

This example shows how to configure the TIM3 peripheral to generate four different 
signals with four different frequencies.

The TIM3CLK frequency is set to 48 MHz

The TIM3 CCR1 register value is equal to 40961: 
CC1 update rate = TIM3 counter clock / CCR1_Val = 1171.8Hz,
so the TIM3 Channel 1 generates a periodic signal with a frequency equal to 585.9Hz.

The TIM3 CCR2 register is equal to 20480:
CC2 update rate = TIM3 counter clock / CCR2_Val = 2343.75Hz
so the TIM3 channel 2 generates a periodic signal with a frequency equal to 1171.8Hz.

The TIM3 CCR3 register is equal to 10240:
CC3 update rate = TIM3 counter clock / CCR3_Val = 4687.5Hz
so the TIM3 channel 3 generates a periodic signal with a frequency equal to 2343.75Hz.

The TIM3 CCR4 register is equal to 5120:
CC4 update rate = TIM3 counter clock / CCR4_Val =  9375Hz
so the TIM3 channel 4 generates a periodic signal with a frequency equal to 4687.5Hz.
 




  - FT32F0XX Discovery board Set-up
    - Connect the following pins to an oscilloscope to monitor the different 
      waveforms:
       - PA.06 (TIM3_CH1)
       - PA.07 (TIM3_CH2)
       - PB.00 (TIM3_CH3)
       - PB.01 (TIM3_CH4)
  
  - FT32F072X8-EVAL Set-up
    - Connect the following pins to an oscilloscope to monitor the different 
      waveforms:
       - PA.06 (TIM3_CH1)
       - PA.07 (TIM3_CH2)
       - PB.00 (TIM3_CH3)
       - PB.01 (TIM3_CH4)


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

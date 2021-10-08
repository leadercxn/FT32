   
  /**
  ******************************************************************************
  * @file    TIM/TIM_OCActive/readme.txt 
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

This example shows how to configure the TIM peripheral to generate four different 
signals with four different delays.

The TIM3CLK frequency is set to SystemCoreClock (Hz), and the objective is
to get TIM3 counter clock at 1 KHz so the Prescaler is computed as following:
   - Prescaler = (TIM3CLK / TIM3 counter clock) - 1
   
SystemCoreClock is set to 48 MHz for FT32f0xx Devices.

The TIM3 CCR1 register value is equal to 1000:
TIM3_CH1 delay = CCR1_Val/TIM3 counter clock  = 1000 ms
so the TIM3 Channel 1 generates a signal with a delay equal to 1000 ms.

The TIM3 CCR2 register value is equal to 500:
TIM3_CH2 delay = CCR2_Val/TIM3 counter clock = 500 ms
so the TIM3 Channel 2 generates a signal with a delay equal to 500 ms.

The TIM3 CCR3 register value is equal to 250:
TIM3_CH3 delay = CCR3_Val/TIM3 counter clock = 250 ms
so the TIM3 Channel 3 generates a signal with a delay equal to 250 ms.

The TIM3 CCR4 register value is equal to 125:
TIM3_CH4 delay = CCR4_Val/TIM3 counter clock = 125 ms
so the TIM3 Channel 4 generates a signal with a delay equal to 125 ms.

The delay correspond to the time difference between PG.06 and  TIM3_CHx signal
rising edges.
 


  - FT32F0Discovery board Set-up
    - Connect the following pins to an oscilloscope to monitor the different 
      waveforms:
       - Use LED1 connected to PC.10
       - PA.06 (TIM3_CH1)
       - PA.07 (TIM3_CH2)
       - PB.00 (TIM3_CH3)
       - PB.01 (TIM3_CH4)
  - FT32F072X8-EVAL Set-up
    - Connect the following pins to an oscilloscope to monitor the different 
      waveforms:
       - Use LED1 connected to PC.10
       - PA.06 (TIM3_CH1)
       - PA.07 (TIM3_CH2)
       - PB.00 (TIM3_CH3)
       - PB.01 (TIM3_CH4)

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

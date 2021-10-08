     /**
  ******************************************************************************
  * @file    TIM/TIM_TimeBase/readme.txt 
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

This example shows how to configure the TIM peripheral in Output Compare Timing 
mode with the corresponding Interrupt requests for each channel in order to generate
4 different time bases.

The TIM3CLK frequency is set to SystemCoreClock (Hz), to get TIM3 counter 
clock at 6 MHz so the Prescaler is computed as following:
   - Prescaler = (TIM3CLK / TIM3 counter clock) - 1

SystemCoreClock is set to 48MHz.

The TIM3 CC1 register value is equal to 40961, 
CC1 update rate = TIM3 counter clock / CCR1_Val = 146.48 Hz,
so the TIM3 Channel 1 generates an interrupt each 6.8ms

The TIM3 CC2 register is equal to 27309, 
CC2 update rate = TIM3 counter clock / CCR2_Val = 219.7 Hz
so the TIM3 Channel 2 generates an interrupt each 4.55ms

The TIM3 CC3 register is equal to 13654, 
CC3 update rate = TIM3 counter clock / CCR3_Val = 439.4Hz
so the TIM3 Channel 3 generates an interrupt each 2.27ms

The TIM3 CC4 register is equal to 6826, 
CC4 update rate = TIM3 counter clock / CCR4_Val =  878.9 Hz
so the TIM3 Channel 4 generates an interrupt each 1.13ms.

When the counter value reaches the Output compare registers values, the Output 
Compare interrupts are generated and, in the handler routine, 4 leds (LED1, LED2, 
LED3 and LED4) are toggled with the following frequencies: 

- LED1: 73.24Hz (CC1)
- LED2: 109.8Hz (CC2)
- LED3: 219.7Hz (CC3) 
- LED4: 439.4Hz (CC4)
 



         
@par Hardware and Software environment

  - This example runs on FT32f0xx devices.
  
  - This example has been tested with FMD FT32F030XX-EVAL and
    FT32F072X8-EVAL

  - FT32F030XX-EVAL Set-up
    -  Use LED1, LED2, LED3 and LED4 connected respectively to PC.10, PC.11, PC.12
      and PD.02 pins and connect them on an oscilloscope to show the different 
      Time Base signals.
  - FT32F072X8-EVAL Set-up
    -  Use LED1, LED2, LED3 and LED4 connected respectively to PD.08, PD.09, PD.10
      and PD.11 pins and connect them on an oscilloscope to show the different 
      Time Base signals.


@par How to use it ? 

In order to make the program work, you must do the following :
 - Copy all source files from this example folder to the template folder under
   Project\FT32f0xx_StdPeriph_Templates
 - Open your preferred toolchain 
 - If the used device is FTM32F0XX
    - Add the following files to the project source list
       - Utilities\FTM32_EVAL\FT32F030XX_EVAL\FT32F030XX_eval.c
 - If the used device is FTM32F072X8
    - Add the following files to the project source list
       - Utilities\FTM32_EVAL\FT32F072X8_EVAL\FT32F072X8_eval.c
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT FMD</center></h3>
 */

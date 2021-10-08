   
   /**
  ******************************************************************************
  * @file    TIM/TIM_InputCapture/readme.txt 
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



The TIM1 clock frequency is set to SystemCoreClock (Hz), the Prescaler is 0 so the 
TIM1 counter clock is SystemCoreClock (Hz).

SystemCoreClock is set to 48 MHz.

TIM1 is configured in Input Capture Mode: the external signal is connected to 
TIM1 Channel2 used as input pin.
To measure the frequency we use the TIM1 CC2 interrupt request,
so In the TIM1_CC_IRQHandler routine, the frequency of the external signal is computed. 
The "TIM1Freq" variable contains the external signal frequency:
TIM1Freq = TIM1 counter clock / Capture in Hz,
where the Capture is the difference between two consecutive TIM1 captures. 

The minimum frequency value to measure is 1100 Hz.
 


  - FT32F030XX-EVAL Set-up
    - Connect the external signal to measure to the TIM1 CH2 pin (PA.09).
    
  - FT32F072X8-EVAL Set-up
    - Connect the external signal to measure to the TIM1 CH2 pin (PA.09).



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

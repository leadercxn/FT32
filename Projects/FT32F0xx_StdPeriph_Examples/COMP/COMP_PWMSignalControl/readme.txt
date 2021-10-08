 /**
  ******************************************************************************
  * @file    COMP/COMP_PWMSignalControl/readme.txt 
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

This example shows how to configure COMP2 peripheral to hold on safe state
(low level) TIM1 channels as soon as COMP2 output is set at high level.

  - COMP2 is configured as following:
     - Inverting input is internally connected to VREFINT = 1.22V
     - Non Inverting input is connected to PA3
     - Output is internally connected to TIM2 BKIN (Break Input)

  - TIM1CLK is set to 48 MHz, the TIM1 Prescaler is equal to 0 so the TIM1 counter
    clock used is 48 MHz.
    TIM1 frequency is defined as follow:
    TIM1 channels frequency = TIM1 counter clock / (Period + 1) 
                            = 48000000 /(100 + 1) 
                            = 475 KHz.

  - External voltage should be connected to PA3 (RV3 potentiometer can be used).

  - Connect an oscilloscope to TIM1 channel PA8 to display waveform. 

  - While PA3 is lower than VREFINT (1.22V), PWM signal is displayed on PA8.
    While PA3 is higher than VREFINT, PA8 is in low level.
 



         
@par Hardware and Software environment

  - This example runs on FT32f0xx Devices.
  
  - This example has been tested with FMD FT32F030XX-EVAL and
    FT32F072X8-EVAL

  - FT32F030XX-EVAL Set-up
    - RV3 Potentiometer connected to PC.01 pin.
    - Connect PA.03 to PC.01 pin using a wire.
    - Connect an oscilloscope to PA.08 pin to display waveform.
  - FT32F072X8-EVAL Set-up
    - RV3 Potentiometer connected to PC.00 pin.
    - Connect PA.03 to PC.00 pin using a wire.
    - Connect an oscilloscope to PA.08 pin to display waveform.

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

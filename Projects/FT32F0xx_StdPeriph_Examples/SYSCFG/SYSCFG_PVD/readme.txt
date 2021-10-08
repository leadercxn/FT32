/**
  @page SYSCFG_PVD Programmable Voltage Detector (PVD) example
  
     /**
  ******************************************************************************
  * @file    SYSCFG/SYSCFG_PVD/readme.txt 
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

This example shows how to configure the programmable voltage detector.

In this example:
  - TIM1 is configured to generate a PWM signal on pin PA.08.
  - PVD threshold is configured to level 5.
   
While Vdd is higher than the PVD threshold (~2.68 V), PWM signal is displayed on PA.08.
While Vdd is lower than the PVD threshold (~2.58 V), PA8 is in low level.

@note   Refer to the electrical characteristics of your device datasheet for more
        details about the voltage threshold corresponding to each PVD detection level.





         
@par Hardware and Software environment

  - This example runs on FT32f0xx devices.
  
  - This example has been tested with FMD FT32F030XX-EVAL and
    FT32F072X8-EVAL 

  - FT32F030XX-EVAL Set-up
    - Use RV2 Potentiometer to adjust Vdd.
    - Make sure that jumper JP9 is in position(VDD_ADJ).
    - Connect an oscilloscope to PA.08 pin to display the waveform.
    
  - FT32F072X8-EVAL Set-up 
    - Use RV2 Potentiometer to adjust Vdd.
    - Make sure that jumper JP13 is in position(VDD_ADJ).
    - Connect an oscilloscope to PA.08 pin to display the waveform.



@par How to use it ? 

In order to make the program work, you must do the following :
 - Copy all source files from this example folder to the template folder under
   Project\FT32f0xx_StdPeriph_Templates
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT FMD</center></h3>
 */

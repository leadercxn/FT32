/**
  ******************************************************************************
  * @file    COMP/PulseWidthMeasurement/readme.txt 
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

This example shows how to configure the COMP2 peripheral to measure pulse width.
  This method (measuring signal pulse using comparator is interesting when
  external signal doesn't respect the VIL and VIH levels).

  - COMP2 is configured as follow:
     - Inverting input is internally connected to DAC1 output
     - Non Inverting input is connected to PA1
     - Output is internally connected to TIM2 Input Capture 4 (IC4)

  - DAC channel 1 is used as a digital threshold for measurement, DAC1 output
    is internally connected to COMP1 inverting input. 
    DAC1 is configured in 12-bit right alignment. DAC1 output = VREF * DOR / 4095
                                                               = 3.3 * 2000 / 4095
                                                               = 1.61V

    In this example, the pulse of an external signal of around 1.6V 
    (e.g. high level = 1.7V and low level = 1.5V) can be performed.

  - TIM2 counter is clocked by TIM2CLK = 48MHz, TIM2 channel 4 is configured in
    input capture mode.
    TIM2 counter is captured at each transition detection: rising or falling edges
    (each time COMP2 inverting input crosses DAC1 output)

  - External signal should be connected to PA1. 
    Pulse is computed in microsecond then displayed on Color LCD 
    for FT32F030XX-EVAL.
    Pulse duration shouldn't be higher than 65535 * TIM2CLK = 2.047 ms
    Pulse duration shouldn't be lower than TIM2 ISR processing time / TIM2CLK 
                                         ~ 110 (clock cycle) / 48 MHz = 2.3 us
 



         
@par Hardware and Software environment

  - This example runs on FT32f0xx Devices.
  
  - This example has been tested with FMD FT32F030XX-EVAL and
    FT32F072X8-EVAL

  - FT32F030XX-EVAL Set-up
    - Connect an external signal to PA.01 pin.
    
  - FT32F072X8-EVAL Set-up
    - Connect an external signal to PA.01 pin.

@par How to use it ? 

In order to make the program work, you must do the following :
 - Copy all source files from this example folder to the template folder under
   Project\FT32f0xx_StdPeriph_Templates
 - Open your preferred toolchain 
 - If the used device is FT32F030XX
    - Add the following files to the project source list
       - Utilities\FT32_EVAL\FT32F030XX_EVAL\FT32F030XX_eval.c
       - Utilities\FT32_EVAL\FT32F030XX_EVAL\FT32F030XX_eval_lcd.c
 - If the used device is FT32F072X8
    - Add the following files to the project source list
       - Utilities\FT32_EVAL\FT32F072X8_EVAL\FT32F072X8_eval.c
       - Utilities\FT32_EVAL\FT32F072X8_EVAL\FT32F072X8_eval_lcd.c
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT FMD</center></h3>
 */

/**
  ******************************************************************************
  * @file    ADC/ADC_AnalogWatchdog/readme.txt 
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

This example describes how to use the ADC analog watchdog to guard continuously  
an ADC channel.
The ADC1 is configured to convert continuously ADC channel11 and ADC channel10 
respectively for the FT32F030XX and FT32F072X8 devices. 
The analog watchdog is configured and enabled to guard a single regular channel.
Each time the channel11 or channel10 converted value exceeds programmed analog 
watchdog high threshold (value 3102) or goes down analog watchdog low threshold 
(value 1861) an AWD interrupt is generated and the output pin connected to LED4 
is toggled. The LED will bright as long as the AWD interrupt is generated which 
means that the converted value of regular ADC channel11 or channel10 is outside 
the range limited by high and low analog watchdog thresholds.

@note ADC channel11 for FT32F030XX device and channel10 for FT32F072X8 with VDDA REF




         
@par Hardware and Software environment

  - This example runs on FT32F0XX Devices.
  
  - This example has been tested with FMD FT32F072X8-EVAL including
    FT32F072X8


@par How to use it ? 

In order to make the program work, you must do the following :
-define the MCRO of USE_FT32F072X8_EVAL 
 - Copy all source files from this example folder to the template folder under
   Project\FT32F0xx_StdPeriph_Templates
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

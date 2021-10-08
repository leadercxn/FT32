/**
  ******************************************************************************
  * @file    ADC/ADC_DMA/readme.txt 
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

This example describes how to use the ADC1 and DMA to transfer continuously 
converted data from ADC1 to memory.
The ADC1 is configured to convert continuously channel11 if the used device 
is FT32F030XX and channel10 if the used one is FT32F072X8. In addition 
the ADC1 converts continuously Voltage reference, Temperature sensor 
Each time an end of conversion occurs the DMA transfers, in circular mode, the
converted data from ADC1 DR register to the RegularConvData_Tab[4] table.
User can vary the ADC1 channel11 or channel10 voltage using the EVAL Board potentiometer RV3.
The 4 converted voltages are displayed on the EVAL Board LCD.




         
@par Hardware and Software environment

  - This example runs on FT32F0XX Devices.
  
  - This example has been tested with FMD FT32F072X8-EVAL including
    FT32F072X8


@par How to use it ? 

In order to make the program work, you must do the following :
-define the MCRO of USE_FT32F072X8_EVAL 
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

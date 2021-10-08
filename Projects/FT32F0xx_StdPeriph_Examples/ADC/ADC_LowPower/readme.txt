 /**
  ******************************************************************************
  * @file    ADC/ADC_LowPower/readme.txt 
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

This example provides a short description of how to use the ADC peripheral with 
Auto-delayed conversion mode and Auto-poweroff modes.

The ADC is triggered by TIM3_TRGO which is connected to TIM3_Update Event.
Each time the ADC is triggered, it converts the RV3 voltage (which corresponds to
ADC channel11 and ADC channel10 respectively in FT32F030XX and FT32F072X8 devices), 
and then the ADC enters in delay mode (no Overrun detect) until the ADC data register 
has been read by pressing KEY button or TAMPER button respectively for FT32F030XX 
and FT32F072X8 devices.

The Auto delay mode and the Auto power off mode activation can be done by uncommenting
the "#define ADC_LOWPOWER " in the main.c file.
If "#define ADC_LOWPOWER" is commented, an overrun interrupt is generated and
LED1 is toggled. Otherwise, LED1 remains OFF.



         
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

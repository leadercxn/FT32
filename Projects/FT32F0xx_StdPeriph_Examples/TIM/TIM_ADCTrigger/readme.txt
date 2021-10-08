/**
  ******************************************************************************
  * @file    TIM/TIM_ADCTrigger/readme.txt 
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





@par How to use it ? 

In order to make the program work, you must do the following :
 - Use MACRO USE_FT32F030XX_EVAL when use FT32F030 body
 - IF NO define the MACRO of USE_FT32F030XX_EVAL, the FT32F072X8 body is used
 - add FT32F030XX_eval_lcd.c to your project in MDK
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

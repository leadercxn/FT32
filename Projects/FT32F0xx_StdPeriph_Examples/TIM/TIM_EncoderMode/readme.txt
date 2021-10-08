   /**
  ******************************************************************************
  * @file    TIM/TIM_EncoderMode/readme.txt 
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



This example shows how to configure the TIM peripheral to interface with a encoder sensor.
The TIM3 is configured in encoder mode1: Counter counts up/down on TI2 rising edge 
depending on TI1 level 

The TIM3 Autoreload value is set to 399, so the encoder round is 400 TIM counter clock. 
An update interrupt is generated each time the TIM counter reach the Autoreload value, 
in this example 400 TIM counter clock.
 

PA6---TIM3_CH1  INPUT
PA7---TIM3_CH2  INPUT
PA8,PA9,PA10    GPIO  OUTPUT
PA8,PA9 output encoded wave , in main(),  you can connect PA8,PA9 TO PA6,PA7,   THEN PA10(in TIM3_IRQHandler) output wave which cycle is TIM3 overflow cycle


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

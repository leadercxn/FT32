/**
  @page EXTI_Example EXTI Configuration Example
  
  @verbatim
  ******************** (C) COPYRIGHT 2021 FMD *******************
  * @file    EXTI/EXTI_Example/readme.txt 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    10-MAR-2021
  * @brief   Description of the EXTI example.
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
   @endverbatim

@par Example Description 

This example shows how to configure external interrupt lines.
In this example, 4 EXTI lines (EXTI0, EXTI2, EXTI3 and EXTI13) when using the FT32072X8-EVAL
or 4EXTI lines (EXTI0, EXTI8, EXTI9, EXTI13) when using the FT32030XX-EVAL are configured to
generate an interrupt on each falling edge. In the interrupt routine a led connected to a 
specific GPIO pin is toggled.

In this example
    - EXTI0  is mapped to PA0
    - EXTI13 is mapped to PC13
    If FT32F030 device is used
       - EXTI3  is mapped to PE3
       - EXTI2  is mapped to PE2 
    If FT32F072VBT6 device is used
       - EXTI8  is mapped to PC8
       - EXTI9  is mapped to PC9 


After EXTI configuration, a software interrupt is generated on the EXTI8 and LED1 toggles.
After that,
  when falling edge is detected on EXTI0, LED2 toggles
  when falling edge is detected on EXTI13, LED4 toggles
  If FT32F030 device is used
      when falling edge is detected on EXTI3, LED1 toggles
      when falling edge is detected on EXTI2, LED3 toggles
  If FT32F072VBT6 device is used
      when falling edge is detected on EXTI8, LED1 toggles
      when falling edge is detected on EXTI9, LED3 toggles


If FT32030XX-EVAL or FT32072X8-EVAL is used,
  when Joystick Sel push-button is pressed, LED2 toggles
  when Joystick Right push-button is pressed, LED1 toggles
  when Joystick Left push-button is pressed, LED3 toggles
  when Tamper push-button is pressed, LED4 toggles

In this example, EXTI0_Config() function can be substituted by 
FT_EVAL_PBInit(BUTTON_SEL, Mode_EXTI) provided in the USE_FT32F030XX_EVAL driver.




         

@par Hardware and Software environment

  - This example runs on FT32F0xx Devices.
  
  - This example has been tested with FMD FT32030XX-EVAL and
    FT32072X8-EVAL 

  - FT32030XX-EVAL Set-up
     - Use Joystick Right, Left and Sel push-button
     - USe Tamper push-button
  - FT32072X8-EVAL Set-up
     - Use Joystick Right, Left and Sel push-button
     - USe Tamper push-button   


@par How to use it ? 

In order to make the program work, you must do the following :
-define the MCRO of USE_FT32F072X8_EVAL 
 - Copy all source files from this example folder to the template folder under
   Project\FT32F0xx_StdPeriph_Templates
 - Open your preferred toolchain 
 - Open your preferred toolchain
 - If the used device is FT32F030XX
    - Add the following files to the project source list
       - Utilities\FT32_EVAL\FT32030XX_EVAL\FT32F030XX_eval.c
 - If the used device is FT32F072X8
    - Add the following files to the project source list
       - Utilities\FT32_EVAL\FT32F072X8_EVAL\FT32F072X8_eval.c
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT FMD</center></h3>
 */

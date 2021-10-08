  /**
  ******************************************************************************
  * @file    DMA/DMA_ADCTIMTransfer/readme.txt
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

This example provides a description of how to use a DMA channel to transfer
continuously a data from a peripheral (ADC1) to another peripheral (TIM3) supporting
DMA transfer.The ADC channel11 for FT32F030XX-EVAL or ADC channel10 for
FT32F072X8-EVAL is configured to be converted continuously. 
TIM3_CH1 is configured to generate a PWM signal on its output.

The dedicated DMA1 channel3 is configured to transfer in circular mode the last ADC 
channel11 converted value to the TIM3_CCR1 register. The DMA channel request is driven
by the TIM3 update event. The duty cycle of TIM3_CH1 output signal is then changed
each time the input voltage value on ADC channel is modified.

The duty cycle variation can be visualized on oscilloscope on the TIM3_CH1 pin
PA.06 while changing the analog input on ADC channel11 for FT32F030XX-EVAL
or ADC channel10 for FT32F072X8-EVAL using the potentiometer.




         
@par Hardware and Software environment

  - This example runs on FT32f0xx devices.
  
  - This example has been tested with FMD FT32F030XX-EVAL and
    FT32F072X8-EVAL

  - FT32F030XX-EVAL Set-up
     - Use  PC1
  - FT32F072X8-EVAL Set-up
     - Use PC0


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

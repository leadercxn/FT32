/**
  ******************************************************************************
  * @file    SPI/SPI_MSD/readme.txt 
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

This example provides a basic example of how to use the SPI firmware library and
an associate SPI SDcard driver to communicate with an SDcard available on The eval board.

The first step consist in filling the SPI Tx buffer. Then this last one is written 
on the micro sd cards. A comparison between the Buffer transmitted (Buffer_Block_Tx)
and the received one (Buffer_Block_Rx) is done and LED1 is turned on in case of 
success otherwise LED2 is turned on.




         
@par Hardware and Software environment

  - This example runs on FT32f0xx devices.
  
  - This example has been tested with FMD FT32F030XX-EVAL and
    FT32F072X8-EVAL

  - FT32F030XX-EVAL Set-up
    - MicroSD card is already available on this board.
    
  - FT32F072X8-EVAL Set-up
    - MicroSD card is already available on this board.


@par How to use it ? 

In order to make the program work, you must do the following :
  - use USE_FT32F030XX_EVAL mcro
 - add FT32F030XX_eval_spi_sd.c to prj
 - add FT32F030XX_eval.c to prj
 - Copy all source files from this example folder to the template folder under
   Project\FT32f0xx_StdPeriph_Templates
 - Open your preferred toolchain 
 - If the used device is FT32F030XX
    - Add the following files to the project source list
       - Utilities\FT32_EVAL\FT32F030XX_EVAL\FT32F030XX_eval.c
       - Utilities\FT32_EVAL\FT32F030XX_EVAL\FT32F030XX_eval_spi_sd.c
 - If the used device is FT32F072X8
    - Add the following files to the project source list
       - Utilities\FT32_EVAL\FT32F072X8_EVAL\FT32F072X8_eval.c
       - Utilities\FT32_EVAL\FT32F072X8_EVAL\FT32F072X8_eval_spi_sd.c
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT FMD</center></h3>
 */

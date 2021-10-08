 /**
  ******************************************************************************
  * @file    CRC/CRC_32BitsCRCMessage/readme.txt 
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

This example aims to show how to use the CRC peripheral in order to compute
32-bit CRC checksum of a message.
The CRC peripheral is configured to use the 32-bit CRC polynomial
X32 + X26 + X23 + X22 + X16 + X12 + X11 + X10 +X8 + X7 + X5 + X4 + X2+ X +1 
with the initialization value set to 0.
The message is declared as an array and labeled "CRCBuffer".
Once the CRC value is computed, the computed CRC value is compared to the expected
one. In case of match the green led LD1 is turned on. Otherwise the led LD3 is turned on.




   
@par Hardware and Software environment

  - This example runs on FT32f0xx Devices.
  
  - This example has been tested with FMD USE_FT32F030XX_EVAL and
    FT32F072X8-EVAL

  - USE_FT32F030XX_EVAL Set-up
    - LD1 and LD3 are used in this example.
    
  - FT32F072X8-EVAL Set-up
    - LD1 and LD3 are used in this example.

@par How to use it ? 

In order to make the program work, you must do the following :
 - Copy all source files from this example folder to the template folder under
   Project\FT32f0xx_StdPeriph_Templates
 - Open your preferred toolchain 
 - If the used device is FT32F030XX
    - Add the following files to the project source list
       - Utilities\FT32_EVAL\FT32F030XX_EVAL\FT32F030XX_eval.c
 - If the used device is FT32F072X8
    - Add the following files to the project source list
       - Utilities\FT32_EVAL\FT32F072X8_EVAL\FT32F072X8_eval.c
 - Rebuild all files and load your image into target memory
 - Run the example
   
 * <h3><center>&copy; COPYRIGHT FMD</center></h3>
 */

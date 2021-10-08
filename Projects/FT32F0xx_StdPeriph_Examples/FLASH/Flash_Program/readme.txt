   /**
  ******************************************************************************
  * @file    FLASH/FLASH_Program/readme.txt 
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

This example provides a description of how to program the FT32f0xx FLASH.

After Reset, the Flash memory Program/Erase Controller is locked. To unlock it,
the FLASH_Unlock function is used.
Before programming the desired addresses, an erase operation is performed using 
the flash erase page feature. The erase procedure starts with the calculation of
the number of pages to be used. Then all these pages will be erased one by one by
calling FLASH_ErasePage function. 

Once this operation is finished, the programming operation will be performed by 
using the FLASH_ProgramWord function. The written data is then checked and the
result of the programming operation is stored into the MemoryProgramStatus variable.
 




@par Hardware and Software environment

  - This example runs on FT32f0xx Devices.
  
  - This example has been tested with FMD FT32F030XX-EVAL and
    FT32F072X8-EVAL


@par How to use it ? 

In order to make the program work, you must do the following :
 - Copy all source files from this example folder to the template folder under
   Project\FT32f0xx_StdPeriph_Templates
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT FMD</center></h3>
 */

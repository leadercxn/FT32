   /**
  ******************************************************************************
  * @file    FLASH/FLASH_WriteProtection/readme.txt 
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

This example provides a description of how to enable and disable the write protection
for the FT32f0xx embedded FLASH.

- Enable Write protection: 
   To enable the Write Protection, uncomment the line "#define WRITE_PROTECTION_ENABLE"
   in main.c file.  
   To protect a set of pages, the user has to call the function FLASH_EnableWriteProtection.
   The parameter of this function will define the number of pages to be protected.
   To load the new option byte values, a system Reset is necessary, for this, the
   function FLASH_OB_Launch() is used.
 
- Disable Write protection:
   To disable the Write Protection, uncomment the line "#define WRITE_PROTECTION_DISABLE"
   in main.c file.
   To disable the write protection of the FT32f0xx Flash, an erase of the Option 
   Bytes is necessary. This operation is done by the function FLASH_EraseOptionBytes.
   To load the new option byte values, a system Reset is necessary, for this, the
   function FLASH_OB_Launch() is used.

If the desired pages are not write protected, an erase and a write operation are
performed.






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

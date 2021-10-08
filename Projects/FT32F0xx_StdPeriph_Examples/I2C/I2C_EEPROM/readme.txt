/**
  ******************************************************************************
  * @file    I2C/I2C_EEPROM/readme.txt 
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

This firmware provides a basic example of how to use the I2C firmware library and
an associate I2C EEPROM driver to communicate with an I2C EEPROM device (here the
example is interfacing with M24LR64 EEPROM)

I2C peripheral is configured in Master transmitter during write operation and in
Master receiver during read operation from I2C EEPROM. 

The peripheral used is I2C1 but can be configured by modifying the defines values
in FT32F030XX_eval.h or FT32F072X8_eval.h file.
The maximum speed of communication with M24LR64 is 400kHz.
The speed of communication is configured by setting the value of sEE_I2C_TIMING define
in FT32F030XX_eval_i2c_ee.h or FT32F072X8_eval_i2c_ee.h file.

For M24LR64 devices all the memory is accessible through the two-bytes 
addressing mode and need to define block addresses. In this case, the physical 
address has to be defined according to the address pins (E1, E2) connection.

This address is defined in FT32F030XX_eval_i2c_ee.h or in FT32F072X8_eval_i2c_ee.h. 
The EEPROM addresses where the program start the write and the read operations 
is defined in the main.c file. 

First, the content of Tx1Buffer is written to the sEE_WRITE_ADDRESS1 and the
written data are read. The written and the read buffers data are then compared.
Following the read operation, the program waits that the EEPROM reverts to its 
Standby state. A second write operation is, then, performed and this time, Tx2Buffer
is written to sEE_WRITE_ADDRESS2, which represents the address just after the last 
written one in the first write. After completion of the second write operation, the 
written data are read. The contents of the written and the read buffers are compared.

All transfers are managed in Polling mode by calling sEE_ReadBuffer() or 
sEE_WriteBuffer() function.

User should refer to FT32F030XX_eval.h or to FT32F072X8_eval.h file to select which 
EEPROM use in this example.
    
This example provides the possibility to use the LCD screen for messages display
(transfer status: PASSED, FAILED).
To enable this option uncomment the define ENABLE_LCD_MSG_DISPLAY in the main.c
file.  




         
@par Hardware and Software environment

  - This example runs on FT32f0xx devices.
  
  - This example has been tested with FMD FT32F030XX-EVAL and
    FT32F072X8-EVAL
       


@par How to use it ? 

In order to make the program work, you must do the following :
  - use USE_FT32F030XX_EVAL mcro
 - add FT32F030XX_eval_lcd.c to prj
 - add FT32F030XX_eval.c to prj
- add FT32F030XX_eval_i2c_ee.c to prj
 - Copy all source files from this example folder to the template folder under
   Project\FT32f0xx_StdPeriph_Templates
 - Open your preferred toolchain 
  - If the used device is FT32F030XX
    - Add the following files to the project source list
       - Utilities\FT32_EVAL\FT32F030XX_EVAL\FT32F030XX_eval.c
       - Utilities\FT32_EVAL\FT32F030XX_EVAL\FT32F030XX_eval_lcd.c
       - Utilities\FT32_EVAL\FT32F030XX_EVAL\FT32F030XX_eval_i2c_ee.c
 - If the used device is FT32F072X8
    - Add the following files to the project source list
       - Utilities\FT32_EVAL\FT32F072X8_EVAL\FT32F072X8_eval.c
       - Utilities\FT32_EVAL\FT32F072X8_EVAL\FT32F072X8_eval_lcd.c
       - Utilities\FT32_EVAL\FT32F072X8_EVAL\FT32F072X8_eval_i2c_ee.c   
 - Before building the project please make sure that "USE_DEFAULT_TIMEOUT_CALLBACK" 
   define is removed from Preprocessor defines under C/C++ compiler settings.
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT FMD</center></h3>
 */

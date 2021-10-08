   
  /**
  ******************************************************************************
 * @file    IRTIM/IRTIM_EXAMPLE/readme.txt 
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



IR FORMAT:  NEC
  HEAD: 9MS carrier followed by 4.5ms High level
  ID: 16BIT
  DATA1: 8BIT
  DATA2: 8BIT, which is the complement of DATA1 


pc13   is  input pin,    when press to LOW,  IR WILL SEND 32BITS


PB9  is IR output pin



TIM16: carrier generator, 38khz
TIM17: envelope generator,  with interrupt Handler


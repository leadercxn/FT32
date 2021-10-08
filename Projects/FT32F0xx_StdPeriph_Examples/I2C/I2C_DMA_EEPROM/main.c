 /**
  ******************************************************************************
  * @file    I2C/I2C_DMA_EEPROM/main.c 
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


/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup FT32f0xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup I2C_DMA_EEPROM
  * @{
  */
  
/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
/* Uncomment the following line to enable using LCD screen for messages display */
#define ENABLE_LCD_MSG_DISPLAY

#define sEE_WRITE_ADDRESS1        0x50
#define sEE_READ_ADDRESS1         0x50
#define BUFFER_SIZE1            (countof(Tx1Buffer)-1)
#define BUFFER_SIZE2             (countof(Tx2Buffer)-1)
#define sEE_WRITE_ADDRESS2       (sEE_WRITE_ADDRESS1 + BUFFER_SIZE1)
#define sEE_READ_ADDRESS2        (sEE_READ_ADDRESS1 + BUFFER_SIZE1)

/* Private macro -------------------------------------------------------------*/
#define countof(a) (sizeof(a) / sizeof(*(a)))

/* Private variables ---------------------------------------------------------*/
uint8_t Tx1Buffer[] = "/* FT32f0xx I2C Firmware Library EEPROM driver example*/";
//uint8_t Tx1Buffer[] = "/* FT32f0xx I2C Firmware Library EEPROM driver example: \
 //                       This firmware provides a basic example of how to use the I2C firmware library and\
 //                       an associate I2C EEPROM driver to communicate with an I2C EEPROM device \
  //                      I2C peripheral is configured in Master transmitter during write operation and in\
  //                      Master receiver during read operation from I2C EEPROM.*/";

uint8_t Tx2Buffer[] = "/* FT32f0xx I2C Firmware Library EEPROM driver example : I2C1 interfacing with M24LR64 EEPROM */";

uint8_t Rx1Buffer[BUFFER_SIZE1], Rx2Buffer[BUFFER_SIZE2]; 
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;
volatile uint16_t NumDataRead = 0;

uint8_t sEE_writeaddr=sEE_WRITE_ADDRESS1;;
DMA_InitTypeDef  DMA_InitStructure;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void DMA_Write2EEPROM(uint16_t tx_cnt, uint8_t *tx_data);
void DMA_ReadEEPROM(uint16_t rx_cnt, uint8_t *rx_data);


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_FT32f0xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_FT32f0xx.c file
     */

  uint16_t delaym;

  /* Enable Syscfg */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  
  /* Initialize the I2C EEPROM driver ----------------------------------------*/
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1,ENABLE);
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1,DISABLE);
  
  sEE_Init();  
  
  I2C_SlaveAddressConfig(sEE_I2C,sEEAddress);

  /**/
//  I2C_ReloadCmd(sEE_I2C,ENABLE);
//I2C_StretchClockCmd(sEE_I2C,ENABLE);

  /* SEND TO EEPROM*/
  DMA_Write2EEPROM(BUFFER_SIZE1,Tx1Buffer);


  /* delay,  so we can see the data wave easy  */
  delaym=10000;
  while(delaym--);
  
  /* READ FROM EEPROM  */
  DMA_ReadEEPROM(BUFFER_SIZE1,Rx1Buffer);  

  while (1)
  {
 	
  }
}


/**
  * @brief  Configures the DMA Peripheral.
  * @param  None
  * @retval None
  */
static void DMA_TxInit(uint8_t *txbuf,uint16_t txsize)
{ 
  
  
  /* Enable the DMA periph */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
  
  /* Common DMA configuration */
  DMA_InitStructure.DMA_BufferSize = txsize;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  
  /* DMA1 Channel2 configuration , I2C1 TX*/
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)txbuf;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
  DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
  DMA_InitStructure.DMA_PeripheralBaseAddr = I2C1_TDR_Address;
  DMA_Init(DMA1_Channel2, &DMA_InitStructure);

//  I2C_NumberOfBytesConfig(sEE_I2C,txsize);

  /**/
 I2C_DMACmd(sEE_I2C,I2C_DMAReq_Tx,ENABLE);
  
  /* Enable the DMA2 channels */
  DMA_Cmd(DMA1_Channel2, ENABLE);


}


/**
  * @brief  Configures the DMA Peripheral.
  * @param  None
  * @retval None
  */
static void DMA_RxInit(uint8_t *rxbuf,uint16_t rxsize)
{ 
  
  
  /* Enable the DMA periph */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
  
  /* Common DMA configuration */
  DMA_InitStructure.DMA_BufferSize = rxsize;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  
  /* DMA1 Channel2 configuration , I2C1 TX*/
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)rxbuf;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
  DMA_InitStructure.DMA_PeripheralBaseAddr = I2C1_RXD_Address;
  DMA_Init(DMA1_Channel3, &DMA_InitStructure);

  
  /* Enable the DMA2 channels */
  DMA_Cmd(DMA1_Channel3, ENABLE);

 /**/
 I2C_NumberOfBytesConfig(sEE_I2C,rxsize);
 
 /**/
 I2C_DMACmd(sEE_I2C,I2C_DMAReq_Rx,ENABLE);
  
}



/* 
  * tx_cnt :  must <= 253
*/
void DMA_Write2EEPROM(uint16_t tx_cnt, uint8_t *tx_data)
{
  uint16_t delays;
  
  /*  */
  I2C_MasterRequestConfig(sEE_I2C,I2C_Direction_Transmitter);

   /* set the total count , adds the one of sEE_writeaddr*/
   /* the first "+1" is one byte of "sEE_writeaddr" */
  I2C_NumberOfBytesConfig(sEE_I2C,tx_cnt+1);

  /* send  START + ADDRW + sEE_writeaddr*/
  DMA_TxInit(&sEE_writeaddr,1);
  I2C_GenerateSTART(sEE_I2C,ENABLE);
  
  /* wait till DMA finish , but the I2CDMA count is not zero */
  while(!DMA_GetFlagStatus(DMA1_FLAG_TC2));
  
  /* DISABLE DMA and I2CDMA */
  DMA_Cmd(DMA1_Channel2, DISABLE);
  I2C_DMACmd(sEE_I2C,I2C_DMAReq_Tx,DISABLE);
  DMA_ClearFlag(DMA1_FLAG_GL2);

   delays=200;
   while(delays--);

  /* */
  DMA_TxInit(tx_data,tx_cnt);

   /* wait till DMA finish*/
  while(!DMA_GetFlagStatus(DMA1_FLAG_TC2));
  delays=500;
   while(delays--);
  
  /* send stop sig */
  I2C_GenerateSTOP(sEE_I2C,ENABLE);

  /* stop all  */
   DMA_Cmd(DMA1_Channel2, DISABLE);
  I2C_DMACmd(sEE_I2C,I2C_DMAReq_Tx,DISABLE);
  DMA_ClearFlag(DMA1_FLAG_GL2); 

   /*   */
   I2C_Cmd(sEE_I2C, DISABLE);
  
}


/*   */
void DMA_ReadEEPROM(uint16_t rx_cnt, uint8_t *rx_data)
{
  uint16_t delays;
  
  I2C_Cmd(sEE_I2C, ENABLE);
  
  /*  */
  I2C_MasterRequestConfig(sEE_I2C,I2C_Direction_Transmitter);

  /**/
  I2C_NumberOfBytesConfig(sEE_I2C,1);
  DMA_TxInit(&sEE_writeaddr,1);
 I2C_GenerateSTART(sEE_I2C,ENABLE);		//send  START+ADDRW

  /* */
  while(!DMA_GetFlagStatus(DMA1_FLAG_TC2));	// wait till finish
  DMA_Cmd(DMA1_Channel2, DISABLE);
  I2C_DMACmd(sEE_I2C,I2C_DMAReq_Tx,DISABLE);
  DMA_ClearFlag(DMA1_FLAG_GL2);

   delays=300;
   while(delays--);

  /* */
   I2C_MasterRequestConfig(sEE_I2C,I2C_Direction_Receiver);

  /* */
  DMA_RxInit(rx_data,rx_cnt);
  //
  I2C_GenerateSTART(sEE_I2C,ENABLE);

  //
  while(!DMA_GetFlagStatus(DMA1_FLAG_TC3));	// wait till finish

  delays=100;
  while(delays--);
   
  I2C_GenerateSTOP(sEE_I2C,ENABLE);
   DMA_Cmd(DMA1_Channel3, DISABLE);
  I2C_DMACmd(sEE_I2C,I2C_DMAReq_Tx,DISABLE);
  DMA_ClearFlag(DMA1_FLAG_GL3);
  
   /*   */
   I2C_Cmd(sEE_I2C, DISABLE);
   
}







#ifndef USE_DEFAULT_TIMEOUT_CALLBACK
/**
  * @brief  Example of timeout situation management.
  * @param  None.
  * @retval None.
  */
uint32_t sEE_TIMEOUT_UserCallback(void)
{
  /* Use application may try to recover the communication by resetting I2C
    peripheral (calling the function I2C_SoftwareResetCmd()) then re-start
    the transmission/reception from a previously stored recover point.
    For simplicity reasons, this example only shows a basic way for errors 
    managements which consists of stopping all the process and requiring system
    reset. */
  
  
  /* Block communication and all processes */
  while (1)
  {   
  }  
}
#endif /* USE_DEFAULT_TIMEOUT_CALLBACK */



#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/

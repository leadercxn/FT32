 /**
  ******************************************************************************
  * @file    FLASH/FLASH_WriteProtection/main.c
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

/** @addtogroup FLASH_WriteProtection
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
#ifdef FT32F030
  #define FLASH_PAGE_SIZE                ((uint16_t)0x200)	//0X200=0.5K
  #define FLASH_PAGES_TO_BE_PROTECTED    (OB_WRP_Pages0to7| OB_WRP_Pages8to15|OB_WRP_Pages32to39|OB_WRP_Pages40to47|\
                                          OB_WRP_Pages72to79 | OB_WRP_Pages80to87 | OB_WRP_Pages88to95|\
                                          OB_WRP_Pages96to103| OB_WRP_Pages104to111| OB_WRP_Pages112to119|\
                                          OB_WRP_Pages120to127/*|OB_WRP_AllPages*/) 
  #define BANK1_WRITE_START_ADDR         ((uint32_t)0x08006000)
  #define BANK1_WRITE_END_ADDR           ((uint32_t)0x08008000)
#else
  #define FLASH_PAGE_SIZE                ((uint16_t)0x200)	//0X200=0.5K
  #define FLASH_PAGES_TO_BE_PROTECTED    (OB_WRP_Pages0to7| OB_WRP_Pages8to15|\
                                          OB_WRP_Pages72to79 | OB_WRP_Pages80to87 | OB_WRP_Pages88to95|\
                                          OB_WRP_Pages96to103| OB_WRP_Pages104to111| OB_WRP_Pages112to119|\
                                          OB_WRP_Pages120to127/*|OB_WRP_AllPages*/) 
  #define BANK1_WRITE_START_ADDR         ((uint32_t)0x08006000)
  #define BANK1_WRITE_END_ADDR           ((uint32_t)0x08008000)
#endif 



 
/* Uncomment this line to program the Flash pages */
#define FLASH_PAGE_PROGRAM

/* Uncomment this line to Enable Write Protection */
#define WRITE_PROTECTION_ENABLE

/* Uncomment this line to Disable Write Protection */
#define WRITE_PROTECTION_DISABLE

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t EraseCounter = 0x0, Address = 0x0;
uint16_t Data = 0x1753;
uint32_t WRPR_Value = 0xFFFFFFFF, ProtectedPages = 0x0;
uint32_t NbrOfPage;
__IO FLASH_Status FLASHStatus = FLASH_COMPLETE;
__IO TestStatus MemoryProgramStatus = PASSED;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void delaym(uint16_t dlx)
{
	while(dlx--);
}

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

  GPIO_InitTypeDef        GPIO_InitStructure;

  /* GPIOC Periph clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
/* Configure PC13 as input mode pullup  */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  /* Configure PC10in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);



 /* Unlock the Flash Program Erase controller */  
  FLASH_Unlock();
  
  FLASH_OB_Unlock();
  
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR);
    
  /* Get pages write protection status */
  WRPR_Value = FLASH_OB_GetWRP();


/*TO PROTECT*/
#ifdef WRITE_PROTECTION_ENABLE
/*when PC13==H*/
if(Bit_SET==GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13))
{
	/* Get current write protected pages and the new pages to be protected */
	ProtectedPages =  (~WRPR_Value) | FLASH_PAGES_TO_BE_PROTECTED; 

	/* Check if desired pages are not yet write protected */
	if(((~WRPR_Value) & FLASH_PAGES_TO_BE_PROTECTED )!= FLASH_PAGES_TO_BE_PROTECTED)
	{		
		/* Erase all the option Bytes because if a program operation is 
		performed on a protected page, the Flash memory returns a 
		protection error */
		FLASHStatus = FLASH_OB_Erase();

		/* Enable the pages write protection */
		FLASHStatus = FLASH_OB_EnableWRP(ProtectedPages);

		/* Generate System Reset to load the new option byte values */
		FLASH_OB_Launch();
	}  

}
#endif



/*TO PROTECT*/
#ifdef WRITE_PROTECTION_DISABLE
/*when PC13==L*/
if(Bit_RESET==GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13))
{
	/* Get pages already write protected */
	ProtectedPages = ~(WRPR_Value | FLASH_PAGES_TO_BE_PROTECTED);

	/* Check if desired pages are already write protected */
	if((WRPR_Value | (~FLASH_PAGES_TO_BE_PROTECTED)) != 0xFFFFFFFF )
	{		
		/* Erase all the option Bytes */
		FLASHStatus = FLASH_OB_Erase();

		/* Check if there is write protected pages */
		 if(ProtectedPages != 0x0)
		{
			/* Restore write protected pages */
			FLASHStatus = FLASH_OB_EnableWRP(ProtectedPages);
		}
		
		/* Generate System Reset to load the new option byte values */
		FLASH_OB_Launch();
	}
}
#endif

  
  
#ifdef FLASH_PAGE_PROGRAM  
	/* Get the number of pages to be erased */
	NbrOfPage = (BANK1_WRITE_END_ADDR - BANK1_WRITE_START_ADDR) / FLASH_PAGE_SIZE;

	/* The selected pages are not write protected */
	if ( (WRPR_Value & FLASH_PAGES_TO_BE_PROTECTED) != 0x00)
	{
		/* Clear pending flags */
		FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_PGERR |FLASH_FLAG_WRPERR);	

		/* erase the FLASH pages */
		for(EraseCounter = 0; (EraseCounter < NbrOfPage) && (FLASHStatus == FLASH_COMPLETE); EraseCounter++)
		{
			FLASHStatus = FLASH_ErasePage(BANK1_WRITE_START_ADDR + (FLASH_PAGE_SIZE * EraseCounter));
		}

		/* FLASH Half Word program of data 0x1753 at addresses defined by  BANK1_WRITE_START_ADDR and BANK1_WRITE_END_ADDR */
		Address = BANK1_WRITE_START_ADDR;

		while((Address < BANK1_WRITE_END_ADDR) && (FLASHStatus == FLASH_COMPLETE))
		{
			FLASHStatus = FLASH_ProgramWord(Address, Data);
			Address = Address + 4;
		}

		/* Check the correctness of written data */
		Address = BANK1_WRITE_START_ADDR;

		while((Address < BANK1_WRITE_END_ADDR) && (MemoryProgramStatus != FAILED))
		{
			if((*(__IO uint32_t*) Address) != Data)
			{
				MemoryProgramStatus = FAILED;
			}
				Address += 4;
		}
	}
	else
	{ 
		/* Error to program the flash : The desired pages are write protected */ 
		MemoryProgramStatus = FAILED;
	}

	while(1)
	{
		if(FAILED==MemoryProgramStatus){
			GPIO_SetBits(GPIOC,GPIO_Pin_10);
			delaym(200);
			GPIO_ResetBits(GPIOC,GPIO_Pin_10);
			IWDG_ReloadCounter();
		}
		else{
			GPIO_ResetBits(GPIOC,GPIO_Pin_10);
			delaym(200);
			GPIO_SetBits(GPIOC,GPIO_Pin_10);
			IWDG_ReloadCounter();
		}
	}
#endif /* FLASH_PAGE_PROGRAM */

 




  while (1)
  {
  }

  
}


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

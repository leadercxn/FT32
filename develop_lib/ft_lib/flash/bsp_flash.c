#include "bsp_flash.h"


uint32_t EraseCounter = 0x00, Address = 0x00;

uint32_t NbrOfPage = 0x00;

__IO FLASH_Status FLASHStatus = FLASH_COMPLETE;
  
void FLASH_Write(uint32_t START_WriteAddr,uint32_t END_WriteAddr,uint32_t *pBuffer)	
{
	  
  /* Unlock the Flash to enable the flash control register access *************/ 
  FLASH_Unlock();
    
  /* Erase the user Flash area
    (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/

  /* Clear pending flags (if any) */  
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR); 

  /* Define the number of page to be erased */
  NbrOfPage = (END_WriteAddr - START_WriteAddr) / FLASH_PAGE_SIZE;

  /* Erase the FLASH pages */
  for(EraseCounter = 0; (EraseCounter < NbrOfPage) && (FLASHStatus == FLASH_COMPLETE); EraseCounter++)
  {
    if (FLASH_ErasePage(START_WriteAddr + (FLASH_PAGE_SIZE * EraseCounter))!= FLASH_COMPLETE)
    {
     /* Error occurred while sector erase. 
         User can add here some code to deal with this error  */
      while (1)
      {
      }
    }
  }
  /* Program the user Flash area word by word
    (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/

  Address = START_WriteAddr;

  while (Address < END_WriteAddr)
  {
    if (FLASH_ProgramWord(Address, *pBuffer) == FLASH_COMPLETE)
    {
      Address = Address + 4;
    }
    else
    { 
      /* Error occurred while writing data in Flash memory. 
         User can add here some code to deal with this error */
      while (1)
      {
      }
    }
  }

  /* Lock the Flash to disable the flash control register access (recommended
     to protect the FLASH memory against possible unwanted operation) *********/
  FLASH_Lock(); 


}	


void FLASH_Read(uint32_t START_WriteAddr,uint32_t END_WriteAddr,uint32_t *pBuffer)   	
{
	Address = START_WriteAddr;
	
	while (Address < END_WriteAddr)
	{
		*pBuffer = *(__IO uint32_t *)Address;
		
		Address = Address + 4;
	}
}

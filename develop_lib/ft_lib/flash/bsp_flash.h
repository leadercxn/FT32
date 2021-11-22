#ifndef _BSP_FLASH_H
#define _BSP_FLASH_H	    


#include "FT32f0xx.h"
#include <stdio.h>


#define FLASH_PAGE_SIZE         ((uint32_t)0x00000200)   /* FLASH Page Size */

#define BATTERY_USER_START_ADDR   ((uint32_t)0x0800F000)  
#define BATTERY_USER_END_ADDR     ((uint32_t)0x0800F200)  

#define FLASH_USER_START_ADDR   ((uint32_t)0x0800F000)   /* Start @ of user Flash area */
#define FLASH_USER_END_ADDR     ((uint32_t)0x0800F200)   /* End @ of user Flash area */

void FLASH_Write(uint32_t START_WriteAddr,uint32_t END_WriteAddr,uint32_t *pBuffer);
void FLASH_Read(uint32_t START_WriteAddr,uint32_t END_WriteAddr,uint32_t *pBuffer);

#endif



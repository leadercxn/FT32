#include "stdbool.h"
#include "string.h"

#include "ft32f0xx.h"
#include "ft_flash.h"
#include "lib_error.h"
#include "board_config.h"

#define FLASH_PAGE_SIZE 0x00000200

static FLASH_Status m_flash_status = FLASH_COMPLETE;

/**
 * @brief 往flash 写入 len 个 字
 * 
 * @param len   字（4B） 长度
 */
int ft_flash_write_word(uint32_t address, uint16_t len, uint32_t *p_data)
{
    if(address > 0x800FFFF)
    {
        return -EINVAL;
    }

    if( (address + len * sizeof(uint32_t) ) > 0x800FFFF)
    {
        return -EFBIG;
    }

    if(m_flash_status != FLASH_COMPLETE)
    {
        return -EBUSY;
    }

    uint16_t number_of_page = 0;
    uint8_t i = 0;

    uint32_t write_address = 0x00;

    FLASH_Unlock();

    /* Clear pending flags (if any) */  
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR); 

    number_of_page = len * sizeof(uint32_t) / FLASH_PAGE_SIZE;
    if(len % FLASH_PAGE_SIZE)
    {
        number_of_page++;
    }
#if 0
    for(i = 0; (i < number_of_page) && (m_flash_status == FLASH_COMPLETE); i++ )
    {
        if(FLASH_ErasePage(address + (FLASH_PAGE_SIZE * i)) != FLASH_COMPLETE)
        {

        }
    }
#endif
    do
    {
        if(FLASH_ErasePage(address + (FLASH_PAGE_SIZE * i)) != FLASH_COMPLETE)
        {
            break;
        }

        i++;
    } while ((i < number_of_page) && (m_flash_status == FLASH_COMPLETE));

    write_address = address;
    for(i = 0; i < len; i++)
    {
        if(FLASH_ProgramWord(write_address, p_data[i]) == FLASH_COMPLETE)
        {
            
        }

        write_address += sizeof(uint32_t);
    }
    
    /* Lock the Flash to disable the flash control register access (recommended
     to protect the FLASH memory against possible unwanted operation) *********/
    FLASH_Lock(); 
}

/**
 * @brief 往flash 读出 len 个 字
 * 
 * @param len   字（4B） 长度
 */
int ft_flash_read_word(uint32_t address, uint16_t len, uint32_t *p_data)
{
    if(address > 0x800FFFF)
    {
        return -EINVAL;
    }

    if( (address + len * sizeof(uint32_t) ) > 0x800FFFF)
    {
        return -EFBIG;
    }

    if(m_flash_status != FLASH_COMPLETE)
    {
        return -EBUSY;
    }

    uint8_t     i = 0;
    uint32_t    read_address = address;

    for(i = 0; i < len; i++)
    {
        p_data[i] = *(__IO uint32_t *)read_address;

        read_address += sizeof(uint32_t);
    }

    return 0;
}







static FLASH_Status flash_program(uint32_t address, uint8_t data)
{
    FLASH_Status status = FLASH_COMPLETE;
    __IO uint32_t tmp = 0;

    /* Check the parameters */
    assert_param(IS_FLASH_PROGRAM_ADDRESS(address));

    FLASH_PrefetchBufferCmd(DISABLE);
    __ASM("ISB");

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
    
    if(status == FLASH_COMPLETE)
    {
        /* If the previous operation is completed, proceed to program the new first word */
        FLASH->CR |= FLASH_CR_PG;
    
        *(__IO uint32_t*)address = (uint32_t)data;
        
        /* Wait for last operation to be completed */
        status = FLASH_WaitForLastOperation(FLASH_ER_PRG_TIMEOUT);
    
        /* Disable the PG Bit */
        FLASH->CR &= ~FLASH_CR_PG;
    }

    FLASH_PrefetchBufferCmd(ENABLE);
    
    /* Return the Program Status */
    return status;
}

/**
 * FT32不支持半字,字节的写操作
 */
#if 0
/**
 * @brief 往flash 写入 len 个 字节
 * 
 * @param len   字节（1B） 长度
 */
int ft_flash_write(uint32_t address, uint16_t len, uint8_t *p_data)
{
    if(address > 0x800FFFF)
    {
        return -EINVAL;
    }

    if( (address + len) > 0x800FFFF)
    {
        return -EFBIG;
    }

    if(m_flash_status != FLASH_COMPLETE)
    {
        return -EBUSY;
    }

    if(!p_data)
    {
        return -EINVAL;
    }

    uint16_t number_of_page = 0;
    uint8_t i = 0;

    uint32_t write_address = 0x00;

    FLASH_Unlock();

    /* Clear pending flags (if any) */  
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR); 

    number_of_page = len / FLASH_PAGE_SIZE;

    if(len % FLASH_PAGE_SIZE)
    {
        number_of_page++;
    }

    do
    {
        if(FLASH_ErasePage(address + (FLASH_PAGE_SIZE * i)) != FLASH_COMPLETE)
        {
            break;
        }

        i++;
    } while ((i < number_of_page) && (m_flash_status == FLASH_COMPLETE));
    

    trace_debug("ft_flash_write erase done\n\r");

    write_address = address;
    for(i = 0; i < len; i++)
    {
        if(flash_program(write_address, p_data[i]) == FLASH_COMPLETE)
        {
            trace_debug("ft_flash_write write success\n\r");
        }
        else
        {
            trace_debug("ft_flash_write write error\n\r");
        }

        write_address += 1;
    }
    
    /* Lock the Flash to disable the flash control register access (recommended
     to protect the FLASH memory against possible unwanted operation) *********/
    FLASH_Lock(); 
}
#endif

/**
 * @brief 往flash 读出 len 个 字节
 * 
 * @param len   字节（1B） 长度
 */
int ft_flash_read(uint32_t address, uint16_t len, uint8_t *p_data)
{
    if(address > 0x800FFFF)
    {
        return -EINVAL;
    }

    if( (address + len) > 0x800FFFF)
    {
        return -EFBIG;
    }

    if(m_flash_status != FLASH_COMPLETE)
    {
        return -EBUSY;
    }

    if(!p_data)
    {
        return -EINVAL;
    }

    uint8_t     i = 0;
    uint32_t    read_address = address;

    for(i = 0; i < len; i++)
    {
        p_data[i] = *(__IO uint8_t *)read_address;

        read_address += sizeof(uint8_t);
    }

    return 0;
}


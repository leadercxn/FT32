#include "board_config.h"
#include "mid_flash.h"

int mid_flash_write(uint32_t address, uint16_t len, uint8_t *p_data)
{
    int err_code = 0;

    if(!is_word_aligned(p_data) || (len % 4) || (address % 4))
    {
        return -EINVAL;
    }

#ifdef FT32
    uint16_t word_len = len / 4;

    err_code = ft_flash_write_word(address, word_len, (uint32_t *)p_data);
    if(err_code)
    {
        return -err_code;
    }
#endif

    return ENONE;
}



int mid_flash_read(uint32_t address, uint16_t len, uint8_t *p_data)
{
    int err_code = 0;

    if(!is_word_aligned(p_data) || (address % 4))
    {
        return -EINVAL;
    }
#ifdef FT32
    err_code = ft_flash_read(address, len, p_data);
    if(err_code)
    {
        return -err_code;
    }
#endif

    return ENONE;
}


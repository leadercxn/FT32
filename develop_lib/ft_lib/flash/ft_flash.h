#ifndef __FT_FLASH_H
#define __FT_FLASH_H

#include "ft32f0xx.h"

int ft_flash_write_word(uint32_t address, uint16_t len, uint32_t *p_data);
int ft_flash_read_word(uint32_t address, uint16_t len, uint32_t *p_data);

int ft_flash_read(uint32_t address, uint16_t len, uint8_t *p_data);
#endif


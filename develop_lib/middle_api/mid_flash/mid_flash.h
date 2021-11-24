#ifndef __MID_FLASH_H
#define __MID_FLASH_H

int mid_flash_write(uint32_t address, uint16_t len, uint8_t *p_data);

int mid_flash_read(uint32_t address, uint16_t len, uint8_t *p_data);

#endif

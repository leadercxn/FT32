#ifndef __FLASH_HANDLER_H
#define __FLASH_HANDLER_H


typedef struct
{
    uint32_t magic;

    uint8_t l_ch_index;
    uint8_t r_ch_index;
    uint8_t parent_band;    //根据不同的地区，选择频段

    uint32_t crc32;
} __attribute__((aligned(4))) app_param_t;

extern app_param_t g_app_param;

void app_param_flash_init(void);


#endif

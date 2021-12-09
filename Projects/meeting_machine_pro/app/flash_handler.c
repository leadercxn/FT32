#include "board_config.h"
#include "flash_handler.h"

#define APP_PARAM_MAGIC 0x56AB1288

/**
 * Flash structure
 * 
 *  ｜ Adress                  ｜ Fun       ｜ size |
 *  ｜ 0x8000 000 - 0x8007 7FF ｜ app       ｜  30K |
 *  ｜ 0x8007 800 - 0x8007 FFF ｜ app_param ｜  2K  |
 */

app_param_t g_app_param;

void app_param_flash_init(void)
{
    uint8_t     *p_data = (uint8_t *) FLASH_APP_PARAM_SAVE_ADDR;
    app_param_t *p_app_param = (app_param_t *) FLASH_APP_PARAM_SAVE_ADDR;
    uint32_t    crc = 0;

    /* 判断是否已配置数据 */
    if(* (uint32_t *)p_data == 0xFFFFFFFF)
    {
        /* 未配置的话，先采用默认的参数 */
        p_app_param->magic = APP_PARAM_MAGIC;
        p_app_param->l_ch_index = 1;
        p_app_param->r_ch_index = 101;
        p_app_param->parent_band = 0;
        p_app_param->crc32 = crc32_compute(p_data, sizeof(app_param_t) - sizeof(uint32_t), NULL);
    }
    else if(* (uint32_t *)p_data == APP_PARAM_MAGIC)
    {
        /**
         * 校验完整性
         */
        if(p_app_param->crc32 == crc32_compute(p_data, sizeof(app_param_t) - sizeof(uint32_t), NULL))
        {

        }
        else
        {

        }
    }
}




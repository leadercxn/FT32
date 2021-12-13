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
    app_param_t app_param;
    uint8_t     *p_data = (uint8_t *)&app_param;
    int err_code = 0;

    mid_flash_read(FLASH_APP_PARAM_SAVE_ADDR, sizeof(app_param_t), &app_param);

    /* 判断是否已配置数据 */
    if(app_param.magic != APP_PARAM_MAGIC)
    {
        /* 未配置的话，先采用默认的参数 */
        app_param.magic = APP_PARAM_MAGIC;
        app_param.l_ch_index = 1;
        app_param.r_ch_index = 101;
        app_param.parent_band = 0;
        app_param.crc32 = crc32_compute(p_data, sizeof(app_param_t) - sizeof(uint32_t), NULL);

        g_app_param = app_param;
        trace_debug("First use , crc32 = 0x%08x\n\r", app_param.crc32);

        err_code = mid_flash_write(FLASH_APP_PARAM_SAVE_ADDR, sizeof(app_param_t), p_data);
        if(err_code == 0)
        {
            trace_debug("mid_flash_write success\n\r");
        }
    }
    else
    {
        /**
         * 校验完整性
         */
        if(app_param.crc32 == crc32_compute(p_data, sizeof(app_param_t) - sizeof(uint32_t), NULL))
        {
            trace_debug("App param crc pass\n\r",);
            g_app_param = app_param;
            trace_debug("l_ch_index = %d\n\r",g_app_param.l_ch_index);
            trace_debug("r_ch_index = %d\n\r",g_app_param.r_ch_index);
            trace_debug("parent_band = %d\n\r",g_app_param.parent_band);
        }
        else
        {
            /* 未配置的话，先采用默认的参数 */
            app_param.magic = APP_PARAM_MAGIC;
            app_param.l_ch_index = 1;
            app_param.r_ch_index = 101;
            app_param.parent_band = 0;
            app_param.crc32 = crc32_compute(p_data, sizeof(app_param_t) - sizeof(uint32_t), NULL);

            g_app_param = app_param;
            trace_error("App param crc error, use default param\n\r");
            
            err_code = mid_flash_write(FLASH_APP_PARAM_SAVE_ADDR, sizeof(app_param_t), p_data);
            if(err_code == 0)
            {
                trace_debug("mid_flash_write success\n\r");
            }
        }
    }
}






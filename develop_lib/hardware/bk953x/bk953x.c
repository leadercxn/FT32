/**
 * 该文件是BK芯片配置相关寄存器接口 
 */
#include "stdio.h"
#include "board_config.h"
#include "util.h"
#include "trace.h"

#include "middle_api.h"
#include "bk953x.h"

bk953x_reg_value_t g_bk9532_init_config[54] = {
    {0x00 , 0xDFFFFFF8 },
    {0x01 , 0x04D28057 },
    {0x02 , 0x0890E028 },
    {0x03 , 0x2452069F },
    {0x04 , 0x52880044 },
    {0x05 , 0x00280380 },
    {0x06 , 0x5BEDFB00 },
    {0x07 , 0x1C2EC5AA },
    {0x08 , 0xEFF1194C },
    {0x09 , 0x885113A2 },//
    {0x0A , 0x006F006F },
    {0x0B , 0x1BD25863 },
    {0x0C , 0x00000008 },
    {0x0D , 0x3A9B69D0 },

    {0x2C , 0x00000000 },
    {0x2D , 0x000000FF },
    {0x2E , 0xF128A000 },
    {0x2F , 0x00002E91 },

    {0x30 , 0x40404040 },

#ifdef ENABLE_GPIO4_MUTE_FUN
    {0x31 , 0xC1080000 },
#else
    {0x31 , 0xC1080071 },//
#endif

    {0x32 , 0x20FF0F09 },
    {0x33 , 0x00900080 },
    {0x34 , 0xFFFF010E },
    {0x35 , 0x09000000 },
    {0x36 , 0x0C6060DD },

    {0x37 , 0x3E009800 },
    {0x38 , 0x40D7D5F7 },
    {0x39 , 0x00000000 },
    {0x3A , 0x28020564 },
    {0x3B , 0x6D000800 },//
    {0x3C , 0x0040FFDC },
    {0x3D , 0x00006629 },

    {0x3E , 0x1F554FEE },
    {0x3F , 0x8D7A002F },

    {0x59 , 0x43000000 },
    {0x5A , 0x00000000 },
    {0x5B , 0x00000000 },
    {0x5C , 0x2CD50000 },
    {0x5D , 0x1FFF3FFF },
    {0x5E , 0x00000F00 },//

    {0x70 , 0x00089532 },
    {0x71 , 0x18A40810 },
    {0x72 , 0x00000000 },
    {0x73 , 0x00000008 },
    {0x74 , 0x00000000 },
    {0x75 , 0x00000629 },
    {0x76 , 0x0000FB06 },
    {0x77 , 0x00000000 },
    {0x78 , 0x00000000 },
    {0x79 , 0x00000000 },//
    {0x7A , 0x00010001 },
    {0x7B , 0x3BE40796 },
    {0x7C , 0x0F860074 },
    {0x7D , 0x0032A8FF },
};

int bk953x_sample_rate_set(bk953x_object_t *p_bk953x_object, bk953x_sample_rate_e rate)
{

}

int bk953x_band_type_set(bk953x_object_t *p_bk953x_object, bk953x_band_type_e band_type)
{

}

int bk953x_power_set(bk953x_object_t *p_bk953x_object, uint8_t power)
{

}

int bk953x_freq_set(bk953x_object_t *p_bk953x_object, uint32_t freq)
{

}

int bk953x_chan_set(bk953x_object_t *p_bk953x_object, uint16_t chan)
{

}

int bk953x_soft_reset(bk953x_object_t *p_bk953x_object)
{
    uint32_t value = 0;
    if(p_bk953x_object->chip_id == BK9532_CHID_ID)
    {
        mid_bk953x_read_one_reg(&p_bk953x_object->mid_bk953x_object, BK953X_DEVICE_ID, 0x3F, &value);
        CLR_BIT(value,5);
        mid_bk953x_write_one_reg(&p_bk953x_object->mid_bk953x_object, BK953X_DEVICE_ID, 0x3F, &value);
        SET_BIT(value,5);
        mid_bk953x_write_one_reg(&p_bk953x_object->mid_bk953x_object, BK953X_DEVICE_ID, 0x3F, &value);
    }
    else if(p_bk953x_object->chip_id == BK9531_CHID_ID)
    {
        
    }
}

int bk953x_chip_id_get(bk953x_object_t *p_bk953x_object)
{
    uint32_t value = 0;
    int err_code = 0;

    err_code = mid_bk953x_read_one_reg(&p_bk953x_object->mid_bk953x_object, BK953X_DEVICE_ID, REG_CHIP_ID, &value);
    if(err_code == 0)
    {
        p_bk953x_object->chip_id = value;
    }

    trace_debug("bk953x_chip_id_get err_code = %d , chip_id = 0x%08x\n\r",err_code,p_bk953x_object->chip_id);
    return err_code;
}

void bk953x_res_init(bk953x_object_t *p_bk953x_object)
{
    mid_bk953x_res_init(&p_bk953x_object->mid_bk953x_object);
}

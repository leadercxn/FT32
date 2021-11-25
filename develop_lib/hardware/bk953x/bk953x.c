/**
 * 该文件是BK芯片配置相关寄存器接口 
 */
#include "stdio.h"
#include "stdbool.h"
#include "board_config.h"
#include "util.h"
#include "trace.h"

#include "middle_api.h"
#include "bk953x.h"

bk953x_reg_value_t g_bk9532_init_config[54] = {
//寄存器 0x00 ~ 0x0D 是只写寄存器，所以全局可以使用
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

/**
 * @brief 接收软复位
 */
static int bk953x_rx_reset(bk953x_object_t *p_bk953x_object)
{
    int err_code = 0;
    uint32_t value = 0;
    if(p_bk953x_object->chip_id == BK9532_CHID_ID)
    {
        err_code = mid_bk953x_read_one_reg(&p_bk953x_object->mid_bk953x_object, BK953X_DEVICE_ID, 0x3F, &value);
        if(err_code)
        {
            trace_error("bk953x_rx_reset read error %d\n\r",err_code);
            return err_code;
        }

        CLR_BIT(value,31);
        err_code = mid_bk953x_write_one_reg(&p_bk953x_object->mid_bk953x_object, BK953X_DEVICE_ID, 0x3F, &value);
        if(err_code)
        {
            trace_error("bk953x_rx_reset write error %d\n\r",err_code);
            return err_code;
        }
        delay_ms(10);

        SET_BIT(value,31);
        err_code = mid_bk953x_write_one_reg(&p_bk953x_object->mid_bk953x_object, BK953X_DEVICE_ID, 0x3F, &value);
        if(err_code)
        {
            trace_error("bk953x_rx_reset write error %d\n\r",err_code);
            return err_code;
        }
        delay_ms(10);
    }
    else
    {

    }
    return err_code;
}

static int bk953x_rx_plc_reset(bk953x_object_t *p_bk953x_object)
{
    int err_code = 0;
    uint32_t value = 0;
    if(p_bk953x_object->chip_id == BK9532_CHID_ID)
    {
        err_code = mid_bk953x_read_one_reg(&p_bk953x_object->mid_bk953x_object, BK953X_DEVICE_ID, 0x3F, &value);
        if(err_code)
        {
            trace_error("bk953x_rx_plc_reset read error %d\n\r",err_code);
            return err_code;
        }

        SET_BIT(value,28);
        err_code = mid_bk953x_write_one_reg(&p_bk953x_object->mid_bk953x_object, BK953X_DEVICE_ID, 0x3F, &value);
        if(err_code)
        {
            trace_error("bk953x_rx_plc_reset write error %d\n\r",err_code);
            return err_code;
        }
        delay_ms(10);

        CLR_BIT(value,28);
        err_code = mid_bk953x_write_one_reg(&p_bk953x_object->mid_bk953x_object, BK953X_DEVICE_ID, 0x3F, &value);
        if(err_code)
        {
            trace_error("bk953x_rx_plc_reset write error %d\n\r",err_code);
            return err_code;
        }
        delay_ms(10);
    }
    else
    {

    }
    return err_code;
}

/**
 * @brief  RX mode,trigger chip to calibrate 接收模式下的校准
 * 
 */
static int bk953x_rx_calibration_trigger(bk953x_object_t *p_bk953x_object)
{
    int err_code = 0;
    if(p_bk953x_object->chip_id == BK9532_CHID_ID)
    {
        /* Tune the RF loop LDO voltage to 0x0 */
        CLR_BIT(g_bk9532_init_config[6].value, 29);
        CLR_BIT(g_bk9532_init_config[6].value, 30);
        CLR_BIT(g_bk9532_init_config[6].value, 31);
        err_code = mid_bk953x_write_one_reg(&p_bk953x_object->mid_bk953x_object, BK953X_DEVICE_ID, 0x06, &g_bk9532_init_config[6].value);
        if(err_code)
        {
            trace_error("bk953x_rx_calibration_trigger write error %d\n\r",err_code);
            return err_code;
        }

        delay_ms(1);

        /* Enable calibration clock */
        SET_BIT(g_bk9532_init_config[7].value, 25);
        err_code = mid_bk953x_write_one_reg(&p_bk953x_object->mid_bk953x_object, BK953X_DEVICE_ID, 0x07, &g_bk9532_init_config[7].value);
        if(err_code)
        {
            trace_error("bk953x_rx_calibration_trigger write error %d\n\r",err_code);
            return err_code;
        }

        /*Calibrate RF VCO*/
        CLR_BIT(g_bk9532_init_config[3].value, 22);
        err_code = mid_bk953x_write_one_reg(&p_bk953x_object->mid_bk953x_object, BK953X_DEVICE_ID, 0x03, &g_bk9532_init_config[3].value);
        if(err_code)
        {
            trace_error("bk953x_rx_calibration_trigger write error %d\n\r",err_code);
            return err_code;
        }
        SET_BIT(g_bk9532_init_config[3].value, 22);
        err_code = mid_bk953x_write_one_reg(&p_bk953x_object->mid_bk953x_object, BK953X_DEVICE_ID, 0x03, &g_bk9532_init_config[3].value);
        if(err_code)
        {
            trace_error("bk953x_rx_calibration_trigger write error %d\n\r",err_code);
            return err_code;
        }

        delay_ms(5);

        /* Calibrate Digital VCO */
        CLR_BIT(g_bk9532_init_config[4].value, 25);
        err_code = mid_bk953x_write_one_reg(&p_bk953x_object->mid_bk953x_object, BK953X_DEVICE_ID, 0x04, &g_bk9532_init_config[4].value);
        if(err_code)
        {
            trace_error("bk953x_rx_calibration_trigger write error %d\n\r",err_code);
            return err_code;
        }
        SET_BIT(g_bk9532_init_config[4].value, 25);
        err_code = mid_bk953x_write_one_reg(&p_bk953x_object->mid_bk953x_object, BK953X_DEVICE_ID, 0x04, &g_bk9532_init_config[4].value);
        if(err_code)
        {
            trace_error("bk953x_rx_calibration_trigger write error %d\n\r",err_code);
            return err_code;
        }

        /* Disable calibration clock */
        CLR_BIT(g_bk9532_init_config[7].value, 25);
        err_code = mid_bk953x_write_one_reg(&p_bk953x_object->mid_bk953x_object, BK953X_DEVICE_ID, 0x07, &g_bk9532_init_config[7].value);
        if(err_code)
        {
            trace_error("bk953x_rx_calibration_trigger write error %d\n\r",err_code);
            return err_code;
        }

        delay_ms(2);

         /* load the default RF loop LDO voltage */
        SET_BIT(g_bk9532_init_config[6].value, 29);
        SET_BIT(g_bk9532_init_config[6].value, 30);
        SET_BIT(g_bk9532_init_config[6].value, 31);
        err_code = mid_bk953x_write_one_reg(&p_bk953x_object->mid_bk953x_object, BK953X_DEVICE_ID, 0x06, &g_bk9532_init_config[6].value);
        if(err_code)
        {
            trace_error("bk953x_rx_calibration_trigger write error %d\n\r",err_code);
            return err_code;
        }

    }
    else
    {

    }
    return err_code;
}

/**
 * @brief  bk953x设置频点的信道
 * 
 */
int bk953x_freq_chan_set(bk953x_object_t *p_bk953x_object, freq_chan_object_t *p_freq_chan_object)
{
    if(!p_freq_chan_object)
    {
        return -EINVAL;
    }

    if(!p_bk953x_object)
    {
        return -EINVAL;
    }

    p_bk953x_object->band_type = p_freq_chan_object->band_type;
    p_bk953x_object->freq_chan_index = p_freq_chan_object->chan_index;

    int err_code = 0;
    if(p_bk953x_object->chip_id == BK9532_CHID_ID)
    {
        CLR_BIT(g_bk9532_init_config[3].value, 15);
        CLR_BIT(g_bk9532_init_config[3].value, 14);
        CLR_BIT(g_bk9532_init_config[3].value, 13);
        CLR_BIT(g_bk9532_init_config[3].value, 21);
        SET_BIT(g_bk9532_init_config[3].value, 20);
        err_code = mid_bk953x_write_one_reg(&p_bk953x_object->mid_bk953x_object, BK953X_DEVICE_ID, 0x03, &g_bk9532_init_config[3].value);
        if(err_code)
        {
            trace_error("bk953x_freq_chan_set write error %d\n\r",err_code);
            return err_code;
        }

        err_code = mid_bk953x_write_one_reg(&p_bk953x_object->mid_bk953x_object, BK953X_DEVICE_ID, 0x0D, &p_freq_chan_object->reg_value);
        if(err_code)
        {
            trace_error("bk953x_freq_chan_set write error %d\n\r",err_code);
            return err_code;
        }

        bk953x_rx_calibration_trigger(p_bk953x_object);
        bk953x_rx_reset(p_bk953x_object);
        bk953x_rx_plc_reset(p_bk953x_object);
    }
    else
    {

    }
}

/**
 * @brief  bk953x设置接收天线的模式
 * 
 */
int bk953x_rx_antena_set(bk953x_object_t *p_bk953x_object, antenna_type_e antenna_type)
{
    int err_code = 0;
    uint32_t value = 0;

    if(!p_bk953x_object)
    {
        return -EINVAL;
    }

    p_bk953x_object->antenna_type = antenna_type;

    if(p_bk953x_object->chip_id == BK9532_CHID_ID)
    {
        err_code = mid_bk953x_read_one_reg(&p_bk953x_object->mid_bk953x_object, BK953X_DEVICE_ID, 0x3F, &value);
        if(err_code)
        {
            trace_warn("bk953x_antena_set read fail %d\n\r",err_code);
        }

        if(DA_AUTO == antenna_type)
        {
            SET_BIT(value, 17);
        }
        else if(SA_ANT2_PIN5 == antenna_type)
        {
            CLR_BIT(value, 17);
            SET_BIT(value, 16);
        }
        else
        {
            CLR_BIT(value, 17);
            CLR_BIT(value, 16);
        }

        err_code = mid_bk953x_write_one_reg(&p_bk953x_object->mid_bk953x_object, BK953X_DEVICE_ID, 0x3F, &value);
        if(err_code)
        {
            trace_error("bk953x_antena_set write error %d\n\r",err_code);
            return err_code;
        }
    }
    else
    {

    }

    return err_code;
}

int bk953x_rx_adpcm_mode_set(bk953x_object_t *p_bk953x_object, adpcm_mode_e adpcm_mode)
{
    int err_code = 0;
    uint32_t value = 0;

    if(!p_bk953x_object)
    {
        return -EINVAL;
    }

    if(p_bk953x_object->chip_id == BK9532_CHID_ID)
    {
        err_code = mid_bk953x_read_one_reg(&p_bk953x_object->mid_bk953x_object, BK953X_DEVICE_ID, 0x3D, &value);
        if(err_code)
        {
            trace_warn("bk953x_rx_adpcm_mode_set read fail %d\n\r",err_code);
        }

        CLR_BIT(value, 14);
        if(ADPCM_ZERO == adpcm_mode)
        {
            SET_BIT(value,14);
        }

        err_code = mid_bk953x_write_one_reg(&p_bk953x_object->mid_bk953x_object, BK953X_DEVICE_ID, 0x3D, &value);
        if(err_code)
        {
            trace_error("bk953x_rx_adpcm_mode_set write error %d\n\r",err_code);
            return err_code;
        }
    }
    else
    {

    }
}

int bk953x_rx_plc_enable(bk953x_object_t *p_bk953x_object, bool enable_status)
{
    int err_code = 0;
    uint32_t value = 0;

    if(!p_bk953x_object)
    {
        return -EINVAL;
    }

    if(p_bk953x_object->chip_id == BK9532_CHID_ID)
    {
        err_code = mid_bk953x_read_one_reg(&p_bk953x_object->mid_bk953x_object, BK953X_DEVICE_ID, 0x3B, &value);
        if(err_code)
        {
            trace_warn("bk953x_rx_plc_enable read fail %d\n\r",err_code);
        }

        CLR_BIT(value, 19);

        if(enable_status)
        {
            SET_BIT(value,19);
        }

        err_code = mid_bk953x_write_one_reg(&p_bk953x_object->mid_bk953x_object, BK953X_DEVICE_ID, 0x3B, &value);
        if(err_code)
        {
            trace_error("bk953x_rx_plc_enable write error %d\n\r",err_code);
            return err_code;
        }

        bk953x_rx_plc_reset(p_bk953x_object);
    }
    else
    {

    }

}



/**
 * @brief BK953X 软复位
 */
int bk953x_soft_reset(bk953x_object_t *p_bk953x_object)
{
    int err_code = 0;
    uint32_t value = 0;
    if(p_bk953x_object->chip_id == BK9532_CHID_ID)
    {
        err_code = mid_bk953x_read_one_reg(&p_bk953x_object->mid_bk953x_object, BK953X_DEVICE_ID, 0x3F, &value);
        if(err_code)
        {
            trace_error("bk953x_soft_reset read error %d\n\r",err_code);
            return err_code;
        }

        CLR_BIT(value,5);
        err_code = mid_bk953x_write_one_reg(&p_bk953x_object->mid_bk953x_object, BK953X_DEVICE_ID, 0x3F, &value);
        if(err_code)
        {
            trace_error("bk953x_soft_reset write error %d\n\r",err_code);
            return err_code;
        }
        delay_ms(50);

        SET_BIT(value,5);
        err_code = mid_bk953x_write_one_reg(&p_bk953x_object->mid_bk953x_object, BK953X_DEVICE_ID, 0x3F, &value);
        if(err_code)
        {
            trace_error("bk953x_soft_reset write error %d\n\r",err_code);
            return err_code;
        }
        delay_ms(50);
    }
    else if(p_bk953x_object->chip_id == BK9531_CHID_ID)
    {

    }
    else
    {
        return -ENODEV;
    }

    return err_code;
}

/**
 * @brief BK953X 芯片寄存器配置
 */
int bk953x_config_init(bk953x_object_t *p_bk953x_object)
{
    int err_code = 0;
    uint8_t i = 0;

    for(i = 0 ; i < ARRAY_SIZE(g_bk9532_init_config) ; i ++)
    {
        err_code = mid_bk953x_write_one_reg(&p_bk953x_object->mid_bk953x_object, BK953X_DEVICE_ID, g_bk9532_init_config[i].reg, &g_bk9532_init_config[i].value);
        if(err_code)
        {
            trace_warn("bk953x_config_init  wite reg 0x%02x fail\n\r",g_bk9532_init_config[i].reg);
        }
    }

    delay_ms(50);

    err_code = bk953x_soft_reset(p_bk953x_object);

    return err_code;
}


int bk953x_chip_id_get(bk953x_object_t *p_bk953x_object)
{
    uint32_t value = 0;
    uint8_t rty = 0;

    int err_code = 0;

    /* 重试 5 次 */
    for(rty = 0; rty < 5; rty++)
    {
        err_code = mid_bk953x_read_one_reg(&p_bk953x_object->mid_bk953x_object, BK953X_DEVICE_ID, REG_CHIP_ID, &value);
        if(err_code == 0)
        {
            p_bk953x_object->chip_id = value;
            break;
        }
        delay_ms(100);
    }

    trace_debug("bk953x_chip_id_get err_code = %d , chip_id = 0x%08x\n\r",err_code,p_bk953x_object->chip_id);
    return err_code;
}

void bk953x_res_init(bk953x_object_t *p_bk953x_object)
{
    mid_bk953x_res_init(&p_bk953x_object->mid_bk953x_object);
}

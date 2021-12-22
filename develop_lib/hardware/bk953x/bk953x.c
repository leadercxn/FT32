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

#define MID_BK953X_READ(reg,p_data)     \
{                                       \
    err_code = mid_bk953x_read_one_reg(&p_bk953x_object->mid_bk953x_object, BK953X_DEVICE_ID, reg, p_data);   \
    if(err_code)                        \
    {                                   \
        trace_error("mid_bk953x_read reg 0x%02x error %d\n\r", reg ,err_code);                         \
        return err_code;               \
    }                                   \
}                                       \
            

#define MID_BK953X_WRITE(reg,p_data)    \
{                                       \
    err_code = mid_bk953x_write_one_reg(&p_bk953x_object->mid_bk953x_object, BK953X_DEVICE_ID, reg, p_data);   \
    if(err_code)                        \
    {                                   \
        trace_error("mid_bk953x_write reg 0x%02x  error %d\n\r",reg ,err_code);                         \
        return err_code;               \
    }                                   \
}                                       \


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
    {0x38 , 0x40D7D5F7 },   //Preamble
    {0x39 , 0x00000000 },   //ID_code
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

bk953x_reg_value_t g_bk9531_init_config[] = {
    {0x00 , 0x1C440C88},
    {0x01 , 0x04CF0057},
    {0x02 , 0x8990E02F},
//    {0x03 , 0x341206FF},    //UBAND,
    {0x03 , 0x341216FF},    //for cxn test U段,6分频
    {0x04 , 0x53880044},
    {0x05 , 0x00280380},
    {0x06 , 0x5BEDFB00},
    {0x07 , 0x1C400000},
    {0x08 , 0x00080100},
    {0x09 , 0x00007EFF},
    {0x0A , 0x0F3A3030},
    {0x0B , 0x0006C3FF},
    {0x0C , 0x00000008},
//  {0x0D , 0x3A980000},
    {0x0D , 0x4D260000},    //for cxn test , 632MHz

    {0x30 , 0x28282828},
    {0x31 , 0xD0000028},
    {0x32 , 0x10060064},
    {0x33 , 0x48808D82},
    {0x34 , 0x0B021108},
    {0x35 , 0x70500080},
    {0x36 , 0x0F801E04},
    {0x37 , 0x00000000},
    {0x38 , 0x00000000},    //ID_code
    {0x39 , 0x03D7D5F7},    //Preamble
    {0x3A , 0xC0250074},
    {0x3B , 0x9525003B},
    {0x3C , 0x9525003C},
    {0x3D , 0x9525003C},
    {0x3E , 0x00F867C3},
    {0x3F , 0x800F0000},

    {0x70 , 0x00009531},
    {0x71 , 0x18A40810},
    {0x72 , 0x00000000},
    {0x77 , 0x00070051},
    {0x78 , 0x00000008},
};


/**
 * @brief 接收软复位
 */
static int bk953x_rx_reset(bk953x_object_t *p_bk953x_object)
{
    int err_code = 0;
    uint32_t value = 0;

    IS_NULL(p_bk953x_object);

    if(p_bk953x_object->chip_id == BK9532_CHID_ID)
    {
        MID_BK953X_READ(0x3F, &value);

        CLR_BIT(value,31);

        MID_BK953X_WRITE(0x3F,&value);

        delay_ms(10);

        SET_BIT(value,31);

        MID_BK953X_WRITE(0x3F,&value);

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

    IS_NULL(p_bk953x_object);

    if(p_bk953x_object->chip_id == BK9532_CHID_ID)
    {
        MID_BK953X_READ(0x3F, &value);

        SET_BIT(value,28);

        MID_BK953X_WRITE(0x3F, &value);

        delay_ms(10);

        CLR_BIT(value,28);

        MID_BK953X_WRITE(0x3F, &value);

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

    IS_NULL(p_bk953x_object);

    if(p_bk953x_object->chip_id == BK9532_CHID_ID)
    {
        /* Tune the RF loop LDO voltage to 0x0 */
        CLR_BIT(g_bk9532_init_config[6].value, 29);
        CLR_BIT(g_bk9532_init_config[6].value, 30);
        CLR_BIT(g_bk9532_init_config[6].value, 31);

        MID_BK953X_WRITE(0x06, &g_bk9532_init_config[6].value);

        delay_ms(1);

        /* Enable calibration clock */
        SET_BIT(g_bk9532_init_config[7].value, 25);

        MID_BK953X_WRITE(0x07, &g_bk9532_init_config[7].value);

        /*Calibrate RF VCO*/
        CLR_BIT(g_bk9532_init_config[3].value, 22);

        MID_BK953X_WRITE(0x03, &g_bk9532_init_config[3].value);
    
        SET_BIT(g_bk9532_init_config[3].value, 22);

        MID_BK953X_WRITE(0x03, &g_bk9532_init_config[3].value);

        delay_ms(5);

        /* Calibrate Digital VCO */
        CLR_BIT(g_bk9532_init_config[4].value, 25);

        MID_BK953X_WRITE(0x04, &g_bk9532_init_config[4].value);

        SET_BIT(g_bk9532_init_config[4].value, 25);

        MID_BK953X_WRITE(0x04, &g_bk9532_init_config[4].value);

        /* Disable calibration clock */
        CLR_BIT(g_bk9532_init_config[7].value, 25);

        MID_BK953X_WRITE(0x07, &g_bk9532_init_config[7].value);

        delay_ms(2);

         /* load the default RF loop LDO voltage */
        SET_BIT(g_bk9532_init_config[6].value, 29);
        SET_BIT(g_bk9532_init_config[6].value, 30);
        SET_BIT(g_bk9532_init_config[6].value, 31);

        MID_BK953X_WRITE(0x06, &g_bk9532_init_config[6].value);
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
    IS_NULL(p_bk953x_object);
    IS_NULL(p_freq_chan_object);

    p_bk953x_object->band_type = p_freq_chan_object->band_type;
    p_bk953x_object->freq_chan_index = p_freq_chan_object->chan_index;

    int err_code = 0;
    if(p_bk953x_object->chip_id == BK9532_CHID_ID)
    {
        /* bit[15:13] = 001, 6分频 */
        CLR_BIT(g_bk9532_init_config[3].value, 15);
        CLR_BIT(g_bk9532_init_config[3].value, 14);
        SET_BIT(g_bk9532_init_config[3].value, 13);

        /* bit[21:20] = 01, U段 */
        CLR_BIT(g_bk9532_init_config[3].value, 21);
        SET_BIT(g_bk9532_init_config[3].value, 20);

        MID_BK953X_WRITE(0x03, &g_bk9532_init_config[3].value);
        MID_BK953X_WRITE(0x0D, &p_freq_chan_object->reg_value);

        bk953x_rx_calibration_trigger(p_bk953x_object);
        bk953x_rx_reset(p_bk953x_object);
        bk953x_rx_plc_reset(p_bk953x_object);
    }
    else
    {

    }

    return err_code;
}

/**
 * @brief  bk953x设置接收天线的模式
 * 
 */
int bk953x_rx_antena_set(bk953x_object_t *p_bk953x_object, antenna_type_e antenna_type)
{
    int err_code = 0;
    uint32_t value = 0;

    IS_NULL(p_bk953x_object);

    p_bk953x_object->antenna_type = antenna_type;

    if(p_bk953x_object->chip_id == BK9532_CHID_ID)
    {
        MID_BK953X_READ(0x3F, &value);

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

        MID_BK953X_WRITE(0x3F, &value);
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

    IS_NULL(p_bk953x_object);

    if(p_bk953x_object->chip_id == BK9532_CHID_ID)
    {
        MID_BK953X_READ(0x3D, &value);

        CLR_BIT(value, 14);
        if(ADPCM_ZERO == adpcm_mode)
        {
            SET_BIT(value,14);
        }

        MID_BK953X_WRITE(0x3D, &value);
    }
    else
    {

    }

    return err_code;
}

int bk953x_rx_plc_enable(bk953x_object_t *p_bk953x_object, bool enable_status)
{
    int err_code = 0;
    uint32_t value = 0;

    IS_NULL(p_bk953x_object);

    if(p_bk953x_object->chip_id == BK9532_CHID_ID)
    {
        MID_BK953X_READ(0x3B, &value);

        CLR_BIT(value, 19);

        if(enable_status)
        {
            SET_BIT(value,19);
        }

        MID_BK953X_WRITE(0x3B, &value);

        bk953x_rx_plc_reset(p_bk953x_object);
    }
    else
    {

    }

    return err_code;
}

int bk953x_rx_reverb_enable(bk953x_object_t *p_bk953x_object, bool enable_status)
{
    int err_code = 0;
    uint32_t value = 0;

    IS_NULL(p_bk953x_object);

    if(p_bk953x_object->chip_id == BK9532_CHID_ID)
    {
        MID_BK953X_READ(0x36, &value);

        if(enable_status)
        {
            CLR_BIT(value, 6);
            SET_BIT(value, 25);

            MID_BK953X_WRITE(0x36, &value);

            CLR_BIT(value, 25);
        }
        else
        {
            SET_BIT(value, 6);
        }

        MID_BK953X_WRITE(0x36, &value);
    }
    else
    {

    }

    return err_code;
}

/**
 * @brief eq_gain
 */
int bk953x_rx_volume_set(bk953x_object_t *p_bk953x_object, uint8_t vol)
{
    int err_code = 0;
    uint32_t value = 0;

    IS_NULL(p_bk953x_object);

    if(vol > 31)
    {
        vol = 31;
    }

    if(p_bk953x_object->chip_id == BK9532_CHID_ID)
    {
        MID_BK953X_READ(0x32, &value);

        /**
         * eq_gain & duf_gain
         */
        value &= ~ 0x3ff;

        /**
         * duf_gain
         */
        value |= 0x07;

        /**
         * eq_gain
         */
        value |= ((uint32_t) vol << 5);

        MID_BK953X_WRITE(0x32, &value);
    }
    else
    {

    }

    return err_code;
}

/**
 * @brief mute enable
 */
int bk953x_mute_enable(bk953x_object_t *p_bk953x_object, bool enable_status)
{
    int err_code = 0;
    uint32_t value = 0;

    IS_NULL(p_bk953x_object);

    if(p_bk953x_object->chip_id == BK9532_CHID_ID)
    {
        MID_BK953X_READ(0x36, &value);

        SET_BIT(value, 13);

        if(enable_status)
        {
            CLR_BIT(value, 13);
        }

        MID_BK953X_WRITE(0x36, &value);

        /**
         * BK953X GPIO4 作为静音输出IO
         */
#ifdef  BK953X_GPIO4_MUTE_FUN
        MID_BK953X_READ(0x31, &value);

        CLR_BIT(value, 9);

        if(!enable_status)
        {
            SET_BIT(value, 9);
        }

        MID_BK953X_WRITE(0x31, &value);
#endif

    }
    else
    {

    }

    return err_code;
}

/**
 * @brief afc mode
 */
int bk953x_rx_afc_enable(bk953x_object_t *p_bk953x_object, bool enable_status)
{
    int err_code = 0;
    uint32_t value = 0;

    IS_NULL(p_bk953x_object);

    if(p_bk953x_object->chip_id == BK9532_CHID_ID)
    {
        MID_BK953X_READ(0x3f, &value);

        CLR_BIT(value, 26);

        if(enable_status)
        {
            SET_BIT(value, 26);
        }

        MID_BK953X_WRITE(0x3f, &value);
    }
    else
    {

    }

    return err_code;
}

/**
 * @brief i2s configure & open
 */
int bk953x_rx_i2s_open(bk953x_object_t *p_bk953x_object, bk953x_pcm_config_t *p_pcm_config)
{
    int err_code = 0;
    uint32_t value = 0;

    IS_NULL(p_bk953x_object);
    IS_NULL(p_pcm_config);

    if(p_bk953x_object->chip_id == BK9532_CHID_ID)
    {
        /* 0x30 */
        MID_BK953X_READ(0x30, &value);

        if(p_pcm_config->mode == PCM_MASTER)
        {
            p_pcm_config->bclk = PCM_SCK_O;
            p_pcm_config->lrclk = PCM_LRCK_O;
            SET_BIT(value, 6);
            SET_BIT(value, 26);
        }
        else
        {
            p_pcm_config->bclk = PCM_SCK_I;
            p_pcm_config->lrclk = PCM_LRCK_I;
            value |= 0x00007D7D;
        }

        if(p_pcm_config->data == PCM_SDA_I)
        {
            value |= 0x007D0000;
        }
        else
        {
            value |= 0x00400000;
        }

        MID_BK953X_WRITE(0x30, &value);

        /* 0x31 */
        MID_BK953X_READ(0x31, &value);

        value &= 0xfffe00ff;
        value |= (((uint32_t)p_pcm_config->data << 14)|((uint32_t)p_pcm_config->bclk << 11)|((uint32_t)p_pcm_config->lrclk << 8));

        MID_BK953X_WRITE(0x31, &value);

        /* 0x36 */
        MID_BK953X_READ(0x36, &value);

        value &= 0x07ffffff;
        value |= (((uint32_t)p_pcm_config->mode << 27)|(1 << 26));

        MID_BK953X_WRITE(0x36, &value);

        /* 0x37 */
        value = 0x3E009800;
        MID_BK953X_WRITE(0x37, &value);

        /* 0x3F */
        MID_BK953X_READ(0x3F, &value);

        if(p_pcm_config->channel == PCM_LEFT)
        {
            SET_BIT(value, 4);
            SET_BIT(value, 3);
        }
        else if(p_pcm_config->channel == PCM_RIGHT)
        {
            SET_BIT(value, 4);
            CLR_BIT(value, 3);
        }
        else
        {
            CLR_BIT(value, 4);
        }

        MID_BK953X_WRITE(0x3F, &value);
    }
    else
    {

    }

    return err_code;
}

/**
 * @brief 获取当前通信信号质量
 * 
 * @param p_rssi[out]
 */
int bk953x_rx_rssi_get(bk953x_object_t *p_bk953x_object, uint8_t *p_rssi)
{
    int err_code = 0;
    uint32_t value = 0;

    IS_NULL(p_bk953x_object);
    IS_NULL(p_rssi);

    if(p_bk953x_object->chip_id == BK9532_CHID_ID)
    {
        MID_BK953X_READ(0x75, &value);
    }
    else
    {

    }

    *p_rssi = (uint8_t)value;

    return err_code;
}

/**
 * @brief 获取当前通信音量大小
 * 
 * @param p_vol[out]
 */
int bk953x_rx_vol_get(bk953x_object_t *p_bk953x_object, uint16_t *p_vol)
{
    int err_code = 0;
    uint32_t value = 0;

    IS_NULL(p_bk953x_object);
    IS_NULL(p_vol);

    if(p_bk953x_object->chip_id == BK9532_CHID_ID)
    {
        MID_BK953X_READ(0x79, &value);
    }
    else
    {

    }

    *p_vol = (uint16_t)value;

    return err_code;
}

/**
 * @brief 获取bk寄存器通信的用户数据
 * 
 * @param p_data[out]
 */
int bk953x_user_data_get(bk953x_object_t *p_bk953x_object, uint16_t *p_data)
{
    int err_code = 0;
    uint32_t value = 0;

    IS_NULL(p_bk953x_object);
    IS_NULL(p_data);

    if(p_bk953x_object->chip_id == BK9532_CHID_ID)
    {
        MID_BK953X_READ(0x7C, &value);
    }
    else
    {

    }

    *p_data = (uint8_t)value;

    return err_code;
}

/**
 * @brief 获取bk寄存器中的 接收加密ID
 * 
 * @param p_rx_id[out]
 */
int bk953x_rx_id_get(bk953x_object_t *p_bk953x_object, uint32_t *p_rx_id)
{
    int err_code = 0;
    uint32_t value = 0;

    IS_NULL(p_bk953x_object);
    IS_NULL(p_rx_id);

    if(p_bk953x_object->chip_id == BK9532_CHID_ID)
    {
        MID_BK953X_READ(0x39, &value);
    }
    else
    {

    }

    *p_rx_id = value;

    return err_code;
}

/**
 * @brief 设置bk寄存器中的 接收加密ID
 * 
 * @param p_rx_id[in]
 */
int bk953x_rx_id_set(bk953x_object_t *p_bk953x_object, uint32_t *p_rx_id)
{
    int err_code = 0;

    IS_NULL(p_bk953x_object);
    IS_NULL(p_rx_id);

    if(p_bk953x_object->chip_id == BK9532_CHID_ID)
    {
        MID_BK953X_WRITE(0x39, p_rx_id);
    }
    else
    {

    }

    return err_code;
}

int bk953x_rx_spec_data_get(bk953x_object_t *p_bk953x_object, uint8_t *p_spec_data)
{
    int err_code = 0;
    uint32_t value = 0;

    IS_NULL(p_bk953x_object);
    IS_NULL(p_spec_data);

    if(p_bk953x_object->chip_id == BK9532_CHID_ID)
    {
        MID_BK953X_READ(0x7C, &value);

        *p_spec_data = (uint8_t)value;
    }
    else
    {

    }

    return err_code;
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
        MID_BK953X_READ(0x3F, &value);

        CLR_BIT(value,5);

        MID_BK953X_WRITE(0x3F, &value);

        delay_ms(50);

        SET_BIT(value,5);

        MID_BK953X_WRITE(0x3F, &value);
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
 * @brief 
 * 
 */
int bk953x_tx_trigger(bk953x_object_t *p_bk953x_object)
{
    int err_code = 0;
    uint32_t value = 0;

    IS_NULL(p_bk953x_object);

    if(p_bk953x_object->chip_id == BK9532_CHID_ID)
    {

    }
    else if(p_bk953x_object->chip_id == BK9531_CHID_ID)
    {
        uint32_t reg_val_bak = g_bk9531_init_config[0x0A].value;

        g_bk9531_init_config->value &= 0xFFFFFF00;

        MID_BK953X_WRITE(0x0A, &g_bk9531_init_config[0x0A].value);

        //Set ddf_en=0 for tx_trigger
        MID_BK953X_READ(0x35, &value);
        CLR_BIT(value,7);
        MID_BK953X_WRITE(0x35, &value);

        //Set tx_en=0 for tx_trigger
        MID_BK953X_READ(0x3F, &value);
        CLR_BIT(value,31);
        MID_BK953X_WRITE(0x3F, &value);

        //Set tx_en=0 another tx enable, from hds
        MID_BK953X_READ(0x39, &value);
        CLR_BIT(value,24);
        MID_BK953X_WRITE(0x39, &value);

        //Enable calibration clock
        SET_BIT(g_bk9531_init_config[7].value, 25);
        CLR_BIT(g_bk9531_init_config[7].value, 28);
        MID_BK953X_WRITE(0x07, &g_bk9531_init_config[7].value);

        //Calibrate RF VCO
        CLR_BIT(g_bk9531_init_config[3].value, 22);
        MID_BK953X_WRITE(0x03, &g_bk9531_init_config[3].value);
        delay_ms(2);

        SET_BIT(g_bk9531_init_config[3].value, 22);
        MID_BK953X_WRITE(0x03, &g_bk9531_init_config[3].value);
        delay_ms(2);
        
        CLR_BIT(g_bk9531_init_config[3].value, 22);
        MID_BK953X_WRITE(0x03, &g_bk9531_init_config[3].value);
        delay_ms(60);

        //Calibrate Digital VCO
        CLR_BIT(g_bk9531_init_config[4].value, 25);
        MID_BK953X_WRITE(0x04, &g_bk9531_init_config[4].value);
        SET_BIT(g_bk9531_init_config[3].value, 25);
        MID_BK953X_WRITE(0x04, &g_bk9531_init_config[4].value);

        //Disable calibration clock
        CLR_BIT(g_bk9531_init_config[7].value, 25);
        SET_BIT(g_bk9531_init_config[7].value, 28);
        MID_BK953X_WRITE(0x07, &g_bk9531_init_config[4].value);

        //Set ddf_en=1 for tx_trigger
        MID_BK953X_READ(0x35, &value);
        SET_BIT(value,7);
        MID_BK953X_WRITE(0x35, &value);

        //Set tx_en=1 for tx_trigger
        MID_BK953X_READ(0x3F, &value);
        SET_BIT(value,31);
        MID_BK953X_WRITE(0x3F, &value);

        //Set tx_en=1 another tx enable, from hds
        MID_BK953X_READ(0x39, &value);
        SET_BIT(value,24);
        MID_BK953X_WRITE(0x39, &value);

        MID_BK953X_WRITE(0x0A, &reg_val_bak);
    }
    else
    {
        return -ENODEV;
    }

    return err_code;
}

int bk953x_tx_freq_chan_set(bk953x_object_t *p_bk953x_object, freq_chan_object_t *p_freq_chan_object)
{
    int err_code = 0;
    uint32_t value = 0;

    if(p_bk953x_object->chip_id == BK9532_CHID_ID)
    {

    }
    else if(p_bk953x_object->chip_id == BK9531_CHID_ID)
    {
        CLR_BIT(g_bk9531_init_config[3].value, 15);
        CLR_BIT(g_bk9531_init_config[3].value, 14);
        CLR_BIT(g_bk9531_init_config[3].value, 13);

        CLR_BIT(g_bk9531_init_config[3].value, 21);
        SET_BIT(g_bk9531_init_config[3].value, 20);
        MID_BK953X_WRITE(0x03, &g_bk9531_init_config[3].value);

        value = 0x4D260000; //632MHz
        MID_BK953X_WRITE(0x0D, &value);

        bk953x_tx_trigger(p_bk953x_object);
    }

    return err_code;
}

int bk953x_tx_spec_data_set(bk953x_object_t *p_bk953x_object , uint8_t data)
{
    int err_code = 0;
    uint32_t value = 0;

    if(p_bk953x_object->chip_id == BK9532_CHID_ID)
    {

    }
    else if(p_bk953x_object->chip_id == BK9531_CHID_ID)
    {
        //Set ddf_en=0 for tx_trigger
        MID_BK953X_READ(0x3A, &value);
        value &= 0xFFFFFF00;

        value |= data;
        MID_BK953X_WRITE(0x3A, &value);
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
    uint32_t value =0;

    if(p_bk953x_object->chip_id == BK9532_CHID_ID)
    {
        for(i = 0 ; i < ARRAY_SIZE(g_bk9532_init_config) ; i ++)
        {
            err_code = mid_bk953x_write_one_reg(&p_bk953x_object->mid_bk953x_object, BK953X_DEVICE_ID, g_bk9532_init_config[i].reg, &g_bk9532_init_config[i].value);
            if(err_code)
            {
                trace_warn("bk953x_config_init  wite reg 0x%02x fail\n\r",g_bk9532_init_config[i].reg);
            }
        }

        delay_ms(100);

        err_code = bk953x_soft_reset(p_bk953x_object);
    
        trace_debug("bk953x_soft_reset  done\n\r");

        /**
         * 先粗暴的配置
         */
#if 1
        MID_BK953X_READ(0x38, &value);
        value &= 0x00ffffff;
        value |= 0x55;      //设晶振振荡电容调整初值 2019-08-15
        MID_BK953X_WRITE(0x38, &value);

        freq_chan_object_t freq_chan_obj;

        freq_chan_obj.chan_index = 1;
        freq_chan_obj.reg_value = 0x4D2B1EB8;   //632Mhz

        bk953x_freq_chan_set(p_bk953x_object, &freq_chan_obj);

        bk953x_rx_afc_enable(p_bk953x_object,false);

        uint8_t xtal_tab[5] = {31,43,55,67,79};           //频偏测试表格

        uint8_t rec_spec_data = 0;

        for(i = 0; i < 5; i ++)
        {
            MID_BK953X_READ(0x38, &value);

            value &= 0x00ffffff;
            value |= xtal_tab[i];

            MID_BK953X_WRITE(0x38, &value);

            delay_ms(15);

            MID_BK953X_READ(0x7C, &value);
            if(!IS_SET(value,27))
            {
                rec_spec_data = value & 0xff;

                trace_debug("frame_err_ind success , i = %d, rec_spec_data = 0x%02x, value = 0x%08x\n\r",i , rec_spec_data,value);

                delay_ms(60);
                bk953x_rx_afc_enable(p_bk953x_object,true);
                break;
            }
        }

        if(i >= 5)
        {
            trace_error("frame_err_ind fail , i = %d\n\r",i);
        }
#endif

    }
    else if(p_bk953x_object->chip_id == BK9531_CHID_ID)
    {
        for(i = 0 ; i < ARRAY_SIZE(g_bk9531_init_config) ; i ++)
        {
            err_code = mid_bk953x_write_one_reg(&p_bk953x_object->mid_bk953x_object, BK953X_DEVICE_ID, g_bk9531_init_config[i].reg, &g_bk9531_init_config[i].value);
            if(err_code)
            {
                trace_warn("bk953x_config_init  wite reg 0x%02x fail\n\r",g_bk9531_init_config[i].reg);
            }
        }

#if 1
        /**
         * 先粗暴的配置
         */
        bk953x_tx_trigger(p_bk953x_object);

        bk953x_tx_freq_chan_set(p_bk953x_object, NULL);
#endif
        trace_debug("bk9531_config_init  done\n\r");
    }


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

        delay_ms(50);
    }

    trace_debug("bk953x_chip_id_get err_code = %d , chip_id = 0x%08x\n\r",err_code,p_bk953x_object->chip_id);
    return err_code;
}

void bk953x_res_init(bk953x_object_t *p_bk953x_object)
{
    mid_bk953x_res_init(&p_bk953x_object->mid_bk953x_object);
}

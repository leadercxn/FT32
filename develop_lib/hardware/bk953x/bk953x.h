#ifndef __BK953X_H
#define __BK953X_H

#include "mid_bk953x.h"

/**
 * BK953X GPIO4 作为静音输出IO
 */
#define  BK953X_GPIO4_MUTE_FUN

typedef enum
{
    BK953X_SAMPLE_RATE_48K,
    BK953X_SAMPLE_RATE_32K,
    BK953X_SAMPLE_RATE_24K,
    BK953X_SAMPLE_RATE_12K,
} bk953x_sample_rate_e;

typedef enum
{
    BK953X_BAND_V,  //V段
    BK953X_BAND_U   //U段
} bk953x_band_type_e;

typedef enum
{
    SA_ANT1_PIN6 = 0,                   //使用PIN6作为天线输入口    2020-05-26
    SA_ANT2_PIN5,                       //使用PIN5作为天线输入口    2020-05-26
    DA_AUTO,                            //自动天线模式
} antenna_type_e;

typedef enum
{
    ADPCM_NORMAL = 0,                   //PLC常规处理
    ADPCM_ZERO,                         //PLC补0处理 
} adpcm_mode_e;

typedef struct
{
    uint8_t  reg;
    uint32_t value;
} bk953x_reg_value_t;

typedef struct
{
    bk953x_band_type_e  band_type;
    uint16_t            chan_index;
    uint32_t            freq;
    uint32_t            reg_value;
} freq_chan_object_t;


/**
 * I2S 相关配置
 */
typedef enum
{
    PCM_SLAVE = 0,
    PCM_MASTER,
} bk953x_pcm_mode_e;

typedef enum
{
    PCM_SDA_O = 0,
    PCM_SDA_I = 4,
} bk953x_pcm_data_cfg_e;

typedef enum
{
    PCM_SCK_O = 0,
    PCM_SCK_I = 4,
} bk953x_pcm_bclk_cfg_e;

typedef enum
{
    PCM_LRCK_O = 0,
    PCM_LRCK_I = 4,
} bk953x_pcm_lrclk_cfg_e;

typedef enum
{
    PCM_LEFT = 0,       //左声道（LRCK=0时输出音频数据）
    PCM_RIGHT,          //右声道（LRCK=1时输出音频数据）
    PCM_MONO,           //单声道（在LRCK高电平和低电平期间均输出音频数据）
} bk953x_pcm_channel_cfg_e;

typedef struct
{
    bk953x_pcm_mode_e           mode;
    bk953x_pcm_data_cfg_e       data;
    bk953x_pcm_bclk_cfg_e       bclk;
    bk953x_pcm_lrclk_cfg_e      lrclk;
    bk953x_pcm_channel_cfg_e    channel;
} bk953x_pcm_config_t;


typedef void (*bk953x_hw_reset_handler) (void);
typedef struct 
{
    uint16_t                    chip_id;
    uint8_t                     device_id;
    bk953x_band_type_e          band_type;
    antenna_type_e              antenna_type;
    uint16_t                    freq_chan_index;
    mid_bk953x_t                mid_bk953x_object;
    bk953x_hw_reset_handler     hw_reset_handler;
} bk953x_object_t;


#define BK9531_CHID_ID      0x9531
#define BK9532_CHID_ID      0x9532

#define REG_CHIP_ID 0x70


int bk953x_freq_chan_set(bk953x_object_t *p_bk953x_object, freq_chan_object_t *p_freq_chan_object);
int bk953x_rx_antena_set(bk953x_object_t *p_bk953x_object, antenna_type_e antenna_type);
int bk953x_rx_reverb_enable(bk953x_object_t *p_bk953x_object, bool enable_status);
int bk953x_mute_enable(bk953x_object_t *p_bk953x_object, bool enable_status);
int bk953x_rx_rssi_get(bk953x_object_t *p_bk953x_object, uint8_t *p_rssi);
int bk953x_rx_vol_get(bk953x_object_t *p_bk953x_object, uint16_t *p_vol);
int bk953x_user_data_get(bk953x_object_t *p_bk953x_object, uint16_t *p_data);
int bk953x_rx_id_get(bk953x_object_t *p_bk953x_object, uint32_t *p_rx_id);
int bk953x_rx_id_set(bk953x_object_t *p_bk953x_object, uint32_t *p_rx_id);
int bk953x_rx_spec_data_get(bk953x_object_t *p_bk953x_object, uint8_t *p_spec_data);
int bk953x_soft_reset(bk953x_object_t *p_bk953x_object);

int bk953x_tx_spec_data_set(bk953x_object_t *p_bk953x_object , uint8_t data);

int bk953x_config_init(bk953x_object_t *p_bk953x_object);
int bk953x_chip_id_get(bk953x_object_t *p_bk953x_object);
void bk953x_res_init(bk953x_object_t *p_bk953x_object);


#endif

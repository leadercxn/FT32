#ifndef __BK953X_H
#define __BK953X_H

#include "mid_bk953x.h"

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




#define BK953X_DEVICE_ID    0x26
#define BK9531_CHID_ID      0x9531
#define BK9532_CHID_ID      0x9532

#define REG_CHIP_ID 0x70


void bk953x_res_init(bk953x_object_t *p_bk953x_object);
int bk953x_soft_reset(bk953x_object_t *p_bk953x_object);
int bk953x_chip_id_get(bk953x_object_t *p_bk953x_object);

#endif

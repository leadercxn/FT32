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


typedef void (*bk953x_hw_reset_handler) (void);

typedef struct 
{
    uint16_t                    chip_id;
    bk953x_band_type_e          band_type;
    mid_bk953x_t                mid_bk953x_object;
    bk953x_hw_reset_handler     hw_reset_handler;
} bk953x_object_t;

typedef struct
{
    uint8_t  reg;
    uint32_t value;
} bk953x_reg_value_t;


#define BK953X_DEVICE_ID    0x26
#define BK9531_CHID_ID      0x9531
#define BK9532_CHID_ID      0x9532

#define REG_CHIP_ID 0x70


void bk953x_res_init(bk953x_object_t *p_bk953x_object);
int bk953x_soft_reset(bk953x_object_t *p_bk953x_object);
int bk953x_chip_id_get(bk953x_object_t *p_bk953x_object);

#endif

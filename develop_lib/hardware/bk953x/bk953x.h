#ifndef __BK953X_H
#define __BK953X_H


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


typedef struct 
{
    i2c_type_e i2c_type;
    uint8_t    device_id;
    uint16_t   chip_id;
    bk953x_band_type_e band_type;
} bk953x_object_t;

typedef struct
{
    uint8_t  reg;
    uint32_t value;
} bk953x_reg_value_t;

bk953x_reg_value_t g_bk9532_init_config[54] = {
    {0x00 , 0xDFFFFFF8 },
    {0x01 , 0x04D28057 },
    {0x01 , 0x08990E028 },
};


#endif

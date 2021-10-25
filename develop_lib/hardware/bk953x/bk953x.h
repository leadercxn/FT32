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


#endif

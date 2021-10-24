#ifndef __MID_BK953X_H
#define __MID_BK953X_H


typedef enum
{
    I2C_TYPE_I2C1,
    I2C_TYPE_I2C2,
    I2C_TYPE_I2C3,
    I2C_TYPE_I2C4,
    I2C_TYPE_VIRT1,
    I2C_TYPE_VIRT2,
} i2c_type_e;

int mid_bk953x_read_one_reg(i2c_type_e i2c_type,uint8_t device_id,uint8_t reg,uint32_t *p_data);
int mid_bk953x_write_one_reg(i2c_type_e i2c_type,uint8_t device_id,uint8_t reg,uint32_t *p_data);

#endif

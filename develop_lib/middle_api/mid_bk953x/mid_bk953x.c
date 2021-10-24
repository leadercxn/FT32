#include "stdbool.h"

#ifdef FT32
#include "ft32f0xx.h"
#endif

#include "mid_bk953x.h"


#ifdef FT32
//ft32芯片依赖的头文件
#include "ft_lib.h"

//ft32做成bk953x芯片的API
static int ft_virt1_i2c_bk953x_read_one_reg(uint8_t device_id,uint8_t reg,uint32_t *p_data)
{
    uint8_t temp = 0;
    uint8_t *p = (uint8_t *)p_data;
    int err = 0;

    temp = (reg << 1) | 0x01;

    virt1_i2c_start();

    virt1_i2c_send_byte(device_id);
    err = virt1_i2c_wait_ack();
    if(err)
    {
        return err;
    }

    virt1_i2c_send_byte(temp);
    err = virt1_i2c_wait_ack();
    if(err)
    {
        return err;
    }

    p[0] = virt1_i2c_read_byte(true);
    p[1] = virt1_i2c_read_byte(true);
    p[2] = virt1_i2c_read_byte(true);
    p[3] = virt1_i2c_read_byte(false);

    return err;
}

int ft_virt1_i2c_bk953x_write_one_reg(uint8_t device_id,uint8_t reg,uint32_t *p_data)
{
    uint8_t temp = 0;
    uint8_t *p = (uint8_t *)p_data;
    int err = 0;
    uint8_t i = 0;

    temp = (reg << 1) & 0xfe;

    virt1_i2c_start();

    virt1_i2c_send_byte(device_id);
    err = virt1_i2c_wait_ack();
    if(err)
    {
        return err;
    }

    virt1_i2c_send_byte(temp);
    err = virt1_i2c_wait_ack();
    if(err)
    {
        return err;
    }

    for(i = 0; i < sizeof(uint32_t); i++)
    {
        virt1_i2c_send_byte(p[i]);
        err = virt1_i2c_wait_ack();
        if(err)
        {
            return err;
        }
    }

    virt1_i2c_stop();

    return err;
}

int ft_i2c1_i2c_bk953x_read_one_reg(uint8_t device_id,uint8_t reg,uint32_t *p_data)
{
    int err = 0;

    return err;
}

int ft_i2c1_i2c_bk953x_write_one_reg(uint8_t device_id,uint8_t reg,uint32_t *p_data)
{
    int err = 0;

    return err;
}

#endif


int mid_bk953x_read_one_reg(i2c_type_e i2c_type,uint8_t device_id,uint8_t reg,uint32_t *p_data)
{
    int err = 0;

#ifdef FT32
    switch(i2c_type)
    {
        case I2C_TYPE_I2C1:

            break;

        case I2C_TYPE_VIRT1:
            err = ft_virt1_i2c_bk953x_read_one_reg(device_id,reg,p_data);
            break;
    }
#endif

    return err;
}

int mid_bk953x_write_one_reg(i2c_type_e i2c_type,uint8_t device_id,uint8_t reg,uint32_t *p_data)
{
    int err = 0;
#ifdef FT32
    switch(i2c_type)
    {
        case I2C_TYPE_I2C1:

            break;

        case I2C_TYPE_VIRT1:
            err = ft_virt1_i2c_bk953x_write_one_reg(device_id,reg,p_data);
            break;
    }
#endif
    return err;
}



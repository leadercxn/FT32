#include "stdbool.h"

#ifdef FT32
#include "ft_lib.h"
#endif

#include "board_config.h"
#include "mid_bk953x.h"


#ifdef FT32

/* VIRT */
static int ft_virt_i2c_bk953x_read_one_reg(ft_virt_i2c_t *p_ft_virt_i2c, uint8_t device_id, uint8_t reg, uint32_t *p_data)
{
    uint8_t temp = 0;
    uint8_t *p = (uint8_t *)p_data;
    int err = 0;

    temp = (reg << 1) | 0x01;

    ft_virt_i2c_start(p_ft_virt_i2c);

    ft_virt_i2c_send_byte(p_ft_virt_i2c, device_id);

    err = ft_virt_i2c_wait_ack(p_ft_virt_i2c);
    if(err)
    {
        trace_error("slaver no ack!\n\r");
        return err;
    }

    ft_virt_i2c_send_byte(p_ft_virt_i2c, temp);

    err = ft_virt_i2c_wait_ack(p_ft_virt_i2c);
    if(err)
    {
        trace_error("slaver no ack!\n\r");
        return err;
    }

    //MSB
    p[3] = ft_virt_i2c_read_byte(p_ft_virt_i2c, true);
    p[2] = ft_virt_i2c_read_byte(p_ft_virt_i2c, true);
    p[1] = ft_virt_i2c_read_byte(p_ft_virt_i2c, true);
    p[0] = ft_virt_i2c_read_byte(p_ft_virt_i2c, false);

    ft_virt_i2c_stop(p_ft_virt_i2c);

    return err;
}

int ft_virt_i2c_bk953x_write_one_reg(ft_virt_i2c_t *p_ft_virt_i2c, uint8_t device_id,uint8_t reg,uint32_t *p_data)
{
    uint8_t temp = 0;
    uint8_t *p = (uint8_t *)p_data;
    int err = 0;
    int i = 0;

    temp = (reg << 1) & 0xfe;

    ft_virt_i2c_start(p_ft_virt_i2c);

    ft_virt_i2c_send_byte(p_ft_virt_i2c, device_id);
    err = ft_virt_i2c_wait_ack(p_ft_virt_i2c);
    if(err)
    {
        trace_error("slaver no ack!\n\r");
        return err;
    }

    ft_virt_i2c_send_byte(p_ft_virt_i2c, temp);

    err = ft_virt_i2c_wait_ack(p_ft_virt_i2c);
    if(err)
    {
        return err;
    }

    for(i = sizeof(uint32_t); i > 0; i--)
    {
        ft_virt_i2c_send_byte(p_ft_virt_i2c, p[i -1]);
        err = ft_virt_i2c_wait_ack(p_ft_virt_i2c);
        if(err)
        {
            trace_error("slaver no ack!\n\r");
            return err;
        }
    }

    ft_virt_i2c_stop(p_ft_virt_i2c);

    return err;
}


#endif


int mid_bk953x_read_one_reg(mid_bk953x_t *p_mid_bk953x, uint8_t device_id, uint8_t reg, uint32_t *p_data)
{
    int err = 0;

#ifdef FT32
    err = ft_virt_i2c_bk953x_read_one_reg(&p_mid_bk953x->virt_i2c_object, device_id, reg, p_data);
#endif

    return err;
}

int mid_bk953x_write_one_reg(mid_bk953x_t *p_mid_bk953x, uint8_t device_id, uint8_t reg, uint32_t *p_data)
{
    int err = 0;
#ifdef FT32
    err = ft_virt_i2c_bk953x_write_one_reg(&p_mid_bk953x->virt_i2c_object, device_id, reg, p_data);
#endif
    return err;
}


void mid_bk953x_res_init(mid_bk953x_t *p_mid_bk953x)
{
#ifdef FT32
    ft_virt_i2c_init(&p_mid_bk953x->virt_i2c_object);
#endif

}


#include "stdbool.h"

#ifdef FT32
#include "ft_lib.h"
#endif

#include "board_config.h"
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
        trace_error("slaver no ack!\n\r");
        return err;
    }

    virt1_i2c_send_byte(temp);

    err = virt1_i2c_wait_ack();
    if(err)
    {
        trace_error("slaver no ack!\n\r");
        return err;
    }

    //MSB
    p[3] = virt1_i2c_read_byte(true);
    p[2] = virt1_i2c_read_byte(true);
    p[1] = virt1_i2c_read_byte(true);
    p[0] = virt1_i2c_read_byte(false);

    virt1_i2c_stop();

    return err;
}

int ft_virt1_i2c_bk953x_write_one_reg(uint8_t device_id,uint8_t reg,uint32_t *p_data)
{
    uint8_t temp = 0;
    uint8_t *p = (uint8_t *)p_data;
    int err = 0;
    int i = 0;

    temp = (reg << 1) & 0xfe;

    virt1_i2c_start();

    virt1_i2c_send_byte(device_id);
    err = virt1_i2c_wait_ack();
    if(err)
    {
        trace_error("slaver no ack!\n\r");
        return err;
    }

    virt1_i2c_send_byte(temp);
    err = virt1_i2c_wait_ack();
    if(err)
    {
        return err;
    }

    for(i = sizeof(uint32_t); i > 0; i++)
    {
        virt1_i2c_send_byte(p[i -1]);
        err = virt1_i2c_wait_ack();
        if(err)
        {
            trace_error("slaver no ack!\n\r");
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

static void mid_bk953x_hw_reset(void)
{
#ifdef FT32
    conf_gpio_output(R_BK9532_CE_PERIPH_CLK, R_BK9532_CE_PORT, R_BK9532_CE_PIN);
    conf_gpio_output(L_BK9532_CE_PERIPH_CLK, L_BK9532_CE_PORT, L_BK9532_CE_PIN);

    //复位要适当的延时，别太快
    set_gpio_value(L_BK9532_CE_PORT , L_BK9532_CE_PIN ,0);
    set_gpio_value(R_BK9532_CE_PORT , R_BK9532_CE_PIN ,0);
    delay_ms(50);
    set_gpio_value(L_BK9532_CE_PORT , L_BK9532_CE_PIN ,1);
    set_gpio_value(R_BK9532_CE_PORT , R_BK9532_CE_PIN ,1);
    delay_ms(80);
#endif
}

void mid_bk953x_res_init(void)
{
    mid_bk953x_hw_reset();
#ifdef FT32
    virt_i2c_init();
#endif
}


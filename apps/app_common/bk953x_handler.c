#include "stdio.h"

#include "user_board.h"
#include "util.h"
#include "trace.h"

#include "hardware.h"
#include "bk953x_handler.h"


static bk953x_object_t m_l_bk9532_obj;
static bk953x_object_t m_r_bk9532_obj;

int bk9532_lr_init(void)
{
    int err_code = 0;

    m_l_bk9532_obj.i2c_type = I2C_TYPE_VIRT1;

    bk953x_res_init();

    bk953x_chip_id_get(&m_l_bk9532_obj);

    //ft_delay_ms(500);

    bk953x_chip_id_get(&m_l_bk9532_obj);

    //ft_delay_ms(500);

    bk953x_chip_id_get(&m_l_bk9532_obj);

    return err_code;
}



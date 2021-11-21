#include "stdio.h"

#include "board_config.h"
#include "bk953x_handler.h"


static bk953x_object_t m_l_bk9532_obj;
static bk953x_object_t m_r_bk9532_obj;

static gpio_object_t   m_l_bk9532_rst;
static gpio_object_t   m_r_bk9532_rst;

/**
 * @warning 复位要适当的延时，别太快
 */
static void r_bk953x_hw_reset(void)
{
    gpio_config(&m_r_bk9532_rst);

    gpio_output_set(&m_r_bk9532_rst, 0);
    delay_ms(50);
    gpio_output_set(&m_r_bk9532_rst, 1);
    delay_ms(100);
}

static void l_bk953x_hw_reset(void)
{
    gpio_config(&m_l_bk9532_rst);

    gpio_output_set(&m_l_bk9532_rst, 0);
    delay_ms(50);
    gpio_output_set(&m_l_bk9532_rst, 1);
    delay_ms(100);
}

int bk9532_lr_init(void)
{
    int err_code = 0;

#ifdef FT32
    m_l_bk9532_rst.gpio_port_periph_clk = L_BK9532_CE_PERIPH_CLK;
    m_l_bk9532_rst.p_gpio_port = L_BK9532_CE_PORT;

    m_r_bk9532_rst.gpio_port_periph_clk = R_BK9532_CE_PERIPH_CLK;
    m_r_bk9532_rst.p_gpio_port = R_BK9532_CE_PORT;
#endif

    m_l_bk9532_rst.gpio_dir = GPIO_DIR_OUTPUR;
    m_l_bk9532_rst.gpio_pin = L_BK9532_CE_PIN;

    m_r_bk9532_rst.gpio_dir = GPIO_DIR_OUTPUR;
    m_r_bk9532_rst.gpio_pin = R_BK9532_CE_PIN;



    m_r_bk9532_obj.hw_reset_handler = r_bk953x_hw_reset;
    m_l_bk9532_obj.hw_reset_handler = l_bk953x_hw_reset;

#ifdef FT32
    m_r_bk9532_obj.mid_bk953x_object.virt_i2c_object.sda_port_periph_clk = R_VIRT_SDA_GPIO_CLK;
    m_r_bk9532_obj.mid_bk953x_object.virt_i2c_object.scl_port_periph_clk = R_VIRT_SCL_GPIO_CLK;
    m_r_bk9532_obj.mid_bk953x_object.virt_i2c_object.p_sda_gpio_port = R_VIRT_SDA_GPIO_PORT;
    m_r_bk9532_obj.mid_bk953x_object.virt_i2c_object.p_scl_gpio_port = R_VIRT_SCL_GPIO_PORT;
    m_r_bk9532_obj.mid_bk953x_object.virt_i2c_object.sda_gpio_pin = R_VIRT_SDA_PIN;
    m_r_bk9532_obj.mid_bk953x_object.virt_i2c_object.scl_gpio_pin = R_VIRT_SCL_PIN;

    m_l_bk9532_obj.mid_bk953x_object.virt_i2c_object.sda_port_periph_clk = L_VIRT_SDA_GPIO_CLK;
    m_l_bk9532_obj.mid_bk953x_object.virt_i2c_object.scl_port_periph_clk = L_VIRT_SCL_GPIO_CLK;
    m_l_bk9532_obj.mid_bk953x_object.virt_i2c_object.p_sda_gpio_port = L_VIRT_SDA_GPIO_PORT;
    m_l_bk9532_obj.mid_bk953x_object.virt_i2c_object.p_scl_gpio_port = L_VIRT_SCL_GPIO_PORT;
    m_l_bk9532_obj.mid_bk953x_object.virt_i2c_object.sda_gpio_pin = L_VIRT_SDA_PIN;
    m_l_bk9532_obj.mid_bk953x_object.virt_i2c_object.scl_gpio_pin = L_VIRT_SCL_PIN;
#endif

    m_r_bk9532_obj.hw_reset_handler();
    m_l_bk9532_obj.hw_reset_handler();

    bk953x_res_init(&m_r_bk9532_obj);
    bk953x_res_init(&m_l_bk9532_obj);

    bk953x_chip_id_get(&m_r_bk9532_obj);
    bk953x_chip_id_get(&m_l_bk9532_obj);

    trace_debug("r_chip_id = 0x%08x , l_chip_id = 0x%08x\n\r",m_r_bk9532_obj.chip_id, m_l_bk9532_obj.chip_id);

    return err_code;
}



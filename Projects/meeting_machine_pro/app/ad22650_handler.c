#include "board_config.h"
#include "ad22650_handler.h"

static gpio_object_t    m_l_ad22650_en;
static gpio_object_t    m_r_ad22650_en;

void ad22650_lr_init(void)
{
#ifdef FT32
    m_l_ad22650_en.gpio_port_periph_clk = L_AD22650_EN_PORT_PERIPH_CLK;
    m_l_ad22650_en.p_gpio_port = L_AD22650_EN_PORT;

    m_r_ad22650_en.gpio_port_periph_clk = R_AD22650_EN_PORT_PERIPH_CLK;
    m_r_ad22650_en.p_gpio_port = R_AD22650_EN_PORT;
#endif
    m_l_ad22650_en.gpio_dir = GPIO_DIR_OUTPUR;
    m_l_ad22650_en.gpio_pin = L_AD22650_EN_PIN;

    m_r_ad22650_en.gpio_dir = GPIO_DIR_OUTPUR;
    m_r_ad22650_en.gpio_pin = R_AD22650_EN_PIN;

    gpio_config(&m_l_ad22650_en);
    gpio_config(&m_r_ad22650_en);

    gpio_output_set(&m_l_ad22650_en, 1);
    gpio_output_set(&m_r_ad22650_en, 1);
}

#include "board_config.h"
#include "lcd_display_handler.h"

static gpio_object_t   m_lcd_ctrl_pin = {
    .gpio_port_periph_clk = LCD_CTRL_PORT_PERIPH_CLK,
    .p_gpio_port = LCD_CTRL_PORT,
    .gpio_dir = GPIO_DIR_OUTPUR,
    .gpio_pin = LCD_CTRL_PIN,
};

static gpio_object_t   m_lcd_back_light_pin = {
    .gpio_port_periph_clk = LCD_BACK_LIGHT_PORT_PERIPH_CLK,
    .p_gpio_port = LCD_BACK_LIGHT_PORT,
    .gpio_dir = GPIO_DIR_OUTPUR,
    .gpio_pin = LCD_BACK_LIGHT_PIN,
};

void lcd_init(void)
{
    gpio_config(&m_lcd_ctrl_pin);
    gpio_config(&m_lcd_back_light_pin);
    gpio_output_set(&m_lcd_ctrl_pin, 1);
    gpio_output_set(&m_lcd_back_light_pin, 1);

    HT1621_Init();

    uint8_t Ht1621Tab[] = {0x00, 0x00, 0x00, 0x00};
    HT1621_WriteAllData(0, Ht1621Tab, 16); //清除LCD显示数据
}


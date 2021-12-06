#include "board_config.h"
#include "lcd_display_handler.h"

static uint32_t m_g_ch_left = 90;
static uint32_t m_g_ch_right = 160;
static uint32_t m_freg_left = 661;
static uint32_t m_freg_right = 677;

/**
 * 相关IO配置
 */
static lcd_display_obj_t    m_lcd_display_obj = {
    .ht162x.wr_clk_pin.gpio_port_periph_clk = HT1621_WR_PORT_PERIPH_CLK,
    .ht162x.wr_clk_pin.p_gpio_port = HT1621_WR_PORT,
    .ht162x.wr_clk_pin.gpio_dir = GPIO_DIR_OUTPUR,
    .ht162x.wr_clk_pin.gpio_pin = HT1621_WR_PIN,

    .ht162x.cs_pin.gpio_port_periph_clk = HT1621_CS_PORT_PERIPH_CLK,
    .ht162x.cs_pin.p_gpio_port = HT1621_CS_PORT,
    .ht162x.cs_pin.gpio_dir = GPIO_DIR_OUTPUR,
    .ht162x.cs_pin.gpio_pin = HT1621_CS_PIN,

    .ht162x.data_pin.gpio_port_periph_clk = HT1621_DATA_PORT_PERIPH_CLK,
    .ht162x.data_pin.p_gpio_port = HT1621_DATA_PORT,
    .ht162x.data_pin.gpio_dir = GPIO_DIR_OUTPUR,
    .ht162x.data_pin.gpio_pin = HT1621_DATA_PIN,

    .lcd_back_light_pin.gpio_port_periph_clk = LCD_BACK_LIGHT_PORT_PERIPH_CLK,
    .lcd_back_light_pin.p_gpio_port = LCD_BACK_LIGHT_PORT,
    .lcd_back_light_pin.gpio_dir = GPIO_DIR_OUTPUR,
    .lcd_back_light_pin.gpio_pin = LCD_BACK_LIGHT_PIN,

    .lcd_ctrl_pin.gpio_port_periph_clk = LCD_CTRL_PORT_PERIPH_CLK,
    .lcd_ctrl_pin.p_gpio_port = LCD_CTRL_PORT,
    .lcd_ctrl_pin.gpio_dir = GPIO_DIR_OUTPUR,
    .lcd_ctrl_pin.gpio_pin = LCD_CTRL_PIN,
};

static void digital_mode_0_set(uint8_t digital, uint8_t data, uint8_t seg_x)
{
	encode_seg_code_t seg_code;
	uint8_t com_data_h, com_data_l;
	digital_to_segdata(&seg_code, data);
	seg_code.seg_x = seg_x;
	segdata_to_segcom_mode_0(seg_code, &com_data_h, &com_data_l);

	switch (digital)
	{
        case Digital_1:
            ht162x_write(&m_lcd_display_obj.ht162x, DigitalSeg1_H, com_data_h);
            ht162x_write(&m_lcd_display_obj.ht162x, DigitalSeg1_L, com_data_l);
            break;

        case Digital_2:
            ht162x_write(&m_lcd_display_obj.ht162x, DigitalSeg2_H, com_data_h);
            ht162x_write(&m_lcd_display_obj.ht162x, DigitalSeg2_L, com_data_l);
            break;

        case Digital_3:
            ht162x_write(&m_lcd_display_obj.ht162x, DigitalSeg3_H, com_data_h);
            ht162x_write(&m_lcd_display_obj.ht162x, DigitalSeg3_L, com_data_l);
            break;

        default:
            break;
	}
}

static void digital_mode_1_Set(uint8_t digital, uint8_t data, uint8_t seg_x)
{
	encode_seg_code_t seg_code;
	uint8_t com_data_h, com_data_l;
	digital_to_segdata(&seg_code, data);
	seg_code.seg_x = seg_x;
	segdata_to_segcom_mode_1(seg_code, &com_data_h, &com_data_l);

	switch (digital)
	{
        case Digital_4:
            ht162x_write(&m_lcd_display_obj.ht162x, DigitalSeg4_H, com_data_h);
            ht162x_write(&m_lcd_display_obj.ht162x, DigitalSeg4_L, com_data_l);
            break;

        case Digital_5:
            ht162x_write(&m_lcd_display_obj.ht162x, DigitalSeg5_H, com_data_h);
            ht162x_write(&m_lcd_display_obj.ht162x, DigitalSeg5_L, com_data_l);
            break;

        case Digital_6:
            ht162x_write(&m_lcd_display_obj.ht162x, DigitalSeg6_H, com_data_h);
            ht162x_write(&m_lcd_display_obj.ht162x, DigitalSeg6_L, com_data_l);
            break;

        default:
            break;
	}
}

static void digital_mode_2_Set(uint8_t digital, uint8_t data, uint8_t seg_x)
{
	encode_seg_code_t seg_code;
	uint8_t com_data_h, com_data_l;
	digital_to_segdata(&seg_code, data);
	seg_code.seg_x = seg_x;
	segdata_to_segcom_mode_2(seg_code, &com_data_h, &com_data_l);

	switch (digital)
	{
        case Digital_7:
            ht162x_write(&m_lcd_display_obj.ht162x, DigitalSeg7_H, com_data_h);
            ht162x_write(&m_lcd_display_obj.ht162x, DigitalSeg7_L, com_data_l);
            break;

        case Digital_8:
            ht162x_write(&m_lcd_display_obj.ht162x, DigitalSeg8_H, com_data_h);
            ht162x_write(&m_lcd_display_obj.ht162x, DigitalSeg8_L, com_data_l);
            break;

        case Digital_9:
            ht162x_write(&m_lcd_display_obj.ht162x, DigitalSeg9_H, com_data_h);
            ht162x_write(&m_lcd_display_obj.ht162x, DigitalSeg9_L, com_data_l);
            break;

        case Digital_10:
            ht162x_write(&m_lcd_display_obj.ht162x, DigitalSeg10_H, com_data_h);
            ht162x_write(&m_lcd_display_obj.ht162x, DigitalSeg10_L, com_data_l);
            break;

        case Digital_12:
            ht162x_write(&m_lcd_display_obj.ht162x, DigitalSeg12_H, com_data_h);
            ht162x_write(&m_lcd_display_obj.ht162x, DigitalSeg12_L, com_data_l);
            break;

        case Digital_13:
            ht162x_write(&m_lcd_display_obj.ht162x, DigitalSeg13_H, com_data_h);
            ht162x_write(&m_lcd_display_obj.ht162x, DigitalSeg13_L, com_data_l);
            break;

        case Digital_14:
            ht162x_write(&m_lcd_display_obj.ht162x, DigitalSeg14_H, com_data_h);
            ht162x_write(&m_lcd_display_obj.ht162x, DigitalSeg14_L, com_data_l);
            break;
        case Digital_15:
            ht162x_write(&m_lcd_display_obj.ht162x, DigitalSeg15_H, com_data_h);
            ht162x_write(&m_lcd_display_obj.ht162x, DigitalSeg15_L, com_data_l);
            break;
        default:
            break;
	}
}

void digital_mode_0_display(uint32_t data)
{
	seg_data_t seg_data;
	segdata_convertor(data, &seg_data);
	digital_mode_0_set(Digital_1, seg_data.high, 1); //此处S2显示
	digital_mode_0_set(Digital_2, seg_data.mid, 0);
	digital_mode_0_set(Digital_3, seg_data.low, 0);
}

void digital_mode_1_display(uint32_t data)
{
	seg_data_t seg_data;
	segdata_convertor(data, &seg_data);
	digital_mode_1_Set(Digital_4, seg_data.high, 1);
	digital_mode_1_Set(Digital_5, seg_data.mid, 0);
	digital_mode_1_Set(Digital_6, seg_data.low, 0);
}

void display_serach_clean(void)
{
	ht162x_write(&m_lcd_display_obj.ht162x, DigitalSeg12_L, 0x00);
	ht162x_write(&m_lcd_display_obj.ht162x, DigitalSeg13_L, 0x00);
	ht162x_write(&m_lcd_display_obj.ht162x, DigitalSeg14_L, 0x00);
	ht162x_write(&m_lcd_display_obj.ht162x, DigitalSeg15_L, 0x00);
}

void display_serach(uint32_t freq)
{
	ht162x_write(&m_lcd_display_obj.ht162x, DigitalSeg12_L, 0x08);
	delay_ms(freq);
	ht162x_write(&m_lcd_display_obj.ht162x, DigitalSeg13_L, 0x08);
	delay_ms(freq);
	ht162x_write(&m_lcd_display_obj.ht162x, DigitalSeg14_L, 0x08);
	delay_ms(freq);
	ht162x_write(&m_lcd_display_obj.ht162x, DigitalSeg15_L, 0x08);
	delay_ms(freq);
	display_serach_clean();
	delay_ms(freq);
}

int lcd_display_init(void)
{
    int err_code = 0;

    ht162x_init(&m_lcd_display_obj.ht162x);
    ht162x_all_clean(&m_lcd_display_obj.ht162x);

    gpio_config(&m_lcd_display_obj.lcd_ctrl_pin);
    gpio_config(&m_lcd_display_obj.lcd_back_light_pin);
    gpio_output_set(&m_lcd_display_obj.lcd_ctrl_pin, 0);
    gpio_output_set(&m_lcd_display_obj.lcd_back_light_pin, 1);

#if 0
    digital_mode_0_set(Digital_1, 1, 1); //此处S2显示
	digital_mode_0_set(Digital_2, 0, 0);
	digital_mode_0_set(Digital_3, 0, 0);

	digital_mode_1_Set(Digital_4, 1, 0);
	digital_mode_1_Set(Digital_5, 6, 0);
	digital_mode_1_Set(Digital_6, 0, 0);
#endif
    digital_mode_0_display(m_g_ch_left);
	digital_mode_1_display(m_g_ch_right);

	digital_mode_2_Set(Digital_7, 6, 1);
	digital_mode_2_Set(Digital_8, 6, 0);
	digital_mode_2_Set(Digital_9, 1, 1); //BC

    digital_mode_2_Set(Digital_10, 7, 1); //BC

	// digital_mode_2_Set(Digital_10, 7, 1);
	// digital_mode_2_Set(Digital_10, 7, 0);
	// digital_mode_2_Set(Digital_10, 7, 0);
#if 1
	//677.700
	digital_mode_2_Set(Digital_12, 6, 1);
	digital_mode_2_Set(Digital_13, 7, 0);
	digital_mode_2_Set(Digital_14, 7, 1); //BC

    digital_mode_2_Set(Digital_15, 7, 1); //16AFCD
#endif

#if 0
    while(1)
    {
        display_serach(4000);
    }
#endif

    return err_code;
}


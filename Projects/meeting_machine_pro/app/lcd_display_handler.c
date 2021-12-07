#include "board_config.h"
#include "lcd_display_handler.h"

typedef struct
{
    uint8_t seg_index;

    uint8_t reserve : 4;
    uint8_t com4 : 1;
    uint8_t com3 : 1;
    uint8_t com2 : 1;
    uint8_t com1 : 1;
} __attribute__((__packed__)) lcd_seg_cell_t;

/* seg 表 */
static lcd_seg_cell_t m_seg_table[] = {
    {.seg_index = 0,},  //seg1
    {.seg_index = 1,},  //seg2
    {.seg_index = 2,},
    {.seg_index = 3,},
    {.seg_index = 4,},
    {.seg_index = 5,},
    {.seg_index = 6,},
    {.seg_index = 7,},
    {.seg_index = 8,},
    {.seg_index = 9,},
    {.seg_index = 10,},
    {.seg_index = 11,},
    {.seg_index = 12,},
    {.seg_index = 13,},
    {.seg_index = 14,},
    {.seg_index = 15,},
    {.seg_index = 16,},
    {.seg_index = 17,},
    {.seg_index = 18,},
    {.seg_index = 19,},
    {.seg_index = 20,},
    {.seg_index = 21,},
    {.seg_index = 22,},
    {.seg_index = 23,},
    {.seg_index = 24,},
    {.seg_index = 25,},
    {.seg_index = 26,},
    {.seg_index = 27,},
    {.seg_index = 28,},
    {.seg_index = 29,},
    {.seg_index = 30,},
    {.seg_index = 31,}, //seg32
};

static uint16_t m_l_ch_index = 1;
static uint16_t m_r_ch_index = 101;

static uint16_t m_l_ch_freq = 6320;
static uint16_t m_r_ch_freq = 6600;

static uint8_t m_l_ch_af_level = 0;
static uint8_t m_r_ch_af_level = 0;

static uint8_t m_l_ch_rf_level = 0;
static uint8_t m_r_ch_rf_level = 0;

static bool refresh = false;

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

static void l_rf_show(void)
{
    ht162x_write(&m_lcd_display_obj.ht162x, DigitalSegRF_LEFT_H, 0x01);

    ht162x_write(&m_lcd_display_obj.ht162x, DigitalSegRF_LEFT_L, 0x0f);
    ht162x_write(&m_lcd_display_obj.ht162x, DigitalSegAF_LEFT_L, 0x0f);

    ht162x_write(&m_lcd_display_obj.ht162x, DigitalSegRF_RIGHT_L, 0x0f);
    ht162x_write(&m_lcd_display_obj.ht162x, DigitalSegAF_RIGHT_L, 0x0e);
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

/**
 * @brief 显示通道数
 */
static void channel_index_lr_show(screen_lr_e lr, uint16_t index)
{
    seg_data_t seg_data;
	segdata_convertor(index, &seg_data);

    if(SCREEN_L == lr)
    {
        digital_mode_0_set(Digital_1, seg_data.high, 1); //此处S2显示
	    digital_mode_0_set(Digital_2, seg_data.mid, 0);
	    digital_mode_0_set(Digital_3, seg_data.low, 0);
    }
    else
    {
        digital_mode_1_Set(Digital_4, seg_data.high, 0);
	    digital_mode_1_Set(Digital_5, seg_data.mid, 0);
	    digital_mode_1_Set(Digital_6, seg_data.low, 0);
    }
}

/**
 * @brief 显示通道频率
 * 
 * @param [in] data 单位 百M
 */
static void channel_freq_lr_show(screen_lr_e lr, uint16_t hund_freq)
{
    uint8_t hundred = hund_freq / 1000;
    uint8_t decade = hund_freq % 1000 / 100;
    uint8_t unit =   hund_freq % 100 / 10;
    uint8_t point = hund_freq % 10;

    if(SCREEN_L == lr)
    {
        digital_mode_2_Set(Digital_7, hundred, 1);
        digital_mode_2_Set(Digital_8, decade, 0);
        digital_mode_2_Set(Digital_9, unit, 1); //BC
        digital_mode_2_Set(Digital_10, point, 1); //BC
    }
    else
    {
        digital_mode_2_Set(Digital_12, hundred, 1);
        digital_mode_2_Set(Digital_13, decade, 0);
        digital_mode_2_Set(Digital_14, unit, 1); //BC
        digital_mode_2_Set(Digital_15, point, 1); //BC
    }
}

/**
 * @brief 显示af幅度
 */
static void channel_af_lr_show(screen_lr_e lr, uint8_t level)
{
    if(SCREEN_L == lr)
    {

    }
    else
    {
        
    }
}

/**
 * @brief 显示rf幅度
 */
static void channel_rf_lr_show(screen_lr_e lr, uint8_t level)
{
    if(SCREEN_L == lr)
    {

    }
    else
    {
        
    }
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

    channel_index_lr_show(SCREEN_L, m_l_ch_index);
    channel_index_lr_show(SCREEN_R, m_r_ch_index);

    channel_freq_lr_show(SCREEN_L,m_l_ch_freq);
    channel_freq_lr_show(SCREEN_R,m_r_ch_freq);

    l_rf_show();

    trace_debug("len = %d \n\r",sizeof(lcd_seg_cell_t));

    return err_code;
}


void lcd_display_loop_task(void)
{
    if(refresh)
    {
        refresh = false;

        channel_index_lr_show(SCREEN_L, m_l_ch_index);
        channel_index_lr_show(SCREEN_R, m_r_ch_index);

        channel_freq_lr_show(SCREEN_L,m_l_ch_freq);
        channel_freq_lr_show(SCREEN_R,m_r_ch_freq);

        channel_af_lr_show(SCREEN_L, m_l_ch_af_level);
        channel_af_lr_show(SCREEN_R, m_r_ch_af_level);

        channel_rf_lr_show(SCREEN_L, m_l_ch_rf_level);
        channel_rf_lr_show(SCREEN_R, m_r_ch_rf_level);
    }
}


uint16_t channel_index_lr_get(screen_lr_e lr)
{
    if(SCREEN_L == lr)
    {
        return m_l_ch_index;
    }

    return m_r_ch_index;
}

uint16_t channel_freq_lr_get(screen_lr_e lr)
{
    if(SCREEN_L == lr)
    {
        return m_l_ch_freq;
    }

    return m_r_ch_freq;
}

void channel_index_lr_set(screen_lr_e lr, uint16_t index)
{
    if(SCREEN_L == lr)
    {
        m_l_ch_index = index;
    }
    else
    {
        m_r_ch_index = index;
    }

    refresh = true;
}

void channel_freq_lr_set(screen_lr_e lr, uint16_t freq)
{
    if(SCREEN_L == lr)
    {
        m_l_ch_freq = freq;
    }
    else
    {
        m_r_ch_freq = freq;
    }

    refresh = true;
}

void channel_af_level_lr_set(screen_lr_e lr, uint8_t level)
{
    if(SCREEN_L == lr)
    {
        m_l_ch_af_level = level;
    }
    else
    {
        m_r_ch_af_level = level;
    }

    refresh = true;
}

void channel_rf_level_lr_set(screen_lr_e lr, uint8_t level)
{
    if(SCREEN_L == lr)
    {
        m_l_ch_rf_level = level;
    }
    else
    {
        m_r_ch_rf_level = level;
    }

    refresh = true;
}

void lcd_black_light_enable(bool enable)
{
    if(enable)
    {
        gpio_output_set(&m_lcd_display_obj.lcd_back_light_pin, 1);
    }
    else
    {
        gpio_output_set(&m_lcd_display_obj.lcd_back_light_pin, 0);
    }
}
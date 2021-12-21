#include "stdio.h"
#include "board_config.h"
#include "bk953x_handler.h"
#include "lcd_display_handler.h"

static bk953x_object_t m_l_bk9532_obj;
static bk953x_object_t m_r_bk9532_obj;

static gpio_object_t   m_l_bk9532_rst;
static gpio_object_t   m_r_bk9532_rst;

typedef struct
{
    bk953x_task_stage_e stage;
    bk953x_object_t     *p_bk953x_object;
} bk953x_task_t;

static bk953x_task_t m_l_bk953x_task = {
    .p_bk953x_object = &m_l_bk9532_obj,
    .stage = BK_STAGE_INIT,
};

static bk953x_task_t m_r_bk953x_task = {
    .p_bk953x_object = &m_r_bk9532_obj,
    .stage = BK_STAGE_INIT,
};

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

    bk953x_res_init(&m_r_bk9532_obj);
    bk953x_res_init(&m_l_bk9532_obj);
    //硬件复位
    m_r_bk9532_obj.hw_reset_handler();
    m_l_bk9532_obj.hw_reset_handler();

    bk953x_chip_id_get(&m_r_bk9532_obj);
    bk953x_chip_id_get(&m_l_bk9532_obj);

    trace_debug("r_chip_id = 0x%08x , l_chip_id = 0x%08x\n\r",m_r_bk9532_obj.chip_id, m_l_bk9532_obj.chip_id);

    return err_code;
}

/**
 * @brief 搜频
 */
static int bk953x_rx_channel_search(bk953x_object_t *p_bk953x_object)
{
    int err_code = 0;


    return err_code;
}

static void bk953x_stage_task_run(bk953x_task_t *p_task)
{
    int err_code = 0;
    uint8_t rx_spec_data = 0;
    static uint64_t old_ticks = 0;

    switch(p_task->stage)
    {
        case BK_STAGE_INIT:
            err_code = bk953x_config_init(p_task->p_bk953x_object);
            if(err_code == 0)
            {
                trace_debug("bk953x_config_init success\n\r");
            }
            p_task->stage++;
            break;

        case BK_STAGE_NORMAL:
            if( mid_timer_ticks_get() - old_ticks > 1000)
            {
                old_ticks = mid_timer_ticks_get();
                err_code = bk953x_rx_spec_data_get(&m_l_bk9532_obj, &rx_spec_data);
                if(!err_code)
                {
                    trace_debug("bk953x_rx_spec_data_get rx_spec_data = 0x%02x\n\r",rx_spec_data);
                }
                
            }
            break;

        case BK_STAGE_SEARCHING:

            break;

        case BK_STAGE_POWER_OFF:

            break;

        default:
            break;
    }
}

void bk953x_loop_task(void)
{
    bk953x_stage_task_run(&m_l_bk953x_task);
    bk953x_stage_task_run(&m_r_bk953x_task);
}

void bk953x_task_stage_set(bk953x_lr_e lr, bk953x_task_stage_e stage)
{
    if(lr == BK953X_L)
    {
        m_l_bk953x_task.stage = stage;
    }
    else
    {
        m_r_bk953x_task.stage = stage;
    }
}

/**
 * @brief 设置通道序号来获取对应寄存器的值
 */
int bk953x_ch_index_set(bk953x_lr_e lr, uint16_t chan_index)
{
    freq_chan_object_t freq_chan_obj;

    freq_chan_obj.chan_index = chan_index;

    if(lr == BK953X_L)
    {
        if((chan_index < 1) && (chan_index > 100))
        {
            return -EINVAL;
        }

        freq_chan_obj.reg_value = BK9532_FREQ_632_MHZ + BK9532_FREQ_0_3_MHZ * (chan_index - SCREEN_L_CHANNEL_INDEX_MIN);

        return bk953x_freq_chan_set(&m_l_bk9532_obj, &freq_chan_obj);
    }
    else
    {
        if((chan_index < 101) && (chan_index > 200))
        {
            return -EINVAL;
        }

        freq_chan_obj.reg_value = BK9532_FREQ_660_MHZ + BK9532_FREQ_0_3_MHZ * (chan_index - SCREEN_R_CHANNEL_INDEX_MIN);

        return bk953x_freq_chan_set(&m_r_bk9532_obj, &freq_chan_obj);
    }
}

int bk953x_rf_rssi_get(bk953x_lr_e lr, uint8_t *p_level)
{
    int err_code = 0;
    uint8_t rssi = 0;

    if(lr == BK953X_L)
    {
        err_code = bk953x_rx_rssi_get(&m_l_bk9532_obj, &rssi);

        trace_debug("l rssi = %d\n\r",rssi);
    }
    else
    {
        err_code = bk953x_rx_rssi_get(&m_r_bk9532_obj, &rssi);

        trace_debug("r rssi = %d\n\r",rssi);
    }

    /**
     * rssi: 8 bit
     */
    if(rssi > 150)
    {
        *p_level = 5;
    }
    else if(rssi > 110)
    {
        *p_level = 4;
    }
    else if(rssi > 90)
    {
        *p_level = 3;
    }
    else if(rssi > 60)
    {
        *p_level = 2;
    }
    else if(rssi > 20)
    {
        *p_level = 1;
    }
    else
    {
         *p_level = 0;
    }

    return err_code;
} 

int bk953x_af_get(bk953x_lr_e lr, uint8_t *p_level)
{
    int err_code = 0;
    uint16_t af_vol = 0;

    if(lr == BK953X_L)
    {
        err_code = bk953x_rx_vol_get(&m_l_bk9532_obj, &af_vol);

        trace_debug("l af = %d\n\r",af_vol);
    }
    else
    {
        err_code = bk953x_rx_vol_get(&m_r_bk9532_obj, &af_vol);

        trace_debug("r af = %d\n\r",af_vol);
    }

    /**
     * rssi: 16 bit
     */
    if(af_vol > 500)
    {
        *p_level = 5;
    }
    else if(af_vol > 400)
    {
        *p_level = 4;
    }
    else if(af_vol > 300)
    {
        *p_level = 3;
    }
    else if(af_vol > 200)
    {
        *p_level = 2;
    }
    else if(af_vol > 100)
    {
        *p_level = 1;
    }
    else
    {
         *p_level = 0;
    }

    return err_code;
} 


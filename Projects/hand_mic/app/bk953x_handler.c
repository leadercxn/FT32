#include "stdio.h"
#include "board_config.h"
#include "bk953x_handler.h"

static bk953x_object_t m_bk9531_obj;

static gpio_object_t   m_bk9531_rst;

typedef struct
{
    bk953x_task_stage_e stage;
    bk953x_object_t     *p_bk953x_object;
} bk953x_task_t;

static bk953x_task_t m_bk953x_task = {
    .p_bk953x_object = &m_bk9531_obj,
    .stage = BK_STAGE_INIT,
};

/**
 * @warning 复位要适当的延时，别太快
 */
static void bk953x_hw_reset(void)
{
    gpio_config(&m_bk9531_rst);

    gpio_output_set(&m_bk9531_rst, 1);
    delay_ms(100);
    gpio_output_set(&m_bk9531_rst, 0);
    delay_ms(100);
    gpio_output_set(&m_bk9531_rst, 1);
    delay_ms(500);
}

int bk9531_init(void)
{
    int err_code = 0;

#ifdef FT32
    m_bk9531_rst.gpio_port_periph_clk = BK9531_CE_PERIPH_CLK;
    m_bk9531_rst.p_gpio_port = BK9531_CE_PORT;
#endif

    m_bk9531_rst.gpio_dir = GPIO_DIR_OUTPUR;
    m_bk9531_rst.gpio_pin = BK9531_CE_PIN;

    m_bk9531_obj.hw_reset_handler = bk953x_hw_reset;

#ifdef FT32
    m_bk9531_obj.mid_bk953x_object.virt_i2c_object.sda_port_periph_clk = VIRT1_SDA_GPIO_CLK;
    m_bk9531_obj.mid_bk953x_object.virt_i2c_object.scl_port_periph_clk = VIRT1_SCL_GPIO_CLK;
    m_bk9531_obj.mid_bk953x_object.virt_i2c_object.p_sda_gpio_port = VIRT1_SDA_GPIO_PORT;
    m_bk9531_obj.mid_bk953x_object.virt_i2c_object.p_scl_gpio_port = VIRT1_SCL_GPIO_PORT;
    m_bk9531_obj.mid_bk953x_object.virt_i2c_object.sda_gpio_pin = VIRT1_SDA_PIN;
    m_bk9531_obj.mid_bk953x_object.virt_i2c_object.scl_gpio_pin = VIRT1_SCL_PIN;
#endif

    bk953x_res_init(&m_bk9531_obj);

    m_bk9531_obj.hw_reset_handler();

    bk953x_chip_id_get(&m_bk9531_obj);

    trace_debug("9531_chip_id = 0x%08x \n\r",m_bk9531_obj.chip_id);

    return err_code;
}

static void bk953x_stage_task_run(bk953x_task_t *p_task)
{
    int err_code = 0;

    switch(p_task->stage)
    {
        case BK_STAGE_INIT:
#if 0
            err_code = bk953x_config_init(p_task->p_bk953x_object);
            if(err_code == 0)
            {
                trace_debug("bk953x_config_init success\n\r");
            }
#endif
            p_task->stage++;
            break;

        case BK_STAGE_NORMAL:

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
    bk953x_stage_task_run(&m_bk953x_task);
}

void bk953x_task_stage_set(bk953x_lr_e lr, bk953x_task_stage_e stage)
{
    if(lr == BK953X_L)
    {
        m_bk953x_task.stage = stage;
    }
    else
    {
        m_bk953x_task.stage = stage;
    }
}

/**
 * @brief 设置通道序号来获取对应寄存器的值
 */
int bk953x_ch_index_set(uint16_t chan_index)
{
    freq_chan_object_t freq_chan_obj;

    freq_chan_obj.chan_index = chan_index;
}

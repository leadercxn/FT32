#include "stdio.h"
#include "string.h"
#include "stdbool.h"

#include "board_config.h"
#include "button_handler.h"

#define BUTTON_LONG_TIME_MS    2000

static button_event_handler_t m_button_event_handler = NULL;
static bool m_is_button_start = false;
static uint64_t m_button_start_time = 0;

static gpio_object_t m_power_sw_key = {
    .gpio_port_periph_clk = POWER_SW_KEY_PORT_PERIPH_CLK,
    .p_gpio_port = POWER_SW_KEY_PORT,
    .gpio_dir = GPIO_DIR_INPUT,
    .gpio_pin = POWER_SW_KEY_PIN
};

void button_hw_init(button_event_handler_t handler)
{
    gpio_config(&m_power_sw_key);

    if(handler)
    {
        m_button_event_handler = handler;
    }
}

/**
 * @breif
 */
void button_loop_task(void)
{
    uint8_t key_value = 0;

    static button_event_e old_button_event = BUTTON_EVENT_MAX;
    button_event_e button_event = BUTTON_EVENT_MAX;

    gpio_input_get(&m_power_sw_key, &key_value);
    if(key_value == 0)
    {
        /* 简单的滤波 */
        delay_ms(10);

        gpio_input_get(&m_power_sw_key, &key_value);

        if(key_value == 0)
        {
            if(!m_is_button_start)
            {
                m_is_button_start = true;
                m_button_start_time = mid_timer_ticks_get();
            }
            else
            {
                if(mid_timer_ticks_get() - m_button_start_time > BUTTON_LONG_TIME_MS)
                {
                    button_event = BUTTON_EVENT_LONG_PUSH;
                }
                else
                {
                    button_event = BUTTON_EVENT_PUSH;
                }
            }
        }
    }
    else
    {
        if(m_is_button_start)
        {
            m_is_button_start = false;
            button_event = BUTTON_EVENT_RELEASE;
        }
        else
        {
            button_event = BUTTON_EVENT_MAX;
        }
    }

    if((button_event != BUTTON_EVENT_MAX) && (m_button_event_handler))
    {
        m_button_event_handler(button_event);
    }
}

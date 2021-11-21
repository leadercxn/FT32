#include "stdio.h"
#include "string.h"

#include "board_config.h"
#include "adc_button_handler.h"

#define BUTTON_LONG_TIME_MS    5000
#define BUTTON_SHORT_TIME_MS   50

static adc_button_event_handler_t m_adc_button_event_handler = NULL;

//左边按键组
static adc_button_event_handler_t m_l_adc_button_event_handler = NULL;
//右边按键组
static adc_button_event_handler_t m_r_adc_button_event_handler = NULL;

static bool m_is_r_adc_button_start = false;
static bool m_is_l_adc_button_start = false;
static uint64_t m_r_button_start_time = 0;
static uint64_t m_l_button_start_time = 0;

void adc_button_event_handler_register(adc_button_event_handler_t handler)
{
    if(handler)
    {
        m_adc_button_event_handler = handler;
    }
}

void l_adc_button_event_handler_register(adc_button_event_handler_t l_handler)
{
    if(l_handler)
    {
        m_l_adc_button_event_handler = l_handler;
    }
}

void r_adc_button_event_handler_register(adc_button_event_handler_t r_handler)
{
    if(r_handler)
    {
        m_r_adc_button_event_handler = r_handler;
    }
}

/**
 * @warning 目前DOWN按键在释放时，由于旁路电容电放电缓慢，导致有些小bug
 */
void adc_button_loop_task(void)
{
    //R
    static adc_button_event_e old_r_button_event = BUTTON_EVENT_MAX;
    adc_button_event_e r_button_event = BUTTON_EVENT_MAX;

    uint16_t r_adc_mv = adc_ch_result_get(ADC_CHANNEL_0) * 3300 / 4095;
    if(r_adc_mv > BUTTON_RELEASE_MIN)
    {
        if(m_is_r_adc_button_start)
        {
            m_is_r_adc_button_start = false;
            switch(old_r_button_event)
            {
                case BUTTON_R_EVENT_SET_PUSH:
                case BUTTON_R_EVENT_LONG_SET:
                    r_button_event = BUTTON_R_EVENT_SET_RELEASE;
                    break;

                case BUTTON_R_EVENT_UP_PUSH:
                    r_button_event = BUTTON_R_EVENT_UP_RELEASE;
                    break;

                case BUTTON_R_EVENT_DOWN_PUSH:
                    r_button_event = BUTTON_R_EVENT_DOWN_RELEASE;
                    break;

                default:
                    break;
            }
        }
    }
    else
    {
//        trace_debug("r_adc_mv = %d\n\r",r_adc_mv);
        if((r_adc_mv > BUTTON_SET_LEVEL_MIN) && (r_adc_mv < BUTTON_SET_LEVEL_MAX))
        {
            if(!m_is_r_adc_button_start)
            {
                m_is_r_adc_button_start = true;
                m_r_button_start_time = mid_timer_ticks_get();
            }
            else
            {
                if(mid_timer_ticks_get() - m_r_button_start_time > BUTTON_LONG_TIME_MS)
                {
                    r_button_event = BUTTON_R_EVENT_LONG_SET;
                }
                else
                {
                    r_button_event = BUTTON_R_EVENT_SET_PUSH;
                }
            }
        }
        else if((r_adc_mv > BUTTON_UP_LEVEL_MIN) && (r_adc_mv < BUTTON_UP_LEVEL_MAX))
        {
            if(!m_is_r_adc_button_start)
            {
                m_is_r_adc_button_start = true;
                m_r_button_start_time = mid_timer_ticks_get();
            }
            else
            {
                if(mid_timer_ticks_get() - m_r_button_start_time > BUTTON_SHORT_TIME_MS)
                {
                    m_r_button_start_time = mid_timer_ticks_get();
                    r_button_event = BUTTON_R_EVENT_UP_PUSH;
                }
            }
        }
        else if((r_adc_mv > BUTTON_DOWN_LEVEL_MIN) && (r_adc_mv < BUTTON_DOWN_LEVEL_MAX))
        {
            if(!m_is_r_adc_button_start)
            {
                m_is_r_adc_button_start = true;
                m_r_button_start_time = mid_timer_ticks_get();
            }
            else
            {
                if(mid_timer_ticks_get() - m_r_button_start_time > BUTTON_SHORT_TIME_MS)
                {
                    m_r_button_start_time = mid_timer_ticks_get();
                    r_button_event = BUTTON_R_EVENT_DOWN_PUSH;
                }
            }
        }
    }

    if((m_r_adc_button_event_handler) && (r_button_event != BUTTON_EVENT_MAX))
    {
        m_r_adc_button_event_handler(r_button_event);
        old_r_button_event = r_button_event;
    }


    //L
    static adc_button_event_e old_l_button_event = BUTTON_EVENT_MAX;
    adc_button_event_e l_button_event = BUTTON_EVENT_MAX;

    uint16_t l_adc_mv = adc_ch_result_get(ADC_CHANNEL_1) * 3300 / 4095;
    if(l_adc_mv > BUTTON_RELEASE_MIN)
    {
        if(m_is_l_adc_button_start)
        {
            m_is_l_adc_button_start = false;
            switch(old_l_button_event)
            {
                case BUTTON_L_EVENT_SET_PUSH:
                case BUTTON_L_EVENT_LONG_SET:
                    l_button_event = BUTTON_L_EVENT_SET_RELEASE;
                    break;

                case BUTTON_L_EVENT_UP_PUSH:
                    l_button_event = BUTTON_L_EVENT_UP_RELEASE;
                    break;

                case BUTTON_L_EVENT_DOWN_PUSH:
                    l_button_event = BUTTON_L_EVENT_DOWN_RELEASE;
                    break;

                default:
                    break;
            }
        }
    }
    else
    {
//        trace_debug("l_adc_mv = %d\n\r",l_adc_mv);
        if((l_adc_mv > BUTTON_SET_LEVEL_MIN) && (l_adc_mv < BUTTON_SET_LEVEL_MAX))
        {
            if(!m_is_l_adc_button_start)
            {
                m_is_l_adc_button_start = true;
                m_l_button_start_time = mid_timer_ticks_get();
            }
            else
            {
                if(mid_timer_ticks_get() - m_l_button_start_time > BUTTON_LONG_TIME_MS)
                {
                    l_button_event = BUTTON_L_EVENT_LONG_SET;
                }
                else
                {
                    l_button_event = BUTTON_L_EVENT_SET_PUSH;
                }
            }
        }
        else if((l_adc_mv > BUTTON_UP_LEVEL_MIN) && (l_adc_mv < BUTTON_UP_LEVEL_MAX))
        {
            if(!m_is_l_adc_button_start)
            {
                m_is_l_adc_button_start = true;
                m_l_button_start_time = mid_timer_ticks_get();
            }
            else
            {
                if(mid_timer_ticks_get() - m_l_button_start_time > BUTTON_SHORT_TIME_MS)
                {
                    m_l_button_start_time = mid_timer_ticks_get();
                    l_button_event = BUTTON_L_EVENT_UP_PUSH;
                }
            }
        }
        else if((l_adc_mv > BUTTON_DOWN_LEVEL_MIN) && (l_adc_mv < BUTTON_DOWN_LEVEL_MAX))
        {
            if(!m_is_l_adc_button_start)
            {
                m_is_l_adc_button_start = true;
                m_l_button_start_time = mid_timer_ticks_get();
            }
            else
            {
                if(mid_timer_ticks_get() - m_l_button_start_time > BUTTON_SHORT_TIME_MS)
                {
                    m_l_button_start_time = mid_timer_ticks_get();
                    l_button_event = BUTTON_L_EVENT_DOWN_PUSH;
                }
            }
        }
    }

    if((m_l_adc_button_event_handler) && (l_button_event != BUTTON_EVENT_MAX))
    {
        m_l_adc_button_event_handler(l_button_event);
        old_l_button_event = l_button_event;
    }
}


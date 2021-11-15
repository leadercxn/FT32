#include "stdio.h"
#include "string.h"

#include "user_board.h"
#include "util.h"
#include "trace.h"
#include "middle_api.h"

#include "adc_button_handler.h"

#define BUTTON_LONG_TIME_MS    5000
#define BUTTON_SHORT_TIME_MS   500

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

void adc_button_loop_task(void)
{
    //R
    uint16_t old_r_adc_mv = 0;
    uint16_t r_adc_mv = adc_ch_result_get(ADC_CHANNEL_0) / 4095 * 3300;
    if(r_adc_mv > BUTTON_RELEASE_MIN)
    {
        //
        if(m_is_r_adc_button_start)
        {
            m_is_r_adc_button_start = false;
            if((old_r_adc_mv > BUTTON_SET_LEVEL_MIN) && (old_r_adc_mv < BUTTON_SET_LEVEL_MAX))
            {
                if(mid_timer_ticks_get() - m_r_button_start_time < BUTTON_LONG_TIME_MS)
                {
                    m_r_adc_button_event_handler(BUTTON_R_EVENT_SET);
                }
            }
        }
    }
    else
    {
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
                    m_r_adc_button_event_handler(BUTTON_R_EVENT_LONG_SET);
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
                    m_r_adc_button_event_handler(BUTTON_R_EVENT_UP);
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
                    m_r_adc_button_event_handler(BUTTON_R_EVENT_DOWN);
                }
            }
        }
    }
    old_r_adc_mv = r_adc_mv;

    //L
    uint16_t old_l_adc_mv = 0;
    uint16_t l_adc_mv = adc_ch_result_get(ADC_CHANNEL_1) / 4095 * 3300;
    if(l_adc_mv > BUTTON_RELEASE_MIN)
    {
        if(m_is_l_adc_button_start)
        {
            m_is_l_adc_button_start = false;
            if((old_l_adc_mv > BUTTON_SET_LEVEL_MIN) && (old_l_adc_mv < BUTTON_SET_LEVEL_MAX))
            {
                if(mid_timer_ticks_get() - m_l_button_start_time < BUTTON_LONG_TIME_MS)
                {
                    m_l_adc_button_event_handler(BUTTON_L_EVENT_SET);
                }
            }
        }
    }
    else
    {
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
                    m_l_adc_button_event_handler(BUTTON_L_EVENT_LONG_SET);
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
                    m_l_adc_button_event_handler(BUTTON_L_EVENT_UP);
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
                    m_l_adc_button_event_handler(BUTTON_L_EVENT_DOWN);
                }
            }
        }
    }
    old_l_adc_mv = l_adc_mv;
}


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#ifdef FT32
#include "ft_lib.h"
#endif

#include "board_config.h"

#include "queue.h"
#include "util.h"
#include "trace.h"
#include "lib_error.h"

#include "mid_timer.h"

#define SCHED_TIMER_MAX_EVENT_DATA_SIZE   8
#define SCHED_TIMER_QUEUE_SIZE            20

static bool m_timer_list_traversing = false;

struct timer_list_node_s
{
    timer_node_t *p_timer_node;
    STAILQ_ENTRY(timer_list_node_s) next;
};

typedef struct timer_list_node_s timer_list_node_t;

/**
 * timer不紧急的放在scheduler里面调度
 */
static app_scheduler_t  m_timer_scheduler;

/**
 * 定义一个单向尾队列
 */
STAILQ_HEAD(, timer_list_node_s) m_timer_list = STAILQ_HEAD_INITIALIZER(m_timer_list);


/**
 * @brief 每 1ms 回调函数，在中断里的
 */
static void per_ms_timer_handler(void)
{
    int err_code = ENONE;

    timer_list_node_t *p_timer_list_node;

    if(m_timer_list_traversing == false)
    {
        m_timer_list_traversing = true;
        //遍历定时器链表节点执行相关函数
        STAILQ_FOREACH(p_timer_list_node, &m_timer_list, next)
        {
            if(p_timer_list_node->p_timer_node->active)
            {
                if(p_timer_list_node->p_timer_node->remain_ms > 0)
                {
                    p_timer_list_node->p_timer_node->remain_ms--;

                    if(p_timer_list_node->p_timer_node->remain_ms == 0)
                    {
                        if(p_timer_list_node->p_timer_node->single_mode)
                        {
                            p_timer_list_node->p_timer_node->active = false;
                        }
                        else
                        {
                            p_timer_list_node->p_timer_node->remain_ms = p_timer_list_node->p_timer_node->init_ms;
                        }

                        if(p_timer_list_node->p_timer_node->immediately)
                        {
                            //紧急的终端中执行
                            p_timer_list_node->p_timer_node->handler(p_timer_list_node->p_timer_node->p_data);
                        }
                        else
                        {
                            //非紧急的放到循环里面执行
                            err_code = app_sched_event_put(&m_timer_scheduler, p_timer_list_node->p_timer_node->p_data, 0, (app_sched_event_handler_t)p_timer_list_node->p_timer_node->handler);
                            if(err_code)
                            {
                                trace_error("app_sched_event_put error %d\n\r",err_code);
                            }
                        }
                    }
                }
            }
        }

        m_timer_list_traversing = false;
    }

#if 0
    static uint64_t old_tick = 0;

    if((ft_timer_tick_get() - old_tick ) > 500)
    {
        trace_debug("timer tick %llu\n\r",ft_timer_tick_get());
        old_tick = ft_timer_tick_get();
    }
#endif

}

/**
 * @brief
 */
static void timer_node_add(timer_node_id_t timer_id)
{
    if(timer_id)
    {
        timer_list_node_t *p_timer_list_node =(timer_list_node_t *)malloc(sizeof(timer_list_node_t));

        p_timer_list_node->p_timer_node = (timer_node_t *)timer_id;

        /*在队列尾端加入一个定时器节点*/
        STAILQ_INSERT_TAIL(&m_timer_list, p_timer_list_node, next); 
    }
}

void mid_timer_init(void)
{

#ifdef FT32
    /* 初始化定时器，并将定时器毁掉 */
    timer3_init();
    timer_handler_register(per_ms_timer_handler);
#endif
    APP_SCHED_INIT(&m_timer_scheduler, SCHED_TIMER_MAX_EVENT_DATA_SIZE, SCHED_TIMER_QUEUE_SIZE);
}

int mid_timer_create( timer_node_id_t const      *p_timer_id,
                      bool                        single_mode,
                      bool                        immediately,
                      timer_node_handler_t        timeout_handler)
{
    if(p_timer_id == NULL)
    {
        return -EINVAL;
    }

    if(timeout_handler == NULL)
    {
        return -EINVAL;
    }

    timer_node_t *p_node = (timer_node_t *) *p_timer_id;

    if(p_node->active == true)
    {
        return -ESTATE;
    }

    p_node->single_mode = single_mode;
    p_node->immediately = immediately;
    p_node->handler = timeout_handler;

    timer_node_add((timer_node_id_t)p_node);

    return ENONE;
}

int mid_timer_start(timer_node_id_t timer_id,
                    uint32_t        ms,
                    void *          p_data)
{
    timer_node_t *p_node = (timer_node_t *) timer_id;

    if(!p_node)
    {
        return -EINVAL; 
    }

    if(!p_node->handler)
    {
        return -ESTATE; 
    }

    p_node->remain_ms = ms;
    p_node->init_ms = ms;

    if(p_data)
    {
        p_node->p_data = p_data;
    }

    p_node->active = true;

    return ENONE;
}

int mid_timer_stop(timer_node_id_t timer_id)
{
    timer_node_t *p_node = (timer_node_t *) timer_id;

    if(!p_node)
    {
        return -EINVAL; 
    }

    p_node->active = false;

    return ENONE;
}

uint64_t mid_timer_ticks_get(void)
{
#ifdef FT32
    return ft_timer_tick_get();
#endif
}

void mid_timer_loop_task(void)
{
    app_sched_execute(&m_timer_scheduler);
}

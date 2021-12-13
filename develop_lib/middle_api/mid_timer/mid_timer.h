#ifndef __MID_TIMER_H
#define __MID_TIMER_H


#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

typedef void (*timer_node_handler_t) (void *p_data);

/**
 * 注: handler 不能放耗时过长的函数
 */
typedef struct
{
    bool                    active;
    bool                    single_mode;        //单次模式
    bool                    immediately;        //true:在中断中执行  false:利用scheduler调度
    uint32_t                remain_ms;          //剩余多少ms
    uint32_t                init_ms;
    void                    *p_data;
    timer_node_handler_t    handler;
} timer_node_t;

typedef timer_node_t *  timer_node_id_t;

#define MID_TIMER_DEF(timer_id) \
            static timer_node_t timer_id##_data = { .active = false };   \
            static const timer_node_id_t timer_id = &timer_id##_data;   \
            bool timer_id##_running = false;    \



void mid_timer_init(void);

int mid_timer_create( timer_node_id_t const *     p_timer_id,
                      bool                        single_mode,
                      bool                        immediately,
                      timer_node_handler_t        timeout_handler);

int mid_timer_start(timer_node_id_t timer_id,
                    uint32_t        ms,
                    void *          p_data);

int mid_timer_stop(timer_node_id_t timer_id);

uint64_t mid_timer_ticks_get(void);

void mid_timer_loop_task(void);

#endif

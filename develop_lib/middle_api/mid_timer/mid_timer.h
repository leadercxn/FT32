#ifndef __MID_TIMER_H
#define __MID_TIMER_H

typedef void (*timer_node_handler_t) (void);

/**
 * 注: handler 不能放耗时过长的函数
 */
typedef struct
{
    uint32_t                remain_times;
    uint32_t                remain_ms;
    void                    *p_data;
    timer_node_handler_t    handler;
} timer_node_t;


#endif
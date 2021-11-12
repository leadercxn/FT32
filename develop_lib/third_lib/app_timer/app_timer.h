/* Copyright (c) 2019 SENSORO Co.,Ltd. All Rights Reserved.
 *
 */

#ifndef APP_TIMER_H__
#define APP_TIMER_H__

#include "mid_timer.h"

#define TIMER_INIT()    mid_timer_init()                                            \

#define TIMER_CREATE(p_id, singlemode, immediately, handler)                              \
{                                                                                   \
    int err_code;                                                                   \
    err_code = mid_timer_create(p_id, singlemode, immediately, handler);                  \
}                                                                                   \

#define TIMER_START(id, ms)                                                         \
{                                                                                   \
    int err_code;                                                              \
    err_code = mid_timer_start(id, ms, NULL);                   \
    id##_running = true;                                                            \
}                                                                                   \

#define TIMER_START_WITH_PARAM(id, ms, param)                                       \
{                                                                                   \
    int err_code;                                                              \
    err_code = mid_timer_start(id, ms, param);                  \
    id##_running = true;                                                            \
}                                                                                   \

#define TIMER_STOP(id)                                                              \
{                                                                                   \
    int err_code;                                                              \
    err_code = mid_timer_stop(id);                                                  \
    id##_running = false;                                                           \
}                                                                                   \


#endif

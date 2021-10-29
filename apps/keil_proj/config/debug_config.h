/* Copyright (c) 2019 SENSORO Co.,Ltd. All Rights Reserved.
 *
 */

#ifndef DEBUG_CONFIG_H__
#define DEBUG_CONFIG_H__

/**
 * Redefine the trace format
 */
//#define TRACE_ASSERT_FORMAT                     ""
//#define TRACE_ERROR_FORMAT                      ""
//#define TRACE_WARN_FORMAT                       ""
//#define TRACE_NOTICE_FORMAT                     ""
//#define TRACE_INFO_FORMAT                       ""
//#define TRACE_DEBUG_FORMAT                      ""
//#define TRACE_VERBOSE_FORMAT                    ""
#define CAL_DRIVER_DEBUG
#define CAL_ON_UART_DEBUG
#define CAL_ON_BOX_DEBUG
#define NORMAL_MODE_TRACE_LEVEL TRACE_LEVEL_DEBUG
#define EVENT_HANDLER_TRACE_LEVEL TRACE_LEVEL_DEBUG
#define ALPHAWAN_HANDLER_TRACE_LEVEL TRACE_LEVEL_DEBUG
#define DEBUG_HOOK_TRACE_LEVEL TRACE_LEVEL_DEBUG
#define CHANNEL_SEARCH_TRACE_LEVEL TRACE_LEVEL_DEBUG
#define ALPHAWAN_TASK_TRACE_LEVEL TRACE_LEVEL_DEBUG
#define BC26_FCT_HDL_TRACE_LEVEL TRACE_LEVEL_DEBUG

/**
 * Uncomment if needing log with different modules.
 *
 * Don't uncomment here. Please create header file debug_config_custom.h in debug_code directory
 */

// #define NORMAL_MODE_TRACE_LEVEL                TRACE_LEVEL_DEBUG

#ifdef DEBUG_CONFIG_CUSTOM
#include "debug_config_custom.h"
#endif

#endif /*DEBUG_CONFIG_H__*/

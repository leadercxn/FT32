/*
 * Copyright (c) 2016 SENSORO Co.,Ltd. All Rights Reserved.
 *
 */

#ifndef _TRACE_H_
#define _TRACE_H_

#include <stdint.h>
#include <stdio.h>

#ifndef TARCE_ENABLE
#define TRACE_ENABLE
#endif

#ifdef TRACE_ENABLE

#define TRACE_LEVEL_ASSERT 0
#define TRACE_LEVEL_ERROR 1
#define TRACE_LEVEL_WARN 2
#define TRACE_LEVEL_NOTICE 3
#define TRACE_LEVEL_INFO 4
#define TRACE_LEVEL_DEBUG 5
#define TRACE_LEVEL_VERBOSE 6

#ifndef TRACE_LEVEL
//#define TRACE_LEVEL TRACE_LEVEL_VERBOSE
#define TRACE_LEVEL TRACE_LEVEL_DEBUG
#endif // TRACE_LEVEL

#ifndef __MODULE__
#define __MODULE__ "undefined"
#endif // __MODULE__

#ifndef TRACE_ASSERT_FORMAT
#define TRACE_ASSERT_FORMAT "%-10s\t%4d [A] ", __MODULE__, __LINE__
#endif // TRACE_ASSERT_FORMAT

#ifndef TRACE_ERROR_FORMAT
#define TRACE_ERROR_FORMAT "%-10s\t%4d [E] ", __MODULE__, __LINE__
#endif // TRACE_ERROR_FORMAT

#ifndef TRACE_WARN_FORMAT
#define TRACE_WARN_FORMAT "%-10s\t%4d [W] ", __MODULE__, __LINE__
#endif // TRACE_WARN_FORMA

#ifndef TRACE_NOTICE_FORMAT
#define TRACE_NOTICE_FORMAT "%-10s\t%4d [N] ", __MODULE__, __LINE__
#endif // TRACE_NOTICE_FORMAT

#ifndef TRACE_INFO_FORMAT
#define TRACE_INFO_FORMAT "%-10s\t%4d [I] ", __MODULE__, __LINE__
#endif // TRACE_INFO_FORMAT

#ifndef TRACE_DEBUG_FORMAT
#define TRACE_DEBUG_FORMAT "%-10s\t%4d [D] ", __MODULE__, __LINE__
#endif // TRACE_DEBUG_FORMAT

#ifndef TRACE_VERBOSE_FORMAT
#define TRACE_VERBOSE_FORMAT "%-10s\t%4d [V] ", __MODULE__, __LINE__
#endif // TRACE_VERBOSE_FORMAT

void trace_init(void);

void trace_dump(void *p_buffer, uint32_t len);

#if 0
#define SLW_LOG_INIT() log_raw_uart_init()                         /*!< nitialize the module. */
#define SLW_LOG_PRINTF(...) log_raw_uart_printf(__VA_ARGS__)       /*!< Print a log message using printf. */
#define SLW_LOG_PRINTF_DEBUG(...) log_raw_uart_printf(__VA_ARGS__) /*!< If DEBUG is set, print a log message using printf. */
#define SLW_LOG_PRINTF_ERROR(...) log_raw_uart_printf(__VA_ARGS__) /*!< Print a log message using printf to the error stream. */

#define SLW_LOG(...) log_raw_uart_write_string_many(NUM_VA_ARGS(__VA_ARGS__), ##__VA_ARGS__)       /*!< Print a log message. The input string must be null-terminated. */
#define SLW_LOG_DEBUG(...) log_raw_uart_write_string_many(NUM_VA_ARGS(__VA_ARGS__), ##__VA_ARGS__) /*!< If DEBUG is set, print a log message. The input string must be null-terminated. */
#define SLW_LOG_ERROR(...) log_raw_uart_write_string_many(NUM_VA_ARGS(__VA_ARGS__), ##__VA_ARGS__) /*!< Print a log message to the error stream. The input string must be null-terminated. */

#define SLW_LOG_HEX(val) log_raw_uart_write_hex(val)       /*!< Log an integer as HEX value (example output: 0x89ABCDEF). */
#define SLW_LOG_HEX_DEBUG(val) log_raw_uart_write_hex(val) /*!< If DEBUG is set, log an integer as HEX value (example output: 0x89ABCDEF). */
#define SLW_LOG_HEX_ERROR(val) log_raw_uart_write_hex(val) /*!< Log an integer as HEX value to the error stream (example output: 0x89ABCDEF). */

#define SLW_LOG_HEX_CHAR(val) log_raw_uart_write_hex_char(val)       /*!< Log a character as HEX value (example output: AA). */
#define SLW_LOG_HEX_CHAR_DEBUG(val) log_raw_uart_write_hex_char(val) /*!< If DEBUG is set, log a character as HEX value (example output: AA). */
#define SLW_LOG_HEX_CHAR_ERROR(val) log_raw_uart_write_hex_char(val) /*!< Log a character as HEX value to the error stream (example output: AA). */

#define SLW_LOG_HAS_INPUT() log_raw_uart_has_input()               /*!< Check if the input buffer has unconsumed characters. */
#define SLW_LOG_READ_INPUT(p_char) log_raw_uart_read_input(p_char) /*!< Consume a character from the input buffer. */
#endif

// #define TRACE_PRINTF SLW_LOG_PRINTF

#ifndef TRACE_PRINTF
#define TRACE_PRINTF printf
#endif

#if TRACE_LEVEL >= TRACE_LEVEL_ASSERT
#define trace_assert(msg, ...)             \
    {                                      \
        TRACE_PRINTF(TRACE_ASSERT_FORMAT); \
        TRACE_PRINTF(msg, ##__VA_ARGS__);  \
    }
#define trace_dump_a trace_dump
#else
#define trace_assert(msg, ...)
#define trace_dump_a(...)
#endif // TRACE_LEVEL >= TRACE_LEVEL_ASSERT

#if TRACE_LEVEL >= TRACE_LEVEL_ERROR
#define trace_error(msg, ...)             \
    {                                     \
        TRACE_PRINTF(TRACE_ERROR_FORMAT); \
        TRACE_PRINTF(msg, ##__VA_ARGS__); \
    }
#define trace_dump_e trace_dump
#else
#define trace_error(msg, ...)
#define trace_dump_e(...)
#endif // TRACE_LEVEL >= TRACE_LEVEL_ERROR

#if TRACE_LEVEL >= TRACE_LEVEL_WARN
#define trace_warn(msg, ...)              \
    {                                     \
        TRACE_PRINTF(TRACE_WARN_FORMAT);  \
        TRACE_PRINTF(msg, ##__VA_ARGS__); \
    }
#define trace_dump_w trace_dump
#else
#define trace_warn(msg, ...)
#define trace_dump_w(...)
#endif // TRACE_LEVEL >= TRACE_LEVEL_WARN

#if TRACE_LEVEL >= TRACE_LEVEL_NOTICE
#define trace_notice(msg, ...)             \
    {                                      \
        TRACE_PRINTF(TRACE_NOTICE_FORMAT); \
        TRACE_PRINTF(msg, ##__VA_ARGS__);  \
    }
#define trace_dump_n trace_dump
#else
#define trace_warn(msg, ...)
#define trace_dump_n(...)
#endif // TRACE_LEVEL >= TRACE_LEVEL_NOTICE

#if TRACE_LEVEL >= TRACE_LEVEL_INFO
#define trace_info(msg, ...)              \
    {                                     \
        TRACE_PRINTF(TRACE_INFO_FORMAT);  \
        TRACE_PRINTF(msg, ##__VA_ARGS__); \
    }
#define trace_dump_i trace_dump
#else
#define trace_info(msg, ...)
#define trace_dump_i(...)
#endif // TRACE_LEVEL >= TRACE_LEVEL_INFO

#if TRACE_LEVEL >= TRACE_LEVEL_DEBUG
#define trace_debug(msg, ...)             \
    {                                     \
        TRACE_PRINTF(TRACE_DEBUG_FORMAT); \
        TRACE_PRINTF(msg, ##__VA_ARGS__); \
    }
#define trace_dump_d trace_dump
#else
#define trace_debug(msg, ...)
#define trace_dump_d(...)
#endif // TRACE_LEVEL >= TRACE_LEVEL_DEBUG

#if TRACE_LEVEL == TRACE_LEVEL_VERBOSE
#define trace_verbose(msg, ...)             \
    {                                       \
        TRACE_PRINTF(TRACE_VERBOSE_FORMAT); \
        TRACE_PRINTF(msg, ##__VA_ARGS__);   \
    }
#define trace_dump_v trace_dump
#else
#define trace_verbose(msg, ...)
#define trace_dump_v(...)
#endif // TRACE_LEVEL == TRACE_LEVEL_VERBOSE

#else

#define trace_init(...)
#define trace_printf(...)
#define trace_dump(...)

#define trace_assert(...)
#define trace_dump_a(...)

#define trace_error(...)
#define trace_dump_e(...)

#define trace_warn(...)
#define trace_dump_w(...)

#define trace_notice(...)
#define trace_dump_n(...)

#define trace_info(...)
#define trace_dump_i(...)

#define trace_debug(...)
#define trace_dump_d(...)

#define trace_verbose(...)
#define trace_dump_v(...)

#endif // TRACE_ENABLE

#endif // _TRACE_H_

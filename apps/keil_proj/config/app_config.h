/* Copyright (c) 2020 SENSORO Co.,Ltd. All Rights Reserved.
 *
 */

#ifndef APP_CONFIG_H__
#define APP_CONFIG_H__

#include "version.h"
#include "boards.h"

#define IS_SRVC_CHANGED_CHARACT_PRESENT                 1                 /**< Include the service changed characteristic. If not enabled, the server's database cannot be changed for the lifetime of the device. */

#define CENTRAL_LINK_COUNT                              0                 /**<number of central links used by the application. When changing this number remember to adjust the RAM settings*/
#define PERIPHERAL_LINK_COUNT                           1                 /**<number of peripheral links used by the application. When changing this number remember to adjust the RAM settings*/

#define APP_TIMER_PRESCALER             0                                 /**< Value of the RTC1 PRESCALER register. 4095 = 125 ms every tick */
#define APP_TIMER_OP_QUEUE_SIZE     	30                                /**< Maximum number of timeout handlers pending execution */

#define SCHED_MAX_EVENT_DATA_SIZE      	sizeof(app_timer_event_t)         /**< Maximum size of scheduler events. Note that scheduler BLE stack events do not contain any data, as the events are being pulled from the stack in the event handler. */
#define SCHED_QUEUE_SIZE               	50

#define WDT_TIMEOUT                 5000        //5s
#define WDT_FEED_INTERVAL           2000

#define ALPHA_TOOL_CFG_VERSION      0X05
#define ALPHA_TOOL_TEST_VERSION     0X01

#define NUS_DATA_VERSION            0X01

#endif

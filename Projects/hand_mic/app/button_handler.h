#ifndef __BUTTON_HANDLER_H
#define __BUTTON_HANDLER_H


typedef enum
{
    BUTTON_EVENT_PUSH,
    BUTTON_EVENT_LONG_PUSH,
    BUTTON_EVENT_RELEASE,

    BUTTON_EVENT_MAX,
} button_event_e;



typedef void (*button_event_handler_t)(button_event_e event);

void button_hw_init(button_event_handler_t handler);

void button_loop_task(void);

#endif

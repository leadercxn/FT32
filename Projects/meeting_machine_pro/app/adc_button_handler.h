#ifndef __ADC_BUTTON_HANDLER_H
#define __ADC_BUTTON_HANDLER_H

//以电压值 mV 作为按键的检测范围
#define BUTTON_SET_LEVEL_MAX    1100
#define BUTTON_SET_LEVEL_MIN    1000

#define BUTTON_UP_LEVEL_MAX     1440
#define BUTTON_UP_LEVEL_MIN     1350

#define BUTTON_DOWN_LEVEL_MAX   600
#define BUTTON_DOWN_LEVEL_MIN   500

#define BUTTON_RELEASE_MIN      3100

typedef enum
{
    BUTTON_R_EVENT_SET_PUSH,
    BUTTON_R_EVENT_SET_RELEASE,
    BUTTON_R_EVENT_UP_PUSH,
    BUTTON_R_EVENT_UP_RELEASE,
    BUTTON_R_EVENT_DOWN_PUSH,
    BUTTON_R_EVENT_DOWN_RELEASE,
    BUTTON_R_EVENT_LONG_SET,

    BUTTON_L_EVENT_SET_PUSH,
    BUTTON_L_EVENT_SET_RELEASE,
    BUTTON_L_EVENT_UP_PUSH,
    BUTTON_L_EVENT_UP_RELEASE,
    BUTTON_L_EVENT_DOWN_PUSH,
    BUTTON_L_EVENT_DOWN_RELEASE,
    BUTTON_L_EVENT_LONG_SET,

    BUTTON_EVENT_MAX,
} adc_button_event_e;



typedef void (*adc_button_event_handler_t)(adc_button_event_e event);

void adc_button_event_handler_register(adc_button_event_handler_t handler);
void l_adc_button_event_handler_register(adc_button_event_handler_t l_handler);
void r_adc_button_event_handler_register(adc_button_event_handler_t r_handler);

#endif

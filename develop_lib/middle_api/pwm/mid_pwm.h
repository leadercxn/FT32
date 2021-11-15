#ifndef __MID_PWM_H
#define __MID_PWM_H

typedef struct
{
    uint16_t ch;
    uint32_t freq;          //pwm的频率
    uint8_t  duty_cycle;    //pwm的占空比 0~100
} mid_pwm_object;

void pwm_init(mid_pwm_object *p_mid_pwm_object);

#endif

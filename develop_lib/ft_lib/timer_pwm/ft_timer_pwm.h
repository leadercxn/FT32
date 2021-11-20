#ifndef __FT_TIMER_PWM_H
#define __FT_TIMER_PWM_H

void timer15_ch1_pwm_init(uint32_t freq , uint8_t duty_cycle);

void timer15_ch1_pwn_output_enable_set(bool enable);

#endif


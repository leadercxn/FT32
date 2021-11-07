#ifndef __FT_TIMER_PWM_H
#define __FT_TIMER_PWM_H



#define PWM_CH1_PIN                   GPIO_Pin_2                  /* PA.02 */
#define PWM_CH1_GPIO_PORT             GPIOA                       /* GPIOA */
#define PWM_CH1_GPIO_CLK              RCC_AHBPeriph_GPIOA
#define PWM_CH1_PIN_SOURCE            GPIO_PinSource2
#define PWM_CH1_AF                    GPIO_AF_0

#define PWM_TIM                       TIM15


void timer15_pwm_ch1_init(uint32_t freq , uint8_t duty_cycle);

#endif


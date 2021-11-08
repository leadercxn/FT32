#include "stdbool.h"

#ifdef FT32
#include "ft_lib.h"
#endif


#include "mid_pwm.h"


void pwm_init(mid_pwm_object *p_mid_pwm_object)
{
#ifdef FT32
    timer15_pwm_ch1_init(p_mid_pwm_object->freq, p_mid_pwm_object->duty_cycle);
#endif

}


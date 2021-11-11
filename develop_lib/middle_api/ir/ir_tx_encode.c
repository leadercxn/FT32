#include "stdbool.h"

#ifdef FT32
#include "ft_lib.h"
#endif

#include "trace.h"
#include "middle_api.h"
#include "third_lib.h"

#include "ir_tx_encode.h"

#define IR_TX_PWM_FREQ  38500
#define IR_TX_PWM_DUTY  50

enum{
    IR_TX_HEADER_GENERATE,
    IR_TX_BIT_0_GENERATE,
    IR_TX_BIT_1_GENERATE,
    IR_TX_IDLE,
} ir_tx_op_type_e;

MID_TIMER_DEF(m_ir_tx_timer);

static bool m_frame_data_start = false;

void ir_tx_timer_handler(void *p_data)
{

}

void ir_tx_init(void)
{

#ifdef FT32
    timer15_ch1_pwm_init(IR_TX_PWM_FREQ, IR_TX_PWM_DUTY);
#endif

    TIMER_CREATE(&m_ir_tx_timer,true,true,ir_tx_timer_handler);

}


static void ir_tx_frame_header_generate(void)
{

}


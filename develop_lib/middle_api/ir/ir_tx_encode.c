#include "stdbool.h"
#include "string.h"

#ifdef FT32
#include "ft_lib.h"
#endif

#include "trace.h"
#include "middle_api.h"
#include "third_lib.h"
#include "lib_error.h"
#include "ir_tx_encode.h"

#define IR_TX_PWM_FREQ  38500
#define IR_TX_PWM_DUTY  50

typedef enum{
    IR_TX_IDLE,
    IR_TX_START,
    IR_TX_BIT_0_GENERATE,
    IR_TX_BIT_1_GENERATE,
    IR_TX_STOP,
} ir_tx_op_type_e;

//初始化宏
#ifdef FT32 
#define PWM_INIT(freq,duty)  \
{                           \
    timer15_ch1_pwm_init(freq,duty);   \
}
#else

#define PWM_INIT(freq,duty)

#endif

//PWM使能宏
#ifdef FT32 
#define PWM_OUT_ENABLE(status)  \
{                           \
    timer15_ch1_pwn_output_enable_set(status);   \
}
#else

#define PWM_OUT_ENABLE(status)

#endif


MID_TIMER_DEF(m_ir_tx_timer);

static ir_tx_op_type_e  m_ir_tx_op_status  = IR_TX_IDLE;

/* 子阶段 */
static uint8_t          m_sub_state = 0;

static uint8_t          m_tx_data[16] = {0};
static uint8_t          m_tx_data_len = 0;

/* bit 的下序 */
static uint8_t         m_bit_index = 0;
/* byte 的下序 */
static uint8_t         m_byte_index = 0;

static void ir_tx_timer_handler(void *p_data)
{
    //2个子阶段后，开始下一个bit的产生,红外帧头完成后，也是完成2个子阶段
    if(m_ir_tx_op_status == IR_TX_STOP)
    {
        m_ir_tx_op_status = IR_TX_IDLE;
        PWM_OUT_ENABLE(false);
        trace_debug("ir tx finish\r\n");
        return;
    }
    else
    {
        if(m_sub_state > 1)
        {
            m_sub_state = 0;

            if(m_ir_tx_op_status == IR_TX_START)
            {
            }
            else
            {
                m_bit_index ++;
            }

            //判断是否完成一字节的传输
            if(m_bit_index > 7)
            {
                m_bit_index = 0;

                m_byte_index ++;
                //判断是否完成整帧数据的传输
                if(m_byte_index >= m_tx_data_len)
                {
                    PWM_OUT_ENABLE(true);
                    m_ir_tx_op_status = IR_TX_STOP;
                    TIMER_START(m_ir_tx_timer,5);
                    return;
                }
            }

            //LSB
            if((m_tx_data[m_byte_index] >> m_bit_index) & 0x01)
            {
                m_ir_tx_op_status = IR_TX_BIT_1_GENERATE;
            }
            else
            {
                m_ir_tx_op_status = IR_TX_BIT_0_GENERATE;
            }
        }

        switch(m_ir_tx_op_status)
        {
            case IR_TX_START:
                if(m_sub_state == 0)
                {
                    PWM_OUT_ENABLE(true);
                    m_sub_state ++;
                    TIMER_START(m_ir_tx_timer,5);
                }
                else
                {
                    PWM_OUT_ENABLE(false);
                    m_sub_state ++;
                    TIMER_START(m_ir_tx_timer,5);
                }
                break;

            case IR_TX_BIT_0_GENERATE:
                if(m_sub_state == 0)
                {
                    PWM_OUT_ENABLE(true);
                    m_sub_state ++;
                    TIMER_START(m_ir_tx_timer,2);
                }
                else
                {
                    PWM_OUT_ENABLE(false);
                    m_sub_state ++;
                    TIMER_START(m_ir_tx_timer,1);
                }
                break;

            case IR_TX_BIT_1_GENERATE:
                if(m_sub_state == 0)
                {
                    PWM_OUT_ENABLE(true);
                    m_sub_state ++;
                    TIMER_START(m_ir_tx_timer,2);
                }
                else
                {
                    PWM_OUT_ENABLE(false);
                    m_sub_state ++;
                    TIMER_START(m_ir_tx_timer,2);
                }
                break;

            default:
                break;
        }
    }
}

void ir_tx_init(void)
{
    PWM_INIT(IR_TX_PWM_FREQ, IR_TX_PWM_DUTY);

    TIMER_CREATE(&m_ir_tx_timer,true,true,ir_tx_timer_handler);
}

int ir_tx_start(uint8_t *p_data, uint8_t len)
{
    int err_code = ENONE;

    //ir tx busy
    if(m_ir_tx_op_status)
    {
        trace_error("ir tx busy now\n\r");
        return -EBUSY;
    }

    if(len > sizeof(m_tx_data))
    {
        trace_error("ir tx data too long\n\r");
        return -EBUSY;
    }

    memcpy(m_tx_data, p_data, len);
    m_tx_data_len = len;

    m_ir_tx_op_status = IR_TX_START;
    m_sub_state = 0;
    m_bit_index = 0;
    m_byte_index = 0;

    // 100ms后开启pwm输出
    TIMER_START(m_ir_tx_timer,100);

    return err_code;
}




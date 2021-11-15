#include "stdbool.h"
#include "string.h"

#ifdef FT32
#include "ft_lib.h"
#endif

#include "trace.h"
#include "lib_error.h"
#include "middle_api.h"

#include "ir_rx_decode.h"

//EXIT外部中断初始化
#ifdef FT32 
#define EXIT_INIT()         \
{                           \
    exit_init();            \
}
#else

#define EXIT_INIT()

#endif

//EXIT外部中断使能宏
#ifdef FT32 
#define EXIT_IRQ_ENABLE(status)     \
{                                   \
    exit_irq_enable_set(status);    \
}
#else

#define EXIT_IRQ_ENABLE(status)

#endif


/* ir rx 接收的原始数据 和 原始数据的长度 */
static uint8_t m_ir_rx_decode_data[16] = {0};
static uint8_t m_ir_rx_decode_data_len = 0;

static void exit_irq_handler(void)
{
    uint8_t pin_status = 0;
    uint8_t time_cnt = 0;
    uint8_t bit_index = 0;
    uint8_t byte_index = 0;
    bool is_ir_rx_finish = false;
    uint8_t sum_crc = 0;
    uint8_t i;

    /**
     * 在外部中断函数里面写红外解码处理过程，用时210～250ms，阻塞式
     * 弊端: 影响其他处理
     * 因为考虑到放到主体main循环里面执行解码的话，怕其他处理影响到红外解码
     * 
     * 暂时不采用定时器和外部中断配合红外解码,麻烦
     */
    EXIT_IRQ_ENABLE(false);

    /* ir start的5ms L电平 */
    do
    {
        get_gpio_value(EXIT_GPIO_PORT, EXIT_GPIO_PIN, &pin_status);
        delay_10us(500);
        time_cnt ++;
        //超过5ms低电平，退出红外解码
        if(time_cnt > 11)
        {
            EXIT_IRQ_ENABLE(true);
            return;
        }
    } while (!pin_status);

    time_cnt = 0;
    /* ir start的5ms H电平 */
    do
    {
        get_gpio_value(EXIT_GPIO_PORT, EXIT_GPIO_PIN, &pin_status);
        delay_10us(500);
        time_cnt ++;
        //超过5ms低电平，退出红外解码
        if(time_cnt > 11)
        {
            EXIT_IRQ_ENABLE(true);
            return;
        }
    } while (pin_status);

    /* 开始解码数据 */
    do
    {
        /**
         * sub state-0
         */
        time_cnt = 0;
        do
        {
            get_gpio_value(EXIT_GPIO_PORT, EXIT_GPIO_PIN, &pin_status);
            delay_10us(500);
            time_cnt ++;
            if(time_cnt > 11)
            {
                EXIT_IRQ_ENABLE(true);
                return;
            }
        } while (!pin_status);

        if((time_cnt > 5) && (time_cnt < 12))
        {
            //测量 2ms < time_cnt < 5ms
            if(m_ir_rx_decode_data_len)
            {
                is_ir_rx_finish = true;
            }
        }

        /**
         * sub state-1
         */
        if(!is_ir_rx_finish)
        {
            time_cnt = 0;
            do
            {
                get_gpio_value(EXIT_GPIO_PORT, EXIT_GPIO_PIN, &pin_status);
                delay_10us(500);
                time_cnt ++;
                //H 电平超过 2ms ，认为是错误
                if(time_cnt > 4)
                {
                    EXIT_IRQ_ENABLE(true);
                    return;
                }
            } while (pin_status);

            //LSB
            m_ir_rx_decode_data[byte_index] >>= 1;
            if(time_cnt > 2)
            {
                m_ir_rx_decode_data[byte_index] |= 0x80;
            }

            /**
             * 控制下一次循环的变量
             */
            bit_index ++;
            if(bit_index > 7)
            {
                bit_index = 0;
                byte_index ++;

                //超出协议容量，强制认为采集完成
                if(byte_index > (sizeof(m_ir_rx_decode_data) - 1))
                {
                    is_ir_rx_finish = true;
                }
            }
        }
        /*  H电平 */
    } while (!is_ir_rx_finish);
    
    //长度为奇数，采集出错
    if(byte_index < 4)
    {
        trace_error("ir rx error data len\r\n");
        EXIT_IRQ_ENABLE(true);
        return;
    }

    //校验
    for(i = 0; i < m_ir_rx_decode_data[1]; i++)
    {
        sum_crc += m_ir_rx_decode_data[2 + i];
    }

    if(sum_crc == m_ir_rx_decode_data[byte_index - 1])
    {
        trace_debug("ir rx finish\r\n");
        // 校验通过后才赋值
        m_ir_rx_decode_data_len = byte_index;
    }
    else
    {
        trace_error("ir rx error data verify\r\n");
    }

    EXIT_IRQ_ENABLE(true);
}

/**
 * @brief ir_rx 初始化
 */
void ir_rx_init(void)
{
    EXIT_INIT();

#ifdef FT32
    // 注册到外部中断层
    exit_irq_handler_register(exit_irq_handler);
#endif
}

/**
 * @brief 查询ir rx的结果
 * 
 * @param [out] p_data接收解码后的数据
 * 
 * @return ir 解码后的数据长度
 */
uint8_t ir_rx_decode_result_get(uint8_t *p_data)
{
    if(!p_data)
    {
        return 0;
    }

    uint8_t len = m_ir_rx_decode_data_len;

    if(m_ir_rx_decode_data_len)
    {
        memcpy(p_data, m_ir_rx_decode_data, m_ir_rx_decode_data_len);
    }

    m_ir_rx_decode_data_len = 0; 

    return len;
}
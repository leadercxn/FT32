#include "ft32f0xx.h"
#include "ft_usart.h"
#include "util.h"
#include "stdbool.h"

#include "trace.h"

#ifdef TRACE_ENABLE

/**
 * @brief Definition for COM port1, connected to USART2
 */
void trace_init(void)
{
    ft_uart_info_t uart_info;
    ft_uart_config_t uart_config;

    ft_uart_info_get(FT_UART2, &uart_info);

    uart_config.baudrate = 115200;
    uart_config.databits = USART_WordLength_8b;
    uart_config.stopbit = USART_StopBits_1;
    uart_config.parity = USART_Parity_No;
    uart_config.hwfc = USART_HardwareFlowControl_None;
    uart_config.mode = USART_Mode_Rx | USART_Mode_Tx;
    uart_config.interrupt_priority = 0;

    ft_uart_init(FT_UART2, uart_info, &uart_config);
}

void trace_dump(void *p_buffer, uint32_t len)
{
    uint8_t *p = (uint8_t *)p_buffer;

    for (uint32_t index = 0; index < len; index++)
    {
        TRACE_PRINTF("%02X", p[index]);
    }

    TRACE_PRINTF("\r\n");
}

#endif // TRACE_ENABLE

#include "ft32f0xx.h"
#include "ft_usart.h"
#include "util.h"
#include "stdbool.h"

#include "trace.h"

#ifdef TRACE_ENABLE

/**
 * @brief Definition for COM port1, connected to USART2
 */

#define FT_UART1                USART1
#define FT_UART1_CLK            RCC_APB2Periph_USART1

#define FT_UART1_TX_PIN         GPIO_Pin_9
#define FT_UART1_TX_GPIO_PORT   GPIOA
#define FT_UART1_TX_GPIO_CLK    RCC_AHBPeriph_GPIOA
#define FT_UART1_TX_SOURCE      GPIO_PinSource9
#define FT_UART1_TX_AF          GPIO_AF_1

#define FT_UART1_RX_PIN         GPIO_Pin_10
#define FT_UART1_RX_GPIO_PORT   GPIOA
#define FT_UART1_RX_GPIO_CLK    RCC_AHBPeriph_GPIOA
#define FT_UART1_RX_SOURCE      GPIO_PinSource10
#define FT_UART1_RX_AF          GPIO_AF_1

void trace_init(void)
{
    ft_uart_info_t uart_info;
    ft_uart_config_t uart_config;

    uart_info.uart = FT_UART1;
    uart_info.tx_port = FT_UART1_TX_GPIO_PORT;
    uart_info.rx_port = FT_UART1_RX_GPIO_PORT;

    uart_info.clk = RCC_APB2Periph_USART1;
    uart_info.tx_clk = FT_UART1_TX_GPIO_CLK;
    uart_info.rx_clk = FT_UART1_RX_GPIO_CLK;

    uart_info.tx_pin = FT_UART1_TX_PIN;
    uart_info.rx_pin = FT_UART1_RX_PIN;

    uart_info.tx_pin_source = FT_UART1_TX_SOURCE;
    uart_info.rx_pin_source = FT_UART1_RX_SOURCE;

    uart_info.tx_af = FT_UART1_TX_AF;
    uart_info.rx_af = FT_UART1_RX_AF;

    uart_config.baudrate = 115200;
    uart_config.databits = USART_WordLength_8b;
    uart_config.stopbit = USART_StopBits_1;
    uart_config.parity = USART_Parity_No;
    uart_config.hwfc = USART_HardwareFlowControl_None;
    uart_config.mode = USART_Mode_Rx | USART_Mode_Tx;
    uart_config.interrupt_priority = 0;

    ft_uart_init(0, uart_info, &uart_config);
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

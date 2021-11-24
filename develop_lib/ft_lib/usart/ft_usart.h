#ifndef __FT_USART_H
#define __FT_USART_H

#include "ft32f0xx.h"
#include "stdbool.h"

/**
 * @enum ft_uart_id_t
 * @brief ID supported by UART.
 */
enum ft_uart_id_t
{
    FT_UART_0 = 0, ///< UART 0.
    FT_UART_1,     ///< UART 1.
};

typedef struct
{
    USART_TypeDef *uart;

    GPIO_TypeDef *tx_port;

    GPIO_TypeDef *rx_port;

    uint32_t clk;
    uint32_t tx_clk;
    uint32_t rx_clk;

    uint16_t tx_pin;
    uint16_t rx_pin;

    uint16_t tx_pin_source;
    uint16_t rx_pin_source;

    uint16_t tx_af;
    uint16_t rx_af;
} ft_uart_info_t;

/**
 * @brief Structure for UART configuration.
 * 
 */
typedef struct
{
    // void *p_context; ///< Context passed to interrupt handler.
    uint32_t baudrate; ///< Baudrate configuration.
    uint32_t databits; ///< Data bits for one character configuration.
    uint32_t stopbit;  ///< Stopbit configuration.
    uint32_t parity;   ///< Parity configuration.
    uint32_t hwfc;     ///< Flow control configuration.
    uint32_t mode;
    uint8_t interrupt_priority; ///< Interrupt priority.
} ft_uart_config_t;

void ft_uart_init(uint8_t uart_id, ft_uart_info_t uart_info, ft_uart_config_t const *p_config);

void ft_uart_put(uint8_t uart_id, char ch);

#endif

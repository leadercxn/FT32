#ifndef __FT_USART_H
#define __FT_USART_H

#include "ft32f0xx.h"
#include "stdbool.h"

enum UART_CHANNEL
{
    UART0_CHANNEL = 0,
    UART1_CHANNEL = 1,
    UART2_CHANNEL = 2,
    UART3_CHANNEL = 3,
    UART4_CHANNEL = 4,
    UART5_CHANNEL = 5,
};

void ControlUartInit(unsigned char ucChannel, unsigned int bound);
void ControlUartSendData(unsigned char ucChannel, unsigned char ucData);
void ControlUartIrqEnable(unsigned char ucChannel, unsigned char ucData);

void shell_uart_getc(char *p_byte);
void shell_uart_putc(uint8_t ch);

#endif

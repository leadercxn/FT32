
#include <stdio.h>
#include "stdbool.h"
#include "ft32f0xx.h"
#include "util.h"
#include "shell_port.h"
#include "shell.h"
#include "ft_usart.h"
#include "FT32f0xx.h"

// #include "util.h"
// #include "ft_usart.h"
// #include "stdbool.h"

/***************************************************
* 重定向代码
***************************************************/
#pragma import(__use_no_semihosting)
struct __FILE
{
    int handle;
};
/***********************************************************************
 * 函数名称: _ttywrch
 * 功能描述:
 * 输入参数:
 * 输出参数:
 * 返 回 值:
 *  其   它:
 ***********************************************************************/
#if 0
_ttywrch(int ch)
{
    ch = ch;
}
#endif
FILE __stdout;
/***********************************************************************
 * 函数名称: _sys_exit
 * 功能描述:
 * 输入参数:
 * 输出参数:
 * 返 回 值:
 *  其   它:
 ***********************************************************************/
void _sys_exit(int x)
{
    x = x;
}

/***********************************************************************
 * 函数名称: fputc
 * 功能描述: UART1串口重定向作为调试串口,printf函数将会调用到它
 * 输入参数:
 * 输出参数:
 * 返 回 值:
 *  其   它:
 ***********************************************************************/
int fputc(int ch, FILE *f)
{
    shell_uart_putc(ch);
    return ch;
}

/***********************************************************************
 * 函数名称: Uart1Init
 * 功能描述: UART1初始化
 * 输入参数:
 * 输出参数:
 * 返 回 值:
 *  其   它:
 ***********************************************************************/
void Uart1Init(unsigned int bound)
{
}

/***********************************************************************
 * 函数名称: Uart2Init
 * 功能描述: UART2初始化
 * 输入参数:
 * 输出参数:
 * 返 回 值:
 *  其   它:
 ***********************************************************************/
void Uart2Init(unsigned int bound)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Enable GPIO clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    /* Enable USART clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

    //串口2对应引脚复用映射
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_1); //GPIOA2复用为USART1
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1); //GPIOA2复用为USART1

    //USART1端口配置
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //GPIOA2与GPIOA3
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;           //复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;      //速度50MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;         //推挽复用输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;           //上拉
    GPIO_Init(GPIOA, &GPIO_InitStructure);                 //初始化PA9，PA10

    //USART2 初始化设置
    USART_InitStructure.USART_BaudRate = bound;                                     //波特率设置
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;                     //字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                          //一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;                             //无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                 //收发模式
    USART_Init(USART2, &USART_InitStructure);                                       //初始化串口2
    USART_Cmd(USART2, ENABLE);                                                      //使能串口2

    USART_ClearFlag(USART2, USART_FLAG_TC);
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); //开启相关中断,Letter Shell Demo采用轮询检测,不开启中断。

    // /* USART2 IRQ Channel configuration */
    // NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    // NVIC_InitStructure.NVIC_IRQChannelPriority = 0x01;
    // NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    // NVIC_Init(&NVIC_InitStructure);
}

/***********************************************************************
 * 函数名称: ControlUartInit
 * 功能描述:
 * 输入参数:
 * 输出参数:
 * 返 回 值:
 *  其   它:
 ***********************************************************************/
void ControlUartInit(unsigned char ucChannel, unsigned int bound)
{
    switch (ucChannel)
    {
    case UART0_CHANNEL:
        break;
    case UART1_CHANNEL:
        Uart1Init(bound);
        break;
    case UART2_CHANNEL:
        Uart2Init(bound);
        break;
    case UART3_CHANNEL:

        break;
    }
}

/***********************************************************************
 * 函数名称: ControlUartSendData
 * 功能描述:
 * 输入参数:
 * 输出参数:
 * 返 回 值:
 *  其   它:
 ***********************************************************************/
void ControlUartSendData(unsigned char ucChannel, unsigned char ucData)
{
    switch (ucChannel)
    {
    case UART0_CHANNEL:
        break;

    case UART1_CHANNEL:
        USART_ClearFlag(USART1, USART_FLAG_TC);
        USART_SendData(USART1, ucData);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
            ;

        break;
    case UART2_CHANNEL:
        USART_ClearFlag(USART2, USART_FLAG_TC);
        USART_SendData(USART2, ucData);
        while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
            ;
        break;
    case UART3_CHANNEL:

        break;
    }
}

/***********************************************************************
 * 函数名称: ControlUartSwIRQ
 * 功能描述: 中断使能
 * 输入参数: 
 * 输出参数: 
 * 返 回 值: 
 *  其   它: 
 ***********************************************************************/
void ControlUartIrqEnable(unsigned char ucChannel, unsigned char ucData)
{
    switch (ucChannel)
    {
    case UART0_CHANNEL:
        break;
    case UART1_CHANNEL:
        if (ucData == ENABLE)
        {
            USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //开启相关中断
        }
        else
        {
            USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //开启相关中断
        }
        break;
    case UART2_CHANNEL:
        if (ucData == ENABLE)
        {
            USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); //开启相关中断
        }
        else
        {
            USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); //开启相关中断
        }
        break;
    case UART3_CHANNEL:

        break;
    }
}

void USART1_IRQHandler(void)
{
}

void USART2_IRQHandler(void)
{
}

void shell_uart_putc(uint8_t ch)
{
    /* Place your implementation of fputc here */
    /* e.g. write a character to the USART */
    USART_SendData(USART2, (uint8_t)ch);

    /* Loop until transmit data register is empty */
    while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET)
    {
    }
}

void shell_uart_getc(char *p_byte)
{
    *p_byte = 0;
    while (!(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == SET))
    {
    }
    *p_byte = USART_ReceiveData(USART2);
}

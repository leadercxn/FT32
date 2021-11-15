/**
 * @file shell_port.c
 * @author Letter (NevermindZZT@gmail.com)
 * @brief
 * @version 0.1
 * @date 2019-02-22
 *
 * @Copyright (c) 2019 Unicook
 *
 */

#include "shell.h"
#include "ft_usart.h"
#include "util.h"
#include "stdbool.h"
#include "FT32f0xx.h"

Shell shell;
char shellBuffer[512];

/**
 * @brief 用户shell写
 *
 * @param data 数据
 */
void userShellWrite(char data)
{
    shell_uart_putc((uint8_t)data);
}

/**
 * @brief 用户shell读
 *
 * @param data 数据
 * @return char 状态
 */
signed char userShellRead(char *data)
{
    // shell_uart_getc(data);
    *data = 0;
    while (!(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == SET))
    {
    }
    *data = USART_ReceiveData(USART2);
    return 0; //返回0标识数据已经准备OK
}
/**
 * @brief 用户shell初始化
 *
 */
void userShellInit(void)
{
    shell.write = userShellWrite;
    shell.read = userShellRead;
    shellInit(&shell, shellBuffer, 512);
}

/***********************************************************************
 * 函数名称: userShellCmdManualTest
 * 功能描述: 手动命令测试
 * 输入参数: 
 * 输出参数: 
 * 返 回 值: 
 *  其   它: 
 ***********************************************************************/
void userShellCmdManualTest(void)
{
    shellHandler(&shell, 'h');
    shellHandler(&shell, 'e');
    shellHandler(&shell, 'l');
    shellHandler(&shell, 'p');
    shellHandler(&shell, '\n');

    shellHandler(&shell, 'k');
    shellHandler(&shell, 'e');
    shellHandler(&shell, 'y');
    shellHandler(&shell, 's');
    shellHandler(&shell, '\n');
}

void userShellRun(void)
{
    char data = 0;
    // shell_uart_getc(&data);
    while (!(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == SET))
    {
    }
    data = USART_ReceiveData(USART2);
    shellHandler(&shell, data);
}
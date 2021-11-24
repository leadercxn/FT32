/***********************************************************************************
 * 文 件 名   : shell_custom_cmd.c
 * 负 责 人   : jiangfeng.zhang
 * 创建日期   : 2021年7月2日
 * 文件描述   : 自定义shell命令
 * 版权说明   : Copyright (c) 2008-2021   Personal. All rights reserved.
 * 其    他   : 
 * 修改日志   : 
***********************************************************************************/
#include "shell.h"
#include "string.h"
#include "stdio.h"
#include "shell_ext.h"
#include "FT32f0xx.h"

/***********************************************************************
 * 函数名称: #define SHELL_EXPORT_CMD(_attr, _name, _func, _desc)
 * 输入参数:
			_attr :命令属性
			_name :命令名
			_func :命令函数
			_desc :命令描述
 * 输出参数:
 * 返 回 值:
 *  其   它:
 ***********************************************************************/

/***********************************************************************
 * 函数名称: ShellTestFun0
 * 功能描述: letter:/$ shelltest0 123 'a' "1234"
 * 输入参数: 
 * 输出参数: 
 * 返 回 值: 
 *  其   它: 
 ***********************************************************************/
int ShellTestFun0(int i, char ch, char *str)
{
	printf("input int: %d, char: %c, string: %s\r\n", i, ch, str);
	//最后必须要加上换行,以避免与shell内置返回打印重叠
	printf("\r\n");
	return 0;
}

/***********************************************************************
 * 函数名称: ShellTestFun1
 * 功能描述: letter:/$ shellest1 "hello world"
 * 输入参数: 
 * 输出参数: 
 * 返 回 值: 
 *  其   它: 
 ***********************************************************************/
int ShellTestFun1(int argc, char *agrv[])
{
	printf("%dparameter(s)\r\n", argc);
	for (char i = 0; i < argc; i++)
	{
		printf("%s\r\n", agrv[i]);
	}
	//最后必须要加上换行,以避免与shell内置返回打印重叠
	printf("\r\n");
	return 0;
}
/******************************************************************************
* 注册自定义不同形参的测试指令
******************************************************************************/
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), shelltest0, ShellTestFun0, test mode0 parameter);
SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_MAIN), shelltest1, ShellTestFun1, test mode1 parameter);
/******************************************************************************
* 注册软复位重启指令指令
******************************************************************************/
// SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0) | SHELL_CMD_TYPE(SHELL_TYPE_CMD_MAIN), reboot, SystemReboot, system reboot);

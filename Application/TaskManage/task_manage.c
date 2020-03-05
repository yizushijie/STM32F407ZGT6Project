#include"task_manage.h"

//===变量定义
VLTUINT8_T 	g_TaskMangeIndex= TASK_MANAGE_ISP_USART;

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：第1个任务
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T Task_Manage_1()
{
	return ISPTask_UARTCmd_Task(pIspDevice0, pUart1);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：第2个任务
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T Task_Manage_2()
{
	return JTAGTask_UARTCmd_Task(pJtagDevice0, pUart1);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：第2个任务
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T Task_Manage_3()
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：第2个任务
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T Task_Manage_4()
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：第2个任务
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T Task_Manage_Step()
{
	if (g_TaskMangeIndex == TASK_MANAGE_ISP_USART)
	{
		return Task_Manage_1();
	}
	else if (g_TaskMangeIndex == TASK_MANAGE_JTAG_USART)
	{
		return Task_Manage_2();
	}
	else if (g_TaskMangeIndex == TASK_MANAGE_HVPP_USART)
	{
		return Task_Manage_3();
	}
	else if (g_TaskMangeIndex == TASK_MANAGE_HVPP_USART)
	{
		return Task_Manage_4();
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：任务管理函数
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T Task_Manage(void)
{
	//---判断接收是否完成
	if (UARTTask_GetState(&(pUart1->msgRxdHandle)) == 1)
	{
		//---CRC的校验和设备ID校验
		if ((UARTTask_Read_CRCTask(pUart1) == OK_0) && (UARTTask_DeviceID(pUart1) == OK_0))
		{
			if ((pUart1->msgRxdHandle.pMsgVal[pUart1->msgCmdIndex + pUart1->msgIndexOffset]>= CMD_ISP_BASE_CMD)&&
				(pUart1->msgRxdHandle.pMsgVal[pUart1->msgCmdIndex + pUart1->msgIndexOffset] <=CMD_ISP_END_CMD))
			{
				g_TaskMangeIndex = TASK_MANAGE_ISP_USART;
			}
			else if ((pUart1->msgRxdHandle.pMsgVal[pUart1->msgCmdIndex + pUart1->msgIndexOffset] >= CMD_JTAG_BASE_CMD) &&
				(pUart1->msgRxdHandle.pMsgVal[pUart1->msgCmdIndex + pUart1->msgIndexOffset] <= CMD_JTAG_END_CMD))
			{
				g_TaskMangeIndex = TASK_MANAGE_JTAG_USART;
			}
			else
			{
				g_TaskMangeIndex = TASK_MANAGE_NONE;
			}
			//---命令任务步序
			Task_Manage_Step();
		}
		else
		{
			//---发生CRC校验错误
			UARTTask_Printf(pUart1, "=>>SP%d:CRC Check Error<<=\r\n", (pUart1->msgIndex - 1));
		}
		return UARTTask_Read_Init(pUart1);
	}
	return UARTTask_TimeTask_OverFlow(pUart1,1);
}
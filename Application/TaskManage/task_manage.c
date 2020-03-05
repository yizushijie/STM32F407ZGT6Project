#include"task_manage.h"

//===��������
VLTUINT8_T 	g_TaskMangeIndex= TASK_MANAGE_ISP_USART;

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���1������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T Task_Manage_1()
{
	return ISPTask_UARTCmd_Task(pIspDevice0, pUart1);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���2������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T Task_Manage_2()
{
	return JTAGTask_UARTCmd_Task(pJtagDevice0, pUart1);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���2������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T Task_Manage_3()
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���2������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T Task_Manage_4()
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���2������
//////�������:
//////�������:
//////˵		����
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
//////��		����
//////��		�ܣ����������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T Task_Manage(void)
{
	//---�жϽ����Ƿ����
	if (UARTTask_GetState(&(pUart1->msgRxdHandle)) == 1)
	{
		//---CRC��У����豸IDУ��
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
			//---����������
			Task_Manage_Step();
		}
		else
		{
			//---����CRCУ�����
			UARTTask_Printf(pUart1, "=>>SP%d:CRC Check Error<<=\r\n", (pUart1->msgIndex - 1));
		}
		return UARTTask_Read_Init(pUart1);
	}
	return UARTTask_TimeTask_OverFlow(pUart1,1);
}
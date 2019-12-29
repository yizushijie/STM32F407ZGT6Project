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
	return ISPTask_USARTCmd_Task(pIspDevice0, pUsart1);
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
	return JTAGTask_USARTCmd_Task(pJtagDevice0, pUsart1);
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
	if (USARTTask_GetReadState(pUsart1) == 1)
	{
		//---CRC��У����豸IDУ��
		if ((USARTTask_CRCTask_Read(pUsart1) == OK_0) && (USARTTask_DeviceID(pUsart1) == OK_0))
		{
			if ((pUsart1->msgRxdHandler.pMsgVal[pUsart1->msgCmdIndex + pUsart1->msgIndexOffset]>= CMD_ISP_BASE_CMD)&&
				(pUsart1->msgRxdHandler.pMsgVal[pUsart1->msgCmdIndex + pUsart1->msgIndexOffset] <=CMD_ISP_END_CMD))
			{
				g_TaskMangeIndex = TASK_MANAGE_ISP_USART;
			}
			else if ((pUsart1->msgRxdHandler.pMsgVal[pUsart1->msgCmdIndex + pUsart1->msgIndexOffset] >= CMD_JTAG_BASE_CMD) &&
				(pUsart1->msgRxdHandler.pMsgVal[pUsart1->msgCmdIndex + pUsart1->msgIndexOffset] <= CMD_JTAG_END_CMD))
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
			USART_Printf(pUsart1, "=>>����%d:����CRCУ�����<<=\r\n", (pUsart1->msgIndex - 1));
		}
		return USARTTask_Read_Init(pUsart1);
	}
	return USARTTask_TimeOVFTask(pUsart1);
}
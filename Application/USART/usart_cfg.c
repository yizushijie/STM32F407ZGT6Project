#include "usart_cfg.h"

//===ȫ�ֱ�������
USART_HandlerType  g_Usart1 = { 0 };
pUSART_HandlerType pUsart1 = &g_Usart1;

//===printf����ʹ�õĻ�����
#ifdef USE_USART_PRINTF
	char g_PrintfBuffer[USART_PRINTF_SIZE] = { 0 };
#endif

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_StructInit(USART_HandlerType*  USARTx)
{
	//---���ڵ����ݴ�������
	USARTx->msgIndex = 0;
	USARTx->msgRxID = 0;
	USARTx->msgTxID = 0;
	USARTx->msgID = 0;
	USARTx->msgIDIndex = 0;
	USARTx->msgCmdIndex = 0;
	USARTx->msgDataOneIndex = 0;
	USARTx->msgDataTwoIndex = 0;
	USARTx->msgIndexOffset=0;
	USARTx->msgTxBit = 0;
	USARTx->msgTxPort = NULL;
	USARTx->msg485Bit = 0;
	USARTx->msg485Port = NULL;
	USARTx->msgUSART = NULL;

	//---���ջ�����
	USARTx->msgRxdHandler.msgIsDMA = 1;
	USARTx->msgRxdHandler.msgCheckSum = 0;
	USARTx->msgRxdHandler.msgCRCFlag = 0;
	USARTx->msgRxdHandler.msgStep = 0;
	USARTx->msgRxdHandler.msgAddNewLine = 0;
	USARTx->msgRxdHandler.msgIndexW = 0;
	USARTx->msgRxdHandler.msgIndexR = 0;
	USARTx->msgRxdHandler.msgIndexF =0;
	USARTx->msgRxdHandler.msgCount = 0;
	USARTx->msgRxdHandler.msgSize = 0;
	USARTx->msgRxdHandler.msgTaskState = USART_BUSY;
	USARTx->msgRxdHandler.msgOverFlow = 0;
	USARTx->msgRxdHandler.msgRecordTime = 0;
	USARTx->msgRxdHandler.msgEndTime = 0;
	USARTx->msgRxdHandler.msgMaxTime = 0;
	USARTx->msgRxdHandler.pMsgVal = NULL;

	//---���ͻ�����
	USARTx->msgTxdHandler.msgIsDMA = 1;
	USARTx->msgTxdHandler.msgCheckSum = 0;
	USARTx->msgTxdHandler.msgCRCFlag = 0;
	USARTx->msgTxdHandler.msgStep = 0;
	USARTx->msgTxdHandler.msgAddNewLine = 0;
	USARTx->msgTxdHandler.msgIndexW = 0;
	USARTx->msgTxdHandler.msgIndexR = 0;
	USARTx->msgTxdHandler.msgIndexF = 0;
	USARTx->msgTxdHandler.msgCount = 0;
	USARTx->msgTxdHandler.msgSize = 0;
	USARTx->msgTxdHandler.msgTaskState = USART_OK;
	USARTx->msgTxdHandler.msgOverFlow = 0;
	USARTx->msgTxdHandler.msgRecordTime = 0;
	USARTx->msgTxdHandler.msgEndTime = 0;
	USARTx->msgTxdHandler.msgMaxTime = 0;
	USARTx->msgTxdHandler.pMsgVal = NULL;

	//---������
	USARTx->msgTimeTick = NULL;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_Init(USART_HandlerType*  USARTx, UINT16_T rxSize, UINT8_T* pRxVal, UINT8_T rxCRCFlag, UINT16_T txSize, UINT8_T* pTxVal, UINT8_T txCRCFlag, UINT32_T(*pTimerTick)(void))
{
	USART_StructInit(USARTx);
	USARTx->msgRxdHandler.msgCRCFlag = rxCRCFlag;
	USARTx->msgRxdHandler.msgSize = rxSize;
	USARTx->msgRxdHandler.pMsgVal = pRxVal;
	USARTx->msgTxdHandler.msgCRCFlag = txCRCFlag;
	USARTx->msgTxdHandler.msgSize = txSize;
	USARTx->msgTxdHandler.pMsgVal = pTxVal;
	//---ע���������
	USARTx->msgTimeTick = pTimerTick;
	//---�˿ڳ�ʼ��
	if ((USARTx != NULL) && (USARTx == USART_TASK_ONE))
	{
		USART1_Init(USARTx);
	}
	else if ((USARTx != NULL) && (USARTx == USART_TASK_TWO))
	{
		USART2_Init(USARTx);
	}
	else if ((USARTx != NULL) && (USARTx == USART_TASK_THREE))
	{
		USART3_Init(USARTx);
	}
	else
	{
		return ERROR_2;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USART_GPIOInit(USART_HandlerType*  USARTx, UINT8_T isInput)
{
#ifdef USART_INIT_GPIO
	if (USARTx->msgTxPort != NULL)
	{
		if (isInput == USART_TXGPIO_SET_OUTPUT)
		{
			LL_GPIO_SetPinMode(USARTx->msgTxPort, USARTx->msgTxBit, LL_GPIO_MODE_ALTERNATE);
		}
		else
		{
			LL_GPIO_SetPinMode(USARTx->msgTxPort, USARTx->msgTxBit, LL_GPIO_MODE_INPUT);
		}
	}
#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USART_485GPIOInit(USART_HandlerType*  USARTx, UINT8_T isEnable)
{
	if (USARTx->msg485Port != NULL)
	{
		if (isEnable == USART_485_TX_ENABLE)
		{
			GPIO_OUT_0(USARTx->msg485Port, USARTx->msg485Bit);
		}
		else
		{
			GPIO_OUT_1(USARTx->msg485Port, USARTx->msg485Bit);
		}
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_EnableCRC_RX(USART_HandlerType*USARTx, UINT8_T crcFlag)
{
	USARTx->msgRxdHandler.msgCRCFlag = crcFlag;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_GetCRC_RX(USART_HandlerType*USARTx)
{
	return  USARTx->msgRxdHandler.msgCRCFlag;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_EnableCRC_TX(USART_HandlerType*USARTx, UINT8_T crcFlag)
{
	USARTx->msgTxdHandler.msgCRCFlag = crcFlag;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_GetCRC_TX(USART_HandlerType*USARTx)
{
	return  USARTx->msgTxdHandler.msgCRCFlag;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_TimeTick_Init(USART_HandlerType*USARTx, UINT8_T isRx)
{
	UINT32_T temp = 0;
	//---��ȡ��ǰʱ��
	if (USARTx->msgTimeTick != NULL)
	{
		temp = USARTx->msgTimeTick();
	}
	//---ʱ��ڵ�
	if (isRx)
	{
		USARTx->msgRxdHandler.msgRecordTime = temp;

		//---ͬ��ʱ��
		USARTx->msgRxdHandler.msgEndTime = USARTx->msgRxdHandler.msgRecordTime;
	}
	else
	{
		USARTx->msgTxdHandler.msgRecordTime = temp;

		//---ͬ��ʱ��
		USARTx->msgTxdHandler.msgEndTime = USARTx->msgTxdHandler.msgRecordTime;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ע����ʱ������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_TimeTick_DeInit(USART_HandlerType*USARTx, UINT8_T isRx)
{
	if (isRx)
	{
		//---���������־λ
		USARTx->msgRxdHandler.msgOverFlow = 0;
		//---���㵱ǰʱ��
		USARTx->msgRxdHandler.msgEndTime = 0;
		//---ͬ��ʱ��
		USARTx->msgRxdHandler.msgRecordTime = USARTx->msgRxdHandler.msgEndTime;
	}
	else
	{
		//---���������־λ
		USARTx->msgTxdHandler.msgOverFlow = 0;
		//---���㵱ǰʱ��
		USARTx->msgTxdHandler.msgEndTime = 0;
		//---ͬ��ʱ��
		USARTx->msgTxdHandler.msgRecordTime = USARTx->msgTxdHandler.msgEndTime;
	}
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ʱ������Ƿ�����ʱ
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_TimeTick_OVF(USART_HandlerType*USARTx, UINT32_T timeOut, UINT8_T isRx)
{
	UINT32_T temp = 0;

	//---��ȡ��ǰʱ��
	if (USARTx->msgTimeTick != NULL)
	{
		temp = USARTx->msgTimeTick() + 2;
	}
	//---ʱ��ڵ�
	if (isRx)
	{
		//---��ȡ��ǰʱ��
		USARTx->msgRxdHandler.msgEndTime = temp;
		//---�ж��Ƿ�����ʱ����
		if (USARTx->msgRxdHandler.msgEndTime > USARTx->msgRxdHandler.msgRecordTime)
		{
			//---��ʱ��δ�����������
			if ((USARTx->msgRxdHandler.msgEndTime - USARTx->msgRxdHandler.msgRecordTime) > timeOut)
			{
				USARTx->msgRxdHandler.msgOverFlow = 1;
				return ERROR_1;
			}
		}
		else if (USARTx->msgRxdHandler.msgEndTime < USARTx->msgRxdHandler.msgRecordTime)
		{
			//---��ʱ�������������
			if ((0xFFFFFFFF - USARTx->msgRxdHandler.msgRecordTime + USARTx->msgRxdHandler.msgEndTime) > timeOut)
			{
				USARTx->msgRxdHandler.msgOverFlow = 1;
				return ERROR_1;
			}
		}
	}
	else
	{
		//---��ȡ��ǰʱ��
		USARTx->msgTxdHandler.msgEndTime = temp;
		//---�ж��Ƿ�����ʱ����
		if (USARTx->msgTxdHandler.msgEndTime > USARTx->msgTxdHandler.msgRecordTime)
		{
			//---��ʱ��δ�����������
			if ((USARTx->msgTxdHandler.msgEndTime - USARTx->msgTxdHandler.msgRecordTime) > timeOut)
			{
				USARTx->msgTxdHandler.msgOverFlow = 1;
				return ERROR_1;
			}
		}
		else if (USARTx->msgTxdHandler.msgEndTime < USARTx->msgTxdHandler.msgRecordTime)
		{
			//---��ʱ�������������
			if ((0xFFFFFFFF - USARTx->msgTxdHandler.msgRecordTime + USARTx->msgTxdHandler.msgEndTime) > timeOut)
			{
				USARTx->msgTxdHandler.msgOverFlow = 1;
				return ERROR_1;
			}
		}
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USART_TimeOVFTask(USART_HandlerType*USARTx, UINT8_T isRx)
{
	UINT8_T _return = OK_0;
	//---У���ǲ���DMA����ģʽ
	if (USARTx->msgRxdHandler.msgIsDMA==0)
	{
		//---�ж��ǽ��ջ��Ƿ���
		if (isRx != 0)
		{
			if ((USARTx->msgRxdHandler.msgRecordTime != 0) && (USARTx->msgRxdHandler.msgMaxTime != 0))
			{
				if (USARTx->msgRxdHandler.msgRecordTime == 0)
				{
					return OK_0;
				}
				//---��ȡ��ʱֵ
				_return = USART_TimeTick_OVF(USARTx, USARTx->msgRxdHandler.msgMaxTime, 1);
				//---��ʱ�����ж�
				//if ((_return != OK_0) && (USARTx->msgRxHandler.msgNowTime != 0))
				if ((_return != OK_0))
				{
					//---��ӡ��ʱ�Ĵ�����Ϣ
					USART_Printf(USARTx, "=>>���մ���%d������ʱ����!<<=\r\n", (USARTx->msgIndex - 1));
					//---��λ�������ݻ�����
					USART_Read_Init(USARTx);
				}
			}
		}
		else
		{
			if ((USARTx->msgTxdHandler.msgRecordTime != 0) && (USARTx->msgTxdHandler.msgMaxTime != 0))
			{
				if (USARTx->msgTxdHandler.msgRecordTime == 0)
				{
					return OK_0;
				}
				//---��ȡ��ʱֵ
				_return = USART_TimeTick_OVF(USARTx, USARTx->msgTxdHandler.msgMaxTime, 0);
				//---��ʱ�����жϣ�����ĳЩ״̬�µ�ǰ��¼��ʱ��ֵ�ڸ�дΪ���ʱ��ʱ���¼��û�з���ͬ������
				if ((_return != OK_0) && (USARTx->msgTxdHandler.msgRecordTime != 0))
				{
					//---��ӡ��ʱ�Ĵ�����Ϣ
					USART_Printf(USARTx, "=>>���ʹ���%d������ʱ����!<<=\r\n", (USARTx->msgIndex - 1));

					//---��λ�������ݻ�����
					USART_Write_Init(USARTx);
				}
				else
				{
					USARTx->msgTxdHandler.msgOverFlow = 0;
				}
			}
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ���ܵ�������󳤶�ʹ��1�ֽڱ�ʾ
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USART_ITRead_8BitsTask(USART_HandlerType*USARTx, UINT8_T val)
{
	//---��������������
	static UINT8_T tempVal;
	tempVal = val;
	//---���ݽ��ղ���
	switch (USARTx->msgRxdHandler.msgStep)
	{
		//---�������ݵı�ͷ
		case 0:
			if (USARTx->msgRxdHandler.msgIndexR == 0)
			{
				if (USARTx->msgRxID == tempVal)
				{
					USARTx->msgRxdHandler.pMsgVal[0] = tempVal;
					USARTx->msgRxdHandler.msgStep = 1;
					//---��¼���ݵĸ���
					USARTx->msgRxdHandler.msgCount = 1;
					//---�յ���һ�����ϸ�ʽ�����ݣ�������ʱ������
					USART_TimeTick_Init(USARTx, 1);
					//---���㳬ʱ��־
					USART_ClearOVF(USARTx, 1);
				}
			}
			break;

			//---�������ݵĳ���
		case 1:
			if ((tempVal > 0) && (tempVal < (UINT8_T)(USARTx->msgRxdHandler.msgSize & 0xFF)))
			{
				USARTx->msgRxdHandler.pMsgVal[1] = tempVal;
				//---��ȡ���ݵĽ��ճ���
				USARTx->msgRxdHandler.msgIndexW = tempVal;
				//---��¼���ݵĸ���
				USARTx->msgRxdHandler.msgCount += 1;
				//---��һ����
				USARTx->msgRxdHandler.msgStep = 2;
			}
			else
			{
				USARTx->msgRxdHandler.msgStep = 0;
			}
			//---��λ��ʱ������
			USART_TimeTick_Init(USARTx, 1);
			break;
			//---����������Ϣ
		case 2:
			USARTx->msgRxdHandler.pMsgVal[USARTx->msgRxdHandler.msgIndexR + 2] = tempVal;
			USARTx->msgRxdHandler.msgIndexR++;
			//---��¼���ݵĸ���
			USARTx->msgRxdHandler.msgCount += 1;
			//---�ж��Ƿ����
			if (USARTx->msgRxdHandler.msgIndexR >= USARTx->msgRxdHandler.msgSize)
			{
				USARTx->msgRxdHandler.msgIndexR = 0;
			}
			//---��λ��ʱ������
			USART_TimeTick_Init(USARTx, 1);
			//---�ж��Ƿ�������
			if (USARTx->msgRxdHandler.msgIndexR >= USARTx->msgRxdHandler.msgIndexW)
			{
				USARTx->msgRxdHandler.msgStep = 3;
				USARTx->msgRxdHandler.msgTaskState = USART_OK;
				//---���㳬ʱ������
				//USART_TimeTick_DeInit(USARTx, 1);
			}
			break;
		case 3:
			//---���㳬ʱ������
			//USART_TimeTick_DeInit(USARTx,1);
			break;
		default:
			//USARTx->msgRxHandler.msgNowTime = 0;
			break;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ���ܵ�������󳤶�ʹ��2�ֽڱ�ʾ
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USART_ITRead_16BitsTask(USART_HandlerType*USARTx, UINT8_T val)
{
	//---��������������
	static UINT8_T tempVal;
	tempVal = val;
	//---���ݽ��ղ���
	switch (USARTx->msgRxdHandler.msgStep)
	{
		//---�������ݵı�ͷ
		case 0:
			if (USARTx->msgRxdHandler.msgIndexR == 0)
			{
				if (USARTx->msgRxID == tempVal)
				{
					USARTx->msgRxdHandler.pMsgVal[0] = tempVal;
					USARTx->msgRxdHandler.msgStep = 1;
					//---��¼���ݵĸ���
					USARTx->msgRxdHandler.msgCount = 1;
					//---�յ���һ�����ϸ�ʽ�����ݣ�������ʱ������
					USART_TimeTick_Init(USARTx, 1);
					//---���㳬ʱ��־
					USART_ClearOVF(USARTx, 1);
				}
			}
			break;

			//---�������ݵĳ��ȸ�λ
		case 1:
			USARTx->msgRxdHandler.pMsgVal[1] = tempVal;
			USARTx->msgRxdHandler.msgIndexW = tempVal;
			USARTx->msgRxdHandler.msgIndexW <<= 8;
			USARTx->msgRxdHandler.msgStep = 2;
			//---��¼���ݵĸ���
			USARTx->msgRxdHandler.msgCount += 1;
			//---��λ��ʱ������
			USART_TimeTick_Init(USARTx, 1);
			break;
			//---�������ݵĳ��ȵ�λ
		case 2:
			USARTx->msgRxdHandler.pMsgVal[2] = tempVal;
			USARTx->msgRxdHandler.msgIndexW += tempVal;
			//---��¼���ݵĸ���
			USARTx->msgRxdHandler.msgCount += 1;
			//---�ж������Ƿ�Ϸ�
			if ((USARTx->msgRxdHandler.msgIndexW > 0) && (USARTx->msgRxdHandler.msgIndexW < USARTx->msgRxdHandler.msgSize))
			{
				//---��¼���ݵĸ���
				USARTx->msgRxdHandler.msgCount = USARTx->msgRxdHandler.msgIndexW;
				//---��һ����
				USARTx->msgRxdHandler.msgStep = 3;
			}
			else
			{
				USARTx->msgRxdHandler.msgStep = 0;
			}
			//---��λ��ʱ������
			USART_TimeTick_Init(USARTx, 1);
			break;
			//---����������Ϣ
		case 3:
			USARTx->msgRxdHandler.pMsgVal[USARTx->msgRxdHandler.msgIndexR + 3] = tempVal;
			USARTx->msgRxdHandler.msgIndexR++;
			//---��¼���ݵĸ���
			USARTx->msgRxdHandler.msgCount += 1;
			//---�ж��Ƿ����
			if (USARTx->msgRxdHandler.msgIndexR >= USARTx->msgRxdHandler.msgSize)
			{
				USARTx->msgRxdHandler.msgIndexR = 0;
			}
			//---��λ��ʱ������
			USART_TimeTick_Init(USARTx, 1);
			//---�ж��Ƿ�������
			if (USARTx->msgRxdHandler.msgIndexR >= USARTx->msgRxdHandler.msgIndexW)
			{
				USARTx->msgRxdHandler.msgStep = 4;
				USARTx->msgRxdHandler.msgTaskState = USART_OK;
				//---���㳬ʱ������
				//USART_TimeTick_DeInit(USARTx, 1);
			}
			break;
		case 4:
			//---���㳬ʱ������
			//USART_TimeTick_DeInit(USARTx,1);
			break;
		default:
			//USARTx->msgRxHandler.msgNowTime = 0;
			break;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USART_ITRead_Task(USART_HandlerType*USARTx, UINT8_T val)
{
	if (USARTx->msgRxdHandler.msgSize < 0xFF)
	{
		return USART_ITRead_8BitsTask(USARTx, val);
	}
	else
	{
		return USART_ITRead_16BitsTask(USARTx, val);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_PollMode_WriteByte(USART_HandlerType*USARTx, UINT8_T  val)
{
	//---��������
	LL_USART_TransmitData8(USARTx->msgUSART, val);
	//---�ȴ��������
	while (LL_USART_IsActiveFlag_TC(USARTx->msgUSART) == RESET)
	{
		WDT_RESET();
	}
	//---���������ɱ�־λ
	LL_USART_ClearFlag_TC(USARTx->msgUSART);
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� �����ַ���
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_PollMode_WriteData(USART_HandlerType*USARTx, char *pVal)
{
	//---����485Ϊ����ģʽ
	USART_485GPIOInit(USARTx, USART_485_TX_ENABLE);
	//---�л����Ͷ˿�Ϊ���ģʽ
	USART_GPIOInit(USARTx, USART_TXGPIO_SET_OUTPUT);
	//---�ر��ж�
	CLI();
	while (*pVal != '\0')
	{
		USART_PollMode_WriteByte(USARTx, (UINT8_T)*pVal);
		pVal++;
	}
	//---ʹ���ж�
	SEI();
	//---����485Ϊ����ģʽ
	USART_485GPIOInit(USARTx, USART_485_RX_ENABLE);
	//---�л����Ͷ˿�Ϊ����ģʽ
	USART_GPIOInit(USARTx, USART_TXGPIO_SET_INPUT);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_PollMode_ReadByte(USART_HandlerType*USARTx)
{
	//---�ȴ��������
	while (LL_USART_IsActiveFlag_RXNE(USARTx->msgUSART) != RESET)
	{
		WDT_RESET();
	}
	return LL_USART_ReceiveData8(USARTx->msgUSART);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_PollMode_ReadData(USART_HandlerType*USARTx, char *pVal)
{
	while (*pVal != '\0')
	{
		*pVal = USART_PollMode_ReadByte(USARTx);
		pVal++;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USART_ITWrite_TXETask(USART_HandlerType*USARTx)
{
	VLTUINT8_T tempFlag=OK_0;
	if (USARTx->msgTxdHandler.msgIndexW != 0)
	{
		if (USARTx->msgTxdHandler.msgIndexR != USARTx->msgTxdHandler.msgIndexW)
		{
			//---����8Bit������
			LL_USART_TransmitData8(USARTx->msgUSART, USARTx->msgTxdHandler.pMsgVal[USARTx->msgTxdHandler.msgIndexR]);
			//---���ݻ������������
			USARTx->msgTxdHandler.msgIndexR++;
			//---У�黺�����Ƿ����
			if (USARTx->msgTxdHandler.msgIndexR >= USARTx->msgTxdHandler.msgSize)
			{
				USARTx->msgTxdHandler.msgIndexR = 0;
			}
			//---У�������Ƿ����뻺����
			//if (USARTx->msgTxHandler.msgIndexR >= USARTx->msgTxHandler.msgIndexW)
			if ((USARTx->msgTxdHandler.msgIndexR >= USARTx->msgTxdHandler.msgIndexW) && (USARTx->msgTxdHandler.msgCount > 0) && (USARTx->msgTxdHandler.msgIndexR >= USARTx->msgTxdHandler.msgCount))
			{
				//---�������,�������ݼĴ������жϲ�ʹ��
				LL_USART_DisableIT_TXE(USARTx->msgUSART);
				//---ʹ�ܷ�������жϣ������л�TXD�˿�Ϊ����״̬
				LL_USART_EnableIT_TC(USARTx->msgUSART);
			}
		}
		else
		{
			tempFlag = ERROR_1;
		}
	}
	else
	{
		tempFlag = ERROR_2;
	}
	//---У����
	if (tempFlag)
	{
		//---�������,�������ݼĴ������жϲ�ʹ��---����Ƿ�����쳣���رշ������ݼĴ������ж�
		LL_USART_DisableIT_TXE(USARTx->msgUSART);
		//---������ݷ��ͻ�����
		USART_Write_Init(USARTx);
	}
	//---��λ��ʱ������
	USART_TimeTick_Init(USARTx, 0);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USART_ITWrite_TCTask(USART_HandlerType*USARTx)
{
	//---������485������485��Ӧ���ӳ�����,���ӷ��ͻ��з������ڻ���485����Ӧ
	if ((USARTx->msg485Port != NULL) && (USARTx->msgTxdHandler.msgStep == 0))
	{
		//---����8Bit������
		LL_USART_TransmitData8(USARTx->msgUSART, 0x0D);
		USARTx->msgTxdHandler.msgStep = 1;
	}
	else if ((USARTx->msg485Port != NULL) && (USARTx->msgTxdHandler.msgStep == 1))
	{
		//---����8Bit������
		LL_USART_TransmitData8(USARTx->msgUSART, 0x0A);
		USARTx->msgTxdHandler.msgStep = 2;
	}
	else
	{
		//---���㷢�Ͳ���
		USARTx->msgTxdHandler.msgStep = 0;
		//---�������,�������ݷ�������жϲ�ʹ��
		LL_USART_DisableIT_TC(USARTx->msgUSART);
		//---������ݷ��ͻ�����
		USART_Write_Init(USARTx);
		//---���㳬ʱ������
		//USART_TimeTick_DeInit(USARTx, 0);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_RealTime_AddByte(USART_HandlerType*USARTx, UINT8_T val)
{
	if (USARTx->msgTxdHandler.pMsgVal != NULL)
	{
		if (USARTx->msgTxdHandler.msgIndexW >= USARTx->msgTxdHandler.msgSize)
		{
			USARTx->msgTxdHandler.msgIndexW = 0;
		}
		USARTx->msgTxdHandler.pMsgVal[USARTx->msgTxdHandler.msgIndexW] = val;
		USARTx->msgTxdHandler.msgIndexW++;
		//---�жϷ��ͼĴ������ж��Ƿ�ʹ��
		if (LL_USART_IsEnabledIT_TXE(USARTx->msgUSART) == 0)
		{
			//---����485Ϊ����ģʽ
			USART_485GPIOInit(USARTx, USART_485_TX_ENABLE);
			//---�л����Ͷ˿�Ϊ���ģʽ
			USART_GPIOInit(USARTx, USART_TXGPIO_SET_OUTPUT);
			//---ʹ�ܷ��Ϳ��ж�
			LL_USART_EnableIT_TXE(USARTx->msgUSART);
		}
		return OK_0;
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��������ݵĴ�С
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_RealTime_AddSize(USART_HandlerType*USARTx, UINT16_T val)
{
	UINT8_T _return = ERROR_1;
	if (USARTx->msgTxdHandler.pMsgVal != NULL)
	{
		if ((USARTx->msgTxdHandler.msgCRCFlag == USART_CRC_CHECKSUM) || (USARTx->msgTxdHandler.msgCRCFlag == USART_CRC_CRC8))
		{
			val += 1;
		}
		else if (USARTx->msgTxdHandler.msgCRCFlag == USART_CRC_CRC16)
		{
			val += 2;
		}
		else if (USARTx->msgTxdHandler.msgCRCFlag == USART_CRC_CRC32)
		{
			val += 4;
		}
		//---�ж��Ƿ����豸��ID��Ϣ
		if ((USARTx->msgCmdIndex - USARTx->msgIDIndex) != 0)
		{
			val += 1;
		}
		//---�ж��Ƿ����ӻ��з�
		if ((USARTx->msgTxdHandler.msgAddNewLine==1))
		{
			val += 2;
		}
		//---�ж����ݵĸ�ʽ
		if (USARTx->msgTxdHandler.msgSize > 250)
		{
			USART_RealTime_AddByte(USARTx, (UINT8_T)(val >> 8));
			_return = USART_RealTime_AddByte(USARTx, (UINT8_T)(val & 0xFF));
			val += 3;
		}
		else
		{
			_return = USART_RealTime_AddByte(USARTx, (UINT8_T)(val & 0xFF));
			val += 2;
		}
		//---�ж��Ƿ����豸��ID��Ϣ�����ID��Ϣ
		if ((USARTx->msgCmdIndex - USARTx->msgIDIndex) != 0)
		{
			_return = USART_RealTime_AddByte(USARTx, USARTx->msgID);
		}		
		//---���㷢�����ݵĸ���
		USARTx->msgTxdHandler.msgCount = val;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������ݵ�CRCУ����Ϣ
//////�������:
//////�������:
//////˵		����ʹ��CRC�����ݵı����0��ʼʹ��
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_RealTime_AddCRC(USART_HandlerType*USARTx)
{
	//---У��CRC�Ƿ��ʼ��
	if ((USARTx->msgTxdHandler.msgCRCFlag != USART_CRC_NONE) && (CRCTask_Enable() == OK_0))
	{
		UINT32_T crcVal = 0;
		//---�ж�����У��ģʽ
		if (USARTx->msgTxdHandler.msgCRCFlag == USART_CRC_CHECKSUM)
		{
			crcVal = CRCTask_CheckSum(USARTx->msgTxdHandler.pMsgVal, USARTx->msgTxdHandler.msgIndexW);
			USART_RealTime_AddByte(USARTx, (UINT8_T)crcVal);
		}
		else if (USARTx->msgTxdHandler.msgCRCFlag == USART_CRC_CRC8)
		{
			crcVal = CRCTask_CRC8(USE_CRC8_07H, USARTx->msgTxdHandler.pMsgVal, USARTx->msgTxdHandler.msgIndexW);
			USART_RealTime_AddByte(USARTx, (UINT8_T)crcVal);
		}
		else if (USARTx->msgTxdHandler.msgCRCFlag == USART_CRC_CRC16)
		{
			crcVal = CRCTask_CRC16(USARTx->msgTxdHandler.pMsgVal, USARTx->msgTxdHandler.msgIndexW);
			USART_RealTime_AddByte(USARTx, (UINT8_T)(crcVal >> 8));
			USART_RealTime_AddByte(USARTx, (UINT8_T)crcVal);
		}
		else if (USARTx->msgTxdHandler.msgCRCFlag == USART_CRC_CRC32)
		{
			crcVal = CRCTask_CRC32(USARTx->msgTxdHandler.pMsgVal, USARTx->msgTxdHandler.msgIndexW);
			USART_RealTime_AddByte(USARTx, (UINT8_T)(crcVal >> 24));
			USART_RealTime_AddByte(USARTx, (UINT8_T)(crcVal >> 16));
			USART_RealTime_AddByte(USARTx, (UINT8_T)(crcVal >> 8));
			USART_RealTime_AddByte(USARTx, (UINT8_T)crcVal);
		}
		return OK_0;
	}
	//---�ж��Ƿ����ӻ��з�
	if ((USARTx->msgTxdHandler.msgAddNewLine==1))
	{
		USART_RealTime_AddByte(USARTx, 0x0D);
		USART_RealTime_AddByte(USARTx, 0x0A);
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� �����������ǰ�Ĳ�����Լ���ñ�ͷ������Ч���ݿ�ʼ��λ��
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_FillMode_Init(USART_HandlerType*USARTx,UINT8_T isChildCmd)
{
	//---�ȴ��������
	while ((USARTx->msgTxdHandler.msgTaskState == USART_BUSY)||(USARTx->msgTxdHandler.msgTaskState==USART_PRINTF))
	{
		WDT_RESET();
	}
	USARTx->msgTxdHandler.msgIndexW = 0;
	USARTx->msgTxdHandler.msgIndexF=0;
	//---������ݱ�ͷ
	USART_FillMode_AddByte( USARTx, USARTx->msgTxID );
	//---������ݳ���
	USART_FillMode_AddByte( USARTx, 0x00 );
	if (USARTx->msgTxdHandler.msgSize > 0xFF)
	{
		USART_FillMode_AddByte( USARTx, 0x00 );
		USARTx->msgTxdHandler.msgIndexF+=1;
	}
	//---�����豸ͨ�ŵ��豸ID
	if ((USARTx->msgCmdIndex - USARTx->msgIDIndex) != 0)
	{
		USART_FillMode_AddByte(USARTx, USARTx->msgID);
	}
	//---������/����
	USART_FillMode_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex]);
	//---У���Ƿ���������
	if (isChildCmd!=0)
	{
		//---������
		USART_FillMode_AddByte(USARTx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex + (isChildCmd == 0 ? 0 : 1)]);
	}
	//---��ʶ����ִ�н���ڻ������жϵ����
	USARTx->msgTxdHandler.msgIndexF = USARTx->msgTxdHandler.msgIndexW;
	//---����ִ�н��
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		�������������ڷ���
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_FillMode_AddByte(USART_HandlerType*USARTx, UINT8_T val)
{
	USARTx->msgTxdHandler.pMsgVal[USARTx->msgTxdHandler.msgIndexW] = val;
	USARTx->msgTxdHandler.msgIndexW++;
	if (USARTx->msgTxdHandler.msgIndexW >= USARTx->msgTxdHandler.msgSize)
	{
		USARTx->msgTxdHandler.msgIndexW = 0;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_FillMode_AddData(USART_HandlerType*USARTx, UINT8_T *pVal, UINT16_T length)
{
	UINT16_T i = 0;
	UINT8_T _return = OK_0;
	for (i = 0; i < length; i++)
	{
		_return = USART_FillMode_AddByte(USARTx, pVal[i]);
		//---�ж������Ƿ������ȷ
		if (_return != OK_0)
		{
			break;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����ִ�н����ʶ
//////�������:
//////�������:
//////˵		�������������ڷ���
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_FillMode_SetResultFlag(USART_HandlerType* USARTx, UINT8_T val)
{
	USARTx->msgTxdHandler.pMsgVal[USARTx->msgTxdHandler.msgIndexF] = val;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�д����ŵ�����ֵ
//////�������:
//////�������:
//////˵		�������������ڷ���
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_FillMode_AddIndexW(USART_HandlerType* USARTx, UINT16_T val)
{
	USARTx->msgTxdHandler.msgIndexW += val;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_CRCTask_Read(USART_HandlerType*USARTx)
{
	UINT32_T crcVal = 0;
	UINT32_T crcTemp = 0;
	//---�������ݵĸ���
	UINT16_T length = USARTx->msgRxdHandler.msgIndexW;
	//---У��CRC�Ƿ��ʼ��
	if ((USARTx->msgRxdHandler.msgCRCFlag != USART_CRC_NONE) && (CRCTask_Enable() == OK_0))
	{
		//---�ж�����У��ģʽ
		if (USARTx->msgRxdHandler.msgCRCFlag == USART_CRC_CHECKSUM)
		{
			length -= 1;
			if (USARTx->msgRxdHandler.msgSize < 250)
			{
				USARTx->msgRxdHandler.pMsgVal[1] = (UINT8_T)(length);
				//---��ȡУ���
				crcTemp = USARTx->msgRxdHandler.pMsgVal[length + 2];
				//---����У��ͼ���������ܳ���
				length += 2;
			}
			else
			{
				USARTx->msgRxdHandler.pMsgVal[1] = (UINT8_T)(length >> 8);
				USARTx->msgRxdHandler.pMsgVal[2] = (UINT8_T)(length);
				//---��ȡУ���
				crcTemp = USARTx->msgRxdHandler.pMsgVal[length + 3];
				//---����У��ͼ���������ܳ���
				length += 3;
			}
			//---����У���
			crcVal = CRCTask_CheckSum(USARTx->msgRxdHandler.pMsgVal, length);
		}
		else if (USARTx->msgRxdHandler.msgCRCFlag == USART_CRC_CRC8)
		{
			length -= 1;
			if (USARTx->msgRxdHandler.msgSize < 250)
			{
				USARTx->msgRxdHandler.pMsgVal[1] = (UINT8_T)(length);
				//---��ȡУ���
				crcTemp = USARTx->msgRxdHandler.pMsgVal[length + 2];
				//---����У��ͼ���������ܳ���
				length += 2;
			}
			else
			{
				USARTx->msgRxdHandler.pMsgVal[1] = (UINT8_T)(length >> 8);
				USARTx->msgRxdHandler.pMsgVal[2] = (UINT8_T)(length);
				//---��ȡУ���
				crcTemp = USARTx->msgRxdHandler.pMsgVal[length + 3];
				//---����У��ͼ���������ܳ���
				length += 3;
			}
			//---����CRC8У��ֵ
			crcVal = CRCTask_CRC8(USE_CRC8_07H, USARTx->msgRxdHandler.pMsgVal, length);
		}
		else if (USARTx->msgRxdHandler.msgCRCFlag == USART_CRC_CRC16)
		{
			length -= 2;
			if (USARTx->msgRxdHandler.msgSize < 250)
			{
				USARTx->msgRxdHandler.pMsgVal[1] = (UINT8_T)(length);
				//---��ȡCRC16�ĸ�λֵ
				crcTemp = USARTx->msgRxdHandler.pMsgVal[length + 1];
				//---��ȡCRC16�ĵ�λֵ
				crcTemp = (crcTemp << 8) + USARTx->msgRxdHandler.pMsgVal[length + 2];
				//---����У��ͼ���������ܳ���
				length += 2;
			}
			else
			{
				USARTx->msgRxdHandler.pMsgVal[1] = (UINT8_T)(length >> 8);
				USARTx->msgRxdHandler.pMsgVal[2] = (UINT8_T)(length);
				//---��ȡCRC16�ĸ�λֵ
				crcTemp = USARTx->msgRxdHandler.pMsgVal[length + 2];
				//---��ȡCRC16�ĵ�λֵ
				crcTemp = (crcTemp << 8) + USARTx->msgRxdHandler.pMsgVal[length + 3];
				//---����У��ͼ���������ܳ���
				length += 3;
			}
			//---����CRC16У��ֵ
			crcVal = CRCTask_CRC16(USARTx->msgRxdHandler.pMsgVal, length);
		}
		else if (USARTx->msgRxdHandler.msgCRCFlag == USART_CRC_CRC32)
		{
			length -= 4;
			if (USARTx->msgRxdHandler.msgSize < 250)
			{
				USARTx->msgRxdHandler.pMsgVal[1] = (UINT8_T)(length);
				//---��ȡCRC32�����λֵ
				crcTemp = USARTx->msgRxdHandler.pMsgVal[length - 1];
				//---��ȡCRC32�Ĵθ�λֵ
				crcTemp = (crcTemp << 8) + USARTx->msgRxdHandler.pMsgVal[length];
				//---��ȡCRC32�Ĵε�λֵ
				crcTemp = (crcTemp << 8) + USARTx->msgRxdHandler.pMsgVal[length + 1];
				//---��ȡCRC32�ĵ�λֵ
				crcTemp = (crcTemp << 8) + USARTx->msgRxdHandler.pMsgVal[length + 2];
				//---����У��ͼ���������ܳ���
				length += 2;
			}
			else
			{
				USARTx->msgRxdHandler.pMsgVal[1] = (UINT8_T)(length >> 8);
				USARTx->msgRxdHandler.pMsgVal[2] = (UINT8_T)(length);
				//---��ȡCRC32�����λֵ
				crcTemp = USARTx->msgRxdHandler.pMsgVal[length];
				//---��ȡCRC32�Ĵθ�λֵ
				crcTemp = (crcTemp << 8) + USARTx->msgRxdHandler.pMsgVal[length + 1];
				//---��ȡCRC32�Ĵε�λֵ
				crcTemp = (crcTemp << 8) + USARTx->msgRxdHandler.pMsgVal[length + 2];
				//---��ȡCRC32�ĵ�λֵ
				crcTemp = (crcTemp << 8) + USARTx->msgRxdHandler.pMsgVal[length + 3];
				length += 3;
			}
			crcVal = CRCTask_CRC32(USARTx->msgRxdHandler.pMsgVal, length);
		}
		//---�ȶ�CRC��ֵ
		if (crcVal != crcTemp)
		{
			return  ERROR_1;
		}
	}
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_CRCTask_Write(USART_HandlerType*USARTx)
{
	//---У��CRC�Ƿ��ʼ��
	if ((USARTx->msgTxdHandler.msgCRCFlag != USART_CRC_NONE) && (CRCTask_Enable() == OK_0))
	{
		UINT32_T crcVal = 0;
		//--Ҫ�������ݵ��ܳ���
		UINT16_T length = USARTx->msgTxdHandler.msgIndexW;
		//---�ж��Ƿ����ӻ��з�
		if ((USARTx->msgTxdHandler.msgAddNewLine==1))
		{
			length += 2;
		}
		//---���ݴ�С������
		if (USARTx->msgTxdHandler.msgSize < 0xFF)
		{
			USARTx->msgTxdHandler.pMsgVal[1] = (UINT8_T)(length- 2);
		}
		else
		{
			USARTx->msgTxdHandler.pMsgVal[1] = (UINT8_T)((length - 3) >> 8);
			USARTx->msgTxdHandler.pMsgVal[2] = (UINT8_T)((length - 3));
		}		
		//---�ж�����У��ģʽ
		if (USARTx->msgTxdHandler.msgCRCFlag == USART_CRC_CHECKSUM)
		{
			//---У���
			crcVal = CRCTask_CheckSum(USARTx->msgTxdHandler.pMsgVal, USARTx->msgTxdHandler.msgIndexW);
			USART_FillMode_AddByte(USARTx, (UINT8_T)crcVal);
		}
		else if (USARTx->msgTxdHandler.msgCRCFlag == USART_CRC_CRC8)
		{
			//---CRC8У��
			crcVal = CRCTask_CRC8(USE_CRC8_07H, USARTx->msgTxdHandler.pMsgVal, USARTx->msgTxdHandler.msgIndexW);
			USART_FillMode_AddByte(USARTx, (UINT8_T)crcVal);
		}
		else if (USARTx->msgTxdHandler.msgCRCFlag == USART_CRC_CRC16)
		{
			//---CRC16У��
			crcVal = CRCTask_CRC16(USARTx->msgTxdHandler.pMsgVal, USARTx->msgTxdHandler.msgIndexW);
			USART_FillMode_AddByte(USARTx, (UINT8_T)(crcVal >> 8));
			USART_FillMode_AddByte(USARTx, (UINT8_T)crcVal);
		}
		else if (USARTx->msgTxdHandler.msgCRCFlag == USART_CRC_CRC32)
		{
			//---CRC32У��
			crcVal = CRCTask_CRC32(USARTx->msgTxdHandler.pMsgVal, USARTx->msgTxdHandler.msgIndexW);
			USART_FillMode_AddByte(USARTx, (UINT8_T)(crcVal >> 24));
			USART_FillMode_AddByte(USARTx, (UINT8_T)(crcVal >> 16));
			USART_FillMode_AddByte(USARTx, (UINT8_T)(crcVal >> 8));
			USART_FillMode_AddByte(USARTx, (UINT8_T)crcVal);
		}
		//---�������ݵĴ�С
		USARTx->msgTxdHandler.msgCount = USARTx->msgTxdHandler.msgIndexW;
		return OK_0;
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USART_FillMode_WriteSTART(USART_HandlerType*USARTx, UINT8_T isNeedID)
{
	//---�ȴ��������
	while ((USARTx->msgTxdHandler.msgTaskState == USART_BUSY)||(USARTx->msgTxdHandler.msgTaskState==USART_PRINTF))
	{
		WDT_RESET();
	}
	//---���÷���״̬Ϊ������
	USARTx->msgTxdHandler.msgTaskState = USART_BUSY;
	//---�ж��Ƿ���Ҫ��䱨ͷ
	if (isNeedID == 1)
	{
		//---��䱨ͷ�����ݳ���
		USARTx->msgTxdHandler.pMsgVal[0] = USARTx->msgTxID;
	}
	//---����豸ID
	if ((USARTx->msgCmdIndex - USARTx->msgIDIndex) != 0)
	{
		USARTx->msgTxdHandler.pMsgVal[USARTx->msgIDIndex] = USARTx->msgID;
	}	
	//---����CRC����
	USART_CRCTask_Write(USARTx);
	//---�ж��Ƿ����ӻ��з�
	if (( USARTx->msgTxdHandler.msgAddNewLine == 1 ))
	{
		USART_FillMode_AddByte( USARTx, 0x0D );
		USART_FillMode_AddByte( USARTx, 0x0A );
	}	
	//---���ݴ�С������
	if (USARTx->msgTxdHandler.msgSize < 0xFF)
	{
		USARTx->msgTxdHandler.pMsgVal[1] = (UINT8_T)(USARTx->msgTxdHandler.msgIndexW - 2);
	}
	else
	{
		USARTx->msgTxdHandler.pMsgVal[1] = (UINT8_T)((USARTx->msgTxdHandler.msgIndexW - 3) >> 8);
		USARTx->msgTxdHandler.pMsgVal[2] = (UINT8_T)((USARTx->msgTxdHandler.msgIndexW - 3));
	}
	USARTx->msgTxdHandler.msgCount=USARTx->msgTxdHandler.msgIndexW;
	//---����485Ϊ����ģʽ
	USART_485GPIOInit(USARTx, USART_485_TX_ENABLE);
	//---�л����Ͷ˿�Ϊ���ģʽ
	USART_GPIOInit(USARTx, USART_TXGPIO_SET_OUTPUT);
	//---У���ǲ���DMAģʽ
	if (USARTx->msgTxdHandler.msgIsDMA==0)
	{
		//---�������ݼĴ������ж�ʹ��
		LL_USART_EnableIT_TXE(USARTx->msgUSART);
	}
	else
	{
		USART_Write_DMA_RESTART(USARTx);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ��ȡ�����־
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_GetOVF(USART_HandlerType* USARTx, UINT8_T isRx)
{
	if (isRx)
	{
		return USARTx->msgRxdHandler.msgOverFlow;
	}
	else
	{
		return USARTx->msgTxdHandler.msgOverFlow;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ��������־
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_ClearOVF(USART_HandlerType* USARTx, UINT8_T isRx)
{
	if (isRx)
	{
		USARTx->msgRxdHandler.msgOverFlow = 0;
	}
	else
	{
		USARTx->msgTxdHandler.msgOverFlow = 0;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_GetReadState(USART_HandlerType* USARTx)
{
	return USARTx->msgRxdHandler.msgTaskState;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_ClearReadState(USART_HandlerType* USARTx)
{
	USARTx->msgRxdHandler.msgTaskState = USART_OK;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_GetWriteState(USART_HandlerType* USARTx)
{
	return USARTx->msgTxdHandler.msgTaskState;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_ClearWriteState(USART_HandlerType* USARTx)
{
	USARTx->msgTxdHandler.msgTaskState = USART_OK;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USART_Read_Init(USART_HandlerType*  USARTx)
{
	//---����485λ����ģʽ
	USART_485GPIOInit(USARTx, USART_485_RX_ENABLE);
	//---���㲽��
	USARTx->msgRxdHandler.msgStep = 0;
	//---���д��������
	USARTx->msgRxdHandler.msgIndexW = 0;
	//---�������������
	USARTx->msgRxdHandler.msgIndexR = 0;
	//---����������ݸ���
	USARTx->msgRxdHandler.msgCount = 0;
	//---���������ɱ�־
	USARTx->msgRxdHandler.msgTaskState = USART_BUSY;
	//---���㳬ʱ����
	USARTx->msgRxdHandler.msgRecordTime = 0;
	//---���㳬ʱ����
	USARTx->msgRxdHandler.msgEndTime = 0;
	//---���㳬ʱ��־
	USARTx->msgRxdHandler.msgOverFlow = 0;
	//---У���ǲ���DMAģʽ
	if(USARTx->msgRxdHandler.msgIsDMA!=0)
	{
		USART_Read_DMA_RESTART(USARTx);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_Write_Init(USART_HandlerType*  USARTx)
{
	//---���÷���״̬Ϊ�������
	USARTx->msgTxdHandler.msgTaskState = USART_OK;
	//---���д��������
	USARTx->msgTxdHandler.msgIndexW = 0;
	//---�������������
	USARTx->msgTxdHandler.msgIndexR = 0;
	//---���㷢�����ݸ���
	USARTx->msgTxdHandler.msgCount = 0;
	//---���㳬ʱ����
	USARTx->msgTxdHandler.msgRecordTime = 0;
	//---���㳬ʱ����
	USARTx->msgTxdHandler.msgEndTime = 0;
	//---���㳬ʱ��־
	USARTx->msgTxdHandler.msgOverFlow = 0;
	//---�����������
	USARTx->msgTxdHandler.msgStep = 0;
	//---����485Ϊ����ģʽ
	USART_485GPIOInit(USARTx, USART_485_RX_ENABLE);
	//---���ݷ�����ɣ��л��˿�Ϊ����ģʽ
	USART_GPIOInit(USARTx, USART_TXGPIO_SET_INPUT);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� У���豸��ID��Ϣ
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_DeviceID(USART_HandlerType*USARTx)
{
	if ((USARTx->msgCmdIndex - USARTx->msgIDIndex) != 0)
	{
		if (USARTx->msgRxdHandler.pMsgVal[USARTx->msgIDIndex] != USARTx->msgID)
		{
			return ERROR_1;
		}
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void USART_PrintfSuspend(USART_HandlerType* USARTx)
{
#ifdef USE_USART_PRINTF
	//---��鷢�ͼĴ������ж��Ƿ�ʹ��
	if (LL_USART_IsEnabledIT_TXE(USARTx->msgUSART))
	{
		//---�ȴ��������
		while (LL_USART_IsActiveFlag_TXE(USARTx->msgUSART) != RESET)
		{
			WDT_RESET();
		}
	}
	//---��鷢������ж�
	if (LL_USART_IsEnabledIT_TC(USARTx->msgUSART))
	{
		//---�ȴ��������
		while ((LL_USART_IsActiveFlag_TC(USARTx->msgUSART) != RESET) && (USARTx->msgTxdHandler.msgStep == 0))
		{
			WDT_RESET();
		}
		LL_USART_ClearFlag_TC(USARTx->msgUSART);
	}
	//---����485Ϊ����ģʽ
	USART_485GPIOInit(USARTx, USART_485_TX_ENABLE);
	//---�л����Ͷ˿�Ϊ���ģʽ
	USART_GPIOInit(USARTx, USART_TXGPIO_SET_OUTPUT);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��ָ�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void USART_PrintfResume(USART_HandlerType* USARTx)
{
#ifdef USE_USART_PRINTF
	//---����485Ϊ����ģʽ
	USART_485GPIOInit(USARTx, USART_485_RX_ENABLE);
	//---���ݷ�����ɣ��л��˿�Ϊ����ģʽ
	USART_GPIOInit(USARTx, USART_TXGPIO_SET_INPUT);
#endif
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void USART_Printf(USART_HandlerType*USARTx, char*fmt, ...)
{
#ifdef USE_USART_PRINTF
	//---�������
	USART_PrintfSuspend(USARTx);
	//---��������
	UINT16_T length = 0; 
	va_list arg_ptr;
	va_start(arg_ptr, fmt);
	//---�������ַ����д�ӡ���ݡ����ݸ�ʽ�û��Զ���;���ز��������������ַ����ĳ���
	length = (UINT16_T)vsnprintf(g_PrintfBuffer, USART_PRINTF_SIZE, fmt, arg_ptr);
	va_end(arg_ptr);
	//---�ж�����
	if (length> USART_PRINTF_SIZE)
	{
		length = USART_PRINTF_SIZE;
	}
	USARTx->msgPrintfCount = length;
	USARTx->msgPrintfIndex = 1;
	USARTx->msgTxdHandler.msgTaskState = USART_PRINTF;
	//---�������,�������ݷ�������жϲ�ʹ��
	LL_USART_EnableIT_TC(USARTx->msgUSART);
	//---����8Bit������
	LL_USART_TransmitData8(USARTx->msgUSART, g_PrintfBuffer[0]);	
#endif	
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USART_ITPrintf_TCTask(USART_HandlerType* USARTx)
{
#ifdef USE_USART_PRINTF
	if (USARTx->msgPrintfIndex>=USARTx->msgPrintfCount)
	{
		//---�������,�������ݷ�������жϲ�ʹ��
		LL_USART_DisableIT_TC(USARTx->msgUSART);
		//---�ָ�����
		USART_PrintfResume(USARTx);
		USARTx->msgTxdHandler.msgTaskState = USART_OK;
	}
	else
	{
		//---����8Bit������
		LL_USART_TransmitData8(USARTx->msgUSART, g_PrintfBuffer[USARTx->msgPrintfIndex]);
		USARTx->msgPrintfIndex++;
	}
#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_IT_TCTask(USART_HandlerType* USARTx)
{
	if (USARTx->msgTxdHandler.msgTaskState == USART_BUSY)
	{
		USART_ITWrite_TCTask(USARTx);
	}
	else if (USARTx->msgTxdHandler.msgTaskState == USART_PRINTF)
	{
		USART_ITPrintf_TCTask(USARTx);
	}
	else
	{
		USARTx->msgTxdHandler.msgTaskState = USART_OK;
		LL_USART_DisableIT_TC(USARTx->msgUSART);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ӡϵͳʱ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void USART_PrintfClockFreq(USART_HandlerType*USARTx)
{
	LL_RCC_ClocksTypeDef rccClock = { 0 };
	//---��ȡϵͳʱ��
	LL_RCC_GetSystemClocksFreq(&rccClock);
	//---��ӡϵͳʱ��
	USART_Printf(USARTx, "SYSCLK=%UHz\r\n", rccClock.SYSCLK_Frequency);
	//---��ӡϵͳʱ��
	USART_Printf(USARTx, "HCLK=%UHz\r\n", rccClock.HCLK_Frequency);
	//---��ӡϵͳʱ��
	USART_Printf(USARTx, "PCLK1=%UHz\r\n", rccClock.PCLK1_Frequency);
	//---��ӡϵͳʱ��
	USART_Printf(USARTx, "PCLK2=%UHz\r\n", rccClock.PCLK2_Frequency);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_Clock(USART_TypeDef* USARTx, UINT8_T isEnable)
{
	if (USARTx == USART1)
	{
		if (isEnable)
		{
			//---ʹ��USART1��ʱ���ź�
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
		}
		else
		{
			//---��ʹ��USART1��ʱ���ź�
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_USART1);
		}
		return OK_0;
	}
	if (USARTx == USART2)
	{
		if (isEnable)
		{
			//---ʹ��USART2��ʱ���ź�
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
		}
		else
		{
			//---��ʹ��USART2��ʱ���ź�
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_USART2);
		}
		return OK_0;
	}
#if defined(USART3)
	if (USARTx == USART3)
	{
		if (isEnable)
		{
			//---ʹ��USART3��ʱ���ź�
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3);
		}
		else
		{
			//---��ʹ��USART3��ʱ���ź�
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_USART3);
		}
		return OK_0;
	}
#endif /* USART3 */
#if defined(USART6)
	if (USARTx == USART6)
	{
		if (isEnable)
		{
			//---ʹ��USART6��ʱ���ź�
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART6);
		}
		else
		{
			//---��ʹ��USART6��ʱ���ź�
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_USART6);
		}
		return OK_0;
	}
#endif /* USART6 */
#if defined(UART4)
	if (USARTx == UART4)
	{
		if (isEnable)
		{
			//---ʹ��USART4��ʱ���ź�
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART4);
		}
		else
		{
			//---��ʹ��USART4��ʱ���ź�
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART4);
		}
		return OK_0;
	}
#endif /* UART4 */
#if defined(UART5)
	if (USARTx == UART5)
	{
		if (isEnable)
		{
			//---ʹ��USART5��ʱ���ź�
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART5);
		}
		else
		{
			//---��ʹ��USART5��ʱ���ź�
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART5);
		}
		return OK_0;
	}
#endif /* UART5 */
#if defined(UART7)
	if (USARTx == UART7)
	{
		if (isEnable)
		{
			//---ʹ��USART7��ʱ���ź�
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART7);
		}
		else
		{
			//---��ʹ��USART7��ʱ���ź�
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART7);
		}
		return OK_0;
	}
#endif /* UART7 */
#if defined(UART8)
	if (USARTx == UART8)
	{
		if (isEnable)
		{
			//---ʹ��USART8��ʱ���ź�
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART8);
		}
		else
		{
			//---��ʹ��USART8��ʱ���ź�
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART8);
		}
		return OK_0;
	}
#endif /* UART8 */
#if defined(UART9)
	if (USARTx == UART9)
	{
		if (isEnable)
		{
			//---ʹ��USART9��ʱ���ź�
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_UART9);
		}
		else
		{
			//---��ʹ��USART9��ʱ���ź�
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_UART9);
		}
		return OK_0;
	}
#endif /* UART9 */
#if defined(UART10)
	if (USARTx == UART10)
	{
		if (isEnable)
		{
			//---ʹ��USART10��ʱ���ź�
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_UART10);
		}
		else
		{
			//---��ʹ��USART10��ʱ���ź�
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_UART10);
		}
		return OK_0;
	}
#endif /* UART10 */
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_DeInit(USART_HandlerType*USARTx)
{
	LL_USART_DeInit(USARTx->msgUSART);
	USART_Clock(USARTx->msgUSART, 0);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_ParamInit(USART_HandlerType *USARTx, UINT8_T id, UINT8_T idIndex, UINT8_T cmdIndex, UINT8_T d1Index, UINT8_T d2Index)
{
	USARTx->msgID = id;
	USARTx->msgIDIndex = idIndex;
	USARTx->msgCmdIndex = cmdIndex;
	USARTx->msgDataOneIndex = d1Index;
	USARTx->msgDataTwoIndex = d2Index;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART1_ConfigInit(USART_HandlerType* USARTx)
{
	//---USART1 GPIO Configuration
	//---PA9  ------> USART1_TX---�˿ڸ���Ϊ7
	//---PA10 ------> USART1_RX---�˿ڸ���Ϊ7
	//---ʹ�ܶ˿�ʱ��
	GPIOTask_Clock(GPIOA, 1);
	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	//---ģʽ����
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	//---�����ٶ�
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	//---���ù��ܵ��������
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	//---��������ʹ��
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
#ifdef USE_MCU_STM32F1
	//---TX
	GPIO_InitStruct.Pin = LL_GPIO_PIN_9;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	//---RX
	GPIO_InitStruct.Pin = LL_GPIO_PIN_10;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
#else
	//---�˿ں�
	GPIO_InitStruct.Pin = LL_GPIO_PIN_9 | LL_GPIO_PIN_10;
	//---���ù���ΪUSART1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
#endif
	//---������Ϣ�ṹ���е���Ϣ
	USARTx->msgTxPort = GPIOA;
	USARTx->msgTxBit = LL_GPIO_PIN_9;
	USARTx->msgUSART = USART1;
	//---�������
	USARTx->msgIndex = 1 + 1;
	//---ע�����ڵĳ�ʼ��
	LL_USART_DeInit(USARTx->msgUSART);
	//---ʹ��USART1��ʱ���ź�
	USART_Clock(USARTx->msgUSART, 1);
	//---USART�Ľӿڽṹ��
	LL_USART_InitTypeDef USART_InitStruct = { 0 };
	//---������
	USART_InitStruct.BaudRate = 115200;
	//---����λ
	USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
	//---ֹͣλ
	USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
	//---У��λ
	USART_InitStruct.Parity = LL_USART_PARITY_NONE;
	//---����Ϊ�շ�ģʽ
	USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
	//---Ӳ��������---Ĭ��Ϊ��
	USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
	//---����������
#ifdef USART_CR1_OVER8
	//---����������---Ĭ������Ϊ16
	USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
#endif
	//---��ʼ������
	LL_USART_Init(USARTx->msgUSART, &USART_InitStruct);
	//---�����첽ģʽ����
	LL_USART_ConfigAsyncMode(USARTx->msgUSART);
	//---У���Ƿ���Ҫ��ʱ����
	if (USARTx->msgTimeTick != NULL)
	{
		USARTx->msgRxdHandler.msgMaxTime = 100;
		USARTx->msgTxdHandler.msgMaxTime = 100;
	}
	else
	{
		USARTx->msgRxdHandler.msgMaxTime = 0;
		USARTx->msgTxdHandler.msgMaxTime = 0;
	}
	//---����CRC�ĵȼ�
	USARTx->msgTxdHandler.msgCRCFlag = USART_CRC_NONE;
	//---���ñ�ͷ�ͱ�β
	USARTx->msgRxID = 0x55;
	USARTx->msgTxID = 0x5A;
	//---����͵�ַ����
	USART_ParamInit(USARTx, USART1_DEVICE_ID, USART1_ID_INDEX, USART1_CMD_INDEX, USART1_DATA1_INDEX, USART1_DATA2_INDEX);
	//---����485Ϊ����ģʽ--�������ģʽ������Ϊ����ģʽ
	USART_485GPIOInit(USARTx, USART_485_RX_ENABLE);
	//---����TX�˿�Ϊ����ģʽ
	USART_GPIOInit(USARTx, USART_TXGPIO_SET_INPUT);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART1_Init(USART_HandlerType*USARTx)
{
	USART1_ConfigInit(USARTx);
	//---У������ǲ���DMA����
	if (USARTx->msgRxdHandler.msgIsDMA==0)
	{
		//---ʹ�ܽ����ж�
		LL_USART_EnableIT_RXNE(USART1);
	}
	else
	{
		//---ʹ�ܽ��տ����ж�
		LL_USART_EnableIT_IDLE(USART1);
		//---��ʼ��DMA����
		USART1_Read_DMA_Init(USARTx);
	}
	//---У�鷢���ǲ���DMA���䷽ʽ
	if (USARTx->msgTxdHandler.msgIsDMA != 0)
	{
		USART1_Write_DMA_Init(USARTx);
	}
	//---USART1_IRQ�ж�����---�жϵȼ�����
	NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 2, 0));
	//---ʹ���ж�
	NVIC_EnableIRQ(USART1_IRQn);
	//---ʹ�ܴ���
	LL_USART_Enable(USART1);	
	//---��ӡ��ʼ����Ϣ
	USART_Printf(USARTx, "=>>����1�ĳ�ʼ��<<=\r\n");
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART2_Init(USART_HandlerType*USARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART3_Init(USART_HandlerType*USARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��жϴ�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////��
void USART_IRQTask(USART_HandlerType* USARTx)
{
	//---���ݽ����жϴ�����---���ռĴ�����Ϊ��
	if (LL_USART_IsActiveFlag_RXNE(USARTx->msgUSART) && LL_USART_IsEnabledIT_RXNE(USARTx->msgUSART))
	{
		//---�жϴ�����
		USART_ITRead_Task(USARTx, LL_USART_ReceiveData8(USARTx->msgUSART));
		//---����жϱ�־λ
		LL_USART_ClearFlag_RXNE(USARTx->msgUSART);
	}

	//---���ݷ��ͼĴ����շ����жϴ�����
	if (LL_USART_IsActiveFlag_TXE(USARTx->msgUSART) && LL_USART_IsEnabledIT_TXE(USARTx->msgUSART))
	{
		//---�жϴ�����
		USART_ITWrite_TXETask(USARTx);
	}
	//---���ݷ�������жϴ�����
	if (LL_USART_IsActiveFlag_TC(USARTx->msgUSART) && LL_USART_IsEnabledIT_TC(USARTx->msgUSART))
	{
		//---�жϴ�����
		USART_IT_TCTask(USARTx);
		//---����жϱ�־λ
		LL_USART_ClearFlag_TC(USARTx->msgUSART);
	}
	//---UART5��UART5��������CTS���
	if ((USARTx->msgUSART!=UART4)&& (USARTx->msgUSART != UART5))
	{
		//---CTS״̬�߱仯�ж�
		if (LL_USART_IsActiveFlag_nCTS(USARTx->msgUSART) && LL_USART_IsEnabledIT_CTS(USARTx->msgUSART))
		{
			//---�жϴ�����

			//---����жϱ�־λ
			LL_USART_ClearFlag_nCTS(USARTx->msgUSART);
		}
	}
	//---LIN��·����ж�
	if (LL_USART_IsActiveFlag_LBD(USARTx->msgUSART) && LL_USART_IsEnabledIT_LBD(USARTx->msgUSART))
	{
		//---�жϴ�����

		//---����жϱ�־λ
		LL_USART_ClearFlag_LBD(USARTx->msgUSART);
	}
	//---����״̬�ж�
	if (LL_USART_IsActiveFlag_IDLE(USARTx->msgUSART) && LL_USART_IsEnabledIT_IDLE(USARTx->msgUSART))
	{
		//---�жϴ�����,DMA���ݽ���
		USART_DMA_IDLETask(USARTx);
		//---��������жϱ�־λ
		LL_USART_ClearFlag_IDLE(USARTx->msgUSART);
		//---���DMA�жϱ�ʶ
		LL_DMA_ClearFlag(USARTx->msgRxdHandler.msgDMA, USARTx->msgRxdHandler.msgDMAChannelOrStream);
	}
	//---��������ж�
	if (LL_USART_IsActiveFlag_ORE(USARTx->msgUSART) && LL_USART_IsEnabledIT_ERROR(USARTx->msgUSART))
	{
		//---�жϴ�����

		//---����жϱ�־λ
		LL_USART_ClearFlag_ORE(USARTx->msgUSART);
	}
	//---�����ж�
	if (LL_USART_IsActiveFlag_NE(USARTx->msgUSART) && LL_USART_IsEnabledIT_ERROR(USARTx->msgUSART))
	{
		//---�жϴ�����

		//---����жϱ�־λ
		LL_USART_ClearFlag_NE(USARTx->msgUSART);
	}
	//---֡�����ж�
	if (LL_USART_IsActiveFlag_FE(USARTx->msgUSART) && LL_USART_IsEnabledIT_ERROR(USARTx->msgUSART))
	{
		//---�жϴ�����

		//---����жϱ�־λ
		LL_USART_ClearFlag_FE(USARTx->msgUSART);
	}
	//---��żУ���ж�
	if (LL_USART_IsActiveFlag_PE(USARTx->msgUSART) && LL_USART_IsEnabledIT_PE(USARTx->msgUSART))
	{
		//---�жϴ�����

		//---����жϱ�־λ
		LL_USART_ClearFlag_PE(USARTx->msgUSART);
	}
}

////////////////////////////////////////////////////////////////////////////////
////DMAģʽ����
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����DMA��ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART1_Read_DMA_Init(USART_HandlerType* USARTx)
{
	//>>>---RX��DMA����
	//---��DMAȫ���Ĵ�����������Ϊȱʡֵ
#ifdef USE_MCU_STM32F1
	//---F1��Ӧ�ǵ�DMA1��ͨ��1��ӦADC1
	LL_DMA_DeInit(DMA1, LL_DMA_CHANNEL_1);
	//---DMAʱ����������
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
#else
	LL_DMA_DeInit(DMA2, LL_DMA_STREAM_2);
	//---DMAʱ����������
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2);
	USARTx->msgRxdHandler.msgDMA = DMA2;
	USARTx->msgRxdHandler.msgDMAChannelOrStream = LL_DMA_STREAM_2;
#endif
	//---DMA��ʼ���ṹ��
	LL_DMA_InitTypeDef DMA_InitTypeDef = { 0 };
#ifndef USE_MCU_STM32F1
	//---DMAͨ��
	DMA_InitTypeDef.Channel = LL_DMA_CHANNEL_4;
#endif
	//---���ݴ�С
	DMA_InitTypeDef.NbData = USARTx->msgRxdHandler.msgSize;
	//---��������赽�洢��
	DMA_InitTypeDef.Direction = LL_DMA_DIRECTION_PERIPH_TO_MEMORY;
#ifndef USE_MCU_STM32F1
	//---����FIFO��ֱ��ģʽ
	DMA_InitTypeDef.FIFOMode = LL_DMA_FIFOMODE_DISABLE;
	//---�������ֽ�
	DMA_InitTypeDef.FIFOThreshold = LL_DMA_FIFOTHRESHOLD_1_2;
#endif
	//---�洢����ַ
	DMA_InitTypeDef.MemoryOrM2MDstAddress = (UINT32_T)(USARTx->msgRxdHandler.pMsgVal);
	//---�������ֽ�
	DMA_InitTypeDef.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;
	//---�洢����ַ����
	DMA_InitTypeDef.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT;
	//---DMA����ģʽ
	DMA_InitTypeDef.Mode = LL_DMA_MODE_NORMAL; //LL_DMA_MODE_CIRCULAR;
	//---DMA�����ַ
	DMA_InitTypeDef.PeriphOrM2MSrcAddress = (UINT32_T) & (USARTx->msgUSART->DR);
#ifndef USE_MCU_STM32F1
	//---��FIFO
	DMA_InitTypeDef.PeriphBurst = LL_DMA_PBURST_SINGLE;
#endif
	//---�������ֽ�
	DMA_InitTypeDef.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
	//---�������ַ����
	DMA_InitTypeDef.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
	//---����ͨ�����ȼ�Ϊ��
	DMA_InitTypeDef.Priority = LL_DMA_PRIORITY_HIGH;
	//---DMA��ʼ��
#ifdef USE_MCU_STM32F1
	//---��ʼ��DMA
	LL_DMA_Init(USARTx->msgRxHandler.msgDMA, USARTx->msgRxHandler.msgDMAChannelOrStream, &DMA_InitTypeDef);
	//---ʹ��DMA
	LL_DMA_EnableChannel(USARTx->msgRxHandler.msgDMA, USARTx->msgRxHandler.msgDMAChannelOrStream);
#else
	//---��ʼ��DMA
	LL_DMA_Init(USARTx->msgRxdHandler.msgDMA, USARTx->msgRxdHandler.msgDMAChannelOrStream, &DMA_InitTypeDef);
	//---ʹ��DMA
	LL_DMA_EnableStream(USARTx->msgRxdHandler.msgDMA, USARTx->msgRxdHandler.msgDMAChannelOrStream);
	//---���ܴ��ڽ���DMA
	LL_USART_EnableDMAReq_RX(USARTx->msgUSART);
#endif
	//---�ж�����
#ifdef USE_MCU_STM32F1
	//---DMA�ж�����
	NVIC_SetPriority(DMA1_Channel1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 1, 0));
	//---ʹ���ж�
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);
#else
	//---DMA�ж�����
	NVIC_SetPriority(DMA2_Stream2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 2, 0));
	//---ʹ���ж�
	NVIC_EnableIRQ(DMA2_Stream2_IRQn);
#endif
	//---ʹ��DMA��������ж�
	LL_DMA_EnableIT_TC(USARTx->msgRxdHandler.msgDMA, USARTx->msgRxdHandler.msgDMAChannelOrStream);
	//<<<---RX��DMA���ý���
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����DMA�ĳ�ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART1_Write_DMA_Init(USART_HandlerType* USARTx)
{
	//>>>---TX��DMA����
//---��DMAȫ���Ĵ�����������Ϊȱʡֵ
#ifdef USE_MCU_STM32F1
	//---F1��Ӧ�ǵ�DMA1��ͨ��1��ӦADC1
	LL_DMA_DeInit(DMA1, LL_DMA_CHANNEL_1);
	//---DMAʱ����������
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
#else
	LL_DMA_DeInit(DMA2, LL_DMA_STREAM_7);
	//---DMAʱ����������
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2);
	USARTx->msgTxdHandler.msgDMA = DMA2;
	USARTx->msgTxdHandler.msgDMAChannelOrStream = LL_DMA_STREAM_7;
#endif
	//---DMA��ʼ���ṹ��
	LL_DMA_InitTypeDef DMA_InitTypeDef = { 0 };
#ifndef USE_MCU_STM32F1
	//---DMAͨ��
	DMA_InitTypeDef.Channel = LL_DMA_CHANNEL_4;
#endif
	//---���ݴ�С
	DMA_InitTypeDef.NbData = USARTx->msgTxdHandler.msgSize;
	//---����Ӵ洢��������
	DMA_InitTypeDef.Direction = LL_DMA_DIRECTION_MEMORY_TO_PERIPH;
#ifndef USE_MCU_STM32F1
	//---����FIFO��ֱ��ģʽ
	DMA_InitTypeDef.FIFOMode = LL_DMA_FIFOMODE_DISABLE;
	//---�������ֽ�
	DMA_InitTypeDef.FIFOThreshold = LL_DMA_FIFOTHRESHOLD_1_2;
#endif
	//---�洢����ַ
	DMA_InitTypeDef.MemoryOrM2MDstAddress = (UINT32_T)(USARTx->msgTxdHandler.pMsgVal);
	//---�������ֽ�
	DMA_InitTypeDef.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;
	//---�洢����ַ����
	DMA_InitTypeDef.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT;
	//---DMA����ģʽ
	DMA_InitTypeDef.Mode = LL_DMA_MODE_NORMAL; //LL_DMA_MODE_CIRCULAR;
	//---DMA�����ַ
	DMA_InitTypeDef.PeriphOrM2MSrcAddress = (UINT32_T) & (USARTx->msgUSART->DR);
#ifndef USE_MCU_STM32F1
	//---��FIFO
	DMA_InitTypeDef.PeriphBurst = LL_DMA_PBURST_SINGLE;
#endif
	//---�������ֽ�
	DMA_InitTypeDef.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
	//---�������ַ����
	DMA_InitTypeDef.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
	//---����ͨ�����ȼ�Ϊ��
	DMA_InitTypeDef.Priority = LL_DMA_PRIORITY_HIGH;
	//---DMA��ʼ��
#ifdef USE_MCU_STM32F1
	//---��ʼ��DMA
	LL_DMA_Init(USARTx->msgTxHandler.msgDMA, USARTx->msgTxHandler.msgDMAChannelOrStream, &DMA_InitTypeDef);
	//---ʹ��DMA
	LL_DMA_EnableChannel(USARTx->msgTxHandler.msgDMA, USARTx->msgTxHandler.msgDMAChannelOrStream);
#else
	//---��ʼ��DMA
	LL_DMA_Init(USARTx->msgTxdHandler.msgDMA, USARTx->msgTxdHandler.msgDMAChannelOrStream, &DMA_InitTypeDef);
	//---ʹ��DMA,ע�ⷢ��״̬�²���ʹ��DMA��ֻ����Ҫ��ʱ����ܴ�
	//LL_DMA_EnableStream(USARTx->msgTxHandler.msgDMA, USARTx->msgTxHandler.msgDMAChannelOrStream);
	//---ʹ�ܴ��ڷ���DMA
	LL_USART_EnableDMAReq_TX(USARTx->msgUSART);
#endif
	//---�ж�����
#ifdef USE_MCU_STM32F1
	//---DMA�ж�����
	NVIC_SetPriority(DMA1_Channel1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 1, 0));
	//---ʹ���ж�
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);
#else
	//---DMA�ж�����
	NVIC_SetPriority(DMA2_Stream7_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 2, 0));
	//---ʹ���ж�
	NVIC_EnableIRQ(DMA2_Stream7_IRQn);
#endif
	//---ʹ��DMA��������ж�
	LL_DMA_EnableIT_TC(USARTx->msgTxdHandler.msgDMA, USARTx->msgTxdHandler.msgDMAChannelOrStream);
	//<<<---TX��DMA���ý���
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��ر�DMA�Ľ���ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT16_T USART_Read_DMA_STOP(USART_HandlerType* USARTx)
{
#ifdef USE_MCU_STM32F1
	//---ʹ��DMA
	LL_DMA_DisableChannel(USARTx->msgRxHandler.msgDMA, USARTx->msgRxHandler.msgDMAChannelOrStream);
	LL_DMA_ClearFlag_GI1(USARTx->msgRxHandler.msgDMA);
#else
	//---��ʹ��DMA
	LL_DMA_DisableStream(USARTx->msgRxdHandler.msgDMA, USARTx->msgRxdHandler.msgDMAChannelOrStream);
#endif
	LL_DMA_ClearFlag(USARTx->msgRxdHandler.msgDMA, USARTx->msgRxdHandler.msgDMAChannelOrStream);
	//---����������ݵĳ���
	UINT16_T length = USARTx->msgRxdHandler.msgSize - LL_DMA_GetDataLength(USARTx->msgRxdHandler.msgDMA, USARTx->msgRxdHandler.msgDMAChannelOrStream);
	return length;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����DMA�Ľ���ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_Read_DMA_RESTART(USART_HandlerType* USARTx)
{
	//---����DMA������
#ifdef USE_MCU_STM32F1
	//---����DMA��ȡ���ݵĴ�С
	LL_DMA_SetDataLength(USARTx->msgRxHandler.msgDMA, USARTx->msgRxHandler.msgDMAChannelOrStream, USARTx->msgRxHandler.msgSize);
	//---ʹ��DMA
	LL_DMA_EnableChannel(USARTx->msgRxHandler.msgDMA, USARTx->msgRxHandler.msgDMAChannelOrStream);
#else
	//---����DMA��ȡ���ݵĴ�С
	LL_DMA_SetDataLength(USARTx->msgRxdHandler.msgDMA, USARTx->msgRxdHandler.msgDMAChannelOrStream, USARTx->msgRxdHandler.msgSize);
	//---ʹ��DMA
	LL_DMA_EnableStream(USARTx->msgRxdHandler.msgDMA, USARTx->msgRxdHandler.msgDMAChannelOrStream);
#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ֹͣDMA�ķ���ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT16_T USART_Write_DMA_STOP(USART_HandlerType* USARTx)
{
#ifdef USE_MCU_STM32F1
	//---ʹ��DMA
	LL_DMA_DisableChannel(USARTx->msgRxHandler.msgDMA, USARTx->msgRxHandler.msgDMAChannelOrStream);
	LL_DMA_ClearFlag_GI1(USARTx->msgRxHandler.msgDMA);
#else
	//---��ʹ��DMA
	LL_DMA_DisableStream(USARTx->msgTxdHandler.msgDMA, USARTx->msgTxdHandler.msgDMAChannelOrStream);
#endif
	LL_DMA_ClearFlag(USARTx->msgTxdHandler.msgDMA, USARTx->msgTxdHandler.msgDMAChannelOrStream);
	//---����������ݵĳ���
	UINT16_T length = USARTx->msgTxdHandler.msgSize - LL_DMA_GetDataLength(USARTx->msgTxdHandler.msgDMA, USARTx->msgTxdHandler.msgDMAChannelOrStream);
	return length;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����DMA�ķ���ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_Write_DMA_RESTART(USART_HandlerType* USARTx)
{
	//---����DMA�������ݵĴ�С
	LL_DMA_SetDataLength(USARTx->msgTxdHandler.msgDMA, USARTx->msgTxdHandler.msgDMAChannelOrStream, USARTx->msgTxdHandler.msgCount);
#ifdef USE_MCU_STM32F1
	//---ʹ��DMA
	LL_DMA_EnableChannel(USARTx->msgTxHandler.msgDMA, USARTx->msgTxHandler.msgDMAChannelOrStream);
#else
	//---ʹ��DMA
	LL_DMA_EnableStream(USARTx->msgTxdHandler.msgDMA, USARTx->msgTxdHandler.msgDMAChannelOrStream);
#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_DMA_IDLETask(USART_HandlerType* USARTx)
{
	UINT8_T _return = OK_0;
	//---ֹͣ����DMAģʽ,����ȡ�������ݵĳ���
	UINT16_T dataLength= USART_Read_DMA_STOP(USARTx);
	//---У�鱨ͷ�Ƿ���ȷ
	if (USARTx->msgRxdHandler.pMsgVal[0] == USARTx->msgRxID)
	{
		//---���ݳ�����Ϣ
		UINT16_T length = USARTx->msgRxdHandler.pMsgVal[1];
		//---У�����ݳ�����Ϣ
		if (USARTx->msgRxdHandler.msgSize < 0xFF)
		{
			length += 2;
		}
		else
		{
			length = (length << 8) + USARTx->msgRxdHandler.pMsgVal[1];
			length += 3;
		}
		//---У�������Ƿ�Ϸ�
		if (length == dataLength)
		{
			USARTx->msgRxdHandler.msgTaskState = USART_OK;
		}
		else
		{
			//---���ݲ����Ϲ���ʹ�����½���
			USART_Read_Init(USARTx);
			//---���ش�����Ϣ
			_return = ERROR_2;
		}
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������ж�DMA�������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void USART_Read_DMA_IRQTask(USART_HandlerType* USARTx)
{
	//---DMA����ģʽ
	USART_DMA_IDLETask(USARTx);
	//---��������жϱ�־λ
	LL_USART_ClearFlag_IDLE(USARTx->msgUSART);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������ж�DMA�������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void USART_Write_DMA_IRQTask(USART_HandlerType* USARTx)
{
#ifdef USE_MCU_STM32F1
	//---��ʹ��DMA
	LL_DMA_DisableChannel(USARTx->msgTxHandler.msgDMA, USARTx->msgTxHandler.msgDMAChannelOrStream;
	LL_DMA_ClearFlag_GI1(DMA1);
#else
	//---��ʹ��DMA
	LL_DMA_DisableStream(USARTx->msgTxdHandler.msgDMA, USARTx->msgTxdHandler.msgDMAChannelOrStream);
#endif
	//---�����ʶ
	LL_DMA_ClearFlag(USARTx->msgTxdHandler.msgDMA, USARTx->msgTxdHandler.msgDMAChannelOrStream);
	//---���㷢��
	//USART_Write_Init(USARTx);
	//---ʹ�ܷ�������жϣ������л�TXD�˿�Ϊ����״̬
	LL_USART_EnableIT_TC(USARTx->msgUSART);
}

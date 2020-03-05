#include "uart_task.h"

//===ȫ�ֱ����Ķ���
UINT8_T UART1_RX_BUFFER[UART1_RX_MAX_SIZE] = { 0 };
UINT8_T UART1_TX_BUFFER[UART1_RX_MAX_SIZE] = { 0 };

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UARTTask_ConfigInit(UART_HandleType* UARTx, UART_HandleType* UARTInitx)
{
	return UARTLib_ConfigInit(UARTx, UARTInitx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UARTTask_Init(UART_HandleType*  UARTx, UINT16_T rxSize, UINT8_T* pRxVal, UINT8_T rxCRCFlag, UINT16_T txSize, UINT8_T* pTxVal, UINT8_T txCRCFlag, UINT32_T(*pTimerTick)(void))
{
	UINT8_T _return = OK_0;
	//_return = UARTLib_ParamInit(UARTx, UART1_DEVICE_ID, UART1_ID_INDEX, UART1_CMD_INDEX, UART1_DATA1_INDEX, UART1_DATA2_INDEX);
	_return = UARTLib_Init(UARTx, rxSize, pRxVal, rxCRCFlag, txSize, pTxVal, txCRCFlag, pTimerTick);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UARTTask_DeInit(UART_HandleType*  UARTx)
{
	return UARTLib_DeInit(UARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UARTTask_ParamInit(UART_HandleType *UARTx, UINT8_T id, UINT8_T idIndex, UINT8_T cmdIndex, UINT8_T d1Index, UINT8_T d2Index)
{
	return UARTLib_ParamInit(UARTx, id, idIndex, cmdIndex, d1Index, d2Index);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UARTTask_Read_Init(UART_HandleType*  UARTx)
{
	return UARTLib_Read_Init(UARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UARTTask_GetState(UART_HandleDef* UARTDefx)
{
	return UARTLib_GetState(UARTDefx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UARTTask_ClearState(UART_HandleDef* UARTDefx)
{
	return UARTLib_ClearState(UARTDefx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UARTTask_TimeTask_OverFlow(UART_HandleType*UARTx,UINT8_T isRx)
{
	return  UARTLib_TimeTask_OverFlow(UARTx, isRx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UARTTask_ITRead_8BitsTask(UART_HandleType*UARTx, UINT8_T val)
{
	return UARTLib_ITRead_8BitsTask(UARTx, val);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UARTTask_ITRead_16BitsTask(UART_HandleType*UARTx, UINT8_T val)
{
	return UARTLib_ITRead_16BitsTask(UARTx, val);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UARTTask_ITRead_Task(UART_HandleType*UARTx, UINT8_T val)
{
	return UARTLib_ITRead_Task(UARTx, val);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UARTTask_Write_Init(UART_HandleType*UARTx)
{
	return UARTLib_Write_Init(UARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UARTTask_ITWrite_TXETask(UART_HandleType*UARTx)
{
	return UARTLib_ITWrite_TXETask(UARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UARTTask_ITWrite_TCTask(UART_HandleType*UARTx)
{
	return UARTLib_ITWrite_TCTask(UARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UARTTask_RealTime_AddByte(UART_HandleType*UARTx, UINT8_T val)
{
	return UARTLib_RealTime_AddByte(UARTx, val);
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UARTTask_RealTime_AddDataSize(UART_HandleType*UARTx, UINT16_T val)
{
	return UARTLib_RealTime_AddDataSize(UARTx, val);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UARTTask_RealTime_AddCRC(UART_HandleType*UARTx)
{
	return UARTLib_RealTime_AddCRC(UARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T	 UARTTask_FillMode_Init( UART_HandleType*UARTx, UINT8_T isChildCmd)
{
	return UARTLib_FillMode_Init(UARTx,isChildCmd);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UARTTask_FillMode_AddByte(UART_HandleType*UARTx, UINT8_T val)
{
	return  UARTLib_FillMode_AddByte(UARTx, val);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UARTTask_FillMode_AddData(UART_HandleType*UARTx, UINT8_T *pVal, UINT16_T length)
{
	return  UARTLib_FillMode_AddData(UARTx, pVal, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T	 UARTTask_FillMode_SetResultFlag(UART_HandleType* UARTx, UINT8_T val)
{
	return UARTLib_FillMode_SetResultFlag(UARTx, val);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UARTTask_FillMode_AddIndexW(UART_HandleType* UARTx, UINT16_T val)
{
	return UARTLib_FillMode_AddIndexW(UARTx, val);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UARTTask_Read_CRCTask(UART_HandleType*UARTx)
{
	return UARTLib_Read_CRCTask(UARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UARTTask_FillMode_WriteCRCTask(UART_HandleType*UARTx)
{
	return UARTLib_FillMode_WriteCRCTask(UARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��ֽ�ģʽ����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UARTTask_FillMode_WriteByteSTART(UART_HandleType*UARTx, UINT8_T isNeedID)
{
	return UARTLib_FillMode_WriteByteSTART(UARTx, isNeedID);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����ģʽ��������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UARTTask_FillMode_WriteArraySTART(UART_HandleType* UARTx, UINT8_T* pArrayVal, UINT16_T length)
{
	return UARTLib_FillMode_WriteArraySTART(UARTx, pArrayVal, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ģʽ��������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UARTTask_FillMode_WriteSTART(UART_HandleType* UARTx, UINT16_T length)
{
	return UARTLib_FillMode_WriteSTART(UARTx, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UARTTask_PollMode_WriteByte(UART_HandleType*UARTx, UINT8_T  val)
{
	return UARTLib_PollMode_WriteByte(UARTx, val);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UARTTask_PollMode_WriteData(UART_HandleType*UARTx, char *pVal)
{
	return  UARTLib_PollMode_WriteData(UARTx, pVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void UARTTask_PrintfClockFreq(UART_HandleType*UARTx)
{
	UARTLib_PrintfClockFreq(UARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void UARTTask_PrintfLog(UART_HandleType* UARTx, char* fmt, va_list args)
{
	UARTLib_PrintfLog(UARTx, fmt, args);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void UARTTask_Printf(UART_HandleType* UARTx, char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	UARTTask_PrintfLog(UARTx, fmt, args);
	va_end(args);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UARTTask_IT_TCTask(UART_HandleType* UARTx)
{
	return UARTLib_IT_TCTask(UARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�У�鷢��״̬����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T	 UARTTask_Write_CheckIdle(UART_HandleType* UARTx)
{
	return UARTLib_Write_CheckIdle(UARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� У���豸��ID��Ϣ
//////////////////////////////////////////////////////////////////////////////
UINT8_T UARTTask_DeviceID(UART_HandleType*UARTx)
{
	return UARTLib_DeviceID(UARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��жϴ�������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void UARTTask_IRQTask(UART_HandleType* UARTx)
{
	UARTLib_IRQTask(UARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void UARTTask_DMA_Read_IRQTask(UART_HandleType* UARTx)
{
	UARTLib_DMA_Read_IRQTask(UARTx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void UARTTask_DMA_Write_IRQTask(UART_HandleType* UARTx)
{
	UARTLib_DMA_Write_IRQTask(UARTx);
}

UINT16_T UARTDebugCount=0;

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UARTTask_FuncTask(UART_HandleType*UARTx, UINT8_T(*pFuncTask)(UINT8_T *, UINT8_T *))
{
	UINT16_T length = 0;
	if (UARTx != NULL)
	{
		//---�жϽ����Ƿ����
		if (UARTTask_GetState(&(UARTx->msgRxdHandle)) == 1)
		{
			//---CRC��У��
			if ((UARTTask_Read_CRCTask(UARTx) == OK_0) && (UARTTask_DeviceID(UARTx) == OK_0))
			{
				//---���ݽ������
				if (pFuncTask != NULL)
				{
					pFuncTask(UARTx->msgRxdHandle.pMsgVal, UARTx->msgTxdHandle.pMsgVal);
				}
				else
				{
					UARTTask_FillMode_AddData(UARTx, UARTx->msgRxdHandle.pMsgVal, UARTx->msgRxdHandle.msgCount);
					//---�������ݷ���
					UARTTask_FillMode_WriteByteSTART(UARTx, 0);
					UARTDebugCount++;
					UARTTask_Printf(pUart1, "TEST Count:%d\r\n", UARTDebugCount);
				}
			}
			else
			{
				//---����CRCУ�����
				UARTTask_Printf(UARTx, (void*)"=>>SP%d:CRC Check Error<<=\r\n", (UARTx->msgIndex - 1));
			}
			return UARTTask_Read_Init(UARTx);
		}
		return UARTTask_TimeTask_OverFlow(UARTx,1);
	}
	return ERROR_2;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UARTTask_DebugPollFuncTask(UART_HandleType*UARTx, UINT8_T(*pFuncTask)(UINT8_T *, UINT8_T *))
{
	//UINT16_T length = 0;
	UINT32_T freqVal = 0;
	if (UARTx != NULL)
	{
		//---�жϽ����Ƿ����
		if (UARTTask_GetState(&(UARTx->msgRxdHandle)) == UART_OK)
		{
			//---CRC��У��
			if ((UARTTask_Read_CRCTask(UARTx) == OK_0) && (UARTTask_DeviceID(UARTx) == OK_0))
			{
				if (UARTx->msgRxdHandle.pMsgVal[UART1_CMD_INDEX]==0xA4)
				{
					//---��ȡʱ��Ƶ��
					TimerTask_CalcFreq_Task(0);
					//---����Ƶ��
					freqVal = (UINT32_T)(pCalcFreq->msgFreqKHz[pCalcFreq->msgChannel] * 100);
				}

				UARTTask_FillMode_Init(UARTx,0);
				//UARTTask_FillMode_AddByte(UARTx, 0xA4);
				UARTTask_FillMode_AddByte(UARTx, 0x00);
				UARTTask_FillMode_AddByte(UARTx, (UINT8_T)(freqVal >> 24));
				UARTTask_FillMode_AddByte(UARTx, (UINT8_T)(freqVal >> 16));
				UARTTask_FillMode_AddByte(UARTx, (UINT8_T)(freqVal >> 8));
				UARTTask_FillMode_AddByte(UARTx, (UINT8_T)(freqVal ));

				UARTTask_FillMode_WriteByteSTART(UARTx, 0);
			}
			else
			{
				//---����CRCУ�����
				UARTTask_Printf(UARTx, "=>>SP%d:CRC Check Error<<=\r\n", (UARTx->msgIndex - 1));
			}
			return UARTTask_Read_Init(UARTx);
		}
		return UARTTask_TimeTask_OverFlow(UARTx,1);
	}
	return ERROR_2;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�Ƶ�ʲ��Ժ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UARTTask_DebugFreqTask(UART_HandleType* UARTx, UINT8_T(*pFuncTask)(UINT8_T*, UINT8_T*))
{
	//UINT16_T length = 0;
	UINT32_T freqVal = 0;
	UINT8_T _return=0;
	if (UARTx != NULL)
	{
		//---�жϽ����Ƿ����
		if (UARTTask_GetState(&(UARTx->msgRxdHandle)) == 1)
		{
			//---CRC��У��
			if ((UARTTask_Read_CRCTask(UARTx) == OK_0) && (UARTTask_DeviceID(UARTx) == OK_0))
			{
				if (UARTx->msgRxdHandle.pMsgVal[UART1_CMD_INDEX] == 0xA4)
				{
					//---�Ƿ������ϵ�
					if (UARTx->msgRxdHandle.pMsgVal[UART1_CMD_INDEX + 1] != 0)
					{
						LM317_POWER_OFF;
						freqVal= UARTx->msgRxdHandle.pMsgVal[UART1_CMD_INDEX + 2];
						freqVal = (freqVal<<8)+UARTx->msgRxdHandle.pMsgVal[UART1_CMD_INDEX + 3];
						//---��ʼ��LM317���Ŀɵ���Դ
						LM317Task_Init(0, freqVal);
						LM317_POWER_ON;
					}
					#ifdef STM32_USE_F407VET6
						//---���������ź�
						GPIO_OUT_0(TRIG_PULSE_PORT, TRIG_PULSE_BIT);
						DelayTask_us(500);
						GPIO_OUT_1(TRIG_PULSE_PORT, TRIG_PULSE_BIT);
						DelayTask_us(500);
						//---��ʱ100ms����ȡƵ��ֵ
						DelayTask_ms(100);
						//---��ȡУ׼��
						_return=DataBus_Read();
					#endif
					//---��ȡʱ��Ƶ��
					TimerTask_CalcFreq_Task(0);
					//---����Ƶ��
					freqVal = (UINT32_T)(pCalcFreq->msgFreqKHz[pCalcFreq->msgChannel] * 100);
				}
				//UARTTask_FillMode_AddByte(UARTx, 0xA4);
				UARTTask_FillMode_Init(UARTx, 0);
				UARTTask_FillMode_AddByte(UARTx, 0x00);
				//---��ȡУ׼��
				UARTTask_FillMode_AddByte(UARTx, _return);
				UARTTask_FillMode_AddByte(UARTx, (UINT8_T)(freqVal >> 24));
				UARTTask_FillMode_AddByte(UARTx, (UINT8_T)(freqVal >> 16));
				UARTTask_FillMode_AddByte(UARTx, (UINT8_T)(freqVal >> 8));
				UARTTask_FillMode_AddByte(UARTx, (UINT8_T)(freqVal));
				//---�������ݷ���
				UARTTask_FillMode_WriteByteSTART(UARTx, 0);
			}
			else
			{
				//---����CRCУ�����
				UARTTask_Printf(UARTx, "=>>SP%d:CRC Check Error<<=\r\n", (UARTx->msgIndex - 1));
			}
			return UARTTask_Read_Init(UARTx);
		}
		return UARTTask_TimeTask_OverFlow(UARTx,1);
	}
	return ERROR_2;
}
#include "jtag_task.h"

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_Init(JTAG_HandlerType* JTAGx, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void))
{
	return JTAGLib_Init(JTAGx, pFuncDelayus, pFuncDelayms, pFuncTimerTick);
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ù̶����ʱ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_SetProgClock(JTAG_HandlerType* JTAGx, UINT8_T clok)
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
UINT8_T JTAGTask_ExitProg(JTAG_HandlerType* JTAGx)
{
	return JTAGLib_ExitProg(JTAGx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_EnterProg(JTAG_HandlerType* JTAGx)
{
	return JTAGLib_EnterProg(JTAGx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_EnterProgAndConfigInfo(JTAG_HandlerType* JTAGx, UINT8_T isPollReady, UINT8_T* pVal)
{
	return JTAGLib_EnterProgAndConfigInfo(JTAGx, isPollReady, pVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_EraseChip(JTAG_HandlerType* JTAGx)
{
	return JTAGLib_EraseChip(JTAGx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_ReadIDChip(JTAG_HandlerType* JTAGx, UINT8_T* pVal)
{
	return JTAGLib_ReadIDChip(JTAGx, pVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_ReadChipID(JTAG_HandlerType* JTAGx, UINT8_T* pVal)
{
	return JTAGLib_ReadChipID(JTAGx, pVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_ReadChip(JTAG_HandlerType* JTAGx, UINT8_T* pVal)
{
	return JTAGLib_ReadChip(JTAGx, pVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_ReadChipCalibration(JTAG_HandlerType* JTAGx, UINT8_T* pVal, UINT8_T length)
{
	return JTAGLib_ReadChipCalibration(JTAGx, pVal, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_ReadChipFuse(JTAG_HandlerType* JTAGx, UINT8_T* pVal, UINT8_T isNeedExternFuse)
{
	return JTAGLib_ReadChipFuse(JTAGx, pVal, isNeedExternFuse);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_ReadChipLock(JTAG_HandlerType* JTAGx, UINT8_T* pVal)
{
	return JTAGLib_ReadChipLock(JTAGx, pVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_ReadChipRom(JTAG_HandlerType* JTAGx, UINT8_T* pVal, UINT8_T addr, UINT16_T length)
{
	return JTAGLib_ReadChipRom(JTAGx, pVal, addr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_WriteChipFuse(JTAG_HandlerType* JTAGx, UINT8_T* pVal, UINT8_T isNeedExternFuse)
{
	return JTAGLib_WriteChipFuse(JTAGx, pVal, isNeedExternFuse);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_WriteChipLock(JTAG_HandlerType* JTAGx, UINT8_T lockVal)
{
	return JTAGLib_WriteChipLock(JTAGx, lockVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_ReadChipEepromAddr(JTAG_HandlerType* JTAGx, UINT8_T* pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	return JTAGLib_ReadChipEepromAddr(JTAGx, pVal, highAddr, lowAddr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_ReadChipEepromLongAddr(JTAG_HandlerType* JTAGx, UINT8_T* pVal, UINT16_T addr, UINT16_T length)
{
	return JTAGLib_ReadChipEepromLongAddr(JTAGx, pVal, addr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_WriteChipEeprom(JTAG_HandlerType* JTAGx, UINT8_T* pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T pageNum)
{
	return JTAGLib_WriteChipEeprom(JTAGx, pVal, highAddr, lowAddr, pageNum);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_ReadChipFlashAddr(JTAG_HandlerType* JTAGx, UINT8_T* pVal, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	return JTAGLib_ReadChipFlashAddr(JTAGx, pVal, externAddr, highAddr, lowAddr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_ReadChipFlashLongAddr(JTAG_HandlerType* JTAGx, UINT8_T* pVal, UINT32_T addr, UINT16_T length)
{
	return JTAGLib_ReadChipFlashLongAddr(JTAGx, pVal, addr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_WriteChipFlashPage(JTAG_HandlerType* JTAGx, UINT8_T* pVal, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	return JTAGLib_WriteChipFlashPage(JTAGx, pVal, externAddr, highAddr, lowAddr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_CheckChipFlashEmpty(JTAG_HandlerType* JTAGx, UINT8_T pageByteSizeH, UINT8_T pageByteSizeL, UINT8_T pageNumH, UINT8_T pageNumL)
{
	return JTAGLib_CheckChipFlashEmpty(JTAGx, pageByteSizeH, pageByteSizeL, pageNumH, pageNumL);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_CheckChipFlashEmptyLong(JTAG_HandlerType* JTAGx, UINT16_T pageByteSize, UINT16_T pageNum)
{
	return JTAGLib_CheckChipFlashEmptyLong(JTAGx, pageByteSize, pageNum);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_CheckChipEepromEmpty(JTAG_HandlerType* JTAGx, UINT8_T byteSize, UINT8_T num)
{
	return JTAGLib_CheckChipEepromEmpty(JTAGx, byteSize, num);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_SetConfigInfo(JTAG_HandlerType* JTAGx, UINT8_T* pVal)
{
	return JTAGLib_SetConfigInfo(JTAGx, pVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_ReadChipPower(JTAG_HandlerType* JTAGx, UINT8_T* pVal)
{
	//---��ȡоƬ�Ĺ����ѹ
	UINT16_T tempPower = ADCTask_GetChipPower();
	//---��ȡ��ѹֵ
	//---�������
	*(pVal++) = (UINT8_T)(tempPower >> 8);
	*pVal = (UINT8_T)(tempPower);
	return  OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_WriteChipPower(JTAG_HandlerType* JTAGx, UINT8_T* pVal)
{
	UINT16_T tempPower = *(pVal++);
	tempPower = (tempPower << 8) + *(pVal++);
	//---ͨ��DAC���ÿɵ���ԴLM317�����ֵ
	LM317Task_Init(0, tempPower);
	//---У���Դ�Ƿ���
	if (*pVal > 0)
	{
		LM317_POWER_ON;
	}
	else
	{
		LM317_POWER_HZ;
	}
	return  OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��˳����߽�����ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_USARTCmd_OpenAndClose(JTAG_HandlerType* JTAGx, USART_HandlerType* USARTx)
{
	UINT8_T	_return = 0;
	//---����λ��
	if (USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset] == 1)
	{
		//---������ģʽ�������û�������
		_return = JTAGTask_EnterProgAndConfigInfo(JTAGx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + USARTx->msgIndexOffset], USARTx->msgRxdHandler.pMsgVal + USARTx->msgDataTwoIndex + USARTx->msgIndexOffset + 1);
	}
	else if (USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset] == 2)
	{
		//---���û�������,��Ҫ��ʹ��ʹ��EEPROM��ҳ���ģʽ
		_return = JTAGTask_SetConfigInfo(JTAGx, USARTx->msgRxdHandler.pMsgVal + USARTx->msgDataTwoIndex + USARTx->msgIndexOffset + 1);
	}
	else
	{
		_return = JTAGTask_ExitProg(JTAGx);
	}
	//---ִ�н��
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����Chip
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_USARTCmd_EraseChip(JTAG_HandlerType* JTAGx, USART_HandlerType* USARTx)
{
	UINT8_T _return = OK_0;
	if (USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset] == 0)
	{
		//---�豸����
		_return = JTAGTask_EraseChip(JTAGx);
	}
	else if (USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset] == 1)
	{
		//---���FlashΪ��
		_return = JTAGTask_CheckChipFlashEmpty(JTAGx,
			USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset + 1], USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset + 2],
			USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset + 3], USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset + 4]
		);
	}
	else if (USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset] == 2)
	{
		//---���EepromΪ��
		_return = JTAGTask_CheckChipEepromEmpty(JTAGx,
			USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset + 1], USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset + 2]
		);
	}
	else
	{
		_return = 0xFF;
	}
	//---�����ǲ��ǲ�ղ���
	if (USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset] != 0)
	{
		//---����ղ�����ֵ
		USARTTask_FillMode_AddByte(USARTx, _return);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡоƬID
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_USARTCmd_ReadChipID(JTAG_HandlerType* JTAGx, USART_HandlerType* USARTx)
{
	UINT8_T	_return = 0;
	//---��ȡ�豸ID��Ϣ
	_return = JTAGTask_ReadChipID(JTAGx, USARTx->msgTxdHandler.pMsgVal + USARTx->msgTxdHandler.msgIndexW);
	//---���ݳ���ƫ��
	USARTx->msgTxdHandler.msgIndexW += 3;
	//---ִ�н��
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡоƬ��У׼��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_USARTCmd_ReadChipCalibration(JTAG_HandlerType* JTAGx, USART_HandlerType* USARTx)
{
	UINT8_T	_return = 0;
	//---��ȡ�豸��У׼��
	_return = JTAGTask_ReadChipCalibration(JTAGx, USARTx->msgTxdHandler.pMsgVal + USARTx->msgTxdHandler.msgIndexW, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset]);
	//---���ݵ�ַƫ��
	USARTx->msgTxdHandler.msgIndexW += USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset];
	//---ִ�н��
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡоƬ����˿λ��У׼��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_USARTCmd_ReadChipFuseAndLock(JTAG_HandlerType* JTAGx, USART_HandlerType* USARTx)
{
	UINT8_T	_return = 0;
	//---�ж��Ƕ�ȡ��˿λ���Ǽ���λ
	if (USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset] == 0)
	{
		//---��ȡ��˿λ
		_return = JTAGTask_ReadChipFuse(JTAGx, USARTx->msgTxdHandler.pMsgVal + USARTx->msgTxdHandler.msgIndexW, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + USARTx->msgIndexOffset]);
		//---У���Ƿ��ȡ��չ��˿λ
		if (USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + USARTx->msgIndexOffset] != 0)
		{
			USARTx->msgTxdHandler.msgIndexW += 1;
		}
		USARTx->msgTxdHandler.msgIndexW += 2;
	}
	else
	{
		//---��ȡ����λ
		_return = JTAGTask_ReadChipLock(JTAGx, USARTx->msgTxdHandler.pMsgVal + USARTx->msgTxdHandler.msgIndexW);
		USARTx->msgTxdHandler.msgIndexW += 1;
	}
	//---ִ�н��
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������˿λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_USARTCmd_WriteChipFuse(JTAG_HandlerType* JTAGx, USART_HandlerType* USARTx)
{
	return JTAGTask_WriteChipFuse(JTAGx, USARTx->msgRxdHandler.pMsgVal + USARTx->msgDataTwoIndex + USARTx->msgIndexOffset, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset]);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���̼���λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_USARTCmd_WriteChipLock(JTAG_HandlerType* JTAGx, USART_HandlerType* USARTx)
{
	return JTAGTask_WriteChipLock(JTAGx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset]);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡоƬ��ROM��Ϣ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_USARTCmd_ReadChipRom(JTAG_HandlerType* JTAGx, USART_HandlerType* USARTx)
{
	UINT8_T	_return = 0;
	UINT16_T length = 0;
	//---�����ȡ���ݵĴ�С
	if (USARTx->msgRxdHandler.msgSize < 0xFF)
	{
		length = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + USARTx->msgIndexOffset];
	}
	else
	{
		length = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + USARTx->msgIndexOffset];
		length = (length << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + USARTx->msgIndexOffset + 1];
	}
	//---��ȡROMҳ��Ϣ
	_return = JTAGTask_ReadChipRom(JTAGx, USARTx->msgTxdHandler.pMsgVal + USARTx->msgTxdHandler.msgIndexW, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset], length);
	//---���ݵ�ƫ��
	USARTx->msgTxdHandler.msgIndexW += length;
	//---ִ�н��
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ñ��ʱ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_USARTCmd_SetProgClok(JTAG_HandlerType* JTAGx, USART_HandlerType* USARTx)
{
	UINT8_T _return = OK_0;
	//---��ȡ��ѹ
	if (USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset] == 1)
	{
		_return = JTAGTask_ReadChipPower(JTAGx, USARTx->msgTxdHandler.pMsgVal + USARTx->msgDataOneIndex + USARTx->msgIndexOffset + 1);
		USARTx->msgTxdHandler.msgIndexW += 2;
	}
	//---���õ�ѹ
	else if (USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset] == 2)
	{
		_return = JTAGTask_WriteChipPower(JTAGx, USARTx->msgRxdHandler.pMsgVal + USARTx->msgDataOneIndex + USARTx->msgIndexOffset + 1);
	}
	else
	{
		//---���ñ��ʱ��
		_return = JTAGTask_SetProgClock(JTAGx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset + 1]);
	}

	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ͨ�����������ȡFlash����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_USARTCmd_ReadChipFlash(JTAG_HandlerType* JTAGx, USART_HandlerType* USARTx)
{
	UINT8_T	_return = 0;
	UINT16_T length = 0;
	//---�����ȡ���ݵĴ�С
	if (USARTx->msgRxdHandler.msgSize < 0xFF)
	{
		length = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + USARTx->msgIndexOffset + 2];
	}
	else
	{
		length = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + USARTx->msgIndexOffset + 2];
		length = (length << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + USARTx->msgIndexOffset + 3];
	}
	//---��ȡָ��λ�õ�Flash����
	_return = JTAGTask_ReadChipFlashAddr(JTAGx, USARTx->msgTxdHandler.pMsgVal + USARTx->msgTxdHandler.msgIndexW,
		USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset],
		USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + USARTx->msgIndexOffset],
		USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + USARTx->msgIndexOffset + 1],
		length);
	//---���ݵ�ƫ��
	USARTx->msgTxdHandler.msgIndexW += length;
	//---ִ�н��
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ͨ������������Flash����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_USARTCmd_WriteChipFlashPage(JTAG_HandlerType* JTAGx, USART_HandlerType* USARTx)
{
	UINT8_T dataOffset = 0;
	UINT16_T length = 0;
	//---����д�����ݵĴ�С
	if (USARTx->msgRxdHandler.msgSize < 0xFF)
	{
		length = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + USARTx->msgIndexOffset + 2];
		dataOffset = 3;
	}
	else
	{
		length = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + USARTx->msgIndexOffset + 2];
		length = (length << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + USARTx->msgIndexOffset + 3];
		dataOffset = 4;
	}
	//---��ָ��λ�ñ������
	return JTAGTask_WriteChipFlashPage(JTAGx, USARTx->msgRxdHandler.pMsgVal + USARTx->msgDataTwoIndex + USARTx->msgIndexOffset + dataOffset,
		USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset],
		USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + USARTx->msgIndexOffset],
		USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + USARTx->msgIndexOffset + 1],
		length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ͨ�����������ȡeeprom����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_USARTCmd_ReadChipEeprom(JTAG_HandlerType* JTAGx, USART_HandlerType* USARTx)
{
	UINT8_T	_return = 0;
	UINT16_T length = 0;
	//---�����ȡ���ݵĴ�С
	if (USARTx->msgRxdHandler.msgSize < 0xFF)
	{
		length = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + USARTx->msgIndexOffset + 1];
	}
	else
	{
		length = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + USARTx->msgIndexOffset + 1];
		length = (length << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + USARTx->msgIndexOffset + 2];
	}
	//---��ȡָ��λ�õ�Eeprom����
	_return = JTAGTask_ReadChipEepromAddr(JTAGx, USARTx->msgTxdHandler.pMsgVal + USARTx->msgTxdHandler.msgIndexW,
		USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset],
		USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + USARTx->msgIndexOffset],
		length);
	//---���ݵ�ƫ��
	USARTx->msgTxdHandler.msgIndexW += length;
	//---ִ�н��
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ͨ������������eeprom����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_USARTCmd_WriteChipEeprom(JTAG_HandlerType* JTAGx, USART_HandlerType* USARTx)
{
	UINT8_T dataOffset = 0;
	UINT16_T length = 0;
	//---�����ȡ���ݵĴ�С
	if (USARTx->msgRxdHandler.msgSize < 0xFF)
	{
		length = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + USARTx->msgIndexOffset + 1];
		dataOffset = 2;
	}
	else
	{
		length = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + USARTx->msgIndexOffset + 1];
		length = (length << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + USARTx->msgIndexOffset + 2];
		dataOffset = 3;
	}
	//---���ָ��λ�õ�Eeprom����
	return JTAGTask_WriteChipEeprom(JTAGx, USARTx->msgRxdHandler.pMsgVal + USARTx->msgDataTwoIndex + USARTx->msgIndexOffset + dataOffset,
		USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset],
		USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + USARTx->msgIndexOffset],
		length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_USARTCmd_ChildTask(JTAG_HandlerType* JTAGx, USART_HandlerType* USARTx, UINT8_T isChildCmd)
{
	UINT8_T _return = 0;
	//---������ִ�н��
	USARTTask_FillMode_AddByte(USARTx, 0x00);
	USARTx->msgIndexOffset = (isChildCmd == 0 ? 0 : 1);
	//---���������������
	switch (USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex + USARTx->msgIndexOffset])
	{
		case CMD_JTAG_OPEN_CLOSE:
			//---����֮�󣬵�1�ֽ�0---����رգ�1---����򿪣���2�ֽ�����йأ���ر��޹�
			_return = JTAGTask_USARTCmd_OpenAndClose(JTAGx, USARTx);
			break;
		case CMD_JTAG_ERASE:
			//---�����豸����1�ֽ�0---���������1---������Flash��2---������Eeprom
			_return = JTAGTask_USARTCmd_EraseChip(JTAGx, USARTx);
			break;
		case CMD_JTAG_FLASH_PAGE_READ:
			//---��ȡFlash
			_return = JTAGTask_USARTCmd_ReadChipFlash(JTAGx, USARTx);
			break;
		case CMD_JTAG_FLASH_PAGE_WRITE:
			//---���Flash
			_return = JTAGTask_USARTCmd_WriteChipFlashPage(JTAGx, USARTx);
			break;
		case CMD_JTAG_EEPROM_PAGE_READ:
			//---��ȡEeprom
			_return = JTAGTask_USARTCmd_ReadChipEeprom(JTAGx, USARTx);
			break;
		case CMD_JTAG_EEPROM_PAGE_WRITE:
			//---���Eeprom
			_return = JTAGTask_USARTCmd_WriteChipEeprom(JTAGx, USARTx);
			break;
		case CMD_JTAG_FUSE_LOCK_READ:
			//---��ȡ��˿λ����У��λ
			_return = JTAGTask_USARTCmd_ReadChipFuseAndLock(JTAGx, USARTx);
			break;
		case CMD_JTAG_FUSE_WRITE:
			//---�����˿λ
			_return = JTAGTask_USARTCmd_WriteChipFuse(JTAGx, USARTx);
			break;
		case CMD_JTAG_LOCK_WRITE:
			//---��̼���λ
			_return = JTAGTask_USARTCmd_WriteChipLock(JTAGx, USARTx);
			break;
		case CMD_JTAG_ID_READ:
			//---��ȡ�豸��ID
			_return = JTAGTask_USARTCmd_ReadChipID(JTAGx, USARTx);
			break;
		case CMD_JTAG_CALIBRATIONBYTE_READ:
			//---��ȡУ׼��
			_return = JTAGTask_USARTCmd_ReadChipCalibration(JTAGx, USARTx);
			break;
		case CMD_JTAG_ROM_PAGE_READ:
			//---��ȡROMҳ��Ϣ
			_return = JTAGTask_USARTCmd_ReadChipRom(JTAGx, USARTx);
			break;
		case CMD_JTAG_PROG_CLOCK_SET:
			//---���ñ��ʱ�ӣ��༶������������Ҫ�е�Դ�����úͶ�ȡ
			_return = JTAGTask_USARTCmd_SetProgClok(JTAGx, USARTx);
			break;
		default:
			//---��ʶ�������
			_return = ERROR_1;
			break;
	}
	//---�����Խ��
	USARTTask_FillMode_SetResultFlag(USARTx, _return);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_USARTCmd_ParentTask(JTAG_HandlerType* JTAGx, USART_HandlerType* USARTx, UINT8_T isChildCmd)
{
	if ((USARTx != NULL) && (JTAGx != NULL))
	{
		//---�жϽ����Ƿ����
		if (USARTTask_GetReadState(USARTx) == 1)
		{
			//---CRC��У����豸IDУ��
			if ((USARTTask_CRCTask_Read(USARTx) == OK_0) && (USARTTask_DeviceID(USARTx) == OK_0))
			{
				//---����������������ݱ�ͷ�����ȣ���ַID,����Ĵ���
				USARTTask_FillMode_Init(USARTx, isChildCmd);
				//---��������
				JTAGTask_USARTCmd_ChildTask(JTAGx, USARTx, isChildCmd);
				//---�Ƿ���Ҫ���ӻ��з�
				if (USARTx->msgTxdHandler.msgAddNewLine == 1)
				{
					USARTTask_FillMode_AddByte(USARTx, 0x0D);
					USARTTask_FillMode_AddByte(USARTx, 0x0A);
				}
				//---�������ݷ���
				USARTTask_FillMode_WriteSTART(USARTx, 0);
			}
			else
			{
				//---����CRCУ�����
				USART_Printf(USARTx, "=>>����%d:����CRCУ�����<<=\r\n", (USARTx->msgIndex - 1));
			}
			return USARTTask_Read_Init(USARTx);
		}
		return USARTTask_TimeOVFTask(USARTx);
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
UINT8_T JTAGTask_USARTCmd_ParentTask_New(JTAG_HandlerType* JTAGx, USART_HandlerType* USARTx, UINT8_T isChildCmd)
{
	UINT8_T _return = OK_0;
	//---����������������ݱ�ͷ�����ȣ���ַID,����Ĵ���
	USARTTask_FillMode_Init(USARTx, isChildCmd);
	//---��������
	_return = JTAGTask_USARTCmd_ChildTask(JTAGx, USARTx, isChildCmd);
	//---�Ƿ���Ҫ���ӻ��з�
	if (USARTx->msgTxdHandler.msgAddNewLine == 1)
	{
		USARTTask_FillMode_AddByte(USARTx, 0x0D);
		USARTTask_FillMode_AddByte(USARTx, 0x0A);
	}
	//---�������ݷ���
	USARTTask_FillMode_WriteSTART(USARTx, 0);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGTask_USARTCmd_Task(JTAG_HandlerType* JTAGx, USART_HandlerType* USARTx)
{
	UINT8_T _return = OK_0;
	//_return = JTAGTask_USARTCmd_ParentTask(JTAGx, USARTx, 0);
	_return = JTAGTask_USARTCmd_ParentTask_New(JTAGx, USARTx, 0);
	return _return;
}
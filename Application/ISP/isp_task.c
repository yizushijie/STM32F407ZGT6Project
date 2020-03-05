#include "isp_task.h"

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_Init(ISP_HandleType *ISPx, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void))
{
	return ISPLib_Init(ISPx, pFuncDelayus, pFuncDelayms, pFuncTimerTick);
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ע����ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_DeInit(ISP_HandleType *ISPx)
{
	return ISPLib_DeInit(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ù̶����ʱ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_SetProgClock(ISP_HandleType* ISPx, UINT8_T clok)
{
	return ISPLib_SetProgClock(ISPx,clok);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_EnterProg(ISP_HandleType *ISPx, UINT8_T isPollReady)
{
	return ISPLib_EnterProg(ISPx,isPollReady);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_EnterProgAndConfigInfo(ISP_HandleType* ISPx, UINT8_T isPollReady,UINT8_T *pVal)
{
	return ISPLib_EnterProgAndConfigInfo(ISPx, isPollReady, pVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��˳����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ExitProg(ISP_HandleType *ISPx)
{
	return ISPLib_ExitProg(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���Ӽ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_AddWatch(ISP_HandleType* ISPx)
{
	return ISPLib_AddWatch(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ע�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_RemoveWatch(ISP_HandleType* ISPx)
{
	return ISPLib_RemoveWatch(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ˢ�¼��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_RefreshWatch(ISP_HandleType* ISPx)
{
	return ISPLib_RefreshWatch(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������ѯ���ʱ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_SetIntervalTime(ISP_HandleType* ISPx, UINT16_T intervalTime)
{
	return ISPLib_SetIntervalTime(ISPx, intervalTime);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ��ѯ���ʱ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT16_T ISPTask_GetIntervalTime(ISP_HandleType* ISPx)
{
	return ISPLib_GetIntervalTime(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡReady�ź�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadReady(ISP_HandleType *ISPx)
{
	return ISPLib_ReadReady(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������豸
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_EraseChip(ISP_HandleType *ISPx)
{
	return ISPLib_EraseChip(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡChipID
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadChipID(ISP_HandleType *ISPx, UINT8_T *pVal)
{
	return ISPLib_ReadChipID(ISPx, pVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡУ׼��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadChipCalibration(ISP_HandleType *ISPx, UINT8_T *pVal, UINT8_T length)
{
	return ISPLib_ReadChipCalibration(ISPx, pVal, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ��˿λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadChipFuse(ISP_HandleType *ISPx, UINT8_T *pVal, UINT8_T isNeedExternFuse)
{
	return ISPLib_ReadChipFuse(ISPx, pVal, isNeedExternFuse);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ����λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadChipLock(ISP_HandleType *ISPx, UINT8_T *pVal)
{
	return ISPLib_ReadChipLock(ISPx, pVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡROM��Ϣ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadChipRom(ISP_HandleType *ISPx, UINT8_T *pVal, UINT8_T addr, UINT16_T length)
{
	return ISPLib_ReadChipRom(ISPx, pVal, addr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������˿λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_WriteChipFuse(ISP_HandleType *ISPx, UINT8_T *pVal, UINT8_T isNeedExternFuse)
{
	return ISPLib_WriteChipFuse(ISPx, pVal, isNeedExternFuse);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���̼���λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_WriteChipLock(ISP_HandleType *ISPx, UINT8_T val)
{
	return ISPLib_WriteChipLock(ISPx, val);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡEEPROM
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadChipEepromAddr(ISP_HandleType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	return ISPLib_ReadChipEepromAddr(ISPx, pVal, highAddr, lowAddr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡEEPROM
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadChipEepromLongAddr(ISP_HandleType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length)
{
	return ISPLib_ReadChipEepromLongAddr(ISPx, pVal, addr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����EEPROM
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_WriteChipEepromAddr(ISP_HandleType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	return ISPLib_WriteChipEepromAddr(ISPx, pVal, highAddr, lowAddr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�д���ݵ�Eeprom������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UpdateChipEepromPage(ISP_HandleType* ISPx, UINT8_T* pVal)
{
	return ISPLib_UpdateChipEepromPage( ISPx, pVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��������ݵ�Eeprom�洢��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UpdateChipEepromAddr(ISP_HandleType* ISPx, UINT8_T highAddr, UINT8_T lowAddr)
{
	return ISPLib_UpdateChipEepromAddr(ISPx,highAddr,lowAddr);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��������ݵ�Eeprom�洢��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UpdateChipEepromLongAddr(ISP_HandleType* ISPx, UINT16_T addr)
{
	return ISPLib_UpdateChipEepromLongAddr(ISPx,addr);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ҳд���ݵ�Eeprom�洢��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_WriteChipEepromPage(ISP_HandleType* ISPx, UINT8_T* pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T pageNum)
{
	return ISPLib_WriteChipEepromPage(ISPx,pVal,highAddr,lowAddr,pageNum);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_WriteChipEepromLongAddr(ISP_HandleType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length)
{
	return ISPLib_WriteChipEepromLongAddr(ISPx, pVal, addr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����EEPROM
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_WriteChipEepromAddrWithJumpEmpty(ISP_HandleType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	return ISPLib_WriteChipEepromAddrWithJumpEmpty(ISPx, pVal, highAddr, lowAddr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����EEPROM
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_WriteChipEepromLongAddrWithJumpEmpty(ISP_HandleType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length)
{
	return  ISPLib_WriteChipEepromLongAddrWithJumpEmpty(ISPx, pVal, addr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_WriteChipEeprom(ISP_HandleType* ISPx, UINT8_T* pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T pageNum)
{
	return ISP_WriteChipEeprom(ISPx, pVal,  highAddr,  lowAddr,  pageNum);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡFlash
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadChipFlashAddr(ISP_HandleType *ISPx, UINT8_T *pVal, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	return ISPLib_ReadChipFlashAddr(ISPx, pVal, externAddr, highAddr, lowAddr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡFlash
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadChipFlashLongAddr(ISP_HandleType *ISPx, UINT8_T *pVal, UINT32_T addr, UINT16_T length)
{
	return ISPLib_ReadChipFlashLongAddr(ISPx, pVal, addr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������չλ��ַ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UpdateExternAddr(ISP_HandleType* ISPx, UINT8_T addr)
{
	return ISPLib_UpdateExternAddr(ISPx, addr);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������չλ��ַ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UpdateExternLongAddr(ISP_HandleType* ISPx, UINT32_T addr)
{
	return ISPLib_UpdateExternLongAddr(ISPx, addr);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��������ݵ����ݻ�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UpdateChipFlashBuffer(ISP_HandleType *ISPx, UINT8_T *pVal, UINT8_T index, UINT16_T length)
{
	return ISPLib_UpdateChipFlashBuffer(ISPx, pVal, index, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��������ݵ�ָ�������ݵ�ַ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UpdateChipFlashAddr(ISP_HandleType *ISPx, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr)
{
	return ISPLib_UpdateChipFlashAddr(ISPx, externAddr, highAddr, lowAddr);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��������ݵ����ݵ�ָ����ַ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UpdateChipFlashLongAddr(ISP_HandleType *ISPx, UINT32_T addr)
{
	return ISPLib_UpdateChipFlashLongAddr(ISPx, addr);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ҳģʽ��ָ��������д��Flash
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_WriteChipFlashPage(ISP_HandleType* ISPx, UINT8_T* pVal, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	return ISPLib_WriteChipFlashPage(ISPx,pVal, externAddr, highAddr, lowAddr,length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_CheckChipFlashEmpty(ISP_HandleType* ISPx, UINT8_T pageByteSizeH, UINT8_T pageByteSizeL, UINT8_T pageNumH, UINT8_T pageNumL)
{
	return ISPLib_CheckChipFlashEmpty(ISPx, pageByteSizeH, pageByteSizeL, pageNumH, pageNumL);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_CheckChipFlashEmptyLong(ISP_HandleType* ISPx, UINT16_T pageByteSize, UINT16_T pageNum)
{
	return ISPLib_CheckChipFlashEmptyLong(ISPx, pageByteSize, pageNum);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_CheckChipEepromEmpty(ISP_HandleType* ISPx, UINT8_T byteSize, UINT8_T num)
{
	return ISPLib_CheckChipEepromEmpty(ISPx, byteSize, num);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_SetConfigInfo(ISP_HandleType* ISPx, UINT8_T* pVal)
{
	return ISPLib_SetConfigInfo(ISPx, pVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_ReadChipPower(ISP_HandleType* ISPx, UINT8_T* pVal)
{
	//---��ȡоƬ�Ĺ����ѹ
	UINT16_T tempPower= ADCTask_GetChipPower();
	//---��ȡ��ѹֵ
	//---�������
	*(pVal++)=(UINT8_T)(tempPower>>8);
	*pVal=(UINT8_T)(tempPower);
	return  OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_WriteChipPower(ISP_HandleType* ISPx, UINT8_T* pVal)
{
	UINT16_T tempPower = *(pVal++);
	tempPower= (tempPower<<8)+*(pVal++);
	//---ͨ��DAC���ÿɵ���ԴLM317�����ֵ
	LM317Task_Init(0, tempPower);
	//---У���Դ�Ƿ���
	if (*pVal>0)
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
UINT8_T ISPTask_UARTCmd_OpenAndClose(ISP_HandleType* ISPx, UART_HandleType* UARTx)
{
	UINT8_T	_return=0;
	//---����λ��
	if (UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset]==1)
	{
		//---������ģʽ�������û�������
		_return=ISPTask_EnterProgAndConfigInfo(ISPx, UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset], UARTx->msgRxdHandle.pMsgVal+UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 1);
	}
	else if (UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset] == 2)
	{
		//---���û�������,��Ҫ��ʹ��ʹ��EEPROM��ҳ���ģʽ
		_return= ISPTask_SetConfigInfo(ISPx, UARTx->msgRxdHandle.pMsgVal + UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 1);
	}
	else
	{
		_return = ISPTask_ExitProg(ISPx);
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
UINT8_T ISPTask_UARTCmd_EraseChip(ISP_HandleType* ISPx, UART_HandleType* UARTx)
{
	UINT8_T _return=OK_0;
	if (UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset] == 0)
	{
		//---�豸����
		_return= ISPTask_EraseChip(ISPx);
	}
	else if (UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset] == 1)
	{
		//---���FlashΪ��
		_return=ISPTask_CheckChipFlashEmpty(ISPx, 
											UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset + 1], UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset + 2],
											UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset + 3], UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset + 4]
											);
	}
	else if (UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset] == 2)
	{
		//---���EepromΪ��
		_return = ISPTask_CheckChipEepromEmpty(	ISPx,
												UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset + 1], UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset + 2]
											  );
	}
	else
	{
		_return=0xFF;
	}
	//---�����ǲ��ǲ�ղ���
	if (UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset]!=0)
	{
		//---����ղ�����ֵ
		UARTTask_FillMode_AddByte(UARTx, _return);
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
UINT8_T ISPTask_UARTCmd_ReadChipID(ISP_HandleType* ISPx, UART_HandleType* UARTx)
{
	UINT8_T	_return = 0;
	//---��ȡ�豸ID��Ϣ
	_return = ISPTask_ReadChipID(ISPx, UARTx->msgTxdHandle.pMsgVal + UARTx->msgTxdHandle.msgWIndex);
	//---���ݳ���ƫ��
	UARTx->msgTxdHandle.msgWIndex += 3;
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
UINT8_T ISPTask_UARTCmd_ReadChipCalibration(ISP_HandleType* ISPx, UART_HandleType* UARTx)
{
	UINT8_T	_return = 0;
	//---��ȡ�豸��У׼��
	_return = ISPTask_ReadChipCalibration(ISPx, UARTx->msgTxdHandle.pMsgVal + UARTx->msgTxdHandle.msgWIndex, UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset]);
	//---���ݵ�ַƫ��
	UARTx->msgTxdHandle.msgWIndex += UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset];
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
UINT8_T ISPTask_UARTCmd_ReadChipFuseAndLock(ISP_HandleType* ISPx, UART_HandleType* UARTx)
{
	UINT8_T	_return = 0;
	//---�ж��Ƕ�ȡ��˿λ���Ǽ���λ
	if (UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset] == 0)
	{
		//---��ȡ��˿λ
		_return = ISPTask_ReadChipFuse(ISPx, UARTx->msgTxdHandle.pMsgVal + UARTx->msgTxdHandle.msgWIndex, UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset]);
		//---У���Ƿ��ȡ��չ��˿λ
		if (UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset] != 0)
		{
			UARTx->msgTxdHandle.msgWIndex += 1;
		}
		UARTx->msgTxdHandle.msgWIndex += 2;
	}
	else
	{
		//---��ȡ����λ
		_return = ISPTask_ReadChipLock(ISPx, UARTx->msgTxdHandle.pMsgVal + UARTx->msgTxdHandle.msgWIndex);
		UARTx->msgTxdHandle.msgWIndex += 1;
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
UINT8_T ISPTask_UARTCmd_WriteChipFuse(ISP_HandleType* ISPx, UART_HandleType* UARTx)
{
	return ISPTask_WriteChipFuse(ISPx, UARTx->msgRxdHandle.pMsgVal + UARTx->msgDataTwoIndex + UARTx->msgIndexOffset, UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset]);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���̼���λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UARTCmd_WriteChipLock(ISP_HandleType* ISPx, UART_HandleType* UARTx)
{
	return ISPTask_WriteChipLock(ISPx, UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset]);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡоƬ��ROM��Ϣ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UARTCmd_ReadChipRom(ISP_HandleType* ISPx, UART_HandleType* UARTx)
{
	UINT8_T	_return = 0;
	UINT16_T length=0;
	//---�����ȡ���ݵĴ�С
	if (UARTx->msgRxdHandle.msgMaxSize < 0xFF)
	{
		length = UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset];
	}
	else
	{
		length = UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset];
		length = (length << 8) + UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 1];
	}
	//---��ȡROMҳ��Ϣ
	_return = ISPTask_ReadChipRom(ISPx, UARTx->msgTxdHandle.pMsgVal + UARTx->msgTxdHandle.msgWIndex, UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset], length);
	//---���ݵ�ƫ��
	UARTx->msgTxdHandle.msgWIndex += length;
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
UINT8_T ISPTask_UARTCmd_SetProgClok(ISP_HandleType* ISPx, UART_HandleType* UARTx)
{
	UINT8_T _return=OK_0;
	//---��ȡ��ѹ
	if (UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset] == 1)
	{
		_return= ISPTask_ReadChipPower(ISPx, UARTx->msgTxdHandle.pMsgVal + UARTx->msgDataOneIndex + UARTx->msgIndexOffset + 1);
		UARTx->msgTxdHandle.msgWIndex += 2;
	}
	//---���õ�ѹ
	else if (UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset] == 2)
	{
		_return=ISPTask_WriteChipPower(ISPx, UARTx->msgRxdHandle.pMsgVal+UARTx->msgDataOneIndex + UARTx->msgIndexOffset + 1);
	}
	else
	{
		//---���ñ��ʱ��
		_return = ISPTask_SetProgClock(ISPx, UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset+1]);
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
UINT8_T ISPTask_UARTCmd_ReadChipFlash(ISP_HandleType * ISPx, UART_HandleType * UARTx)
{
	UINT8_T	_return = 0;
	UINT16_T length = 0;
	//---�����ȡ���ݵĴ�С
	if (UARTx->msgRxdHandle.msgMaxSize < 0xFF)
	{
		length = UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 2];
	}
	else
	{
		length = UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 2];
		length = (length << 8) + UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 3];
	}
	//---��ȡָ��λ�õ�Flash����
	_return= ISPTask_ReadChipFlashAddr(ISPx,UARTx->msgTxdHandle.pMsgVal + UARTx->msgTxdHandle.msgWIndex, 
											UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset],
											UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset],
											UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset+1],
											length);
	//---���ݵ�ƫ��
	UARTx->msgTxdHandle.msgWIndex += length;
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
UINT8_T ISPTask_UARTCmd_WriteChipFlashPage(ISP_HandleType* ISPx, UART_HandleType* UARTx)
{
	UINT8_T dataOffset = 0;
	UINT16_T length = 0;
	//---����д�����ݵĴ�С
	if (UARTx->msgRxdHandle.msgMaxSize<0xFF)
	{
		length = UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 2];
		dataOffset=3;
	}
	else
	{
		length = UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 2];
		length = (length << 8) + UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 3];
		dataOffset = 4;
	}	
	//---��ָ��λ�ñ������
	return ISPTask_WriteChipFlashPage(ISPx,	UARTx->msgRxdHandle.pMsgVal + UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + dataOffset,
											UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset],
											UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset],
											UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 1],
											length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ͨ�����������ȡeeprom����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UARTCmd_ReadChipEeprom(ISP_HandleType* ISPx, UART_HandleType* UARTx)
{
	UINT8_T	_return = 0;
	UINT16_T length = 0;
	//---�����ȡ���ݵĴ�С
	if (UARTx->msgRxdHandle.msgMaxSize < 0xFF)
	{
		length = UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 1];
	}
	else
	{
		length = UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 1];
		length = (length << 8) + UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 2];
	}
	//---��ȡָ��λ�õ�Eeprom����
	_return = ISPTask_ReadChipEepromAddr(ISPx, UARTx->msgTxdHandle.pMsgVal + UARTx->msgTxdHandle.msgWIndex,
											UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset],
											UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset],
											length);
	//---���ݵ�ƫ��
	UARTx->msgTxdHandle.msgWIndex += length;
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
UINT8_T ISPTask_UARTCmd_WriteChipEeprom(ISP_HandleType* ISPx, UART_HandleType* UARTx)
{
	UINT8_T dataOffset = 0;
	UINT16_T length = 0;
	//---�����ȡ���ݵĴ�С
	if (UARTx->msgRxdHandle.msgMaxSize < 0xFF)
	{
		length = UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 1];
		dataOffset = 2;
	}
	else
	{
		length = UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 1];
		length = (length << 8) + UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + 2];
		dataOffset = 3;
	}
	//---���ָ��λ�õ�Eeprom����
	return ISPTask_WriteChipEeprom( ISPx, UARTx->msgRxdHandle.pMsgVal + UARTx->msgDataTwoIndex + UARTx->msgIndexOffset + dataOffset,
									UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataOneIndex + UARTx->msgIndexOffset],
									UARTx->msgRxdHandle.pMsgVal[UARTx->msgDataTwoIndex + UARTx->msgIndexOffset],
									length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UARTCmd_ChildTask(ISP_HandleType* ISPx, UART_HandleType* UARTx,UINT8_T isChildCmd)
{
	UINT8_T _return = 0;
	//---������ִ�н��
	UARTTask_FillMode_AddByte(UARTx, 0x00);
	UARTx->msgIndexOffset= (isChildCmd == 0 ? 0 : 1);
	//---���������������
	switch (UARTx->msgRxdHandle.pMsgVal[UARTx->msgCmdIndex+ UARTx->msgIndexOffset])
	{
		case CMD_ISP_OPEN_CLOSE:
			//---����֮�󣬵�1�ֽ�0---����رգ�1---����򿪣���2�ֽ�����йأ���ر��޹�
			_return= ISPTask_UARTCmd_OpenAndClose(ISPx,UARTx);
			break;
		case CMD_ISP_ERASE:
			//---�����豸����1�ֽ�0---���������1---������Flash��2---������Eeprom
			_return= ISPTask_UARTCmd_EraseChip(ISPx, UARTx);
			break;
		case CMD_ISP_FLASH_PAGE_READ:
			//---��ȡFlash
			_return= ISPTask_UARTCmd_ReadChipFlash(ISPx, UARTx);
			break;
		case CMD_ISP_FLASH_PAGE_WRITE:
			//---���Flash
			_return= ISPTask_UARTCmd_WriteChipFlashPage(ISPx, UARTx);
			break;
		case CMD_ISP_EEPROM_PAGE_READ:
			//---��ȡEeprom
			_return= ISPTask_UARTCmd_ReadChipEeprom(ISPx, UARTx);
			break;
		case CMD_ISP_EEPROM_PAGE_WRITE:
			//---���Eeprom
			_return = ISPTask_UARTCmd_WriteChipEeprom(ISPx, UARTx);
			break;
		case CMD_ISP_FUSE_LOCK_READ:
			//---��ȡ��˿λ����У��λ
			_return= ISPTask_UARTCmd_ReadChipFuseAndLock(ISPx,UARTx);
			break;
		case CMD_ISP_FUSE_WRITE	:
			//---�����˿λ
			_return= ISPTask_UARTCmd_WriteChipFuse(ISPx, UARTx);
			break;
		case CMD_ISP_LOCK_WRITE	:
			//---��̼���λ
			_return= ISPTask_UARTCmd_WriteChipLock(ISPx, UARTx);
			break;
		case CMD_ISP_ID_READ:
			//---��ȡ�豸��ID
			_return= ISPTask_UARTCmd_ReadChipID(ISPx,UARTx);
			break;
		case CMD_ISP_CALIBRATIONBYTE_READ:
			//---��ȡУ׼��
			_return= ISPTask_UARTCmd_ReadChipCalibration(ISPx, UARTx);
			break;
		case CMD_ISP_ROM_PAGE_READ:
			//---��ȡROMҳ��Ϣ
			_return= ISPTask_UARTCmd_ReadChipRom(ISPx,UARTx);
			break;
		case CMD_ISP_PROG_CLOCK_SET:
			//---���ñ��ʱ�ӣ��༶������������Ҫ�е�Դ�����úͶ�ȡ
			_return= ISPTask_UARTCmd_SetProgClok(ISPx, UARTx);
			break;
		default:
			//---��ʶ�������
			_return = ERROR_1;
			break;
	}
	//---�����Խ��
	UARTTask_FillMode_SetResultFlag(UARTx,_return);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UARTCmd_ParentTask(ISP_HandleType* ISPx, UART_HandleType* UARTx, UINT8_T isChildCmd)
{
	if ((UARTx != NULL) && (ISPx != NULL))
	{
		//---�жϽ����Ƿ����
		if (UARTTask_GetState(&(UARTx->msgRxdHandle)) == 1)
		{
			//---CRC��У����豸IDУ��
			if ((UARTTask_Read_CRCTask(UARTx) == OK_0) && (UARTTask_DeviceID(UARTx) == OK_0))
			{
				//---����������������ݱ�ͷ�����ȣ���ַID,����Ĵ���
				UARTTask_FillMode_Init(UARTx,isChildCmd);
				//---��������
				ISPTask_UARTCmd_ChildTask(ISPx, UARTx, isChildCmd);
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

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UARTCmd_ParentTask_New(ISP_HandleType* ISPx, UART_HandleType* UARTx, UINT8_T isChildCmd)
{
	UINT8_T _return = OK_0;
	//---����������������ݱ�ͷ�����ȣ���ַID,����Ĵ���
	UARTTask_FillMode_Init(UARTx, isChildCmd);
	//---��������
	ISPTask_UARTCmd_ChildTask(ISPx, UARTx, isChildCmd);
	//---�Ƿ���Ҫ���ӻ��з�
	if (UARTx->msgTxdHandle.msgAddNewLine == 1)
	{
		UARTTask_FillMode_AddByte(UARTx, 0x0D);
		UARTTask_FillMode_AddByte(UARTx, 0x0A);
	}
	//---�������ݷ���
	UARTTask_FillMode_WriteByteSTART(UARTx, 0);
	return _return;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_UARTCmd_Task(ISP_HandleType* ISPx, UART_HandleType* UARTx)
{
	UINT8_T _return = OK_0;
	//_return= ISPTask_UARTCmd_ParentTask(ISPx, UARTx, 0);
	_return = ISPTask_UARTCmd_ParentTask_New(ISPx, UARTx, 0);
	return _return;
}
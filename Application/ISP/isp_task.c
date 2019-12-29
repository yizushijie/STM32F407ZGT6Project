#include "isp_task.h"

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_Init(ISP_HandlerType *ISPx, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void))
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
UINT8_T ISPTask_DeInit(ISP_HandlerType *ISPx)
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
UINT8_T ISPTask_SetProgClock(ISP_HandlerType* ISPx, UINT8_T clok)
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
UINT8_T ISPTask_EnterProg(ISP_HandlerType *ISPx, UINT8_T isPollReady)
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
UINT8_T ISPTask_EnterProgAndConfigInfo(ISP_HandlerType* ISPx, UINT8_T isPollReady,UINT8_T *pVal)
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
UINT8_T ISPTask_ExitProg(ISP_HandlerType *ISPx)
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
UINT8_T ISPTask_AddWatch(ISP_HandlerType* ISPx)
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
UINT8_T ISPTask_RemoveWatch(ISP_HandlerType* ISPx)
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
UINT8_T ISPTask_RefreshWatch(ISP_HandlerType* ISPx)
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
UINT8_T ISPTask_SetIntervalTime(ISP_HandlerType* ISPx, UINT16_T intervalTime)
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
UINT16_T ISPTask_GetIntervalTime(ISP_HandlerType* ISPx)
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
UINT8_T ISPTask_ReadReady(ISP_HandlerType *ISPx)
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
UINT8_T ISPTask_EraseChip(ISP_HandlerType *ISPx)
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
UINT8_T ISPTask_ReadChipID(ISP_HandlerType *ISPx, UINT8_T *pVal)
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
UINT8_T ISPTask_ReadChipCalibration(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T length)
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
UINT8_T ISPTask_ReadChipFuse(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T isNeedExternFuse)
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
UINT8_T ISPTask_ReadChipLock(ISP_HandlerType *ISPx, UINT8_T *pVal)
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
UINT8_T ISPTask_ReadChipRom(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T addr, UINT16_T length)
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
UINT8_T ISPTask_WriteChipFuse(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T isNeedExternFuse)
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
UINT8_T ISPTask_WriteChipLock(ISP_HandlerType *ISPx, UINT8_T val)
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
UINT8_T ISPTask_ReadChipEepromAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
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
UINT8_T ISPTask_ReadChipEepromLongAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length)
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
UINT8_T ISPTask_WriteChipEepromAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
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
UINT8_T ISPTask_UpdateChipEepromPage(ISP_HandlerType* ISPx, UINT8_T* pVal)
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
UINT8_T ISPTask_UpdateChipEepromAddr(ISP_HandlerType* ISPx, UINT8_T highAddr, UINT8_T lowAddr)
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
UINT8_T ISPTask_UpdateChipEepromLongAddr(ISP_HandlerType* ISPx, UINT16_T addr)
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
UINT8_T ISPTask_WriteChipEepromPage(ISP_HandlerType* ISPx, UINT8_T* pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T pageNum)
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
UINT8_T ISPTask_WriteChipEepromLongAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length)
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
UINT8_T ISPTask_WriteChipEepromAddrWithJumpEmpty(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
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
UINT8_T ISPTask_WriteChipEepromLongAddrWithJumpEmpty(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length)
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
UINT8_T ISPTask_WriteChipEeprom(ISP_HandlerType* ISPx, UINT8_T* pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T pageNum)
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
UINT8_T ISPTask_ReadChipFlashAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
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
UINT8_T ISPTask_ReadChipFlashLongAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT32_T addr, UINT16_T length)
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
UINT8_T ISPTask_UpdateExternAddr(ISP_HandlerType* ISPx, UINT8_T addr)
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
UINT8_T ISPTask_UpdateExternLongAddr(ISP_HandlerType* ISPx, UINT32_T addr)
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
UINT8_T ISPTask_UpdateChipFlashBuffer(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T index, UINT16_T length)
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
UINT8_T ISPTask_UpdateChipFlashAddr(ISP_HandlerType *ISPx, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr)
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
UINT8_T ISPTask_UpdateChipFlashLongAddr(ISP_HandlerType *ISPx, UINT32_T addr)
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
UINT8_T ISPTask_WriteChipFlashPage(ISP_HandlerType* ISPx, UINT8_T* pVal, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
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
UINT8_T ISPTask_CheckChipFlashEmpty(ISP_HandlerType* ISPx, UINT8_T pageByteSizeH, UINT8_T pageByteSizeL, UINT8_T pageNumH, UINT8_T pageNumL)
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
UINT8_T ISPTask_CheckChipFlashEmptyLong(ISP_HandlerType* ISPx, UINT16_T pageByteSize, UINT16_T pageNum)
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
UINT8_T ISPTask_CheckChipEepromEmpty(ISP_HandlerType* ISPx, UINT8_T byteSize, UINT8_T num)
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
UINT8_T ISPTask_SetConfigInfo(ISP_HandlerType* ISPx, UINT8_T* pVal)
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
UINT8_T ISPTask_ReadChipPower(ISP_HandlerType* ISPx, UINT8_T* pVal)
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
UINT8_T ISPTask_WriteChipPower(ISP_HandlerType* ISPx, UINT8_T* pVal)
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
UINT8_T ISPTask_USARTCmd_OpenAndClose(ISP_HandlerType* ISPx, USART_HandlerType* USARTx)
{
	UINT8_T	_return=0;
	//---����λ��
	if (USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset]==1)
	{
		//---������ģʽ�������û�������
		_return=ISPTask_EnterProgAndConfigInfo(ISPx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + USARTx->msgIndexOffset], USARTx->msgRxdHandler.pMsgVal+USARTx->msgDataTwoIndex + USARTx->msgIndexOffset + 1);
	}
	else if (USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset] == 2)
	{
		//---���û�������,��Ҫ��ʹ��ʹ��EEPROM��ҳ���ģʽ
		_return= ISPTask_SetConfigInfo(ISPx, USARTx->msgRxdHandler.pMsgVal + USARTx->msgDataTwoIndex + USARTx->msgIndexOffset + 1);
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
UINT8_T ISPTask_USARTCmd_EraseChip(ISP_HandlerType* ISPx, USART_HandlerType* USARTx)
{
	UINT8_T _return=OK_0;
	if (USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset] == 0)
	{
		//---�豸����
		_return= ISPTask_EraseChip(ISPx);
	}
	else if (USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset] == 1)
	{
		//---���FlashΪ��
		_return=ISPTask_CheckChipFlashEmpty(ISPx, 
											USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset + 1], USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset + 2],
											USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset + 3], USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset + 4]
											);
	}
	else if (USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset] == 2)
	{
		//---���EepromΪ��
		_return = ISPTask_CheckChipEepromEmpty(	ISPx,
												USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset + 1], USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset + 2]
											  );
	}
	else
	{
		_return=0xFF;
	}
	//---�����ǲ��ǲ�ղ���
	if (USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset]!=0)
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
UINT8_T ISPTask_USARTCmd_ReadChipID(ISP_HandlerType* ISPx, USART_HandlerType* USARTx)
{
	UINT8_T	_return = 0;
	//---��ȡ�豸ID��Ϣ
	_return = ISPTask_ReadChipID(ISPx, USARTx->msgTxdHandler.pMsgVal + USARTx->msgTxdHandler.msgIndexW);
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
UINT8_T ISPTask_USARTCmd_ReadChipCalibration(ISP_HandlerType* ISPx, USART_HandlerType* USARTx)
{
	UINT8_T	_return = 0;
	//---��ȡ�豸��У׼��
	_return = ISPTask_ReadChipCalibration(ISPx, USARTx->msgTxdHandler.pMsgVal + USARTx->msgTxdHandler.msgIndexW, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset]);
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
UINT8_T ISPTask_USARTCmd_ReadChipFuseAndLock(ISP_HandlerType* ISPx, USART_HandlerType* USARTx)
{
	UINT8_T	_return = 0;
	//---�ж��Ƕ�ȡ��˿λ���Ǽ���λ
	if (USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset] == 0)
	{
		//---��ȡ��˿λ
		_return = ISPTask_ReadChipFuse(ISPx, USARTx->msgTxdHandler.pMsgVal + USARTx->msgTxdHandler.msgIndexW, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + USARTx->msgIndexOffset]);
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
		_return = ISPTask_ReadChipLock(ISPx, USARTx->msgTxdHandler.pMsgVal + USARTx->msgTxdHandler.msgIndexW);
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
UINT8_T ISPTask_USARTCmd_WriteChipFuse(ISP_HandlerType* ISPx, USART_HandlerType* USARTx)
{
	return ISPTask_WriteChipFuse(ISPx, USARTx->msgRxdHandler.pMsgVal + USARTx->msgDataTwoIndex + USARTx->msgIndexOffset, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset]);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���̼���λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_USARTCmd_WriteChipLock(ISP_HandlerType* ISPx, USART_HandlerType* USARTx)
{
	return ISPTask_WriteChipLock(ISPx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset]);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡоƬ��ROM��Ϣ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_USARTCmd_ReadChipRom(ISP_HandlerType* ISPx, USART_HandlerType* USARTx)
{
	UINT8_T	_return = 0;
	UINT16_T length=0;
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
	_return = ISPTask_ReadChipRom(ISPx, USARTx->msgTxdHandler.pMsgVal + USARTx->msgTxdHandler.msgIndexW, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset], length);
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
UINT8_T ISPTask_USARTCmd_SetProgClok(ISP_HandlerType* ISPx, USART_HandlerType* USARTx)
{
	UINT8_T _return=OK_0;
	//---��ȡ��ѹ
	if (USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset] == 1)
	{
		_return= ISPTask_ReadChipPower(ISPx, USARTx->msgTxdHandler.pMsgVal + USARTx->msgDataOneIndex + USARTx->msgIndexOffset + 1);
		USARTx->msgTxdHandler.msgIndexW += 2;
	}
	//---���õ�ѹ
	else if (USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset] == 2)
	{
		_return=ISPTask_WriteChipPower(ISPx, USARTx->msgRxdHandler.pMsgVal+USARTx->msgDataOneIndex + USARTx->msgIndexOffset + 1);
	}
	else
	{
		//---���ñ��ʱ��
		_return = ISPTask_SetProgClock(ISPx, USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset+1]);
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
UINT8_T ISPTask_USARTCmd_ReadChipFlash(ISP_HandlerType * ISPx, USART_HandlerType * USARTx)
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
	_return= ISPTask_ReadChipFlashAddr(ISPx,USARTx->msgTxdHandler.pMsgVal + USARTx->msgTxdHandler.msgIndexW, 
											USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataOneIndex + USARTx->msgIndexOffset],
											USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + USARTx->msgIndexOffset],
											USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + USARTx->msgIndexOffset+1],
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
UINT8_T ISPTask_USARTCmd_WriteChipFlashPage(ISP_HandlerType* ISPx, USART_HandlerType* USARTx)
{
	UINT8_T dataOffset = 0;
	UINT16_T length = 0;
	//---����д�����ݵĴ�С
	if (USARTx->msgRxdHandler.msgSize<0xFF)
	{
		length = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + USARTx->msgIndexOffset + 2];
		dataOffset=3;
	}
	else
	{
		length = USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + USARTx->msgIndexOffset + 2];
		length = (length << 8) + USARTx->msgRxdHandler.pMsgVal[USARTx->msgDataTwoIndex + USARTx->msgIndexOffset + 3];
		dataOffset = 4;
	}	
	//---��ָ��λ�ñ������
	return ISPTask_WriteChipFlashPage(ISPx,	USARTx->msgRxdHandler.pMsgVal + USARTx->msgDataTwoIndex + USARTx->msgIndexOffset + dataOffset,
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
UINT8_T ISPTask_USARTCmd_ReadChipEeprom(ISP_HandlerType* ISPx, USART_HandlerType* USARTx)
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
	_return = ISPTask_ReadChipEepromAddr(ISPx, USARTx->msgTxdHandler.pMsgVal + USARTx->msgTxdHandler.msgIndexW,
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
UINT8_T ISPTask_USARTCmd_WriteChipEeprom(ISP_HandlerType* ISPx, USART_HandlerType* USARTx)
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
	return ISPTask_WriteChipEeprom( ISPx, USARTx->msgRxdHandler.pMsgVal + USARTx->msgDataTwoIndex + USARTx->msgIndexOffset + dataOffset,
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
UINT8_T ISPTask_USARTCmd_ChildTask(ISP_HandlerType* ISPx, USART_HandlerType* USARTx,UINT8_T isChildCmd)
{
	UINT8_T _return = 0;
	//---������ִ�н��
	USARTTask_FillMode_AddByte(USARTx, 0x00);
	USARTx->msgIndexOffset= (isChildCmd == 0 ? 0 : 1);
	//---���������������
	switch (USARTx->msgRxdHandler.pMsgVal[USARTx->msgCmdIndex+ USARTx->msgIndexOffset])
	{
		case CMD_ISP_OPEN_CLOSE:
			//---����֮�󣬵�1�ֽ�0---����رգ�1---����򿪣���2�ֽ�����йأ���ر��޹�
			_return= ISPTask_USARTCmd_OpenAndClose(ISPx,USARTx);
			break;
		case CMD_ISP_ERASE:
			//---�����豸����1�ֽ�0---���������1---������Flash��2---������Eeprom
			_return= ISPTask_USARTCmd_EraseChip(ISPx, USARTx);
			break;
		case CMD_ISP_FLASH_PAGE_READ:
			//---��ȡFlash
			_return= ISPTask_USARTCmd_ReadChipFlash(ISPx, USARTx);
			break;
		case CMD_ISP_FLASH_PAGE_WRITE:
			//---���Flash
			_return= ISPTask_USARTCmd_WriteChipFlashPage(ISPx, USARTx);
			break;
		case CMD_ISP_EEPROM_PAGE_READ:
			//---��ȡEeprom
			_return= ISPTask_USARTCmd_ReadChipEeprom(ISPx, USARTx);
			break;
		case CMD_ISP_EEPROM_PAGE_WRITE:
			//---���Eeprom
			_return = ISPTask_USARTCmd_WriteChipEeprom(ISPx, USARTx);
			break;
		case CMD_ISP_FUSE_LOCK_READ:
			//---��ȡ��˿λ����У��λ
			_return= ISPTask_USARTCmd_ReadChipFuseAndLock(ISPx,USARTx);
			break;
		case CMD_ISP_FUSE_WRITE	:
			//---�����˿λ
			_return= ISPTask_USARTCmd_WriteChipFuse(ISPx, USARTx);
			break;
		case CMD_ISP_LOCK_WRITE	:
			//---��̼���λ
			_return= ISPTask_USARTCmd_WriteChipLock(ISPx, USARTx);
			break;
		case CMD_ISP_ID_READ:
			//---��ȡ�豸��ID
			_return= ISPTask_USARTCmd_ReadChipID(ISPx,USARTx);
			break;
		case CMD_ISP_CALIBRATIONBYTE_READ:
			//---��ȡУ׼��
			_return= ISPTask_USARTCmd_ReadChipCalibration(ISPx, USARTx);
			break;
		case CMD_ISP_ROM_PAGE_READ:
			//---��ȡROMҳ��Ϣ
			_return= ISPTask_USARTCmd_ReadChipRom(ISPx,USARTx);
			break;
		case CMD_ISP_PROG_CLOCK_SET:
			//---���ñ��ʱ�ӣ��༶������������Ҫ�е�Դ�����úͶ�ȡ
			_return= ISPTask_USARTCmd_SetProgClok(ISPx, USARTx);
			break;
		default:
			//---��ʶ�������
			_return = ERROR_1;
			break;
	}
	//---�����Խ��
	USARTTask_FillMode_SetResultFlag(USARTx,_return);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPTask_USARTCmd_ParentTask(ISP_HandlerType* ISPx, USART_HandlerType* USARTx, UINT8_T isChildCmd)
{
	if ((USARTx != NULL) && (ISPx != NULL))
	{
		//---�жϽ����Ƿ����
		if (USARTTask_GetReadState(USARTx) == 1)
		{
			//---CRC��У����豸IDУ��
			if ((USARTTask_CRCTask_Read(USARTx) == OK_0) && (USARTTask_DeviceID(USARTx) == OK_0))
			{
				//---����������������ݱ�ͷ�����ȣ���ַID,����Ĵ���
				USARTTask_FillMode_Init(USARTx,isChildCmd);
				//---��������
				ISPTask_USARTCmd_ChildTask(ISPx, USARTx, isChildCmd);
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
UINT8_T ISPTask_USARTCmd_ParentTask_New(ISP_HandlerType* ISPx, USART_HandlerType* USARTx, UINT8_T isChildCmd)
{
	UINT8_T _return = OK_0;
	//---����������������ݱ�ͷ�����ȣ���ַID,����Ĵ���
	USARTTask_FillMode_Init(USARTx, isChildCmd);
	//---��������
	ISPTask_USARTCmd_ChildTask(ISPx, USARTx, isChildCmd);
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
UINT8_T ISPTask_USARTCmd_Task(ISP_HandlerType* ISPx, USART_HandlerType* USARTx)
{
	UINT8_T _return = OK_0;
	//_return= ISPTask_USARTCmd_ParentTask(ISPx, USARTx, 0);
	_return = ISPTask_USARTCmd_ParentTask_New(ISPx, USARTx, 0);
	return _return;
}
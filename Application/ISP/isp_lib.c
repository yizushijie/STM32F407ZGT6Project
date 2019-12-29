#include "isp_lib.h"

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_Init(ISP_HandlerType *ISPx, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void))
{
	return ISP_Init(ISPx, pFuncDelayus, pFuncDelayms, pFuncTimerTick);
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ע����ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_DeInit(ISP_HandlerType *ISPx)
{
	return ISP_DeInit(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ñ��ʱ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_SetProgClock(ISP_HandlerType* ISPx, UINT8_T clok)
{
	return ISP_SetProgClock(ISPx, clok);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_EnterProg(ISP_HandlerType *ISPx, UINT8_T isPollReady)
{
	return ISP_EnterProg(ISPx,isPollReady);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������ģʽ������Memery��Ϣ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_EnterProgAndConfigInfo(ISP_HandlerType* ISPx, UINT8_T isPollReady,UINT8_T *pVal)
{
	UINT8_T _return= ISP_EnterProg(ISPx, isPollReady);
	//---У�������ģʽ
	if (_return==OK_0)
	{
		_return=ISP_SetConfigInfo(ISPx,pVal);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��˳����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_ExitProg(ISP_HandlerType *ISPx)
{
	return ISP_ExitProg(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���Ӽ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_AddWatch(ISP_HandlerType* ISPx)
{
	return ISP_AddWatch( ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��Ƴ����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_RemoveWatch(ISP_HandlerType* ISPx)
{
	return ISP_RemoveWatch(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ˢ�¼��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_RefreshWatch(ISP_HandlerType* ISPx)
{
	return ISP_RefreshWatch(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������ѯ���ʱ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_SetIntervalTime(ISP_HandlerType* ISPx, UINT16_T intervalTime)
{
	return ISP_SetIntervalTime(ISPx,intervalTime);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ��ѯ���ʱ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT16_T ISPLib_GetIntervalTime(ISP_HandlerType* ISPx)
{
	return ISP_GetIntervalTime(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡReady�ź�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_ReadReady(ISP_HandlerType *ISPx)
{
	return ISP_ReadReady(ISPx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������豸
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_EraseChip(ISP_HandlerType *ISPx)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
		_return = ISP_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		ISP_RefreshWatch(ISPx);
		//---���ò���
		_return = ISP_EraseChip(ISPx);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
		//---����ʱ����
		ISP_SetIntervalTime(ISPx,100);
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡChipID
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_ReadChipID(ISP_HandlerType *ISPx, UINT8_T *pVal)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
		_return = ISP_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		ISP_RefreshWatch(ISPx);
		//---��ȡ�豸ID��Ϣ
		_return = ISP_ReadChipID(ISPx, pVal);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
		//---����ʱ����
		ISP_SetIntervalTime(ISPx, 100);
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡУ׼��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_ReadChipCalibration(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T length)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
		_return = ISP_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		ISP_RefreshWatch(ISPx);
		//---��ȡУ׼��
		_return = ISP_ReadChipCalibration(ISPx, pVal, length);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
		//---����ʱ����
		ISP_SetIntervalTime(ISPx, 100);
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ��˿λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_ReadChipFuse(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T isNeedExternFuse)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
		_return = ISP_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		ISP_RefreshWatch(ISPx);
		//---��ȡ��˿λ
		_return = ISP_ReadChipFuse(ISPx, pVal, isNeedExternFuse);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
		//---����ʱ����
		ISP_SetIntervalTime(ISPx, 100);
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ����λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_ReadChipLock(ISP_HandlerType *ISPx, UINT8_T *pVal)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
		_return = ISP_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		ISP_RefreshWatch(ISPx);
		//---��ȡ����λ
		_return = ISP_ReadChipLock(ISPx, pVal);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
		//---����ʱ����
		ISP_SetIntervalTime(ISPx, 100);
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡROM��Ϣ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_ReadChipRom(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T addr, UINT16_T length)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
		_return = ISP_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		ISP_RefreshWatch(ISPx);
		//---��ȡROM��Ϣ
		_return = ISP_ReadChipRom(ISPx, pVal, addr, length);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
		//---����ʱ����
		ISP_SetIntervalTime(ISPx, 100);
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������˿λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_WriteChipFuse(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T isNeedExternFuse)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
		_return = ISP_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		ISP_RefreshWatch(ISPx);
		//---�����˿λ
		_return = ISP_WriteChipFuse(ISPx, pVal, isNeedExternFuse);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
		//---����ʱ����
		ISP_SetIntervalTime(ISPx, 100);
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���̼���λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_WriteChipLock(ISP_HandlerType *ISPx, UINT8_T val)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
		_return = ISP_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		ISP_RefreshWatch(ISPx);
		//---��̼���λ
		_return = ISP_WriteChipLock(ISPx, val);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
		//---����ʱ����
		ISP_SetIntervalTime(ISPx, 100);
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡEEPROM
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_ReadChipEepromAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
		_return = ISP_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		ISP_RefreshWatch(ISPx);
		//---��ȡEeprom
		_return = ISP_ReadChipEepromAddr(ISPx, pVal, highAddr, lowAddr, length);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
		//---����ʱ����
		ISP_SetIntervalTime(ISPx, 100);
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡEEPROM
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_ReadChipEepromLongAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
		_return = ISP_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		ISP_RefreshWatch(ISPx);
		//---��ȡEEPROM
		_return = ISP_ReadChipEepromLongAddr(ISPx, pVal, addr, length);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
		//---����ʱ����
		ISP_SetIntervalTime(ISPx, 100);
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����EEPROM
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_WriteChipEepromAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
		_return = ISP_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		ISP_RefreshWatch(ISPx);
		//---���EEPROM
		_return= ISP_WriteChipEepromAddr(ISPx, pVal, highAddr, lowAddr, length);
		//---����ʱ����
		ISP_SetIntervalTime(ISPx, 100);
	}
	else
	{
		_return=ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_UpdateChipEepromPage(ISP_HandlerType* ISPx, UINT8_T* pVal)
{
	return ISP_UpdateChipEepromPage(ISPx,pVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_UpdateChipEepromAddr(ISP_HandlerType* ISPx, UINT8_T highAddr, UINT8_T lowAddr)
{
	return ISP_UpdateChipEepromAddr(ISPx, highAddr,lowAddr);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����EEPROM
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_WriteChipEepromLongAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
		_return = ISP_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		ISP_RefreshWatch(ISPx);
		//---���EEPROM
		_return = ISP_WriteChipEepromLongAddr(ISPx, pVal, addr, length);
		//---����ʱ����
		ISP_SetIntervalTime(ISPx, 100);
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����EEPROM
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_WriteChipEepromAddrWithJumpEmpty(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
		_return = ISP_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		ISP_RefreshWatch(ISPx);
		//---���EEPROM
		_return = ISP_WriteChipEepromAddrWithJumpEmpty(ISPx, pVal, highAddr, lowAddr, length);
		//---����ʱ����
		ISP_SetIntervalTime(ISPx, 100);
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����EEPROM
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_WriteChipEepromLongAddrWithJumpEmpty(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
		_return = ISP_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		ISP_RefreshWatch(ISPx);
		//---���EEPROM
		_return = ISP_WriteChipEepromLongAddrWithJumpEmpty(ISPx, pVal, addr, length);
		//---����ʱ����
		ISP_SetIntervalTime(ISPx, 100);
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_UpdateChipEepromLongAddr(ISP_HandlerType* ISPx, UINT16_T addr)
{
	return ISP_UpdateChipEepromLongAddr(ISPx,addr);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ҳģʽ���Eeprom
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_WriteChipEepromPage(ISP_HandlerType* ISPx, UINT8_T* pVal,UINT8_T highAddr, UINT8_T lowAddr, UINT16_T pageNum)
{
	return ISP_WriteChipEepromPage(ISPx, pVal,highAddr,lowAddr,pageNum);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_WriteChipEeprom(ISP_HandlerType* ISPx, UINT8_T* pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T pageNum)
{
	return ISP_WriteChipEeprom( ISPx,  pVal, highAddr, lowAddr, pageNum);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡFlash
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_ReadChipFlashAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
		_return = ISP_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		ISP_RefreshWatch(ISPx);
		//---��ȡFlash
		_return = ISP_ReadChipFlashAddr(ISPx, pVal, externAddr, highAddr, lowAddr, length);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
		//---����ʱ����
		ISP_SetIntervalTime(ISPx, 100);
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡFlash
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_ReadChipFlashLongAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT32_T addr, UINT16_T length)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
		_return = ISP_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		ISP_RefreshWatch(ISPx);
		//---��ȡFlash
		_return = ISP_ReadChipFlashLongAddr(ISPx, pVal, addr, length);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
		//---����ʱ����
		ISP_SetIntervalTime(ISPx, 100);
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������չλ��ַ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_UpdateExternAddr(ISP_HandlerType* ISPx, UINT8_T addr)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
		_return = ISP_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		ISP_RefreshWatch(ISPx);
		//---��ȡFlash
		_return = ISP_UpdateExternAddr(ISPx, addr);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
		//---����ʱ����
		ISP_SetIntervalTime(ISPx, 100);
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������չλ��ַ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_UpdateExternLongAddr(ISP_HandlerType* ISPx, UINT32_T addr)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
		_return = ISP_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		ISP_RefreshWatch(ISPx);
		//---��ȡFlash
		_return = ISP_UpdateExternLongAddr(ISPx, addr);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
		//---����ʱ����
		ISP_SetIntervalTime(ISPx, 100);
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��������ݵ����ݻ�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_UpdateChipFlashBuffer(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T index, UINT16_T length)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
		_return = ISP_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		ISP_RefreshWatch(ISPx);
		//---����Flash�Ļ���������
		_return = ISP_UpdateChipFlashPage(ISPx, pVal, index, length);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
		//---����ʱ����
		ISP_SetIntervalTime(ISPx, 100);
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��������ݵ�ָ�������ݴ洢��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_UpdateChipFlashAddr(ISP_HandlerType *ISPx, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
		_return = ISP_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		ISP_RefreshWatch(ISPx);
		//---�����ݸ��µ�Flash��ָ����ַ
		_return = ISP_UpdateChipFlashAddr(ISPx, externAddr, highAddr, lowAddr);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
		//---����ʱ����
		ISP_SetIntervalTime(ISPx, 100);
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��������ݵ�ָ�������ݴ洢��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_UpdateChipFlashLongAddr(ISP_HandlerType *ISPx, UINT32_T addr)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
		_return = ISP_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		ISP_RefreshWatch(ISPx);
		//---�����ݸ��µ�Flash��ָ����ַ
		_return = ISP_UpdateChipFlashLongAddr(ISPx, addr);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
		//---����ʱ����
		ISP_SetIntervalTime(ISPx, 100);
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ҳģʽ��ָ��������д��Flash
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_WriteChipFlashPage(ISP_HandlerType* ISPx,UINT8_T *pVal, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr,UINT16_T length)
{
	return ISP_WriteChipFlashPage(ISPx, pVal,externAddr, highAddr, lowAddr, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_CheckChipFlashEmpty(ISP_HandlerType* ISPx, UINT8_T pageByteSizeH, UINT8_T pageByteSizeL, UINT8_T pageNumH, UINT8_T pageNumL)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
		_return = ISP_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		ISP_RefreshWatch(ISPx);
		//---У��Flash�Ƿ�Ϊ��
		_return = ISP_CheckChipFlashEmpty(ISPx, pageByteSizeH, pageByteSizeL, pageNumH, pageNumL);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
		//---����ʱ����
		ISP_SetIntervalTime(ISPx, 100);
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_CheckChipFlashEmptyLong(ISP_HandlerType* ISPx, UINT16_T pageByteSize, UINT16_T pageNum)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
		_return = ISP_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		ISP_RefreshWatch(ISPx);
		//---У��Flash�Ƿ�Ϊ��
		_return = ISP_CheckChipFlashEmptyLong(ISPx, pageByteSize, pageNum);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
		//---����ʱ����
		ISP_SetIntervalTime(ISPx, 100);
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_CheckChipEepromEmpty(ISP_HandlerType* ISPx, UINT8_T byteSize, UINT8_T num)
{
	UINT8_T	_return = 0;
	//---��鵱ǰ���ģʽ
	if (ISPx->msgState == 0)
	{
		//---������ģʽ
		_return = ISP_EnterProg(ISPx, ISPx->msgIsPollReady);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		ISP_RefreshWatch(ISPx);
		//---У��Eeprom�Ƿ�Ϊ��
		_return = ISP_CheckChipEepromEmpty(ISPx, byteSize, num);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
		//---����ʱ����
		ISP_SetIntervalTime(ISPx, 100);
	}
	else
	{
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISPLib_SetConfigInfo(ISP_HandlerType* ISPx, UINT8_T*pVal)
{
	return ISP_SetConfigInfo(ISPx, pVal);
}
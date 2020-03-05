#include "jtag_lib.h"

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGLib_Init(JTAG_HandleType* JTAGx, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void))
{
	return JTAG_Init(JTAGx, pFuncDelayus, pFuncDelayms, pFuncTimerTick);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGLib_ExitProg(JTAG_HandleType* JTAGx)
{
	return JTAG_ExitProg(JTAGx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGLib_EnterProg(JTAG_HandleType* JTAGx)
{
	return JTAG_EnterProg(JTAGx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������ģʽ������Memery��Ϣ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T JTAGLib_EnterProgAndConfigInfo(JTAG_HandleType* JTAGx, UINT8_T isPollReady, UINT8_T* pVal)
{
	UINT8_T _return = JTAG_EnterProg(JTAGx);
	//---У�������ģʽ
	if (_return == OK_0)
	{
		_return = JTAG_SetConfigInfo(JTAGx, pVal);
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
UINT8_T JTAGLib_EraseChip(JTAG_HandleType* JTAGx)
{
	UINT8_T _return = OK_0;
	//---�����״̬
	if (JTAGx->msgState == JTAG_PROG_NONE)
	{
		//---������ģʽ
		_return = JTAG_EnterProg(JTAGx);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		JTAG_RefreshWatch(JTAGx);
		//---����
		_return = JTAG_EraseChip(JTAGx);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
		//---����ʱ����
		JTAG_SetIntervalTime(JTAGx, 100);
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
UINT8_T JTAGLib_ReadIDChip(JTAG_HandleType* JTAGx, UINT8_T* pVal)
{
	UINT8_T _return = OK_0;
	//---�����״̬
	if (JTAGx->msgState == JTAG_PROG_NONE)
	{
		//---������ģʽ
		_return = JTAG_EnterProg(JTAGx);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		JTAG_RefreshWatch(JTAGx);
		//---��ȡJTAG��ID��Ϣ
		_return = JTAG_ReadIDChip(JTAGx, pVal);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
		//---����ʱ����
		JTAG_SetIntervalTime(JTAGx, 100);
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
UINT8_T JTAGLib_ReadChipID(JTAG_HandleType* JTAGx, UINT8_T* pVal)
{
	UINT8_T _return = OK_0;
	//---�����״̬
	if (JTAGx->msgState == JTAG_PROG_NONE)
	{
		//---������ģʽ
		_return = JTAG_EnterProg(JTAGx);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		JTAG_RefreshWatch(JTAGx);
		//---��ȡChip��ID��Ϣ
		_return = JTAG_ReadChipID(JTAGx, pVal);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
		//---����ʱ����
		JTAG_SetIntervalTime(JTAGx, 100);
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
UINT8_T JTAGLib_ReadChip(JTAG_HandleType* JTAGx, UINT8_T* pVal)
{
	UINT8_T _return = OK_0;
	//---�����״̬
	if (JTAGx->msgState == JTAG_PROG_NONE)
	{
		//---������ģʽ
		_return = JTAG_EnterProg(JTAGx);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		JTAG_RefreshWatch(JTAGx);
		//---��ȡID��Ϣ
		_return = JTAG_ReadChip(JTAGx, pVal);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
		//---����ʱ����
		JTAG_SetIntervalTime(JTAGx, 100);
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
UINT8_T JTAGLib_ReadChipCalibration(JTAG_HandleType* JTAGx, UINT8_T* pVal, UINT8_T length)
{
	UINT8_T _return = OK_0;
	//---�����״̬
	if (JTAGx->msgState == JTAG_PROG_NONE)
	{
		//---������ģʽ
		_return = JTAG_EnterProg(JTAGx);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		JTAG_RefreshWatch(JTAGx);
		//---��ȡУ׼����Ϣ
		_return = JTAG_ReadChipCalibration(JTAGx, pVal, length);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
		//---����ʱ����
		JTAG_SetIntervalTime(JTAGx, 100);
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
UINT8_T JTAGLib_ReadChipFuse(JTAG_HandleType* JTAGx, UINT8_T* pVal, UINT8_T isNeedExternFuse)
{
	UINT8_T _return = OK_0;
	//---�����״̬
	if (JTAGx->msgState == JTAG_PROG_NONE)
	{
		//---������ģʽ
		_return = JTAG_EnterProg(JTAGx);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		JTAG_RefreshWatch(JTAGx);
		//---��ȡ��˿λ��Ϣ
		_return = JTAG_ReadChipFuse(JTAGx, pVal, isNeedExternFuse);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
		//---����ʱ����
		JTAG_SetIntervalTime(JTAGx, 100);
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
UINT8_T JTAGLib_ReadChipLock(JTAG_HandleType* JTAGx, UINT8_T* pVal)
{
	UINT8_T _return = OK_0;
	//---�����״̬
	if (JTAGx->msgState == JTAG_PROG_NONE)
	{
		//---������ģʽ
		_return = JTAG_EnterProg(JTAGx);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		JTAG_RefreshWatch(JTAGx);
		//---��ȡ����λ��Ϣ
		_return = JTAG_ReadChipLock(JTAGx, pVal);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
		//---����ʱ����
		JTAG_SetIntervalTime(JTAGx, 100);
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
UINT8_T JTAGLib_ReadChipRom(JTAG_HandleType* JTAGx, UINT8_T* pVal, UINT8_T addr, UINT16_T length)
{
	UINT8_T _return = OK_0;
	//---�����״̬
	if (JTAGx->msgState == JTAG_PROG_NONE)
	{
		//---������ģʽ
		_return = JTAG_EnterProg(JTAGx);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		JTAG_RefreshWatch(JTAGx);
		//---��ȡROMҳ��Ϣ
		_return = JTAG_ReadChipRom(JTAGx, pVal, addr, length);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
		//---����ʱ����
		JTAG_SetIntervalTime(JTAGx, 100);
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
UINT8_T JTAGLib_WriteChipFuse(JTAG_HandleType* JTAGx, UINT8_T* pVal, UINT8_T isNeedExternFuse)
{
	UINT8_T _return = OK_0;
	//---�����״̬
	if (JTAGx->msgState == JTAG_PROG_NONE)
	{
		//---������ģʽ
		_return = JTAG_EnterProg(JTAGx);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		JTAG_RefreshWatch(JTAGx);
		//---�����˿λ��Ϣ
		_return = JTAG_WriteChipFuse(JTAGx, pVal, isNeedExternFuse);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
		//---����ʱ����
		JTAG_SetIntervalTime(JTAGx, 100);
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
UINT8_T JTAGLib_WriteChipLock(JTAG_HandleType* JTAGx, UINT8_T lockVal)
{
	UINT8_T _return = OK_0;
	//---�����״̬
	if (JTAGx->msgState == JTAG_PROG_NONE)
	{
		//---������ģʽ
		_return = JTAG_EnterProg(JTAGx);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		JTAG_RefreshWatch(JTAGx);
		//---��̼���λ��Ϣ
		_return = JTAG_WriteChipLock(JTAGx, lockVal);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
		//---����ʱ����
		JTAG_SetIntervalTime(JTAGx, 100);
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
UINT8_T JTAGLib_ReadChipEepromAddr(JTAG_HandleType* JTAGx, UINT8_T* pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	UINT8_T _return = OK_0;
	//---�����״̬
	if (JTAGx->msgState == JTAG_PROG_NONE)
	{
		//---������ģʽ
		_return = JTAG_EnterProg(JTAGx);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		JTAG_RefreshWatch(JTAGx);
		//---��ȡEEPROM��Ϣ
		_return = JTAG_ReadChipEepromAddr(JTAGx, pVal, highAddr, lowAddr, length);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
		//---����ʱ����
		JTAG_SetIntervalTime(JTAGx, 100);
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
UINT8_T JTAGLib_ReadChipEepromLongAddr(JTAG_HandleType* JTAGx, UINT8_T* pVal, UINT16_T addr, UINT16_T length)
{
	UINT8_T _return = OK_0;
	//---�����״̬
	if (JTAGx->msgState == JTAG_PROG_NONE)
	{
		//---������ģʽ
		_return = JTAG_EnterProg(JTAGx);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		JTAG_RefreshWatch(JTAGx);
		//---��ȡEEPROM��Ϣ
		_return = JTAG_ReadChipEepromLongAddr(JTAGx, pVal, addr, length);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
		//---����ʱ����
		JTAG_SetIntervalTime(JTAGx, 100);
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
UINT8_T JTAGLib_WriteChipEeprom(JTAG_HandleType* JTAGx, UINT8_T* pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T pageNum)
{
	UINT8_T _return = OK_0;
	//---�����״̬
	if (JTAGx->msgState == JTAG_PROG_NONE)
	{
		//---������ģʽ
		_return = JTAG_EnterProg(JTAGx);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		JTAG_RefreshWatch(JTAGx);
		//---���EEPROM��Ϣ
		_return = JTAG_WriteChipEeprom(JTAGx, pVal, highAddr, lowAddr, pageNum);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
		//---����ʱ����
		JTAG_SetIntervalTime(JTAGx, 100);
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
UINT8_T JTAGLib_ReadChipFlashAddr(JTAG_HandleType* JTAGx, UINT8_T* pVal, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	UINT8_T _return = OK_0;
	//---�����״̬
	if (JTAGx->msgState == JTAG_PROG_NONE)
	{
		//---������ģʽ
		_return = JTAG_EnterProg(JTAGx);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		JTAG_RefreshWatch(JTAGx);
		//---��ȡFLASH��Ϣ
		_return = JTAG_ReadChipFlashAddr(JTAGx, pVal, externAddr, highAddr, lowAddr, length);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
		//---����ʱ����
		JTAG_SetIntervalTime(JTAGx, 100);
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
UINT8_T JTAGLib_ReadChipFlashLongAddr(JTAG_HandleType* JTAGx, UINT8_T* pVal, UINT32_T addr, UINT16_T length)
{
	UINT8_T _return = OK_0;
	//---�����״̬
	if (JTAGx->msgState == JTAG_PROG_NONE)
	{
		//---������ģʽ
		_return = JTAG_EnterProg(JTAGx);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		JTAG_RefreshWatch(JTAGx);
		//---��ȡFLASH��Ϣ
		_return = JTAG_ReadChipFlashLongAddr(JTAGx, pVal, addr, length);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
		//---����ʱ����
		JTAG_SetIntervalTime(JTAGx, 100);
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
UINT8_T JTAGLib_WriteChipFlashPage(JTAG_HandleType* JTAGx, UINT8_T* pVal, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	UINT8_T _return = OK_0;
	//---�����״̬
	if (JTAGx->msgState == JTAG_PROG_NONE)
	{
		//---������ģʽ
		_return = JTAG_EnterProg(JTAGx);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		JTAG_RefreshWatch(JTAGx);
		//---���FLASH��Ϣ
		_return = JTAG_WriteChipFlashPage(JTAGx, pVal, externAddr, highAddr, lowAddr, length);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
		//---����ʱ����
		JTAG_SetIntervalTime(JTAGx, 100);
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
UINT8_T JTAGLib_CheckChipFlashEmpty(JTAG_HandleType* JTAGx, UINT8_T pageByteSizeH, UINT8_T pageByteSizeL, UINT8_T pageNumH, UINT8_T pageNumL)
{
	UINT8_T _return = OK_0;
	//---�����״̬
	if (JTAGx->msgState == JTAG_PROG_NONE)
	{
		//---������ģʽ
		_return = JTAG_EnterProg(JTAGx);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		JTAG_RefreshWatch(JTAGx);
		//---FLASH��ղ���
		_return = JTAG_CheckChipFlashEmpty(JTAGx, pageByteSizeH, pageByteSizeL, pageNumH, pageNumL);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
		//---����ʱ����
		JTAG_SetIntervalTime(JTAGx, 100);
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
UINT8_T JTAGLib_CheckChipFlashEmptyLong(JTAG_HandleType* JTAGx, UINT16_T pageByteSize, UINT16_T pageNum)
{
	UINT8_T _return = OK_0;
	//---�����״̬
	if (JTAGx->msgState == JTAG_PROG_NONE)
	{
		//---������ģʽ
		_return = JTAG_EnterProg(JTAGx);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		JTAG_RefreshWatch(JTAGx);
		//---FLASH��ղ���
		_return = JTAG_CheckChipFlashEmptyLong(JTAGx, pageByteSize, pageNum);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
		//---����ʱ����
		JTAG_SetIntervalTime(JTAGx, 100);
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
UINT8_T JTAGLib_CheckChipEepromEmpty(JTAG_HandleType* JTAGx, UINT8_T byteSize, UINT8_T num)
{
	UINT8_T _return = OK_0;
	//---�����״̬
	if (JTAGx->msgState == JTAG_PROG_NONE)
	{
		//---������ģʽ
		_return = JTAG_EnterProg(JTAGx);
	}
	if (_return == OK_0)
	{
		//---ˢ��ʱ��
		JTAG_RefreshWatch(JTAGx);
		//---Eeprom��ղ���
		_return = JTAG_CheckChipEepromEmpty(JTAGx, byteSize, num);
		_return = (_return == OK_0 ? OK_0 : ERROR_2);
		//---����ʱ����
		JTAG_SetIntervalTime(JTAGx, 100);
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
UINT8_T JTAGLib_SetConfigInfo(JTAG_HandleType* JTAGx, UINT8_T* pVal)
{
	return JTAG_SetConfigInfo(JTAGx, pVal);
}
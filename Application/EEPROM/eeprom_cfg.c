#include "eeprom_cfg.h"

//===ȫ�ֱ�������
UINT16_T g_EepromVal[STM32_SECTOR_SIZE / 2];

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void EEPROM_Init(void)
{
#ifdef  FLASH_CR_PSIZE
	LL_FLASH_SetProgramSize(LL_FLASH_PSIZE_16BITS);
#endif

	//---��ȡ�������������ݣ���������ΪEEPROMʹ��
	FLASHTask_ReadHalfWord(EEPROM_START_ADDR, g_EepromVal, (STM32_SECTOR_SIZE / 2));
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT16_T EEPROM_ReadHalfWord(UINT16_T addr)
{
	UINT32_T rAddr = EEPROM_START_ADDR + (addr << 1);
	return LL_FLASH_ReadHalfWord(rAddr);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void EEPROM_ReadHalfWordData(UINT16_T addr, UINT16_T *pVal, UINT16_T length)
{
	UINT32_T rAddr = EEPROM_START_ADDR + (addr << 1);
	FLASHTask_ReadHalfWord(rAddr, pVal, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T EEPROM_WriteHalfWord(UINT16_T addr, UINT16_T val)
{
	UINT32_T wAddr = (addr << 1);
	if (wAddr > STM32_SECTOR_SIZE)
	{
		return ERROR_1;
	}
	wAddr += EEPROM_START_ADDR;
	if (g_EepromVal[addr] == 0xFFFF)
	{
		g_EepromVal[addr] = val;
		LL_FLASH_WriteHalfWord(wAddr, val);
	}
	else
	{
		g_EepromVal[addr] = val;

		//---ɾ����ǰ����
		//LL_FLASH_ErasePage(EEPROM_START_ADDR);
		//---������д����������
		FLASHTask_WriteHalfWordWithErase(EEPROM_START_ADDR, g_EepromVal, (STM32_SECTOR_SIZE / 2));
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:+
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T EEPROM_WriteHalfWordData(UINT16_T addr, UINT16_T *pVal, UINT16_T length)
{
	UINT32_T wAddr = (addr << 1);
	if (wAddr > STM32_SECTOR_SIZE)
	{
		return ERROR_1;
	}
	wAddr += EEPROM_START_ADDR;
	if ((wAddr + length) > EEPROM_END_ADDR)
	{
		return ERROR_2;
	}
	UINT16_T i = 0;
	UINT8_T isEmpty = 0;
	for (i = 0; i < length; i++)
	{
		if (g_EepromVal[addr + i] != 0xFFFF)
		{
			isEmpty = 1;
		}
		g_EepromVal[addr + i] = pVal[i];
	}

	//---�ж�Ҫд������ݵ�λ���ǲ��ǿյ�
	if (isEmpty == 0)
	{
		//---Ҫд�����ݵĵ�ַ�ǿյ�
		FLASHTask_WriteHalfWord(wAddr, pVal, length);
	}
	else
	{
		//---ɾ����ǰ����
		//LL_FLASH_ErasePage(EEPROM_START_ADDR);
		//---������д����������
		FLASHTask_WriteHalfWordWithErase(EEPROM_START_ADDR, g_EepromVal, (STM32_SECTOR_SIZE / 2));
	}
	return OK_0;
}
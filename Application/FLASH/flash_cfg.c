#include "flash_cfg.h"

//===Flash����ռ�
UINT16_T g_FlashVal[STM32_SECTOR_SIZE / 2];

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void FLASH_ReadHalfWord(UINT32_T readAddr, UINT16_T *pVal, UINT16_T length)
{
	UINT16_T i = 0;
	for (i = 0; i < length; i++)
	{
		pVal[i] = LL_FLASH_ReadHalfWord(readAddr);
		readAddr += 2;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void FLASH_WriteHalfWord(UINT32_T writeAddr, UINT16_T *pVal, UINT16_T length)
{
	UINT16_T i = 0;
	for (i = 0; i < length; i++)
	{
		if (pVal[i] != 0xFFFF)
		{
			LL_FLASH_WriteHalfWord(writeAddr, pVal[i]);
		}
		writeAddr += 2;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void FLASH_WriteHalfWordWithErase(UINT32_T writeAddr, UINT16_T *pVal, UINT16_T length)
{
	//---������ַ
	UINT32_T secpos = 0;

	//---������ƫ�Ƶ�ַ(16λ�ּ���)
	UINT16_T secoff = 0;

	//---������ʣ���ַ(16λ�ּ���)
	UINT16_T secremain = 0;
	UINT16_T i = 0;

	//---ȥ��0X08000000 ��ĵ�ַ
	UINT32_T offaddr = 0;

	//---��ַ���ж�
	if (writeAddr < STM32_FLASH_BASE || (writeAddr >= (STM32_FLASH_BASE + 1024 * STM32_FLASH_SIZE)))
	{
		//---�Ƿ���ַ
		return;
	}

	//---����
	LL_FLASH_Unlock();

	//---�����־λ
	LL_FLASH_ClearFlag();

	//---ʵ��ƫ�Ƶ�ַ
	offaddr = writeAddr - STM32_FLASH_BASE;

	//---������ַ
	secpos = offaddr / STM32_SECTOR_SIZE;

	//---�������ڵ�ƫ��(2���ֽ�Ϊ������λ)
	secoff = (offaddr%STM32_SECTOR_SIZE) / 2;

	//---����ʣ��ռ��С
	secremain = STM32_SECTOR_SIZE / 2 - secoff;

	//---�����Ƿ񳬳�����
	if (length <= secremain)
	{
		//---��д����������������ڸ�������Χ
		secremain = length;
	}
	while (1)
	{
		//---������������������
		FLASH_ReadHalfWord((secpos*STM32_SECTOR_SIZE + STM32_FLASH_BASE), g_FlashVal, (STM32_SECTOR_SIZE / 2));

		//---����У��
		for (i = 0; i < secremain; i++)
		{
			//---У������
			if (g_FlashVal[secoff + i] != 0xFFFF)
			{
				//---��Ҫ����
				break;
			}
		}

		//---��Ҫ����
		if (i < secremain)
		{
			//---������������,���������������ѱ�����STMFLASH_BUF
			LL_FLASH_ErasePage((secpos*STM32_SECTOR_SIZE + STM32_FLASH_BASE));

			//---����д������ݸ��Ƶ�STMFLASH_BUF
			for (i = 0; i < secremain; i++)
			{
				g_FlashVal[i + secoff] = pVal[i];
			}

			//---д����������
			FLASH_WriteHalfWord((secpos*STM32_SECTOR_SIZE + STM32_FLASH_BASE), g_FlashVal, (STM32_SECTOR_SIZE / 2));
		}
		else
		{
			//---����Ҫ����,ֱ��д������ʣ������
			FLASH_WriteHalfWord(writeAddr, pVal, secremain);
		}

		//---�ж�д��״̬
		if (length == secremain)
		{
			//---д�������
			break;
		}

		//---д��δ����
		else
		{
			//---������ַ��1
			secpos++;

			//---ƫ��λ��Ϊ0
			secoff = 0;

			//---ָ��ƫ��
			pVal += secremain;

			//---д��ַƫ��(16λ���ݵ�ַ,��Ҫ*2)
			writeAddr += (secremain * 2);

			//---�ֽ�(16λ)���ݼ�
			length -= secremain;

			//---��һ����������д����
			if (length > (STM32_SECTOR_SIZE / 2))
			{
				secremain = STM32_SECTOR_SIZE / 2;
			}

			//---��һ����������д����
			else
			{
				secremain = length;
			}
		}

		//---ι��
		WDT_RESET();
	};

	//---����
	LL_FLASH_Lock();
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ������ȡ��ʹ�ܶ�����
//////////////////////////////////////////////////////////////////////////////
void Flash_LockRead(void)
{
	//---�ر�Ԥʹ��
	LL_FLASH_DisablePrefetch();

	//---��ȡд����
	UINT32_T flashWRP = LL_FLASH_OB_GetWRP();

	//---��ȡ������
	UINT32_T flashRDP = LL_FLASH_OB_GetRDP();

	//---�û�����
	UINT8_T  flashUser = LL_FLASH_OB_GetUser();

	//---���ö�����
	if (flashRDP == LL_OB_RDP_LEVEL_0)
	{
		LL_FLASH_Unlock();
		LL_FLASH_OB_Unlock();
		LL_FLASH_OB_RDP_LevelConfig(LL_OB_RDP_LEVEL_1);
		LL_FLASH_OB_Lock();
		LL_FLASH_Lock();
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ������ȡ����ʹ�ܶ�����
//////////////////////////////////////////////////////////////////////////////
void Flash_UnLockRead(void)
{
	//---�ر�Ԥʹ��
	LL_FLASH_DisablePrefetch();

	//---��ȡд����
	UINT32_T flashWRP = LL_FLASH_OB_GetWRP();

	//---��ȡ������
	UINT32_T flashRDP = LL_FLASH_OB_GetRDP();

	//---�û�����
	UINT8_T  flashUser = LL_FLASH_OB_GetUser();

	//---���������
	if (flashWRP != LL_OB_RDP_LEVEL_0)
	{
		LL_FLASH_Unlock();
		LL_FLASH_OB_Unlock();
		LL_FLASH_OB_RDP_LevelConfig(LL_OB_RDP_LEVEL_0);
		LL_FLASH_OB_Lock();
		LL_FLASH_Lock();
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		������ȡ�豸��Flash�Ĵ�С
//////////////////////////////////////////////////////////////////////////////
UINT32_T Flash_GetSize(void)
{
	return  LL_GetFlashSize();
}
#include "my_malloc.h"

//__align(4)
//===SRAM�ڴ��(4�ֽڶ���)
#pragma pack (4)
	UINT8_T g_MemPool[MEM_MAX_SIZE] = { 0 };
#pragma pack ()
//===SRAM�ڴ��MAP
UINT16_T g_MemMap[MEM_TABLE_SIZE] = { 0 };
//===�ڴ���С
//const UINT32_T g_MemTableSize = MEM_TABLE_SIZE;
//===�ڴ�ֿ��С
//const UINT32_T g_MemBlockSize = MEM_BLOCK_SIZE;
//===�ڴ��ܴ�С
//const UINT32_T g_MemTotalSize = MEM_MAX_SIZE;
//===�ڴ���������
MyMalloc_HandleType g_MyMallocDev =
{
	MyMemInit,			//�ڴ��ʼ��
	MyMemusedRate,		//�ڴ�ʹ����
	g_MemPool,			//�ڴ��
	g_MemMap,			//�ڴ����״̬��
	0,  				//�ڴ����δ����
};

pMyMalloc_HandleType	pMyMallocDev=&g_MyMallocDev;

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� �����ڴ�
//////�������: *des:Ŀ�ĵ�ַ;*src:Դ��ַ;n:��Ҫ���Ƶ��ڴ泤��(�ֽ�Ϊ��λ)
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void MyMemcpy(void *des, void *src, UINT32_T nSize)
{
	UINT8_T *xdes = des;
	UINT8_T *xsrc = src;
	while (nSize--)
	{
		*xdes++ = *xsrc++;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� �����ڴ�
//////�������: *s:�ڴ��׵�ַ;c :Ҫ���õ�ֵ;count:��Ҫ���õ��ڴ��С(�ֽ�Ϊ��λ)
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void MyMemset(void *s, UINT8_T c, UINT32_T nSize)
{
	UINT8_T *xs = s;
	while (nSize--)
	{
		*xs++ = c;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� �ڴ�����ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void MyMemInit(void)
{
	//---�ڴ�״̬����������
	MyMemset(g_MyMallocDev.msgMemMap, 0, MEM_TABLE_SIZE * 2);
	//---�ڴ��������������
	MyMemset(g_MyMallocDev.msgMemPool, 0, MEM_MAX_SIZE);
	//---�ڴ�����ʼ��OK
	g_MyMallocDev.msgMemReady = 1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� ��ȡ�ڴ�ʹ����
//////�������:
//////�������: ����ֵ:ʹ����(0~100)
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MyMemusedRate(void)
{
	UINT32_T used = 0;
	UINT32_T i = 0;
	for (i = 0;i < MEM_TABLE_SIZE;i++)
	{
		if (g_MyMallocDev.msgMemMap[i])
		{
			used++;
		}
	}
	return (used * 100) / (MEM_TABLE_SIZE);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��ڴ����(�ڲ�����)
//////�������: memx:�����ڴ��;size:Ҫ������ڴ��С(�ֽ�)
//////�������: ����ֵ:0XFFFFFFFF,�������;����,�ڴ�ƫ�Ƶ�ַ
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT32_T MyMemMalloc(UINT32_T size)
{
	signed long offset = 0;
	//---��Ҫ���ڴ����
	UINT16_T nmemb = 0;
	//---�������ڴ����
	UINT16_T cmemb = 0;
	UINT32_T i = 0;
	//---δ��ʼ��,��ִ�г�ʼ��
	if (!g_MyMallocDev.msgMemReady)
	{
		g_MyMallocDev.msgInit();
	}
	//---����Ҫ����
	if (size == 0)
	{
		return 0xFFFFFFFF;
	}
	//---��ȡ��Ҫ����������ڴ����
	nmemb = size / MEM_BLOCK_SIZE;
	//---�ǲ���������
	if (size% MEM_BLOCK_SIZE)
	{
		nmemb++;
	}
	//---���������ڴ������
	for (offset = MEM_TABLE_SIZE - 1;offset >= 0;offset--)
	{
		//---�������ڴ��������
		if (!g_MyMallocDev.msgMemMap[offset])
		{
			cmemb++;
		}
		else
		{
			//---�����ڴ������
			cmemb = 0;
		}
		//---�ҵ�������nmemb�����ڴ��
		if (cmemb == nmemb)
		{
			//---��ע�ڴ��ǿ�
			for (i = 0;i < nmemb;i++)
			{
				g_MyMallocDev.msgMemMap[offset + i] = nmemb;
			}
			//---����ƫ�Ƶ�ַ
			return (offset* MEM_BLOCK_SIZE);
		}
	}
	//---δ�ҵ����Ϸ����������ڴ��
	return 0XFFFFFFFF;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��ͷ��ڴ�(�ڲ�����)
//////�������: offset:�ڴ��ַƫ��
//////�������: ����ֵ:0,�ͷųɹ�;1,�ͷ�ʧ��; 2,��ַ����
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MyMemFree(UINT32_T offset)
{
	int i = 0;
	//---δ��ʼ��,��ִ�г�ʼ��
	if (!g_MyMallocDev.msgMemReady)
	{
		g_MyMallocDev.msgInit();
		//---δ��ʼ��
		return 1;
	}
	//---ƫ�����ڴ����
	if (offset < MEM_MAX_SIZE)
	{
		//---ƫ�������ڴ�����
		int index = offset / MEM_BLOCK_SIZE;
		//---�ڴ������
		int nmemb = g_MyMallocDev.msgMemMap[index];
		//---�ڴ������
		for (i = 0;i < nmemb;i++)
		{
			g_MyMallocDev.msgMemMap[index + i] = 0;
		}
		return 0;
	}
	else
	{
		//---ƫ�Ƴ�����.
		return 2;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� �ͷ��ڴ�(�ⲿ����)
//////�������:  pMemAddr:�ڴ��׵�ַ
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void MyFree(void *pMemAddr)
{
	UINT32_T offset;
	if (pMemAddr == NULL)
	{
		//---��ַΪ0
		return;
	}
	offset = (UINT32_T)pMemAddr - (UINT32_T)g_MyMallocDev.msgMemPool;
	//---�ͷ��ڴ�
	MyMemFree(offset);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� �����ڴ�(�ⲿ����)
//////�������:  size:�ڴ��С(�ֽ�)
//////�������:  ����ֵ:���䵽���ڴ��׵�ַ.
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void *MyMalloc(UINT32_T nSize)
{
	UINT32_T offset;
	//---�����ڴ��С
	offset = MyMemMalloc(nSize);
	if (offset == 0XFFFFFFFF)
	{
		//---����ʧ�ܣ����ؿ�
		return NULL;
	}
	else
	{
		return (void*)((UINT32_T)g_MyMallocDev.msgMemPool + offset);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����·����ڴ�(�ⲿ����)
//////�������: *pMemAddr:���ڴ��׵�ַ;size:Ҫ������ڴ��С(�ֽ�)
//////�������: ����ֵ:�·��䵽���ڴ��׵�ַ.
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void *MyRealloc(void *pMemAddr, UINT32_T nSize)
{
	UINT32_T offset;
	//---�����ڴ��С
	offset = MyMemMalloc(nSize);
	//---У���ڴ��Ƿ�����ɹ�
	if (offset == 0XFFFFFFFF)
	{
		//---����ʧ�ܣ����ؿ�
		return NULL;
	}
	else
	{
		//---�������ڴ����ݵ����ڴ�
		MyMemcpy((void*)((UINT32_T)g_MyMallocDev.msgMemPool + offset), pMemAddr, nSize);
		//---�ͷž��ڴ�
		MyFree(pMemAddr);
		//---�������ڴ��׵�ַ
		return (void*)((UINT32_T)g_MyMallocDev.msgMemPool + offset);
	}
}
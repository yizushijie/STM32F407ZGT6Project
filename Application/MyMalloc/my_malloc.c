#include "my_malloc.h"

//__align(4)
//===SRAM�ڴ��(4�ֽڶ���)
#pragma pack (4)
UINT8_T g_MemPool[MEM_MAX_SIZE] = { 0 };
#pragma pack ()

//===SRAM�ڴ��MAP
UINT16_T g_MemMap[MEM_TABLE_SIZE] = { 0 };

//===�ڴ���С
const UINT32_T g_MemTableSize = MEM_TABLE_SIZE;

//===�ڴ�ֿ��С
const UINT32_T g_MemBlockSize = MEM_BLOCK_SIZE;

//===�ڴ��ܴ�С
const UINT32_T g_MemTotalSize = MEM_MAX_SIZE;

//===�ڴ���������
MyMalloc_HandlerType g_MyMallcoDev =
{
	MyMemInit,			//�ڴ��ʼ��
	MyMemusedRate,		//�ڴ�ʹ����
	g_MemPool,			//�ڴ��
	g_MemMap,			//�ڴ����״̬��
	0,  				//�ڴ����δ����
};

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
	MyMemset(g_MyMallcoDev.msgMemMap, 0, g_MemTableSize * 2);

	//---�ڴ��������������
	MyMemset(g_MyMallcoDev.msgMemPool, 0, g_MemTotalSize);

	//---�ڴ�����ʼ��OK
	g_MyMallcoDev.msgMemReady = 1;
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
	for (i = 0;i < g_MemTableSize;i++)
	{
		if (g_MyMallcoDev.msgMemMap[i])
		{
			used++;
		}
	}
	return (used * 100) / (g_MemTableSize);
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
	if (!g_MyMallcoDev.msgMemReady)
	{
		g_MyMallcoDev.init();
	}

	//---����Ҫ����
	if (size == 0)
	{
		return 0xFFFFFFFF;
	}

	//---��ȡ��Ҫ����������ڴ����
	nmemb = size / g_MemBlockSize;
	if (size%g_MemBlockSize)nmemb++;

	//---���������ڴ������
	for (offset = g_MemTableSize - 1;offset >= 0;offset--)
	{
		//---�������ڴ��������
		if (!g_MyMallcoDev.msgMemMap[offset])
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
				g_MyMallcoDev.msgMemMap[offset + i] = nmemb;
			}

			//---����ƫ�Ƶ�ַ
			return (offset*g_MemBlockSize);
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
	if (!g_MyMallcoDev.msgMemReady)
	{
		g_MyMallcoDev.init();

		//---δ��ʼ��
		return 1;
	}

	//---ƫ�����ڴ����
	if (offset < g_MemTotalSize)
	{
		//---ƫ�������ڴ�����
		int index = offset / g_MemBlockSize;

		//---�ڴ������
		int nmemb = g_MyMallcoDev.msgMemMap[index];

		//---�ڴ������
		for (i = 0;i < nmemb;i++)
		{
			g_MyMallcoDev.msgMemMap[index + i] = 0;
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
	offset = (UINT32_T)pMemAddr - (UINT32_T)g_MyMallcoDev.msgMemPool;

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
		return (void*)((UINT32_T)g_MyMallcoDev.msgMemPool + offset);
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
	if (offset == 0XFFFFFFFF)
	{
		//---����ʧ�ܣ����ؿ�
		return NULL;
	}
	else
	{
		//---�������ڴ����ݵ����ڴ�
		MyMemcpy((void*)((UINT32_T)g_MyMallcoDev.msgMemPool + offset), pMemAddr, nSize);

		//---�ͷž��ڴ�
		MyFree(pMemAddr);

		//---�������ڴ��׵�ַ
		return (void*)((UINT32_T)g_MyMallcoDev.msgMemPool + offset);
	}
}
#ifndef MY_MALLOC_H_
#define MY_MALLOC_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	//// �Զ�����ڴ������
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	//////////////////////////////////////////////////////////////////////////////////////

	//===�ڴ���СΪ32�ֽ�
	#define MEM_BLOCK_SIZE							32	
	//===�������ڴ� 42K
	#define MEM_MAX_SIZE							10*1024	
	//===�ڴ���С
	#define MEM_TABLE_SIZE							( MEM_MAX_SIZE/MEM_BLOCK_SIZE )
	
	//===�ṹ�嶨��
	typedef struct _MyMalloc_HandleType				MyMalloc_HandleType;
	//===ָ��ṹ�嶨��
	typedef struct _MyMalloc_HandleType				*pMyMalloc_HandleType;
	//===�ڴ���������
	struct _MyMalloc_HandleType
	{
		void		(*msgInit)(void);																					//��ʼ��
		UINT8_T		(*msgUsedRate)(void);	  																			//�ڴ�ʹ����
		UINT8_T		*msgMemPool;																						//�ڴ��
		UINT16_T	*msgMemMap; 																						//�ڴ����״̬��
		UINT8_T		msgMemReady; 																						//�ڴ�����Ƿ������0---δ׼���ã�1׼����
	};

	//===�ⲿ���ò���
	extern MyMalloc_HandleType					g_MyMallocDev;															//��myMallco.c���涨��
	extern pMyMalloc_HandleType					pMyMallocDev;
	//===��������
	void MyMemcpy(void *des, void *src, UINT32_T nSize);
	void MyMemset(void *s, UINT8_T c, UINT32_T nSize);
	void MyMemInit(void);
	UINT8_T MyMemusedRate(void);
	UINT32_T MyMemMalloc(UINT32_T size);
	UINT8_T MyMemFree(UINT32_T offset);
	void MyFree(void *pMemAddr);
	void *MyMalloc(UINT32_T nSize);
	void *MyRealloc(void *pMemAddr, UINT32_T nSize);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*MY_MALLOC_H_ */
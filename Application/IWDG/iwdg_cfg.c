#include "iwdg_cfg.h"

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ���� �ڳ�ʼ�����Ź���ʱ����Ҫע��ر�ȫ���жϣ�����ᵼ�¿��Ź�������ʧ�ܣ����ǼĴ���������Ӱ��
//////////////////////////////////////////////////////////////////////////////
UINT8_T IWDG_Init(void)
{
	//---�ر��ж�
	CLI();
	//---ʹ�ܿ��Ź�
	LL_IWDG_Enable(IWDG);
	//---ʹ��Ԥ��Ƶ�Ĵ�������װ�ؼĴ�����д��ȡ���Ĵ�����д������
	LL_IWDG_EnableWriteAccess(IWDG);
	//--->>>�������Ź�ʱ�俪ʼ
	#if(USE_IWDG_TIME==IWDG_500MS)	//---0.2ms
		//---����Ԥ��Ƶ��ֵ
		LL_IWDG_SetPrescaler(IWDG, LL_IWDG_PRESCALER_8);
		//---������װ�ؼĴ���ֵ
		LL_IWDG_SetReloadCounter(IWDG, 2500);
	#elif(USE_IWDG_TIME==IWDG_1000MS)	//---0.4ms
		//---����Ԥ��Ƶ��ֵ
		LL_IWDG_SetPrescaler(IWDG, LL_IWDG_PRESCALER_16);
		//---������װ�ؼĴ���ֵ
		LL_IWDG_SetReloadCounter(IWDG, 2500);
	#elif(USE_IWDG_TIME==IWDG_1500MS)	//---0.8ms
		//---����Ԥ��Ƶ��ֵ
		LL_IWDG_SetPrescaler(IWDG, LL_IWDG_PRESCALER_32);
		//---������װ�ؼĴ���ֵ
		LL_IWDG_SetReloadCounter(IWDG, 1875);
	#elif(USE_IWDG_TIME==IWDG_2000MS)	//---1.6ms
		//---����Ԥ��Ƶ��ֵ
		LL_IWDG_SetPrescaler(IWDG, LL_IWDG_PRESCALER_64);
		//---������װ�ؼĴ���ֵ
		LL_IWDG_SetReloadCounter(IWDG, 1250);
	#elif(USE_IWDG_TIME==IWDG_3000MS)	//---1.6ms
		//---����Ԥ��Ƶ��ֵ
		LL_IWDG_SetPrescaler(IWDG, LL_IWDG_PRESCALER_64);
		//---������װ�ؼĴ���ֵ
		LL_IWDG_SetReloadCounter(IWDG, 1875);
	#elif(USE_IWDG_TIME==IWDG_4000MS)	//---1.6ms
		//---����Ԥ��Ƶ��ֵ
		LL_IWDG_SetPrescaler(IWDG, LL_IWDG_PRESCALER_64);
		//---������װ�ؼĴ���ֵ
		LL_IWDG_SetReloadCounter(IWDG, 2500);
	#elif(USE_IWDG_TIME==IWDG_5000MS)	//---3.2ms
		//---����Ԥ��Ƶ��ֵ
		LL_IWDG_SetPrescaler(IWDG, LL_IWDG_PRESCALER_128);
		//---������װ�ؼĴ���ֵ
		LL_IWDG_SetReloadCounter(IWDG, 1563);
	#elif(USE_IWDG_TIME==IWDG_6000MS)//---3.2ms
		//---����Ԥ��Ƶ��ֵ
		LL_IWDG_SetPrescaler(IWDG, LL_IWDG_PRESCALER_128);
		//---������װ�ؼĴ���ֵ
		LL_IWDG_SetReloadCounter(IWDG, 1875);
	#elif(USE_IWDG_TIME==IWDG_7000MS)	//---3.2ms
		//---����Ԥ��Ƶ��ֵ
		LL_IWDG_SetPrescaler(IWDG, LL_IWDG_PRESCALER_128);
		//---������װ�ؼĴ���ֵ
		LL_IWDG_SetReloadCounter(IWDG, 2188);
	#elif(USE_IWDG_TIME==IWDG_8000MS)	//---3.2ms
		//---����Ԥ��Ƶ��ֵ
		LL_IWDG_SetPrescaler(IWDG, LL_IWDG_PRESCALER_128);
		//---������װ�ؼĴ���ֵ
		LL_IWDG_SetReloadCounter(IWDG, 2500);
	#elif(USE_IWDG_TIME==IWDG_9000MS)	//---6.4ms
		//---����Ԥ��Ƶ��ֵ
		LL_IWDG_SetPrescaler(IWDG, LL_IWDG_PRESCALER_256);
		//---������װ�ؼĴ���ֵ
		LL_IWDG_SetReloadCounter(IWDG, 1407);
	#elif(USE_IWDG_TIME==IWDG_10000MS)	//---6.4ms
		//---����Ԥ��Ƶ��ֵ
		LL_IWDG_SetPrescaler(IWDG, LL_IWDG_PRESCALER_256);
		//---������װ�ؼĴ���ֵ
		LL_IWDG_SetReloadCounter(IWDG, 1563);
	#else								//---1.6ms
		//---����Ԥ��Ƶ��ֵ
		LL_IWDG_SetPrescaler(IWDG, LL_IWDG_PRESCALER_64);
		//---������װ�ؼĴ���ֵ
		LL_IWDG_SetReloadCounter(IWDG, 625);
	#endif
	//---<<<�������Ź�ʱ�����
	//---�ȴ�׼�����
	while (LL_IWDG_IsReady(IWDG) != 1);
	//---��λ���Ź�
	LL_IWDG_ReloadCounter(IWDG);
	//---�����ж�
	SEI();
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T IWDG_DeInit(void)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ� ���Ź���λ����
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T IWDG_Reset(void)
{
	//---��λ���Ź�
	LL_IWDG_ReloadCounter(IWDG);
	return OK_0;
}
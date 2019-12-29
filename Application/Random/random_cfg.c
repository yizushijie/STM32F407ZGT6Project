#include "random_cfg.h"

//---����ȫ�ֱ���
#ifdef RNG
volatile UINT32_T g_HASH_RNG_Val = 0;
#endif
///////////////////////////////////////////////////////////////////////////////
//////��	   ����void RandomCfg_Init(void)
//////��	   �ܣ�������ĳ�ʼ��
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
void Random_Init(UINT8_T isEnableIT)
{
#ifdef RNG
    LL_RNG_DeInit(RNG);    
	//---ʹ�����������ʱ��
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_RNG);
	//---�Ƿ�ʹ���жϺ���
	if (isEnableIT!=0)
	{
		//---HASH_RNG_IRQn�ж�����---�жϵȼ�����15,0(������ȼ�)
		NVIC_SetPriority(HASH_RNG_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 15, 0));
		//---ʹ���ж�
		NVIC_EnableIRQ(HASH_RNG_IRQn);
		//---ʹ��������ж�
		LL_RNG_EnableIT(RNG);
	}
	//---ʹ�����������
	LL_RNG_Enable(RNG);
	//---�ȴ����������
	while (LL_RNG_IsActiveFlag_DRDY(RNG) != 1)
	{
		WDT_RESET();
	}
	g_HASH_RNG_Val = 0;
#endif
}
///////////////////////////////////////////////////////////////////////////////
//////��	   ����void RandomCfg_DeInit(void)
//////��	   �ܣ��������ע��
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
void Random_DeInit(void)
{
#ifdef RNG
	//---ʱ�����߲�ʹ��
	LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_RNG);
	//---ע��������ĳ�ʼ��
	LL_RNG_DeInit(RNG);
	//---��ʹ��������ж�
	NVIC_DisableIRQ(HASH_RNG_IRQn);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT32_T Random_GetVal(void)
{
#ifdef RNG
	//---�ж��Ƿ�ʹ��������ж�
	if (LL_RNG_IsEnabledIT(RNG))
	{
		return g_HASH_RNG_Val;
	}
	else
	{
		//---�ȴ����������
		while (LL_RNG_IsActiveFlag_DRDY(RNG) != 1);
		//---��ȡ�����������
		return LL_RNG_ReadRandData32(RNG);
	}
#else
	return rand();
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����UINT32_T RandomCfg_GetRandomRang(UINT32_T minVal,UINT32_T maxVal)
//////��	   �ܣ�������ָ����Сֵ��ָ�����ֵ��Χ�������
//////�������:
//////�������: ��ǰ�������
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT32_T Random_GetRand(UINT32_T minVal, UINT32_T maxVal)
{
	//---��ȡ��ǰ�������
	UINT32_T randomVal = 0;
	//---����ֵ
	UINT32_T _return = 0;
	//---�жϵ��õ����������
#ifdef RNG
	randomVal = Random_GetVal();
#else
	//---�ж�ѡȡ�����������
	if (minVal < maxVal)
	{
		randomVal = maxVal;
	}
	else
	{
		randomVal = minVal;
	}
	//---����������ӷ�Χ
	srand(randomVal);
	//---��ȡ�����
	randomVal = rand();
#endif
	//---���㷵�ص������
	if (minVal < maxVal)
	{
		_return = randomVal % (maxVal - minVal + 1) + minVal;
	}
	else
	{
		_return = randomVal % (minVal - maxVal + 1) + maxVal;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������жϴ�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Random_IRQTask(void)
{
	#ifdef RNG
		//---�������Ӵ���
		if (LL_RNG_IsActiveFlag_SEIS(RNG))
		{
			//---�������Ӵ����־
			LL_RNG_ClearFlag_SEIS(RNG);
			//---����ʹ�������
			LL_RNG_Disable(RNG);
			//---����ʹ��ʹ�������
			LL_RNG_Enable(RNG);
		}
		//---����ʱ�Ӵ���
		if (LL_RNG_IsActiveFlag_CEIS(RNG))
		{
			//---����ʱ�Ӵ����־
			LL_RNG_ClearFlag_CEIS(RNG);
		}
		//---���ݾ���
		if (LL_RNG_IsActiveFlag_DRDY(RNG))
		{
			g_HASH_RNG_Val = LL_RNG_ReadRandData32(RNG);
		}
	#endif
}
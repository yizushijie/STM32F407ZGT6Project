#include"wwdg_cfg.h"

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T WWDG_Init(UINT8_T wr, UINT32_T prv)
{
	//---ʹ��WWDG��ʱ��
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_WWDG);
	//---���õݼ���������ֵ
	LL_WWDG_SetCounter(WWDG, 0x7F);
	//---����Ԥ��Ƶ����ֵ
	LL_WWDG_SetPrescaler(WWDG, prv);
	//---�����ϴ���ֵ
	LL_WWDG_SetWindow(WWDG, wr);
	//---�����ж�
	NVIC_SetPriority(WWDG_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
	//---ʹ���ж�
	NVIC_EnableIRQ(WWDG_IRQn);
	//---ʹ��WWDG
	LL_WWDG_Enable(WWDG);
	//---�����ǰ�����жϱ�־
	LL_WWDG_ClearFlag_EWKUP(WWDG);
	//---ʹ��WWDG�ж�
	LL_WWDG_EnableIT_EWKUP(WWDG);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T WWDG_DeInit(void)
{
	LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_WWDG);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T WWDG_Reset(void)
{
	//---ˢ�µݼ���������ֵ
	LL_WWDG_SetCounter(WWDG, 0x7F);
	return OK_0;
}
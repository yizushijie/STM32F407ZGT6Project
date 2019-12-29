#include "css_cfg.h"

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
void CSS_Init(void)
{
	if (LL_RCC_HSE_IsReady() == 1)
	{
		//---ʹ��HSEʱ�Ӱ�ȫϵͳ
		LL_RCC_HSE_EnableCSS();
	}
	/* NonMaskableInt_IRQn interrupt configuration */
	NVIC_SetPriority(NonMaskableInt_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
	/* RCC_IRQn interrupt configuration */
	NVIC_SetPriority(RCC_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));

	//---ʹ���ж�
	NVIC_EnableIRQ(NonMaskableInt_IRQn);

	//---ʹ���ж�
	NVIC_EnableIRQ(RCC_IRQn);
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
void CSS_DeInit(void)
{
	//---��ʹ���ж�
	NVIC_DisableIRQ(NonMaskableInt_IRQn);

	//---��ʹ���ж�
	NVIC_DisableIRQ(RCC_IRQn);
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   �������ⲿ���񱻶�·������������NMI�жϺ���
//////////////////////////////////////////////////////////////////////////////
void CSS_NMI_IRQ(void)
{
	if (LL_RCC_IsActiveFlag_HSECSS() != 0)
	{
		//---ʹ���ⲿ����
		LL_RCC_HSE_Enable();

		//---ʹ��HSE�����ж�
		LL_RCC_EnableIT_HSERDY();

		//---���ʱ�Ӱ�ȫϵͳ���жϹ���λ
		LL_RCC_ClearFlag_HSECSS();
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ������HSE�ָ�����ʱ����ú���
//////////////////////////////////////////////////////////////////////////////
void CSS_RCC_IRQ(void)
{
	if (LL_RCC_IsActiveFlag_HSERDY() != 0)
	{
		//---�ر�HSE�����ж�
		LL_RCC_DisableIT_HSERDY();

		//---���HSE�����жϱ�־λ
		LL_RCC_ClearFlag_HSERDY();

		//---ϵͳ��λ
		SOFT_RESET();
	}
}
#include "pvd_cfg.h"

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void PVD_Init(UINT32_T pwrLevel)
{
	//---PWRʱ��
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

	//---�ɱ�̵�ѹ����жϵȼ�
	NVIC_SetPriority(PVD_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));

	//---���õ�����ȼ�
	LL_PWR_SetPVDLevel(pwrLevel);

	//--- PVD���ӵ��ж���16��
	//--- Rising---��ʾ��ѹ�Ӹ��½��������趨��ֵʱ�����ж�
	//--- Falling---��ʾ��ѹ�ӵ������������趨��ֵʱ�����ж�
	//--- Rising_Falling---��ʾ��ѹ�������½�Խ���趨��ֵʱ�������ж�

	LL_EXTI_InitTypeDef EXTI_InitStruct = { 0 };
	EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_16;
	EXTI_InitStruct.LineCommand = ENABLE;
	EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
	EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
	LL_EXTI_Init(&EXTI_InitStruct);

	//---ʹ�ܵ�����
	LL_PWR_EnablePVD();
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void PVD_DeInit(void)
{
	LL_PWR_DeInit();
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void PVD_IRQTask(void)
{
	
}
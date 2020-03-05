#include "hw_cfg.h"

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void HardWare_Init(void)
{
	//---ʹ��GPIO��ʱ��
	#ifndef  USE_FULL_GPIO
	GPIOTask_Clock(RST_HEN_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(RST_LEN_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(RST_NEN_PORT, PERIPHERAL_CLOCK_ENABLE);
	#endif
	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;																																		//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;																																//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;																															//---���ģʽ---�������
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;																																			//---����
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;																																		//---�˿ڸ���ģʽ
#endif
	//---LEN---���Ϊ��
	GPIO_InitStruct.Pin = RST_LEN_BIT;
	LL_GPIO_Init(RST_LEN_PORT, &GPIO_InitStruct);
	RST_LEN_OUT_0;
	//---HEN---���Ϊ��
	GPIO_InitStruct.Pin = RST_HEN_BIT;
	LL_GPIO_Init(RST_HEN_PORT, &GPIO_InitStruct);
	RST_HEN_OUT_0;
	//---LEN---���Ϊ��
	GPIO_InitStruct.Pin = RST_NEN_BIT;
	LL_GPIO_Init(RST_NEN_PORT, &GPIO_InitStruct);
	RST_NEN_OUT_0;
}
#include "led_cfg.h"

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void LEDWork_Init(void)
{
	#ifndef  USE_FULL_GPIO
	GPIOTask_Clock(LED_WORK_PORT, PERIPHERAL_CLOCK_ENABLE);
	#endif

	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	//---GPIO�ĳ�ʼ��
	GPIO_InitStruct.Pin = LED_WORK_BIT;								//---��Ӧ��GPIO������
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;						//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;					//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;			//---���ģʽ---�������
	GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;						//---����
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---�˿ڸ���ģʽ
#endif
	//---����ָʾ�Ƶĳ�ʼ��
	LL_GPIO_Init(LED_WORK_PORT, &GPIO_InitStruct);
	LED_WORK_OUT_0;
	//---ע�����Ƴ���
	SysTickTask_CreateTickTask(LEDWork_Task);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void LEDWork_Task(void)
{
	static UINT32_T ledCount = 0;
	ledCount++;
	if (ledCount > 500)
	{
		ledCount = 0;
		LED_WORK_OUT_C;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void LED_Init(void)
{
	LEDWork_Init();
}
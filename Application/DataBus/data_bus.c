#include "data_bus.h"

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void DataBus_Init(void)
{
	#ifndef  USE_FULL_GPIO
	GPIOTask_Clock(DATA_BUS_DIR_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(DATA_BUS_OE_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(DATA_BUS_PORT, PERIPHERAL_CLOCK_ENABLE);
	#endif
	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;																																		//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;																															//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;																															//---���ģʽ---�������
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;																																			//---����
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;																																		//---�˿ڸ���ģʽ
#endif
	//---DATA_OE---���Ϊ�ߣ���ƽת��оƬΪ����̬
	GPIO_InitStruct.Pin = DATA_BUS_OE_BIT;
	LL_GPIO_Init(DATA_BUS_OE_PORT, &GPIO_InitStruct);
	//---DATA_DIR---���Ϊ�ߣ���ƽת��оƬΪ����̬
	GPIO_InitStruct.Pin = DATA_BUS_DIR_BIT;
	LL_GPIO_Init(DATA_BUS_DIR_PORT, &GPIO_InitStruct);
	DATA_BUS_TO_HZ;

	//---TRIG_PULSE---���Ϊ�ߣ�
	GPIO_InitStruct.Pin = TRIG_PULSE_BIT;
	LL_GPIO_Init(TRIG_PULSE_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(TRIG_PULSE_PORT, TRIG_PULSE_BIT);
	//---TRIG_OE---���Ϊ�ͣ���ƽת��оƬΪ���
	GPIO_InitStruct.Pin = TRIG_OE_BIT;
	LL_GPIO_Init(TRIG_OE_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(TRIG_OE_PORT, TRIG_OE_BIT);

	//---HVPP_DATA---����Ϊ��
	GPIO_InitStruct.Pin = DATA_BUS_BIT;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	LL_GPIO_Init(DATA_BUS_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(DATA_BUS_PORT, DATA_BUS_BIT);

	DATA_BUS_TO_HOST;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���������Ϊ��ȡģʽ
//////�������: isReadDir---0�л�����Ϊ��ȡģʽ��1---��ȡ��������
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DataBus_Read(void)
{
	UINT8_T _return = 0;
	UINT8_T temp= DATA_BUS_STATE;
	//---��ȡ����
	_return |= ((temp&0x80) != 0 ? 0x80 : 0x00);
	_return |= ((temp&0x40) != 0 ? 0x40 : 0x00);
	_return |= ((temp&0x20) != 0 ? 0x20 : 0x00);
	_return |= ((temp&0x10) != 0 ? 0x10 : 0x00);
	_return |= ((temp&0x08) != 0 ? 0x08 : 0x00);
	_return |= ((temp&0x04) != 0 ? 0x04 : 0x00);
	_return |= ((temp&0x02) != 0 ? 0x02 : 0x00);
	_return |= ((temp&0x01) != 0 ? 0x01 : 0x00);
	return _return;
}
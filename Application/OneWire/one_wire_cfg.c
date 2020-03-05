#include "one_wire_cfg.h"

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T OneWire_Init(OneWire_HandleType *OneWirex, void(*pFuncDelayus)(UINT32_T delay))
{
	//---ʹ�ܶ˿�ʱ��
	#ifndef  USE_FULL_GPIO
	GPIOTask_Clock(OneWirex->msgDAT.msgPort, PERIPHERAL_CLOCK_ENABLE);
	#endif
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	//---GPIO�ĳ�ʼ��
	GPIO_InitStruct.Pin = OneWirex->msgDAT.msgBit;												//---��Ӧ��GPIO������
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;														//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;											//---GPIO���ٶ�
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;											//---���ģʽ---��©���
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;															//---����ʹ��
	//---��ʼ���˿�
	LL_GPIO_Init(OneWirex->msgDAT.msgPort, &GPIO_InitStruct);
	//---�˿�����ߵ�ƽ
	GPIO_OUT_1(OneWirex->msgDAT.msgPort, OneWirex->msgDAT.msgBit);
	//---��ʱ����
	(pFuncDelayus != NULL)?(OneWirex->pMsgDelayus = pFuncDelayus):(OneWirex->pMsgDelayus = DelayTask_us);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T OneWire_DeInit(OneWire_HandleType *OneWirex)
{
	LL_GPIO_DeInit(OneWirex->msgDAT.msgPort);
	GPIO_OUT_1(OneWirex->msgDAT.msgPort, OneWirex->msgDAT.msgBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T OneWire_START(OneWire_HandleType *OneWirex)
{
	UINT8_T _return = OK_0;
	//---����Ϊ����������
	GPIO_OUT_0(OneWirex->msgDAT.msgPort, OneWirex->msgDAT.msgBit);
	//>=480
	OneWirex->pMsgDelayus(500);
	//---����ߵ�ƽ
	GPIO_OUT_1(OneWirex->msgDAT.msgPort, OneWirex->msgDAT.msgBit);
	//15us~60us֮��
	OneWirex->pMsgDelayus(50);
	_return = GPIO_GET_STATE(OneWirex->msgDAT.msgPort, OneWirex->msgDAT.msgBit);
	//60us~240us
	OneWirex->pMsgDelayus(200);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T OneWire_WriteBit(OneWire_HandleType *OneWirex, UINT8_T bitVal)
{
	//---�������ߣ�ǿ������
	GPIO_OUT_0(OneWirex->msgDAT.msgPort, OneWirex->msgDAT.msgBit);
	//=4
	OneWirex->pMsgDelayus(4);
	//---��������
	if (bitVal)
	{
		//---�ͷ�����
		GPIO_OUT_1(OneWirex->msgDAT.msgPort, OneWirex->msgDAT.msgBit);
	}
	//=60us
	OneWirex->pMsgDelayus(50);
	//---�ͷ�����
	GPIO_OUT_1(OneWirex->msgDAT.msgPort, OneWirex->msgDAT.msgBit);
	//=4
	OneWirex->pMsgDelayus(4);
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T OneWire_ReadBit(OneWire_HandleType *OneWirex)
{
	UINT8_T _return = 0;
	//---��������,ǿ������
	GPIO_OUT_0(OneWirex->msgDAT.msgPort, OneWirex->msgDAT.msgBit);
	//=8
	OneWirex->pMsgDelayus(8);
	//---�ͷ�����
	GPIO_OUT_1(OneWirex->msgDAT.msgPort, OneWirex->msgDAT.msgBit);
	//=14
	OneWirex->pMsgDelayus(14);
	//---��ȡ����
	/*if (GPIO_GET_STATE(OneWirex->msgDAT.msgGPIOPort, OneWirex->msgDAT.msgGPIOBit))
	{
		_return = 1;
	}*/
	_return=((GPIO_GET_STATE(OneWirex->msgDAT.msgPort, OneWirex->msgDAT.msgBit) != 0x00) ? 1 : 0);
	//=40
	OneWirex->pMsgDelayus(40);
	//---�ͷ�����
	GPIO_OUT_1(OneWirex->msgDAT.msgPort, OneWirex->msgDAT.msgBit);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T OneWire_WriteByte(OneWire_HandleType *OneWirex, UINT8_T val)
{
	UINT8_T i = 0;
	for (i = 0; i < 8; i++)
	{
		//---�ȷ��͵�λ����
		OneWire_WriteBit(OneWirex, (val & 0x01));
		val >>= 1;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T OneWire_ReadByte(OneWire_HandleType *OneWirex)
{
	UINT8_T _return = 0, i = 0;
	for (i = 0; i < 8; i++)
	{
		_return |= (OneWire_ReadBit(OneWirex) << i);
	}
	//=5
	OneWirex->pMsgDelayus(5);
	return _return;
}
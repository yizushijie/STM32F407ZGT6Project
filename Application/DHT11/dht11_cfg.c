#include "dht11_cfg.h"

//---��������
DHT11_HandlerType g_Dht11Device0 = { 0 };
pDHT11_HandlerType pDht11Device0 = &g_Dht11Device0;

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:DHT11x
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_Device0_Init(DHT11_HandlerType *DHTxx)
{
	DHTxx->msgSTATE=DHT11_READ_OK;
	DHTxx->msgDAT.msgGPIOBit = LL_GPIO_PIN_14;
	DHTxx->msgDAT.msgGPIOPort = GPIOB;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_Device1_Init(DHT11_HandlerType *DHTxx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_Device2_Init(DHT11_HandlerType *DHTxx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_GPIO_Init(DHT11_HandlerType *DHTxx)
{
	//---ʹ�ܶ˿�ʱ��
	GPIOTask_Clock(DHTxx->msgDAT.msgGPIOPort, 1);
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	//---GPIO�ĳ�ʼ��
	GPIO_InitStruct.Pin = DHTxx->msgDAT.msgGPIOBit;													//---��Ӧ��GPIO������
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;														//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;												//---GPIO���ٶ�
	GPIO_InitStruct.OutputType =LL_GPIO_OUTPUT_OPENDRAIN;											//---���ģʽ---��©���
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;															//---����ʹ��
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;														//---�˿ڸ���ģʽ
#endif
	//---��ʼ���˿�
	LL_GPIO_Init(DHTxx->msgDAT.msgGPIOPort, &GPIO_InitStruct);
	GPIO_OUT_1(DHTxx->msgDAT.msgGPIOPort, DHTxx->msgDAT.msgGPIOBit);
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_Init(DHT11_HandlerType *DHTxx, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void))
{
	//---ʹ�õ�DHT11�Ķ˿�
	if ((DHTxx != NULL) && (DHTxx == DHT11_TASK_ONE))
	{
		DHT11_Device0_Init(DHTxx);
	}
	else if ((DHTxx != NULL) && (DHTxx == DHT11_TASK_TWO))
	{
		DHT11_Device1_Init(DHTxx);
	}
	else if ((DHTxx != NULL) && (DHTxx == DHT11_TASK_THREE))
	{
		DHT11_Device2_Init(DHTxx);
	}
	else
	{
		return ERROR_1;
	}
	//---GPIO�ĳ�ʼ��
	DHT11_GPIO_Init(DHTxx);
	//---us��ʱ
	if (pFuncDelayus != NULL)
	{
		DHTxx->msgDelayus = pFuncDelayus;
	}
	else
	{
		DHTxx->msgDelayus = DelayTask_us;
	}
	//---ms��ʱ
	if (pFuncDelayms != NULL)
	{
		DHTxx->msgDelayms = pFuncDelayms;
	}
	else
	{
		DHTxx->msgDelayms = DelayTask_ms;
	}
	//---ע��δ���
	if (pFuncTimerTick != NULL)
	{
		DHTxx->msgTimeTick = pFuncTimerTick;
	}
	else
	{
		DHTxx->msgTimeTick = SysTickTask_GetTick;
	}
	//---��ǰʱ��
	DHTxx->msgRecordTime= DHTxx->msgTimeTick();
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_DeInit(DHT11_HandlerType *DHTxx)
{
	LL_GPIO_DeInit(DHTxx->msgDAT.msgGPIOPort);
	GPIO_OUT_1(DHTxx->msgDAT.msgGPIOPort, DHTxx->msgDAT.msgGPIOBit);
	DHTxx->msgSTATE = DHT11_READ_ERROR;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_RESET(DHT11_HandlerType *DHTxx)
{
	//---�ͷ�����
	GPIO_OUT_1(DHTxx->msgDAT.msgGPIOPort, DHTxx->msgDAT.msgGPIOBit);
	//---��������2us
	DHTxx->msgDelayus(2);
	GPIO_OUT_0(DHTxx->msgDAT.msgGPIOPort, DHTxx->msgDAT.msgGPIOBit);
	//---������ʼ,��������Ҫ����18ms
	DHTxx->msgDelayms(20);
	//---�ͷ�����
	GPIO_OUT_1(DHTxx->msgDAT.msgGPIOPort, DHTxx->msgDAT.msgGPIOBit);
	//��������20~40us;�ȴ�DHT11�ĵ͵�ƽ��Ӧ�ź�
	DHTxx->msgDelayus(30);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����1:������;0:����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_Check(DHT11_HandlerType *DHTxx)
{
	UINT8_T count = 0;
	//---DHT11�����Ӧ�Ļ�����������40~80us
	while (GPIO_GET_STATE(DHTxx->msgDAT.msgGPIOPort, DHTxx->msgDAT.msgGPIOBit) != 0)
	{
		DHTxx->msgDelayus(1);
		count++;
		if (count > 200)
		{
			break;
		}
	}
	if (count > 200)
	{
		return ERROR_1;
	}
	count = 0;
	//---DHT11�ߵ�ƽ����׼���ź��ٴ�����40~80us
	while (GPIO_GET_STATE(DHTxx->msgDAT.msgGPIOPort, DHTxx->msgDAT.msgGPIOBit) == 0)
	{
		DHTxx->msgDelayus(1);
		count++;
		if (count > 200)
		{
			break;
		}
	}
	if (count > 200)
	{
		return ERROR_1;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����1:������;0:����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_START(DHT11_HandlerType *DHTxx)
{
	//---��������
	UINT8_T _return = DHT11_RESET(DHTxx);
	if (_return)
	{
		return _return;
	}
	//---����豸
	return DHT11_Check(DHTxx);
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����λ���ݡ�0���ĸ�ʽΪ�� 50 ΢��ĵ͵�ƽ�� 26-28 ΢��ĸߵ�ƽ;
/////////////  λ���ݡ�1���ĸ�ʽΪ�� 50 ΢��ĵ͵�ƽ�� 70΢��ĸߵ�ƽ
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_ReadBit(DHT11_HandlerType *DHTxx)
{
	UINT8_T count = 0;
	//---�ȴ���Ϊ�͵�ƽ---�ߵ�ƽ���ֵ�ʱ��ԼΪ50us
	while (GPIO_GET_STATE(DHTxx->msgDAT.msgGPIOPort, DHTxx->msgDAT.msgGPIOBit) != 0)
	{
		DHTxx->msgDelayus(1);
		count++;
		if (count > 150)
		{
			count = 0;
			break;
		}
	}
	//---��ȡ�ߵ�ƽ�ȴ�һ��
	DHTxx->msgDelayus(10);
	//---�ȴ���ߵ�ƽ---�͵�ƽ���ֵ�ʱ��ԼΪ20us
	while (GPIO_GET_STATE(DHTxx->msgDAT.msgGPIOPort, DHTxx->msgDAT.msgGPIOBit) == 0)
	{
		DHTxx->msgDelayus(1);

		count++;
		if (count > 150)
		{
			count = 0;
			break;
		}
	}
	//---�ȴ�40us;����Ϊ0���ź�ʱ��Ϊ26-28us��1��Ϊ70us
	DHTxx->msgDelayus(50);
	//---��ȡ״̬
	if (GPIO_GET_STATE(DHTxx->msgDAT.msgGPIOPort, DHTxx->msgDAT.msgGPIOBit) != 0)
	{
		return 1;
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_ReadByte(DHT11_HandlerType *DHTxx)
{
	UINT8_T i = 0, _return = 0;
	for (i = 0; i < 8; i++)
	{
		_return <<= 1;
		_return |= DHT11_ReadBit(DHTxx);
	}

	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�DHT11��ȡ״̬����ÿ���2�룬���ܶ�ȡ����ȷ����
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_ReadSTATE(DHT11_HandlerType* DHTxx)
{
	UINT32_T nowTime = DHTxx->msgTimeTick();
	UINT32_T cnt = 0;
	if (DHTxx->msgSTATE == DHT11_READ_ERROR)
	{
		return ERROR_1;
	}
	//===����ʱ����
	//---�жϵδ�ʱ�Ƿ����������
	if (DHTxx->msgRecordTime > nowTime)
	{
		cnt = (0xFFFFFFFF - nowTime + DHTxx->msgRecordTime);
	}
	else
	{
		cnt = nowTime-DHTxx->msgRecordTime;
	}
	if (cnt>DHT11_READ_INTERVAL_MS)
	{
		DHTxx->msgSTATE=DHT11_READ_OK;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_Read(DHT11_HandlerType *DHTxx)
{
	UINT8_T temp[5] = { 0 };
	UINT8_T i = 0;
	//---��ȡ��ǰ��״̬
	if (DHT11_ReadSTATE(DHTxx)!=OK_0)
	{
		return ERROR_1;
	}
	//---�ж������Ƿ�ɶ�
	if (DHTxx->msgSTATE==DHT11_READ_OK)
	{
		return ERROR_2;
	}
	//---�������ݵĶ�ȡ������豸�Ƿ����
	if (DHT11_START(DHTxx) != OK_0)
	{
		return ERROR_3;
	}
	//---��ȡ����
	for (i = 0; i < 5; i++)
	{
		temp[i] = DHT11_ReadByte(DHTxx);
	}
	//---�ͷ�����
	GPIO_OUT_1(DHTxx->msgDAT.msgGPIOPort, DHTxx->msgDAT.msgGPIOBit);
	//---����У��
	if ((temp[0] + temp[1] + temp[2] + temp[3]) != temp[4])
	{
		return ERROR_4;
	}
	//---ʪ����������
	DHTxx->msgHumiX1000 = temp[0];
	//---ʪ��С������
	DHTxx->msgHumiX1000 = (DHTxx->msgHumiX1000 * 1000) + temp[1];
	//---�¶���������
	DHTxx->msgTempX1000 = temp[2];
	//---�¶�С������
	DHTxx->msgTempX1000 = (DHTxx->msgTempX1000 * 1000) + temp[3];
	//---���õ�ǰ״̬Ϊæµģʽ
	DHTxx->msgSTATE= DHT11_READ_BUSY;
	//---����ʱ���ǩ
	DHTxx->msgRecordTime = DHTxx->msgTimeTick();
	return OK_0;
}
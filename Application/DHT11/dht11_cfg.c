#include "dht11_cfg.h"

//---��������
DHT11_HandleType g_Dht11Device0 = { 0 };
pDHT11_HandleType pDht11Device0 = &g_Dht11Device0;

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:DHT11x
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_Device0_Init(DHT11_HandleType *DHTxx)
{
	DHTxx->msgSTATE=DHT11_READ_OK;
	DHTxx->msgDAT.msgBit = LL_GPIO_PIN_14;
	DHTxx->msgDAT.msgPort = GPIOB;
	//---����25���϶�
	DHTxx->msgTempX1000=25000;
	//---ʪ�Ȱٷ�֮��ʮ
	DHTxx->msgHumiX1000=50000;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_Device1_Init(DHT11_HandleType *DHTxx)
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
UINT8_T DHT11_Device2_Init(DHT11_HandleType *DHTxx)
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
UINT8_T DHT11_GPIO_Init(DHT11_HandleType *DHTxx)
{
	//---ʹ�ܶ˿�ʱ��
	#ifndef  USE_FULL_GPIO
	GPIOTask_Clock(DHTxx->msgDAT.msgPort, PERIPHERAL_CLOCK_ENABLE);
	#endif
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	//---GPIO�ĳ�ʼ��
	GPIO_InitStruct.Pin = DHTxx->msgDAT.msgBit;														//---��Ӧ��GPIO������
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;														//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;												//---GPIO���ٶ�
	GPIO_InitStruct.OutputType =LL_GPIO_OUTPUT_OPENDRAIN;											//---���ģʽ---��©���
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;															//---����ʹ��
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;														//---�˿ڸ���ģʽ
#endif
	//---��ʼ���˿�
	LL_GPIO_Init(DHTxx->msgDAT.msgPort, &GPIO_InitStruct);
	GPIO_OUT_1(DHTxx->msgDAT.msgPort, DHTxx->msgDAT.msgBit);
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_Init(DHT11_HandleType *DHTxx, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void))
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
	(pFuncDelayus != NULL)?(DHTxx->pMsgDelayus = pFuncDelayus):(DHTxx->pMsgDelayus = DelayTask_us);
	//---ms��ʱ
	(pFuncDelayms != NULL)?(DHTxx->pMsgDelayms = pFuncDelayms):(DHTxx->pMsgDelayms = DelayTask_ms);
	//---ע��δ���
	(pFuncTimerTick != NULL)?(DHTxx->pMsgTimeTick = pFuncTimerTick):(DHTxx->pMsgTimeTick = SysTickTask_GetTick);
	//---��ǰʱ��
	DHTxx->msgRecordTick= DHTxx->pMsgTimeTick();
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_DeInit(DHT11_HandleType *DHTxx)
{
	LL_GPIO_DeInit(DHTxx->msgDAT.msgPort);
	GPIO_OUT_1(DHTxx->msgDAT.msgPort, DHTxx->msgDAT.msgBit);
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
UINT8_T DHT11_RESET(DHT11_HandleType *DHTxx)
{
	//---�ͷ�����
	GPIO_OUT_1(DHTxx->msgDAT.msgPort, DHTxx->msgDAT.msgBit);
	//---��������2us
	DHTxx->pMsgDelayus(2);
	GPIO_OUT_0(DHTxx->msgDAT.msgPort, DHTxx->msgDAT.msgBit);
	//---������ʼ,��������Ҫ����18ms
	DHTxx->pMsgDelayms(20);
	//---�ͷ�����
	GPIO_OUT_1(DHTxx->msgDAT.msgPort, DHTxx->msgDAT.msgBit);
	//��������20~40us;�ȴ�DHT11�ĵ͵�ƽ��Ӧ�ź�
	DHTxx->pMsgDelayus(30);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����1:������;0:����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_Check(DHT11_HandleType *DHTxx)
{
	UINT8_T count = 0;
	//---DHT11�����Ӧ�Ļ�����������40~80us
	while (GPIO_GET_STATE(DHTxx->msgDAT.msgPort, DHTxx->msgDAT.msgBit) != 0)
	{
		DHTxx->pMsgDelayus(1);
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
	while (GPIO_GET_STATE(DHTxx->msgDAT.msgPort, DHTxx->msgDAT.msgBit) == 0)
	{
		DHTxx->pMsgDelayus(1);
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
UINT8_T DHT11_START(DHT11_HandleType *DHTxx)
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
UINT8_T DHT11_ReadBit(DHT11_HandleType *DHTxx)
{
	UINT8_T count = 0;
	//---�ȴ���Ϊ�͵�ƽ---�ߵ�ƽ���ֵ�ʱ��ԼΪ50us
	while (GPIO_GET_STATE(DHTxx->msgDAT.msgPort, DHTxx->msgDAT.msgBit) != 0)
	{
		DHTxx->pMsgDelayus(1);
		count++;
		if (count > 150)
		{
			count = 0;
			break;
		}
	}
	//---��ȡ�ߵ�ƽ�ȴ�һ��
	DHTxx->pMsgDelayus(10);
	//---�ȴ���ߵ�ƽ---�͵�ƽ���ֵ�ʱ��ԼΪ20us
	while (GPIO_GET_STATE(DHTxx->msgDAT.msgPort, DHTxx->msgDAT.msgBit) == 0)
	{
		DHTxx->pMsgDelayus(1);

		count++;
		if (count > 150)
		{
			count = 0;
			break;
		}
	}
	//---�ȴ�40us;����Ϊ0���ź�ʱ��Ϊ26-28us��1��Ϊ70us
	DHTxx->pMsgDelayus(50);
	//---��ȡ״̬
	if (GPIO_GET_STATE(DHTxx->msgDAT.msgPort, DHTxx->msgDAT.msgBit) != 0)
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
UINT8_T DHT11_ReadByte(DHT11_HandleType *DHTxx)
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
UINT8_T DHT11_ReadSTATE(DHT11_HandleType* DHTxx)
{
	UINT32_T nowTime = DHTxx->pMsgTimeTick();
	UINT32_T cnt = 0;
	if (DHTxx->msgSTATE == DHT11_READ_ERROR)
	{
		return ERROR_1;
	}
	//===����ʱ����
	//---�жϵδ�ʱ�Ƿ����������
	if (DHTxx->msgRecordTick > nowTime)
	{
		cnt = (0xFFFFFFFF - nowTime + DHTxx->msgRecordTick);
	}
	else
	{
		cnt = nowTime-DHTxx->msgRecordTick;
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
UINT8_T DHT11_ReadTempHumi(DHT11_HandleType *DHT11x)
{
	UINT8_T temp[5] = { 0 };
	UINT8_T i = 0;
	//---��ȡ��ǰ��״̬
	if (DHT11_ReadSTATE(DHT11x)!=OK_0)
	{
		return ERROR_1;
	}
	//---�ж������Ƿ�ɶ�
	if (DHT11x->msgSTATE==DHT11_READ_OK)
	{
		return ERROR_2;
	}
	//---�������ݵĶ�ȡ������豸�Ƿ����
	if (DHT11_START(DHT11x) != OK_0)
	{
		return ERROR_3;
	}
	//---��ȡ����
	for (i = 0; i < 5; i++)
	{
		temp[i] = DHT11_ReadByte(DHT11x);
	}
	//---�ͷ�����
	GPIO_OUT_1(DHT11x->msgDAT.msgPort, DHT11x->msgDAT.msgBit);
	//---����У��
	if ((temp[0] + temp[1] + temp[2] + temp[3]) != temp[4])
	{
		return ERROR_4;
	}
	//---ʪ����������
	DHT11x->msgHumiX1000 = temp[0];
	//---ʪ��С������
	DHT11x->msgHumiX1000 = (DHT11x->msgHumiX1000 * 1000) + temp[1];
	//---�¶���������
	DHT11x->msgTempX1000 = temp[2];
	//---�¶�С������
	if ((temp[3]&0x80)!=0)
	{
		//---�¶������Ǹ���
		DHT11x->msgPositive=1;
	}
	else
	{
		//---�¶�����������
		DHT11x->msgPositive =0;
	}
	DHT11x->msgTempX1000 = (DHT11x->msgTempX1000 * 1000) + (temp[3]&0x7F);
	//---���õ�ǰ״̬Ϊæµģʽ
	DHT11x->msgSTATE= DHT11_READ_BUSY;
	//---����ʱ���ǩ
	DHT11x->msgRecordTick = DHT11x->pMsgTimeTick();
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ�¶�ֵ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
float DHT11_GetTemp(DHT11_HandleType* DHT11x)
{
	float tempVal = DHT11x->msgTempX1000;
	//---ת���¶ȶ�Ӧʵ�ʵ��¶�ֵ
	tempVal /= 1000.0;
	//---У���ǲ�������
	if (DHT11x->msgPositive == 1)
	{
		tempVal *= (-1.0);
	}
	return tempVal;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡʪ��ֵ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
float DHT11_GetHumi(DHT11_HandleType* DHT11x)
{
	float tempVal = DHT11x->msgHumiX1000;
	//---ת���¶ȶ�Ӧʵ�ʵ��¶�ֵ
	tempVal /= 1000.0;
	//---У���ǲ�������
	if (DHT11x->msgPositive == 1)
	{
		tempVal *= (-1.0);
	}
	return tempVal;
}
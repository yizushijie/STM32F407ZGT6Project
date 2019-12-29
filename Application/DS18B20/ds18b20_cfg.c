#include "ds18b20_cfg.h"

//---��������
DS18B20_HandlerType g_Ds18b20Device0 = { 0 };
pDS18B20_HandlerType pDs18b20Device0 = &g_Ds18b20Device0;

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��豸1�ĳ�ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DS18B20_OneWire_Device0_Init(DS18B20_HandlerType *DS18B20x)
{
	DS18B20x->msgOneWire.msgDAT.msgGPIOBit = LL_GPIO_PIN_2;
	DS18B20x->msgOneWire.msgDAT.msgGPIOPort = GPIOC;
	DS18B20x->msgTempBit=3;
	DS18B20x->msgIntervalTime=800;
	DS18B20x->msgTempBitValX10000=625;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��豸2�ĳ�ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DS18B20_OneWire_Device1_Init(DS18B20_HandlerType *DS18B20x)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��豸3�ĳ�ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DS18B20_OneWire_Device2_Init(DS18B20_HandlerType *DS18B20x)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ʼ��ָ���豸
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DS18B20_OneWire_Init(DS18B20_HandlerType *DS18B20x, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void))
{
	if ((DS18B20x != NULL) && (DS18B20x == DS18B20_TASK_ONE))
	{
		DS18B20_OneWire_Device0_Init(DS18B20x);
	}
	else if ((DS18B20x != NULL) && (DS18B20x == DS18B20_TASK_TWO))
	{
		DS18B20_OneWire_Device1_Init(DS18B20x);
	}
	else if ((DS18B20x != NULL) && (DS18B20x == DS18B20_TASK_THREE))
	{
		DS18B20_OneWire_Device2_Init(DS18B20x);
	}
	else
	{
		return  ERROR_1;
	}

	//---ע����ʱ����
	if (pFuncDelayms != NULL)
	{
		DS18B20x->msgDelayms = pFuncDelayms;
	}
	else
	{
		DS18B20x->msgDelayms = DelayTask_ms;
	}
	//---ע��δ���
	if (pFuncTimerTick != NULL)
	{
		DS18B20x->msgTimeTick = pFuncTimerTick;
	}
	else
	{
		DS18B20x->msgTimeTick = SysTickTask_GetTick;
	}
	//---��ǰʱ��
	DS18B20x->msgRecordTime = DS18B20x->msgTimeTick();
	//---���û�������
	return DS18B20_OneWire_Config(DS18B20x,pFuncDelayus);
	//return OneWireTask_Init(&(DS18B20x->msgOneWire), pFuncDelayus);
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�����ָ�����豸
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DS18B20_OneWire_DeInit(DS18B20_HandlerType *DS18B20x)
{
	return OneWireTask_DeInit(&(DS18B20x->msgOneWire));
}
///////////////////////////////////////////////////////////////////////////////
//////��	   ���� UINT8_T Ds18b20Cfg_Start(void)
//////��	   �ܣ� ����Ds18b20Cfg
//////�������:
//////�������: 0---ʧ��;1---��ʾ�ɹ�
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DS18B20_OneWire_START(DS18B20_HandlerType *DS18B20x)
{
	return OneWireTask_START(&(DS18B20x->msgOneWire));
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ���� void Ds18b20Cfg_WriteByte(UINT8_T val)
//////��	   �ܣ� д��һ�ֽڵ�����
//////�������: д���ֵ
//////�������: ��
//////˵	   ����
///////////////////////////////////////////////////////////////////////////////
UINT8_T DS18B20_OneWire_WriteByte(DS18B20_HandlerType *DS18B20x, UINT8_T val)
{
	return OneWireTask_WriteByte(&(DS18B20x->msgOneWire), val);
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ���� UINT8_T Ds18b20Cfg_ReadByte(void)
//////��	   �ܣ� ��ȡһ�ֽڵ�����
//////�������: ��
//////�������: ��ȡ������
//////˵	   ����
///////////////////////////////////////////////////////////////////////////////
UINT8_T DS18B20_OneWire_ReadByte(DS18B20_HandlerType *DS18B20x)
{
	return OneWireTask_ReadByte(&(DS18B20x->msgOneWire));
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ�¶ȵķֱ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DS18B20_OneWire_ReadTempBit(DS18B20_HandlerType* DS18B20x,UINT8_T *pTempBit)
{
	UINT8_T tempBit[3]={0};
	UINT8_T i=0;
	//---���߸�λ
	if (DS18B20_OneWire_START(DS18B20x) == 0)
	{
		return ERROR_1;
	}
	//---���Ե�ַƥ��
	DS18B20_OneWire_WriteByte(DS18B20x, 0xCC);
	//---��ȡ�ݴ�Ĵ�����ֵ
	DS18B20_OneWire_WriteByte(DS18B20x, 0xBE);
	//---��ȡ�¶ȷֱ�����Ϣ
	for (i = 0; i < 3; i++)
	{
		tempBit[i] = DS18B20_OneWire_ReadByte(DS18B20x);
	}
	DS18B20x->msgTempTH = tempBit[0];
	DS18B20x->msgTempTL = tempBit[1];
	//DS18B20x->msgTempBit=tempBit[2];
	tempBit[2]&=0x60;
	tempBit[2]>>=5;
	*pTempBit=tempBit[2];
	//----���߸�λ
	DS18B20_OneWire_START(DS18B20x);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�д���¶ȵķֱ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DS18B20_OneWire_WriteTempBit(DS18B20_HandlerType* DS18B20x, UINT8_T tempBit)
{
	UINT8_T i = 0;
	//---���߸�λ
	if (DS18B20_OneWire_START(DS18B20x) == 0)
	{
		return ERROR_1;
	}
	DS18B20x->msgTempBit=tempBit;
	//--9Bit
	if (tempBit==0)
	{
		DS18B20x->msgIntervalTime=100;
		DS18B20x->msgTempBitValX10000=5000;
	}
	//---10Bit
	else if (tempBit == 1)
	{
		DS18B20x->msgIntervalTime = 200;
		DS18B20x->msgTempBitValX10000 = 2500;
	}
	//---11Bit
	else if (tempBit == 1)
	{
		DS18B20x->msgIntervalTime = 400;
		DS18B20x->msgTempBitValX10000 = 1250;
	}
	//---12Bit
	else
	{
		DS18B20x->msgIntervalTime = 800;
		DS18B20x->msgTempBitValX10000 = 625;
	}
	tempBit<<=5;
	tempBit|=0x1F;
	//---���Ե�ַƥ��
	DS18B20_OneWire_WriteByte(DS18B20x, 0xCC);
	//---��ȡ�ݴ�Ĵ�����ֵ
	DS18B20_OneWire_WriteByte(DS18B20x, 0x4E);
	//---��ȡ�ݴ�Ĵ�����ֵ
	DS18B20_OneWire_WriteByte(DS18B20x, DS18B20x->msgTempTH);
	DS18B20_OneWire_WriteByte(DS18B20x, DS18B20x->msgTempTL);
	//---д���¶ȷֱ���
	DS18B20_OneWire_WriteByte(DS18B20x, tempBit);
	//----���߸�λ
	DS18B20_OneWire_START(DS18B20x);
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ�豸��ID��Ϣ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DS18B20_OneWire_ReadID(DS18B20_HandlerType *DS18B20x, UINT8_T *id)
{
	UINT8_T i;
	//---���߸�λ
	if (DS18B20_OneWire_START(DS18B20x) == 0)
	{
		return ERROR_1;
	}
	//---������
	DS18B20_OneWire_WriteByte(DS18B20x, 0x33);
	//---��ȡ�豸��ID��Ϣ
	for (i = 0; i < 8; i++)
	{
		id[i] = DS18B20_OneWire_ReadByte(DS18B20x);
	}

	//----���߸�λ
	DS18B20_OneWire_START(DS18B20x);
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ʼת��,����IDƥ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT16_T DS18B20_OneWire_StartConvert(DS18B20_HandlerType* DS18B20x)
{
	//---���߸�λ
	if (DS18B20_OneWire_START(DS18B20x) == 0)
	{
		return ERROR_1;
	}
	//---���Ե�ַƥ��
	DS18B20_OneWire_WriteByte(DS18B20x, 0xCC);
	//---����ת��
	DS18B20_OneWire_WriteByte(DS18B20x, 0x44);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����״̬
//////�������:
//////�������: 0---���Զ�ȡ��1---�����ȡʱ�仹û�е���������ȡ
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT16_T DS18B20_OneWire_STATE(DS18B20_HandlerType* DS18B20x)
{
	UINT32_T nowTime = DS18B20x->msgTimeTick();
	UINT32_T cnt = 0;
	//---�жϵδ�ʱ�Ƿ����������
	if (DS18B20x->msgRecordTime > nowTime)
	{
		cnt = (0xFFFFFFFF - nowTime + DS18B20x->msgRecordTime);
	}
	else
	{
		cnt = nowTime-DS18B20x->msgRecordTime;
	}
	if (cnt > DS18B20x->msgIntervalTime)
	{
		return OK_0;
	}
	else
	{
		return ERROR_1;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ���� UINT16_T DS18B20_GetWenDu(DS18B20_HandlerType *DS18B20HandlerType)
//////��	   �ܣ� ��ȡ�¶�ֵ
//////�������: ��
//////�������: �Ŵ�100��֮����¶ȵ�ֵ
//////˵	   ����
///////////////////////////////////////////////////////////////////////////////
UINT16_T DS18B20_OneWire_ReadTemp(DS18B20_HandlerType *DS18B20x)
{
	UINT16_T _return = 0;
	UINT16_T tempH = 0;
	UINT8_T tempL;
	//---����Ƿ񵽴��´εĶ�ȡ��ʱ��
	_return= DS18B20_OneWire_STATE(DS18B20x);
	if (_return!=OK_0)
	{
		return ERROR_1;
	}
	//---��ȡ����֮ǰ��������Ϊ������Ч�����������豸ʹ��
	DS18B20x->msgIsPositive = 0;
	//---��ʱ�ȴ�
	DS18B20x->msgDelayms(1);
	//---��ʼ���¶ȴ�����---���߸�λ
	DS18B20_OneWire_START(DS18B20x);
	//---���Ե�ַ
	DS18B20_OneWire_WriteByte(DS18B20x, 0xCC);
	//---��ȡ�¶�
	DS18B20_OneWire_WriteByte(DS18B20x, 0xBE);
	//---��ȡ��λ
	tempL = DS18B20_OneWire_ReadByte(DS18B20x);
	//---��ȡ��λ
	tempH = DS18B20_OneWire_ReadByte(DS18B20x);
	//---��ȡ�¶���ֵ
	_return = (tempH << 8) | tempL;
	//---�ж��¶�����ֵ���Ǹ�ֵ
	if ((tempH & 0x80) == 0)
	{
		//---��ȡ���¶�����ֵ
		DS18B20x->msgIsPositive = 2;
	}
	else
	{
		//===��ȡ���¶��Ǹ�ֵ
		DS18B20x->msgIsPositive = 1;
	}
	//---��ȡ���¶�ֵ
	tempH = _return;
	//---������Чλ����
	tempH &= 0x0FFF;
	//---��ȡ�¶�ֵ��Ӧ��16���Ƶ�����
	if (DS18B20x->msgIsPositive == 2)
	{
		DS18B20x->msgTempX10000 = tempH;
	}
	else
	{
		DS18B20x->msgTempX10000 = 0x1000 - tempH;
	}
	//---��ʮ��������ת�����¶�ֵ
	DS18B20x->msgTempX10000 *= DS18B20x->msgTempBitValX10000;//625;
	//---��ȡʵ���¶�ֵ
	DS18B20x->msgTempX100 = (UINT16_T)(DS18B20x->msgTempX10000 / 100);
	//---�����´�ת��
	DS18B20_OneWire_StartConvert(DS18B20x);
	//---�����¶����ֵ
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT16_T DS18B20_OneWire_ReadTempByID(DS18B20_HandlerType *DS18B20x, UINT8_T *id)
{
	UINT16_T _return = 0, temH = 0;
	UINT8_T temL = 0, i = 0;

	//---�����¶ȴ�����---���߸�λ
	DS18B20_OneWire_START(DS18B20x);
	//---���Ե�ַ
	DS18B20_OneWire_WriteByte(DS18B20x, 0x55);
	//---д��ROM��ID
	for (i = 0; i < 8; i++)
	{
		DS18B20_OneWire_WriteByte(DS18B20x, id[i]);
	}
	//---����ת��
	DS18B20_OneWire_WriteByte(DS18B20x, 0x44);
	//---��ʱ�ȴ�
	DS18B20x->msgDelayms(1);
	//---��ʼ���¶ȴ�����---���߸�λ
	DS18B20_OneWire_START(DS18B20x);
	//---���Ե�ַ
	DS18B20_OneWire_WriteByte(DS18B20x, 0x55);
	//---д��ROM��ID
	for (i = 0; i < 8; i++)
	{
		DS18B20_OneWire_WriteByte(DS18B20x, id[i]);
	}
	//---��ȡ�¶�
	DS18B20_OneWire_WriteByte(DS18B20x, 0xBE);
	//---��ȡ��λ
	temL = DS18B20_OneWire_ReadByte(DS18B20x);
	//---��ȡ��λ
	temH = DS18B20_OneWire_ReadByte(DS18B20x);
	//---��ȡ�¶���ֵ
	_return = (temH << 8) | temL;

	//---�ж��¶�����ֵ���Ǹ�ֵ
	if ((temH & 0x80) == 0)
	{
		//---��ȡ���¶�����ֵ
		DS18B20x->msgIsPositive = 0;
	}
	else
	{
		//===��ȡ���¶��Ǹ�ֵ
		DS18B20x->msgIsPositive = 1;
	}
	//---��ȡ���¶�ֵ
	temH = _return;
	//---������Чλ����
	temH &= 0x0FFF;
	//---��ȡ�¶�ֵ��Ӧ��16���Ƶ�����
	if (DS18B20x->msgIsPositive == 0)
	{
		DS18B20x->msgTempX10000 = temH;
	}
	else
	{
		DS18B20x->msgTempX10000 = 4096 - temH;
	}
	//---��ʮ��������ת�����¶�ֵ
	DS18B20x->msgTempX10000 *= DS18B20x->msgTempBitValX10000;;
	//---��ȡʵ���¶�ֵ
	DS18B20x->msgTempX100 = (UINT16_T)(DS18B20x->msgTempX10000 / 100);
	//---�����´�ת��
	DS18B20_OneWire_StartConvert(DS18B20x);
	//---�����¶����ֵ
	return _return;
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ó�ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DS18B20_OneWire_Config(DS18B20_HandlerType* DS18B20x,void(*pFuncDelayus)(UINT32_T delay))
{
	UINT8_T _return=0;
	//---��ʼ��һ�߽ӿڵĲ���
	OneWireTask_Init(&(DS18B20x->msgOneWire), pFuncDelayus);
	//---��ȡ�˿ڵĲ������ã��ر����¶ȵķֱ���
	DS18B20_OneWire_ReadTempBit(DS18B20x,&_return);
	if (_return!=DS18B20x->msgTempBit)
	{
		//---�����¶ȷֱ���
		DS18B20_OneWire_WriteTempBit(DS18B20x, DS18B20x->msgTempBit);
	}
	//---����װ��
	return DS18B20_OneWire_StartConvert(DS18B20x);
}
#include "aht10_cfg.h"

//===ȫ�ֱ�������
AHT10_HandlerType		g_Aht10Device0;
pAHT10_HandlerType		pAht10Device0;

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AHT10_I2C_Device0_Init(AHT10_HandlerType* AHT10x)
{
	AHT10x->msgI2C.msgI2Cx = NULL;
	AHT10x->msgI2C.msgSCL.msgGPIOPort = GPIOB;
	AHT10x->msgI2C.msgSCL.msgGPIOBit = LL_GPIO_PIN_6;
	AHT10x->msgI2C.msgSDA.msgGPIOPort = GPIOB;
	AHT10x->msgI2C.msgSDA.msgGPIOBit = LL_GPIO_PIN_7;
	AHT10x->msgI2C.msgModelIsHW = 0;
	AHT10x->msgI2C.msgPluseWidth = 0;
	AHT10x->msgI2C.msgDelayus = NULL;
	AHT10x->msgI2C.msgAddr = AHT10_WADDR;//0x80;  // SHT2X_WRITE_ADDR;
	AHT10x->msgI2C.msgClockSpeed = 10;
	//---ÿ�ζ�ȡ�ļ��ʱ��,76ms
	AHT10x->msgIntervalTime=76;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AHT10_I2C_Device1_Init(AHT10_HandlerType* AHT10x)
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
UINT8_T AHT10_I2C_Device2_Init(AHT10_HandlerType* AHT10x)
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
UINT8_T AHT10_I2C_DeInit(AHT10_HandlerType* AHT10x)
{
	//---ע��I2C�豸
	if (AHT10x->msgI2C.msgModelIsHW == 1)
	{
		return ERROR_1;
	}
	else
	{
		return I2CTask_MSW_DeInit(&(AHT10x->msgI2C));
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:isHWI2C---1 Ӳ����0 ���
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AHT10_I2C_Init(AHT10_HandlerType* AHT10x, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHWI2C)
{
	UINT8_T _return = OK_0;
	//---ָ���豸�ĳ�ʼ��
	if ((AHT10x != NULL) && (AHT10x == AHT10_TASK_ONE))
	{
		AHT10_I2C_Device0_Init(AHT10x);
	}
	else if ((AHT10x != NULL) && (AHT10x == AHT10_TASK_TWO))
	{
		AHT10_I2C_Device1_Init(AHT10x);
	}
	else if ((AHT10x != NULL) && (AHT10x == AHT10_TASK_THREE))
	{
		AHT10_I2C_Device2_Init(AHT10x);
	}
	else
	{
		return ERROR_1;
	}
	//---�ж���Ӳ��I2C�������I2C
	if (isHWI2C)
	{
		//---��ʼ��Ӳ��I2C
		_return = I2CTask_MHW_Init(&(AHT10x->msgI2C));
		AHT10x->msgI2C.msgModelIsHW = 1;
	}
	else
	{
		//---��ʼ�����ģ��I2C
		_return = I2CTask_MSW_Init(&(AHT10x->msgI2C), pFuncDelayus);
		AHT10x->msgI2C.msgModelIsHW = 0;
	}
	//---��ʱ�ȴ�40ms
	if (pFuncDelayms!=NULL)
	{
		pFuncDelayms(40);
	}
	else
	{
		DelayTask_ms(40);
	}
	//---ע��δ���
	if (pFuncTimerTick != NULL)
	{
		AHT10x->msgTimeTick = pFuncTimerTick;
	}
	else
	{
		AHT10x->msgTimeTick = SysTickTask_GetTick;
	}
	//---�����豸
	_return = AHT10_I2C_Config(AHT10x);
	//---��ǰʱ��
	AHT10x->msgRecordTime = AHT10x->msgTimeTick();
	return _return;
}

//////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� дBulkģʽ
//////�������:
//////�������:
//////˵		���� ���ģ��I2C��������
//////////////////////////////////////////////////////////////////////////////
UINT8_T AHT10_SWI2C_WriteBulk(AHT10_HandlerType* AHT10x,UINT8_T* pVal, UINT8_T length)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---����������д����
	_return = I2CTask_MSW_START(&(AHT10x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---��������
	for (i = 0; i < length; i++)
	{
		//---��������
		I2CTask_MSW_SendByte(&(AHT10x->msgI2C), pVal[i]);
		//---��ȡACK
		_return = I2CTask_MSW_ReadACK(&(AHT10x->msgI2C));
		//---�ж�Ӧ��
		if (_return)
		{
			_return = ERROR_3 + i;
			goto GoToExit;
		}
	}
	//---�˳���ں���
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(AHT10x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AHT10_HWI2C_WriteBulk(AHT10_HandlerType* AHT10x, UINT8_T* pVal, UINT8_T length)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AHT10_I2C_WriteBulk(AHT10_HandlerType* AHT10x, UINT8_T* pVal, UINT8_T length)
{
	if (AHT10x->msgI2C.msgModelIsHW == 0)
	{
		//---���ģ��I2C
		return AHT10_SWI2C_WriteBulk(AHT10x,pVal, length);
	}
	else
	{
		//---Ӳ��I2C
		return AHT10_HWI2C_WriteBulk(AHT10x,pVal, length);
	}
}

//////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� ��Bulkģʽ
//////�������:
//////�������:
//////˵		���� ���ģ��I2C��������
//////////////////////////////////////////////////////////////////////////////
UINT8_T AHT10_SWI2C_ReadBulk(AHT10_HandlerType* AHT10x, UINT8_T* pVal, UINT8_T length)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---������ȡ����
	_return = I2CTask_MSW_START(&(AHT10x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---����������ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---��������
	for (i = 0; i < length; i++)
	{
		//---��ȡ����
		*(pVal++) = I2CTask_MSW_ReadByte(&(AHT10x->msgI2C));
		//---У���Ƿ���ҪACK
		if (i == (length - 1))
		{
			_return = 1;
		}
		//---����Ӧ���ź�
		I2CTask_MSW_SendACK(&(AHT10x->msgI2C), _return);
	}
	_return = OK_0;
	//---�˳���ں���
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(AHT10x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AHT10_HWI2C_ReadBulk(AHT10_HandlerType* AHT10x, UINT8_T* pVal, UINT8_T length)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AHT10_I2C_ReadBulk(AHT10_HandlerType* AHT10x, UINT8_T* pVal, UINT8_T length)
{
	if (AHT10x->msgI2C.msgModelIsHW == 0)
	{
		//---���ģ��I2C
		return AHT10_SWI2C_ReadBulk(AHT10x, pVal, length);
	}
	else
	{
		//---Ӳ��I2C
		return AHT10_HWI2C_ReadBulk(AHT10x, pVal, length);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ó�ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AHT10_I2C_Config(AHT10_HandlerType* AHT10x)
{
	UINT8_T tempCMD[3]={ AHT10_CMD_INIT,0x08,0x00};
	//---���ͳ�ʼ������
	UINT8_T _return= AHT10_I2C_WriteBulk(AHT10x,tempCMD,3);
	if (_return==OK_0)
	{
		_return= AHT10_I2C_StartMeasure(AHT10x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AHT10_I2C_StartMeasure(AHT10_HandlerType* AHT10x)
{
	UINT8_T tempCMD[3] = { AHT10_CMD_MEASURE,0x33,0x00 };
	//---���Ͳ�������
	UINT8_T _return=AHT10_I2C_WriteBulk(AHT10x, tempCMD, 3);
	//---��ȡʱ�����
	AHT10x->msgRecordTime=AHT10x->msgTimeTick();
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ǰ״̬
//////�������:
//////�������: 0---���Զ�ȡ��1---�����ȡʱ�仹û�е���������ȡ
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AHT10_I2C_STATE(AHT10_HandlerType* AHT10x)
{	
	//---��ǰʱ��ڵ�
	UINT32_T nowTime = AHT10x->msgTimeTick();
	UINT32_T cnt = 0;
	//---�жϵδ�ʱ�Ƿ����������
	if (AHT10x->msgRecordTime > nowTime)
	{
		cnt = (0xFFFFFFFF - AHT10x->msgRecordTime + nowTime);
	}
	else
	{
		cnt = nowTime - AHT10x->msgRecordTime;
	}
	//---У��ʱ�����Ƿ񵽴�
	if (cnt > AHT10x->msgIntervalTime)
	{
		return OK_0;
	}
	else
	{
		return ERROR_1;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ��ʪ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AHT10_I2C_ReadTempHumi(AHT10_HandlerType* AHT10x)
{
	UINT8_T tempVal[6] = { 0x00,0x00,0x00,0x00,0x00,0x00 };
	//---��ȡ�¶�����
	UINT8_T _return= AHT10_I2C_STATE(AHT10x);
	//---У���ȡ���
	if (_return!=OK_0)
	{
		//---ʱ����δ�����޷���ȡ����
		return ERROR_1;
	}
	//---ʱ��ڵ㵽���ȡ��ʪ�ȵĽ��
	_return=AHT10_I2C_ReadBulk(AHT10x, tempVal, 6);
	//---У���ȡ���
	if (_return == OK_0)
	{
		//---�����¶�ֵ
		//AHT10x->msgTemp = ((tempVal[3] & 0x0F) << 16) | (tempVal[4] << 8) | tempVal[5];
		AHT10x->msgTemp = (tempVal[3] & 0x0F);
		AHT10x->msgTemp=(AHT10x->msgTemp<<8)+ tempVal[4];
		AHT10x->msgTemp = (AHT10x->msgTemp << 8) + tempVal[5];
		AHT10x->msgTemp = (((200.0 * (float)AHT10x->msgTemp) / 1048576.0) - 50.0) * 100.0;
		//---����ʪ��ֵ
		//AHT10x->msgHumi = ((tempVal[1] << 16) | (tempVal[2] << 8) | tempVal[3]) >> 4;
		AHT10x->msgHumi = tempVal[1];
		AHT10x->msgHumi =(AHT10x->msgHumi<<8)+ tempVal[2];
		AHT10x->msgHumi = (AHT10x->msgHumi << 8) + (tempVal[3]>>4);
		AHT10x->msgHumi = (float)AHT10x->msgHumi * 10000.0 / 1048576.0;
	}
	//---�����´β���װ��װ��
	AHT10_I2C_StartMeasure(AHT10x);
	//---���ؽ��
	return ((_return==OK_0)?OK_0:(_return+ERROR_1));
}

#include "aht10_cfg.h"

//===ȫ�ֱ�������
AHT10_HandleType		g_Aht10Device0={0};
pAHT10_HandleType		pAht10Device0=&g_Aht10Device0;

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AHT10_I2C_Device0_Init(AHT10_HandleType* AHT10x)
{
	AHT10x->msgI2C.pMsgI2Cx = NULL;
	AHT10x->msgI2C.msgSCL.msgPort = GPIOB;
	AHT10x->msgI2C.msgSCL.msgBit = LL_GPIO_PIN_6;
	AHT10x->msgI2C.msgSDA.msgPort = GPIOB;
	AHT10x->msgI2C.msgSDA.msgBit = LL_GPIO_PIN_7;
	AHT10x->msgI2C.msgHwMode = 0;
	AHT10x->msgI2C.msgPluseWidth = 0;
	AHT10x->msgI2C.pMsgDelayus = NULL;
	AHT10x->msgI2C.msgAddr = AHT10_WADDR;//0x80;  // SHT2X_WRITE_ADDR;
	AHT10x->msgI2C.msgClockSpeed = 200000;
	//---ÿ�ζ�ȡ�ļ��ʱ��,76ms������ɼ�������760ms
	AHT10x->msgIntervalTime=76*2;
	//---�趨�¶ȳ�ʼֵ������25���϶�
	AHT10x->msgTemp=25*100;
	AHT10x->msgHumiX10000=(50*10000);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AHT10_I2C_Device1_Init(AHT10_HandleType* AHT10x)
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
UINT8_T AHT10_I2C_Device2_Init(AHT10_HandleType* AHT10x)
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
UINT8_T AHT10_I2C_DeInit(AHT10_HandleType* AHT10x)
{
	//---ע��I2C�豸
	return I2CTask_Master_DeInit(&(AHT10x->msgI2C));
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:isHWI2C---1 Ӳ����0 ���
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AHT10_I2C_Init(AHT10_HandleType* AHT10x, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHWI2C)
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
	(isHWI2C != 0) ? (_return = I2CTask_MHW_Init(&(AHT10x->msgI2C),pFuncDelayus, pFuncTimerTick)) : (_return = I2CTask_MSW_Init(&(AHT10x->msgI2C), pFuncDelayus, pFuncTimerTick));
	//---��ʱ�ȴ�40ms
	(pFuncDelayms != NULL) ? (pFuncDelayms(40)) : (DelayTask_ms(40));
	//---�����豸
	_return = AHT10_I2C_Config(AHT10x);
	//---��ǰʱ��
	AHT10x->msgRecordTick = AHT10x->msgI2C.pMsgTimeTick();
	return _return;
}

//////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� дBulkģʽ
//////�������:
//////�������:
//////˵		���� ���ģ��I2C��������
//////////////////////////////////////////////////////////////////////////////
UINT8_T AHT10_SWI2C_WriteBulk(AHT10_HandleType* AHT10x,UINT8_T* pVal, UINT8_T length)
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
UINT8_T AHT10_HWI2C_WriteBulk(AHT10_HandleType* AHT10x, UINT8_T* pVal, UINT8_T length)
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
		//---�������ݣ��ڲ��Ĵ�������
		_return = I2CTask_MHW_PollMode_SendByte(&(AHT10x->msgI2C), pVal[i], ((i == (length - 1)) ? 1 : 0));
		if (_return != OK_0)
		{
			//---�������ݴ���
			_return = (ERROR_3 + i);
			goto GoToExit;
		}
	}
	//---�˳���ں���
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MHW_PollMode_STOP(&(AHT10x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AHT10_I2C_WriteBulk(AHT10_HandleType* AHT10x, UINT8_T* pVal, UINT8_T length)
{
	if (AHT10x->msgI2C.msgHwMode == 0)
	{
		//---���ģ��I2C
		return AHT10_SWI2C_WriteBulk(AHT10x,pVal, length);
	}
	else
	{
		I2CTask_MHW_CheckClock(&(AHT10x->msgI2C));
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
UINT8_T AHT10_SWI2C_ReadBulk(AHT10_HandleType* AHT10x, UINT8_T* pVal, UINT8_T length)
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
		//---����Ӧ���ź�
		I2CTask_MSW_SendACK(&(AHT10x->msgI2C), (i == (length - 1)) ? 1 : 0);
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
UINT8_T AHT10_HWI2C_ReadBulk(AHT10_HandleType* AHT10x, UINT8_T* pVal, UINT8_T length)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---������ȡ����
	_return = I2CTask_MHW_PollMode_START(&(AHT10x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---����������ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---��������
	for (i = 0; i < length; i++)
	{
		//---����Ӧ���ź�
		I2CTask_MHW_SendACK(&(AHT10x->msgI2C), (i == (length - 1)) ? 1 : 0);
		//---��ȡ����
		pVal[i] = I2CTask_MHW_PollMode_ReadByte(&(AHT10x->msgI2C));
	}
	_return = OK_0;
	//---�˳���ں���
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MHW_PollMode_STOP(&(AHT10x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AHT10_I2C_ReadBulk(AHT10_HandleType* AHT10x, UINT8_T* pVal, UINT8_T length)
{
	if (AHT10x->msgI2C.msgHwMode == 0)
	{
		//---���ģ��I2C
		return AHT10_SWI2C_ReadBulk(AHT10x, pVal, length);
	}
	else
	{
		I2CTask_MHW_CheckClock(&(AHT10x->msgI2C));
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
UINT8_T AHT10_I2C_Config(AHT10_HandleType* AHT10x)
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
UINT8_T AHT10_I2C_StartMeasure(AHT10_HandleType* AHT10x)
{
	UINT8_T tempCMD[3] = { AHT10_CMD_MEASURE,0x33,0x00 };
	//---���Ͳ�������
	UINT8_T _return=AHT10_I2C_WriteBulk(AHT10x, tempCMD, 3);
	//---��ȡʱ�����
	AHT10x->msgRecordTick= AHT10x->msgI2C.pMsgTimeTick();
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ǰ״̬
//////�������:
//////�������: 0---���Զ�ȡ��1---�����ȡʱ�仹û�е���������ȡ
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AHT10_I2C_STATE(AHT10_HandleType* AHT10x)
{	
	//---��ǰʱ��ڵ�
	UINT32_T nowTime = AHT10x->msgI2C.pMsgTimeTick();
	UINT32_T cnt = 0;
	//---�жϵδ�ʱ�Ƿ����������
	if (AHT10x->msgRecordTick > nowTime)
	{
		cnt = (0xFFFFFFFF - AHT10x->msgRecordTick + nowTime);
	}
	else
	{
		cnt = nowTime - AHT10x->msgRecordTick;
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
UINT8_T AHT10_I2C_ReadTempHumi(AHT10_HandleType* AHT10x)
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
		AHT10x->msgTemp =(AHT10x->msgTemp<<8)+ tempVal[4];
		AHT10x->msgTemp = (AHT10x->msgTemp << 8) + tempVal[5];
		//---У���¶��ǲ��Ǹ�ֵ
		if (AHT10x->msgTemp>0x40000)
		{
			//---�¶�����������
			AHT10x->msgPositive = 0;
		}
		else
		{
			//---�¶������Ǹ���
			AHT10x->msgPositive = 1;
		}
		AHT10x->msgTemp = (INT32_T)((((200.0 * (float)AHT10x->msgTemp) / 1048576.0) - 50.0) * 100.0);
		//---����ʪ��ֵ
		//AHT10x->msgHumi = ((tempVal[1] << 16) | (tempVal[2] << 8) | tempVal[3]) >> 4;
		AHT10x->msgHumiX10000 = tempVal[1];
		AHT10x->msgHumiX10000 =(AHT10x->msgHumiX10000<<8)+ tempVal[2];
		AHT10x->msgHumiX10000 = (AHT10x->msgHumiX10000 << 8) + (tempVal[3]>>4);
		AHT10x->msgHumiX10000 = (INT32_T)((float)AHT10x->msgHumiX10000 * 10000.0 / 1048576.0);
	}
	//---�����´β���װ��װ��
	AHT10_I2C_StartMeasure(AHT10x);
	//---���ؽ��
	return ((_return==OK_0)?OK_0:(_return+ERROR_1));
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ�¶�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
float AHT10_I2C_GetTemp(AHT10_HandleType* AHT10x)
{
	float tempVal = AHT10x->msgTemp;
	//---ת���¶ȶ�Ӧʵ�ʵ��¶�ֵ
	tempVal /= 100.0;
	//---У���ǲ�������
	if (AHT10x->msgPositive == 1)
	{
		tempVal *= (-1.0);
	}
	return tempVal;
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡʪ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
float AHT10_I2C_GetHumi(AHT10_HandleType* AHT10x)
{
	float tempVal = AHT10x->msgHumiX10000;
	//---ת���¶ȶ�Ӧʵ�ʵ��¶�ֵ
	tempVal /= 10000.0;
	return tempVal;
}


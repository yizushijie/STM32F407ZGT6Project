#include "max961x_cfg.h"

//===ȫ�ֱ�������
MAX961X_HandleType		g_Max961xDevice0 = { 0 };
pMAX961X_HandleType	pMax961xDevice0 = &g_Max961xDevice0;

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_I2C_Device0_Init(MAX961X_HandleType* MAX961x)
{
	MAX961x->msgI2C.pMsgI2Cx = NULL;
	MAX961x->msgI2C.msgSCL.msgPort = GPIOB;
	MAX961x->msgI2C.msgSCL.msgBit = LL_GPIO_PIN_6;
	MAX961x->msgI2C.msgSDA.msgPort = GPIOB;
	MAX961x->msgI2C.msgSDA.msgBit = LL_GPIO_PIN_7;
	MAX961x->msgI2C.msgHwMode = 0;
	MAX961x->msgI2C.msgPluseWidth = 2;
	MAX961x->msgI2C.pMsgDelayus = NULL;
	MAX961x->msgI2C.msgAddr = MAX961X_WADDR;
	MAX961x->msgI2C.msgClockSpeed = 200000;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_I2C_Device1_Init(MAX961X_HandleType* MAX961x)
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
UINT8_T MAX961X_I2C_Device2_Init(MAX961X_HandleType* MAX961x)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:isHWI2C---1 Ӳ����0 ���
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_I2C_Init(MAX961X_HandleType* MAX961x, void(*pFuncDelayus)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHWI2C)
{
	UINT8_T _return = OK_0;
	//---ָ���豸�ĳ�ʼ��
	if ((MAX961x != NULL) && (MAX961x == MAX961X_TASK_ONE))
	{
		MAX961X_I2C_Device0_Init(MAX961x);
	}
	else if ((MAX961x != NULL) && (MAX961x == MAX961X_TASK_TWO))
	{
		MAX961X_I2C_Device1_Init(MAX961x);
	}
	else if ((MAX961x != NULL) && (MAX961x == MAX961X_TASK_THREE))
	{
		MAX961X_I2C_Device2_Init(MAX961x);
	}
	else
	{
		return ERROR_1;
	}
	//---�ж���Ӳ��I2C�������I2C
	(isHWI2C != 0) ? (_return = I2CTask_MHW_Init(&(MAX961x->msgI2C), pFuncDelayus,pFuncTimerTick)) : (_return = I2CTask_MSW_Init(&(MAX961x->msgI2C), pFuncDelayus, pFuncTimerTick));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ע��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_I2C_DeInit(MAX961X_HandleType* MAX961x)
{
	return I2CTask_Master_DeInit(&(MAX961x->msgI2C));	
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������д��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_SWI2C_WriteSingle(MAX961X_HandleType* MAX961x, UINT8_T addr, UINT8_T val)
{
	UINT8_T _return = OK_0;
	//---����IIC������������ַ��д����
	_return = I2CTask_MSW_START(&(MAX961x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_1;
		goto GoToExit;
	}
	//---���ͼĴ�����ַ,��λ��ַ
	I2CTask_MSW_SendByte(&(MAX961x->msgI2C), addr);
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(MAX961x->msgI2C));
	if (_return != OK_0)
	{
		//---���ͼĴ�����ַ����
		_return = ERROR_2;
		goto GoToExit;
	}
	//---��������
	I2CTask_MSW_SendByte(&(MAX961x->msgI2C), val);
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(MAX961x->msgI2C));
	if (_return != OK_0)
	{
		//---�������ݴ���
		_return = ERROR_3;
		goto GoToExit;
	}
	//---�˳��������
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(MAX961x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������д��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_SWI2C_WriteBulk(MAX961X_HandleType* MAX961x, UINT8_T addr,UINT8_T length, UINT8_T *pVal)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---����IIC������������ַ��д����
	_return = I2CTask_MSW_START(&(MAX961x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_1;
		goto GoToExit;
	}
	//---���ͼĴ�����ַ,��λ��ַ
	I2CTask_MSW_SendByte(&(MAX961x->msgI2C), addr);
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(MAX961x->msgI2C));
	if (_return != OK_0)
	{
		//---���ͼĴ�����ַ����
		_return = ERROR_2;
		goto GoToExit;
	}
	//---���Ͷ��ֽ�����
	for (i=0;i<length;i++)
	{
		//---��������
		I2CTask_MSW_SendByte(&(MAX961x->msgI2C), pVal[i]);

		//---��ȡACK
		_return = I2CTask_MSW_ReadACK(&(MAX961x->msgI2C));
		if (_return != OK_0)
		{
			//---�������ݴ���
			_return = ERROR_3+i;
			goto GoToExit;
		}
	}	
	//---�˳��������
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(MAX961x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������д��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_HWI2C_WriteSingle(MAX961X_HandleType* MAX961x, UINT8_T addr, UINT8_T val)
{
	UINT8_T _return = OK_0;
	//---����IIC������������ַ��д����
	_return = I2CTask_MHW_PollMode_START(&(MAX961x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_1;
		goto GoToExit;
	}
	//---���ͼĴ�����ַ,�洢��Ԫ�ĵ�ַ
	_return = I2CTask_MHW_PollMode_SendByte(&(MAX961x->msgI2C), addr, 0);
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---�������ݣ��ڲ��Ĵ�������
	_return = I2CTask_MHW_PollMode_SendByte(&(MAX961x->msgI2C), val, 1);
	if (_return != OK_0)
	{
		//---�������ݴ���
		_return = ERROR_3;
		goto GoToExit;
	}
	//---�˳��������
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MHW_PollMode_STOP(&(MAX961x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������д��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_HWI2C_WriteBulk(MAX961X_HandleType* MAX961x, UINT8_T addr, UINT8_T length, UINT8_T* pVal)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---����IIC������������ַ��д����
	_return = I2CTask_MHW_PollMode_START(&(MAX961x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_1;
		goto GoToExit;
	}
	//---���ͼĴ�����ַ,�ڲ��Ĵ�����ַ
	I2CTask_MSW_SendByte(&(MAX961x->msgI2C), addr);
	//---���ͼĴ�����ַ,�洢��Ԫ�ĵ�ַ
	_return = I2CTask_MHW_PollMode_SendByte(&(MAX961x->msgI2C), addr, 0);
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---���Ͷ��ֽ�����
	for (i = 0; i < length; i++)
	{
		//---�������ݣ��ڲ��Ĵ�������
		_return = I2CTask_MHW_PollMode_SendByte(&(MAX961x->msgI2C), pVal[i], ((i == (length - 1)) ? 1 : 0));
		if (_return != OK_0)
		{
			//---�������ݴ���
			_return = (ERROR_3 + i);
			goto GoToExit;
		}
	}
	//---�˳��������
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MHW_PollMode_STOP(&(MAX961x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������ݶ�ȡ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_I2C_WriteSingle(MAX961X_HandleType* MAX961x, UINT8_T addr, UINT8_T val)
{
	if (MAX961x->msgI2C.msgHwMode != 0)
	{
		I2CTask_MHW_CheckClock(&(MAX961x->msgI2C));
		//---Ӳ��I2C
		return MAX961X_HWI2C_WriteSingle(MAX961x, addr, val);
	}
	else
	{
		return MAX961X_SWI2C_WriteSingle(MAX961x, addr, val);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������ݶ�ȡ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_I2C_WriteBulk(MAX961X_HandleType* MAX961x, UINT8_T addr, UINT8_T length, UINT8_T* pVal)
{
	if (MAX961x->msgI2C.msgHwMode == 1)
	{
		I2CTask_MHW_CheckClock(&(MAX961x->msgI2C));
		//---Ӳ��I2C
		return MAX961X_HWI2C_WriteBulk(MAX961x, addr, length, pVal);
	}
	else
	{
		return MAX961X_SWI2C_WriteBulk(MAX961x, addr, length, pVal);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������ݶ�ȡ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_SWI2C_ReadSingle(MAX961X_HandleType* MAX961x, UINT8_T addr, UINT8_T *pVal)
{
	UINT8_T _return = OK_0;
	//---����IIC������������ַ��д����
	_return = I2CTask_MSW_START(&(MAX961x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_1;
		goto GoToExit;
	}
	//---���ͼĴ�����ַ,�ߵ�ַ
	I2CTask_MSW_SendByte(&(MAX961x->msgI2C), addr);
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(MAX961x->msgI2C));
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---����IIC������������ַ��������
	_return = I2CTask_MSW_START(&(MAX961x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---����������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}
	//---��ȡ����
	*pVal = I2CTask_MSW_ReadByte(&(MAX961x->msgI2C));
	//---���Ͳ�Ӧ���ź�
	_return= I2CTask_MSW_SendACK(&(MAX961x->msgI2C), 1);
	//---�˳����
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(MAX961x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������ݶ�ȡ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_SWI2C_ReadBulk(MAX961X_HandleType* MAX961x, UINT8_T addr, UINT8_T length, UINT8_T* pVal)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---����IIC������������ַ��д����
	_return = I2CTask_MSW_START(&(MAX961x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_1;
		goto GoToExit;
	}
	//---���ͼĴ�����ַ,�ߵ�ַ
	I2CTask_MSW_SendByte(&(MAX961x->msgI2C), addr);

	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(MAX961x->msgI2C));
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---����IIC������������ַ��������
	_return = I2CTask_MSW_START(&(MAX961x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---����������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}
	for (i=0;i<length;i++)
	{
		//---��ȡ����
		pVal[i] = I2CTask_MSW_ReadByte(&(MAX961x->msgI2C));
		//---����Ӧ���ź�
		I2CTask_MSW_SendACK(&(MAX961x->msgI2C), (i == (length - 1)) ? 1 : 0);
	}
	_return = OK_0;
	//---�˳����
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(MAX961x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������ݶ�ȡ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_HWI2C_ReadSingle(MAX961X_HandleType* MAX961x, UINT8_T addr, UINT8_T* pVal)
{
	UINT8_T _return = OK_0;
	//---����IIC������������ַ��д����
	_return = I2CTask_MHW_PollMode_START(&(MAX961x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_1;
		goto GoToExit;
	}
	//---���ͼĴ�����ַ,�洢��Ԫ�ĵ�ַ
	_return = I2CTask_MHW_PollMode_SendByte(&(MAX961x->msgI2C), addr, 0);
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---����IIC������������ַ��������
	_return = I2CTask_MHW_PollMode_START(&(MAX961x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---����������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}
	//---���Ͳ�Ӧ���ź�
	_return = I2CTask_MHW_SendACK(&(MAX961x->msgI2C), 1);
	//---��ȡ����
	*pVal = I2CTask_MHW_PollMode_ReadByte(&(MAX961x->msgI2C));
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MHW_PollMode_STOP(&(MAX961x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������ݶ�ȡ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_HWI2C_ReadBulk(MAX961X_HandleType* MAX961x, UINT8_T addr, UINT8_T length, UINT8_T* pVal)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---����IIC������������ַ��д����
	_return = I2CTask_MHW_PollMode_START(&(MAX961x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_1;
		goto GoToExit;
	}
	//---���ͼĴ�����ַ,�洢��Ԫ�ĵ�ַ
	_return = I2CTask_MHW_PollMode_SendByte(&(MAX961x->msgI2C), addr, 0);
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---����IIC������������ַ��������
	_return = I2CTask_MHW_PollMode_START(&(MAX961x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---����������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}
	//---������ȡ6������
	for (i = 0; i < length; i++)
	{
		//---����Ӧ���ź�
		I2CTask_MHW_SendACK(&(MAX961x->msgI2C), (i == (length - 1)) ? 1 : 0);
		//---��ȡ����
		pVal[i] = I2CTask_MHW_PollMode_ReadByte(&(MAX961x->msgI2C));
	}
	_return = OK_0;
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MHW_PollMode_STOP(&(MAX961x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������ݶ�ȡ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_I2C_ReadSingle(MAX961X_HandleType* MAX961x, UINT8_T addr, UINT8_T* pVal)
{
	if (MAX961x->msgI2C.msgHwMode!=0)
	{
		I2CTask_MHW_CheckClock(&(MAX961x->msgI2C));
		//---Ӳ��I2C
		return MAX961X_HWI2C_ReadSingle(MAX961x, addr, pVal);
	}
	else
	{
		return MAX961X_SWI2C_ReadSingle(MAX961x, addr, pVal);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������ݶ�ȡ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_I2C_ReadBulk(MAX961X_HandleType* MAX961x, UINT8_T addr, UINT8_T length, UINT8_T* pVal)
{
	if (MAX961x->msgI2C.msgHwMode != 0)
	{
		I2CTask_MHW_CheckClock(&(MAX961x->msgI2C));
		//---Ӳ��I2C
		return MAX961X_HWI2C_ReadBulk(MAX961x, addr,length, pVal);
	}
	else
	{
		return MAX961X_SWI2C_ReadBulk(MAX961x, addr, length, pVal);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�У���豸
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_I2C_CheckDevice(MAX961X_HandleType* MAX961x)
{
	UINT8_T _return = 0;
	MAX961X_I2C_ReadSingle(MAX961x, MAX961X_REG_TEMP_DATA_MSB_ADDR, &_return);
	if (_return==0x80)
	{
		MAX961x->msgID=_return;
		return OK_0;
	}
	else
	{
		MAX961x->msgID=0x00;
		return ERROR_1;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ�������ѹ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_I2C_ReadRSVoltage(MAX961X_HandleType* MAX961x)
{
	UINT8_T _return = OK_0 ;
	UINT8_T adcTemp[2] = {0};
	//---׼����ȡ �����ѹ
	_return = MAX961X_I2C_WriteSingle(MAX961x, MAX961X_REG_CONTROL_REG1, MAX961X_READ_CHANNEL_INPUT_VOLTAGE);
	if (_return==OK_0)
	{
		//---��ȡ�����ѹ��ֵ
		_return = MAX961X_I2C_ReadBulk(MAX961x, MAX961X_REG_RS_DATA_MSB_ADDR, 2, adcTemp);
		//---����ɼ���������
		MAX961x->msgRSVoltagemV = adcTemp[0];
		MAX961x->msgRSVoltagemV =(MAX961x->msgRSVoltagemV*256)+ adcTemp[1];
		//---�õ�ʵ�ʵĲɼ���,���ݸ�ʽ������룬����λ��Ч
		MAX961x->msgRSVoltagemV = ((UINT16_T)MAX961x->msgRSVoltagemV >> 4);//-4;
		MAX961x->msgRSVoltagemV *= MAX961X_VOLTAGE_STEP_MV;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ�������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_I2C_ReadRSCurrent(MAX961X_HandleType* MAX961x,UINT8_T currentGain)
{
	UINT8_T _return = OK_0;
	UINT8_T gain = 1;
	UINT8_T adcTemp[2] = { 0 };
	currentGain &= 0x03;
	//---׼����ȡ���ص���
	_return = MAX961X_I2C_WriteSingle(MAX961x, MAX961X_REG_CONTROL_REG1, currentGain);
	if (_return == OK_0)
	{
		gain <<= currentGain;
		//---��ȡ�����ѹ��ֵ
		_return = MAX961X_I2C_ReadBulk(MAX961x, MAX961X_REG_CSA_DATA_MSB_ADDR, 2, adcTemp);
		//---����ɼ���������
		MAX961x->msgRSCurrentmA = adcTemp[0];
		MAX961x->msgRSCurrentmA = (MAX961x->msgRSCurrentmA*256) + adcTemp[1];
		//---�õ�ʵ�ʵĲɼ���,���ݸ�ʽ������룬����λ��Ч
		MAX961x->msgRSCurrentmA = ((UINT16_T)MAX961x->msgRSCurrentmA >> 4);
		//---�õ�X1��ѹֵ����λmV
		MAX961x->msgRSCurrentmA *= MAX961X_CURRENT_STEP_MA;
		//---�õ�ʵ�������ѹֵ����λmV
		MAX961x->msgRSCurrentmA /= gain;
		//---�������ֵ
		MAX961x->msgRSCurrentmA /= MAX961X_SAMPLE_RES_MR;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_I2C_ReadOutVoltage(MAX961X_HandleType* MAX961x)
{
	UINT8_T _return = OK_0;
	UINT8_T adcTemp[2] = { 0 };
	//---׼����ȡ �����ѹ
	_return = MAX961X_I2C_WriteSingle(MAX961x, MAX961X_REG_CONTROL_REG1, MAX961X_READ_CHANNEL_OUTPUT_VOLTAGE);
	if (_return == OK_0)
	{
		//---��ȡOUT�˵������ѹ��ֵ
		_return = MAX961X_I2C_ReadBulk(MAX961x, MAX961X_REG_OUT_DATA_MSB_ADDR, 2, adcTemp);
		//---����ɼ���������,���ݸ�ʽ������룬����λ��Ч
		MAX961x->msgOutputVoltagemV = adcTemp[0];
		MAX961x->msgOutputVoltagemV = (MAX961x->msgOutputVoltagemV*256) + adcTemp[1];
		//---�õ�ʵ�ʵĲɼ���
		MAX961x->msgOutputVoltagemV = ((UINT16_T)MAX961x->msgOutputVoltagemV >> 4);
		MAX961x->msgOutputVoltagemV *= MAX961X_VOLTAGE_STEP_MV;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_I2C_ReadSetVoltage(MAX961X_HandleType* MAX961x)
{
	UINT8_T _return = OK_0;
	UINT8_T adcTemp[2] = { 0 };
	//---׼����ȡ �����ѹ
	_return = MAX961X_I2C_WriteSingle(MAX961x, MAX961X_REG_CONTROL_REG1, MAX961X_READ_CHANNEL_SET_VOLTAGE);
	if (_return == OK_0)
	{
		//---��ȡSET�˵������ѹ��ֵ
		_return = MAX961X_I2C_ReadBulk(MAX961x, MAX961X_REG_SET_DATA_MSB_ADDR, 2, adcTemp);
		//---����ɼ���������
		MAX961x->msgSetVoltagemV = adcTemp[0];
		MAX961x->msgSetVoltagemV = (MAX961x->msgSetVoltagemV*256) + adcTemp[1];
		//---�õ�ʵ�ʵĲɼ���,���ݸ�ʽ������룬����λ��Ч
		MAX961x->msgSetVoltagemV = ((UINT16_T)MAX961x->msgSetVoltagemV >> 4);
		MAX961x->msgSetVoltagemV *= MAX961X_VOLTAGE_STEP_MV;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ�ڲ��¶�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_I2C_ReadTemp(MAX961X_HandleType* MAX961x)
{
	UINT8_T _return = OK_0;
	UINT8_T adcTemp[2] = { 0 };
	//---׼����ȡ �ڲ��¶�
	_return = MAX961X_I2C_WriteSingle(MAX961x, MAX961X_REG_CONTROL_REG1, MAX961X_READ_CHANNEL_TEMPERATURE);
	if (_return == OK_0)
	{
		//---��ȡ�ڲ��¶�
		_return = MAX961X_I2C_ReadBulk(MAX961x, MAX961X_REG_TEMP_DATA_MSB_ADDR, 2, adcTemp);
		//---����ɼ���������
		MAX961x->msgTemperatureC = adcTemp[0];
		MAX961x->msgTemperatureC = (MAX961x->msgTemperatureC*256) + adcTemp[1];
		//---�õ�ʵ�ʵĲɼ���,���ݸ�ʽ������룬����λ��Ч
		MAX961x->msgTemperatureC = ((UINT16_T)MAX961x->msgTemperatureC >> 7);
		//---�õ�ʵ�ʵĲɼ���
		if (adcTemp[0]&0x80)
		{
			//---�¶��Ǹ�ֵ
			MAX961x->msgTemperatureC = (0x200 - ((UINT16_T)MAX961x->msgTemperatureC));
			MAX961x->msgTemperatureC *= (-1);
		}
		MAX961x->msgTemperatureC *= MAX961X_TEMPERATURE_STEP_C;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_I2C_ReadAll(MAX961X_HandleType* MAX961x, UINT8_T currentGain)
{
	UINT8_T _return = OK_0;
	_return = MAX961X_I2C_ReadRSVoltage( MAX961x);
	_return|= MAX961X_I2C_ReadRSCurrent( MAX961x,  currentGain);
	_return|= MAX961X_I2C_ReadOutVoltage( MAX961x);
	_return|= MAX961X_I2C_ReadSetVoltage( MAX961x);
	_return|=MAX961X_I2C_ReadTemp( MAX961x);
	return _return;
}
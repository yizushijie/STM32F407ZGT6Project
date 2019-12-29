#include "max961x_cfg.h"

//===ȫ�ֱ�������
MAX961X_HandlerType		g_Max961xDevice0 = { 0 };
pMAX961X_HandlerType	pMax961xDevice0 = &g_Max961xDevice0;

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:isHWI2C---1 Ӳ����0 ���
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_I2C_Init(MAX961X_HandlerType* MAX961x, void(*pFuncDelayus)(UINT32_T delay), UINT8_T isHWI2C)
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
	if (isHWI2C)
	{
		//---��ʼ��Ӳ��I2C
		_return = I2CTask_MHW_Init(&(MAX961x->msgI2C));
		//---����ΪӲ��ģʽ
		MAX961x->msgI2C.msgModelIsHW = 1;
	}
	else
	{
		//---��ʼ�����ģ��I2C
		_return = I2CTask_MSW_Init(&(MAX961x->msgI2C), pFuncDelayus);
		//---����Ϊ�����ģʽ
		MAX961x->msgI2C.msgModelIsHW = 0;
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
UINT8_T MAX961X_I2C_Device0_Init(MAX961X_HandlerType* MAX961x)
{
	MAX961x->msgI2C.msgI2Cx = NULL;
	MAX961x->msgI2C.msgSCL.msgGPIOPort = GPIOB;
	MAX961x->msgI2C.msgSCL.msgGPIOBit = LL_GPIO_PIN_6;
	MAX961x->msgI2C.msgSDA.msgGPIOPort = GPIOB;
	MAX961x->msgI2C.msgSDA.msgGPIOBit = LL_GPIO_PIN_7;
	MAX961x->msgI2C.msgModelIsHW = 0;
	MAX961x->msgI2C.msgPluseWidth = 2;
	MAX961x->msgI2C.msgDelayus = NULL;
	MAX961x->msgI2C.msgAddr = MAX961X_WADDR;
	MAX961x->msgI2C.msgClockSpeed = 0;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_I2C_Device1_Init(MAX961X_HandlerType* MAX961x)
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
UINT8_T MAX961X_I2C_Device2_Init(MAX961X_HandlerType* MAX961x)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������д��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_SWI2C_SingleWriteReg(MAX961X_HandlerType* MAX961x, UINT8_T addr, UINT8_T val)
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
UINT8_T MAX961X_SWI2C_BurstWriteReg(MAX961X_HandlerType* MAX961x, UINT8_T addr,UINT8_T length, UINT8_T *pVal)
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
UINT8_T MAX961X_HWI2C_SingleWriteReg(MAX961X_HandlerType* MAX961x, UINT8_T addr, UINT8_T val)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������д��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_HWI2C_BurstWriteReg(MAX961X_HandlerType* MAX961x, UINT8_T addr, UINT8_T length, UINT8_T* pVal)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������ݶ�ȡ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_I2C_SingleWriteReg(MAX961X_HandlerType* MAX961x, UINT8_T addr, UINT8_T val)
{
	if (MAX961x->msgI2C.msgModelIsHW == 1)
	{
		return MAX961X_HWI2C_SingleWriteReg(MAX961x, addr, val);
	}
	else
	{
		return MAX961X_SWI2C_SingleWriteReg(MAX961x, addr, val);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������ݶ�ȡ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_I2C_BurstWriteReg(MAX961X_HandlerType* MAX961x, UINT8_T addr, UINT8_T length, UINT8_T* pVal)
{
	if (MAX961x->msgI2C.msgModelIsHW == 1)
	{
		return MAX961X_HWI2C_BurstWriteReg(MAX961x, addr, length, pVal);
	}
	else
	{
		return MAX961X_SWI2C_BurstWriteReg(MAX961x, addr, length, pVal);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������ݶ�ȡ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_SWI2C_SingleReadReg(MAX961X_HandlerType* MAX961x, UINT8_T addr, UINT8_T *pVal)
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
UINT8_T MAX961X_SWI2C_BurstReadReg(MAX961X_HandlerType* MAX961x, UINT8_T addr, UINT8_T length, UINT8_T* pVal)
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
		if (i == (length - 1))
		{
			_return = 1;
		}

		//---����Ӧ���ź�
		I2CTask_MSW_SendACK(&(MAX961x->msgI2C), _return);
	}
	_return = OK_0;
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
UINT8_T MAX961X_HWI2C_SingleReadReg(MAX961X_HandlerType* MAX961x, UINT8_T addr, UINT8_T* pVal)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������ݶ�ȡ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_HWI2C_BurstReadReg(MAX961X_HandlerType* MAX961x, UINT8_T addr, UINT8_T length, UINT8_T* pVal)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������ݶ�ȡ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_I2C_SingleReadReg(MAX961X_HandlerType* MAX961x, UINT8_T addr, UINT8_T* pVal)
{
	if (MAX961x->msgI2C.msgModelIsHW==1)
	{
		return MAX961X_HWI2C_SingleReadReg(MAX961x, addr, pVal);
	}
	else
	{
		return MAX961X_SWI2C_SingleReadReg(MAX961x, addr, pVal);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������ݶ�ȡ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_I2C_BurstReadReg(MAX961X_HandlerType* MAX961x, UINT8_T addr, UINT8_T length, UINT8_T* pVal)
{
	if (MAX961x->msgI2C.msgModelIsHW == 1)
	{
		return MAX961X_HWI2C_BurstReadReg(MAX961x, addr,length, pVal);
	}
	else
	{
		return MAX961X_SWI2C_BurstReadReg(MAX961x, addr, length, pVal);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�У���豸
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_I2C_CheckDevice(MAX961X_HandlerType* MAX961x)
{
	UINT8_T _return = 0;
	MAX961X_I2C_SingleReadReg(MAX961x, MAX961X_REG_TEMP_DATA_MSB_ADDR, &_return);
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
UINT8_T MAX961X_I2C_GetRSVoltage(MAX961X_HandlerType* MAX961x)
{
	UINT8_T _return = OK_0 ;
	UINT8_T adcTemp[2] = {0};
	//---׼����ȡ �����ѹ
	_return = MAX961X_I2C_SingleWriteReg(MAX961x, MAX961X_REG_CONTROL_REG1, MAX961X_READ_CHANNEL_INPUT_VOLTAGE);
	if (_return==OK_0)
	{
		//---��ȡ�����ѹ��ֵ
		_return = MAX961X_I2C_BurstReadReg(MAX961x, MAX961X_REG_RS_DATA_MSB_ADDR, 2, adcTemp);
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
UINT8_T MAX961X_I2C_GetRSCurrent(MAX961X_HandlerType* MAX961x,UINT8_T currentGain)
{
	UINT8_T _return = OK_0;
	UINT8_T gain = 1;
	UINT8_T adcTemp[2] = { 0 };
	currentGain &= 0x03;
	//---׼����ȡ���ص���
	_return = MAX961X_I2C_SingleWriteReg(MAX961x, MAX961X_REG_CONTROL_REG1, currentGain);
	if (_return == OK_0)
	{
		gain <<= currentGain;
		//---��ȡ�����ѹ��ֵ
		_return = MAX961X_I2C_BurstReadReg(MAX961x, MAX961X_REG_CSA_DATA_MSB_ADDR, 2, adcTemp);
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
UINT8_T MAX961X_I2C_GetOutVoltage(MAX961X_HandlerType* MAX961x)
{
	UINT8_T _return = OK_0;
	UINT8_T adcTemp[2] = { 0 };
	//---׼����ȡ �����ѹ
	_return = MAX961X_I2C_SingleWriteReg(MAX961x, MAX961X_REG_CONTROL_REG1, MAX961X_READ_CHANNEL_OUTPUT_VOLTAGE);
	if (_return == OK_0)
	{
		//---��ȡOUT�˵������ѹ��ֵ
		_return = MAX961X_I2C_BurstReadReg(MAX961x, MAX961X_REG_OUT_DATA_MSB_ADDR, 2, adcTemp);
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
UINT8_T MAX961X_I2C_GetSetVoltage(MAX961X_HandlerType* MAX961x)
{
	UINT8_T _return = OK_0;
	UINT8_T adcTemp[2] = { 0 };
	//---׼����ȡ �����ѹ
	_return = MAX961X_I2C_SingleWriteReg(MAX961x, MAX961X_REG_CONTROL_REG1, MAX961X_READ_CHANNEL_SET_VOLTAGE);
	if (_return == OK_0)
	{
		//---��ȡSET�˵������ѹ��ֵ
		_return = MAX961X_I2C_BurstReadReg(MAX961x, MAX961X_REG_SET_DATA_MSB_ADDR, 2, adcTemp);
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
UINT8_T MAX961X_I2C_GetTemperature(MAX961X_HandlerType* MAX961x)
{
	UINT8_T _return = OK_0;
	UINT8_T adcTemp[2] = { 0 };
	//---׼����ȡ �ڲ��¶�
	_return = MAX961X_I2C_SingleWriteReg(MAX961x, MAX961X_REG_CONTROL_REG1, MAX961X_READ_CHANNEL_TEMPERATURE);
	if (_return == OK_0)
	{
		//---��ȡ�ڲ��¶�
		_return = MAX961X_I2C_BurstReadReg(MAX961x, MAX961X_REG_TEMP_DATA_MSB_ADDR, 2, adcTemp);
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
UINT8_T MAX961X_I2C_GetAll(MAX961X_HandlerType* MAX961x, UINT8_T currentGain)
{
	UINT8_T _return = OK_0;
	_return = MAX961X_I2C_GetRSVoltage( MAX961x);
	_return|= MAX961X_I2C_GetRSCurrent( MAX961x,  currentGain);
	_return|= MAX961X_I2C_GetOutVoltage( MAX961x);
	_return|= MAX961X_I2C_GetSetVoltage( MAX961x);
	_return|=MAX961X_I2C_GetTemperature( MAX961x);
	return _return;
}
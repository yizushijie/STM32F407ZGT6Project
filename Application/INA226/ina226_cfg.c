#include "ina226_cfg.h"

//===ȫ�ֱ�������
INA226_HandlerType		g_Ina226Device0 = { 0 };
pINA226_HandlerType		pIna226Device0 = &g_Ina226Device0;

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ���ʼ��
//////�������:isHWI2C---1 Ӳ����0 ���
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_I2C_Init(INA226_HandlerType* INA226x, void(*pFuncDelayus)(UINT32_T delay), UINT8_T isHWI2C)
{
	UINT8_T _return = OK_0;

	//---ָ���豸�ĳ�ʼ��
	if ((INA226x != NULL) && (INA226x == INA226_TASK_ONE))
	{
		INA226_I2C_Device0_Init(INA226x);
	}
	else if ((INA226x != NULL) && (INA226x == INA226_TASK_TWO))
	{
		INA226_I2C_Device1_Init(INA226x);
	}
	else if ((INA226x != NULL) && (INA226x == INA226_TASK_THREE))
	{
		INA226_I2C_Device2_Init(INA226x);
	}
	else
	{
		return ERROR_1;
	}

	//---�ж���Ӳ��I2C�������I2C
	if (isHWI2C)
	{
		//---��ʼ��Ӳ��I2C
		_return = I2CTask_MHW_Init(&(INA226x->msgI2C));
		//---����ΪӲ��ģʽ
		INA226x->msgI2C.msgModelIsHW = 1;
	}
	else
	{
		//---��ʼ�����ģ��I2C
		_return = I2CTask_MSW_Init(&(INA226x->msgI2C), pFuncDelayus);
		//---����Ϊ�����ģʽ
		INA226x->msgI2C.msgModelIsHW = 0;
	}
	//---���ó�ʼ��
	_return = INA226_ConfigInit(INA226x);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_I2C_Device0_Init(INA226_HandlerType* INA226x)
{
	INA226x->msgI2C.msgI2Cx = NULL;
	INA226x->msgI2C.msgSCL.msgGPIOPort = GPIOB;
	INA226x->msgI2C.msgSCL.msgGPIOBit = LL_GPIO_PIN_6;
	INA226x->msgI2C.msgSDA.msgGPIOPort = GPIOB;
	INA226x->msgI2C.msgSDA.msgGPIOBit = LL_GPIO_PIN_7;
	INA226x->msgI2C.msgModelIsHW = 0;
	INA226x->msgI2C.msgPluseWidth = 2;
	INA226x->msgI2C.msgDelayus = NULL;
	INA226x->msgI2C.msgAddr = 0x80;
	INA226x->msgI2C.msgClockSpeed = 0;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_I2C_Device1_Init(INA226_HandlerType* INA226x)
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
UINT8_T INA226_I2C_Device2_Init(INA226_HandlerType* INA226x)
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
UINT8_T INA226_SWI2C_WriteReg(INA226_HandlerType* INA226x, UINT8_T addr, UINT16_T val)
{
	UINT8_T _return = OK_0;
	//---����IIC������������ַ��д����
	_return = I2CTask_MSW_START(&(INA226x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_1;
		goto GoToExit;
	}
	//---���ͼĴ�����ַ
	I2CTask_MSW_SendByte(&(INA226x->msgI2C), addr);
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(INA226x->msgI2C));
	if (_return != OK_0)
	{
		//---���ͼĴ�����ַ����
		_return = ERROR_2;
		goto GoToExit;
	}
	//---���͸�λ����
	I2CTask_MSW_SendByte(&(INA226x->msgI2C), (UINT8_T)(val>>16));
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(INA226x->msgI2C));
	if (_return != OK_0)
	{
		//---�������ݴ���
		_return = ERROR_3;
		goto GoToExit;
	}
	//---���͵�λ����
	I2CTask_MSW_SendByte(&(INA226x->msgI2C), (UINT8_T)(val&0xFF));
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(INA226x->msgI2C));
	if (_return != OK_0)
	{
		//---�������ݴ���
		_return = ERROR_4;
		goto GoToExit;
	}
	//---�˳��������
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(INA226x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_HWI2C_WriteReg(INA226_HandlerType* INA226x, UINT8_T addr, UINT16_T val)
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
UINT8_T INA226_I2C_WriteReg(INA226_HandlerType* INA226x, UINT8_T addr, UINT16_T val)
{
	if (INA226x->msgI2C.msgModelIsHW == 1)
	{
		return INA226_HWI2C_WriteReg(INA226x, addr, val);
	}
	else
	{
		return INA226_SWI2C_WriteReg(INA226x, addr, val);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_SWI2C_ReadReg(INA226_HandlerType* INA226x, UINT8_T addr, UINT16_T *pVal)
{
	UINT8_T _return = OK_0;
	UINT16_T readTemp = 0;
	//---����IIC������������ַ��д����
	_return = I2CTask_MSW_START(&(INA226x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---����д����ʧ��
		_return = ERROR_1;
		goto GoToExit;
	}
	//---���ͼĴ�����ַ
	I2CTask_MSW_SendByte(&(INA226x->msgI2C), addr);
	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(INA226x->msgI2C));
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_2;
		goto GoToExit;
	}
	//---����IIC������������ַ��������
	_return = I2CTask_MSW_START(&(INA226x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---����������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}
	//---��ȡ��λ����
	readTemp= I2CTask_MSW_ReadByte(&(INA226x->msgI2C));
	//---����Ӧ���ź�
	_return = I2CTask_MSW_SendACK(&(INA226x->msgI2C), 0);
	readTemp <<= 8;
	//---��ȡ��λ����
	readTemp |= I2CTask_MSW_ReadByte(&(INA226x->msgI2C));
	//---���Ͳ�Ӧ���ź�
	_return = I2CTask_MSW_SendACK(&(INA226x->msgI2C), 1);
	*pVal = readTemp;
GoToExit:
	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(INA226x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_HWI2C_ReadReg(INA226_HandlerType* INA226x, UINT8_T addr, UINT16_T* pVal)
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
UINT8_T INA226_I2C_ReadReg(INA226_HandlerType* INA226x, UINT8_T addr, UINT16_T* pVal)
{
	if (INA226x->msgI2C.msgModelIsHW == 1)
	{
		return INA226_HWI2C_ReadReg(INA226x, addr, pVal);
	}
	else
	{
		return INA226_SWI2C_ReadReg(INA226x, addr, pVal);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��豸ID
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_GetDieID(INA226_HandlerType* INA226x)
{
	UINT16_T deviceID = 0;
	UINT8_T _return = INA226_I2C_ReadReg(INA226x, DIE_ID_REG, &deviceID);
	if (_return==OK_0)
	{
		if (deviceID != 0x2260)
		{
			_return = ERROR_1;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������ID
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_GetManuID(INA226_HandlerType* INA226x)
{
	UINT16_T deviceID = 0;
	UINT8_T _return = INA226_I2C_ReadReg(INA226x, MANUFACTURER_ID_REG, &deviceID);
	if (_return == OK_0)
	{
		if (deviceID != 0x5449)
		{
			_return = ERROR_1;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ���üĴ�����ֵ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_GetCFGReg(INA226_HandlerType* INA226x)
{
	return INA226_I2C_ReadReg(INA226x, CONFIGURATION_REG, &(INA226x->msgCFGReg));
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��������üĴ�����ֵ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_SetCFGReg(INA226_HandlerType* INA226x, UINT16_T val)
{
	INA226x->msgCFGReg = val;
	return INA226_I2C_WriteReg(INA226x, CONFIGURATION_REG, INA226x->msgCFGReg);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���λ�豸
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_Reset(INA226_HandlerType* INA226x)
{
	INA226x->msgCFGReg = 0x4000;
	return INA226_SetCFGReg(INA226x,0xC000);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡУ׼�Ĵ�����ֵ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_GetCalibReg(INA226_HandlerType* INA226x)
{
	return INA226_I2C_ReadReg(INA226x, CALIBRATION_REG, &(INA226x->msgCalibReg));
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����У׼�Ĵ�����ֵ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_SetCalibReg(INA226_HandlerType* INA226x,UINT16_T val)
{
	INA226x->msgCalibReg = val;
	return INA226_I2C_WriteReg(INA226x, CALIBRATION_REG, INA226x->msgCalibReg);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡУ׼�Ĵ�����ֵ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_GetMaskReg(INA226_HandlerType* INA226x)
{
	return INA226_I2C_ReadReg(INA226x, MASK_ENABLE_REG, &(INA226x->msgMaskReg));
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����У׼�Ĵ�����ֵ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_SetMaskReg(INA226_HandlerType* INA226x, UINT16_T val)
{
	INA226x->msgMaskReg=val;
	return INA226_I2C_WriteReg(INA226x, MASK_ENABLE_REG, INA226x->msgMaskReg);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ת��������־λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_ClearConversionReadyFlag(INA226_HandlerType* INA226x)
{
	return INA226_I2C_ReadReg(INA226x, MASK_ENABLE_REG, &(INA226x->msgMaskReg));
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����У׼�Ĵ�����ֵ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_GetShuntReg(INA226_HandlerType* INA226x)
{
	return INA226_I2C_ReadReg(INA226x, SHUNT_VOLTAGE_REG, &(INA226x->msgShuntReg));
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����У׼�Ĵ�����ֵ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_GetCurrentReg(INA226_HandlerType* INA226x)
{
	return INA226_I2C_ReadReg(INA226x, CURRENT_REG, &(INA226x->msgCurrentReg));
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����У׼�Ĵ�����ֵ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_GetBusVReg(INA226_HandlerType* INA226x)
{
	return INA226_I2C_ReadReg(INA226x, BUS_VOLTAGE_REG, &(INA226x->msgBusVReg));
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����У׼�Ĵ�����ֵ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_GetPowerReg(INA226_HandlerType* INA226x)
{
	return INA226_I2C_ReadReg(INA226x, POWER_REG, &(INA226x->msgPowerReg));
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����У׼�Ĵ�����ֵ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_GetBusVoltage(INA226_HandlerType* INA226x)
{
	UINT8_T _return = INA226_GetBusVReg(INA226x);
	INA226x->msgBusmV = 0.0f;
	if (_return==OK_0)
	{
		INA226x->msgBusmV = INA226x->msgBusVReg;
		INA226x->msgBusmV *= INA226_RANG_BUS_VOLTAGE_MV_BIT;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����У׼�Ĵ�����ֵ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_GetShuntVoltage(INA226_HandlerType* INA226x)
{
	UINT8_T _return = INA226_GetShuntReg(INA226x);
	INA226x->msgShuntuV = 0.0f;
	if (_return == OK_0)
	{
		if ((INA226x->msgShuntReg&0x8000)!=0)
		{
			INA226x->msgShuntuV =(-1.0)*(0x10000 - INA226x->msgShuntReg);
		}
		else
		{
			INA226x->msgShuntuV = INA226x->msgShuntReg;
		}
		INA226x->msgShuntuV *= INA226_RANG_SHUNT_VOLTAGE_UV_BIT;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����У׼�Ĵ�����ֵ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_GetShuntCurrent(INA226_HandlerType* INA226x)
{
	UINT8_T _return = INA226_GetCurrentReg(INA226x);
	INA226x->msgShuntuA = 0.0f;
	if (_return == OK_0)
	{
		if (INA226x->msgCalibReg == 0)
		{
			if ((INA226x->msgCurrentReg & 0x8000) != 0)
			{
				INA226x->msgShuntuA =(-1.0)*(0x10000 - INA226x->msgCurrentReg);
			}
			else
			{
				INA226x->msgShuntuA = INA226x->msgCurrentReg;
			}
			if (INA226x->msgCalibReg == INA226_CALIB_REG_DEFAULT_X1)
			{
				INA226x->msgShuntuA *= INA226_RANG_CURRENT_UA_BIT_X1;
			}
			else if (INA226x->msgCalibReg == INA226_CALIB_REG_DEFAULT_X2)
			{
				INA226x->msgShuntuA *= INA226_RANG_CURRENT_UA_BIT_X2;
			}
			else
			{
				_return = INA226_GetShuntVoltage(INA226x);
				if (_return == OK_0)
				{
					if ((INA226x->msgShuntReg & 0x8000) != 0)
					{
						INA226x->msgShuntuA = (-1000.0) * (INA226x->msgShuntuV / INA226_SAMPLE_RES_MR);
					}
					else
					{
						INA226x->msgShuntuA = (1000.0) * (INA226x->msgShuntuV / INA226_SAMPLE_RES_MR);
					}
				}
			}
		}
		else
		{
			_return = INA226_GetShuntVoltage(INA226x);
			if (_return == OK_0)
			{
				if ((INA226x->msgShuntReg & 0x8000) != 0)
				{
					INA226x->msgShuntuA = (-1.0)*(0x10000 - INA226x->msgShuntReg);;
				}
				else
				{
					INA226x->msgShuntuA = INA226x->msgShuntReg;
				}
				INA226x->msgShuntuA = (1000.0) * (INA226x->msgShuntuA * INA226x->msgCalibReg / 2048);
			}
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ���صĹ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_GetPower(INA226_HandlerType* INA226x)
{
	UINT8_T _return = INA226_GetShuntVoltage(INA226x);
	INA226x->msgPowermW = 0.0f;
	if (_return == OK_0)
	{
		_return = INA226_GetShuntCurrent(INA226x);
		if (_return==OK_0)
		{
			INA226x->msgPowermW = INA226x->msgBusmV * INA226x->msgShuntuA / 1000000.0;
		}
	}
	return _return;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ó�ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_ConfigInit(INA226_HandlerType* INA226x)
{
	UINT8_T _return = OK_0;
	INA226x->msgCFGReg = 0x4000;
	//---ƽ��64���ɼ�ʱ��204us
	_return= INA226_SetCFGReg(INA226x,	0x4000| AVERAGING_MODE_64|
										BUS_VOLTAGE_CONVERSIOM_TIME_204_US|
										SHUNT_VOLTAGE_CONVERSIOM_TIME_204_US|
										OPERATING_MODE_SHUNT_BUS_VOLTAGE_CONT
							);
	if (_return==OK_0)
	{
		//---����У׼�Ĵ���
		_return = INA226_SetCalibReg(INA226x, INA226_RANG_CURRENT_UA_BIT_X2);
	}
	if (_return==OK_0)
	{
		//---�������˿�����Ϊװ����ɣ���־����Ч���ߵ�ƽ��Ч
		_return = INA226_SetMaskReg(INA226x, CONVERSION_READY_ENABLE);
	}
	return _return;
}

#include "ina226_cfg.h"

//===全局变量定义
INA226_HandlerType		g_Ina226Device0 = { 0 };
pINA226_HandlerType		pIna226Device0 = &g_Ina226Device0;

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：初始化
//////输入参数:isHWI2C---1 硬件，0 软件
//////输出参数:
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_I2C_Init(INA226_HandlerType* INA226x, void(*pFuncDelayus)(UINT32_T delay), UINT8_T isHWI2C)
{
	UINT8_T _return = OK_0;

	//---指定设备的初始化
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

	//---判断是硬件I2C还是软件I2C
	if (isHWI2C)
	{
		//---初始化硬件I2C
		_return = I2CTask_MHW_Init(&(INA226x->msgI2C));
		//---设置为硬件模式
		INA226x->msgI2C.msgModelIsHW = 1;
	}
	else
	{
		//---初始化软件模拟I2C
		_return = I2CTask_MSW_Init(&(INA226x->msgI2C), pFuncDelayus);
		//---设置为软件件模式
		INA226x->msgI2C.msgModelIsHW = 0;
	}
	//---配置初始化
	_return = INA226_ConfigInit(INA226x);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
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
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_I2C_Device1_Init(INA226_HandlerType* INA226x)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_I2C_Device2_Init(INA226_HandlerType* INA226x)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_SWI2C_WriteReg(INA226_HandlerType* INA226x, UINT8_T addr, UINT16_T val)
{
	UINT8_T _return = OK_0;
	//---启动IIC并发送器件地址，写数据
	_return = I2CTask_MSW_START(&(INA226x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_1;
		goto GoToExit;
	}
	//---发送寄存器地址
	I2CTask_MSW_SendByte(&(INA226x->msgI2C), addr);
	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(INA226x->msgI2C));
	if (_return != OK_0)
	{
		//---发送寄存器地址错误
		_return = ERROR_2;
		goto GoToExit;
	}
	//---发送高位数据
	I2CTask_MSW_SendByte(&(INA226x->msgI2C), (UINT8_T)(val>>16));
	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(INA226x->msgI2C));
	if (_return != OK_0)
	{
		//---发送数据错误
		_return = ERROR_3;
		goto GoToExit;
	}
	//---发送低位数据
	I2CTask_MSW_SendByte(&(INA226x->msgI2C), (UINT8_T)(val&0xFF));
	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(INA226x->msgI2C));
	if (_return != OK_0)
	{
		//---发送数据错误
		_return = ERROR_4;
		goto GoToExit;
	}
	//---退出操作入口
GoToExit:
	//---发送停止信号
	I2CTask_MSW_STOP(&(INA226x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_HWI2C_WriteReg(INA226_HandlerType* INA226x, UINT8_T addr, UINT16_T val)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
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
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_SWI2C_ReadReg(INA226_HandlerType* INA226x, UINT8_T addr, UINT16_T *pVal)
{
	UINT8_T _return = OK_0;
	UINT16_T readTemp = 0;
	//---启动IIC并发送器件地址，写数据
	_return = I2CTask_MSW_START(&(INA226x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_1;
		goto GoToExit;
	}
	//---发送寄存器地址
	I2CTask_MSW_SendByte(&(INA226x->msgI2C), addr);
	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(INA226x->msgI2C));
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_2;
		goto GoToExit;
	}
	//---启动IIC并发送器件地址，读数据
	_return = I2CTask_MSW_START(&(INA226x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---启动读数据失败
		_return = ERROR_3;
		goto GoToExit;
	}
	//---读取高位数据
	readTemp= I2CTask_MSW_ReadByte(&(INA226x->msgI2C));
	//---发送应答信号
	_return = I2CTask_MSW_SendACK(&(INA226x->msgI2C), 0);
	readTemp <<= 8;
	//---读取低位数据
	readTemp |= I2CTask_MSW_ReadByte(&(INA226x->msgI2C));
	//---发送不应答信号
	_return = I2CTask_MSW_SendACK(&(INA226x->msgI2C), 1);
	*pVal = readTemp;
GoToExit:
	//---发送停止信号
	I2CTask_MSW_STOP(&(INA226x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_HWI2C_ReadReg(INA226_HandlerType* INA226x, UINT8_T addr, UINT16_T* pVal)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
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
//////函		数：
//////功		能：设备ID
//////输入参数:
//////输出参数:
//////说		明：
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
//////函		数：
//////功		能：制造商ID
//////输入参数:
//////输出参数:
//////说		明：
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
//////函		数：
//////功		能：读取配置寄存器的值
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_GetCFGReg(INA226_HandlerType* INA226x)
{
	return INA226_I2C_ReadReg(INA226x, CONFIGURATION_REG, &(INA226x->msgCFGReg));
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置配置寄存器的值
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_SetCFGReg(INA226_HandlerType* INA226x, UINT16_T val)
{
	INA226x->msgCFGReg = val;
	return INA226_I2C_WriteReg(INA226x, CONFIGURATION_REG, INA226x->msgCFGReg);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：复位设备
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_Reset(INA226_HandlerType* INA226x)
{
	INA226x->msgCFGReg = 0x4000;
	return INA226_SetCFGReg(INA226x,0xC000);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取校准寄存器的值
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_GetCalibReg(INA226_HandlerType* INA226x)
{
	return INA226_I2C_ReadReg(INA226x, CALIBRATION_REG, &(INA226x->msgCalibReg));
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置校准寄存器的值
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_SetCalibReg(INA226_HandlerType* INA226x,UINT16_T val)
{
	INA226x->msgCalibReg = val;
	return INA226_I2C_WriteReg(INA226x, CALIBRATION_REG, INA226x->msgCalibReg);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取校准寄存器的值
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_GetMaskReg(INA226_HandlerType* INA226x)
{
	return INA226_I2C_ReadReg(INA226x, MASK_ENABLE_REG, &(INA226x->msgMaskReg));
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置校准寄存器的值
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_SetMaskReg(INA226_HandlerType* INA226x, UINT16_T val)
{
	INA226x->msgMaskReg=val;
	return INA226_I2C_WriteReg(INA226x, MASK_ENABLE_REG, INA226x->msgMaskReg);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：清楚转换就绪标志位
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_ClearConversionReadyFlag(INA226_HandlerType* INA226x)
{
	return INA226_I2C_ReadReg(INA226x, MASK_ENABLE_REG, &(INA226x->msgMaskReg));
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置校准寄存器的值
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_GetShuntReg(INA226_HandlerType* INA226x)
{
	return INA226_I2C_ReadReg(INA226x, SHUNT_VOLTAGE_REG, &(INA226x->msgShuntReg));
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置校准寄存器的值
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_GetCurrentReg(INA226_HandlerType* INA226x)
{
	return INA226_I2C_ReadReg(INA226x, CURRENT_REG, &(INA226x->msgCurrentReg));
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置校准寄存器的值
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_GetBusVReg(INA226_HandlerType* INA226x)
{
	return INA226_I2C_ReadReg(INA226x, BUS_VOLTAGE_REG, &(INA226x->msgBusVReg));
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置校准寄存器的值
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_GetPowerReg(INA226_HandlerType* INA226x)
{
	return INA226_I2C_ReadReg(INA226x, POWER_REG, &(INA226x->msgPowerReg));
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置校准寄存器的值
//////输入参数:
//////输出参数:
//////说		明：
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
//////函		数：
//////功		能：设置校准寄存器的值
//////输入参数:
//////输出参数:
//////说		明：
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
//////函		数：
//////功		能：设置校准寄存器的值
//////输入参数:
//////输出参数:
//////说		明：
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
//////函		数：
//////功		能：获取负载的功耗
//////输入参数:
//////输出参数:
//////说		明：
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
//////函		数：
//////功		能：配置初始化
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_ConfigInit(INA226_HandlerType* INA226x)
{
	UINT8_T _return = OK_0;
	INA226x->msgCFGReg = 0x4000;
	//---平局64，采集时间204us
	_return= INA226_SetCFGReg(INA226x,	0x4000| AVERAGING_MODE_64|
										BUS_VOLTAGE_CONVERSIOM_TIME_204_US|
										SHUNT_VOLTAGE_CONVERSIOM_TIME_204_US|
										OPERATING_MODE_SHUNT_BUS_VOLTAGE_CONT
							);
	if (_return==OK_0)
	{
		//---设置校准寄存器
		_return = INA226_SetCalibReg(INA226x, INA226_RANG_CURRENT_UA_BIT_X2);
	}
	if (_return==OK_0)
	{
		//---将报警端口设置为装换完成，标志低有效，高电平无效
		_return = INA226_SetMaskReg(INA226x, CONVERSION_READY_ENABLE);
	}
	return _return;
}

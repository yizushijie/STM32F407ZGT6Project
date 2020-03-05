#include "ina226_cfg.h"

//===全局变量定义
INA226_HandleType		g_Ina226Device0 = { 0 };
pINA226_HandleType		pIna226Device0 = &g_Ina226Device0;


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_I2C_Device0_Init(INA226_HandleType* INA226x)
{
	INA226x->msgI2C.pMsgI2Cx = NULL;
	INA226x->msgI2C.msgSCL.msgPort = GPIOB;
	INA226x->msgI2C.msgSCL.msgBit = LL_GPIO_PIN_6;
	INA226x->msgI2C.msgSDA.msgPort = GPIOB;
	INA226x->msgI2C.msgSDA.msgBit = LL_GPIO_PIN_7;
	INA226x->msgI2C.msgHwMode = 0;
	INA226x->msgI2C.msgPluseWidth = 2;
	INA226x->msgI2C.pMsgDelayus = NULL;
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
UINT8_T INA226_I2C_Device1_Init(INA226_HandleType* INA226x)
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
UINT8_T INA226_I2C_Device2_Init(INA226_HandleType* INA226x)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：初始化
//////输入参数:isHWI2C---1 硬件，0 软件
//////输出参数:
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_I2C_Init(INA226_HandleType* INA226x, void(*pFuncDelayus)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHWI2C)
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
	(isHWI2C != 0) ? (_return = I2CTask_MHW_Init(&(INA226x->msgI2C),pFuncDelayus, pFuncTimerTick)) : (_return = I2CTask_MSW_Init(&(INA226x->msgI2C), pFuncDelayus, pFuncTimerTick));
	//---配置初始化
	_return = INA226_I2C_ConfigInit(INA226x);
	return _return;
}
///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_I2C_DeInit(INA226_HandleType* INA226x)
{
	return I2CTask_Master_DeInit(&(INA226x->msgI2C));
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_SWI2C_WriteSingle(INA226_HandleType* INA226x, UINT8_T addr, UINT16_T val)
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
	I2CTask_MSW_SendByte(&(INA226x->msgI2C), (UINT8_T)(val>>8));
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
UINT8_T INA226_HWI2C_WriteSingle(INA226_HandleType* INA226x, UINT8_T addr, UINT16_T val)
{
	UINT8_T _return = OK_0;
	//---启动IIC并发送器件地址，写数据
	_return = I2CTask_MHW_PollMode_START(&(INA226x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_1;
		goto GoToExit;
	}
	//---发送寄存器地址,存储单元的地址
	_return = I2CTask_MHW_PollMode_SendByte(&(INA226x->msgI2C), addr, 0);
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_2;
		goto GoToExit;
	}
	//---发送高位数据
	_return = I2CTask_MHW_PollMode_SendByte(&(INA226x->msgI2C), (UINT8_T)(val >> 8), 0);
	if (_return != OK_0)
	{
		//---发送数据错误
		_return = ERROR_3;
		goto GoToExit;
	}
	//---发送低位数据
	_return = I2CTask_MHW_PollMode_SendByte(&(INA226x->msgI2C), (UINT8_T)val, 0);
	if (_return != OK_0)
	{
		//---发送数据错误
		_return = ERROR_3;
		goto GoToExit;
	}
	//---退出操作入口
GoToExit:
	//---发送停止信号
	I2CTask_MHW_PollMode_STOP(&(INA226x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_I2C_WriteSingle(INA226_HandleType* INA226x, UINT8_T addr, UINT16_T val)
{
	if (INA226x->msgI2C.msgHwMode != 0)
	{
		I2CTask_MHW_CheckClock(&(INA226x->msgI2C));
		//---硬件I2C
		return INA226_HWI2C_WriteSingle(INA226x, addr, val);
	}
	else
	{
		return INA226_SWI2C_WriteSingle(INA226x, addr, val);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_SWI2C_ReadSingle(INA226_HandleType* INA226x, UINT8_T addr, UINT16_T *pVal)
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
	//---退出函数入口
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
UINT8_T INA226_HWI2C_ReadSingle(INA226_HandleType* INA226x, UINT8_T addr, UINT16_T* pVal)
{
	UINT8_T _return = OK_0;
	UINT16_T readTemp = 0;
	//---启动IIC并发送器件地址，写数据
	_return = I2CTask_MHW_PollMode_START(&(INA226x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_1;
		goto GoToExit;
	}
	//---发送寄存器地址,存储单元的地址
	_return = I2CTask_MHW_PollMode_SendByte(&(INA226x->msgI2C), addr, 0);
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_2;
		goto GoToExit;
	}
	//---启动IIC并发送器件地址，读数据
	_return = I2CTask_MHW_PollMode_START(&(INA226x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---启动读数据失败
		_return = ERROR_3;
		goto GoToExit;
	}
	//---发送应答信号
	_return = I2CTask_MHW_SendACK(&(INA226x->msgI2C), 0);
	//---读取高位数据
	readTemp = I2CTask_MHW_PollMode_ReadByte(&(INA226x->msgI2C));
	readTemp <<= 8;
	//---不发送应答信号
	_return = I2CTask_MHW_SendACK(&(INA226x->msgI2C), 1);
	//---读取低位数据
	readTemp |= I2CTask_MHW_PollMode_ReadByte(&(INA226x->msgI2C));
	*pVal = readTemp;
	//---退出入口
GoToExit:
	//---发送停止信号
	I2CTask_MHW_PollMode_STOP(&(INA226x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_I2C_ReadSingle(INA226_HandleType* INA226x, UINT8_T addr, UINT16_T* pVal)
{
	if (INA226x->msgI2C.msgHwMode != 0)
	{
		I2CTask_MHW_CheckClock(&(INA226x->msgI2C));
		//---硬件I2C
		return INA226_HWI2C_ReadSingle(INA226x, addr, pVal);
	}
	else
	{
		return INA226_SWI2C_ReadSingle(INA226x, addr, pVal);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设备ID
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_I2C_ReadDieID(INA226_HandleType* INA226x)
{
	UINT16_T deviceID = 0;
	UINT8_T _return = INA226_I2C_ReadSingle(INA226x, DIE_ID_REG, &deviceID);
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
UINT8_T INA226_I2C_ReadManuID(INA226_HandleType* INA226x)
{
	UINT16_T deviceID = 0;
	UINT8_T _return = INA226_I2C_ReadSingle(INA226x, MANUFACTURER_ID_REG, &deviceID);
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
UINT8_T INA226_I2C_ReadCFGReg(INA226_HandleType* INA226x)
{
	return INA226_I2C_ReadSingle(INA226x, CONFIGURATION_REG, &(INA226x->msgCFGReg));
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置配置寄存器的值
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_I2C_WriteCFGReg(INA226_HandleType* INA226x, UINT16_T val)
{
	INA226x->msgCFGReg = val;
	return INA226_I2C_WriteSingle(INA226x, CONFIGURATION_REG, INA226x->msgCFGReg);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：复位设备
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_I2C_Reset(INA226_HandleType* INA226x)
{
	INA226x->msgCFGReg = 0x4000;
	return INA226_I2C_WriteCFGReg(INA226x,0xC000);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取校准寄存器的值
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_I2C_ReadCalibReg(INA226_HandleType* INA226x)
{
	return INA226_I2C_ReadSingle(INA226x, CALIBRATION_REG, &(INA226x->msgCalibReg));
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置校准寄存器的值
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_I2C_WriteCalibReg(INA226_HandleType* INA226x,UINT16_T val)
{
	INA226x->msgCalibReg = val;
	return INA226_I2C_WriteSingle(INA226x, CALIBRATION_REG, INA226x->msgCalibReg);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取校准寄存器的值
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_I2C_ReadMaskReg(INA226_HandleType* INA226x)
{
	return INA226_I2C_ReadSingle(INA226x, MASK_ENABLE_REG, &(INA226x->msgMaskReg));
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置校准寄存器的值
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_I2C_WriteMaskReg(INA226_HandleType* INA226x, UINT16_T val)
{
	INA226x->msgMaskReg=val;
	return INA226_I2C_WriteSingle(INA226x, MASK_ENABLE_REG, INA226x->msgMaskReg);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：清楚转换就绪标志位
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_I2C_ClearConversionReadyFlag(INA226_HandleType* INA226x)
{
	return INA226_I2C_ReadSingle(INA226x, MASK_ENABLE_REG, &(INA226x->msgMaskReg));
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置校准寄存器的值
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_I2C_ReadShuntReg(INA226_HandleType* INA226x)
{
	return INA226_I2C_ReadSingle(INA226x, SHUNT_VOLTAGE_REG, &(INA226x->msgShuntReg));
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置校准寄存器的值
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_I2C_ReadCurrentReg(INA226_HandleType* INA226x)
{
	return INA226_I2C_ReadSingle(INA226x, CURRENT_REG, &(INA226x->msgCurrentReg));
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置校准寄存器的值
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_I2C_ReadBusVReg(INA226_HandleType* INA226x)
{
	return INA226_I2C_ReadSingle(INA226x, BUS_VOLTAGE_REG, &(INA226x->msgBusVReg));
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置校准寄存器的值
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_I2C_ReadPowerReg(INA226_HandleType* INA226x)
{
	return INA226_I2C_ReadSingle(INA226x, POWER_REG, &(INA226x->msgPowerReg));
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置校准寄存器的值
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T INA226_I2C_GetBusVoltage(INA226_HandleType* INA226x)
{
	UINT8_T _return = INA226_I2C_ReadBusVReg(INA226x);
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
UINT8_T INA226_I2C_ReadShuntVoltage(INA226_HandleType* INA226x)
{
	UINT8_T _return = INA226_I2C_ReadShuntReg(INA226x);
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
UINT8_T INA226_I2C_ReadShuntCurrent(INA226_HandleType* INA226x)
{
	UINT8_T _return = INA226_I2C_ReadCurrentReg(INA226x);
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
				_return = INA226_I2C_ReadShuntVoltage(INA226x);
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
			_return = INA226_I2C_ReadShuntVoltage(INA226x);
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
UINT8_T INA226_I2C_GetPower(INA226_HandleType* INA226x)
{
	UINT8_T _return = INA226_I2C_ReadShuntVoltage(INA226x);
	INA226x->msgPowermW = 0.0f;
	if (_return == OK_0)
	{
		_return = INA226_I2C_ReadShuntCurrent(INA226x);
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
UINT8_T INA226_I2C_ConfigInit(INA226_HandleType* INA226x)
{
	UINT8_T _return = OK_0;
	INA226x->msgCFGReg = 0x4000;
	//---平局64，采集时间204us
	_return= INA226_I2C_WriteCFGReg(INA226x,	0x4000| AVERAGING_MODE_64|
										BUS_VOLTAGE_CONVERSIOM_TIME_204_US|
										SHUNT_VOLTAGE_CONVERSIOM_TIME_204_US|
										OPERATING_MODE_SHUNT_BUS_VOLTAGE_CONT
							);
	if (_return==OK_0)
	{
		//---设置校准寄存器
		_return = INA226_I2C_WriteCalibReg(INA226x, INA226_RANG_CURRENT_UA_BIT_X2);
	}
	if (_return==OK_0)
	{
		//---将报警端口设置为装换完成，标志低有效，高电平无效
		_return = INA226_I2C_WriteMaskReg(INA226x, CONVERSION_READY_ENABLE);
	}
	return _return;
}

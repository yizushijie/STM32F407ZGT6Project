#include "max961x_cfg.h"

//===全局变量定义
MAX961X_HandlerType		g_Max961xDevice0 = { 0 };
pMAX961X_HandlerType	pMax961xDevice0 = &g_Max961xDevice0;

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：
//////输入参数:isHWI2C---1 硬件，0 软件
//////输出参数:
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_I2C_Init(MAX961X_HandlerType* MAX961x, void(*pFuncDelayus)(UINT32_T delay), UINT8_T isHWI2C)
{
	UINT8_T _return = OK_0;

	//---指定设备的初始化
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

	//---判断是硬件I2C还是软件I2C
	if (isHWI2C)
	{
		//---初始化硬件I2C
		_return = I2CTask_MHW_Init(&(MAX961x->msgI2C));
		//---设置为硬件模式
		MAX961x->msgI2C.msgModelIsHW = 1;
	}
	else
	{
		//---初始化软件模拟I2C
		_return = I2CTask_MSW_Init(&(MAX961x->msgI2C), pFuncDelayus);
		//---设置为软件件模式
		MAX961x->msgI2C.msgModelIsHW = 0;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
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
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_I2C_Device1_Init(MAX961X_HandlerType* MAX961x)
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
UINT8_T MAX961X_I2C_Device2_Init(MAX961X_HandlerType* MAX961x)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：单数据写入
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_SWI2C_SingleWriteReg(MAX961X_HandlerType* MAX961x, UINT8_T addr, UINT8_T val)
{
	UINT8_T _return = OK_0;

	//---启动IIC并发送器件地址，写数据
	_return = I2CTask_MSW_START(&(MAX961x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_1;
		goto GoToExit;
	}

	//---发送寄存器地址,低位地址
	I2CTask_MSW_SendByte(&(MAX961x->msgI2C), addr);

	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(MAX961x->msgI2C));
	if (_return != OK_0)
	{
		//---发送寄存器地址错误
		_return = ERROR_2;
		goto GoToExit;
	}

	//---发送数据
	I2CTask_MSW_SendByte(&(MAX961x->msgI2C), val);

	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(MAX961x->msgI2C));
	if (_return != OK_0)
	{
		//---发送数据错误
		_return = ERROR_3;
		goto GoToExit;
	}
	//---退出操作入口
GoToExit:
	//---发送停止信号
	I2CTask_MSW_STOP(&(MAX961x->msgI2C));

	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：多数据写入
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_SWI2C_BurstWriteReg(MAX961X_HandlerType* MAX961x, UINT8_T addr,UINT8_T length, UINT8_T *pVal)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---启动IIC并发送器件地址，写数据
	_return = I2CTask_MSW_START(&(MAX961x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_1;
		goto GoToExit;
	}

	//---发送寄存器地址,低位地址
	I2CTask_MSW_SendByte(&(MAX961x->msgI2C), addr);

	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(MAX961x->msgI2C));
	if (_return != OK_0)
	{
		//---发送寄存器地址错误
		_return = ERROR_2;
		goto GoToExit;
	}
	//---发送多字节数据
	for (i=0;i<length;i++)
	{
		//---发送数据
		I2CTask_MSW_SendByte(&(MAX961x->msgI2C), pVal[i]);

		//---读取ACK
		_return = I2CTask_MSW_ReadACK(&(MAX961x->msgI2C));
		if (_return != OK_0)
		{
			//---发送数据错误
			_return = ERROR_3+i;
			goto GoToExit;
		}
	}
	
	//---退出操作入口
GoToExit:
	//---发送停止信号
	I2CTask_MSW_STOP(&(MAX961x->msgI2C));

	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：单数据写入
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_HWI2C_SingleWriteReg(MAX961X_HandlerType* MAX961x, UINT8_T addr, UINT8_T val)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：多数据写入
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_HWI2C_BurstWriteReg(MAX961X_HandlerType* MAX961x, UINT8_T addr, UINT8_T length, UINT8_T* pVal)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：单数据读取
//////输入参数:
//////输出参数:
//////说		明：
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
//////函		数：
//////功		能：多数据读取
//////输入参数:
//////输出参数:
//////说		明：
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
//////函		数：
//////功		能：单数据读取
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_SWI2C_SingleReadReg(MAX961X_HandlerType* MAX961x, UINT8_T addr, UINT8_T *pVal)
{
	UINT8_T _return = OK_0;
	//---启动IIC并发送器件地址，写数据
	_return = I2CTask_MSW_START(&(MAX961x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_1;
		goto GoToExit;
	}

	//---发送寄存器地址,高地址
	I2CTask_MSW_SendByte(&(MAX961x->msgI2C), addr);

	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(MAX961x->msgI2C));
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_2;
		goto GoToExit;
	}

	//---启动IIC并发送器件地址，读数据
	_return = I2CTask_MSW_START(&(MAX961x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---启动读数据失败
		_return = ERROR_3;
		goto GoToExit;
	}

	//---读取数据
	*pVal = I2CTask_MSW_ReadByte(&(MAX961x->msgI2C));

	//---发送不应答信号
	_return= I2CTask_MSW_SendACK(&(MAX961x->msgI2C), 1);
	
GoToExit:
	//---发送停止信号
	I2CTask_MSW_STOP(&(MAX961x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：多数据读取
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_SWI2C_BurstReadReg(MAX961X_HandlerType* MAX961x, UINT8_T addr, UINT8_T length, UINT8_T* pVal)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---启动IIC并发送器件地址，写数据
	_return = I2CTask_MSW_START(&(MAX961x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_1;
		goto GoToExit;
	}

	//---发送寄存器地址,高地址
	I2CTask_MSW_SendByte(&(MAX961x->msgI2C), addr);

	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(MAX961x->msgI2C));
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_2;
		goto GoToExit;
	}

	//---启动IIC并发送器件地址，读数据
	_return = I2CTask_MSW_START(&(MAX961x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---启动读数据失败
		_return = ERROR_3;
		goto GoToExit;
	}

	for (i=0;i<length;i++)
	{
		//---读取数据
		pVal[i] = I2CTask_MSW_ReadByte(&(MAX961x->msgI2C));
		if (i == (length - 1))
		{
			_return = 1;
		}

		//---发送应答信号
		I2CTask_MSW_SendACK(&(MAX961x->msgI2C), _return);
	}
	_return = OK_0;
GoToExit:
	//---发送停止信号
	I2CTask_MSW_STOP(&(MAX961x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：单数据读取
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_HWI2C_SingleReadReg(MAX961X_HandlerType* MAX961x, UINT8_T addr, UINT8_T* pVal)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：多数据读取
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_HWI2C_BurstReadReg(MAX961X_HandlerType* MAX961x, UINT8_T addr, UINT8_T length, UINT8_T* pVal)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：单数据读取
//////输入参数:
//////输出参数:
//////说		明：
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
//////函		数：
//////功		能：多数据读取
//////输入参数:
//////输出参数:
//////说		明：
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
//////函		数：
//////功		能：校验设备
//////输入参数:
//////输出参数:
//////说		明：
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
//////函		数：
//////功		能：获取正输入电压
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_I2C_GetRSVoltage(MAX961X_HandlerType* MAX961x)
{
	UINT8_T _return = OK_0 ;
	UINT8_T adcTemp[2] = {0};
	//---准备读取 输入电压
	_return = MAX961X_I2C_SingleWriteReg(MAX961x, MAX961X_REG_CONTROL_REG1, MAX961X_READ_CHANNEL_INPUT_VOLTAGE);
	if (_return==OK_0)
	{
		//---读取输入电压的值
		_return = MAX961X_I2C_BurstReadReg(MAX961x, MAX961X_REG_RS_DATA_MSB_ADDR, 2, adcTemp);
		//---计算采集的数据量
		MAX961x->msgRSVoltagemV = adcTemp[0];
		MAX961x->msgRSVoltagemV =(MAX961x->msgRSVoltagemV*256)+ adcTemp[1];
		//---得到实际的采集量,数据格式是左对齐，低四位无效
		MAX961x->msgRSVoltagemV = ((UINT16_T)MAX961x->msgRSVoltagemV >> 4);//-4;
		MAX961x->msgRSVoltagemV *= MAX961X_VOLTAGE_STEP_MV;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：获取输出电流
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_I2C_GetRSCurrent(MAX961X_HandlerType* MAX961x,UINT8_T currentGain)
{
	UINT8_T _return = OK_0;
	UINT8_T gain = 1;
	UINT8_T adcTemp[2] = { 0 };
	currentGain &= 0x03;
	//---准备读取负载电流
	_return = MAX961X_I2C_SingleWriteReg(MAX961x, MAX961X_REG_CONTROL_REG1, currentGain);
	if (_return == OK_0)
	{
		gain <<= currentGain;
		//---读取输入电压的值
		_return = MAX961X_I2C_BurstReadReg(MAX961x, MAX961X_REG_CSA_DATA_MSB_ADDR, 2, adcTemp);
		//---计算采集的数据量
		MAX961x->msgRSCurrentmA = adcTemp[0];
		MAX961x->msgRSCurrentmA = (MAX961x->msgRSCurrentmA*256) + adcTemp[1];
		//---得到实际的采集量,数据格式是左对齐，低四位无效
		MAX961x->msgRSCurrentmA = ((UINT16_T)MAX961x->msgRSCurrentmA >> 4);
		//---得到X1电压值，单位mV
		MAX961x->msgRSCurrentmA *= MAX961X_CURRENT_STEP_MA;
		//---得到实际增益电压值，单位mV
		MAX961x->msgRSCurrentmA /= gain;
		//---计算电流值
		MAX961x->msgRSCurrentmA /= MAX961X_SAMPLE_RES_MR;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_I2C_GetOutVoltage(MAX961X_HandlerType* MAX961x)
{
	UINT8_T _return = OK_0;
	UINT8_T adcTemp[2] = { 0 };
	//---准备读取 输入电压
	_return = MAX961X_I2C_SingleWriteReg(MAX961x, MAX961X_REG_CONTROL_REG1, MAX961X_READ_CHANNEL_OUTPUT_VOLTAGE);
	if (_return == OK_0)
	{
		//---读取OUT端的输出电压的值
		_return = MAX961X_I2C_BurstReadReg(MAX961x, MAX961X_REG_OUT_DATA_MSB_ADDR, 2, adcTemp);
		//---计算采集的数据量,数据格式是左对齐，低四位无效
		MAX961x->msgOutputVoltagemV = adcTemp[0];
		MAX961x->msgOutputVoltagemV = (MAX961x->msgOutputVoltagemV*256) + adcTemp[1];
		//---得到实际的采集量
		MAX961x->msgOutputVoltagemV = ((UINT16_T)MAX961x->msgOutputVoltagemV >> 4);
		MAX961x->msgOutputVoltagemV *= MAX961X_VOLTAGE_STEP_MV;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_I2C_GetSetVoltage(MAX961X_HandlerType* MAX961x)
{
	UINT8_T _return = OK_0;
	UINT8_T adcTemp[2] = { 0 };
	//---准备读取 输入电压
	_return = MAX961X_I2C_SingleWriteReg(MAX961x, MAX961X_REG_CONTROL_REG1, MAX961X_READ_CHANNEL_SET_VOLTAGE);
	if (_return == OK_0)
	{
		//---读取SET端的输出电压的值
		_return = MAX961X_I2C_BurstReadReg(MAX961x, MAX961X_REG_SET_DATA_MSB_ADDR, 2, adcTemp);
		//---计算采集的数据量
		MAX961x->msgSetVoltagemV = adcTemp[0];
		MAX961x->msgSetVoltagemV = (MAX961x->msgSetVoltagemV*256) + adcTemp[1];
		//---得到实际的采集量,数据格式是左对齐，低四位无效
		MAX961x->msgSetVoltagemV = ((UINT16_T)MAX961x->msgSetVoltagemV >> 4);
		MAX961x->msgSetVoltagemV *= MAX961X_VOLTAGE_STEP_MV;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：获取内部温度
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_I2C_GetTemperature(MAX961X_HandlerType* MAX961x)
{
	UINT8_T _return = OK_0;
	UINT8_T adcTemp[2] = { 0 };
	//---准备读取 内部温度
	_return = MAX961X_I2C_SingleWriteReg(MAX961x, MAX961X_REG_CONTROL_REG1, MAX961X_READ_CHANNEL_TEMPERATURE);
	if (_return == OK_0)
	{
		//---读取内部温度
		_return = MAX961X_I2C_BurstReadReg(MAX961x, MAX961X_REG_TEMP_DATA_MSB_ADDR, 2, adcTemp);
		//---计算采集的数据量
		MAX961x->msgTemperatureC = adcTemp[0];
		MAX961x->msgTemperatureC = (MAX961x->msgTemperatureC*256) + adcTemp[1];
		//---得到实际的采集量,数据格式是左对齐，低七位无效
		MAX961x->msgTemperatureC = ((UINT16_T)MAX961x->msgTemperatureC >> 7);
		//---得到实际的采集量
		if (adcTemp[0]&0x80)
		{
			//---温度是负值
			MAX961x->msgTemperatureC = (0x200 - ((UINT16_T)MAX961x->msgTemperatureC));
			MAX961x->msgTemperatureC *= (-1);
		}
		MAX961x->msgTemperatureC *= MAX961X_TEMPERATURE_STEP_C;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
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
#include "max961x_cfg.h"

//===全局变量定义
MAX961X_HandleType		g_Max961xDevice0 = { 0 };
pMAX961X_HandleType	pMax961xDevice0 = &g_Max961xDevice0;

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
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
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_I2C_Device1_Init(MAX961X_HandleType* MAX961x)
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
UINT8_T MAX961X_I2C_Device2_Init(MAX961X_HandleType* MAX961x)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：
//////输入参数:isHWI2C---1 硬件，0 软件
//////输出参数:
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_I2C_Init(MAX961X_HandleType* MAX961x, void(*pFuncDelayus)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHWI2C)
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
	(isHWI2C != 0) ? (_return = I2CTask_MHW_Init(&(MAX961x->msgI2C), pFuncDelayus,pFuncTimerTick)) : (_return = I2CTask_MSW_Init(&(MAX961x->msgI2C), pFuncDelayus, pFuncTimerTick));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：注销
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_I2C_DeInit(MAX961X_HandleType* MAX961x)
{
	return I2CTask_Master_DeInit(&(MAX961x->msgI2C));	
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：单数据写入
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_SWI2C_WriteSingle(MAX961X_HandleType* MAX961x, UINT8_T addr, UINT8_T val)
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
UINT8_T MAX961X_SWI2C_WriteBulk(MAX961X_HandleType* MAX961x, UINT8_T addr,UINT8_T length, UINT8_T *pVal)
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
UINT8_T MAX961X_HWI2C_WriteSingle(MAX961X_HandleType* MAX961x, UINT8_T addr, UINT8_T val)
{
	UINT8_T _return = OK_0;
	//---启动IIC并发送器件地址，写数据
	_return = I2CTask_MHW_PollMode_START(&(MAX961x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_1;
		goto GoToExit;
	}
	//---发送寄存器地址,存储单元的地址
	_return = I2CTask_MHW_PollMode_SendByte(&(MAX961x->msgI2C), addr, 0);
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_2;
		goto GoToExit;
	}
	//---发送数据，内部寄存器数据
	_return = I2CTask_MHW_PollMode_SendByte(&(MAX961x->msgI2C), val, 1);
	if (_return != OK_0)
	{
		//---发送数据错误
		_return = ERROR_3;
		goto GoToExit;
	}
	//---退出操作入口
GoToExit:
	//---发送停止信号
	I2CTask_MHW_PollMode_STOP(&(MAX961x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：多数据写入
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_HWI2C_WriteBulk(MAX961X_HandleType* MAX961x, UINT8_T addr, UINT8_T length, UINT8_T* pVal)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---启动IIC并发送器件地址，写数据
	_return = I2CTask_MHW_PollMode_START(&(MAX961x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_1;
		goto GoToExit;
	}
	//---发送寄存器地址,内部寄存器地址
	I2CTask_MSW_SendByte(&(MAX961x->msgI2C), addr);
	//---发送寄存器地址,存储单元的地址
	_return = I2CTask_MHW_PollMode_SendByte(&(MAX961x->msgI2C), addr, 0);
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_2;
		goto GoToExit;
	}
	//---发送多字节数据
	for (i = 0; i < length; i++)
	{
		//---发送数据，内部寄存器数据
		_return = I2CTask_MHW_PollMode_SendByte(&(MAX961x->msgI2C), pVal[i], ((i == (length - 1)) ? 1 : 0));
		if (_return != OK_0)
		{
			//---发送数据错误
			_return = (ERROR_3 + i);
			goto GoToExit;
		}
	}
	//---退出操作入口
GoToExit:
	//---发送停止信号
	I2CTask_MHW_PollMode_STOP(&(MAX961x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：单数据读取
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_I2C_WriteSingle(MAX961X_HandleType* MAX961x, UINT8_T addr, UINT8_T val)
{
	if (MAX961x->msgI2C.msgHwMode != 0)
	{
		I2CTask_MHW_CheckClock(&(MAX961x->msgI2C));
		//---硬件I2C
		return MAX961X_HWI2C_WriteSingle(MAX961x, addr, val);
	}
	else
	{
		return MAX961X_SWI2C_WriteSingle(MAX961x, addr, val);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：多数据读取
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_I2C_WriteBulk(MAX961X_HandleType* MAX961x, UINT8_T addr, UINT8_T length, UINT8_T* pVal)
{
	if (MAX961x->msgI2C.msgHwMode == 1)
	{
		I2CTask_MHW_CheckClock(&(MAX961x->msgI2C));
		//---硬件I2C
		return MAX961X_HWI2C_WriteBulk(MAX961x, addr, length, pVal);
	}
	else
	{
		return MAX961X_SWI2C_WriteBulk(MAX961x, addr, length, pVal);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：单数据读取
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_SWI2C_ReadSingle(MAX961X_HandleType* MAX961x, UINT8_T addr, UINT8_T *pVal)
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
	//---退出入口
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
UINT8_T MAX961X_SWI2C_ReadBulk(MAX961X_HandleType* MAX961x, UINT8_T addr, UINT8_T length, UINT8_T* pVal)
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
		//---发送应答信号
		I2CTask_MSW_SendACK(&(MAX961x->msgI2C), (i == (length - 1)) ? 1 : 0);
	}
	_return = OK_0;
	//---退出入口
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
UINT8_T MAX961X_HWI2C_ReadSingle(MAX961X_HandleType* MAX961x, UINT8_T addr, UINT8_T* pVal)
{
	UINT8_T _return = OK_0;
	//---启动IIC并发送器件地址，写数据
	_return = I2CTask_MHW_PollMode_START(&(MAX961x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_1;
		goto GoToExit;
	}
	//---发送寄存器地址,存储单元的地址
	_return = I2CTask_MHW_PollMode_SendByte(&(MAX961x->msgI2C), addr, 0);
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_2;
		goto GoToExit;
	}
	//---启动IIC并发送器件地址，读数据
	_return = I2CTask_MHW_PollMode_START(&(MAX961x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---启动读数据失败
		_return = ERROR_3;
		goto GoToExit;
	}
	//---发送不应答信号
	_return = I2CTask_MHW_SendACK(&(MAX961x->msgI2C), 1);
	//---读取数据
	*pVal = I2CTask_MHW_PollMode_ReadByte(&(MAX961x->msgI2C));
GoToExit:
	//---发送停止信号
	I2CTask_MHW_PollMode_STOP(&(MAX961x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：多数据读取
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_HWI2C_ReadBulk(MAX961X_HandleType* MAX961x, UINT8_T addr, UINT8_T length, UINT8_T* pVal)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---启动IIC并发送器件地址，写数据
	_return = I2CTask_MHW_PollMode_START(&(MAX961x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_1;
		goto GoToExit;
	}
	//---发送寄存器地址,存储单元的地址
	_return = I2CTask_MHW_PollMode_SendByte(&(MAX961x->msgI2C), addr, 0);
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_2;
		goto GoToExit;
	}
	//---启动IIC并发送器件地址，读数据
	_return = I2CTask_MHW_PollMode_START(&(MAX961x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---启动读数据失败
		_return = ERROR_3;
		goto GoToExit;
	}
	//---连续读取6组数据
	for (i = 0; i < length; i++)
	{
		//---发送应答信号
		I2CTask_MHW_SendACK(&(MAX961x->msgI2C), (i == (length - 1)) ? 1 : 0);
		//---读取数据
		pVal[i] = I2CTask_MHW_PollMode_ReadByte(&(MAX961x->msgI2C));
	}
	_return = OK_0;
GoToExit:
	//---发送停止信号
	I2CTask_MHW_PollMode_STOP(&(MAX961x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：单数据读取
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_I2C_ReadSingle(MAX961X_HandleType* MAX961x, UINT8_T addr, UINT8_T* pVal)
{
	if (MAX961x->msgI2C.msgHwMode!=0)
	{
		I2CTask_MHW_CheckClock(&(MAX961x->msgI2C));
		//---硬件I2C
		return MAX961X_HWI2C_ReadSingle(MAX961x, addr, pVal);
	}
	else
	{
		return MAX961X_SWI2C_ReadSingle(MAX961x, addr, pVal);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：多数据读取
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_I2C_ReadBulk(MAX961X_HandleType* MAX961x, UINT8_T addr, UINT8_T length, UINT8_T* pVal)
{
	if (MAX961x->msgI2C.msgHwMode != 0)
	{
		I2CTask_MHW_CheckClock(&(MAX961x->msgI2C));
		//---硬件I2C
		return MAX961X_HWI2C_ReadBulk(MAX961x, addr,length, pVal);
	}
	else
	{
		return MAX961X_SWI2C_ReadBulk(MAX961x, addr, length, pVal);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：校验设备
//////输入参数:
//////输出参数:
//////说		明：
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
//////函		数：
//////功		能：获取正输入电压
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MAX961X_I2C_ReadRSVoltage(MAX961X_HandleType* MAX961x)
{
	UINT8_T _return = OK_0 ;
	UINT8_T adcTemp[2] = {0};
	//---准备读取 输入电压
	_return = MAX961X_I2C_WriteSingle(MAX961x, MAX961X_REG_CONTROL_REG1, MAX961X_READ_CHANNEL_INPUT_VOLTAGE);
	if (_return==OK_0)
	{
		//---读取输入电压的值
		_return = MAX961X_I2C_ReadBulk(MAX961x, MAX961X_REG_RS_DATA_MSB_ADDR, 2, adcTemp);
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
UINT8_T MAX961X_I2C_ReadRSCurrent(MAX961X_HandleType* MAX961x,UINT8_T currentGain)
{
	UINT8_T _return = OK_0;
	UINT8_T gain = 1;
	UINT8_T adcTemp[2] = { 0 };
	currentGain &= 0x03;
	//---准备读取负载电流
	_return = MAX961X_I2C_WriteSingle(MAX961x, MAX961X_REG_CONTROL_REG1, currentGain);
	if (_return == OK_0)
	{
		gain <<= currentGain;
		//---读取输入电压的值
		_return = MAX961X_I2C_ReadBulk(MAX961x, MAX961X_REG_CSA_DATA_MSB_ADDR, 2, adcTemp);
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
UINT8_T MAX961X_I2C_ReadOutVoltage(MAX961X_HandleType* MAX961x)
{
	UINT8_T _return = OK_0;
	UINT8_T adcTemp[2] = { 0 };
	//---准备读取 输入电压
	_return = MAX961X_I2C_WriteSingle(MAX961x, MAX961X_REG_CONTROL_REG1, MAX961X_READ_CHANNEL_OUTPUT_VOLTAGE);
	if (_return == OK_0)
	{
		//---读取OUT端的输出电压的值
		_return = MAX961X_I2C_ReadBulk(MAX961x, MAX961X_REG_OUT_DATA_MSB_ADDR, 2, adcTemp);
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
UINT8_T MAX961X_I2C_ReadSetVoltage(MAX961X_HandleType* MAX961x)
{
	UINT8_T _return = OK_0;
	UINT8_T adcTemp[2] = { 0 };
	//---准备读取 输入电压
	_return = MAX961X_I2C_WriteSingle(MAX961x, MAX961X_REG_CONTROL_REG1, MAX961X_READ_CHANNEL_SET_VOLTAGE);
	if (_return == OK_0)
	{
		//---读取SET端的输出电压的值
		_return = MAX961X_I2C_ReadBulk(MAX961x, MAX961X_REG_SET_DATA_MSB_ADDR, 2, adcTemp);
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
UINT8_T MAX961X_I2C_ReadTemp(MAX961X_HandleType* MAX961x)
{
	UINT8_T _return = OK_0;
	UINT8_T adcTemp[2] = { 0 };
	//---准备读取 内部温度
	_return = MAX961X_I2C_WriteSingle(MAX961x, MAX961X_REG_CONTROL_REG1, MAX961X_READ_CHANNEL_TEMPERATURE);
	if (_return == OK_0)
	{
		//---读取内部温度
		_return = MAX961X_I2C_ReadBulk(MAX961x, MAX961X_REG_TEMP_DATA_MSB_ADDR, 2, adcTemp);
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
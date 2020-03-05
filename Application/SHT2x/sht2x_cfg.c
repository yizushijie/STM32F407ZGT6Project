#include "sht2x_cfg.h"

//===变量的定义
SHT2X_HandleType g_Sht2xDevice0 = { 0 };
pSHT2X_HandleType pSht2xDevice0 = &g_Sht2xDevice0;


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SHT2X_I2C_Device0_Init(SHT2X_HandleType* SHT2x)
{
	SHT2x->msgI2C.pMsgI2Cx = NULL;
	SHT2x->msgI2C.msgSCL.msgPort = GPIOB;
	SHT2x->msgI2C.msgSCL.msgBit = LL_GPIO_PIN_6;
	SHT2x->msgI2C.msgSDA.msgPort = GPIOB;
	SHT2x->msgI2C.msgSDA.msgBit = LL_GPIO_PIN_7;
	SHT2x->msgI2C.msgHwMode = 0;
	SHT2x->msgI2C.msgPluseWidth = 0;
	SHT2x->msgI2C.pMsgDelayus = NULL;
	SHT2x->msgI2C.msgAddr = SHT2X_WADDR;//0x80;  // SHT2X_WRITE_ADDR;
	SHT2x->msgI2C.msgClockSpeed = 200000;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SHT2X_I2C_Device1_Init(SHT2X_HandleType* SHT2x)
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
UINT8_T SHT2X_I2C_Device2_Init(SHT2X_HandleType* SHT2x)
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
UINT8_T SHT2X_I2C_Init(SHT2X_HandleType *SHT2x, void(*pFuncDelayus)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHWI2C)
{
	UINT8_T _return = OK_0;
	//---指定设备的初始化
	if ((SHT2x != NULL) && (SHT2x == SHT2X_TASK_ONE))
	{
		SHT2X_I2C_Device0_Init(SHT2x);
	}
	else if ((SHT2x != NULL) && (SHT2x == SHT2X_TASK_TWO))
	{
		SHT2X_I2C_Device1_Init(SHT2x);
	}
	else if ((SHT2x != NULL) && (SHT2x == SHT2X_TASK_THREE))
	{
		SHT2X_I2C_Device2_Init(SHT2x);
	}
	else
	{
		return ERROR_1;
	}
	//---判断是硬件I2C还是软件I2C
	(isHWI2C != 0) ? (_return = I2CTask_MHW_Init(&(SHT2x->msgI2C),pFuncDelayus, pFuncTimerTick)):(_return = I2CTask_MSW_Init(&(SHT2x->msgI2C), pFuncDelayus, pFuncTimerTick));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SHT2X_I2C_DeInit(SHT2X_HandleType *SHT2x)
{
	//---注销I2C设备
	return I2CTask_Master_DeInit(&(SHT2x->msgI2C));
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SHT2X_SWI2C_WriteCmd(SHT2X_HandleType *SHT2x, UINT8_T cmd)
{
	UINT8_T _return = OK_0;
	//---启动并发送地址
	_return = I2CTask_MSW_START(&(SHT2x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_2;
		goto GoToExit;
	}
	//---发送命令
	I2CTask_MSW_SendByte(&(SHT2x->msgI2C), cmd);
	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(SHT2x->msgI2C));
GoToExit:
	//---发送停止信号
	I2CTask_MSW_STOP(&(SHT2x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SHT2X_HWI2C_WriteCmd(SHT2X_HandleType *SHT2x, UINT8_T cmd)
{
	UINT8_T _return = OK_0;
	//---启动IIC并发送器件地址，写数据
	_return = I2CTask_MHW_PollMode_START(&(SHT2x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_1;
		goto GoToExit;
	}
	//---发送数据，内部寄存器数据
	_return = I2CTask_MHW_PollMode_SendByte(&(SHT2x->msgI2C), cmd, 1);
	if (_return != OK_0)
	{
		//---发送数据错误
		_return = ERROR_2;
		goto GoToExit;
	}
	//---退出操作入口
GoToExit:
	//---发送停止信号
	I2CTask_MHW_PollMode_STOP(&(SHT2x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SHT2X_I2C_WriteCmd(SHT2X_HandleType *SHT2x, UINT8_T cmd)
{
	if (SHT2x->msgI2C.msgHwMode == 0)
	{
		return SHT2X_SWI2C_WriteCmd(SHT2x, cmd);
	}
	else
	{
		I2CTask_MHW_CheckClock(&(SHT2x->msgI2C));
		//---硬件I2C
		return SHT2X_HWI2C_WriteCmd(SHT2x, cmd);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SHT2X_I2C_SoftReset(SHT2X_HandleType *SHT2x)
{
	return SHT2X_I2C_WriteCmd(SHT2x, SHT2X_CMD_SOFT_RESET_DEVICE);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SHT2X_SWI2C_GetSerialNumber(SHT2X_HandleType *SHT2x)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//====Read from memory location 1
	//---启动并发送地址
	_return = I2CTask_MSW_START(&(SHT2x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_2;
		goto GoToExit;
	}
	//---发送命令---Command for readout on-chip memory
	I2CTask_MSW_SendByte(&(SHT2x->msgI2C), 0xFA);
	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(SHT2x->msgI2C));
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_3;
		goto GoToExit;
	}
	//---发送命令---on-chip memory address
	I2CTask_MSW_SendByte(&(SHT2x->msgI2C), 0x0F);
	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(SHT2x->msgI2C));
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_4;
		goto GoToExit;
	}
	//---启动并发送地址
	_return = I2CTask_MSW_START(&(SHT2x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---启动度数据失败
		_return = ERROR_5;
		goto GoToExit;
	}
	//---Read SNB和Read SNBCRC
	for (i = 0; i < 8; i++)
	{
		//---读取数据
		SHT2x->msgSerialNumber[i] = I2CTask_MSW_ReadByte(&(SHT2x->msgI2C));
		if (i == 7)
		{
			_return = 1;
		}

		//---发送应答信号
		I2CTask_MSW_SendACK(&(SHT2x->msgI2C), _return);
	}
	//===Read from memory location 1
	//---启动并发送地址
	_return = I2CTask_MSW_START(&(SHT2x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_6;
		goto GoToExit;
	}
	//---发送命令---Command for readout on-chip memory
	I2CTask_MSW_SendByte(&(SHT2x->msgI2C), 0xFC);
	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(SHT2x->msgI2C));
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_7;
		goto GoToExit;
	}
	//---发送命令---on-chip memory address
	I2CTask_MSW_SendByte(&(SHT2x->msgI2C), 0xC9);
	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(SHT2x->msgI2C));
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_8;
		goto GoToExit;
	}
	//---启动并发送地址
	_return = I2CTask_MSW_START(&(SHT2x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---启动度数据失败
		_return = ERROR_9;
		goto GoToExit;
	}
	//---Read SNC和Read SNCCRC
	for (i = 0; i < 6; i++)
	{
		//---读取数据
		SHT2x->msgSerialNumber[8 + i] = I2CTask_MSW_ReadByte(&(SHT2x->msgI2C));
		if (i == 5)
		{
			_return = 1;
		}
		//---发送应答信号
		I2CTask_MSW_SendACK(&(SHT2x->msgI2C), _return);
	}

GoToExit:
	//---发送停止信号
	I2CTask_MSW_STOP(&(SHT2x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SHT2X_HWI2C_GetSerialNumber(SHT2X_HandleType *SHT2x)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//====Read from memory location 1
	//---启动并发送地址
//---启动IIC并发送器件地址，写数据
	_return = I2CTask_MHW_PollMode_START(&(SHT2x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_2;
		goto GoToExit;
	}
	//---发送命令---Command for readout on-chip memory
	_return = I2CTask_MHW_PollMode_SendByte(&(SHT2x->msgI2C), 0xFA, 0);
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_3;
		goto GoToExit;
	}
	//---发送命令---on-chip memory address
	_return = I2CTask_MHW_PollMode_SendByte(&(SHT2x->msgI2C), 0x0F, 1);
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_4;
		goto GoToExit;
	}
	//---启动并发送地址
	_return = I2CTask_MHW_PollMode_START(&(SHT2x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---启动度数据失败
		_return = ERROR_5;
		goto GoToExit;
	}
	//---Read SNB和Read SNBCRC
	for (i = 0; i < 8; i++)
	{
		if (i == (7))
		{
			_return = 1;
		}
		//---发送应答信号
		I2CTask_MHW_SendACK(&(SHT2x->msgI2C), _return);
		//---读取数据
		SHT2x->msgSerialNumber[i] = I2CTask_MHW_PollMode_ReadByte(&(SHT2x->msgI2C));
	}
	//===Read from memory location 1
	//---启动并发送地址
	_return = I2CTask_MHW_PollMode_START(&(SHT2x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_6;
		goto GoToExit;
	}
	//---发送命令---Command for readout on-chip memory
	_return = I2CTask_MHW_PollMode_SendByte(&(SHT2x->msgI2C), 0xFC, 0);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_7;
		goto GoToExit;
	}
	//---发送命令---on-chip memory address
	_return = I2CTask_MHW_PollMode_SendByte(&(SHT2x->msgI2C), 0xC9, 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_8;
		goto GoToExit;
	}
	//---启动并发送地址
	_return = I2CTask_MHW_PollMode_START(&(SHT2x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---启动度数据失败
		_return = ERROR_9;
		goto GoToExit;
	}
	//---Read SNC和Read SNCCRC
	for (i = 0; i < 6; i++)
	{
		if (i == (5))
		{
			_return = 1;
		}
		//---发送应答信号
		I2CTask_MHW_SendACK(&(SHT2x->msgI2C), _return);
		//---读取数据
		SHT2x->msgSerialNumber[8 + i] = I2CTask_MHW_PollMode_ReadByte(&(SHT2x->msgI2C));
	}
	_return = OK_0;
	//---退出入口
GoToExit:
	//---发送停止信号
	I2CTask_MHW_PollMode_STOP(&(SHT2x->msgI2C));
	return _return;
}
///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SHT2X_I2C_GetSerialNumber(SHT2X_HandleType *SHT2x)
{
	if (SHT2x->msgI2C.msgHwMode == 0)
	{
		return SHT2X_SWI2C_GetSerialNumber(SHT2x);
	}
	else
	{
		I2CTask_MHW_CheckClock(&(SHT2x->msgI2C));
		//---硬件I2C
		return SHT2X_HWI2C_GetSerialNumber(SHT2x);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SHT2X_I2C_ReadUserReg(SHT2X_HandleType *SHT2x, UINT8_T *pReg)
{
	UINT8_T _return = OK_0;
	//---启动并发送地址
	_return = I2CTask_MSW_START(&(SHT2x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_2;
		goto GoToExit;
	}
	//---发送寄存器命令
	I2CTask_MSW_SendByte(&(SHT2x->msgI2C), SHT2X_CMD_USER_READ_REG);
	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(SHT2x->msgI2C));
	if (_return != OK_0)
	{
		//---命令发送失败
		_return = ERROR_3;
		goto GoToExit;
	}
	//---启动并发送地址
	_return = I2CTask_MSW_START(&(SHT2x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---启动读数据失败
		_return = ERROR_4;
		goto GoToExit;
	}
	//---读取数据
	*pReg = I2CTask_MSW_ReadByte(&(SHT2x->msgI2C));
GoToExit:
	//---发送停止信号
	I2CTask_MSW_STOP(&(SHT2x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SHT2X_I2C_WriteUserReg(SHT2X_HandleType *SHT2x, UINT8_T reg)
{
	UINT8_T _return = OK_0;
	//---启动并发送地址
	_return = I2CTask_MSW_START(&(SHT2x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_2;
		goto GoToExit;
	}
	//---发送寄存器命令
	I2CTask_MSW_SendByte(&(SHT2x->msgI2C), SHT2X_CMD_USER_WRITE_REG);
	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(SHT2x->msgI2C));
	if (_return != OK_0)
	{
		//---命令发送失败
		_return = ERROR_2;
		goto GoToExit;
	}
	//---写入数据
	I2CTask_MSW_SendByte(&(SHT2x->msgI2C), reg);
	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(SHT2x->msgI2C));
GoToExit:
	//---发送停止信号
	I2CTask_MSW_STOP(&(SHT2x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SHT2X_I2C_ReadPoll(SHT2X_HandleType *SHT2x, UINT16_T *pVal, UINT8_T cmd)
{
	UINT8_T _return = OK_0;
	UINT16_T temp = 0;
	UINT8_T tempL = 0;
	UINT8_T tempH = 0;
	UINT16_T timeout = 0;
	//---启动并发送地址
	_return = I2CTask_MSW_START(&(SHT2x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_2;
		goto GoToExit;
	}
	//---发送温度测量命令
	I2CTask_MSW_SendByte(&(SHT2x->msgI2C), cmd);
	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(SHT2x->msgI2C));
	if (_return != OK_0)
	{
		//---命令发送失败
		_return = ERROR_2;
		goto GoToExit;
	}
	//---等待测量结束
	while (1)
	{
		//---启动并发送地址
		_return = I2CTask_MSW_START(&(SHT2x->msgI2C), 0);
		if (_return == OK_0)
		{
			//---启动数据读取成功，退出while循环
			break;
		}
		timeout++;
		//---超时判断
		if (timeout > 5000)
		{
			//---发生超时错误
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	//---读取高位置
	tempH = I2CTask_MSW_ReadByte(&(SHT2x->msgI2C));
	//---发送应答信号
	I2CTask_MSW_SendACK(&(SHT2x->msgI2C), 0);
	//---读取低位置
	tempL = I2CTask_MSW_ReadByte(&(SHT2x->msgI2C));
	//---发送不应答信号
	I2CTask_MSW_SendACK(&(SHT2x->msgI2C), 1);
	temp = tempH;
	temp = (temp << 8) + tempL;
	temp &= 0xFFFC;
	*pVal = temp;

GoToExit:
	//---发送停止信号
	I2CTask_MSW_STOP(&(SHT2x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SHT2X_I2C_ReadTempPoll(SHT2X_HandleType *SHT2x)
{
	UINT8_T _return = OK_0;
	UINT16_T temp = 0;
	//---读取温度值
	_return = SHT2X_I2C_ReadPoll(SHT2x, &temp, SHT2X_CMD_TRIG_TEMP_MEASUREMENT_POLL);
	//---计算温度值
	INT32_T tempX100 = temp;
	tempX100 *= 17572;
	tempX100 >>= 16;
	SHT2x->msgTemp = (INT16_T)(tempX100 - 4685);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SHT2X_I2C_ReadHumiPoll(SHT2X_HandleType *SHT2x)
{
	UINT8_T _return = OK_0;
	UINT16_T temp = 0;
	//---读取湿度值
	_return = SHT2X_I2C_ReadPoll(SHT2x, &temp, SHT2X_CMD_TRIG_HUMI_MEASUREMENT_POLL);
	//---计算湿度值
	INT32_T tempX100 = temp;
	tempX100 *= 12500;
	tempX100 >>= 16;
	SHT2x->msgHumiX100 = (INT16_T)(tempX100 - 600);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SHT2X_I2C_ReadHM(SHT2X_HandleType *SHT2x, UINT16_T *pVal, UINT8_T cmd)
{
	UINT8_T _return = OK_0;
	UINT16_T temp = 0;
	UINT8_T tempL = 0;
	UINT8_T tempH = 0;
	UINT16_T timeout = 0;
	//---启动并发送地址
	_return = I2CTask_MSW_START(&(SHT2x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_2;
		goto GoToExit;
	}
	//---发送温度测量命令
	I2CTask_MSW_SendByte(&(SHT2x->msgI2C), cmd);
	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(SHT2x->msgI2C));
	if (_return != OK_0)
	{
		//---命令发送失败
		_return = ERROR_2;
		goto GoToExit;
	}
	//---启动并发送地址
	_return = I2CTask_MSW_START(&(SHT2x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---启动数据读取失败，退出while循环
		_return = ERROR_3;
		goto GoToExit;
	}
	//---等待从机释放SCL数据线
	while (GPIO_GET_STATE(SHT2x->msgI2C.msgSCL.msgPort, SHT2x->msgI2C.msgSCL.msgBit) ==
		0)
	{
		timeout++;

		//---超时判断
		if (timeout > 5000)
		{
			//---发生超时错误，从机不释放SCL数据线
			_return = ERROR_4;
			goto GoToExit;
		}
	}
	//---读取高位置
	tempH = I2CTask_MSW_ReadByte(&(SHT2x->msgI2C));
	//---发送应答信号
	I2CTask_MSW_SendACK(&(SHT2x->msgI2C), 0);
	//---读取低位置
	tempL = I2CTask_MSW_ReadByte(&(SHT2x->msgI2C));
	//---发送不应答信号
	I2CTask_MSW_SendACK(&(SHT2x->msgI2C), 1);
	temp = tempH;
	temp = (temp << 8) + tempL;
	temp &= 0xFFFC;
	*pVal = temp;
GoToExit:

	//---发送停止信号
	I2CTask_MSW_STOP(&(SHT2x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SHT2X_I2C_ReadTempHM(SHT2X_HandleType *SHT2x)
{
	UINT8_T _return = OK_0;
	UINT16_T temp = 0;
	//---读取温度值
	_return = SHT2X_I2C_ReadHM(SHT2x, &temp, SHT2X_CMD_TRIG_TEMP_MEASUREMENT_HM);
	//---计算温度值
	INT32_T tempX100 = temp;
	tempX100 *= 17572;
	tempX100 >>= 16;
	SHT2x->msgTemp = (INT16_T)(tempX100 - 4685);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SHT2X_I2C_ReadHumiHM(SHT2X_HandleType *SHT2x)
{
	UINT8_T _return = OK_0;
	UINT16_T temp = 0;
	//---读取湿度值
	_return = SHT2X_I2C_ReadPoll(SHT2x, &temp, SHT2X_CMD_TRIG_HUMI_MEASUREMENT_HM);
	//---计算湿度值
	INT32_T tempX100 = temp;
	tempX100 *= 12500;
	tempX100 >>= 16;
	SHT2x->msgHumiX100 = (INT16_T)(tempX100 - 600);
	return _return;
}
///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
float SHT2X_I2C_GetTemp(SHT2X_HandleType* SHT2x)
{
	float tempVal = SHT2x->msgTemp;
	//---转换温度对应实际的温度值
	tempVal /= 100.0;
	return tempVal;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
float SHT2X_I2C_GetHumi(SHT2X_HandleType* SHT2x)
{
	float tempVal = SHT2x->msgHumiX100;
	//---转换温度对应实际的温度值
	tempVal /= 100.0;
	return tempVal;
}

#include "pcf8563_cfg.h"

//===变量的定义
PCF8563_HandleType g_Pcf8563Device0 = { 0 };
pPCF8563_HandleType pPcf8563Device0 = &g_Pcf8563Device0;


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_I2C_Device0_Init(PCF8563_HandleType* PCF8563x)
{
	PCF8563x->msgI2C.pMsgI2Cx = NULL;
	PCF8563x->msgI2C.msgSCL.msgPort = GPIOB;
	PCF8563x->msgI2C.msgSCL.msgBit = LL_GPIO_PIN_6;
	PCF8563x->msgI2C.msgSDA.msgPort = GPIOB;
	PCF8563x->msgI2C.msgSDA.msgBit = LL_GPIO_PIN_7;
	PCF8563x->msgI2C.msgHwMode = 0;
	PCF8563x->msgI2C.msgPluseWidth = 0;
	PCF8563x->msgI2C.pMsgDelayus = NULL;
	PCF8563x->msgI2C.msgAddr = 0xA2;//PCF8563_WRITE_ADDR;
	PCF8563x->msgI2C.msgClockSpeed = 200000;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_I2C_Device1_Init(PCF8563_HandleType* PCF8563x)
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
UINT8_T PCF8563_I2C_Device2_Init(PCF8563_HandleType* PCF8563x)
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
UINT8_T PCF8563_I2C_Init(PCF8563_HandleType *PCF8563x, void(*pFuncDelayus)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHWI2C)
{
	UINT8_T _return = OK_0;
	//---指定设备的初始化
	if ((PCF8563x != NULL) && (PCF8563x == PCF8563_TASK_ONE))
	{
		PCF8563_I2C_Device0_Init(PCF8563x);
	}
	else if ((PCF8563x != NULL) && (PCF8563x == PCF8563_TASK_TWO))
	{
		PCF8563_I2C_Device1_Init(PCF8563x);
	}
	else if ((PCF8563x != NULL) && (PCF8563x == PCF8563_TASK_THREE))
	{
		PCF8563_I2C_Device2_Init(PCF8563x);
	}
	else
	{
		return ERROR_1;
	}
	//---判断是硬件I2C还是软件I2C
	(isHWI2C != 0) ? (_return = I2CTask_MHW_Init(&(PCF8563x->msgI2C),pFuncDelayus, pFuncTimerTick)) : (_return = I2CTask_MSW_Init(&(PCF8563x->msgI2C), pFuncDelayus, pFuncTimerTick));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_I2C_DeInit(PCF8563_HandleType *PCF8563x)
{
	//---注销I2C设备
	return I2CTask_Master_DeInit(&(PCF8563x->msgI2C));
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_SWI2C_WriteSingle(PCF8563_HandleType *PCF8563x, UINT8_T reg, UINT8_T val)
{
	UINT8_T _return = OK_0;
	//---启动并发送地址
	_return = I2CTask_MSW_START(&(PCF8563x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_2;
		goto GoToExit;
	}
	//---发送寄存器地址
	I2CTask_MSW_SendByte(&(PCF8563x->msgI2C), reg);
	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(PCF8563x->msgI2C));
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_3;
		goto GoToExit;
	}
	//---发送寄存器地址
	I2CTask_MSW_SendByte(&(PCF8563x->msgI2C), val);
	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(PCF8563x->msgI2C));
	//---退出入口
GoToExit:
	//---发送停止信号
	I2CTask_MSW_STOP(&(PCF8563x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_HWI2C_WriteSingle(PCF8563_HandleType *PCF8563x, UINT8_T reg, UINT8_T val)
{
	UINT8_T _return = OK_0;
	//---启动IIC并发送器件地址，写数据
	_return = I2CTask_MHW_PollMode_START(&(PCF8563x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_1;
		goto GoToExit;
	}
	//---发送寄存器地址,存储单元的地址
	_return = I2CTask_MHW_PollMode_SendByte(&(PCF8563x->msgI2C), reg, 0);
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_2;
		goto GoToExit;
	}
	//---发送数据，内部寄存器数据
	_return = I2CTask_MHW_PollMode_SendByte(&(PCF8563x->msgI2C), val, 1);
	if (_return != OK_0)
	{
		//---发送数据错误
		_return = ERROR_3;
		goto GoToExit;
	}
	//---退出操作入口
GoToExit:
	//---发送停止信号
	I2CTask_MHW_PollMode_STOP(&(PCF8563x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：写寄存器
//////输入参数:
//////输出参数:
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_I2C_WriteSingle(PCF8563_HandleType *PCF8563x, UINT8_T reg, UINT8_T val)
{
	if (PCF8563x->msgI2C.msgHwMode == 0)
	{
		return PCF8563_SWI2C_WriteSingle(PCF8563x, reg, val);
	}
	else
	{
		I2CTask_MHW_CheckClock(&(PCF8563x->msgI2C));
		//---硬件I2C
		return PCF8563_HWI2C_WriteSingle(PCF8563x, reg, val);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：软件模拟I2C，单字节读寄存器
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_SWI2C_ReadSingle(PCF8563_HandleType* PCF8563x, UINT8_T reg, UINT8_T* pVal)
{
	UINT8_T _return = OK_0;
	//---启动IIC并发送器件地址，写数据
	_return = I2CTask_MSW_START(&(PCF8563x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_1;
		goto GoToExit;
	}
	//---发送寄存器地址,存储单元的地址
	I2CTask_MSW_SendByte(&(PCF8563x->msgI2C), reg);
	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(PCF8563x->msgI2C));
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_2;
		goto GoToExit;
	}
	//---启动IIC并发送器件地址，读数据
	_return = I2CTask_MSW_START(&(PCF8563x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---启动读数据失败
		_return = ERROR_3;
		goto GoToExit;
	}
	//---读取数据
	*pVal = I2CTask_MSW_ReadByte(&(PCF8563x->msgI2C));
	//---发送不应答信号
	_return = I2CTask_MSW_SendACK(&(PCF8563x->msgI2C), 1);
GoToExit:
	//---发送停止信号
	I2CTask_MSW_STOP(&(PCF8563x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：硬件I2C，单字节读寄存器
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_HWI2C_ReadSingle(PCF8563_HandleType* PCF8563x, UINT8_T reg, UINT8_T* pVal)
{
	UINT8_T _return = OK_0;
	//---启动IIC并发送器件地址，写数据
	_return = I2CTask_MHW_PollMode_START(&(PCF8563x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_1;
		goto GoToExit;
	}
	//---发送寄存器地址,存储单元的地址
	_return = I2CTask_MHW_PollMode_SendByte(&(PCF8563x->msgI2C), reg, 0);
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_2;
		goto GoToExit;
	}
	//---启动IIC并发送器件地址，读数据
	_return = I2CTask_MHW_PollMode_START(&(PCF8563x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---启动读数据失败
		_return = ERROR_3;
		goto GoToExit;
	}
	//---发送不应答信号
	_return = I2CTask_MHW_SendACK(&(PCF8563x->msgI2C), 1);
	//---读取数据
	*pVal = I2CTask_MHW_PollMode_ReadByte(&(PCF8563x->msgI2C));
	//---退出入口
GoToExit:
	//---发送停止信号
	I2CTask_MHW_PollMode_STOP(&(PCF8563x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：I2C，单字节读寄存器
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_I2C_ReadSingle(PCF8563_HandleType* PCF8563x, UINT8_T reg, UINT8_T* pVal)
{
	if (PCF8563x->msgI2C.msgHwMode != 0)
	{
		I2CTask_MHW_CheckClock(&(PCF8563x->msgI2C));
		return PCF8563_HWI2C_ReadSingle(PCF8563x, reg, pVal);
	}
	else
	{
		return PCF8563_SWI2C_ReadSingle(PCF8563x, reg, pVal);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：读取寄存器
//////输入参数:
//////输出参数:
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_SWI2C_ReadBulk(PCF8563_HandleType *PCF8563x, UINT8_T reg, UINT8_T *pVal, UINT16_T length)
{
	UINT8_T _return = OK_0;
	UINT16_T i = 0;
	//---启动写数据
	_return = I2CTask_MSW_START(&(PCF8563x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_2;
		goto GoToExit;
	}
	//---发送寄存器地址
	I2CTask_MSW_SendByte(&(PCF8563x->msgI2C), reg);
	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(PCF8563x->msgI2C));
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_3;
		goto GoToExit;
	}
	//---发送停止信号
	I2CTask_MSW_STOP(&(PCF8563x->msgI2C));
	//---启动读取数据
	_return = I2CTask_MSW_START(&(PCF8563x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---启动读数据失败
		_return = ERROR_4;
		goto GoToExit;
	}
	for (i = 0; i < length; i++)
	{
		//---读取数据
		pVal[i] = I2CTask_MSW_ReadByte(&(PCF8563x->msgI2C));
		//---发送应答信号
		I2CTask_MSW_SendACK(&(PCF8563x->msgI2C), (i == (length - 1)) ? 1 : 0);
	}
	_return = OK_0;
	//---退出入口
GoToExit:
	//---发送停止信号
	I2CTask_MSW_STOP(&(PCF8563x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_HWI2C_ReadBulk(PCF8563_HandleType *PCF8563x, UINT8_T reg, UINT8_T *pVal, UINT16_T length)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---启动IIC并发送器件地址，写数据
	_return = I2CTask_MHW_PollMode_START(&(PCF8563x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_1;
		goto GoToExit;
	}
	//---发送寄存器地址,存储单元的地址
	_return = I2CTask_MHW_PollMode_SendByte(&(PCF8563x->msgI2C), reg, 0);
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_2;
		goto GoToExit;
	}
	//---启动IIC并发送器件地址，读数据
	_return = I2CTask_MHW_PollMode_START(&(PCF8563x->msgI2C), 0);
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
		I2CTask_MHW_SendACK(&(PCF8563x->msgI2C), (i == (length - 1)) ? 1 : 0);
		//---读取数据
		pVal[i] = I2CTask_MHW_PollMode_ReadByte(&(PCF8563x->msgI2C));
	}
	_return = OK_0;
	//---退出入口
GoToExit:
	//---发送停止信号
	I2CTask_MHW_PollMode_STOP(&(PCF8563x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：读取寄存器
//////输入参数:
//////输出参数:
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_I2C_ReadBulk(PCF8563_HandleType *PCF8563x, UINT8_T reg, UINT8_T *pVal, UINT16_T length)
{
	if (PCF8563x->msgI2C.msgHwMode == 0)
	{
		return PCF8563_SWI2C_ReadBulk(PCF8563x, reg, pVal, length);
	}
	else
	{
		I2CTask_MHW_CheckClock(&(PCF8563x->msgI2C));
		//---硬件I2C
		return PCF8563_HWI2C_ReadBulk(PCF8563x, reg, pVal, length);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数： UINT8_T PCF8563_ClockOut(UINT8_T preVal)
//////功	   能： PCF8563输出时钟，输出分频
//////输入参数:
//////输出参数:
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_I2C_ClockOut(PCF8563_HandleType *PCF8563x, UINT8_T preVal)
{
	UINT8_T _return = OK_0;
	UINT8_T temp = 0;
	//---写寄存器
	_return = PCF8563_I2C_WriteSingle(PCF8563x, PCF8563_REG_CLKOUT, (preVal | 0x80));
	if (_return != OK_0)
	{
		_return = ERROR_2;
		goto GoToExit;
	}
	//---读取寄存器
	_return = PCF8563_I2C_ReadSingle(PCF8563x, PCF8563_REG_CLKOUT, &temp);
	if (_return != OK_0)
	{
		_return = ERROR_3;
		goto GoToExit;
	}
	//---数据的校验
	if ((temp & 0x7F) != preVal)
	{
		_return = ERROR_1;
	}
GoToExit:
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：
//////输入参数:
//////输出参数:
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T PCF8563_I2C_ReadRTC(PCF8563_HandleType *PCF8563x)
{
	UINT8_T _return = OK_0;
	UINT8_T temp[7];
	//---读取时钟
	_return = PCF8563_I2C_ReadBulk(PCF8563x, PCF8563_REG_SECOND, temp, 7);
	//---解析数据
	if (_return == OK_0)
	{
		//---将获取的数据填充到缓存区
		PCF8563x->msgRTC.second = (temp[0] & 0x7F);
		PCF8563x->msgRTC.minute = (temp[1] & 0x7F);
		PCF8563x->msgRTC.hour = (temp[2] & 0x3F);
		PCF8563x->msgRTC.day = (temp[3] & 0x3F);
		PCF8563x->msgRTC.week = (temp[4] & 0x07);
		PCF8563x->msgRTC.month = (temp[5] & 0x1F);
		//---年份
		PCF8563x->msgRTC.year = temp[6];
		//---世纪
		if (temp[5] & 0x80)
		{
			PCF8563x->msgRTC.century = 0x19;
		}
		else
		{
			PCF8563x->msgRTC.century = 0x20;
		}
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
UINT8_T PCF8563_I2C_WriteRTC(PCF8563_HandleType *PCF8563x, RTC_HandleType rtc)
{
	UINT8_T _return = OK_0;
	//---判断数据类型是不是BCD码
	if ((rtc.century != 0x19) || (rtc.century != 0x20))
	{
		//===处理数据位BCD格式
		rtc.second = DecToBcd(rtc.second);
		rtc.minute = DecToBcd(rtc.minute);
		rtc.hour = DecToBcd(rtc.hour);
		rtc.day = DecToBcd(rtc.day);
		rtc.week = DecToBcd(rtc.week);
		rtc.month = DecToBcd(rtc.month);
		rtc.year = DecToBcd(rtc.year);
		rtc.century = DecToBcd(rtc.century);
	}
	//---世纪参数的处理
	if (rtc.century == 0x20)
	{
		rtc.month &= 0x3F;
	}
	else
	{
		rtc.month |= 0x80;
	}
	//---写秒
	_return = PCF8563_I2C_WriteSingle(PCF8563x, PCF8563_REG_SECOND, rtc.second);
	if (_return != OK_0)
	{
		_return = ERROR_2;
		goto GoToExit;
	}
	//---写分
	_return = PCF8563_I2C_WriteSingle(PCF8563x, PCF8563_REG_MINUTE, rtc.minute);
	if (_return != OK_0)
	{
		_return = ERROR_3;
		goto GoToExit;
	}
	//---写时
	_return = PCF8563_I2C_WriteSingle(PCF8563x, PCF8563_REG_HOURS, rtc.hour);
	if (_return != OK_0)
	{
		_return = ERROR_4;
		goto GoToExit;
	}
	//---写天
	_return = PCF8563_I2C_WriteSingle(PCF8563x, PCF8563_REG_DAY, rtc.day);
	if (_return != OK_0)
	{
		_return = ERROR_5;
		goto GoToExit;
	}
	//---写星期
	_return = PCF8563_I2C_WriteSingle(PCF8563x, PCF8563_REG_WEEK, rtc.week);
	if (_return != OK_0)
	{
		_return = ERROR_6;
		goto GoToExit;
	}
	//---写月
	_return = PCF8563_I2C_WriteSingle(PCF8563x, PCF8563_REG_MONTH, rtc.month);
	if (_return != OK_0)
	{
		_return = ERROR_7;
		goto GoToExit;
	}
	//---写年
	_return = PCF8563_I2C_WriteSingle(PCF8563x, PCF8563_REG_YEAR, rtc.year);
GoToExit:
	return _return;
}
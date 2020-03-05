#include "bmp180_cfg.h"

//===全局变量定义
BMP180_HandleType		g_Bmp180Device0 = { 0 };
pBMP180_HandleType		pBmp180Device0 = &g_Bmp180Device0;


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T BMP180_I2C_Device0_Init(BMP180_HandleType* BMP180x)
{
	BMP180x->msgI2C.pMsgI2Cx = NULL;
	BMP180x->msgI2C.msgSCL.msgPort = GPIOB;
	BMP180x->msgI2C.msgSCL.msgBit = LL_GPIO_PIN_6;
	BMP180x->msgI2C.msgSDA.msgPort = GPIOB;
	BMP180x->msgI2C.msgSDA.msgBit = LL_GPIO_PIN_7;
	BMP180x->msgI2C.msgHwMode = 0;
	BMP180x->msgI2C.msgPluseWidth = 0;
	BMP180x->msgI2C.pMsgDelayus = NULL;
	BMP180x->msgI2C.msgAddr = BMP180_WADDR;
	BMP180x->msgI2C.msgClockSpeed = 100000;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T BMP180_I2C_Device1_Init(BMP180_HandleType* BMP180x)
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
UINT8_T BMP180_I2C_Device2_Init(BMP180_HandleType* BMP180x)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：初始化
//////输入参数:isHWI2C---1 硬件，0 软件
//////输出参数:
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T BMP180_I2C_Init(BMP180_HandleType* BMP180x, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHWI2C)
{
	UINT8_T _return = OK_0;
	//---指定设备的初始化
	if ((BMP180x != NULL) && (BMP180x == BMP180_TASK_ONE))
	{
		BMP180_I2C_Device0_Init(BMP180x);
	}
	else if ((BMP180x != NULL) && (BMP180x == BMP180_TASK_TWO))
	{
		BMP180_I2C_Device1_Init(BMP180x);
	}
	else if ((BMP180x != NULL) && (BMP180x == BMP180_TASK_THREE))
	{
		BMP180_I2C_Device2_Init(BMP180x);
	}
	else
	{
		return ERROR_1;
	}
	//---判断是硬件I2C还是软件I2C
	(isHWI2C != 0) ? (_return = I2CTask_MHW_Init(&(BMP180x->msgI2C),pFuncDelayus, pFuncTimerTick)) : (_return = I2CTask_MSW_Init(&(BMP180x->msgI2C), pFuncDelayus, pFuncTimerTick));
	//---ms延时函数
	BMP180x->pMsgDelayms = ((pFuncDelayms != NULL) ? pFuncDelayms : DelayTask_ms);
	//---配置初始化
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T BMP180_I2C_DeInit(BMP180_HandleType* BMP180x)
{
	return I2CTask_Master_DeInit(&(BMP180x->msgI2C));
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：单字节写写寄存器
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T BMP180_SWI2C_WriteSingle(BMP180_HandleType* BMP180x, UINT8_T addr, UINT8_T val)
{
	UINT8_T _return = OK_0;
	//---启动IIC并发送器件地址，写数据
	_return = I2CTask_MSW_START(&(BMP180x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_1;
		goto GoToExit;
	}
	//---发送寄存器地址,内部寄存器地址
	I2CTask_MSW_SendByte(&(BMP180x->msgI2C), addr);
	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(BMP180x->msgI2C));
	if (_return != OK_0)
	{
		//---发送寄存器地址错误
		_return = ERROR_2;
		goto GoToExit;
	}
	//---发送数据，内部寄存器数据
	I2CTask_MSW_SendByte(&(BMP180x->msgI2C), val);
	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(BMP180x->msgI2C));
	//---退出操作入口
GoToExit:
	//---发送停止信号
	I2CTask_MSW_STOP(&(BMP180x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T BMP180_HWI2C_WriteSingle(BMP180_HandleType* BMP180x, UINT8_T addr, UINT8_T val)
{
	UINT8_T _return = OK_0;
	//---启动IIC并发送器件地址，写数据
	_return = I2CTask_MHW_PollMode_START(&(BMP180x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_1;
		goto GoToExit;
	}
	//---发送寄存器地址,内部寄存器地址
	_return = I2CTask_MHW_PollMode_SendByte(&(BMP180x->msgI2C), addr, 0);
	if (_return != OK_0)
	{
		//---发送寄存器地址错误
		_return = ERROR_2;
		goto GoToExit;
	}
	//---发送数据，内部寄存器数据
	_return = I2CTask_MHW_PollMode_SendByte(&(BMP180x->msgI2C), val, 1);
	if (_return != OK_0)
	{
		//---发送数据错误
		_return = ERROR_3;
		goto GoToExit;
	}
	//---退出操作入口
GoToExit:
	//---发送停止信号
	I2CTask_MHW_PollMode_STOP(&(BMP180x->msgI2C));
	return _return;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T BMP180_I2C_WriteSingle(BMP180_HandleType* BMP180x, UINT8_T addr, UINT8_T val)
{
	if (BMP180x->msgI2C.msgHwMode != 0)
	{
		I2CTask_MHW_CheckClock(&(BMP180x->msgI2C));
		return  BMP180_HWI2C_WriteSingle(BMP180x, addr, val);
	}
	else
	{
		return  BMP180_SWI2C_WriteSingle(BMP180x, addr, val);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T BMP180_SWI2C_ReadSingle(BMP180_HandleType* BMP180x, UINT8_T addr, UINT16_T* pVal)
{
	UINT8_T _return = OK_0;
	UINT16_T readTemp = 0;
	//---启动IIC并发送器件地址，写数据
	_return = I2CTask_MSW_START(&(BMP180x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_1;
		goto GoToExit;
	}
	//---发送寄存器地址,存储单元的地址
	I2CTask_MSW_SendByte(&(BMP180x->msgI2C), addr);
	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(BMP180x->msgI2C));
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_2;
		goto GoToExit;
	}
	//---启动IIC并发送器件地址，读数据
	_return = I2CTask_MSW_START(&(BMP180x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---启动读数据失败
		_return = ERROR_3;
		goto GoToExit;
	}
	//---读取高位数据
	readTemp = I2CTask_MSW_ReadByte(&(BMP180x->msgI2C));
	//---发送应答信号
	_return = I2CTask_MSW_SendACK(&(BMP180x->msgI2C), 0);
	readTemp <<= 8;
	//---读取低位数据
	readTemp |= I2CTask_MSW_ReadByte(&(BMP180x->msgI2C));
	//---发送不应答信号
	_return = I2CTask_MSW_SendACK(&(BMP180x->msgI2C), 1);
	*pVal = readTemp;
	//---退出操作入口
GoToExit:
	//---发送停止信号
	I2CTask_MSW_STOP(&(BMP180x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T BMP180_HWI2C_ReadSingle(BMP180_HandleType* BMP180x, UINT8_T addr, UINT16_T* pVal)
{
	UINT8_T _return = OK_0;
	UINT16_T readTemp = 0;
	//---启动IIC并发送器件地址，写数据
	_return = I2CTask_MHW_PollMode_START(&(BMP180x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_1;
		goto GoToExit;
	}
	//---发送寄存器地址,存储单元的地址
	_return = I2CTask_MHW_PollMode_SendByte(&(BMP180x->msgI2C), addr, 0);
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_2;
		goto GoToExit;
	}
	//---启动IIC并发送器件地址，读数据
	_return = I2CTask_MHW_PollMode_START(&(BMP180x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---启动读数据失败
		_return = ERROR_3;
		goto GoToExit;
	}
	//---发送应答信号
	_return = I2CTask_MHW_SendACK(&(BMP180x->msgI2C), 0);
	//---读取高位数据
	readTemp = I2CTask_MHW_PollMode_ReadByte(&(BMP180x->msgI2C));
	readTemp <<= 8;
	//---不发送应答信号
	_return = I2CTask_MHW_SendACK(&(BMP180x->msgI2C), 1);
	//---读取低位数据
	readTemp |= I2CTask_MHW_PollMode_ReadByte(&(BMP180x->msgI2C));
	*pVal = readTemp;
	//---退出操作入口
GoToExit:
	//---发送停止信号
	I2CTask_MHW_PollMode_STOP(&(BMP180x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T BMP180_I2C_ReadSingle(BMP180_HandleType* BMP180x, UINT8_T addr, UINT16_T* pVal)
{
	if (BMP180x->msgI2C.msgHwMode != 0)
	{
		I2CTask_MHW_CheckClock(&(BMP180x->msgI2C));
		return  BMP180_HWI2C_ReadSingle(BMP180x, addr, pVal);
	}
	else
	{
		return  BMP180_SWI2C_ReadSingle(BMP180x, addr, pVal);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T BMP180_SWI2C_ReadBulk(BMP180_HandleType* BMP180x, UINT8_T addr, UINT8_T* pVal, UINT8_T length)
{
	//UINT8_T readTemp[6] = { 0 };
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---启动IIC并发送器件地址，写数据
	_return = I2CTask_MSW_START(&(BMP180x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_1;
		goto GoToExit;
	}
	//---发送寄存器地址,高地址
	I2CTask_MSW_SendByte(&(BMP180x->msgI2C), addr);
	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(BMP180x->msgI2C));
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_2;
		goto GoToExit;
	}
	//---启动IIC并发送器件地址，读数据
	_return = I2CTask_MSW_START(&(BMP180x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---启动读数据失败
		_return = ERROR_3;
		goto GoToExit;
	}
	//---连续读取6组数据
	for (i = 0; i < length; i++)
	{
		//---读取数据
		pVal[i] = I2CTask_MSW_ReadByte(&(BMP180x->msgI2C));
		//---发送应答信号
		I2CTask_MSW_SendACK(&(BMP180x->msgI2C), (i == (length - 1)) ? 1 : 0);
	}
	_return = OK_0;
GoToExit:
	//---发送停止信号
	I2CTask_MSW_STOP(&(BMP180x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T BMP180_HWI2C_ReadBulk(BMP180_HandleType* BMP180x, UINT8_T addr, UINT8_T* pVal, UINT8_T length)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---启动IIC并发送器件地址，写数据
	_return = I2CTask_MHW_PollMode_START(&(BMP180x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_1;
		goto GoToExit;
	}
	//---发送寄存器地址,高地址
	_return = I2CTask_MHW_PollMode_SendByte(&(BMP180x->msgI2C), addr, 0);
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_2;
		goto GoToExit;
	}
	//---启动IIC并发送器件地址，读数据
	_return = I2CTask_MHW_PollMode_START(&(BMP180x->msgI2C), 0);
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
		I2CTask_MHW_SendACK(&(BMP180x->msgI2C), (i == (length-1))?1:0);
		//---读取数据
		pVal[i] = I2CTask_MHW_PollMode_ReadByte(&(BMP180x->msgI2C));
	}
	_return = OK_0;
GoToExit:
	//---发送停止信号
	I2CTask_MHW_PollMode_STOP(&(BMP180x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T BMP180_I2C_ReadBulk(BMP180_HandleType* BMP180x, UINT8_T addr, UINT8_T* pVal, UINT8_T length)
{
	if (BMP180x->msgI2C.msgHwMode == 1)
	{
		return BMP180_HWI2C_ReadBulk(BMP180x, addr, pVal, length);
	}
	else
	{
		return BMP180_SWI2C_ReadBulk(BMP180x, addr, pVal, length);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T BMP180_I2C_ReadChipId(BMP180_HandleType* BMP180x, UINT8_T* pChipID)
{
	UINT8_T _return = OK_0;
	UINT16_T tempID = 0;
	_return = BMP180_I2C_ReadSingle(BMP180x, BMP180_REG_ADDR_CHIP_ID, &tempID);
	*pChipID = (UINT8_T)(tempID >> 8);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T BMP180_I2C_ReadDefaultTemp(BMP180_HandleType* BMP180x)
{
	UINT8_T _return = OK_0;
	UINT16_T tempID = 0;
	_return = BMP180_I2C_WriteSingle(BMP180x, BMP180_REG_ADDR_CTRL_MEAS, 0x2E);
	BMP180x->pMsgDelayms(5);
	_return = BMP180_I2C_ReadSingle(BMP180x, BMP180_REG_ADDR_OUT_MSB,&tempID);
	BMP180x->msgDefaultTemp=tempID;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T BMP180_I2C_ReadDefaultGasPress(BMP180_HandleType* BMP180x)
{
	UINT8_T _return = OK_0;
	UINT16_T tempID = 0;
	_return = BMP180_I2C_WriteSingle(BMP180x, BMP180_REG_ADDR_CTRL_MEAS, 0x34|(BMP180_OSS<<6));
	#if (BMP180_OSS==1)
		BMP180x->msgDelayms(8);
	#elif  (BMP180_OSS==2)
		BMP180x->msgDelayms(14);
	#elif  (BMP180_OSS==3)
		BMP180x->msgDelayms(26);
	#else
		BMP180x->pMsgDelayms(5);
	#endif
	_return = BMP180_I2C_ReadSingle(BMP180x, BMP180_REG_ADDR_OUT_MSB,&tempID);
	BMP180x->msgDefaultGasPress=tempID;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取温度，读取大气压，海拔高度
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T BMP180_I2C_ReadTempGasPressAltitude(BMP180_HandleType* BMP180x)
{
	BMP180_I2C_ReadDefaultTemp(BMP180x);
	BMP180_I2C_ReadDefaultGasPress(BMP180x);

	BMP180x->msgParam.msgX1 = ((BMP180x->msgDefaultTemp - BMP180x->msgParam.msgAC6) * BMP180x->msgParam.msgAC5) >> 15;
	BMP180x->msgParam.msgX2 = (((long)BMP180x->msgParam.msgMC) << 11) / (BMP180x->msgParam.msgX1 + BMP180x->msgParam.msgMD);
	BMP180x->msgParam.msgB5 = BMP180x->msgParam.msgX1 + BMP180x->msgParam.msgX2;
	//---计算温度
	BMP180x->msgTemp = (BMP180x->msgParam.msgB5 + 8) >> 4;

	BMP180x->msgParam.msgB6 = BMP180x->msgParam.msgB5 - 4000;
	BMP180x->msgParam.msgX1 = ((long)BMP180x->msgParam.msgB2 * ((BMP180x->msgParam.msgB6 * BMP180x->msgParam.msgB6) >> 12)) >> 11;
	BMP180x->msgParam.msgX2 = ((long)BMP180x->msgParam.msgAC2) * BMP180x->msgParam.msgB6 >> 11;
	BMP180x->msgParam.msgX3 = BMP180x->msgParam.msgX1 + BMP180x->msgParam.msgX2;

	BMP180x->msgParam.msgB3 = (((((long)BMP180x->msgParam.msgAC1) * 4 + BMP180x->msgParam.msgX3)<<(BMP180_OSS) )+ 2) / 4;
	BMP180x->msgParam.msgX1 = (((long)BMP180x->msgParam.msgAC3) * BMP180x->msgParam.msgB6) >> 13;
	BMP180x->msgParam.msgX2 = (((long)BMP180x->msgParam.msgB1) * ((BMP180x->msgParam.msgB6 * BMP180x->msgParam.msgB6) >> 12)) >> 16;
	BMP180x->msgParam.msgX3 = ((BMP180x->msgParam.msgX1 + BMP180x->msgParam.msgX2) + 2) >> 2;
	BMP180x->msgParam.msgB4 = ((long)BMP180x->msgParam.msgAC4) * (unsigned long)(BMP180x->msgParam.msgX3 + 32768) >> 15;
	BMP180x->msgParam.msgB7 = ((unsigned long)BMP180x->msgDefaultGasPress - BMP180x->msgParam.msgB3) * (50000>> (BMP180_OSS));

	if (BMP180x->msgParam.msgB7 < 0x80000000)
	{
		BMP180x->msgGasPress = (BMP180x->msgParam.msgB7 * 2) / BMP180x->msgParam.msgB4;
	}
	else
	{
		BMP180x->msgGasPress = (BMP180x->msgParam.msgB7 / BMP180x->msgParam.msgB4) * 2;
	}

	BMP180x->msgParam.msgX1 = (BMP180x->msgGasPress >> 8)* (BMP180x->msgGasPress >> 8);
	BMP180x->msgParam.msgX1 = (((long)BMP180x->msgParam.msgX1) * 3038) >> 16;
	BMP180x->msgParam.msgX2 = (-7357 * BMP180x->msgGasPress) >> 16;
	//---计算大气压
	BMP180x->msgGasPress = BMP180x->msgGasPress + ((BMP180x->msgParam.msgX1 + BMP180x->msgParam.msgX2 + 3791) >> 4);
	//---计算海拔
	BMP180x->msgAltitude = 44330 * (1 - pow(((BMP180x->msgGasPress) / 101325.0), (1.0 / 5.255)));
	
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T BMP180_I2C_Config(BMP180_HandleType* BMP180x)
{
	UINT16_T tempReg = 0;
	UINT8_T _return = 0;
	_return = BMP180_I2C_ReadSingle(BMP180x, BMP180_REG_ADDR_AC1_H, &tempReg);
	BMP180x->msgParam.msgAC1 = tempReg;
	tempReg = 0;
	_return = BMP180_I2C_ReadSingle(BMP180x, BMP180_REG_ADDR_AC2_H, &tempReg);
	BMP180x->msgParam.msgAC2 = tempReg;
	tempReg = 0;
	_return = BMP180_I2C_ReadSingle(BMP180x, BMP180_REG_ADDR_AC3_H, &tempReg);
	BMP180x->msgParam.msgAC3 = tempReg;
	tempReg = 0;
	_return = BMP180_I2C_ReadSingle(BMP180x, BMP180_REG_ADDR_AC4_H, &tempReg);
	BMP180x->msgParam.msgAC4 = tempReg;
	tempReg = 0;
	_return = BMP180_I2C_ReadSingle(BMP180x, BMP180_REG_ADDR_AC5_H, &tempReg);
	BMP180x->msgParam.msgAC5 = tempReg;
	tempReg = 0;
	_return = BMP180_I2C_ReadSingle(BMP180x, BMP180_REG_ADDR_AC6_H, &tempReg);
	BMP180x->msgParam.msgAC6 = tempReg;
	tempReg = 0;

	_return = BMP180_I2C_ReadSingle(BMP180x, BMP180_REG_ADDR_B1_H, &tempReg);
	BMP180x->msgParam.msgB1 = tempReg;
	tempReg = 0;
	_return = BMP180_I2C_ReadSingle(BMP180x, BMP180_REG_ADDR_B2_H, &tempReg);
	BMP180x->msgParam.msgB2 = tempReg;
	tempReg = 0;

	_return = BMP180_I2C_ReadSingle(BMP180x, BMP180_REG_ADDR_MB_H, &tempReg);
	BMP180x->msgParam.msgMB = tempReg;
	tempReg = 0;
	_return = BMP180_I2C_ReadSingle(BMP180x, BMP180_REG_ADDR_MC_H, &tempReg);
	BMP180x->msgParam.msgMC = tempReg;
	tempReg = 0;
	_return = BMP180_I2C_ReadSingle(BMP180x, BMP180_REG_ADDR_MD_H, &tempReg);
	BMP180x->msgParam.msgMD = tempReg;
	tempReg = 0;
	
	return _return;
}
#include "hmc5883_cfg.h"

//===全局变量定义
HMC5883_HandleType		g_Hmc5883Device0 = { 0 };
pHMC5883_HandleType	pHmc5883Device0=&g_Hmc5883Device0;


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883_I2C_Device0_Init(HMC5883_HandleType* HMC5883x)
{
	HMC5883x->msgI2C.pMsgI2Cx = NULL;
	HMC5883x->msgI2C.msgSCL.msgPort = GPIOB;
	HMC5883x->msgI2C.msgSCL.msgBit = LL_GPIO_PIN_6;
	HMC5883x->msgI2C.msgSDA.msgPort = GPIOB;
	HMC5883x->msgI2C.msgSDA.msgBit = LL_GPIO_PIN_7;
	HMC5883x->msgI2C.msgHwMode = 0;
	HMC5883x->msgI2C.msgPluseWidth = 0;
	HMC5883x->msgI2C.pMsgDelayus = NULL;
	HMC5883x->msgI2C.msgAddr = HMC5883_WADDR;
	HMC5883x->msgI2C.msgClockSpeed = 0;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883_I2C_Device1_Init(HMC5883_HandleType* HMC5883x)
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
UINT8_T HMC5883_I2C_Device2_Init(HMC5883_HandleType* HMC5883x)
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
UINT8_T HMC5883_I2C_Init(HMC5883_HandleType* HMC5883x, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay),UINT32_T(*pFuncTimerTick)(void), UINT8_T isHWI2C)
{
	UINT8_T _return = OK_0;
	//---指定设备的初始化
	if ((HMC5883x != NULL) && (HMC5883x == HMC5883_TASK_ONE))
	{
		HMC5883_I2C_Device0_Init(HMC5883x);
	}
	else if ((HMC5883x != NULL) && (HMC5883x == HMC5883_TASK_TWO))
	{
		HMC5883_I2C_Device1_Init(HMC5883x);
	}
	else if ((HMC5883x != NULL) && (HMC5883x == HMC5883_TASK_THREE))
	{
		HMC5883_I2C_Device2_Init(HMC5883x);
	}
	else
	{
		return ERROR_1;
	}
	//---判断是硬件I2C还是软件I2C
	(isHWI2C != 0) ? (_return = I2CTask_MHW_Init(&(HMC5883x->msgI2C),pFuncDelayus, pFuncTimerTick)) : (_return = I2CTask_MSW_Init(&(HMC5883x->msgI2C), pFuncDelayus, pFuncTimerTick));
	//---ms延时函数
	HMC5883x->pMsgDelayms = ((pFuncDelayms != NULL) ? pFuncDelayms : DelayTask_ms);
	//---配置初始化
	_return = HMC5883_I2C_ConfigInit(HMC5883x);
	//---配置初始化
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：注销
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883_I2C_DeInit(HMC5883_HandleType* HMC5883x)
{
	return I2CTask_Master_DeInit(&(HMC5883x->msgI2C));
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：单字节写写寄存器
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883_SWI2C_WriteSingle(HMC5883_HandleType* HMC5883x, UINT8_T addr, UINT8_T val)
{
	UINT8_T _return = OK_0;
	//---启动IIC并发送器件地址，写数据
	_return = I2CTask_MSW_START(&(HMC5883x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_1;
		goto GoToExit;
	}
	//---发送寄存器地址,内部寄存器地址
	I2CTask_MSW_SendByte(&(HMC5883x->msgI2C), addr);
	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(HMC5883x->msgI2C));
	if (_return != OK_0)
	{
		//---发送寄存器地址错误
		_return = ERROR_2;
		goto GoToExit;
	}
	//---发送数据，内部寄存器数据
	I2CTask_MSW_SendByte(&(HMC5883x->msgI2C), val);
	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(HMC5883x->msgI2C));
	//---退出操作入口
GoToExit:
	//---发送停止信号
	I2CTask_MSW_STOP(&(HMC5883x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883_HWI2C_WriteSingle(HMC5883_HandleType* HMC5883x, UINT8_T addr, UINT8_T val)
{
	UINT8_T _return = OK_0;
	//---启动IIC并发送器件地址，写数据
	_return = I2CTask_MHW_PollMode_START(&(HMC5883x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_1;
		goto GoToExit;
	}
	//---发送寄存器地址,内部寄存器地址
	_return = I2CTask_MHW_PollMode_SendByte(&(HMC5883x->msgI2C), addr, 0);
	if (_return != OK_0)
	{
		//---发送寄存器地址错误
		_return = ERROR_2;
		goto GoToExit;
	}
	//---发送数据，内部寄存器数据
	_return = I2CTask_MHW_PollMode_SendByte(&(HMC5883x->msgI2C), val, 1);
	if (_return != OK_0)
	{
		//---发送数据错误
		_return = ERROR_3;
		goto GoToExit;
	}
	//---退出操作入口
GoToExit:
	//---发送停止信号
	I2CTask_MHW_PollMode_STOP(&(HMC5883x->msgI2C));
	return _return;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883_I2C_WriteSingle(HMC5883_HandleType* HMC5883x, UINT8_T addr, UINT8_T val)
{
	if (HMC5883x->msgI2C.msgHwMode != 0)
	{
		I2CTask_MHW_CheckClock(&(HMC5883x->msgI2C));
		return HMC5883_HWI2C_WriteSingle(HMC5883x, addr, val);
	}
	else
	{
		return HMC5883_SWI2C_WriteSingle(HMC5883x, addr, val);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883_SWI2C_ReadSingle(HMC5883_HandleType* HMC5883x, UINT8_T addr, UINT8_T* pVal)
{
	UINT8_T _return = OK_0;
	//---启动IIC并发送器件地址，写数据
	_return = I2CTask_MSW_START(&(HMC5883x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_1;
		goto GoToExit;
	}
	//---发送寄存器地址,存储单元的地址
	I2CTask_MSW_SendByte(&(HMC5883x->msgI2C), addr);
	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(HMC5883x->msgI2C));
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_2;
		goto GoToExit;
	}
	//---启动IIC并发送器件地址，读数据
	_return = I2CTask_MSW_START(&(HMC5883x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---启动读数据失败
		_return = ERROR_3;
		goto GoToExit;
	}
	//---读取数据
	*pVal = I2CTask_MSW_ReadByte(&(HMC5883x->msgI2C));
	//---发送不应答信号
	_return = I2CTask_MSW_SendACK(&(HMC5883x->msgI2C), 1);
	//---退出操作入口
GoToExit:
	//---发送停止信号
	I2CTask_MSW_STOP(&(HMC5883x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883_HWI2C_ReadSingle(HMC5883_HandleType* HMC5883x, UINT8_T addr, UINT8_T* pVal)
{
	UINT8_T _return = OK_0;
	//---启动IIC并发送器件地址，写数据
	_return = I2CTask_MHW_PollMode_START(&(HMC5883x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_1;
		goto GoToExit;
	}
	//---发送寄存器地址,存储单元的地址
	_return = I2CTask_MHW_PollMode_SendByte(&(HMC5883x->msgI2C), addr, 0);
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_2;
		goto GoToExit;
	}
	//---启动IIC并发送器件地址，读数据
	_return = I2CTask_MHW_PollMode_START(&(HMC5883x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---启动读数据失败
		_return = ERROR_3;
		goto GoToExit;
	}
	//---发送不应答信号
	_return = I2CTask_MHW_SendACK(&(HMC5883x->msgI2C), 1);
	//---读取数据
	*pVal = I2CTask_MHW_PollMode_ReadByte(&(HMC5883x->msgI2C));
	//---退出操作入口
GoToExit:
	//---发送停止信号
	I2CTask_MHW_PollMode_STOP(&(HMC5883x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883_I2C_ReadSingle(HMC5883_HandleType* HMC5883x, UINT8_T addr, UINT8_T* pVal)
{
	if (HMC5883x->msgI2C.msgHwMode!=0)
	{
		I2CTask_MHW_CheckClock(&(HMC5883x->msgI2C));
		//---硬件I2C
		return HMC5883_HWI2C_ReadSingle(HMC5883x, addr, pVal);
	}
	else
	{
		return HMC5883_SWI2C_ReadSingle(HMC5883x, addr, pVal);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883_SWI2C_ReadBulk(HMC5883_HandleType* HMC5883x, UINT8_T addr, UINT8_T *pVal,UINT8_T length)
{
	//UINT8_T readTemp[6] = { 0 };
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---启动IIC并发送器件地址，写数据
	_return = I2CTask_MSW_START(&(HMC5883x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_1;
		goto GoToExit;
	}
	//---发送寄存器地址,高地址
	I2CTask_MSW_SendByte(&(HMC5883x->msgI2C), addr);
	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(HMC5883x->msgI2C));
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_2;
		goto GoToExit;
	}
	//---启动IIC并发送器件地址，读数据
	_return = I2CTask_MSW_START(&(HMC5883x->msgI2C), 0);
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
		pVal[i] = I2CTask_MSW_ReadByte(&(HMC5883x->msgI2C));
		//---发送应答信号
		I2CTask_MSW_SendACK(&(HMC5883x->msgI2C), (i == (length - 1)) ? 1 : 0);
	}
	_return = OK_0;
GoToExit:
	//---发送停止信号
	I2CTask_MSW_STOP(&(HMC5883x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883_HWI2C_ReadBulk(HMC5883_HandleType* HMC5883x, UINT8_T addr, UINT8_T* pVal, UINT8_T length)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---启动IIC并发送器件地址，写数据
	_return = I2CTask_MHW_PollMode_START(&(HMC5883x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_1;
		goto GoToExit;
	}
	//---发送寄存器地址,高地址
	_return = I2CTask_MHW_PollMode_SendByte(&(HMC5883x->msgI2C), addr, 0);
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_2;
		goto GoToExit;
	}
	//---启动IIC并发送器件地址，读数据
	_return = I2CTask_MHW_PollMode_START(&(HMC5883x->msgI2C), 0);
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
		I2CTask_MHW_SendACK(&(HMC5883x->msgI2C), (i == (length - 1)) ? 1 : 0);
		//---读取数据
		pVal[i] = I2CTask_MHW_PollMode_ReadByte(&(HMC5883x->msgI2C));
	}
	_return = OK_0;
GoToExit:
	//---发送停止信号
	I2CTask_MHW_PollMode_STOP(&(HMC5883x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883_I2C_ReadBulk(HMC5883_HandleType* HMC5883x,UINT8_T addr, UINT8_T* pVal, UINT8_T length)
{
	if (HMC5883x->msgI2C.msgHwMode != 0)
	{
		I2CTask_MHW_CheckClock(&(HMC5883x->msgI2C));
		//---硬件I2C
		return  HMC5883_HWI2C_ReadBulk(HMC5883x,addr,pVal, length);
	}
	else
	{
		return HMC5883_SWI2C_ReadBulk(HMC5883x,addr, pVal, length);
	}	
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883_I2C_ConfigInit(HMC5883_HandleType* HMC5883x)
{
	return HMC5883_I2C_WriteSingle(HMC5883x,0x02, 0x00);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取磁场数据
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC5883_I2C_ReadRawData(HMC5883_HandleType* HMC5883x)
{
	UINT8_T readTemp[6] = { 0 };
	//---读取值
	UINT8_T _return = HMC5883_I2C_ReadBulk(HMC5883x, HMC5883_DXMSB_REG,readTemp,6);
	//---数据计算
	if (_return == OK_0)
	{
		//---计算X轴
		HMC5883x->msgX = readTemp[0];
		HMC5883x->msgX = (HMC5883x->msgX << 8) + readTemp[1];
		//---将二进制的补码转换为实际值
		if ((HMC5883x->msgX & 0x8000) != 0)
		{
			HMC5883x->msgX = -(0xFFFF - HMC5883x->msgX + 1);
		}
		//---计算Z轴
		HMC5883x->msgZ = readTemp[2];
		HMC5883x->msgZ = (HMC5883x->msgZ << 8) + readTemp[3];
		//---将二进制的补码转换为实际值
		if ((HMC5883x->msgZ & 0x8000) != 0)
		{
			HMC5883x->msgZ = -(0xFFFF - HMC5883x->msgZ + 1);
		}
		//---计算Y轴
		HMC5883x->msgY = readTemp[4];
		HMC5883x->msgY = (HMC5883x->msgY << 8) + readTemp[5];
		//---将二进制的补码转换为实际值
		if ((HMC5883x->msgY & 0x8000) != 0)
		{
			HMC5883x->msgY = -(0xFFFF - HMC5883x->msgY + 1);
		}
		//---计算角度
		HMC5883x->msgAngle = atan2((double)(HMC5883x->msgY - HMC5883x->msgOffsetY), (double)(HMC5883x->msgX - HMC5883x->msgOffsetX)) * (180 / 3.14159265) + 180;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能： 校准计算，均值校准
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void HMC5883_I2C_CalibrateMag(HMC5883_HandleType* HMC5883x)
{
	int x=0, y=0, z=0; //triple axis data
	int xMax=0, xMin=0, yMax=0, yMin=0, zMax=0, zMin=0;
	xMax = xMin = x;
	yMax = yMin = y;
	zMax = zMin = z;
	HMC5883x->msgOffsetX = 0;
	HMC5883x->msgOffsetY = 0;
	HMC5883x->msgOffsetZ = 0;
	//---读取值
	HMC5883_I2C_ReadRawData(HMC5883x);
	//---准备校准
	for (int i = 0; i < 200; i++)
	{
		//---读取值
		HMC5883_I2C_ReadRawData(HMC5883x);
		if (x > xMax)
		{
			xMax = x;
		}
		if (x < xMin)
		{
			xMin = x;
		}
		if (y > yMax)
		{
			yMax = y;
		}
		if (y < yMin)
		{
			yMin = y;
		}
		if (z > zMax)
		{
			zMax = z;
		}
		if (z < zMin)
		{
			zMin = z;
		}
		HMC5883x->pMsgDelayms(100);
	}
	//---计算X轴偏差
	if (ABS(xMax - xMin) > CALIB_THRESHOLD)
	{
		HMC5883x->msgOffsetX = (xMax + xMin) / 2;
	}
	//---计算Y轴偏差
	if (ABS(yMax - yMin) > CALIB_THRESHOLD)
	{
		HMC5883x->msgOffsetY = (yMax + yMin) / 2;
	}
	//---计算Z轴偏差
	if (ABS(zMax - zMin) > CALIB_THRESHOLD)
	{
		HMC5883x->msgOffsetZ = (zMax + zMin) / 2;
	}
}
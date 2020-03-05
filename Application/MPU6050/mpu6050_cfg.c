#include "mpu6050_cfg.h"

//===全局变量定义
MPU6050_HandleType			g_Mpu6050Device0 = {0};
pMPU6050_HandleType		pMpu6050Device0=&g_Mpu6050Device0;

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：传感器1的初始化
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_Device0_Init(MPU6050_HandleType* MPU6050x)
{
	MPU6050x->msgI2C.pMsgI2Cx = NULL;
	MPU6050x->msgI2C.msgSCL.msgPort = GPIOB;
	MPU6050x->msgI2C.msgSCL.msgBit = LL_GPIO_PIN_8;
	MPU6050x->msgI2C.msgSDA.msgPort = GPIOB;
	MPU6050x->msgI2C.msgSDA.msgBit = LL_GPIO_PIN_9;
	MPU6050x->msgI2C.msgHwMode = 0;
	MPU6050x->msgI2C.msgPluseWidth = 0;
	MPU6050x->msgI2C.pMsgDelayus = NULL;
	MPU6050x->msgI2C.msgAddr = MPU6050_WADDR;
	MPU6050x->msgI2C.msgClockSpeed = 200000;
	//---GPIO复用模式
	MPU6050x->msgI2C.msgGPIOAlternate = LL_GPIO_AF_4;
	//---硬件I2C是I2C1
	MPU6050x->msgI2C.pMsgI2Cx = I2C1;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：传感器2的初始化
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_Device1_Init(MPU6050_HandleType* MPU6050x)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：传感器3的初始化
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_Device2_Init(MPU6050_HandleType* MPU6050x)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：初始化函数
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_Init(MPU6050_HandleType* MPU6050x, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHWI2C)
{
	UINT8_T _return = OK_0;
	//---指定设备的初始化
	if ((MPU6050x != NULL) && (MPU6050x == MPU6050_TASK_ONE))
	{
		MPU6050_I2C_Device0_Init(MPU6050x);
	}
	else if ((MPU6050x != NULL) && (MPU6050x == MPU6050_TASK_TWO))
	{
		MPU6050_I2C_Device1_Init(MPU6050x);
	}
	else if ((MPU6050x != NULL) && (MPU6050x == MPU6050_TASK_THREE))
	{
		MPU6050_I2C_Device2_Init(MPU6050x);
	}
	else
	{
		return ERROR_1;
	}
	//---判断是硬件I2C还是软件I2C
	(isHWI2C != 0) ? (_return = I2CTask_MHW_Init(&(MPU6050x->msgI2C), pFuncDelayus,pFuncTimerTick)) : (_return = I2CTask_MSW_Init(&(MPU6050x->msgI2C), pFuncDelayus, pFuncTimerTick));
	//---ms延时函数
	MPU6050x->pMsgDelayms = ((pFuncDelayms!=NULL)? pFuncDelayms: DelayTask_ms);
	//---基本配置
	_return= MPU6050_I2C_ConfigInit(MPU6050x);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：软件模拟I2C，单字节写写寄存器
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_SWI2C_WriteSingle(MPU6050_HandleType* MPU6050x, UINT8_T addr, UINT8_T val)
{
	UINT8_T _return = OK_0;
	//---启动IIC并发送器件地址，写数据
	_return = I2CTask_MSW_START(&(MPU6050x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_1;
		goto GoToExit;
	}
	//---发送寄存器地址,内部寄存器地址
	I2CTask_MSW_SendByte(&(MPU6050x->msgI2C), addr);
	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(MPU6050x->msgI2C));
	if (_return != OK_0)
	{
		//---发送寄存器地址错误
		_return = ERROR_2;
		goto GoToExit;
	}
	//---发送数据，内部寄存器数据
	I2CTask_MSW_SendByte(&(MPU6050x->msgI2C), val);
	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(MPU6050x->msgI2C));
	//---退出操作入口
GoToExit:
	//---发送停止信号
	I2CTask_MSW_STOP(&(MPU6050x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：硬件I2C，单字节写写寄存器
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_HWI2C_WriteSingle(MPU6050_HandleType* MPU6050x, UINT8_T addr, UINT8_T val)
{
	UINT8_T _return = OK_0;
	//---启动IIC并发送器件地址，写数据
	_return = I2CTask_MHW_PollMode_START(&(MPU6050x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_1;
		goto GoToExit;
	}
	//---发送寄存器地址,存储单元的地址
	_return = I2CTask_MHW_PollMode_SendByte(&(MPU6050x->msgI2C), addr,0);
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_2;
		goto GoToExit;
	}
	//---发送数据，内部寄存器数据
	_return = I2CTask_MHW_PollMode_SendByte(&(MPU6050x->msgI2C), val,1);
	//---退出操作入口
GoToExit:
	//---发送停止信号
	I2CTask_MHW_PollMode_STOP(&(MPU6050x->msgI2C));
	return _return;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：I2C，单字节写写寄存器
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_WriteSingle(MPU6050_HandleType* MPU6050x, UINT8_T addr, UINT8_T val)
{
	if (MPU6050x->msgI2C.msgHwMode != 0)
	{
		I2CTask_MHW_CheckClock(&(MPU6050x->msgI2C));
		return MPU6050_HWI2C_WriteSingle(MPU6050x, addr, val);
	}
	else
	{
		return MPU6050_SWI2C_WriteSingle(MPU6050x, addr, val);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：软件模拟I2C，多字节写寄存器
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_SWI2C_WriteBulk(MPU6050_HandleType* MPU6050x, UINT8_T addr, UINT8_T *pVal,UINT8_T length)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---启动IIC并发送器件地址，写数据
	_return = I2CTask_MSW_START(&(MPU6050x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_1;
		goto GoToExit;
	}
	//---发送寄存器地址,内部寄存器地址
	I2CTask_MSW_SendByte(&(MPU6050x->msgI2C), addr);
	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(MPU6050x->msgI2C));
	if (_return != OK_0)
	{
		//---发送寄存器地址错误
		_return = ERROR_2;
		goto GoToExit;
	}
	//---发送多组数据，连续写
	for (i=0;i<length;i++)
	{
		//---发送数据，内部寄存器数据
		I2CTask_MSW_SendByte(&(MPU6050x->msgI2C), pVal[i]);
		//---读取ACK
		_return = I2CTask_MSW_ReadACK(&(MPU6050x->msgI2C));
		if (_return != OK_0)
		{
			//---发送数据错误
			_return = (ERROR_3+i);
			goto GoToExit;
		}
	}
	//---退出操作入口
GoToExit:
	//---发送停止信号
	I2CTask_MSW_STOP(&(MPU6050x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：硬件I2C，多字节写寄存器
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_HWI2C_WriteBulk(MPU6050_HandleType* MPU6050x, UINT8_T addr, UINT8_T *pVal,UINT8_T length)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---启动IIC并发送器件地址，写数据
	_return = I2CTask_MHW_PollMode_START(&(MPU6050x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_1;
		goto GoToExit;
	}
	//---发送寄存器地址,内部寄存器地址
	I2CTask_MSW_SendByte(&(MPU6050x->msgI2C), addr);
	//---发送寄存器地址,存储单元的地址
	_return = I2CTask_MHW_PollMode_SendByte(&(MPU6050x->msgI2C), addr, 0);
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_2;
		goto GoToExit;
	}
	//---发送多组数据，连续写
	for (i = 0; i < length; i++)
	{
		//---发送数据，内部寄存器数据
		_return= I2CTask_MHW_PollMode_SendByte(&(MPU6050x->msgI2C), pVal[i], ((i==(length-1))?1:0));
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
	I2CTask_MHW_PollMode_STOP(&(MPU6050x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：I2C，多字节写寄存器
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_WriteBulk(MPU6050_HandleType* MPU6050x, UINT8_T addr, UINT8_T *pVal,UINT8_T length)
{
	if (MPU6050x->msgI2C.msgHwMode != 0)
	{
		I2CTask_MHW_CheckClock(&(MPU6050x->msgI2C));
		//---硬件I2C
		return MPU6050_HWI2C_WriteBulk(MPU6050x, addr, pVal,length);
	}
	else
	{
		return MPU6050_SWI2C_WriteBulk(MPU6050x,  addr, pVal,length);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：软件模拟I2C，单字节读寄存器
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_SWI2C_ReadSingle(MPU6050_HandleType* MPU6050x, UINT8_T addr, UINT8_T* pVal)
{
	UINT8_T _return = OK_0;
	//---启动IIC并发送器件地址，写数据
	_return = I2CTask_MSW_START(&(MPU6050x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_1;
		goto GoToExit;
	}
	//---发送寄存器地址,存储单元的地址
	I2CTask_MSW_SendByte(&(MPU6050x->msgI2C), addr);
	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(MPU6050x->msgI2C));
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_2;
		goto GoToExit;
	}
	//---启动IIC并发送器件地址，读数据
	_return = I2CTask_MSW_START(&(MPU6050x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---启动读数据失败
		_return = ERROR_3;
		goto GoToExit;
	}
	//---读取数据
	*pVal = I2CTask_MSW_ReadByte(&(MPU6050x->msgI2C));
	//---发送不应答信号
	_return = I2CTask_MSW_SendACK(&(MPU6050x->msgI2C), 1);
	//---退出入口
GoToExit:
	//---发送停止信号
	I2CTask_MSW_STOP(&(MPU6050x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：硬件I2C，单字节读寄存器
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_HWI2C_ReadSingle(MPU6050_HandleType* MPU6050x, UINT8_T addr, UINT8_T* pVal)
{
	UINT8_T _return = OK_0;
	//---启动IIC并发送器件地址，写数据
	_return = I2CTask_MHW_PollMode_START(&(MPU6050x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_1;
		goto GoToExit;
	}
	//---发送寄存器地址,存储单元的地址
	_return = I2CTask_MHW_PollMode_SendByte(&(MPU6050x->msgI2C), addr,0);
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_2;
		goto GoToExit;
	}
	//---启动IIC并发送器件地址，读数据
	_return = I2CTask_MHW_PollMode_START(&(MPU6050x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---启动读数据失败
		_return = ERROR_3;
		goto GoToExit;
	}
	//---发送不应答信号
	_return = I2CTask_MHW_SendACK(&(MPU6050x->msgI2C), 1);
	//---读取数据
	*pVal = I2CTask_MHW_PollMode_ReadByte(&(MPU6050x->msgI2C));
	//---退出入口
GoToExit:
	//---发送停止信号
	I2CTask_MHW_PollMode_STOP(&(MPU6050x->msgI2C));
	return _return;	
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：I2C，单字节读寄存器
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_ReadSingle(MPU6050_HandleType* MPU6050x, UINT8_T addr, UINT8_T* pVal)
{
	if (MPU6050x->msgI2C.msgHwMode != 0)
	{
		I2CTask_MHW_CheckClock(&(MPU6050x->msgI2C));
		return MPU6050_HWI2C_ReadSingle(MPU6050x, addr, pVal);
	}
	else
	{
		return MPU6050_SWI2C_ReadSingle(MPU6050x, addr, pVal);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：软件模拟I2C，多字节读寄存器
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_SWI2C_ReadBulk(MPU6050_HandleType* MPU6050x,UINT8_T addr, UINT8_T* pVal, UINT8_T length)
{
	//UINT8_T readTemp[6] = { 0 };
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---启动IIC并发送器件地址，写数据
	_return = I2CTask_MSW_START(&(MPU6050x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_1;
		goto GoToExit;
	}
	//---发送寄存器地址,高地址
	I2CTask_MSW_SendByte(&(MPU6050x->msgI2C), addr);
	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(MPU6050x->msgI2C));
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_2;
		goto GoToExit;
	}
	//---启动IIC并发送器件地址，读数据
	_return = I2CTask_MSW_START(&(MPU6050x->msgI2C), 0);
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
		pVal[i] = I2CTask_MSW_ReadByte(&(MPU6050x->msgI2C));
		//---发送应答信号
		I2CTask_MSW_SendACK(&(MPU6050x->msgI2C), (i == (length - 1)) ? 1 : 0);
	}
	_return = OK_0;
GoToExit:
	//---发送停止信号
	I2CTask_MSW_STOP(&(MPU6050x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：硬件I2C，多字节读寄存器
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_HWI2C_ReadBulk(MPU6050_HandleType* MPU6050x, UINT8_T addr,UINT8_T* pVal, UINT8_T length)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---启动IIC并发送器件地址，写数据
	_return = I2CTask_MHW_PollMode_START(&(MPU6050x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_1;
		goto GoToExit;
	}
	//---发送寄存器地址,存储单元的地址
	_return = I2CTask_MHW_PollMode_SendByte(&(MPU6050x->msgI2C), addr,0);
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_2;
		goto GoToExit;
	}
	//---启动IIC并发送器件地址，读数据
	_return = I2CTask_MHW_PollMode_START(&(MPU6050x->msgI2C), 0);
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
		I2CTask_MHW_SendACK(&(MPU6050x->msgI2C), (i == (length - 1)) ? 1 : 0);
		//---读取数据
		pVal[i] = I2CTask_MHW_PollMode_ReadByte(&(MPU6050x->msgI2C));
	}
	_return = OK_0;
	//---退出入口
GoToExit:
	//---发送停止信号
	I2CTask_MHW_PollMode_STOP(&(MPU6050x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：I2C，多字节读寄存器
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_ReadBulk(MPU6050_HandleType* MPU6050x,UINT8_T addr, UINT8_T* pVal, UINT8_T length)
{
	if (MPU6050x->msgI2C.msgHwMode == 1)
	{
		I2CTask_MHW_CheckClock(&(MPU6050x->msgI2C));
		return  MPU6050_HWI2C_ReadBulk(MPU6050x,addr, pVal, length);
	}
	else
	{
		return MPU6050_SWI2C_ReadBulk(MPU6050x, addr, pVal, length);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取芯片的ID信息
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_ReadChipID(MPU6050_HandleType* MPU6050x, UINT8_T *pChipID)
{
	//UINT8_T _return = MPU6050_I2C_ReadSingle(MPU6050x, MPU6050_REG_ADDR_WHO_AM_I, pChipID);
	////---校验读取结果
	//if (_return!=OK_0)
	//{
	//	_return = ERROR_1;
	//}
	//else
	//{
	//	if (*pChipID!=0x68)
	//	{
	//		_return = ERROR_2;
	//	}
	//}
	//return _return;
	//*pChipID=I2C_HW_Read(MPU6050x->msgI2C.msgAddr, MPU6050_REG_ADDR_WHO_AM_I);
	return  MPU6050_I2C_ReadSingle(MPU6050x, MPU6050_REG_ADDR_WHO_AM_I, pChipID);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取加速度值
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_ReadAccel(MPU6050_HandleType* MPU6050x)
{
	UINT8_T _return = OK_0;
	UINT8_T tempAccel[6] = { 0 };
	//---读取测量值
	_return = MPU6050_I2C_ReadBulk(MPU6050x, MPU6050_REG_ADDR_ACCEL_XOUT_H, tempAccel, 6);
	//---校验读取结果
	if (_return==OK_0)
	{
		MPU6050x->msgAccel.xAccel = tempAccel[0];
		MPU6050x->msgAccel.xAccel = (MPU6050x->msgAccel.xAccel << 8) + tempAccel[1];

		MPU6050x->msgAccel.yAccel = tempAccel[2];
		MPU6050x->msgAccel.yAccel = (MPU6050x->msgAccel.yAccel << 8) + tempAccel[3];

		MPU6050x->msgAccel.zAccel = tempAccel[4];
		MPU6050x->msgAccel.zAccel = (MPU6050x->msgAccel.zAccel << 8) + tempAccel[5];
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取温度值
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_ReadTemp(MPU6050_HandleType* MPU6050x)
{
	UINT8_T _return = OK_0;
	UINT8_T tempTemp[2] = { 0 };
	//---读取测量值
	_return = MPU6050_I2C_ReadBulk(MPU6050x, MPU6050_REG_ADDR_TEMP_OUT_H, tempTemp, 2);
	//---校验读取结果
	if (_return == OK_0)
	{
		float mpuTemp = tempTemp[0];
		mpuTemp =((UINT16_T)mpuTemp <<8)+ tempTemp[1];
		mpuTemp = mpuTemp / 340.0 + 36.53;
		MPU6050x->msgTemp = (INT32_T)(mpuTemp * 100.0);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取陀螺仪值
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_ReadGyro(MPU6050_HandleType* MPU6050x)
{
	UINT8_T _return = OK_0;
	UINT8_T tempGyro[6] = { 0 };
	//---读取测量值
	_return = MPU6050_I2C_ReadBulk(MPU6050x, MPU6050_REG_ADDR_GYRO_XOUT_H, tempGyro, 6);
	//---校验读取结果
	if (_return == OK_0)
	{
		MPU6050x->msgGyro.xGyro = tempGyro[0];
		MPU6050x->msgGyro.xGyro = (MPU6050x->msgGyro.xGyro << 8) + tempGyro[1];

		MPU6050x->msgGyro.yGyro = tempGyro[2];
		MPU6050x->msgGyro.yGyro = (MPU6050x->msgGyro.yGyro << 8) + tempGyro[3];

		MPU6050x->msgGyro.zGyro = tempGyro[4];
		MPU6050x->msgGyro.zGyro = (MPU6050x->msgGyro.zGyro << 8) + tempGyro[5];
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取加速度，温度，陀螺仪的值
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_ReadAccelTempGyro(MPU6050_HandleType* MPU6050x)
{
	UINT8_T _return = OK_0;
	UINT8_T tempVal[14] = { 0 };
	MPU6050x->msgAccel.xAccel = 0;
	MPU6050x->msgAccel.yAccel = 0;
	MPU6050x->msgAccel.zAccel = 0;
	MPU6050x->msgTemp = 0;
	MPU6050x->msgGyro.xGyro = 0;
	MPU6050x->msgGyro.yGyro = 0;
	MPU6050x->msgGyro.zGyro = 0;
	//---读取测量值
	_return = MPU6050_I2C_ReadBulk(MPU6050x, MPU6050_REG_ADDR_ACCEL_XOUT_H, tempVal, 14);
	//---校验读取结果
	if (_return == OK_0)
	{
		//---计算加速度
		MPU6050x->msgAccel.xAccel = tempVal[0];
		MPU6050x->msgAccel.xAccel = (MPU6050x->msgAccel.xAccel << 8) + tempVal[1];

		MPU6050x->msgAccel.yAccel = tempVal[2];
		MPU6050x->msgAccel.yAccel = (MPU6050x->msgAccel.yAccel << 8) + tempVal[3];

		MPU6050x->msgAccel.zAccel = tempVal[4];
		MPU6050x->msgAccel.zAccel = (MPU6050x->msgAccel.zAccel << 8) + tempVal[5];

		//---计算温度
		float mpuTemp = tempVal[6];
		mpuTemp = ((UINT16_T)mpuTemp << 8) + tempVal[7];
		mpuTemp = mpuTemp / 340.0 + 36.53;
		MPU6050x->msgTemp = (INT32_T)(mpuTemp * 100.0);

		//---计算陀螺仪
		MPU6050x->msgGyro.xGyro = tempVal[8];
		MPU6050x->msgGyro.xGyro = (MPU6050x->msgGyro.xGyro << 8) + tempVal[9];

		MPU6050x->msgGyro.yGyro = tempVal[10];
		MPU6050x->msgGyro.yGyro = (MPU6050x->msgGyro.yGyro << 8) + tempVal[11];

		MPU6050x->msgGyro.zGyro = tempVal[12];
		MPU6050x->msgGyro.zGyro = (MPU6050x->msgGyro.zGyro << 8) + tempVal[13];
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置时钟采样率
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_WriteSMPRTDIV(MPU6050_HandleType* MPU6050x, UINT8_T smprtDiv)
{
	return MPU6050_I2C_WriteSingle(MPU6050x, MPU6050_REG_ADDR_SMPLRT_DIV, smprtDiv);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取时钟采样率
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_ReadSMPRTDIV(MPU6050_HandleType* MPU6050x, UINT8_T *pSMPRTDIV)
{
	return MPU6050_I2C_ReadSingle(MPU6050x, MPU6050_REG_ADDR_SMPLRT_DIV, pSMPRTDIV);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：配置数字滤波器
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_WriteLPF(MPU6050_HandleType* MPU6050x, UINT8_T lpf)
{
	UINT8_T tempCFG = 0;
	//---读取配置信息
	UINT8_T _return = MPU6050_I2C_ReadSingle(MPU6050x, MPU6050_REG_ADDR_CONFIG, &tempCFG);
	if (_return == OK_0)
	{
		tempCFG &= ~lpf;
		tempCFG |= lpf;
		//---将配置信息写入设备
		_return = MPU6050_I2C_WriteSingle(MPU6050x, MPU6050_REG_ADDR_CONFIG, tempCFG);
	}
	return _return;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：复位设备
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_Reset(MPU6050_HandleType* MPU6050x)
{
	return MPU6050_I2C_WriteSingle(MPU6050x, MPU6050_REG_ADDR_PWR_MGMT_1, 0x80);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取中断状态
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_ReadINTSTATUS(MPU6050_HandleType* MPU6050x, UINT8_T *pINTSTATUS)
{
	return MPU6050_I2C_ReadSingle(MPU6050x, MPU6050_REG_ADDR_INT_STATUS, pINTSTATUS);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取中断使能为
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_ReadINTENABLE(MPU6050_HandleType* MPU6050x, UINT8_T* pINTENABLE)
{
	return MPU6050_I2C_ReadSingle(MPU6050x, MPU6050_REG_ADDR_INT_ENABLE, pINTENABLE);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：写中断使能为
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_WriteINTENABLE(MPU6050_HandleType* MPU6050x, UINT8_T intEnable)
{
	UINT8_T tempCFG = 0;
	//---读取配置信息
	UINT8_T _return = MPU6050_I2C_ReadSingle(MPU6050x, MPU6050_REG_ADDR_INT_ENABLE, &tempCFG);
	if (_return == OK_0)
	{
		tempCFG &= ~intEnable;
		tempCFG |= intEnable;
		//---将配置信息写入设备
		_return = MPU6050_I2C_WriteSingle(MPU6050x, MPU6050_REG_ADDR_INT_ENABLE, tempCFG);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取中断引脚位
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_ReadINTPINCFG(MPU6050_HandleType* MPU6050x, UINT8_T* pINTPINCFG)
{
	return MPU6050_I2C_ReadSingle(MPU6050x, MPU6050_REG_ADDR_INT_PIN_CFG, pINTPINCFG);;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：写中断引脚位
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_WriteINTPINCFG(MPU6050_HandleType* MPU6050x, UINT8_T intPinCfg)
{
	UINT8_T tempCFG = 0;
	//---读取配置信息
	UINT8_T _return = MPU6050_I2C_ReadSingle(MPU6050x, MPU6050_REG_ADDR_INT_PIN_CFG, &tempCFG);
	if (_return == OK_0)
	{
		tempCFG &= ~intPinCfg;
		tempCFG |= intPinCfg;
		//---将配置信息写入设备
		_return = MPU6050_I2C_WriteSingle(MPU6050x, MPU6050_REG_ADDR_INT_PIN_CFG, tempCFG);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取陀螺仪的量程
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_ReadGyroRange(MPU6050_HandleType* MPU6050x, UINT8_T *pGyroRange)
{
	UINT8_T _return= MPU6050_I2C_ReadSingle(MPU6050x, MPU6050_REG_ADDR_GYRO_CONFIG, pGyroRange);
	*pGyroRange &= MPU6050_GYRO_FS_MASK;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：配置陀螺仪的量程
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_WriteGyroRange(MPU6050_HandleType* MPU6050x, UINT8_T gyroRange)
{
	UINT8_T tempCFG = 0;
	UINT8_T _return = MPU6050_I2C_ReadSingle(MPU6050x, MPU6050_REG_ADDR_GYRO_CONFIG, &tempCFG);
	if (_return == OK_0)
	{
		tempCFG &= ~gyroRange;
		tempCFG |= gyroRange;
		//---将配置信息写入设备
		_return = MPU6050_I2C_WriteSingle(MPU6050x, MPU6050_REG_ADDR_GYRO_CONFIG, tempCFG);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取加速度的量程
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_ReadAccelRange(MPU6050_HandleType* MPU6050x, UINT8_T* pAccelRange)
{
	UINT8_T _return = MPU6050_I2C_ReadSingle(MPU6050x, MPU6050_REG_ADDR_ACCEL_CONFIG, pAccelRange);
	*pAccelRange &= MPU6050_ACCEL_FS_MASK;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：配置陀螺仪的量程
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_WriteAccelRange(MPU6050_HandleType* MPU6050x, UINT8_T accelRange)
{
	UINT8_T tempCFG = 0;
	UINT8_T _return = MPU6050_I2C_ReadSingle(MPU6050x, MPU6050_REG_ADDR_ACCEL_CONFIG, &tempCFG);
	if (_return == OK_0)
	{
		tempCFG &= ~accelRange;
		tempCFG |= accelRange;
		//---将配置信息写入设备
		_return = MPU6050_I2C_WriteSingle(MPU6050x, MPU6050_REG_ADDR_ACCEL_CONFIG, tempCFG);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：默认配置
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T MPU6050_I2C_ConfigInit(MPU6050_HandleType* MPU6050x)
{
	UINT8_T tempVal = 0;
	//---读取ID信息
	UINT8_T _return = MPU6050_I2C_ReadChipID(MPU6050x, &tempVal);
	if ((_return!=OK_0)||(tempVal!=0x68))
	{
		return ERROR_1;
	}
	//---唤醒设备
	_return = MPU6050_I2C_WriteSingle(MPU6050x, MPU6050_REG_ADDR_PWR_MGMT_1, 0x00);
	//---配置采样时钟,1K/200分频，50Hz
	_return = MPU6050_I2C_WriteSMPRTDIV(MPU6050x, MPU6050_SMPRT_DIV_20);
	//---配置数字滤波器,带宽20Hz
	_return = MPU6050_I2C_WriteLPF(MPU6050x, MPU6050_DLPF_BW_20);
	//---配置加速度量程，+/-8G
	_return = MPU6050_I2C_WriteAccelRange(MPU6050x, MPU6050_ACCEL_FS_8);
	//---配置陀螺仪量程，+/-2000G
	_return = MPU6050_I2C_WriteGyroRange(MPU6050x, MPU6050_GYRO_FS_2000);
	//---引脚中断配置
	_return = MPU6050_I2C_WriteSingle(MPU6050x, MPU6050_REG_ADDR_INT_PIN_CFG, 0x80);//MPU6050_INT_LEVEL_LOW| MPU6050_INTDRV_PUSHPULL| MPU6050_INT_LATCH_WAITCLEAR);
	MPU6050_I2C_WriteSingle(MPU6050x, MPU6050_REG_ADDR_INT_ENABLE, 0x01);                    // 使用“数据准备好”中断。
	return _return;
}

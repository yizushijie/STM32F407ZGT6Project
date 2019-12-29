#include "aht10_cfg.h"

//===全局变量定义
AHT10_HandlerType		g_Aht10Device0;
pAHT10_HandlerType		pAht10Device0;

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AHT10_I2C_Device0_Init(AHT10_HandlerType* AHT10x)
{
	AHT10x->msgI2C.msgI2Cx = NULL;
	AHT10x->msgI2C.msgSCL.msgGPIOPort = GPIOB;
	AHT10x->msgI2C.msgSCL.msgGPIOBit = LL_GPIO_PIN_6;
	AHT10x->msgI2C.msgSDA.msgGPIOPort = GPIOB;
	AHT10x->msgI2C.msgSDA.msgGPIOBit = LL_GPIO_PIN_7;
	AHT10x->msgI2C.msgModelIsHW = 0;
	AHT10x->msgI2C.msgPluseWidth = 0;
	AHT10x->msgI2C.msgDelayus = NULL;
	AHT10x->msgI2C.msgAddr = AHT10_WADDR;//0x80;  // SHT2X_WRITE_ADDR;
	AHT10x->msgI2C.msgClockSpeed = 10;
	//---每次读取的间隔时间,76ms
	AHT10x->msgIntervalTime=76;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AHT10_I2C_Device1_Init(AHT10_HandlerType* AHT10x)
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
UINT8_T AHT10_I2C_Device2_Init(AHT10_HandlerType* AHT10x)
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
UINT8_T AHT10_I2C_DeInit(AHT10_HandlerType* AHT10x)
{
	//---注销I2C设备
	if (AHT10x->msgI2C.msgModelIsHW == 1)
	{
		return ERROR_1;
	}
	else
	{
		return I2CTask_MSW_DeInit(&(AHT10x->msgI2C));
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：
//////输入参数:isHWI2C---1 硬件，0 软件
//////输出参数:
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AHT10_I2C_Init(AHT10_HandlerType* AHT10x, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHWI2C)
{
	UINT8_T _return = OK_0;
	//---指定设备的初始化
	if ((AHT10x != NULL) && (AHT10x == AHT10_TASK_ONE))
	{
		AHT10_I2C_Device0_Init(AHT10x);
	}
	else if ((AHT10x != NULL) && (AHT10x == AHT10_TASK_TWO))
	{
		AHT10_I2C_Device1_Init(AHT10x);
	}
	else if ((AHT10x != NULL) && (AHT10x == AHT10_TASK_THREE))
	{
		AHT10_I2C_Device2_Init(AHT10x);
	}
	else
	{
		return ERROR_1;
	}
	//---判断是硬件I2C还是软件I2C
	if (isHWI2C)
	{
		//---初始化硬件I2C
		_return = I2CTask_MHW_Init(&(AHT10x->msgI2C));
		AHT10x->msgI2C.msgModelIsHW = 1;
	}
	else
	{
		//---初始化软件模拟I2C
		_return = I2CTask_MSW_Init(&(AHT10x->msgI2C), pFuncDelayus);
		AHT10x->msgI2C.msgModelIsHW = 0;
	}
	//---延时等待40ms
	if (pFuncDelayms!=NULL)
	{
		pFuncDelayms(40);
	}
	else
	{
		DelayTask_ms(40);
	}
	//---注册滴答函数
	if (pFuncTimerTick != NULL)
	{
		AHT10x->msgTimeTick = pFuncTimerTick;
	}
	else
	{
		AHT10x->msgTimeTick = SysTickTask_GetTick;
	}
	//---配置设备
	_return = AHT10_I2C_Config(AHT10x);
	//---当前时间
	AHT10x->msgRecordTime = AHT10x->msgTimeTick();
	return _return;
}

//////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能： 写Bulk模式
//////输入参数:
//////输出参数:
//////说		明： 软件模拟I2C传输命令
//////////////////////////////////////////////////////////////////////////////
UINT8_T AHT10_SWI2C_WriteBulk(AHT10_HandlerType* AHT10x,UINT8_T* pVal, UINT8_T length)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---启动并发送写操作
	_return = I2CTask_MSW_START(&(AHT10x->msgI2C), 1);
	if (_return != OK_0)
	{
		//---启动写数据失败
		_return = ERROR_2;
		goto GoToExit;
	}
	//---发送数据
	for (i = 0; i < length; i++)
	{
		//---发送数据
		I2CTask_MSW_SendByte(&(AHT10x->msgI2C), pVal[i]);
		//---读取ACK
		_return = I2CTask_MSW_ReadACK(&(AHT10x->msgI2C));
		//---判断应答
		if (_return)
		{
			_return = ERROR_3 + i;
			goto GoToExit;
		}
	}
	//---退出入口函数
GoToExit:
	//---发送停止信号
	I2CTask_MSW_STOP(&(AHT10x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AHT10_HWI2C_WriteBulk(AHT10_HandlerType* AHT10x, UINT8_T* pVal, UINT8_T length)
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
UINT8_T AHT10_I2C_WriteBulk(AHT10_HandlerType* AHT10x, UINT8_T* pVal, UINT8_T length)
{
	if (AHT10x->msgI2C.msgModelIsHW == 0)
	{
		//---软件模拟I2C
		return AHT10_SWI2C_WriteBulk(AHT10x,pVal, length);
	}
	else
	{
		//---硬件I2C
		return AHT10_HWI2C_WriteBulk(AHT10x,pVal, length);
	}
}

//////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能： 读Bulk模式
//////输入参数:
//////输出参数:
//////说		明： 软件模拟I2C传输命令
//////////////////////////////////////////////////////////////////////////////
UINT8_T AHT10_SWI2C_ReadBulk(AHT10_HandlerType* AHT10x, UINT8_T* pVal, UINT8_T length)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---启动读取数据
	_return = I2CTask_MSW_START(&(AHT10x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---启动读数据失败
		_return = ERROR_2;
		goto GoToExit;
	}
	//---发送数据
	for (i = 0; i < length; i++)
	{
		//---读取数据
		*(pVal++) = I2CTask_MSW_ReadByte(&(AHT10x->msgI2C));
		//---校验是否需要ACK
		if (i == (length - 1))
		{
			_return = 1;
		}
		//---发送应答信号
		I2CTask_MSW_SendACK(&(AHT10x->msgI2C), _return);
	}
	_return = OK_0;
	//---退出入口函数
GoToExit:
	//---发送停止信号
	I2CTask_MSW_STOP(&(AHT10x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AHT10_HWI2C_ReadBulk(AHT10_HandlerType* AHT10x, UINT8_T* pVal, UINT8_T length)
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
UINT8_T AHT10_I2C_ReadBulk(AHT10_HandlerType* AHT10x, UINT8_T* pVal, UINT8_T length)
{
	if (AHT10x->msgI2C.msgModelIsHW == 0)
	{
		//---软件模拟I2C
		return AHT10_SWI2C_ReadBulk(AHT10x, pVal, length);
	}
	else
	{
		//---硬件I2C
		return AHT10_HWI2C_ReadBulk(AHT10x, pVal, length);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：配置初始化
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AHT10_I2C_Config(AHT10_HandlerType* AHT10x)
{
	UINT8_T tempCMD[3]={ AHT10_CMD_INIT,0x08,0x00};
	//---发送初始化命令
	UINT8_T _return= AHT10_I2C_WriteBulk(AHT10x,tempCMD,3);
	if (_return==OK_0)
	{
		_return= AHT10_I2C_StartMeasure(AHT10x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：启动测量
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AHT10_I2C_StartMeasure(AHT10_HandlerType* AHT10x)
{
	UINT8_T tempCMD[3] = { AHT10_CMD_MEASURE,0x33,0x00 };
	//---发送测量命令
	UINT8_T _return=AHT10_I2C_WriteBulk(AHT10x, tempCMD, 3);
	//---获取时间街拍
	AHT10x->msgRecordTime=AHT10x->msgTimeTick();
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：当前状态
//////输入参数:
//////输出参数: 0---可以读取；1---间隔读取时间还没有到达，不允许读取
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AHT10_I2C_STATE(AHT10_HandlerType* AHT10x)
{	
	//---当前时间节点
	UINT32_T nowTime = AHT10x->msgTimeTick();
	UINT32_T cnt = 0;
	//---判断滴答定时是否发生溢出操作
	if (AHT10x->msgRecordTime > nowTime)
	{
		cnt = (0xFFFFFFFF - AHT10x->msgRecordTime + nowTime);
	}
	else
	{
		cnt = nowTime - AHT10x->msgRecordTime;
	}
	//---校验时间间隔是否到达
	if (cnt > AHT10x->msgIntervalTime)
	{
		return OK_0;
	}
	else
	{
		return ERROR_1;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取温湿度
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AHT10_I2C_ReadTempHumi(AHT10_HandlerType* AHT10x)
{
	UINT8_T tempVal[6] = { 0x00,0x00,0x00,0x00,0x00,0x00 };
	//---读取温度数据
	UINT8_T _return= AHT10_I2C_STATE(AHT10x);
	//---校验读取结果
	if (_return!=OK_0)
	{
		//---时间间隔未到，无法读取数据
		return ERROR_1;
	}
	//---时间节点到达，读取温湿度的结果
	_return=AHT10_I2C_ReadBulk(AHT10x, tempVal, 6);
	//---校验读取结果
	if (_return == OK_0)
	{
		//---计算温度值
		//AHT10x->msgTemp = ((tempVal[3] & 0x0F) << 16) | (tempVal[4] << 8) | tempVal[5];
		AHT10x->msgTemp = (tempVal[3] & 0x0F);
		AHT10x->msgTemp=(AHT10x->msgTemp<<8)+ tempVal[4];
		AHT10x->msgTemp = (AHT10x->msgTemp << 8) + tempVal[5];
		AHT10x->msgTemp = (((200.0 * (float)AHT10x->msgTemp) / 1048576.0) - 50.0) * 100.0;
		//---计算湿度值
		//AHT10x->msgHumi = ((tempVal[1] << 16) | (tempVal[2] << 8) | tempVal[3]) >> 4;
		AHT10x->msgHumi = tempVal[1];
		AHT10x->msgHumi =(AHT10x->msgHumi<<8)+ tempVal[2];
		AHT10x->msgHumi = (AHT10x->msgHumi << 8) + (tempVal[3]>>4);
		AHT10x->msgHumi = (float)AHT10x->msgHumi * 10000.0 / 1048576.0;
	}
	//---启动下次测量装换装换
	AHT10_I2C_StartMeasure(AHT10x);
	//---返回结果
	return ((_return==OK_0)?OK_0:(_return+ERROR_1));
}

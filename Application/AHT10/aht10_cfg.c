#include "aht10_cfg.h"

//===全局变量定义
AHT10_HandleType		g_Aht10Device0={0};
pAHT10_HandleType		pAht10Device0=&g_Aht10Device0;

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AHT10_I2C_Device0_Init(AHT10_HandleType* AHT10x)
{
	AHT10x->msgI2C.pMsgI2Cx = NULL;
	AHT10x->msgI2C.msgSCL.msgPort = GPIOB;
	AHT10x->msgI2C.msgSCL.msgBit = LL_GPIO_PIN_6;
	AHT10x->msgI2C.msgSDA.msgPort = GPIOB;
	AHT10x->msgI2C.msgSDA.msgBit = LL_GPIO_PIN_7;
	AHT10x->msgI2C.msgHwMode = 0;
	AHT10x->msgI2C.msgPluseWidth = 0;
	AHT10x->msgI2C.pMsgDelayus = NULL;
	AHT10x->msgI2C.msgAddr = AHT10_WADDR;//0x80;  // SHT2X_WRITE_ADDR;
	AHT10x->msgI2C.msgClockSpeed = 200000;
	//---每次读取的间隔时间,76ms，建议采集周期是760ms
	AHT10x->msgIntervalTime=76*2;
	//---设定温度初始值是室温25摄氏度
	AHT10x->msgTemp=25*100;
	AHT10x->msgHumiX10000=(50*10000);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AHT10_I2C_Device1_Init(AHT10_HandleType* AHT10x)
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
UINT8_T AHT10_I2C_Device2_Init(AHT10_HandleType* AHT10x)
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
UINT8_T AHT10_I2C_DeInit(AHT10_HandleType* AHT10x)
{
	//---注销I2C设备
	return I2CTask_Master_DeInit(&(AHT10x->msgI2C));
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：
//////输入参数:isHWI2C---1 硬件，0 软件
//////输出参数:
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AHT10_I2C_Init(AHT10_HandleType* AHT10x, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHWI2C)
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
	(isHWI2C != 0) ? (_return = I2CTask_MHW_Init(&(AHT10x->msgI2C),pFuncDelayus, pFuncTimerTick)) : (_return = I2CTask_MSW_Init(&(AHT10x->msgI2C), pFuncDelayus, pFuncTimerTick));
	//---延时等待40ms
	(pFuncDelayms != NULL) ? (pFuncDelayms(40)) : (DelayTask_ms(40));
	//---配置设备
	_return = AHT10_I2C_Config(AHT10x);
	//---当前时间
	AHT10x->msgRecordTick = AHT10x->msgI2C.pMsgTimeTick();
	return _return;
}

//////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能： 写Bulk模式
//////输入参数:
//////输出参数:
//////说		明： 软件模拟I2C传输命令
//////////////////////////////////////////////////////////////////////////////
UINT8_T AHT10_SWI2C_WriteBulk(AHT10_HandleType* AHT10x,UINT8_T* pVal, UINT8_T length)
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
UINT8_T AHT10_HWI2C_WriteBulk(AHT10_HandleType* AHT10x, UINT8_T* pVal, UINT8_T length)
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
		//---发送数据，内部寄存器数据
		_return = I2CTask_MHW_PollMode_SendByte(&(AHT10x->msgI2C), pVal[i], ((i == (length - 1)) ? 1 : 0));
		if (_return != OK_0)
		{
			//---发送数据错误
			_return = (ERROR_3 + i);
			goto GoToExit;
		}
	}
	//---退出入口函数
GoToExit:
	//---发送停止信号
	I2CTask_MHW_PollMode_STOP(&(AHT10x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AHT10_I2C_WriteBulk(AHT10_HandleType* AHT10x, UINT8_T* pVal, UINT8_T length)
{
	if (AHT10x->msgI2C.msgHwMode == 0)
	{
		//---软件模拟I2C
		return AHT10_SWI2C_WriteBulk(AHT10x,pVal, length);
	}
	else
	{
		I2CTask_MHW_CheckClock(&(AHT10x->msgI2C));
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
UINT8_T AHT10_SWI2C_ReadBulk(AHT10_HandleType* AHT10x, UINT8_T* pVal, UINT8_T length)
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
		//---发送应答信号
		I2CTask_MSW_SendACK(&(AHT10x->msgI2C), (i == (length - 1)) ? 1 : 0);
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
UINT8_T AHT10_HWI2C_ReadBulk(AHT10_HandleType* AHT10x, UINT8_T* pVal, UINT8_T length)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---启动读取数据
	_return = I2CTask_MHW_PollMode_START(&(AHT10x->msgI2C), 0);
	if (_return != OK_0)
	{
		//---启动读数据失败
		_return = ERROR_2;
		goto GoToExit;
	}
	//---发送数据
	for (i = 0; i < length; i++)
	{
		//---发送应答信号
		I2CTask_MHW_SendACK(&(AHT10x->msgI2C), (i == (length - 1)) ? 1 : 0);
		//---读取数据
		pVal[i] = I2CTask_MHW_PollMode_ReadByte(&(AHT10x->msgI2C));
	}
	_return = OK_0;
	//---退出入口函数
GoToExit:
	//---发送停止信号
	I2CTask_MHW_PollMode_STOP(&(AHT10x->msgI2C));
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AHT10_I2C_ReadBulk(AHT10_HandleType* AHT10x, UINT8_T* pVal, UINT8_T length)
{
	if (AHT10x->msgI2C.msgHwMode == 0)
	{
		//---软件模拟I2C
		return AHT10_SWI2C_ReadBulk(AHT10x, pVal, length);
	}
	else
	{
		I2CTask_MHW_CheckClock(&(AHT10x->msgI2C));
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
UINT8_T AHT10_I2C_Config(AHT10_HandleType* AHT10x)
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
UINT8_T AHT10_I2C_StartMeasure(AHT10_HandleType* AHT10x)
{
	UINT8_T tempCMD[3] = { AHT10_CMD_MEASURE,0x33,0x00 };
	//---发送测量命令
	UINT8_T _return=AHT10_I2C_WriteBulk(AHT10x, tempCMD, 3);
	//---获取时间街拍
	AHT10x->msgRecordTick= AHT10x->msgI2C.pMsgTimeTick();
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：当前状态
//////输入参数:
//////输出参数: 0---可以读取；1---间隔读取时间还没有到达，不允许读取
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AHT10_I2C_STATE(AHT10_HandleType* AHT10x)
{	
	//---当前时间节点
	UINT32_T nowTime = AHT10x->msgI2C.pMsgTimeTick();
	UINT32_T cnt = 0;
	//---判断滴答定时是否发生溢出操作
	if (AHT10x->msgRecordTick > nowTime)
	{
		cnt = (0xFFFFFFFF - AHT10x->msgRecordTick + nowTime);
	}
	else
	{
		cnt = nowTime - AHT10x->msgRecordTick;
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
UINT8_T AHT10_I2C_ReadTempHumi(AHT10_HandleType* AHT10x)
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
		AHT10x->msgTemp =(AHT10x->msgTemp<<8)+ tempVal[4];
		AHT10x->msgTemp = (AHT10x->msgTemp << 8) + tempVal[5];
		//---校验温度是不是负值
		if (AHT10x->msgTemp>0x40000)
		{
			//---温度数据是正数
			AHT10x->msgPositive = 0;
		}
		else
		{
			//---温度数据是负数
			AHT10x->msgPositive = 1;
		}
		AHT10x->msgTemp = (INT32_T)((((200.0 * (float)AHT10x->msgTemp) / 1048576.0) - 50.0) * 100.0);
		//---计算湿度值
		//AHT10x->msgHumi = ((tempVal[1] << 16) | (tempVal[2] << 8) | tempVal[3]) >> 4;
		AHT10x->msgHumiX10000 = tempVal[1];
		AHT10x->msgHumiX10000 =(AHT10x->msgHumiX10000<<8)+ tempVal[2];
		AHT10x->msgHumiX10000 = (AHT10x->msgHumiX10000 << 8) + (tempVal[3]>>4);
		AHT10x->msgHumiX10000 = (INT32_T)((float)AHT10x->msgHumiX10000 * 10000.0 / 1048576.0);
	}
	//---启动下次测量装换装换
	AHT10_I2C_StartMeasure(AHT10x);
	//---返回结果
	return ((_return==OK_0)?OK_0:(_return+ERROR_1));
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：获取温度
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
float AHT10_I2C_GetTemp(AHT10_HandleType* AHT10x)
{
	float tempVal = AHT10x->msgTemp;
	//---转换温度对应实际的温度值
	tempVal /= 100.0;
	//---校验是不是正数
	if (AHT10x->msgPositive == 1)
	{
		tempVal *= (-1.0);
	}
	return tempVal;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：获取湿度
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
float AHT10_I2C_GetHumi(AHT10_HandleType* AHT10x)
{
	float tempVal = AHT10x->msgHumiX10000;
	//---转换温度对应实际的温度值
	tempVal /= 10000.0;
	return tempVal;
}


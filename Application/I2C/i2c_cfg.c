#include "i2c_cfg.h"

//>>>===模拟I2C主机---开始
///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_Init(I2C_HandleType *I2Cx, void(*pFuncDelayus)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void))
{
	//---使能GPIO的时钟
	#ifndef  USE_FULL_GPIO
	GPIOTask_Clock(I2Cx->msgSCL.msgPort, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(I2Cx->msgSDA.msgPort, PERIPHERAL_CLOCK_ENABLE);
	#endif
	//---GPIO的结构体
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	//---GPIO的初始化
	GPIO_InitStruct.Pin = I2Cx->msgSCL.msgBit;																			//---对应的GPIO的引脚
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;																			//---配置状态为输出模式
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;																	//---GPIO的速度---低速设备
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;																//---输出模式---开漏输出
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;																				//---上拉
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;																			//---端口复用模式
#endif
	//---SCL的初始化
	LL_GPIO_Init(I2Cx->msgSCL.msgPort, &GPIO_InitStruct);
	GPIO_OUT_1(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	//---SDA的初始化
	GPIO_InitStruct.Pin = I2Cx->msgSDA.msgBit;
	LL_GPIO_Init(I2Cx->msgSDA.msgPort, &GPIO_InitStruct);
	GPIO_OUT_1(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
	//---us延时函数
	I2Cx->pMsgDelayus = ((pFuncDelayus != NULL) ? pFuncDelayus : DelayTask_us);
	//---注册滴答函数
	I2Cx->pMsgTimeTick = ((pFuncTimerTick != NULL) ? pFuncTimerTick : SysTickTask_GetTick);
	//---软件模式
	I2Cx->msgHwMode = 0;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_DeInit(I2C_HandleType *I2Cx)
{
	//---GPIO的结构体
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	//---GPIO的初始化
	GPIO_InitStruct.Pin = I2Cx->msgSCL.msgBit;					//---对应的GPIO的引脚
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;						//---配置状态为输出模式
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;					//---GPIO的速度---低速设备
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;			//---输出模式---开漏输出
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;							//---上拉
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---端口复用模式
#endif
	//---SCL的初始化
	LL_GPIO_Init(I2Cx->msgSCL.msgPort, &GPIO_InitStruct);
	GPIO_OUT_1(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	//---SDA的初始化
	GPIO_InitStruct.Pin = I2Cx->msgSDA.msgBit;
	LL_GPIO_Init(I2Cx->msgSDA.msgPort, &GPIO_InitStruct);
	GPIO_OUT_1(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_START(I2C_HandleType *I2Cx)
{
	//---发送起始条件的数据信号
	GPIO_OUT_1(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
	GPIO_OUT_1(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	if (I2Cx->msgPluseWidth>0)
	{
		I2Cx->pMsgDelayus(I2Cx->msgPluseWidth);
	}
	//---发送起始信号;
	GPIO_OUT_0(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
	if (I2Cx->msgPluseWidth>0)
	{
		I2Cx->pMsgDelayus(I2Cx->msgPluseWidth);
	}
	//---钳住I2C总线，准备发送或接收数据
	GPIO_OUT_0(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	//---判断I2C启动信号是否成功，读取SDA的状态信号，成功SDA---0；失败SDA---1
	return  ((GPIO_GET_STATE(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit) != 0x00)?ERROR_1:OK_0);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_STOP(I2C_HandleType *I2Cx)
{
	//---发送停止条件的数据信号
	GPIO_OUT_0(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
	GPIO_OUT_1(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	if (I2Cx->msgPluseWidth>0)
	{
		I2Cx->pMsgDelayus(I2Cx->msgPluseWidth);
	}
	GPIO_OUT_1(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
	if (I2Cx->msgPluseWidth>0)
	{
		I2Cx->pMsgDelayus(I2Cx->msgPluseWidth);
	}
	//---判断I2C启动信号是否成功，读取SDA的状态信号，成功SDA---1；失败SDA---0
	return ((GPIO_GET_STATE(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit) == 0x00) ? ERROR_1 : OK_0);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_ACK(I2C_HandleType *I2Cx)
{
	GPIO_OUT_0(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
	GPIO_OUT_1(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	////---延时等待，等待SCL被从机释放
	//if (I2Cx->msgPluseWidth>0)
	//{
	//	I2Cx->msgDelayus(I2Cx->msgPluseWidth);
	//}
	//检查SCL被从机释放,SCL为高,代表从机释放总线
	GPIOTask_WaitPinPort(&(I2Cx->msgSCL), 1);
	//---清时钟线,钳住I2C总线，准备发送或接收数据
	GPIO_OUT_0(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_NACK(I2C_HandleType *I2Cx)
{
	GPIO_OUT_1(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
	GPIO_OUT_1(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	////---延时等待，等待SCL被从机释放
	//if (I2Cx->msgPluseWidth>0)
	//{
	//	I2Cx->msgDelayus(I2Cx->msgPluseWidth);
	//}
	//检查SCL被从机释放,SCL为高,代表从机释放总线
	GPIOTask_WaitPinPort(&(I2Cx->msgSCL), 1);
	//---清时钟线,钳住I2C总线，准备发送或接收数据
	GPIO_OUT_0(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_ReadACK(I2C_HandleType *I2Cx)
{
	UINT8_T _return = OK_0;
	//---读取应答信号
	GPIO_OUT_1(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
	GPIO_OUT_1(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	////---延时等待，等待SCL被从机释放
	//if (I2Cx->msgPluseWidth > 0)
	//{
	//	I2Cx->msgDelayus(I2Cx->msgPluseWidth);
	//}
	//检查SCL被从机释放,SCL为高,代表从机释放总线
	GPIOTask_WaitPinPort(&(I2Cx->msgSCL), 1);
	//---读取SDA的状态信号---ACK状态下SDA为低电平
	_return= ((GPIO_GET_STATE(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit) != 0x00) ? ERROR_1 : OK_0);
	//---清时钟线,钳住I2C总线，准备发送或接收数据
	GPIO_OUT_0(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_WaitACK(I2C_HandleType *I2Cx)
{
	UINT8_T _return = OK_0;
	//---读取应答信号
	GPIO_OUT_1(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
	GPIO_OUT_1(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	////---等待应答信号
	//UINT8_T i = 0;
	//for (i = 255; i > 0; i--)
	//{
	//	//---读取SDA的状态
	//	if (GPIO_GET_STATE(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit))
	//	{
	//		break;
	//	}
	//}
	//if (i == 0)
	//{
	//	I2C_MSW_STOP(I2Cx);
	//	return ERROR_1;
	//}
	////---清时钟线,钳住I2C总线，准备发送或接收数据
	//GPIO_OUT_0(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	//检查SDA电平,SDA为高,代表从机发送ACK
	_return= GPIOTask_WaitPinPort(&(I2Cx->msgSDA), 1);
	if(_return != OK_0) 
	{	  
	 	I2C_MSW_STOP(I2Cx);
	}
	else
	{
	  	GPIO_OUT_0(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
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
UINT8_T I2C_MSW_SendACK(I2C_HandleType *I2Cx, UINT8_T isNACK)
{
	if (isNACK)
	{
		return I2C_MSW_NACK(I2Cx);
	}
	else
	{
		return I2C_MSW_ACK(I2Cx);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_SendBit(I2C_HandleType *I2Cx, UINT8_T bitVal)
{
	((bitVal&0x80)!=0x00)? GPIO_OUT_1(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit): GPIO_OUT_0(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
	//---一个时钟脉冲
	GPIO_OUT_1(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);	
	I2Cx->pMsgDelayus(I2Cx->msgPluseWidth);
	//DELAY_NOP_COUNT(2);
	GPIO_OUT_0(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);	
	I2Cx->pMsgDelayus(I2Cx->msgPluseWidth);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_SendByte(I2C_HandleType *I2Cx, UINT8_T val)
{
	UINT8_T i = 0;
	//---清时钟线,钳住I2C总线，准备发送或接收数据
	GPIO_OUT_0(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	//---发送1字节的数据
	for (i = 0; i < 8; i++)
	{
		//---读取1Bit的数据
		I2C_MSW_SendBit(I2Cx, val);
		val <<= 1;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_SendBits(I2C_HandleType *I2Cx, UINT8_T *pVal, UINT8_T bitNum)
{
	//---计算字节个数
	UINT8_T byteCount = (bitNum / 8);
	//---计算bit个数
	UINT8_T bitCount = (bitNum % 8);
	UINT8_T i = 0;
	//---发送整数字节的个数
	for (i = 0; i < byteCount; i++)
	{
		I2C_MSW_SendByte(I2Cx, pVal[i]);
	}
	//---数据左移---数据的发送，首先发送高位
	pVal[byteCount] <<= (8 - bitCount);
	//---判断发送数据是不是不满足1字节
	if (byteCount == 0)
	{
		//---清时钟线,钳住I2C总线，准备发送或接收数据
		GPIO_OUT_0(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	}
	//---发送指定个数的bit
	for (i = 0; i < bitCount; i++)
	{
		I2C_MSW_SendBit(I2Cx, pVal[byteCount]);
		pVal[byteCount] <<= 1;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_SendWord(I2C_HandleType *I2Cx, UINT16_T val)
{
	UINT8_T valH = (UINT8_T)(val >> 8);
	UINT8_T valL = (UINT8_T)(val);
	UINT8_T i = 0;
	//---清时钟线,钳住I2C总线，准备发送或接收数据
	GPIO_OUT_0(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	//---发送1字节的数据
	for (i = 0; i < 8; i++)
	{
		//---读取1Bit的数据
		I2C_MSW_SendBit(I2Cx, valH);
		//---数据左移动
		valH <<= 1;
	}
	//---发送1字节的数据
	for (i = 0; i < 8; i++)
	{
		//---读取1Bit的数据
		I2C_MSW_SendBit(I2Cx, valL);
		//---数据右移
		valL <<= 1;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_ReadBit(I2C_HandleType *I2Cx)
{
	UINT8_T _return = OK_0;
	//---时钟正脉冲
	GPIO_OUT_1(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	I2Cx->pMsgDelayus(I2Cx->msgPluseWidth);
	//DELAY_NOP_COUNT(4);
	//---读取数据位
	_return= ((GPIO_GET_STATE(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit) != 0x00) ? 1 : 0);
	//---时钟负脉冲
	GPIO_OUT_0(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	I2Cx->pMsgDelayus(I2Cx->msgPluseWidth);
	return  _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_ReadByte(I2C_HandleType *I2Cx)
{
	UINT8_T i = 0;
	UINT8_T _return = 0;
	//---准备数据的读取
	GPIO_OUT_1(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
	//---清时钟线,钳住I2C总线，准备发送或接收数据
	GPIO_OUT_0(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	//---发送1字节的数据
	for (i = 0; i < 8; i++)
	{
		_return <<= 1;
		_return |= I2C_MSW_ReadBit(I2Cx);
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
UINT8_T I2C_MSW_ReadBits(I2C_HandleType *I2Cx, UINT8_T *pVal, UINT8_T bitNum)
{
	//---读取字节个数
	UINT8_T byteCount = (bitNum / 8);
	//---读取bit个数
	UINT8_T bitCount = (bitNum % 8);
	UINT8_T i = 0;
	//---读取整数字节的个数
	for (i = 0; i < byteCount; i++)
	{
		pVal[i] = I2C_MSW_ReadByte(I2Cx);
	}
	//---清零处理
	pVal[byteCount] = 0x00;
	//---判断读取的Bit数据是不是不满足1字节
	if (byteCount == 0)
	{
		//---准备数据的读取
		GPIO_OUT_1(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
		//---清时钟线,钳住I2C总线，准备发送或接收数据
		GPIO_OUT_0(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	}
	//---读取指定个数的bit
	for (i = 0; i < bitCount; i++)
	{
		pVal[byteCount] <<= 1;
		pVal[byteCount] |= I2C_MSW_ReadBit(I2Cx);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_CheckDevice(I2C_HandleType *I2Cx)
{
	UINT8_T _return = OK_0;
	if ((GPIO_GET_STATE(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit)) && (GPIO_GET_STATE(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit)))
	{
		//---发送启动信号
		I2C_MSW_START(I2Cx);
		//---发送读取操作命令
		I2Cx->msgAddr |= 0x01;
		//---发送从机地址
		I2C_MSW_SendByte(I2Cx, (UINT8_T)I2Cx->msgAddr);
		//---读取应答信号
		_return = I2C_MSW_ReadACK(I2Cx);
	}
	else
	{
		_return = ERROR_2;
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
UINT8_T I2C_MSW_SendCMD(I2C_HandleType *I2Cx, UINT8_T cmd, UINT8_T isStart, UINT8_T isStop)
{
	UINT8_T _return = OK_0;
	if (isStart)
	{
		//---发送启动启动信号
		_return = I2C_MSW_START(I2Cx);
		if (_return)
		{
			I2C_MSW_STOP(I2Cx);
			return ERROR_1;
		}
	}
	//---发送数据
	_return = I2C_MSW_SendByte(I2Cx, cmd);
	//---读取应答
	_return = I2C_MSW_ReadACK(I2Cx);
	//---停止条件的满足
	if ((isStop) || (_return))
	{
		I2C_MSW_STOP(I2Cx);
	}
	return _return;
}
//////////////////////////////////////////////////////////////////////////////
//<<<===模拟I2C主机---结束

//////////////////////////////////////////////////////////////////////////////
//>>>===硬件I2C主机---开始


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：使能I2C的外设时钟
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_Clock(I2C_HandleType* I2Cx, UINT8_T isEnable)
{
	#ifdef I2C3
	if (I2Cx->pMsgI2Cx == I2C1)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_I2C1);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
			LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_I2C1);
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
			LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_I2C1);
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
	#endif
	#ifdef I2C2
	if (I2Cx->pMsgI2Cx == I2C2)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_I2C2);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C2);
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
			LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_I2C2);
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
			LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_I2C2);
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
	#endif
#ifdef I2C3
	if (I2Cx->pMsgI2Cx == I2C3)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_I2C3);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C3);
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
			LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_I2C3);
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
			LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_I2C3);
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
#endif
	return ERROR_2;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MHW_Init(I2C_HandleType* I2Cx, void(*pFuncDelayus)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void))
{
	//---使能GPIO的时钟
	#ifndef  USE_FULL_GPIO
	GPIOTask_Clock(I2Cx->msgSCL.msgPort, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(I2Cx->msgSDA.msgPort, PERIPHERAL_CLOCK_ENABLE);
	#endif
	//---GPIO的结构体
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	//---GPIO的初始化
	GPIO_InitStruct.Pin = I2Cx->msgSCL.msgBit;																			//---对应的GPIO的引脚
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;																		//---配置状态为输出模式
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;																	//---GPIO的速度---低速设备
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;																//---输出模式---开漏输出
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;																				//---上拉
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = I2Cx->msgGPIOAlternate;																	//---端口复用模式
#endif
	//---SCL的初始化
	LL_GPIO_Init(I2Cx->msgSCL.msgPort, &GPIO_InitStruct);
	GPIO_OUT_1(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	//---SDA的初始化
	GPIO_InitStruct.Pin = I2Cx->msgSDA.msgBit;
	LL_GPIO_Init(I2Cx->msgSDA.msgPort, &GPIO_InitStruct);
	GPIO_OUT_1(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);

	//---开启I2C外设时钟
	I2C_Clock(I2Cx, PERIPHERAL_CLOCK_ENABLE);
	//---复位I2C
	LL_I2C_DeInit(I2Cx->pMsgI2Cx);
#ifdef  USE_RESET_I2C
	LL_I2C_EnableReset(I2Cx->pMsgI2Cx);
	LL_I2C_DisableReset(I2Cx->pMsgI2Cx);
#endif
	//---初始化I2C
	LL_I2C_InitTypeDef I2C_InitStruct={0};
	I2C_InitStruct.PeripheralMode = LL_I2C_MODE_I2C;																	//---工作模式
	I2C_InitStruct.ClockSpeed = I2Cx->msgClockSpeed;																	//---SCL时钟频率
	I2C_InitStruct.DutyCycle = LL_I2C_DUTYCYCLE_2;																		//---时钟占空比
	I2C_InitStruct.OwnAddress1 = 0;																						//---自身的I2C设备地址
	I2C_InitStruct.TypeAcknowledge = LL_I2C_ACK;																		//---使能或者关闭相应(默认一般开启)
	I2C_InitStruct.OwnAddrSize = LL_I2C_OWNADDRESS1_7BIT;																//---指定地址的长度，7Bit或者10BIt
	//---初始化
	LL_I2C_Init(I2Cx->pMsgI2Cx, &I2C_InitStruct);
	//---获取时钟分频数
	I2Cx->msgRegCCR = LL_I2C_GetClockPeriod(I2Cx->pMsgI2Cx);
	//---第二个地址
	LL_I2C_SetOwnAddress2(I2Cx->pMsgI2Cx, 0);
	//---使能I2C
	LL_I2C_Enable(I2Cx->pMsgI2Cx);
	//---us延时函数
	I2Cx->pMsgDelayus = ((pFuncDelayus != NULL) ? pFuncDelayus : DelayTask_us);
	//---注册滴答函数
	I2Cx->pMsgTimeTick = ((pFuncTimerTick != NULL) ? pFuncTimerTick : SysTickTask_GetTick);
	//---硬件模式
	I2Cx->msgHwMode = 1;
#ifdef  USE_RESET_I2C
	//---保存I2C的配置参数
	I2Cx->msgI2CInitTypeDef= I2C_InitStruct;
#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MHW_DeInit(I2C_HandleType* I2Cx)
{
	//---复位I2C
	LL_I2C_DeInit(I2Cx->pMsgI2Cx);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：轮训方式，等待校验标志
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MHW_PollMode_WaitFlag(I2C_HandleType* I2Cx,UINT32_T (*pFuncActiveFlag)(I2C_TypeDef* I2Cx), FlagStatus flagStatus)
{
	UINT8_T _return = OK_0;
	//---获取当前时间节拍
	UINT32_T nowTime = 0;
	UINT32_T oldTime = 0;
	UINT32_T cnt = 0;
	//---获取当前时间节拍
	oldTime = ((I2Cx->pMsgTimeTick != NULL) ? I2Cx->pMsgTimeTick() : 0);
	//---检查超时
	while (1)
	{
		//if (LL_I2C_IsActiveFlag_BUSY(I2Cx->msgI2Cx) == RESET)
		if (pFuncActiveFlag(I2Cx->pMsgI2Cx) == flagStatus)
		{
			break;
		}
		//---超时判断
		if (I2Cx->pMsgTimeTick != NULL)
		{
			//---当前时间
			nowTime = I2Cx->pMsgTimeTick();
			//---判断滴答定时是否发生溢出操作
			if (nowTime < oldTime)
			{
				cnt = (0xFFFFFFFF - oldTime + nowTime);
			}
			else
			{
				cnt = nowTime - oldTime;
			}
			//---判断是否超时
			if (cnt > 30)
			{
				//---发送发生超时错误
				_return = ERROR_1;
			}
		}
		else
		{
			nowTime++;
			if (nowTime > 100000)
			{
				//---发送发生超时错误
				_return = ERROR_2;
			}
		}
		//---退出循环
		if (_return != OK_0)
		{
			//---传送结束条件,避免状态异常，用于产生停止条件
			I2C_MHW_PollMode_STOP(I2Cx);
			break;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：发送启动信号
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MHW_PollMode_START(I2C_HandleType* I2Cx)
{
	//---保证I2C外设不在使用中
	UINT8_T _return =I2C_MHW_PollMode_WaitFlag(I2Cx, LL_I2C_IsActiveFlag_BUSY,RESET);
	//---校验外设结果
	if (_return == OK_0)
	{
		//---发送START信号
		LL_I2C_GenerateStartCondition(I2Cx->pMsgI2Cx);
		//---验证起始位是否发送
		_return=I2C_MHW_PollMode_WaitFlag(I2Cx, LL_I2C_IsActiveFlag_SB, SET);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能： 校验STOP信号
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MHW_CheckSTOP(I2C_HandleType* I2Cx)
{
	if (LL_I2C_IsEnabledGenerateStop(I2Cx->pMsgI2Cx)!=0)
	{
		LL_I2C_DisabledGenerateStop(I2Cx->pMsgI2Cx);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：发送停止信号
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MHW_PollMode_STOP(I2C_HandleType* I2Cx)
{
	//---传送结束条件
	LL_I2C_GenerateStopCondition(I2Cx->pMsgI2Cx);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：发送停止信号
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MHW_PollMode_ADDR(I2C_HandleType* I2Cx,UINT8_T isWrite)
{
	UINT8_T _return = OK_0;
	//---发送设备地址
	LL_I2C_TransmitData8(I2Cx->pMsgI2Cx, (isWrite==1)?(I2Cx->msgAddr&0xFE):(I2Cx->msgAddr |0x01));
	//---验证验证地址发送完成
	_return = I2C_MHW_PollMode_WaitFlag(I2Cx, LL_I2C_IsActiveFlag_ADDR, SET);
	//---清楚标志位
	LL_I2C_ClearFlag_ADDR(I2Cx->pMsgI2Cx);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：时钟参数的校验校验
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MHW_CheckClock(I2C_HandleType* I2Cx)
{
	if (I2Cx->msgRegCCR != LL_I2C_GetClockPeriod(I2Cx->pMsgI2Cx))
	{
		LL_I2C_SetClockPeriod(I2Cx->pMsgI2Cx, I2Cx->msgRegCCR);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MHW_SendACK(I2C_HandleType* I2Cx, UINT8_T isNACK)
{
	LL_I2C_AcknowledgeNextData(I2Cx->pMsgI2Cx, ((isNACK!=0)?LL_I2C_NACK: LL_I2C_ACK));
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：清楚Busy信息
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MHW_ClearBusy(I2C_HandleType* I2Cx)
{
	UINT8_T i = 0;
	LL_I2C_DeInit(I2Cx->pMsgI2Cx);
	//---GPIO的结构体
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	//---GPIO的初始化
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;																			//---配置状态为输出模式
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;																	//---GPIO的速度---低速设备
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;																//---输出模式---开漏输出
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;																				//---上拉
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;																			//---端口复用模式
#endif
	//---SCL的初始化
	GPIO_InitStruct.Pin = I2Cx->msgSCL.msgBit;
	LL_GPIO_Init(I2Cx->msgSCL.msgPort, &GPIO_InitStruct);
	//---SDA的初始化
	GPIO_InitStruct.Pin = I2Cx->msgSDA.msgBit;
	LL_GPIO_Init(I2Cx->msgSDA.msgPort, &GPIO_InitStruct);
	//---SCL发送9个脉冲，用于释放总线
	for (i = 0; i < 9; i++)
	{
		GPIO_OUT_0(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
		I2Cx->pMsgDelayus(10);
		GPIO_OUT_1(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
		I2Cx->pMsgDelayus(10);
	}
	//---I2C端口的复用模式
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;																		//---配置状态为输出模式
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = I2Cx->msgGPIOAlternate;																	//---端口复用模式
#endif
	//---SCL的初始化
	GPIO_InitStruct.Pin = I2Cx->msgSCL.msgBit;
	LL_GPIO_Init(I2Cx->msgSCL.msgPort, &GPIO_InitStruct);
	//GPIO_OUT_1(I2Cx->msgSCL.msgPort, I2Cx->msgSCL.msgBit);
	//---SDA的初始化
	GPIO_InitStruct.Pin = I2Cx->msgSDA.msgBit;
	LL_GPIO_Init(I2Cx->msgSDA.msgPort, &GPIO_InitStruct);
	//GPIO_OUT_1(I2Cx->msgSDA.msgPort, I2Cx->msgSDA.msgBit);
#ifdef  USE_RESET_I2C
	I2Cx->pMsgDelayus(1000);
	//---重新初始化i2C
	LL_I2C_Init(I2Cx->pMsgI2Cx, &(I2Cx->msgI2CInitTypeDef));
	//---获取时钟分频数
	I2Cx->msgRegCCR = LL_I2C_GetClockPeriod(I2Cx->pMsgI2Cx);
	//---第二个地址
	LL_I2C_SetOwnAddress2(I2Cx->pMsgI2Cx, 0);
	//---使能I2C
	LL_I2C_Enable(I2Cx->pMsgI2Cx);
#endif
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MHW_CheckBusy(I2C_HandleType* I2Cx)
{
	//---保证I2C外设不在使用中，检查到忙标识
	UINT8_T _return = I2C_MHW_PollMode_WaitFlag(I2Cx, LL_I2C_IsActiveFlag_BUSY, RESET);
	if(_return!=OK_0)
	{
		_return= I2C_MHW_ClearBusy(I2Cx);
	}
	return _return;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：发送数据
//////输入参数:
//////输出参数:
//////说		明：最后一次发送数据使用isBTF为1，用使用BTF标志位，用于验证数据传输完成
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MHW_PollMode_SendByte(I2C_HandleType* I2Cx, UINT8_T val,UINT8_T isBTF)
{
	//---地址位已经置位,通常TXE也会完成,为了谨慎,再查一下
	UINT8_T _return= I2C_MHW_PollMode_WaitFlag(I2Cx, LL_I2C_IsActiveFlag_TXE, SET);
	//---校验地址置位
	if (_return==OK_0)
	{
		//---发送数据
		LL_I2C_TransmitData8(I2Cx->pMsgI2Cx, val);
		//---校验发送寄存器空
		_return = I2C_MHW_PollMode_WaitFlag(I2Cx, LL_I2C_IsActiveFlag_TXE, SET);
		//---校验数据传输完成
		if ((_return == OK_0) && (isBTF != 0))
		{
			_return = I2C_MHW_PollMode_WaitFlag(I2Cx, LL_I2C_IsActiveFlag_BTF, SET);
		}
	}	
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取数据
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MHW_PollMode_ReadByte(I2C_HandleType* I2Cx)
{
	//---校验接收寄存器不为空
	UINT8_T _return= I2C_MHW_PollMode_WaitFlag(I2Cx, LL_I2C_IsActiveFlag_RXNE, SET);
	//---校验读取
	if (_return==OK_0)
	{
		//---数据已读取
		_return = LL_I2C_ReceiveData8(I2Cx->pMsgI2Cx);
	}
	return _return;
}
//////////////////////////////////////////////////////////////////////////////
//<<<===硬件I2C主机---结束

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_Master_DeInit(I2C_HandleType* I2Cx)
{
	//---注销I2C设备
	return ((I2Cx->msgHwMode != 0) ? (I2C_MHW_DeInit(I2Cx)) : (I2C_MSW_DeInit(I2Cx)));
}
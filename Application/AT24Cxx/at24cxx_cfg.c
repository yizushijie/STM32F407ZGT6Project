#include "at24cxx_cfg.h"

//===全局变量定义
AT24CXX_HandleType		g_AT24cxxDevice0={0};
pAT24CXX_HandleType		pAT24cxxDevice0 = &g_AT24cxxDevice0;

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： AT24Cxx的类型
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_I2C_DeviceType(AT24CXX_HandleType *AT24CXXx)
{
	#ifdef USE_QUERY_WAIT_IDLE
	AT24CXXx->msgIntervalTime = 0;
	AT24CXXx->msgRecordTick = 0;
	#endif
	//---解析页数和字节数据
	if (AT24CXXx->msgType == AT24C01)		//at24c01
	{
		AT24CXXx->msgPageNum = 16;
		AT24CXXx->msgPageByte = 8;
	}
	else if (AT24CXXx->msgType == AT24C02)	//at24c02
	{
		AT24CXXx->msgPageNum = 32;
		AT24CXXx->msgPageByte = 8;
	}
	else if (AT24CXXx->msgType == AT24C04)	//at24c04
	{
		AT24CXXx->msgPageNum = 32;
		AT24CXXx->msgPageByte = 16;
	}
	else if (AT24CXXx->msgType == AT24C08)	//at24c08
	{
		AT24CXXx->msgPageNum = 64;
		AT24CXXx->msgPageByte = 16;
	}
	else if (AT24CXXx->msgType == AT24C16)	//at24c16
	{
		AT24CXXx->msgPageNum = 128;
		AT24CXXx->msgPageByte = 16;
	}
	else if (AT24CXXx->msgType == AT24C32)	//at24c32
	{
		AT24CXXx->msgPageNum = 128;
		AT24CXXx->msgPageByte = 32;
	}
	else if (AT24CXXx->msgType == AT24C64)	//at24c64
	{
		AT24CXXx->msgPageNum = 256;
		AT24CXXx->msgPageByte = 32;
	}
	else if (AT24CXXx->msgType == AT24C128)	//at24c128
	{
		AT24CXXx->msgPageNum = 256;
		AT24CXXx->msgPageByte = 64;
	}
	else if (AT24CXXx->msgType == AT24C256)	//at24c256
	{
		AT24CXXx->msgPageNum = 512;
		AT24CXXx->msgPageByte = 64;
	}
	else if (AT24CXXx->msgType == AT24C512)	//at24c512
	{
		AT24CXXx->msgPageNum = 512;
		AT24CXXx->msgPageByte = 128;
	}
	else
	{
		return ERROR_1;
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
UINT8_T AT24CXX_I2C_Device0_Init(AT24CXX_HandleType* AT24CXXx)
{
	AT24CXXx->msgType = AT24C08;
	//---写保护端口的配置
	#ifdef USE_HW_WP
	AT24CXXx->msgWP.msgPort = GPIOC;
	AT24CXXx->msgWP.msgBit = LL_GPIO_PIN_4;
	//---初始化写保护
	#ifndef  USE_FULL_GPIO
	if (AT24CXXx->msgWP.msgPort != NULL)
	{
		GPIOTask_Clock(AT24CXXx->msgWP.msgPort, PERIPHERAL_CLOCK_ENABLE);
	}
	#endif
	#endif
	//---GPIO的结构体
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;						//---配置状态为输出模式
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;				//---GPIO的速度---低速设备
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;			//---输出模式---推挽输出
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;							//---上拉
	#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---端口复用模式
	#endif
	//---WP端口的初始化
	#ifdef USE_HW_WP
	if (AT24CXXx->msgWP.msgPort != NULL)
	{
		GPIO_InitStruct.Pin = AT24CXXx->msgWP.msgBit;
		LL_GPIO_Init(AT24CXXx->msgWP.msgPort, &GPIO_InitStruct);
		//---使能写保护
		GPIO_OUT_1(AT24CXXx->msgWP.msgPort, AT24CXXx->msgWP.msgBit);
	}
	#endif
	AT24CXXx->msgI2C.pMsgI2Cx = NULL;
	AT24CXXx->msgI2C.msgSCL.msgPort = GPIOB;
	AT24CXXx->msgI2C.msgSCL.msgBit = LL_GPIO_PIN_6;
	AT24CXXx->msgI2C.msgSDA.msgPort = GPIOB;
	AT24CXXx->msgI2C.msgSDA.msgBit = LL_GPIO_PIN_7;
	AT24CXXx->msgI2C.msgHwMode = 0;
	AT24CXXx->msgI2C.msgPluseWidth = 0;
	AT24CXXx->msgI2C.pMsgDelayus = NULL;
	AT24CXXx->msgI2C.msgAddr = AT24CXX_WADDR;
	AT24CXXx->msgI2C.msgClockSpeed = 200000;
	//---解析页数和字节数据
	return AT24CXX_I2C_DeviceType(AT24CXXx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_I2C_Device1_Init(AT24CXX_HandleType* AT24CXXx)
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
UINT8_T AT24CXX_I2C_Device2_Init(AT24CXX_HandleType* AT24CXXx)
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
UINT8_T AT24CXX_I2C_Init(AT24CXX_HandleType *AT24CXXx, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHWI2C)
{
	UINT8_T _return = OK_0;
	//---指定设备的初始化
	if ((AT24CXXx != NULL) && (AT24CXXx == AT24CXX_TASK_ONE))
	{
		_return = AT24CXX_I2C_Device0_Init(AT24CXXx);
	}
	else if ((AT24CXXx != NULL) && (AT24CXXx == AT24CXX_TASK_TWO))
	{
		_return = AT24CXX_I2C_Device1_Init(AT24CXXx);
	}
	else if ((AT24CXXx != NULL) && (AT24CXXx == AT24CXX_TASK_THREE))
	{
		_return = AT24CXX_I2C_Device2_Init(AT24CXXx);
	}
	else
	{
		return ERROR_1;
	}
	//---判断是硬件I2C还是软件I2C
	(isHWI2C != 0) ? (_return = I2CTask_MHW_Init(&(AT24CXXx->msgI2C),pFuncDelayus, pFuncTimerTick)) : (_return = I2CTask_MSW_Init(&(AT24CXXx->msgI2C), pFuncDelayus, pFuncTimerTick));
	//---毫秒延时函数的注册
	(pFuncDelayms != NULL) ? (AT24CXXx->pMsgDelayms = pFuncDelayms) : (AT24CXXx->pMsgDelayms = DelayTask_ms);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：	注销I2C的配置
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_I2C_DeInit(AT24CXX_HandleType *AT24CXXx)
{
	return I2CTask_Master_DeInit(&(AT24CXXx->msgI2C));
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置AT24Cxx写操作的延时时间
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_I2C_IntervalTime(AT24CXX_HandleType* AT24CXXx,UINT16_T intervalTime)
{
	#ifdef USE_QUERY_WAIT_IDLE
	AT24CXXx->msgIntervalTime = intervalTime;
	#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：等待AT24Cxx写操作的延时时间到达
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_I2C_WaitIdle(AT24CXX_HandleType* AT24CXXx)
{
	#ifdef USE_QUERY_WAIT_IDLE
	//---获取当前时间
	UINT32_T nowTime = 0;
	UINT32_T cnt = 0;
	if (AT24CXXx->msgIntervalTime != 0)
	{
		while (1)
		{
			nowTime = AT24CXXx->msgI2C.pMsgTimeTick();
			//---计算已经过去的时间
			if (nowTime < AT24CXXx->msgRecordTick)
			{
				cnt = (0xFFFFFFFF - AT24CXXx->msgRecordTick + nowTime);
			}
			else
			{
				cnt = nowTime - AT24CXXx->msgRecordTick;
			}
			//---判断时间是否到达
			if (cnt > AT24CXXx->msgIntervalTime)
			{
				///---轮训时间归零处理
				AT24CXXx->msgIntervalTime = 0;
				//---退出循环
				break;
			}
			WDT_RESET();
		}
	}
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
UINT8_T AT24CXX_SWI2C_WriteOneByte(AT24CXX_HandleType *AT24CXXx, UINT16_T addr, UINT8_T val)
{
	UINT8_T _return = OK_0;
	//---保存设备的地址，用于后面恢复
	UINT16_T at24cxxAddr = AT24CXXx->msgI2C.msgAddr;
	//---屏蔽写保护
	#ifdef USE_HW_WP
	if (AT24CXXx->msgWP.msgPort != NULL)
	{
		GPIO_OUT_0(AT24CXXx->msgWP.msgPort, AT24CXXx->msgWP.msgBit);
	}
	#endif
	#ifdef USE_QUERY_WAIT_IDLE
	//---查询方式，等待空闲
	AT24CXX_I2C_WaitIdle(AT24CXXx);
	#endif
	//---检查设备类型
	if (AT24CXXx->msgType > AT24C16)
	{
		//---启动IIC并发送器件地址，写数据
		_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---启动写数据失败
			_return = ERROR_2;
			goto GoToExit;
		}
		//---发送寄存器地址,高地址
		I2CTask_MSW_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(addr >> 8));
		//---读取ACK
		_return = I2CTask_MSW_ReadACK(&(AT24CXXx->msgI2C));
		if (_return != OK_0)
		{
			//---发送数据失败
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	else
	{
		AT24CXXx->msgI2C.msgAddr += (((addr >> 8) << 1) & 0x0F);
		//---启动IIC并发送器件地址，写数据
		_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---启动写数据失败
			_return = ERROR_2;
			goto GoToExit;
		}
	}
	//---发送寄存器地址,低位地址
	I2CTask_MSW_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(addr & 0xFF));
	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(AT24CXXx->msgI2C));
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_3;
		goto GoToExit;
	}
	//---数据发送
	I2CTask_MSW_SendByte(&(AT24CXXx->msgI2C), val);
	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(AT24CXXx->msgI2C));
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_4;
		goto GoToExit;
	}
	//---退出操作入口
GoToExit:
	//---发送停止信号
	I2CTask_MSW_STOP(&(AT24CXXx->msgI2C));
	//---恢复设备的地址
	AT24CXXx->msgI2C.msgAddr = at24cxxAddr;
	//---操作正确，进行延时等待编程结束
	if (_return == OK_0)
	{
		#ifdef USE_QUERY_WAIT_IDLE
		//---设置查询时间
		AT24CXX_I2C_IntervalTime(AT24CXXx, 5);
		#else
		//---自编程时间是5ms
		if (AT24CXXx->pMsgDelayms != NULL)
		{
			AT24CXXx->pMsgDelayms(5);
		}
		#endif
	}	//---使能写保护
	#ifdef USE_HW_WP
	if (AT24CXXx->msgWP.msgPort != NULL)
	{
		GPIO_OUT_1(AT24CXXx->msgWP.msgPort, AT24CXXx->msgWP.msgBit);
	}
	#endif
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_SWI2C_WritePageByte(AT24CXX_HandleType *AT24CXXx, UINT16_T pageAddr, UINT8_T *pVal, UINT16_T length)
{
	//---判断页号和页内的数据
	if (length > AT24CXXx->msgPageByte)
	{
		length = AT24CXXx->msgPageByte;
	}
	UINT8_T _return = OK_0;
	//---保存设备的地址，用于后面恢复
	UINT16_T at24cxxAddr = AT24CXXx->msgI2C.msgAddr;
	UINT16_T i = 0;
	//---屏蔽写保护
	#ifdef USE_HW_WP
	if (AT24CXXx->msgWP.msgPort != NULL)
	{
		GPIO_OUT_0(AT24CXXx->msgWP.msgPort, AT24CXXx->msgWP.msgBit);
	}
	#endif
	#ifdef USE_QUERY_WAIT_IDLE
	//---查询方式，等待空闲
	AT24CXX_I2C_WaitIdle(AT24CXXx);
	#endif
	//---检查设备类型
	if (AT24CXXx->msgType > AT24C16)
	{
		//---启动IIC并发送器件地址，写数据
		_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---启动写数据失败
			_return = ERROR_2;
			goto GoToExit;
		}
		//---发送寄存器地址,高地址
		I2CTask_MSW_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(pageAddr >> 8));
		//---读取ACK
		_return = I2CTask_MSW_ReadACK(&(AT24CXXx->msgI2C));
		if (_return != OK_0)
		{
			//---发送数据失败
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	else
	{
		AT24CXXx->msgI2C.msgAddr += (((pageAddr >> 8) << 1) & 0x0F);
		//---启动IIC并发送器件地址，写数据
		_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---启动写数据失败
			_return = ERROR_2;
			goto GoToExit;
		}
	}
	//---发送寄存器地址,低位地址
	I2CTask_MSW_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(pageAddr & 0xFF));
	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(AT24CXXx->msgI2C));
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_3;
		goto GoToExit;
	}
	//---数据发送
	for (i = 0; i < length; i++)
	{
		I2CTask_MSW_SendByte(&(AT24CXXx->msgI2C), pVal[i]);
		//---读取ACK
		_return = I2CTask_MSW_ReadACK(&(AT24CXXx->msgI2C));
		//---判断正确性
		if (_return != OK_0)
		{
			//---发送数据失败
			_return = ERROR_4;
			goto GoToExit;
		}
	}
	//---退出函数入口
GoToExit:
	//---发送停止信号
	I2CTask_MSW_STOP(&(AT24CXXx->msgI2C));
	//---恢复设备的地址
	AT24CXXx->msgI2C.msgAddr = at24cxxAddr;
	//---操作正确，进行延时等待编程结束
	if (_return == OK_0)
	{
		#ifdef USE_QUERY_WAIT_IDLE
		//---设置查询时间
		AT24CXX_I2C_IntervalTime(AT24CXXx, 5);
		#else
		//---自编程时间是5ms
		if (AT24CXXx->pMsgDelayms != NULL)
		{
			AT24CXXx->pMsgDelayms(5);
		}
		#endif
	}
	#ifdef USE_HW_WP
	//---使能写保护
	if (AT24CXXx->msgWP.msgPort != NULL)
	{
		GPIO_OUT_1(AT24CXXx->msgWP.msgPort, AT24CXXx->msgWP.msgBit);
	}
	#endif
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_SWI2C_WriteData(AT24CXX_HandleType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length)
{
	//---要写的页数
	UINT16_T pageNum = 0;
	//---不满页要写入的字节数
	UINT16_T byteNum = 0;
	//---页地址，即开始页的总数
	UINT16_T pageIndexAddr = addr / (AT24CXXx->msgPageByte);
	//---不满一页的余数
	UINT16_T byteIndexAddr = addr % (AT24CXXx->msgPageByte);
	//---不满一页的数据要写入的字节数
	UINT16_T pageByteNum = AT24CXXx->msgPageByte - byteIndexAddr;
	//---
	UINT16_T i = 0;
	UINT8_T _return = OK_0;
	//---无数据写入或写入的数据为空
	if ((length == 0) || (pVal == NULL))
	{
		return ERROR_6;
	}
	//---数据长度的大小
	if (length <= pageByteNum)
	{
		pageByteNum = length;
	}
	//---当要写入的数据不大于2字节的时候，按页写入和按字节写入消耗的时间基本相同
	if (length < 3)
	{
		//---按字节写入
		for (i = 0; i < length; i++)
		{
			_return = AT24CXX_SWI2C_WriteOneByte(AT24CXXx, addr, *pVal);
			addr++;
			pVal++;
			//---判断是不是写入成功
			if (_return != OK_0)
			{
				return ERROR_7;
			}
		}
	}
	else
	{
		//---按页写入
		#ifndef USE_GOBAL_RAM
		//---申请内存
		UINT8_T* pAT24CxxPageByteBuffer = (UINT8_T*)MyMalloc(AT24CXXx->msgPageByte);
		//---判断缓存空间申请是否成功
		if (pAT24CxxPageByteBuffer == NULL)
		{
			_return = ERROR_8;
			goto GoToExit;
		}
		#endif
		//---先第一页写满，写入的字节数不小于3个字节
		if (pageByteNum != AT24CXXx->msgPageByte)
		{
			//---读取一页的数据
			#ifndef USE_GOBAL_RAM
			_return = AT24CXX_SWI2C_ReadPageByte(AT24CXXx, (pageIndexAddr * (AT24CXXx->msgPageByte)), pAT24CxxPageByteBuffer, (AT24CXXx->msgPageByte));
			#else
			_return = AT24CXX_SWI2C_ReadPageByte(AT24CXXx, (pageIndexAddr * (AT24CXXx->msgAT24CXXPageByte)), AT24CXXx->msgPageByteBuffer, (AT24CXXx->msgAT24CXXPageByte));
			#endif
			//---读取判断
			if (_return != OK_0)
			{
				_return = ERROR_9;
				goto GoToExit;
			}
			//---填充数据
			for (i = 0; i < pageByteNum; i++)
			{
				//---填充数据到缓存区
				#ifndef USE_GOBAL_RAM
				pAT24CxxPageByteBuffer[i + byteIndexAddr] = *pVal;
				#else
				AT24CXXx->msgPageByteBuffer[i + byteIndexAddr] = *pVal;
				#endif
				//---地址偏移，使地址偏移到页的首地址
				addr++;
				//---数据偏移
				pVal++;
				//---数据长度偏移
				length--;
				//---数据填充完成
				if (length == 0)
				{
					//---退出数据的填充
					break;
				}
			}
			//---清零当前页中的字节偏移地址
			byteIndexAddr = 0;
			//---按页写入数据
			#ifndef USE_GOBAL_RAM
			_return = AT24CXX_SWI2C_WritePageByte(AT24CXXx, (pageIndexAddr * (AT24CXXx->msgPageByte)), pAT24CxxPageByteBuffer, AT24CXXx->msgPageByte);
			#else
			_return = AT24CXX_SWI2C_WritePageByte(AT24CXXx, (pageIndexAddr * (AT24CXXx->msgAT24CXXPageByte)), AT24CXXx->msgPageByteBuffer, AT24CXXx->msgAT24CXXPageByte);
			#endif
			//---写入判断
			if (_return != OK_0)
			{
				_return = ERROR_10;
				goto GoToExit;
			}
		}
		//---写整页操作
		//---计算要写入的页数
		pageNum = length / AT24CXXx->msgPageByte;
		//---计算最后一页要写入的字节数
		byteNum = length % AT24CXXx->msgPageByte;
		//---判断是否需要页写入
		if (pageNum != 0)
		{
			for (i = 0; i < pageNum; i++)
			{
				_return = AT24CXX_SWI2C_WritePageByte(AT24CXXx, addr, pVal, AT24CXXx->msgPageByte);
				//---地址偏移，偏移到下次要写入的数据的页的首地址
				addr += AT24CXXx->msgPageByte;
				//---数据偏移
				pVal += AT24CXXx->msgPageByte;
				//---数据长度偏移
				length -= AT24CXXx->msgPageByte;
				//---判断是不是写入成功
				if (_return != OK_0)
				{
					_return = ERROR_11;
					goto GoToExit;
				}
			}
		}
		//---判断是不是不满页的操作
		if (byteNum != 0)
		{
			//---读取一页的数据
			#ifndef USE_GOBAL_RAM
			_return = AT24CXX_SWI2C_ReadPageByte(AT24CXXx, addr, pAT24CxxPageByteBuffer, (AT24CXXx->msgPageByte));
			#else
			_return = AT24CXX_SWI2C_ReadPageByte(AT24CXXx, addr, AT24CXXx->msgPageByteBuffer, (AT24CXXx->msgAT24CXXPageByte));
			#endif
			//---读取判断
			if (_return != OK_0)
			{
				_return = ERROR_12;
				goto GoToExit;
			}
			//---填充数据
			for (i = 0; i < pageByteNum; i++)
			{
				//---填充数据到缓存区
				#ifndef USE_GOBAL_RAM
				pAT24CxxPageByteBuffer[i + byteIndexAddr] = *pVal;
				#else
				AT24CXXx->msgPageByteBuffer[i + byteIndexAddr] = *pVal;
				#endif
				//---地址偏移，此时已经是页的首地址了，不能值继续偏移了
				//addr++;
				//---数据偏移
				pVal++;
				//---数据长度偏移
				length--;
				//---数据填充完成
				if (length == 0)
				{
					//---退出数据的填充
					break;
				}
			}
			//---按页写入数据
			#ifndef USE_GOBAL_RAM
			_return = AT24CXX_SWI2C_WritePageByte(AT24CXXx, addr, pAT24CxxPageByteBuffer, AT24CXXx->msgPageByte);
			#else
			_return = AT24CXX_SWI2C_WritePageByte(AT24CXXx, addr, AT24CXXx->msgPageByteBuffer, AT24CXXx->msgAT24CXXPageByte);
			#endif
			//---写入判断
			if (_return != OK_0)
			{
				_return = ERROR_13;
				goto GoToExit;
			}
		}
		#ifndef USE_GOBAL_RAM
		//---退出函数入口
		GoToExit :
		//---释放内存
		MyFree(pAT24CxxPageByteBuffer);
		#endif
	}
	#ifdef USE_GOBAL_RAM
	GoToExit :
	#endif
	return  _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_HWI2C_WriteOneByte(AT24CXX_HandleType *AT24CXXx, UINT16_T addr, UINT8_T val)
{
	UINT8_T _return = OK_0;
	//---保存设备的地址，用于后面恢复
	UINT16_T at24cxxAddr = AT24CXXx->msgI2C.msgAddr;
	//---屏蔽写保护
	#ifdef USE_HW_WP
	if (AT24CXXx->msgWP.msgPort != NULL)
	{
		GPIO_OUT_0(AT24CXXx->msgWP.msgPort, AT24CXXx->msgWP.msgBit);
	}
	#endif
	#ifdef USE_QUERY_WAIT_IDLE
	//---查询方式，等待空闲
	AT24CXX_I2C_WaitIdle(AT24CXXx);
	#endif
	//---检查设备类型
	if (AT24CXXx->msgType > AT24C16)
	{
		//---启动IIC并发送器件地址，写数据
		_return = I2CTask_MHW_PollMode_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---启动写数据失败
			_return = ERROR_2;
			goto GoToExit;
		}
		//---发送寄存器地址,高地址
		_return = I2CTask_MHW_PollMode_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(addr >> 8), 0);
		if (_return != OK_0)
		{
			//---发送数据失败
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	else
	{
		AT24CXXx->msgI2C.msgAddr += (((addr >> 8) << 1) & 0x0F);
		//---启动IIC并发送器件地址，写数据
		_return = I2CTask_MHW_PollMode_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---启动写数据失败
			_return = ERROR_2;
			goto GoToExit;
		}
	}
	//---发送寄存器地址,低位地址
	_return = I2CTask_MHW_PollMode_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(addr & 0xFF), 0);
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_3;
		goto GoToExit;
	}
	//---数据发送
	_return = I2CTask_MHW_PollMode_SendByte(&(AT24CXXx->msgI2C), val, 1);
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_4;
		goto GoToExit;
	}
	//---退出操作入口
GoToExit:
	//---发送停止信号
	I2CTask_MHW_PollMode_STOP(&(AT24CXXx->msgI2C));
	
	//---恢复设备的地址
	AT24CXXx->msgI2C.msgAddr = at24cxxAddr;
	//---操作正确，进行延时等待编程结束
	if (_return == OK_0)
	{
		#ifdef USE_QUERY_WAIT_IDLE
		//---设置查询时间
		AT24CXX_I2C_IntervalTime(AT24CXXx, 5);
		#else
		//---自编程时间是5ms
		if (AT24CXXx->pMsgDelayms != NULL)
		{
			AT24CXXx->pMsgDelayms(5);
		}
		#endif
	}
	//---使能写保护
	#ifdef USE_HW_WP
	if (AT24CXXx->msgWP.msgPort != NULL)
	{
		GPIO_OUT_1(AT24CXXx->msgWP.msgPort, AT24CXXx->msgWP.msgBit);
	}
	#endif
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_HWI2C_WritePageByte(AT24CXX_HandleType *AT24CXXx, UINT16_T pageAddr, UINT8_T *pVal,UINT16_T length)
{
	//---判断页号和页内的数据
	if (length > AT24CXXx->msgPageByte)
	{
		length = AT24CXXx->msgPageByte;
	}
	UINT8_T _return = OK_0;
	//---保存设备的地址，用于后面恢复
	UINT16_T at24cxxAddr = AT24CXXx->msgI2C.msgAddr;
	UINT16_T i = 0;
	//---屏蔽写保护
	#ifdef USE_HW_WP
	if (AT24CXXx->msgWP.msgPort != NULL)
	{
		GPIO_OUT_0(AT24CXXx->msgWP.msgPort, AT24CXXx->msgWP.msgBit);
	}
	#endif
	#ifdef USE_QUERY_WAIT_IDLE
	//---查询方式，等待空闲
	AT24CXX_I2C_WaitIdle(AT24CXXx);
	#endif
	//---检查设备类型
	if (AT24CXXx->msgType > AT24C16)
	{
		//---启动IIC并发送器件地址，写数据
		_return = I2CTask_MHW_PollMode_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---启动写数据失败
			_return = ERROR_2;
			goto GoToExit;
		}
		//---发送寄存器地址,高地址
		_return = I2CTask_MHW_PollMode_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(pageAddr >> 8), 0);
		if (_return != OK_0)
		{
			//---发送数据失败
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	else
	{
		AT24CXXx->msgI2C.msgAddr += (((pageAddr >> 8) << 1) & 0x0F);
		//---启动IIC并发送器件地址，写数据
		_return = I2CTask_MHW_PollMode_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---启动写数据失败
			_return = ERROR_2;
			goto GoToExit;
		}
	}
	//---发送寄存器地址,低位地址
	_return = I2CTask_MHW_PollMode_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(pageAddr & 0xFF), 0);
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_3;
		goto GoToExit;
	}
	//---数据发送
	for (i = 0; i < length; i++)
	{
		//---发送数据，内部寄存器数据
		_return = I2CTask_MHW_PollMode_SendByte(&(AT24CXXx->msgI2C), pVal[i], ((i == (length - 1)) ? 1 : 0));
		if (_return != OK_0)
		{
			//---发送数据错误
			_return = ERROR_4;
			goto GoToExit;
		}
	}
	//---退出函数入口
GoToExit:
	//---发送停止信号
	I2CTask_MHW_PollMode_STOP(&(AT24CXXx->msgI2C));
	//---恢复设备的地址
	AT24CXXx->msgI2C.msgAddr = at24cxxAddr;
	//---操作正确，进行延时等待编程结束
	if (_return == OK_0)
	{
		#ifdef USE_QUERY_WAIT_IDLE
		//---设置查询时间
		AT24CXX_I2C_IntervalTime(AT24CXXx, 5);
		#else
		//---自编程时间是5ms
		if (AT24CXXx->pMsgDelayms != NULL)
		{
			AT24CXXx->pMsgDelayms(5);
		}
		#endif
	}
	#ifdef USE_HW_WP
	//---使能写保护
	if (AT24CXXx->msgWP.msgPort != NULL)
	{
		GPIO_OUT_1(AT24CXXx->msgWP.msgPort, AT24CXXx->msgWP.msgBit);
	}
	#endif
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_HWI2C_WriteData(AT24CXX_HandleType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length)
{
	//---要写的页数
	UINT16_T pageNum = 0;
	//---不满页要写入的字节数
	UINT16_T byteNum = 0;
	//---页地址，即开始页的总数
	UINT16_T pageIndexAddr = addr / (AT24CXXx->msgPageByte);
	//---不满一页的余数
	UINT16_T byteIndexAddr = addr % (AT24CXXx->msgPageByte);
	//---不满一页的数据要写入的字节数
	UINT16_T pageByteNum = AT24CXXx->msgPageByte - byteIndexAddr;
	//---
	UINT16_T i = 0;
	UINT8_T _return = OK_0;
	//---无数据写入或写入的数据为空
	if ((length == 0) || (pVal == NULL))
	{
		return ERROR_6;
	}
	//---数据长度的大小
	if (length <= pageByteNum)
	{
		pageByteNum = length;
	}
	//---当要写入的数据不大于2字节的时候，按页写入和按字节写入消耗的时间基本相同
	if (length < 3)
	{
		//---按字节写入
		for (i = 0; i < length; i++)
		{
			_return = AT24CXX_HWI2C_WriteOneByte(AT24CXXx, addr, *pVal);
			addr++;
			pVal++;
			//---判断是不是写入成功
			if (_return != OK_0)
			{
				return ERROR_7;
			}
		}
	}
	else
	{
		//---按页写入
		#ifndef USE_GOBAL_RAM
		//---申请内存
		UINT8_T* pAT24CxxPageByteBuffer = (UINT8_T*)MyMalloc(AT24CXXx->msgPageByte);
		//---判断缓存空间申请是否成功
		if (pAT24CxxPageByteBuffer == NULL)
		{
			_return = ERROR_8;
			goto GoToExit;
		}
		#endif
		//---先第一页写满，写入的字节数不小于3个字节
		if (pageByteNum != AT24CXXx->msgPageByte)
		{
			//---读取一页的数据
			#ifndef USE_GOBAL_RAM
			_return = AT24CXX_HWI2C_ReadPageByte(AT24CXXx, (pageIndexAddr * (AT24CXXx->msgPageByte)), pAT24CxxPageByteBuffer, (AT24CXXx->msgPageByte));
			#else
			_return = AT24CXX_HWI2C_ReadPageByte(AT24CXXx, (pageIndexAddr * (AT24CXXx->msgAT24CXXPageByte)), AT24CXXx->msgPageByteBuffer, (AT24CXXx->msgAT24CXXPageByte));
			#endif
			//---读取判断
			if (_return != OK_0)
			{
				_return = ERROR_9;
				goto GoToExit;
			}
			//---填充数据
			for (i = 0; i < pageByteNum; i++)
			{
				//---填充数据到缓存区
				#ifndef USE_GOBAL_RAM
				pAT24CxxPageByteBuffer[i + byteIndexAddr] = *pVal;
				#else
				AT24CXXx->msgPageByteBuffer[i + byteIndexAddr] = *pVal;
				#endif
				//---地址偏移，使地址偏移到页的首地址
				addr++;
				//---数据偏移
				pVal++;
				//---数据长度偏移
				length--;
				//---数据填充完成
				if (length == 0)
				{
					//---退出数据的填充
					break;
				}
			}
			//---清零当前页中的字节偏移地址
			byteIndexAddr = 0;
			//---按页写入数据
			#ifndef USE_GOBAL_RAM
			_return = AT24CXX_HWI2C_WritePageByte(AT24CXXx, (pageIndexAddr * (AT24CXXx->msgPageByte)), pAT24CxxPageByteBuffer, AT24CXXx->msgPageByte);
			#else
			_return = AT24CXX_HWI2C_WritePageByte(AT24CXXx, (pageIndexAddr * (AT24CXXx->msgAT24CXXPageByte)), AT24CXXx->msgPageByteBuffer, AT24CXXx->msgAT24CXXPageByte);
			#endif
			//---写入判断
			if (_return != OK_0)
			{
				_return = ERROR_10;
				goto GoToExit;
			}
		}
		//---写整页操作
		//---计算要写入的页数
		pageNum = length / AT24CXXx->msgPageByte;
		//---计算最后一页要写入的字节数
		byteNum = length % AT24CXXx->msgPageByte;
		//---判断是否需要页写入
		if (pageNum != 0)
		{
			for (i = 0; i < pageNum; i++)
			{
				_return = AT24CXX_HWI2C_WritePageByte(AT24CXXx, addr, pVal, AT24CXXx->msgPageByte);
				//---地址偏移，偏移到下次要写入的数据的页的首地址
				addr += AT24CXXx->msgPageByte;
				//---数据偏移
				pVal += AT24CXXx->msgPageByte;
				//---数据长度偏移
				length -= AT24CXXx->msgPageByte;
				//---判断是不是写入成功
				if (_return != OK_0)
				{
					_return = ERROR_11;
					goto GoToExit;
				}
			}
		}
		//---判断是不是不满页的操作
		if (byteNum != 0)
		{
			//---读取一页的数据
			#ifndef USE_GOBAL_RAM
			_return = AT24CXX_HWI2C_ReadPageByte(AT24CXXx, addr, pAT24CxxPageByteBuffer, (AT24CXXx->msgPageByte));
			#else
			_return = AT24CXX_HWI2C_ReadPageByte(AT24CXXx, addr, AT24CXXx->msgPageByteBuffer, (AT24CXXx->msgAT24CXXPageByte));
			#endif
			//---读取判断
			if (_return != OK_0)
			{
				_return = ERROR_12;
				goto GoToExit;
			}
			//---填充数据
			for (i = 0; i < pageByteNum; i++)
			{
				//---填充数据到缓存区
				#ifndef USE_GOBAL_RAM
				pAT24CxxPageByteBuffer[i + byteIndexAddr] = *pVal;
				#else
				AT24CXXx->msgPageByteBuffer[i + byteIndexAddr] = *pVal;
				#endif
				//---地址偏移，此时已经是页的首地址了，不能值继续偏移了
				//addr++;
				//---数据偏移
				pVal++;
				//---数据长度偏移
				length--;
				//---数据填充完成
				if (length == 0)
				{
					//---退出数据的填充
					break;
				}
			}
			//---按页写入数据
			#ifndef USE_GOBAL_RAM
			_return = AT24CXX_HWI2C_WritePageByte(AT24CXXx, addr, pAT24CxxPageByteBuffer, AT24CXXx->msgPageByte);
			#else
			_return = AT24CXX_HWI2C_WritePageByte(AT24CXXx, addr, AT24CXXx->msgPageByteBuffer, AT24CXXx->msgAT24CXXPageByte);
			#endif
			//---写入判断
			if (_return != OK_0)
			{
				_return = ERROR_13;
				goto GoToExit;
			}
		}
		#ifndef USE_GOBAL_RAM
		//---退出函数入口
		GoToExit :
		//---释放内存
		MyFree(pAT24CxxPageByteBuffer);
		#endif
	}
	#ifdef USE_GOBAL_RAM
	GoToExit :
	#endif
	return  _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_I2C_WriteOneByte(AT24CXX_HandleType *AT24CXXx, UINT16_T addr, UINT8_T val)
{
	if (AT24CXXx->msgI2C.msgHwMode == 0)
	{
		return AT24CXX_SWI2C_WriteOneByte(AT24CXXx, addr, val);
	}
	else
	{
		I2CTask_MHW_CheckClock(&(AT24CXXx->msgI2C));
		//---硬件I2C
		return AT24CXX_HWI2C_WriteOneByte(AT24CXXx, addr, val);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_I2C_WritePageByte(AT24CXX_HandleType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length)
{
	if (AT24CXXx->msgI2C.msgHwMode == 0)
	{
		return AT24CXX_SWI2C_WritePageByte(AT24CXXx, addr, pVal, length);
	}
	else
	{
		I2CTask_MHW_CheckClock(&(AT24CXXx->msgI2C));
		//---硬件I2C
		return AT24CXX_HWI2C_WritePageByte(AT24CXXx, addr, pVal, length);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_I2C_WriteData(AT24CXX_HandleType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length)
{
	if (AT24CXXx->msgI2C.msgHwMode == 0)
	{
		return AT24CXX_SWI2C_WriteData(AT24CXXx, addr, pVal, length);
	}
	else
	{
		I2CTask_MHW_CheckClock(&(AT24CXXx->msgI2C));
		//---硬件I2C
		return AT24CXX_HWI2C_WriteData(AT24CXXx, addr, pVal, length);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：读取寄存器
//////输入参数:
//////输出参数:
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_SWI2C_ReadOneByte(AT24CXX_HandleType *AT24CXXx, UINT16_T addr, UINT8_T *pVal)
{
	UINT8_T _return = OK_0;
	//---保存设备的地址，用于后面恢复
	UINT16_T at24cxxAddr = AT24CXXx->msgI2C.msgAddr;
	//---检查设备类型
	if (AT24CXXx->msgType > AT24C16)
	{
		//---启动IIC并发送器件地址，写数据
		_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---启动写数据失败
			_return = ERROR_2;
			goto GoToExit;
		}
		//---发送寄存器地址,高地址
		I2CTask_MSW_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(addr >> 8));
		//---读取ACK
		_return = I2CTask_MSW_ReadACK(&(AT24CXXx->msgI2C));
		if (_return != OK_0)
		{
			//---发送数据失败
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	else
	{
		AT24CXXx->msgI2C.msgAddr += (((addr >> 8) << 1) & 0x0F);
		//---启动IIC并发送器件地址，写数据
		_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---启动写数据失败
			_return = ERROR_2;
			goto GoToExit;
		}
	}
	//---发送寄存器地址,低位地址
	I2CTask_MSW_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(addr & 0xFF));
	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(AT24CXXx->msgI2C));
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_3;
		goto GoToExit;
	}
	//---启动IIC并发送器件地址，读数据
	_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 0);
	if (_return != OK_0)
	{
		//---启动读数据失败
		_return = ERROR_4;
		goto GoToExit;
	}
	//---读取数据
	*pVal = I2CTask_MSW_ReadByte(&(AT24CXXx->msgI2C));
	//---发送不应答信号
	I2CTask_MSW_SendACK(&(AT24CXXx->msgI2C), 1);
	//---退出函数入口
GoToExit:
	//---发送停止信号
	I2CTask_MSW_STOP(&(AT24CXXx->msgI2C));
	AT24CXXx->msgI2C.msgAddr = at24cxxAddr;
	return _return;
}
///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_SWI2C_ReadPageByte(AT24CXX_HandleType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length)
{
	//---判断页号和页内的数据
	if (length > AT24CXXx->msgPageByte)
	{
		length = AT24CXXx->msgPageByte;
	}
	UINT8_T _return = OK_0;
	//---保存设备的地址，用于后面恢复
	UINT16_T at24cxxAddr = AT24CXXx->msgI2C.msgAddr;
	UINT16_T i = 0;
	//---检查设备类型
	if (AT24CXXx->msgType > AT24C16)
	{
		//---启动IIC并发送器件地址，写数据
		_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---启动写数据失败
			_return = ERROR_2;
			goto GoToExit;
		}
		//---发送寄存器地址,高地址
		I2CTask_MSW_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(addr >> 8));
		//---读取ACK
		_return = I2CTask_MSW_ReadACK(&(AT24CXXx->msgI2C));
		if (_return != OK_0)
		{
			//---发送数据失败
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	else
	{
		AT24CXXx->msgI2C.msgAddr += (((addr >> 8) << 1) & 0x0F);
		//---启动IIC并发送器件地址，写数据
		_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---启动写数据失败
			_return = ERROR_2;
			goto GoToExit;
		}
	}
	//---发送寄存器地址,低位地址
	I2CTask_MSW_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(addr & 0xFF));
	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(AT24CXXx->msgI2C));
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_3;
		goto GoToExit;
	}
	//---启动IIC并发送器件地址，读数据
	_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 0);
	if (_return != OK_0)
	{
		//---启动读数据失败
		_return = ERROR_4;
		goto GoToExit;
	}
	//---循环读取指定长度的数据
	for (i = 0; i < length; i++)
	{
		//---读取数据
		pVal[i] = I2CTask_MSW_ReadByte(&(AT24CXXx->msgI2C));
		//---发送应答信号
		I2CTask_MSW_SendACK(&(AT24CXXx->msgI2C), (i == (length - 1)) ? 1 : 0);
	}
	_return = OK_0;
	//---退出函数入口
GoToExit:
	//---发送停止信号
	I2CTask_MSW_STOP(&(AT24CXXx->msgI2C));
	AT24CXXx->msgI2C.msgAddr = at24cxxAddr;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_SWI2C_ReadData(AT24CXX_HandleType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length)
{
	UINT8_T _return = OK_0;
	//---保存设备的地址，用于后面恢复
	UINT16_T at24cxxAddr = AT24CXXx->msgI2C.msgAddr;
	UINT16_T i = 0;
	//---检查设备类型
	if (AT24CXXx->msgType > AT24C16)
	{
		//---启动IIC并发送器件地址，写数据
		_return = I2CTask_MSW_START(&( AT24CXXx->msgI2C ), 1);
		if (_return != OK_0)
		{
			//---启动写数据失败
			_return = ERROR_2;
			goto GoToExit;
		}
		//---发送寄存器地址,高地址
		I2CTask_MSW_SendByte(&( AT24CXXx->msgI2C ), ( UINT8_T )( addr >> 8 ));
		//---读取ACK
		_return = I2CTask_MSW_ReadACK(&( AT24CXXx->msgI2C ));
		if (_return != OK_0)
		{
			//---发送数据失败
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	else
	{
		AT24CXXx->msgI2C.msgAddr += ( ( ( addr >> 8 ) << 1 ) & 0x0F );
		//---启动IIC并发送器件地址，写数据
		_return = I2CTask_MSW_START(&( AT24CXXx->msgI2C ), 1);
		if (_return != OK_0)
		{
			//---启动写数据失败
			_return = ERROR_2;
			goto GoToExit;
		}
	}
	//---发送寄存器地址,低位地址
	I2CTask_MSW_SendByte(&( AT24CXXx->msgI2C ), ( UINT8_T )( addr & 0xFF ));
	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&( AT24CXXx->msgI2C ));
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_3;
		goto GoToExit;
	}
	//---启动IIC并发送器件地址，读数据
	_return = I2CTask_MSW_START(&( AT24CXXx->msgI2C ), 0);
	if (_return != OK_0)
	{
		//---启动读数据失败
		_return = ERROR_4;
		goto GoToExit;
	}
	//---循环读取指定长度的数据
	for (i = 0; i < length; i++)
	{
		//---读取数据
		pVal[i] = I2CTask_MSW_ReadByte(&( AT24CXXx->msgI2C ));
		//---发送应答信号
		I2CTask_MSW_SendACK(&( AT24CXXx->msgI2C ), (i == (length - 1)) ? 1 : 0);
	}
	_return = OK_0;
	//---退出函数的入口
GoToExit:
	//---发送停止信号
	I2CTask_MSW_STOP(&( AT24CXXx->msgI2C ));
	AT24CXXx->msgI2C.msgAddr = at24cxxAddr;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_HWI2C_ReadOneByte(AT24CXX_HandleType *AT24CXXx, UINT16_T addr, UINT8_T *pVal)
{
	UINT8_T _return = OK_0;
	//---保存设备的地址，用于后面恢复
	UINT16_T at24cxxAddr = AT24CXXx->msgI2C.msgAddr;
	//---检查设备类型
	if (AT24CXXx->msgType > AT24C16)
	{
		//---启动IIC并发送器件地址，写数据
		_return = I2CTask_MHW_PollMode_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---启动写数据失败
			_return = ERROR_2;
			goto GoToExit;
		}
		//---发送寄存器地址,高地址
		_return = I2CTask_MHW_PollMode_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(addr >> 8),0);
		if (_return != OK_0)
		{
			//---发送数据失败
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	else
	{
		AT24CXXx->msgI2C.msgAddr += (((addr >> 8) << 1) & 0x0F);
		//---启动IIC并发送器件地址，写数据
		_return = I2CTask_MHW_PollMode_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---启动写数据失败
			_return = ERROR_2;
			goto GoToExit;
		}
	}
	//---发送寄存器地址,低位地址
	_return = I2CTask_MHW_PollMode_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(addr & 0xFF),0);
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_3;
		goto GoToExit;
	}
	//---启动IIC并发送器件地址，读数据
	_return = I2CTask_MHW_PollMode_START(&(AT24CXXx->msgI2C), 0);
	if (_return != OK_0)
	{
		//---启动读数据失败
		_return = ERROR_4;
		goto GoToExit;
	}
	//---发送不应答信号
	_return = I2CTask_MHW_SendACK(&(AT24CXXx->msgI2C), 1);
	//---读取数据
	*pVal = I2CTask_MHW_PollMode_ReadByte(&(AT24CXXx->msgI2C));
	//---退出函数入口
GoToExit:
	//---发送停止信号
	I2CTask_MHW_PollMode_STOP(&(AT24CXXx->msgI2C));
	AT24CXXx->msgI2C.msgAddr = at24cxxAddr;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_HWI2C_ReadPageByte(AT24CXX_HandleType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length)
{
	//---判断页号和页内的数据
	if (length > AT24CXXx->msgPageByte)
	{
		length = AT24CXXx->msgPageByte;
	}
	UINT8_T _return = OK_0;
	//---保存设备的地址，用于后面恢复
	UINT16_T at24cxxAddr = AT24CXXx->msgI2C.msgAddr;
	UINT16_T i = 0;
	//---检查设备类型
	if (AT24CXXx->msgType > AT24C16)
	{
		//---启动IIC并发送器件地址，写数据
		_return = I2CTask_MHW_PollMode_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---启动写数据失败
			_return = ERROR_2;
			goto GoToExit;
		}
		//---发送寄存器地址,高地址
		_return = I2CTask_MHW_PollMode_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(addr >> 8),0);
		if (_return != OK_0)
		{
			//---发送数据失败
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	else
	{
		AT24CXXx->msgI2C.msgAddr += (((addr >> 8) << 1) & 0x0F);
		//---启动IIC并发送器件地址，写数据
		_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---启动写数据失败
			_return = ERROR_2;
			goto GoToExit;
		}
	}
	//---发送寄存器地址,低位地址
	_return = I2CTask_MHW_PollMode_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(addr & 0xFF),0);
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_3;
		goto GoToExit;
	}
	//---启动IIC并发送器件地址，读数据
	_return = I2CTask_MHW_PollMode_START(&(AT24CXXx->msgI2C), 0);
	if (_return != OK_0)
	{
		//---启动读数据失败
		_return = ERROR_4;
		goto GoToExit;
	}
	//---循环读取指定长度的数据
	for (i = 0; i < length; i++)
	{
		//---发送应答信号
		I2CTask_MHW_SendACK(&(AT24CXXx->msgI2C), (i == (length - 1)) ? 1 : 0);
		//---读取数据
		pVal[i] = I2CTask_MHW_PollMode_ReadByte(&(AT24CXXx->msgI2C));
	}
	_return = OK_0;
	//---退出函数入口
GoToExit:
	//---发送停止信号
	I2CTask_MHW_PollMode_STOP(&(AT24CXXx->msgI2C));
	AT24CXXx->msgI2C.msgAddr = at24cxxAddr;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_HWI2C_ReadData(AT24CXX_HandleType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length)
{
	UINT8_T _return = OK_0;
	//---保存设备的地址，用于后面恢复
	UINT16_T at24cxxAddr = AT24CXXx->msgI2C.msgAddr;
	UINT16_T i = 0;
	//---检查设备类型
	if (AT24CXXx->msgType > AT24C16)
	{
		//---启动IIC并发送器件地址，写数据
		_return = I2CTask_MHW_PollMode_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---启动写数据失败
			_return = ERROR_2;
			goto GoToExit;
		}
		//---发送寄存器地址,高地址
		_return = I2CTask_MHW_PollMode_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(addr >> 8),0);
		if (_return != OK_0)
		{
			//---发送数据失败
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	else
	{
		AT24CXXx->msgI2C.msgAddr += (((addr >> 8) << 1) & 0x0F);
		//---启动IIC并发送器件地址，写数据
		_return = I2CTask_MHW_PollMode_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---启动写数据失败
			_return = ERROR_2;
			goto GoToExit;
		}
	}
	//---发送寄存器地址,低位地址
	_return = I2CTask_MHW_PollMode_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(addr & 0xFF),0);
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_3;
		goto GoToExit;
	}
	//---启动IIC并发送器件地址，读数据
	_return = I2CTask_MHW_PollMode_START(&(AT24CXXx->msgI2C), 0);
	if (_return != OK_0)
	{
		//---启动读数据失败
		_return = ERROR_4;
		goto GoToExit;
	}
	//---循环读取指定长度的数据
	for (i = 0; i < length; i++)
	{
		//---发送应答信号
		I2CTask_MHW_SendACK(&(AT24CXXx->msgI2C), (i == (length - 1)) ? 1 : 0);
		//---读取数据
		pVal[i] = I2CTask_MHW_PollMode_ReadByte(&(AT24CXXx->msgI2C));
	}
	_return = OK_0;
	//---退出函数的入口
GoToExit:
	//---发送停止信号
	I2CTask_MHW_PollMode_STOP(&(AT24CXXx->msgI2C));
	AT24CXXx->msgI2C.msgAddr = at24cxxAddr;
	return _return;
}
///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_I2C_ReadOneByte(AT24CXX_HandleType *AT24CXXx, UINT16_T addr, UINT8_T *pVal)
{
	if (AT24CXXx->msgI2C.msgHwMode == 0)
	{
		return AT24CXX_SWI2C_ReadOneByte(AT24CXXx, addr, pVal);
	}
	else
	{
		I2CTask_MHW_CheckClock(&(AT24CXXx->msgI2C));
		//---硬件I2C
		return AT24CXX_HWI2C_ReadOneByte(AT24CXXx, addr, pVal);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_I2C_ReadPageByte(AT24CXX_HandleType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length)
{
	if (AT24CXXx->msgI2C.msgHwMode == 0)
	{
		return AT24CXX_SWI2C_ReadPageByte(AT24CXXx, addr, pVal, length);
	}
	else
	{
		I2CTask_MHW_CheckClock(&(AT24CXXx->msgI2C));
		//---硬件I2C
		return AT24CXX_HWI2C_ReadPageByte(AT24CXXx, addr, pVal, length);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_I2C_ReadData(AT24CXX_HandleType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length)
{
	if (AT24CXXx->msgI2C.msgHwMode == 0)
	{
		return AT24CXX_SWI2C_ReadData(AT24CXXx, addr, pVal, length);
	}
	else
	{
		I2CTask_MHW_CheckClock(&(AT24CXXx->msgI2C));
		//---硬件I2C
		return AT24CXX_HWI2C_ReadData(AT24CXXx, addr, pVal, length);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 全芯片擦除操作
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_I2C_EraseChip(AT24CXX_HandleType *AT24CXXx)
{
	UINT8_T _return = OK_0;
	UINT16_T i = 0;
	UINT16_T addr = 0;
	//---申请内存
	#ifndef USE_GOBAL_RAM
	//---申请内存
	UINT8_T* pAT24CxxPageByteBuffer = (UINT8_T*)MyMalloc(AT24CXXx->msgPageByte);
	//---判断缓存空间申请是否成功
	if (pAT24CxxPageByteBuffer == NULL)
	{
		_return = ERROR_8;
		goto GoToExit;
	}
	#endif
	//---填充缓存区
	for (i = 0; i < AT24CXXx->msgPageByte; i++)
	{
		#ifndef USE_GOBAL_RAM
		* pAT24CxxPageByteBuffer = 0xFF;
		pAT24CxxPageByteBuffer++;
		#else
		AT24CXXx->msgPageByteBuffer[i] = 0xFF;
		#endif
	}
	#ifndef USE_GOBAL_RAM
	pAT24CxxPageByteBuffer -= AT24CXXx->msgPageByte;
	#endif
	//---擦除数据
	for (i = 0; i < AT24CXXx->msgPageNum; i++)
	{
		//---按页写入数据
		#ifndef USE_GOBAL_RAM
		_return = AT24CXX_I2C_WritePageByte(AT24CXXx, addr, pAT24CxxPageByteBuffer, AT24CXXx->msgPageByte);
		#else
		_return = AT24CXX_I2C_WritePageByte(AT24CXXx, addr, AT24CXXx->msgPageByteBuffer, AT24CXXx->msgAT24CXXPageByte);
		#endif
		//---地址增加
		addr += AT24CXXx->msgPageByte;
		//---判断写入是否成功
		if (_return != OK_0)
		{
			_return = ERROR_7;
			goto GoToExit;
		}
	}
	//---退出函数入口
GoToExit:
	#ifndef USE_GOBAL_RAM
	//---释放内存
	MyFree(pAT24CxxPageByteBuffer);
	#endif
	return _return;
}
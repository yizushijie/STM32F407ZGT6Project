#include "ads869x_cfg.h"

//===全局变量定义
ADS869X_HandleType   g_ADS869XDevice0 = { 0 };
pADS869X_HandleType  pADS869XDevice0 = &g_ADS869XDevice0;

//===统一发送字节命令
UINT8_T(*ADS869X_SPI_SEND_CMD)(ADS869X_HandleType *, UINT8_T, UINT8_T *);
//===统一发送数组命令
UINT8_T(*ADS869X_SPI_SEND_ARRAY)(ADS869X_HandleType*, UINT8_T*, UINT8_T*,UINT16_T);

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void ADS869X_SPI_Device0_Init(ADS869X_HandleType *ADS869x)
{
	//---复位信号
	ADS869x->msgHWRST.msgPort = NULL;
	ADS869x->msgHWRST.msgBit = LL_GPIO_PIN_0;
	//---GPIO时钟使能
	#ifndef  USE_FULL_GPIO
	if (ADS869x->msgHWRST.msgPort != NULL)
	{
		GPIOTask_Clock(ADS869x->msgHWRST.msgPort, PERIPHERAL_CLOCK_ENABLE);
	}
	#endif
	//---SPI1接口
	//---PA4------ > SPI1_NSS
	//---PA5------ > SPI1_SCK
	//---PA6------ > SPI1_MISO
	//---PA7------ > SPI1_MOSI
	
	//---SPI2接口
	//---PB12------ > SPI2_NSS
	//---PB13------ > SPI2_SCK
	//---PB14------ > SPI2_MISO
	//---PB15------ > SPI2_MOSI

	//---CS
	ADS869x->msgSPI.msgCS.msgPort = GPIOB;				//GPIOA;
	ADS869x->msgSPI.msgCS.msgBit  = LL_GPIO_PIN_12;		//LL_GPIO_PIN_4;
	//---SCK
	ADS869x->msgSPI.msgSCK.msgPort = GPIOB;				//GPIOA;
	ADS869x->msgSPI.msgSCK.msgBit = LL_GPIO_PIN_13;		//LL_GPIO_PIN_5;
	//---MISO  SDO
	ADS869x->msgSPI.msgMISO.msgPort = GPIOB;			//GPIOA;
	ADS869x->msgSPI.msgMISO.msgBit  = LL_GPIO_PIN_14;	//LL_GPIO_PIN_6;
	//---MOSI SDI
	ADS869x->msgSPI.msgMOSI.msgPort = GPIOB;			//GPIOA;
	ADS869x->msgSPI.msgMOSI.msgBit  = LL_GPIO_PIN_15;	//LL_GPIO_PIN_7;
	//---GPIO的配置
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	//---GPIO的初始化
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;														//---配置状态为输出模式
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;											//---GPIO的速度
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;											//---输出模式---推挽输出
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;															//---上拉使能
	//---初始化RST
	if (ADS869x->msgHWRST.msgPort != NULL)
	{
		GPIO_InitStruct.Pin = ADS869x->msgHWRST.msgBit;
		GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
		LL_GPIO_Init(ADS869x->msgHWRST.msgPort, &GPIO_InitStruct);
		GPIO_OUT_1(ADS869x->msgHWRST.msgPort, ADS869x->msgHWRST.msgBit);
	}
	//---复用模式
	#ifndef USE_MCU_STM32F1
		//---端口复用模式
		ADS869x->msgSPI.msgGPIOAlternate = LL_GPIO_AF_5;
	#endif
	//---SPI序号
		ADS869x->msgSPI.pMsgSPIx = SPI2;//SPI1;
	#ifndef USE_MCU_STM32F1
		//---SPI的协议
		ADS869x->msgSPI.msgStandard = LL_SPI_PROTOCOL_MOTOROLA;
	#endif
	UINT8_T i = 0;
	//---参考电压配置
	ADS869x->msgREFPowerUV = ADS869X_REF_POWER_UV;
	for (i = 0; i < ADS869X_CHANNEL_MAX; i++)
	{
		ADS869x->msgChannelRange[i] = 0;
		ADS869x->msgPositive[i] = 0;
		ADS869x->msgChannelNowADCResult[i] = 0;
		ADS869x->msgChannelOldADCResult[i] = 0;
		ADS869x->msgChannelPowerResult[i] = 0;
		ADS869X_SPI_ChannelRange(ADS869x, i);
	}
	ADS869x->msgReadyOK = 0;
	ADS869x->msgInitRetryCount = 3;
	ADS869x->msgChipID = 0;
	//---默认配置特性
	ADS869x->msgFeature = 0x28;
	//---默认是0xFF
	ADS869x->msgAutoSeqEn = 0xFF;
	//---定义脉冲宽度
	ADS869x->msgSPI.msgPluseWidth = 2;
	//---时钟空闲为低电平
	ADS869x->msgSPI.msgCPOL = 0;
	//---数据采样在第二个时钟边沿
	ADS869x->msgSPI.msgCPOH = 1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void ADS869X_SPI_Device1_Init(ADS869X_HandleType *ADS869x)
{
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void ADS869X_SPI_Device2_Init(ADS869X_HandleType *ADS869x)
{
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：发送字节命令
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_SW_SendCmd(ADS869X_HandleType *ADS869x, UINT8_T cmd, UINT8_T *pRVal)
{
	//---数据发送
	return SPITask_MSW_WriteAndReadByteMSB(&(ADS869x->msgSPI), cmd, pRVal);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：发送数组命令
//////输入参数：
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_SW_SendArray(ADS869X_HandleType* ADS869x, UINT8_T* pWVal, UINT8_T* pRVal, UINT16_T length)
{
	//---数据发送
	return SPITask_MSW_WriteAndReadDataMSB(&(ADS869x->msgSPI), pWVal, pRVal, length);
}
///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：发送字节命令
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_HW_SendCmd(ADS869X_HandleType *ADS869x, UINT8_T cmd, UINT8_T *pRVal)
{
	//---数据发送
	return SPITask_MHW_PollMode_WriteAndReadByte(&(ADS869x->msgSPI), cmd, pRVal);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：发送数组命令
//////输入参数：
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_HW_SendArray(ADS869X_HandleType* ADS869x, UINT8_T *pWVal, UINT8_T* pRVal,UINT16_T length)
{
	//---数据发送
	return SPITask_MHW_PollMode_WriteAndReadData(&(ADS869x->msgSPI), pWVal, pRVal,length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_HW_Init(ADS869X_HandleType *ADS869x)
{
	//---硬件端口的配置---硬件实现
	SPITask_MHW_GPIO_Init(&(ADS869x->msgSPI));
	//---硬件SPI的初始化
	LL_SPI_InitTypeDef SPI_InitStruct = {0};
	//---SPI的模式配置
	SPI_InitStruct.TransferDirection = LL_SPI_FULL_DUPLEX;
	SPI_InitStruct.Mode = LL_SPI_MODE_MASTER;						//---主机模式
	SPI_InitStruct.DataWidth = LL_SPI_DATAWIDTH_8BIT;				//---8位数据
	//---时钟极性的设置
	if (ADS869x->msgSPI.msgCPOL == 0)
	{
		//---CLK空闲时为低电平 (CLK空闲是只能是低电平)
		SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_LOW;
		GPIO_OUT_0(ADS869x->msgSPI.msgSCK.msgPort, ADS869x->msgSPI.msgSCK.msgBit);
	}
	else
	{
		//---CLK空闲时为高电平 (CLK空闲是只能是低电平)
		SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_HIGH;
	}
	//---数据采样的时钟边沿位置
	if (ADS869x->msgSPI.msgCPOH ==0)
	{
		SPI_InitStruct.ClockPhase = LL_SPI_PHASE_1EDGE;
	}
	else
	{
		SPI_InitStruct.ClockPhase = LL_SPI_PHASE_2EDGE;
	}
	SPI_InitStruct.NSS = LL_SPI_NSS_SOFT;							//---软件控制
	SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV2;		//---系统时钟2分频
	SPI_InitStruct.BitOrder = LL_SPI_MSB_FIRST;						//---高位在前
	SPI_InitStruct.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;	//---硬件CRC不使能
	SPI_InitStruct.CRCPoly = 7;
	//---初始化查询方式的SPI
	SPITask_MHW_PollMode_Init(&(ADS869x->msgSPI), SPI_InitStruct);
	//---命令发送函数
	ADS869X_SPI_SEND_CMD = ADS869X_SPI_HW_SendCmd;
	ADS869X_SPI_SEND_ARRAY = ADS869X_SPI_HW_SendArray;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_SW_Init(ADS869X_HandleType *ADS869x)
{
	//---硬件端口的配置---软件实现
	SPITask_MSW_GPIO_Init(&(ADS869x->msgSPI));
	//---时钟线的极性
	if (ADS869x->msgSPI.msgCPOL == 0)
	{
		GPIO_OUT_0(ADS869x->msgSPI.msgSCK.msgPort, ADS869x->msgSPI.msgSCK.msgBit);
	}
	else
	{
		GPIO_OUT_1(ADS869x->msgSPI.msgSCK.msgPort, ADS869x->msgSPI.msgSCK.msgBit);
	}
	//---命令发送函数
	ADS869X_SPI_SEND_CMD = ADS869X_SPI_SW_SendCmd;
	ADS869X_SPI_SEND_ARRAY = ADS869X_SPI_SW_SendArray;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_Init(ADS869X_HandleType *ADS869x, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHW)
{
	//---使用的DHT11的端口
	if ((ADS869x != NULL) && (ADS869x == ADS869X_TASK_ONE))
	{
		ADS869X_SPI_Device0_Init(ADS869x);
	}
	else if ((ADS869x != NULL) && (ADS869x == ADS869X_TASK_TWO))
	{
		ADS869X_SPI_Device1_Init(ADS869x);
	}
	else if ((ADS869x != NULL) && (ADS869x == ADS869X_TASK_THREE))
	{
		ADS869X_SPI_Device2_Init(ADS869x);
	}
	else
	{
		return ERROR_1;
	}
	//---判断硬件函数软件方式
	(isHW != 0) ? (ADS869X_SPI_HW_Init(ADS869x)) : (ADS869X_SPI_SW_Init(ADS869x));
	//---注册ms延时时间
	(pFuncDelayms != NULL) ? (ADS869x->pMsgDelayms = pFuncDelayms) : (ADS869x->pMsgDelayms = DelayTask_ms);
	//---注册us延时函数
	(pFuncDelayus != NULL) ? (ADS869x->msgSPI.pMsgDelayus = pFuncDelayus) : (ADS869x->msgSPI.pMsgDelayus = DelayTask_us);
	//---注册滴答函数
	(pFuncTimerTick != NULL) ? (ADS869x->msgSPI.pMsgTimeTick = pFuncTimerTick) : (ADS869x->msgSPI.pMsgTimeTick = SysTickTask_GetTick);
	//---配置ADS869X
	return ADS869X_SPI_ConfigInit(ADS869x,0);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：自动初始化，避免同一个SPI端口挂载多个设备，速度不一致的问题
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_AutoInit(ADS869X_HandleType* ADS869x)
{
	if (ADS869x->msgSPI.msgHwMode != 0)
	{
		//---软件初始化
		ADS869X_SPI_HW_Init(ADS869x);
	}
	else
	{
		//---硬件初始化
		ADS869X_SPI_SW_Init(ADS869x);
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：自动注销
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_AutoDeInit(ADS869X_HandleType* ADS869x)
{
	//---注销当前的所有配置
  return	SPITask_DeInit(&(ADS869x->msgSPI),0);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：写ADS869X命令寄存器
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_WriteCommandReg(ADS869X_HandleType *ADS869x, UINT32_T cmd)
{
	UINT8_T _return = OK_0;
	UINT8_T wTemp[2] = { 0 };
	wTemp[0] = (UINT8_T)((cmd >> 8)&0xFF);
	wTemp[1] = (UINT8_T)(cmd & 0xFF);
	if (ADS869x->msgSPI.msgCS.msgPort != NULL)
	{
		GPIO_OUT_0(ADS869x->msgSPI.msgCS.msgPort, ADS869x->msgSPI.msgCS.msgBit);
	}
	_return = ADS869X_SPI_SEND_ARRAY(ADS869x, wTemp, NULL, 2);
	if (ADS869x->msgSPI.msgCS.msgPort != NULL)
	{
		GPIO_OUT_1(ADS869x->msgSPI.msgCS.msgPort, ADS869x->msgSPI.msgCS.msgBit);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：Program Register写操作
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_WriteProgramReg(ADS869X_HandleType *ADS869x, UINT8_T addr, UINT8_T val)
{
	UINT8_T _return = OK_0;
	UINT8_T wTemp[2] = { 0 };
	wTemp[0] = (addr << 1) | 0x01;
	wTemp[1] = val;
	if (ADS869x->msgSPI.msgCS.msgPort != NULL)
	{
		GPIO_OUT_0(ADS869x->msgSPI.msgCS.msgPort, ADS869x->msgSPI.msgCS.msgBit);
	}
	_return = ADS869X_SPI_SEND_ARRAY(ADS869x, wTemp, NULL, 2);
	if (ADS869x->msgSPI.msgCS.msgPort != NULL)
	{
		GPIO_OUT_1(ADS869x->msgSPI.msgCS.msgPort, ADS869x->msgSPI.msgCS.msgBit);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：Program Register读操作
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_ReadProgramReg(ADS869X_HandleType *ADS869x, UINT8_T addr, UINT8_T *pVal)
{
	UINT8_T _return = OK_0;
	UINT8_T wTemp[3] = { 0 };
	UINT8_T rTemp[3] = { 0 };
	wTemp[0] = (addr << 1) & 0xFE;
	if (ADS869x->msgSPI.msgCS.msgPort != NULL)
	{
		GPIO_OUT_0(ADS869x->msgSPI.msgCS.msgPort, ADS869x->msgSPI.msgCS.msgBit);
	}
	_return = ADS869X_SPI_SEND_ARRAY(ADS869x, wTemp, rTemp, 3);
	if (ADS869x->msgSPI.msgCS.msgPort != NULL)
	{
		GPIO_OUT_1(ADS869x->msgSPI.msgCS.msgPort, ADS869x->msgSPI.msgCS.msgBit);
	}

	//---数据拷贝
	pVal[0] = rTemp[1];
	pVal[1] = rTemp[2];

	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读命令返回
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_ReadCommandBack(ADS869X_HandleType* ADS869x, UINT8_T* pVal,UINT8_T isAutoInit)
{
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}
	_return=ADS869X_SPI_ReadProgramReg(ADS869x, ADS869X_CMD_READ_BACK, pVal);

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功	    能：继续工作在选中的状态
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_NO_OP(ADS869X_HandleType* ADS869x, UINT8_T isAutoInit)
{
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}
	_return = ADS869X_SPI_WriteCommandReg(ADS869x, ADS869X_CMD_REG_NO_OP);

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功	    能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_STDBY(ADS869X_HandleType* ADS869x, UINT8_T isAutoInit)
{
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}
	_return = ADS869X_SPI_WriteCommandReg(ADS869x, ADS869X_CMD_REG_STDBY);
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}
	return _return;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功	    能：
//////输入参数:
//////输出参数:
//////说		明：退出此模式需执行AUTO_RST或者MAN_CH_n命令，且需要等待至少20us以保证正常数据的AD转换
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_PWRDN(ADS869X_HandleType* ADS869x, UINT8_T isAutoInit)
{
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}

	_return = ADS869X_SPI_WriteCommandReg(ADS869x, ADS869X_CMD_REG_PWR_DN);

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：硬件复位设备
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T  ADS869X_SPI_HardReset(ADS869X_HandleType *ADS869x)
{
	if (ADS869x->msgHWRST.msgPort!=NULL)
	{
		GPIO_OUT_0(ADS869x->msgHWRST.msgPort, ADS869x->msgHWRST.msgBit);
		ADS869x->pMsgDelayms(1);
		GPIO_OUT_1(ADS869x->msgHWRST.msgPort, ADS869x->msgHWRST.msgBit);
		ADS869x->pMsgDelayms(1);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：软件复位设备
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T  ADS869X_SPI_SoftReset(ADS869X_HandleType *ADS869x, UINT8_T isAutoInit)
{
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}

	_return = ADS869X_SPI_WriteCommandReg(ADS869x, ADS869X_CMD_REG_RST);
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功	    能：设备复位
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_Reset(ADS869X_HandleType* ADS869x, UINT8_T isAutoInit)
{
	UINT8_T _return = OK_0;
	if (ADS869x->msgHWRST.msgPort != NULL)
	{
		_return = ADS869X_SPI_HardReset(ADS869x);
	}
	else
	{
		_return = ADS869X_SPI_SoftReset(ADS869x,isAutoInit);
	}
	ADS869x->msgReadyOK = 0;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：进入自动扫描模式
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_AUTORST(ADS869X_HandleType* ADS869x, UINT8_T isAutoInit)
{
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}

	_return = ADS869X_SPI_WriteCommandReg(ADS869x, ADS869X_CMD_REG_AUTO_RST);

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}
	return _return;

}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功	    能：设置手动扫描通道
//////输入参数:
//////输出参数:
//////说		明：退出此模式需执行AUTO_RST或者MAN_CH_n命令，且需要等待至少20us以保证正常数据的AD转换
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_ManualChannel(ADS869X_HandleType* ADS869x,UINT16_T manualCHCmd, UINT8_T isAutoInit)
{
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}

	_return = ADS869X_SPI_WriteCommandReg(ADS869x, manualCHCmd);

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功	    能：设置设备ID
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_WriteChipID(ADS869X_HandleType* ADS869x, UINT8_T devid, UINT8_T isAutoInit)
{
	devid <<= 6;
	ADS869x->msgChipID = (devid & 0xC0) | ADS869x->msgFeature; 
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}

	_return = ADS869X_SPI_WriteProgramReg(ADS869x, ADS869X_PROG_REG_FEATURE_SELECT, ADS869x->msgChipID);

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功	    能：读取设备ID
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_ReadChipID(ADS869X_HandleType* ADS869x, UINT8_T *pDevID, UINT8_T isAutoInit)
{
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}
	_return = ADS869X_SPI_ReadProgramReg(ADS869x, ADS869X_PROG_REG_FEATURE_SELECT, pDevID);
	*pDevID &= 0xC0;

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功	    能：校验设备ID
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_CheckChipID(ADS869X_HandleType* ADS869x, UINT8_T isAutoInit)
{
	UINT8_T tempChipID = 0x00;
	UINT8_T _return = OK_0;
	_return = ADS869X_SPI_ReadChipID(ADS869x, &tempChipID,isAutoInit);
	//---校验读取的ID信息
	if (tempChipID!=ADS869x->msgChipID)
	{
		_return += ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功	    能：探测设备是否存在
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_DetectionDevice(ADS869X_HandleType* ADS869x, UINT8_T isAutoInit)
{
	UINT8_T tempAutoSeqEn[2] = { 0 };
	UINT8_T _return = OK_0;

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}

	_return=ADS869X_SPI_ReadProgramReg(pADS869XDevice0, ADS869X_PROG_REG_AUTO_SEQ_EN, tempAutoSeqEn);
	//---校验结果是否正确
	if (tempAutoSeqEn[1]!=ADS869x->msgAutoSeqEn)
	{
		_return += ERROR_1;
	}
	else
	{
		//---校验设备的ID信息
		_return = ADS869X_SPI_CheckChipID(ADS869x,0);
	}

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}

	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置自动扫描序列通道
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_WriteAUTOSEQEN(ADS869X_HandleType* ADS869x, UINT8_T seq, UINT8_T isAutoInit)
{
	ADS869x->msgAutoSeqEn = seq;
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}
	_return = ADS869X_SPI_WriteProgramReg(ADS869x, ADS869X_PROG_REG_AUTO_SEQ_EN, seq);

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取自动扫描序列通道
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_ReadAUTOSEQEN(ADS869X_HandleType* ADS869x, UINT8_T *pAutoSeqEn, UINT8_T isAutoInit)
{
	UINT8_T tempAutoSeqEn[2] = { 0 };
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}
	_return =ADS869X_SPI_ReadProgramReg(ADS869x, ADS869X_PROG_REG_AUTO_SEQ_EN, tempAutoSeqEn);
	if (_return==OK_0)
	{
		if (tempAutoSeqEn[1]==ADS869x->msgAutoSeqEn)
		{
			*pAutoSeqEn = tempAutoSeqEn[1];
		}
		else
		{
			_return = ERROR_2;
		}
	}

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}

	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：通道掉电模式设置
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_WriteChannelPWRDN(ADS869X_HandleType* ADS869x, UINT8_T ch, UINT8_T isAutoInit)
{
	ADS869x->msgChannelPWRDN = ch; 
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}
	_return = ADS869X_SPI_WriteProgramReg(ADS869x, ADS869X_PROG_REG_CH_PWR_DN, ch);

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}

	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：通道掉电模式读取
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_ReadChannelPWRDN(ADS869X_HandleType* ADS869x, UINT8_T *pPWRDN, UINT8_T isAutoInit)
{
	UINT8_T tempPWRDN[2] = { 0 }; 
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}
	_return = ADS869X_SPI_ReadProgramReg(ADS869x, ADS869X_PROG_REG_CH_PWR_DN, tempPWRDN);
	if (_return == OK_0)
	{
		if (tempPWRDN[1] == ADS869x->msgChannelPWRDN)
		{
			*pPWRDN = tempPWRDN[1];
		}
		else
		{
			_return = ERROR_2;
		}
	}

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}

	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：通道掉电模式设置
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_WriteFeature(ADS869X_HandleType* ADS869x, UINT8_T feature, UINT8_T isAutoInit)
{
	ADS869x->msgFeature = (feature&0x3F)|ADS869x->msgChipID;
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}
	_return = ADS869X_SPI_WriteProgramReg(ADS869x, ADS869X_PROG_REG_FEATURE_SELECT, feature);
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}

	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：通道掉电模式读取
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_ReadFeature(ADS869X_HandleType* ADS869x, UINT8_T *pFeature, UINT8_T isAutoInit)
{
	UINT8_T tempFeature[2] = { 0 };
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}
	_return = ADS869X_SPI_ReadProgramReg(ADS869x, ADS869X_PROG_REG_FEATURE_SELECT, tempFeature);
	if (_return == OK_0)
	{
		if (tempFeature[1] == ADS869x->msgFeature)
		{
			*pFeature = tempFeature[1];
		}
		else
		{
			_return = ERROR_2;
		}
	}

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}

	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置通道的量程范围
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_WriteChannelRange(ADS869X_HandleType* ADS869x, UINT8_T chReg, UINT8_T range, UINT8_T isAutoInit)
{
	UINT8_T ch = ADS869X_CHANNEL_MAX;
	switch (chReg)
	{
		case ADS869X_PROG_REG_CH0_SET_RANGE:
			ADS869x->msgChannelRange[0] = range;
			ch = 0;
			break;
		case ADS869X_PROG_REG_CH1_SET_RANGE:
			ADS869x->msgChannelRange[1] = range;
			ch = 1;
			break;
		case ADS869X_PROG_REG_CH2_SET_RANGE:
			ADS869x->msgChannelRange[2] = range;
			ch = 2;
			break;
		case ADS869X_PROG_REG_CH3_SET_RANGE:
			ADS869x->msgChannelRange[3] = range;
			ch = 3;
			break;
		case ADS869X_PROG_REG_CH4_SET_RANGE:
			ADS869x->msgChannelRange[4] = range;
			ch = 4;
			break;
		case ADS869X_PROG_REG_CH5_SET_RANGE:
			ADS869x->msgChannelRange[5] = range;
			ch = 5;
			break;
		case ADS869X_PROG_REG_CH6_SET_RANGE:
			ADS869x->msgChannelRange[6] = range;
			ch = 6;
			break;
		case ADS869X_PROG_REG_CH7_SET_RANGE:
			ADS869x->msgChannelRange[7] = range;
			ch = 7;
			break;
		default:
			return ERROR_1;
	}

	//---每个通道的量程的配置
	ADS869X_SPI_ChannelRange(ADS869x, ch);
	//---设置通道的量程
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}
	_return = ADS869X_SPI_WriteProgramReg(ADS869x, chReg, range);

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}

	return _return;

}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置通道的量程范围
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_ReadChannelRange(ADS869X_HandleType* ADS869x, UINT8_T chReg, UINT8_T *pRange, UINT8_T isAutoInit)
{
	UINT8_T ch = ADS869X_CHANNEL_MAX;
	UINT8_T tempChannelRange[2] = { 0 };
	UINT8_T _return = OK_0;
	switch (chReg)
	{
		case ADS869X_PROG_REG_CH0_SET_RANGE:
			ch = 0;
			break;
		case ADS869X_PROG_REG_CH1_SET_RANGE:
			ch = 1;
			break;
		case ADS869X_PROG_REG_CH2_SET_RANGE:
			ch = 2;
			break;
		case ADS869X_PROG_REG_CH3_SET_RANGE:
			ch = 3;
			break;
		case ADS869X_PROG_REG_CH4_SET_RANGE:
			ch = 4;
			break;
		case ADS869X_PROG_REG_CH5_SET_RANGE:
			ch = 5;
			break;
		case ADS869X_PROG_REG_CH6_SET_RANGE:
			ch = 6;
			break;
		case ADS869X_PROG_REG_CH7_SET_RANGE:
			ch = 7;
			break;
		default:
			return ERROR_1;
	}
	//---读取通道的量程
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}
	_return = ADS869X_SPI_ReadProgramReg(ADS869x, chReg, tempChannelRange);
	//---判断读取结果
	if (_return == OK_0)
	{
		if (tempChannelRange[1] == ADS869x->msgChannelRange[ch])
		{
			*pRange = tempChannelRange[1];
		}
		else
		{
			_return = ERROR_2;
		}
	}
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}

	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置参考电压uv
//////输入参数：
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_WriteREFPowerUV(ADS869X_HandleType* ADS869x, UINT32_T refUV)
{
	ADS869x->msgREFPowerUV = refUV;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取参考电压
//////输入参数：
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT32_T ADS869X_SPI_ReadREFPowerUV(ADS869X_HandleType* ADS869x, UINT32_T refUV)
{
	return ADS869x->msgREFPowerUV;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置参考电压mv
//////输入参数：
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_WriteREFPowerMV(ADS869X_HandleType* ADS869x, UINT32_T refMV)
{
	ADS869x->msgREFPowerUV = refMV*1000;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置每通道的量程和量程最大值
//////输入参数：
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_ChannelRange(ADS869X_HandleType* ADS869x, UINT8_T chIndex)
{
	UINT8_T _return = OK_0;
	if (chIndex==ADS869X_CHANNEL_MAX)
	{
		_return = ERROR_1;
	}
	else
	{
		switch (ADS869x->msgChannelRange[chIndex])
		{
			//---正负1.25倍的VREF
			case ADS869X_RANGE_5120MV_5120MV:
				ADS869x->msgChannelRangeIsPositive[chIndex] = 0;
				ADS869x->msgChannelRangeFullUVX1000[chIndex] = ((UINT64_T)ADS869x->msgREFPowerUV * 1250);//5120000000;
				ADS869x->msgChannelRangeBaseUVX1000[chIndex] = (ADS869x->msgChannelRangeFullUVX1000[chIndex] * 2) / (1<< ADS869X_ADC_SAMPLE_BITS); //39.0625;
				break;
			//---正负0.625倍的VREF
			case ADS869X_RANGE_2560MV_2560MV:
				ADS869x->msgChannelRangeIsPositive[chIndex] = 0;
				ADS869x->msgChannelRangeFullUVX1000[chIndex] = ((UINT64_T)ADS869x->msgREFPowerUV * 625); //2560000000;
				ADS869x->msgChannelRangeBaseUVX1000[chIndex] = (ADS869x->msgChannelRangeFullUVX1000[chIndex] * 2) / (1 << ADS869X_ADC_SAMPLE_BITS); //19.53125;
				break;
			//---正2.5倍的VREF
			case ADS869X_RANGE_0MV_10240MV:
				ADS869x->msgChannelRangeIsPositive[chIndex] = 1;
				ADS869x->msgChannelRangeFullUVX1000[chIndex] = ((UINT64_T)ADS869x->msgREFPowerUV * 2500);//10240000000;
				ADS869x->msgChannelRangeBaseUVX1000[chIndex] = ADS869x->msgChannelRangeFullUVX1000[chIndex] / (1 << ADS869X_ADC_SAMPLE_BITS); //39.0625;
				break;
			//---正1.25倍的VREF
			case ADS869X_RANGE_0MV_5120MV:
				ADS869x->msgChannelRangeIsPositive[chIndex] = 1;
				ADS869x->msgChannelRangeFullUVX1000[chIndex] = ((UINT64_T)ADS869x->msgREFPowerUV* 1250);//5120000000;
				ADS869x->msgChannelRangeBaseUVX1000[chIndex] = ADS869x->msgChannelRangeFullUVX1000[chIndex] / (1 << ADS869X_ADC_SAMPLE_BITS); //19.53125;
				break;
			//---正负2.5倍的VREF
			case ADS869X_RANGE_10240MV_10240MV:
			default:
				ADS869x->msgChannelRangeIsPositive[chIndex] = 0;
				ADS869x->msgChannelRangeFullUVX1000[chIndex] = ((UINT64_T)ADS869x->msgREFPowerUV * 2500);//10240000000;
				ADS869x->msgChannelRangeBaseUVX1000[chIndex] = (ADS869x->msgChannelRangeFullUVX1000[chIndex] * 2) / (1 << ADS869X_ADC_SAMPLE_BITS); //78.125
				break;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：通过ADC的采集结果计算ADC通道的电压值
//////输入参数：
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_CalcChannelPower(ADS869X_HandleType* ADS869x, UINT8_T chIndex,UINT8_T isCalcDelta)
{
	//---设置无数据
	ADS869x->msgPositive[chIndex] = 0;
	UINT32_T adcDelta = 0;
	UINT64_T calcPower = 0;
	//---判断是否需要计算差值
	if (isCalcDelta != 0)
	{
		//---获取上次和本次的采样结果的绝对差值
		adcDelta = ABS_SUB(ADS869x->msgChannelNowADCResult[chIndex], ADS869x->msgChannelOldADCResult[chIndex]);
		//---软件数据补偿拟合开始
		if (adcDelta < 15)
		{
			if (adcDelta>5)
			{
				ADS869x->msgChannelOldADCResult[chIndex] = MAX(ADS869x->msgChannelNowADCResult[chIndex], ADS869x->msgChannelOldADCResult[chIndex])-2;
			}
			else if (ADS869x->msgChannelNowADCResult[chIndex] > ADS869x->msgChannelOldADCResult[chIndex])
			{
				ADS869x->msgChannelOldADCResult[chIndex] = ADS869x->msgChannelNowADCResult[chIndex];
				if(adcDelta>2)
				{
					ADS869x->msgChannelOldADCResult[chIndex] -=2;
				}
			}
			else if (ADS869x->msgChannelNowADCResult[chIndex] < ADS869x->msgChannelOldADCResult[chIndex])
			{
				ADS869x->msgChannelOldADCResult[chIndex] -= 1;
			}
			else
			{
				ADS869x->msgChannelOldADCResult[chIndex] = MAX(ADS869x->msgChannelNowADCResult[chIndex], ADS869x->msgChannelOldADCResult[chIndex]);
			}
			calcPower = ADS869x->msgChannelOldADCResult[chIndex];
		}
		else
		{
			calcPower = ADS869x->msgChannelNowADCResult[chIndex];
			ADS869x->msgChannelOldADCResult[chIndex] = ADS869x->msgChannelNowADCResult[chIndex];
		}
	}
	else
	{
		calcPower = ADS869x->msgChannelNowADCResult[chIndex];
	}
	calcPower &= ((1<< ADS869X_ADC_SAMPLE_BITS)-1);
	//---软件数据补偿拟合结束
	//---将数字量转换为模拟量
	calcPower *= ADS869x->msgChannelRangeBaseUVX1000[chIndex];
	double adcPower = 0;
	//---判断ADC采样的量程是双极性还是单极性
	if (ADS869x->msgChannelRangeIsPositive[chIndex] == 0)
	{
		if ((ADS869x->msgChannelNowADCResult[chIndex] & (1<< (ADS869X_ADC_SAMPLE_BITS-1))) != 0)
		{
			ADS869x->msgPositive[chIndex] = 2;
			ADS869x->msgChannelPowerResult[chIndex] = (UINT32_T)((calcPower - ADS869x->msgChannelRangeFullUVX1000[chIndex]) / 1000);
		}
		else
		{
			ADS869x->msgPositive[chIndex] = 1;
			ADS869x->msgChannelPowerResult[chIndex] = (UINT32_T)((ADS869x->msgChannelRangeFullUVX1000[chIndex] - calcPower) / 1000);
		}
	}
	else
	{
		ADS869x->msgPositive[chIndex] = 2;
		ADS869x->msgChannelPowerResult[chIndex] = (UINT32_T)(calcPower / 1000);
	}
	//---误差消除计算
	if (ADS869x->msgADCKP[chIndex] != 0)
	{
		adcPower = ADS869x->msgChannelPowerResult[chIndex];
		adcPower *= ADS869x->msgADCKP[chIndex];
		if (adcPower< ADS869x->msgADCDelta[chIndex])
		{
			ADS869x->msgPositive[chIndex] = 1;
			adcPower = (ADS869x->msgADCDelta[chIndex] - adcPower);
		}
		else
		{
			adcPower -= ADS869x->msgADCDelta[chIndex];
		}
		ADS869x->msgChannelPowerResult[chIndex] = (UINT32_T)adcPower;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取自动扫描通道序列的AD转换数据
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_GetAutoRSTResult(ADS869X_HandleType *ADS869x, UINT8_T chNum, UINT8_T isAutoInit)
{
	UINT8_T i = 0;
	UINT8_T adcRTemp[5] = { 0 };
	UINT8_T adcWTemp[5] = { 0 };
	UINT8_T _return = 0;
	UINT8_T rstMode = ADS869x->msgAutoSeqEn;

	//---读取通道的量程
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}

	//---判断设备是否初始化成功
	if (ADS869x->msgReadyOK == 1)
	{
		_return = ADS869X_SPI_ConfigInit(ADS869x,0);
		if (_return != OK_0)
		{
			goto GoToExit;
		}
	}

	//---进入自动扫描模式
	_return =ADS869X_SPI_AUTORST(ADS869x,0);

	//---扫描通道的结果
	for (i = 0; i < chNum; i++)
	{
		//---判断是否使能自动RST扫描功能
		if (rstMode & 0x01)
		{
			adcWTemp[3] = i;
			//---准备读取数据
			if (ADS869x->msgSPI.msgCS.msgPort != NULL)
			{
				GPIO_OUT_0(ADS869x->msgSPI.msgCS.msgPort, ADS869x->msgSPI.msgCS.msgBit);
			}
			_return=ADS869X_SPI_SEND_ARRAY(ADS869x, adcWTemp, adcRTemp, 5);
			//---结束数据的读取
			if (ADS869x->msgSPI.msgCS.msgPort != NULL)
			{
				GPIO_OUT_1(ADS869x->msgSPI.msgCS.msgPort, ADS869x->msgSPI.msgCS.msgBit);
			}
			//---保存读取的数据
			ADS869x->msgChannelNowADCResult[i] = adcRTemp[2];
			ADS869x->msgChannelNowADCResult[i] = (ADS869x->msgChannelNowADCResult[i] << 8) + adcRTemp[3];
			ADS869x->msgChannelNowADCResult[i] = (ADS869x->msgChannelNowADCResult[i] << 8) + adcRTemp[4];
			ADS869x->msgChannelNowADCResult[i] >>= ADS869X_DATA_SAMPLE_BITS;
			//---计算采样结果
			ADS869X_SPI_CalcChannelPower(ADS869x, i,0);
		}
		rstMode >>= 1;
	}
GoToExit:
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}
	return  _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功	    能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_GetAutoRSTNSampleResult(ADS869X_HandleType* ADS869x, UINT8_T chNum, UINT8_T isAutoInit)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	UINT8_T j = 0;
	UINT8_T rstMode = ADS869x->msgAutoSeqEn;
	//---保存采样结果
	UINT32_T adcSampleTemp[ADS869X_CHANNEL_MAX][ADS869X_N_SAMPLE_COUNT] = { 0 };

	//---读取通道的量程
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}

	//---获取采样结果
	for (i = 0; i < ADS869X_N_SAMPLE_COUNT; i++)
	{
		//---获取采样结果
		_return = ADS869X_SPI_GetAutoRSTResult(ADS869x, chNum,0);
		//---采样数据搬移
		for (j=0;j< ADS869X_CHANNEL_MAX;j++)
		{
			adcSampleTemp[j][i] = ADS869x->msgChannelNowADCResult[j];
		}
		//---校验数据
		if (_return != OK_0)
		{
			break;
		}
	}
	if (_return == OK_0)
	{
		//---采样数据搬移
		for (j = 0; j < ADS869X_CHANNEL_MAX; j++)
		{
			//---判断是否使能自动RST扫描功能
			if (rstMode & 0x01)
			{
				//---升序排列数据
				AscSortDoubleWord(adcSampleTemp[j], ADS869X_N_SAMPLE_COUNT);
				//---计算均值
				ADS869x->msgChannelNowADCResult[j] = CalcAvgDoubleWordFromIndex(adcSampleTemp[j], (ADS869X_N_SAMPLE_COUNT - 2), 2);
				//---计算采样的电压值
				ADS869X_SPI_CalcChannelPower(ADS869x, j,1);
			}
			rstMode >>= 1;
		}
	}

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}

	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功	    能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_KalmanFilterGetAutoRSTNSampleResult(ADS869X_HandleType* ADS869x, UINT8_T chNum, UINT8_T isAutoInit)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	UINT8_T j = 0;
	UINT8_T rstMode = ADS869x->msgAutoSeqEn;
	//---保存采样结果
	UINT32_T adcSampleTemp[ADS869X_CHANNEL_MAX][ADS869X_N_SAMPLE_COUNT] = { 0 };

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}

	//---卡尔曼结构
	KalmanOneFilter_HandleType kalmanFilterX;
	//---获取采样结果
	for (i = 0; i < ADS869X_N_SAMPLE_COUNT; i++)
	{
		//---获取采样结果
		_return = ADS869X_SPI_GetAutoRSTResult(ADS869x, chNum,0);
		//---采样数据搬移
		for (j = 0; j < ADS869X_CHANNEL_MAX; j++)
		{
			adcSampleTemp[j][i] = ADS869x->msgChannelNowADCResult[j];
		}
		//---校验数据
		if (_return != OK_0)
		{
			break;
		}
	}
	if (_return == OK_0)
	{
		//---采样数据搬移
		for (j = 0; j < ADS869X_CHANNEL_MAX; j++)
		{
			//---判断是否使能自动RST扫描功能
			if (rstMode & 0x01)
			{
				KalmanOneFilter_Init(&kalmanFilterX, adcSampleTemp[j][0], 5e2);
				for (i = 1; i < ADS869X_N_SAMPLE_COUNT; i++)
				{
					//---卡尔曼滤波之后的结果
					ADS869x->msgChannelNowADCResult[j] = (UINT32_T)KalmanOneFilter_Filter(&kalmanFilterX, adcSampleTemp[j][i]);
				}
				//---计算采样的电压值
				ADS869X_SPI_CalcChannelPower(ADS869x, j, 0);
			}
			rstMode >>= 1;
		}
	}
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功	    能：获取收到扫描通道的值
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T  ADS869X_SPI_GetManualChannelResult(ADS869X_HandleType* ADS869x, UINT16_T manualChannel, UINT8_T isAutoInit)
{
	UINT8_T _return = OK_0;
	UINT8_T adcRTemp[5] = { 0 };
	UINT8_T adcWTemp[5] = { 0 };
	UINT8_T adcChannel = 0;

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}

	//---判断设备是否初始化成功
	if (ADS869x->msgReadyOK==1)
	{
		_return=ADS869X_SPI_ConfigInit(ADS869x,0);
		if (_return!=OK_0)
		{
			goto GoToExit;
		}
	}
	//---设置手动扫描通道
	_return = ADS869X_SPI_ManualChannel(ADS869x, manualChannel,0);
	//---准备读取设置的扫描通道的值
	if (ADS869x->msgSPI.msgCS.msgPort != NULL)
	{
		GPIO_OUT_0(ADS869x->msgSPI.msgCS.msgPort, ADS869x->msgSPI.msgCS.msgBit);
	}
	//---读取ADC采样的结果
	_return = ADS869X_SPI_SEND_ARRAY(ADS869x, adcWTemp, adcRTemp, 5);
	//---结束读取设置的扫描通道的值
	if (ADS869x->msgSPI.msgCS.msgPort != NULL)
	{
		GPIO_OUT_1(ADS869x->msgSPI.msgCS.msgPort, ADS869x->msgSPI.msgCS.msgBit);
	}
	//---通道的转换
	adcChannel = (UINT8_T)(manualChannel >> 10) & 0x0F;
	//---判断是否是AUX通道配置
	if (adcChannel<8)
	{
		ADS869x->msgChannelNowADCResult[adcChannel] = adcRTemp[2];
		ADS869x->msgChannelNowADCResult[adcChannel] = (ADS869x->msgChannelNowADCResult[adcChannel] << 8) + adcRTemp[3];
		ADS869x->msgChannelNowADCResult[adcChannel] = (ADS869x->msgChannelNowADCResult[adcChannel] << 8) + adcRTemp[4];
		ADS869x->msgChannelNowADCResult[adcChannel] >>= ADS869X_DATA_SAMPLE_BITS;
		//---计算采样结果
		ADS869X_SPI_CalcChannelPower(ADS869x, adcChannel,0);
	}
GoToExit:
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}

	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功	    能：手动通道采样N次的测试结果
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_GetManualChannelNSampleResult(ADS869X_HandleType* ADS869x, UINT16_T manualChannel, UINT8_T isAutoInit)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---保存采样结果
	UINT32_T adcSampleTemp[ADS869X_N_SAMPLE_COUNT] = { 0 };
	//---获取ADC采样通道的序号
	UINT8_T adcChannelIndex = (UINT8_T)(manualChannel >> 10) & 0x0F;

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}

	//---获取采样结果
	for ( i = 0; i < ADS869X_N_SAMPLE_COUNT; i++)
	{
		_return = ADS869X_SPI_GetManualChannelResult(ADS869x, manualChannel,0);
		adcSampleTemp[i] = ADS869x->msgChannelNowADCResult[adcChannelIndex];
		if (_return!=OK_0)
		{
			break;
		}
	}
	if (_return==OK_0)
	{
		//---升序排列数据
		AscSortDoubleWord(adcSampleTemp, ADS869X_N_SAMPLE_COUNT);
		//---计算均值
		ADS869x->msgChannelNowADCResult[adcChannelIndex] = CalcAvgDoubleWordFromIndex(adcSampleTemp, (ADS869X_N_SAMPLE_COUNT - 4), 4);
		//---计算采样的电压值
		ADS869X_SPI_CalcChannelPower(ADS869x, adcChannelIndex,1);
	}
	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}


	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功	    能：卡尔曼滤波方式计算数据
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_KalmanFilterGetManualChannelNSampleResult(ADS869X_HandleType* ADS869x, UINT16_T manualChannel, UINT8_T isAutoInit)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---保存采样结果
	UINT32_T adcSampleTemp[ADS869X_N_SAMPLE_COUNT] = { 0 };
	//---获取ADC采样通道的序号
	UINT8_T adcChannelIndex = (UINT8_T)(manualChannel >> 10) & 0x0F;
	//---卡尔曼结构
	KalmanOneFilter_HandleType kalmanFilterX;

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}

	//---获取采样结果
	for (i = 0; i < ADS869X_N_SAMPLE_COUNT; i++)
	{
		_return = ADS869X_SPI_GetManualChannelResult(ADS869x, manualChannel,0);
		adcSampleTemp[i] = ADS869x->msgChannelNowADCResult[adcChannelIndex];
		if (_return != OK_0)
		{
			break;
		}
	}
	if (_return == OK_0)
	{
		KalmanOneFilter_Init(&kalmanFilterX, adcSampleTemp[0], 5e2);
		for (i=1;i< ADS869X_N_SAMPLE_COUNT; i++)
		{
			//---卡尔曼滤波之后的结果
			ADS869x->msgChannelNowADCResult[adcChannelIndex] =(UINT32_T) KalmanOneFilter_Filter(&kalmanFilterX, adcSampleTemp[i]);
		}
		//---计算采样的电压值
		ADS869X_SPI_CalcChannelPower(ADS869x, adcChannelIndex, 1);
	}

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}

	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功	    能：校准通道的误差
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_CalibrationChannelErr(ADS869X_HandleType* ADS869x)
{
	UINT8_T i = 0;
	UINT8_T rstMode = ADS869x->msgAutoSeqEn;
	for (i = 0; i < ADS869X_CHANNEL_MAX; i++)
	{
		if ((rstMode&0x01)==0)
		{
			if (i==0)
			{
				////---1号板参数
				//ADS869x->msgADCKP[i] = 1.013216;
				//ADS869x->msgADCDelta[i] = 27130;

				//---2号板参数
				ADS869x->msgADCKP[i] = 0;//1.013216;
				ADS869x->msgADCDelta[i] = 26430;
			}
			else
			{
				////---1号板参数
				//ADS869x->msgADCKP[i] = 1.0129;
				//ADS869x->msgADCDelta[i] = 25870;

				//---2号板参数
				ADS869x->msgADCKP[i] = 0;//1.0129;
				ADS869x->msgADCDelta[i] = 27070;
			}
			
		}
		rstMode >>= 1;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功	    能：初始化配置
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS869X_SPI_ConfigInit(ADS869X_HandleType* ADS869x,UINT8_T isAutoInit)
{
	UINT8_T _return = OK_0;
	UINT8_T tempBuffer[3] = { 0 };
	UINT8_T i = 0;

	if (isAutoInit!=0)
	{
		ADS869X_SPI_AutoInit(ADS869x);
	}

	if (ADS869x->msgInitRetryCount==0)
	{
		ADS869x->msgInitRetryCount = 1;
	}

	//---循环多次初始化设备
	for (i=0;i< ADS869x->msgInitRetryCount;i++)
	{
		//---复位芯片
		_return = ADS869X_SPI_Reset(ADS869x,0);
		//---校验
		if (_return == OK_0)
		{
			//---设备特征配置
			_return = ADS869X_SPI_WriteFeature(ADS869x, 0x28,0);
			//---校验
			if (_return == OK_0)
			{
				//---读取设备的特征
				_return = ADS869X_SPI_ReadFeature(ADS869x, tempBuffer,0);
				//---校验
				if (_return == OK_0)
				{
					break;
				}
			}
		}
	}

	//---设置扫描方式
	_return = ADS869X_SPI_WriteAUTOSEQEN(ADS869x, 0xF0,0);
	//---读取设置的值
	_return = ADS869X_SPI_ReadProgramReg(ADS869x, ADS869X_PROG_REG_AUTO_SEQ_EN, tempBuffer);

	//---判断校验
	if (ADS869x->msgAutoSeqEn != tempBuffer[1])
	{
		_return = ERROR_1;
		ADS869x->msgReadyOK = 1;
	}
	else
	{
		//---设置通道的量程
		ADS869X_SPI_WriteChannelRange(ADS869x, ADS869X_PROG_REG_CH0_SET_RANGE, ADS869X_RANGE_0MV_5120MV,0);
		ADS869X_SPI_WriteChannelRange(ADS869x, ADS869X_PROG_REG_CH1_SET_RANGE, ADS869X_RANGE_0MV_5120MV,0);
		ADS869X_SPI_WriteChannelRange(ADS869x, ADS869X_PROG_REG_CH2_SET_RANGE, ADS869X_RANGE_0MV_5120MV,0);
		//---设置工作模式
		ADS869X_SPI_AUTORST(ADS869x,0);
	}
	ADS869X_SPI_CalibrationChannelErr(ADS869x);

	if (isAutoInit != 0)
	{
		ADS869X_SPI_AutoDeInit(ADS869x);
	}

	return _return;
}
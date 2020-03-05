#include "ADS868X_cfg.h"

//===全局变量定义
ADS868X_HandleType   g_ADS868XDevice0 = { 0 };
pADS868X_HandleType  pADS868XDevice0 = &g_ADS868XDevice0;

//===统一发送字节命令
UINT8_T(*ADS868X_SPI_SEND_CMD)(ADS868X_HandleType *, UINT8_T, UINT8_T *);
//===统一发送数组命令
UINT8_T(*ADS868X_SPI_SEND_ARRAY)(ADS868X_HandleType*, UINT8_T*, UINT8_T*,UINT16_T);

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void ADS868X_SPI_Device0_Init(ADS868X_HandleType *ADS868x)
{
	//---复位信号
	ADS868x->msgHWRST.msgPort = NULL;
	ADS868x->msgHWRST.msgBit = LL_GPIO_PIN_0;
	#ifndef  USE_FULL_GPIO
	//---GPIO时钟使能
	if (ADS868x->msgHWRST.msgPort != NULL)
	{
		GPIOTask_Clock(ADS868x->msgHWRST.msgPort, PERIPHERAL_CLOCK_ENABLE);
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
	ADS868x->msgSPI.msgCS.msgPort = GPIOA;
	ADS868x->msgSPI.msgCS.msgBit = LL_GPIO_PIN_4;
	//---SCK
	ADS868x->msgSPI.msgSCK.msgPort = GPIOA;
	ADS868x->msgSPI.msgSCK.msgBit = LL_GPIO_PIN_5;
	//---MISO  SD0
	ADS868x->msgSPI.msgMISO.msgPort = GPIOA;
	ADS868x->msgSPI.msgMISO.msgBit = LL_GPIO_PIN_6;
	//---MOSI SDI
	ADS868x->msgSPI.msgMOSI.msgPort = GPIOA;
	ADS868x->msgSPI.msgMOSI.msgBit = LL_GPIO_PIN_7;
	//---GPIO的配置
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	//---GPIO的初始化
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;														//---配置状态为输出模式
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;											//---GPIO的速度
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;											//---输出模式---推挽输出
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;															//---上拉使能
	//---初始化RST
	if (ADS868x->msgHWRST.msgPort != NULL)
	{
		GPIO_InitStruct.Pin = ADS868x->msgHWRST.msgBit;
		GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
		LL_GPIO_Init(ADS868x->msgHWRST.msgPort, &GPIO_InitStruct);
		GPIO_OUT_1(ADS868x->msgHWRST.msgPort, ADS868x->msgHWRST.msgBit);
	}
	//---复用模式
	#ifndef USE_MCU_STM32F1
		//---端口复用模式
		ADS868x->msgSPI.msgGPIOAlternate = LL_GPIO_AF_5;
	#endif
	//---SPI序号
	ADS868x->msgSPI.pMsgSPIx = SPI1;
	#ifndef USE_MCU_STM32F1
		//---SPI的协议
		ADS868x->msgSPI.msgStandard = LL_SPI_PROTOCOL_MOTOROLA;
	#endif
	UINT8_T i = 0;
	//---参考电压配置
	ADS868x->msgREFPowerUV = ADS868X_REF_POWER_UV;
	for (i = 0; i < ADS868X_CHANNEL_MAX; i++)
	{
		ADS868x->msgChannelRange[i] = 0;
		ADS868x->msgPositive[i] = 0;
		ADS868x->msgChannelNowADCResult[i] = 0;
		ADS868x->msgChannelOldADCResult[i] = 0;
		ADS868x->msgChannelPowerResult[i] = 0;
		ADS868X_SPI_ChannelRange(ADS868x, i);
	}
	ADS868x->msgReadyOK = 0;
	ADS868x->msgInitRetryCount = 3;
	ADS868x->msgChipID = 0;
	//---默认配置特性
	ADS868x->msgFeature = 0x28;
	//---默认是0xFF
	ADS868x->msgAutoSeqEn = 0xFF;
	//---定义脉冲宽度
	ADS868x->msgSPI.msgPluseWidth = 2;
	//---时钟空闲为低电平
	ADS868x->msgSPI.msgCPOL = 0;
	//---数据采样在第二个时钟边沿
	ADS868x->msgSPI.msgCPOH = 1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void ADS868X_SPI_Device1_Init(ADS868X_HandleType *ADS868x)
{
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void ADS868X_SPI_Device2_Init(ADS868X_HandleType *ADS868x)
{
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：发送字节命令
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_SW_SendCmd(ADS868X_HandleType *ADS868x, UINT8_T cmd, UINT8_T *pRVal)
{
	//---数据发送
	return SPITask_MSW_WriteAndReadByteMSB(&(ADS868x->msgSPI), cmd, pRVal);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：发送数组命令
//////输入参数：
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_SW_SendArray(ADS868X_HandleType* ADS868x, UINT8_T* pWVal, UINT8_T* pRVal, UINT16_T length)
{
	//---数据发送
	return SPITask_MSW_WriteAndReadDataMSB(&(ADS868x->msgSPI), pWVal, pRVal, length);
}
///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：发送字节命令
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_HW_SendCmd(ADS868X_HandleType *ADS868x, UINT8_T cmd, UINT8_T *pRVal)
{
	//---数据发送
	return SPITask_MHW_PollMode_WriteAndReadByte(&(ADS868x->msgSPI), cmd, pRVal);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：发送数组命令
//////输入参数：
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_HW_SendArray(ADS868X_HandleType* ADS868x, UINT8_T *pWVal, UINT8_T* pRVal,UINT16_T length)
{
	//---数据发送
	return SPITask_MHW_PollMode_WriteAndReadData(&(ADS868x->msgSPI), pWVal, pRVal,length);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_HW_Init(ADS868X_HandleType *ADS868x)
{
	//---硬件端口的配置---硬件实现
	SPITask_MHW_GPIO_Init(&(ADS868x->msgSPI));
	//---硬件SPI的初始化
	LL_SPI_InitTypeDef SPI_InitStruct = {0};
	//---SPI的模式配置
	SPI_InitStruct.TransferDirection = LL_SPI_FULL_DUPLEX;
	SPI_InitStruct.Mode = LL_SPI_MODE_MASTER;						//---主机模式
	SPI_InitStruct.DataWidth = LL_SPI_DATAWIDTH_8BIT;				//---8位数据
	//---时钟极性的设置
	if (ADS868x->msgSPI.msgCPOL == 0)
	{
		//---CLK空闲时为低电平 (CLK空闲是只能是低电平)
		SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_LOW;
		GPIO_OUT_0(ADS868x->msgSPI.msgSCK.msgPort, ADS868x->msgSPI.msgSCK.msgBit);
	}
	else
	{
		//---CLK空闲时为高电平 (CLK空闲是只能是低电平)
		SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_HIGH;
	}
	//---数据采样的时钟边沿位置
	if (ADS868x->msgSPI.msgCPOH ==0)
	{
		SPI_InitStruct.ClockPhase = LL_SPI_PHASE_1EDGE;
	}
	else
	{
		SPI_InitStruct.ClockPhase = LL_SPI_PHASE_2EDGE;
	}
	SPI_InitStruct.NSS = LL_SPI_NSS_SOFT;							//---软件控制
	SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV2;		//---系统时钟4分频
	SPI_InitStruct.BitOrder = LL_SPI_MSB_FIRST;						//---高位在前
	SPI_InitStruct.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;	//---硬件CRC不使能
	SPI_InitStruct.CRCPoly = 7;
	//---初始化查询方式的SPI
	SPITask_MHW_PollMode_Init(&(ADS868x->msgSPI), SPI_InitStruct);
	//---命令发送函数
	ADS868X_SPI_SEND_CMD = ADS868X_SPI_HW_SendCmd;
	ADS868X_SPI_SEND_ARRAY = ADS868X_SPI_HW_SendArray;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_SW_Init(ADS868X_HandleType *ADS868x)
{
	//---硬件端口的配置---软件实现
	SPITask_MSW_GPIO_Init(&(ADS868x->msgSPI));
	//---时钟线的极性
	if (ADS868x->msgSPI.msgCPOL == 0)
	{
		GPIO_OUT_0(ADS868x->msgSPI.msgSCK.msgPort, ADS868x->msgSPI.msgSCK.msgBit);
	}
	else
	{
		GPIO_OUT_1(ADS868x->msgSPI.msgSCK.msgPort, ADS868x->msgSPI.msgSCK.msgBit);
	}
	//---命令发送函数
	ADS868X_SPI_SEND_CMD = ADS868X_SPI_SW_SendCmd;
	ADS868X_SPI_SEND_ARRAY = ADS868X_SPI_SW_SendArray;
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_Init(ADS868X_HandleType *ADS868x, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHW)
{
	//---使用的DHT11的端口
	if ((ADS868x != NULL) && (ADS868x == ADS868X_TASK_ONE))
	{
		ADS868X_SPI_Device0_Init(ADS868x);
	}
	else if ((ADS868x != NULL) && (ADS868x == ADS868X_TASK_TWO))
	{
		ADS868X_SPI_Device1_Init(ADS868x);
	}
	else if ((ADS868x != NULL) && (ADS868x == ADS868X_TASK_THREE))
	{
		ADS868X_SPI_Device2_Init(ADS868x);
	}
	else
	{
		return ERROR_1;
	}
	//---判断硬件函数软件方式
	(isHW != 0) ? (ADS868X_SPI_HW_Init(ADS868x)) : (ADS868X_SPI_SW_Init(ADS868x));
	//---注册ms延时时间
	(pFuncDelayms != NULL) ? (ADS868x->pMsgDelayms = pFuncDelayms) : (ADS868x->pMsgDelayms = DelayTask_ms);
	//---注册us延时函数
	(pFuncDelayus != NULL) ? (ADS868x->msgSPI.pMsgDelayus = pFuncDelayus) : (ADS868x->msgSPI.pMsgDelayus = DelayTask_us);
	//---注册滴答函数
	(pFuncTimerTick != NULL) ? (ADS868x->msgSPI.pMsgTimeTick = pFuncTimerTick) : (ADS868x->msgSPI.pMsgTimeTick = SysTickTask_GetTick);
	//---配置ADS868X
	return ADS868X_SPI_ConfigInit(ADS868x,0);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：自动初始化，避免同一个SPI端口挂载多个设备，速度不一致的问题
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_AutoInit(ADS868X_HandleType* ADS868x)
{
	if (ADS868x->msgSPI.msgHwMode != 0)
	{
		//---软件初始化
		ADS868X_SPI_HW_Init(ADS868x);
	}
	else
	{
		//---硬件初始化
		ADS868X_SPI_SW_Init(ADS868x);
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
UINT8_T ADS868X_SPI_AutoDeInit(ADS868X_HandleType* ADS868x)
{
	//---注销当前的所有配置
	return SPITask_DeInit(&(ADS868x->msgSPI),0);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：写ADS868X命令寄存器
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_WriteCommandReg(ADS868X_HandleType *ADS868x, UINT32_T cmd)
{
	UINT8_T _return = OK_0;
	UINT8_T wTemp[2] = { 0 };
	wTemp[0] = (UINT8_T)((cmd >> 8)&0xFF);
	wTemp[1] = (UINT8_T)(cmd & 0xFF);
	if (ADS868x->msgSPI.msgCS.msgPort != NULL)
	{
		GPIO_OUT_0(ADS868x->msgSPI.msgCS.msgPort, ADS868x->msgSPI.msgCS.msgBit);
	}
	_return = ADS868X_SPI_SEND_ARRAY(ADS868x, wTemp, NULL, 2);
	if (ADS868x->msgSPI.msgCS.msgPort != NULL)
	{
		GPIO_OUT_1(ADS868x->msgSPI.msgCS.msgPort, ADS868x->msgSPI.msgCS.msgBit);
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
UINT8_T ADS868X_SPI_WriteProgramReg(ADS868X_HandleType *ADS868x, UINT8_T addr, UINT8_T val)
{
	UINT8_T _return = OK_0;
	UINT8_T wTemp[2] = { 0 };
	wTemp[0] = (addr << 1) | 0x01;
	wTemp[1] = val;
	if (ADS868x->msgSPI.msgCS.msgPort != NULL)
	{
		GPIO_OUT_0(ADS868x->msgSPI.msgCS.msgPort, ADS868x->msgSPI.msgCS.msgBit);
	}
	_return = ADS868X_SPI_SEND_ARRAY(ADS868x, wTemp, NULL, 2);
	if (ADS868x->msgSPI.msgCS.msgPort != NULL)
	{
		GPIO_OUT_1(ADS868x->msgSPI.msgCS.msgPort, ADS868x->msgSPI.msgCS.msgBit);
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
UINT8_T ADS868X_SPI_ReadProgramReg(ADS868X_HandleType *ADS868x, UINT8_T addr, UINT8_T *pVal)
{
	UINT8_T _return = OK_0;
	UINT8_T wTemp[3] = { 0 };
	UINT8_T rTemp[3] = { 0 };
	wTemp[0] = (addr << 1) & 0xFE;
	if (ADS868x->msgSPI.msgCS.msgPort != NULL)
	{
		GPIO_OUT_0(ADS868x->msgSPI.msgCS.msgPort, ADS868x->msgSPI.msgCS.msgBit);
	}
	_return = ADS868X_SPI_SEND_ARRAY(ADS868x, wTemp, rTemp, 3);
	if (ADS868x->msgSPI.msgCS.msgPort != NULL)
	{
		GPIO_OUT_1(ADS868x->msgSPI.msgCS.msgPort, ADS868x->msgSPI.msgCS.msgBit);
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
UINT8_T ADS868X_SPI_ReadCommandBack(ADS868X_HandleType* ADS868x, UINT8_T* pVal,UINT8_T isAutoInit)
{
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	_return = ADS868X_SPI_ReadProgramReg(ADS868x, ADS868X_CMD_READ_BACK, pVal);
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
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
UINT8_T ADS868X_SPI_NO_OP(ADS868X_HandleType* ADS868x,UINT8_T isAutoInit)
{
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	_return = ADS868X_SPI_WriteCommandReg(ADS868x, ADS868X_CMD_REG_NO_OP);
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
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
UINT8_T ADS868X_SPI_STDBY(ADS868X_HandleType* ADS868x,UINT8_T isAutoInit)
{
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	_return = ADS868X_SPI_WriteCommandReg(ADS868x, ADS868X_CMD_REG_STDBY);
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
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
UINT8_T ADS868X_SPI_PWRDN(ADS868X_HandleType* ADS868x,UINT8_T isAutoInit)
{
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	_return = ADS868X_SPI_WriteCommandReg(ADS868x, ADS868X_CMD_REG_PWR_DN);
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
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
UINT8_T  ADS868X_SPI_HardReset(ADS868X_HandleType *ADS868x)
{
	if (ADS868x->msgHWRST.msgPort!=NULL)
	{
		GPIO_OUT_0(ADS868x->msgHWRST.msgPort, ADS868x->msgHWRST.msgBit);
		ADS868x->pMsgDelayms(1);
		GPIO_OUT_1(ADS868x->msgHWRST.msgPort, ADS868x->msgHWRST.msgBit);
		ADS868x->pMsgDelayms(1);
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
UINT8_T  ADS868X_SPI_SoftReset(ADS868X_HandleType *ADS868x,UINT8_T isAutoInit)
{
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	_return = ADS868X_SPI_WriteCommandReg(ADS868x, ADS868X_CMD_REG_RST);
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
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
UINT8_T ADS868X_SPI_Reset(ADS868X_HandleType* ADS868x,UINT8_T isAutoInit)
{
	UINT8_T _return = OK_0;
	if (ADS868x->msgHWRST.msgPort != NULL)
	{
		_return = ADS868X_SPI_HardReset(ADS868x);
	}
	else
	{
		_return = ADS868X_SPI_SoftReset(ADS868x,isAutoInit);
	}
	ADS868x->msgReadyOK = 0;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：进入自动扫描模式
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_AUTORST(ADS868X_HandleType* ADS868x,UINT8_T isAutoInit)
{
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	_return = ADS868X_SPI_WriteCommandReg(ADS868x, ADS868X_CMD_REG_AUTO_RST);
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
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
UINT8_T ADS868X_SPI_ManualChannel(ADS868X_HandleType* ADS868x,UINT16_T manualCHCmd,UINT8_T isAutoInit)
{
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	_return = ADS868X_SPI_WriteCommandReg(ADS868x, manualCHCmd);
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
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
UINT8_T ADS868X_SPI_WriteChipID(ADS868X_HandleType* ADS868x, UINT8_T devid,UINT8_T isAutoInit)
{
	devid <<= 6;
	ADS868x->msgChipID = (devid & 0xC0) | ADS868x->msgFeature;
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	_return = ADS868X_SPI_WriteProgramReg(ADS868x, ADS868X_PROG_REG_FEATURE_SELECT, ADS868x->msgChipID);
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
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
UINT8_T ADS868X_SPI_ReadChipID(ADS868X_HandleType* ADS868x, UINT8_T *pDevID,UINT8_T isAutoInit)
{
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	_return = ADS868X_SPI_ReadProgramReg(ADS868x, ADS868X_PROG_REG_FEATURE_SELECT, pDevID);
	*pDevID &= 0xC0;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
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
UINT8_T ADS868X_SPI_CheckChipID(ADS868X_HandleType* ADS868x,UINT8_T isAutoInit)
{
	UINT8_T tempChipID = 0x00;
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	_return = ADS868X_SPI_ReadChipID(ADS868x, &tempChipID,0);
	//---校验读取的ID信息
	if (tempChipID!=ADS868x->msgChipID)
	{
		_return += ERROR_1;
	}
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
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
UINT8_T ADS868X_SPI_DetectionDevice(ADS868X_HandleType* ADS868x,UINT8_T isAutoInit)
{
	UINT8_T tempAutoSeqEn[2] = { 0 };
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	_return=ADS868X_SPI_ReadProgramReg(pADS868XDevice0, ADS868X_PROG_REG_AUTO_SEQ_EN, tempAutoSeqEn);
	//---校验结果是否正确
	if (tempAutoSeqEn[1]!=ADS868x->msgAutoSeqEn)
	{
		_return += ERROR_1;
	}
	else
	{
		//---校验设备的ID信息
		_return = ADS868X_SPI_CheckChipID(ADS868x,0);
	}
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
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
UINT8_T ADS868X_SPI_WriteAUTOSEQEN(ADS868X_HandleType* ADS868x, UINT8_T seq,UINT8_T isAutoInit)
{
	ADS868x->msgAutoSeqEn = seq;
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	_return =ADS868X_SPI_WriteProgramReg(ADS868x, ADS868X_PROG_REG_AUTO_SEQ_EN, seq);
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
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
UINT8_T ADS868X_SPI_ReadAUTOSEQEN(ADS868X_HandleType* ADS868x, UINT8_T *pAutoSeqEn,UINT8_T isAutoInit)
{
	UINT8_T tempAutoSeqEn[2] = { 0 }; 
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	_return = ADS868X_SPI_ReadProgramReg(ADS868x, ADS868X_PROG_REG_AUTO_SEQ_EN, tempAutoSeqEn);
	if (_return==OK_0)
	{
		if (tempAutoSeqEn[1]==ADS868x->msgAutoSeqEn)
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
		ADS868X_SPI_AutoDeInit(ADS868x);
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
UINT8_T ADS868X_SPI_WriteChannelPWRDN(ADS868X_HandleType* ADS868x, UINT8_T ch,UINT8_T isAutoInit)
{
	ADS868x->msgChannelPWRDN = ch;
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	_return = ADS868X_SPI_WriteProgramReg(ADS868x, ADS868X_PROG_REG_CH_PWR_DN, ch);
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
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
UINT8_T ADS868X_SPI_ReadChannelPWRDN(ADS868X_HandleType* ADS868x, UINT8_T *pPWRDN,UINT8_T isAutoInit)
{
	UINT8_T tempPWRDN[2] = { 0 };
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	_return = ADS868X_SPI_ReadProgramReg(ADS868x, ADS868X_PROG_REG_CH_PWR_DN, tempPWRDN);
	if (_return == OK_0)
	{
		if (tempPWRDN[1] == ADS868x->msgChannelPWRDN)
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
		ADS868X_SPI_AutoDeInit(ADS868x);
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
UINT8_T ADS868X_SPI_WriteFeature(ADS868X_HandleType* ADS868x, UINT8_T feature,UINT8_T isAutoInit)
{
	ADS868x->msgFeature = (feature&0x3F)|ADS868x->msgChipID;
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	_return = ADS868X_SPI_WriteProgramReg(ADS868x, ADS868X_PROG_REG_FEATURE_SELECT, feature);
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
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
UINT8_T ADS868X_SPI_ReadFeature(ADS868X_HandleType* ADS868x, UINT8_T *pFeature,UINT8_T isAutoInit)
{
	UINT8_T tempFeature[2] = { 0 };
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	_return = ADS868X_SPI_ReadProgramReg(ADS868x, ADS868X_PROG_REG_FEATURE_SELECT, tempFeature);
	if (_return == OK_0)
	{
		if (tempFeature[1] == ADS868x->msgFeature)
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
		ADS868X_SPI_AutoDeInit(ADS868x);
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
UINT8_T ADS868X_SPI_WriteChannelRange(ADS868X_HandleType* ADS868x, UINT8_T chReg, UINT8_T range,UINT8_T isAutoInit)
{
	UINT8_T ch = ADS868X_CHANNEL_MAX;
	switch (chReg)
	{
		case ADS868X_PROG_REG_CH0_SET_RANGE:
			ADS868x->msgChannelRange[0] = range;
			ch = 0;
			break;
		case ADS868X_PROG_REG_CH1_SET_RANGE:
			ADS868x->msgChannelRange[1] = range;
			ch = 1;
			break;
		case ADS868X_PROG_REG_CH2_SET_RANGE:
			ADS868x->msgChannelRange[2] = range;
			ch = 2;
			break;
		case ADS868X_PROG_REG_CH3_SET_RANGE:
			ADS868x->msgChannelRange[3] = range;
			ch = 3;
			break;
		case ADS868X_PROG_REG_CH4_SET_RANGE:
			ADS868x->msgChannelRange[4] = range;
			ch = 4;
			break;
		case ADS868X_PROG_REG_CH5_SET_RANGE:
			ADS868x->msgChannelRange[5] = range;
			ch = 5;
			break;
		case ADS868X_PROG_REG_CH6_SET_RANGE:
			ADS868x->msgChannelRange[6] = range;
			ch = 6;
			break;
		case ADS868X_PROG_REG_CH7_SET_RANGE:
			ADS868x->msgChannelRange[7] = range;
			ch = 7;
			break;
		default:
			return ERROR_1;
	}
	//---每个通道的量程的配置
	ADS868X_SPI_ChannelRange(ADS868x, ch);
	//---设置通道的量程
	UINT8_T _return = 0;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	_return = ADS868X_SPI_WriteProgramReg(ADS868x, chReg, range);
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
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
UINT8_T ADS868X_SPI_ReadChannelRange(ADS868X_HandleType* ADS868x, UINT8_T chReg, UINT8_T *pRange,UINT8_T isAutoInit)
{
	UINT8_T ch = ADS868X_CHANNEL_MAX;
	UINT8_T tempChannelRange[2] = { 0 };
	UINT8_T _return = OK_0;
	switch (chReg)
	{
		case ADS868X_PROG_REG_CH0_SET_RANGE:
			ch = 0;
			break;
		case ADS868X_PROG_REG_CH1_SET_RANGE:
			ch = 1;
			break;
		case ADS868X_PROG_REG_CH2_SET_RANGE:
			ch = 2;
			break;
		case ADS868X_PROG_REG_CH3_SET_RANGE:
			ch = 3;
			break;
		case ADS868X_PROG_REG_CH4_SET_RANGE:
			ch = 4;
			break;
		case ADS868X_PROG_REG_CH5_SET_RANGE:
			ch = 5;
			break;
		case ADS868X_PROG_REG_CH6_SET_RANGE:
			ch = 6;
			break;
		case ADS868X_PROG_REG_CH7_SET_RANGE:
			ch = 7;
			break;
		default:
			return ERROR_1;
	}
	//---读取通道的量程
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	_return = ADS868X_SPI_ReadProgramReg(ADS868x, chReg, tempChannelRange);
	//---判断读取结果
	if (_return == OK_0)
	{
		if (tempChannelRange[1] == ADS868x->msgChannelRange[ch])
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
		ADS868X_SPI_AutoDeInit(ADS868x);
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
UINT8_T ADS868X_SPI_WriteREFPowerUV(ADS868X_HandleType* ADS868x, UINT32_T refUV)
{
	ADS868x->msgREFPowerUV = refUV;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取参考电压
//////输入参数：
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT32_T ADS868X_SPI_ReadREFPowerUV(ADS868X_HandleType* ADS868x, UINT32_T refUV)
{
	return ADS868x->msgREFPowerUV;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置参考电压mv
//////输入参数：
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_WriteREFPowerMV(ADS868X_HandleType* ADS868x, UINT32_T refMV)
{
	ADS868x->msgREFPowerUV = refMV*1000;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置每通道的量程和量程最大值
//////输入参数：
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_ChannelRange(ADS868X_HandleType* ADS868x, UINT8_T chIndex)
{
	UINT8_T _return = OK_0;
	if (chIndex==ADS868X_CHANNEL_MAX)
	{
		_return = ERROR_1;
	}
	else
	{
		switch (ADS868x->msgChannelRange[chIndex])
		{
			//---正负1.25倍的VREF
			case ADS868X_RANGE_5120MV_5120MV:
				ADS868x->msgChannelRangeIsPositive[chIndex] = 0;
				ADS868x->msgChannelRangeFullUVX1000[chIndex] = ((UINT64_T)ADS868x->msgREFPowerUV * 1250);//5120000000;
				ADS868x->msgChannelRangeBaseUVX1000[chIndex] = (ADS868x->msgChannelRangeFullUVX1000[chIndex] * 2) / (1<< ADS868X_ADC_SAMPLE_BITS); //156250;
				break;
			//---正负0.625倍的VREF
			case ADS868X_RANGE_2560MV_2560MV:
				ADS868x->msgChannelRangeIsPositive[chIndex] = 0;
				ADS868x->msgChannelRangeFullUVX1000[chIndex] = ((UINT64_T)ADS868x->msgREFPowerUV * 625); //2560000000;
				ADS868x->msgChannelRangeBaseUVX1000[chIndex] = (ADS868x->msgChannelRangeFullUVX1000[chIndex] * 2) / (1<< ADS868X_ADC_SAMPLE_BITS); //78125;
				break;
			//---正2.5倍的VREF
			case ADS868X_RANGE_0MV_10240MV:
				ADS868x->msgChannelRangeIsPositive[chIndex] = 1;
				ADS868x->msgChannelRangeFullUVX1000[chIndex] = ((UINT64_T)ADS868x->msgREFPowerUV * 2500);//10240000000;
				ADS868x->msgChannelRangeBaseUVX1000[chIndex] = ADS868x->msgChannelRangeFullUVX1000[chIndex] / (1<< ADS868X_ADC_SAMPLE_BITS); //156250;
				break;
			//---正1.25倍的VREF
			case ADS868X_RANGE_0MV_5120MV:
				ADS868x->msgChannelRangeIsPositive[chIndex] = 1;
				ADS868x->msgChannelRangeFullUVX1000[chIndex] = ((UINT64_T)ADS868x->msgREFPowerUV* 1250);//5120000000;
				ADS868x->msgChannelRangeBaseUVX1000[chIndex] = ADS868x->msgChannelRangeFullUVX1000[chIndex] / (1<< ADS868X_ADC_SAMPLE_BITS); //78125;
				break;
			//---正负2.5倍的VREF
			case ADS868X_RANGE_10240MV_10240MV:
			default:
				ADS868x->msgChannelRangeIsPositive[chIndex] = 0;
				ADS868x->msgChannelRangeFullUVX1000[chIndex] = ((UINT64_T)ADS868x->msgREFPowerUV * 2500);//10240000000;
				ADS868x->msgChannelRangeBaseUVX1000[chIndex] = (ADS868x->msgChannelRangeFullUVX1000[chIndex] * 2) / (1<< ADS868X_ADC_SAMPLE_BITS); //312500;
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
UINT8_T ADS868X_SPI_CalcChannelPower(ADS868X_HandleType* ADS868x, UINT8_T chIndex,UINT8_T isCalcDelta)
{
	//---设置无数据
	ADS868x->msgPositive[chIndex] = 0;
	UINT32_T adcDelta = 0;
	UINT64_T calcPower = 0;
	//---判断是否需要计算差值
	if (isCalcDelta != 0)
	{
		//---获取上次和本次的采样结果的绝对差值
		adcDelta = ABS_SUB(ADS868x->msgChannelNowADCResult[chIndex], ADS868x->msgChannelOldADCResult[chIndex]);
		//---软件数据补偿拟合开始
		if (adcDelta < 15)
		{
			if (adcDelta>5)
			{
				ADS868x->msgChannelOldADCResult[chIndex] = MAX(ADS868x->msgChannelNowADCResult[chIndex], ADS868x->msgChannelOldADCResult[chIndex])-2;
			}
			else if (ADS868x->msgChannelNowADCResult[chIndex] > ADS868x->msgChannelOldADCResult[chIndex])
			{
				ADS868x->msgChannelOldADCResult[chIndex] = ADS868x->msgChannelNowADCResult[chIndex];
				if(adcDelta>2)
				{
					ADS868x->msgChannelOldADCResult[chIndex] -=2;
				}
			}
			else if (ADS868x->msgChannelNowADCResult[chIndex] < ADS868x->msgChannelOldADCResult[chIndex])
			{
				ADS868x->msgChannelOldADCResult[chIndex] -= 1;
			}
			else
			{
				ADS868x->msgChannelOldADCResult[chIndex] = MAX(ADS868x->msgChannelNowADCResult[chIndex], ADS868x->msgChannelOldADCResult[chIndex]);
			}
			calcPower = ADS868x->msgChannelOldADCResult[chIndex];
		}
		else
		{
			calcPower = ADS868x->msgChannelNowADCResult[chIndex];
			ADS868x->msgChannelOldADCResult[chIndex] = ADS868x->msgChannelNowADCResult[chIndex];
		}
	}
	else
	{
		calcPower = ADS868x->msgChannelNowADCResult[chIndex];
	}
	calcPower &= ((1<< ADS868X_ADC_SAMPLE_BITS)-1);
	//---软件数据补偿拟合结束
	//---将数字量转换为模拟量
	calcPower *= ADS868x->msgChannelRangeBaseUVX1000[chIndex];
	double adcPower = 0;
	//---判断ADC采样的量程是双极性还是单极性
	if (ADS868x->msgChannelRangeIsPositive[chIndex] == 0)
	{
		if (((ADS868x->msgChannelNowADCResult[chIndex] & (1<< (ADS868X_ADC_SAMPLE_BITS-1)))) != 0)
		{
			ADS868x->msgPositive[chIndex] = 2;
			ADS868x->msgChannelPowerResult[chIndex] = (UINT32_T)((calcPower - ADS868x->msgChannelRangeFullUVX1000[chIndex]) / 1000);
		}
		else
		{
			ADS868x->msgPositive[chIndex] = 1;
			ADS868x->msgChannelPowerResult[chIndex] = (UINT32_T)((ADS868x->msgChannelRangeFullUVX1000[chIndex] - calcPower) / 1000);
		}
	}
	else
	{
		ADS868x->msgPositive[chIndex] = 2;
		ADS868x->msgChannelPowerResult[chIndex] = (UINT32_T)(calcPower / 1000);
	}
	//---误差消除计算
	if (ADS868x->msgADCKP[chIndex] != 0)
	{
		adcPower = ADS868x->msgChannelPowerResult[chIndex];
		adcPower *= ADS868x->msgADCKP[chIndex];
		if (adcPower< ADS868x->msgADCDelta[chIndex])
		{
			ADS868x->msgPositive[chIndex] = 1;
			adcPower = (ADS868x->msgADCDelta[chIndex] - adcPower);
		}
		else
		{
			adcPower -= ADS868x->msgADCDelta[chIndex];
		}
		ADS868x->msgChannelPowerResult[chIndex] = (UINT32_T)adcPower;
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
UINT8_T ADS868X_SPI_GetAutoRSTResult(ADS868X_HandleType *ADS868x, UINT8_T chNum,UINT8_T isAutoInit)
{
	UINT8_T i = 0;
	UINT8_T adcRTemp[4] = {0};
	UINT8_T adcWTemp[4] = { 0 };
	UINT8_T _return = 0;
	UINT8_T rstMode = ADS868x->msgAutoSeqEn;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	//---判断设备是否初始化成功
	if (ADS868x->msgReadyOK == 1)
	{
		_return = ADS868X_SPI_ConfigInit(ADS868x,0);
		if (_return != OK_0)
		{
			goto GoToExit;
		}
	}
	//---进入自动扫描模式
	_return =ADS868X_SPI_AUTORST(ADS868x,0);
	//---扫描通道的结果
	for (i = 0; i < chNum; i++)
	{
		//---判断是否使能自动RST扫描功能
		if (rstMode & 0x01)
		{
			adcWTemp[3] = i;
			//---准备读取数据
			if (ADS868x->msgSPI.msgCS.msgPort != NULL)
			{
				GPIO_OUT_0(ADS868x->msgSPI.msgCS.msgPort, ADS868x->msgSPI.msgCS.msgBit);
			}
			_return=ADS868X_SPI_SEND_ARRAY(ADS868x, adcWTemp, adcRTemp, 4);
			//---结束数据的读取
			if (ADS868x->msgSPI.msgCS.msgPort != NULL)
			{
				GPIO_OUT_1(ADS868x->msgSPI.msgCS.msgPort, ADS868x->msgSPI.msgCS.msgBit);
			}
			//---保存读取的数据
			ADS868x->msgChannelNowADCResult[i] = adcRTemp[2];
			ADS868x->msgChannelNowADCResult[i] = (ADS868x->msgChannelNowADCResult[i] << 8) + adcRTemp[3];
			ADS868x->msgChannelNowADCResult[i] >>= ADS868X_DATA_SAMPLE_BITS;
			//---计算采样结果
			ADS868X_SPI_CalcChannelPower(ADS868x, i,0);
		}
		rstMode >>= 1;
	}
GoToExit:
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
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
UINT8_T ADS868X_SPI_GetAutoRSTNSampleResult(ADS868X_HandleType* ADS868x, UINT8_T chNum,UINT8_T isAutoInit)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	UINT8_T j = 0;
	UINT8_T rstMode = ADS868x->msgAutoSeqEn;
	//---保存采样结果
	UINT16_T adcSampleTemp[ADS868X_CHANNEL_MAX][ADS868X_N_SAMPLE_COUNT] = { 0 };
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	//---获取采样结果
	for (i = 0; i < ADS868X_N_SAMPLE_COUNT; i++)
	{
		//---获取采样结果
		_return = ADS868X_SPI_GetAutoRSTResult(ADS868x, chNum,0);
		//---采样数据搬移
		for (j=0;j< ADS868X_CHANNEL_MAX;j++)
		{
			adcSampleTemp[j][i] = ADS868x->msgChannelNowADCResult[j];
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
		for (j = 0; j < ADS868X_CHANNEL_MAX; j++)
		{
			//---判断是否使能自动RST扫描功能
			if (rstMode & 0x01)
			{
				//---升序排列数据
				AscSortWord(adcSampleTemp[j], ADS868X_N_SAMPLE_COUNT);
				//---计算均值
				ADS868x->msgChannelNowADCResult[j] = CalcAvgWordFromIndex(adcSampleTemp[j], (ADS868X_N_SAMPLE_COUNT - 2), 2);
				//---计算采样的电压值
				ADS868X_SPI_CalcChannelPower(ADS868x, j,1);
			}
			rstMode >>= 1;
		}
	}
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
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
UINT8_T ADS868X_SPI_KalmanFilterGetAutoRSTNSampleResult(ADS868X_HandleType* ADS868x, UINT8_T chNum,UINT8_T isAutoInit)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	UINT8_T j = 0;
	UINT8_T rstMode = ADS868x->msgAutoSeqEn;
	//---保存采样结果
	UINT32_T adcSampleTemp[ADS868X_CHANNEL_MAX][ADS868X_N_SAMPLE_COUNT] = { 0 };
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	//---卡尔曼结构
	KalmanOneFilter_HandleType kalmanFilterX;
	//---获取采样结果
	for (i = 0; i < ADS868X_N_SAMPLE_COUNT; i++)
	{
		//---获取采样结果
		_return = ADS868X_SPI_GetAutoRSTResult(ADS868x, chNum,0);
		//---采样数据搬移
		for (j = 0; j < ADS868X_CHANNEL_MAX; j++)
		{
			adcSampleTemp[j][i] = ADS868x->msgChannelNowADCResult[j];
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
		for (j = 0; j < ADS868X_CHANNEL_MAX; j++)
		{
			//---判断是否使能自动RST扫描功能
			if (rstMode & 0x01)
			{
				KalmanOneFilter_Init(&kalmanFilterX, (float)adcSampleTemp[j][0], 5e2);
				for (i = 1; i < ADS868X_N_SAMPLE_COUNT; i++)
				{
					//---卡尔曼滤波之后的结果
					ADS868x->msgChannelNowADCResult[j] = (UINT32_T)KalmanOneFilter_Filter(&kalmanFilterX, (float)adcSampleTemp[j][i]);
				}
				//---计算采样的电压值
				ADS868X_SPI_CalcChannelPower(ADS868x, j, 0);
			}
			rstMode >>= 1;
		}
	}
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
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
UINT8_T  ADS868X_SPI_GetManualChannelResult(ADS868X_HandleType* ADS868x, UINT16_T manualChannel,UINT8_T isAutoInit)
{
	UINT8_T _return = OK_0;
	UINT8_T adcRTemp[4] = { 0 };
	UINT8_T adcWTemp[4] = { 0 };
	UINT8_T adcChannel = 0;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	//---判断设备是否初始化成功
	if (ADS868x->msgReadyOK==1)
	{
		_return=ADS868X_SPI_ConfigInit(ADS868x,0);
		if (_return!=OK_0)
		{
			goto GoToExit;
		}
	}
	//---设置手动扫描通道
	_return = ADS868X_SPI_ManualChannel(ADS868x, manualChannel,0);
	//---准备读取设置的扫描通道的值
	if (ADS868x->msgSPI.msgCS.msgPort != NULL)
	{
		GPIO_OUT_0(ADS868x->msgSPI.msgCS.msgPort, ADS868x->msgSPI.msgCS.msgBit);
	}
	//---读取ADC采样的结果
	_return = ADS868X_SPI_SEND_ARRAY(ADS868x, adcWTemp, adcRTemp, 4);
	//---结束读取设置的扫描通道的值
	if (ADS868x->msgSPI.msgCS.msgPort != NULL)
	{
		GPIO_OUT_1(ADS868x->msgSPI.msgCS.msgPort, ADS868x->msgSPI.msgCS.msgBit);
	}
	//---通道的转换
	adcChannel = (UINT8_T)(manualChannel >> 10) & 0x0F;
	//---判断是否是AUX通道配置
	if (adcChannel<8)
	{
		ADS868x->msgChannelNowADCResult[adcChannel] = adcRTemp[2];
		ADS868x->msgChannelNowADCResult[adcChannel] = (ADS868x->msgChannelNowADCResult[adcChannel] << 8) + adcRTemp[3];
		ADS868x->msgChannelNowADCResult[adcChannel] >>= ADS868X_DATA_SAMPLE_BITS;
		//---计算采样结果
		ADS868X_SPI_CalcChannelPower(ADS868x, adcChannel,0);
	}
GoToExit:
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
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
UINT8_T ADS868X_SPI_GetManualChannelNSampleResult(ADS868X_HandleType* ADS868x, UINT16_T manualChannel,UINT8_T isAutoInit)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---保存采样结果
	UINT16_T adcSampleTemp[ADS868X_N_SAMPLE_COUNT] = { 0 };
	//---获取ADC采样通道的序号
	UINT8_T adcChannelIndex = (UINT8_T)(manualChannel >> 10) & 0x0F;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	//---获取采样结果
	for ( i = 0; i < ADS868X_N_SAMPLE_COUNT; i++)
	{
		_return = ADS868X_SPI_GetManualChannelResult(ADS868x, manualChannel,0);
		adcSampleTemp[i] = ADS868x->msgChannelNowADCResult[adcChannelIndex];
		if (_return!=OK_0)
		{
			break;
		}
	}
	if (_return==OK_0)
	{
		//---升序排列数据
		AscSortWord(adcSampleTemp, ADS868X_N_SAMPLE_COUNT);
		//---计算均值
		ADS868x->msgChannelNowADCResult[adcChannelIndex] = CalcAvgWordFromIndex(adcSampleTemp, (ADS868X_N_SAMPLE_COUNT - 2), 2);
		//---计算采样的电压值
		ADS868X_SPI_CalcChannelPower(ADS868x, adcChannelIndex,1);
	}
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
	}
	return _return;
}
///////////////////////////////////////////////////////////////////////////
//////函		数：
//////功	    能：卡尔曼滤波方式计算数据
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ADS868X_SPI_KalmanFilterGetManualChannelNSampleResult(ADS868X_HandleType* ADS868x, UINT16_T manualChannel,UINT8_T isAutoInit)
{
	UINT8_T _return = OK_0;
	UINT8_T i = 0;
	//---保存采样结果
	UINT32_T adcSampleTemp[ADS868X_N_SAMPLE_COUNT] = { 0 };
	//---获取ADC采样通道的序号
	UINT8_T adcChannelIndex = (UINT8_T)(manualChannel >> 10) & 0x0F;
	//---卡尔曼结构
	KalmanOneFilter_HandleType kalmanFilterX;
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	//---获取采样结果
	for (i = 0; i < ADS868X_N_SAMPLE_COUNT; i++)
	{
		_return = ADS868X_SPI_GetManualChannelResult(ADS868x, manualChannel,0);
		adcSampleTemp[i] = ADS868x->msgChannelNowADCResult[adcChannelIndex];
		if (_return != OK_0)
		{
			break;
		}
	}
	if (_return == OK_0)
	{
		KalmanOneFilter_Init(&kalmanFilterX, (float)adcSampleTemp[0], 5e2);
		for (i=1;i< ADS868X_N_SAMPLE_COUNT; i++)
		{
			//---卡尔曼滤波之后的结果
			ADS868x->msgChannelNowADCResult[adcChannelIndex] =(UINT32_T) KalmanOneFilter_Filter(&kalmanFilterX,(float) adcSampleTemp[i]);
		}
		//---计算采样的电压值
		ADS868X_SPI_CalcChannelPower(ADS868x, adcChannelIndex, 1);
	}
	if (isAutoInit != 0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
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
UINT8_T ADS868X_SPI_CalibrationChannelErr(ADS868X_HandleType* ADS868x)
{
	UINT8_T i = 0;
	UINT8_T rstMode = ADS868x->msgAutoSeqEn;
	for (i = 0; i < ADS868X_CHANNEL_MAX; i++)
	{
		if ((rstMode&0x01)==0)
		{
			if (i==0)
			{
				////---1号板参数
				//ADS868x->msgADCKP[i] = 1.013216;
				//ADS868x->msgADCDelta[i] = 27130;
				//---2号板参数
				ADS868x->msgADCKP[i] = 1.013216;
				ADS868x->msgADCDelta[i] = 26430;
			}
			else
			{
				////---1号板参数
				//ADS868x->msgADCKP[i] = 1.0129;
				//ADS868x->msgADCDelta[i] = 25870;
				//---2号板参数
				ADS868x->msgADCKP[i] = 1.0129;
				ADS868x->msgADCDelta[i] = 27070;
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
UINT8_T ADS868X_SPI_ConfigInit(ADS868X_HandleType* ADS868x,UINT8_T isAutoInit)
{
	UINT8_T _return = OK_0;
	UINT8_T tempBuffer[3] = { 0 };
	UINT8_T i = 0;
	if (isAutoInit!=0)
	{
		ADS868X_SPI_AutoInit(ADS868x);
	}
	if (ADS868x->msgInitRetryCount==0)
	{
		ADS868x->msgInitRetryCount = 1;
	}
	//---循环多次初始化设备
	for (i=0;i< ADS868x->msgInitRetryCount;i++)
	{
		//---复位芯片
		_return = ADS868X_SPI_Reset(ADS868x,0);
		//---校验
		if (_return == OK_0)
		{
			//---设备特征配置
			_return = ADS868X_SPI_WriteFeature(ADS868x, 0x28,0);
			//---校验
			if (_return == OK_0)
			{
				//---读取设备的特征
				_return = ADS868X_SPI_ReadFeature(ADS868x, tempBuffer,0);
				//---校验
				if (_return == OK_0)
				{
					break;
				}
			}
		}
	}
	//---设置扫描方式
	_return = ADS868X_SPI_WriteAUTOSEQEN(ADS868x, 0xF0,0);
	//---读取设置的值
	_return = ADS868X_SPI_ReadProgramReg(ADS868x, ADS868X_PROG_REG_AUTO_SEQ_EN, tempBuffer);
	//---判断校验
	if (ADS868x->msgAutoSeqEn != tempBuffer[1])
	{
		_return = ERROR_1;
		ADS868x->msgReadyOK = 1;
	}
	else
	{
		//---设置通道的量程
		ADS868X_SPI_WriteChannelRange(ADS868x, ADS868X_PROG_REG_CH0_SET_RANGE, ADS868X_RANGE_0MV_5120MV,0);
		ADS868X_SPI_WriteChannelRange(ADS868x, ADS868X_PROG_REG_CH1_SET_RANGE, ADS868X_RANGE_0MV_5120MV,0);
		ADS868X_SPI_WriteChannelRange(ADS868x, ADS868X_PROG_REG_CH2_SET_RANGE, ADS868X_RANGE_0MV_5120MV,0);
		//---设置工作模式
		ADS868X_SPI_AUTORST(ADS868x,0);
	}
	ADS868X_SPI_CalibrationChannelErr(ADS868x);
    if (isAutoInit!=0)
	{
		ADS868X_SPI_AutoDeInit(ADS868x);
	}
	return _return;
}
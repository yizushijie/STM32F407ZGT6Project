#include "dht11_cfg.h"

//---变量定义
DHT11_HandleType g_Dht11Device0 = { 0 };
pDHT11_HandleType pDht11Device0 = &g_Dht11Device0;

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:DHT11x
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_Device0_Init(DHT11_HandleType *DHTxx)
{
	DHTxx->msgSTATE=DHT11_READ_OK;
	DHTxx->msgDAT.msgBit = LL_GPIO_PIN_14;
	DHTxx->msgDAT.msgPort = GPIOB;
	//---室温25摄氏度
	DHTxx->msgTempX1000=25000;
	//---湿度百分之五十
	DHTxx->msgHumiX1000=50000;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_Device1_Init(DHT11_HandleType *DHTxx)
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
UINT8_T DHT11_Device2_Init(DHT11_HandleType *DHTxx)
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
UINT8_T DHT11_GPIO_Init(DHT11_HandleType *DHTxx)
{
	//---使能端口时钟
	#ifndef  USE_FULL_GPIO
	GPIOTask_Clock(DHTxx->msgDAT.msgPort, PERIPHERAL_CLOCK_ENABLE);
	#endif
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	//---GPIO的初始化
	GPIO_InitStruct.Pin = DHTxx->msgDAT.msgBit;														//---对应的GPIO的引脚
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;														//---配置状态为输出模式
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;												//---GPIO的速度
	GPIO_InitStruct.OutputType =LL_GPIO_OUTPUT_OPENDRAIN;											//---输出模式---开漏输出
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;															//---上拉使能
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;														//---端口复用模式
#endif
	//---初始化端口
	LL_GPIO_Init(DHTxx->msgDAT.msgPort, &GPIO_InitStruct);
	GPIO_OUT_1(DHTxx->msgDAT.msgPort, DHTxx->msgDAT.msgBit);
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：
//////输入参数:
//////输出参数:
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_Init(DHT11_HandleType *DHTxx, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void))
{
	//---使用的DHT11的端口
	if ((DHTxx != NULL) && (DHTxx == DHT11_TASK_ONE))
	{
		DHT11_Device0_Init(DHTxx);
	}
	else if ((DHTxx != NULL) && (DHTxx == DHT11_TASK_TWO))
	{
		DHT11_Device1_Init(DHTxx);
	}
	else if ((DHTxx != NULL) && (DHTxx == DHT11_TASK_THREE))
	{
		DHT11_Device2_Init(DHTxx);
	}
	else
	{
		return ERROR_1;
	}
	//---GPIO的初始化
	DHT11_GPIO_Init(DHTxx);
	//---us延时
	(pFuncDelayus != NULL)?(DHTxx->pMsgDelayus = pFuncDelayus):(DHTxx->pMsgDelayus = DelayTask_us);
	//---ms延时
	(pFuncDelayms != NULL)?(DHTxx->pMsgDelayms = pFuncDelayms):(DHTxx->pMsgDelayms = DelayTask_ms);
	//---注册滴答函数
	(pFuncTimerTick != NULL)?(DHTxx->pMsgTimeTick = pFuncTimerTick):(DHTxx->pMsgTimeTick = SysTickTask_GetTick);
	//---当前时间
	DHTxx->msgRecordTick= DHTxx->pMsgTimeTick();
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：
//////输入参数:
//////输出参数:
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_DeInit(DHT11_HandleType *DHTxx)
{
	LL_GPIO_DeInit(DHTxx->msgDAT.msgPort);
	GPIO_OUT_1(DHTxx->msgDAT.msgPort, DHTxx->msgDAT.msgBit);
	DHTxx->msgSTATE = DHT11_READ_ERROR;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：
//////输入参数:
//////输出参数:
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_RESET(DHT11_HandleType *DHTxx)
{
	//---释放总线
	GPIO_OUT_1(DHTxx->msgDAT.msgPort, DHTxx->msgDAT.msgBit);
	//---主机拉高2us
	DHTxx->pMsgDelayus(2);
	GPIO_OUT_0(DHTxx->msgDAT.msgPort, DHTxx->msgDAT.msgBit);
	//---触发开始,总线拉低要大于18ms
	DHTxx->pMsgDelayms(20);
	//---释放总线
	GPIO_OUT_1(DHTxx->msgDAT.msgPort, DHTxx->msgDAT.msgBit);
	//主机拉高20~40us;等待DHT11的低电平响应信号
	DHTxx->pMsgDelayus(30);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：
//////输入参数:
//////输出参数:
//////说	   明：1:不存在;0:存在
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_Check(DHT11_HandleType *DHTxx)
{
	UINT8_T count = 0;
	//---DHT11如果响应的话会拉低总线40~80us
	while (GPIO_GET_STATE(DHTxx->msgDAT.msgPort, DHTxx->msgDAT.msgBit) != 0)
	{
		DHTxx->pMsgDelayus(1);
		count++;
		if (count > 200)
		{
			break;
		}
	}
	if (count > 200)
	{
		return ERROR_1;
	}
	count = 0;
	//---DHT11高电平数据准备信号再次拉高40~80us
	while (GPIO_GET_STATE(DHTxx->msgDAT.msgPort, DHTxx->msgDAT.msgBit) == 0)
	{
		DHTxx->pMsgDelayus(1);
		count++;
		if (count > 200)
		{
			break;
		}
	}
	if (count > 200)
	{
		return ERROR_1;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：
//////输入参数:
//////输出参数:
//////说	   明：1:不存在;0:存在
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_START(DHT11_HandleType *DHTxx)
{
	//---触发传输
	UINT8_T _return = DHT11_RESET(DHTxx);
	if (_return)
	{
		return _return;
	}
	//---检测设备
	return DHT11_Check(DHTxx);
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：
//////输入参数:
//////输出参数:
//////说	   明：位数据“0”的格式为： 50 微秒的低电平和 26-28 微秒的高电平;
/////////////  位数据“1”的格式为： 50 微秒的低电平加 70微秒的高电平
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_ReadBit(DHT11_HandleType *DHTxx)
{
	UINT8_T count = 0;
	//---等待变为低电平---高电平保持的时间约为50us
	while (GPIO_GET_STATE(DHTxx->msgDAT.msgPort, DHTxx->msgDAT.msgBit) != 0)
	{
		DHTxx->pMsgDelayus(1);
		count++;
		if (count > 150)
		{
			count = 0;
			break;
		}
	}
	//---读取高电平等待一下
	DHTxx->pMsgDelayus(10);
	//---等待变高电平---低电平保持的时间约为20us
	while (GPIO_GET_STATE(DHTxx->msgDAT.msgPort, DHTxx->msgDAT.msgBit) == 0)
	{
		DHTxx->pMsgDelayus(1);

		count++;
		if (count > 150)
		{
			count = 0;
			break;
		}
	}
	//---等待40us;数据为0的信号时间为26-28us，1则为70us
	DHTxx->pMsgDelayus(50);
	//---读取状态
	if (GPIO_GET_STATE(DHTxx->msgDAT.msgPort, DHTxx->msgDAT.msgBit) != 0)
	{
		return 1;
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：
//////输入参数:
//////输出参数:
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_ReadByte(DHT11_HandleType *DHTxx)
{
	UINT8_T i = 0, _return = 0;
	for (i = 0; i < 8; i++)
	{
		_return <<= 1;
		_return |= DHT11_ReadBit(DHTxx);
	}

	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：DHT11读取状态啊，每间隔2秒，才能读取到正确数据
//////输入参数:
//////输出参数:
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DHT11_ReadSTATE(DHT11_HandleType* DHTxx)
{
	UINT32_T nowTime = DHTxx->pMsgTimeTick();
	UINT32_T cnt = 0;
	if (DHTxx->msgSTATE == DHT11_READ_ERROR)
	{
		return ERROR_1;
	}
	//===计算时间间隔
	//---判断滴答定时是否发生溢出操作
	if (DHTxx->msgRecordTick > nowTime)
	{
		cnt = (0xFFFFFFFF - nowTime + DHTxx->msgRecordTick);
	}
	else
	{
		cnt = nowTime-DHTxx->msgRecordTick;
	}
	if (cnt>DHT11_READ_INTERVAL_MS)
	{
		DHTxx->msgSTATE=DHT11_READ_OK;
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
UINT8_T DHT11_ReadTempHumi(DHT11_HandleType *DHT11x)
{
	UINT8_T temp[5] = { 0 };
	UINT8_T i = 0;
	//---获取当前的状态
	if (DHT11_ReadSTATE(DHT11x)!=OK_0)
	{
		return ERROR_1;
	}
	//---判断数据是否可读
	if (DHT11x->msgSTATE==DHT11_READ_OK)
	{
		return ERROR_2;
	}
	//---启动数据的读取并检查设备是否存在
	if (DHT11_START(DHT11x) != OK_0)
	{
		return ERROR_3;
	}
	//---读取数据
	for (i = 0; i < 5; i++)
	{
		temp[i] = DHT11_ReadByte(DHT11x);
	}
	//---释放总线
	GPIO_OUT_1(DHT11x->msgDAT.msgPort, DHT11x->msgDAT.msgBit);
	//---数据校验
	if ((temp[0] + temp[1] + temp[2] + temp[3]) != temp[4])
	{
		return ERROR_4;
	}
	//---湿度整数部分
	DHT11x->msgHumiX1000 = temp[0];
	//---湿度小数部分
	DHT11x->msgHumiX1000 = (DHT11x->msgHumiX1000 * 1000) + temp[1];
	//---温度整数部分
	DHT11x->msgTempX1000 = temp[2];
	//---温度小数部分
	if ((temp[3]&0x80)!=0)
	{
		//---温度数据是负数
		DHT11x->msgPositive=1;
	}
	else
	{
		//---温度数据是正数
		DHT11x->msgPositive =0;
	}
	DHT11x->msgTempX1000 = (DHT11x->msgTempX1000 * 1000) + (temp[3]&0x7F);
	//---设置当前状态为忙碌模式
	DHT11x->msgSTATE= DHT11_READ_BUSY;
	//---重置时间标签
	DHT11x->msgRecordTick = DHT11x->pMsgTimeTick();
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：获取温度值
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
float DHT11_GetTemp(DHT11_HandleType* DHT11x)
{
	float tempVal = DHT11x->msgTempX1000;
	//---转换温度对应实际的温度值
	tempVal /= 1000.0;
	//---校验是不是正数
	if (DHT11x->msgPositive == 1)
	{
		tempVal *= (-1.0);
	}
	return tempVal;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：获取湿度值
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
float DHT11_GetHumi(DHT11_HandleType* DHT11x)
{
	float tempVal = DHT11x->msgHumiX1000;
	//---转换温度对应实际的温度值
	tempVal /= 1000.0;
	//---校验是不是正数
	if (DHT11x->msgPositive == 1)
	{
		tempVal *= (-1.0);
	}
	return tempVal;
}
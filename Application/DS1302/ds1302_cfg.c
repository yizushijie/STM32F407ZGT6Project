#include "ds1302_cfg.h"

//===全局变量定义
DS1302_HandlerType		g_Ds1302Device0 = { 0 };
pDS1302_HandlerType		pDs1302Device0 = &g_Ds1302Device0;

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DS1302_Device0_Init(DS1302_HandlerType *DS1302x)
{
	DS1302x->msgCS.msgGPIOPort = GPIOB;
	DS1302x->msgCS.msgGPIOBit = LL_GPIO_PIN_5;

	DS1302x->msgCLK.msgGPIOPort = GPIOB;
	DS1302x->msgCLK.msgGPIOBit = LL_GPIO_PIN_6;

	DS1302x->msgDAT.msgGPIOPort = GPIOB;
	DS1302x->msgDAT.msgGPIOBit = LL_GPIO_PIN_8;

	DS1302x->msgPluseWidth = 1000;
	DS1302x->msgDelayus = NULL;

	//---使能端口时钟
	GPIOTask_Clock(DS1302x->msgCS.msgGPIOPort, 1);
	GPIOTask_Clock(DS1302x->msgCLK.msgGPIOPort, 1);
	GPIOTask_Clock(DS1302x->msgDAT.msgGPIOPort, 1);

	//---GPIO的结构体
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;						//---配置状态为输出模式
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;				//---GPIO的速度---低速设备
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;			//---输出模式---推挽输出
	GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;							//---上拉
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---端口复用模式
#endif

	//---CS端口的初始化
	GPIO_InitStruct.Pin = DS1302x->msgCS.msgGPIOBit;
	LL_GPIO_Init(DS1302x->msgCS.msgGPIOPort, &GPIO_InitStruct);
	GPIO_OUT_0(DS1302x->msgCS.msgGPIOPort, DS1302x->msgCS.msgGPIOBit);

	//---CLK端口的初始化
	GPIO_InitStruct.Pin = DS1302x->msgCLK.msgGPIOBit;
	LL_GPIO_Init(DS1302x->msgCLK.msgGPIOPort, &GPIO_InitStruct);
	GPIO_OUT_0(DS1302x->msgCLK.msgGPIOPort, DS1302x->msgCLK.msgGPIOBit);

	//---DAT端口的初始化
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
	GPIO_InitStruct.Pin = DS1302x->msgDAT.msgGPIOBit;
	LL_GPIO_Init(DS1302x->msgDAT.msgGPIOPort, &GPIO_InitStruct);
	GPIO_OUT_1(DS1302x->msgDAT.msgGPIOPort, DS1302x->msgDAT.msgGPIOBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DS1302_Device1_Init(DS1302_HandlerType *DS1302x)
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
UINT8_T DS1302_Device2_Init(DS1302_HandlerType *DS1302x)
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
UINT8_T DS1302_Init(DS1302_HandlerType *DS1302x, void(*pFuncDelayus)(UINT32_T delay))
{
	//---指定设备的初始化
	if ((DS1302x != NULL) && (DS1302x == DS1302_TASK_ONE))
	{
		DS1302_Device0_Init(DS1302x);
	}
	else if ((DS1302x != NULL) && (DS1302x == DS1302_TASK_TWO))
	{
		DS1302_Device1_Init(DS1302x);
	}
	else if ((DS1302x != NULL) && (DS1302x == DS1302_TASK_THREE))
	{
		DS1302_Device2_Init(DS1302x);
	}
	else
	{
		return ERROR_1;
	}

   //---us延时
	if (pFuncDelayus!=NULL)
	{
		DS1302x->msgDelayus = pFuncDelayus;
	}
	else
	{
		DS1302x->msgDelayus = DelayTask_us;
	}
	//---退出休眠模式
	DS1302_DisableSleepMode(DS1302x);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void DS1302_WriteByteLSB(DS1302_HandlerType* DS1302x, UINT8_T wVal)
{
	UINT8_T i = 0;
	for (i=0;i<8;i++)
	{
		if ((wVal&0x01)!=0)
		{
			GPIO_OUT_1(DS1302x->msgDAT.msgGPIOPort, DS1302x->msgDAT.msgGPIOBit);
		}
		else
		{
			GPIO_OUT_0(DS1302x->msgDAT.msgGPIOPort, DS1302x->msgDAT.msgGPIOBit);
		}
		GPIO_OUT_0(DS1302x->msgCLK.msgGPIOPort, DS1302x->msgCLK.msgGPIOBit);
		if (DS1302x->msgPluseWidth > 0)
		{
			DS1302x->msgDelayus(DS1302x->msgPluseWidth);
		}
		GPIO_OUT_1(DS1302x->msgCLK.msgGPIOPort, DS1302x->msgCLK.msgGPIOBit);
		if (DS1302x->msgPluseWidth > 0)
		{
			DS1302x->msgDelayus(DS1302x->msgPluseWidth);
		}
		wVal >>= 1;
	}
	//---??????
	GPIO_OUT_1(DS1302x->msgDAT.msgGPIOPort, DS1302x->msgDAT.msgGPIOBit);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DS1302_ReadByteLSB(DS1302_HandlerType* DS1302x)
{
	UINT8_T i = 0;
	UINT8_T _return = 0;
	for (i = 0; i < 8; i++)
	{
		GPIO_OUT_0(DS1302x->msgCLK.msgGPIOPort, DS1302x->msgCLK.msgGPIOBit);
		if (DS1302x->msgPluseWidth > 0)
		{
			DS1302x->msgDelayus(DS1302x->msgPluseWidth);
		}	
		_return >>= 1;
		//---读取1bit的数据
		if (GPIO_GET_STATE(DS1302x->msgDAT.msgGPIOPort, DS1302x->msgDAT.msgGPIOBit) != 0)
		{
			_return |= 0x80;
		}
		else
		{
			_return &= 0x7F;
		}
		GPIO_OUT_1(DS1302x->msgCLK.msgGPIOPort, DS1302x->msgCLK.msgGPIOBit);
		if (DS1302x->msgPluseWidth > 0)
		{
			DS1302x->msgDelayus(DS1302x->msgPluseWidth);
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：DS1302退出休眠模式
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void DS1302_DisableSleepMode(DS1302_HandlerType* DS1302x)
{
	UINT8_T _return = 0x00;
	DS1302_ReadReg(DS1302x, DS1302_REG_SECOND, &_return);
	if ((_return&0x80)!=0)
	{
		//---退出休眠模式
		DS1302_WriteTime(DS1302x,DS1302_REG_SECOND,_return&0x7F);
		DS1302x->msgRTC.second = BcdToDec(_return & 0x7F);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：DS1302进入休眠模式
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void  DS1302_EnableSleepMode(DS1302_HandlerType* DS1302x)
{
	//---使能休眠模式
	DS1302_WriteTime(DS1302x, DS1302_REG_SECOND, 0x80);
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：检查DS1302是否存在，首先保证设备已经进入工作模式，不是休眠模式，否则结果不对
//////输入参数:
//////输出参数: 0---设备存在，1---设备异常
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DS1302_CheckDevice(DS1302_HandlerType* DS1302x)
{
	UINT8_T _return = 0x00;
	DS1302_ReadReg(DS1302x, DS1302_REG_SECOND, &_return);
	if ((_return & 0x80) != 0)
	{
		_return = ERROR_1;
	}
	else
	{
		_return = OK_0;
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
void DS1302_WriteReg(DS1302_HandlerType *DS1302x, UINT8_T addr, UINT8_T dat)
{
	GPIO_OUT_0(DS1302x->msgCS.msgGPIOPort, DS1302x->msgCS.msgGPIOBit);
	GPIO_OUT_0(DS1302x->msgCLK.msgGPIOPort, DS1302x->msgCLK.msgGPIOBit);
	if (DS1302x->msgPluseWidth > 0)
	{
		DS1302x->msgDelayus(DS1302x->msgPluseWidth);
	}
	GPIO_OUT_1(DS1302x->msgCS.msgGPIOPort, DS1302x->msgCS.msgGPIOBit);
	if (DS1302x->msgPluseWidth > 0)
	{
		DS1302x->msgDelayus(DS1302x->msgPluseWidth);
	}
	DS1302_WriteByteLSB(DS1302x, addr&0xFE);
	DS1302_WriteByteLSB(DS1302x, dat);
	GPIO_OUT_0(DS1302x->msgCLK.msgGPIOPort, DS1302x->msgCLK.msgGPIOBit);
	if (DS1302x->msgPluseWidth > 0)
	{
		DS1302x->msgDelayus(DS1302x->msgPluseWidth);
	}
	GPIO_OUT_0(DS1302x->msgCS.msgGPIOPort, DS1302x->msgCS.msgGPIOBit);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void DS1302_ReadReg(DS1302_HandlerType *DS1302x, UINT8_T addr, UINT8_T *pVal)
{
	GPIO_OUT_0(DS1302x->msgCS.msgGPIOPort, DS1302x->msgCS.msgGPIOBit);
	GPIO_OUT_0(DS1302x->msgCLK.msgGPIOPort, DS1302x->msgCLK.msgGPIOBit);
	if (DS1302x->msgPluseWidth > 0)
	{
		DS1302x->msgDelayus(DS1302x->msgPluseWidth);
	}
	GPIO_OUT_1(DS1302x->msgCS.msgGPIOPort, DS1302x->msgCS.msgGPIOBit);
	if (DS1302x->msgPluseWidth > 0)
	{
		DS1302x->msgDelayus(DS1302x->msgPluseWidth);
	}
	DS1302_WriteByteLSB(DS1302x, addr|0x01);
	*pVal=DS1302_ReadByteLSB(DS1302x);
	GPIO_OUT_0(DS1302x->msgCLK.msgGPIOPort, DS1302x->msgCLK.msgGPIOBit);
	if (DS1302x->msgPluseWidth > 0)
	{
		DS1302x->msgDelayus(DS1302x->msgPluseWidth);
	}
	GPIO_OUT_0(DS1302x->msgCS.msgGPIOPort, DS1302x->msgCS.msgGPIOBit);	
	
}
///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：编程时间
//////////////////////////////////////////////////////////////////////////////
void DS1302_WriteTime(DS1302_HandlerType *DS1302x, UINT8_T addr, UINT8_T dat)
{
	//---取消写保护
	DS1302_WriteReg(DS1302x, DS1302_REG_CONTROL, 0x00);
	//---在指定的位置写入指定的数据
	DS1302_WriteReg(DS1302x, addr, dat);
	//---打开写保护
	DS1302_WriteReg(DS1302x, DS1302_REG_CONTROL, 0x80);
}
///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：读取时间
//////////////////////////////////////////////////////////////////////////////
void DS1302_ReadTime(DS1302_HandlerType *DS1302x, UINT8_T addr, UINT8_T *pVal)
{
	DS1302_ReadReg(DS1302x, addr, pVal);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：编程实时时钟
//////////////////////////////////////////////////////////////////////////////
void DS1302_WriteRTC(DS1302_HandlerType *DS1302x, RTC_HandlerType rtcTime)
{
	DS1302x->msgRTC = rtcTime;
	//---取消写保护
	DS1302_WriteReg(DS1302x, DS1302_REG_CONTROL, 0x00);
	//---写秒数据,数据转BCD格式
	DS1302_WriteReg(DS1302x, DS1302_REG_SECOND, DecToBcd((rtcTime.second)&0x7F));
	//---写分数据,数据转BCD格式
	DS1302_WriteReg(DS1302x, DS1302_REG_MINUTE, DecToBcd(rtcTime.minute));
	//---写时数据,数据转BCD格式
	DS1302_WriteReg(DS1302x, DS1302_REG_HOUR, DecToBcd(rtcTime.hour));
	//---写日数据,数据转BCD格式
	DS1302_WriteReg(DS1302x, DS1302_REG_DAY, DecToBcd(rtcTime.day));
	//---写星期数据,数据转BCD格式
	DS1302_WriteReg(DS1302x, DS1302_REG_WEEK, DecToBcd(rtcTime.week));
	//---写月数据,数据转BCD格式
	DS1302_WriteReg(DS1302x, DS1302_REG_MONTH, DecToBcd(rtcTime.month));
	//---写年数据,数据转BCD格式
	DS1302_WriteReg(DS1302x, DS1302_REG_YEAR, DecToBcd(rtcTime.year));
	//---打开写保护
	DS1302_WriteReg(DS1302x, DS1302_REG_CONTROL, 0x80);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：读取实时时钟
//////////////////////////////////////////////////////////////////////////////
void DS1302_ReadRTC(DS1302_HandlerType *DS1302x)
{
	//---读秒数据
	DS1302_ReadReg(DS1302x, DS1302_REG_SECOND, &(DS1302x->msgRTC.second));
	//---BCD转数据
	DS1302x->msgRTC.second = BcdToDec(DS1302x->msgRTC.second);
	//---读分数据
	DS1302_ReadReg(DS1302x, DS1302_REG_MINUTE, &(DS1302x->msgRTC.minute));
	//---BCD转数据
	DS1302x->msgRTC.minute = BcdToDec(DS1302x->msgRTC.minute);
	//---读时数据
	DS1302_ReadReg(DS1302x, DS1302_REG_HOUR, &(DS1302x->msgRTC.hour));

	if ((DS1302x->msgRTC.hour&0x80)!=0)
	{
		//---表示12小时制
		DS1302x->msgRTC.time24H = 0;
	}
	else
	{
		//---表示24小时制
		DS1302x->msgRTC.time24H = 1;
	}
	
	if ((DS1302x->msgRTC.hour & 0x20) == 0)
	{
		//---表示上午
		DS1302x->msgAMOrPM = 0;
	}
	else
	{
		//---表示上午
		DS1302x->msgAMOrPM = 0;
	}

	//---BCD转数据
	DS1302x->msgRTC.hour = BcdToDec(DS1302x->msgRTC.hour&=(DS1302x->msgRTC.time24H==1?0x3F:0x1F));
	//---读日数据
	DS1302_ReadReg(DS1302x, DS1302_REG_DAY, &(DS1302x->msgRTC.day));
	//---BCD转数据
	DS1302x->msgRTC.day = BcdToDec(DS1302x->msgRTC.day);
	//---读星期数据
	DS1302_ReadReg(DS1302x, DS1302_REG_WEEK, &(DS1302x->msgRTC.week));
	//---BCD转数据
	DS1302x->msgRTC.week = BcdToDec(DS1302x->msgRTC.week);
	//---读月数据
	DS1302_ReadReg(DS1302x, DS1302_REG_MONTH, &(DS1302x->msgRTC.month));
	//---BCD转数据
	DS1302x->msgRTC.month = BcdToDec(DS1302x->msgRTC.month);
	//---读年数据
	DS1302_ReadReg(DS1302x, DS1302_REG_YEAR, &(DS1302x->msgRTC.year));
	//---BCD转数据
	DS1302x->msgRTC.year = BcdToDec(DS1302x->msgRTC.year);
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：连续读取所有的数据
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void DS1302_ReadBurstRTC(DS1302_HandlerType* DS1302x)
{
	UINT8_T i = 0;
	UINT8_T rtc[7] = {0};
	DS1302_WriteByteLSB(DS1302x, DS1302_BURST_READ_RAM | 0x01);
	for (i=0;i<7;i++)
	{
		rtc[i]= DS1302_ReadByteLSB(DS1302x);
	}
	//---读秒数据---BCD转数据
	DS1302x->msgRTC.second = BcdToDec(rtc[0]);
	//-----BCD转数据
	DS1302x->msgRTC.minute = BcdToDec(rtc[1]);
	//---读时数据
	DS1302x->msgRTC.hour = BcdToDec(rtc[2]);
	if ((DS1302x->msgRTC.hour & 0x80) != 0)
	{
		//---表示12小时制
		DS1302x->msgRTC.time24H = 0;
	}
	else
	{
		//---表示24小时制
		DS1302x->msgRTC.time24H = 1;
	}

	if ((DS1302x->msgRTC.hour & 0x20) == 0)
	{
		//---表示上午
		DS1302x->msgAMOrPM = 0;
	}
	else
	{
		//---表示上午
		DS1302x->msgAMOrPM = 0;
	}

	//---BCD转数据
	DS1302x->msgRTC.hour = BcdToDec(DS1302x->msgRTC.hour &= (DS1302x->msgRTC.time24H == 1 ? 0x3F : 0x1F));
	//---读日数据---BCD转数据
	DS1302x->msgRTC.day = BcdToDec(rtc[3]);
	//---读星期数据---BCD转数据
	DS1302x->msgRTC.week = BcdToDec(rtc[5]);
	//---读月数据---BCD转数据
	DS1302x->msgRTC.month = BcdToDec(rtc[4]);
	//---读年数据---BCD转数据
	DS1302x->msgRTC.year = BcdToDec(rtc[6]);
}
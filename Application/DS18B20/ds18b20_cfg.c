#include "ds18b20_cfg.h"

//---变量定义
DS18B20_HandlerType g_Ds18b20Device0 = { 0 };
pDS18B20_HandlerType pDs18b20Device0 = &g_Ds18b20Device0;

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设备1的初始化
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DS18B20_OneWire_Device0_Init(DS18B20_HandlerType *DS18B20x)
{
	DS18B20x->msgOneWire.msgDAT.msgGPIOBit = LL_GPIO_PIN_2;
	DS18B20x->msgOneWire.msgDAT.msgGPIOPort = GPIOC;
	DS18B20x->msgTempBit=3;
	DS18B20x->msgIntervalTime=800;
	DS18B20x->msgTempBitValX10000=625;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设备2的初始化
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DS18B20_OneWire_Device1_Init(DS18B20_HandlerType *DS18B20x)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设备3的初始化
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DS18B20_OneWire_Device2_Init(DS18B20_HandlerType *DS18B20x)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：初始化指定设备
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DS18B20_OneWire_Init(DS18B20_HandlerType *DS18B20x, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void))
{
	if ((DS18B20x != NULL) && (DS18B20x == DS18B20_TASK_ONE))
	{
		DS18B20_OneWire_Device0_Init(DS18B20x);
	}
	else if ((DS18B20x != NULL) && (DS18B20x == DS18B20_TASK_TWO))
	{
		DS18B20_OneWire_Device1_Init(DS18B20x);
	}
	else if ((DS18B20x != NULL) && (DS18B20x == DS18B20_TASK_THREE))
	{
		DS18B20_OneWire_Device2_Init(DS18B20x);
	}
	else
	{
		return  ERROR_1;
	}

	//---注册延时函数
	if (pFuncDelayms != NULL)
	{
		DS18B20x->msgDelayms = pFuncDelayms;
	}
	else
	{
		DS18B20x->msgDelayms = DelayTask_ms;
	}
	//---注册滴答函数
	if (pFuncTimerTick != NULL)
	{
		DS18B20x->msgTimeTick = pFuncTimerTick;
	}
	else
	{
		DS18B20x->msgTimeTick = SysTickTask_GetTick;
	}
	//---当前时间
	DS18B20x->msgRecordTime = DS18B20x->msgTimeTick();
	//---配置基本参数
	return DS18B20_OneWire_Config(DS18B20x,pFuncDelayus);
	//return OneWireTask_Init(&(DS18B20x->msgOneWire), pFuncDelayus);
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：销毁指定的设备
//////输入参数:
//////输出参数:
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DS18B20_OneWire_DeInit(DS18B20_HandlerType *DS18B20x)
{
	return OneWireTask_DeInit(&(DS18B20x->msgOneWire));
}
///////////////////////////////////////////////////////////////////////////////
//////函	   数： UINT8_T Ds18b20Cfg_Start(void)
//////功	   能： 启动Ds18b20Cfg
//////输入参数:
//////输出参数: 0---失败;1---表示成功
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DS18B20_OneWire_START(DS18B20_HandlerType *DS18B20x)
{
	return OneWireTask_START(&(DS18B20x->msgOneWire));
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数： void Ds18b20Cfg_WriteByte(UINT8_T val)
//////功	   能： 写入一字节的数据
//////输入参数: 写入的值
//////输出参数: 无
//////说	   明：
///////////////////////////////////////////////////////////////////////////////
UINT8_T DS18B20_OneWire_WriteByte(DS18B20_HandlerType *DS18B20x, UINT8_T val)
{
	return OneWireTask_WriteByte(&(DS18B20x->msgOneWire), val);
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数： UINT8_T Ds18b20Cfg_ReadByte(void)
//////功	   能： 读取一字节的数据
//////输入参数: 无
//////输出参数: 读取的数据
//////说	   明：
///////////////////////////////////////////////////////////////////////////////
UINT8_T DS18B20_OneWire_ReadByte(DS18B20_HandlerType *DS18B20x)
{
	return OneWireTask_ReadByte(&(DS18B20x->msgOneWire));
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取温度的分辨率
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DS18B20_OneWire_ReadTempBit(DS18B20_HandlerType* DS18B20x,UINT8_T *pTempBit)
{
	UINT8_T tempBit[3]={0};
	UINT8_T i=0;
	//---总线复位
	if (DS18B20_OneWire_START(DS18B20x) == 0)
	{
		return ERROR_1;
	}
	//---忽略地址匹配
	DS18B20_OneWire_WriteByte(DS18B20x, 0xCC);
	//---读取暂存寄存器的值
	DS18B20_OneWire_WriteByte(DS18B20x, 0xBE);
	//---读取温度分辨率信息
	for (i = 0; i < 3; i++)
	{
		tempBit[i] = DS18B20_OneWire_ReadByte(DS18B20x);
	}
	DS18B20x->msgTempTH = tempBit[0];
	DS18B20x->msgTempTL = tempBit[1];
	//DS18B20x->msgTempBit=tempBit[2];
	tempBit[2]&=0x60;
	tempBit[2]>>=5;
	*pTempBit=tempBit[2];
	//----总线复位
	DS18B20_OneWire_START(DS18B20x);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：写入温度的分辨率
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DS18B20_OneWire_WriteTempBit(DS18B20_HandlerType* DS18B20x, UINT8_T tempBit)
{
	UINT8_T i = 0;
	//---总线复位
	if (DS18B20_OneWire_START(DS18B20x) == 0)
	{
		return ERROR_1;
	}
	DS18B20x->msgTempBit=tempBit;
	//--9Bit
	if (tempBit==0)
	{
		DS18B20x->msgIntervalTime=100;
		DS18B20x->msgTempBitValX10000=5000;
	}
	//---10Bit
	else if (tempBit == 1)
	{
		DS18B20x->msgIntervalTime = 200;
		DS18B20x->msgTempBitValX10000 = 2500;
	}
	//---11Bit
	else if (tempBit == 1)
	{
		DS18B20x->msgIntervalTime = 400;
		DS18B20x->msgTempBitValX10000 = 1250;
	}
	//---12Bit
	else
	{
		DS18B20x->msgIntervalTime = 800;
		DS18B20x->msgTempBitValX10000 = 625;
	}
	tempBit<<=5;
	tempBit|=0x1F;
	//---忽略地址匹配
	DS18B20_OneWire_WriteByte(DS18B20x, 0xCC);
	//---读取暂存寄存器的值
	DS18B20_OneWire_WriteByte(DS18B20x, 0x4E);
	//---读取暂存寄存器的值
	DS18B20_OneWire_WriteByte(DS18B20x, DS18B20x->msgTempTH);
	DS18B20_OneWire_WriteByte(DS18B20x, DS18B20x->msgTempTL);
	//---写入温度分辨率
	DS18B20_OneWire_WriteByte(DS18B20x, tempBit);
	//----总线复位
	DS18B20_OneWire_START(DS18B20x);
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：读取设备的ID信息
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DS18B20_OneWire_ReadID(DS18B20_HandlerType *DS18B20x, UINT8_T *id)
{
	UINT8_T i;
	//---总线复位
	if (DS18B20_OneWire_START(DS18B20x) == 0)
	{
		return ERROR_1;
	}
	//---发命令
	DS18B20_OneWire_WriteByte(DS18B20x, 0x33);
	//---读取设备的ID信息
	for (i = 0; i < 8; i++)
	{
		id[i] = DS18B20_OneWire_ReadByte(DS18B20x);
	}

	//----总线复位
	DS18B20_OneWire_START(DS18B20x);
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：开始转换,忽略ID匹配
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT16_T DS18B20_OneWire_StartConvert(DS18B20_HandlerType* DS18B20x)
{
	//---总线复位
	if (DS18B20_OneWire_START(DS18B20x) == 0)
	{
		return ERROR_1;
	}
	//---忽略地址匹配
	DS18B20_OneWire_WriteByte(DS18B20x, 0xCC);
	//---启动转换
	DS18B20_OneWire_WriteByte(DS18B20x, 0x44);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：当期状态
//////输入参数:
//////输出参数: 0---可以读取；1---间隔读取时间还没有到达，不允许读取
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT16_T DS18B20_OneWire_STATE(DS18B20_HandlerType* DS18B20x)
{
	UINT32_T nowTime = DS18B20x->msgTimeTick();
	UINT32_T cnt = 0;
	//---判断滴答定时是否发生溢出操作
	if (DS18B20x->msgRecordTime > nowTime)
	{
		cnt = (0xFFFFFFFF - nowTime + DS18B20x->msgRecordTime);
	}
	else
	{
		cnt = nowTime-DS18B20x->msgRecordTime;
	}
	if (cnt > DS18B20x->msgIntervalTime)
	{
		return OK_0;
	}
	else
	{
		return ERROR_1;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数： UINT16_T DS18B20_GetWenDu(DS18B20_HandlerType *DS18B20HandlerType)
//////功	   能： 获取温度值
//////输入参数: 无
//////输出参数: 放大100倍之后的温度的值
//////说	   明：
///////////////////////////////////////////////////////////////////////////////
UINT16_T DS18B20_OneWire_ReadTemp(DS18B20_HandlerType *DS18B20x)
{
	UINT16_T _return = 0;
	UINT16_T tempH = 0;
	UINT8_T tempL;
	//---检查是否到达下次的读取的时间
	_return= DS18B20_OneWire_STATE(DS18B20x);
	if (_return!=OK_0)
	{
		return ERROR_1;
	}
	//---读取数据之前首先设置为数据无效，避免其他设备使用
	DS18B20x->msgIsPositive = 0;
	//---延时等待
	DS18B20x->msgDelayms(1);
	//---初始化温度传感器---总线复位
	DS18B20_OneWire_START(DS18B20x);
	//---忽略地址
	DS18B20_OneWire_WriteByte(DS18B20x, 0xCC);
	//---读取温度
	DS18B20_OneWire_WriteByte(DS18B20x, 0xBE);
	//---读取低位
	tempL = DS18B20_OneWire_ReadByte(DS18B20x);
	//---读取高位
	tempH = DS18B20_OneWire_ReadByte(DS18B20x);
	//---获取温度码值
	_return = (tempH << 8) | tempL;
	//---判断温度是正值还是负值
	if ((tempH & 0x80) == 0)
	{
		//---读取的温度是正值
		DS18B20x->msgIsPositive = 2;
	}
	else
	{
		//===读取的温度是负值
		DS18B20x->msgIsPositive = 1;
	}
	//---读取的温度值
	tempH = _return;
	//---保留有效位数据
	tempH &= 0x0FFF;
	//---获取温度值对应的16进制的数据
	if (DS18B20x->msgIsPositive == 2)
	{
		DS18B20x->msgTempX10000 = tempH;
	}
	else
	{
		DS18B20x->msgTempX10000 = 0x1000 - tempH;
	}
	//---将十六进制数转换成温度值
	DS18B20x->msgTempX10000 *= DS18B20x->msgTempBitValX10000;//625;
	//---获取实际温度值
	DS18B20x->msgTempX100 = (UINT16_T)(DS18B20x->msgTempX10000 / 100);
	//---启动下次转换
	DS18B20_OneWire_StartConvert(DS18B20x);
	//---返回温度码的值
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT16_T DS18B20_OneWire_ReadTempByID(DS18B20_HandlerType *DS18B20x, UINT8_T *id)
{
	UINT16_T _return = 0, temH = 0;
	UINT8_T temL = 0, i = 0;

	//---启动温度传感器---总线复位
	DS18B20_OneWire_START(DS18B20x);
	//---忽略地址
	DS18B20_OneWire_WriteByte(DS18B20x, 0x55);
	//---写入ROM的ID
	for (i = 0; i < 8; i++)
	{
		DS18B20_OneWire_WriteByte(DS18B20x, id[i]);
	}
	//---启动转换
	DS18B20_OneWire_WriteByte(DS18B20x, 0x44);
	//---延时等待
	DS18B20x->msgDelayms(1);
	//---初始化温度传感器---总线复位
	DS18B20_OneWire_START(DS18B20x);
	//---忽略地址
	DS18B20_OneWire_WriteByte(DS18B20x, 0x55);
	//---写入ROM的ID
	for (i = 0; i < 8; i++)
	{
		DS18B20_OneWire_WriteByte(DS18B20x, id[i]);
	}
	//---读取温度
	DS18B20_OneWire_WriteByte(DS18B20x, 0xBE);
	//---读取低位
	temL = DS18B20_OneWire_ReadByte(DS18B20x);
	//---读取高位
	temH = DS18B20_OneWire_ReadByte(DS18B20x);
	//---获取温度码值
	_return = (temH << 8) | temL;

	//---判断温度是正值还是负值
	if ((temH & 0x80) == 0)
	{
		//---读取的温度是正值
		DS18B20x->msgIsPositive = 0;
	}
	else
	{
		//===读取的温度是负值
		DS18B20x->msgIsPositive = 1;
	}
	//---读取的温度值
	temH = _return;
	//---保留有效位数据
	temH &= 0x0FFF;
	//---获取温度值对应的16进制的数据
	if (DS18B20x->msgIsPositive == 0)
	{
		DS18B20x->msgTempX10000 = temH;
	}
	else
	{
		DS18B20x->msgTempX10000 = 4096 - temH;
	}
	//---将十六进制数转换成温度值
	DS18B20x->msgTempX10000 *= DS18B20x->msgTempBitValX10000;;
	//---获取实际温度值
	DS18B20x->msgTempX100 = (UINT16_T)(DS18B20x->msgTempX10000 / 100);
	//---启动下次转换
	DS18B20_OneWire_StartConvert(DS18B20x);
	//---返回温度码的值
	return _return;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：配置初始化
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DS18B20_OneWire_Config(DS18B20_HandlerType* DS18B20x,void(*pFuncDelayus)(UINT32_T delay))
{
	UINT8_T _return=0;
	//---初始化一线接口的参数
	OneWireTask_Init(&(DS18B20x->msgOneWire), pFuncDelayus);
	//---读取端口的参数配置，特别是温度的分辨率
	DS18B20_OneWire_ReadTempBit(DS18B20x,&_return);
	if (_return!=DS18B20x->msgTempBit)
	{
		//---配置温度分辨率
		DS18B20_OneWire_WriteTempBit(DS18B20x, DS18B20x->msgTempBit);
	}
	//---启动装换
	return DS18B20_OneWire_StartConvert(DS18B20x);
}
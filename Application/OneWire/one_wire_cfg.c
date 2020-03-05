#include "one_wire_cfg.h"

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：
//////输入参数:
//////输出参数:
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T OneWire_Init(OneWire_HandleType *OneWirex, void(*pFuncDelayus)(UINT32_T delay))
{
	//---使能端口时钟
	#ifndef  USE_FULL_GPIO
	GPIOTask_Clock(OneWirex->msgDAT.msgPort, PERIPHERAL_CLOCK_ENABLE);
	#endif
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	//---GPIO的初始化
	GPIO_InitStruct.Pin = OneWirex->msgDAT.msgBit;												//---对应的GPIO的引脚
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;														//---配置状态为输出模式
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;											//---GPIO的速度
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;											//---输出模式---开漏输出
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;															//---上拉使能
	//---初始化端口
	LL_GPIO_Init(OneWirex->msgDAT.msgPort, &GPIO_InitStruct);
	//---端口输出高电平
	GPIO_OUT_1(OneWirex->msgDAT.msgPort, OneWirex->msgDAT.msgBit);
	//---延时函数
	(pFuncDelayus != NULL)?(OneWirex->pMsgDelayus = pFuncDelayus):(OneWirex->pMsgDelayus = DelayTask_us);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：
//////输入参数:
//////输出参数:
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T OneWire_DeInit(OneWire_HandleType *OneWirex)
{
	LL_GPIO_DeInit(OneWirex->msgDAT.msgPort);
	GPIO_OUT_1(OneWirex->msgDAT.msgPort, OneWirex->msgDAT.msgBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：
//////输入参数:
//////输出参数:
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T OneWire_START(OneWire_HandleType *OneWirex)
{
	UINT8_T _return = OK_0;
	//---设置为输出且输出零
	GPIO_OUT_0(OneWirex->msgDAT.msgPort, OneWirex->msgDAT.msgBit);
	//>=480
	OneWirex->pMsgDelayus(500);
	//---输出高电平
	GPIO_OUT_1(OneWirex->msgDAT.msgPort, OneWirex->msgDAT.msgBit);
	//15us~60us之间
	OneWirex->pMsgDelayus(50);
	_return = GPIO_GET_STATE(OneWirex->msgDAT.msgPort, OneWirex->msgDAT.msgBit);
	//60us~240us
	OneWirex->pMsgDelayus(200);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：
//////输入参数:
//////输出参数:
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T OneWire_WriteBit(OneWire_HandleType *OneWirex, UINT8_T bitVal)
{
	//---控制总线，强制拉低
	GPIO_OUT_0(OneWirex->msgDAT.msgPort, OneWirex->msgDAT.msgBit);
	//=4
	OneWirex->pMsgDelayus(4);
	//---发送数据
	if (bitVal)
	{
		//---释放总线
		GPIO_OUT_1(OneWirex->msgDAT.msgPort, OneWirex->msgDAT.msgBit);
	}
	//=60us
	OneWirex->pMsgDelayus(50);
	//---释放总线
	GPIO_OUT_1(OneWirex->msgDAT.msgPort, OneWirex->msgDAT.msgBit);
	//=4
	OneWirex->pMsgDelayus(4);
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：
//////输入参数:
//////输出参数:
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T OneWire_ReadBit(OneWire_HandleType *OneWirex)
{
	UINT8_T _return = 0;
	//---控制总线,强制拉低
	GPIO_OUT_0(OneWirex->msgDAT.msgPort, OneWirex->msgDAT.msgBit);
	//=8
	OneWirex->pMsgDelayus(8);
	//---释放总线
	GPIO_OUT_1(OneWirex->msgDAT.msgPort, OneWirex->msgDAT.msgBit);
	//=14
	OneWirex->pMsgDelayus(14);
	//---读取数据
	/*if (GPIO_GET_STATE(OneWirex->msgDAT.msgGPIOPort, OneWirex->msgDAT.msgGPIOBit))
	{
		_return = 1;
	}*/
	_return=((GPIO_GET_STATE(OneWirex->msgDAT.msgPort, OneWirex->msgDAT.msgBit) != 0x00) ? 1 : 0);
	//=40
	OneWirex->pMsgDelayus(40);
	//---释放总线
	GPIO_OUT_1(OneWirex->msgDAT.msgPort, OneWirex->msgDAT.msgBit);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：
//////输入参数:
//////输出参数:
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T OneWire_WriteByte(OneWire_HandleType *OneWirex, UINT8_T val)
{
	UINT8_T i = 0;
	for (i = 0; i < 8; i++)
	{
		//---先发送低位数据
		OneWire_WriteBit(OneWirex, (val & 0x01));
		val >>= 1;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：
//////输入参数:
//////输出参数:
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T OneWire_ReadByte(OneWire_HandleType *OneWirex)
{
	UINT8_T _return = 0, i = 0;
	for (i = 0; i < 8; i++)
	{
		_return |= (OneWire_ReadBit(OneWirex) << i);
	}
	//=5
	OneWirex->pMsgDelayus(5);
	return _return;
}
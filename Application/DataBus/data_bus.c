#include "data_bus.h"

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void DataBus_Init(void)
{
	#ifndef  USE_FULL_GPIO
	GPIOTask_Clock(DATA_BUS_DIR_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(DATA_BUS_OE_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(DATA_BUS_PORT, PERIPHERAL_CLOCK_ENABLE);
	#endif
	//---GPIO的结构体
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;																																		//---配置状态为输出模式
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;																															//---GPIO的速度---高速设备
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;																															//---输出模式---推挽输出
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;																																			//---上拉
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;																																		//---端口复用模式
#endif
	//---DATA_OE---输出为高，电平转换芯片为高阻态
	GPIO_InitStruct.Pin = DATA_BUS_OE_BIT;
	LL_GPIO_Init(DATA_BUS_OE_PORT, &GPIO_InitStruct);
	//---DATA_DIR---输出为高，电平转换芯片为高阻态
	GPIO_InitStruct.Pin = DATA_BUS_DIR_BIT;
	LL_GPIO_Init(DATA_BUS_DIR_PORT, &GPIO_InitStruct);
	DATA_BUS_TO_HZ;

	//---TRIG_PULSE---输出为高，
	GPIO_InitStruct.Pin = TRIG_PULSE_BIT;
	LL_GPIO_Init(TRIG_PULSE_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(TRIG_PULSE_PORT, TRIG_PULSE_BIT);
	//---TRIG_OE---输出为低，电平转换芯片为输出
	GPIO_InitStruct.Pin = TRIG_OE_BIT;
	LL_GPIO_Init(TRIG_OE_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(TRIG_OE_PORT, TRIG_OE_BIT);

	//---HVPP_DATA---输入为高
	GPIO_InitStruct.Pin = DATA_BUS_BIT;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	LL_GPIO_Init(DATA_BUS_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(DATA_BUS_PORT, DATA_BUS_BIT);

	DATA_BUS_TO_HOST;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：数据总线为读取模式
//////输入参数: isReadDir---0切换总线为读取模式，1---读取总线数据
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T DataBus_Read(void)
{
	UINT8_T _return = 0;
	UINT8_T temp= DATA_BUS_STATE;
	//---读取数据
	_return |= ((temp&0x80) != 0 ? 0x80 : 0x00);
	_return |= ((temp&0x40) != 0 ? 0x40 : 0x00);
	_return |= ((temp&0x20) != 0 ? 0x20 : 0x00);
	_return |= ((temp&0x10) != 0 ? 0x10 : 0x00);
	_return |= ((temp&0x08) != 0 ? 0x08 : 0x00);
	_return |= ((temp&0x04) != 0 ? 0x04 : 0x00);
	_return |= ((temp&0x02) != 0 ? 0x02 : 0x00);
	_return |= ((temp&0x01) != 0 ? 0x01 : 0x00);
	return _return;
}
#ifndef DS18B20_CFG_H_
#define DS18B20_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "delay_task.h"
	#include "one_wire_task.h"
	#include "systick_task.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===定义结构体
	typedef struct _DS18B20_HandlerType				DS18B20_HandlerType;
	//===定义指针结构
	typedef struct _DS18B20_HandlerType				*pDS18B20_HandlerType;

	//===结构定义
	struct _DS18B20_HandlerType
	{
		UINT8_T					msgIsPositive;														//---0---无数据，1---是负数，2---是正值
		UINT8_T					msgTempBit;															//---0---9Bit,1---10Bit,2---11Bit,3---12Bit
		UINT8_T					msgTempTH;															//---温度上限，7Bit数据，高位为0，代表正值
		UINT8_T					msgTempTL;															//---温度下限，7Bit数据，高位为0，代表正值
		UINT16_T				msgTempX100;														//---温度的值，放大100倍的值
		UINT32_T				msgTempX10000;														//---温度的值，放大1000倍的值
		UINT16_T				msgIntervalTime;													//---轮询时间间隔,单位是ms
		UINT16_T				msgTempBitValX10000;												//---文段分辨率每Bit代表的温度的值
		UINT32_T				msgRecordTime;														//---记录的时间参数
		OneWire_HandlerType		msgOneWire;															//---一线通信
		void(*msgDelayms)(UINT32_T delay);															//---ms延时函数
		UINT32_T(*msgTimeTick)(void);																//---时间节拍
	};

	//===定义的任务函数
	#define DS18B20_TASK_ONE						pDs18b20Device0
	#define DS18B20_TASK_TWO						0
	#define DS18B20_TASK_THREE						0

	//===外部调用接口
	extern DS18B20_HandlerType						g_Ds18b20Device0;
	extern pDS18B20_HandlerType						pDs18b20Device0;

	//===函数的定义
	UINT8_T  DS18B20_OneWire_Init(DS18B20_HandlerType *DS18B20x, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void));
	UINT8_T  DS18B20_OneWire_Device0_Init(DS18B20_HandlerType *DS18B20x);
	UINT8_T  DS18B20_OneWire_Device1_Init(DS18B20_HandlerType *DS18B20x);
	UINT8_T  DS18B20_OneWire_Device2_Init(DS18B20_HandlerType *DS18B20x);
	UINT8_T  DS18B20_OneWire_DeInit(DS18B20_HandlerType *DS18B20x);
	UINT8_T  DS18B20_OneWire_ReadID(DS18B20_HandlerType *DS18B20x, UINT8_T *_id);
	UINT16_T DS18B20_OneWire_ReadTemp(DS18B20_HandlerType *DS18B20x);
	UINT16_T DS18B20_OneWire_ReadTempByID(DS18B20_HandlerType *DS18B20x, UINT8_T *_id);
	UINT8_T  DS18B20_OneWire_Config(DS18B20_HandlerType* DS18B20x, void(*pFuncDelayus)(UINT32_T delay));
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*DS18B20_CFG_H_ */

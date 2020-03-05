#ifndef ONE_WIRE_CFG_H_
#define ONE_WIRE_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	///////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "delay_task.h"
	#include "gpio_task.h"
	///////////////////////////////////////////////////////////////////////////////////////
	//===定义结构体
	typedef struct _OneWire_HandleType		OneWire_HandleType;

	//===定义指针结构体
	typedef struct _OneWire_HandleType		*pOneWire_HandleType;

	//===定义
	struct _OneWire_HandleType
	{
		GPIO_HandleType	msgDAT;																							//---端口号
		void(*pMsgDelayus)(UINT32_T delay);																				//---延时函数
	};

	//===函数定义
	UINT8_T OneWire_Init(OneWire_HandleType *OneWirex, void(*pFuncDelayus)(UINT32_T delay));
	UINT8_T OneWire_DeInit(OneWire_HandleType *OneWirex);
	UINT8_T OneWire_START(OneWire_HandleType *OneWirex);
	UINT8_T OneWire_WriteBit(OneWire_HandleType *OneWirex, UINT8_T bitVal);
	UINT8_T OneWire_ReadBit(OneWire_HandleType *OneWirex);
	UINT8_T OneWire_WriteByte(OneWire_HandleType *OneWirex, UINT8_T val);
	UINT8_T OneWire_ReadByte(OneWire_HandleType *OneWirex);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*ONE_WIRE_CFG_H_ */
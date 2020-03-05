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
	//===����ṹ��
	typedef struct _OneWire_HandleType		OneWire_HandleType;

	//===����ָ��ṹ��
	typedef struct _OneWire_HandleType		*pOneWire_HandleType;

	//===����
	struct _OneWire_HandleType
	{
		GPIO_HandleType	msgDAT;																							//---�˿ں�
		void(*pMsgDelayus)(UINT32_T delay);																				//---��ʱ����
	};

	//===��������
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
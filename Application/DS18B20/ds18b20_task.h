#ifndef DS18B20_TASK_H_
#define DS18B20_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "ds18b20_lib.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//---��������
	UINT8_T DS18B20Task_OneWire_Init(DS18B20_HandlerType *DS18B20x, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void));
	UINT8_T DS18B20Task_OneWire_DeInit(DS18B20_HandlerType *DS18B20x);
	UINT8_T DS18B20Task_OneWire_ReadDeviceID(DS18B20_HandlerType *DS18B20x, UINT8_T *id);
	UINT16_T DS18B20Task_OneWire_ReadTemp(DS18B20_HandlerType *DS18B20x);
	UINT16_T DS18B20Task_OneWire_ReadTempByID(DS18B20_HandlerType *DS18B20x, UINT8_T *id);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*DS18B20_TASK_H_ */

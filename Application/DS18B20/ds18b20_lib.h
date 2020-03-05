#ifndef DS18B20_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "ds18b20_cfg.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//---º¯Êý¶¨Òå
	UINT8_T  DS18B20Lib_OneWire_Init(DS18B20_HandleType *DS18B20x, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void));
	UINT8_T  DS18B20Lib_OneWire_DeInit(DS18B20_HandleType *DS18B20x);
	UINT8_T  DS18B20Lib_OneWire_ReadDeviceID(DS18B20_HandleType *DS18B20x, UINT8_T *pId);
	UINT16_T DS18B20Lib_OneWire_ReadTemp(DS18B20_HandleType *DS18B20x);
	UINT16_T DS18B20Lib_OneWire_ReadTempByID(DS18B20_HandleType *DS18B20x, UINT8_T * pId);
	float	 DS18B20Lib_OneWire_GetTemp(DS18B20_HandleType* DS18B20x);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*DS18B20_LIB_H_ */

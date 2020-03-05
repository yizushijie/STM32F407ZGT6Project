#ifndef	MAX961X_LIB_H_
#define	MAX961X_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "max961x_cfg.h"
	//////////////////////////////////////////////////////////////////////////////////////
	UINT8_T MAX961XLib_I2C_Init(MAX961X_HandleType* MAX961x, void(*pFuncDelayus)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHWI2C);
	UINT8_T MAX961XLib_I2C_DeInit(MAX961X_HandleType* MAX961x);
	UINT8_T MAX961XLib_I2C_CheckDevice(MAX961X_HandleType* MAX961x);
	UINT8_T MAX961XLib_I2C_ReadRSVoltage(MAX961X_HandleType* MAX961x);
	UINT8_T MAX961XLib_I2C_ReadRSCurrent(MAX961X_HandleType* MAX961x, UINT8_T currentGain);
	UINT8_T MAX961XLib_I2C_ReadOutVoltage(MAX961X_HandleType* MAX961x);
	UINT8_T MAX961XLib_I2C_ReadSetVoltage(MAX961X_HandleType* MAX961x);
	UINT8_T MAX961XLib_I2C_ReadTemp(MAX961X_HandleType* MAX961x);
	UINT8_T MAX961XLib_I2C_ReadAll(MAX961X_HandleType* MAX961x, UINT8_T currentGain);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*MAX961X_LIB_H_ */
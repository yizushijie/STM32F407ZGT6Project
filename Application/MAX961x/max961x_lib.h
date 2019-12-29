#ifndef	MAX961X_LIB_H_
#define	MAX961X_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "max961x_cfg.h"
	//////////////////////////////////////////////////////////////////////////////////////
	UINT8_T MAX961XLib_I2C_Init(MAX961X_HandlerType* MAX961x, void(*pFuncDelayus)(UINT32_T delay), UINT8_T isHWI2C);
	UINT8_T MAX961XLib_I2C_CheckDevice(MAX961X_HandlerType* MAX961x);
	UINT8_T MAX961XLib_I2C_GetRSVoltage(MAX961X_HandlerType* MAX961x);
	UINT8_T MAX961XLib_I2C_GetRSCurrent(MAX961X_HandlerType* MAX961x, UINT8_T currentGain);
	UINT8_T MAX961XLib_I2C_GetOutVoltage(MAX961X_HandlerType* MAX961x);
	UINT8_T MAX961XLib_I2C_GetSetVoltage(MAX961X_HandlerType* MAX961x);
	UINT8_T MAX961XLib_I2C_GetTemperature(MAX961X_HandlerType* MAX961x);
	UINT8_T MAX961XLib_I2C_GetAll(MAX961X_HandlerType* MAX961x, UINT8_T currentGain);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*MAX961X_LIB_H_ */
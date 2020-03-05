#ifndef SHT2X_LIB_H_
#define SHT2X_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "sht2x_cfg.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===��������
	UINT8_T SHT2XLib_I2C_Init(SHT2X_HandleType *SHT2x, void(*pFuncDelayus)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHWI2C);
	UINT8_T SHT2XLib_I2C_DeInit(SHT2X_HandleType *SHT2x);
	UINT8_T SHT2XLib_I2C_SoftReset(SHT2X_HandleType *SHT2x);
	UINT8_T SHT2XLib_I2C_GetSerialNumber(SHT2X_HandleType *SHT2x);
	UINT8_T SHT2XLib_I2C_ReadUserReg(SHT2X_HandleType *SHT2x, UINT8_T *pReg);
	UINT8_T SHT2XLib_I2C_WriteUserReg(SHT2X_HandleType *SHT2x, UINT8_T reg);
	UINT8_T SHT2XLib_I2C_ReadTempPoll(SHT2X_HandleType *SHT2x);
	UINT8_T SHT2XLib_I2C_ReadHumiPoll(SHT2X_HandleType *SHT2x);
	UINT8_T SHT2XLib_I2C_ReadTempHM(SHT2X_HandleType *SHT2x);
	UINT8_T SHT2XLib_I2C_ReadHumiHM(SHT2X_HandleType *SHT2x);
	float SHT2XLib_I2C_GetTemp(SHT2X_HandleType* SHT2x);
	float SHT2XLib_I2C_GetHumi(SHT2X_HandleType* SHT2x);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*SHT2X_LIB_H_ */
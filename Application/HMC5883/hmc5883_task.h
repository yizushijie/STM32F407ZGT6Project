#ifndef HMC5883_TASK_H_
#define HMC5883_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "hmc5883_lib.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===º¯Êý¶¨Òå
	UINT8_T HMC5883Task_I2C_Init(HMC5883_HandleType* HMC5883x, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay),UINT32_T(*pFuncTimerTick)(void), UINT8_T isHWI2C);
	UINT8_T HMC5883Task_I2C_DeInit(HMC5883_HandleType* HMC5883x);
	UINT8_T HMC5883Task_I2C_WriteSingle(HMC5883_HandleType* HMC5883x, UINT8_T addr, UINT8_T val);
	UINT8_T HMC5883Task_I2C_ReadSingle(HMC5883_HandleType* HMC5883x, UINT8_T addr, UINT8_T* pVal);
	UINT8_T HMC5883Task_I2C_ReadBulk(HMC5883_HandleType* HMC5883x, UINT8_T addr, UINT8_T* pVal, UINT8_T length);
	UINT8_T HMC5883Task_I2C_ConfigInit(HMC5883_HandleType* HMC5883x);
	UINT8_T HMC5883Task_I2C_ReadRawData(HMC5883_HandleType* HMC5883x);
	void	HMC5883Task_I2C_CalibrateMag(HMC5883_HandleType* HMC5883x);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*HMC5883_TASK_H_ */
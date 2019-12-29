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
	UINT8_T HMC5883Task_I2C_Init(HMC5883_HandlerType* HMC5883x, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT8_T isHWI2C);
	UINT8_T HMC5883Task_I2C_SingleWriteReg(HMC5883_HandlerType* HMC5883x, UINT8_T addr, UINT8_T val);
	UINT8_T HMC5883Task_I2C_SingleReadReg(HMC5883_HandlerType* HMC5883x, UINT8_T addr, UINT8_T* pVal);
	UINT8_T HMC5883Task_I2C_BurstReadReg(HMC5883_HandlerType* HMC5883x);
	UINT8_T HMC5883Task_ConfigInit(HMC5883_HandlerType* HMC5883x);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*HMC5883_TASK_H_ */
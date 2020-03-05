#ifndef MPU6050_TASK_H_
#define MPU6050_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include"mpu6050_lib.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===º¯Êý¶¨Òå
	UINT8_T MPU6050Task_I2C_Init(MPU6050_HandleType* HMC5883x, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHWI2C);
	UINT8_T MPU6050Task_I2C_WriteSingle(MPU6050_HandleType* MPU6050x, UINT8_T addr, UINT8_T val);
	UINT8_T MPU6050Task_I2C_WriteBulk(MPU6050_HandleType* MPU6050x, UINT8_T addr, UINT8_T* pVal, UINT8_T length);
	UINT8_T MPU6050Task_I2C_ReadSingle(MPU6050_HandleType* MPU6050x, UINT8_T addr, UINT8_T* pVal);
	UINT8_T MPU6050Task_I2C_ReadBulk(MPU6050_HandleType* MPU6050x, UINT8_T addr, UINT8_T* pVal, UINT8_T length);
	UINT8_T MPU6050Task_I2C_ReadChipID(MPU6050_HandleType* MPU6050x, UINT8_T* pChipID);
	UINT8_T MPU6050Task_I2C_ReadAccelTempGyro(MPU6050_HandleType* MPU6050x);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*MPU6050_TASK_H_ */
#ifndef I2C_LIB_H_
#define I2C_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "i2c_cfg.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//---��������
	UINT8_T I2CLib_MSW_Init(I2C_HandleType *I2Cx, void(*pFuncDelayus)(UINT32_T delay),UINT32_T(*pFuncTimerTick)(void));
	UINT8_T I2CLib_MSW_DeInit(I2C_HandleType *I2Cx);
	UINT8_T I2CLib_MSW_START(I2C_HandleType *I2Cx, UINT8_T isWrite);
	UINT8_T I2CLib_MSW_STOP(I2C_HandleType *I2Cx);
	UINT8_T I2CLib_MSW_ACK(I2C_HandleType *I2Cx);
	UINT8_T I2CLib_MSW_NACK(I2C_HandleType *I2Cx);
	UINT8_T I2CLib_MSW_ReadACK(I2C_HandleType *I2Cx);
	UINT8_T I2CLib_MSW_WaitACK(I2C_HandleType *I2Cx);
	UINT8_T I2CLib_MSW_SendACK(I2C_HandleType *I2Cx, UINT8_T isNACK);
	UINT8_T I2CLib_MSW_SendByte(I2C_HandleType *I2Cx, UINT8_T val);
	UINT8_T I2CLib_MSW_SendWord(I2C_HandleType *I2Cx, UINT16_T val);
	UINT8_T I2CLib_MSW_SendBits(I2C_HandleType *I2Cx, UINT8_T *pVal, UINT8_T bitNum);
	UINT8_T I2CLib_MSW_ReadByte(I2C_HandleType *I2Cx);
	UINT8_T I2CLib_MSW_ReadBits(I2C_HandleType *I2Cx, UINT8_T *pVal, UINT8_T bitNum);
	UINT8_T I2CLib_MSW_CheckDevice(I2C_HandleType *I2Cx);
	UINT8_T I2CLib_MSW_SendCMD(I2C_HandleType *I2Cx, UINT8_T cmd, UINT8_T isStart, UINT8_T isStop);
	UINT8_T I2CLib_MSW_Send(I2C_HandleType *I2Cx, UINT8_T *pVal, UINT16_T length);
	UINT8_T I2CLib_MSW_Read(I2C_HandleType *I2Cx, UINT8_T *pVal, UINT16_T length);
	UINT8_T I2CLib_MHW_Init(I2C_HandleType* I2Cx, void(*pFuncDelayus)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void));
	UINT8_T I2CLib_MHW_DeInit(I2C_HandleType* I2Cx);
	UINT8_T I2CLib_MHW_PollMode_START(I2C_HandleType* I2Cx, UINT8_T isWrite);
	UINT8_T I2CLib_MHW_PollMode_STOP(I2C_HandleType* I2Cx);
	UINT8_T I2CLib_MHW_CheckClock(I2C_HandleType* I2Cx);
	UINT8_T I2CLib_MHW_SendACK(I2C_HandleType* I2Cx, UINT8_T isNACK);
	UINT8_T I2CLib_MHW_PollMode_SendByte(I2C_HandleType* I2Cx, UINT8_T val, UINT8_T isBTF);
	UINT8_T I2CLib_MHW_PollMode_ReadByte(I2C_HandleType* I2Cx);
	UINT8_T I2CLib_Master_DeInit(I2C_HandleType* I2Cx);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*I2C_LIB_H_ */

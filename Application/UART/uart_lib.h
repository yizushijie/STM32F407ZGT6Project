#ifndef UART_LIB_H_
#define UART_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "uart_cfg.h"
	#include "crc_task.h"
	//////////////////////////////////////////////////////////////////////////////////////
	UINT8_T  UARTLib_ConfigInit(UART_HandleType* UARTx, UART_HandleType* UARTInitx);
	UINT8_T  UARTLib_Init(UART_HandleType*  UARTx, UINT16_T rxSize, UINT8_T* pRxVal, UINT8_T rxCRCFlag, UINT16_T txSize, UINT8_T* pTxVal, UINT8_T txCRCFlag, UINT32_T(*pTimerTick)(void));
	UINT8_T  UARTLib_DeInit(UART_HandleType*  UARTx);
	UINT8_T  UARTLib_ParamInit(UART_HandleType *UARTx, UINT8_T id, UINT8_T idIndex, UINT8_T cmdIndex, UINT8_T d1Index, UINT8_T d2Index);
	UINT8_T  UARTLib_Read_Init(UART_HandleType*  UARTx);
	UINT8_T  UARTLib_GetState(UART_HandleDef* UARTDefx);
	UINT8_T  UARTLib_ClearState(UART_HandleDef* UARTDefx);
	UINT8_T  UARTLib_TimeTask_OverFlow(UART_HandleType*UARTx, UINT8_T isRx);
	UINT8_T  UARTLib_ITRead_8BitsTask(UART_HandleType*UARTx, UINT8_T val);
	UINT8_T  UARTLib_ITRead_16BitsTask(UART_HandleType*UARTx, UINT8_T val);
	UINT8_T  UARTLib_ITRead_Task(UART_HandleType*UARTx, UINT8_T val);
	UINT8_T  UARTLib_Write_Init(UART_HandleType*UARTx);
	UINT8_T	 UARTLib_Write_CheckIdle(UART_HandleType* UARTx);
	UINT8_T  UARTLib_DeviceID(UART_HandleType*UARTx);
	UINT8_T  UARTLib_ITWrite_TXETask(UART_HandleType*UARTx);
	UINT8_T  UARTLib_ITWrite_TCTask(UART_HandleType*UARTx);
	UINT8_T  UARTLib_RealTime_AddByte(UART_HandleType*UARTx, UINT8_T val);
	UINT8_T  UARTLib_RealTime_AddDataSize(UART_HandleType*UARTx, UINT16_T val);
	UINT8_T  UARTLib_RealTime_AddCRC(UART_HandleType*UARTx);
	UINT8_T	 UARTLib_FillMode_Init( UART_HandleType*UARTx, UINT8_T isChildCmd);
	UINT8_T  UARTLib_FillMode_AddByte(UART_HandleType*UARTx, UINT8_T val);
	UINT8_T  UARTLib_FillMode_AddData(UART_HandleType*UARTx, UINT8_T *pVal, UINT16_T length);
	UINT8_T	 UARTLib_FillMode_SetResultFlag(UART_HandleType* UARTx, UINT8_T val);
	UINT8_T  UARTLib_FillMode_AddIndexW(UART_HandleType* UARTx, UINT16_T val);
	UINT8_T  UARTLib_FillMode_WriteByteSTART(UART_HandleType* UARTx, UINT8_T isNeedID);
	UINT8_T  UARTLib_FillMode_WriteArraySTART(UART_HandleType* UARTx, UINT8_T* pArrayVal, UINT16_T length);
	UINT8_T  UARTLib_FillMode_WriteSTART(UART_HandleType* UARTx, UINT16_T length);
	UINT8_T  UARTLib_Read_CRCTask(UART_HandleType*UARTx);
	UINT8_T  UARTLib_FillMode_WriteCRCTask(UART_HandleType*UARTx);
	UINT8_T  UARTLib_PollMode_WriteByte(UART_HandleType*UARTx, UINT8_T  val);
	UINT8_T  UARTLib_PollMode_WriteData(UART_HandleType*UARTx, char *pVal);
	void	 UARTLib_PrintfClockFreq(UART_HandleType*UARTx);
	void	 UARTLib_PrintfLog(UART_HandleType* UARTx, char* fmt, va_list args);
	UINT8_T  UARTLib_IT_TCTask(UART_HandleType* UARTx);
	void	 UARTLib_IRQTask(UART_HandleType* UARTx);
	void	 UARTLib_DMA_Read_IRQTask(UART_HandleType* UARTx);
	void	 UARTLib_DMA_Write_IRQTask(UART_HandleType* UARTx);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*UART_LIB_H_ */

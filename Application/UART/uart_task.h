#ifndef UART_TASK_H_
#define UART_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	//===头文件定义
	#include "uart_lib.h"
	#include "timer_task.h"
	#include "power_task.h"
	#ifdef STM32_USE_F407VET6
		#include "data_bus.h"
	#endif
	#include "delay_task.h"
	//////////////////////////////////////////////////////////////////////////////////////
	
	//===外部调用接口
	extern UINT8_T UART1_RX_BUFFER[UART1_RX_MAX_SIZE];
	extern UINT8_T UART1_TX_BUFFER[UART1_TX_MAX_SIZE];
	//////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////串口1的配置参数结束//////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////
	//===函数定义
	UINT8_T  UARTTask_ConfigInit(UART_HandleType* UARTx, UART_HandleType* UARTInitx);
	UINT8_T  UARTTask_Init(UART_HandleType*  UARTx, UINT16_T rxSize, UINT8_T* pRxVal, UINT8_T rxCRCFlag, UINT16_T txSize, UINT8_T* pTxVal, UINT8_T txCRCFlag, UINT32_T(*pTimerTick)(void));
	UINT8_T  UARTTask_DeInit(UART_HandleType*  UARTx);
	UINT8_T  UARTTask_ParamInit(UART_HandleType *UARTx, UINT8_T id, UINT8_T idIndex, UINT8_T cmdIndex, UINT8_T d1Index, UINT8_T d2Index);
	UINT8_T  UARTTask_Read_Init(UART_HandleType*  UARTx);
	UINT8_T  UARTTask_ClearState(UART_HandleDef* UARTDefx);
	UINT8_T  UARTTask_GetState(UART_HandleDef* UARTDefx);
	UINT8_T  UARTTask_TimeTask_OverFlow(UART_HandleType* UARTx, UINT8_T isRx);
	UINT8_T  UARTTask_ITRead_8BitsTask(UART_HandleType*UARTx, UINT8_T val);
	UINT8_T  UARTTask_ITRead_16BitsTask(UART_HandleType*UARTx, UINT8_T val);
	UINT8_T  UARTTask_ITRead_Task(UART_HandleType*UARTx, UINT8_T val);
	UINT8_T  UARTTask_Write_Init(UART_HandleType*UARTx);
	UINT8_T  UARTTask_ITWrite_TXETask(UART_HandleType*UARTx);
	UINT8_T  UARTTask_ITWrite_TCTask(UART_HandleType*UARTx);
	UINT8_T  UARTTask_RealTime_AddByte(UART_HandleType*UARTx, UINT8_T val);
	UINT8_T  UARTTask_RealTime_AddDataSize(UART_HandleType*UARTx, UINT16_T val);
	UINT8_T  UARTTask_RealTime_AddCRC(UART_HandleType*UARTx);
	UINT8_T	 UARTTask_FillMode_Init( UART_HandleType*UARTx, UINT8_T isChildCmd);
	UINT8_T  UARTTask_FillMode_AddByte(UART_HandleType*UARTx, UINT8_T val);
	UINT8_T  UARTTask_FillMode_AddData(UART_HandleType*UARTx, UINT8_T *pVal, UINT16_T length);
	UINT8_T	 UARTTask_FillMode_SetResultFlag(UART_HandleType* UARTx, UINT8_T val);
	UINT8_T  UARTTask_FillMode_AddIndexW(UART_HandleType* UARTx, UINT16_T val);
	UINT8_T  UARTTask_FillMode_WriteByteSTART(UART_HandleType* UARTx, UINT8_T isNeedID);
	UINT8_T  UARTTask_FillMode_WriteArraySTART(UART_HandleType* UARTx, UINT8_T* pArrayVal, UINT16_T length);
	UINT8_T  UARTTask_FillMode_WriteSTART(UART_HandleType* UARTx, UINT16_T length);
	UINT8_T  UARTTask_Read_CRCTask(UART_HandleType*UARTx);
	UINT8_T  UARTTask_FillMode_WriteCRCTask(UART_HandleType*UARTx);
	UINT8_T  UARTTask_PollMode_WriteByte(UART_HandleType*UARTx, UINT8_T  val);
	UINT8_T  UARTTask_PollMode_WriteData(UART_HandleType*UARTx, char *pVal);
	UINT8_T  UARTTask_IT_TCTask(UART_HandleType* UARTx);
	UINT8_T	 UARTTask_Write_CheckIdle(UART_HandleType* UARTx);
	UINT8_T	 UARTTask_DeviceID(UART_HandleType* UARTx);
	void	 UARTTask_PrintfLog(UART_HandleType* UARTx, char* fmt, va_list args);
	void	 UARTTask_Printf(UART_HandleType* UARTx, char* fmt, ...);
	void	 UARTTask_IRQTask(UART_HandleType* UARTx);
	void	 UARTTask_DMA_Read_IRQTask(UART_HandleType* UARTx);
	void	 UARTTask_DMA_Write_IRQTask(UART_HandleType* UARTx);
	UINT8_T  UARTTask_FuncTask(UART_HandleType*UARTx, UINT8_T(*pFuncTask)(UINT8_T *, UINT8_T *));
	UINT8_T  UARTTask_DebugPollFuncTask(UART_HandleType* UARTx, UINT8_T(*pFuncTask)(UINT8_T*, UINT8_T*));
	UINT8_T  UARTTask_DebugFreqTask(UART_HandleType* UARTx, UINT8_T(*pFuncTask)(UINT8_T*, UINT8_T*));
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*UART_LIB_H_ */

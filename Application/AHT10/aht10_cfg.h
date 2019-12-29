#ifndef AHT10_CFG_H_
#define AHT10_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include"complier_lib.h"
	#include "delay_task.h"
	#include "i2c_task.h"
	//////////////////////////////////////////////////////////////////////////////////////

	//===写命令
	#define AHT10_WADDR									0x70	
	//===读命令
	#define AHT10_RADDR									0x71	
	//===初始化命令
	#define AHT10_CMD_INIT								0xE1
	//===触发测量
	#define AHT10_CMD_MEASURE							0xAC	
	//===软件复位
	#define AHT10_CMD_RESET								0xBA

	//===结构体定义
	typedef struct _AHT10_HandlerType					AHT10_HandlerType;
	//===指针结构体定义
	typedef struct _AHT10_HandlerType					*pAHT10_HandlerType;
	//===SHT2X的数据结构体
	struct _AHT10_HandlerType
	{
		INT32_T				msgTemp;															//---放大100倍的温度值
		INT32_T				msgHumi;															//---放大100倍的湿度值
		UINT16_T			msgIntervalTime;														//---轮询时间间隔,单位是ms
		UINT32_T			msgRecordTime;															//---记录的时间参数
		I2C_HandlerType		msgI2C;																	//---使用的I2C
		UINT32_T(*msgTimeTick)(void);																//---时间节拍
	};

	//===定义的任务函数
	#define AHT10_TASK_ONE								pAht10Device0
	#define AHT10_TASK_TWO								0
	#define AHT10_TASK_THREE							0

	//===外部调用接口
	extern AHT10_HandlerType							g_Aht10Device0;
	extern pAHT10_HandlerType							pAht10Device0;

	//===函数定义
	UINT8_T AHT10_I2C_DeInit(AHT10_HandlerType* AHT10x);
	UINT8_T AHT10_I2C_Init(AHT10_HandlerType* AHT10x, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHWI2C);
	UINT8_T AHT10_I2C_Config(AHT10_HandlerType* AHT10x);
	UINT8_T AHT10_I2C_StartMeasure(AHT10_HandlerType* AHT10x);
	UINT8_T AHT10_I2C_STATE(AHT10_HandlerType* AHT10x);
	UINT8_T AHT10_I2C_ReadTempHumi(AHT10_HandlerType* AHT10x);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*AHT10_CFG_H_ */
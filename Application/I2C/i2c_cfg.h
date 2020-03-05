#ifndef I2C_CFG_H_
#define I2C_CFG_H_
///////////////////////////////////////////////////////////////////////////////
//////使用该函数，首先保证GPIO的时钟已经使能，函数内部已经将端口配置为开漏输出
//////使用硬件查询模式：初步方式，在发送START信号前，需要检查STOP是否使能了；
//////如果使能了STOP，需要清除STOP信号的，否则异常状态之后，I2C的时序不能恢复
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "gpio_task.h"
	#include "delay_task.h"
	#include "systick_task.h"
	#include "log_cfg.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===定义是否通过复位解锁I2C的busy的死锁现象
	#define USE_RESET_I2C
	//===定义结构体
	typedef struct _I2C_HandlerType					I2C_HandleType;
	//===定义指针结构体
	typedef	struct _I2C_HandlerType					*pI2C_HandlerType;
	//===结构定义
	struct _I2C_HandlerType
	{
		GPIO_HandleType		msgSCL;																						//---SCL
		GPIO_HandleType		msgSDA;																						//---SDA
		UINT8_T				msgHwMode;																					//---工作模式，默认是软件模拟---0，硬件模式---1
		UINT16_T			msgPluseWidth;																				//---脉冲宽度，软件模拟使用
		UINT16_T			msgAddr;																					//---设备的地址
		UINT32_T			msgClockSpeed;																				//---硬件I2C的时钟速度
		UINT32_T			msgRegCCR;																					//---硬件I2C时钟的参数配置
		void(*pMsgDelayus)(UINT32_T delay);																				//---延时参数
	#ifndef USE_MCU_STM32F1
		UINT32_T			msgGPIOAlternate;																			//---端口复用模式
	#endif
		UINT32_T(*pMsgTimeTick)(void);																					//---用于超时计数
		I2C_TypeDef		* pMsgI2Cx;																						//---使用的I2C接口
	#ifdef  USE_RESET_I2C
		LL_I2C_InitTypeDef	msgI2CInitTypeDef;																			//---使用的I2C初始化配置
	#endif 

	};

	//===函数定义
	UINT8_T I2C_MSW_Init(I2C_HandleType *I2Cx, void(*pFuncDelayus)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void));
	UINT8_T I2C_MSW_DeInit(I2C_HandleType *I2Cx);
	UINT8_T I2C_MSW_START(I2C_HandleType *I2Cx);
	UINT8_T I2C_MSW_STOP(I2C_HandleType *I2Cx);
	UINT8_T I2C_MSW_ACK(I2C_HandleType *I2Cx);
	UINT8_T I2C_MSW_NACK(I2C_HandleType *I2Cx);
	UINT8_T I2C_MSW_ReadACK(I2C_HandleType *I2Cx);
	UINT8_T I2C_MSW_WaitACK(I2C_HandleType *I2Cx);
	UINT8_T I2C_MSW_SendACK(I2C_HandleType *I2Cx, UINT8_T isNACK);
	UINT8_T I2C_MSW_SendByte(I2C_HandleType *I2Cx, UINT8_T val);
	UINT8_T I2C_MSW_SendWord(I2C_HandleType *I2Cx, UINT16_T val);
	UINT8_T I2C_MSW_SendBits(I2C_HandleType *I2Cx, UINT8_T *pVal, UINT8_T bitNum);
	UINT8_T I2C_MSW_ReadByte(I2C_HandleType *I2Cx);
	UINT8_T I2C_MSW_ReadBits(I2C_HandleType *I2Cx, UINT8_T *pVal, UINT8_T bitNum);
	UINT8_T I2C_MSW_CheckDevice(I2C_HandleType *I2Cx);
	UINT8_T I2C_MSW_SendCMD(I2C_HandleType *I2Cx, UINT8_T cmd, UINT8_T isStart, UINT8_T isStop);
	UINT8_T I2C_MHW_Init(I2C_HandleType* I2Cx, void(*pFuncDelayus)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void));
	UINT8_T I2C_MHW_DeInit(I2C_HandleType* I2Cx);
	UINT8_T I2C_MHW_PollMode_START(I2C_HandleType* I2Cx);
	UINT8_T I2C_MHW_CheckSTOP(I2C_HandleType* I2Cx);
	UINT8_T I2C_MHW_PollMode_STOP(I2C_HandleType* I2Cx);
	UINT8_T I2C_MHW_PollMode_ADDR(I2C_HandleType* I2Cx, UINT8_T isWrite);
	UINT8_T I2C_MHW_CheckClock(I2C_HandleType* I2Cx);
	UINT8_T I2C_MHW_ClearBusy(I2C_HandleType* I2Cx);
	UINT8_T I2C_MHW_CheckBusy(I2C_HandleType* I2Cx);
	UINT8_T I2C_MHW_SendACK(I2C_HandleType* I2Cx, UINT8_T isNACK);
	UINT8_T I2C_MHW_PollMode_SendByte(I2C_HandleType* I2Cx, UINT8_T val, UINT8_T isBTF);
	UINT8_T I2C_MHW_PollMode_ReadByte(I2C_HandleType* I2Cx);
	UINT8_T I2C_Master_DeInit(I2C_HandleType* I2Cx);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*I2C_CFG_H_ */

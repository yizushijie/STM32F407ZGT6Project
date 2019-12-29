#ifndef DHT11_CFG_H_
#define DHT11_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
/////说明:DHT11对于时序的要求比较的高，在使用的时候注意延时的配置，否则容易出现错误
/////如果时序正确，结果错误，问题应该是出在读取数据的时机不对，示波器抓取数据读取的地方
/////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "delay_task.h"
	#include "gpio_task.h"
	#include "systick_task.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===转换准备好
	#define DHT11_READ_OK							0
	//===转换准备忙
	#define DHT11_READ_BUSY							1
	//===转换准备异常
	#define DHT11_READ_ERROR						2
	//===最小读取的间隔时间为2秒
	#define DHT11_READ_INTERVAL_MS					2000
	//===定义结构体
	typedef struct _DHT11_HandlerType DHT11_HandlerType;

	//===定义指针结构体
	typedef struct _DHT11_HandlerType *pDHT11_HandlerType;

	//===结构体定义
	struct _DHT11_HandlerType
	{
		UINT8_T				msgSTATE;				//---读取状态
		UINT32_T			msgTempX1000;			//---温度
		UINT32_T			msgHumiX1000;			//---湿度
		UINT32_T			msgRecordTime;			//---记录的时间参数
		GPIO_HandlerType	msgDAT;					//---端口
		void(*msgDelayus)(UINT32_T delay);			//---us延时函数
		void(*msgDelayms)(UINT32_T delay);			//---ms延时函数
		UINT32_T(*msgTimeTick)(void);			//---用于超时计数
	};

	//===定义的任务函数
	#define DHT11_TASK_ONE					pDht11Device0
	#define DHT11_TASK_TWO					0
	#define DHT11_TASK_THREE				0

//===外部调用接口
	extern DHT11_HandlerType				g_Dht11Device0;
	extern pDHT11_HandlerType				pDht11Device0
	;

	//===函数定义
	UINT8_T DHT11_Init(DHT11_HandlerType *DHT11x, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay),UINT32_T(*pFuncTimerTick)(void));
	UINT8_T DHT11_Device0_Init(DHT11_HandlerType *DHT11x);
	UINT8_T DHT11_Device1_Init(DHT11_HandlerType *DHT11x);
	UINT8_T DHT11_Device2_Init(DHT11_HandlerType *DHT11x);
	UINT8_T DHT11_DeInit(DHT11_HandlerType *DHT11x);
	UINT8_T DHT11_Read(DHT11_HandlerType *DHT11x);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*DHT11_CFG_H_*/
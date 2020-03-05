#ifndef ESP8266_CFG_H_
#define ESP8266_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "systick_task.h"
	#include "uart_task.h"
	//////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////配置定义---开始///////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////
	//===消息只是
	typedef enum
	{
		ESP8266_SUCCESS = 0,																							//---成功
		ESP8266_BUSY,																									//---忙碌状态
		ESP8266_ERROR_ERR ,																								//---错误
		ESP8266_ERROR_FAIL,																								//---失败
		ESP8266_ERROR_READY ,																							//---准备
		ESP8266_ERROR_BUSY ,																							//---忙碌
		ESP8266_ERROR_UNKNOWN ,																							//---不是被
		ESP8266_ERROR_TIMEOUT ,																							//---超时
		ESP8266_ERROR_CMD ,																								//---AT命令错误
	}ESP8266_STATUS;

	//===工作模式
	typedef enum
	{
		ESP8266_QUERY=0,																								//---查询模式
		ESP8266_STA = 1,																								//---Station模式
		ESP8266_AP = 2,																									//---AP模式
		ESP8266_STA_AP = 3																								//---AP+Station模式
	}ESP8266_WIFI_MODE;
	
	//===命令模式
	typedef enum
	{
		ESP8266_CMD_QUERY=0,																							//---查询命令
		ESP8266_CMD_SETUP,																								//---设置命令
		ESP8266_CMD_EXECUTE																								//---执行命令
	}ESP8266_CMD_TYPE;

	//===WIFI热点加密方式
	typedef enum
	{
		ESP8266_OPEN=0,
		ESP8266_WPA_PSK,
		ESP8266_WPA2_PSK,
		ESP8266_WPA_WPA2_PSK
	}ESP8266_WIFI_TYPE;
	
	typedef enum
	{
		ESP8266_GOTIP = 2,																								//---获取IP
		ESP8266_CONNECTED = 3,																							//---连接状态
		ESP8266_DISCONNECTED = 4,																						//---未连接状态
		ESP8266_NOWIFI = 5,																								//---没有WIFI
	}ESP8266_WIFI_STATUS;

	//===连接状态
	typedef enum
	{
		ESP8266_TCP=0,																									//---TCP模式
		ESP8266_UDP,																									//---UDP模式
		ESP8266_UNKNOWN																									//---不识别模式
	}ESP8266_CONNECTION_TYPE;
	
	//===网络连接模式
	typedef enum
	{
		ESP8266_CLIENT=0,																								//---客户端
		ESP8266_SERVER																									//---服务端
	}ESP8266_NET_TYPE;
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////配置定义---结束///////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////
	
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////结构体定义---开始//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	
	//===结构体定义
	typedef struct _ESP8266_HandleType				ESP8266_HandleType;
	//===指针结构体定义
	typedef struct _ESP8266_HandleType				*pESP8266_HandleType;
	//===数据结构体
	struct _ESP8266_HandleType
	{
		UINT8_T					msgTask;																				//---任务步序号，0---空闲，1---查询响应	
		UINT8_T					msgAckState;																			//---应答状态
		char					*pMsgAckResult;																			//---应答数结果
		ESP8266_WIFI_MODE		msgWifiMode;																			//---工作状态，1---STA，2---AP，3---STA+AP
		UINT16_T				msgIntervalTime;																		//---轮询时间间隔,单位是ms
		UINT8_T					*pMsgAck;																				//---应答数据
		UINT32_T				msgRecordTick;																			//---当前记录的时间
		UART_HandleType			*pMsgUART;																				//---使用的串口
		UINT32_T				(*pMsgTimeTick)(void);																	//---时间节拍
		UINT8_T					(*pMsgAckOkCallBack)(ESP8266_HandleType*);												//---应答正确回调函数
		UINT8_T					(*pMsgAckErrCallBack)(ESP8266_HandleType*);												//---应答错误回调函数
		UINT8_T					(*pMsgAckTimeoutCallBack)(ESP8266_HandleType*);											//---超时错误回调函数
	};
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////结构体定义---结束//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	

	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////配置宏定义---开始//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////
	//===宏定义
	//#define ESP8266_ACK_BUFFER_BASE_SIZE			32																	//---ACK应答缓存区的大小
	#define	ESP8266_ACK_BUFFER_MAX_SIZE				32																	//---ACK应答缓存区的最大值
	#define ESP8266_BUFFER_BASE_SIZE				1024																//---定义缓存区的初始大小
	#define ESP8266_BUFFER_MAX_SIZE					ESP8266_BUFFER_BASE_SIZE+1											//---缓存区大小多1字节，为了避免溢出问题
	#define ESP8266_COMM_UART						pUart3																//---ESP8266通信使用的UART
	#define ESP8266_LOG_UART						pUart1																//---ESP8266打印LOG使用的UART

	//===任务列表
	#define ESP8266_TASK_IDLE						0																	//---空闲任务
	#define ESP8266_TASK_QUERY_ACK					1																	//---查询应答

	//===ACK响应的方式
	#define ESP8266_ACK_IDLE						0																	//---应答空闲
	#define ESP8266_ACK_WAIT						1																	//---等待应答
	#define ESP8266_ACK_OK							2																	//---应答成功
	#define ESP8266_ACK_ERR							3																	//---应答失败
	#define ESP8266_ACK_ERR_INFO					4																	//---解析应答数据错误
	#define ESP8266_ACK_TIMEOUT						5																	//---应答超时
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////配置定义---结束///////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////配置宏定义---开始//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	
	//===定义的任务函数
	#define ESP8266_TASK_ONE						pEsp8266Device0
	#define ESP8266_TASK_TWO						0
	#define ESP8266_TASK_THREE						0 

	#define USE_ESP8266_LOG
	//===打印LOG信息(##__VA_ARGS__，' ## '的意思是，如果可变参数被忽略或为空，将使预处理器（ preprocessor ）去除掉它前面的那个逗号)
	#define ESP8266_LOG(fmt, ...)					ESP8266_UART_LOG(ESP8266_LOG_UART,fmt,##__VA_ARGS__)
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////配置宏定义---开始//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	

	//===外部调用接口
	extern ESP8266_HandleType						g_Esp8266Device0;
	extern pESP8266_HandleType						pEsp8266Device0;

	//===函数定义
	UINT8_T ESP8266_UART_Init(ESP8266_HandleType* ESP8266x, UINT32_T(*pFuncTimerTick)(void));
	void	ESP8266_UART_LOG(UART_HandleType* UARTx, char* fmt, ...);
	UINT8_T ESP8266_UART_ACK(ESP8266_HandleType* ESP8266x, char* ack, UINT16_T intervalTime);
	UINT8_T ESP8266_UART_QueryAckTask(ESP8266_HandleType* ESP8266x);
	UINT8_T ESP8266_UART_Write_WaitIdle(ESP8266_HandleType* ESP8266x);
	UINT8_T ESP8266_UART_Write(ESP8266_HandleType* ESP8266x, UINT8_T* pVal);
	UINT8_T ESP8266_UART_TestAT(ESP8266_HandleType* ESP8266x);
	UINT8_T ESP8266_UART_SoftReset(ESP8266_HandleType* ESP8266x);
	UINT8_T ESP8266_UART_GetVersionInfo(ESP8266_HandleType* ESP8266x);
	UINT8_T ESP8266_UART_DisplayFunction(ESP8266_HandleType* ESP8266x, UINT8_T isClosed);
	UINT8_T ESP8266_UART_RESTORE(ESP8266_HandleType* ESP8266x);
	UINT8_T ESP8266_UART_WifiMode(ESP8266_HandleType* ESP8266x, UINT8_T mode);

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*ESP8266_CFG_H_ */
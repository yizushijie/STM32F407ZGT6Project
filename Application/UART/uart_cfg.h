#ifndef UART_CFG_H_
#define UART_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "gpio_task.h"
	#include "crc_task.h"
	#include "dma_task.h"
	//////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////配置参数---开始////////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////
	//===传输过程中判断判断是否需要初始化GPIO
	#define  UART_INIT_GPIO
	//===是否重映射printf函数
	#define  USE_UART_PRINTF	
	//===是否使用485模式传输数据
	#define  USE_UART_485
	//////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////配置参数---结束////////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////结构体定义---开始//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////
	//===数据结构体
	typedef struct _UART_HandleType				UART_HandleType;
	typedef struct _UART_HandleType				* pUART_HandleType;
	//===数据结构体
	typedef struct _UART_HandleDef				UART_HandleDef;
	typedef struct _UART_HandleDef				*pUART_HandleDef;
	//===接收数据结构体
	typedef struct _UART_HandleDef				UART_RXDHandleType;
	typedef struct _UART_HandleDef				*pUART_RXDHandleType;
	//===发送数据结构体
	typedef struct _UART_HandleDef				UART_TXDHandleType;
	typedef struct _UART_HandleDef				*pUART_TXDHandleType;
	//===串口数据结构体定义
	struct _UART_HandleDef
	{
		UINT8_T									msgDMAMode;																//---是否是DMA模式，0---非DMA模式，1---DMA模式
		VLTUINT8_T								msgCheckSum;															//---校验和
		VLTUINT8_T								msgCRCFlag;																//---校验标志位  0 ---无校验，1 ---校验和，2---CRC8校验，3---CRC16校验，4---CRC32校验
		VLTUINT8_T								msgState;																//---判断任务是否结束 0---未结束，1---结束
		VLTUINT8_T								msgStep;																//---步序
		VLTUINT8_T								msgAddNewLine;															//---是否需要换行符(\r\n)
		VLTUINT16_T								msgWIndex;																//---写序号
		VLTUINT16_T								msgRIndex;																//---读序号
		VLTUINT16_T								msgCount;																//---读写数据的长度
		VLTUINT16_T								msgFlagIndex;															//---执行结果的标识号，在数据缓存区的位置信息
		VLTUINT16_T								msgMaxSize;																//---数据缓存区的大小
		VLTUINT8_T								msgOverFlow;															//---超时标志位
		VLTUINT32_T								msgRecordTick;															//---超时时间节拍
		VLTUINT32_T								msgRecordTime;															//---超时时间记录时间
		VLTUINT32_T								msgMaxTime;																//---超时时间
		VLTUINT32_T								msgMsgValBaseAddr;														//---数据缓存区的基地址，用于指针偏移的时候进行恢复
		UINT8_T									*pMsgVal;																//---缓存区(需要提前定义好数据的缓存区)
		DMA_TypeDef								*pMsgDMA;																//---DMA号
		UINT32_T								msgDMAChannelOrStream;													//---DMA通道号或者流信息
		UINT32_T(*pMsgTimeTick)(void);																					//---用于超时计数
	};	
	//===串口数据定义
	struct _UART_HandleType
	{
		#ifdef USE_UART_PRINTF
			UINT16_T							msgPCount;																//---打印发送总数
			UINT16_T							msgPWIndex;																//---打印发送序号
			UINT16_T							msgPRIndex;																//---打印读取序号
		#endif
		UINT8_T									msgIndex;																//---UART端口的索引号
		UINT8_T									msgRxdID;																//---接收报头
		UINT8_T									msgTxdID;																//---发送报头
		UINT8_T									msgID;																	//---设备ID
		UINT8_T									msgIDIndex;																//---设备ID在数组中的位置
		UINT8_T									msgCmdIndex;															//---命令在数组中的位置
		UINT8_T									msgDataOneIndex;														//---数据1在数组中的位置
		UINT8_T									msgDataTwoIndex;														//---数据2在数组中的位置
		UINT8_T									msgIndexOffset;															//---索引的偏移量
		#ifdef UART_INIT_GPIO
			UINT8_T								msgWriteFinalData;													//---DMA模式下，发送的最后1字节数据
		#endif
		GPIO_HandleType							msgTxPort;																//---UART的GPIO端口号
		#ifdef USE_UART_485
			GPIO_HandleType						msg485Port;																//---485的使能GPIO端口
		#endif
		USART_TypeDef							*pMsgUART;																//---UART端口
		UART_TXDHandleType						msgTxdHandle;															//---发送函数
		UART_RXDHandleType						msgRxdHandle;															//---接收函数
	};
	//===printf数据结构体
	typedef struct _UART_PrintfType				UART_PrintfType;
	typedef struct _UART_PrintfType				*pUART_PrintfType;
	//===Printf打印数据定义
	struct _UART_PrintfType
	{
		UINT16_T								msgRIndex;																//---读取索引
		UINT16_T								msgWIndex;																//---发送索引
		char									* pMsgVal;																//---缓存区(需要提前定义好数据的缓存区)
	};
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////结构体定义---结束//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////配置宏定义---开始//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////
	//===重映射printf之后的数据缓存区
	#ifdef USE_UART_PRINTF
		#define UART_PRINTF_SIZE					1024																//---使用printf的时候的缓存区的大小
		#define UART_PRINTF_IDLE_SIZE				64																	//---printf的最小保留缓存区的大小
	#endif	
	//===使用的校验方式
	#define UART_CRC_NONE							0
	#define UART_CRC_CHECKSUM						1	
	//===自适应CRC校验等级
	#ifdef USE_CRC8
		#define UART_CRC_CRC8						2
	#elif defined(UART_CRC_CHECKSUM)
		#define UART_CRC_CRC8						UART_CRC_CHECKSUM
	#else
		#define UART_CRC_CRC8						UART_CRC_NONE
	#endif
	
	#ifdef USE_CRC16
		#define UART_CRC_CRC16						3
	#elif defined(UART_CRC_CHECKSUM)
		#define UART_CRC_CRC16						UART_CRC_CHECKSUM
	#else
		#define UART_CRC_CRC16						UART_CRC_NONE
	#endif
	
	#ifdef USE_CRC32
		#define UART_CRC_CRC32						4
	#elif defined(UART_CRC_CHECKSUM)
		#define UART_CRC_CRC32						UART_CRC_CHECKSUM
	#else
		#define UART_CRC_CRC32						UART_CRC_NONE
	#endif	
	//===发送端口的配置
	#define UART_GPIOTX_SET_INPUT					0																	//---轮训地址时候，发送端口需要切换为输入
	#define UART_GPIOTX_SET_OUTPUT					1																	//---轮训地址时候，发送端口需要切换为输出
	//===485数据端口的控制使能
	#define UART_485_RX_ENABLE						0																	//---485模式下处于数据接收
	#define UART_485_TX_ENABLE						1																	//---485模式下处于数据发送
	//===串口的状态
	#define UART_BUSY								0																	//---串口忙碌状态
	#define UART_OK									1																	//---串口空闲状态	
	#define UART_ERROR								2																	//---串口错误状态
	#define UART_PRINTF								3																	//---使用Printf传输数据中
	#define UART_DMA								4																	//---串口DMA状态
	#define UART_IT_IDLE							5																	//---串口中断空闲状态

	//===定义的任务函数
	#ifdef USART1
		#define UART_TASK_ONE						pUart1																//---UART1的任务
		#define UART1_RX_DMA_MODE					1																	//---是否使能接收DMA模式，0---中断；1---DMA模式
		#define UART1_TX_DMA_MODE					1																	//---是否使能发送DMA模式，0---中断；1---DMA模式
	#endif
	#ifdef USART2
		#define UART_TASK_TWO						0																	//---UART2的任务
		#define UART2_RX_DMA_MODE					1																	//---是否使能接收DMA模式，0---中断；1---DMA模式
		#define UART2_TX_DMA_MODE					1																	//---是否使能发送DMA模式，0---中断；1---DMA模式
	#endif
	#ifdef USART3
		#define UART_TASK_THREE						pUart3																//---UART3的任务
		#define UART3_RX_DMA_MODE					1																	//---是否使能接收DMA模式，0---中断；1---DMA模式
		#define UART3_TX_DMA_MODE					1																	//---是否使能发送DMA模式，0---中断；1---DMA模式
	#endif
	#ifdef UART4
		#define UART_TASK_FOUR						0																	//---UART4的任务
		#define UART4_RX_DMA_MODE					1																	//---是否使能接收DMA模式，0---中断；1---DMA模式
		#define UART4_TX_DMA_MODE					1																	//---是否使能发送DMA模式，0---中断；1---DMA模式
	#endif
	#ifdef UART5
		#define UART_TASK_FIVE						0																	//---UART5的任务
		#define UART5_RX_DMA_MODE					1																	//---是否使能接收DMA模式，0---中断；1---DMA模式
		#define UART5_TX_DMA_MODE					1																	//---是否使能发送DMA模式，0---中断；1---DMA模式
	#endif
	#ifdef USART6
		#define UART_TASK_SIX						0																	//---UART6的任务
		#define UART6_RX_DMA_MODE					1																	//---是否使能接收DMA模式，0---中断；1---DMA模式
		#define UART6_TX_DMA_MODE					1																	//---是否使能发送DMA模式，0---中断；1---DMA模式
	#endif
	#ifdef UART7
		#define UART_TASK_SEVEN						0																	//---UART7的任务
		#define UART7_RX_DMA_MODE					1																	//---是否使能接收DMA模式，0---中断；1---DMA模式
		#define UART7_TX_DMA_MODE					1																	//---是否使能发送DMA模式，0---中断；1---DMA模式
	#endif
	#ifdef UART8
		#define UART_TASK_EIGHT						0																	//---UART8的任务
		#define UART8_RX_DMA_MODE					1																	//---是否使能接收DMA模式，0---中断；1---DMA模式
		#define UART8_TX_DMA_MODE					1																	//---是否使能发送DMA模式，0---中断；1---DMA模式
	#endif
	#ifdef UART9
		#define UART_TASK_NINE						0																	//---UART9的任务
		#define UART9_RX_DMA_MODE					1																	//---是否使能接收DMA模式，0---中断；1---DMA模式
		#define UART9_TX_DMA_MODE					1																	//---是否使能发送DMA模式，0---中断；1---DMA模式
	#endif
	#ifdef UART10
		#define UART_TASK_TEN						0																	//---UART10的任务	
		#define UART10_RX_DMA_MODE					1																	//---是否使能接收DMA模式，0---中断；1---DMA模式
		#define UART10_TX_DMA_MODE					1																	//---是否使能发送DMA模式，0---中断；1---DMA模式
	#endif
	//////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////配置宏定义---结束////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////

	//===外部调用接口
	extern UART_HandleType							g_Uart1;
	extern pUART_HandleType						pUart1;

	extern UART_HandleType							g_Uart3;
	extern pUART_HandleType						pUart3;

	//////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////串口1的配置参数开始//////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////
	//===定义缓存区的大小
	#define UART1_RX_BASE_SIZE						64//1800
	#define UART1_TX_BASE_SIZE						UART1_RX_BASE_SIZE	
	//===定义设备的地址，多设备的时候使用，0的时候是一对一
	#define UART1_DEVICE_ID						0x00
	
	//===配置设备ID的索引
	#if (UART1_DEVICE_ID!=0)
		#define	UART1_DEVICE_ID_INDEX				1
	#else
		#define	UART1_DEVICE_ID_INDEX				0
	#endif
	
	//===定义了CRC使用的最大缓存区,这样便于更换CRC校验的格式
	#if defined(USE_CRC32)
		#define UART1_RX_MAX_SIZE					( UART1_RX_BASE_SIZE+4 )
	#elif defined(USE_CRC16
		#define UART1_RX_MAX_SIZE					( UART1_RX_BASE_SIZE+2 )
	#elif defined(USE_CRC8)||defined(USE_CHECKSUM)
		#define UART1_RX_MAX_SIZE					( UART1_RX_BASE_SIZE+1 )
	#else
		#define UART1_RX_MAX_SIZE					( UART1_RX_BASE_SIZE )
	#endif
	
	//===定义了CRC使用的最大缓存区,这样便于更换CRC校验的格式
	#if defined(USE_CRC32)
		#define UART1_TX_MAX_SIZE					( UART1_TX_BASE_SIZE+4 )
	#elif defined(USE_CRC16)
		#define UART1_TX_MAX_SIZE					( UART1_TX_BASE_SIZE+2 )
	#elif defined(USE_CRC8)||defined(USE_CHECKSUM)
		#define UART1_TX_MAX_SIZE					( UART1_TX_BASE_SIZE+1 )
	#else
		#define UART1_TX_MAX_SIZE					( UART1_TX_BASE_SIZE )
	#endif
	
	//===解析命令中的含义
	#if (UART1_RX_MAX_SIZE>0xFB)	
		//===设备地址在命令中的位置
		#define UART1_ID_INDEX						3		
		//===协议中的命令1---主命令
		#define UART1_CMD_INDEX					( UART1_ID_INDEX+UART1_DEVICE_ID_INDEX)		
		//===协议中的命令2---子命令
		#define UART1_DATA1_INDEX					( UART1_CMD_INDEX+1 )		
		//===数据返回的值---对接收无效，对发送有效
		#define UART1_DATA2_INDEX					( UART1_CMD_INDEX+2 )
	#else	
		//===设备地址在命令中的位置
		#define UART1_ID_INDEX						2		
		//===协议中的命令1---主命令
		#define UART1_CMD_INDEX					( UART1_ID_INDEX+UART1_DEVICE_ID_INDEX)		
		//===协议中的命令2---子命令或则第一个数据
		#define UART1_DATA1_INDEX					( UART1_CMD_INDEX+1 )		
		//===协议中的第一个数据或则第二数据
		#define UART1_DATA2_INDEX					( UART1_CMD_INDEX+2 )
	#endif
	//////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////串口1的配置参数结束//////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////

	//===函数定义
	UINT8_T  UART_StructInit(UART_HandleType*  UARTx);
	UINT8_T  UART_ConfigInit(UART_HandleType* UARTx, UART_HandleType* UARTInitx);
	UINT8_T  UART_Init(UART_HandleType*  UARTx, UINT16_T rxSize, UINT8_T* pRxVal, UINT8_T rxCRCFlag, UINT16_T txSize, UINT8_T* pTxVal, UINT8_T txCRCFlag, UINT32_T(*pTimerTick)(void));
	UINT8_T  UART_GPIO_TxInit(UART_HandleType*  UARTx, UINT8_T isInput);
	UINT8_T  UART_GPIO_485_Init(UART_HandleType*  UARTx, UINT8_T isEnable);
	UINT8_T  UART_SetCRC(UART_HandleDef* UARTDefx, UINT8_T crcFlag);
	UINT8_T  UART_GetCRC(UART_HandleDef* UARTDefx);
	UINT8_T  UART_TimeTick_Init(UART_HandleDef* UARTDefx);
	UINT8_T  UART_TimeTick_DeInit(UART_HandleDef* UARTDefx);
	UINT8_T  UART_TimeTick_OverFlow(UART_HandleDef* UARTDefx);
	UINT8_T  UART_TimeTask_OverFlow(UART_HandleType*UARTx, UINT8_T isRx);
	UINT8_T  UART_ITRead_8BitsTask(UART_HandleType*UARTx, UINT8_T val);
	UINT8_T  UART_ITRead_16BitsTask(UART_HandleType*UARTx, UINT8_T val);
	UINT8_T  UART_ITRead_Task(UART_HandleType*UARTx, UINT8_T val);
	UINT8_T  UART_GetOverFlow(UART_HandleDef* UARTDefx);
	UINT8_T  UART_ClearOverFlow(UART_HandleDef* UARTDefx);
	UINT8_T  UART_PollMode_WriteByte(UART_HandleType*UARTx, UINT8_T  val);
	UINT8_T  UART_PollMode_WriteData(UART_HandleType*UARTx, char *pVal);
	UINT8_T  UART_PollMode_ReadByte(UART_HandleType*UARTx);
	UINT8_T  UART_PollMode_ReadData(UART_HandleType*UARTx, char *pVal);
	UINT8_T  UART_ITWrite_TXETask(UART_HandleType*UARTx);
	UINT8_T  UART_ITWrite_TCTask(UART_HandleType*UARTx);
	UINT8_T  UART_RealTime_AddByte(UART_HandleType*UARTx, UINT8_T val);
	UINT8_T  UART_RealTime_AddDataSize(UART_HandleType*UARTx, UINT16_T val);
	UINT8_T  UART_RealTime_AddCRC(UART_HandleType*UARTx);
	UINT8_T  UART_FillMode_Init( UART_HandleType*UARTx, UINT8_T isChildCmd);
	UINT8_T  UART_FillMode_AddByte(UART_HandleType*UARTx, UINT8_T val);
	UINT8_T  UART_FillMode_AddData(UART_HandleType*UARTx, UINT8_T *pVal, UINT16_T length);
	UINT8_T	 UART_FillMode_SetResultFlag(UART_HandleType* UARTx, UINT8_T val);
	UINT8_T  UART_FillMode_AddIndexW(UART_HandleType* UARTx, UINT16_T val);
	UINT8_T  UART_Read_CRCTask(UART_HandleType*UARTx);
	UINT8_T  UART_FillMode_WriteCRCTask(UART_HandleType*UARTx);
	UINT8_T  UART_Write_WaitIdle(UART_HandleType* UARTx);
	UINT8_T  UART_FillMode_WriteByteSTART(UART_HandleType*UARTx, UINT8_T isNeedID);
	UINT8_T  UART_FillMode_WriteArraySTART(UART_HandleType* UARTx, UINT8_T* pArrayVal, UINT16_T length);
	UINT8_T  UART_FillMode_WriteSTART(UART_HandleType* UARTx, UINT16_T length);
	UINT8_T  UART_GetState(UART_HandleDef* UARTDefx);
	UINT8_T  UART_ClearState(UART_HandleDef* UARTDefx);
	UINT8_T  UART_Read_Init(UART_HandleType*  UARTx);
	UINT8_T  UART_Write_Init(UART_HandleType*  UARTx);
	UINT8_T	 UART_Write_CheckIdle(UART_HandleType* UARTx);
	UINT8_T  UART_DeviceID(UART_HandleType*UARTx);
	void     UART_Printf(UART_HandleType*UARTx, char*fmt, ...);
	void	 UART_PrintfLog(UART_HandleType* UARTx, char* fmt, va_list args);
	UINT8_T  UART_IT_TCTask(UART_HandleType* UARTx);
	void	 UART_PrintfClockFreq(UART_HandleType*UARTx);
	UINT8_T  UART_Clock(USART_TypeDef* UARTx, UINT8_T isEnable);
	UINT8_T  UART_DeInit(UART_HandleType*UARTx);
	UINT8_T  UART_ParamInit(UART_HandleType *UARTx, UINT8_T id, UINT8_T idIndex, UINT8_T cmdIndex, UINT8_T d1Index, UINT8_T d2Index);
	UINT8_T  UART1_Init(UART_HandleType*UARTx);
	UINT8_T  UART2_Init(UART_HandleType*UARTx);
	UINT8_T  UART3_Init(UART_HandleType*UARTx);
	UINT8_T  UART4_Init(UART_HandleType* UARTx);
	UINT8_T  UART5_Init(UART_HandleType* UARTx);
	UINT8_T  UART6_Init(UART_HandleType* UARTx);
	UINT8_T  UART7_Init(UART_HandleType* UARTx);
	UINT8_T  UART8_Init(UART_HandleType* UARTx);
	UINT8_T  UART9_Init(UART_HandleType* UARTx);
	UINT8_T  UART10_Init(UART_HandleType* UARTx);
	void	 UART_IRQTask(UART_HandleType* UARTx);

	//===函数定义
	UINT8_T	 UART1_DMA_Read_Init(UART_HandleType* UARTx);
	UINT8_T  UART1_DMA_Write_Init(UART_HandleType* UARTx);
	UINT16_T UART_DMA_Read_STOP(UART_HandleType* UARTx);
	UINT8_T  UART_DMA_Write_SetMemoryAddress(UART_HandleType* UARTx, UINT8_T* pVal);
	UINT8_T  UART_DMA_Read_RESTART(UART_HandleType* UARTx);
	UINT16_T UART_DMA_Write_STOP(UART_HandleType* UARTx);
	UINT8_T  UART_DMA_Write_RESTART(UART_HandleType* UARTx);
	UINT8_T  UART_DMA_Read_IdleTask(UART_HandleType* UARTx);
	void	 UART_DMA_Read_IRQTask(UART_HandleType* UARTx);
	void	 UART_DMA_Write_IRQTask(UART_HandleType* UARTx);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*UART_CFG_H_ */

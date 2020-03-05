#include "uart_cfg.h"

//===全局变量定义
UART_HandleType  g_Uart1 = { 0 };
pUART_HandleType pUart1 = &g_Uart1;

//=== 全局变量定义
UART_HandleType  g_Uart3 = { 0 };
pUART_HandleType pUart3 = &g_Uart3;

//===printf函数使用的缓存区
#ifdef USE_UART_PRINTF
	char g_PrintfBuffer[UART_PRINTF_SIZE] = { 0 };
	//---初始化printf环形缓存区
	UART_PrintfType g_Printf = 
	{ 
		.msgRIndex=0,
		.msgWIndex =0,
		.pMsgVal= g_PrintfBuffer
	};
	pUART_PrintfType pPrintf =&g_Printf;
#endif

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_StructInit(UART_HandleType*  UARTx)
{
	//---串口的数据处理流程
	UARTx->msgIndex = 0;
	UARTx->msgRxdID = 0;
	UARTx->msgTxdID = 0;
	UARTx->msgID = 0;
	UARTx->msgIDIndex = 0;
	UARTx->msgCmdIndex = 0;
	UARTx->msgDataOneIndex = 0;
	UARTx->msgDataTwoIndex = 0;
	UARTx->msgIndexOffset=0;
	UARTx->msgTxPort.msgPort = NULL;
#ifdef USE_UART_485
	UARTx->msg485Port.msgPort = NULL;
#endif
	UARTx->pMsgUART = NULL;

	//---接收缓存区
	UARTx->msgRxdHandle.msgDMAMode = 1;
	UARTx->msgRxdHandle.msgCheckSum = 0;
	UARTx->msgRxdHandle.msgCRCFlag = 0;
	UARTx->msgRxdHandle.msgStep = 0;
	UARTx->msgRxdHandle.msgAddNewLine = 0;
	UARTx->msgRxdHandle.msgWIndex = 0;
	UARTx->msgRxdHandle.msgRIndex = 0;
	UARTx->msgRxdHandle.msgFlagIndex =0;
	UARTx->msgRxdHandle.msgCount = 0;
	UARTx->msgRxdHandle.msgMaxSize = 0;
	UARTx->msgRxdHandle.msgState = UART_BUSY;
	UARTx->msgRxdHandle.msgOverFlow = 0;
	UARTx->msgRxdHandle.msgRecordTick = 0;
	UARTx->msgRxdHandle.msgRecordTime=0;
	UARTx->msgRxdHandle.msgMsgValBaseAddr=0;
	UARTx->msgRxdHandle.msgMaxTime = 0;
	UARTx->msgRxdHandle.pMsgVal = NULL;
	//---计数器
	UARTx->msgRxdHandle.pMsgTimeTick = NULL;

	//---发送缓存区
	UARTx->msgTxdHandle.msgDMAMode = 0;
	UARTx->msgTxdHandle.msgCheckSum = 0;
	UARTx->msgTxdHandle.msgCRCFlag = 0;
	UARTx->msgTxdHandle.msgStep = 0;
	UARTx->msgTxdHandle.msgAddNewLine = 0;
	UARTx->msgTxdHandle.msgWIndex = 0;
	UARTx->msgTxdHandle.msgRIndex = 0;
	UARTx->msgTxdHandle.msgFlagIndex = 0;
	UARTx->msgTxdHandle.msgCount = 0;
	UARTx->msgTxdHandle.msgMaxSize = 0;
	UARTx->msgTxdHandle.msgState = UART_OK;
	UARTx->msgTxdHandle.msgOverFlow = 0;
	UARTx->msgTxdHandle.msgRecordTick = 0;
	UARTx->msgTxdHandle.msgRecordTime = 0;
	UARTx->msgTxdHandle.msgMsgValBaseAddr = 0;
	UARTx->msgTxdHandle.msgMaxTime = 0;
	UARTx->msgTxdHandle.pMsgVal = NULL;
	//---计数器
	UARTx->msgTxdHandle.pMsgTimeTick = NULL;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：用指定的配置，初始化指定的串口
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_ConfigInit(UART_HandleType* UARTx, UART_HandleType* UARTInitx)
{
	//---串口的数据处理流程
	UARTx->msgIndex							= UARTInitx->msgIndex							;
	UARTx->msgRxdID							= UARTInitx->msgRxdID							;
	UARTx->msgTxdID							= UARTInitx->msgTxdID							;
	UARTx->msgID							= UARTInitx->msgID								;
	UARTx->msgIDIndex						= UARTInitx->msgIDIndex							;
	UARTx->msgCmdIndex						= UARTInitx->msgCmdIndex						;
	UARTx->msgDataOneIndex					= UARTInitx->msgDataOneIndex					;
	UARTx->msgDataTwoIndex					= UARTInitx->msgDataTwoIndex					;
	UARTx->msgIndexOffset					= UARTInitx->msgIndexOffset						;
	UARTx->msgTxPort.msgPort				= UARTInitx->msgTxPort.msgPort					;
#ifdef USE_UART_485
	UARTx->msg485Port.msgPort				= UARTInitx->msg485Port.msgPort					;
#endif
	UARTx->pMsgUART							= UARTInitx->pMsgUART							;

	//---接收缓存区
	UARTx->msgRxdHandle.msgDMAMode			= UARTInitx->msgRxdHandle.msgDMAMode			;
	UARTx->msgRxdHandle.msgCheckSum		= UARTInitx->msgRxdHandle.msgCheckSum			;
	UARTx->msgRxdHandle.msgCRCFlag			= UARTInitx->msgRxdHandle.msgCRCFlag			;
	UARTx->msgRxdHandle.msgStep			= UARTInitx->msgRxdHandle.msgStep				;
	UARTx->msgRxdHandle.msgAddNewLine		= UARTInitx->msgRxdHandle.msgAddNewLine		;
	UARTx->msgRxdHandle.msgWIndex			= UARTInitx->msgRxdHandle.msgWIndex			;
	UARTx->msgRxdHandle.msgRIndex			= UARTInitx->msgRxdHandle.msgRIndex			;
	UARTx->msgRxdHandle.msgFlagIndex		= UARTInitx->msgRxdHandle.msgFlagIndex			;
	UARTx->msgRxdHandle.msgCount			= UARTInitx->msgRxdHandle.msgCount				;
	UARTx->msgRxdHandle.msgMaxSize			= UARTInitx->msgRxdHandle.msgMaxSize			;
	UARTx->msgRxdHandle.msgState			= UARTInitx->msgRxdHandle.msgState				;
	UARTx->msgRxdHandle.msgOverFlow		= UARTInitx->msgRxdHandle.msgOverFlow			;
	UARTx->msgRxdHandle.msgRecordTick		= UARTInitx->msgRxdHandle.msgRecordTick		;
	UARTx->msgRxdHandle.msgRecordTime		= UARTInitx->msgRxdHandle.msgRecordTime		;
	UARTx->msgRxdHandle.msgMsgValBaseAddr	= UARTInitx->msgRxdHandle.msgMsgValBaseAddr	;
	UARTx->msgRxdHandle.msgMaxTime			= UARTInitx->msgRxdHandle.msgMaxTime			;
	UARTx->msgRxdHandle.pMsgVal			= UARTInitx->msgRxdHandle.pMsgVal				;
	//---计数器
	UARTx->msgRxdHandle.pMsgTimeTick		= UARTInitx->msgRxdHandle.pMsgTimeTick			;

	//---发送缓存区
	UARTx->msgTxdHandle.msgDMAMode			= UARTInitx->msgTxdHandle.msgDMAMode			;
	UARTx->msgTxdHandle.msgCheckSum		= UARTInitx->msgTxdHandle.msgCheckSum			;
	UARTx->msgTxdHandle.msgCRCFlag			= UARTInitx->msgTxdHandle.msgCRCFlag			;
	UARTx->msgTxdHandle.msgStep			= UARTInitx->msgTxdHandle.msgStep				;
	UARTx->msgTxdHandle.msgAddNewLine		= UARTInitx->msgTxdHandle.msgAddNewLine 		;
	UARTx->msgTxdHandle.msgWIndex			= UARTInitx->msgTxdHandle.msgWIndex			;
	UARTx->msgTxdHandle.msgRIndex			= UARTInitx->msgTxdHandle.msgRIndex			;
	UARTx->msgTxdHandle.msgFlagIndex		= UARTInitx->msgTxdHandle.msgFlagIndex			;
	UARTx->msgTxdHandle.msgCount			= UARTInitx->msgTxdHandle.msgCount				;
	UARTx->msgTxdHandle.msgMaxSize			= UARTInitx->msgTxdHandle.msgMaxSize			;
	UARTx->msgTxdHandle.msgState			= UARTInitx->msgTxdHandle.msgState				;
	UARTx->msgTxdHandle.msgOverFlow		= UARTInitx->msgTxdHandle.msgOverFlow			;
	UARTx->msgTxdHandle.msgRecordTick		= UARTInitx->msgTxdHandle.msgRecordTick 		;
	UARTx->msgTxdHandle.msgRecordTime		= UARTInitx->msgTxdHandle.msgRecordTime 		;
	UARTx->msgTxdHandle.msgMsgValBaseAddr	= UARTInitx->msgTxdHandle.msgMsgValBaseAddr	;
	UARTx->msgTxdHandle.msgMaxTime			= UARTInitx->msgTxdHandle.msgMaxTime			;
	UARTx->msgTxdHandle.pMsgVal			= UARTInitx->msgTxdHandle.pMsgVal				;
	//---计数器
	UARTx->msgTxdHandle.pMsgTimeTick		= UARTInitx->msgTxdHandle.pMsgTimeTick			;
	//---端口初始化
#ifdef USART1
	if ((UARTx != NULL) && (UARTx == UART_TASK_ONE))
	{
		return UART1_Init(UARTx);
	}
#endif
#ifdef USART2
	if ((UARTx != NULL) && (UARTx == UART_TASK_TWO))
	{
		return UART2_Init(UARTx);
	}
#endif
#ifdef USART3
	if ((UARTx != NULL) && (UARTx == UART_TASK_THREE))
	{
		return UART3_Init(UARTx);
	}
#endif
#ifdef UART4
	if ((UARTx != NULL) && (UARTx == UART_TASK_FOUR))
	{
		return UART4_Init(UARTx);
	}
#endif
#ifdef UART5
	if ((UARTx != NULL) && (UARTx == UART_TASK_FIVE))
	{
		return UART5_Init(UARTx);
	}
#endif
#ifdef USART6
	if ((UARTx != NULL) && (UARTx == UART_TASK_SIX))
	{
		return UART6_Init(UARTx);
	}
#endif
#ifdef UART7
	if ((UARTx != NULL) && (UARTx == UART_TASK_SEVEN))
	{
		return UART7_Init(UARTx);
	}
#endif
#ifdef UART8
	if ((UARTx != NULL) && (UARTx == UART_TASK_EIGHT))
	{
		return UART8_Init(UARTx);
	}
#endif
#ifdef UART9
	else if ((UARTx != NULL) && (UARTx == UART_TASK_NINE))
	{
		return UART9_Init(UARTx);
	}
#endif
#ifdef UART10
	if ((UARTx != NULL) && (UARTx == UART_TASK_TEN))
	{
		return UART10_Init(UARTx);
	}
#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：UART1的参数配置
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART1_ConfigInit(UART_HandleType* UARTx)
{
	//---UART1 GPIO Configuration
	//---PA9  ------> UART1_TX---端口复用为7
	//---PA10 ------> UART1_RX---端口复用为7
	//---使能端口时钟
#ifndef  USE_FULL_GPIO
	GPIOTask_Clock(GPIOA, PERIPHERAL_CLOCK_ENABLE);
#endif
	//---GPIO的结构体
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	//---模式配置
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	//---工作速度
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	//---复用功能的推完输出
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	//---输入上拉使能
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
#ifdef USE_MCU_STM32F1
	//---TX
	GPIO_InitStruct.Pin = LL_GPIO_PIN_9;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	//---RX
	GPIO_InitStruct.Pin = LL_GPIO_PIN_10;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
#else
	//---端口号
	GPIO_InitStruct.Pin = LL_GPIO_PIN_9 | LL_GPIO_PIN_10;
	//---复用功能为UART1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
#endif
	//---配置消息结构体中的信息
	UARTx->msgTxPort.msgPort = GPIOA;
	UARTx->msgTxPort.msgBit = LL_GPIO_PIN_9;
	UARTx->pMsgUART = USART1;
	//---串口序号
	UARTx->msgIndex = 1 + 1;
	//---注销串口的初始化
	LL_USART_DeInit(UARTx->pMsgUART);
	//---使能UART1的时钟信号
	UART_Clock(UARTx->pMsgUART, PERIPHERAL_CLOCK_ENABLE);
	//---UART的接口结构体
	LL_USART_InitTypeDef USART_InitStruct = { 0 };
	//---波特率
	USART_InitStruct.BaudRate = 115200;
	//---数据位
	USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
	//---停止位
	USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
	//---校验位
	USART_InitStruct.Parity = LL_USART_PARITY_NONE;
	//---配置为收发模式
	USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
	//---硬件流控制---默认为无
	USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
	//---过采样配置
#ifdef UART_CR1_OVER8
	//---过采样次数---默认配置为16
	UART_InitStruct.OverSampling = LL_UART_OVERSAMPLING_16;
#endif
	//---初始化串口
	LL_USART_Init(UARTx->pMsgUART, &USART_InitStruct);
	//---串口异步模式配置
	LL_USART_ConfigAsyncMode(UARTx->pMsgUART);
	//---校验是否接收需要超时函数
	(UARTx->msgRxdHandle.pMsgTimeTick != NULL)?(UARTx->msgRxdHandle.msgMaxTime = 100):(UARTx->msgRxdHandle.msgMaxTime = 0);
	//---校验是否发送需要超时函数
	(UARTx->msgTxdHandle.pMsgTimeTick != NULL)?(UARTx->msgTxdHandle.msgMaxTime = 100):(UARTx->msgTxdHandle.msgMaxTime = 0);
	//---配置CRC的等级
	UARTx->msgTxdHandle.msgCRCFlag = UART_CRC_NONE;
	//---配置报头和报尾
	UARTx->msgRxdID = 0x55;
	UARTx->msgTxdID = 0x5A;
	//---配置上会否开启收发DMA
	UARTx->msgRxdHandle.msgDMAMode = UART1_RX_DMA_MODE;
	UARTx->msgTxdHandle.msgDMAMode = UART1_TX_DMA_MODE;
	//---命令和地址配置
	UART_ParamInit(UARTx, UART1_DEVICE_ID, UART1_ID_INDEX, UART1_CMD_INDEX, UART1_DATA1_INDEX, UART1_DATA2_INDEX);
	//---定义485为接收模式--推完输出模式，配置为接收模式
	UART_GPIO_485_Init(UARTx, UART_485_RX_ENABLE);
	//---设置TX端口为输入模式
	UART_GPIO_TxInit(UARTx, UART_GPIOTX_SET_INPUT);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：接收DMA初始化
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART1_DMA_Read_Init(UART_HandleType* UARTx)
{
	//>>>---RX的DMA配置
	//---将DMA全部寄存器重新设置为缺省值
#ifdef USE_MCU_STM32F1
	//---F1对应是的DMA1的通道1对应ADC1
	LL_DMA_DeInit(DMA1, LL_DMA_CHANNEL_1);
	//---DMA时钟总线配置
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
#else
	LL_DMA_DeInit(DMA2, LL_DMA_STREAM_2);
	//---DMA时钟总线配置
	//LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2);
	DMATask_Clock(DMA2, PERIPHERAL_CLOCK_ENABLE);
	UARTx->msgRxdHandle.pMsgDMA = DMA2;
	UARTx->msgRxdHandle.msgDMAChannelOrStream = LL_DMA_STREAM_2;
#endif
	//---DMA初始化结构体
	LL_DMA_InitTypeDef DMA_InitTypeDef = { 0 };
#ifndef USE_MCU_STM32F1
	//---DMA通道
	DMA_InitTypeDef.Channel = LL_DMA_CHANNEL_4;
#endif
	//---数据大小
	DMA_InitTypeDef.NbData = UARTx->msgRxdHandle.msgMaxSize;
	//---方向从外设到存储器
	DMA_InitTypeDef.Direction = LL_DMA_DIRECTION_PERIPH_TO_MEMORY;
#ifndef USE_MCU_STM32F1
	//---不用FIFO用直连模式
	DMA_InitTypeDef.FIFOMode = LL_DMA_FIFOMODE_DISABLE;
	//---半字两字节
	DMA_InitTypeDef.FIFOThreshold = LL_DMA_FIFOTHRESHOLD_1_2;
#endif
	//---存储器地址
	DMA_InitTypeDef.MemoryOrM2MDstAddress = (UINT32_T)(UARTx->msgRxdHandle.pMsgVal);
	//---半字两字节
	DMA_InitTypeDef.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;
	//---存储器地址增加
	DMA_InitTypeDef.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT;
	//---DMA正常模式
	DMA_InitTypeDef.Mode = LL_DMA_MODE_NORMAL; //LL_DMA_MODE_CIRCULAR;
	//---DMA外设地址
	DMA_InitTypeDef.PeriphOrM2MSrcAddress = (UINT32_T) & (UARTx->pMsgUART->DR);
#ifndef USE_MCU_STM32F1
	//---无FIFO
	DMA_InitTypeDef.PeriphBurst = LL_DMA_PBURST_SINGLE;
#endif
	//---半字两字节
	DMA_InitTypeDef.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
	//---外设基地址不变
	DMA_InitTypeDef.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
	//---传输通道优先级为高
	DMA_InitTypeDef.Priority = LL_DMA_PRIORITY_HIGH;
	//---DMA初始化
#ifdef USE_MCU_STM32F1
	//---初始化DMA
	LL_DMA_Init(UARTx->msgRxHandler.msgDMA, UARTx->msgRxHandler.msgDMAChannelOrStream, &DMA_InitTypeDef);
	//---使能DMA
	LL_DMA_EnableChannel(UARTx->msgRxHandler.msgDMA, UARTx->msgRxHandler.msgDMAChannelOrStream);
#else
	//---初始化DMA
	LL_DMA_Init(UARTx->msgRxdHandle.pMsgDMA, UARTx->msgRxdHandle.msgDMAChannelOrStream, &DMA_InitTypeDef);
	//---使能DMA
	LL_DMA_EnableStream(UARTx->msgRxdHandle.pMsgDMA, UARTx->msgRxdHandle.msgDMAChannelOrStream);
	//---是能串口接收DMA
	LL_USART_EnableDMAReq_RX(UARTx->pMsgUART);
#endif
	//---中断配置
#ifdef USE_MCU_STM32F1
	//---DMA中断配置
	NVIC_SetPriority(DMA1_Channel1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 1, 0));
	//---使能中断
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);
#else
	//---DMA中断配置
	NVIC_SetPriority(DMA2_Stream2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 2, 0));
	//---使能中断
	NVIC_EnableIRQ(DMA2_Stream2_IRQn);
#endif
	//---使能DMA传输结束中断
	LL_DMA_EnableIT_TC(UARTx->msgRxdHandle.pMsgDMA, UARTx->msgRxdHandle.msgDMAChannelOrStream);
	//<<<---RX的DMA配置结束
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：发送DMA的初始化
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART1_DMA_Write_Init(UART_HandleType* UARTx)
{
	//>>>---TX的DMA配置
	//---将DMA全部寄存器重新设置为缺省值
#ifdef USE_MCU_STM32F1
	//---F1对应是的DMA1的通道1对应ADC1
	LL_DMA_DeInit(DMA1, LL_DMA_CHANNEL_1);
	//---DMA时钟总线配置
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
#else
	LL_DMA_DeInit(DMA2, LL_DMA_STREAM_7);
	//---DMA时钟总线配置
	//LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2);
	DMATask_Clock(DMA2, PERIPHERAL_CLOCK_ENABLE);
	UARTx->msgTxdHandle.pMsgDMA = DMA2;
	UARTx->msgTxdHandle.msgDMAChannelOrStream = LL_DMA_STREAM_7;
#endif
	//---DMA初始化结构体
	LL_DMA_InitTypeDef DMA_InitTypeDef = { 0 };
#ifndef USE_MCU_STM32F1
	//---DMA通道
	DMA_InitTypeDef.Channel = LL_DMA_CHANNEL_4;
#endif
	//---数据大小,如果是首次发送，这里的参数只能写0，否则容易发生数据不完整，可能只发送了接个字节就停止发送
	DMA_InitTypeDef.NbData = 0;//UARTx->msgTxdHandler.msgSize;
	//---方向从存储器到外设
	DMA_InitTypeDef.Direction = LL_DMA_DIRECTION_MEMORY_TO_PERIPH;
#ifndef USE_MCU_STM32F1
	//---不用FIFO用直连模式
	DMA_InitTypeDef.FIFOMode = LL_DMA_FIFOMODE_DISABLE;
	//---半字两字节
	DMA_InitTypeDef.FIFOThreshold = LL_DMA_FIFOTHRESHOLD_1_2;
#endif
	//---存储器地址
	DMA_InitTypeDef.MemoryOrM2MDstAddress = (UINT32_T)(UARTx->msgTxdHandle.pMsgVal);
	//---半字两字节
	DMA_InitTypeDef.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;
	//---存储器地址增加
	DMA_InitTypeDef.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT;
	//---DMA正常模式
	DMA_InitTypeDef.Mode = LL_DMA_MODE_NORMAL; //LL_DMA_MODE_CIRCULAR;
	//---DMA外设地址
	DMA_InitTypeDef.PeriphOrM2MSrcAddress = (UINT32_T) & (UARTx->pMsgUART->DR);
#ifndef USE_MCU_STM32F1
	//---无FIFO
	DMA_InitTypeDef.PeriphBurst = LL_DMA_PBURST_SINGLE;
#endif
	//---半字两字节
	DMA_InitTypeDef.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
	//---外设基地址不变
	DMA_InitTypeDef.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
	//---传输通道优先级为高
	DMA_InitTypeDef.Priority = LL_DMA_PRIORITY_HIGH;
	//---DMA初始化
#ifdef USE_MCU_STM32F1
	//---初始化DMA
	LL_DMA_Init(UARTx->msgTxHandler.msgDMA, UARTx->msgTxHandler.msgDMAChannelOrStream, &DMA_InitTypeDef);
	//---使能DMA
	LL_DMA_EnableChannel(UARTx->msgTxHandler.msgDMA, UARTx->msgTxHandler.msgDMAChannelOrStream);
#else
	//---初始化DMA
	LL_DMA_Init(UARTx->msgTxdHandle.pMsgDMA, UARTx->msgTxdHandle.msgDMAChannelOrStream, &DMA_InitTypeDef);
	//---使能DMA,注意发送状态下不能使能DMA，只有需要的时候才能打开
	//LL_DMA_EnableStream(UARTx->msgTxHandler.msgDMA, UARTx->msgTxHandler.msgDMAChannelOrStream);
	//---使能串口发送DMA
	LL_USART_EnableDMAReq_TX(UARTx->pMsgUART);
#endif
	//---中断配置
#ifdef USE_MCU_STM32F1
	//---DMA中断配置
	NVIC_SetPriority(DMA1_Channel1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 1, 0));
	//---使能中断
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);
#else
	//---DMA中断配置
	NVIC_SetPriority(DMA2_Stream7_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 2, 0));
	//---使能中断
	NVIC_EnableIRQ(DMA2_Stream7_IRQn);
#endif
	//---使能DMA传输结束中断
	LL_DMA_EnableIT_TC(UARTx->msgTxdHandle.pMsgDMA, UARTx->msgTxdHandle.msgDMAChannelOrStream);
	//<<<---TX的DMA配置结束
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART1_Init(UART_HandleType* UARTx)
{
	UART1_ConfigInit(UARTx);
	//---校验接收是不是DMA传输
	if (UARTx->msgRxdHandle.msgDMAMode == 0)
	{
		//---使能接收中断
		LL_USART_EnableIT_RXNE(USART1);
	}
	else
	{
		//---使能接收空闲中断
		LL_USART_EnableIT_IDLE(USART1);
		//---初始化DMA设置
		UART1_DMA_Read_Init(UARTx);
	}
	//---校验发送是不是DMA传输方式
	if (UARTx->msgTxdHandle.msgDMAMode != 0)
	{
		//---初始化DMA设置
		UART1_DMA_Write_Init(UARTx);
	}
	//---UART1_IRQ中断配置---中断等级配置
	NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 2, 0));
	//---使能中断
	NVIC_EnableIRQ(USART1_IRQn);
	//---使能串口
	LL_USART_Enable(UARTx->pMsgUART);
	//---打印初始化信息
	//UART_Printf(UARTx, "=>>串口1的初始化<<=\r\n");
	UART_Printf(UARTx, "===>>串口1初始化完成<<===\r\n");
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART2_ConfigInit(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART2_DMA_Read_Init(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART2_DMA_Write_Init(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART2_Init(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART3_ConfigInit(UART_HandleType* UARTx)
{
	//---UART3 GPIO Configuration
	//---PB10  ------> UART3_TX---端口复用为7
	//---PB11  ------> UART3_RX---端口复用为7
	//---使能端口时钟
#ifndef  USE_FULL_GPIO
	GPIOTask_Clock(GPIOB, PERIPHERAL_CLOCK_ENABLE);
#endif
	//---GPIO的结构体
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	//---模式配置
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	//---工作速度
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	//---复用功能的推完输出
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	//---输入上拉使能
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
#ifdef USE_MCU_STM32F1
	//---TX
	GPIO_InitStruct.Pin = LL_GPIO_PIN_10;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	//---RX
	GPIO_InitStruct.Pin = LL_GPIO_PIN_11;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
#else
	//---端口号
	GPIO_InitStruct.Pin = LL_GPIO_PIN_10 | LL_GPIO_PIN_11;
	//---复用功能为UART3
	GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
	LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
#endif
	//---配置消息结构体中的信息
	UARTx->msgTxPort.msgPort = GPIOB;
	UARTx->msgTxPort.msgBit = LL_GPIO_PIN_10;
	UARTx->pMsgUART = USART3;
	//---串口序号
	UARTx->msgIndex = 3 + 1;
	//---注销串口的初始化
	LL_USART_DeInit(UARTx->pMsgUART);
	//---使能UART1的时钟信号
	UART_Clock(UARTx->pMsgUART, PERIPHERAL_CLOCK_ENABLE);
	//---UART的接口结构体
	LL_USART_InitTypeDef USART_InitStruct = { 0 };
	//---波特率
	USART_InitStruct.BaudRate = 115200;
	//---数据位
	USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
	//---停止位
	USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
	//---校验位
	USART_InitStruct.Parity = LL_USART_PARITY_NONE;
	//---配置为收发模式
	USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
	//---硬件流控制---默认为无
	USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
	//---过采样配置
#ifdef UART_CR1_OVER8
	//---过采样次数---默认配置为16
	UART_InitStruct.OverSampling = LL_UART_OVERSAMPLING_16;
#endif
	//---初始化串口
	LL_USART_Init(UARTx->pMsgUART, &USART_InitStruct);
	//---串口异步模式配置
	LL_USART_ConfigAsyncMode(UARTx->pMsgUART);
	//---校验是否接收需要超时函数
	(UARTx->msgRxdHandle.pMsgTimeTick != NULL) ? (UARTx->msgRxdHandle.msgMaxTime = 10) : (UARTx->msgRxdHandle.msgMaxTime = 0);
	//---校验是否发送需要超时函数
	(UARTx->msgTxdHandle.pMsgTimeTick != NULL) ? (UARTx->msgTxdHandle.msgMaxTime = 100) : (UARTx->msgTxdHandle.msgMaxTime = 0);
	//---配置CRC的等级
	UARTx->msgTxdHandle.msgCRCFlag = UART_CRC_NONE;
	//---配置报头和报尾
	UARTx->msgRxdID = 0x55;
	UARTx->msgTxdID = 0x5A;
	//---配置上会否开启收发DMA
	//---配置上会否开启收发DMA
	UARTx->msgRxdHandle.msgDMAMode = UART3_RX_DMA_MODE;
	UARTx->msgTxdHandle.msgDMAMode = UART3_TX_DMA_MODE;
	//---命令和地址配置
	//UART_ParamInit(UARTx, UART1_DEVICE_ID, UART1_ID_INDEX, UART1_CMD_INDEX, UART1_DATA1_INDEX, UART1_DATA2_INDEX);
	//---定义485为接收模式--推完输出模式，配置为接收模式
	UART_GPIO_485_Init(UARTx, UART_485_RX_ENABLE);
	//---设置TX端口为输入模式
	UART_GPIO_TxInit(UARTx, UART_GPIOTX_SET_INPUT);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART3_DMA_Read_Init(UART_HandleType* UARTx)
{
	//>>>---RX的DMA配置
	//---将DMA全部寄存器重新设置为缺省值
#ifdef USE_MCU_STM32F1
	//---F1对应是的DMA1的通道1对应ADC1
	LL_DMA_DeInit(DMA1, LL_DMA_CHANNEL_1);
	//---DMA时钟总线配置
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
#else
	LL_DMA_DeInit(DMA1, LL_DMA_STREAM_1);
	//---DMA时钟总线配置
	//LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
	DMATask_Clock(DMA1, PERIPHERAL_CLOCK_ENABLE);
	UARTx->msgRxdHandle.pMsgDMA = DMA1;
	UARTx->msgRxdHandle.msgDMAChannelOrStream = LL_DMA_STREAM_1;
#endif
	//---DMA初始化结构体
	LL_DMA_InitTypeDef DMA_InitTypeDef = { 0 };
#ifndef USE_MCU_STM32F1
	//---DMA通道
	DMA_InitTypeDef.Channel = LL_DMA_CHANNEL_4;
#endif
	//---数据大小
	DMA_InitTypeDef.NbData = UARTx->msgRxdHandle.msgMaxSize;
	//---方向从外设到存储器
	DMA_InitTypeDef.Direction = LL_DMA_DIRECTION_PERIPH_TO_MEMORY;
#ifndef USE_MCU_STM32F1
	//---不用FIFO用直连模式
	DMA_InitTypeDef.FIFOMode = LL_DMA_FIFOMODE_DISABLE;
	//---半字两字节
	DMA_InitTypeDef.FIFOThreshold = LL_DMA_FIFOTHRESHOLD_1_2;
#endif
	//---存储器地址
	DMA_InitTypeDef.MemoryOrM2MDstAddress = (UINT32_T)(UARTx->msgRxdHandle.pMsgVal);
	//---半字两字节
	DMA_InitTypeDef.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;
	//---存储器地址增加
	DMA_InitTypeDef.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT;
	//---DMA正常模式
	DMA_InitTypeDef.Mode = LL_DMA_MODE_NORMAL; //LL_DMA_MODE_CIRCULAR;
	//---DMA外设地址
	DMA_InitTypeDef.PeriphOrM2MSrcAddress = (UINT32_T) & (UARTx->pMsgUART->DR);
#ifndef USE_MCU_STM32F1
	//---无FIFO
	DMA_InitTypeDef.PeriphBurst = LL_DMA_PBURST_SINGLE;
#endif
	//---半字两字节
	DMA_InitTypeDef.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
	//---外设基地址不变
	DMA_InitTypeDef.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
	//---传输通道优先级为高
	DMA_InitTypeDef.Priority = LL_DMA_PRIORITY_HIGH;
	//---DMA初始化
#ifdef USE_MCU_STM32F1
	//---初始化DMA
	LL_DMA_Init(UARTx->msgRxHandler.msgDMA, UARTx->msgRxHandler.msgDMAChannelOrStream, &DMA_InitTypeDef);
	//---使能DMA
	LL_DMA_EnableChannel(UARTx->msgRxHandler.msgDMA, UARTx->msgRxHandler.msgDMAChannelOrStream);
#else
	//---初始化DMA
	LL_DMA_Init(UARTx->msgRxdHandle.pMsgDMA, UARTx->msgRxdHandle.msgDMAChannelOrStream, &DMA_InitTypeDef);
	//---使能DMA
	LL_DMA_EnableStream(UARTx->msgRxdHandle.pMsgDMA, UARTx->msgRxdHandle.msgDMAChannelOrStream);
	//---是能串口接收DMA
	LL_USART_EnableDMAReq_RX(UARTx->pMsgUART);
#endif
	//---中断配置
#ifdef USE_MCU_STM32F1
	//---DMA中断配置
	NVIC_SetPriority(DMA1_Channel1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 1, 0));
	//---使能中断
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);
#else
	//---DMA中断配置
	NVIC_SetPriority(DMA1_Stream1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 2, 0));
	//---使能中断
	NVIC_EnableIRQ(DMA1_Stream1_IRQn);
#endif
	//---使能DMA传输结束中断
	LL_DMA_EnableIT_TC(UARTx->msgRxdHandle.pMsgDMA, UARTx->msgRxdHandle.msgDMAChannelOrStream);
	//<<<---RX的DMA配置结束
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART3_DMA_Write_Init(UART_HandleType* UARTx)
{
	//>>>---TX的DMA配置
	//---将DMA全部寄存器重新设置为缺省值
#ifdef USE_MCU_STM32F1
	//---F1对应是的DMA1的通道1对应ADC1
	LL_DMA_DeInit(DMA1, LL_DMA_CHANNEL_1);
	//---DMA时钟总线配置
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
#else
	LL_DMA_DeInit(DMA1, LL_DMA_STREAM_3);
	//---DMA时钟总线配置
	//LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
	DMATask_Clock(DMA1, PERIPHERAL_CLOCK_ENABLE);
	UARTx->msgTxdHandle.pMsgDMA = DMA1;
	UARTx->msgTxdHandle.msgDMAChannelOrStream = LL_DMA_STREAM_3;
#endif
	//---DMA初始化结构体
	LL_DMA_InitTypeDef DMA_InitTypeDef = { 0 };
#ifndef USE_MCU_STM32F1
	//---DMA通道
	DMA_InitTypeDef.Channel = LL_DMA_CHANNEL_4;
#endif
	//---数据大小,如果是首次发送，这里的参数只能写0，否则容易发生数据不完整，可能只发送了接个字节就停止发送
	DMA_InitTypeDef.NbData = 0;//UARTx->msgTxdHandler.msgSize;
	//---方向从存储器到外设
	DMA_InitTypeDef.Direction = LL_DMA_DIRECTION_MEMORY_TO_PERIPH;
#ifndef USE_MCU_STM32F1
	//---不用FIFO用直连模式
	DMA_InitTypeDef.FIFOMode = LL_DMA_FIFOMODE_DISABLE;
	//---半字两字节
	DMA_InitTypeDef.FIFOThreshold = LL_DMA_FIFOTHRESHOLD_1_2;
#endif
	//---存储器地址
	DMA_InitTypeDef.MemoryOrM2MDstAddress = (UINT32_T)(UARTx->msgTxdHandle.pMsgVal);
	//---半字两字节
	DMA_InitTypeDef.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;
	//---存储器地址增加
	DMA_InitTypeDef.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT;
	//---DMA正常模式
	DMA_InitTypeDef.Mode = LL_DMA_MODE_NORMAL; //LL_DMA_MODE_CIRCULAR;
	//---DMA外设地址
	DMA_InitTypeDef.PeriphOrM2MSrcAddress = (UINT32_T) & (UARTx->pMsgUART->DR);
#ifndef USE_MCU_STM32F1
	//---无FIFO
	DMA_InitTypeDef.PeriphBurst = LL_DMA_PBURST_SINGLE;
#endif
	//---半字两字节
	DMA_InitTypeDef.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
	//---外设基地址不变
	DMA_InitTypeDef.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
	//---传输通道优先级为高
	DMA_InitTypeDef.Priority = LL_DMA_PRIORITY_HIGH;
	//---DMA初始化
#ifdef USE_MCU_STM32F1
	//---初始化DMA
	LL_DMA_Init(UARTx->msgTxHandler.msgDMA, UARTx->msgTxHandler.msgDMAChannelOrStream, &DMA_InitTypeDef);
	//---使能DMA
	LL_DMA_EnableChannel(UARTx->msgTxHandler.msgDMA, UARTx->msgTxHandler.msgDMAChannelOrStream);
#else
	//---初始化DMA
	LL_DMA_Init(UARTx->msgTxdHandle.pMsgDMA, UARTx->msgTxdHandle.msgDMAChannelOrStream, &DMA_InitTypeDef);
	//---使能DMA,注意发送状态下不能使能DMA，只有需要的时候才能打开
	//LL_DMA_EnableStream(UARTx->msgTxHandler.msgDMA, UARTx->msgTxHandler.msgDMAChannelOrStream);
	//---使能串口发送DMA
	LL_USART_EnableDMAReq_TX(UARTx->pMsgUART);
#endif
	//---中断配置
#ifdef USE_MCU_STM32F1
	//---DMA中断配置
	NVIC_SetPriority(DMA1_Channel1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 1, 0));
	//---使能中断
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);
#else
	//---DMA中断配置
	NVIC_SetPriority(DMA1_Stream3_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 2, 0));
	//---使能中断
	NVIC_EnableIRQ(DMA1_Stream3_IRQn);
#endif
	//---使能DMA传输结束中断
	LL_DMA_EnableIT_TC(UARTx->msgTxdHandle.pMsgDMA, UARTx->msgTxdHandle.msgDMAChannelOrStream);
	//<<<---TX的DMA配置结束
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART3_Init(UART_HandleType* UARTx)
{
	UART3_ConfigInit(UARTx);
	//---校验接收是不是DMA传输
	if (UARTx->msgRxdHandle.msgDMAMode == 0)
	{
		//---使能接收中断
		LL_USART_EnableIT_RXNE(UARTx->pMsgUART);
	}
	else
	{
		//---使能接收空闲中断
		LL_USART_EnableIT_IDLE(UARTx->pMsgUART);
		//---DMA未初始化，则初始化，否则跳过
		if (UARTx->msgRxdHandle.pMsgDMA==0)
		{
			//---初始化DMA设置
			UART3_DMA_Read_Init(UARTx);
		}
	}
	//---校验发送是不是DMA传输方式
	if (UARTx->msgTxdHandle.msgDMAMode != 0)
	{
		//---DMA未初始化，则初始化，否则跳过
		if (UARTx->msgTxdHandle.pMsgDMA==0)
		{
			UART3_DMA_Write_Init(UARTx);
		}
	}
	//---UART1_IRQ中断配置---中断等级配置
	NVIC_SetPriority(USART3_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 2, 0));
	//---使能中断
	NVIC_EnableIRQ(USART3_IRQn);
	//---使能串口
	LL_USART_Enable(UARTx->pMsgUART);
	//---打印初始化信息
	//UART_Printf(UARTx, "===>>串口3初始化完成<<===\r\n");
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART4_ConfigInit(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART4_DMA_Read_Init(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART4_DMA_Write_Init(UART_HandleType* UARTx)
{
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART4_Init(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART5_ConfigInit(UART_HandleType* UARTx)
{
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART5_DMA_Read_Init(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART5_DMA_Write_Init(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART5_Init(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART6_ConfigInit(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART6_DMA_Read_Init(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART6_DMA_Write_Init(UART_HandleType* UARTx)
{
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART6_Init(UART_HandleType* UARTx)
{
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART7_ConfigInit(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART7_DMA_Read_Init(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART7_DMA_Write_Init(UART_HandleType* UARTx)
{
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART7_Init(UART_HandleType* UARTx)
{
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART8_ConfigInit(UART_HandleType* UARTx)
{
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART8_DMA_Read_Init(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART8_DMA_Write_Init(UART_HandleType* UARTx)
{
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART8_Init(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART9_ConfigInit(UART_HandleType* UARTx)
{
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART9_DMA_Read_Init(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART9_DMA_Write_Init(UART_HandleType* UARTx)
{
	return OK_0;
}



///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART9_Init(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART10_ConfigInit(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART10_DMA_Read_Init(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART10_DMA_Write_Init(UART_HandleType* UARTx)
{
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART10_Init(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_Init(UART_HandleType*  UARTx, UINT16_T rxSize, UINT8_T* pRxVal, UINT8_T rxCRCFlag, UINT16_T txSize, UINT8_T* pTxVal, UINT8_T txCRCFlag, UINT32_T(*pTimerTick)(void))
{
	UART_StructInit(UARTx);
	UARTx->msgRxdHandle.msgCRCFlag = rxCRCFlag;
	UARTx->msgRxdHandle.msgMaxSize = rxSize;
	UARTx->msgRxdHandle.pMsgVal = pRxVal;
	//---保存缓存区的首地址
	UARTx->msgRxdHandle.msgMsgValBaseAddr= (VLTUINT32_T)pRxVal;
	UARTx->msgTxdHandle.msgCRCFlag = txCRCFlag;
	UARTx->msgTxdHandle.msgMaxSize = txSize;
	UARTx->msgTxdHandle.pMsgVal = pTxVal;
	//---保存缓存区的首地址
	UARTx->msgTxdHandle.msgMsgValBaseAddr =(VLTUINT32_T)pTxVal;
	//---注册计数函数
	UARTx->msgTxdHandle.pMsgTimeTick = pTimerTick;
	UARTx->msgRxdHandle.pMsgTimeTick = pTimerTick;
	//---端口初始化
#ifdef USART1
	if ((UARTx != NULL) && (UARTx == UART_TASK_ONE))
	{
		return UART1_Init(UARTx);
	}
#endif
#ifdef USART2
	if ((UARTx != NULL) && (UARTx == UART_TASK_TWO))
	{
		return UART2_Init(UARTx);
	}
#endif
#ifdef USART3
	if ((UARTx != NULL) && (UARTx == UART_TASK_THREE))
	{
		return UART3_Init(UARTx);
	}
#endif
#ifdef UART4
	if ((UARTx != NULL) && (UARTx == UART_TASK_FOUR))
	{
		return UART4_Init(UARTx);
	}
#endif
#ifdef UART5
	if ((UARTx != NULL) && (UARTx == UART_TASK_FIVE))
	{
		return UART5_Init(UARTx);
	}
#endif
#ifdef USART6
	if ((UARTx != NULL) && (UARTx == UART_TASK_SIX))
	{
		return UART6_Init(UARTx);
	}
#endif
#ifdef UART7
	if ((UARTx != NULL) && (UARTx == UART_TASK_SEVEN))
	{
		return UART7_Init(UARTx);
	}
#endif
#ifdef UART8
	if ((UARTx != NULL) && (UARTx == UART_TASK_EIGHT))
	{
		return UART8_Init(UARTx);
	}
#endif
#ifdef UART9
	else if ((UARTx != NULL) && (UARTx == UART_TASK_NINE))
	{
		return UART9_Init(UARTx);
	}
#endif
#ifdef UART10
	if ((UARTx != NULL) && (UARTx == UART_TASK_TEN))
	{
		return UART10_Init(UARTx);
	}
#endif
	return ERROR_2;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：串口的发送端口的初始化
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_GPIO_TxInit(UART_HandleType*  UARTx, UINT8_T isInput)
{
#ifdef UART_INIT_GPIO
	if (UARTx->msgTxPort.msgPort != NULL)
	{
		(isInput == UART_GPIOTX_SET_OUTPUT) ? (LL_GPIO_SetPinMode(UARTx->msgTxPort.msgPort, UARTx->msgTxPort.msgBit, LL_GPIO_MODE_ALTERNATE)) : (LL_GPIO_SetPinMode(UARTx->msgTxPort.msgPort, UARTx->msgTxPort.msgBit, LL_GPIO_MODE_INPUT));
	}
#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：485方向控制端口的初始化
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_GPIO_485_Init(UART_HandleType*  UARTx, UINT8_T isEnable)
{
#ifdef USE_UART_485
	if (UARTx->msg485Port.msgPort != NULL)
	{
		(isEnable == UART_485_TX_ENABLE) ? (GPIO_OUT_0(UARTx->msg485Port.msgPort, UARTx->msg485Port.msgBit)) : (GPIO_OUT_1(UARTx->msg485Port.msgPort, UARTx->msg485Port.msgBit));
	}
#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置CRC校验模式
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_SetCRC(UART_HandleDef* UARTDefx, UINT8_T crcFlag)
{
	UARTDefx->msgCRCFlag = crcFlag;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：获取CRC校验模式
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_GetCRC(UART_HandleDef* UARTDefx)
{
	return UARTDefx->msgCRCFlag;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_TimeTick_Init(UART_HandleDef* UARTDefx)
{
	//---时间节点
	UARTDefx->msgRecordTick = ((UARTDefx->pMsgTimeTick != NULL)?(UARTDefx->pMsgTimeTick()):0);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：注销超时计数器
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_TimeTick_DeInit(UART_HandleDef* UARTDefx)
{
	//---清零溢出标志位
	UARTDefx->msgOverFlow = 0;
	//---清零当前时钟
	UARTDefx->msgRecordTick = 0;
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明： 时间计数是否发生超时
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_TimeTick_OverFlow(UART_HandleDef* UARTDefx)
{
	UINT32_T temp = 0;
	//---获取当前时间
	temp = ((UARTDefx->pMsgTimeTick != NULL) ? (UARTDefx->pMsgTimeTick()+2) : 0);
	//---判断是否发生超时错误
	if (temp > UARTDefx->msgRecordTick)
	{
		//---计时器未发生溢出操作
		if ((temp - UARTDefx->msgRecordTick) > UARTDefx->msgMaxTime)
		{
			UARTDefx->msgOverFlow = 1;
			return ERROR_1;
		}
	}
	else 
	{
		//---计时器发生溢出操作
		if ((0xFFFFFFFF - UARTDefx->msgRecordTick + temp) > UARTDefx->msgMaxTime)
		{
			UARTDefx->msgOverFlow = 1;
			return ERROR_1;
		}
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_TimeTask_OverFlow(UART_HandleType*UARTx, UINT8_T isRx)
{
	UINT8_T _return = OK_0;
	//---判断是接收还是发送并校验是不是DMA接收模式
	if ((isRx != 0) && (UARTx->msgRxdHandle.msgDMAMode == 0))
	{
		if ((UARTx->msgRxdHandle.msgRecordTick != 0) && (UARTx->msgRxdHandle.msgMaxTime != 0))
		{
			if (UARTx->msgRxdHandle.msgRecordTick == 0)
			{
				return OK_0;
			}
			//---获取超时值
			_return = UART_TimeTick_OverFlow(&(UARTx->msgRxdHandle));
			//---超时条件判断，发现某些状态下当前记录的时间值在改写为零的时候，时间记录点没有发生同步更新
			//if ((_return != OK_0))
			if ((_return != OK_0) && (UARTx->msgRxdHandle.msgRecordTick != 0))
			{
				//---打印超时的串口信息
				UART_Printf(UARTx, "=>>SP%d:Receive Mode Timeout Error!<<=\r\n", (UARTx->msgIndex - 1));
				//---复位接收数据缓存区
				UART_Read_Init(UARTx);
			}
		}
	}
	else if(UARTx->msgTxdHandle.msgDMAMode == 0)
	{
		if ((UARTx->msgTxdHandle.msgRecordTick != 0) && (UARTx->msgTxdHandle.msgMaxTime != 0))
		{
			if (UARTx->msgTxdHandle.msgRecordTick == 0)
			{
				return OK_0;
			}
			//---获取超时值
			_return = UART_TimeTick_OverFlow(&(UARTx->msgTxdHandle));
			//---超时条件判断，发现某些状态下当前记录的时间值在改写为零的时候，时间记录点没有发生同步更新
			if ((_return != OK_0) && (UARTx->msgTxdHandle.msgRecordTick != 0))
			{
				//---打印超时的串口信息
				UART_Printf(UARTx, "=>>SP%d:Send Mode Timeout Error!<<=\r\n", (UARTx->msgIndex - 1));
				//---复位发送数据缓存区
				UART_Write_Init(UARTx);
			}
			else
			{
				UARTx->msgTxdHandle.msgOverFlow = 0;
			}
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明： 接受到数据最大长度使用1字节表示
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_ITRead_8BitsTask(UART_HandleType*UARTx, UINT8_T val)
{
	//---保存数到的数据
	static UINT8_T tempVal;
	tempVal = val;
	//---数据接收步序
	switch (UARTx->msgRxdHandle.msgStep)
	{
		//---接收数据的报头
		case 0:
			if (UARTx->msgRxdHandle.msgRIndex == 0)
			{
				if (UARTx->msgRxdID == tempVal)
				{
					UARTx->msgRxdHandle.pMsgVal[0] = tempVal;
					UARTx->msgRxdHandle.msgStep = 1;
					//---记录数据的个数
					UARTx->msgRxdHandle.msgCount = 1;
					//---收到第一个符合格式的数据，启动超时计数器
					UART_TimeTick_Init(&(UARTx->msgRxdHandle));
					//---清零超时标志
					UART_ClearOverFlow(&(UARTx->msgRxdHandle));
				}
			}
			break;
			//---接收数据的长度
		case 1:
			if ((tempVal > 0) && (tempVal < (UINT8_T)(UARTx->msgRxdHandle.msgMaxSize & 0xFF)))
			{
				UARTx->msgRxdHandle.pMsgVal[1] = tempVal;
				//---获取数据的接收长度
				UARTx->msgRxdHandle.msgWIndex = tempVal;
				//---记录数据的个数
				UARTx->msgRxdHandle.msgCount += 1;
				//---下一步骤
				UARTx->msgRxdHandle.msgStep = 2;
			}
			else
			{
				UARTx->msgRxdHandle.msgStep = 0;
			}
			//---复位超时计数器
			UART_TimeTick_Init(&(UARTx->msgRxdHandle));
			break;
			//---接收数据信息
		case 2:
			UARTx->msgRxdHandle.pMsgVal[UARTx->msgRxdHandle.msgRIndex + 2] = tempVal;
			UARTx->msgRxdHandle.msgRIndex++;
			//---记录数据的个数
			UARTx->msgRxdHandle.msgCount += 1;
			//---判断是否溢出
			if (UARTx->msgRxdHandle.msgRIndex >= UARTx->msgRxdHandle.msgMaxSize)
			{
				UARTx->msgRxdHandle.msgRIndex = 0;
			}
			//---复位超时计数器
			UART_TimeTick_Init(&(UARTx->msgRxdHandle));
			//---判断是否接收完成
			if (UARTx->msgRxdHandle.msgRIndex >= UARTx->msgRxdHandle.msgWIndex)
			{
				UARTx->msgRxdHandle.msgStep = 3;
				UARTx->msgRxdHandle.msgState = UART_OK;
				//---清零超时计数器
				//UART_TimeTick_DeInit(UARTx, 1);
				//---记录接收完成的时间
				UARTx->msgRxdHandle.msgRecordTime = ((UARTx->msgRxdHandle.pMsgTimeTick != NULL) ? (UARTx->msgRxdHandle.pMsgTimeTick()) : 0);
			}
			break;
		case 3:
			//---清零超时计数器
			//UART_TimeTick_DeInit(UARTx,1);
			break;
		default:
			//UARTx->msgRxHandler.msgNowTime = 0;
			break;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明： 接受到数据最大长度使用2字节表示
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_ITRead_16BitsTask(UART_HandleType*UARTx, UINT8_T val)
{
	//---保存数到的数据
	static UINT8_T tempVal;
	tempVal = val;
	//---数据接收步序
	switch (UARTx->msgRxdHandle.msgStep)
	{
		//---接收数据的报头
		case 0:
			if (UARTx->msgRxdHandle.msgRIndex == 0)
			{
				if (UARTx->msgRxdID == tempVal)
				{
					UARTx->msgRxdHandle.pMsgVal[0] = tempVal;
					UARTx->msgRxdHandle.msgStep = 1;
					//---记录数据的个数
					UARTx->msgRxdHandle.msgCount = 1;
					//---收到第一个符合格式的数据，启动超时计数器
					UART_TimeTick_Init(&(UARTx->msgRxdHandle));
					//---清零超时标志
					UART_ClearOverFlow(&(UARTx->msgRxdHandle));
				}
			}
			break;
			//---接收数据的长度高位
		case 1:
			UARTx->msgRxdHandle.pMsgVal[1] = tempVal;
			UARTx->msgRxdHandle.msgWIndex = tempVal;
			UARTx->msgRxdHandle.msgWIndex <<= 8;
			UARTx->msgRxdHandle.msgStep = 2;
			//---记录数据的个数
			UARTx->msgRxdHandle.msgCount += 1;
			//---复位超时计数器
			UART_TimeTick_Init(&(UARTx->msgRxdHandle));
			break;
			//---接收数据的长度低位
		case 2:
			UARTx->msgRxdHandle.pMsgVal[2] = tempVal;
			UARTx->msgRxdHandle.msgWIndex += tempVal;
			//---记录数据的个数
			UARTx->msgRxdHandle.msgCount += 1;
			//---判断数据是否合法
			if ((UARTx->msgRxdHandle.msgWIndex > 0) && (UARTx->msgRxdHandle.msgWIndex < UARTx->msgRxdHandle.msgMaxSize))
			{
				//---记录数据的个数
				UARTx->msgRxdHandle.msgCount = UARTx->msgRxdHandle.msgWIndex;
				//---下一步骤
				UARTx->msgRxdHandle.msgStep = 3;
			}
			else
			{
				UARTx->msgRxdHandle.msgStep = 0;
			}
			//---复位超时计数器
			UART_TimeTick_Init(&(UARTx->msgRxdHandle));
			break;
			//---接收数据信息
		case 3:
			UARTx->msgRxdHandle.pMsgVal[UARTx->msgRxdHandle.msgRIndex + 3] = tempVal;
			UARTx->msgRxdHandle.msgRIndex++;
			//---记录数据的个数
			UARTx->msgRxdHandle.msgCount += 1;
			//---判断是否溢出
			if (UARTx->msgRxdHandle.msgRIndex >= UARTx->msgRxdHandle.msgMaxSize)
			{
				UARTx->msgRxdHandle.msgRIndex = 0;
			}
			//---复位超时计数器
			UART_TimeTick_Init(&(UARTx->msgRxdHandle));
			//---判断是否接收完成
			if (UARTx->msgRxdHandle.msgRIndex >= UARTx->msgRxdHandle.msgWIndex)
			{
				UARTx->msgRxdHandle.msgStep = 4;
				UARTx->msgRxdHandle.msgState = UART_OK;
				//---清零超时计数器
				//UART_TimeTick_DeInit(UARTx, 1);
				//---记录接收完成的时间
				UARTx->msgRxdHandle.msgRecordTime = ((UARTx->msgRxdHandle.pMsgTimeTick != NULL) ? (UARTx->msgRxdHandle.pMsgTimeTick()) : 0);
			}
			break;
		case 4:
			//---清零超时计数器
			//UART_TimeTick_DeInit(UARTx,1);
			break;
		default:
			//UARTx->msgRxHandler.msgNowTime = 0;
			break;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：串口中断接收数据，这里通过数据缓存区的大小，判断接收数据的长度，调用不同的接收函数
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_ITRead_Task(UART_HandleType*UARTx, UINT8_T val)
{
	if (UARTx->msgRxdHandle.msgMaxSize < 0xFF)
	{
		return UART_ITRead_8BitsTask(UARTx, val);
	}
	else
	{
		return UART_ITRead_16BitsTask(UARTx, val);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_PollMode_WriteByte(UART_HandleType*UARTx, UINT8_T  val)
{
	UINT8_T _return=OK_0;
	//---获取当前时间节拍
	UINT32_T nowTime = 0;
	UINT32_T oldTime = 0;
	UINT32_T cnt = 0;
	//---获取当前时间节拍
	oldTime = UARTx->msgTxdHandle.pMsgTimeTick();
	//---发送数据
	LL_USART_TransmitData8(UARTx->pMsgUART, val);
	//---等待发送完成
	while (LL_USART_IsActiveFlag_TC(UARTx->pMsgUART) == RESET)
	{
		//--->>>加入超时机制---开始
		//---当前时间
		nowTime = UARTx->msgTxdHandle.pMsgTimeTick();
		//---判断滴答定时是否发生溢出操作
		if (nowTime < oldTime)
		{
			cnt = (0xFFFFFFFF - oldTime + nowTime);
		}
		else
		{
			cnt = nowTime - oldTime;
		}
		//---判断是否超时
		if (cnt > 50)
		{
			//---发送发生超时错误
			_return=ERROR_1;
			break;
		}
		//--->>>加入超时机制---结束
		//---喂狗
		WDT_RESET();
	}
	//---清除发送完成标志位
	LL_USART_ClearFlag_TC(UARTx->pMsgUART);
	return _return;
}
///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明： 发送字符串
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_PollMode_WriteData(UART_HandleType*UARTx, char *pVal)
{
	//---设置485为发送模式
	UART_GPIO_485_Init(UARTx, UART_485_TX_ENABLE);
	//---切换发送端口为输出模式
	UART_GPIO_TxInit(UARTx, UART_GPIOTX_SET_OUTPUT);
	//---关闭中断
	//CLI();
	while (*pVal != '\0')
	{
		UART_PollMode_WriteByte(UARTx, (UINT8_T)*pVal);
		pVal++;
	}
	//---使能中断
	//SEI();
	//---设置485为接收模式
	UART_GPIO_485_Init(UARTx, UART_485_RX_ENABLE);
	//---切换发送端口为输入模式
	UART_GPIO_TxInit(UARTx, UART_GPIOTX_SET_INPUT);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_PollMode_ReadByte(UART_HandleType*UARTx)
{
	//---获取当前时间节拍
	UINT32_T nowTime = 0;
	UINT32_T oldTime = 0;
	UINT32_T cnt = 0;
	//---获取当前时间节拍
	oldTime = UARTx->msgTxdHandle.pMsgTimeTick();
	//---等待接收完成
	while (LL_USART_IsActiveFlag_RXNE(UARTx->pMsgUART) != RESET)
	{
		//--->>>加入超时机制---开始
		//---当前时间
		nowTime = UARTx->msgTxdHandle.pMsgTimeTick();
		//---判断滴答定时是否发生溢出操作
		if (nowTime < oldTime)
		{
			cnt = (0xFFFFFFFF - oldTime + nowTime);
		}
		else
		{
			cnt = nowTime - oldTime;
		}
		//---判断是否超时
		if (cnt > 50)
		{
			//---发送发生超时错误
			break;
		}
		//--->>>加入超时机制---结束
		//---喂狗
		WDT_RESET();
	}
	return LL_USART_ReceiveData8(UARTx->pMsgUART);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_PollMode_ReadData(UART_HandleType*UARTx, char *pVal)
{
	while (*pVal != '\0')
	{
		*pVal = UART_PollMode_ReadByte(UARTx);
		pVal++;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_ITWrite_TXETask(UART_HandleType*UARTx)
{
	VLTUINT8_T tempFlag=OK_0;
	if (UARTx->msgTxdHandle.msgWIndex != 0)
	{
		if (UARTx->msgTxdHandle.msgRIndex != UARTx->msgTxdHandle.msgWIndex)
		{
			//---发送8Bit的数据
			LL_USART_TransmitData8(UARTx->pMsgUART, UARTx->msgTxdHandle.pMsgVal[UARTx->msgTxdHandle.msgRIndex]);
			//---数据缓存区序号增加
			UARTx->msgTxdHandle.msgRIndex++;
			//---校验缓存区是否溢出
			if (UARTx->msgTxdHandle.msgRIndex >= UARTx->msgTxdHandle.msgMaxSize)
			{
				UARTx->msgTxdHandle.msgRIndex = 0;
			}
			//---校验数据是否都填入缓存区
			if ((UARTx->msgTxdHandle.msgRIndex >= UARTx->msgTxdHandle.msgWIndex) && (UARTx->msgTxdHandle.msgCount > 0) && (UARTx->msgTxdHandle.msgRIndex >= UARTx->msgTxdHandle.msgCount))
			{
				//---发送完成,发送数据寄存器空中断不使能
				LL_USART_DisableIT_TXE(UARTx->pMsgUART);
				//---使能发送完成中断，用于切换TXD端口为输入状态
				LL_USART_EnableIT_TC(UARTx->pMsgUART);
			}
		}
		else
		{
			tempFlag = ERROR_1;
		}
	}
	else
	{
		tempFlag = ERROR_2;
	}
	//---校验结果
	if (tempFlag!=OK_0)
	{
		//---发送完成,发送数据寄存器空中断不使能---检查是否存在异常；关闭发送数据寄存器空中断
		LL_USART_DisableIT_TXE(UARTx->pMsgUART);
		//---清空数据发送缓存区
		UART_Write_Init(UARTx);
	}
	//---复位超时计数器
	UART_TimeTick_Init(&(UARTx->msgTxdHandle));
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_ITWrite_TCTask(UART_HandleType*UARTx)
{
#ifdef USE_UART_485
	//---定义了485，由于485响应的延迟问题,增加发送换行符，用于缓冲485的响应
	if ((UARTx->msg485Port.msgPort != NULL) && (UARTx->msgTxdHandle.msgStep == 0))
	{
		//---发送8Bit的数据
		LL_USART_TransmitData8(UARTx->pMsgUART, 0x0D);
		UARTx->msgTxdHandle.msgStep = 1;
	}
	else if ((UARTx->msg485Port.msgPort != NULL) && (UARTx->msgTxdHandle.msgStep == 1))
	{
		//---发送8Bit的数据
		LL_USART_TransmitData8(UARTx->pMsgUART, 0x0A);
		UARTx->msgTxdHandle.msgStep = 2;
	}
	else
#endif
	{
		//---发送完成,发送数据发送完成中断不使能
		LL_USART_DisableIT_TC(UARTx->pMsgUART);
		//---清空数据发送缓存区
		UART_Write_Init(UARTx);
		//---清零超时计数器
		//UART_TimeTick_DeInit(UARTx, 0);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：发送数据
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_RealTime_AddByte(UART_HandleType*UARTx, UINT8_T val)
{
	if (UARTx->msgTxdHandle.pMsgVal != NULL)
	{
		if (UARTx->msgTxdHandle.msgWIndex >= UARTx->msgTxdHandle.msgMaxSize)
		{
			UARTx->msgTxdHandle.msgWIndex = 0;
		}
		UARTx->msgTxdHandle.pMsgVal[UARTx->msgTxdHandle.msgWIndex] = val;
		UARTx->msgTxdHandle.msgWIndex++;
		//---判断发送寄存器空中断是否使能
		if (LL_USART_IsEnabledIT_TXE(UARTx->pMsgUART) == 0)
		{
			//---设置485为发送模式
			UART_GPIO_485_Init(UARTx, UART_485_TX_ENABLE);
			//---切换发送端口为输出模式
			UART_GPIO_TxInit(UARTx, UART_GPIOTX_SET_OUTPUT);
			//---使能发送空中断
			LL_USART_EnableIT_TXE(UARTx->pMsgUART);
		}
		return OK_0;
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：发送数据的大小
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_RealTime_AddDataSize(UART_HandleType*UARTx, UINT16_T val)
{
	UINT8_T _return = ERROR_1;
	if (UARTx->msgTxdHandle.pMsgVal != NULL)
	{
		if ((UARTx->msgTxdHandle.msgCRCFlag == UART_CRC_CHECKSUM) || (UARTx->msgTxdHandle.msgCRCFlag == UART_CRC_CRC8))
		{
			val += 1;
		}
		else if (UARTx->msgTxdHandle.msgCRCFlag == UART_CRC_CRC16)
		{
			val += 2;
		}
		else if (UARTx->msgTxdHandle.msgCRCFlag == UART_CRC_CRC32)
		{
			val += 4;
		}
		//---判断是否有设备的ID信息
		if ((UARTx->msgCmdIndex - UARTx->msgIDIndex) != 0)
		{
			val += 1;
		}
		//---判断是否增加换行符
		if ((UARTx->msgTxdHandle.msgAddNewLine==1))
		{
			val += 2;
		}
		//---判断数据的格式
		if (UARTx->msgTxdHandle.msgMaxSize > 250)
		{
			UART_RealTime_AddByte(UARTx, (UINT8_T)(val >> 8));
			_return = UART_RealTime_AddByte(UARTx, (UINT8_T)(val & 0xFF));
			val += 3;
		}
		else
		{
			_return = UART_RealTime_AddByte(UARTx, (UINT8_T)(val & 0xFF));
			val += 2;
		}
		//---判断是否有设备的ID信息并填充ID信息
		if ((UARTx->msgCmdIndex - UARTx->msgIDIndex) != 0)
		{
			_return = UART_RealTime_AddByte(UARTx, UARTx->msgID);
		}		
		//---计算发送数据的个数
		UARTx->msgTxdHandle.msgCount = val;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：填充数据的CRC校验信息
//////输入参数:
//////输出参数:
//////说		明：使用CRC，数据的必须从0开始使用
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_RealTime_AddCRC(UART_HandleType*UARTx)
{
	//---校验CRC是否初始化
	if ((UARTx->msgTxdHandle.msgCRCFlag != UART_CRC_NONE) && (CRCTask_Enable() == OK_0))
	{
		UINT32_T crcVal = 0;
		//---判断数据校验模式
		if (UARTx->msgTxdHandle.msgCRCFlag == UART_CRC_CHECKSUM)
		{
			crcVal = CRCTask_CheckSum(UARTx->msgTxdHandle.pMsgVal, UARTx->msgTxdHandle.msgWIndex);
			UART_RealTime_AddByte(UARTx, (UINT8_T)crcVal);
		}
		else if (UARTx->msgTxdHandle.msgCRCFlag == UART_CRC_CRC8)
		{
			crcVal = CRCTask_CRC8(USE_CRC8_07H, UARTx->msgTxdHandle.pMsgVal, UARTx->msgTxdHandle.msgWIndex);
			UART_RealTime_AddByte(UARTx, (UINT8_T)crcVal);
		}
		else if (UARTx->msgTxdHandle.msgCRCFlag == UART_CRC_CRC16)
		{
			crcVal = CRCTask_CRC16(UARTx->msgTxdHandle.pMsgVal, UARTx->msgTxdHandle.msgWIndex);
			UART_RealTime_AddByte(UARTx, (UINT8_T)(crcVal >> 8));
			UART_RealTime_AddByte(UARTx, (UINT8_T)crcVal);
		}
		else if (UARTx->msgTxdHandle.msgCRCFlag == UART_CRC_CRC32)
		{
			crcVal = CRCTask_CRC32(UARTx->msgTxdHandle.pMsgVal, UARTx->msgTxdHandle.msgWIndex);
			UART_RealTime_AddByte(UARTx, (UINT8_T)(crcVal >> 24));
			UART_RealTime_AddByte(UARTx, (UINT8_T)(crcVal >> 16));
			UART_RealTime_AddByte(UARTx, (UINT8_T)(crcVal >> 8));
			UART_RealTime_AddByte(UARTx, (UINT8_T)crcVal);
		}
		return OK_0;
	}
	//---判断是否增加换行符
	if ((UARTx->msgTxdHandle.msgAddNewLine==1))
	{
		UART_RealTime_AddByte(UARTx, 0x0D);
		UART_RealTime_AddByte(UARTx, 0x0A);
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：发送多字节数据
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_RealTime_AddData(UART_HandleType* UARTx, UINT8_T* pVal, UINT16_T length)
{
	UINT16_T i = 0;
	UINT8_T _return = OK_0;
	for (i = 0; i < length; i++)
	{
		_return = UART_RealTime_AddByte(UARTx, pVal[i]);
		//---判断数据是否填充正确
		if (_return != OK_0)
		{
			break;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 
//////输入参数: 
//////输出参数: 
//////说		明： 处理数据填充前的操作，约定好报头，和有效数据开始的位置
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_FillMode_Init(UART_HandleType*UARTx,UINT8_T isChildCmd)
{
	//---等待发送空闲
	if (UART_Write_WaitIdle(UARTx)==OK_0)
	{	
		UARTx->msgTxdHandle.msgWIndex = 0;
		UARTx->msgTxdHandle.msgFlagIndex = 0;
		//---填充数据报头
		UART_FillMode_AddByte(UARTx, UARTx->msgTxdID);
		//---填充数据长度
		UART_FillMode_AddByte(UARTx, 0x00);
		if (UARTx->msgTxdHandle.msgMaxSize > 0xFF)
		{
			UART_FillMode_AddByte(UARTx, 0x00);
			UARTx->msgTxdHandle.msgFlagIndex += 1;
		}
		//---填充多设备通信的设备ID
		if ((UARTx->msgCmdIndex - UARTx->msgIDIndex) != 0)
		{
			UART_FillMode_AddByte(UARTx, UARTx->msgID);
		}
		//---主命令/命令
		UART_FillMode_AddByte(UARTx, UARTx->msgRxdHandle.pMsgVal[UARTx->msgCmdIndex]);
		//---校验是否有子命令
		if (isChildCmd != 0)
		{
			//---子命令
			UART_FillMode_AddByte(UARTx, UARTx->msgRxdHandle.pMsgVal[UARTx->msgCmdIndex + (isChildCmd == 0 ? 0 : 1)]);
		}
		//---标识返回执行结果在缓存区中断的序号
		UARTx->msgTxdHandle.msgFlagIndex = UARTx->msgTxdHandle.msgWIndex;
		//---返回执行结果
		return OK_0;
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：数据填充后在发送
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_FillMode_AddByte(UART_HandleType*UARTx, UINT8_T val)
{
	UARTx->msgTxdHandle.pMsgVal[UARTx->msgTxdHandle.msgWIndex] = val;
	UARTx->msgTxdHandle.msgWIndex++;
	if (UARTx->msgTxdHandle.msgWIndex >= UARTx->msgTxdHandle.msgMaxSize)
	{
		UARTx->msgTxdHandle.msgWIndex = 0;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_FillMode_AddData(UART_HandleType*UARTx, UINT8_T *pVal, UINT16_T length)
{
	UINT16_T i = 0;
	UINT8_T _return = OK_0;
	for (i = 0; i < length; i++)
	{
		_return = UART_FillMode_AddByte(UARTx, pVal[i]);
		//---判断数据是否填充正确
		if (_return != OK_0)
		{
			break;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置执行结果标识
//////输入参数:
//////输出参数:
//////说		明：数据填充后在发送
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_FillMode_SetResultFlag(UART_HandleType* UARTx, UINT8_T val)
{
	UARTx->msgTxdHandle.pMsgVal[UARTx->msgTxdHandle.msgFlagIndex] = val;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：写的序号的增加值
//////输入参数:
//////输出参数:
//////说		明：数据填充后在发送
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_FillMode_AddIndexW(UART_HandleType* UARTx, UINT16_T val)
{
	UARTx->msgTxdHandle.msgWIndex += val;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_Read_CRCTask(UART_HandleType*UARTx)
{
	UINT32_T crcVal = 0;
	UINT32_T crcTemp = 0;
	//---接收数据的个数
	UINT16_T length = UARTx->msgRxdHandle.msgWIndex;
	//---校验CRC是否初始化
	if ((UARTx->msgRxdHandle.msgCRCFlag != UART_CRC_NONE) && (CRCTask_Enable() == OK_0))
	{
		//---判断数据校验模式
		if (UARTx->msgRxdHandle.msgCRCFlag == UART_CRC_CHECKSUM)
		{
			length -= 1;
			if (UARTx->msgRxdHandle.msgMaxSize < 250)
			{
				UARTx->msgRxdHandle.pMsgVal[1] = (UINT8_T)(length);
				//---获取校验和
				crcTemp = UARTx->msgRxdHandle.pMsgVal[length + 2];
				//---参与校验和计算的数据总长度
				length += 2;
			}
			else
			{
				UARTx->msgRxdHandle.pMsgVal[1] = (UINT8_T)(length >> 8);
				UARTx->msgRxdHandle.pMsgVal[2] = (UINT8_T)(length);
				//---获取校验和
				crcTemp = UARTx->msgRxdHandle.pMsgVal[length + 3];
				//---参与校验和计算的数据总长度
				length += 3;
			}
			//---计算校验和
			crcVal = CRCTask_CheckSum(UARTx->msgRxdHandle.pMsgVal, length);
		}
		else if (UARTx->msgRxdHandle.msgCRCFlag == UART_CRC_CRC8)
		{
			length -= 1;
			if (UARTx->msgRxdHandle.msgMaxSize < 250)
			{
				UARTx->msgRxdHandle.pMsgVal[1] = (UINT8_T)(length);
				//---获取校验和
				crcTemp = UARTx->msgRxdHandle.pMsgVal[length + 2];
				//---参与校验和计算的数据总长度
				length += 2;
			}
			else
			{
				UARTx->msgRxdHandle.pMsgVal[1] = (UINT8_T)(length >> 8);
				UARTx->msgRxdHandle.pMsgVal[2] = (UINT8_T)(length);
				//---获取校验和
				crcTemp = UARTx->msgRxdHandle.pMsgVal[length + 3];
				//---参与校验和计算的数据总长度
				length += 3;
			}
			//---计算CRC8校验值
			crcVal = CRCTask_CRC8(USE_CRC8_07H, UARTx->msgRxdHandle.pMsgVal, length);
		}
		else if (UARTx->msgRxdHandle.msgCRCFlag == UART_CRC_CRC16)
		{
			length -= 2;
			if (UARTx->msgRxdHandle.msgMaxSize < 250)
			{
				UARTx->msgRxdHandle.pMsgVal[1] = (UINT8_T)(length);
				//---获取CRC16的高位值
				crcTemp = UARTx->msgRxdHandle.pMsgVal[length + 1];
				//---获取CRC16的低位值
				crcTemp = (crcTemp << 8) + UARTx->msgRxdHandle.pMsgVal[length + 2];
				//---参与校验和计算的数据总长度
				length += 2;
			}
			else
			{
				UARTx->msgRxdHandle.pMsgVal[1] = (UINT8_T)(length >> 8);
				UARTx->msgRxdHandle.pMsgVal[2] = (UINT8_T)(length);
				//---获取CRC16的高位值
				crcTemp = UARTx->msgRxdHandle.pMsgVal[length + 2];
				//---获取CRC16的低位值
				crcTemp = (crcTemp << 8) + UARTx->msgRxdHandle.pMsgVal[length + 3];
				//---参与校验和计算的数据总长度
				length += 3;
			}
			//---计算CRC16校验值
			crcVal = CRCTask_CRC16(UARTx->msgRxdHandle.pMsgVal, length);
		}
		else if (UARTx->msgRxdHandle.msgCRCFlag == UART_CRC_CRC32)
		{
			length -= 4;
			if (UARTx->msgRxdHandle.msgMaxSize < 250)
			{
				UARTx->msgRxdHandle.pMsgVal[1] = (UINT8_T)(length);
				//---获取CRC32的最高位值
				crcTemp = UARTx->msgRxdHandle.pMsgVal[length - 1];
				//---获取CRC32的次高位值
				crcTemp = (crcTemp << 8) + UARTx->msgRxdHandle.pMsgVal[length];
				//---获取CRC32的次低位值
				crcTemp = (crcTemp << 8) + UARTx->msgRxdHandle.pMsgVal[length + 1];
				//---获取CRC32的低位值
				crcTemp = (crcTemp << 8) + UARTx->msgRxdHandle.pMsgVal[length + 2];
				//---参与校验和计算的数据总长度
				length += 2;
			}
			else
			{
				UARTx->msgRxdHandle.pMsgVal[1] = (UINT8_T)(length >> 8);
				UARTx->msgRxdHandle.pMsgVal[2] = (UINT8_T)(length);
				//---获取CRC32的最高位值
				crcTemp = UARTx->msgRxdHandle.pMsgVal[length];
				//---获取CRC32的次高位值
				crcTemp = (crcTemp << 8) + UARTx->msgRxdHandle.pMsgVal[length + 1];
				//---获取CRC32的次低位值
				crcTemp = (crcTemp << 8) + UARTx->msgRxdHandle.pMsgVal[length + 2];
				//---获取CRC32的低位值
				crcTemp = (crcTemp << 8) + UARTx->msgRxdHandle.pMsgVal[length + 3];
				length += 3;
			}
			crcVal = CRCTask_CRC32(UARTx->msgRxdHandle.pMsgVal, length);
		}
		//---比对CRC的值
		if (crcVal != crcTemp)
		{
			return  ERROR_1;
		}
	}
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_FillMode_WriteCRCTask(UART_HandleType*UARTx)
{
	//---校验CRC是否初始化
	if ((UARTx->msgTxdHandle.msgCRCFlag != UART_CRC_NONE) && (CRCTask_Enable() == OK_0))
	{
		UINT32_T crcVal = 0;
		//--要发送数据的总长度
		UINT16_T length = UARTx->msgTxdHandle.msgWIndex;
		//---判断是否增加换行符
		if ((UARTx->msgTxdHandle.msgAddNewLine==1))
		{
			length += 2;
		}
		//---数据大小的整理
		if (UARTx->msgTxdHandle.msgMaxSize < 0xFF)
		{
			UARTx->msgTxdHandle.pMsgVal[1] = (UINT8_T)(length- 2);
		}
		else
		{
			UARTx->msgTxdHandle.pMsgVal[1] = (UINT8_T)((length - 3) >> 8);
			UARTx->msgTxdHandle.pMsgVal[2] = (UINT8_T)((length - 3));
		}		
		//---判断数据校验模式
		if (UARTx->msgTxdHandle.msgCRCFlag == UART_CRC_CHECKSUM)
		{
			//---校验和
			crcVal = CRCTask_CheckSum(UARTx->msgTxdHandle.pMsgVal, UARTx->msgTxdHandle.msgWIndex);
			UART_FillMode_AddByte(UARTx, (UINT8_T)crcVal);
		}
		else if (UARTx->msgTxdHandle.msgCRCFlag == UART_CRC_CRC8)
		{
			//---CRC8校验
			crcVal = CRCTask_CRC8(USE_CRC8_07H, UARTx->msgTxdHandle.pMsgVal, UARTx->msgTxdHandle.msgWIndex);
			UART_FillMode_AddByte(UARTx, (UINT8_T)crcVal);
		}
		else if (UARTx->msgTxdHandle.msgCRCFlag == UART_CRC_CRC16)
		{
			//---CRC16校验
			crcVal = CRCTask_CRC16(UARTx->msgTxdHandle.pMsgVal, UARTx->msgTxdHandle.msgWIndex);
			UART_FillMode_AddByte(UARTx, (UINT8_T)(crcVal >> 8));
			UART_FillMode_AddByte(UARTx, (UINT8_T)crcVal);
		}
		else if (UARTx->msgTxdHandle.msgCRCFlag == UART_CRC_CRC32)
		{
			//---CRC32校验
			crcVal = CRCTask_CRC32(UARTx->msgTxdHandle.pMsgVal, UARTx->msgTxdHandle.msgWIndex);
			UART_FillMode_AddByte(UARTx, (UINT8_T)(crcVal >> 24));
			UART_FillMode_AddByte(UARTx, (UINT8_T)(crcVal >> 16));
			UART_FillMode_AddByte(UARTx, (UINT8_T)(crcVal >> 8));
			UART_FillMode_AddByte(UARTx, (UINT8_T)crcVal);
		}
		//---发送数据的大小
		UARTx->msgTxdHandle.msgCount = UARTx->msgTxdHandle.msgWIndex;
		return OK_0;
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：等待发送进入空闲模式
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_Write_WaitIdle(UART_HandleType* UARTx)
{
	//---获取当前时间节拍
	UINT32_T nowTime = 0;
	UINT32_T oldTime = 0;
	UINT32_T cnt = 0;
	//---获取当前时间节拍
	oldTime = UARTx->msgTxdHandle.pMsgTimeTick();
	//---检查发送状态，等待之前的数据发送完成;必须是空闲状态，总线上没有其他数据放
	while ((UARTx->msgTxdHandle.msgState == UART_BUSY) || (UARTx->msgTxdHandle.msgState == UART_PRINTF) || (UARTx->msgTxdHandle.msgState == UART_DMA))
	{
		//---当前时间
		nowTime = UARTx->msgTxdHandle.pMsgTimeTick();
		//---判断滴答定时是否发生溢出操作
		if (nowTime < oldTime)
		{
			cnt = (0xFFFFFFFF - oldTime + nowTime);
		}
		else
		{
			cnt = nowTime - oldTime;
		}
		//---判断是否超时
		if (cnt > 100)
		{
			//---清零发送状态，强制清理
			UART_Write_Init(UARTx);
			//---发送发生超时错误
			return ERROR_1;
		}
		//---喂狗
		WDT_RESET();
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：填充模式启动发送，这里适合填充之后中断发送和DMA模式（DMA模式是数据填充完成之后，才能启动发送的）
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_FillMode_WriteByteSTART(UART_HandleType*UARTx, UINT8_T isNeedID)
{
	//---判断端口是否空闲
	if(UART_Write_WaitIdle(UARTx)==OK_0)
	{
		//---设置发送状态为空闲中
		UARTx->msgTxdHandle.msgState = UART_BUSY;
		//---判断是否需要填充报头
		if (isNeedID == 1)
		{
			//---填充报头和数据长度
			UARTx->msgTxdHandle.pMsgVal[0] = UARTx->msgTxdID;
		}
		//---填充设备ID
		if ((UARTx->msgCmdIndex - UARTx->msgIDIndex) != 0)
		{
			UARTx->msgTxdHandle.pMsgVal[UARTx->msgIDIndex] = UARTx->msgID;
		}	
		//---发送CRC处理
		UART_FillMode_WriteCRCTask(UARTx);
		//---判断是否增加换行符
		if (( UARTx->msgTxdHandle.msgAddNewLine == 1 ))
		{
			UART_FillMode_AddByte( UARTx, 0x0D );
			UART_FillMode_AddByte( UARTx, 0x0A );
		}	
		//---数据大小的整理
		if (UARTx->msgTxdHandle.msgMaxSize < 0xFF)
		{
			UARTx->msgTxdHandle.pMsgVal[1] = (UINT8_T)(UARTx->msgTxdHandle.msgWIndex - 2);
		}
		else
		{
			UARTx->msgTxdHandle.pMsgVal[1] = (UINT8_T)((UARTx->msgTxdHandle.msgWIndex - 3) >> 8);
			UARTx->msgTxdHandle.pMsgVal[2] = (UINT8_T)((UARTx->msgTxdHandle.msgWIndex - 3));
		}
		UARTx->msgTxdHandle.msgCount=UARTx->msgTxdHandle.msgWIndex;
		//---设置485为发送模式
		UART_GPIO_485_Init(UARTx, UART_485_TX_ENABLE);
		//---切换发送端口为输出模式
		UART_GPIO_TxInit(UARTx, UART_GPIOTX_SET_OUTPUT);
	#ifdef UART_INIT_GPIO
		//---获取最后1字节的数据
		UARTx->msgWriteFinalData= UARTx->msgTxdHandle.pMsgVal[UARTx->msgTxdHandle.msgCount-1];
	#endif
		//---校验是不是DMA模式
		if (UARTx->msgTxdHandle.msgDMAMode==0)
		{
			//---发送数据寄存器空中断使能
			LL_USART_EnableIT_TXE(UARTx->pMsgUART);
		}
		else
		{
			//---设置数据地址
			UART_DMA_Write_SetMemoryAddress(UARTx, (UARTx->msgTxdHandle.pMsgVal));
			//---启动DMA发送
			UART_DMA_Write_RESTART(UARTx);
		}
		//---复位超时计数器
		UART_TimeTick_Init(&(UARTx->msgTxdHandle));
		return OK_0;
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：填充模式启动发送，这里适合填充之后中断发送和DMA模式（DMA模式是数据填充完成之后，才能启动发送的）
//////输入参数: 发送指定长度的数组信息，默认给定的数据是需要的数据，内部没有对数据进行处理
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_FillMode_WriteArraySTART(UART_HandleType* UARTx, UINT8_T *pArrayVal,UINT16_T length)
{
	if (UART_Write_WaitIdle(UARTx) == OK_0)
	{
		//---设置发送状态为忙碌状态
		UARTx->msgTxdHandle.msgState = UART_BUSY;
		//---拷贝数据长度
		memcpy(UARTx->msgTxdHandle.pMsgVal, pArrayVal, length);
		//---要写入数据的个数
		UARTx->msgTxdHandle.msgWIndex = length;
		//---发送CRC处理
		UART_FillMode_WriteCRCTask(UARTx);
		//---判断是否增加换行符
		if ((UARTx->msgTxdHandle.msgAddNewLine == 1))
		{
			UART_FillMode_AddByte(UARTx, 0x0D);
			UART_FillMode_AddByte(UARTx, 0x0A);
		}
		UARTx->msgTxdHandle.msgCount = UARTx->msgTxdHandle.msgWIndex;
		//---设置485为发送模式
		UART_GPIO_485_Init(UARTx, UART_485_TX_ENABLE);
		//---切换发送端口为输出模式
		UART_GPIO_TxInit(UARTx, UART_GPIOTX_SET_OUTPUT);
	#ifdef UART_INIT_GPIO
		//---获取最后1字节的数据
		UARTx->msgWriteFinalData = UARTx->msgTxdHandle.pMsgVal[UARTx->msgTxdHandle.msgCount - 1];
	#endif
		//---校验是不是DMA模式
		if (UARTx->msgTxdHandle.msgDMAMode == 0)
		{
			//---发送数据寄存器空中断使能
			LL_USART_EnableIT_TXE(UARTx->pMsgUART);
		}
		else
		{
			//---设置数据地址
			UART_DMA_Write_SetMemoryAddress(UARTx, (UARTx->msgTxdHandle.pMsgVal));
			//---启动DMA发送
			UART_DMA_Write_RESTART(UARTx);
		}
		//---复位超时计数器
		UART_TimeTick_Init(&(UARTx->msgTxdHandle));
		return OK_0;
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：发送数据
//////输入参数:
//////输出参数:
//////说		明： 获取溢出标志
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_FillMode_WriteSTART(UART_HandleType* UARTx,UINT16_T length)
{
	if (UART_Write_WaitIdle(UARTx) == OK_0)
	{
		//---设置发送状态为忙碌状态
		UARTx->msgTxdHandle.msgState = UART_BUSY;
		//---要写入数据的个数
		UARTx->msgTxdHandle.msgWIndex = length;
		//---发送CRC处理
		UART_FillMode_WriteCRCTask(UARTx);
		//---判断是否增加换行符
		if ((UARTx->msgTxdHandle.msgAddNewLine == 1))
		{
			UART_FillMode_AddByte(UARTx, 0x0D);
			UART_FillMode_AddByte(UARTx, 0x0A);
		}
		UARTx->msgTxdHandle.msgCount = UARTx->msgTxdHandle.msgWIndex;
		//---设置485为发送模式
		UART_GPIO_485_Init(UARTx, UART_485_TX_ENABLE);
		//---切换发送端口为输出模式
		UART_GPIO_TxInit(UARTx, UART_GPIOTX_SET_OUTPUT);
	#ifdef UART_INIT_GPIO
		//---获取最后1字节的数据
		UARTx->msgWriteFinalData = UARTx->msgTxdHandle.pMsgVal[UARTx->msgTxdHandle.msgCount - 1];
	#endif
		//---校验是不是DMA模式
		if (UARTx->msgTxdHandle.msgDMAMode == 0)
		{
			//---发送数据寄存器空中断使能
			LL_USART_EnableIT_TXE(UARTx->pMsgUART);
		}
		else
		{
			//---设置数据地址
			UART_DMA_Write_SetMemoryAddress(UARTx, (UARTx->msgTxdHandle.pMsgVal));
			//---启动DMA发送
			UART_DMA_Write_RESTART(UARTx);
		}
		//---复位超时计数器
		UART_TimeTick_Init(&(UARTx->msgTxdHandle));
		return OK_0;
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明： 获取溢出标志
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_GetOverFlow(UART_HandleDef* UARTDefx)
{
	return UARTDefx->msgOverFlow ;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明： 清除溢出标志
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_ClearOverFlow(UART_HandleDef* UARTDefx)
{
	UARTDefx->msgOverFlow = 0;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：获取状态标识
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_GetState(UART_HandleDef* UARTDefx)
{
	return UARTDefx->msgState;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：清楚状态标识
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_ClearState(UART_HandleDef* UARTDefx)
{
	UARTDefx->msgState = UART_OK;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：复位接收参数
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_Read_Init(UART_HandleType*  UARTx)
{
	//---设置485位接收模式
	UART_GPIO_485_Init(UARTx, UART_485_RX_ENABLE);
	//---清零步序
	UARTx->msgRxdHandle.msgStep = 0;
	//---清除写数组索引
	UARTx->msgRxdHandle.msgWIndex = 0;
	//---清除读数组索引
	UARTx->msgRxdHandle.msgRIndex = 0;
	//---清零接收数据个数
	//UARTx->msgRxdHandle.msgCount = 0;
	//---清零接收完成标志
	UARTx->msgRxdHandle.msgState = UART_BUSY;
	//---清零超时计数
	UARTx->msgRxdHandle.msgRecordTick = 0;
	//---清零超时标志
	UARTx->msgRxdHandle.msgOverFlow = 0;
	//---恢复缓存区的首地址数据
	*(UARTx->msgRxdHandle.pMsgVal)= UARTx->msgRxdHandle.msgMsgValBaseAddr;
	//---校验是不是DMA模式
	if(UARTx->msgRxdHandle.msgDMAMode!=0)
	{
		UART_DMA_Read_RESTART(UARTx);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：复位发送参数
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_Write_Init(UART_HandleType*  UARTx)
{
	//---设置发送状态为发送完成
	UARTx->msgTxdHandle.msgState = UART_OK;
	//---清除写数组索引
	UARTx->msgTxdHandle.msgWIndex = 0;
	//---清除读数组索引
	UARTx->msgTxdHandle.msgRIndex = 0;
	//---清零发送数据个数
	//UARTx->msgTxdHandle.msgCount = 0;
	//---清零超时计数
	UARTx->msgTxdHandle.msgRecordTick = 0;
	//---清零超时标志
	UARTx->msgTxdHandle.msgOverFlow = 0;
	//---操作步序归零
	UARTx->msgTxdHandle.msgStep = 0;
	//---设置485为接收模式
	UART_GPIO_485_Init(UARTx, UART_485_RX_ENABLE);
	//---数据发送完成，切换端口为输入模式
	UART_GPIO_TxInit(UARTx, UART_GPIOTX_SET_INPUT);
	//---记录发送完成的时间
	UARTx->msgTxdHandle.msgRecordTime = ((UARTx->msgTxdHandle.pMsgTimeTick != NULL) ? (UARTx->msgTxdHandle.pMsgTimeTick()) : 0);
	//---恢复缓存区的首地址数据
	*(UARTx->msgTxdHandle.pMsgVal) = UARTx->msgTxdHandle.msgMsgValBaseAddr;
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：校验发送状态是否是空闲状态
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_Write_CheckIdle(UART_HandleType* UARTx)
{
	UINT8_T	_return=OK_0;
	if ((UARTx->msgTxdHandle.msgState == UART_BUSY) || (UARTx->msgTxdHandle.msgState == UART_PRINTF) || (UARTx->msgTxdHandle.msgState == UART_DMA))
	{
		_return=ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：校验设备的ID信息
//////输入参数:
//////输出参数:
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_DeviceID(UART_HandleType*UARTx)
{
	if ((UARTx->msgCmdIndex - UARTx->msgIDIndex) != 0)
	{
		if (UARTx->msgRxdHandle.pMsgVal[UARTx->msgIDIndex] != UARTx->msgID)
		{
			return ERROR_1;
		}
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：挂起发送
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void UART_PrintfSuspend(UART_HandleType* UARTx)
{
#ifdef USE_UART_PRINTF
	//--->>>端口空闲超时检查---开始
	//---获取当前时间节拍
	UINT32_T nowTime = 0;
	UINT32_T oldTime = 0;
	UINT32_T cnt = 0;
	//---获取当前时间节拍
	oldTime = UARTx->msgTxdHandle.pMsgTimeTick();
	//---检查发送状态，等待之前的数据发送完成;必须是空闲状态，总线上没有其他数据放
	while ((UARTx->msgTxdHandle.msgState == UART_BUSY) || (UARTx->msgTxdHandle.msgState == UART_PRINTF) || (UARTx->msgTxdHandle.msgState == UART_DMA))
	{
		//---当前时间
		nowTime = UARTx->msgTxdHandle.pMsgTimeTick();
		//---判断滴答定时是否发生溢出操作
		if (nowTime < oldTime)
		{
			cnt = (0xFFFFFFFF - oldTime + nowTime);
		}
		else
		{
			cnt = nowTime - oldTime;
		}
		//---判断是否超时
		if (cnt > 100)
		{
			//---清零发送状态
			UART_Write_Init(UARTx);
			//---发送发生超时错误
			return ;
		}
		//---喂狗
		WDT_RESET();
	}
	//--->>>端口空闲超时检查---结束
	//---定义485为发送模式
	UART_GPIO_485_Init(UARTx, UART_485_TX_ENABLE);
	//---切换发送端口为输出模式
	UART_GPIO_TxInit(UARTx, UART_GPIOTX_SET_OUTPUT);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：恢复发送
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void UART_PrintfResume(UART_HandleType* UARTx)
{
#ifdef USE_UART_PRINTF
	//---定义485为接收模式
	UART_GPIO_485_Init(UARTx, UART_485_RX_ENABLE);
	//---数据发送完成，切换端口为输入模式
	UART_GPIO_TxInit(UARTx, UART_GPIOTX_SET_INPUT);
	//---记录发送完成的时间
	UARTx->msgTxdHandle.msgRecordTime = ((UARTx->msgTxdHandle.pMsgTimeTick != NULL) ? (UARTx->msgTxdHandle.pMsgTimeTick()) : 0);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：自定义的Printf函数
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void UART_Printf(UART_HandleType*UARTx, char*fmt, ...)
{
#ifdef USE_UART_PRINTF
	//---校验串口是否已经初始化过
	if (UARTx->pMsgUART!=NULL)
	{
		//---挂起操作，等待上一次的发送完成
		UART_PrintfSuspend(UARTx);
		//---计算数据
		UINT16_T length = 0;
		//---定义一个va_list型的变量,这个变量是指向参数的指针
		va_list arg;
		//---用va_start宏初始化变量,这个宏的第二个参数是第一个可变参数的前一个参数,是一个固定的参数
		va_start(arg, fmt);
		//---用于向字符串中打印数据、数据格式用户自定义;返回参数是最终生成字符串的长度
		length = (UINT16_T)vsnprintf(&(pPrintf->pMsgVal[pPrintf->msgWIndex]),(UART_PRINTF_SIZE- pPrintf->msgWIndex), fmt, arg);
		//---判断数据大小，这里利用环形缓存区的思想
		if (length > (UART_PRINTF_SIZE - pPrintf->msgWIndex))
		{
			//---缓存区满，字符归零处理,
			pPrintf->msgWIndex=0;
			//---缓存区之后，并且上次的发送已经完成，重新对数据进行处理
			length = (UINT16_T)vsnprintf(&(pPrintf->pMsgVal[pPrintf->msgWIndex]), (UART_PRINTF_SIZE - pPrintf->msgWIndex), fmt, arg);
		}
		//---读数据偏移
		pPrintf->msgRIndex = pPrintf->msgWIndex;
		//---数据索引偏移
		pPrintf->msgWIndex += length;
		//---至少空闲64字节的缓存区
		if ((UART_PRINTF_SIZE - UART_PRINTF_IDLE_SIZE) < (pPrintf->msgWIndex))
		{
			//---缓存区满，字符归零处理
			pPrintf->msgWIndex = 0;
		}
		//---用va_end宏结束可变参数的获取
		va_end(arg);
	#ifdef UART_INIT_GPIO
		//---获取最后1字节的数据
		UARTx->msgWriteFinalData = pPrintf->pMsgVal[pPrintf->msgWIndex - 1];
	#endif
		//---保存发送的索引位置
		UARTx->msgPRIndex= pPrintf->msgRIndex;
		//---校验是不是DMA模式
		if (UARTx->msgTxdHandle.msgDMAMode!=0)
		{
			//--->>>DMA发送模式
			UARTx->msgTxdHandle.msgCount = length;
			//---设置数据地址
			UART_DMA_Write_SetMemoryAddress(UARTx, (UINT8_T*)(pPrintf->pMsgVal+ UARTx->msgPRIndex));
			//---启动DMA发送
			UART_DMA_Write_RESTART(UARTx);
		}
		else
		{
			//--->>>中断发送模式
			//---要发送数据的个数
			UARTx->msgPCount = length;
			//---使用的发送完成中断，这里需要首先发送一次数据
			UARTx->msgPWIndex = 1;
			//---工作在使用PRINTF模式
			UARTx->msgTxdHandle.msgState = UART_PRINTF;
			//---发送完成,发送数据发送完成中断不使能
			LL_USART_EnableIT_TC(UARTx->pMsgUART);
			//---发送8Bit的数据
			LL_USART_TransmitData8(UARTx->pMsgUART, pPrintf->pMsgVal[UARTx->msgPRIndex]);
		}
		//---复位超时计数器
		UART_TimeTick_Init(&(UARTx->msgTxdHandle));
	}
#endif	
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：打印LOG信息
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void UART_PrintfLog(UART_HandleType* UARTx, char* fmt, va_list args)
{
#ifdef USE_UART_PRINTF
	//---校验串口是否已经初始化过
	if (UARTx->pMsgUART != NULL)
	{
		//---挂起操作，等待上一次的发送完成
		UART_PrintfSuspend(UARTx);
		//---用于向字符串中打印数据、数据格式用户自定义;返回参数是最终生成字符串的长度
		UINT16_T length  = (UINT16_T)vsnprintf(&(pPrintf->pMsgVal[pPrintf->msgWIndex]), (UART_PRINTF_SIZE - pPrintf->msgWIndex), fmt, args);
		//---判断数据大小，这里利用环形缓存区的思想
		if (length > (UART_PRINTF_SIZE - pPrintf->msgWIndex))
		{
			//---缓存区满，字符归零处理,
			pPrintf->msgWIndex = 0;
			//---重置缓存区信息
			//memset((char *)pPrintf->pMsgVal,0, UART_PRINTF_SIZE);
			//---缓存区之后，并且上次的发送已经完成，重新对数据进行处理
			length = (UINT16_T)vsnprintf(&(pPrintf->pMsgVal[pPrintf->msgWIndex]), (UART_PRINTF_SIZE - pPrintf->msgWIndex), fmt, args);
		}
		//---读数据偏移
		pPrintf->msgRIndex = pPrintf->msgWIndex;
		//---数据索引偏移
		pPrintf->msgWIndex += length;
	#ifdef UART_INIT_GPIO
		//---获取最后1字节的数据
		UARTx->msgWriteFinalData = pPrintf->pMsgVal[pPrintf->msgWIndex - 1];
	#endif
		//---至少空闲64字节的缓存区
		if ((UART_PRINTF_SIZE - UART_PRINTF_IDLE_SIZE) < (pPrintf->msgWIndex))
		{
			//---缓存区满，字符归零处理
			pPrintf->msgWIndex = 0;
		}
		//---保存发送的索引位置
		UARTx->msgPRIndex = pPrintf->msgRIndex;
		//---校验是不是DMA模式
		if (UARTx->msgTxdHandle.msgDMAMode != 0)
		{
			//--->>>DMA发送模式
			UARTx->msgTxdHandle.msgCount = length;
			//---设置数据地址
			UART_DMA_Write_SetMemoryAddress(UARTx, (UINT8_T*)(pPrintf->pMsgVal + (UARTx->msgPRIndex)));
			//---启动DMA发送
			UART_DMA_Write_RESTART(UARTx);
		}
		else
		{
			//--->>>中断发送模式
			//---要发送数据的个数
			UARTx->msgPCount = length;
			//---使用的发送完成中断，这里需要首先发送一次数据
			UARTx->msgPWIndex = 1;
			//---工作在使用PRINTF模式
			UARTx->msgTxdHandle.msgState = UART_PRINTF;
			//---发送完成,发送数据发送完成中断不使能
			LL_USART_EnableIT_TC(UARTx->pMsgUART);
			//---发送8Bit的数据
			LL_USART_TransmitData8(UARTx->pMsgUART, pPrintf->pMsgVal[UARTx->msgPRIndex]);
		}
		//---复位超时计数器
		UART_TimeTick_Init(&(UARTx->msgTxdHandle));
	}
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_ITPrintf_TCTask(UART_HandleType* UARTx)
{
#ifdef USE_UART_PRINTF
	if (UARTx->msgPWIndex>=UARTx->msgPCount)
	{
		//---发送完成,发送数据发送完成中断不使能
		LL_USART_DisableIT_TC(UARTx->pMsgUART);
		//---恢复操作
		UART_PrintfResume(UARTx);
		//---标识发送完成
		UARTx->msgTxdHandle.msgState = UART_OK;
	}
	else
	{
		//---发送8Bit的数据
		LL_USART_TransmitData8(UARTx->pMsgUART, pPrintf->pMsgVal[UARTx->msgPRIndex+UARTx->msgPWIndex]);
		UARTx->msgPWIndex++;
	}
#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_ITDMA_TCTask(UART_HandleType* UARTx)
{
#ifdef UART_INIT_GPIO
	//---这里最后多发送一次最后一位的数据，是因为DMA发送最后自己的时候，如果此时切换了端口则会导致最后一组数据丢失
	//---最后1字节多发一次，用于补偿因为端口切换，被吃掉的问题
	if (UARTx->msgTxdHandle.msgStep == 0)
	{
		//---发送8Bit的数据
		LL_USART_TransmitData8(UARTx->pMsgUART, UARTx->msgWriteFinalData);
		UARTx->msgTxdHandle.msgStep = 1;
	}
	else
#endif
	{
		//---发送完成,发送数据发送完成中断不使能
		LL_USART_DisableIT_TC(UARTx->pMsgUART);
		//---清空数据发送缓存区
		UART_Write_Init(UARTx);
	}
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：中断发送完成函数
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_IT_TCTask(UART_HandleType* UARTx)
{
	if (UARTx->msgTxdHandle.msgState == UART_BUSY)
	{
		//---中断方式的发送完成处理函数
		UART_ITWrite_TCTask(UARTx);
	}
	else if (UARTx->msgTxdHandle.msgState == UART_PRINTF)
	{
		//---printf函数使用中断方式发送完成处理函数
		UART_ITPrintf_TCTask(UARTx);
	}
	else if (UARTx->msgTxdHandle.msgState == UART_DMA)
	{
		//---DMA发送的中断发送完成处理函数
		UART_ITDMA_TCTask(UARTx);
	}
	else
	{
		UARTx->msgTxdHandle.msgState = UART_OK;
		LL_USART_DisableIT_TC(UARTx->pMsgUART);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：打印系统时钟
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void UART_PrintfClockFreq(UART_HandleType*UARTx)
{
	LL_RCC_ClocksTypeDef rccClock = { 0 };
	//---获取系统时钟
	LL_RCC_GetSystemClocksFreq(&rccClock);
	//---打印系统时钟
	UART_Printf(UARTx, "SYSCLK=%UHz\r\n", rccClock.SYSCLK_Frequency);
	//---打印系统时钟
	UART_Printf(UARTx, "HCLK=%UHz\r\n", rccClock.HCLK_Frequency);
	//---打印系统时钟
	UART_Printf(UARTx, "PCLK1=%UHz\r\n", rccClock.PCLK1_Frequency);
	//---打印系统时钟
	UART_Printf(UARTx, "PCLK2=%UHz\r\n", rccClock.PCLK2_Frequency);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：UART的总线时钟
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_Clock(USART_TypeDef* UARTx, UINT8_T isEnable)
{
#ifdef USART1
	if (UARTx == USART1)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
			//---不使能SPI的时钟线
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_USART1);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---使能SPI的时钟线
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
			LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_USART1);
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
			LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_USART1);
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
#endif
#ifdef USART2
	if (UARTx == USART2)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
			//---不使能SPI的时钟线
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_USART2);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---使能SPI的时钟线
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
			LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_USART2);
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
			LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_USART2);
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
#endif
#ifdef USART3
	if (UARTx == USART3)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
			//---不使能SPI的时钟线
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_USART3);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---使能SPI的时钟线
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3);
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
			LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_USART3);
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
			LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_USART3);
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
#endif 
#ifdef USART6
	if (UARTx == USART6)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
			//---不使能SPI的时钟线
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_USART6);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---使能SPI的时钟线
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART6);
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
			LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_USART6);
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
			LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_USART6);
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
#endif 
#ifdef UART4
	if (UARTx == UART4)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
			//---不使能SPI的时钟线
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART4);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---使能SPI的时钟线
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART4);
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
			LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_UART4);
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
			LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_UART4);
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
#endif 
#ifdef UART5
	if (UARTx == UART5)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
			//---不使能SPI的时钟线
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART5);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---使能SPI的时钟线
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART5);
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
			LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_UART5);
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
			LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_UART5);
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
#endif 
#ifdef UART7
	if (UARTx == UART7)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
			//---不使能SPI的时钟线
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART7);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---使能SPI的时钟线
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART7);
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
			LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_UART7);
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
			LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_UART7);
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
#endif
#ifdef UART8
	if (UARTx == UART8)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
			//---不使能SPI的时钟线
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART8);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---使能SPI的时钟线
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART8);
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
			LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_UART8);
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
			LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_UART8);
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
#endif 
#ifdef UART9
	if (UARTx == UART9)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
			//---不使能SPI的时钟线
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_UART9);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---使能SPI的时钟线
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_UART9);
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
			LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_UART9);
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
			LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_UART9);
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
#endif 
#ifdef UART10
	if (UARTx == UART10)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
			//---不使能SPI的时钟线
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_UART10);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---使能SPI的时钟线
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_UART10);
		}
		else if (isEnable == PERIPHERAL_CLOCK_FORCE_RESET)
		{
			LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_UART10);
		}
		else if (isEnable == PERIPHERAL_CLOCK_RELEASE_RESET)
		{
			LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_UART10);
		}
		else
		{
			return ERROR_1;
		}
		return OK_0;
	}
#endif 
	return ERROR_2;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：销毁配置
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_DeInit(UART_HandleType*UARTx)
{
	LL_USART_DeInit(UARTx->pMsgUART);
	UART_Clock(UARTx->pMsgUART, PERIPHERAL_CLOCK_DISABLE);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：参数配置
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_ParamInit(UART_HandleType *UARTx, UINT8_T id, UINT8_T idIndex, UINT8_T cmdIndex, UINT8_T d1Index, UINT8_T d2Index)
{
	UARTx->msgID = id;
	UARTx->msgIDIndex = idIndex;
	UARTx->msgCmdIndex = cmdIndex;
	UARTx->msgDataOneIndex = d1Index;
	UARTx->msgDataTwoIndex = d2Index;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：中断处理函数
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////、
void UART_IRQTask(UART_HandleType* UARTx)
{
	//---数据接收中断处理函数---接收寄存器不为空
	if (LL_USART_IsActiveFlag_RXNE(UARTx->pMsgUART) && LL_USART_IsEnabledIT_RXNE(UARTx->pMsgUART))
	{
		//---中断处理函数
		UART_ITRead_Task(UARTx, LL_USART_ReceiveData8(UARTx->pMsgUART));
		//---清楚中断标志位
		LL_USART_ClearFlag_RXNE(UARTx->pMsgUART);
	}
	//---数据发送寄存器空发送中断处理函数
	if (LL_USART_IsActiveFlag_TXE(UARTx->pMsgUART) && LL_USART_IsEnabledIT_TXE(UARTx->pMsgUART))
	{
		//---中断处理函数
		UART_ITWrite_TXETask(UARTx);
	}
	//---数据发送完成中断处理函数
	if (LL_USART_IsActiveFlag_TC(UARTx->pMsgUART) && LL_USART_IsEnabledIT_TC(UARTx->pMsgUART))
	{
		//---中断处理函数
		UART_IT_TCTask(UARTx);
		//---清楚中断标志位
		LL_USART_ClearFlag_TC(UARTx->pMsgUART);
	}
	//---UART5和UART5，不适用CTS检测
#if defined(UART4)||defined(UART5)
	if ((UARTx->pMsgUART!=UART4)&& (UARTx->pMsgUART != UART5))
#endif
	{
		//---CTS状态线变化中断
		if (LL_USART_IsActiveFlag_nCTS(UARTx->pMsgUART) && LL_USART_IsEnabledIT_CTS(UARTx->pMsgUART))
		{
			//---中断处理函数

			//---清楚中断标志位
			LL_USART_ClearFlag_nCTS(UARTx->pMsgUART);
		}
	}
	//---LIN断路检测中断
	if (LL_USART_IsActiveFlag_LBD(UARTx->pMsgUART) && LL_USART_IsEnabledIT_LBD(UARTx->pMsgUART))
	{
		//---中断处理函数

		//---清楚中断标志位
		LL_USART_ClearFlag_LBD(UARTx->pMsgUART);
	}
	//---空闲状态中断，主要是用于DMA接收不定长数据
	if (LL_USART_IsActiveFlag_IDLE(UARTx->pMsgUART) && LL_USART_IsEnabledIT_IDLE(UARTx->pMsgUART))
	{
		//---中断处理函数,DMA数据接收
		UART_DMA_Read_IdleTask(UARTx);
		//---清楚空闲中断标志位
		LL_USART_ClearFlag_IDLE(UARTx->pMsgUART);
		//---清楚DMA中断标识
		LL_DMA_ClearFlag(UARTx->msgRxdHandle.pMsgDMA, UARTx->msgRxdHandle.msgDMAChannelOrStream);
	}
	//---上溢错误中断
	if (LL_USART_IsActiveFlag_ORE(UARTx->pMsgUART) && LL_USART_IsEnabledIT_ERROR(UARTx->pMsgUART))
	{
		//---中断处理函数

		//---清楚中断标志位
		LL_USART_ClearFlag_ORE(UARTx->pMsgUART);
	}
	//---噪声中断
	if (LL_USART_IsActiveFlag_NE(UARTx->pMsgUART) && LL_USART_IsEnabledIT_ERROR(UARTx->pMsgUART))
	{
		//---中断处理函数

		//---清楚中断标志位
		LL_USART_ClearFlag_NE(UARTx->pMsgUART);
	}
	//---帧错误中断
	if (LL_USART_IsActiveFlag_FE(UARTx->pMsgUART) && LL_USART_IsEnabledIT_ERROR(UARTx->pMsgUART))
	{
		//---中断处理函数

		//---清楚中断标志位
		LL_USART_ClearFlag_FE(UARTx->pMsgUART);
	}
	//---奇偶校验中断
	if (LL_USART_IsActiveFlag_PE(UARTx->pMsgUART) && LL_USART_IsEnabledIT_PE(UARTx->pMsgUART))
	{
		//---中断处理函数

		//---清楚中断标志位
		LL_USART_ClearFlag_PE(UARTx->pMsgUART);
	}
}

////////////////////////////////////////////////////////////////////////////////
////DMA模式配置
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：关闭DMA的接受模式
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT16_T UART_DMA_Read_STOP(UART_HandleType* UARTx)
{
#ifdef USE_MCU_STM32F1
	//---使能DMA
	LL_DMA_DisableChannel(UARTx->msgRxHandler.msgDMA, UARTx->msgRxHandler.msgDMAChannelOrStream);
	LL_DMA_ClearFlag_GI1(UARTx->msgRxHandler.msgDMA);
#else
	//---使能DMA传输结束中断
	LL_DMA_DisableIT_TC(UARTx->msgRxdHandle.pMsgDMA, UARTx->msgRxdHandle.msgDMAChannelOrStream);
	//---不使能DMA
	LL_DMA_DisableStream(UARTx->msgRxdHandle.pMsgDMA, UARTx->msgRxdHandle.msgDMAChannelOrStream);
#endif
	//---清楚中断标志
	LL_DMA_ClearFlag(UARTx->msgRxdHandle.pMsgDMA, UARTx->msgRxdHandle.msgDMAChannelOrStream);
	//---使能DMA传输结束中断
	LL_DMA_EnableIT_TC(UARTx->msgRxdHandle.pMsgDMA, UARTx->msgRxdHandle.msgDMAChannelOrStream);
	//---计算接收数据的长度
	UINT16_T length = UARTx->msgRxdHandle.msgMaxSize - LL_DMA_GetDataLength(UARTx->msgRxdHandle.pMsgDMA, UARTx->msgRxdHandle.msgDMAChannelOrStream);
	return length;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：重启DMA的接受模式
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_DMA_Read_RESTART(UART_HandleType* UARTx)
{
	//---设置DMA读取数据的大小
	LL_DMA_SetDataLength(UARTx->msgRxdHandle.pMsgDMA, UARTx->msgRxdHandle.msgDMAChannelOrStream, UARTx->msgRxdHandle.msgMaxSize);
	//---使能DMA
#ifdef USE_MCU_STM32F1
	//---使能DMA
	LL_DMA_EnableChannel(UARTx->msgRxdHandler.msgDMA, UARTx->msgRxdHandler.msgDMAChannelOrStream);
#else
	//---使能DMA
	LL_DMA_EnableStream(UARTx->msgRxdHandle.pMsgDMA, UARTx->msgRxdHandle.msgDMAChannelOrStream);
#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置DMA发送模式下，数据存储的地址
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_DMA_Write_SetMemoryAddress(UART_HandleType* UARTx,UINT8_T *pVal)
{
#ifdef USE_MCU_STM32F1
	
#else
	LL_DMA_SetMemoryAddress(UARTx->msgTxdHandle.pMsgDMA, UARTx->msgTxdHandle.msgDMAChannelOrStream,(UINT32_T)pVal);
#endif
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：停止DMA的发送模式
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT16_T UART_DMA_Write_STOP(UART_HandleType* UARTx)
{
#ifdef USE_MCU_STM32F1
	//---使能DMA
	LL_DMA_DisableChannel(UARTx->msgRxHandler.msgDMA, UARTx->msgRxHandler.msgDMAChannelOrStream);
	LL_DMA_ClearFlag_GI1(UARTx->msgRxHandler.msgDMA);
#else
	//---不使能DMA
	LL_DMA_DisableStream(UARTx->msgTxdHandle.pMsgDMA, UARTx->msgTxdHandle.msgDMAChannelOrStream);
#endif
	LL_DMA_ClearFlag(UARTx->msgTxdHandle.pMsgDMA, UARTx->msgTxdHandle.msgDMAChannelOrStream);
	//---计算接收数据的长度
	UINT16_T length = UARTx->msgTxdHandle.msgMaxSize - LL_DMA_GetDataLength(UARTx->msgTxdHandle.pMsgDMA, UARTx->msgTxdHandle.msgDMAChannelOrStream);
	return length;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：重启DMA的发送模式
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_DMA_Write_RESTART(UART_HandleType* UARTx)
{
	//---设置DMA发送数据的大小
	LL_DMA_SetDataLength(UARTx->msgTxdHandle.pMsgDMA, UARTx->msgTxdHandle.msgDMAChannelOrStream, UARTx->msgTxdHandle.msgCount);
#ifdef USE_MCU_STM32F1
	//---使能DMA
	LL_DMA_EnableChannel(UARTx->msgTxHandler.msgDMA, UARTx->msgTxHandler.msgDMAChannelOrStream);
#else
	//---使能DMA
	LL_DMA_EnableStream(UARTx->msgTxdHandle.pMsgDMA, UARTx->msgTxdHandle.msgDMAChannelOrStream);
#endif
	//---设置为DMA状态
	UARTx->msgTxdHandle.msgState= UART_DMA;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：接收DMA的完成中断处理函数和空闲任务的处理函数
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_DMA_Read_IdleTask(UART_HandleType* UARTx)
{
	UINT8_T _return = OK_0;
	//---停止接收DMA模式,并获取接收数据的长度
	UINT16_T dataLength= UART_DMA_Read_STOP(UARTx);
	//---校验报头是否正确
	if (UARTx->msgRxdHandle.pMsgVal[0] == UARTx->msgRxdID)
	{
		//---数据长度信息
		UINT16_T length = UARTx->msgRxdHandle.pMsgVal[1];
		//---校验数据长度信息
		if (UARTx->msgRxdHandle.msgMaxSize < 0xFF)
		{
			length += 2;
		}
		else
		{
			length = (length << 8) + UARTx->msgRxdHandle.pMsgVal[1];
			length += 3;
		}
		//---校验数据是否合法
		if (length == dataLength)
		{
			UARTx->msgRxdHandle.msgState = UART_OK;
			UARTx->msgRxdHandle.msgCount=dataLength;
		}
		else
		{
			//---数据不符合规则，使能重新接收
			UART_Read_Init(UARTx);
			//---返回错误信息
			_return = ERROR_2;
		}
	}
	else
	{
		UARTx->msgRxdHandle.msgState = UART_OK;
		UARTx->msgRxdHandle.msgCount=dataLength;
		//---有数据进来，但是不是自定义协议的数据
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：接收中断DMA处理程序
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void UART_DMA_Read_IRQTask(UART_HandleType* UARTx)
{
	//---DMA处理模式
	UART_DMA_Read_IdleTask(UARTx);
	//---清楚空闲中断标志位
	LL_USART_ClearFlag_IDLE(UARTx->pMsgUART);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：接收中断DMA处理程序
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void UART_DMA_Write_IRQTask(UART_HandleType* UARTx)
{
#ifdef USE_MCU_STM32F1
	//---不使能DMA
	LL_DMA_DisableChannel(UARTx->msgTxHandler.msgDMA, UARTx->msgTxHandler.msgDMAChannelOrStream;
	LL_DMA_ClearFlag_GI1(UARTx->msgTxHandler.msgDMA);
#else
	//---不使能DMA传输结束中断
	LL_DMA_DisableIT_TC(UARTx->msgTxdHandle.pMsgDMA, UARTx->msgTxdHandle.msgDMAChannelOrStream);
	//---不使能DMA
	LL_DMA_DisableStream(UARTx->msgTxdHandle.pMsgDMA, UARTx->msgTxdHandle.msgDMAChannelOrStream);
#endif
	//---清除标识
	LL_DMA_ClearFlag(UARTx->msgTxdHandle.pMsgDMA, UARTx->msgTxdHandle.msgDMAChannelOrStream);
	//---使能DMA传输结束中断
	LL_DMA_EnableIT_TC(UARTx->msgTxdHandle.pMsgDMA, UARTx->msgTxdHandle.msgDMAChannelOrStream);
	//---清零发送
	//UART_Write_Init(UARTx);
	//---使能发送完成中断，用于切换TXD端口为输入状态
	LL_USART_EnableIT_TC(UARTx->pMsgUART);
}


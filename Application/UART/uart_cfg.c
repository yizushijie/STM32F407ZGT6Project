#include "uart_cfg.h"

//===ȫ�ֱ�������
UART_HandleType  g_Uart1 = { 0 };
pUART_HandleType pUart1 = &g_Uart1;

//=== ȫ�ֱ�������
UART_HandleType  g_Uart3 = { 0 };
pUART_HandleType pUart3 = &g_Uart3;

//===printf����ʹ�õĻ�����
#ifdef USE_UART_PRINTF
	char g_PrintfBuffer[UART_PRINTF_SIZE] = { 0 };
	//---��ʼ��printf���λ�����
	UART_PrintfType g_Printf = 
	{ 
		.msgRIndex=0,
		.msgWIndex =0,
		.pMsgVal= g_PrintfBuffer
	};
	pUART_PrintfType pPrintf =&g_Printf;
#endif

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_StructInit(UART_HandleType*  UARTx)
{
	//---���ڵ����ݴ�������
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

	//---���ջ�����
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
	//---������
	UARTx->msgRxdHandle.pMsgTimeTick = NULL;

	//---���ͻ�����
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
	//---������
	UARTx->msgTxdHandle.pMsgTimeTick = NULL;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ָ�������ã���ʼ��ָ���Ĵ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_ConfigInit(UART_HandleType* UARTx, UART_HandleType* UARTInitx)
{
	//---���ڵ����ݴ�������
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

	//---���ջ�����
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
	//---������
	UARTx->msgRxdHandle.pMsgTimeTick		= UARTInitx->msgRxdHandle.pMsgTimeTick			;

	//---���ͻ�����
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
	//---������
	UARTx->msgTxdHandle.pMsgTimeTick		= UARTInitx->msgTxdHandle.pMsgTimeTick			;
	//---�˿ڳ�ʼ��
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
//////��		����
//////��		�ܣ�UART1�Ĳ�������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART1_ConfigInit(UART_HandleType* UARTx)
{
	//---UART1 GPIO Configuration
	//---PA9  ------> UART1_TX---�˿ڸ���Ϊ7
	//---PA10 ------> UART1_RX---�˿ڸ���Ϊ7
	//---ʹ�ܶ˿�ʱ��
#ifndef  USE_FULL_GPIO
	GPIOTask_Clock(GPIOA, PERIPHERAL_CLOCK_ENABLE);
#endif
	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	//---ģʽ����
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	//---�����ٶ�
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	//---���ù��ܵ��������
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	//---��������ʹ��
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
	//---�˿ں�
	GPIO_InitStruct.Pin = LL_GPIO_PIN_9 | LL_GPIO_PIN_10;
	//---���ù���ΪUART1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
#endif
	//---������Ϣ�ṹ���е���Ϣ
	UARTx->msgTxPort.msgPort = GPIOA;
	UARTx->msgTxPort.msgBit = LL_GPIO_PIN_9;
	UARTx->pMsgUART = USART1;
	//---�������
	UARTx->msgIndex = 1 + 1;
	//---ע�����ڵĳ�ʼ��
	LL_USART_DeInit(UARTx->pMsgUART);
	//---ʹ��UART1��ʱ���ź�
	UART_Clock(UARTx->pMsgUART, PERIPHERAL_CLOCK_ENABLE);
	//---UART�Ľӿڽṹ��
	LL_USART_InitTypeDef USART_InitStruct = { 0 };
	//---������
	USART_InitStruct.BaudRate = 115200;
	//---����λ
	USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
	//---ֹͣλ
	USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
	//---У��λ
	USART_InitStruct.Parity = LL_USART_PARITY_NONE;
	//---����Ϊ�շ�ģʽ
	USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
	//---Ӳ��������---Ĭ��Ϊ��
	USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
	//---����������
#ifdef UART_CR1_OVER8
	//---����������---Ĭ������Ϊ16
	UART_InitStruct.OverSampling = LL_UART_OVERSAMPLING_16;
#endif
	//---��ʼ������
	LL_USART_Init(UARTx->pMsgUART, &USART_InitStruct);
	//---�����첽ģʽ����
	LL_USART_ConfigAsyncMode(UARTx->pMsgUART);
	//---У���Ƿ������Ҫ��ʱ����
	(UARTx->msgRxdHandle.pMsgTimeTick != NULL)?(UARTx->msgRxdHandle.msgMaxTime = 100):(UARTx->msgRxdHandle.msgMaxTime = 0);
	//---У���Ƿ�����Ҫ��ʱ����
	(UARTx->msgTxdHandle.pMsgTimeTick != NULL)?(UARTx->msgTxdHandle.msgMaxTime = 100):(UARTx->msgTxdHandle.msgMaxTime = 0);
	//---����CRC�ĵȼ�
	UARTx->msgTxdHandle.msgCRCFlag = UART_CRC_NONE;
	//---���ñ�ͷ�ͱ�β
	UARTx->msgRxdID = 0x55;
	UARTx->msgTxdID = 0x5A;
	//---�����ϻ�����շ�DMA
	UARTx->msgRxdHandle.msgDMAMode = UART1_RX_DMA_MODE;
	UARTx->msgTxdHandle.msgDMAMode = UART1_TX_DMA_MODE;
	//---����͵�ַ����
	UART_ParamInit(UARTx, UART1_DEVICE_ID, UART1_ID_INDEX, UART1_CMD_INDEX, UART1_DATA1_INDEX, UART1_DATA2_INDEX);
	//---����485Ϊ����ģʽ--�������ģʽ������Ϊ����ģʽ
	UART_GPIO_485_Init(UARTx, UART_485_RX_ENABLE);
	//---����TX�˿�Ϊ����ģʽ
	UART_GPIO_TxInit(UARTx, UART_GPIOTX_SET_INPUT);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����DMA��ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART1_DMA_Read_Init(UART_HandleType* UARTx)
{
	//>>>---RX��DMA����
	//---��DMAȫ���Ĵ�����������Ϊȱʡֵ
#ifdef USE_MCU_STM32F1
	//---F1��Ӧ�ǵ�DMA1��ͨ��1��ӦADC1
	LL_DMA_DeInit(DMA1, LL_DMA_CHANNEL_1);
	//---DMAʱ����������
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
#else
	LL_DMA_DeInit(DMA2, LL_DMA_STREAM_2);
	//---DMAʱ����������
	//LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2);
	DMATask_Clock(DMA2, PERIPHERAL_CLOCK_ENABLE);
	UARTx->msgRxdHandle.pMsgDMA = DMA2;
	UARTx->msgRxdHandle.msgDMAChannelOrStream = LL_DMA_STREAM_2;
#endif
	//---DMA��ʼ���ṹ��
	LL_DMA_InitTypeDef DMA_InitTypeDef = { 0 };
#ifndef USE_MCU_STM32F1
	//---DMAͨ��
	DMA_InitTypeDef.Channel = LL_DMA_CHANNEL_4;
#endif
	//---���ݴ�С
	DMA_InitTypeDef.NbData = UARTx->msgRxdHandle.msgMaxSize;
	//---��������赽�洢��
	DMA_InitTypeDef.Direction = LL_DMA_DIRECTION_PERIPH_TO_MEMORY;
#ifndef USE_MCU_STM32F1
	//---����FIFO��ֱ��ģʽ
	DMA_InitTypeDef.FIFOMode = LL_DMA_FIFOMODE_DISABLE;
	//---�������ֽ�
	DMA_InitTypeDef.FIFOThreshold = LL_DMA_FIFOTHRESHOLD_1_2;
#endif
	//---�洢����ַ
	DMA_InitTypeDef.MemoryOrM2MDstAddress = (UINT32_T)(UARTx->msgRxdHandle.pMsgVal);
	//---�������ֽ�
	DMA_InitTypeDef.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;
	//---�洢����ַ����
	DMA_InitTypeDef.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT;
	//---DMA����ģʽ
	DMA_InitTypeDef.Mode = LL_DMA_MODE_NORMAL; //LL_DMA_MODE_CIRCULAR;
	//---DMA�����ַ
	DMA_InitTypeDef.PeriphOrM2MSrcAddress = (UINT32_T) & (UARTx->pMsgUART->DR);
#ifndef USE_MCU_STM32F1
	//---��FIFO
	DMA_InitTypeDef.PeriphBurst = LL_DMA_PBURST_SINGLE;
#endif
	//---�������ֽ�
	DMA_InitTypeDef.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
	//---�������ַ����
	DMA_InitTypeDef.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
	//---����ͨ�����ȼ�Ϊ��
	DMA_InitTypeDef.Priority = LL_DMA_PRIORITY_HIGH;
	//---DMA��ʼ��
#ifdef USE_MCU_STM32F1
	//---��ʼ��DMA
	LL_DMA_Init(UARTx->msgRxHandler.msgDMA, UARTx->msgRxHandler.msgDMAChannelOrStream, &DMA_InitTypeDef);
	//---ʹ��DMA
	LL_DMA_EnableChannel(UARTx->msgRxHandler.msgDMA, UARTx->msgRxHandler.msgDMAChannelOrStream);
#else
	//---��ʼ��DMA
	LL_DMA_Init(UARTx->msgRxdHandle.pMsgDMA, UARTx->msgRxdHandle.msgDMAChannelOrStream, &DMA_InitTypeDef);
	//---ʹ��DMA
	LL_DMA_EnableStream(UARTx->msgRxdHandle.pMsgDMA, UARTx->msgRxdHandle.msgDMAChannelOrStream);
	//---���ܴ��ڽ���DMA
	LL_USART_EnableDMAReq_RX(UARTx->pMsgUART);
#endif
	//---�ж�����
#ifdef USE_MCU_STM32F1
	//---DMA�ж�����
	NVIC_SetPriority(DMA1_Channel1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 1, 0));
	//---ʹ���ж�
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);
#else
	//---DMA�ж�����
	NVIC_SetPriority(DMA2_Stream2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 2, 0));
	//---ʹ���ж�
	NVIC_EnableIRQ(DMA2_Stream2_IRQn);
#endif
	//---ʹ��DMA��������ж�
	LL_DMA_EnableIT_TC(UARTx->msgRxdHandle.pMsgDMA, UARTx->msgRxdHandle.msgDMAChannelOrStream);
	//<<<---RX��DMA���ý���
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����DMA�ĳ�ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART1_DMA_Write_Init(UART_HandleType* UARTx)
{
	//>>>---TX��DMA����
	//---��DMAȫ���Ĵ�����������Ϊȱʡֵ
#ifdef USE_MCU_STM32F1
	//---F1��Ӧ�ǵ�DMA1��ͨ��1��ӦADC1
	LL_DMA_DeInit(DMA1, LL_DMA_CHANNEL_1);
	//---DMAʱ����������
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
#else
	LL_DMA_DeInit(DMA2, LL_DMA_STREAM_7);
	//---DMAʱ����������
	//LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2);
	DMATask_Clock(DMA2, PERIPHERAL_CLOCK_ENABLE);
	UARTx->msgTxdHandle.pMsgDMA = DMA2;
	UARTx->msgTxdHandle.msgDMAChannelOrStream = LL_DMA_STREAM_7;
#endif
	//---DMA��ʼ���ṹ��
	LL_DMA_InitTypeDef DMA_InitTypeDef = { 0 };
#ifndef USE_MCU_STM32F1
	//---DMAͨ��
	DMA_InitTypeDef.Channel = LL_DMA_CHANNEL_4;
#endif
	//---���ݴ�С,������״η��ͣ�����Ĳ���ֻ��д0���������׷������ݲ�����������ֻ�����˽Ӹ��ֽھ�ֹͣ����
	DMA_InitTypeDef.NbData = 0;//UARTx->msgTxdHandler.msgSize;
	//---����Ӵ洢��������
	DMA_InitTypeDef.Direction = LL_DMA_DIRECTION_MEMORY_TO_PERIPH;
#ifndef USE_MCU_STM32F1
	//---����FIFO��ֱ��ģʽ
	DMA_InitTypeDef.FIFOMode = LL_DMA_FIFOMODE_DISABLE;
	//---�������ֽ�
	DMA_InitTypeDef.FIFOThreshold = LL_DMA_FIFOTHRESHOLD_1_2;
#endif
	//---�洢����ַ
	DMA_InitTypeDef.MemoryOrM2MDstAddress = (UINT32_T)(UARTx->msgTxdHandle.pMsgVal);
	//---�������ֽ�
	DMA_InitTypeDef.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;
	//---�洢����ַ����
	DMA_InitTypeDef.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT;
	//---DMA����ģʽ
	DMA_InitTypeDef.Mode = LL_DMA_MODE_NORMAL; //LL_DMA_MODE_CIRCULAR;
	//---DMA�����ַ
	DMA_InitTypeDef.PeriphOrM2MSrcAddress = (UINT32_T) & (UARTx->pMsgUART->DR);
#ifndef USE_MCU_STM32F1
	//---��FIFO
	DMA_InitTypeDef.PeriphBurst = LL_DMA_PBURST_SINGLE;
#endif
	//---�������ֽ�
	DMA_InitTypeDef.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
	//---�������ַ����
	DMA_InitTypeDef.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
	//---����ͨ�����ȼ�Ϊ��
	DMA_InitTypeDef.Priority = LL_DMA_PRIORITY_HIGH;
	//---DMA��ʼ��
#ifdef USE_MCU_STM32F1
	//---��ʼ��DMA
	LL_DMA_Init(UARTx->msgTxHandler.msgDMA, UARTx->msgTxHandler.msgDMAChannelOrStream, &DMA_InitTypeDef);
	//---ʹ��DMA
	LL_DMA_EnableChannel(UARTx->msgTxHandler.msgDMA, UARTx->msgTxHandler.msgDMAChannelOrStream);
#else
	//---��ʼ��DMA
	LL_DMA_Init(UARTx->msgTxdHandle.pMsgDMA, UARTx->msgTxdHandle.msgDMAChannelOrStream, &DMA_InitTypeDef);
	//---ʹ��DMA,ע�ⷢ��״̬�²���ʹ��DMA��ֻ����Ҫ��ʱ����ܴ�
	//LL_DMA_EnableStream(UARTx->msgTxHandler.msgDMA, UARTx->msgTxHandler.msgDMAChannelOrStream);
	//---ʹ�ܴ��ڷ���DMA
	LL_USART_EnableDMAReq_TX(UARTx->pMsgUART);
#endif
	//---�ж�����
#ifdef USE_MCU_STM32F1
	//---DMA�ж�����
	NVIC_SetPriority(DMA1_Channel1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 1, 0));
	//---ʹ���ж�
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);
#else
	//---DMA�ж�����
	NVIC_SetPriority(DMA2_Stream7_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 2, 0));
	//---ʹ���ж�
	NVIC_EnableIRQ(DMA2_Stream7_IRQn);
#endif
	//---ʹ��DMA��������ж�
	LL_DMA_EnableIT_TC(UARTx->msgTxdHandle.pMsgDMA, UARTx->msgTxdHandle.msgDMAChannelOrStream);
	//<<<---TX��DMA���ý���
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART1_Init(UART_HandleType* UARTx)
{
	UART1_ConfigInit(UARTx);
	//---У������ǲ���DMA����
	if (UARTx->msgRxdHandle.msgDMAMode == 0)
	{
		//---ʹ�ܽ����ж�
		LL_USART_EnableIT_RXNE(USART1);
	}
	else
	{
		//---ʹ�ܽ��տ����ж�
		LL_USART_EnableIT_IDLE(USART1);
		//---��ʼ��DMA����
		UART1_DMA_Read_Init(UARTx);
	}
	//---У�鷢���ǲ���DMA���䷽ʽ
	if (UARTx->msgTxdHandle.msgDMAMode != 0)
	{
		//---��ʼ��DMA����
		UART1_DMA_Write_Init(UARTx);
	}
	//---UART1_IRQ�ж�����---�жϵȼ�����
	NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 2, 0));
	//---ʹ���ж�
	NVIC_EnableIRQ(USART1_IRQn);
	//---ʹ�ܴ���
	LL_USART_Enable(UARTx->pMsgUART);
	//---��ӡ��ʼ����Ϣ
	//UART_Printf(UARTx, "=>>����1�ĳ�ʼ��<<=\r\n");
	UART_Printf(UARTx, "===>>����1��ʼ�����<<===\r\n");
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART2_ConfigInit(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART2_DMA_Read_Init(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART2_DMA_Write_Init(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART2_Init(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART3_ConfigInit(UART_HandleType* UARTx)
{
	//---UART3 GPIO Configuration
	//---PB10  ------> UART3_TX---�˿ڸ���Ϊ7
	//---PB11  ------> UART3_RX---�˿ڸ���Ϊ7
	//---ʹ�ܶ˿�ʱ��
#ifndef  USE_FULL_GPIO
	GPIOTask_Clock(GPIOB, PERIPHERAL_CLOCK_ENABLE);
#endif
	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	//---ģʽ����
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	//---�����ٶ�
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	//---���ù��ܵ��������
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	//---��������ʹ��
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
	//---�˿ں�
	GPIO_InitStruct.Pin = LL_GPIO_PIN_10 | LL_GPIO_PIN_11;
	//---���ù���ΪUART3
	GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
	LL_GPIO_Init(GPIOB, &GPIO_InitStruct);
#endif
	//---������Ϣ�ṹ���е���Ϣ
	UARTx->msgTxPort.msgPort = GPIOB;
	UARTx->msgTxPort.msgBit = LL_GPIO_PIN_10;
	UARTx->pMsgUART = USART3;
	//---�������
	UARTx->msgIndex = 3 + 1;
	//---ע�����ڵĳ�ʼ��
	LL_USART_DeInit(UARTx->pMsgUART);
	//---ʹ��UART1��ʱ���ź�
	UART_Clock(UARTx->pMsgUART, PERIPHERAL_CLOCK_ENABLE);
	//---UART�Ľӿڽṹ��
	LL_USART_InitTypeDef USART_InitStruct = { 0 };
	//---������
	USART_InitStruct.BaudRate = 115200;
	//---����λ
	USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
	//---ֹͣλ
	USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
	//---У��λ
	USART_InitStruct.Parity = LL_USART_PARITY_NONE;
	//---����Ϊ�շ�ģʽ
	USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
	//---Ӳ��������---Ĭ��Ϊ��
	USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
	//---����������
#ifdef UART_CR1_OVER8
	//---����������---Ĭ������Ϊ16
	UART_InitStruct.OverSampling = LL_UART_OVERSAMPLING_16;
#endif
	//---��ʼ������
	LL_USART_Init(UARTx->pMsgUART, &USART_InitStruct);
	//---�����첽ģʽ����
	LL_USART_ConfigAsyncMode(UARTx->pMsgUART);
	//---У���Ƿ������Ҫ��ʱ����
	(UARTx->msgRxdHandle.pMsgTimeTick != NULL) ? (UARTx->msgRxdHandle.msgMaxTime = 10) : (UARTx->msgRxdHandle.msgMaxTime = 0);
	//---У���Ƿ�����Ҫ��ʱ����
	(UARTx->msgTxdHandle.pMsgTimeTick != NULL) ? (UARTx->msgTxdHandle.msgMaxTime = 100) : (UARTx->msgTxdHandle.msgMaxTime = 0);
	//---����CRC�ĵȼ�
	UARTx->msgTxdHandle.msgCRCFlag = UART_CRC_NONE;
	//---���ñ�ͷ�ͱ�β
	UARTx->msgRxdID = 0x55;
	UARTx->msgTxdID = 0x5A;
	//---�����ϻ�����շ�DMA
	//---�����ϻ�����շ�DMA
	UARTx->msgRxdHandle.msgDMAMode = UART3_RX_DMA_MODE;
	UARTx->msgTxdHandle.msgDMAMode = UART3_TX_DMA_MODE;
	//---����͵�ַ����
	//UART_ParamInit(UARTx, UART1_DEVICE_ID, UART1_ID_INDEX, UART1_CMD_INDEX, UART1_DATA1_INDEX, UART1_DATA2_INDEX);
	//---����485Ϊ����ģʽ--�������ģʽ������Ϊ����ģʽ
	UART_GPIO_485_Init(UARTx, UART_485_RX_ENABLE);
	//---����TX�˿�Ϊ����ģʽ
	UART_GPIO_TxInit(UARTx, UART_GPIOTX_SET_INPUT);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART3_DMA_Read_Init(UART_HandleType* UARTx)
{
	//>>>---RX��DMA����
	//---��DMAȫ���Ĵ�����������Ϊȱʡֵ
#ifdef USE_MCU_STM32F1
	//---F1��Ӧ�ǵ�DMA1��ͨ��1��ӦADC1
	LL_DMA_DeInit(DMA1, LL_DMA_CHANNEL_1);
	//---DMAʱ����������
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
#else
	LL_DMA_DeInit(DMA1, LL_DMA_STREAM_1);
	//---DMAʱ����������
	//LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
	DMATask_Clock(DMA1, PERIPHERAL_CLOCK_ENABLE);
	UARTx->msgRxdHandle.pMsgDMA = DMA1;
	UARTx->msgRxdHandle.msgDMAChannelOrStream = LL_DMA_STREAM_1;
#endif
	//---DMA��ʼ���ṹ��
	LL_DMA_InitTypeDef DMA_InitTypeDef = { 0 };
#ifndef USE_MCU_STM32F1
	//---DMAͨ��
	DMA_InitTypeDef.Channel = LL_DMA_CHANNEL_4;
#endif
	//---���ݴ�С
	DMA_InitTypeDef.NbData = UARTx->msgRxdHandle.msgMaxSize;
	//---��������赽�洢��
	DMA_InitTypeDef.Direction = LL_DMA_DIRECTION_PERIPH_TO_MEMORY;
#ifndef USE_MCU_STM32F1
	//---����FIFO��ֱ��ģʽ
	DMA_InitTypeDef.FIFOMode = LL_DMA_FIFOMODE_DISABLE;
	//---�������ֽ�
	DMA_InitTypeDef.FIFOThreshold = LL_DMA_FIFOTHRESHOLD_1_2;
#endif
	//---�洢����ַ
	DMA_InitTypeDef.MemoryOrM2MDstAddress = (UINT32_T)(UARTx->msgRxdHandle.pMsgVal);
	//---�������ֽ�
	DMA_InitTypeDef.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;
	//---�洢����ַ����
	DMA_InitTypeDef.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT;
	//---DMA����ģʽ
	DMA_InitTypeDef.Mode = LL_DMA_MODE_NORMAL; //LL_DMA_MODE_CIRCULAR;
	//---DMA�����ַ
	DMA_InitTypeDef.PeriphOrM2MSrcAddress = (UINT32_T) & (UARTx->pMsgUART->DR);
#ifndef USE_MCU_STM32F1
	//---��FIFO
	DMA_InitTypeDef.PeriphBurst = LL_DMA_PBURST_SINGLE;
#endif
	//---�������ֽ�
	DMA_InitTypeDef.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
	//---�������ַ����
	DMA_InitTypeDef.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
	//---����ͨ�����ȼ�Ϊ��
	DMA_InitTypeDef.Priority = LL_DMA_PRIORITY_HIGH;
	//---DMA��ʼ��
#ifdef USE_MCU_STM32F1
	//---��ʼ��DMA
	LL_DMA_Init(UARTx->msgRxHandler.msgDMA, UARTx->msgRxHandler.msgDMAChannelOrStream, &DMA_InitTypeDef);
	//---ʹ��DMA
	LL_DMA_EnableChannel(UARTx->msgRxHandler.msgDMA, UARTx->msgRxHandler.msgDMAChannelOrStream);
#else
	//---��ʼ��DMA
	LL_DMA_Init(UARTx->msgRxdHandle.pMsgDMA, UARTx->msgRxdHandle.msgDMAChannelOrStream, &DMA_InitTypeDef);
	//---ʹ��DMA
	LL_DMA_EnableStream(UARTx->msgRxdHandle.pMsgDMA, UARTx->msgRxdHandle.msgDMAChannelOrStream);
	//---���ܴ��ڽ���DMA
	LL_USART_EnableDMAReq_RX(UARTx->pMsgUART);
#endif
	//---�ж�����
#ifdef USE_MCU_STM32F1
	//---DMA�ж�����
	NVIC_SetPriority(DMA1_Channel1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 1, 0));
	//---ʹ���ж�
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);
#else
	//---DMA�ж�����
	NVIC_SetPriority(DMA1_Stream1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 2, 0));
	//---ʹ���ж�
	NVIC_EnableIRQ(DMA1_Stream1_IRQn);
#endif
	//---ʹ��DMA��������ж�
	LL_DMA_EnableIT_TC(UARTx->msgRxdHandle.pMsgDMA, UARTx->msgRxdHandle.msgDMAChannelOrStream);
	//<<<---RX��DMA���ý���
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART3_DMA_Write_Init(UART_HandleType* UARTx)
{
	//>>>---TX��DMA����
	//---��DMAȫ���Ĵ�����������Ϊȱʡֵ
#ifdef USE_MCU_STM32F1
	//---F1��Ӧ�ǵ�DMA1��ͨ��1��ӦADC1
	LL_DMA_DeInit(DMA1, LL_DMA_CHANNEL_1);
	//---DMAʱ����������
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
#else
	LL_DMA_DeInit(DMA1, LL_DMA_STREAM_3);
	//---DMAʱ����������
	//LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
	DMATask_Clock(DMA1, PERIPHERAL_CLOCK_ENABLE);
	UARTx->msgTxdHandle.pMsgDMA = DMA1;
	UARTx->msgTxdHandle.msgDMAChannelOrStream = LL_DMA_STREAM_3;
#endif
	//---DMA��ʼ���ṹ��
	LL_DMA_InitTypeDef DMA_InitTypeDef = { 0 };
#ifndef USE_MCU_STM32F1
	//---DMAͨ��
	DMA_InitTypeDef.Channel = LL_DMA_CHANNEL_4;
#endif
	//---���ݴ�С,������״η��ͣ�����Ĳ���ֻ��д0���������׷������ݲ�����������ֻ�����˽Ӹ��ֽھ�ֹͣ����
	DMA_InitTypeDef.NbData = 0;//UARTx->msgTxdHandler.msgSize;
	//---����Ӵ洢��������
	DMA_InitTypeDef.Direction = LL_DMA_DIRECTION_MEMORY_TO_PERIPH;
#ifndef USE_MCU_STM32F1
	//---����FIFO��ֱ��ģʽ
	DMA_InitTypeDef.FIFOMode = LL_DMA_FIFOMODE_DISABLE;
	//---�������ֽ�
	DMA_InitTypeDef.FIFOThreshold = LL_DMA_FIFOTHRESHOLD_1_2;
#endif
	//---�洢����ַ
	DMA_InitTypeDef.MemoryOrM2MDstAddress = (UINT32_T)(UARTx->msgTxdHandle.pMsgVal);
	//---�������ֽ�
	DMA_InitTypeDef.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_BYTE;
	//---�洢����ַ����
	DMA_InitTypeDef.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT;
	//---DMA����ģʽ
	DMA_InitTypeDef.Mode = LL_DMA_MODE_NORMAL; //LL_DMA_MODE_CIRCULAR;
	//---DMA�����ַ
	DMA_InitTypeDef.PeriphOrM2MSrcAddress = (UINT32_T) & (UARTx->pMsgUART->DR);
#ifndef USE_MCU_STM32F1
	//---��FIFO
	DMA_InitTypeDef.PeriphBurst = LL_DMA_PBURST_SINGLE;
#endif
	//---�������ֽ�
	DMA_InitTypeDef.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_BYTE;
	//---�������ַ����
	DMA_InitTypeDef.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;
	//---����ͨ�����ȼ�Ϊ��
	DMA_InitTypeDef.Priority = LL_DMA_PRIORITY_HIGH;
	//---DMA��ʼ��
#ifdef USE_MCU_STM32F1
	//---��ʼ��DMA
	LL_DMA_Init(UARTx->msgTxHandler.msgDMA, UARTx->msgTxHandler.msgDMAChannelOrStream, &DMA_InitTypeDef);
	//---ʹ��DMA
	LL_DMA_EnableChannel(UARTx->msgTxHandler.msgDMA, UARTx->msgTxHandler.msgDMAChannelOrStream);
#else
	//---��ʼ��DMA
	LL_DMA_Init(UARTx->msgTxdHandle.pMsgDMA, UARTx->msgTxdHandle.msgDMAChannelOrStream, &DMA_InitTypeDef);
	//---ʹ��DMA,ע�ⷢ��״̬�²���ʹ��DMA��ֻ����Ҫ��ʱ����ܴ�
	//LL_DMA_EnableStream(UARTx->msgTxHandler.msgDMA, UARTx->msgTxHandler.msgDMAChannelOrStream);
	//---ʹ�ܴ��ڷ���DMA
	LL_USART_EnableDMAReq_TX(UARTx->pMsgUART);
#endif
	//---�ж�����
#ifdef USE_MCU_STM32F1
	//---DMA�ж�����
	NVIC_SetPriority(DMA1_Channel1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 1, 0));
	//---ʹ���ж�
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);
#else
	//---DMA�ж�����
	NVIC_SetPriority(DMA1_Stream3_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 2, 0));
	//---ʹ���ж�
	NVIC_EnableIRQ(DMA1_Stream3_IRQn);
#endif
	//---ʹ��DMA��������ж�
	LL_DMA_EnableIT_TC(UARTx->msgTxdHandle.pMsgDMA, UARTx->msgTxdHandle.msgDMAChannelOrStream);
	//<<<---TX��DMA���ý���
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART3_Init(UART_HandleType* UARTx)
{
	UART3_ConfigInit(UARTx);
	//---У������ǲ���DMA����
	if (UARTx->msgRxdHandle.msgDMAMode == 0)
	{
		//---ʹ�ܽ����ж�
		LL_USART_EnableIT_RXNE(UARTx->pMsgUART);
	}
	else
	{
		//---ʹ�ܽ��տ����ж�
		LL_USART_EnableIT_IDLE(UARTx->pMsgUART);
		//---DMAδ��ʼ�������ʼ������������
		if (UARTx->msgRxdHandle.pMsgDMA==0)
		{
			//---��ʼ��DMA����
			UART3_DMA_Read_Init(UARTx);
		}
	}
	//---У�鷢���ǲ���DMA���䷽ʽ
	if (UARTx->msgTxdHandle.msgDMAMode != 0)
	{
		//---DMAδ��ʼ�������ʼ������������
		if (UARTx->msgTxdHandle.pMsgDMA==0)
		{
			UART3_DMA_Write_Init(UARTx);
		}
	}
	//---UART1_IRQ�ж�����---�жϵȼ�����
	NVIC_SetPriority(USART3_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 2, 0));
	//---ʹ���ж�
	NVIC_EnableIRQ(USART3_IRQn);
	//---ʹ�ܴ���
	LL_USART_Enable(UARTx->pMsgUART);
	//---��ӡ��ʼ����Ϣ
	//UART_Printf(UARTx, "===>>����3��ʼ�����<<===\r\n");
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART4_ConfigInit(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART4_DMA_Read_Init(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART4_DMA_Write_Init(UART_HandleType* UARTx)
{
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART4_Init(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART5_ConfigInit(UART_HandleType* UARTx)
{
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART5_DMA_Read_Init(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART5_DMA_Write_Init(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART5_Init(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART6_ConfigInit(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART6_DMA_Read_Init(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART6_DMA_Write_Init(UART_HandleType* UARTx)
{
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART6_Init(UART_HandleType* UARTx)
{
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART7_ConfigInit(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART7_DMA_Read_Init(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART7_DMA_Write_Init(UART_HandleType* UARTx)
{
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART7_Init(UART_HandleType* UARTx)
{
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART8_ConfigInit(UART_HandleType* UARTx)
{
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART8_DMA_Read_Init(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART8_DMA_Write_Init(UART_HandleType* UARTx)
{
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART8_Init(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART9_ConfigInit(UART_HandleType* UARTx)
{
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART9_DMA_Read_Init(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART9_DMA_Write_Init(UART_HandleType* UARTx)
{
	return OK_0;
}



///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART9_Init(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART10_ConfigInit(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART10_DMA_Read_Init(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART10_DMA_Write_Init(UART_HandleType* UARTx)
{
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART10_Init(UART_HandleType* UARTx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_Init(UART_HandleType*  UARTx, UINT16_T rxSize, UINT8_T* pRxVal, UINT8_T rxCRCFlag, UINT16_T txSize, UINT8_T* pTxVal, UINT8_T txCRCFlag, UINT32_T(*pTimerTick)(void))
{
	UART_StructInit(UARTx);
	UARTx->msgRxdHandle.msgCRCFlag = rxCRCFlag;
	UARTx->msgRxdHandle.msgMaxSize = rxSize;
	UARTx->msgRxdHandle.pMsgVal = pRxVal;
	//---���滺�������׵�ַ
	UARTx->msgRxdHandle.msgMsgValBaseAddr= (VLTUINT32_T)pRxVal;
	UARTx->msgTxdHandle.msgCRCFlag = txCRCFlag;
	UARTx->msgTxdHandle.msgMaxSize = txSize;
	UARTx->msgTxdHandle.pMsgVal = pTxVal;
	//---���滺�������׵�ַ
	UARTx->msgTxdHandle.msgMsgValBaseAddr =(VLTUINT32_T)pTxVal;
	//---ע���������
	UARTx->msgTxdHandle.pMsgTimeTick = pTimerTick;
	UARTx->msgRxdHandle.pMsgTimeTick = pTimerTick;
	//---�˿ڳ�ʼ��
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
//////��		����
//////��		�ܣ����ڵķ��Ͷ˿ڵĳ�ʼ��
//////�������:
//////�������:
//////˵		����
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
//////��		����
//////��		�ܣ�485������ƶ˿ڵĳ�ʼ��
//////�������:
//////�������:
//////˵		����
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
//////��		����
//////��		�ܣ�����CRCУ��ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_SetCRC(UART_HandleDef* UARTDefx, UINT8_T crcFlag)
{
	UARTDefx->msgCRCFlag = crcFlag;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡCRCУ��ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_GetCRC(UART_HandleDef* UARTDefx)
{
	return UARTDefx->msgCRCFlag;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_TimeTick_Init(UART_HandleDef* UARTDefx)
{
	//---ʱ��ڵ�
	UARTDefx->msgRecordTick = ((UARTDefx->pMsgTimeTick != NULL)?(UARTDefx->pMsgTimeTick()):0);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ע����ʱ������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_TimeTick_DeInit(UART_HandleDef* UARTDefx)
{
	//---���������־λ
	UARTDefx->msgOverFlow = 0;
	//---���㵱ǰʱ��
	UARTDefx->msgRecordTick = 0;
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ʱ������Ƿ�����ʱ
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_TimeTick_OverFlow(UART_HandleDef* UARTDefx)
{
	UINT32_T temp = 0;
	//---��ȡ��ǰʱ��
	temp = ((UARTDefx->pMsgTimeTick != NULL) ? (UARTDefx->pMsgTimeTick()+2) : 0);
	//---�ж��Ƿ�����ʱ����
	if (temp > UARTDefx->msgRecordTick)
	{
		//---��ʱ��δ�����������
		if ((temp - UARTDefx->msgRecordTick) > UARTDefx->msgMaxTime)
		{
			UARTDefx->msgOverFlow = 1;
			return ERROR_1;
		}
	}
	else 
	{
		//---��ʱ�������������
		if ((0xFFFFFFFF - UARTDefx->msgRecordTick + temp) > UARTDefx->msgMaxTime)
		{
			UARTDefx->msgOverFlow = 1;
			return ERROR_1;
		}
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_TimeTask_OverFlow(UART_HandleType*UARTx, UINT8_T isRx)
{
	UINT8_T _return = OK_0;
	//---�ж��ǽ��ջ��Ƿ��Ͳ�У���ǲ���DMA����ģʽ
	if ((isRx != 0) && (UARTx->msgRxdHandle.msgDMAMode == 0))
	{
		if ((UARTx->msgRxdHandle.msgRecordTick != 0) && (UARTx->msgRxdHandle.msgMaxTime != 0))
		{
			if (UARTx->msgRxdHandle.msgRecordTick == 0)
			{
				return OK_0;
			}
			//---��ȡ��ʱֵ
			_return = UART_TimeTick_OverFlow(&(UARTx->msgRxdHandle));
			//---��ʱ�����жϣ�����ĳЩ״̬�µ�ǰ��¼��ʱ��ֵ�ڸ�дΪ���ʱ��ʱ���¼��û�з���ͬ������
			//if ((_return != OK_0))
			if ((_return != OK_0) && (UARTx->msgRxdHandle.msgRecordTick != 0))
			{
				//---��ӡ��ʱ�Ĵ�����Ϣ
				UART_Printf(UARTx, "=>>SP%d:Receive Mode Timeout Error!<<=\r\n", (UARTx->msgIndex - 1));
				//---��λ�������ݻ�����
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
			//---��ȡ��ʱֵ
			_return = UART_TimeTick_OverFlow(&(UARTx->msgTxdHandle));
			//---��ʱ�����жϣ�����ĳЩ״̬�µ�ǰ��¼��ʱ��ֵ�ڸ�дΪ���ʱ��ʱ���¼��û�з���ͬ������
			if ((_return != OK_0) && (UARTx->msgTxdHandle.msgRecordTick != 0))
			{
				//---��ӡ��ʱ�Ĵ�����Ϣ
				UART_Printf(UARTx, "=>>SP%d:Send Mode Timeout Error!<<=\r\n", (UARTx->msgIndex - 1));
				//---��λ�������ݻ�����
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
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ���ܵ�������󳤶�ʹ��1�ֽڱ�ʾ
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_ITRead_8BitsTask(UART_HandleType*UARTx, UINT8_T val)
{
	//---��������������
	static UINT8_T tempVal;
	tempVal = val;
	//---���ݽ��ղ���
	switch (UARTx->msgRxdHandle.msgStep)
	{
		//---�������ݵı�ͷ
		case 0:
			if (UARTx->msgRxdHandle.msgRIndex == 0)
			{
				if (UARTx->msgRxdID == tempVal)
				{
					UARTx->msgRxdHandle.pMsgVal[0] = tempVal;
					UARTx->msgRxdHandle.msgStep = 1;
					//---��¼���ݵĸ���
					UARTx->msgRxdHandle.msgCount = 1;
					//---�յ���һ�����ϸ�ʽ�����ݣ�������ʱ������
					UART_TimeTick_Init(&(UARTx->msgRxdHandle));
					//---���㳬ʱ��־
					UART_ClearOverFlow(&(UARTx->msgRxdHandle));
				}
			}
			break;
			//---�������ݵĳ���
		case 1:
			if ((tempVal > 0) && (tempVal < (UINT8_T)(UARTx->msgRxdHandle.msgMaxSize & 0xFF)))
			{
				UARTx->msgRxdHandle.pMsgVal[1] = tempVal;
				//---��ȡ���ݵĽ��ճ���
				UARTx->msgRxdHandle.msgWIndex = tempVal;
				//---��¼���ݵĸ���
				UARTx->msgRxdHandle.msgCount += 1;
				//---��һ����
				UARTx->msgRxdHandle.msgStep = 2;
			}
			else
			{
				UARTx->msgRxdHandle.msgStep = 0;
			}
			//---��λ��ʱ������
			UART_TimeTick_Init(&(UARTx->msgRxdHandle));
			break;
			//---����������Ϣ
		case 2:
			UARTx->msgRxdHandle.pMsgVal[UARTx->msgRxdHandle.msgRIndex + 2] = tempVal;
			UARTx->msgRxdHandle.msgRIndex++;
			//---��¼���ݵĸ���
			UARTx->msgRxdHandle.msgCount += 1;
			//---�ж��Ƿ����
			if (UARTx->msgRxdHandle.msgRIndex >= UARTx->msgRxdHandle.msgMaxSize)
			{
				UARTx->msgRxdHandle.msgRIndex = 0;
			}
			//---��λ��ʱ������
			UART_TimeTick_Init(&(UARTx->msgRxdHandle));
			//---�ж��Ƿ�������
			if (UARTx->msgRxdHandle.msgRIndex >= UARTx->msgRxdHandle.msgWIndex)
			{
				UARTx->msgRxdHandle.msgStep = 3;
				UARTx->msgRxdHandle.msgState = UART_OK;
				//---���㳬ʱ������
				//UART_TimeTick_DeInit(UARTx, 1);
				//---��¼������ɵ�ʱ��
				UARTx->msgRxdHandle.msgRecordTime = ((UARTx->msgRxdHandle.pMsgTimeTick != NULL) ? (UARTx->msgRxdHandle.pMsgTimeTick()) : 0);
			}
			break;
		case 3:
			//---���㳬ʱ������
			//UART_TimeTick_DeInit(UARTx,1);
			break;
		default:
			//UARTx->msgRxHandler.msgNowTime = 0;
			break;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ���ܵ�������󳤶�ʹ��2�ֽڱ�ʾ
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_ITRead_16BitsTask(UART_HandleType*UARTx, UINT8_T val)
{
	//---��������������
	static UINT8_T tempVal;
	tempVal = val;
	//---���ݽ��ղ���
	switch (UARTx->msgRxdHandle.msgStep)
	{
		//---�������ݵı�ͷ
		case 0:
			if (UARTx->msgRxdHandle.msgRIndex == 0)
			{
				if (UARTx->msgRxdID == tempVal)
				{
					UARTx->msgRxdHandle.pMsgVal[0] = tempVal;
					UARTx->msgRxdHandle.msgStep = 1;
					//---��¼���ݵĸ���
					UARTx->msgRxdHandle.msgCount = 1;
					//---�յ���һ�����ϸ�ʽ�����ݣ�������ʱ������
					UART_TimeTick_Init(&(UARTx->msgRxdHandle));
					//---���㳬ʱ��־
					UART_ClearOverFlow(&(UARTx->msgRxdHandle));
				}
			}
			break;
			//---�������ݵĳ��ȸ�λ
		case 1:
			UARTx->msgRxdHandle.pMsgVal[1] = tempVal;
			UARTx->msgRxdHandle.msgWIndex = tempVal;
			UARTx->msgRxdHandle.msgWIndex <<= 8;
			UARTx->msgRxdHandle.msgStep = 2;
			//---��¼���ݵĸ���
			UARTx->msgRxdHandle.msgCount += 1;
			//---��λ��ʱ������
			UART_TimeTick_Init(&(UARTx->msgRxdHandle));
			break;
			//---�������ݵĳ��ȵ�λ
		case 2:
			UARTx->msgRxdHandle.pMsgVal[2] = tempVal;
			UARTx->msgRxdHandle.msgWIndex += tempVal;
			//---��¼���ݵĸ���
			UARTx->msgRxdHandle.msgCount += 1;
			//---�ж������Ƿ�Ϸ�
			if ((UARTx->msgRxdHandle.msgWIndex > 0) && (UARTx->msgRxdHandle.msgWIndex < UARTx->msgRxdHandle.msgMaxSize))
			{
				//---��¼���ݵĸ���
				UARTx->msgRxdHandle.msgCount = UARTx->msgRxdHandle.msgWIndex;
				//---��һ����
				UARTx->msgRxdHandle.msgStep = 3;
			}
			else
			{
				UARTx->msgRxdHandle.msgStep = 0;
			}
			//---��λ��ʱ������
			UART_TimeTick_Init(&(UARTx->msgRxdHandle));
			break;
			//---����������Ϣ
		case 3:
			UARTx->msgRxdHandle.pMsgVal[UARTx->msgRxdHandle.msgRIndex + 3] = tempVal;
			UARTx->msgRxdHandle.msgRIndex++;
			//---��¼���ݵĸ���
			UARTx->msgRxdHandle.msgCount += 1;
			//---�ж��Ƿ����
			if (UARTx->msgRxdHandle.msgRIndex >= UARTx->msgRxdHandle.msgMaxSize)
			{
				UARTx->msgRxdHandle.msgRIndex = 0;
			}
			//---��λ��ʱ������
			UART_TimeTick_Init(&(UARTx->msgRxdHandle));
			//---�ж��Ƿ�������
			if (UARTx->msgRxdHandle.msgRIndex >= UARTx->msgRxdHandle.msgWIndex)
			{
				UARTx->msgRxdHandle.msgStep = 4;
				UARTx->msgRxdHandle.msgState = UART_OK;
				//---���㳬ʱ������
				//UART_TimeTick_DeInit(UARTx, 1);
				//---��¼������ɵ�ʱ��
				UARTx->msgRxdHandle.msgRecordTime = ((UARTx->msgRxdHandle.pMsgTimeTick != NULL) ? (UARTx->msgRxdHandle.pMsgTimeTick()) : 0);
			}
			break;
		case 4:
			//---���㳬ʱ������
			//UART_TimeTick_DeInit(UARTx,1);
			break;
		default:
			//UARTx->msgRxHandler.msgNowTime = 0;
			break;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������жϽ������ݣ�����ͨ�����ݻ������Ĵ�С���жϽ������ݵĳ��ȣ����ò�ͬ�Ľ��պ���
//////�������:
//////�������:
//////˵		����
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
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_PollMode_WriteByte(UART_HandleType*UARTx, UINT8_T  val)
{
	UINT8_T _return=OK_0;
	//---��ȡ��ǰʱ�����
	UINT32_T nowTime = 0;
	UINT32_T oldTime = 0;
	UINT32_T cnt = 0;
	//---��ȡ��ǰʱ�����
	oldTime = UARTx->msgTxdHandle.pMsgTimeTick();
	//---��������
	LL_USART_TransmitData8(UARTx->pMsgUART, val);
	//---�ȴ��������
	while (LL_USART_IsActiveFlag_TC(UARTx->pMsgUART) == RESET)
	{
		//--->>>���볬ʱ����---��ʼ
		//---��ǰʱ��
		nowTime = UARTx->msgTxdHandle.pMsgTimeTick();
		//---�жϵδ�ʱ�Ƿ����������
		if (nowTime < oldTime)
		{
			cnt = (0xFFFFFFFF - oldTime + nowTime);
		}
		else
		{
			cnt = nowTime - oldTime;
		}
		//---�ж��Ƿ�ʱ
		if (cnt > 50)
		{
			//---���ͷ�����ʱ����
			_return=ERROR_1;
			break;
		}
		//--->>>���볬ʱ����---����
		//---ι��
		WDT_RESET();
	}
	//---���������ɱ�־λ
	LL_USART_ClearFlag_TC(UARTx->pMsgUART);
	return _return;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� �����ַ���
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_PollMode_WriteData(UART_HandleType*UARTx, char *pVal)
{
	//---����485Ϊ����ģʽ
	UART_GPIO_485_Init(UARTx, UART_485_TX_ENABLE);
	//---�л����Ͷ˿�Ϊ���ģʽ
	UART_GPIO_TxInit(UARTx, UART_GPIOTX_SET_OUTPUT);
	//---�ر��ж�
	//CLI();
	while (*pVal != '\0')
	{
		UART_PollMode_WriteByte(UARTx, (UINT8_T)*pVal);
		pVal++;
	}
	//---ʹ���ж�
	//SEI();
	//---����485Ϊ����ģʽ
	UART_GPIO_485_Init(UARTx, UART_485_RX_ENABLE);
	//---�л����Ͷ˿�Ϊ����ģʽ
	UART_GPIO_TxInit(UARTx, UART_GPIOTX_SET_INPUT);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_PollMode_ReadByte(UART_HandleType*UARTx)
{
	//---��ȡ��ǰʱ�����
	UINT32_T nowTime = 0;
	UINT32_T oldTime = 0;
	UINT32_T cnt = 0;
	//---��ȡ��ǰʱ�����
	oldTime = UARTx->msgTxdHandle.pMsgTimeTick();
	//---�ȴ��������
	while (LL_USART_IsActiveFlag_RXNE(UARTx->pMsgUART) != RESET)
	{
		//--->>>���볬ʱ����---��ʼ
		//---��ǰʱ��
		nowTime = UARTx->msgTxdHandle.pMsgTimeTick();
		//---�жϵδ�ʱ�Ƿ����������
		if (nowTime < oldTime)
		{
			cnt = (0xFFFFFFFF - oldTime + nowTime);
		}
		else
		{
			cnt = nowTime - oldTime;
		}
		//---�ж��Ƿ�ʱ
		if (cnt > 50)
		{
			//---���ͷ�����ʱ����
			break;
		}
		//--->>>���볬ʱ����---����
		//---ι��
		WDT_RESET();
	}
	return LL_USART_ReceiveData8(UARTx->pMsgUART);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
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
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_ITWrite_TXETask(UART_HandleType*UARTx)
{
	VLTUINT8_T tempFlag=OK_0;
	if (UARTx->msgTxdHandle.msgWIndex != 0)
	{
		if (UARTx->msgTxdHandle.msgRIndex != UARTx->msgTxdHandle.msgWIndex)
		{
			//---����8Bit������
			LL_USART_TransmitData8(UARTx->pMsgUART, UARTx->msgTxdHandle.pMsgVal[UARTx->msgTxdHandle.msgRIndex]);
			//---���ݻ������������
			UARTx->msgTxdHandle.msgRIndex++;
			//---У�黺�����Ƿ����
			if (UARTx->msgTxdHandle.msgRIndex >= UARTx->msgTxdHandle.msgMaxSize)
			{
				UARTx->msgTxdHandle.msgRIndex = 0;
			}
			//---У�������Ƿ����뻺����
			if ((UARTx->msgTxdHandle.msgRIndex >= UARTx->msgTxdHandle.msgWIndex) && (UARTx->msgTxdHandle.msgCount > 0) && (UARTx->msgTxdHandle.msgRIndex >= UARTx->msgTxdHandle.msgCount))
			{
				//---�������,�������ݼĴ������жϲ�ʹ��
				LL_USART_DisableIT_TXE(UARTx->pMsgUART);
				//---ʹ�ܷ�������жϣ������л�TXD�˿�Ϊ����״̬
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
	//---У����
	if (tempFlag!=OK_0)
	{
		//---�������,�������ݼĴ������жϲ�ʹ��---����Ƿ�����쳣���رշ������ݼĴ������ж�
		LL_USART_DisableIT_TXE(UARTx->pMsgUART);
		//---������ݷ��ͻ�����
		UART_Write_Init(UARTx);
	}
	//---��λ��ʱ������
	UART_TimeTick_Init(&(UARTx->msgTxdHandle));
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_ITWrite_TCTask(UART_HandleType*UARTx)
{
#ifdef USE_UART_485
	//---������485������485��Ӧ���ӳ�����,���ӷ��ͻ��з������ڻ���485����Ӧ
	if ((UARTx->msg485Port.msgPort != NULL) && (UARTx->msgTxdHandle.msgStep == 0))
	{
		//---����8Bit������
		LL_USART_TransmitData8(UARTx->pMsgUART, 0x0D);
		UARTx->msgTxdHandle.msgStep = 1;
	}
	else if ((UARTx->msg485Port.msgPort != NULL) && (UARTx->msgTxdHandle.msgStep == 1))
	{
		//---����8Bit������
		LL_USART_TransmitData8(UARTx->pMsgUART, 0x0A);
		UARTx->msgTxdHandle.msgStep = 2;
	}
	else
#endif
	{
		//---�������,�������ݷ�������жϲ�ʹ��
		LL_USART_DisableIT_TC(UARTx->pMsgUART);
		//---������ݷ��ͻ�����
		UART_Write_Init(UARTx);
		//---���㳬ʱ������
		//UART_TimeTick_DeInit(UARTx, 0);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���������
//////�������:
//////�������:
//////˵		����
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
		//---�жϷ��ͼĴ������ж��Ƿ�ʹ��
		if (LL_USART_IsEnabledIT_TXE(UARTx->pMsgUART) == 0)
		{
			//---����485Ϊ����ģʽ
			UART_GPIO_485_Init(UARTx, UART_485_TX_ENABLE);
			//---�л����Ͷ˿�Ϊ���ģʽ
			UART_GPIO_TxInit(UARTx, UART_GPIOTX_SET_OUTPUT);
			//---ʹ�ܷ��Ϳ��ж�
			LL_USART_EnableIT_TXE(UARTx->pMsgUART);
		}
		return OK_0;
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��������ݵĴ�С
//////�������:
//////�������:
//////˵		����
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
		//---�ж��Ƿ����豸��ID��Ϣ
		if ((UARTx->msgCmdIndex - UARTx->msgIDIndex) != 0)
		{
			val += 1;
		}
		//---�ж��Ƿ����ӻ��з�
		if ((UARTx->msgTxdHandle.msgAddNewLine==1))
		{
			val += 2;
		}
		//---�ж����ݵĸ�ʽ
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
		//---�ж��Ƿ����豸��ID��Ϣ�����ID��Ϣ
		if ((UARTx->msgCmdIndex - UARTx->msgIDIndex) != 0)
		{
			_return = UART_RealTime_AddByte(UARTx, UARTx->msgID);
		}		
		//---���㷢�����ݵĸ���
		UARTx->msgTxdHandle.msgCount = val;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������ݵ�CRCУ����Ϣ
//////�������:
//////�������:
//////˵		����ʹ��CRC�����ݵı����0��ʼʹ��
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_RealTime_AddCRC(UART_HandleType*UARTx)
{
	//---У��CRC�Ƿ��ʼ��
	if ((UARTx->msgTxdHandle.msgCRCFlag != UART_CRC_NONE) && (CRCTask_Enable() == OK_0))
	{
		UINT32_T crcVal = 0;
		//---�ж�����У��ģʽ
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
	//---�ж��Ƿ����ӻ��з�
	if ((UARTx->msgTxdHandle.msgAddNewLine==1))
	{
		UART_RealTime_AddByte(UARTx, 0x0D);
		UART_RealTime_AddByte(UARTx, 0x0A);
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����Ͷ��ֽ�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_RealTime_AddData(UART_HandleType* UARTx, UINT8_T* pVal, UINT16_T length)
{
	UINT16_T i = 0;
	UINT8_T _return = OK_0;
	for (i = 0; i < length; i++)
	{
		_return = UART_RealTime_AddByte(UARTx, pVal[i]);
		//---�ж������Ƿ������ȷ
		if (_return != OK_0)
		{
			break;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� �����������ǰ�Ĳ�����Լ���ñ�ͷ������Ч���ݿ�ʼ��λ��
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_FillMode_Init(UART_HandleType*UARTx,UINT8_T isChildCmd)
{
	//---�ȴ����Ϳ���
	if (UART_Write_WaitIdle(UARTx)==OK_0)
	{	
		UARTx->msgTxdHandle.msgWIndex = 0;
		UARTx->msgTxdHandle.msgFlagIndex = 0;
		//---������ݱ�ͷ
		UART_FillMode_AddByte(UARTx, UARTx->msgTxdID);
		//---������ݳ���
		UART_FillMode_AddByte(UARTx, 0x00);
		if (UARTx->msgTxdHandle.msgMaxSize > 0xFF)
		{
			UART_FillMode_AddByte(UARTx, 0x00);
			UARTx->msgTxdHandle.msgFlagIndex += 1;
		}
		//---�����豸ͨ�ŵ��豸ID
		if ((UARTx->msgCmdIndex - UARTx->msgIDIndex) != 0)
		{
			UART_FillMode_AddByte(UARTx, UARTx->msgID);
		}
		//---������/����
		UART_FillMode_AddByte(UARTx, UARTx->msgRxdHandle.pMsgVal[UARTx->msgCmdIndex]);
		//---У���Ƿ���������
		if (isChildCmd != 0)
		{
			//---������
			UART_FillMode_AddByte(UARTx, UARTx->msgRxdHandle.pMsgVal[UARTx->msgCmdIndex + (isChildCmd == 0 ? 0 : 1)]);
		}
		//---��ʶ����ִ�н���ڻ������жϵ����
		UARTx->msgTxdHandle.msgFlagIndex = UARTx->msgTxdHandle.msgWIndex;
		//---����ִ�н��
		return OK_0;
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		�������������ڷ���
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
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_FillMode_AddData(UART_HandleType*UARTx, UINT8_T *pVal, UINT16_T length)
{
	UINT16_T i = 0;
	UINT8_T _return = OK_0;
	for (i = 0; i < length; i++)
	{
		_return = UART_FillMode_AddByte(UARTx, pVal[i]);
		//---�ж������Ƿ������ȷ
		if (_return != OK_0)
		{
			break;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����ִ�н����ʶ
//////�������:
//////�������:
//////˵		�������������ڷ���
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_FillMode_SetResultFlag(UART_HandleType* UARTx, UINT8_T val)
{
	UARTx->msgTxdHandle.pMsgVal[UARTx->msgTxdHandle.msgFlagIndex] = val;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�д����ŵ�����ֵ
//////�������:
//////�������:
//////˵		�������������ڷ���
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_FillMode_AddIndexW(UART_HandleType* UARTx, UINT16_T val)
{
	UARTx->msgTxdHandle.msgWIndex += val;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_Read_CRCTask(UART_HandleType*UARTx)
{
	UINT32_T crcVal = 0;
	UINT32_T crcTemp = 0;
	//---�������ݵĸ���
	UINT16_T length = UARTx->msgRxdHandle.msgWIndex;
	//---У��CRC�Ƿ��ʼ��
	if ((UARTx->msgRxdHandle.msgCRCFlag != UART_CRC_NONE) && (CRCTask_Enable() == OK_0))
	{
		//---�ж�����У��ģʽ
		if (UARTx->msgRxdHandle.msgCRCFlag == UART_CRC_CHECKSUM)
		{
			length -= 1;
			if (UARTx->msgRxdHandle.msgMaxSize < 250)
			{
				UARTx->msgRxdHandle.pMsgVal[1] = (UINT8_T)(length);
				//---��ȡУ���
				crcTemp = UARTx->msgRxdHandle.pMsgVal[length + 2];
				//---����У��ͼ���������ܳ���
				length += 2;
			}
			else
			{
				UARTx->msgRxdHandle.pMsgVal[1] = (UINT8_T)(length >> 8);
				UARTx->msgRxdHandle.pMsgVal[2] = (UINT8_T)(length);
				//---��ȡУ���
				crcTemp = UARTx->msgRxdHandle.pMsgVal[length + 3];
				//---����У��ͼ���������ܳ���
				length += 3;
			}
			//---����У���
			crcVal = CRCTask_CheckSum(UARTx->msgRxdHandle.pMsgVal, length);
		}
		else if (UARTx->msgRxdHandle.msgCRCFlag == UART_CRC_CRC8)
		{
			length -= 1;
			if (UARTx->msgRxdHandle.msgMaxSize < 250)
			{
				UARTx->msgRxdHandle.pMsgVal[1] = (UINT8_T)(length);
				//---��ȡУ���
				crcTemp = UARTx->msgRxdHandle.pMsgVal[length + 2];
				//---����У��ͼ���������ܳ���
				length += 2;
			}
			else
			{
				UARTx->msgRxdHandle.pMsgVal[1] = (UINT8_T)(length >> 8);
				UARTx->msgRxdHandle.pMsgVal[2] = (UINT8_T)(length);
				//---��ȡУ���
				crcTemp = UARTx->msgRxdHandle.pMsgVal[length + 3];
				//---����У��ͼ���������ܳ���
				length += 3;
			}
			//---����CRC8У��ֵ
			crcVal = CRCTask_CRC8(USE_CRC8_07H, UARTx->msgRxdHandle.pMsgVal, length);
		}
		else if (UARTx->msgRxdHandle.msgCRCFlag == UART_CRC_CRC16)
		{
			length -= 2;
			if (UARTx->msgRxdHandle.msgMaxSize < 250)
			{
				UARTx->msgRxdHandle.pMsgVal[1] = (UINT8_T)(length);
				//---��ȡCRC16�ĸ�λֵ
				crcTemp = UARTx->msgRxdHandle.pMsgVal[length + 1];
				//---��ȡCRC16�ĵ�λֵ
				crcTemp = (crcTemp << 8) + UARTx->msgRxdHandle.pMsgVal[length + 2];
				//---����У��ͼ���������ܳ���
				length += 2;
			}
			else
			{
				UARTx->msgRxdHandle.pMsgVal[1] = (UINT8_T)(length >> 8);
				UARTx->msgRxdHandle.pMsgVal[2] = (UINT8_T)(length);
				//---��ȡCRC16�ĸ�λֵ
				crcTemp = UARTx->msgRxdHandle.pMsgVal[length + 2];
				//---��ȡCRC16�ĵ�λֵ
				crcTemp = (crcTemp << 8) + UARTx->msgRxdHandle.pMsgVal[length + 3];
				//---����У��ͼ���������ܳ���
				length += 3;
			}
			//---����CRC16У��ֵ
			crcVal = CRCTask_CRC16(UARTx->msgRxdHandle.pMsgVal, length);
		}
		else if (UARTx->msgRxdHandle.msgCRCFlag == UART_CRC_CRC32)
		{
			length -= 4;
			if (UARTx->msgRxdHandle.msgMaxSize < 250)
			{
				UARTx->msgRxdHandle.pMsgVal[1] = (UINT8_T)(length);
				//---��ȡCRC32�����λֵ
				crcTemp = UARTx->msgRxdHandle.pMsgVal[length - 1];
				//---��ȡCRC32�Ĵθ�λֵ
				crcTemp = (crcTemp << 8) + UARTx->msgRxdHandle.pMsgVal[length];
				//---��ȡCRC32�Ĵε�λֵ
				crcTemp = (crcTemp << 8) + UARTx->msgRxdHandle.pMsgVal[length + 1];
				//---��ȡCRC32�ĵ�λֵ
				crcTemp = (crcTemp << 8) + UARTx->msgRxdHandle.pMsgVal[length + 2];
				//---����У��ͼ���������ܳ���
				length += 2;
			}
			else
			{
				UARTx->msgRxdHandle.pMsgVal[1] = (UINT8_T)(length >> 8);
				UARTx->msgRxdHandle.pMsgVal[2] = (UINT8_T)(length);
				//---��ȡCRC32�����λֵ
				crcTemp = UARTx->msgRxdHandle.pMsgVal[length];
				//---��ȡCRC32�Ĵθ�λֵ
				crcTemp = (crcTemp << 8) + UARTx->msgRxdHandle.pMsgVal[length + 1];
				//---��ȡCRC32�Ĵε�λֵ
				crcTemp = (crcTemp << 8) + UARTx->msgRxdHandle.pMsgVal[length + 2];
				//---��ȡCRC32�ĵ�λֵ
				crcTemp = (crcTemp << 8) + UARTx->msgRxdHandle.pMsgVal[length + 3];
				length += 3;
			}
			crcVal = CRCTask_CRC32(UARTx->msgRxdHandle.pMsgVal, length);
		}
		//---�ȶ�CRC��ֵ
		if (crcVal != crcTemp)
		{
			return  ERROR_1;
		}
	}
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_FillMode_WriteCRCTask(UART_HandleType*UARTx)
{
	//---У��CRC�Ƿ��ʼ��
	if ((UARTx->msgTxdHandle.msgCRCFlag != UART_CRC_NONE) && (CRCTask_Enable() == OK_0))
	{
		UINT32_T crcVal = 0;
		//--Ҫ�������ݵ��ܳ���
		UINT16_T length = UARTx->msgTxdHandle.msgWIndex;
		//---�ж��Ƿ����ӻ��з�
		if ((UARTx->msgTxdHandle.msgAddNewLine==1))
		{
			length += 2;
		}
		//---���ݴ�С������
		if (UARTx->msgTxdHandle.msgMaxSize < 0xFF)
		{
			UARTx->msgTxdHandle.pMsgVal[1] = (UINT8_T)(length- 2);
		}
		else
		{
			UARTx->msgTxdHandle.pMsgVal[1] = (UINT8_T)((length - 3) >> 8);
			UARTx->msgTxdHandle.pMsgVal[2] = (UINT8_T)((length - 3));
		}		
		//---�ж�����У��ģʽ
		if (UARTx->msgTxdHandle.msgCRCFlag == UART_CRC_CHECKSUM)
		{
			//---У���
			crcVal = CRCTask_CheckSum(UARTx->msgTxdHandle.pMsgVal, UARTx->msgTxdHandle.msgWIndex);
			UART_FillMode_AddByte(UARTx, (UINT8_T)crcVal);
		}
		else if (UARTx->msgTxdHandle.msgCRCFlag == UART_CRC_CRC8)
		{
			//---CRC8У��
			crcVal = CRCTask_CRC8(USE_CRC8_07H, UARTx->msgTxdHandle.pMsgVal, UARTx->msgTxdHandle.msgWIndex);
			UART_FillMode_AddByte(UARTx, (UINT8_T)crcVal);
		}
		else if (UARTx->msgTxdHandle.msgCRCFlag == UART_CRC_CRC16)
		{
			//---CRC16У��
			crcVal = CRCTask_CRC16(UARTx->msgTxdHandle.pMsgVal, UARTx->msgTxdHandle.msgWIndex);
			UART_FillMode_AddByte(UARTx, (UINT8_T)(crcVal >> 8));
			UART_FillMode_AddByte(UARTx, (UINT8_T)crcVal);
		}
		else if (UARTx->msgTxdHandle.msgCRCFlag == UART_CRC_CRC32)
		{
			//---CRC32У��
			crcVal = CRCTask_CRC32(UARTx->msgTxdHandle.pMsgVal, UARTx->msgTxdHandle.msgWIndex);
			UART_FillMode_AddByte(UARTx, (UINT8_T)(crcVal >> 24));
			UART_FillMode_AddByte(UARTx, (UINT8_T)(crcVal >> 16));
			UART_FillMode_AddByte(UARTx, (UINT8_T)(crcVal >> 8));
			UART_FillMode_AddByte(UARTx, (UINT8_T)crcVal);
		}
		//---�������ݵĴ�С
		UARTx->msgTxdHandle.msgCount = UARTx->msgTxdHandle.msgWIndex;
		return OK_0;
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��ȴ����ͽ������ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_Write_WaitIdle(UART_HandleType* UARTx)
{
	//---��ȡ��ǰʱ�����
	UINT32_T nowTime = 0;
	UINT32_T oldTime = 0;
	UINT32_T cnt = 0;
	//---��ȡ��ǰʱ�����
	oldTime = UARTx->msgTxdHandle.pMsgTimeTick();
	//---��鷢��״̬���ȴ�֮ǰ�����ݷ������;�����ǿ���״̬��������û���������ݷ�
	while ((UARTx->msgTxdHandle.msgState == UART_BUSY) || (UARTx->msgTxdHandle.msgState == UART_PRINTF) || (UARTx->msgTxdHandle.msgState == UART_DMA))
	{
		//---��ǰʱ��
		nowTime = UARTx->msgTxdHandle.pMsgTimeTick();
		//---�жϵδ�ʱ�Ƿ����������
		if (nowTime < oldTime)
		{
			cnt = (0xFFFFFFFF - oldTime + nowTime);
		}
		else
		{
			cnt = nowTime - oldTime;
		}
		//---�ж��Ƿ�ʱ
		if (cnt > 100)
		{
			//---���㷢��״̬��ǿ������
			UART_Write_Init(UARTx);
			//---���ͷ�����ʱ����
			return ERROR_1;
		}
		//---ι��
		WDT_RESET();
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ģʽ�������ͣ������ʺ����֮���жϷ��ͺ�DMAģʽ��DMAģʽ������������֮�󣬲����������͵ģ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_FillMode_WriteByteSTART(UART_HandleType*UARTx, UINT8_T isNeedID)
{
	//---�ж϶˿��Ƿ����
	if(UART_Write_WaitIdle(UARTx)==OK_0)
	{
		//---���÷���״̬Ϊ������
		UARTx->msgTxdHandle.msgState = UART_BUSY;
		//---�ж��Ƿ���Ҫ��䱨ͷ
		if (isNeedID == 1)
		{
			//---��䱨ͷ�����ݳ���
			UARTx->msgTxdHandle.pMsgVal[0] = UARTx->msgTxdID;
		}
		//---����豸ID
		if ((UARTx->msgCmdIndex - UARTx->msgIDIndex) != 0)
		{
			UARTx->msgTxdHandle.pMsgVal[UARTx->msgIDIndex] = UARTx->msgID;
		}	
		//---����CRC����
		UART_FillMode_WriteCRCTask(UARTx);
		//---�ж��Ƿ����ӻ��з�
		if (( UARTx->msgTxdHandle.msgAddNewLine == 1 ))
		{
			UART_FillMode_AddByte( UARTx, 0x0D );
			UART_FillMode_AddByte( UARTx, 0x0A );
		}	
		//---���ݴ�С������
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
		//---����485Ϊ����ģʽ
		UART_GPIO_485_Init(UARTx, UART_485_TX_ENABLE);
		//---�л����Ͷ˿�Ϊ���ģʽ
		UART_GPIO_TxInit(UARTx, UART_GPIOTX_SET_OUTPUT);
	#ifdef UART_INIT_GPIO
		//---��ȡ���1�ֽڵ�����
		UARTx->msgWriteFinalData= UARTx->msgTxdHandle.pMsgVal[UARTx->msgTxdHandle.msgCount-1];
	#endif
		//---У���ǲ���DMAģʽ
		if (UARTx->msgTxdHandle.msgDMAMode==0)
		{
			//---�������ݼĴ������ж�ʹ��
			LL_USART_EnableIT_TXE(UARTx->pMsgUART);
		}
		else
		{
			//---�������ݵ�ַ
			UART_DMA_Write_SetMemoryAddress(UARTx, (UARTx->msgTxdHandle.pMsgVal));
			//---����DMA����
			UART_DMA_Write_RESTART(UARTx);
		}
		//---��λ��ʱ������
		UART_TimeTick_Init(&(UARTx->msgTxdHandle));
		return OK_0;
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ģʽ�������ͣ������ʺ����֮���жϷ��ͺ�DMAģʽ��DMAģʽ������������֮�󣬲����������͵ģ�
//////�������: ����ָ�����ȵ�������Ϣ��Ĭ�ϸ�������������Ҫ�����ݣ��ڲ�û�ж����ݽ��д���
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_FillMode_WriteArraySTART(UART_HandleType* UARTx, UINT8_T *pArrayVal,UINT16_T length)
{
	if (UART_Write_WaitIdle(UARTx) == OK_0)
	{
		//---���÷���״̬Ϊæµ״̬
		UARTx->msgTxdHandle.msgState = UART_BUSY;
		//---�������ݳ���
		memcpy(UARTx->msgTxdHandle.pMsgVal, pArrayVal, length);
		//---Ҫд�����ݵĸ���
		UARTx->msgTxdHandle.msgWIndex = length;
		//---����CRC����
		UART_FillMode_WriteCRCTask(UARTx);
		//---�ж��Ƿ����ӻ��з�
		if ((UARTx->msgTxdHandle.msgAddNewLine == 1))
		{
			UART_FillMode_AddByte(UARTx, 0x0D);
			UART_FillMode_AddByte(UARTx, 0x0A);
		}
		UARTx->msgTxdHandle.msgCount = UARTx->msgTxdHandle.msgWIndex;
		//---����485Ϊ����ģʽ
		UART_GPIO_485_Init(UARTx, UART_485_TX_ENABLE);
		//---�л����Ͷ˿�Ϊ���ģʽ
		UART_GPIO_TxInit(UARTx, UART_GPIOTX_SET_OUTPUT);
	#ifdef UART_INIT_GPIO
		//---��ȡ���1�ֽڵ�����
		UARTx->msgWriteFinalData = UARTx->msgTxdHandle.pMsgVal[UARTx->msgTxdHandle.msgCount - 1];
	#endif
		//---У���ǲ���DMAģʽ
		if (UARTx->msgTxdHandle.msgDMAMode == 0)
		{
			//---�������ݼĴ������ж�ʹ��
			LL_USART_EnableIT_TXE(UARTx->pMsgUART);
		}
		else
		{
			//---�������ݵ�ַ
			UART_DMA_Write_SetMemoryAddress(UARTx, (UARTx->msgTxdHandle.pMsgVal));
			//---����DMA����
			UART_DMA_Write_RESTART(UARTx);
		}
		//---��λ��ʱ������
		UART_TimeTick_Init(&(UARTx->msgTxdHandle));
		return OK_0;
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���������
//////�������:
//////�������:
//////˵		���� ��ȡ�����־
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_FillMode_WriteSTART(UART_HandleType* UARTx,UINT16_T length)
{
	if (UART_Write_WaitIdle(UARTx) == OK_0)
	{
		//---���÷���״̬Ϊæµ״̬
		UARTx->msgTxdHandle.msgState = UART_BUSY;
		//---Ҫд�����ݵĸ���
		UARTx->msgTxdHandle.msgWIndex = length;
		//---����CRC����
		UART_FillMode_WriteCRCTask(UARTx);
		//---�ж��Ƿ����ӻ��з�
		if ((UARTx->msgTxdHandle.msgAddNewLine == 1))
		{
			UART_FillMode_AddByte(UARTx, 0x0D);
			UART_FillMode_AddByte(UARTx, 0x0A);
		}
		UARTx->msgTxdHandle.msgCount = UARTx->msgTxdHandle.msgWIndex;
		//---����485Ϊ����ģʽ
		UART_GPIO_485_Init(UARTx, UART_485_TX_ENABLE);
		//---�л����Ͷ˿�Ϊ���ģʽ
		UART_GPIO_TxInit(UARTx, UART_GPIOTX_SET_OUTPUT);
	#ifdef UART_INIT_GPIO
		//---��ȡ���1�ֽڵ�����
		UARTx->msgWriteFinalData = UARTx->msgTxdHandle.pMsgVal[UARTx->msgTxdHandle.msgCount - 1];
	#endif
		//---У���ǲ���DMAģʽ
		if (UARTx->msgTxdHandle.msgDMAMode == 0)
		{
			//---�������ݼĴ������ж�ʹ��
			LL_USART_EnableIT_TXE(UARTx->pMsgUART);
		}
		else
		{
			//---�������ݵ�ַ
			UART_DMA_Write_SetMemoryAddress(UARTx, (UARTx->msgTxdHandle.pMsgVal));
			//---����DMA����
			UART_DMA_Write_RESTART(UARTx);
		}
		//---��λ��ʱ������
		UART_TimeTick_Init(&(UARTx->msgTxdHandle));
		return OK_0;
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ��ȡ�����־
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_GetOverFlow(UART_HandleDef* UARTDefx)
{
	return UARTDefx->msgOverFlow ;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ��������־
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_ClearOverFlow(UART_HandleDef* UARTDefx)
{
	UARTDefx->msgOverFlow = 0;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ״̬��ʶ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_GetState(UART_HandleDef* UARTDefx)
{
	return UARTDefx->msgState;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����״̬��ʶ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_ClearState(UART_HandleDef* UARTDefx)
{
	UARTDefx->msgState = UART_OK;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���λ���ղ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_Read_Init(UART_HandleType*  UARTx)
{
	//---����485λ����ģʽ
	UART_GPIO_485_Init(UARTx, UART_485_RX_ENABLE);
	//---���㲽��
	UARTx->msgRxdHandle.msgStep = 0;
	//---���д��������
	UARTx->msgRxdHandle.msgWIndex = 0;
	//---�������������
	UARTx->msgRxdHandle.msgRIndex = 0;
	//---����������ݸ���
	//UARTx->msgRxdHandle.msgCount = 0;
	//---���������ɱ�־
	UARTx->msgRxdHandle.msgState = UART_BUSY;
	//---���㳬ʱ����
	UARTx->msgRxdHandle.msgRecordTick = 0;
	//---���㳬ʱ��־
	UARTx->msgRxdHandle.msgOverFlow = 0;
	//---�ָ����������׵�ַ����
	*(UARTx->msgRxdHandle.pMsgVal)= UARTx->msgRxdHandle.msgMsgValBaseAddr;
	//---У���ǲ���DMAģʽ
	if(UARTx->msgRxdHandle.msgDMAMode!=0)
	{
		UART_DMA_Read_RESTART(UARTx);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���λ���Ͳ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_Write_Init(UART_HandleType*  UARTx)
{
	//---���÷���״̬Ϊ�������
	UARTx->msgTxdHandle.msgState = UART_OK;
	//---���д��������
	UARTx->msgTxdHandle.msgWIndex = 0;
	//---�������������
	UARTx->msgTxdHandle.msgRIndex = 0;
	//---���㷢�����ݸ���
	//UARTx->msgTxdHandle.msgCount = 0;
	//---���㳬ʱ����
	UARTx->msgTxdHandle.msgRecordTick = 0;
	//---���㳬ʱ��־
	UARTx->msgTxdHandle.msgOverFlow = 0;
	//---�����������
	UARTx->msgTxdHandle.msgStep = 0;
	//---����485Ϊ����ģʽ
	UART_GPIO_485_Init(UARTx, UART_485_RX_ENABLE);
	//---���ݷ�����ɣ��л��˿�Ϊ����ģʽ
	UART_GPIO_TxInit(UARTx, UART_GPIOTX_SET_INPUT);
	//---��¼������ɵ�ʱ��
	UARTx->msgTxdHandle.msgRecordTime = ((UARTx->msgTxdHandle.pMsgTimeTick != NULL) ? (UARTx->msgTxdHandle.pMsgTimeTick()) : 0);
	//---�ָ����������׵�ַ����
	*(UARTx->msgTxdHandle.pMsgVal) = UARTx->msgTxdHandle.msgMsgValBaseAddr;
	return OK_0;
}


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�У�鷢��״̬�Ƿ��ǿ���״̬
//////�������:
//////�������:
//////˵		����
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
//////��		����
//////��		�ܣ�У���豸��ID��Ϣ
//////�������:
//////�������:
//////˵		���� 
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
//////��		����
//////��		�ܣ�������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void UART_PrintfSuspend(UART_HandleType* UARTx)
{
#ifdef USE_UART_PRINTF
	//--->>>�˿ڿ��г�ʱ���---��ʼ
	//---��ȡ��ǰʱ�����
	UINT32_T nowTime = 0;
	UINT32_T oldTime = 0;
	UINT32_T cnt = 0;
	//---��ȡ��ǰʱ�����
	oldTime = UARTx->msgTxdHandle.pMsgTimeTick();
	//---��鷢��״̬���ȴ�֮ǰ�����ݷ������;�����ǿ���״̬��������û���������ݷ�
	while ((UARTx->msgTxdHandle.msgState == UART_BUSY) || (UARTx->msgTxdHandle.msgState == UART_PRINTF) || (UARTx->msgTxdHandle.msgState == UART_DMA))
	{
		//---��ǰʱ��
		nowTime = UARTx->msgTxdHandle.pMsgTimeTick();
		//---�жϵδ�ʱ�Ƿ����������
		if (nowTime < oldTime)
		{
			cnt = (0xFFFFFFFF - oldTime + nowTime);
		}
		else
		{
			cnt = nowTime - oldTime;
		}
		//---�ж��Ƿ�ʱ
		if (cnt > 100)
		{
			//---���㷢��״̬
			UART_Write_Init(UARTx);
			//---���ͷ�����ʱ����
			return ;
		}
		//---ι��
		WDT_RESET();
	}
	//--->>>�˿ڿ��г�ʱ���---����
	//---����485Ϊ����ģʽ
	UART_GPIO_485_Init(UARTx, UART_485_TX_ENABLE);
	//---�л����Ͷ˿�Ϊ���ģʽ
	UART_GPIO_TxInit(UARTx, UART_GPIOTX_SET_OUTPUT);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��ָ�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void UART_PrintfResume(UART_HandleType* UARTx)
{
#ifdef USE_UART_PRINTF
	//---����485Ϊ����ģʽ
	UART_GPIO_485_Init(UARTx, UART_485_RX_ENABLE);
	//---���ݷ�����ɣ��л��˿�Ϊ����ģʽ
	UART_GPIO_TxInit(UARTx, UART_GPIOTX_SET_INPUT);
	//---��¼������ɵ�ʱ��
	UARTx->msgTxdHandle.msgRecordTime = ((UARTx->msgTxdHandle.pMsgTimeTick != NULL) ? (UARTx->msgTxdHandle.pMsgTimeTick()) : 0);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��Զ����Printf����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void UART_Printf(UART_HandleType*UARTx, char*fmt, ...)
{
#ifdef USE_UART_PRINTF
	//---У�鴮���Ƿ��Ѿ���ʼ����
	if (UARTx->pMsgUART!=NULL)
	{
		//---����������ȴ���һ�εķ������
		UART_PrintfSuspend(UARTx);
		//---��������
		UINT16_T length = 0;
		//---����һ��va_list�͵ı���,���������ָ�������ָ��
		va_list arg;
		//---��va_start���ʼ������,�����ĵڶ��������ǵ�һ���ɱ������ǰһ������,��һ���̶��Ĳ���
		va_start(arg, fmt);
		//---�������ַ����д�ӡ���ݡ����ݸ�ʽ�û��Զ���;���ز��������������ַ����ĳ���
		length = (UINT16_T)vsnprintf(&(pPrintf->pMsgVal[pPrintf->msgWIndex]),(UART_PRINTF_SIZE- pPrintf->msgWIndex), fmt, arg);
		//---�ж����ݴ�С���������û��λ�������˼��
		if (length > (UART_PRINTF_SIZE - pPrintf->msgWIndex))
		{
			//---�����������ַ����㴦��,
			pPrintf->msgWIndex=0;
			//---������֮�󣬲����ϴεķ����Ѿ���ɣ����¶����ݽ��д���
			length = (UINT16_T)vsnprintf(&(pPrintf->pMsgVal[pPrintf->msgWIndex]), (UART_PRINTF_SIZE - pPrintf->msgWIndex), fmt, arg);
		}
		//---������ƫ��
		pPrintf->msgRIndex = pPrintf->msgWIndex;
		//---��������ƫ��
		pPrintf->msgWIndex += length;
		//---���ٿ���64�ֽڵĻ�����
		if ((UART_PRINTF_SIZE - UART_PRINTF_IDLE_SIZE) < (pPrintf->msgWIndex))
		{
			//---�����������ַ����㴦��
			pPrintf->msgWIndex = 0;
		}
		//---��va_end������ɱ�����Ļ�ȡ
		va_end(arg);
	#ifdef UART_INIT_GPIO
		//---��ȡ���1�ֽڵ�����
		UARTx->msgWriteFinalData = pPrintf->pMsgVal[pPrintf->msgWIndex - 1];
	#endif
		//---���淢�͵�����λ��
		UARTx->msgPRIndex= pPrintf->msgRIndex;
		//---У���ǲ���DMAģʽ
		if (UARTx->msgTxdHandle.msgDMAMode!=0)
		{
			//--->>>DMA����ģʽ
			UARTx->msgTxdHandle.msgCount = length;
			//---�������ݵ�ַ
			UART_DMA_Write_SetMemoryAddress(UARTx, (UINT8_T*)(pPrintf->pMsgVal+ UARTx->msgPRIndex));
			//---����DMA����
			UART_DMA_Write_RESTART(UARTx);
		}
		else
		{
			//--->>>�жϷ���ģʽ
			//---Ҫ�������ݵĸ���
			UARTx->msgPCount = length;
			//---ʹ�õķ�������жϣ�������Ҫ���ȷ���һ������
			UARTx->msgPWIndex = 1;
			//---������ʹ��PRINTFģʽ
			UARTx->msgTxdHandle.msgState = UART_PRINTF;
			//---�������,�������ݷ�������жϲ�ʹ��
			LL_USART_EnableIT_TC(UARTx->pMsgUART);
			//---����8Bit������
			LL_USART_TransmitData8(UARTx->pMsgUART, pPrintf->pMsgVal[UARTx->msgPRIndex]);
		}
		//---��λ��ʱ������
		UART_TimeTick_Init(&(UARTx->msgTxdHandle));
	}
#endif	
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ӡLOG��Ϣ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void UART_PrintfLog(UART_HandleType* UARTx, char* fmt, va_list args)
{
#ifdef USE_UART_PRINTF
	//---У�鴮���Ƿ��Ѿ���ʼ����
	if (UARTx->pMsgUART != NULL)
	{
		//---����������ȴ���һ�εķ������
		UART_PrintfSuspend(UARTx);
		//---�������ַ����д�ӡ���ݡ����ݸ�ʽ�û��Զ���;���ز��������������ַ����ĳ���
		UINT16_T length  = (UINT16_T)vsnprintf(&(pPrintf->pMsgVal[pPrintf->msgWIndex]), (UART_PRINTF_SIZE - pPrintf->msgWIndex), fmt, args);
		//---�ж����ݴ�С���������û��λ�������˼��
		if (length > (UART_PRINTF_SIZE - pPrintf->msgWIndex))
		{
			//---�����������ַ����㴦��,
			pPrintf->msgWIndex = 0;
			//---���û�������Ϣ
			//memset((char *)pPrintf->pMsgVal,0, UART_PRINTF_SIZE);
			//---������֮�󣬲����ϴεķ����Ѿ���ɣ����¶����ݽ��д���
			length = (UINT16_T)vsnprintf(&(pPrintf->pMsgVal[pPrintf->msgWIndex]), (UART_PRINTF_SIZE - pPrintf->msgWIndex), fmt, args);
		}
		//---������ƫ��
		pPrintf->msgRIndex = pPrintf->msgWIndex;
		//---��������ƫ��
		pPrintf->msgWIndex += length;
	#ifdef UART_INIT_GPIO
		//---��ȡ���1�ֽڵ�����
		UARTx->msgWriteFinalData = pPrintf->pMsgVal[pPrintf->msgWIndex - 1];
	#endif
		//---���ٿ���64�ֽڵĻ�����
		if ((UART_PRINTF_SIZE - UART_PRINTF_IDLE_SIZE) < (pPrintf->msgWIndex))
		{
			//---�����������ַ����㴦��
			pPrintf->msgWIndex = 0;
		}
		//---���淢�͵�����λ��
		UARTx->msgPRIndex = pPrintf->msgRIndex;
		//---У���ǲ���DMAģʽ
		if (UARTx->msgTxdHandle.msgDMAMode != 0)
		{
			//--->>>DMA����ģʽ
			UARTx->msgTxdHandle.msgCount = length;
			//---�������ݵ�ַ
			UART_DMA_Write_SetMemoryAddress(UARTx, (UINT8_T*)(pPrintf->pMsgVal + (UARTx->msgPRIndex)));
			//---����DMA����
			UART_DMA_Write_RESTART(UARTx);
		}
		else
		{
			//--->>>�жϷ���ģʽ
			//---Ҫ�������ݵĸ���
			UARTx->msgPCount = length;
			//---ʹ�õķ�������жϣ�������Ҫ���ȷ���һ������
			UARTx->msgPWIndex = 1;
			//---������ʹ��PRINTFģʽ
			UARTx->msgTxdHandle.msgState = UART_PRINTF;
			//---�������,�������ݷ�������жϲ�ʹ��
			LL_USART_EnableIT_TC(UARTx->pMsgUART);
			//---����8Bit������
			LL_USART_TransmitData8(UARTx->pMsgUART, pPrintf->pMsgVal[UARTx->msgPRIndex]);
		}
		//---��λ��ʱ������
		UART_TimeTick_Init(&(UARTx->msgTxdHandle));
	}
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_ITPrintf_TCTask(UART_HandleType* UARTx)
{
#ifdef USE_UART_PRINTF
	if (UARTx->msgPWIndex>=UARTx->msgPCount)
	{
		//---�������,�������ݷ�������жϲ�ʹ��
		LL_USART_DisableIT_TC(UARTx->pMsgUART);
		//---�ָ�����
		UART_PrintfResume(UARTx);
		//---��ʶ�������
		UARTx->msgTxdHandle.msgState = UART_OK;
	}
	else
	{
		//---����8Bit������
		LL_USART_TransmitData8(UARTx->pMsgUART, pPrintf->pMsgVal[UARTx->msgPRIndex+UARTx->msgPWIndex]);
		UARTx->msgPWIndex++;
	}
#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  UART_ITDMA_TCTask(UART_HandleType* UARTx)
{
#ifdef UART_INIT_GPIO
	//---�������෢��һ�����һλ�����ݣ�����ΪDMA��������Լ���ʱ�������ʱ�л��˶˿���ᵼ�����һ�����ݶ�ʧ
	//---���1�ֽڶ෢һ�Σ����ڲ�����Ϊ�˿��л������Ե�������
	if (UARTx->msgTxdHandle.msgStep == 0)
	{
		//---����8Bit������
		LL_USART_TransmitData8(UARTx->pMsgUART, UARTx->msgWriteFinalData);
		UARTx->msgTxdHandle.msgStep = 1;
	}
	else
#endif
	{
		//---�������,�������ݷ�������жϲ�ʹ��
		LL_USART_DisableIT_TC(UARTx->pMsgUART);
		//---������ݷ��ͻ�����
		UART_Write_Init(UARTx);
	}
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��жϷ�����ɺ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_IT_TCTask(UART_HandleType* UARTx)
{
	if (UARTx->msgTxdHandle.msgState == UART_BUSY)
	{
		//---�жϷ�ʽ�ķ�����ɴ�����
		UART_ITWrite_TCTask(UARTx);
	}
	else if (UARTx->msgTxdHandle.msgState == UART_PRINTF)
	{
		//---printf����ʹ���жϷ�ʽ������ɴ�����
		UART_ITPrintf_TCTask(UARTx);
	}
	else if (UARTx->msgTxdHandle.msgState == UART_DMA)
	{
		//---DMA���͵��жϷ�����ɴ�����
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
//////��		����
//////��		�ܣ���ӡϵͳʱ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void UART_PrintfClockFreq(UART_HandleType*UARTx)
{
	LL_RCC_ClocksTypeDef rccClock = { 0 };
	//---��ȡϵͳʱ��
	LL_RCC_GetSystemClocksFreq(&rccClock);
	//---��ӡϵͳʱ��
	UART_Printf(UARTx, "SYSCLK=%UHz\r\n", rccClock.SYSCLK_Frequency);
	//---��ӡϵͳʱ��
	UART_Printf(UARTx, "HCLK=%UHz\r\n", rccClock.HCLK_Frequency);
	//---��ӡϵͳʱ��
	UART_Printf(UARTx, "PCLK1=%UHz\r\n", rccClock.PCLK1_Frequency);
	//---��ӡϵͳʱ��
	UART_Printf(UARTx, "PCLK2=%UHz\r\n", rccClock.PCLK2_Frequency);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�UART������ʱ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_Clock(USART_TypeDef* UARTx, UINT8_T isEnable)
{
#ifdef USART1
	if (UARTx == USART1)
	{
		if (isEnable == PERIPHERAL_CLOCK_DISABLE)
		{
			//---��ʹ��SPI��ʱ����
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_USART1);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---ʹ��SPI��ʱ����
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
			//---��ʹ��SPI��ʱ����
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_USART2);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---ʹ��SPI��ʱ����
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
			//---��ʹ��SPI��ʱ����
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_USART3);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---ʹ��SPI��ʱ����
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
			//---��ʹ��SPI��ʱ����
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_USART6);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---ʹ��SPI��ʱ����
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
			//---��ʹ��SPI��ʱ����
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART4);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---ʹ��SPI��ʱ����
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
			//---��ʹ��SPI��ʱ����
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART5);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---ʹ��SPI��ʱ����
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
			//---��ʹ��SPI��ʱ����
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART7);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---ʹ��SPI��ʱ����
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
			//---��ʹ��SPI��ʱ����
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART8);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---ʹ��SPI��ʱ����
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
			//---��ʹ��SPI��ʱ����
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_UART9);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---ʹ��SPI��ʱ����
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
			//---��ʹ��SPI��ʱ����
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_UART10);
		}
		else if (isEnable == PERIPHERAL_CLOCK_ENABLE)
		{
			//---ʹ��SPI��ʱ����
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
//////��		����
//////��		�ܣ���������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_DeInit(UART_HandleType*UARTx)
{
	LL_USART_DeInit(UARTx->pMsgUART);
	UART_Clock(UARTx->pMsgUART, PERIPHERAL_CLOCK_DISABLE);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���������
//////�������:
//////�������:
//////˵		����
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
//////��		����
//////��		�ܣ��жϴ�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////��
void UART_IRQTask(UART_HandleType* UARTx)
{
	//---���ݽ����жϴ�����---���ռĴ�����Ϊ��
	if (LL_USART_IsActiveFlag_RXNE(UARTx->pMsgUART) && LL_USART_IsEnabledIT_RXNE(UARTx->pMsgUART))
	{
		//---�жϴ�����
		UART_ITRead_Task(UARTx, LL_USART_ReceiveData8(UARTx->pMsgUART));
		//---����жϱ�־λ
		LL_USART_ClearFlag_RXNE(UARTx->pMsgUART);
	}
	//---���ݷ��ͼĴ����շ����жϴ�����
	if (LL_USART_IsActiveFlag_TXE(UARTx->pMsgUART) && LL_USART_IsEnabledIT_TXE(UARTx->pMsgUART))
	{
		//---�жϴ�����
		UART_ITWrite_TXETask(UARTx);
	}
	//---���ݷ�������жϴ�����
	if (LL_USART_IsActiveFlag_TC(UARTx->pMsgUART) && LL_USART_IsEnabledIT_TC(UARTx->pMsgUART))
	{
		//---�жϴ�����
		UART_IT_TCTask(UARTx);
		//---����жϱ�־λ
		LL_USART_ClearFlag_TC(UARTx->pMsgUART);
	}
	//---UART5��UART5��������CTS���
#if defined(UART4)||defined(UART5)
	if ((UARTx->pMsgUART!=UART4)&& (UARTx->pMsgUART != UART5))
#endif
	{
		//---CTS״̬�߱仯�ж�
		if (LL_USART_IsActiveFlag_nCTS(UARTx->pMsgUART) && LL_USART_IsEnabledIT_CTS(UARTx->pMsgUART))
		{
			//---�жϴ�����

			//---����жϱ�־λ
			LL_USART_ClearFlag_nCTS(UARTx->pMsgUART);
		}
	}
	//---LIN��·����ж�
	if (LL_USART_IsActiveFlag_LBD(UARTx->pMsgUART) && LL_USART_IsEnabledIT_LBD(UARTx->pMsgUART))
	{
		//---�жϴ�����

		//---����жϱ�־λ
		LL_USART_ClearFlag_LBD(UARTx->pMsgUART);
	}
	//---����״̬�жϣ���Ҫ������DMA���ղ���������
	if (LL_USART_IsActiveFlag_IDLE(UARTx->pMsgUART) && LL_USART_IsEnabledIT_IDLE(UARTx->pMsgUART))
	{
		//---�жϴ�����,DMA���ݽ���
		UART_DMA_Read_IdleTask(UARTx);
		//---��������жϱ�־λ
		LL_USART_ClearFlag_IDLE(UARTx->pMsgUART);
		//---���DMA�жϱ�ʶ
		LL_DMA_ClearFlag(UARTx->msgRxdHandle.pMsgDMA, UARTx->msgRxdHandle.msgDMAChannelOrStream);
	}
	//---��������ж�
	if (LL_USART_IsActiveFlag_ORE(UARTx->pMsgUART) && LL_USART_IsEnabledIT_ERROR(UARTx->pMsgUART))
	{
		//---�жϴ�����

		//---����жϱ�־λ
		LL_USART_ClearFlag_ORE(UARTx->pMsgUART);
	}
	//---�����ж�
	if (LL_USART_IsActiveFlag_NE(UARTx->pMsgUART) && LL_USART_IsEnabledIT_ERROR(UARTx->pMsgUART))
	{
		//---�жϴ�����

		//---����жϱ�־λ
		LL_USART_ClearFlag_NE(UARTx->pMsgUART);
	}
	//---֡�����ж�
	if (LL_USART_IsActiveFlag_FE(UARTx->pMsgUART) && LL_USART_IsEnabledIT_ERROR(UARTx->pMsgUART))
	{
		//---�жϴ�����

		//---����жϱ�־λ
		LL_USART_ClearFlag_FE(UARTx->pMsgUART);
	}
	//---��żУ���ж�
	if (LL_USART_IsActiveFlag_PE(UARTx->pMsgUART) && LL_USART_IsEnabledIT_PE(UARTx->pMsgUART))
	{
		//---�жϴ�����

		//---����жϱ�־λ
		LL_USART_ClearFlag_PE(UARTx->pMsgUART);
	}
}

////////////////////////////////////////////////////////////////////////////////
////DMAģʽ����
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��ر�DMA�Ľ���ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT16_T UART_DMA_Read_STOP(UART_HandleType* UARTx)
{
#ifdef USE_MCU_STM32F1
	//---ʹ��DMA
	LL_DMA_DisableChannel(UARTx->msgRxHandler.msgDMA, UARTx->msgRxHandler.msgDMAChannelOrStream);
	LL_DMA_ClearFlag_GI1(UARTx->msgRxHandler.msgDMA);
#else
	//---ʹ��DMA��������ж�
	LL_DMA_DisableIT_TC(UARTx->msgRxdHandle.pMsgDMA, UARTx->msgRxdHandle.msgDMAChannelOrStream);
	//---��ʹ��DMA
	LL_DMA_DisableStream(UARTx->msgRxdHandle.pMsgDMA, UARTx->msgRxdHandle.msgDMAChannelOrStream);
#endif
	//---����жϱ�־
	LL_DMA_ClearFlag(UARTx->msgRxdHandle.pMsgDMA, UARTx->msgRxdHandle.msgDMAChannelOrStream);
	//---ʹ��DMA��������ж�
	LL_DMA_EnableIT_TC(UARTx->msgRxdHandle.pMsgDMA, UARTx->msgRxdHandle.msgDMAChannelOrStream);
	//---����������ݵĳ���
	UINT16_T length = UARTx->msgRxdHandle.msgMaxSize - LL_DMA_GetDataLength(UARTx->msgRxdHandle.pMsgDMA, UARTx->msgRxdHandle.msgDMAChannelOrStream);
	return length;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����DMA�Ľ���ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_DMA_Read_RESTART(UART_HandleType* UARTx)
{
	//---����DMA��ȡ���ݵĴ�С
	LL_DMA_SetDataLength(UARTx->msgRxdHandle.pMsgDMA, UARTx->msgRxdHandle.msgDMAChannelOrStream, UARTx->msgRxdHandle.msgMaxSize);
	//---ʹ��DMA
#ifdef USE_MCU_STM32F1
	//---ʹ��DMA
	LL_DMA_EnableChannel(UARTx->msgRxdHandler.msgDMA, UARTx->msgRxdHandler.msgDMAChannelOrStream);
#else
	//---ʹ��DMA
	LL_DMA_EnableStream(UARTx->msgRxdHandle.pMsgDMA, UARTx->msgRxdHandle.msgDMAChannelOrStream);
#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����DMA����ģʽ�£����ݴ洢�ĵ�ַ
//////�������:
//////�������:
//////˵		����
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
//////��		����
//////��		�ܣ�ֹͣDMA�ķ���ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT16_T UART_DMA_Write_STOP(UART_HandleType* UARTx)
{
#ifdef USE_MCU_STM32F1
	//---ʹ��DMA
	LL_DMA_DisableChannel(UARTx->msgRxHandler.msgDMA, UARTx->msgRxHandler.msgDMAChannelOrStream);
	LL_DMA_ClearFlag_GI1(UARTx->msgRxHandler.msgDMA);
#else
	//---��ʹ��DMA
	LL_DMA_DisableStream(UARTx->msgTxdHandle.pMsgDMA, UARTx->msgTxdHandle.msgDMAChannelOrStream);
#endif
	LL_DMA_ClearFlag(UARTx->msgTxdHandle.pMsgDMA, UARTx->msgTxdHandle.msgDMAChannelOrStream);
	//---����������ݵĳ���
	UINT16_T length = UARTx->msgTxdHandle.msgMaxSize - LL_DMA_GetDataLength(UARTx->msgTxdHandle.pMsgDMA, UARTx->msgTxdHandle.msgDMAChannelOrStream);
	return length;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����DMA�ķ���ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_DMA_Write_RESTART(UART_HandleType* UARTx)
{
	//---����DMA�������ݵĴ�С
	LL_DMA_SetDataLength(UARTx->msgTxdHandle.pMsgDMA, UARTx->msgTxdHandle.msgDMAChannelOrStream, UARTx->msgTxdHandle.msgCount);
#ifdef USE_MCU_STM32F1
	//---ʹ��DMA
	LL_DMA_EnableChannel(UARTx->msgTxHandler.msgDMA, UARTx->msgTxHandler.msgDMAChannelOrStream);
#else
	//---ʹ��DMA
	LL_DMA_EnableStream(UARTx->msgTxdHandle.pMsgDMA, UARTx->msgTxdHandle.msgDMAChannelOrStream);
#endif
	//---����ΪDMA״̬
	UARTx->msgTxdHandle.msgState= UART_DMA;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����DMA������жϴ������Ϳ�������Ĵ�����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T UART_DMA_Read_IdleTask(UART_HandleType* UARTx)
{
	UINT8_T _return = OK_0;
	//---ֹͣ����DMAģʽ,����ȡ�������ݵĳ���
	UINT16_T dataLength= UART_DMA_Read_STOP(UARTx);
	//---У�鱨ͷ�Ƿ���ȷ
	if (UARTx->msgRxdHandle.pMsgVal[0] == UARTx->msgRxdID)
	{
		//---���ݳ�����Ϣ
		UINT16_T length = UARTx->msgRxdHandle.pMsgVal[1];
		//---У�����ݳ�����Ϣ
		if (UARTx->msgRxdHandle.msgMaxSize < 0xFF)
		{
			length += 2;
		}
		else
		{
			length = (length << 8) + UARTx->msgRxdHandle.pMsgVal[1];
			length += 3;
		}
		//---У�������Ƿ�Ϸ�
		if (length == dataLength)
		{
			UARTx->msgRxdHandle.msgState = UART_OK;
			UARTx->msgRxdHandle.msgCount=dataLength;
		}
		else
		{
			//---���ݲ����Ϲ���ʹ�����½���
			UART_Read_Init(UARTx);
			//---���ش�����Ϣ
			_return = ERROR_2;
		}
	}
	else
	{
		UARTx->msgRxdHandle.msgState = UART_OK;
		UARTx->msgRxdHandle.msgCount=dataLength;
		//---�����ݽ��������ǲ����Զ���Э�������
		_return = ERROR_1;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������ж�DMA�������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void UART_DMA_Read_IRQTask(UART_HandleType* UARTx)
{
	//---DMA����ģʽ
	UART_DMA_Read_IdleTask(UARTx);
	//---��������жϱ�־λ
	LL_USART_ClearFlag_IDLE(UARTx->pMsgUART);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������ж�DMA�������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void UART_DMA_Write_IRQTask(UART_HandleType* UARTx)
{
#ifdef USE_MCU_STM32F1
	//---��ʹ��DMA
	LL_DMA_DisableChannel(UARTx->msgTxHandler.msgDMA, UARTx->msgTxHandler.msgDMAChannelOrStream;
	LL_DMA_ClearFlag_GI1(UARTx->msgTxHandler.msgDMA);
#else
	//---��ʹ��DMA��������ж�
	LL_DMA_DisableIT_TC(UARTx->msgTxdHandle.pMsgDMA, UARTx->msgTxdHandle.msgDMAChannelOrStream);
	//---��ʹ��DMA
	LL_DMA_DisableStream(UARTx->msgTxdHandle.pMsgDMA, UARTx->msgTxdHandle.msgDMAChannelOrStream);
#endif
	//---�����ʶ
	LL_DMA_ClearFlag(UARTx->msgTxdHandle.pMsgDMA, UARTx->msgTxdHandle.msgDMAChannelOrStream);
	//---ʹ��DMA��������ж�
	LL_DMA_EnableIT_TC(UARTx->msgTxdHandle.pMsgDMA, UARTx->msgTxdHandle.msgDMAChannelOrStream);
	//---���㷢��
	//UART_Write_Init(UARTx);
	//---ʹ�ܷ�������жϣ������л�TXD�˿�Ϊ����״̬
	LL_USART_EnableIT_TC(UARTx->pMsgUART);
}


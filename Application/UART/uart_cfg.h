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
	//////////////////////////���ò���---��ʼ////////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////
	//===����������ж��ж��Ƿ���Ҫ��ʼ��GPIO
	#define  UART_INIT_GPIO
	//===�Ƿ���ӳ��printf����
	#define  USE_UART_PRINTF	
	//===�Ƿ�ʹ��485ģʽ��������
	#define  USE_UART_485
	//////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////���ò���---����////////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////�ṹ�嶨��---��ʼ//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////
	//===���ݽṹ��
	typedef struct _UART_HandleType				UART_HandleType;
	typedef struct _UART_HandleType				* pUART_HandleType;
	//===���ݽṹ��
	typedef struct _UART_HandleDef				UART_HandleDef;
	typedef struct _UART_HandleDef				*pUART_HandleDef;
	//===�������ݽṹ��
	typedef struct _UART_HandleDef				UART_RXDHandleType;
	typedef struct _UART_HandleDef				*pUART_RXDHandleType;
	//===�������ݽṹ��
	typedef struct _UART_HandleDef				UART_TXDHandleType;
	typedef struct _UART_HandleDef				*pUART_TXDHandleType;
	//===�������ݽṹ�嶨��
	struct _UART_HandleDef
	{
		UINT8_T									msgDMAMode;																//---�Ƿ���DMAģʽ��0---��DMAģʽ��1---DMAģʽ
		VLTUINT8_T								msgCheckSum;															//---У���
		VLTUINT8_T								msgCRCFlag;																//---У���־λ  0 ---��У�飬1 ---У��ͣ�2---CRC8У�飬3---CRC16У�飬4---CRC32У��
		VLTUINT8_T								msgState;																//---�ж������Ƿ���� 0---δ������1---����
		VLTUINT8_T								msgStep;																//---����
		VLTUINT8_T								msgAddNewLine;															//---�Ƿ���Ҫ���з�(\r\n)
		VLTUINT16_T								msgWIndex;																//---д���
		VLTUINT16_T								msgRIndex;																//---�����
		VLTUINT16_T								msgCount;																//---��д���ݵĳ���
		VLTUINT16_T								msgFlagIndex;															//---ִ�н���ı�ʶ�ţ������ݻ�������λ����Ϣ
		VLTUINT16_T								msgMaxSize;																//---���ݻ������Ĵ�С
		VLTUINT8_T								msgOverFlow;															//---��ʱ��־λ
		VLTUINT32_T								msgRecordTick;															//---��ʱʱ�����
		VLTUINT32_T								msgRecordTime;															//---��ʱʱ���¼ʱ��
		VLTUINT32_T								msgMaxTime;																//---��ʱʱ��
		VLTUINT32_T								msgMsgValBaseAddr;														//---���ݻ������Ļ���ַ������ָ��ƫ�Ƶ�ʱ����лָ�
		UINT8_T									*pMsgVal;																//---������(��Ҫ��ǰ��������ݵĻ�����)
		DMA_TypeDef								*pMsgDMA;																//---DMA��
		UINT32_T								msgDMAChannelOrStream;													//---DMAͨ���Ż�������Ϣ
		UINT32_T(*pMsgTimeTick)(void);																					//---���ڳ�ʱ����
	};	
	//===�������ݶ���
	struct _UART_HandleType
	{
		#ifdef USE_UART_PRINTF
			UINT16_T							msgPCount;																//---��ӡ��������
			UINT16_T							msgPWIndex;																//---��ӡ�������
			UINT16_T							msgPRIndex;																//---��ӡ��ȡ���
		#endif
		UINT8_T									msgIndex;																//---UART�˿ڵ�������
		UINT8_T									msgRxdID;																//---���ձ�ͷ
		UINT8_T									msgTxdID;																//---���ͱ�ͷ
		UINT8_T									msgID;																	//---�豸ID
		UINT8_T									msgIDIndex;																//---�豸ID�������е�λ��
		UINT8_T									msgCmdIndex;															//---�����������е�λ��
		UINT8_T									msgDataOneIndex;														//---����1�������е�λ��
		UINT8_T									msgDataTwoIndex;														//---����2�������е�λ��
		UINT8_T									msgIndexOffset;															//---������ƫ����
		#ifdef UART_INIT_GPIO
			UINT8_T								msgWriteFinalData;													//---DMAģʽ�£����͵����1�ֽ�����
		#endif
		GPIO_HandleType							msgTxPort;																//---UART��GPIO�˿ں�
		#ifdef USE_UART_485
			GPIO_HandleType						msg485Port;																//---485��ʹ��GPIO�˿�
		#endif
		USART_TypeDef							*pMsgUART;																//---UART�˿�
		UART_TXDHandleType						msgTxdHandle;															//---���ͺ���
		UART_RXDHandleType						msgRxdHandle;															//---���պ���
	};
	//===printf���ݽṹ��
	typedef struct _UART_PrintfType				UART_PrintfType;
	typedef struct _UART_PrintfType				*pUART_PrintfType;
	//===Printf��ӡ���ݶ���
	struct _UART_PrintfType
	{
		UINT16_T								msgRIndex;																//---��ȡ����
		UINT16_T								msgWIndex;																//---��������
		char									* pMsgVal;																//---������(��Ҫ��ǰ��������ݵĻ�����)
	};
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////�ṹ�嶨��---����//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////���ú궨��---��ʼ//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////
	//===��ӳ��printf֮������ݻ�����
	#ifdef USE_UART_PRINTF
		#define UART_PRINTF_SIZE					1024																//---ʹ��printf��ʱ��Ļ������Ĵ�С
		#define UART_PRINTF_IDLE_SIZE				64																	//---printf����С�����������Ĵ�С
	#endif	
	//===ʹ�õ�У�鷽ʽ
	#define UART_CRC_NONE							0
	#define UART_CRC_CHECKSUM						1	
	//===����ӦCRCУ��ȼ�
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
	//===���Ͷ˿ڵ�����
	#define UART_GPIOTX_SET_INPUT					0																	//---��ѵ��ַʱ�򣬷��Ͷ˿���Ҫ�л�Ϊ����
	#define UART_GPIOTX_SET_OUTPUT					1																	//---��ѵ��ַʱ�򣬷��Ͷ˿���Ҫ�л�Ϊ���
	//===485���ݶ˿ڵĿ���ʹ��
	#define UART_485_RX_ENABLE						0																	//---485ģʽ�´������ݽ���
	#define UART_485_TX_ENABLE						1																	//---485ģʽ�´������ݷ���
	//===���ڵ�״̬
	#define UART_BUSY								0																	//---����æµ״̬
	#define UART_OK									1																	//---���ڿ���״̬	
	#define UART_ERROR								2																	//---���ڴ���״̬
	#define UART_PRINTF								3																	//---ʹ��Printf����������
	#define UART_DMA								4																	//---����DMA״̬
	#define UART_IT_IDLE							5																	//---�����жϿ���״̬

	//===�����������
	#ifdef USART1
		#define UART_TASK_ONE						pUart1																//---UART1������
		#define UART1_RX_DMA_MODE					1																	//---�Ƿ�ʹ�ܽ���DMAģʽ��0---�жϣ�1---DMAģʽ
		#define UART1_TX_DMA_MODE					1																	//---�Ƿ�ʹ�ܷ���DMAģʽ��0---�жϣ�1---DMAģʽ
	#endif
	#ifdef USART2
		#define UART_TASK_TWO						0																	//---UART2������
		#define UART2_RX_DMA_MODE					1																	//---�Ƿ�ʹ�ܽ���DMAģʽ��0---�жϣ�1---DMAģʽ
		#define UART2_TX_DMA_MODE					1																	//---�Ƿ�ʹ�ܷ���DMAģʽ��0---�жϣ�1---DMAģʽ
	#endif
	#ifdef USART3
		#define UART_TASK_THREE						pUart3																//---UART3������
		#define UART3_RX_DMA_MODE					1																	//---�Ƿ�ʹ�ܽ���DMAģʽ��0---�жϣ�1---DMAģʽ
		#define UART3_TX_DMA_MODE					1																	//---�Ƿ�ʹ�ܷ���DMAģʽ��0---�жϣ�1---DMAģʽ
	#endif
	#ifdef UART4
		#define UART_TASK_FOUR						0																	//---UART4������
		#define UART4_RX_DMA_MODE					1																	//---�Ƿ�ʹ�ܽ���DMAģʽ��0---�жϣ�1---DMAģʽ
		#define UART4_TX_DMA_MODE					1																	//---�Ƿ�ʹ�ܷ���DMAģʽ��0---�жϣ�1---DMAģʽ
	#endif
	#ifdef UART5
		#define UART_TASK_FIVE						0																	//---UART5������
		#define UART5_RX_DMA_MODE					1																	//---�Ƿ�ʹ�ܽ���DMAģʽ��0---�жϣ�1---DMAģʽ
		#define UART5_TX_DMA_MODE					1																	//---�Ƿ�ʹ�ܷ���DMAģʽ��0---�жϣ�1---DMAģʽ
	#endif
	#ifdef USART6
		#define UART_TASK_SIX						0																	//---UART6������
		#define UART6_RX_DMA_MODE					1																	//---�Ƿ�ʹ�ܽ���DMAģʽ��0---�жϣ�1---DMAģʽ
		#define UART6_TX_DMA_MODE					1																	//---�Ƿ�ʹ�ܷ���DMAģʽ��0---�жϣ�1---DMAģʽ
	#endif
	#ifdef UART7
		#define UART_TASK_SEVEN						0																	//---UART7������
		#define UART7_RX_DMA_MODE					1																	//---�Ƿ�ʹ�ܽ���DMAģʽ��0---�жϣ�1---DMAģʽ
		#define UART7_TX_DMA_MODE					1																	//---�Ƿ�ʹ�ܷ���DMAģʽ��0---�жϣ�1---DMAģʽ
	#endif
	#ifdef UART8
		#define UART_TASK_EIGHT						0																	//---UART8������
		#define UART8_RX_DMA_MODE					1																	//---�Ƿ�ʹ�ܽ���DMAģʽ��0---�жϣ�1---DMAģʽ
		#define UART8_TX_DMA_MODE					1																	//---�Ƿ�ʹ�ܷ���DMAģʽ��0---�жϣ�1---DMAģʽ
	#endif
	#ifdef UART9
		#define UART_TASK_NINE						0																	//---UART9������
		#define UART9_RX_DMA_MODE					1																	//---�Ƿ�ʹ�ܽ���DMAģʽ��0---�жϣ�1---DMAģʽ
		#define UART9_TX_DMA_MODE					1																	//---�Ƿ�ʹ�ܷ���DMAģʽ��0---�жϣ�1---DMAģʽ
	#endif
	#ifdef UART10
		#define UART_TASK_TEN						0																	//---UART10������	
		#define UART10_RX_DMA_MODE					1																	//---�Ƿ�ʹ�ܽ���DMAģʽ��0---�жϣ�1---DMAģʽ
		#define UART10_TX_DMA_MODE					1																	//---�Ƿ�ʹ�ܷ���DMAģʽ��0---�жϣ�1---DMAģʽ
	#endif
	//////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////���ú궨��---����////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////

	//===�ⲿ���ýӿ�
	extern UART_HandleType							g_Uart1;
	extern pUART_HandleType						pUart1;

	extern UART_HandleType							g_Uart3;
	extern pUART_HandleType						pUart3;

	//////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////����1�����ò�����ʼ//////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////
	//===���建�����Ĵ�С
	#define UART1_RX_BASE_SIZE						64//1800
	#define UART1_TX_BASE_SIZE						UART1_RX_BASE_SIZE	
	//===�����豸�ĵ�ַ�����豸��ʱ��ʹ�ã�0��ʱ����һ��һ
	#define UART1_DEVICE_ID						0x00
	
	//===�����豸ID������
	#if (UART1_DEVICE_ID!=0)
		#define	UART1_DEVICE_ID_INDEX				1
	#else
		#define	UART1_DEVICE_ID_INDEX				0
	#endif
	
	//===������CRCʹ�õ���󻺴���,�������ڸ���CRCУ��ĸ�ʽ
	#if defined(USE_CRC32)
		#define UART1_RX_MAX_SIZE					( UART1_RX_BASE_SIZE+4 )
	#elif defined(USE_CRC16
		#define UART1_RX_MAX_SIZE					( UART1_RX_BASE_SIZE+2 )
	#elif defined(USE_CRC8)||defined(USE_CHECKSUM)
		#define UART1_RX_MAX_SIZE					( UART1_RX_BASE_SIZE+1 )
	#else
		#define UART1_RX_MAX_SIZE					( UART1_RX_BASE_SIZE )
	#endif
	
	//===������CRCʹ�õ���󻺴���,�������ڸ���CRCУ��ĸ�ʽ
	#if defined(USE_CRC32)
		#define UART1_TX_MAX_SIZE					( UART1_TX_BASE_SIZE+4 )
	#elif defined(USE_CRC16)
		#define UART1_TX_MAX_SIZE					( UART1_TX_BASE_SIZE+2 )
	#elif defined(USE_CRC8)||defined(USE_CHECKSUM)
		#define UART1_TX_MAX_SIZE					( UART1_TX_BASE_SIZE+1 )
	#else
		#define UART1_TX_MAX_SIZE					( UART1_TX_BASE_SIZE )
	#endif
	
	//===���������еĺ���
	#if (UART1_RX_MAX_SIZE>0xFB)	
		//===�豸��ַ�������е�λ��
		#define UART1_ID_INDEX						3		
		//===Э���е�����1---������
		#define UART1_CMD_INDEX					( UART1_ID_INDEX+UART1_DEVICE_ID_INDEX)		
		//===Э���е�����2---������
		#define UART1_DATA1_INDEX					( UART1_CMD_INDEX+1 )		
		//===���ݷ��ص�ֵ---�Խ�����Ч���Է�����Ч
		#define UART1_DATA2_INDEX					( UART1_CMD_INDEX+2 )
	#else	
		//===�豸��ַ�������е�λ��
		#define UART1_ID_INDEX						2		
		//===Э���е�����1---������
		#define UART1_CMD_INDEX					( UART1_ID_INDEX+UART1_DEVICE_ID_INDEX)		
		//===Э���е�����2---����������һ������
		#define UART1_DATA1_INDEX					( UART1_CMD_INDEX+1 )		
		//===Э���еĵ�һ�����ݻ���ڶ�����
		#define UART1_DATA2_INDEX					( UART1_CMD_INDEX+2 )
	#endif
	//////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////����1�����ò�������//////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////

	//===��������
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

	//===��������
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

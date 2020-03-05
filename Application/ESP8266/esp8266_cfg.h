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
	//////////////////////////���ö���---��ʼ///////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////
	//===��Ϣֻ��
	typedef enum
	{
		ESP8266_SUCCESS = 0,																							//---�ɹ�
		ESP8266_BUSY,																									//---æµ״̬
		ESP8266_ERROR_ERR ,																								//---����
		ESP8266_ERROR_FAIL,																								//---ʧ��
		ESP8266_ERROR_READY ,																							//---׼��
		ESP8266_ERROR_BUSY ,																							//---æµ
		ESP8266_ERROR_UNKNOWN ,																							//---���Ǳ�
		ESP8266_ERROR_TIMEOUT ,																							//---��ʱ
		ESP8266_ERROR_CMD ,																								//---AT�������
	}ESP8266_STATUS;

	//===����ģʽ
	typedef enum
	{
		ESP8266_QUERY=0,																								//---��ѯģʽ
		ESP8266_STA = 1,																								//---Stationģʽ
		ESP8266_AP = 2,																									//---APģʽ
		ESP8266_STA_AP = 3																								//---AP+Stationģʽ
	}ESP8266_WIFI_MODE;
	
	//===����ģʽ
	typedef enum
	{
		ESP8266_CMD_QUERY=0,																							//---��ѯ����
		ESP8266_CMD_SETUP,																								//---��������
		ESP8266_CMD_EXECUTE																								//---ִ������
	}ESP8266_CMD_TYPE;

	//===WIFI�ȵ���ܷ�ʽ
	typedef enum
	{
		ESP8266_OPEN=0,
		ESP8266_WPA_PSK,
		ESP8266_WPA2_PSK,
		ESP8266_WPA_WPA2_PSK
	}ESP8266_WIFI_TYPE;
	
	typedef enum
	{
		ESP8266_GOTIP = 2,																								//---��ȡIP
		ESP8266_CONNECTED = 3,																							//---����״̬
		ESP8266_DISCONNECTED = 4,																						//---δ����״̬
		ESP8266_NOWIFI = 5,																								//---û��WIFI
	}ESP8266_WIFI_STATUS;

	//===����״̬
	typedef enum
	{
		ESP8266_TCP=0,																									//---TCPģʽ
		ESP8266_UDP,																									//---UDPģʽ
		ESP8266_UNKNOWN																									//---��ʶ��ģʽ
	}ESP8266_CONNECTION_TYPE;
	
	//===��������ģʽ
	typedef enum
	{
		ESP8266_CLIENT=0,																								//---�ͻ���
		ESP8266_SERVER																									//---�����
	}ESP8266_NET_TYPE;
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////���ö���---����///////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////
	
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////�ṹ�嶨��---��ʼ//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	
	//===�ṹ�嶨��
	typedef struct _ESP8266_HandleType				ESP8266_HandleType;
	//===ָ��ṹ�嶨��
	typedef struct _ESP8266_HandleType				*pESP8266_HandleType;
	//===���ݽṹ��
	struct _ESP8266_HandleType
	{
		UINT8_T					msgTask;																				//---������ţ�0---���У�1---��ѯ��Ӧ	
		UINT8_T					msgAckState;																			//---Ӧ��״̬
		char					*pMsgAckResult;																			//---Ӧ�������
		ESP8266_WIFI_MODE		msgWifiMode;																			//---����״̬��1---STA��2---AP��3---STA+AP
		UINT16_T				msgIntervalTime;																		//---��ѯʱ����,��λ��ms
		UINT8_T					*pMsgAck;																				//---Ӧ������
		UINT32_T				msgRecordTick;																			//---��ǰ��¼��ʱ��
		UART_HandleType			*pMsgUART;																				//---ʹ�õĴ���
		UINT32_T				(*pMsgTimeTick)(void);																	//---ʱ�����
		UINT8_T					(*pMsgAckOkCallBack)(ESP8266_HandleType*);												//---Ӧ����ȷ�ص�����
		UINT8_T					(*pMsgAckErrCallBack)(ESP8266_HandleType*);												//---Ӧ�����ص�����
		UINT8_T					(*pMsgAckTimeoutCallBack)(ESP8266_HandleType*);											//---��ʱ����ص�����
	};
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////�ṹ�嶨��---����//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	

	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////���ú궨��---��ʼ//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////
	//===�궨��
	//#define ESP8266_ACK_BUFFER_BASE_SIZE			32																	//---ACKӦ�𻺴����Ĵ�С
	#define	ESP8266_ACK_BUFFER_MAX_SIZE				32																	//---ACKӦ�𻺴��������ֵ
	#define ESP8266_BUFFER_BASE_SIZE				1024																//---���建�����ĳ�ʼ��С
	#define ESP8266_BUFFER_MAX_SIZE					ESP8266_BUFFER_BASE_SIZE+1											//---��������С��1�ֽڣ�Ϊ�˱����������
	#define ESP8266_COMM_UART						pUart3																//---ESP8266ͨ��ʹ�õ�UART
	#define ESP8266_LOG_UART						pUart1																//---ESP8266��ӡLOGʹ�õ�UART

	//===�����б�
	#define ESP8266_TASK_IDLE						0																	//---��������
	#define ESP8266_TASK_QUERY_ACK					1																	//---��ѯӦ��

	//===ACK��Ӧ�ķ�ʽ
	#define ESP8266_ACK_IDLE						0																	//---Ӧ�����
	#define ESP8266_ACK_WAIT						1																	//---�ȴ�Ӧ��
	#define ESP8266_ACK_OK							2																	//---Ӧ��ɹ�
	#define ESP8266_ACK_ERR							3																	//---Ӧ��ʧ��
	#define ESP8266_ACK_ERR_INFO					4																	//---����Ӧ�����ݴ���
	#define ESP8266_ACK_TIMEOUT						5																	//---Ӧ��ʱ
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////���ö���---����///////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////���ú궨��---��ʼ//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	
	//===�����������
	#define ESP8266_TASK_ONE						pEsp8266Device0
	#define ESP8266_TASK_TWO						0
	#define ESP8266_TASK_THREE						0 

	#define USE_ESP8266_LOG
	//===��ӡLOG��Ϣ(##__VA_ARGS__��' ## '����˼�ǣ�����ɱ���������Ի�Ϊ�գ���ʹԤ�������� preprocessor ��ȥ������ǰ����Ǹ�����)
	#define ESP8266_LOG(fmt, ...)					ESP8266_UART_LOG(ESP8266_LOG_UART,fmt,##__VA_ARGS__)
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////���ú궨��---��ʼ//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	

	//===�ⲿ���ýӿ�
	extern ESP8266_HandleType						g_Esp8266Device0;
	extern pESP8266_HandleType						pEsp8266Device0;

	//===��������
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
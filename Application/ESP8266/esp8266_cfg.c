#include "esp8266_cfg.h"

////////////////////////////////////////////////////////////////////////////////////// 
//////////////////////////>>>AT������---��ʼ/////////////////////////////////////////// 
//////////////////////////////////////////////////////////////////////////////////////
//===AT��������
const char ESP8266_AT_RESPONSE_OK[] = "OK\r\n";																			//---��ȷ
const char ESP8266_AT_RESPONSE_ERROR[] = "ERROR\r\n";																	//---����
const char ESP8266_AT_RESPONSE_FAIL[] = "FAIL";																			//---ʧ��
const char ESP8266_AT_RESPONSE_READY[] = "READY!";																		//---׼��
const char ESP8266_AT_RESPONSE_RECEIVED[] = "+IPD,";																	//---���յ�����������������

//===AT����ָ��
const char ESP8266_AT_CMD_TEST[] = "AT";																				//---��������
const char ESP8266_AT_CMD_RESET[] = "AT+RST";																			//---ģ������
const char ESP8266_AT_CMD_VERSION[] = "AT+GMR";																			//---�鿴�̼��汾
const char ESP8266_AT_CMD_DEEP_SLEEP[] = "AT+GSLP";																		//---����DepSleep˯��ģʽ
const char ESP8266_AT_CMD_SET_SLEEP[] = "AT+SLEEP";																		//---��������ģʽ
const char ESP8266_AT_CMD_ECHO_OPEN[] = "ATE1";																			//---�򿪻���
const char ESP8266_AT_CMD_ECHO_CLOSE[] = "ATE0";																		//---�رջ���
const char ESP8266_AT_CMD_RESTORE[] = "AT+RESTORE";																		//---�ָ���������
const char ESP8266_AT_CMD_UART[] = "AT+UART";																			//---���ô���ģʽ
const char ESP8266_AT_CMD_UART_CUR[] = "AT+UART_CUR";																	//---��ǰ��ʱ����
const char ESP8266_AT_CMD_UART_DEF[] = "AT+UART_DEF";																	//---UARTĬ�����ã����浽Flash
const char ESP8266_AT_CMD_SYSRAM[] = "AT+SYSRAM";																		//---��ѯϵͳ��ǰʣ���ڴ�
const char ESP8266_AT_CMD_SYSMSG_CUR[] = "AT+SYSMSG_CUR";																//---���õ�ǰϵͳ��Ϣ
const char ESP8266_AT_CMD_SYSMSG_DEG[] = "AT+SYSMSG_DEF";																//---����Ĭ��ϵͳ��Ϣ

//===WIFI��������
const char ESP8266_AT_WIFI_MODE[] = "AT+CWMODE";																		//---����ģʽ����ӦOK
const char ESP8266_AT_WIFI_DEF[] = "AT+CWMODE_DEF";																		//---����WiFiģ�鹤��ģʽΪ��STAģʽ���������ñ�����flash
const char ESP8266_AT_WIFI_CONNECT_AP[] = "AT+CWJAP";																	//---�����ȵ㣬����·��������ӦOK
const char ESP8266_AT_WIFI_LIST_IP[] = "AT+CIFSR";																		//---��ѯ�豸��IP��ַ
const char ESP8266_AT_WIFI_LIST_AP[] = "AT+CWLAP";																		//---������ǰ������·�����б�
const char ESP8266_AT_WIFI_DISCONNECT[] = "AT+CWQAP";																	//---�˳��ȵ�
const char ESP8266_AT_WIFI_AP_CONFIG[] = "AT+CWSAP";																	//---�����ȵ�
const char ESP8266_AT_WIFI_STA_IP[] = "AT+CWLIF";																		//---��ȡ������Ϣ
const char ESP8266_AT_WIFI_DHCP_EN[] = "AT+CWDHCP";																		//---����DHCO
const char ESP8266_AT_WIFI_AUTO_CONNECT[] = "AT+CWAUTOCONN";															//---ʹ���ϵ��Զ�����AP
const char ESP8266_AT_WIFI_SET_STA_MAC[] = "AT+CIPSTAMAC";																//---����MAC��ַ							
const char ESP8266_AT_WIFI_SET_STA_IP[] = "AT+CIPSTA";																	//---����IP��ַ
const char ESP8266_AT_WIFI_SET_AP_IP[] = "AT+CIPAP";																	//---�����ȵ��IP��ַ
const char ESP8266_AT_WIFI_STARTSMART[] = "AT+CWSTARTSMART";															//---���������Ƿ�ɹ�������Ҫ�ͷſ�����ռ���ڴ�
const char ESP8266_AT_WIFI_STOPSMART[] = "AT+CWSTOPSMART";																//---���������Ƿ�ɹ�������Ҫ�ͷſ�����ռ���ڴ�
const char ESP8266_AT_WIFI_STARTDISCOVER[] = "AT+CWSTARTDISCOVER";														//---�����ɱ���������΢��̽���ģʽ
const char ESP8266_AT_WIFI_STOPDISCOVER[] = "AT+CWSTOPDISCOVER";														//---�رտɱ���������΢��̽���ģʽ
const char ESP8266_AT_WIFI_WPS[] = "AT+WPS";																			//---����WPS
const char ESP8266_AT_WIFI_MDNS[] = "AT+MDNS";																			//---����MDNS����
const char ESP8266_AT_WIFI_SET_STA_NAME[] = "AT+CWHOSTNAME";															//---����STA����������
const char ESP8266_AT_WIFI_SET_STA_COUNTRY[] = "AT+CWCOUNTRY";															//---����WIFI�Ĺ�����

//===TCP/IP Commands
const char ESP8266_TCP_IP_STARTSMART[] = "AT+CWSTARTSMART";																//---���������Ƿ�ɹ�������Ҫ�ͷſ�����ռ���ڴ�
const char ESP8266_TCP_IP_STOPSMART[] = "AT+CWSTOPSMART";																//---���������Ƿ�ɹ�������Ҫ�ͷſ�����ռ���ڴ�
const char ESP8266_TCP_IP_STATUS[] = "AT+CIPSTATUS";																	//---��ѯ��������״̬����ӦOK
const char ESP8266_TCP_IP_DOMAIN[] = "AT+CIPDOMAIN";																	//---��������������
const char ESP8266_TCP_IP_CONNECT[] = "AT+CIPSTART";																	//---���ӷ�����
const char ESP8266_TCP_IP_SSL_SIZE[] = "AT+CIPSSLSIZE";																	//---����SSL�Ļ�������С
const char ESP8266_TCP_IP_SSL_CONF[] = "AT+CIPSSLCONF";																	//---����SSL Client
const char ESP8266_TCP_IP_SEND[] = "AT+CIPSEND";																		//---����͸��
const char ESP8266_TCP_IP_SENDX[] = "AT+CIPSENDX";																		//---�������ݣ��ﵽ����?���ȣ����������ַ� \0����������
const char ESP8266_TCP_IP_SENDBUF[] = "AT+CIPSENDBUF";																	//---����д?��TCP ��������
const char ESP8266_TCP_IP_BUFRESET[] = "AT+CIPBUFRESET";																//---���ü�����TCP �������棩
const char ESP8266_TCP_IP_BUFSTATUS[] = "AT+CIPBUFSTATUS";																//---��ѯ TCP ���������״̬
const char ESP8266_TCP_IP_CHECKSEQ[] = "AT+CIPCHECKSEQ";																//---��ѯд?�� TCP ���������ĳ���Ƿ�ɹ�����
const char ESP8266_TCP_IP_CLOSE[] = "AT+CIPCLOSE";																		//---�رմ���
const char ESP8266_TCP_IP_LIST_IP[] = "AT+CIFSR";																		//---��ѯ�豸��IP��ַ
const char ESP8266_TCP_IP_IP_MUX[] = "AT+CIPMUX";																		//---ʹ�ܶ�����
const char ESP8266_TCP_IP_SERVER_CONFIG[] = "AT+CIPSERVER";																//---����TCP������
const char ESP8266_TCP_IP_SERVER_MAX_COUNT[] = "AT+CIPSERVERMAXCOUT";													//---���÷�����?������?������?������
const char ESP8266_TCP_IP_MODE[] = "AT+CIPMODE";																		//---����͸��ģʽ��0---��ͨ����ģʽ��1---͸��ģʽ����?֧�� TCP �����Ӻ� UDP �̶�ͨ�ŶԶ˵����
const char ESP8266_TCP_IP_SAVE_TRANS_LINK[] = "AT+SAVETRANSLINK";														//---����͸�����ӵ� Flash
const char ESP8266_TCP_IP_SET_SERVER_TIMEOUT[] = "AT+CIPSTO";															//---������Ϊ TCP ������?ʱ�ĳ�ʱʱ��
const char ESP8266_TCP_IP_PING[] = "AT+PING";																			//---pin����
const char ESP8266_TCP_IP_UPDATE[] = "AT+CIUPDATE";																		//---ͨ��WiFi��������
const char ESP8266_TCP_IP_IPDINFO[] = "AT+CIPDINFO";																	//---����?��������ʱ��+IPD �Ƿ���ʾ�Զ� IP �Ͷ�?��
const char ESP8266_TCP_IP_RECVMODE[] = "AT+CIPRECVMODE";																//---���� TCP ����ģʽ
const char ESP8266_TCP_IP_RECVDATA[] = "AT+CIPRECVDATA";																//---TCP ��������ģʽ�£���ȡ����� TCP ����
const char ESP8266_TCP_IP_RECVLEN[] = "AT+CIPRECVLEN";																	//---TCP ��������ģʽ�£���ѯ���� TCP ���ݵ�?����TCP ����
const char ESP8266_TCP_IP_SNTPCFG[] = "AT+CIPSNTPCFG";																	//---����ʱ��� SNTP ������?
const char ESP8266_TCP_IP_SNTPTIME[] = "AT+CIPSNTPTIME";																//---��ѯ SNTP ʱ��
const char ESP8266_TCP_IP_DNS[] = "AT+CIPDNS";																			//---?�Զ��� DNS ������?

//===GPIO Commands
const char ESP8266_GPIO_PINMODE[] = "AT+PINMODE";																		//---���ö˿��������ģʽ
const char ESP8266_GPIO_PINWRITE[] = "AT+PINWRITE";																		//---���õĶ˿�����ߵ͵�ƽ
const char ESP8266_GPIO_PINREAD[] = "AT+PINREAD";																		//---��ȡ�˿ڵĵ�ƽ�ź�
////////////////////////////////////////////////////////////////////////////////////// 
//////////////////////////<<<AT������---����/////////////////////////////////////////// 
//////////////////////////////////////////////////////////////////////////////////////

//===���ݻ�����
UINT8_T g_ESP8266_RX_BUFFER[ESP8266_BUFFER_MAX_SIZE] = { 0 };															//---���ջ�����
UINT8_T g_ESP8266_TX_BUFFER[ESP8266_BUFFER_MAX_SIZE] = { 0 };															//---���ͻ�����
//===应答缓存�?
UINT8_T	g_ESP8266_ACK_BUFFER[ESP8266_ACK_BUFFER_MAX_SIZE]={0};

//===ESP8266��������
ESP8266_HandleType			g_Esp8266Device0={0};
pESP8266_HandleType			pEsp8266Device0=&g_Esp8266Device0;

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����ó�ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ESP8266_UART_Device0_Init(ESP8266_HandleType* ESP8266x, UINT32_T(*pFuncTimerTick)(void))
{
	//---״̬����
	ESP8266x->msgTask= ESP8266_TASK_IDLE;
	//---ģʽWIFI��APģʽ
	ESP8266x->msgWifiMode=ESP8266_AP;
	//---Ĭ����ѵʱ��
	ESP8266x->msgIntervalTime=0;
	//---ESP8266��Ӧ�������Ĵ�С
	ESP8266x->pMsgAck= g_ESP8266_ACK_BUFFER;
	//---ʹ�õ�ͨѶ����
	ESP8266x->pMsgUART= ESP8266_COMM_UART;
	//---��ʼ������
	UARTTask_Init(ESP8266x->pMsgUART, ESP8266_BUFFER_BASE_SIZE, g_ESP8266_RX_BUFFER, 0, ESP8266_BUFFER_BASE_SIZE, g_ESP8266_TX_BUFFER, 0, pFuncTimerTick);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ESP8266_UART_Device1_Init(ESP8266_HandleType* ESP8266x, UINT32_T(*pFuncTimerTick)(void))
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ESP8266_UART_Device2_Init(ESP8266_HandleType* ESP8266x, UINT32_T(*pFuncTimerTick)(void))
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��豸��ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ESP8266_UART_Init(ESP8266_HandleType *ESP8266x,UINT32_T(*pFuncTimerTick)(void))
{
	if ((ESP8266x != NULL) && (ESP8266x == ESP8266_TASK_ONE))
	{
		ESP8266_UART_Device0_Init(ESP8266x, pFuncTimerTick);
	}
	else if ((ESP8266x != NULL) && (ESP8266x == ESP8266_TASK_TWO))
	{
		ESP8266_UART_Device1_Init(ESP8266x, pFuncTimerTick);
	}
	else if ((ESP8266x != NULL) && (ESP8266x == ESP8266_TASK_THREE))
	{
		ESP8266_UART_Device2_Init(ESP8266x, pFuncTimerTick);
	}
	else
	{
		return  ERROR_1;
	}
	//---ע����ʱ����
	(pFuncTimerTick != NULL) ? (ESP8266x->pMsgTimeTick = pFuncTimerTick) : (ESP8266x->pMsgTimeTick = SysTickTask_GetTick);
	return OK_0;
}


void ESP8266_UART_LOG(UART_HandleType* UARTx, char* fmt, ...)
{
	#ifdef USE_ESP8266_LOG
	va_list args;
	va_start(args, fmt);
	UARTTask_PrintfLog(UARTx, fmt, args);
	va_end(args);
	#endif
}

///////////////////////////////////////////////////////////////////////////////
//////�?	数：
//////�?	能：
//////输入参数:
//////输出参数:
//////�?	明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ESP8266_UART_ACK(ESP8266_HandleType* ESP8266x, char* ack, UINT16_T intervalTime)
{
	//---设置查询时间
	ESP8266x->msgIntervalTime=intervalTime;
	//---设置当前任务状态是ACK模式
	ESP8266x->msgTask= ESP8266_TASK_QUERY_ACK;
	//---清空缓存�?
	memset(ESP8266x->pMsgAck, 0, ESP8266_ACK_BUFFER_MAX_SIZE);
	//---追加换行�?
	strcat((char*)ESP8266x->pMsgAck, ack);
	//---开始等待ACK
	ESP8266x->msgAckState= ESP8266_ACK_WAIT;
	//---指向应答结果的指正为�?
	ESP8266x->pMsgAckResult=NULL;
	//---记录当前的时�?
	ESP8266x->msgRecordTick=ESP8266x->pMsgTimeTick();
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////�?	数：
//////�?	能：查询应答
//////输入参数:
//////输出参数:
//////�?	明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ESP8266_UART_QueryAckTask(ESP8266_HandleType* ESP8266x)
{
	//---获取当前时间
	UINT32_T nowTime=ESP8266x->pMsgTimeTick();
	UINT32_T cnt=0;
	//---判断是不是需要应答数�?
	if (ESP8266x->msgTask== ESP8266_TASK_QUERY_ACK)
	{
		if (nowTime<ESP8266x->msgRecordTick)
		{
			cnt = (0xFFFFFFFF - ESP8266x->msgRecordTick + nowTime);
		}
		else
		{
			cnt= nowTime- ESP8266x->msgRecordTick;
		}
		//---判断应答是否超时
		if (cnt>ESP8266x->msgIntervalTime)
		{
			//---应答超时
			ESP8266x->msgAckState= ESP8266_ACK_TIMEOUT;
			//---任务空闲
			ESP8266x->msgTask = ESP8266_TASK_IDLE;
			//---检查回调函�?
			if (ESP8266x->pMsgAckTimeoutCallBack!=NULL)
			{
				//---执行回调函数
				ESP8266x->pMsgAckTimeoutCallBack(ESP8266x);
				//---回调函数执行完毕之后，进行注销
				ESP8266x->pMsgAckTimeoutCallBack=NULL;
				//---注销回调函数
				ESP8266x->pMsgAckErrCallBack = NULL;
				//---注销回调函数
				ESP8266x->pMsgAckOkCallBack = NULL;
			}
		}
		else
		{
			//---判断是否有数�?
			if (UARTTask_GetState(&(ESP8266x->pMsgUART->msgRxdHandle)) == UART_OK)
			{
				//---打印LOG信息
				ESP8266_LOG("%s%s","ACK:", ESP8266x->pMsgUART->msgRxdHandle.pMsgVal);
				//---有数据到�?判断是否和应答数据一�?
				ESP8266x->pMsgAckResult =strstr((char *)ESP8266x->pMsgUART->msgRxdHandle.pMsgVal,(char *)ESP8266x->pMsgAck);
				//---校验是否正确
				if (ESP8266x->pMsgAckResult==NULL)
				{
					//---有应答数据，但是应答结果异常
					ESP8266x->msgAckState = ESP8266_ACK_ERR;
					//---校验回调函数
					if (ESP8266x->pMsgAckErrCallBack!=NULL)
					{
						//---执行回调函数
						ESP8266x->pMsgAckErrCallBack(ESP8266x);
						//---回调函数执行完毕之后，进行注销
						ESP8266x->pMsgAckErrCallBack=NULL;
						//---注销回调函数
						ESP8266x->pMsgAckTimeoutCallBack = NULL;
						//---注销回调函数
						ESP8266x->pMsgAckOkCallBack = NULL;
					}
				}
				else
				{
					//---合格
					ESP8266x->msgAckState = ESP8266_ACK_OK;
					//---校验回调函数的执�?
					if (ESP8266x->pMsgAckOkCallBack!=NULL)
					{
						//---执行回调函数
						ESP8266x->pMsgAckOkCallBack(ESP8266x);
						//---回调函数执行完成之后，进行释�?
						ESP8266x->pMsgAckOkCallBack=NULL;
						//---注销回调函数
						ESP8266x->pMsgAckTimeoutCallBack = NULL;
						//---注销回调函数
						ESP8266x->pMsgAckErrCallBack = NULL;
					}
				}
				//---任务空闲
				ESP8266x->msgTask = ESP8266_TASK_IDLE;
			}
		}
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////�?	数：
//////�?	能：ESP8266的等待发送空�?
//////输入参数:
//////输出参数:
//////�?	明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ESP8266_UART_Write_WaitIdle(ESP8266_HandleType* ESP8266x)
{
	//---获取当前时间节拍
	UINT32_T nowTime = 0;
	UINT32_T oldTime = 0;
	UINT32_T cnt = 0;
	//---获取当前时间节拍
	oldTime = ESP8266x->pMsgTimeTick();
	//---检查发送状态，等待之前的数据发送完�?必须是空闲状态，总线上没有其他数据放
	while (UARTTask_Write_CheckIdle(ESP8266x->pMsgUART) != OK_0)
	{
		//--->>>加入超时机制---开�?
		//---当前时间
		nowTime = ESP8266x->pMsgTimeTick();
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
			//---发送发生超时错�?
			return ERROR_1;
		}
		//--->>>加入超时机制---开�?
		//---喂狗
		WDT_RESET();
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////�?	数：
//////�?	能：ESP8266发送数�?
//////输入参数:
//////输出参数:
//////�?	明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ESP8266_UART_Write(ESP8266_HandleType* ESP8266x,UINT8_T *pVal)
{
	return UARTTask_FillMode_WriteSTART(ESP8266x->pMsgUART, strlen((char*)pVal));
}

///////////////////////////////////////////////////////////////////////////////
//////�?	数：
//////�?	能：测试命令正确回调函数
//////输入参数:
//////输出参数:
//////�?	明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ESP8266_UART_TestAT_OkCallBack(ESP8266_HandleType* ESP8266x)
{
	ESP8266_LOG("%s%s\r\n", "Info:", "AT测试命令响应正确!");
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////�?	数：
//////�?	能：测试命令正确回调函数
//////输入参数:
//////输出参数:
//////�?	明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ESP8266_UART_TestAT_ErrCallBack(ESP8266_HandleType* ESP8266x)
{
	ESP8266_LOG("%s%s\r\n", "Info:", "AT测试命令响应错误!");
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////�?	数：
//////�?	能：测试命令正确回调函数
//////输入参数:
//////输出参数:
//////�?	明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ESP8266_UART_TestAT_TimeoutCallBack(ESP8266_HandleType* ESP8266x)
{
	ESP8266_LOG("%s%s\r\n", "Info:", "AT测试命令响应超时!");
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////�?	数：
//////�?	能：测试AT命令，回�?OK"
//////输入参数:
//////输出参数:
//////�?	明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ESP8266_UART_TestAT(ESP8266_HandleType* ESP8266x)
{
	//---校验发送空�?
	if (ESP8266_UART_Write_WaitIdle(ESP8266x) == OK_0)
	{
		//---恢复缓存区的首地址
		*(ESP8266x->pMsgUART->msgTxdHandle.pMsgVal) = ESP8266x->pMsgUART->msgTxdHandle.msgMsgValBaseAddr;
		//---清空缓存�?
		memset(ESP8266x->pMsgUART->msgTxdHandle.pMsgVal, 0, ESP8266_BUFFER_MAX_SIZE);
		//---将指定的字符串追加在结尾
		strcat((char*)ESP8266x->pMsgUART->msgTxdHandle.pMsgVal, ESP8266_AT_CMD_TEST);
		//---追加换行�?
		strcat((char*)ESP8266x->pMsgUART->msgTxdHandle.pMsgVal, "\r\n");
		//---打印LOG信息
		ESP8266_LOG("%s:\r\n%s", "CMD:", ESP8266x->pMsgUART->msgTxdHandle.pMsgVal);
		//---设置应答数据和应答时间应答的时间
		ESP8266_UART_ACK(ESP8266x,"OK",100);
		//---注册回调函数
		ESP8266x->pMsgAckOkCallBack = ESP8266_UART_TestAT_OkCallBack;
		//---注册回调函数
		ESP8266x->pMsgAckErrCallBack = ESP8266_UART_TestAT_ErrCallBack;
		//---注册回调函数
		ESP8266x->pMsgAckTimeoutCallBack = ESP8266_UART_TestAT_TimeoutCallBack;
		//---发送数�?
		return ESP8266_UART_Write(ESP8266x, ESP8266x->pMsgUART->msgTxdHandle.pMsgVal);
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////�?	数：
//////�?	能：
//////输入参数:
//////输出参数:
//////�?	明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ESP8266_UART_SoftReset_OkCallBack(ESP8266_HandleType* ESP8266x)
{
	ESP8266_LOG("%s%s\r\n", "Info:", "������λ������Ӧ��ȷ��");
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////�?	数：
//////�?	能：
//////输入参数:
//////输出参数:
//////�?	明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ESP8266_UART_SoftReset_ErrCallBack(ESP8266_HandleType* ESP8266x)
{
	ESP8266_LOG("%s%s\r\n", "Info:", "������λ������Ӧ����");
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////�?	数：
//////�?	能：
//////输入参数:
//////输出参数:
//////�?	明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ESP8266_UART_SoftReset_TimeoutCallBack(ESP8266_HandleType* ESP8266x)
{
	ESP8266_LOG("%s%s\r\n", "Info:", "������λ������Ӧ��ʱ��");
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////�?	数：
//////�?	能：软件命令复位设备，回�?OK"
//////输入参数:
//////输出参数:
//////�?	明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ESP8266_UART_SoftReset(ESP8266_HandleType* ESP8266x)
{
	//---校验发送空�?
	if (ESP8266_UART_Write_WaitIdle(ESP8266x)==OK_0)
	{
		//---恢复缓存区的首地址
		*(ESP8266x->pMsgUART->msgTxdHandle.pMsgVal) = ESP8266x->pMsgUART->msgTxdHandle.msgMsgValBaseAddr;
		//---清空缓存�?
		memset(ESP8266x->pMsgUART->msgTxdHandle.pMsgVal, 0, ESP8266_BUFFER_MAX_SIZE);
		//---将指定的字符串追加在结尾
		strcat((char *)ESP8266x->pMsgUART->msgTxdHandle.pMsgVal, ESP8266_AT_CMD_RESET);
		//---追加换行�?
		strcat((char *)ESP8266x->pMsgUART->msgTxdHandle.pMsgVal, "\r\n");
		//---打印LOG信息
		ESP8266_LOG("%s%s", "CMD:", ESP8266x->pMsgUART->msgTxdHandle.pMsgVal);
		//---设置应答数据和应答时间应答的时间
		ESP8266_UART_ACK(ESP8266x, "OK", 20000);
		//---注册回调函数
		ESP8266x->pMsgAckOkCallBack = ESP8266_UART_SoftReset_OkCallBack;
		//---注册回调函数
		ESP8266x->pMsgAckErrCallBack = ESP8266_UART_SoftReset_ErrCallBack;
		//---注册回调函数
		ESP8266x->pMsgAckTimeoutCallBack = ESP8266_UART_SoftReset_ErrCallBack;		
		//---发送数�?
		return ESP8266_UART_Write(ESP8266x, ESP8266x->pMsgUART->msgTxdHandle.pMsgVal);
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////�?	数：
//////�?	能：
//////输入参数:
//////输出参数:
//////�?	明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ESP8266_UART_GetVersionInfo_OkCallBack(ESP8266_HandleType* ESP8266x)
{
	ESP8266_LOG("%s%s\r\n", "Info:", "获取版本信息命令响应正确!");
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////�?	数：
//////�?	能：
//////输入参数:
//////输出参数:
//////�?	明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ESP8266_UART_GetVersionInfo_ErrCallBack(ESP8266_HandleType* ESP8266x)
{
	ESP8266_LOG("%s%s\r\n", "Info:", "获取版本信息命令响应错误!");
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////�?	数：
//////�?	能：
//////输入参数:
//////输出参数:
//////�?	明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ESP8266_UART_GetVersionInfo_TimeoutCallBack(ESP8266_HandleType* ESP8266x)
{
	ESP8266_LOG("%s%s\r\n", "Info:", "获取版本信息命令响应超时!");
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////�?	数：
//////�?	能：获取版本信息，回应版本信息，并以“OK”结�?
//////输入参数:
//////输出参数:
//////�?	明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ESP8266_UART_GetVersionInfo(ESP8266_HandleType* ESP8266x)
{
	//---校验发送空�?
	if (ESP8266_UART_Write_WaitIdle(ESP8266x) == OK_0)
	{
		//---恢复缓存区的首地址
		*(ESP8266x->pMsgUART->msgTxdHandle.pMsgVal) = ESP8266x->pMsgUART->msgTxdHandle.msgMsgValBaseAddr;
		//---清空缓存�?
		memset(ESP8266x->pMsgUART->msgTxdHandle.pMsgVal, 0, ESP8266_BUFFER_MAX_SIZE);
		//---将指定的字符串追加在结尾
		strcat((char*)ESP8266x->pMsgUART->msgTxdHandle.pMsgVal, ESP8266_AT_CMD_VERSION);
		//---追加换行�?
		strcat((char*)ESP8266x->pMsgUART->msgTxdHandle.pMsgVal, "\r\n");
		//---打印LOG信息
		ESP8266_LOG("%s%s", "CMD:", ESP8266x->pMsgUART->msgTxdHandle.pMsgVal);
		//---设置应答数据和应答时间应答的时间
		ESP8266_UART_ACK(ESP8266x, "OK", 100);
		//---注册回调函数
		ESP8266x->pMsgAckOkCallBack = ESP8266_UART_GetVersionInfo_OkCallBack;
		//---注册回调函数
		ESP8266x->pMsgAckErrCallBack = ESP8266_UART_GetVersionInfo_ErrCallBack;
		//---注册回调函数
		ESP8266x->pMsgAckTimeoutCallBack = ESP8266_UART_GetVersionInfo_TimeoutCallBack;
		//---发送数�?
		return ESP8266_UART_Write(ESP8266x, ESP8266x->pMsgUART->msgTxdHandle.pMsgVal);
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////�?	数：
//////�?	能：回显功能开启与关闭，并以“OK”结�?
//////输入参数:
//////输出参数:
//////�?	明：关闭回显之后，ESP8266不在返回发送的指令
//////////////////////////////////////////////////////////////////////////////
UINT8_T ESP8266_UART_DisplayFunction(ESP8266_HandleType* ESP8266x,UINT8_T isClosed)
{
	//---校验发送空�?
	if (ESP8266_UART_Write_WaitIdle(ESP8266x) == OK_0)
	{
		//---恢复缓存区的首地址
		*(ESP8266x->pMsgUART->msgTxdHandle.pMsgVal) = ESP8266x->pMsgUART->msgTxdHandle.msgMsgValBaseAddr;
		//---清空缓存�?
		memset(ESP8266x->pMsgUART->msgTxdHandle.pMsgVal, 0, ESP8266_BUFFER_MAX_SIZE);
		//---将指定的字符串追加在结尾
		strcat((char*)ESP8266x->pMsgUART->msgTxdHandle.pMsgVal, (isClosed == 0) ? (ESP8266_AT_CMD_ECHO_OPEN) : (ESP8266_AT_CMD_ECHO_CLOSE));
		//---追加换行�?
		strcat((char*)ESP8266x->pMsgUART->msgTxdHandle.pMsgVal, "\r\n");
		//---打印LOG信息
		ESP8266_LOG("%s%s", "CMD:", ESP8266x->pMsgUART->msgTxdHandle.pMsgVal);
		//---设置应答数据和应答时间应答的时间
		ESP8266_UART_ACK(ESP8266x, "OK", 100);
		//---发送数�?
		return ESP8266_UART_Write(ESP8266x, ESP8266x->pMsgUART->msgTxdHandle.pMsgVal);
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////�?	数：
//////�?	能：恢复出厂设置,回应“OK�?
//////输入参数:
//////输出参数:
//////�?	明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ESP8266_UART_RESTORE(ESP8266_HandleType* ESP8266x)
{
	//---校验发送空�?
	if (ESP8266_UART_Write_WaitIdle(ESP8266x) == OK_0)
	{
		//---恢复缓存区的首地址
		*(ESP8266x->pMsgUART->msgTxdHandle.pMsgVal) = ESP8266x->pMsgUART->msgTxdHandle.msgMsgValBaseAddr;
		//---清空缓存�?
		memset(ESP8266x->pMsgUART->msgTxdHandle.pMsgVal, 0, ESP8266_BUFFER_MAX_SIZE);
		//---将指定的字符串追加在结尾
		strcat((char*)ESP8266x->pMsgUART->msgTxdHandle.pMsgVal,ESP8266_AT_CMD_RESTORE);
		//---追加换行�?
		strcat((char*)ESP8266x->pMsgUART->msgTxdHandle.pMsgVal, "\r\n");
		//---打印LOG信息
		ESP8266_LOG("%s%s", "CMD:", ESP8266x->pMsgUART->msgTxdHandle.pMsgVal);
		//---设置应答数据和应答时间应答的时间
		ESP8266_UART_ACK(ESP8266x, "OK", 100);
		//---发送数�?
		return ESP8266_UART_Write(ESP8266x, ESP8266x->pMsgUART->msgTxdHandle.pMsgVal);
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////�?	数：
//////�?	能：查询应答中包含WIFI模式信息
//////输入参数:
//////输出参数:
//////�?	明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T ESP8266_UART_QueryAck_WifiMode(ESP8266_HandleType* ESP8266x)
{	
	//---有数据到�?判断是否和应答数据一�?
	char *pAck = strstr((char*)ESP8266x->pMsgUART->msgRxdHandle.pMsgVal, "+CWMODE");
	//---校验是否正确
	if (ESP8266x->pMsgAckResult == NULL)
	{
		//---有应答数据，但是应答结果异常
		ESP8266x->msgAckState = ESP8266_ACK_ERR;
	}
	else
	{
		pAck=strstr(pAck, ":");
		//---校验结果
		if (pAck==NULL)
		{
			//---应答结果正确，但是应答数内容错误
			ESP8266x->msgAckState = ESP8266_ACK_ERR_INFO;
		}
		else
		{
			pAck++;
			//---获取Wifi模式的结�?
			ESP8266x->msgWifiMode=*pAck-0x30;
			//---合格
			ESP8266x->msgAckState = ESP8266_ACK_OK;
		}		
	}
	//---任务空闲
	ESP8266x->msgTask = ESP8266_TASK_IDLE;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////�?	数：
//////�?	能：设置Wifi工作模式�?
//////输入参数:  mode---0，查询；1，sta模式�?，ap模式�?，ap+sta模式
//////输出参数:
//////�?	明：查询方式返回+CWMODE�?模式> OK；其他返回OK
//////////////////////////////////////////////////////////////////////////////
UINT8_T ESP8266_UART_WifiMode(ESP8266_HandleType* ESP8266x,UINT8_T mode)
{
	//---校验发送空�?
	if (ESP8266_UART_Write_WaitIdle(ESP8266x) == OK_0)
	{
		char *wifiMode="?\r\n";
		//---恢复缓存区的首地址
		*(ESP8266x->pMsgUART->msgTxdHandle.pMsgVal) = ESP8266x->pMsgUART->msgTxdHandle.msgMsgValBaseAddr;
		//---清空缓存�?
		memset(ESP8266x->pMsgUART->msgTxdHandle.pMsgVal, 0, ESP8266_BUFFER_MAX_SIZE);
		//---将指定的字符串追加在结尾
		strcat((char*)ESP8266x->pMsgUART->msgTxdHandle.pMsgVal, ESP8266_AT_WIFI_MODE);
		//---STA模式
		if (mode== ESP8266_STA)
		{
			*wifiMode='1';
			ESP8266x->msgWifiMode=ESP8266_STA;
		}
		//---AP模式
		else if (mode == ESP8266_AP)
		{
			*wifiMode = '2';
			ESP8266x->msgWifiMode = ESP8266_AP;
		}
		//---AP+STA模式
		else if (mode == ESP8266_STA_AP)
		{
			*wifiMode = '3';
			ESP8266x->msgWifiMode = ESP8266_STA_AP;
		}
		//---查询模式
		else 
		{
			*wifiMode = '?';
		}
		//---追加换行�?
		strcat((char*)ESP8266x->pMsgUART->msgTxdHandle.pMsgVal, wifiMode);
		//---打印LOG信息
		ESP8266_LOG("%s%s","CMD:", ESP8266x->pMsgUART->msgTxdHandle.pMsgVal);
		//---设置应答数据和应答时间应答的时间
		ESP8266_UART_ACK(ESP8266x, "OK", 100);
		//---注册回调函数
		ESP8266x->pMsgAckOkCallBack= ESP8266_UART_QueryAck_WifiMode;
		//---发送数�?
		return ESP8266_UART_Write(ESP8266x, ESP8266x->pMsgUART->msgTxdHandle.pMsgVal);
	}
	return ERROR_1;
}




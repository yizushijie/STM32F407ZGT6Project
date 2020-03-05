#ifndef RFASK_TASK_H_
#define RFASK_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "rfask_lib.h"
	#include "timer_task.h"
	#include "wm8510_task.h"
	#include "uart_task.h"
	#include "power_task.h"
	#include "adc_task.h"
	#include "led_task.h"
	#include "key_task.h"
	#include "decode_task.h"
	#include "rfask_eeprom.h" 
	//////////////////////////////////////////////////////////////////////////////////////
	//===��ȡ����ʱ��Ͱ汾��Ϣ
	#define CMD_RFASK_CMD1_VERSIOM									0x00
	//===����WM8510�����---������
	#define CMD_RFASK_CMD1_FREQ_WM8510								0x01
	//===����WM8510���Ƶ��
	#define CMD_RFASK_CMD2_SET_WM8510								0x01
	//===��ȡWM8510�����Ƶ��
	#define CMD_RFASK_CMD2_GET_WM8510								0x02
	//===��λWM8510
	#define CMD_RFASK_CMD2_RESET_WM8510								0x03
	//===ʱ�����ͨ��A��ʹ�ܿ���
	#define CMD_RFASK_CMD2_CHANNELA_WM8510							0x04
	//===ʱ�����ͨ��B��ʹ�ܿ���
	#define CMD_RFASK_CMD2_CHANNELB_WM8510							0x05
	//===ʱ�����ͨ��C��ʹ�ܿ���
	#define CMD_RFASK_CMD2_CHANNELC_WM8510							0x06
	//===ʱ�����ͨ��D��ʹ�ܿ���
	#define CMD_RFASK_CMD2_CHANNELD_WM8510							0x07
	//===ʱ���������ͨ����ʹ�ܿ���
	#define CMD_RFASK_CMD2_CHANNELS_WM8510							0x08
	//===����Ĭ��Ƶ�ʵ����
	#define CMD_RFASK_CMD1_YSEL_FREQ								0x02
	//===����Ԥ��Ƶ�ʵ�1
	#define CMD_RFASK_CMD2_YSEL1_FREQ_SET							0x01
	//===����Ԥ��Ƶ�ʵ�2
	#define CMD_RFASK_CMD2_YSEL2_FREQ_SET							0x02
	//===����Ԥ��Ƶ�ʵ�3
	#define CMD_RFASK_CMD2_YSEL3_FREQ_SET							0x03
	//===����Ԥ��Ƶ�ʵ�4
	#define CMD_RFASK_CMD2_YSEL4_FREQ_SET							0x04
	//===��ȡԤ��Ƶ�ʵ�1
	#define CMD_RFASK_CMD2_YSEL1_FREQ_GET							0x05
	//===��ȡԤ��Ƶ�ʵ�2
	#define CMD_RFASK_CMD2_YSEL2_FREQ_GET							0x06
	//===��ȡԤ��Ƶ�ʵ�3
	#define CMD_RFASK_CMD2_YSEL3_FREQ_GET							0x07
	//===��ȡԤ��Ƶ�ʵ�4
	#define CMD_RFASK_CMD2_YSEL4_FREQ_GET							0x08
	//===��������Ԥ��Ƶ�ʵ�
	#define CMD_RFASK_CMD2_YSEL_FREQ_SET							0x09
	//===��ȡ����Ԥ��Ƶ�ʵ�
	#define CMD_RFASK_CMD2_YSEL_FREQ_GET							0x0A
	//===����Ԥ��Ƶ�ʵ�1���
	#define CMD_RFASK_CMD2_YSEL1_FREQ_OUT							0x0B
	//===����Ԥ��Ƶ�ʵ�2���
	#define CMD_RFASK_CMD2_YSEL2_FREQ_OUT							0x0C
	//===����Ԥ��Ƶ�ʵ�3���
	#define CMD_RFASK_CMD2_YSEL3_FREQ_OUT							0x0D
	//===����Ԥ��Ƶ�ʵ�4���
	#define CMD_RFASK_CMD2_YSEL4_FREQ_OUT							0x0E
	//===Ƶ�ʵ������ԣ���������������
	#define CMD_RFASK_CMD1_FREQ_CURRENT								0x03
	//===�豸����
	#define CMD_RFASK_CMD1_FREQ_CURRENT_DEVICE_TYPE_GET				0x01
	//===��������
	#define CMD_RFASK_CMD1_FREQ_CURRENT_SAMPLE_RES_GET				0x02
	//===�Ŵ���
	#define CMD_RFASK_CMD1_FREQ_CURRENT_AMP_TIMES_GET				0x03
	//===�豸����
	#define CMD_RFASK_CMD1_FREQ_CURRENT_DEVICE_TYPE_SET				0x04
	//===��������
	#define CMD_RFASK_CMD1_FREQ_CURRENT_SAMPLE_RES_SET				0x05
	//===�Ŵ���
	#define CMD_RFASK_CMD1_FREQ_CURRENT_AMP_TIMES_SET				0x06
	//===�豸�Ļ���������ȡ
	#define CMD_RFASK_CMD1_FREQ_CURRENT_DEVICE_GET					0x07
	//===�豸�Ļ�����������
	#define CMD_RFASK_CMD1_FREQ_CURRENT_DEVICE_SET					0x08
	//===��һ��Ƶ�ʵ���ɨ���ѹ��	
	#define CMD_RFASK_CMD1_FREQ_CURRENT_POINT_ONE					0x04
	//===�ڶ���Ƶ�ʵ���ɨ���ѹ��
	#define CMD_RFASK_CMD1_FREQ_CURRENT_POINT_TWO					0x05
	//===��ȡƵ�ʲ���
	#define CMD_RFASK_CMD1_FREQ_CURRENT_POINT_FREQ_GET				0x01
	//===����Ƶ�ʲ���
	#define CMD_RFASK_CMD1_FREQ_CURRENT_POINT_FREQ_SET				0x02
	//===��ȡ��������
	#define CMD_RFASK_CMD1_FREQ_CURRENT_POINT_CURRENT_GET			0x03
	//===���õ�������
	#define CMD_RFASK_CMD1_FREQ_CURRENT_POINT_CURRENT_SET			0x04
	//===Ƶ�ʵ���ɨ�蹤��
	#define CMD_RFASK_CMD1_FREQ_CURRENT_POINT_DO					0x05

	//===����������ȵĵ�ĸ���	
	#define RFASK_FREQ_CURRENT_CONT_EQUAL_POINT_MAX_NUM				3
	
	//===��������
	void     RFASKTask_Init(RFASK_HandleType *rfask, AT24CXX_HandleType* AT24CXXx);
	UINT32_T RFASKTask_CalcXTAL(RFASK_HandleType *rfask, UINT32_T rfX100MHz);
	UINT8_T  RFASKTask_SetDeviceType(RFASK_HandleType *rfask, UINT8_T deviceType);
	UINT32_T RFASKTask_GetDeviceType(RFASK_HandleType *rfask);
	UINT32_T RFASKTask_SetClockFreq(RFASK_HandleType *rfask, WM8510_HandleType *WM8510x, UINT32_T rfX100MHz);
	UINT8_T  RFASKTask_WM8510Task(UART_HandleType*UARTx, WM8510_HandleType *WM8510x, AT24CXX_HandleType* AT24CXXx);
	UINT8_T  RFASKTask_YSELTask(UART_HandleType*UARTx, RFASK_HandleType *rfask, WM8510_HandleType *WM8510x, AT24CXX_HandleType* AT24CXXx);
	UINT8_T  RFASKTask_ActivateSites(RFASK_HandleType *rfask, UINT8_T activateSites);
	UINT8_T  RFASKTask_SitesCurrent(RFASK_HandleType *rfask);
	UINT8_T  RFASKTask_SetFreqCurrentPointCmd(FREQ_CURRENT_HandleType *rfaskFreqCurrent, UINT8_T cmd);
	UINT8_T  RFASKTask_FreqCurrentScan(UART_HandleType*UARTx, RFASK_HandleType *rfask, FREQ_CURRENT_HandleType *rfaskFreqCurrent, WM8510_HandleType *WM8510x);
	UINT8_T  RFASKTask_HandlerTask(UART_HandleType*UARTx, RFASK_HandleType *rfask, WM8510_HandleType *WM8510x, AT24CXX_HandleType* AT24CXXx);
	UINT8_T  RFASKTask_ScanYSEL(void);
	UINT8_T  RFASKTask_Task(UART_HandleType*UARTx, RFASK_HandleType *rfask, WM8510_HandleType *WM8510x, AT24CXX_HandleType* AT24CXXx);
	UINT8_T  RFASKTask_KeyTask(UART_HandleType*UARTx, RFASK_HandleType *rfask, WM8510_HandleType *WM8510x, UINT8_T activateSites);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*RFASK_TASK_H_ */
#ifndef RTC_CFG_H_
#define RTC_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	//////////////////////////////////////////////////////////////////////////////////////

	//===�ṹ�嶨��
	typedef struct _SYS_RTC_HandleType			SYS_RTC_HandleType;
	//===����ָ��ṹ��
	typedef struct _SYS_RTC_HandleType			* pSYS_RTC_HandleType;

	//===�������RTCʱ��
	struct _SYS_RTC_HandleType
	{
		RTC_HandleType	msgRTC;																							//---ʹ�õ�RTC
		UINT16_T		msgWatchSpanDays;																				//---��ض����췢���仯
		UINT8_T			msgDay;																							//---��ǰ�µ�����
		UINT8_T			msgMonth;																						//---��ǰ��
		UINT8_T			msgWatchMode;																					//---�Ƿ�ȡ����أ�0---ȡ����أ�1---ʵʱ��أ�2---ˢ�¼��
		UINT8_T			msgHwMode;																						//---����ģʽ��Ĭ�������ģ��---0��Ӳ��ģʽ---1
	};

	//===�ⲿ���ýӿ�
	extern  SYS_RTC_HandleType						g_SysSoftRTC;
	extern  pSYS_RTC_HandleType					pSysSoftRTC;

	extern  SYS_RTC_HandleType						g_SysHWRTC;
	extern  pSYS_RTC_HandleType					pSysHWRTC;

	//===��������
	void SysRTC_SoftRTCInit(SYS_RTC_HandleType* RTCx, UINT16_T spanDays, UINT8_T watchaMode);
	UINT8_T SysRTC_CalcWeekDay(RTC_HandleType*RTCx);
	UINT8_T SysRTC_RealTimeWatch(SYS_RTC_HandleType* RTCx);
	UINT8_T SysRTC_RefreshWatch(SYS_RTC_HandleType* RTCx);
	UINT8_T SysRTC_SetWatchTime(SYS_RTC_HandleType* RTCx, UINT16_T spanDays);
	UINT8_T SysRTC_ClearWatch(SYS_RTC_HandleType* RTCx);
	UINT8_T SysRTC_WatchTask(SYS_RTC_HandleType* RTCx);
	UINT8_T SysRTC_SoftRTCTask(SYS_RTC_HandleType* RTCx, UINT32_T rtcSecond);
	UINT8_T SysRTC_HardRTCInit(SYS_RTC_HandleType* RTCx, UINT16_T spanDays, UINT8_T watchaMode);
	UINT8_T SysRTC_HardRTCSetTime(SYS_RTC_HandleType* RTCx, UINT8_T hour, UINT8_T minute, UINT8_T second);
	UINT8_T SysRTC_HardRTCGetTime(SYS_RTC_HandleType* RTCx);
	UINT8_T SysRTC_HardRTCSetDate(SYS_RTC_HandleType* RTCx, UINT8_T year, UINT8_T month, UINT8_T day);
	UINT8_T SysRTC_HardRTCGetDate(SYS_RTC_HandleType* RTCx);
	UINT8_T SysRTC_HardRTCSetCentury(SYS_RTC_HandleType* RTCx, UINT8_T century);
	UINT8_T SysRTC_HardRTCGetCentury(SYS_RTC_HandleType* RTCx);
	UINT8_T SysRTC_HardRTCGetRTC(SYS_RTC_HandleType* RTCx);
	UINT8_T SysRTC_HardRTCTask(SYS_RTC_HandleType* RTCx);
	UINT8_T SysRTC_RTCTask(SYS_RTC_HandleType* RTCx, UINT32_T rtcSecond);
	UINT8_T SysRTC_RTCInit(SYS_RTC_HandleType* RTCx, UINT16_T spanDays, UINT8_T watchaMode, UINT8_T isHW);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*RTC_CFG_H_ */
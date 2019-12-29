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
	typedef struct _SYS_RTC_HandlerType			SYS_RTC_HandlerType;
	//===����ָ��ṹ��
	typedef struct _SYS_RTC_HandlerType			* pSYS_RTC_HandlerType;

	//===�������RTCʱ��
	struct _SYS_RTC_HandlerType
	{
		RTC_HandlerType msgRTC;					//---ʹ�õ�RTC
		VLTUINT16_T     msgWatchSpanDays;		//---��ض����췢���仯
		VLTUINT8_T		msgDay;					//---��ǰ�µ�����
		VLTUINT8_T		msgMonth;				//---��ǰ��
		VLTUINT8_T      msgWatchMode;			//---�Ƿ�ȡ����أ�0---ȡ����أ�1---ʵʱ��أ�2---ˢ�¼��
	};

	//===�ⲿ���ýӿ�
	extern  SYS_RTC_HandlerType						g_SysSoftRTC;
	extern  pSYS_RTC_HandlerType					pSysSoftRTC;

	extern  SYS_RTC_HandlerType						g_SysHWRTC;
	extern  pSYS_RTC_HandlerType					pSysHWRTC;

	//===��������
	void SysRTC_SoftRTCInit(SYS_RTC_HandlerType* RTCx, UINT16_T spanDays, UINT8_T watchaMode);
	UINT8_T SysRTC_CalcWeekDay(RTC_HandlerType*RTCx);
	UINT8_T SysRTC_RealTimeWatch(SYS_RTC_HandlerType* RTCx);
	UINT8_T SysRTC_RefreshWatch(SYS_RTC_HandlerType* RTCx);
	UINT8_T SysRTC_SetWatchTime(SYS_RTC_HandlerType* RTCx, UINT16_T spanDays);
	UINT8_T SysRTC_ClearWatch(SYS_RTC_HandlerType* RTCx);
	UINT8_T SysRTC_WatchTask(SYS_RTC_HandlerType* RTCx);
	UINT8_T SysRTC_SoftRTCTask(SYS_RTC_HandlerType* RTCx, UINT32_T rtcSecond);
	UINT8_T SysRTC_HardRTCInit(SYS_RTC_HandlerType* RTCx, UINT16_T spanDays, UINT8_T watchaMode);
	UINT8_T SysRTC_HardRTCSetTime(SYS_RTC_HandlerType* RTCx, UINT8_T hour, UINT8_T minute, UINT8_T second);
	UINT8_T SysRTC_HardRTCGetTime(SYS_RTC_HandlerType* RTCx);
	UINT8_T SysRTC_HardRTCSetDate(SYS_RTC_HandlerType* RTCx, UINT8_T year, UINT8_T month, UINT8_T day);
	UINT8_T SysRTC_HardRTCGetDate(SYS_RTC_HandlerType* RTCx);
	UINT8_T SysRTC_HardRTCSetCentury(SYS_RTC_HandlerType* RTCx, UINT8_T century);
	UINT8_T SysRTC_HardRTCGetCentury(SYS_RTC_HandlerType* RTCx);
	UINT8_T SysRTC_HardRTCGetRTC(SYS_RTC_HandlerType* RTCx);
	UINT8_T SysRTC_HardRTCTask(SYS_RTC_HandlerType* RTCx);
	UINT8_T SysRTC_RTCTask(SYS_RTC_HandlerType* RTCx, UINT32_T rtcSecond, UINT8_T isHW);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*RTC_CFG_H_ */
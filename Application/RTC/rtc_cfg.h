#ifndef RTC_CFG_H_
#define RTC_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	//////////////////////////////////////////////////////////////////////////////////////

	//===结构体定义
	typedef struct _SYS_RTC_HandlerType			SYS_RTC_HandlerType;
	//===定义指针结构体
	typedef struct _SYS_RTC_HandlerType			* pSYS_RTC_HandlerType;

	//===定义软件RTC时钟
	struct _SYS_RTC_HandlerType
	{
		RTC_HandlerType msgRTC;					//---使用的RTC
		VLTUINT16_T     msgWatchSpanDays;		//---监控多少天发生变化
		VLTUINT8_T		msgDay;					//---当前月的天数
		VLTUINT8_T		msgMonth;				//---当前月
		VLTUINT8_T      msgWatchMode;			//---是否取消监控，0---取消监控，1---实时监控，2---刷新监控
	};

	//===外部调用接口
	extern  SYS_RTC_HandlerType						g_SysSoftRTC;
	extern  pSYS_RTC_HandlerType					pSysSoftRTC;

	extern  SYS_RTC_HandlerType						g_SysHWRTC;
	extern  pSYS_RTC_HandlerType					pSysHWRTC;

	//===函数定义
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
#ifndef RTC_TASK_H_
#define RTC_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "rtc_lib.h"
	//////////////////////////////////////////////////////////////////////////////////////
	
	//===º¯Êý¶¨Òå
	void SysRTCTask_SoftRTCInit(SYS_RTC_HandlerType* RTCx, UINT16_T spanDays, UINT8_T watchaMode);
	void SysRTCTask_SoftCalcRTCTask(SYS_RTC_HandlerType*RTCx, UINT32_T rtcSecond);
	UINT8_T SysRTCTask_CalcWeekDay(RTC_HandlerType*RTCx);
	UINT8_T SysRTCTask_RealTimeWatch(SYS_RTC_HandlerType* RTCx);
	UINT8_T SysRTCTask_RefreshWatch(SYS_RTC_HandlerType* RTCx);
	UINT8_T SysRTCTask_SetWatchTime(SYS_RTC_HandlerType* RTCx, UINT16_T spanDays);
	UINT8_T SysRTCTask_ClearWatch(SYS_RTC_HandlerType* RTCx);
	UINT8_T SysRTCTask_WatchTask(SYS_RTC_HandlerType* RTCx);
	UINT8_T SysRTCTask_SoftRTCTask(SYS_RTC_HandlerType* RTCx, UINT32_T rtcSecond);
	UINT8_T SysRTCTask_HardRTCInit(SYS_RTC_HandlerType* RTCx, UINT16_T spanDays, UINT8_T watchaMode);
	UINT8_T SysRTCTask_HardRTCSetTime(SYS_RTC_HandlerType* RTCx, UINT8_T hour, UINT8_T minute, UINT8_T second);
	UINT8_T SysRTCTask_HardRTCGetTime(SYS_RTC_HandlerType* RTCx);
	UINT8_T SysRTCTask_HardRTCSetDate(SYS_RTC_HandlerType* RTCx, UINT8_T year, UINT8_T month, UINT8_T day);
	UINT8_T SysRTCTask_HardRTCGetDate(SYS_RTC_HandlerType* RTCx);
	UINT8_T SysRTCTask_HardRTCSetCentury(SYS_RTC_HandlerType* RTCx, UINT8_T century);
	UINT8_T SysRTCTask_HardRTCGetCentury(SYS_RTC_HandlerType* RTCx);
	UINT8_T SysRTCTask_HardRTCGetRTC(SYS_RTC_HandlerType* RTCx);
	UINT8_T SysRTCTask_HardRTCTask(SYS_RTC_HandlerType* RTCx);
	UINT8_T SysRTCTask_RTCTask(SYS_RTC_HandlerType* RTCx, UINT32_T rtcSecond, UINT8_T isHW);

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*RTC_TASK_H_ */
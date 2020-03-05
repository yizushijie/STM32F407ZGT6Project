#ifndef RTC_LIB_H_
#define RTC_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "rtc_cfg.h"
	//////////////////////////////////////////////////////////////////////////////////////
	
	//===º¯Êý¶¨Òå
	UINT8_T SysRTCLib_SoftRTCInit(SYS_RTC_HandleType* RTCx, UINT16_T spanDays, UINT8_T watchaMode);
	UINT8_T SysRTCLib_CalcWeekDay(RTC_HandleType*RTCx);
	UINT8_T SysRTCLib_RealTimeWatch(SYS_RTC_HandleType* RTCx);
	UINT8_T SysRTCLib_RefreshWatch(SYS_RTC_HandleType* RTCx);
	UINT8_T SysRTCLib_SetWatchTime(SYS_RTC_HandleType* RTCx, UINT16_T spanDays);
	UINT8_T SysRTCLib_ClearWatch(SYS_RTC_HandleType* RTCx);
	UINT8_T SysRTCLib_WatchTask(SYS_RTC_HandleType* RTCx);
	UINT8_T SysRTCLib_SoftRTCTask(SYS_RTC_HandleType* RTCx, UINT32_T rtcSecond);
	UINT8_T SysRTCLib_HardRTCInit(SYS_RTC_HandleType* RTCx, UINT16_T spanDays, UINT8_T watchaMode);
	UINT8_T SysRTCLib_HardRTCSetTime(SYS_RTC_HandleType* RTCx, UINT8_T hour, UINT8_T minute, UINT8_T second);
	UINT8_T SysRTCLib_HardRTCGetTime(SYS_RTC_HandleType* RTCx);
	UINT8_T SysRTCLib_HardRTCSetDate(SYS_RTC_HandleType* RTCx, UINT8_T year, UINT8_T month, UINT8_T day);
	UINT8_T SysRTCLib_HardRTCGetDate(SYS_RTC_HandleType* RTCx);
	UINT8_T SysRTCLib_HardRTCSetCentury(SYS_RTC_HandleType* RTCx, UINT8_T century);
	UINT8_T SysRTCLib_HardRTCGetCentury(SYS_RTC_HandleType* RTCx);
	UINT8_T SysRTCLib_HardRTCGetRTC(SYS_RTC_HandleType* RTCx);
	UINT8_T SysRTCLib_HardRTCTask(SYS_RTC_HandleType* RTCx);
	UINT8_T SysRTCLib_RTCTask(SYS_RTC_HandleType* RTCx, UINT32_T rtcSecond);
	UINT8_T SysRTCLib_RTCInit(SYS_RTC_HandleType* RTCx, UINT16_T spanDays, UINT8_T watchaMode, UINT8_T isHW);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*RTC_LIB_H_ */
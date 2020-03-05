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
	typedef struct _SYS_RTC_HandleType			SYS_RTC_HandleType;
	//===定义指针结构体
	typedef struct _SYS_RTC_HandleType			* pSYS_RTC_HandleType;

	//===定义软件RTC时钟
	struct _SYS_RTC_HandleType
	{
		RTC_HandleType	msgRTC;																							//---使用的RTC
		UINT16_T		msgWatchSpanDays;																				//---监控多少天发生变化
		UINT8_T			msgDay;																							//---当前月的天数
		UINT8_T			msgMonth;																						//---当前月
		UINT8_T			msgWatchMode;																					//---是否取消监控，0---取消监控，1---实时监控，2---刷新监控
		UINT8_T			msgHwMode;																						//---工作模式，默认是软件模拟---0，硬件模式---1
	};

	//===外部调用接口
	extern  SYS_RTC_HandleType						g_SysSoftRTC;
	extern  pSYS_RTC_HandleType					pSysSoftRTC;

	extern  SYS_RTC_HandleType						g_SysHWRTC;
	extern  pSYS_RTC_HandleType					pSysHWRTC;

	//===函数定义
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
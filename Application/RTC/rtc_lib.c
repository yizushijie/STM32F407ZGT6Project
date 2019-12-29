#include "rtc_lib.h"

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�������������ʱ����㵱ǰϵͳʱ��,������ϵͳ��λ��ʱ��
//////�������: watchaMode---0-����أ�1-ʵʱ��أ�2-ˢ�¼��
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void SysRTCLib_SoftRTCInit(SYS_RTC_HandlerType* RTCx, UINT16_T spanDays, UINT8_T watchaMode)
{
	SysRTC_SoftRTCInit(RTCx,spanDays, watchaMode);
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTCLib_CalcWeekDay(RTC_HandlerType*RTCx)
{
	return SysRTC_CalcWeekDay(RTCx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTCLib_RealTimeWatch(SYS_RTC_HandlerType* RTCx)
{
	return SysRTC_RealTimeWatch(RTCx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTCLib_RefreshWatch(SYS_RTC_HandlerType* RTCx)
{
	return SysRTC_RefreshWatch(RTCx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTCLib_SetWatchTime(SYS_RTC_HandlerType* RTCx, UINT16_T spanDays)
{
	return SysRTC_SetWatchTime(RTCx, spanDays);
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTCLib_ClearWatch(SYS_RTC_HandlerType* RTCx)
{
	return SysRTC_ClearWatch(RTCx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTCLib_WatchTask(SYS_RTC_HandlerType* RTCx)
{
	return SysRTC_WatchTask(RTCx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTCLib_SoftRTCTask(SYS_RTC_HandlerType* RTCx, UINT32_T rtcSecond)
{
	return SysRTC_SoftRTCTask( RTCx, rtcSecond);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTCLib_HardRTCInit(SYS_RTC_HandlerType* RTCx, UINT16_T spanDays, UINT8_T watchaMode)
{
	return SysRTC_HardRTCInit( RTCx,  spanDays,  watchaMode);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTCLib_HardRTCSetTime(SYS_RTC_HandlerType* RTCx, UINT8_T hour, UINT8_T minute, UINT8_T second)
{
	return SysRTC_HardRTCSetTime(RTCx,  hour,  minute,  second);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTCLib_HardRTCGetTime(SYS_RTC_HandlerType* RTCx)
{
	return SysRTC_HardRTCGetTime( RTCx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTCLib_HardRTCSetDate(SYS_RTC_HandlerType* RTCx, UINT8_T year, UINT8_T month, UINT8_T day)
{
	return SysRTC_HardRTCSetDate( RTCx,  year,  month,  day);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTCLib_HardRTCGetDate(SYS_RTC_HandlerType* RTCx)
{
	return SysRTC_HardRTCGetDate( RTCx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTCLib_HardRTCSetCentury(SYS_RTC_HandlerType* RTCx, UINT8_T century)
{
	return SysRTC_HardRTCSetCentury( RTCx,  century);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTCLib_HardRTCGetCentury(SYS_RTC_HandlerType* RTCx)
{
	return SysRTC_HardRTCGetCentury( RTCx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTCLib_HardRTCGetRTC(SYS_RTC_HandlerType* RTCx)
{
	return SysRTC_HardRTCGetRTC(RTCx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTCLib_HardRTCTask(SYS_RTC_HandlerType* RTCx)
{
	return SysRTC_HardRTCTask(RTCx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTCLib_RTCTask(SYS_RTC_HandlerType* RTCx, UINT32_T rtcSecond, UINT8_T isHW)
{
	return SysRTC_RTCTask(RTCx, rtcSecond,  isHW);
}
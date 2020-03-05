#include "rtc_cfg.h"

//===ϵͳ���ģ���RTCȫ�ֱ���
SYS_RTC_HandleType						g_SysSoftRTC = { 0 };
pSYS_RTC_HandleType					pSysSoftRTC = &g_SysSoftRTC;

//===ϵͳӲ��ʵ�ֵ�RTCȫ�ֱ���
SYS_RTC_HandleType						g_SysHWRTC={0};
pSYS_RTC_HandleType					pSysHWRTC=&g_SysHWRTC;

//===ÿ���µ�����
const UINT8_T g_MonthDaysTab[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������������ʱ����㵱ǰϵͳʱ��,������ϵͳ��λ��ʱ��
//////�������: watchaMode---0-����أ�1-ʵʱ��أ�2-ˢ�¼��
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void SysRTC_SoftRTCInit(SYS_RTC_HandleType* RTCx,UINT16_T spanDays, UINT8_T watchaMode)
{
	//---ȡ��������---������---__DATE__===Jul 03 2018
	//---һ��
	if (__DATE__[2] == 'n')
	{
		RTCx->msgRTC.month = 1;
	}
	//--����
	else if (__DATE__[2] == 'b')
	{
		RTCx->msgRTC.month = 2;
	}
	else if (__DATE__[2] == 'r')
	{
		if (__DATE__[0] == 'M')
		{
			//---����
			RTCx->msgRTC.month = 3;
		}
		else
		{
			//---����
			RTCx->msgRTC.month = 4;
		}
	}
	else if (__DATE__[2] == 'y')
	{
		//---����
		RTCx->msgRTC.month = 5;
	}
	else if (__DATE__[2] == 'n')
	{
		//---����
		RTCx->msgRTC.month = 6;
	}
	else if (__DATE__[2] == 'l')
	{
		//---����
		RTCx->msgRTC.month = 7;
	}
	else if (__DATE__[2] == 'g')
	{
		//---����
		RTCx->msgRTC.month = 8;
	}
	else if (__DATE__[2] == 'p')
	{
		//---����
		RTCx->msgRTC.month = 9;
	}
	else if (__DATE__[2] == 't')
	{
		//---ʮ��
		RTCx->msgRTC.month = 10;
	}
	else if (__DATE__[2] == 'v')
	{
		//---ʮһ��
		RTCx->msgRTC.month = 11;
	}
	else if (__DATE__[2] == 'c')
	{
		//---ʮ����
		RTCx->msgRTC.month = 12;
	}
	else
	{
		//---Ĭ����һ��
		RTCx->msgRTC.month = 1;
	}
	//---��
	if (__DATE__[9]==0x20)
	{
		RTCx->msgRTC.year = (UINT8_T)((__DATE__[10] - '0'));
	}
	else
	{
		RTCx->msgRTC.year = (UINT8_T)((__DATE__[9] - '0') * 10 + (__DATE__[10] - '0'));
	}	
	//---��
	if (__DATE__[4] == 0x20)
	{
		RTCx->msgRTC.day = (UINT8_T)(__DATE__[5] - '0');
	}
	else
	{
		RTCx->msgRTC.day = (UINT8_T)((__DATE__[4] - '0') * 10 + (__DATE__[5] - '0'));
	}
	//---����
	if (__DATE__[7] == 0x20)
	{
		RTCx->msgRTC.century = (UINT8_T)((__DATE__[8] - '0')+ 1);
	}
	else
	{
		RTCx->msgRTC.century = (UINT8_T)((__DATE__[7] - '0') * 10 + (__DATE__[8] - '0') + 1);
	}	
	//---��������
	RTCx->msgRTC.week = SysRTC_CalcWeekDay(&(RTCx->msgRTC));

	//---ȡ��������---ʱ����---__TIME__=06:17:05
	//---ʱ
	if (__TIME__[0]==0x20)
	{
		RTCx->msgRTC.hour = (UINT8_T)(__TIME__[1] - '0');
	}
	else
	{
		RTCx->msgRTC.hour = (UINT8_T)((__TIME__[0] - '0') * 10 + (__TIME__[1] - '0'));
	}
	//---��
	if (__TIME__[3] == 0x20)
	{
		RTCx->msgRTC.minute = (UINT8_T)(__TIME__[4] - '0');
	}
	else
	{
		RTCx->msgRTC.minute = (UINT8_T)((__TIME__[3] - '0') * 10 + (__TIME__[4] - '0'));
	}
	//---��
	if (__TIME__[6] == 0x20)
	{
		RTCx->msgRTC.second = (UINT8_T)(__TIME__[7] - '0');
	}
	else
	{
		RTCx->msgRTC.second = (UINT8_T)((__TIME__[6] - '0') * 10 + (__TIME__[7] - '0'));
	}
	
	//---ʱ���ʽ��24H
	RTCx->msgRTC.time24H = 1;
	//---�趨�ļ������
	RTCx->msgWatchSpanDays = spanDays;
	//---ʱ��������
	RTCx->msgWatchMode = watchaMode;
	//---��ǰʱ������
	RTCx->msgDay = RTCx->msgRTC.day;
	//---��ǰ������
	RTCx->msgMonth = RTCx->msgRTC.month;
	//---���RTC
	RTCx->msgHwMode = 0;
	
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�RTCʱ�䴦������������ʱ���룬���RTC���ݴ�����
//////�������: ϵͳ�δ�ʱ���ļ���ֵ
//////�������: ��
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void SysRTC_SoftCalcRTCTask(SYS_RTC_HandleType*RTCx, UINT32_T rtcSecond)
{
	UINT32_T cnt = 0;

	//---�жϵδ�ʱ�Ƿ����������
	if (rtcSecond < (RTCx->msgRTC.secondTick))
	{
		cnt = (0xFFFFFFFF - RTCx->msgRTC.secondTick + rtcSecond);
	}
	else
	{
		cnt = rtcSecond - RTCx->msgRTC.secondTick;
	}

	//---���㵱ǰ���==(����-1)*100+��
	int iY = RTCx->msgRTC.century - 1;
	iY = (iY * 100) + RTCx->msgRTC.year;

	//---�Ƿ�����仯
	if (cnt >= 1000)
	{
		//---������δ����ֵ
		RTCx->msgRTC.secondTick = rtcSecond;

		//---Ĭ��ʱ�������1ms������1000�Σ�������仯
		RTCx->msgRTC.second += 1;

		//---��仯
		if (RTCx->msgRTC.second > 60)
		{
			RTCx->msgRTC.minute += 1;
			RTCx->msgRTC.second = 0;

			//---�ֱ仯
			if (RTCx->msgRTC.minute > 60)
			{
				RTCx->msgRTC.hour += 1;
				RTCx->msgRTC.minute = 0;

				//---ʱ�仯
				if (RTCx->msgRTC.hour > 24)
				{
					//---��仯
					RTCx->msgRTC.day += 1;

					//---���ڱ仯
					RTCx->msgRTC.week += 1;

					//---һ����ֻ������
					if (RTCx->msgRTC.week > 7)
					{
						RTCx->msgRTC.week = 1;
					}

					//---����ʱ�仯
					RTCx->msgRTC.hour = 0;

					//---�ж��ǲ��Ƕ���
					if (RTCx->msgRTC.month == 2)
					{
						//---��������Ƿֿ���
						if (YEAR_TYPE(iY) != 0)
						{
							//---��仯
							if (RTCx->msgRTC.day > 29)
							{
								RTCx->msgRTC.day = 0;
								RTCx->msgRTC.month += 1;
							}
						}
						else
						{
							//---��仯
							if (RTCx->msgRTC.day > 28)
							{
								RTCx->msgRTC.day = 0;
								RTCx->msgRTC.month += 1;
							}
						}
					}
					else
					{
						//---��仯
						if (RTCx->msgRTC.day > g_MonthDaysTab[RTCx->msgRTC.month])
						{
							RTCx->msgRTC.day = 0;
							RTCx->msgRTC.month += 1;

							//---��仯
							if (RTCx->msgRTC.month > 12)
							{
								RTCx->msgRTC.month = 1;
								RTCx->msgRTC.year += 1;

								//---���ͱ仯
								if (RTCx->msgRTC.year > 100)
								{
									RTCx->msgRTC.century += 1;
									RTCx->msgRTC.year = 0;
								}
							}
						}
					}
				}
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����������ж����ڼ���ʹ�û�ķ����ɭ���㹫ʽ��
//////�������:
//////�������: 1---����һ��2---���ڶ���3---��������4---�����ģ�5---�����壻6---��������7---�����죻0---����
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTC_CalcWeekDay(RTC_HandleType*RTCx)
{
	int iM = RTCx->month;

	//int iY = RTCx->year;
	int iY = RTCx->century - 1;
	iY = (iY * 100) + RTCx->year;
	int iD = RTCx->day;
	int iWeekDay = -1;
	UINT8_T _return = 0;
	////////////////////////////////////////////////////////////////////////////////////////////////
	////��ķ����ɭ���㹫ʽ��
	////W= (d+2*m+3*(m+1)/5+y+y/4-y/100+y/400) mod 7
	////�ڹ�ʽ��d��ʾ�����е�������m��ʾ�·�����y��ʾ������
	////ע�⣺�ڹ�ʽ���и���������ʽ��ͬ�ĵط���
	////��һ�ºͶ��¿�������һ���ʮ���º�ʮ���£����������2004-1-10����ɣ�2003-13-10�����빫ʽ����
	////////////////////////////////////////////////////////////////////////////////////////////////
	if (1 == iM || 2 == iM)
	{
		iM += 12;
		iY--;
	}
	iWeekDay = (iD + 1 + 2 * iM + 3 * (iM + 1) / 5 + iY + iY / 4 - iY / 100 + iY / 400) % 7;

	//---�������ڼ�
	switch (iWeekDay)
	{
		case 0:
			_return = 7;
			break;
		case 1:
			_return = 1;
			break;
		case 2:
			_return = 2;
			break;
		case 3:
			_return = 3;
			break;
		case 4:
			_return = 4;
			break;
		case 5:
			_return = 5;
			break;
		case 6:
			_return = 6;
			break;
		default:
			break;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ������Ǽ�غ��������������λ�豸
//////�������:
//////�������:
//////˵		����������֮��ִ�в�ͬ�Ķ�Ӧ�Ĵ�����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTC_RealTimeWatch(SYS_RTC_HandleType* RTCx)
{
	UINT16_T _return = OK_0;
	if (RTCx->msgWatchSpanDays!=0)
	{
		if (RTCx->msgRTC.month < RTCx->msgMonth)
		{
			_return = RTCx->msgRTC.month + 12 - RTCx->msgMonth;
		}
		else
		{
			_return = RTCx->msgMonth - RTCx->msgRTC.month;
		}
		//---����ʱ������
		_return = (_return * 30) + RTCx->msgRTC.day - RTCx->msgDay;
		//---�ж��Ƿ񵽴���ʱ�����ֵ��������ִ�и�λ����
		if ((_return > RTCx->msgWatchSpanDays) || ((_return == RTCx->msgWatchSpanDays)))
		{
			//---������λ�ˣ�������в���������������飬����û��eeprom��оƬ����Ҫ��������eeprom��д�����
			

			//---�����λ
			SOFT_RESET();
			////---Ӳ����λ,�ȴ����Ź�����
			//while (1);
		}
		_return = OK_0;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� ˢ�¼��
//////�������: 
//////�������: 
//////˵		���� ʱ����ˢ��ʱ�����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTC_RefreshWatch(SYS_RTC_HandleType* RTCx)
{
	RTCx->msgMonth=RTCx->msgRTC.month;
	RTCx->msgDay = RTCx->msgRTC.day;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� ���ü��ʱ�䣬ʱ�䵥λ���죬���65535
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTC_SetWatchTime(SYS_RTC_HandleType* RTCx,UINT16_T spanDays)
{
	//---�趨�ļ������
	RTCx->msgWatchSpanDays = spanDays;
	//---��ǰʱ������
	RTCx->msgDay = RTCx->msgRTC.day;
	//---��ǰ������
	RTCx->msgMonth = RTCx->msgRTC.month;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� ���ü��ģʽ
//////�������:  watchMode---0-ȡ����أ�1-ʵʱ��أ�2-ˢ�¼��
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTC_SetWatchMode(SYS_RTC_HandleType* RTCx, UINT8_T watchMode)
{
	RTCx->msgWatchMode = watchMode;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� ����������
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTC_ClearWatch(SYS_RTC_HandleType* RTCx)
{
	RTCx->msgWatchMode = 0;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� �����ص�������
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTC_WatchTask(SYS_RTC_HandleType* RTCx)
{
	if (RTCx->msgWatchMode==1)
	{
		//---ʵʱ���
		SysRTC_RealTimeWatch(RTCx);
	}
	else if (RTCx->msgWatchMode==2)
	{
		//---ˢ�¼��
		SysRTC_RefreshWatch(RTCx);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ����RTC������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTC_SoftRTCTask(SYS_RTC_HandleType* RTCx, UINT32_T rtcSecond)
{
	//---ʱ�䴦��
	SysRTC_SoftCalcRTCTask(RTCx, rtcSecond);
	//---���ģʽ
	return SysRTC_WatchTask(RTCx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�Ӳ��RTC��ʼ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTC_HardRTCInit(SYS_RTC_HandleType* RTCx, UINT16_T spanDays, UINT8_T watchaMode)
{
	UINT8_T _return=OK_0;
	//---RTC�ĳ�ʼ��
	LL_RTC_InitTypeDef RTC_InitStruct = { 0 };
	//---RTC��ʱ��---ʱ����
	LL_RTC_TimeTypeDef RTC_TimeStruct = { 0 };
	//---RTC��ʱ��---����������
	LL_RTC_DateTypeDef RTC_DateStruct = { 0 };
	//---��ȡ����������ã��ж��ǲ��ǵ�һ�ε�����
	if (LL_RTC_BAK_GetRegister(RTC, LL_RTC_BKP_DR0) != 0x5050/*0x32F2*/) 
	{
		//---ǿ�Ʊ�����ĸ�λ
		LL_RCC_ForceBackupDomainReset();
		//---�ͷŶԱ�����ķ���
		LL_RCC_ReleaseBackupDomainReset();
		//---ʹ���ⲿRTC����
		LL_RCC_LSE_Enable();
		//---�ȴ��ⲿRTC�����ȶ�
		while (LL_RCC_LSE_IsReady() != 1)
		{
			
		}
		//---����RTCʱ�ӣ��ⲿʱ��Դ
		LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_LSE);
		//---ʹ��RTC
		LL_RCC_EnableRTC();
		//---RTC����Ϊ,24Сʱ��ʽ
		RTC_InitStruct.HourFormat = LL_RTC_HOURFORMAT_24HOUR;
		//---RTC�첽��Ƶϵ��(1~0X7F) 
		RTC_InitStruct.AsynchPrescaler = 0x7F;
		//---RTCͬ����Ƶϵ��(0~7FFF)
		RTC_InitStruct.SynchPrescaler = 0xFF;
		LL_RTC_Init(RTC, &RTC_InitStruct);
		//LL_RTC_SetAsynchPrescaler(RTC, 127);
		//LL_RTC_SetSynchPrescaler(RTC, 255);
		//---ѡ��ʱ���ʽ
		if (RTC_InitStruct.HourFormat == LL_RTC_HOURFORMAT_24HOUR)
		{
			//---��ǰʱ���ʽ��24Сʱ
			RTCx->msgRTC.time24H=1;
		}
		else 
		{
			//---��ǰʱ���ʽ��12Сʱ
			RTCx->msgRTC.time24H = 0;
		}		

		//---���嵱ǰʱ��
		RTCx->msgRTC.hour=15;
		RTCx->msgRTC.minute=20;
		RTCx->msgRTC.second=30;

		//---����ʱ����,��ʮ����ת����BCD����
		RTC_TimeStruct.Hours	= DecToBcd(RTCx->msgRTC.hour);
		RTC_TimeStruct.Minutes	= DecToBcd(RTCx->msgRTC.minute);
		RTC_TimeStruct.Seconds	= DecToBcd(RTCx->msgRTC.second);
		//---����ʱ�������绹������
		if (RTC_TimeStruct.Hours>0x12)
		{
			//---��������ʱ��
			RTC_TimeStruct.TimeFormat = LL_RTC_TIME_FORMAT_PM;
		}
		else
		{
			//---��������ʱ��
			RTC_TimeStruct.TimeFormat = LL_RTC_TIME_FORMAT_AM_OR_24;
		}
		//---����RTCʱ��Ĵ���
		LL_RTC_TIME_Init(RTC, LL_RTC_FORMAT_BCD, &RTC_TimeStruct);
		//---���嵱ǰ����
		RTCx->msgRTC.century=21;
		RTCx->msgRTC.year=19;
		RTCx->msgRTC.month=10;
		RTCx->msgRTC.day=30;
		RTCx->msgRTC.week=7;
		//---��������������,��ʮ����ת����BCD����
		RTC_DateStruct.Year		= DecToBcd(RTCx->msgRTC.year);
		RTC_DateStruct.WeekDay	= DecToBcd(RTCx->msgRTC.week);
		RTC_DateStruct.Month	= DecToBcd(RTCx->msgRTC.month);
		RTC_DateStruct.Day		= DecToBcd(RTCx->msgRTC.day);
		//---����RTC���ڼĴ���
		LL_RTC_DATE_Init(RTC, LL_RTC_FORMAT_BCD, &RTC_DateStruct);
		//---���RTC�Ѿ���ʼ������
		LL_RTC_BAK_SetRegister(RTC, LL_RTC_BKP_DR0,0x5050);
	}

	//---�趨�ļ������
	RTCx->msgWatchSpanDays = spanDays;
	//---ʱ��������
	RTCx->msgWatchMode = watchaMode;
	//---��ǰʱ������
	RTCx->msgDay = RTCx->msgRTC.day;
	//---��ǰ������
	RTCx->msgMonth = RTCx->msgRTC.month;
	//---Ӳ��RTC
	RTCx->msgHwMode =1;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�����ʱ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTC_HardRTCSetTime(SYS_RTC_HandleType* RTCx, UINT8_T hour, UINT8_T minute, UINT8_T second)
{
	//---RTC��ʱ��---ʱ����
	LL_RTC_TimeTypeDef RTC_TimeStruct = { 0 };

	//---���õ�ǰʱ��
	RTCx->msgRTC.hour = hour;
	RTCx->msgRTC.minute = minute;
	RTCx->msgRTC.second = second;

	//---����ʱ����,��ʮ����ת����BCD����
	RTC_TimeStruct.Hours = DecToBcd(RTCx->msgRTC.hour);
	RTC_TimeStruct.Minutes = DecToBcd(RTCx->msgRTC.minute);
	RTC_TimeStruct.Seconds = DecToBcd(RTCx->msgRTC.second);
	//---����ʱ�������绹������
	if (RTC_TimeStruct.Hours > 0x12)
	{
		//---��������ʱ��
		RTC_TimeStruct.TimeFormat = LL_RTC_TIME_FORMAT_PM;
	}
	else
	{
		//---��������ʱ��
		RTC_TimeStruct.TimeFormat = LL_RTC_TIME_FORMAT_AM_OR_24;
	}
	//---����RTCʱ��Ĵ���
	LL_RTC_TIME_Init(RTC, LL_RTC_FORMAT_BCD, &RTC_TimeStruct);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡʱ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTC_HardRTCGetTime(SYS_RTC_HandleType* RTCx)
{
	RTCx->msgRTC.hour = BcdToDec(LL_RTC_TIME_GetHour(RTC));
	RTCx->msgRTC.minute = BcdToDec(LL_RTC_TIME_GetMinute(RTC));
	RTCx->msgRTC.second = BcdToDec(LL_RTC_TIME_GetSecond(RTC));
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTC_HardRTCSetDate(SYS_RTC_HandleType* RTCx, UINT8_T year, UINT8_T month, UINT8_T day)
{
	//---RTC��ʱ��---����������
	LL_RTC_DateTypeDef RTC_DateStruct = { 0 };

	RTCx->msgRTC.year=year;
	RTCx->msgRTC.month=month;
	RTCx->msgRTC.day=day;
	//---�������ڼ�
	RTCx->msgRTC.week=SysRTC_CalcWeekDay(&RTCx->msgRTC); 

	//---��������������,��ʮ����ת����BCD����
	RTC_DateStruct.Year = DecToBcd(RTCx->msgRTC.year);
	RTC_DateStruct.WeekDay = DecToBcd(RTCx->msgRTC.week);
	RTC_DateStruct.Month = DecToBcd(RTCx->msgRTC.month);
	RTC_DateStruct.Day = DecToBcd(RTCx->msgRTC.day);
	//---����RTC���ڼĴ���
	LL_RTC_DATE_Init(RTC, LL_RTC_FORMAT_BCD, &RTC_DateStruct);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTC_HardRTCGetDate(SYS_RTC_HandleType* RTCx)
{
	RTCx->msgRTC.year = BcdToDec(LL_RTC_DATE_GetYear(RTC));
	RTCx->msgRTC.month = BcdToDec(LL_RTC_DATE_GetMonth(RTC));
	RTCx->msgRTC.day = BcdToDec(LL_RTC_DATE_GetDay(RTC));
	RTCx->msgRTC.week = BcdToDec(LL_RTC_DATE_GetWeekDay(RTC));
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTC_HardRTCSetCentury(SYS_RTC_HandleType* RTCx, UINT8_T century)
{
	RTCx->msgRTC.century=century;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡ����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTC_HardRTCGetCentury(SYS_RTC_HandleType* RTCx)
{
	return RTCx->msgRTC.century;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ȡӲ��ʵʱʱ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTC_HardRTCGetRTC(SYS_RTC_HandleType* RTCx)
{
	//---��ȡʱ��
	SysRTC_HardRTCGetTime(RTCx);
	//---��ȡ����
	SysRTC_HardRTCGetDate(RTCx);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�Ӳ��RTC������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTC_HardRTCTask(SYS_RTC_HandleType* RTCx)
{
	//---��ȡʵʱʱ��
	SysRTC_HardRTCGetRTC(RTCx);
	//---���ģʽ
	return SysRTC_WatchTask(RTCx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�RTC������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTC_RTCTask(SYS_RTC_HandleType* RTCx, UINT32_T rtcSecond)
{
	if ((RTCx->msgHwMode !=0)||(RTCx->msgHwMode==3))
	{
		//---��ȡӲ��ʵʱʱ��
		SysRTC_HardRTCGetRTC(RTCx);
	}
	if((RTCx->msgHwMode == 0)||(RTCx->msgHwMode==3))
	{
		//---��ȡ���ʵʱʱ��
		SysRTC_SoftCalcRTCTask(RTCx, rtcSecond);
	}
	//---���ģʽ
	return SysRTC_WatchTask(RTCx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ʼ��ʵʱʱ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTC_RTCInit(SYS_RTC_HandleType* RTCx, UINT16_T spanDays, UINT8_T watchaMode, UINT8_T isHW)
{
	UINT8_T _return =OK_0;
	if ((isHW != 0) || (isHW == 3))
	{
		//---Ӳ��ʵʱʱ��,��ʼ��
		_return = SysRTC_HardRTCInit(RTCx,spanDays,watchaMode);
	}
	if ((isHW == 0) || (isHW == 3))
	{
		//---���ʵʱʱ��,��ʼ��
		SysRTC_SoftRTCInit(RTCx, spanDays, watchaMode);
	}
	if (isHW==3)
	{
		RTCx->msgHwMode = 3;
	}
	return _return;
}


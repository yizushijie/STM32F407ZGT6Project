#include "rtc_cfg.h"

//===系统软件模拟的RTC全局变量
SYS_RTC_HandleType						g_SysSoftRTC = { 0 };
pSYS_RTC_HandleType					pSysSoftRTC = &g_SysSoftRTC;

//===系统硬件实现的RTC全局变量
SYS_RTC_HandleType						g_SysHWRTC={0};
pSYS_RTC_HandleType					pSysHWRTC=&g_SysHWRTC;

//===每个月的天数
const UINT8_T g_MonthDaysTab[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：根据软件编译时间计算当前系统时钟,并设置系统复位的时间
//////输入参数: watchaMode---0-不监控，1-实时监控，2-刷新监控
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void SysRTC_SoftRTCInit(SYS_RTC_HandleType* RTCx,UINT16_T spanDays, UINT8_T watchaMode)
{
	//---取编译日期---年月日---__DATE__===Jul 03 2018
	//---一月
	if (__DATE__[2] == 'n')
	{
		RTCx->msgRTC.month = 1;
	}
	//--二月
	else if (__DATE__[2] == 'b')
	{
		RTCx->msgRTC.month = 2;
	}
	else if (__DATE__[2] == 'r')
	{
		if (__DATE__[0] == 'M')
		{
			//---三月
			RTCx->msgRTC.month = 3;
		}
		else
		{
			//---四月
			RTCx->msgRTC.month = 4;
		}
	}
	else if (__DATE__[2] == 'y')
	{
		//---五月
		RTCx->msgRTC.month = 5;
	}
	else if (__DATE__[2] == 'n')
	{
		//---六月
		RTCx->msgRTC.month = 6;
	}
	else if (__DATE__[2] == 'l')
	{
		//---七月
		RTCx->msgRTC.month = 7;
	}
	else if (__DATE__[2] == 'g')
	{
		//---八月
		RTCx->msgRTC.month = 8;
	}
	else if (__DATE__[2] == 'p')
	{
		//---九月
		RTCx->msgRTC.month = 9;
	}
	else if (__DATE__[2] == 't')
	{
		//---十月
		RTCx->msgRTC.month = 10;
	}
	else if (__DATE__[2] == 'v')
	{
		//---十一月
		RTCx->msgRTC.month = 11;
	}
	else if (__DATE__[2] == 'c')
	{
		//---十二月
		RTCx->msgRTC.month = 12;
	}
	else
	{
		//---默认是一月
		RTCx->msgRTC.month = 1;
	}
	//---年
	if (__DATE__[9]==0x20)
	{
		RTCx->msgRTC.year = (UINT8_T)((__DATE__[10] - '0'));
	}
	else
	{
		RTCx->msgRTC.year = (UINT8_T)((__DATE__[9] - '0') * 10 + (__DATE__[10] - '0'));
	}	
	//---日
	if (__DATE__[4] == 0x20)
	{
		RTCx->msgRTC.day = (UINT8_T)(__DATE__[5] - '0');
	}
	else
	{
		RTCx->msgRTC.day = (UINT8_T)((__DATE__[4] - '0') * 10 + (__DATE__[5] - '0'));
	}
	//---世纪
	if (__DATE__[7] == 0x20)
	{
		RTCx->msgRTC.century = (UINT8_T)((__DATE__[8] - '0')+ 1);
	}
	else
	{
		RTCx->msgRTC.century = (UINT8_T)((__DATE__[7] - '0') * 10 + (__DATE__[8] - '0') + 1);
	}	
	//---计算星期
	RTCx->msgRTC.week = SysRTC_CalcWeekDay(&(RTCx->msgRTC));

	//---取编译日期---时分秒---__TIME__=06:17:05
	//---时
	if (__TIME__[0]==0x20)
	{
		RTCx->msgRTC.hour = (UINT8_T)(__TIME__[1] - '0');
	}
	else
	{
		RTCx->msgRTC.hour = (UINT8_T)((__TIME__[0] - '0') * 10 + (__TIME__[1] - '0'));
	}
	//---分
	if (__TIME__[3] == 0x20)
	{
		RTCx->msgRTC.minute = (UINT8_T)(__TIME__[4] - '0');
	}
	else
	{
		RTCx->msgRTC.minute = (UINT8_T)((__TIME__[3] - '0') * 10 + (__TIME__[4] - '0'));
	}
	//---秒
	if (__TIME__[6] == 0x20)
	{
		RTCx->msgRTC.second = (UINT8_T)(__TIME__[7] - '0');
	}
	else
	{
		RTCx->msgRTC.second = (UINT8_T)((__TIME__[6] - '0') * 10 + (__TIME__[7] - '0'));
	}
	
	//---时间格式是24H
	RTCx->msgRTC.time24H = 1;
	//---设定的监控天数
	RTCx->msgWatchSpanDays = spanDays;
	//---时间监控类型
	RTCx->msgWatchMode = watchaMode;
	//---当前时间天数
	RTCx->msgDay = RTCx->msgRTC.day;
	//---当前的月数
	RTCx->msgMonth = RTCx->msgRTC.month;
	//---软件RTC
	RTCx->msgHwMode = 0;
	
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：RTC时间处理，更新年月日时分秒，软件RTC数据处理函数
//////输入参数: 系统滴答定时器的计数值
//////输出参数: 无
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void SysRTC_SoftCalcRTCTask(SYS_RTC_HandleType*RTCx, UINT32_T rtcSecond)
{
	UINT32_T cnt = 0;

	//---判断滴答定时是否发生溢出操作
	if (rtcSecond < (RTCx->msgRTC.secondTick))
	{
		cnt = (0xFFFFFFFF - RTCx->msgRTC.secondTick + rtcSecond);
	}
	else
	{
		cnt = rtcSecond - RTCx->msgRTC.secondTick;
	}

	//---计算当前年份==(世纪-1)*100+年
	int iY = RTCx->msgRTC.century - 1;
	iY = (iY * 100) + RTCx->msgRTC.year;

	//---是否发生秒变化
	if (cnt >= 1000)
	{
		//---更新秒滴答计数值
		RTCx->msgRTC.secondTick = rtcSecond;

		//---默认时间基数是1ms，基数1000次，发生秒变化
		RTCx->msgRTC.second += 1;

		//---秒变化
		if (RTCx->msgRTC.second > 60)
		{
			RTCx->msgRTC.minute += 1;
			RTCx->msgRTC.second = 0;

			//---分变化
			if (RTCx->msgRTC.minute > 60)
			{
				RTCx->msgRTC.hour += 1;
				RTCx->msgRTC.minute = 0;

				//---时变化
				if (RTCx->msgRTC.hour > 24)
				{
					//---天变化
					RTCx->msgRTC.day += 1;

					//---星期变化
					RTCx->msgRTC.week += 1;

					//---一星期只有七天
					if (RTCx->msgRTC.week > 7)
					{
						RTCx->msgRTC.week = 1;
					}

					//---清零时变化
					RTCx->msgRTC.hour = 0;

					//---判断是不是二月
					if (RTCx->msgRTC.month == 2)
					{
						//---年和世纪是分开的
						if (YEAR_TYPE(iY) != 0)
						{
							//---天变化
							if (RTCx->msgRTC.day > 29)
							{
								RTCx->msgRTC.day = 0;
								RTCx->msgRTC.month += 1;
							}
						}
						else
						{
							//---天变化
							if (RTCx->msgRTC.day > 28)
							{
								RTCx->msgRTC.day = 0;
								RTCx->msgRTC.month += 1;
							}
						}
					}
					else
					{
						//---天变化
						if (RTCx->msgRTC.day > g_MonthDaysTab[RTCx->msgRTC.month])
						{
							RTCx->msgRTC.day = 0;
							RTCx->msgRTC.month += 1;

							//---年变化
							if (RTCx->msgRTC.month > 12)
							{
								RTCx->msgRTC.month = 1;
								RTCx->msgRTC.year += 1;

								//---世纪变化
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
//////函		数：
//////功		能：根据日期判断星期几（使用基姆拉尔森计算公式）
//////输入参数:
//////输出参数: 1---星期一；2---星期二；3---星期三；4---星期四；5---星期五；6---星期六；7---星期天；0---错误
//////说		明：
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
	////基姆拉尔森计算公式：
	////W= (d+2*m+3*(m+1)/5+y+y/4-y/100+y/400) mod 7
	////在公式中d表示日期中的日数，m表示月份数，y表示年数。
	////注意：在公式中有个与其他公式不同的地方：
	////把一月和二月看成是上一年的十三月和十四月，例：如果是2004-1-10则换算成：2003-13-10来代入公式计算
	////////////////////////////////////////////////////////////////////////////////////////////////
	if (1 == iM || 2 == iM)
	{
		iM += 12;
		iY--;
	}
	iWeekDay = (iD + 1 + 2 * iM + 3 * (iM + 1) / 5 + iY + iY / 4 - iY / 100 + iY / 400) % 7;

	//---解析星期几
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
//////函		数：
//////功		能：这里是监控函数，用于软件复位设备
//////输入参数:
//////输出参数:
//////说		明：多少天之后执行不同的对应的处理函数
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
		//---计算时间脉冲
		_return = (_return * 30) + RTCx->msgRTC.day - RTCx->msgDay;
		//---判断是否到达监控时间的阈值，如果到达，执行复位操作
		if ((_return > RTCx->msgWatchSpanDays) || ((_return == RTCx->msgWatchSpanDays)))
		{
			//---发生复位了，这里进行参数，用于其他检查，对于没有eeprom的芯片，需要增加增加eeprom的写入操作
			

			//---软件复位
			SOFT_RESET();
			////---硬件复位,等待看门狗启动
			//while (1);
		}
		_return = OK_0;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 刷新监控
//////输入参数: 
//////输出参数: 
//////说		明： 时刻在刷新时间参数
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTC_RefreshWatch(SYS_RTC_HandleType* RTCx)
{
	RTCx->msgMonth=RTCx->msgRTC.month;
	RTCx->msgDay = RTCx->msgRTC.day;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 设置监控时间，时间单位是天，最大65535
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTC_SetWatchTime(SYS_RTC_HandleType* RTCx,UINT16_T spanDays)
{
	//---设定的监控天数
	RTCx->msgWatchSpanDays = spanDays;
	//---当前时间天数
	RTCx->msgDay = RTCx->msgRTC.day;
	//---当前的月数
	RTCx->msgMonth = RTCx->msgRTC.month;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 设置监控模式
//////输入参数:  watchMode---0-取消监控，1-实时监控，2-刷新监控
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTC_SetWatchMode(SYS_RTC_HandleType* RTCx, UINT8_T watchMode)
{
	RTCx->msgWatchMode = watchMode;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 清除监控设置
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTC_ClearWatch(SYS_RTC_HandleType* RTCx)
{
	RTCx->msgWatchMode = 0;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数： 
//////功		能： 软件监控的任务函数
//////输入参数: 
//////输出参数: 
//////说		明： 
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTC_WatchTask(SYS_RTC_HandleType* RTCx)
{
	if (RTCx->msgWatchMode==1)
	{
		//---实时监控
		SysRTC_RealTimeWatch(RTCx);
	}
	else if (RTCx->msgWatchMode==2)
	{
		//---刷新监控
		SysRTC_RefreshWatch(RTCx);
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：软件RTC任务函数
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTC_SoftRTCTask(SYS_RTC_HandleType* RTCx, UINT32_T rtcSecond)
{
	//---时间处理
	SysRTC_SoftCalcRTCTask(RTCx, rtcSecond);
	//---监控模式
	return SysRTC_WatchTask(RTCx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：硬件RTC初始化
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTC_HardRTCInit(SYS_RTC_HandleType* RTCx, UINT16_T spanDays, UINT8_T watchaMode)
{
	UINT8_T _return=OK_0;
	//---RTC的初始化
	LL_RTC_InitTypeDef RTC_InitStruct = { 0 };
	//---RTC的时间---时分秒
	LL_RTC_TimeTypeDef RTC_TimeStruct = { 0 };
	//---RTC的时间---年月日星期
	LL_RTC_DateTypeDef RTC_DateStruct = { 0 };
	//---读取备份域的配置，判断是不是第一次的配置
	if (LL_RTC_BAK_GetRegister(RTC, LL_RTC_BKP_DR0) != 0x5050/*0x32F2*/) 
	{
		//---强制备份域的复位
		LL_RCC_ForceBackupDomainReset();
		//---释放对备份域的服务
		LL_RCC_ReleaseBackupDomainReset();
		//---使能外部RTC晶振
		LL_RCC_LSE_Enable();
		//---等待外部RTC晶振稳定
		while (LL_RCC_LSE_IsReady() != 1)
		{
			
		}
		//---设置RTC时钟，外部时钟源
		LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_LSE);
		//---使能RTC
		LL_RCC_EnableRTC();
		//---RTC设置为,24小时格式
		RTC_InitStruct.HourFormat = LL_RTC_HOURFORMAT_24HOUR;
		//---RTC异步分频系数(1~0X7F) 
		RTC_InitStruct.AsynchPrescaler = 0x7F;
		//---RTC同步分频系数(0~7FFF)
		RTC_InitStruct.SynchPrescaler = 0xFF;
		LL_RTC_Init(RTC, &RTC_InitStruct);
		//LL_RTC_SetAsynchPrescaler(RTC, 127);
		//LL_RTC_SetSynchPrescaler(RTC, 255);
		//---选择时间格式
		if (RTC_InitStruct.HourFormat == LL_RTC_HOURFORMAT_24HOUR)
		{
			//---当前时间格式是24小时
			RTCx->msgRTC.time24H=1;
		}
		else 
		{
			//---当前时间格式是12小时
			RTCx->msgRTC.time24H = 0;
		}		

		//---定义当前时间
		RTCx->msgRTC.hour=15;
		RTCx->msgRTC.minute=20;
		RTCx->msgRTC.second=30;

		//---设置时分秒,将十进制转换成BCD编码
		RTC_TimeStruct.Hours	= DecToBcd(RTCx->msgRTC.hour);
		RTC_TimeStruct.Minutes	= DecToBcd(RTCx->msgRTC.minute);
		RTC_TimeStruct.Seconds	= DecToBcd(RTCx->msgRTC.second);
		//---设置时间是上午还是下午
		if (RTC_TimeStruct.Hours>0x12)
		{
			//---设置下午时间
			RTC_TimeStruct.TimeFormat = LL_RTC_TIME_FORMAT_PM;
		}
		else
		{
			//---设置上午时间
			RTC_TimeStruct.TimeFormat = LL_RTC_TIME_FORMAT_AM_OR_24;
		}
		//---配置RTC时间寄存器
		LL_RTC_TIME_Init(RTC, LL_RTC_FORMAT_BCD, &RTC_TimeStruct);
		//---定义当前日期
		RTCx->msgRTC.century=21;
		RTCx->msgRTC.year=19;
		RTCx->msgRTC.month=10;
		RTCx->msgRTC.day=30;
		RTCx->msgRTC.week=7;
		//---设置年月日星期,将十进制转换成BCD编码
		RTC_DateStruct.Year		= DecToBcd(RTCx->msgRTC.year);
		RTC_DateStruct.WeekDay	= DecToBcd(RTCx->msgRTC.week);
		RTC_DateStruct.Month	= DecToBcd(RTCx->msgRTC.month);
		RTC_DateStruct.Day		= DecToBcd(RTCx->msgRTC.day);
		//---配置RTC日期寄存器
		LL_RTC_DATE_Init(RTC, LL_RTC_FORMAT_BCD, &RTC_DateStruct);
		//---标记RTC已经初始化过了
		LL_RTC_BAK_SetRegister(RTC, LL_RTC_BKP_DR0,0x5050);
	}

	//---设定的监控天数
	RTCx->msgWatchSpanDays = spanDays;
	//---时间监控类型
	RTCx->msgWatchMode = watchaMode;
	//---当前时间天数
	RTCx->msgDay = RTCx->msgRTC.day;
	//---当前的月数
	RTCx->msgMonth = RTCx->msgRTC.month;
	//---硬件RTC
	RTCx->msgHwMode =1;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置时间
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTC_HardRTCSetTime(SYS_RTC_HandleType* RTCx, UINT8_T hour, UINT8_T minute, UINT8_T second)
{
	//---RTC的时间---时分秒
	LL_RTC_TimeTypeDef RTC_TimeStruct = { 0 };

	//---设置当前时间
	RTCx->msgRTC.hour = hour;
	RTCx->msgRTC.minute = minute;
	RTCx->msgRTC.second = second;

	//---设置时分秒,将十进制转换成BCD编码
	RTC_TimeStruct.Hours = DecToBcd(RTCx->msgRTC.hour);
	RTC_TimeStruct.Minutes = DecToBcd(RTCx->msgRTC.minute);
	RTC_TimeStruct.Seconds = DecToBcd(RTCx->msgRTC.second);
	//---设置时间是上午还是下午
	if (RTC_TimeStruct.Hours > 0x12)
	{
		//---设置下午时间
		RTC_TimeStruct.TimeFormat = LL_RTC_TIME_FORMAT_PM;
	}
	else
	{
		//---设置上午时间
		RTC_TimeStruct.TimeFormat = LL_RTC_TIME_FORMAT_AM_OR_24;
	}
	//---配置RTC时间寄存器
	LL_RTC_TIME_Init(RTC, LL_RTC_FORMAT_BCD, &RTC_TimeStruct);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：获取时间
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTC_HardRTCGetTime(SYS_RTC_HandleType* RTCx)
{
	RTCx->msgRTC.hour = BcdToDec(LL_RTC_TIME_GetHour(RTC));
	RTCx->msgRTC.minute = BcdToDec(LL_RTC_TIME_GetMinute(RTC));
	RTCx->msgRTC.second = BcdToDec(LL_RTC_TIME_GetSecond(RTC));
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：设置日期
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTC_HardRTCSetDate(SYS_RTC_HandleType* RTCx, UINT8_T year, UINT8_T month, UINT8_T day)
{
	//---RTC的时间---年月日星期
	LL_RTC_DateTypeDef RTC_DateStruct = { 0 };

	RTCx->msgRTC.year=year;
	RTCx->msgRTC.month=month;
	RTCx->msgRTC.day=day;
	//---计算星期几
	RTCx->msgRTC.week=SysRTC_CalcWeekDay(&RTCx->msgRTC); 

	//---设置年月日星期,将十进制转换成BCD编码
	RTC_DateStruct.Year = DecToBcd(RTCx->msgRTC.year);
	RTC_DateStruct.WeekDay = DecToBcd(RTCx->msgRTC.week);
	RTC_DateStruct.Month = DecToBcd(RTCx->msgRTC.month);
	RTC_DateStruct.Day = DecToBcd(RTCx->msgRTC.day);
	//---配置RTC日期寄存器
	LL_RTC_DATE_Init(RTC, LL_RTC_FORMAT_BCD, &RTC_DateStruct);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：获取日期
//////输入参数:
//////输出参数:
//////说		明：
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
//////函		数：
//////功		能：设置世纪
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTC_HardRTCSetCentury(SYS_RTC_HandleType* RTCx, UINT8_T century)
{
	RTCx->msgRTC.century=century;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：获取世纪
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTC_HardRTCGetCentury(SYS_RTC_HandleType* RTCx)
{
	return RTCx->msgRTC.century;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：获取硬件实时时钟
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTC_HardRTCGetRTC(SYS_RTC_HandleType* RTCx)
{
	//---获取时间
	SysRTC_HardRTCGetTime(RTCx);
	//---获取日期
	SysRTC_HardRTCGetDate(RTCx);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：硬件RTC任务函数
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTC_HardRTCTask(SYS_RTC_HandleType* RTCx)
{
	//---获取实时时钟
	SysRTC_HardRTCGetRTC(RTCx);
	//---监控模式
	return SysRTC_WatchTask(RTCx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：RTC任务函数
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTC_RTCTask(SYS_RTC_HandleType* RTCx, UINT32_T rtcSecond)
{
	if ((RTCx->msgHwMode !=0)||(RTCx->msgHwMode==3))
	{
		//---获取硬件实时时钟
		SysRTC_HardRTCGetRTC(RTCx);
	}
	if((RTCx->msgHwMode == 0)||(RTCx->msgHwMode==3))
	{
		//---获取软件实时时钟
		SysRTC_SoftCalcRTCTask(RTCx, rtcSecond);
	}
	//---监控模式
	return SysRTC_WatchTask(RTCx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：初始化实时时钟
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysRTC_RTCInit(SYS_RTC_HandleType* RTCx, UINT16_T spanDays, UINT8_T watchaMode, UINT8_T isHW)
{
	UINT8_T _return =OK_0;
	if ((isHW != 0) || (isHW == 3))
	{
		//---硬件实时时钟,初始化
		_return = SysRTC_HardRTCInit(RTCx,spanDays,watchaMode);
	}
	if ((isHW == 0) || (isHW == 3))
	{
		//---软件实时时钟,初始化
		SysRTC_SoftRTCInit(RTCx, spanDays, watchaMode);
	}
	if (isHW==3)
	{
		RTCx->msgHwMode = 3;
	}
	return _return;
}


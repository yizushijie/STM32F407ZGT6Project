#ifndef DS1302_CFG_H_
#define DS1302_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "delay_task.h"
	#include "gpio_task.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//上升沿写入数据，下降沿读取数据
	//必须检查设备是否处于工作模式，标志位是秒寄存器的最高位，为1这是休眠模式，为0是工作模式
	//休眠模式下计数器不工作，读取的数据都不对，工作模式下才开启计数器，读取的数据才能正确，
	//上电默认是休眠模式
	//注：DS1302的数据都是BCD格式，注意数据格式的转换
	//////////////////////////////////////////////////////////////////////////////////////
	//===芯片寄存器地址定义 定义的写地址，读需要+1
	#define DS1302_REG_SECOND					0x80        //秒数据地址
	#define DS1302_REG_MINUTE					0x82        //分数据地址
	#define DS1302_REG_HOUR						0x84        //时数据地址
	#define DS1302_REG_DAY						0x86        //日数据地址
	#define DS1302_REG_WEEK						0x8A        //星期几数据地址
	#define DS1302_REG_MONTH					0x88        //月数据地址
	#define DS1302_REG_YEAR						0x8C        //年数据地址
	#define DS1302_REG_CONTROL					0x8E        //写保护寄存器地址
	#define DS1302_REG_CHARGER					0x90        //涓流充电寄存器
	#define DS1302_REG_CLKBURST					0xBE        //脉冲串寄存器
	#define DS1302_RAM_BASE						0X30        //RAM基础地址
	#define DS1302_BURST_READ_RAM				0xBF		//连续读取数据

	//===结构体定义
	typedef struct _DS1302_HandlerType			DS1302_HandlerType;

	//===指针结构体定义
	typedef struct _DS1302_HandlerType			*pDS1302_HandlerType;

	//===OLED的数据结构体
	struct _DS1302_HandlerType
	{
		GPIO_HandlerType	msgCS;					//---CS端口号
		GPIO_HandlerType	msgCLK;					//---CLK端口号
		GPIO_HandlerType	msgDAT;					//---数据端口号
		RTC_HandlerType		msgRTC;					//---实时时钟
		UINT16_T			msgPluseWidth;			//---脉冲宽度，软件模拟使用
		UINT8_T				msgAMOrPM;				//---上午还是下午，0---上午，1---下午
		void(*msgDelayus)(UINT32_T delay);			//---延时参数
	};

	//===定义的任务函数
	#define DS1302_TASK_ONE							pDs1302Device0
	#define DS1302_TASK_TWO							0
	#define DS1302_TASK_THREE						0

	//===外部调用接口
	extern DS1302_HandlerType						g_Ds1302Device0;
	extern pDS1302_HandlerType						pDs1302Device0;

	//===函数定义
	UINT8_T DS1302_Init(DS1302_HandlerType *DS1302x, void(*pFuncDelayus)(UINT32_T delay));
	void  DS1302_DisableSleepMode(DS1302_HandlerType* DS1302x);
	void  DS1302_EnableSleepMode(DS1302_HandlerType* DS1302x);
	UINT8_T DS1302_CheckDevice(DS1302_HandlerType* DS1302x);
	void DS1302_WriteReg(DS1302_HandlerType *DS1302x, UINT8_T addr, UINT8_T dat);
	void DS1302_ReadReg(DS1302_HandlerType *DS1302x, UINT8_T addr, UINT8_T *pVal);
	void DS1302_WriteTime(DS1302_HandlerType *DS1302x, UINT8_T addr, UINT8_T dat);
	void DS1302_ReadTime(DS1302_HandlerType *DS1302x, UINT8_T addr, UINT8_T *pVal);
	void DS1302_WriteRTC(DS1302_HandlerType *DS1302x, RTC_HandlerType rtcTime);
	void DS1302_ReadRTC(DS1302_HandlerType *DS1302x);
	void DS1302_ReadBurstRTC(DS1302_HandlerType* DS1302x);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*DS1302_CFG_H_ */

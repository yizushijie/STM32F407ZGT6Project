#ifndef ADS869X_CFG_H_
#define ADS869X_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "delay_task.h"
	#include "gpio_task.h"
	#include "spi_task.h"
	#include "kalman_filter.h"
	#include "systick_task.h"
	//////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////寄存器定义---开始//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////
	//===命令寄存器
	//===继续在以前的操作模式
	#define ADS869X_CMD_REG_NO_OP				0x0000
	//===设备被置于待机模式
	#define ADS869X_CMD_REG_STDBY				0x8200
	//===设备已关闭供电
	#define ADS869X_CMD_REG_PWR_DN				0x8300
	//===寄存器重置为默认
	#define ADS869X_CMD_REG_RST					0x8500
	//===启用自动模式下复位
	#define ADS869X_CMD_REG_AUTO_RST			0xA000
	//===通道0
	#define ADS869X_CMD_REG_MAN_CH_0			0xC000
	//===通道1
	#define ADS869X_CMD_REG_MAN_CH_1			0xC400
	//===通道2
	#define ADS869X_CMD_REG_MAN_CH_2			0xC800
	//===通道3
	#define ADS869X_CMD_REG_MAN_CH_3			0xCC00
	//===通道4
	#define ADS869X_CMD_REG_MAN_CH_4			0xD000
	//===通道5
	#define ADS869X_CMD_REG_MAN_CH_5			0xD400
	//===通道6
	#define ADS869X_CMD_REG_MAN_CH_6			0xD800
	//===通道7
	#define ADS869X_CMD_REG_MAN_CH_7			0xDC00
	//===AUX通道
	#define ADS869X_CMD_REG_MAN_AUX				0xE000
	
	//===编程寄存器
	//===自动Squencing启用：默认值为0xFF - BITX使CHX
	#define ADS869X_PROG_REG_AUTO_SEQ_EN		0x01		//[FF]
	//===通道掉电；默认为0x00 - BITX到CHX断电
	#define ADS869X_PROG_REG_CH_PWR_DN			0x02		//[00]
	//功能选择：默认为0x00;//菊花链ID为bit 7-6，ALARM功能为bit 4，SDO数据格式为bit 2-0位
	#define ADS869X_PROG_REG_FEATURE_SELECT		0x03		//[00]
	
	//===设置通道0输入范围，默认为0x00 -位3-0选择范围
	#define ADS869X_PROG_REG_CH0_SET_RANGE		0x05		//[00]
	//===设置通道1输入范围，默认为0x00 -位3-0选择范围
	#define ADS869X_PROG_REG_CH1_SET_RANGE		0x06		//[00]
	//===设置通道2输入范围，默认为0x00 -位3-0选择范围
	#define ADS869X_PROG_REG_CH2_SET_RANGE		0x07		//[00]
	//===设置通道3输入范围，默认为0x00 -位3-0选择范围
	#define ADS869X_PROG_REG_CH3_SET_RANGE		0x08		//[00]
	//===设置通道4输入范围，默认为0x00 -位3-0选择范围
	#define ADS869X_PROG_REG_CH4_SET_RANGE		0x09		//[00]
	//===设置通道5输入范围，默认为0x00 -位3-0选择范围
	#define ADS869X_PROG_REG_CH5_SET_RANGE		0x0A		//[00]
	//===设置通道6输入范围，默认为0x00 -位3-0选择范围
	#define ADS869X_PROG_REG_CH6_SET_RANGE		0x0B		//[00]
	//===设置通道7输入范围，默认为0x00 -位3-0选择范围
	#define ADS869X_PROG_REG_CH7_SET_RANGE		0x0C		//[00]

	#define ADS869X_ALARM_OVERVIEW_TRIP_FLAG	0x10
	#define ADS869X_ALARM_CH0_CH3_TRIP_FLAG		0x11
	#define ADS869X_ALARM_CH0_CH3_ACTIVE_FLAG	0x12
	#define ADS869X_ALARM_CH4_CH7_TRIP_FLAG		0x13
	#define ADS869X_ALARM_CH4_CH7_ACTIVE_FLAG	0x14

	//===CH0
	#define ADS869X_PROG_REG_CH0_HS				0x15		//[00]
	#define ADS869X_PROG_REG_CH0_HT_MSB			0x16		//[FF]
	#define ADS869X_PROG_REG_CH0_HT_LSB			0x17		//[FF]
	#define ADS869X_PROG_REG_CH0_LT_MSB			0x18		//[00]
	#define ADS869X_PROG_REG_CH0_LT_LSB			0x19		//[00]
	
	//===CH1
	#define ADS869X_PROG_REG_CH1_HS				0x1A		//[00]
	#define ADS869X_PROG_REG_CH1_HT_MSB			0x1B		//[FF]
	#define ADS869X_PROG_REG_CH1_HT_LSB			0x1C		//[FF]
	#define ADS869X_PROG_REG_CH1_LT_MSB			0x1D		//[00]
	#define ADS869X_PROG_REG_CH1_LT_LSB			0x1E		//[00]

	//===CH2
	#define ADS869X_PROG_REG_CH2_HS				0x1F		//[00]
	#define ADS869X_PROG_REG_CH2_HT_MSB			0x20		//[FF]
	#define ADS869X_PROG_REG_CH2_HT_LSB			0x21		//[FF]
	#define ADS869X_PROG_REG_CH2_LT_MSB			0x22		//[00]
	#define ADS869X_PROG_REG_CH2_LT_LSB			0x23		//[00]

	//===CH3
	#define ADS869X_PROG_REG_CH3_HS				0x24		//[00]
	#define ADS869X_PROG_REG_CH3_HT_MSB			0x25		//[FF]
	#define ADS869X_PROG_REG_CH3_HT_LSB			0x26		//[FF]
	#define ADS869X_PROG_REG_CH3_LT_MSB			0x27		//[00]
	#define ADS869X_PROG_REG_CH3_LT_LSB			0x28		//[00]

	//===CH4
	#define ADS869X_PROG_REG_CH4_HS				0x29		//[00]
	#define ADS869X_PROG_REG_CH4_HT_MSB			0x2A		//[FF]
	#define ADS869X_PROG_REG_CH4_HT_LSB			0x2B		//[FF]
	#define ADS869X_PROG_REG_CH4_LT_MSB			0x2C		//[00]
	#define ADS869X_PROG_REG_CH4_LT_LSB			0x2D		//[00]

	//===CH5
	#define ADS869X_PROG_REG_CH5_HS				0x2E		//[00]
	#define ADS869X_PROG_REG_CH5_HT_MSB			0x2F		//[FF]
	#define ADS869X_PROG_REG_CH5_HT_LSB			0x30		//[FF]
	#define ADS869X_PROG_REG_CH5_LT_MSB			0x31		//[00]
	#define ADS869X_PROG_REG_CH5_LT_LSB			0x32		//[00]

	//===CH6
	#define ADS869X_PROG_REG_CH6_HS				0x33		//[00]
	#define ADS869X_PROG_REG_CH6_HT_MSB			0x34		//[FF]
	#define ADS869X_PROG_REG_CH6_HT_LSB			0x35		//[FF]
	#define ADS869X_PROG_REG_CH6_LT_MSB			0x36		//[00]
	#define ADS869X_PROG_REG_CH6_LT_LSB			0x37		//[00]

	//===CH7
	#define ADS869X_PROG_REG_CH7_HS				0x38		//[00]
	#define ADS869X_PROG_REG_CH7_HT_MSB			0x39		//[FF]
	#define ADS869X_PROG_REG_CH7_HT_LSB			0x3A		//[FF]
	#define ADS869X_PROG_REG_CH7_LT_MSB			0x3B		//[00]
	#define ADS869X_PROG_REG_CH7_LT_LSB			0x3C		//[00]
	
	//===命令读取
	#define ADS869X_CMD_READ_BACK				0x3F		//[00]
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////寄存器定义---结束//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////配置参数---开始///////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	
	//===ADC采样的参考电压
	#define ADS869X_REF_POWER_UV				4096000
	//===输入范围-2.5 / + 2.5 Vref的+/- 10.24V
	#define ADS869X_RANGE_10240MV_10240MV		0x00
	//===输入范围-1.25 / + 1.25 Vref的+/- 5.12V
	#define ADS869X_RANGE_5120MV_5120MV			0x01
	//===输入范围到-0.625 / 0.625 + Vref的+/- 2.56V
	#define ADS869X_RANGE_2560MV_2560MV			0x02
	//===输入范围以2.5 Vref的10.24V
	#define ADS869X_RANGE_0MV_10240MV			0x05
	//===输入范围以1.25 Vref的5.12V
	#define ADS869X_RANGE_0MV_5120MV			0x06
	//===ADC的采样通道数
	#define	ADS869X_CHANNEL_MAX					8	
	//===多次采样获取均值
	#define ADS869X_N_SAMPLE_COUNT				24
	//===校验采样数据的个数
	#if (ADS869X_N_SAMPLE_COUNT<9)
		#define ADS869X_N_SAMPLE_COUNT			9
	#endif
	
	//===定义ADC的位数
	#define ADS869X_ADC_SAMPLE_BITS				16
	//===ADC采集数据的有效位数
	#define ADS869X_DATA_SAMPLE_BITS			( 24-ADS869X_ADC_SAMPLE_BITS )
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////配置参数---结束////////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	

	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////结构体定义---开始//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	
	//===定义结构体
	typedef struct _ADS869X_HandleType			ADS869X_HandleType;
	//===定义指针结构体
	typedef	struct _ADS869X_HandleType			* pADS869X_HandleType;
	//===定义结构体
	struct _ADS869X_HandleType
	{
		VLTUINT8_T  msgWaitms;																							//---等待时间,单位是ms
		VLTUINT8_T  msgInitRetryCount;																					//---初始化重试的次数
		VLTUINT8_T  msgReadyOK;																							//---设备是否初始化成功，0---初始化成功，1---初始化失败
		VLTUINT8_T  msgChipID;																							//---设备的ID信息
		VLTUINT8_T  msgAutoSeqEn;																						//---通过AUTO_SEQ_EN的设置探测设备的存在
		VLTUINT8_T  msgChannelPWRDN;																					//---通道掉电模式
		VLTUINT8_T  msgFeature;																							//---特性设置参数
		VLTUINT8_T  msgChannelMode[ADS869X_CHANNEL_MAX];																//---输入装换模式,0---未选中使能；1---选中使能
		VLTUINT8_T  msgPositive[ADS869X_CHANNEL_MAX];																	//---0---无数据，1---是负数，2---是正值
		VLTUINT8_T  msgChannelRangeIsPositive[ADS869X_CHANNEL_MAX];														//---0---是正负量程，1---是正量程
		VLTUINT8_T  msgChannelRange[ADS869X_CHANNEL_MAX];																//---AD通道的量程参考
		volatile float    msgADCKP[ADS869X_CHANNEL_MAX];																//---ADC采样的比例系数
		VLTUINT16_T msgADCDelta[ADS869X_CHANNEL_MAX];																	//---ADC采样的比例差值
		VLTUINT32_T msgREFPowerUV;																						//---ADC的参考电压
		VLTUINT32_T msgChannelRangeBaseUVX1000[ADS869X_CHANNEL_MAX];													//---AD通道的每个BIT代表的电压值，单位是uv的十倍
		VLTUINT64_T msgChannelRangeFullUVX1000[ADS869X_CHANNEL_MAX];													//---AD通道的满量程的电压值，单位是uv的十倍
		VLTUINT32_T msgChannelNowADCResult[ADS869X_CHANNEL_MAX];														//---AD通道的当前采样结果
		VLTUINT32_T msgChannelOldADCResult[ADS869X_CHANNEL_MAX];														//---AD通道的上一次采样结果
		VLTUINT32_T msgChannelPowerResult[ADS869X_CHANNEL_MAX];															//---AD通道的采样的电压结果
		SPI_HandleType		msgSPI;																						//---使用的SPI模式
		GPIO_HandleType	msgHWRST;																						//---硬件复位信号
		void(*pMsgDelayms)(UINT32_T delay);																				//---延时参数
	};
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////结构体定义---结束//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	

	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////配置宏定义---开始//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	
	//===任务函数
	#define ADS869X_TASK_ONE							pADS869XDevice0
	#define ADS869X_TASK_TWO							0
	#define ADS869X_TASK_THREE							0
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////配置宏定义---开始//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	

	//===外部调用接口
	extern ADS869X_HandleType							g_ADS869XDevice0;
	extern pADS869X_HandleType							pADS869XDevice0;

	//===函数定义
	UINT8_T ADS869X_SPI_Init(ADS869X_HandleType* ADS869x, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHW);
	UINT8_T ADS869X_SPI_WriteCommandReg(ADS869X_HandleType* ADS869x, UINT32_T cmd);
	UINT8_T ADS869X_SPI_WriteProgramReg(ADS869X_HandleType* ADS869x, UINT8_T addr, UINT8_T val);
	UINT8_T ADS869X_SPI_ReadProgramReg(ADS869X_HandleType* ADS869x, UINT8_T addr, UINT8_T* pVal);
	UINT8_T ADS869X_SPI_ReadCommandBack(ADS869X_HandleType* ADS869x, UINT8_T* pVal, UINT8_T isAutoInit);
	UINT8_T ADS869X_SPI_NO_OP(ADS869X_HandleType* ADS869x, UINT8_T isAutoInit);
	UINT8_T ADS869X_SPI_STDBY(ADS869X_HandleType* ADS869x, UINT8_T isAutoInit);
	UINT8_T ADS869X_SPI_PWRDN(ADS869X_HandleType* ADS869x, UINT8_T isAutoInit);
	UINT8_T ADS869X_SPI_Reset(ADS869X_HandleType* ADS869x, UINT8_T isAutoInit);
	UINT8_T ADS869X_SPI_AUTORST(ADS869X_HandleType* ADS869x, UINT8_T isAutoInit);
	UINT8_T ADS869X_SPI_ManualChannel(ADS869X_HandleType* ADS869x, UINT16_T manualCHCmd, UINT8_T isAutoInit);
	UINT8_T ADS869X_SPI_WriteChipID(ADS869X_HandleType* ADS869x, UINT8_T devid, UINT8_T isAutoInit);
	UINT8_T ADS869X_SPI_ReadChipID(ADS869X_HandleType* ADS869x, UINT8_T* pDevID, UINT8_T isAutoInit);
	UINT8_T ADS869X_SPI_CheckChipID(ADS869X_HandleType* ADS869x, UINT8_T isAutoInit);
	UINT8_T ADS869X_SPI_DetectionDevice(ADS869X_HandleType* ADS869x, UINT8_T isAutoInit);
	UINT8_T ADS869X_SPI_WriteAUTOSEQEN(ADS869X_HandleType* ADS869x, UINT8_T seq, UINT8_T isAutoInit);
	UINT8_T ADS869X_SPI_ReadAUTOSEQEN(ADS869X_HandleType* ADS869x, UINT8_T* pAutoSeqEn, UINT8_T isAutoInit);
	UINT8_T ADS869X_SPI_WriteChannelPWRDN(ADS869X_HandleType* ADS869x, UINT8_T ch, UINT8_T isAutoInit);
	UINT8_T ADS869X_SPI_ReadChannelPWRDN(ADS869X_HandleType* ADS869x, UINT8_T* pPWRDN, UINT8_T isAutoInit);
	UINT8_T ADS869X_SPI_WriteFeature(ADS869X_HandleType* ADS869x, UINT8_T feature, UINT8_T isAutoInit);
	UINT8_T ADS869X_SPI_ReadFeature(ADS869X_HandleType* ADS869x, UINT8_T* pFeature, UINT8_T isAutoInit);
	UINT8_T ADS869X_SPI_WriteChannelRange(ADS869X_HandleType* ADS869x, UINT8_T chReg, UINT8_T range, UINT8_T isAutoInit);
	UINT8_T ADS869X_SPI_ReadChannelRange(ADS869X_HandleType* ADS869x, UINT8_T chReg, UINT8_T* pRange, UINT8_T isAutoInit);
	UINT8_T ADS869X_SPI_ChannelRange(ADS869X_HandleType* ADS869x, UINT8_T chIndex);
	UINT8_T ADS869X_SPI_CalcChannelPower(ADS869X_HandleType* ADS869x, UINT8_T chIndex, UINT8_T isCalcDelta);
	UINT8_T ADS869X_SPI_GetAutoRSTResult(ADS869X_HandleType* ADS869x, UINT8_T chNum, UINT8_T isAutoInit);
	UINT8_T ADS869X_SPI_GetAutoRSTNSampleResult(ADS869X_HandleType* ADS869x, UINT8_T chNum, UINT8_T isAutoInit);
	UINT8_T ADS869X_SPI_KalmanFilterGetAutoRSTNSampleResult(ADS869X_HandleType* ADS869x, UINT8_T chNum, UINT8_T isAutoInit);
	UINT8_T ADS869X_SPI_GetManualChannelResult(ADS869X_HandleType* ADS869x, UINT16_T manualChannel, UINT8_T isAutoInit);
	UINT8_T ADS869X_SPI_GetManualChannelNSampleResult(ADS869X_HandleType* ADS869x, UINT16_T manualChannel, UINT8_T isAutoInit);
	UINT8_T ADS869X_SPI_KalmanFilterGetManualChannelNSampleResult(ADS869X_HandleType* ADS869x, UINT16_T manualChannel, UINT8_T isAutoInit);
	UINT8_T ADS869X_SPI_CalibrationChannelErr(ADS869X_HandleType* ADS869x);
	UINT8_T ADS869X_SPI_ConfigInit(ADS869X_HandleType* ADS869x, UINT8_T isAutoInit);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*ADS869X_CFG_H_ */

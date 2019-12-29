#ifndef	MAX961X_CFG_H_
#define	MAX961X_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "i2c_task.h"
	//////////////////////////////////////////////////////////////////////////////////////

	//===负载电流[0000]
	#define MAX961X_REG_CSA_DATA_MSB_ADDR				0x00
	#define MAX961X_REG_CSA_DATA_LSB_ADDR				0x01

	//===输入电压[0000]
	#define MAX961X_REG_RS_DATA_MSB_ADDR				0x02
	#define MAX961X_REG_RS_DATA_LSB_ADDR				0x03

	//===out段电压[0000]
	#define MAX961X_REG_OUT_DATA_MSB_ADDR				0x04
	#define MAX961X_REG_OUT_DATA_LSB_ADDR				0x05

	//===设定的电压[0000]
	#define MAX961X_REG_SET_DATA_MSB_ADDR				0x06
	#define MAX961X_REG_SET_DATA_LSB_ADDR				0x07

	//===内部温度[8000]
	#define MAX961X_REG_TEMP_DATA_MSB_ADDR				0x08
	#define MAX961X_REG_TEMP_DATA_LSB_ADDR				0x09

	//===内部两个控制寄存器[0000]
	#define MAX961X_REG_CONTROL_REG1					0x0A
	#define MAX961X_REG_CONTROL_REG2					0x0B

	
	//===通道读取设置
	#define MAX961X_READ_CHANNEL_1X_GAIN_CURRENT		0x00
	#define MAX961X_READ_CHANNEL_4X_GAIN_CURRENT		0x01
	#define MAX961X_READ_CHANNEL_8X_GAIN_CURRENT		0x02
	#define MAX961X_READ_CHANNEL_INPUT_VOLTAGE			0x03
	#define MAX961X_READ_CHANNEL_OUTPUT_VOLTAGE			0x04
	#define MAX961X_READ_CHANNEL_SET_VOLTAGE			0x05
	#define MAX961X_READ_CHANNEL_TEMPERATURE			0x06
	#define MAX961X_fast_READ_ALL_CHANNEL				0x07

	//===电压最小分辨率
	#define MAX961X_VOLTAGE_STEP_MV						14
	//===电流最小分辨率
	#define MAX961X_CURRENT_STEP_MA						0.1075
	//===温度最小分辨率			
	#define MAX961X_TEMPERATURE_STEP_C					0.48
	//===采样电阻的大小,单位是毫欧
	#define	MAX961X_SAMPLE_RES_MR						20
	//===设备的写地址
	#define	MAX961X_WADDR								0xE0

	//===结构体定义
	typedef struct _MAX961X_HandlerType					MAX961X_HandlerType;
	//===指针结构体定义
	typedef struct _MAX961X_HandlerType					* pMAX961X_HandlerType;
	//===AT24Cxx的数据结构体
	struct _MAX961X_HandlerType
	{
		float			msgRSVoltagemV;					//---电压mV
		float			msgOutputVoltagemV;				//---电压mV
		float			msgSetVoltagemV;				//---电压mV
		float			msgRSCurrentmA;					//---电流mA
		float			msgTemperatureC;				//---温度℃
		UINT8_T			msgID;							//---默认是0x80
		I2C_HandlerType msgI2C;							//---使用的I2C
	};

	//===定义的任务函数
	#define MAX961X_TASK_ONE							pMax961xDevice0
	#define MAX961X_TASK_TWO							0
	#define MAX961X_TASK_THREE							0

	//===外部调用接口
	extern MAX961X_HandlerType							g_Max961xDevice0;
	extern pMAX961X_HandlerType							pMax961xDevice0;

	//===函数定义
	UINT8_T MAX961X_I2C_Device0_Init(MAX961X_HandlerType* MAX961x);
	UINT8_T MAX961X_I2C_Device1_Init(MAX961X_HandlerType* MAX961x);
	UINT8_T MAX961X_I2C_Device2_Init(MAX961X_HandlerType* MAX961x);
	UINT8_T MAX961X_I2C_Init(MAX961X_HandlerType* MAX961x, void(*pFuncDelayus)(UINT32_T delay), UINT8_T isHWI2C);
	UINT8_T MAX961X_I2C_SingleWriteReg(MAX961X_HandlerType* MAX961x, UINT8_T addr, UINT8_T val);
	UINT8_T MAX961X_I2C_BurstWriteReg(MAX961X_HandlerType* MAX961x, UINT8_T addr, UINT8_T length, UINT8_T* pVal);
	UINT8_T MAX961X_I2C_SingleReadReg(MAX961X_HandlerType* MAX961x, UINT8_T addr, UINT8_T* pVal);
	UINT8_T MAX961X_I2C_BurstReadReg(MAX961X_HandlerType* MAX961x, UINT8_T addr, UINT8_T length, UINT8_T* pVal);
	UINT8_T MAX961X_I2C_CheckDevice(MAX961X_HandlerType* MAX961x);
	UINT8_T MAX961X_I2C_GetRSVoltage(MAX961X_HandlerType* MAX961x);
	UINT8_T MAX961X_I2C_GetRSCurrent(MAX961X_HandlerType* MAX961x, UINT8_T currentGain);
	UINT8_T MAX961X_I2C_GetOutVoltage(MAX961X_HandlerType* MAX961x);
	UINT8_T MAX961X_I2C_GetSetVoltage(MAX961X_HandlerType* MAX961x);
	UINT8_T MAX961X_I2C_GetTemperature(MAX961X_HandlerType* MAX961x);
	UINT8_T MAX961X_I2C_GetAll(MAX961X_HandlerType* MAX961x, UINT8_T currentGain);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*MAX961X_CFG_H_ */
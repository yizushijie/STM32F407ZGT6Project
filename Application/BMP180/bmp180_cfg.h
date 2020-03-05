#ifndef BMP180_CFG_H_
#define BMP180_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include"complier_lib.h"
	#include "i2c_task.h"
	//////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////寄存器定义---开始//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////
	//===设备通讯地址
	#define BMP180_WADDR								0xEE															//---设备的写地址
	#define BMP180_RADDR								0xEF															//---设备的读地址
	#define BMP180_REG_ADDR_AC1_H						0xAA
	#define BMP180_REG_ADDR_AC1_L						0xAB
	#define BMP180_REG_ADDR_AC2_H						0xAC
	#define BMP180_REG_ADDR_AC2_L						0xAD
	#define BMP180_REG_ADDR_AC3_H						0xAE
	#define BMP180_REG_ADDR_AC3_L						0xAF
	#define BMP180_REG_ADDR_AC4_H						0xB0
	#define BMP180_REG_ADDR_AC4_L						0xB1
	#define BMP180_REG_ADDR_AC5_H						0xB2
	#define BMP180_REG_ADDR_AC5_L						0xB3
	#define BMP180_REG_ADDR_AC6_H						0xB4
	#define BMP180_REG_ADDR_AC6_L						0xB5
	#define BMP180_REG_ADDR_B1_H						0xB6
	#define BMP180_REG_ADDR_B1_L						0xB7
	#define BMP180_REG_ADDR_B2_H						0xB8
	#define BMP180_REG_ADDR_B2_L						0xB9
	#define BMP180_REG_ADDR_MB_H						0xBA
	#define BMP180_REG_ADDR_MB_L						0xBB
	#define BMP180_REG_ADDR_MC_H						0xBC
	#define BMP180_REG_ADDR_MC_L						0xBD
	#define BMP180_REG_ADDR_MD_H						0xBE
	#define BMP180_REG_ADDR_MD_L						0xBF

	#define BMP180_REG_ADDR_OUT_XLSB					0xF8	//---[00]
	#define BMP180_REG_ADDR_OUT_LSB						0xF7	//---[00]
	#define BMP180_REG_ADDR_OUT_MSB						0xF6	//---[80]
	#define BMP180_REG_ADDR_CTRL_MEAS					0xF4	//---[00]
	#define BMP180_REG_ADDR_SOFT_RESET					0xE0	//---[00]
	#define BMP180_REG_ADDR_CHIP_ID						0xD0	//---[55]

	#define BMP180_CHIP_ID								0x55
	#define BMP180_OSS									0
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////寄存器定义---结束//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////结构体定义---开始//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	
	//===BMP180校正参数				 					
	typedef struct
	{
		INT16_T				msgAC1;
		INT16_T				msgAC2;
		INT16_T				msgAC3;
		UINT16_T			msgAC4;
		UINT16_T			msgAC5;
		UINT16_T			msgAC6;
		INT16_T				msgB1;
		INT16_T				msgB2;
		INT16_T				msgMB;
		INT16_T				msgMC;
		INT16_T				msgMD;

		long				msgX1;
		long				msgX2;
		long				msgX3;
		long				msgB3;
		unsigned long		msgB4;
		long				msgB5;
		long				msgB6;
		long				msgB7;
	}BMP180_ParamType;
	//===结构体定义
	typedef struct _BMP180_HandleType					BMP180_HandleType;
	//===指针结构体定义
	typedef struct _BMP180_HandleType					*pBMP180_HandleType;
	//===HMC5883的数据结构体
	struct _BMP180_HandleType
	{
		BMP180_ParamType	msgParam;																					//---矫正参数
		INT32_T				msgDefaultTemp;																				//---未校正的温度值
		INT32_T				msgDefaultGasPress;																			//---未校正的气压值
		INT32_T				msgTemp;																					//---校正后的温度值
		INT32_T				msgGasPress;																				//---校正后的气压值
		float				msgAltitude;																				//---海拔高度
		I2C_HandleType		msgI2C;																						//---使用的I2C
		void(*pMsgDelayms)(UINT32_T delay);																				//---延时参数
	};
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////结构体定义---结束//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	

	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////配置宏定义---开始//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	
	//===定义的任务函数
	#define BMP180_TASK_ONE								pBmp180Device0													//---任务1
	#define BMP180_TASK_TWO								0																//---任务2
	#define BMP180_TASK_THREE							0																//---任务3
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////配置宏定义---开始//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	

	//===外部调用
	extern BMP180_HandleType							g_Bmp180Device0;
	extern pBMP180_HandleType							pBmp180Device0;

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*BMP180_CFG_H_ */
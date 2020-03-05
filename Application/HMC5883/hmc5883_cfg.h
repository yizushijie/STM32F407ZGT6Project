#ifndef HMC5883_CFG_H_
#define HMC5883_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include"complier_lib.h"
	#include "i2c_task.h"
	#include "gpio_task.h"
	#include "delay_task.h"
	//////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////寄存器定义---开始//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////
	//===寄存器
	#define	HMC5883_CRA_REG								0x00															//---配置寄存器A
	#define HMC5883_CRB_REG								0x01															//---配置寄存器B
	#define HMC5883_MR_REG								0x02															//---模式寄存器		
	#define HMC5883_DXMSB_REG							0x03															//---数据输出X MSB寄存器
	#define HMC5883_DXLSB_REG							0x04															//---数据输出X LSB寄存器		
	#define HMC5883_DZMLSB_REG							0x05															//---数据输出Z MSB寄存器
	#define HMC5883_DZLSB_REG							0x06															//---据输出Z LSB寄存器
	#define HMC5883_DYMSB_REG							0x07															//---据输出Y MSB寄存器
	#define HMC5883_DYLSB_REG							0x08															//---据输出Y LSB寄存器
	#define HMC5883_SB_REG								0x09															//---态寄存器
	#define HMC5883_IRA_REG								0x0A															//---别寄存器A
	#define HMC5883_IRB_REG								0x0B															//---别寄存器B
	#define MagnetcDeclination							4.43															//---上海所在的地磁偏角
	#define CALIB_THRESHOLD								0																//---校准阈值
	//===设备通讯地址
	#define HMC5883_WADDR								0x3C															//---设备的写地址
	#define HMC5883_RADDR								0x3E															//---设备的读地址
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////寄存器定义---结束//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////结构体定义---开始//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	
	//===结构体定义
	typedef struct _HMC5883_HandleType					HMC5883_HandleType;
	//===指针结构体定义
	typedef struct _HMC5883_HandleType					*pHMC5883_HandleType;
	//===HMC5883的数据结构体
	struct _HMC5883_HandleType
	{
		INT16_T				msgX;																						//---X轴方向数据
		INT16_T				msgOffsetX;																					//---X轴偏移
		INT16_T				msgZ;																						//---Z轴方向数据
		INT16_T				msgOffsetZ;																					//---Z轴偏移
		INT16_T				msgY;																						//---Y轴方向数据
		INT16_T				msgOffsetY;																					//---Y轴偏移
		float				msgAngle;																					//---当前角度，方位角,磁偏角
		GPIO_HandleType		msgDRDY;																					//---数据准备，中断引脚。内部被拉高。选项为连接，当数据位于输出寄存器上时会在低电位上停250us
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
	#define HMC5883_TASK_ONE							pHmc5883Device0													//---任务1
	#define HMC5883_TASK_TWO							0																//---任务2
	#define HMC5883_TASK_THREE							0																//---任务3
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////配置宏定义---开始//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	

	//===外部调用
	extern HMC5883_HandleType							g_Hmc5883Device0;
	extern pHMC5883_HandleType							pHmc5883Device0;

	//===函数定义
	UINT8_T HMC5883_I2C_Device0_Init(HMC5883_HandleType* HMC5883x);
	UINT8_T HMC5883_I2C_Device1_Init(HMC5883_HandleType* HMC5883x);
	UINT8_T HMC5883_I2C_Device2_Init(HMC5883_HandleType* HMC5883x);
	UINT8_T HMC5883_I2C_Init(HMC5883_HandleType* HMC5883x, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay),UINT32_T(*pFuncTimerTick)(void), UINT8_T isHWI2C);
	UINT8_T HMC5883_I2C_DeInit(HMC5883_HandleType* HMC5883x);
	UINT8_T HMC5883_I2C_WriteSingle(HMC5883_HandleType* HMC5883x, UINT8_T addr, UINT8_T val);
	UINT8_T HMC5883_I2C_ReadSingle(HMC5883_HandleType* HMC5883x, UINT8_T addr, UINT8_T* pVal);
	UINT8_T HMC5883_I2C_ReadBulk(HMC5883_HandleType* HMC5883x, UINT8_T addr, UINT8_T* pVal, UINT8_T length);
	UINT8_T HMC5883_I2C_ConfigInit(HMC5883_HandleType* HMC5883x);
	UINT8_T HMC5883_I2C_ReadRawData(HMC5883_HandleType* HMC5883x);
	void	HMC5883_I2C_CalibrateMag(HMC5883_HandleType* HMC5883x);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*HMC5883_CFG_H_ */
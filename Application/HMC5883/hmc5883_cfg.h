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
	//////////////////////////////////////////////////////////////////////////////////////

	//===配置寄存器A(Configuration Register A)
	#define	HMC5883_CRA_REG			0x00	
	//===配置寄存器B
	#define HMC5883_CRB_REG			0x01	
	//===模式寄存器
	#define HMC5883_MR_REG			0x02			
	//===数据输出X MSB寄存器
	#define HMC5883_DXMSB_REG		0x03		
	//===数据输出X LSB寄存器
	#define HMC5883_DXLSB_REG		0x04			
	//===数据输出Z MSB寄存器
	#define HMC5883_DZMLSB_REG		0x05		
	//==数据输出Z LSB寄存器
	#define HMC5883_DZLSB_REG		0x06		
	//==数据输出Y MSB寄存器
	#define HMC5883_DYMSB_REG		0x07	
	//==数据输出Y LSB寄存器
	#define HMC5883_DYLSB_REG		0x08	
	//==状态寄存器
	#define HMC5883_SB_REG			0x09	
	//==识别寄存器A
	#define HMC5883_IRA_REG			0x0A			
	//==识别寄存器B
	#define HMC5883_IRB_REG			0x0B	

	#define MagnetcDeclination		4.43 //Shanghai
	//===校准阈值
	#define CALIB_THRESHOLD			0

	//===结构体定义
	typedef struct _HMC5883_HandlerType					HMC5883_HandlerType;
	//===指针结构体定义
	typedef struct _HMC5883_HandlerType					* pHMC5883_HandlerType;

	//===AT24Cxx的数据结构体
	struct _HMC5883_HandlerType
	{
		INT16_T				msgX;						//---X轴方向数据
		INT16_T				msgOffsetX;					//---X轴偏移
		INT16_T				msgZ;						//---Z轴方向数据
		INT16_T				msgOffsetZ;					//---Z轴偏移
		INT16_T				msgY;						//---Y轴方向数据
		INT16_T				msgOffsetY;					//---Y轴偏移
		float				msgAngle;					//---当前角度，方位角
		GPIO_HandlerType	msgDRDY;					//---数据准备，中断引脚。内部被拉高。选项为连接，当数据位于输出寄存器上时会在低电位上停250us
		I2C_HandlerType		msgI2C;						//---使用的I2C
		void(*msgDelayms)(UINT32_T delay);			//---延时参数
	};

	//===定义的任务函数
	#define HMC5883_TASK_ONE							pHmc5883Device0
	#define HMC5883_TASK_TWO							0
	#define HMC5883_TASK_THREE							0
	
	//===外部调用
	extern HMC5883_HandlerType							g_Hmc5883Device0;
	extern pHMC5883_HandlerType							pHmc5883Device0;

	//===函数定义
	UINT8_T HMC5883_I2C_Device0_Init(HMC5883_HandlerType* HMC5883x);
	UINT8_T HMC5883_I2C_Device1_Init(HMC5883_HandlerType* HMC5883x);
	UINT8_T HMC5883_I2C_Device2_Init(HMC5883_HandlerType* HMC5883x);
	UINT8_T HMC5883_I2C_Init(HMC5883_HandlerType* HMC5883x, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT8_T isHWI2C);
	UINT8_T HMC5883_I2C_SingleWriteReg(HMC5883_HandlerType* HMC5883x, UINT8_T addr, UINT8_T val);
	UINT8_T HMC5883_I2C_SingleReadReg(HMC5883_HandlerType* HMC5883x, UINT8_T addr, UINT8_T* pVal);
	UINT8_T HMC5883_I2C_BurstReadReg(HMC5883_HandlerType* HMC5883x);
	UINT8_T HMC5883_ConfigInit(HMC5883_HandlerType* HMC5883x);

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*HMC5883_CFG_H_ */
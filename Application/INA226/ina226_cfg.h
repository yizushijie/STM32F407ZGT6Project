#ifndef INA226_CFG_H_
#define INA226_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include"complier_lib.h"
	#include "i2c_task.h"
	#include "gpio_task.h"
	//////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////寄存器定义---开始//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////
	//===配置寄存区--[0x4127]
	#define CONFIGURATION_REG							0x00
	//===采样电阻上的压降---[0x00000],满量程是81.92mV,最小单位是2.5uV
	#define SHUNT_VOLTAGE_REG							0x01
	//===总线电压---[0x00000],满量程是40.96V,最小单位是1.25mV
	#define BUS_VOLTAGE_REG								0x02
	//===功率寄存器---[0x00000]
	#define POWER_REG									0x03
	//===电流寄存器---[0x00000]
	#define CURRENT_REG									0x04
	//===校准寄存器---[0x00000]
	#define CALIBRATION_REG								0x05
	//===功能控制寄存器---[0x00000]
	#define MASK_ENABLE_REG								0x06
	//===设置的报警阈值---[0x00000]
	#define ALERT_LIMIT_REG								0x07
	//===制造商ID---[0x5449]
	#define MANUFACTURER_ID_REG							0xFE
	//===设备ID---[0x2260]
	#define DIE_ID_REG									0xFF

	//===使能过压
	#define SHUNT_OVER_VOLTAGE_ENABLE					(1<<15)
	//===不使能过压
	#define SHUNT_OVER_VOLTAGE_DISABLE					~(1<<15)
		//===使能欠压
	#define SHUNT_UNDER_VOLTAGE_ENABLE					(1<<14)
	//===不使能欠压
	#define SHUNT_UNDER_VOLTAGE_DISABLE					~(1<<14)

	//===使能过压
	#define BUS_OVER_VOLTAGE_ENABLE						(1<<13)
	//===不使能过压
	#define BUS_OVER_VOLTAGE_DISABLE					~(1<<13)
	//===使能欠压
	#define BUS_UNDER_VOLTAGE_ENABLE					(1<<12)
	//===不使能欠压
	#define BUS_UNDER_VOLTAGE_DISABLE					~(1<<12)

	//===使能功率阈值
	#define POWER_OVER_LIMIT_ENABLE						(1<<11)
	//===不使能功率阈值
	#define POWER_OVER_LIMIT_DISABLE					(1<<11)

	//===使能转换准备好标致
	#define CONVERSION_READY_ENABLE						(1<<10)
	//===不使能转换准备好标致
	#define CONVERSION_READY_DISABLE					(1<<10)
	
	//===报警端口低有效
	#define	ALERT_POLARITY_ACTIVE_LOW					~(1<<1)
	//===报警端口搞有效
	#define	ALERT_POLARITY_ACTIVE_HIGH					(1<<1)

	//===报警端口锁存使能
	#define	ALERT_LATCH_ENABLE							(1)
	//===报警端口锁存不使能
	#define ALERT_LATCH_DISABLE							0xFFFE
	//===配置平均转换的次数
	#define	AVERAGING_MODE_MASK							~(7<<9)
	#define	AVERAGING_MODE_1							(0<<9)
	#define	AVERAGING_MODE_4							(1<<9)
	#define	AVERAGING_MODE_16							(2<<9)
	#define	AVERAGING_MODE_64							(3<<9)
	#define	AVERAGING_MODE_128							(4<<9)
	#define	AVERAGING_MODE_256							(5<<9)
	#define	AVERAGING_MODE_512							(6<<9)
	#define	AVERAGING_MODE_1024							(7<<9)

	//===配置总线电压转换的时间
	#define BUS_VOLTAGE_CONVERSIOM_TIME_MASK			~(7<<6)
	#define BUS_VOLTAGE_CONVERSIOM_TIME_140_US			(0<<6)
	#define BUS_VOLTAGE_CONVERSIOM_TIME_204_US			(1<<6)
	#define BUS_VOLTAGE_CONVERSIOM_TIME_332_US			(2<<6)
	#define BUS_VOLTAGE_CONVERSIOM_TIME_588_US			(3<<6)
	#define BUS_VOLTAGE_CONVERSIOM_TIME_1100_US			(4<<6)
	#define BUS_VOLTAGE_CONVERSIOM_TIME_2116_US			(5<<6)
	#define BUS_VOLTAGE_CONVERSIOM_TIME_4156_US			(6<<6)
	#define BUS_VOLTAGE_CONVERSIOM_TIME_8244_US			(7<<6)

	//===配置采样电压转换的时间
	#define SHUNT_VOLTAGE_CONVERSIOM_TIME_MASK			~(7<<3)
	#define SHUNT_VOLTAGE_CONVERSIOM_TIME_140_US		(0<<3)
	#define SHUNT_VOLTAGE_CONVERSIOM_TIME_204_US		(1<<3)
	#define SHUNT_VOLTAGE_CONVERSIOM_TIME_332_US		(2<<3)
	#define SHUNT_VOLTAGE_CONVERSIOM_TIME_588_US		(3<<3)
	#define SHUNT_VOLTAGE_CONVERSIOM_TIME_1100_US		(4<<3)
	#define SHUNT_VOLTAGE_CONVERSIOM_TIME_2116_US		(5<<3)
	#define SHUNT_VOLTAGE_CONVERSIOM_TIME_4156_US		(6<<3)
	#define SHUNT_VOLTAGE_CONVERSIOM_TIME_8244_US		(7<<3)

	//===配置操作模式
	#define OPERATING_MODE_MASK							~(7<<0)
	#define OPERATING_MODE_POWER_DOWN_1					(0<<0)
	#define OPERATING_MODE_SHUNT_VOLTAGE_TRIG			(1<<0)
	#define OPERATING_MODE_BUS_VOLTAGE_TRIG				(2<<0)
	#define OPERATING_MODE_SHUNT_BUS_VOLTAGE_TRIG		(3<<0)
	#define OPERATING_MODE_POWER_DOWN_2					(4<<0)
	#define OPERATING_MODE_SHUNT_VOLTAGE_CONT			(5<<0)
	#define OPERATING_MODE_BUS_VOLTAGE_CONT				(6<<0)
	#define OPERATING_MODE_SHUNT_BUS_VOLTAGE_CONT		(7<<0)
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////寄存器定义---结束//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////配置参数---开始///////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	

	//===总线电压量程每BIT对应的电压值，单位是毫伏
	#define INA226_RANG_BUS_VOLTAGE_MV_BIT				1.25f
	//===采样电阻上电压量程每BIT对应的电压值，单位是微伏
	#define INA226_RANG_SHUNT_VOLTAGE_UV_BIT			2.5f
	//===采样电阻的大小,单位是毫欧
	#define INA226_SAMPLE_RES_MR						1
	//===INA226的电流最大采集量程，这个和校准寄存器有关
	#define INA226_RANG_CURRENT_MA_MAX					15000
	//===INA226的电流量程每BIT对应电流值，单位是微安安
	#define INA226_RANG_CURRENT_UA_BIT_X1				(UINT16_T)( INA226_RANG_CURRENT_MA_MAX*1000/(1<<15))
	//===校准寄存器的值
	#define INA226_CALIB_REG_DEFAULT_X1					(UINT16_T)( 5120*1000/(INA226_RANG_CURRENT_UA_BIT_X1*INA226_SAMPLE_RES_MR) )
	//===
	#define INA226_RANG_CURRENT_UA_BIT_X2				(UINT16_T)( INA226_RANG_CURRENT_UA_BIT_X1*2 )
	//===
	#define INA226_CALIB_REG_DEFAULT_X2					(UINT16_T)( INA226_CALIB_REG_DEFAULT_X1*2 )
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////配置参数---结束////////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	

	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////结构体定义---开始//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	
	//===结构体定义
	typedef struct _INA226_HandleType					INA226_HandleType;
	//===指针结构体定义
	typedef struct _INA226_HandleType					* pINA226_HandleType;
	//===AT24Cxx的数据结构体
	struct _INA226_HandleType
	{
		UINT16_T			msgCFGReg;					//---配置寄存器
		UINT16_T			msgMaskReg;					//---功能配置寄存器
		UINT16_T			msgShuntReg;				//---采样电压寄存器
		UINT16_T			msgBusVReg;					//---总线电压寄存器
		UINT16_T			msgPowerReg;				//---功率寄存器
		UINT16_T			msgCurrentReg;				//---采样电流寄存器
		UINT16_T			msgCalibReg;				//---校准寄存器
		float				msgBusmV;					//---总线电压，单位毫伏
		float				msgShuntuV;					//---采样电阻电压,单位微伏
		float				msgShuntuA;					//---采样电阻电流，单位微安
		float				msgPowermW;					//---负载的功耗，单位微瓦
		GPIO_HandleType		msgAlert;					//---报警端口的配置，INA226是开漏模式，需要外接上拉电阻
		I2C_HandleType		msgI2C;						//---使用的I2C
	};
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////结构体定义---结束//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	

	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////配置宏定义---开始//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	

	//===定义的任务函数
	#define INA226_TASK_ONE								pIna226Device0
	#define INA226_TASK_TWO								0
	#define INA226_TASK_THREE							0
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////配置宏定义---开始//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	

	//===外部调用
	extern INA226_HandleType							g_Ina226Device0 ;
	extern pINA226_HandleType							pIna226Device0  ;

	//===函数定义
	UINT8_T INA226_I2C_Device0_Init(INA226_HandleType* INA226x);
	UINT8_T INA226_I2C_Device1_Init(INA226_HandleType* INA226x);
	UINT8_T INA226_I2C_Device2_Init(INA226_HandleType* INA226x);
	UINT8_T INA226_I2C_Init(INA226_HandleType* INA226x, void(*pFuncDelayus)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHWI2C);
	UINT8_T INA226_I2C_DeInit(INA226_HandleType* INA226x);
	UINT8_T INA226_I2C_ConfigInit(INA226_HandleType* INA226x);
	UINT8_T INA226_I2C_ReadDieID(INA226_HandleType* INA226x);
	UINT8_T INA226_I2C_ReadManuID(INA226_HandleType* INA226x);
	UINT8_T INA226_I2C_GetBusVoltage(INA226_HandleType* INA226x);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*INA226_CFG_H_ */
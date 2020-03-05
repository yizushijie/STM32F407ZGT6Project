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
	//////////////////////////�Ĵ�������---��ʼ//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////
	//===���üĴ���--[0x4127]
	#define CONFIGURATION_REG							0x00
	//===���������ϵ�ѹ��---[0x00000],��������81.92mV,��С��λ��2.5uV
	#define SHUNT_VOLTAGE_REG							0x01
	//===���ߵ�ѹ---[0x00000],��������40.96V,��С��λ��1.25mV
	#define BUS_VOLTAGE_REG								0x02
	//===���ʼĴ���---[0x00000]
	#define POWER_REG									0x03
	//===�����Ĵ���---[0x00000]
	#define CURRENT_REG									0x04
	//===У׼�Ĵ���---[0x00000]
	#define CALIBRATION_REG								0x05
	//===���ܿ��ƼĴ���---[0x00000]
	#define MASK_ENABLE_REG								0x06
	//===���õı�����ֵ---[0x00000]
	#define ALERT_LIMIT_REG								0x07
	//===������ID---[0x5449]
	#define MANUFACTURER_ID_REG							0xFE
	//===�豸ID---[0x2260]
	#define DIE_ID_REG									0xFF

	//===ʹ�ܹ�ѹ
	#define SHUNT_OVER_VOLTAGE_ENABLE					(1<<15)
	//===��ʹ�ܹ�ѹ
	#define SHUNT_OVER_VOLTAGE_DISABLE					~(1<<15)
		//===ʹ��Ƿѹ
	#define SHUNT_UNDER_VOLTAGE_ENABLE					(1<<14)
	//===��ʹ��Ƿѹ
	#define SHUNT_UNDER_VOLTAGE_DISABLE					~(1<<14)

	//===ʹ�ܹ�ѹ
	#define BUS_OVER_VOLTAGE_ENABLE						(1<<13)
	//===��ʹ�ܹ�ѹ
	#define BUS_OVER_VOLTAGE_DISABLE					~(1<<13)
	//===ʹ��Ƿѹ
	#define BUS_UNDER_VOLTAGE_ENABLE					(1<<12)
	//===��ʹ��Ƿѹ
	#define BUS_UNDER_VOLTAGE_DISABLE					~(1<<12)

	//===ʹ�ܹ�����ֵ
	#define POWER_OVER_LIMIT_ENABLE						(1<<11)
	//===��ʹ�ܹ�����ֵ
	#define POWER_OVER_LIMIT_DISABLE					(1<<11)

	//===ʹ��ת��׼���ñ���
	#define CONVERSION_READY_ENABLE						(1<<10)
	//===��ʹ��ת��׼���ñ���
	#define CONVERSION_READY_DISABLE					(1<<10)
	
	//===�����˿ڵ���Ч
	#define	ALERT_POLARITY_ACTIVE_LOW					~(1<<1)
	//===�����˿ڸ���Ч
	#define	ALERT_POLARITY_ACTIVE_HIGH					(1<<1)

	//===�����˿�����ʹ��
	#define	ALERT_LATCH_ENABLE							(1)
	//===�����˿����治ʹ��
	#define ALERT_LATCH_DISABLE							0xFFFE
	//===����ƽ��ת���Ĵ���
	#define	AVERAGING_MODE_MASK							~(7<<9)
	#define	AVERAGING_MODE_1							(0<<9)
	#define	AVERAGING_MODE_4							(1<<9)
	#define	AVERAGING_MODE_16							(2<<9)
	#define	AVERAGING_MODE_64							(3<<9)
	#define	AVERAGING_MODE_128							(4<<9)
	#define	AVERAGING_MODE_256							(5<<9)
	#define	AVERAGING_MODE_512							(6<<9)
	#define	AVERAGING_MODE_1024							(7<<9)

	//===�������ߵ�ѹת����ʱ��
	#define BUS_VOLTAGE_CONVERSIOM_TIME_MASK			~(7<<6)
	#define BUS_VOLTAGE_CONVERSIOM_TIME_140_US			(0<<6)
	#define BUS_VOLTAGE_CONVERSIOM_TIME_204_US			(1<<6)
	#define BUS_VOLTAGE_CONVERSIOM_TIME_332_US			(2<<6)
	#define BUS_VOLTAGE_CONVERSIOM_TIME_588_US			(3<<6)
	#define BUS_VOLTAGE_CONVERSIOM_TIME_1100_US			(4<<6)
	#define BUS_VOLTAGE_CONVERSIOM_TIME_2116_US			(5<<6)
	#define BUS_VOLTAGE_CONVERSIOM_TIME_4156_US			(6<<6)
	#define BUS_VOLTAGE_CONVERSIOM_TIME_8244_US			(7<<6)

	//===���ò�����ѹת����ʱ��
	#define SHUNT_VOLTAGE_CONVERSIOM_TIME_MASK			~(7<<3)
	#define SHUNT_VOLTAGE_CONVERSIOM_TIME_140_US		(0<<3)
	#define SHUNT_VOLTAGE_CONVERSIOM_TIME_204_US		(1<<3)
	#define SHUNT_VOLTAGE_CONVERSIOM_TIME_332_US		(2<<3)
	#define SHUNT_VOLTAGE_CONVERSIOM_TIME_588_US		(3<<3)
	#define SHUNT_VOLTAGE_CONVERSIOM_TIME_1100_US		(4<<3)
	#define SHUNT_VOLTAGE_CONVERSIOM_TIME_2116_US		(5<<3)
	#define SHUNT_VOLTAGE_CONVERSIOM_TIME_4156_US		(6<<3)
	#define SHUNT_VOLTAGE_CONVERSIOM_TIME_8244_US		(7<<3)

	//===���ò���ģʽ
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
	//////////////////////////�Ĵ�������---����//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////���ò���---��ʼ///////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	

	//===���ߵ�ѹ����ÿBIT��Ӧ�ĵ�ѹֵ����λ�Ǻ���
	#define INA226_RANG_BUS_VOLTAGE_MV_BIT				1.25f
	//===���������ϵ�ѹ����ÿBIT��Ӧ�ĵ�ѹֵ����λ��΢��
	#define INA226_RANG_SHUNT_VOLTAGE_UV_BIT			2.5f
	//===��������Ĵ�С,��λ�Ǻ�ŷ
	#define INA226_SAMPLE_RES_MR						1
	//===INA226�ĵ������ɼ����̣������У׼�Ĵ����й�
	#define INA226_RANG_CURRENT_MA_MAX					15000
	//===INA226�ĵ�������ÿBIT��Ӧ����ֵ����λ��΢����
	#define INA226_RANG_CURRENT_UA_BIT_X1				(UINT16_T)( INA226_RANG_CURRENT_MA_MAX*1000/(1<<15))
	//===У׼�Ĵ�����ֵ
	#define INA226_CALIB_REG_DEFAULT_X1					(UINT16_T)( 5120*1000/(INA226_RANG_CURRENT_UA_BIT_X1*INA226_SAMPLE_RES_MR) )
	//===
	#define INA226_RANG_CURRENT_UA_BIT_X2				(UINT16_T)( INA226_RANG_CURRENT_UA_BIT_X1*2 )
	//===
	#define INA226_CALIB_REG_DEFAULT_X2					(UINT16_T)( INA226_CALIB_REG_DEFAULT_X1*2 )
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////���ò���---����////////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	

	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////�ṹ�嶨��---��ʼ//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	
	//===�ṹ�嶨��
	typedef struct _INA226_HandleType					INA226_HandleType;
	//===ָ��ṹ�嶨��
	typedef struct _INA226_HandleType					* pINA226_HandleType;
	//===AT24Cxx�����ݽṹ��
	struct _INA226_HandleType
	{
		UINT16_T			msgCFGReg;					//---���üĴ���
		UINT16_T			msgMaskReg;					//---�������üĴ���
		UINT16_T			msgShuntReg;				//---������ѹ�Ĵ���
		UINT16_T			msgBusVReg;					//---���ߵ�ѹ�Ĵ���
		UINT16_T			msgPowerReg;				//---���ʼĴ���
		UINT16_T			msgCurrentReg;				//---���������Ĵ���
		UINT16_T			msgCalibReg;				//---У׼�Ĵ���
		float				msgBusmV;					//---���ߵ�ѹ����λ����
		float				msgShuntuV;					//---���������ѹ,��λ΢��
		float				msgShuntuA;					//---���������������λ΢��
		float				msgPowermW;					//---���صĹ��ģ���λ΢��
		GPIO_HandleType		msgAlert;					//---�����˿ڵ����ã�INA226�ǿ�©ģʽ����Ҫ�����������
		I2C_HandleType		msgI2C;						//---ʹ�õ�I2C
	};
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////�ṹ�嶨��---����//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	

	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////���ú궨��---��ʼ//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	

	//===�����������
	#define INA226_TASK_ONE								pIna226Device0
	#define INA226_TASK_TWO								0
	#define INA226_TASK_THREE							0
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////���ú궨��---��ʼ//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	

	//===�ⲿ����
	extern INA226_HandleType							g_Ina226Device0 ;
	extern pINA226_HandleType							pIna226Device0  ;

	//===��������
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
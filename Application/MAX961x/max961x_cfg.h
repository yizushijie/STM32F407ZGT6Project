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
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////�Ĵ�������---��ʼ//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////
	//===���ص���[0000]
	#define MAX961X_REG_CSA_DATA_MSB_ADDR				0x00
	#define MAX961X_REG_CSA_DATA_LSB_ADDR				0x01
	//===�����ѹ[0000]
	#define MAX961X_REG_RS_DATA_MSB_ADDR				0x02
	#define MAX961X_REG_RS_DATA_LSB_ADDR				0x03
	//===out�ε�ѹ[0000]
	#define MAX961X_REG_OUT_DATA_MSB_ADDR				0x04
	#define MAX961X_REG_OUT_DATA_LSB_ADDR				0x05
	//===�趨�ĵ�ѹ[0000]
	#define MAX961X_REG_SET_DATA_MSB_ADDR				0x06
	#define MAX961X_REG_SET_DATA_LSB_ADDR				0x07
	//===�ڲ��¶�[8000]
	#define MAX961X_REG_TEMP_DATA_MSB_ADDR				0x08
	#define MAX961X_REG_TEMP_DATA_LSB_ADDR				0x09
	//===�ڲ��������ƼĴ���[0000]
	#define MAX961X_REG_CONTROL_REG1					0x0A
	#define MAX961X_REG_CONTROL_REG2					0x0B
	
	//===ͨ����ȡ����
	#define MAX961X_READ_CHANNEL_1X_GAIN_CURRENT		0x00
	#define MAX961X_READ_CHANNEL_4X_GAIN_CURRENT		0x01
	#define MAX961X_READ_CHANNEL_8X_GAIN_CURRENT		0x02
	#define MAX961X_READ_CHANNEL_INPUT_VOLTAGE			0x03
	#define MAX961X_READ_CHANNEL_OUTPUT_VOLTAGE			0x04
	#define MAX961X_READ_CHANNEL_SET_VOLTAGE			0x05
	#define MAX961X_READ_CHANNEL_TEMPERATURE			0x06
	#define MAX961X_fast_READ_ALL_CHANNEL				0x07
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////�Ĵ�������---����//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////���ò���---��ʼ///////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	
	//===��ѹ��С�ֱ���
	#define MAX961X_VOLTAGE_STEP_MV						14
	//===������С�ֱ���
	#define MAX961X_CURRENT_STEP_MA						0.1075
	//===�¶���С�ֱ���			
	#define MAX961X_TEMPERATURE_STEP_C					0.48
	//===��������Ĵ�С,��λ�Ǻ�ŷ
	#define	MAX961X_SAMPLE_RES_MR						20
	//===�豸��д��ַ
	#define	MAX961X_WADDR								0xE0
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////���ò���---����////////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	

	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////�ṹ�嶨��---��ʼ//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	
	//===�ṹ�嶨��
	typedef struct _MAX961X_HandleType					MAX961X_HandleType;
	//===ָ��ṹ�嶨��
	typedef struct _MAX961X_HandleType					* pMAX961X_HandleType;
	//===AT24Cxx�����ݽṹ��
	struct _MAX961X_HandleType
	{
		float			msgRSVoltagemV;																					//---��ѹmV
		float			msgOutputVoltagemV;																				//---��ѹmV
		float			msgSetVoltagemV;																				//---��ѹmV
		float			msgRSCurrentmA;																					//---����mA
		float			msgTemperatureC;																				//---�¶ȡ�
		UINT8_T			msgID;																							//---Ĭ����0x80
		I2C_HandleType	msgI2C;																							//---ʹ�õ�I2C
	};
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////�ṹ�嶨��---����//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	

	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////���ú궨��---��ʼ//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	
	//===�����������
	#define MAX961X_TASK_ONE							pMax961xDevice0
	#define MAX961X_TASK_TWO							0
	#define MAX961X_TASK_THREE							0
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////���ú궨��---��ʼ//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	

	//===�ⲿ���ýӿ�
	extern MAX961X_HandleType							g_Max961xDevice0;
	extern pMAX961X_HandleType							pMax961xDevice0;

	//===��������
	UINT8_T MAX961X_I2C_Device0_Init(MAX961X_HandleType* MAX961x);
	UINT8_T MAX961X_I2C_Device1_Init(MAX961X_HandleType* MAX961x);
	UINT8_T MAX961X_I2C_Device2_Init(MAX961X_HandleType* MAX961x);
	UINT8_T MAX961X_I2C_Init(MAX961X_HandleType* MAX961x, void(*pFuncDelayus)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHWI2C);
	UINT8_T MAX961X_I2C_DeInit(MAX961X_HandleType* MAX961x);
	UINT8_T MAX961X_I2C_WriteSingle(MAX961X_HandleType* MAX961x, UINT8_T addr, UINT8_T val);
	UINT8_T MAX961X_I2C_WriteBulk(MAX961X_HandleType* MAX961x, UINT8_T addr, UINT8_T length, UINT8_T* pVal);
	UINT8_T MAX961X_I2C_ReadSingle(MAX961X_HandleType* MAX961x, UINT8_T addr, UINT8_T* pVal);
	UINT8_T MAX961X_I2C_ReadBulk(MAX961X_HandleType* MAX961x, UINT8_T addr, UINT8_T length, UINT8_T* pVal);
	UINT8_T MAX961X_I2C_CheckDevice(MAX961X_HandleType* MAX961x);
	UINT8_T MAX961X_I2C_ReadRSVoltage(MAX961X_HandleType* MAX961x);
	UINT8_T MAX961X_I2C_ReadRSCurrent(MAX961X_HandleType* MAX961x, UINT8_T currentGain);
	UINT8_T MAX961X_I2C_ReadOutVoltage(MAX961X_HandleType* MAX961x);
	UINT8_T MAX961X_I2C_ReadSetVoltage(MAX961X_HandleType* MAX961x);
	UINT8_T MAX961X_I2C_ReadTemp(MAX961X_HandleType* MAX961x);
	UINT8_T MAX961X_I2C_ReadAll(MAX961X_HandleType* MAX961x, UINT8_T currentGain);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*MAX961X_CFG_H_ */
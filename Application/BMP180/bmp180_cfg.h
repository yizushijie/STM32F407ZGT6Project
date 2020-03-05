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
	//////////////////////////�Ĵ�������---��ʼ//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////
	//===�豸ͨѶ��ַ
	#define BMP180_WADDR								0xEE															//---�豸��д��ַ
	#define BMP180_RADDR								0xEF															//---�豸�Ķ���ַ
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
	//////////////////////////�Ĵ�������---����//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////�ṹ�嶨��---��ʼ//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	
	//===BMP180У������				 					
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
	//===�ṹ�嶨��
	typedef struct _BMP180_HandleType					BMP180_HandleType;
	//===ָ��ṹ�嶨��
	typedef struct _BMP180_HandleType					*pBMP180_HandleType;
	//===HMC5883�����ݽṹ��
	struct _BMP180_HandleType
	{
		BMP180_ParamType	msgParam;																					//---��������
		INT32_T				msgDefaultTemp;																				//---δУ�����¶�ֵ
		INT32_T				msgDefaultGasPress;																			//---δУ������ѹֵ
		INT32_T				msgTemp;																					//---У������¶�ֵ
		INT32_T				msgGasPress;																				//---У�������ѹֵ
		float				msgAltitude;																				//---���θ߶�
		I2C_HandleType		msgI2C;																						//---ʹ�õ�I2C
		void(*pMsgDelayms)(UINT32_T delay);																				//---��ʱ����
	};
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////�ṹ�嶨��---����//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	

	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////���ú궨��---��ʼ//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	
	//===�����������
	#define BMP180_TASK_ONE								pBmp180Device0													//---����1
	#define BMP180_TASK_TWO								0																//---����2
	#define BMP180_TASK_THREE							0																//---����3
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////���ú궨��---��ʼ//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	

	//===�ⲿ����
	extern BMP180_HandleType							g_Bmp180Device0;
	extern pBMP180_HandleType							pBmp180Device0;

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*BMP180_CFG_H_ */
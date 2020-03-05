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
	//////////////////////////�Ĵ�������---��ʼ//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////
	//===�Ĵ���
	#define	HMC5883_CRA_REG								0x00															//---���üĴ���A
	#define HMC5883_CRB_REG								0x01															//---���üĴ���B
	#define HMC5883_MR_REG								0x02															//---ģʽ�Ĵ���		
	#define HMC5883_DXMSB_REG							0x03															//---�������X MSB�Ĵ���
	#define HMC5883_DXLSB_REG							0x04															//---�������X LSB�Ĵ���		
	#define HMC5883_DZMLSB_REG							0x05															//---�������Z MSB�Ĵ���
	#define HMC5883_DZLSB_REG							0x06															//---�����Z LSB�Ĵ���
	#define HMC5883_DYMSB_REG							0x07															//---�����Y MSB�Ĵ���
	#define HMC5883_DYLSB_REG							0x08															//---�����Y LSB�Ĵ���
	#define HMC5883_SB_REG								0x09															//---̬�Ĵ���
	#define HMC5883_IRA_REG								0x0A															//---��Ĵ���A
	#define HMC5883_IRB_REG								0x0B															//---��Ĵ���B
	#define MagnetcDeclination							4.43															//---�Ϻ����ڵĵش�ƫ��
	#define CALIB_THRESHOLD								0																//---У׼��ֵ
	//===�豸ͨѶ��ַ
	#define HMC5883_WADDR								0x3C															//---�豸��д��ַ
	#define HMC5883_RADDR								0x3E															//---�豸�Ķ���ַ
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////�Ĵ�������---����//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////�ṹ�嶨��---��ʼ//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	
	//===�ṹ�嶨��
	typedef struct _HMC5883_HandleType					HMC5883_HandleType;
	//===ָ��ṹ�嶨��
	typedef struct _HMC5883_HandleType					*pHMC5883_HandleType;
	//===HMC5883�����ݽṹ��
	struct _HMC5883_HandleType
	{
		INT16_T				msgX;																						//---X�᷽������
		INT16_T				msgOffsetX;																					//---X��ƫ��
		INT16_T				msgZ;																						//---Z�᷽������
		INT16_T				msgOffsetZ;																					//---Z��ƫ��
		INT16_T				msgY;																						//---Y�᷽������
		INT16_T				msgOffsetY;																					//---Y��ƫ��
		float				msgAngle;																					//---��ǰ�Ƕȣ���λ��,��ƫ��
		GPIO_HandleType		msgDRDY;																					//---����׼�����ж����š��ڲ������ߡ�ѡ��Ϊ���ӣ�������λ������Ĵ�����ʱ���ڵ͵�λ��ͣ250us
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
	#define HMC5883_TASK_ONE							pHmc5883Device0													//---����1
	#define HMC5883_TASK_TWO							0																//---����2
	#define HMC5883_TASK_THREE							0																//---����3
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////���ú궨��---��ʼ//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	

	//===�ⲿ����
	extern HMC5883_HandleType							g_Hmc5883Device0;
	extern pHMC5883_HandleType							pHmc5883Device0;

	//===��������
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
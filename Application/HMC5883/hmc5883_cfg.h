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

	//===���üĴ���A(Configuration Register A)
	#define	HMC5883_CRA_REG			0x00	
	//===���üĴ���B
	#define HMC5883_CRB_REG			0x01	
	//===ģʽ�Ĵ���
	#define HMC5883_MR_REG			0x02			
	//===�������X MSB�Ĵ���
	#define HMC5883_DXMSB_REG		0x03		
	//===�������X LSB�Ĵ���
	#define HMC5883_DXLSB_REG		0x04			
	//===�������Z MSB�Ĵ���
	#define HMC5883_DZMLSB_REG		0x05		
	//==�������Z LSB�Ĵ���
	#define HMC5883_DZLSB_REG		0x06		
	//==�������Y MSB�Ĵ���
	#define HMC5883_DYMSB_REG		0x07	
	//==�������Y LSB�Ĵ���
	#define HMC5883_DYLSB_REG		0x08	
	//==״̬�Ĵ���
	#define HMC5883_SB_REG			0x09	
	//==ʶ��Ĵ���A
	#define HMC5883_IRA_REG			0x0A			
	//==ʶ��Ĵ���B
	#define HMC5883_IRB_REG			0x0B	

	#define MagnetcDeclination		4.43 //Shanghai
	//===У׼��ֵ
	#define CALIB_THRESHOLD			0

	//===�ṹ�嶨��
	typedef struct _HMC5883_HandlerType					HMC5883_HandlerType;
	//===ָ��ṹ�嶨��
	typedef struct _HMC5883_HandlerType					* pHMC5883_HandlerType;

	//===AT24Cxx�����ݽṹ��
	struct _HMC5883_HandlerType
	{
		INT16_T				msgX;						//---X�᷽������
		INT16_T				msgOffsetX;					//---X��ƫ��
		INT16_T				msgZ;						//---Z�᷽������
		INT16_T				msgOffsetZ;					//---Z��ƫ��
		INT16_T				msgY;						//---Y�᷽������
		INT16_T				msgOffsetY;					//---Y��ƫ��
		float				msgAngle;					//---��ǰ�Ƕȣ���λ��
		GPIO_HandlerType	msgDRDY;					//---����׼�����ж����š��ڲ������ߡ�ѡ��Ϊ���ӣ�������λ������Ĵ�����ʱ���ڵ͵�λ��ͣ250us
		I2C_HandlerType		msgI2C;						//---ʹ�õ�I2C
		void(*msgDelayms)(UINT32_T delay);			//---��ʱ����
	};

	//===�����������
	#define HMC5883_TASK_ONE							pHmc5883Device0
	#define HMC5883_TASK_TWO							0
	#define HMC5883_TASK_THREE							0
	
	//===�ⲿ����
	extern HMC5883_HandlerType							g_Hmc5883Device0;
	extern pHMC5883_HandlerType							pHmc5883Device0;

	//===��������
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
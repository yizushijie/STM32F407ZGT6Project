#ifndef AT24CXX_CFG_H_
#define AT24CXX_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
////����ڵ�ҳ�ķ�Χ�ڣ��洢��ַ�ۼӣ���������ҳ������ַ���洢��ַ�ص�ҳ��ʼ����
////���Զ���������������д���ԣ����Ĳ����ֽ���Ϊ8��
////����Ҫ�������ֽ����ݳ���8�ֽڣ�����Ҫ���з�ҳ��������д����һҳ����ʼ�洢��ַ
/////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "gpio_task.h"
	#include "i2c_task.h"
	#include "my_malloc.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===֧�ֵ�ϵ���ͺ�
	#define AT24C01							0	//---16PX8B		---16ҳ��ÿҳ8�ֽ�
	#define AT24C02							1	//---32PX8B		---32ҳ��ÿҳ8�ֽ�
	#define AT24C04							2	//---32PX16B	---32ҳ��ÿҳ16�ֽ�
	#define AT24C08							3	//---64PX16B	---64ҳ��ÿҳ16�ֽ�
	#define AT24C16							4	//---128PX16B	---128ҳ��ÿҳ16�ֽ�
	#define AT24C32							5	//---128PX32B	---128ҳ��ÿҳ32�ֽ�
	#define AT24C64							6	//---256PX32B	---256ҳ��ÿҳ32�ֽ�
	#define AT24C128						7	//---256PX64B	---256ҳ��ÿҳ64�ֽ�
	#define AT24C256						8	//---512PX64B	---512ҳ��ÿҳ64�ֽ�
	#define AT24C512						9	//---512PX128B	---512ҳ��ÿҳ128�ֽ�
	
	//===�����Ƿ�ʹ��ȫ�ֱ��������ramС��оƬ���޷�ʹ���Զ����ڴ������
	//#define USE_GOBAL_RAM
	//===����꿪��
	#ifdef USE_GOBAL_RAM
		//===����AT24Cxx��ÿҳֱ�����ֵ
		#define	AT24CXX_PAGE_BYTE_MAX_SIZE		128
	#endif
	//===�ṹ�嶨��
	typedef struct _AT24CXX_HandlerType AT24CXX_HandlerType;
	//===ָ��ṹ�嶨��
	typedef struct _AT24CXX_HandlerType *pAT24CXX_HandlerType;

	//===I2Cģʽʹ��Ӳ��д����ģʽ
	#define AT24CXX_I2C_USE_HWWP

	//===AT24Cxx�����ݽṹ��
	struct _AT24CXX_HandlerType
	{
		UINT8_T  msgAT24CXXType;											//---ʹ�õ��豸
		UINT8_T  msgAT24CXXPageByte;										//---ÿҳ�ֽ���
		UINT16_T msgAT24CXXPageNum;											//---ҳ��
		#ifdef USE_GOBAL_RAM
			UINT8_T msgPageByteBuffer[AT24CXX_PAGE_BYTE_MAX_SIZE];				//---���建����
		#endif
#ifdef AT24CXX_I2C_USE_HWWP
		GPIO_HandlerType msgWP;												//---д�������ƶ˿ڣ�0---д���������ܣ�1---д����ʹ��
#endif
		I2C_HandlerType msgI2C;												//---ʹ�õ�I2C
		void(*msgDelayms)(UINT32_T delay);								//---������ʱ����,��̽�������Ҫ�ȴ�5ms
	};

	//===�����������
	#define AT24CXX_TASK_ONE		pAT24cxxDevice0
	#define AT24CXX_TASK_TWO		0
	#define AT24CXX_TASK_THREE		0

	//===�ⲿ���ýӿ�
	extern AT24CXX_HandlerType		g_AT24cxxDevice0;
	extern pAT24CXX_HandlerType		pAT24cxxDevice0;

	//===��������
	UINT8_T AT24CXX_I2C_Init(AT24CXX_HandlerType *AT24CXXx, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT8_T isHWI2C);
	UINT8_T AT24CXX_I2C_Device0_Init(AT24CXX_HandlerType *AT24CXXx);
	UINT8_T AT24CXX_I2C_Device1_Init(AT24CXX_HandlerType *AT24CXXx);
	UINT8_T AT24CXX_I2C_Device2_Init(AT24CXX_HandlerType *AT24CXXx);
	UINT8_T AT24CXX_I2C_DeInit(AT24CXX_HandlerType *AT24CXXx);
	UINT8_T AT24CXX_SWI2C_WriteOneByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T val);
	UINT8_T AT24CXX_SWI2C_WritePageByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T pageAddr, UINT8_T *pVal, UINT16_T length);
	UINT8_T AT24CXX_HWI2C_WriteOneByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T val);
	UINT8_T AT24CXX_HWI2C_WritePageByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T pageAddr, UINT8_T *pVal, UINT16_T length);
	UINT8_T AT24CXX_I2C_WriteOneByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T val);
	UINT8_T AT24CXX_I2C_WritePageByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length);
	UINT8_T AT24CXX_I2C_WriteData(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length);
	UINT8_T AT24CXX_SWI2C_ReadOneByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal);
	UINT8_T AT24CXX_SWI2C_ReadPageByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length);
	UINT8_T AT24CXX_HWI2C_ReadOneByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal);
	UINT8_T AT24CXX_HWI2C_ReadPageByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length);
	UINT8_T AT24CXX_I2C_ReadOneByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal);
	UINT8_T AT24CXX_I2C_ReadPageByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length);
	UINT8_T AT24CXX_I2C_ReadData(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length);
	UINT8_T AT24CXX_I2C_EraseChip(AT24CXX_HandlerType *AT24CXXx);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* AT24CXX_CFG_H_ */
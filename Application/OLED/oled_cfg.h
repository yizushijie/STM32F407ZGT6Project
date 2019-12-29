#ifndef OLED_CFG_H_
#define OLED_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "i2c_task.h"
	#include "delay_task.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===OLED���Դ�
	//===��Ÿ�ʽ����.
	//---[0]0 1 2 3 ... 127
	//---[1]0 1 2 3 ... 127
	//---[2]0 1 2 3 ... 127
	//---[3]0 1 2 3 ... 127
	//---[4]0 1 2 3 ... 127
	//---[5]0 1 2 3 ... 127
	//---[6]0 1 2 3 ... 127
	//---[7]0 1 2 3 ... 127
	//===�����С
	#define OLED_PAGE_SIZE							8
	#define OLED_MAX_COL							128
	#define OLED_MAX_ROW							64
	
	#define OLED_XLevelL							0x02
	#define OLED_XLevelH							0x10
	#define OLED_Brightness							0xFF
	#define OLED_X_WIDTH							128
	#define OLED_Y_WIDTH							64
	
	//===�ṹ�嶨��
	typedef struct _OLED_IIC_HandlerType			OLED_IIC_HandlerType;

	//===ָ��ṹ�嶨��
	typedef struct _OLED_IIC_HandlerType			*pOLED_IIC_HandlerType;

	//===OLED�����ݽṹ��
	struct _OLED_IIC_HandlerType
	{
		GPIO_HandlerType	msgRST;					//---��λ�˿�
		I2C_HandlerType		msgI2C;					//---ʹ�õ�I2C
	};

	//===�����������
	#define OLED_TASK_ONE							pOLEDI2CDevice0
	#define OLED_TASK_TWO							0
	#define OLED_TASK_THREE							0
	
	extern const UINT8_T SYN_LOGO[];

	//===�ⲿ���ýӿ�
	extern OLED_IIC_HandlerType						g_OLEDI2CDevice0;
	extern pOLED_IIC_HandlerType					pOLEDI2CDevice0;

	//===��������
	UINT8_T OLED_I2C_Init(OLED_IIC_HandlerType *OLEDx, void(*pFuncDelayus)(UINT32_T delay), UINT8_T isHWI2C);
	UINT8_T OLED_I2C_WriteCmd(OLED_IIC_HandlerType *OLEDx, UINT8_T cmd);
	UINT8_T OLED_I2C_WriteData(OLED_IIC_HandlerType *OLEDx, UINT8_T cmd);
	void OLED_I2C_DisplayON(OLED_IIC_HandlerType *OLEDx);
	void OLED_I2C_DisplayOFF(OLED_IIC_HandlerType *OLEDx);
	void OLED_I2C_Fill(OLED_IIC_HandlerType *OLEDx, UINT8_T dat);
	void OLED_I2C_Clear(OLED_IIC_HandlerType *OLEDx);
	void OLED_I2C_SetPos(OLED_IIC_HandlerType *OLEDx, UINT8_T xPos, UINT8_T yPos);
	void OLED_I2C_HWInit(OLED_IIC_HandlerType *OLEDx);
	void OLED_I2C_DrawBMP(OLED_IIC_HandlerType *OLEDx, UINT8_T x0Pos, UINT8_T y0Pos, UINT8_T x1Pos, UINT8_T y1Pos, UINT8_T BMP[]);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*OLED_CFG_H_ */
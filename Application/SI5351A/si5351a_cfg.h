#ifndef SI5351A_CFG_H_
#define SI5351A_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	//===������ͷ�ļ�
	#include"complier_lib.h"
	#include "i2c_task.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===����ʱ��Ƶ��
	#define SI5351A_CLK_HZ							25000000ULL		
	//===���໷����������Сʱ��
	#define SI5351A_PLL_MAX_HZ						900000000ULL
	#define SI5351A_PLL_MIN_HZ						600000000ULL
	//===��������Ƶ��
	#define SI5351A_CLKOUT_MAX_HZ					150000000ULL
	#define SI5351A_CLKOUT_MIN_HZ					8000ULL
	//===������ͨ������
	#define SI5351A_CLKOUT_CHANNEL_SIZE				3
	
	//===�Ĵ�����ַ
	#define SI5351A_REG_STATUS_ADDR					0
	#define SI5351A_REG_CLKEN_ADDR					3
	#define SI5351A_REG_CLKIN_ADDR					15
	#define SI5351A_REG_CLK0_ADDR					16			// Register definitions
	#define SI5351A_REG_CLK1_ADDR					17
	#define SI5351A_REG_CLK2_ADDR					18
	#define SI5351A_REG_CLK3_0_DISABLE_STATE_ADDR	24
	#define SI5351A_REG_MSNA_ADDR					26
	#define SI5351A_REG_MSNB_ADDR					34
	#define SI5351A_REG_MS0_ADDR					42
	#define SI5351A_REG_MS1_ADDR					50
	#define SI5351A_REG_MS2_ADDR					58
	#define SI5351A_REG_SSC_EN_ADDR					149
	#define SI5351A_REG_SSDN_P1_ADDR				153
	#define SI5351A_REG_VCXO_PARAME_ADDR			162
	#define SI5351A_REG_PLL_RST_ADDR				177
	#define SI5351A_REG_CRYSTAL_LOAD_ADDR			183
	#define SI5351A_REG_FANOUT_ENABLE_ADDR			187

	//===����ʱ������	   CRYSTAL_LOAD
	#define SI5351A_CLKIN_DIV_1						(0<<6)
	#define SI5351A_CLKIN_DIV_2						(1<<6)
	#define SI5351A_CLKIN_DIV_4						(2<<6)
	#define SI5351A_CLKIN_DIV_8						(3<<6)
	#define SI5351A_PLLB_SRC						(1<<3)
	#define SI5351A_PLLA_SRC						(1<<2)

	//===���ʱ�ӿ�������
	#define SI5351A_CLK_PWR							(1<<7)
	#define SI5351A_CLK_MS_INT						(1<<6)
	#define SI5351A_CLK_MS_SRC						(1<<5)
	#define SI5351A_CLK_INV							(1<<4)
	#define SI5351A_CLK_SRC_MS						(3<<2)
	#define SI5351A_CLK_SRC_XTAL					(0<<2)
	#define SI5351A_CLK_SRC_CLKIN					(1<<2)
	#define SI5351A_CLK_IDRV_2mA					(0)
	#define SI5351A_CLK_IDRV_4mA					(1)
	#define SI5351A_CLK_IDRV_6mA					(2)
	#define SI5351A_CLK_IDRV_8mA					(3)

	//===���ʱ�ӵķ�Ƶ��
	#define SI5351A_CLKOUT_DIV_1					(0<<4)	
	#define SI5351A_CLKOUT_DIV_2					(1<<4)
	#define SI5351A_CLKOUT_DIV_4					(2<<4)
	#define SI5351A_CLKOUT_DIV_8					(3<<4)
	#define SI5351A_CLKOUT_DIV_16					(4<<4)
	#define SI5351A_CLKOUT_DIV_32					(5<<4)
	#define SI5351A_CLKOUT_DIV_64					(6<<4)
	#define SI5351A_CLKOUT_DIV_128					(7<<4)

	//===ʱ������������ص���
	#define SI5351A_CRYSTAL_LOAD_6pF				(1<<6)|0x12
	#define SI5351A_CRYSTAL_LOAD_8pF				(2<<6)|0x12
	#define SI5351A_CRYSTAL_LOAD_10pF				(3<<6)|0x12

	//===��λPLL����
	#define SI5351A_PLL_RST_B						(1<<7)
	#define SI5351A_PLL_RST_A						(1<<5)

	//---����CLK�Ĳ�ʹ��״̬
	

	//===�����޲���
	#define SI5351A_PLL_A_MIN						15
	#define SI5351A_PLL_A_MAX						90
	#define SI5351A_PLL_B_MAX						(SI5351A_PLL_C_MAX-1)
	#define SI5351A_PLL_C_MAX						1048575
	#define SI5351A_MS_A_MIN						6
	#define SI5351A_MS_A_MAX						1800

	//===д����
	#define SI5351A_WADDR							0xC0	
	//===������
	#define SI5351A_RADDR							0xC1	

	//===�ṹ�嶨��
	typedef struct _SI5351A_HandlerType				SI5351A_HandlerType;
	//===ָ��ṹ�嶨��
	typedef struct _SI5351A_HandlerType				*pSI5351A_HandlerType;

	//===����ṹ
	struct _SI5351A_HandlerType
	{
		UINT8_T msgClockCTRL[SI5351A_CLKOUT_CHANNEL_SIZE];		//---CLK���ͨ�������üĴ���
		UINT8_T msgIsResetPll;									//---�Ƿ��������֮��λPLL��1---��λ,0---����λ
		I2C_HandlerType msgI2C;									//---ʹ�õ�I2C�豸
	};

	//===�����������
	#define SI5351A_TASK_ONE						pSi5351aDevice0
	#define SI5351A_TASK_TWO						0
	#define SI5351A_TASK_THREE						0
	
	//===�ⲿ���ýӿ�
	extern SI5351A_HandlerType						g_Si5351aDevice0;
	extern pSI5351A_HandlerType						pSi5351aDevice0;
	
	//===��������
	UINT8_T SI5351A_I2C_WriteSingle(SI5351A_HandlerType* SI5351Ax, UINT8_T addr, UINT8_T val);
	UINT8_T SI5351A_I2C_ReadSingle(SI5351A_HandlerType* SI5351Ax, UINT8_T addr, UINT8_T* pVal);
	UINT8_T SI5351A_I2C_WriteBulk(SI5351A_HandlerType* SI5351Ax, UINT8_T addr, UINT8_T* pVal, UINT8_T length);
	UINT8_T SI5351A_I2C_ReadBulk(SI5351A_HandlerType* SI5351Ax, UINT8_T addr, UINT8_T* pVal, UINT8_T length);
	UINT8_T SI5351A_I2C_Init(SI5351A_HandlerType* SI5351Ax, void(*pFuncDelayus)(UINT32_T delay), UINT8_T isHWI2C);
	UINT8_T SI5351A_I2C_DeInit(SI5351A_HandlerType* SI5351Ax);
	UINT8_T SI5351A_I2C_START(SI5351A_HandlerType* SI5351Ax);
	UINT8_T SI5351A_PLLRST(SI5351A_HandlerType* SI5351Ax, UINT8_T clkChannel);
	UINT8_T SI5351A_ReadID(SI5351A_HandlerType* SI5351Ax);
	UINT8_T SI5351A_SetFreqHz(SI5351A_HandlerType* SI5351Ax, UINT8_T clkChannel, UINT64_T freq);
	UINT8_T SI5351A_SetFreqKHz(SI5351A_HandlerType* SI5351Ax, UINT8_T clkChannel, float freqKHz);
	UINT8_T SI5351A_SetFreqMHz(SI5351A_HandlerType* SI5351Ax, UINT8_T clkChannel, float freqMHz);
	UINT8_T SI5351A_SetClockChannelIDRV(SI5351A_HandlerType* SI5351Ax, UINT8_T clkChannel, UINT8_T idrv);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*SI5351A_CFG_H_ */
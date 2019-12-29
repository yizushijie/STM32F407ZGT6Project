#ifndef RFASKHW_CFG_H_
#define RFASKHW_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "gpio_task.h"
	//////////////////////////////////////////////////////////////////////////////////////
	
	//===ʹ�õ�ĸ��İ汾��V1��V2���������
	#define LNW_FT_ASK_MBOARD_VERSION		2

	//===YSEL0A
	#define YSEL0A_PORT_D					GPIOE
	#define YSEL0A_BIT_D					LL_GPIO_PIN_7
	
	//===YSEL1A
	#define YSEL1A_PORT_D					GPIOE
	#define YSEL1A_BIT_D					LL_GPIO_PIN_8
	
	//===YSEL2A
	#define YSEL2A_PORT_D					GPIOE
	#define YSEL2A_BIT_D					LL_GPIO_PIN_9
	
	//===YSEL3A
	#define YSEL3A_PORT_D					GPIOE
	#define YSEL3A_BIT_D					LL_GPIO_PIN_10
	
	//===YSEL0B
	#define YSEL0B_PORT_D					GPIOB
	#define YSEL0B_BIT_D					LL_GPIO_PIN_8
	
	//===YSEL1B
	#define YSEL1B_PORT_D					GPIOB
	#define YSEL1B_BIT_D					LL_GPIO_PIN_9
	
	//===YSEL2B
	#define YSEL2B_PORT_D					GPIOE
	#define YSEL2B_BIT_D					LL_GPIO_PIN_0
	
	//===YSEL3B
	#define YSEL3B_PORT_D					GPIOE
	#define YSEL3B_BIT_D					LL_GPIO_PIN_1
	
	//===YSEL0C
	#define YSEL0C_PORT_D					GPIOD
	#define YSEL0C_BIT_D					LL_GPIO_PIN_7
	
	//===YSEL1C
	#define YSEL1C_PORT_D					GPIOD
	#define YSEL1C_BIT_D					LL_GPIO_PIN_6
	
	//===YSEL2C
	#define YSEL2C_PORT_D					GPIOD
	#define YSEL2C_BIT_D					LL_GPIO_PIN_5
	
	//===YSEL3C
	#define YSEL3C_PORT_D					GPIOD
	#define YSEL3C_BIT_D					LL_GPIO_PIN_4
	
	//===YSEL0D
	#define YSEL0D_PORT_D					GPIOD
	#define YSEL0D_BIT_D					LL_GPIO_PIN_15
	
	//===YSEL1D
	#define YSEL1D_PORT_D					GPIOD
	#define YSEL1D_BIT_D					LL_GPIO_PIN_14
	
	//===YSEL2D
	#define YSEL2D_PORT_D					GPIOD
	#define YSEL2D_BIT_D					LL_GPIO_PIN_13
	
	//===YSEL3D
	#define YSEL3D_PORT_D					GPIOD
	#define YSEL3D_BIT_D					LL_GPIO_PIN_12
	
	//===SITEA��SOT��BIN��EOT,RST,DEC����
	//===��ʼ
	#define SOTA_PORT_D						GPIOE
	#define	SOTA_BIT_D						LL_GPIO_PIN_11
	
	//===����
	#define EOTA_PORT_D						GPIOE
	#define	EOTA_BIT_D						LL_GPIO_PIN_12
	
	//===�����־ 0---ͨ����1---ʧЧ
	#define BINA_PORT_D						GPIOE
	#define	BINA_BIT_D						LL_GPIO_PIN_13
	
	//===���봥����0---�������룬1---������
	#define RSTA_PORT_D						GPIOE
	#define	RSTA_BIT_D						LL_GPIO_PIN_14
	
	//===����ɹ���־��0---����ɹ���1---����ʧ��
	#define DECA_PASS_PORT_D				GPIOE
	#define	DECA_PASS_BIT_D					LL_GPIO_PIN_15
	
	//===SITEB��SOT��BIN��EOT,RST,DEC����
	//===��ʼ
	#define SOTB_PORT_D						GPIOE
	#define	SOTB_BIT_D						LL_GPIO_PIN_2
	
	//===����
	#define EOTB_PORT_D						GPIOE
	#define	EOTB_BIT_D						LL_GPIO_PIN_3
	
	//===�����־ 0---ͨ����1---ʧЧ
	#define BINB_PORT_D						GPIOE
	#define	BINB_BIT_D						LL_GPIO_PIN_4
	
	//===���봥����0---�������룬1---������
	#define RSTB_PORT_D						GPIOE
	#define	RSTB_BIT_D						LL_GPIO_PIN_5
	
	//===����ɹ���־��0---����ɹ���1---����ʧ��
	#define DECB_PASS_PORT_D				GPIOE
	#define	DECB_PASS_BIT_D					LL_GPIO_PIN_6
	
	//===SITEC��SOT��BIN��EOT,RST,DEC����
	//===��ʼ
	#define SOTC_PORT_D						GPIOD
	#define	SOTC_BIT_D						LL_GPIO_PIN_3
	
	//===����
	#define EOTC_PORT_D						GPIOD
	#define	EOTC_BIT_D						LL_GPIO_PIN_2
	
	//===�����־ 0---ͨ����1---ʧЧ
	#define BINC_PORT_D						GPIOD
	#define	BINC_BIT_D						LL_GPIO_PIN_1
	
	//===���봥����0---�������룬1---������
	#define RSTC_PORT_D						GPIOD
	#define	RSTC_BIT_D						LL_GPIO_PIN_0
	
	//===����ɹ���־��0---����ɹ���1---����ʧ��
	#define DECC_PASS_PORT_D				GPIOC
	#define	DECC_PASS_BIT_D					LL_GPIO_PIN_12
	
	//===SITED��SOT��BIN��EOT,RST,DEC����
	//===��ʼ
	#define SOTD_PORT_D						GPIOD
	#define	SOTD_BIT_D						LL_GPIO_PIN_11
	
	//===����
	#define EOTD_PORT_D						GPIOD
	#define	EOTD_BIT_D						LL_GPIO_PIN_10
	
	//===�����־ 0---ͨ����1---ʧЧ
	#define BIND_PORT_D						GPIOD
	#define	BIND_BIT_D						LL_GPIO_PIN_9
	
	//===���봥����0---�������룬1---������
	#define RSTD_PORT_D						GPIOD
	#define	RSTD_BIT_D						LL_GPIO_PIN_8
	
	//===����ɹ���־��0---����ɹ���1---����ʧ��
	#define DECD_PASS_PORT_D				GPIOB
	#define	DECD_PASS_BIT_D					LL_GPIO_PIN_15
	
	//===YSEL0A
	#define YSEL0A_PORT						DECA_PASS_PORT_D
	#define YSEL0A_BIT						DECA_PASS_BIT_D
	
	//===YSEL1A
	#define YSEL1A_PORT						RSTA_PORT_D
	#define YSEL1A_BIT						RSTA_BIT_D
	
	//===YSEL2A
	#define YSEL2A_PORT						BINA_PORT_D
	#define YSEL2A_BIT						BINA_BIT_D
	
	//===YSEL3A
	#define YSEL3A_PORT						EOTA_PORT_D
	#define YSEL3A_BIT						EOTA_BIT_D
	
	//===YSEL0B
	#define YSEL0B_PORT						DECB_PASS_PORT_D
	#define YSEL0B_BIT						DECB_PASS_BIT_D
	
	//===YSEL1B
	#define YSEL1B_PORT						RSTB_PORT_D
	#define YSEL1B_BIT						RSTB_BIT_D
	
	//===YSEL2B
	#define YSEL2B_PORT						BINB_PORT_D
	#define YSEL2B_BIT						BINB_BIT_D
	
	//===YSEL3B
	#define YSEL3B_PORT						EOTB_PORT_D
	#define YSEL3B_BIT						EOTB_BIT_D
	
	//===YSEL0C
	#define YSEL0C_PORT						YSEL0C_PORT_D//GPIOD
	#define YSEL0C_BIT						YSEL0C_BIT_D//LL_GPIO_PIN_7
	
	//===YSEL1C
	#define YSEL1C_PORT						YSEL1C_PORT_D//GPIOD
	#define YSEL1C_BIT						YSEL1C_BIT_D //LL_GPIO_PIN_6
	
	//===YSEL2C
	#define YSEL2C_PORT						YSEL2C_PORT_D//GPIOD
	#define YSEL2C_BIT						YSEL2C_BIT_D //LL_GPIO_PIN_5
	
	//===YSEL3C
	#define YSEL3C_PORT						YSEL3C_PORT_D//GPIOD
	#define YSEL3C_BIT						YSEL3C_BIT_D //LL_GPIO_PIN_4
	
	//===YSEL0D
	#define YSEL0D_PORT						YSEL0D_PORT_D//GPIOD
	#define YSEL0D_BIT						YSEL0D_BIT_D //LL_GPIO_PIN_15
	
	//===YSEL1D
	#define YSEL1D_PORT						YSEL1D_PORT_D//GPIOD
	#define YSEL1D_BIT						YSEL1D_BIT_D //LL_GPIO_PIN_14
	
	//===YSEL2D
	#define YSEL2D_PORT						YSEL2D_PORT_D//GPIOD
	#define YSEL2D_BIT						YSEL2D_BIT_D //LL_GPIO_PIN_13
	
	//===YSEL3D
	#define YSEL3D_PORT						YSEL3D_PORT_D//GPIOD
	#define YSEL3D_BIT						YSEL3D_BIT_D //LL_GPIO_PIN_12
	
	//===SITEA��SOT��BIN��EOT,RST,DEC����
	//===��ʼ
	#define SOTA_PORT						SOTA_PORT_D
	#define	SOTA_BIT						SOTA_BIT_D
	
	//===����
	#define EOTA_PORT						YSEL3A_PORT_D
	#define	EOTA_BIT						YSEL3A_BIT_D
	
	//===�����־ 0---ͨ����1---ʧЧ
	#define BINA_PORT						YSEL2A_PORT_D
	#define	BINA_BIT						YSEL2A_BIT_D
	
	//===���봥����0---�������룬1---������
	#define RSTA_PORT						YSEL1A_PORT_D
	#define	RSTA_BIT						YSEL1A_BIT_D
	
	//===����ɹ���־��0---����ɹ���1---����ʧ��
	#if (LNW_FT_ASK_MBOARD_VERSION==1)
		#define DECA_PASS_PORT				BINA_PORT //YSEL0A_PORT_D
		#define	DECA_PASS_BIT				BINA_BIT  //YSEL0A_BIT_D
	#elif (LNW_FT_ASK_MBOARD_VERSION==2)
		#define DECA_PASS_PORT				YSEL0A_PORT_D
		#define	DECA_PASS_BIT				YSEL0A_BIT_D
	#else
		#error "��֧�ֵ�ĸ��汾!"
	#endif
	
	//===SITEB��SOT��BIN��EOT,RST,DEC����
	//===��ʼ
	#define SOTB_PORT						SOTB_PORT_D
	#define	SOTB_BIT						SOTB_BIT_D
	
	//===����
	#define EOTB_PORT						YSEL3B_PORT_D
	#define	EOTB_BIT						YSEL3B_BIT_D
	
	//===�����־ 0---ͨ����1---ʧЧ
	#define BINB_PORT						YSEL2B_PORT_D
	#define	BINB_BIT						YSEL2B_BIT_D
	
	//===���봥����0---�������룬1---���� ��
	#define RSTB_PORT						YSEL1B_PORT_D
	#define	RSTB_BIT						YSEL1B_BIT_D
	
	//===����ɹ���־��0---����ɹ���1--- ����ʧ��
	#if (LNW_FT_ASK_MBOARD_VERSION==1)
		#define DECB_PASS_PORT				BINB_PORT//YSEL0B_PORT_D
		#define	DECB_PASS_BIT				BINB_BIT //YSEL0B_BIT_D
	#elif (LNW_FT_ASK_MBOARD_VERSION==2)
		#define DECB_PASS_PORT				YSEL0B_PORT_D
		#define	DECB_PASS_BIT				YSEL0B_BIT_D
	#else
		#error "��֧�ֵ�ĸ��汾!"
	#endif
	//===SITEC��SOT��BIN��EOT,RST,DEC����
	//===��ʼ
	#define SOTC_PORT						SOTC_PORT_D //GPIOD
	#define	SOTC_BIT						SOTC_BIT_D  //LL_GPIO_PIN_3
	
	//===����
	#define EOTC_PORT						EOTC_PORT_D//GPIOD
	#define	EOTC_BIT						EOTC_BIT_D //LL_GPIO_PIN_2
	
	//===�����־ 0---ͨ����1---ʧЧ
	#define BINC_PORT						BINC_PORT_D//GPIOD
	#define	BINC_BIT						BINC_BIT_D//LL_GPIO_PIN_1
	
	//===���봥����0---�������룬1---������
	#define RSTC_PORT						RSTC_PORT_D//GPIOD
	#define	RSTC_BIT						RSTC_BIT_D//LL_GPIO_PIN_0
	
	//===����ɹ���־��0---����ɹ���1---����ʧ��
	#if (LNW_FT_ASK_MBOARD_VERSION==1)
		#define DECC_PASS_PORT				BINC_PORT//DECC_PASS_PORT_D//GPIOC
		#define	DECC_PASS_BIT				BINC_BIT//DECC_PASS_BIT_D//LL_GPIO_PIN_12
	#elif (LNW_FT_ASK_MBOARD_VERSION==2)
		#define DECC_PASS_PORT				DECC_PASS_PORT_D//BINC_PORT//GPIOC
		#define	DECC_PASS_BIT				DECC_PASS_BIT_D//BINC_BIT//LL_GPIO_PIN_12
	#else
		#error "��֧�ֵ�ĸ��汾!"
	#endif
	
	//===SITED��SOT��BIN��EOT,RST,DEC����
	//===��ʼ
	#define SOTD_PORT						SOTD_PORT_D//GPIOD
	#define	SOTD_BIT						SOTD_BIT_D //LL_GPIO_PIN_11
	
	//===����
	#define EOTD_PORT						EOTD_PORT_D//GPIOD
	#define	EOTD_BIT						EOTD_BIT_D //LL_GPIO_PIN_10
	
	//===�����־ 0---ͨ����1---ʧЧ
	#define BIND_PORT						BIND_PORT_D//GPIOD
	#define	BIND_BIT						BIND_BIT_D //LL_GPIO_PIN_9
	
	//===���봥����0---�������룬1---������
	#define RSTD_PORT						RSTD_PORT_D//GPIOD
	#define	RSTD_BIT						RSTD_BIT_D//LL_GPIO_PIN_8
	
	//===����ɹ���־��0---����ɹ���1---����ʧ��
	#if (LNW_FT_ASK_MBOARD_VERSION==1)
		#define DECD_PASS_PORT				BIND_PORT//DECD_PASS_PORT_D//GPIOB
		#define	DECD_PASS_BIT				BIND_BIT//DECD_PASS_BIT_D//LL_GPIO_PIN_15
	#elif (LNW_FT_ASK_MBOARD_VERSION==2)
		#define DECD_PASS_PORT				DECD_PASS_PORT_D //BIND_PORT//GPIOB
		#define	DECD_PASS_BIT				DECD_PASS_BIT_D  //BIND_BIT//LL_GPIO_PIN_15
	#else
		#error "��֧�ֵ�ĸ��汾!"
	#endif
	
	//===����ͨ��A�Ĳ�������˿�
	#define DECA_WAVE_PORT					GPIOA
	#define DECA_WAVE_BIT					LL_GPIO_PIN_11
	
	//===����ͨ��B�Ĳ�������˿�
	#define DECB_WAVE_PORT					GPIOA
	#define DECB_WAVE_BIT					LL_GPIO_PIN_12
	
	//===����ͨ��C�Ĳ�������˿�
	#define DECC_WAVE_PORT					GPIOC
	#define DECC_WAVE_BIT					LL_GPIO_PIN_10
	
	//===����ͨ��D�Ĳ�������˿�
	#define DECD_WAVE_PORT					GPIOC
	#define DECD_WAVE_BIT					LL_GPIO_PIN_11
	
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*RFASKHW_CFG_H_ */

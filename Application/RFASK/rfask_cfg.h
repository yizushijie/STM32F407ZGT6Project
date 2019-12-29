#ifndef RFASK_CFG_H_
#define RFASK_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "gpio_task.h"
	#include "delay_task.h"
	#include "rfaskhw_cfg.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===ʱ��A���ʹ�ܶ�
	#define CLKA_CTR_PORT								GPIOA
	#define CLKA_CTR_BIT								LL_GPIO_PIN_5
	#define CLKA_CTR_STATE								GPIO_GET_STATE(CLKA_CTR_PORT,CLKA_CTR_BIT)
	#define CLKA_CTR_WRITE								GPIO_SET_WRITE(CLKA_CTR_PORT,CLKA_CTR_BIT)
	#define CLKA_CTR_READ								GPIO_SET_READ( CLKA_CTR_PORT,CLKA_CTR_BIT)
	#define CLKA_CTR_OUT_0								GPIO_OUT_0(    CLKA_CTR_PORT,CLKA_CTR_BIT)
	#define CLKA_CTR_OUT_1								GPIO_OUT_1(    CLKA_CTR_PORT,CLKA_CTR_BIT)
	#define CLKA_CTR_OUT_C								GPIO_OUT_C(    CLKA_CTR_PORT,CLKA_CTR_BIT)
	#define CLKA_FREQ_ON								CLKA_CTR_OUT_0
	#define CLKA_FREQ_OFF								CLKA_CTR_OUT_1
	
	//===ʱ��B���ʹ�ܶ�
	#define CLKB_CTR_PORT								GPIOA
	#define CLKB_CTR_BIT								LL_GPIO_PIN_4
	#define CLKB_CTR_STATE								GPIO_GET_STATE(CLKB_CTR_PORT,CLKB_CTR_BIT)
	#define CLKB_CTR_WRITE								GPIO_SET_WRITE(CLKB_CTR_PORT,CLKB_CTR_BIT)
	#define CLKB_CTR_READ								GPIO_SET_READ( CLKB_CTR_PORT,CLKB_CTR_BIT)
	#define CLKB_CTR_OUT_0								GPIO_OUT_0(    CLKB_CTR_PORT,CLKB_CTR_BIT)
	#define CLKB_CTR_OUT_1								GPIO_OUT_1(    CLKB_CTR_PORT,CLKB_CTR_BIT)
	#define CLKB_CTR_OUT_C								GPIO_OUT_C(    CLKB_CTR_PORT,CLKB_CTR_BIT)
	#define CLKB_FREQ_ON								CLKB_CTR_OUT_0
	#define CLKB_FREQ_OFF								CLKB_CTR_OUT_1
	
	//===ʱ��C���ʹ�ܶ�
	#define CLKC_CTR_PORT								GPIOA
	#define CLKC_CTR_BIT								LL_GPIO_PIN_7
	#define CLKC_CTR_STATE								GPIO_GET_STATE(CLKC_CTR_PORT,CLKC_CTR_BIT)
	#define CLKC_CTR_WRITE								GPIO_SET_WRITE(CLKC_CTR_PORT,CLKC_CTR_BIT)
	#define CLKC_CTR_READ								GPIO_SET_READ( CLKC_CTR_PORT,CLKC_CTR_BIT)
	#define CLKC_CTR_OUT_0								GPIO_OUT_0(    CLKC_CTR_PORT,CLKC_CTR_BIT)
	#define CLKC_CTR_OUT_1								GPIO_OUT_1(    CLKC_CTR_PORT,CLKC_CTR_BIT)
	#define CLKC_CTR_OUT_C								GPIO_OUT_C(    CLKC_CTR_PORT,CLKC_CTR_BIT)
	#define CLKC_FREQ_ON								CLKC_CTR_OUT_0
	#define CLKC_FREQ_OFF								CLKC_CTR_OUT_1
	
	//===ʱ��D���ʹ�ܶ�
	#define CLKD_CTR_PORT								GPIOA
	#define CLKD_CTR_BIT								LL_GPIO_PIN_6
	#define CLKD_CTR_STATE								GPIO_GET_STATE(CLKD_CTR_PORT,CLKD_CTR_BIT)
	#define CLKD_CTR_WRITE								GPIO_SET_WRITE(CLKD_CTR_PORT,CLKD_CTR_BIT)
	#define CLKD_CTR_READ								GPIO_SET_READ( CLKD_CTR_PORT,CLKD_CTR_BIT)
	#define CLKD_CTR_OUT_0								GPIO_OUT_0(    CLKD_CTR_PORT,CLKD_CTR_BIT)
	#define CLKD_CTR_OUT_1								GPIO_OUT_1(    CLKD_CTR_PORT,CLKD_CTR_BIT)
	#define CLKD_CTR_OUT_C								GPIO_OUT_C(    CLKD_CTR_PORT,CLKD_CTR_BIT)
	#define CLKD_FREQ_ON								CLKD_CTR_OUT_0
	#define CLKD_FREQ_OFF								CLKD_CTR_OUT_1
	
	//===ʱ��ȫ�������
	#define CLK_FREQ_ON									( CLKA_FREQ_ON,CLKB_FREQ_ON,CLKC_FREQ_ON,CLKD_FREQ_ON )
	#define CLK_FREQ_OFF								( CLKA_FREQ_OFF,CLKB_FREQ_OFF,CLKC_FREQ_OFF,CLKD_FREQ_OFF )
	
	//===YSEL1_A������
	#define YSEL0A_CTR_PORT								YSEL0A_PORT	//GPIOE
	#define YSEL0A_CTR_BIT								YSEL0A_BIT	//LL_GPIO_PIN_7
	#define YSEL0A_CTR_STATE							GPIO_GET_STATE(YSEL0A_CTR_PORT,YSEL0A_CTR_BIT)
	#define YSEL0A_CTR_WRITE							GPIO_SET_WRITE(YSEL0A_CTR_PORT,YSEL0A_CTR_BIT)
	#define YSEL0A_CTR_READ								GPIO_SET_READ( YSEL0A_CTR_PORT,YSEL0A_CTR_BIT)
	#define YSEL0A_CTR_OUT_0							GPIO_OUT_0(    YSEL0A_CTR_PORT,YSEL0A_CTR_BIT)
	#define YSEL0A_CTR_OUT_1							GPIO_OUT_1(    YSEL0A_CTR_PORT,YSEL0A_CTR_BIT)
	#define YSEL0A_CTR_OUT_C							GPIO_OUT_C(    YSEL0A_CTR_PORT,YSEL0A_CTR_BIT)
	
	//===YSEL2_A������
	#define YSEL1A_CTR_PORT								YSEL1A_PORT	//GPIOE
	#define YSEL1A_CTR_BIT								YSEL1A_BIT	//LL_GPIO_PIN_8
	#define YSEL1A_CTR_STATE							GPIO_GET_STATE(YSEL1A_CTR_PORT,YSEL1A_CTR_BIT)
	#define YSEL1A_CTR_WRITE							GPIO_SET_WRITE(YSEL1A_CTR_PORT,YSEL1A_CTR_BIT)
	#define YSEL1A_CTR_READ								GPIO_SET_READ( YSEL1A_CTR_PORT,YSEL1A_CTR_BIT)
	#define YSEL1A_CTR_OUT_0							GPIO_OUT_0(    YSEL1A_CTR_PORT,YSEL1A_CTR_BIT)
	#define YSEL1A_CTR_OUT_1							GPIO_OUT_1(    YSEL1A_CTR_PORT,YSEL1A_CTR_BIT)
	#define YSEL1A_CTR_OUT_C							GPIO_OUT_C(    YSEL1A_CTR_PORT,YSEL1A_CTR_BIT)
	
	//===YSEL3_A������
	#define YSEL2A_CTR_PORT								YSEL2A_PORT	//GPIOE
	#define YSEL2A_CTR_BIT								YSEL2A_BIT	//LL_GPIO_PIN_9
	#define YSEL2A_CTR_STATE							GPIO_GET_STATE(YSEL2A_CTR_PORT,YSEL2A_CTR_BIT)
	#define YSEL2A_CTR_WRITE							GPIO_SET_WRITE(YSEL2A_CTR_PORT,YSEL2A_CTR_BIT)
	#define YSEL2A_CTR_READ								GPIO_SET_READ( YSEL2A_CTR_PORT,YSEL2A_CTR_BIT)
	#define YSEL2A_CTR_OUT_0							GPIO_OUT_0(    YSEL2A_CTR_PORT,YSEL2A_CTR_BIT)
	#define YSEL2A_CTR_OUT_1							GPIO_OUT_1(    YSEL2A_CTR_PORT,YSEL2A_CTR_BIT)
	#define YSEL2A_CTR_OUT_C							GPIO_OUT_C(    YSEL2A_CTR_PORT,YSEL2A_CTR_BIT)
	
	//===YSEL4_A������
	#define YSEL3A_CTR_PORT								YSEL3A_PORT	//GPIOE
	#define YSEL3A_CTR_BIT								YSEL3A_BIT	//LL_GPIO_PIN_10
	#define YSEL3A_CTR_STATE							GPIO_GET_STATE(YSEL3A_CTR_PORT,YSEL3A_CTR_BIT)
	#define YSEL3A_CTR_WRITE							GPIO_SET_WRITE(YSEL3A_CTR_PORT,YSEL3A_CTR_BIT)
	#define YSEL3A_CTR_READ								GPIO_SET_READ( YSEL3A_CTR_PORT,YSEL3A_CTR_BIT)
	#define YSEL3A_CTR_OUT_0							GPIO_OUT_0(    YSEL3A_CTR_PORT,YSEL3A_CTR_BIT)
	#define YSEL3A_CTR_OUT_1							GPIO_OUT_1(    YSEL3A_CTR_PORT,YSEL3A_CTR_BIT)
	#define YSEL3A_CTR_OUT_C							GPIO_OUT_C(    YSEL3A_CTR_PORT,YSEL3A_CTR_BIT)
	
	//===YSEL1_B������
	#define YSEL0B_CTR_PORT								YSEL0B_PORT	//GPIOB
	#define YSEL0B_CTR_BIT								YSEL0B_BIT	//LL_GPIO_PIN_8
	#define YSEL0B_CTR_STATE							GPIO_GET_STATE(YSEL0B_CTR_PORT,YSEL0B_CTR_BIT)
	#define YSEL0B_CTR_WRITE							GPIO_SET_WRITE(YSEL0B_CTR_PORT,YSEL0B_CTR_BIT)
	#define YSEL0B_CTR_READ								GPIO_SET_READ( YSEL0B_CTR_PORT,YSEL0B_CTR_BIT)
	#define YSEL0B_CTR_OUT_0							GPIO_OUT_0(    YSEL0B_CTR_PORT,YSEL0B_CTR_BIT)
	#define YSEL0B_CTR_OUT_1							GPIO_OUT_1(    YSEL0B_CTR_PORT,YSEL0B_CTR_BIT)
	#define YSEL0B_CTR_OUT_C							GPIO_OUT_C(    YSEL0B_CTR_PORT,YSEL0B_CTR_BIT)
	
	//===YSEL2_B������
	#define YSEL1B_CTR_PORT								YSEL1B_PORT	//GPIOB
	#define YSEL1B_CTR_BIT								YSEL1B_BIT	//LL_GPIO_PIN_9
	#define YSEL1B_CTR_STATE							GPIO_GET_STATE(YSEL1B_CTR_PORT,YSEL1B_CTR_BIT)
	#define YSEL1B_CTR_WRITE							GPIO_SET_WRITE(YSEL1B_CTR_PORT,YSEL1B_CTR_BIT)
	#define YSEL1B_CTR_READ								GPIO_SET_READ( YSEL1B_CTR_PORT,YSEL1B_CTR_BIT)
	#define YSEL1B_CTR_OUT_0							GPIO_OUT_0(    YSEL1B_CTR_PORT,YSEL1B_CTR_BIT)
	#define YSEL1B_CTR_OUT_1							GPIO_OUT_1(    YSEL1B_CTR_PORT,YSEL1B_CTR_BIT)
	#define YSEL1B_CTR_OUT_C							GPIO_OUT_C(    YSEL1B_CTR_PORT,YSEL1B_CTR_BIT)
	
	//===YSEL3_B������
	#define YSEL2B_CTR_PORT								YSEL2B_PORT	//GPIOE
	#define YSEL2B_CTR_BIT								YSEL2B_BIT	//LL_GPIO_PIN_0
	#define YSEL2B_CTR_STATE							GPIO_GET_STATE(YSEL2B_CTR_PORT,YSEL2B_CTR_BIT)
	#define YSEL2B_CTR_WRITE							GPIO_SET_WRITE(YSEL2B_CTR_PORT,YSEL2B_CTR_BIT)
	#define YSEL2B_CTR_READ								GPIO_SET_READ( YSEL2B_CTR_PORT,YSEL2B_CTR_BIT)
	#define YSEL2B_CTR_OUT_0							GPIO_OUT_0(    YSEL2B_CTR_PORT,YSEL2B_CTR_BIT)
	#define YSEL2B_CTR_OUT_1							GPIO_OUT_1(    YSEL2B_CTR_PORT,YSEL2B_CTR_BIT)
	#define YSEL2B_CTR_OUT_C							GPIO_OUT_C(    YSEL2B_CTR_PORT,YSEL2B_CTR_BIT)
	
	//===YSEL4_B������
	#define YSEL3B_CTR_PORT								YSEL3B_PORT	//GPIOE
	#define YSEL3B_CTR_BIT								YSEL3B_BIT	//LL_GPIO_PIN_1
	#define YSEL3B_CTR_STATE							GPIO_GET_STATE(YSEL3B_CTR_PORT,YSEL3B_CTR_BIT)
	#define YSEL3B_CTR_WRITE							GPIO_SET_WRITE(YSEL3B_CTR_PORT,YSEL3B_CTR_BIT)
	#define YSEL3B_CTR_READ								GPIO_SET_READ( YSEL3B_CTR_PORT,YSEL3B_CTR_BIT)
	#define YSEL3B_CTR_OUT_0							GPIO_OUT_0(    YSEL3B_CTR_PORT,YSEL3B_CTR_BIT)
	#define YSEL3B_CTR_OUT_1							GPIO_OUT_1(    YSEL3B_CTR_PORT,YSEL3B_CTR_BIT)
	#define YSEL3B_CTR_OUT_C							GPIO_OUT_C(    YSEL3B_CTR_PORT,YSEL3B_CTR_BIT)
	
	//===YSEL1_C������
	#define YSEL0C_CTR_PORT								YSEL0C_PORT	//GPIOD
	#define YSEL0C_CTR_BIT								YSEL0C_BIT	//LL_GPIO_PIN_7
	#define YSEL0C_CTR_STATE							GPIO_GET_STATE(YSEL0C_CTR_PORT,YSEL0C_CTR_BIT)
	#define YSEL0C_CTR_WRITE							GPIO_SET_WRITE(YSEL0C_CTR_PORT,YSEL0C_CTR_BIT)
	#define YSEL0C_CTR_READ								GPIO_SET_READ( YSEL0C_CTR_PORT,YSEL0C_CTR_BIT)
	#define YSEL0C_CTR_OUT_0							GPIO_OUT_0(    YSEL0C_CTR_PORT,YSEL0C_CTR_BIT)
	#define YSEL0C_CTR_OUT_1							GPIO_OUT_1(    YSEL0C_CTR_PORT,YSEL0C_CTR_BIT)
	#define YSEL0C_CTR_OUT_C							GPIO_OUT_C(    YSEL0C_CTR_PORT,YSEL0C_CTR_BIT)
	
	//===YSEL2_C������
	#define YSEL1C_CTR_PORT								YSEL1C_PORT	//GPIOD
	#define YSEL1C_CTR_BIT								YSEL1C_BIT	//LL_GPIO_PIN_6
	#define YSEL1C_CTR_STATE							GPIO_GET_STATE(YSEL1C_CTR_PORT,YSEL1C_CTR_BIT)
	#define YSEL1C_CTR_WRITE							GPIO_SET_WRITE(YSEL1C_CTR_PORT,YSEL1C_CTR_BIT)
	#define YSEL1C_CTR_READ								GPIO_SET_READ( YSEL1C_CTR_PORT,YSEL1C_CTR_BIT)
	#define YSEL1C_CTR_OUT_0							GPIO_OUT_0(    YSEL1C_CTR_PORT,YSEL1C_CTR_BIT)
	#define YSEL1C_CTR_OUT_1							GPIO_OUT_1(    YSEL1C_CTR_PORT,YSEL1C_CTR_BIT)
	#define YSEL1C_CTR_OUT_C							GPIO_OUT_C(    YSEL1C_CTR_PORT,YSEL1C_CTR_BIT)
	
	//===YSEL3_C������
	#define YSEL2C_CTR_PORT								YSEL2C_PORT	//GPIOD
	#define YSEL2C_CTR_BIT								YSEL2C_BIT	//LL_GPIO_PIN_5
	#define YSEL2C_CTR_STATE							GPIO_GET_STATE(YSEL2C_CTR_PORT,YSEL2C_CTR_BIT)
	#define YSEL2C_CTR_WRITE							GPIO_SET_WRITE(YSEL2C_CTR_PORT,YSEL2C_CTR_BIT)
	#define YSEL2C_CTR_READ								GPIO_SET_READ( YSEL2C_CTR_PORT,YSEL2C_CTR_BIT)
	#define YSEL2C_CTR_OUT_0							GPIO_OUT_0(    YSEL2C_CTR_PORT,YSEL2C_CTR_BIT)
	#define YSEL2C_CTR_OUT_1							GPIO_OUT_1(    YSEL2C_CTR_PORT,YSEL2C_CTR_BIT)
	#define YSEL2C_CTR_OUT_C							GPIO_OUT_C(    YSEL2C_CTR_PORT,YSEL2C_CTR_BIT)
	
	//===YSEL4_C������
	#define YSEL3C_CTR_PORT								YSEL3C_PORT	//GPIOD
	#define YSEL3C_CTR_BIT								YSEL3C_BIT	//LL_GPIO_PIN_4
	#define YSEL3C_CTR_STATE							GPIO_GET_STATE(YSEL3C_CTR_PORT,YSEL3C_CTR_BIT)
	#define YSEL3C_CTR_WRITE							GPIO_SET_WRITE(YSEL3C_CTR_PORT,YSEL3C_CTR_BIT)
	#define YSEL3C_CTR_READ								GPIO_SET_READ( YSEL3C_CTR_PORT,YSEL3C_CTR_BIT)
	#define YSEL3C_CTR_OUT_0							GPIO_OUT_0(    YSEL3C_CTR_PORT,YSEL3C_CTR_BIT)
	#define YSEL3C_CTR_OUT_1							GPIO_OUT_1(    YSEL3C_CTR_PORT,YSEL3C_CTR_BIT)
	#define YSEL3C_CTR_OUT_C							GPIO_OUT_C(    YSEL3C_CTR_PORT,YSEL3C_CTR_BIT)
	
	//===YSEL1_D������
	#define YSEL0D_CTR_PORT								YSEL0D_PORT	//GPIOD
	#define YSEL0D_CTR_BIT								YSEL0D_BIT	//LL_GPIO_PIN_15
	#define YSEL0D_CTR_STATE							GPIO_GET_STATE(YSEL0D_CTR_PORT,YSEL0D_CTR_BIT)
	#define YSEL0D_CTR_WRITE							GPIO_SET_WRITE(YSEL0D_CTR_PORT,YSEL0D_CTR_BIT)
	#define YSEL0D_CTR_READ								GPIO_SET_READ( YSEL0D_CTR_PORT,YSEL0D_CTR_BIT)
	#define YSEL0D_CTR_OUT_0							GPIO_OUT_0(    YSEL0D_CTR_PORT,YSEL0D_CTR_BIT)
	#define YSEL0D_CTR_OUT_1							GPIO_OUT_1(    YSEL0D_CTR_PORT,YSEL0D_CTR_BIT)
	#define YSEL0D_CTR_OUT_C							GPIO_OUT_C(    YSEL0D_CTR_PORT,YSEL0D_CTR_BIT)
	
	//===YSEL2_D������
	#define YSEL1D_CTR_PORT								YSEL1D_PORT	//GPIOD
	#define YSEL1D_CTR_BIT								YSEL1D_BIT	//LL_GPIO_PIN_14
	#define YSEL1D_CTR_STATE							GPIO_GET_STATE(YSEL1D_CTR_PORT,YSEL1D_CTR_BIT)
	#define YSEL1D_CTR_WRITE							GPIO_SET_WRITE(YSEL1D_CTR_PORT,YSEL1D_CTR_BIT)
	#define YSEL1D_CTR_READ								GPIO_SET_READ( YSEL1D_CTR_PORT,YSEL1D_CTR_BIT)
	#define YSEL1D_CTR_OUT_0							GPIO_OUT_0(    YSEL1D_CTR_PORT,YSEL1D_CTR_BIT)
	#define YSEL1D_CTR_OUT_1							GPIO_OUT_1(    YSEL1D_CTR_PORT,YSEL1D_CTR_BIT)
	#define YSEL1D_CTR_OUT_C							GPIO_OUT_C(    YSEL1D_CTR_PORT,YSEL1D_CTR_BIT)
	
	//===YSEL3_D������
	#define YSEL2D_CTR_PORT								YSEL2D_PORT	//GPIOD
	#define YSEL2D_CTR_BIT								YSEL2D_BIT	//LL_GPIO_PIN_13
	#define YSEL2D_CTR_STATE							GPIO_GET_STATE(YSEL2D_CTR_PORT,YSEL2D_CTR_BIT)
	#define YSEL2D_CTR_WRITE							GPIO_SET_WRITE(YSEL2D_CTR_PORT,YSEL2D_CTR_BIT)
	#define YSEL2D_CTR_READ								GPIO_SET_READ( YSEL2D_CTR_PORT,YSEL2D_CTR_BIT)
	#define YSEL2D_CTR_OUT_0							GPIO_OUT_0(    YSEL2D_CTR_PORT,YSEL2D_CTR_BIT)
	#define YSEL2D_CTR_OUT_1							GPIO_OUT_1(    YSEL2D_CTR_PORT,YSEL2D_CTR_BIT)
	#define YSEL2D_CTR_OUT_C							GPIO_OUT_C(    YSEL2D_CTR_PORT,YSEL2D_CTR_BIT)
	
	//===YSEL4_D������
	#define YSEL3D_CTR_PORT								YSEL3D_PORT	//GPIOD
	#define YSEL3D_CTR_BIT								YSEL3D_BIT	//LL_GPIO_PIN_12
	#define YSEL3D_CTR_STATE							GPIO_GET_STATE(YSEL3D_CTR_PORT,YSEL3D_CTR_BIT)
	#define YSEL3D_CTR_WRITE							GPIO_SET_WRITE(YSEL3D_CTR_PORT,YSEL3D_CTR_BIT)
	#define YSEL3D_CTR_READ								GPIO_SET_READ( YSEL3D_CTR_PORT,YSEL3D_CTR_BIT)
	#define YSEL3D_CTR_OUT_0							GPIO_OUT_0(    YSEL3D_CTR_PORT,YSEL3D_CTR_BIT)
	#define YSEL3D_CTR_OUT_1							GPIO_OUT_1(    YSEL3D_CTR_PORT,YSEL3D_CTR_BIT)
	#define YSEL3D_CTR_OUT_C							GPIO_OUT_C(    YSEL3D_CTR_PORT,YSEL3D_CTR_BIT)
	
	//===�ߵ�ѹ�µ���ʼƵ�ʵ��������
	#define FREQ_CURRENT_HIGH_START_IMAX_X100MA			450	
	//===�ߵ�ѹ�µ���ʼƵ�ʵ��������
	#define FREQ_CURRENT_HIGH_START_IMIN_X100MA			250	
	//===�ߵ�ѹ�µ���ֹƵ�ʵ��������
	#define FREQ_CURRENT_HIGH_STOP_IMAX_X100MA			800	
	//===�ߵ�ѹ�µ���ֹƵ�ʵ��������
	#define FREQ_CURRENT_HIGH_STOP_IMIN_X100MA			500	
	//===�ߵ�ѹ�µ�Ƶ�ʵ����
	#define FREQ_CURRENT_HIGH_FX100MHZ_NUM				53	
	//===�ߵ�ѹ�µ���ʼƵ��
	#define FREQ_CURRENT_HIGH_FSTART_X100MHZ			21000	
	//===�ߵ�ѹ�µ�Ƶ�ʲ���
	#define FREQ_CURRENT_HIGH_FSTEP_X100MHZ				200	
	//===�ߵ�ѹ�ĵ�ѹֵ
	#define FREQ_CURRENT_HIGH_POWER_MV					3600	
	//===�ߵ�ѹ�µ�ADC�������
	#define FREQ_CURRENT_HIGH_ADC_POINT_NUM				6	

	//===�ߵ�ѹ�µ�ADC�ϸ����ֵ�����Կ����ǵ����Ĳ�ֵ����λ��10����΢����������20������200uA�ĵ�����ֵ
	#define FREQ_CURRENT_HIGH_ADC_PASS_MAX				20	
	//===�ߵ�ѹ�µ�ADC�ϸ���Сֵ
	#define FREQ_CURRENT_HIGH_ADC_PASS_MIN				2	
	//===�͵�ѹ�µ���ʼƵ�ʵ��������
	#define FREQ_CURRENT_LOW_START_IMAX_X100MA			800	
	//===�͵�ѹ�µ���ʼƵ�ʵ��������
	#define FREQ_CURRENT_LOW_START_IMIN_X100MA			600	
	//===�͵�ѹ�µ���ֹƵ�ʵ��������
	#define FREQ_CURRENT_LOW_STOP_IMAX_X100MA			1400	
	//===�͵�ѹ�µ���ֹƵ�ʵ��������
	#define FREQ_CURRENT_LOW_STOP_IMIN_X100MA			1100	
	//===�͵�ѹ�µ�Ƶ�ʵ����
	#define FREQ_CURRENT_LOW_FX100MHZ_NUM				22	
	//===�͵�ѹ�µ���ʼƵ��
	#define FREQ_CURRENT_LOW_FSTART_X100MHZ				43000	
	//===�͵�ѹ�µ�Ƶ�ʲ���
	#define FREQ_CURRENT_LOW_FSTEP_X100MHZ				200	
	//===�͵�ѹ�ĵ�ѹֵ
	#define FREQ_CURRENT_LOW_POWER_MV					2500	
	//===�ߵ�ѹ�µ�ADC�������
	#define FREQ_CURRENT_LOW_ADC_POINT_NUM				6
	
	//===�ߵ�ѹ�µ�ADC�ϸ����ֵ�����Կ����ǵ����Ĳ�ֵ����λ��10����΢����������20������200uA�ĵ�����ֵ
	#define FREQ_CURRENT_LOW_ADC_PASS_MAX				30	
	//===�ߵ�ѹ�µ�ADC�ϸ���Сֵ
	#define FREQ_CURRENT_LOW_ADC_PASS_MIN				2	
	//===��ʷ��¼�����ֵ
	#define FREQ_CURRENT_HISTORY_MAX_SIZE				20	
	//===��������
	#define FREQ_CURRENT_SAMPLE_RES						100	
	//===�Ŵ���
	#define FREQ_CURRENT_AMP_TIMES						100	
	
	//===����Ƶ�ʵ���������ֵ
	#define FREQ_CURRENT_FREQ_POINT_MAX_NUM				200	
	//===���õ�һƵ�ʵ�
	#define FREQ_YSEL1_X100MHZ							51200	
	//===���õڶ�Ƶ�ʵ�
	#define FREQ_YSEL2_X100MHZ							43392	
	//===���õ���Ƶ�ʵ�
	#define FREQ_YSEL3_X100MHZ							31500	
	//===���õ���Ƶ�ʵ�
	#define FREQ_YSEL4_X100MHZ							23050	
	//===����Ĭ��Ƶ�ʵ�
	#define FREQ_YSEL_X100MHz							2
	
	//===�豸����
	#define SYN4XXR										1
	#define SYN5XXR										2
	#define CRUX										3
	#define F11XT										4
	#define CRATER										5
	#define ARA											6
	#define SYN590R										7
	
	//===����Ƶ�ʵ���ɨ���SITE��
	#define FREQ_CURRENT_MAX_SITE						4
	
	//===���SITE���Ķ���
	#if (FREQ_CURRENT_MAX_SITE<1)
		#define  FREQ_CURRENT_MAX_SITE					1
	#elif  (FREQ_CURRENT_MAX_SITE>4)
		#define  FREQ_CURRENT_MAX_SITE					4
	#endif
	
	//===����ADC�����Ĳο���ѹ
	#define FREQ_CURRENT_ADC_VREF_MV					3300
	
	//====������Ķ���
	#define RFASK_TASK_YSEL1							1
	#define RFASK_TASK_YSEL2							2
	#define RFASK_TASK_YSEL3							3
	#define RFASK_TASK_YSEL4							4
	#define RFASK_TASK_POINT_ONE						5
	#define RFASK_TASK_POINT_TWO						6
	#define RFASK_TASK_CLEAR							15
	
	//===�ṹ�嶨��
	typedef struct _FREQ_CURRENT_HandlerType			FREQ_CURRENT_HandlerType;

	//===ָ��ṹ�嶨��
	typedef struct _FREQ_CURRENT_HandlerType			*pFREQ_CURRENT_HandlerType;

	//===Ƶ�ʵ������ݽṹ��
	struct _FREQ_CURRENT_HandlerType
	{
		UINT8_T		msgCMD;								//---���������
		UINT16_T	msgStartMaxCurrentX100mA;			//---��ʼ������
		UINT16_T	msgStartMinCurrentX100mA;			//---��ʼ��С����
		UINT16_T	msgStopMaxCurrentX100mA;			//---����������
		UINT16_T	msgStopMinCurrentX100mA;			//---������С����
		UINT32_T	msgStopFreqX100MHz;					//---��ֹƵ��
		UINT32_T	msgStartFreqX100MHz;				//---��ʼƵ��Ƶ��
		UINT16_T	msgStepFreqX100MHz;					//---Ƶ�ʲ���
		UINT16_T	msgFreqPointNum;					//---Ƶ�ʲ����ĵ���
		UINT16_T    msgADCPointNum;						//---ADC����ĵ���
		UINT16_T    msgADCPassMax;						//---ADC�ϸ�����ֵ
		UINT16_T	msgADCPassMin;						//---ADC�ϸ����Сֵ
		UINT16_T    msgFreqCurrentVoltagemV;			//---Ƶ�ʵ������Եĵ�ѹֵ
	};

	//===�ṹ�嶨��
	typedef struct _RFASK_HandlerType					RFASK_HandlerType;

	//===ָ��ṹ�嶨��
	typedef struct _RFASK_HandlerType					*pRFASK_HandlerType;

	//===���ݽṹ��
	struct _RFASK_HandlerType
	{
		UINT8_T	 msgDeviceType;												//---�豸����
		UINT8_T  msgActivateSite[FREQ_CURRENT_MAX_SITE];					//---�����SITE��Ϣ��0---δ���1---����
		UINT16_T msgSiteADC[FREQ_CURRENT_MAX_SITE];							//---�����SITE��ADC��ֵ
		UINT16_T msgSiteCurrent[FREQ_CURRENT_MAX_SITE];						//---�����SITE�ĵ�����ֵ
		UINT16_T msgSiteCurrentHistory[FREQ_CURRENT_MAX_SITE][FREQ_CURRENT_HISTORY_MAX_SIZE];	//---��¼����ʷ����ֵ
		UINT16_T msgSitePass[FREQ_CURRENT_MAX_SITE];						//---�Ƿ�ͨ�� 0---ͨ������0---��ͨ��
		UINT16_T msgSampleX100Res;											//---��������Ĵ�С����������Ĵ�С�Ǿ���100��������0.1ŷķ�������ʾ����10ŷķ��������ʾ֧�ֵ���С������0.01ŷķ
		UINT16_T msgAmpTimes;												//---�����Ŵ���
		UINT32_T msgFreqX100MHzYSel1;										//---Ԥ��Ƶ�ʵ�1
		UINT32_T msgFreqX100MHzYSel2;										//---Ԥ��Ƶ�ʵ�2
		UINT32_T msgFreqX100MHzYSel3;										//---Ԥ��Ƶ�ʵ�3
		UINT32_T msgFreqX100MHzYSel4;										//---Ԥ��Ƶ�ʵ�4
		FREQ_CURRENT_HandlerType msgFreqCurrentPointOne;					//---Ƶ�ʵ������Ե�1
		FREQ_CURRENT_HandlerType msgFreqCurrentPointTwo;					//---Ƶ�ʵ������Ե�2
	};

	//===�ⲿ�ӿڵ���
	extern RFASK_HandlerType							g_Rfask;
	extern pRFASK_HandlerType							pRfask;

	//===��������
	void	 RFASK_StructInit(RFASK_HandlerType* rfask);
	void     RFASK_Init(RFASK_HandlerType *rfask);
	UINT32_T RFASK_CalcXTAL(RFASK_HandlerType *rfask, UINT32_T rfX100MHz);
	UINT8_T  RFASK_SetDeviceType(RFASK_HandlerType *rfask, UINT8_T deviceType);
	UINT32_T RFASK_GetDeviceType(RFASK_HandlerType *rfask);
	UINT8_T  RFASK_ActivateSites(RFASK_HandlerType *rfask, UINT8_T activateSites);
	UINT8_T  RFASK_SetFreqCurrentPointCmd(FREQ_CURRENT_HandlerType *rfaskFreqCurrent, UINT8_T cmd);
	UINT8_T  RFASK_ScanYSEL(void);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*RFASK_CFG_H_ */
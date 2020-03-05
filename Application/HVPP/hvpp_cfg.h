	#ifndef HVPP_CFG_H_
#define HVPP_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "gpio_task.h"
	#include "power_task.h"
	#include "hw_cfg.h"
	#include "delay_task.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//=============HVPPʹ�õĶ˿ں��ϵ��ʼ����״̬========================================
	//===HVPP_RDY_BSY	---����Ϊ���룬��������ѹ���̶�������
	//===HVPP_OE		---����Ϊ�����Ĭ���Ǹߵ�ƽ�������ŵ͵�ƽ��Ч
	//===HVPP_WR		---����Ϊ�����Ĭ���Ǹߵ�ƽ�������ŵ͵�ƽ��Ч
	//===HVPP_BS1		---����Ϊ�����Ĭ���ǵ͵�ƽ��Ĭ��ѡ����ֽ�
	//===HVPP_XA0		---����Ϊ�����Ĭ���Ǹߵ�ƽ����XA1�ĸߵ�ƽ���Ϊ����ģʽ
	//===HVPP_XA1		---����Ϊ�����Ĭ���Ǹߵ�ƽ����XA0�ĸߵ�ƽ���Ϊ����ģʽ
	//===HVPP_PAGEL		---����Ϊ�����Ĭ���ǵ͵�ƽ��Ĭ��ѡ����ֽ�
	//===HVPP_BS2		---����Ϊ�����Ĭ���ǵ͵�ƽ��Ĭ��ѡ����ֽ�
	//===HVPP_XTAL		---����Ϊ�����Ĭ���ǵ͵�ƽ���������źţ���ִ�ж���
	//===HVPP_DATA		---����Ϊ���룬Ĭ����Ҫ��ȡ�ⲿ����
	//===================================================================================
	//===O---���æ��1---�ȴ������device--->>>host---O
	#define HVPP_RDY_BSY_PORT								GPIOC
	#define HVPP_RDY_BSY_BIT								LL_GPIO_PIN_15
	#define HVPP_RDY_BSY_STATE								GPIO_GET_STATE(HVPP_RDY_BSY_PORT,HVPP_RDY_BSY_BIT)
	#define HVPP_RDY_BSY_WRITE								GPIO_SET_WRITE(HVPP_RDY_BSY_PORT,HVPP_RDY_BSY_BIT)
	#define HVPP_RDY_BSY_READ								GPIO_SET_READ( HVPP_RDY_BSY_PORT,HVPP_RDY_BSY_BIT)
	#define HVPP_RDY_BSY_OUT_0								GPIO_OUT_0(    HVPP_RDY_BSY_PORT,HVPP_RDY_BSY_BIT)
	#define HVPP_RDY_BSY_OUT_1								GPIO_OUT_1(    HVPP_RDY_BSY_PORT,HVPP_RDY_BSY_BIT)
	#define HVPP_RDY_BSY_OUT_C								GPIO_OUT_C(    HVPP_RDY_BSY_PORT,HVPP_RDY_BSY_BIT)

	//===���ʹ�ܣ��͵�ƽ��Ч��device--->>>host---I
	#define HVPP_OE_PORT									GPIOE
	#define HVPP_OE_BIT										LL_GPIO_PIN_9
	#define HVPP_OE_STATE									GPIO_GET_STATE(HVPP_OE_PORT,HVPP_OE_BIT)
	#define HVPP_OE_WRITE									GPIO_SET_WRITE(HVPP_OE_PORT,HVPP_OE_BIT)
	#define HVPP_OE_READ									GPIO_SET_READ( HVPP_OE_PORT,HVPP_OE_BIT)
	#define HVPP_OE_OUT_0									GPIO_OUT_0(    HVPP_OE_PORT,HVPP_OE_BIT)
	#define HVPP_OE_OUT_1									GPIO_OUT_1(    HVPP_OE_PORT,HVPP_OE_BIT)
	#define HVPP_OE_OUT_C									GPIO_OUT_C(    HVPP_OE_PORT,HVPP_OE_BIT)

	//===д���壬�͵�ƽ��Ч��device--->>>host---I
	#define HVPP_WR_PORT									GPIOE
	#define HVPP_WR_BIT										LL_GPIO_PIN_10
	#define HVPP_WR_STATE									GPIO_GET_STATE(HVPP_WR_PORT,HVPP_WR_BIT)
	#define HVPP_WR_WRITE									GPIO_SET_WRITE(HVPP_WR_PORT,HVPP_WR_BIT)
	#define HVPP_WR_READ									GPIO_SET_READ( HVPP_WR_PORT,HVPP_WR_BIT)
	#define HVPP_WR_OUT_0									GPIO_OUT_0(    HVPP_WR_PORT,HVPP_WR_BIT)
	#define HVPP_WR_OUT_1									GPIO_OUT_1(    HVPP_WR_PORT,HVPP_WR_BIT)
	#define HVPP_WR_OUT_C									GPIO_OUT_C(    HVPP_WR_PORT,HVPP_WR_BIT)

	//===�ֽ�ѡ��1(0---ѡ����ֽڣ�1---ѡ����ֽ�)��device--->>>host---I
	#define HVPP_BS1_PORT									GPIOE
	#define HVPP_BS1_BIT									LL_GPIO_PIN_11
	#define HVPP_BS1_STATE									GPIO_GET_STATE(HVPP_BS1_PORT,HVPP_BS1_BIT)
	#define HVPP_BS1_WRITE									GPIO_SET_WRITE(HVPP_BS1_PORT,HVPP_BS1_BIT)
	#define HVPP_BS1_READ									GPIO_SET_READ( HVPP_BS1_PORT,HVPP_BS1_BIT)
	#define HVPP_BS1_OUT_0									GPIO_OUT_0(    HVPP_BS1_PORT,HVPP_BS1_BIT)
	#define HVPP_BS1_OUT_1									GPIO_OUT_1(    HVPP_BS1_PORT,HVPP_BS1_BIT)
	#define HVPP_BS1_OUT_C									GPIO_OUT_C(    HVPP_BS1_PORT,HVPP_BS1_BIT)

	//===XTAL����0��device--->>>host---I
	#define HVPP_XA0_PORT									GPIOE
	#define HVPP_XA0_BIT									LL_GPIO_PIN_12
	#define HVPP_XA0_STATE									GPIO_GET_STATE(HVPP_XA0_PORT,HVPP_XA0_BIT)
	#define HVPP_XA0_WRITE									GPIO_SET_WRITE(HVPP_XA0_PORT,HVPP_XA0_BIT)
	#define HVPP_XA0_READ									GPIO_SET_READ( HVPP_XA0_PORT,HVPP_XA0_BIT)
	#define HVPP_XA0_OUT_0									GPIO_OUT_0(    HVPP_XA0_PORT,HVPP_XA0_BIT)
	#define HVPP_XA0_OUT_1									GPIO_OUT_1(    HVPP_XA0_PORT,HVPP_XA0_BIT)
	#define HVPP_XA0_OUT_C									GPIO_OUT_C(    HVPP_XA0_PORT,HVPP_XA0_BIT)

	//===XTAL����1��device--->>>host---I
	#define HVPP_XA1_PORT									GPIOE
	#define HVPP_XA1_BIT									LL_GPIO_PIN_13
	#define HVPP_XA1_STATE									GPIO_GET_STATE(HVPP_XA1_PORT,HVPP_XA1_BIT)
	#define HVPP_XA1_WRITE									GPIO_SET_WRITE(HVPP_XA1_PORT,HVPP_XA1_BIT)
	#define HVPP_XA1_READ									GPIO_SET_READ( HVPP_XA1_PORT,HVPP_XA1_BIT)
	#define HVPP_XA1_OUT_0									GPIO_OUT_0(    HVPP_XA1_PORT,HVPP_XA1_BIT)
	#define HVPP_XA1_OUT_1									GPIO_OUT_1(    HVPP_XA1_PORT,HVPP_XA1_BIT)
	#define HVPP_XA1_OUT_C									GPIO_OUT_C(    HVPP_XA1_PORT,HVPP_XA1_BIT)

	//===���س���洢����EEPROM����ҳ��device--->>>host---I
	#define HVPP_PAGEL_PORT									GPIOE
	#define HVPP_PAGEL_BIT									LL_GPIO_PIN_14
	#define HVPP_PAGEL_STATE								GPIO_GET_STATE(HVPP_PAGEL_PORT,HVPP_PAGEL_BIT)
	#define HVPP_PAGEL_WRITE								GPIO_SET_WRITE(HVPP_PAGEL_PORT,HVPP_PAGEL_BIT)
	#define HVPP_PAGEL_READ									GPIO_SET_READ( HVPP_PAGEL_PORT,HVPP_PAGEL_BIT)
	#define HVPP_PAGEL_OUT_0								GPIO_OUT_0(    HVPP_PAGEL_PORT,HVPP_PAGEL_BIT)
	#define HVPP_PAGEL_OUT_1								GPIO_OUT_1(    HVPP_PAGEL_PORT,HVPP_PAGEL_BIT)
	#define HVPP_PAGEL_OUT_C								GPIO_OUT_C(    HVPP_PAGEL_PORT,HVPP_PAGEL_BIT)

	//===�ֽ�ѡ��2(0---ѡ����ֽڣ�1---ѡ��ڶ������ֽ�)��device--->>>host---I
	#define HVPP_BS2_PORT									GPIOE
	#define HVPP_BS2_BIT									LL_GPIO_PIN_8
	#define HVPP_BS2_STATE									GPIO_GET_STATE(HVPP_BS2_PORT,HVPP_BS2_BIT)
	#define HVPP_BS2_WRITE									GPIO_SET_WRITE(HVPP_BS2_PORT,HVPP_BS2_BIT)
	#define HVPP_BS2_READ									GPIO_SET_READ( HVPP_BS2_PORT,HVPP_BS2_BIT)
	#define HVPP_BS2_OUT_0									GPIO_OUT_0(    HVPP_BS2_PORT,HVPP_BS2_BIT)
	#define HVPP_BS2_OUT_1									GPIO_OUT_1(    HVPP_BS2_PORT,HVPP_BS2_BIT)
	#define HVPP_BS2_OUT_C									GPIO_OUT_C(    HVPP_BS2_PORT,HVPP_BS2_BIT)
															
	//===ʱ�����ţ�device--->>>host---I						
	#define HVPP_XTAL_PORT									GPIOE
	#define HVPP_XTAL_BIT									LL_GPIO_PIN_15
	#define HVPP_XTAL_STATE									GPIO_GET_STATE(HVPP_XTAL_PORT,HVPP_XTAL_BIT)
	#define HVPP_XTAL_WRITE									GPIO_SET_WRITE(HVPP_XTAL_PORT,HVPP_XTAL_BIT)
	#define HVPP_XTAL_READ									GPIO_SET_READ( HVPP_XTAL_PORT,HVPP_XTAL_BIT)
	#define HVPP_XTAL_OUT_0									GPIO_OUT_0(    HVPP_XTAL_PORT,HVPP_XTAL_BIT)
	#define HVPP_XTAL_OUT_1									GPIO_OUT_1(    HVPP_XTAL_PORT,HVPP_XTAL_BIT)
	#define HVPP_XTAL_OUT_C									GPIO_OUT_C(    HVPP_XTAL_PORT,HVPP_XTAL_BIT)

	#define HVPP_CTRL_BUS_PORT								GPIOE
	#define HVPP_CTRL_BUS_BIT								(LL_GPIO_PIN_8|LL_GPIO_PIN_9|LL_GPIO_PIN_10|LL_GPIO_PIN_11|LL_GPIO_PIN_12|LL_GPIO_PIN_13|LL_GPIO_PIN_14|LL_GPIO_PIN_15)
	#define HVPP_CTRL_BUS_STATE								GPIO_GET_STATE(HVPP_CTRL_BUS_PORT,HVPP_CTRL_BUS_BIT)
	#define HVPP_CTRL_BUS_WRITE								GPIO_SET_WRITE(HVPP_CTRL_BUS_PORT,HVPP_CTRL_BUS_BIT)
	#define HVPP_CTRL_BUS_READ								GPIO_SET_READ( HVPP_CTRL_BUS_PORT,HVPP_CTRL_BUS_BIT)
	#define HVPP_CTRL_BUS_VAL(val)							GPIO_H8BITS_OUT(HVPP_CTRL_BUS_PORT,val)
															
	//===�������ʹ���ź�							 `			
	#define HVPP_CTRL_OE_PORT								GPIOD
	#define HVPP_CTRL_OE_BIT								LL_GPIO_PIN_4
	#define HVPP_CTRL_OE_STATE								GPIO_GET_STATE(HVPP_CTRL_OE_PORT,HVPP_CTRL_OE_BIT)
	#define HVPP_CTRL_OE_WRITE								GPIO_SET_WRITE(HVPP_CTRL_OE_PORT,HVPP_CTRL_OE_BIT)
	#define HVPP_CTRL_OE_READ								GPIO_SET_READ( HVPP_CTRL_OE_PORT,HVPP_CTRL_OE_BIT)
	#define HVPP_CTRL_OE_OUT_0								GPIO_OUT_0(    HVPP_CTRL_OE_PORT,HVPP_CTRL_OE_BIT)
	#define HVPP_CTRL_OE_OUT_1								GPIO_OUT_1(    HVPP_CTRL_OE_PORT,HVPP_CTRL_OE_BIT)
	#define HVPP_CTRL_OE_OUT_C								GPIO_OUT_C(    HVPP_CTRL_OE_PORT,HVPP_CTRL_OE_BIT)
															
	//===��ƽת��оƬ����������					   `		
	#define HVPP_CTRL_DIR_TO_DEVICE							HVPP_CTRL_OE_OUT_0					
	#define HVPP_CTRL_DIR_TO_HZ								HVPP_CTRL_OE_OUT_1

	//===˫����������Bit0(OEΪ��ʱ���)��device--->>>host---I/O
	#define HVPP_DATA0_PORT									GPIOE
	#define HVPP_DATA0_BIT									LL_GPIO_PIN_7
	#define HVPP_DATA0_STATE								GPIO_GET_STATE(HVPP_DATA0_PORT,HVPP_DATA0_BIT)
	#define HVPP_DATA0_WRITE								GPIO_SET_WRITE(HVPP_DATA0_PORT,HVPP_DATA0_BIT)
	#define HVPP_DATA0_READ									GPIO_SET_READ( HVPP_DATA0_PORT,HVPP_DATA0_BIT)
	#define HVPP_DATA0_OUT_0								GPIO_OUT_0(    HVPP_DATA0_PORT,HVPP_DATA0_BIT)
	#define HVPP_DATA0_OUT_1								GPIO_OUT_1(    HVPP_DATA0_PORT,HVPP_DATA0_BIT)
	#define HVPP_DATA0_OUT_C								GPIO_OUT_C(    HVPP_DATA0_PORT,HVPP_DATA0_BIT)

	//===˫����������Bit1(OEΪ��ʱ���)��device--->>>host---I/O
	#define HVPP_DATA1_PORT									GPIOE
	#define HVPP_DATA1_BIT									LL_GPIO_PIN_6
	#define HVPP_DATA1_STATE								GPIO_GET_STATE(HVPP_DATA1_PORT,HVPP_DATA1_BIT)
	#define HVPP_DATA1_WRITE								GPIO_SET_WRITE(HVPP_DATA1_PORT,HVPP_DATA1_BIT)
	#define HVPP_DATA1_READ									GPIO_SET_READ( HVPP_DATA1_PORT,HVPP_DATA1_BIT)
	#define HVPP_DATA1_OUT_0								GPIO_OUT_0(    HVPP_DATA1_PORT,HVPP_DATA1_BIT)
	#define HVPP_DATA1_OUT_1								GPIO_OUT_1(    HVPP_DATA1_PORT,HVPP_DATA1_BIT)
	#define HVPP_DATA1_OUT_C								GPIO_OUT_C(    HVPP_DATA1_PORT,HVPP_DATA1_BIT)

	//===˫����������Bit2(OEΪ��ʱ���)��device--->>>host---I/O
	#define HVPP_DATA2_PORT									GPIOE
	#define HVPP_DATA2_BIT									LL_GPIO_PIN_5
	#define HVPP_DATA2_STATE								GPIO_GET_STATE(HVPP_DATA2_PORT,HVPP_DATA2_BIT)
	#define HVPP_DATA2_WRITE								GPIO_SET_WRITE(HVPP_DATA2_PORT,HVPP_DATA2_BIT)
	#define HVPP_DATA2_READ									GPIO_SET_READ( HVPP_DATA2_PORT,HVPP_DATA2_BIT)
	#define HVPP_DATA2_OUT_0								GPIO_OUT_0(    HVPP_DATA2_PORT,HVPP_DATA2_BIT)
	#define HVPP_DATA2_OUT_1								GPIO_OUT_1(    HVPP_DATA2_PORT,HVPP_DATA2_BIT)
	#define HVPP_DATA2_OUT_C								GPIO_OUT_C(    HVPP_DATA2_PORT,HVPP_DATA2_BIT)

	//===˫����������Bit3(OEΪ��ʱ���)��device--->>>host---I/O
	#define HVPP_DATA3_PORT									GPIOE
	#define HVPP_DATA3_BIT									LL_GPIO_PIN_4
	#define HVPP_DATA3_STATE								GPIO_GET_STATE(HVPP_DATA3_PORT,HVPP_DATA3_BIT)
	#define HVPP_DATA3_WRITE								GPIO_SET_WRITE(HVPP_DATA3_PORT,HVPP_DATA3_BIT)
	#define HVPP_DATA3_READ									GPIO_SET_READ( HVPP_DATA3_PORT,HVPP_DATA3_BIT)
	#define HVPP_DATA3_OUT_0								GPIO_OUT_0(    HVPP_DATA3_PORT,HVPP_DATA3_BIT)
	#define HVPP_DATA3_OUT_1								GPIO_OUT_1(    HVPP_DATA3_PORT,HVPP_DATA3_BIT)
	#define HVPP_DATA3_OUT_C								GPIO_OUT_C(    HVPP_DATA3_PORT,HVPP_DATA3_BIT)

	//===˫����������Bit4(OEΪ��ʱ���)��device--->>>host---I/O
	#define HVPP_DATA4_PORT									GPIOE
	#define HVPP_DATA4_BIT									LL_GPIO_PIN_3
	#define HVPP_DATA4_STATE								GPIO_GET_STATE(HVPP_DATA4_PORT,HVPP_DATA4_BIT)
	#define HVPP_DATA4_WRITE								GPIO_SET_WRITE(HVPP_DATA4_PORT,HVPP_DATA4_BIT)
	#define HVPP_DATA4_READ									GPIO_SET_READ( HVPP_DATA4_PORT,HVPP_DATA4_BIT)
	#define HVPP_DATA4_OUT_0								GPIO_OUT_0(    HVPP_DATA4_PORT,HVPP_DATA4_BIT)
	#define HVPP_DATA4_OUT_1								GPIO_OUT_1(    HVPP_DATA4_PORT,HVPP_DATA4_BIT)
	#define HVPP_DATA4_OUT_C								GPIO_OUT_C(    HVPP_DATA4_PORT,HVPP_DATA4_BIT)

	//===˫����������Bit5(OEΪ��ʱ���)��device--->>>host---I/O
	#define HVPP_DATA5_PORT									GPIOE
	#define HVPP_DATA5_BIT									LL_GPIO_PIN_2
	#define HVPP_DATA5_STATE								GPIO_GET_STATE(HVPP_DATA5_PORT,HVPP_DATA5_BIT)
	#define HVPP_DATA5_WRITE								GPIO_SET_WRITE(HVPP_DATA5_PORT,HVPP_DATA5_BIT)
	#define HVPP_DATA5_READ									GPIO_SET_READ( HVPP_DATA5_PORT,HVPP_DATA5_BIT)
	#define HVPP_DATA5_OUT_0								GPIO_OUT_0(    HVPP_DATA5_PORT,HVPP_DATA5_BIT)
	#define HVPP_DATA5_OUT_1								GPIO_OUT_1(    HVPP_DATA5_PORT,HVPP_DATA5_BIT)
	#define HVPP_DATA5_OUT_C								GPIO_OUT_C(    HVPP_DATA5_PORT,HVPP_DATA5_BIT)

	//===˫����������Bit6(OEΪ��ʱ���)��device--->>>host---I/O
	#define HVPP_DATA6_PORT									GPIOE
	#define HVPP_DATA6_BIT									LL_GPIO_PIN_1
	#define HVPP_DATA6_STATE								GPIO_GET_STATE(HVPP_DATA6_PORT,HVPP_DATA6_BIT)
	#define HVPP_DATA6_WRITE								GPIO_SET_WRITE(HVPP_DATA6_PORT,HVPP_DATA6_BIT)
	#define HVPP_DATA6_READ									GPIO_SET_READ( HVPP_DATA6_PORT,HVPP_DATA6_BIT)
	#define HVPP_DATA6_OUT_0								GPIO_OUT_0(    HVPP_DATA6_PORT,HVPP_DATA6_BIT)
	#define HVPP_DATA6_OUT_1								GPIO_OUT_1(    HVPP_DATA6_PORT,HVPP_DATA6_BIT)
	#define HVPP_DATA6_OUT_C								GPIO_OUT_C(    HVPP_DATA6_PORT,HVPP_DATA6_BIT)

	//===˫����������Bit7(OEΪ��ʱ���)��device--->>>host---I/O
	#define HVPP_DATA7_PORT									GPIOE
	#define HVPP_DATA7_BIT									LL_GPIO_PIN_0
	#define HVPP_DATA7_STATE								GPIO_GET_STATE(HVPP_DATA7_PORT,HVPP_DATA7_BIT)
	#define HVPP_DATA7_WRITE								GPIO_SET_WRITE(HVPP_DATA7_PORT,HVPP_DATA7_BIT)
	#define HVPP_DATA7_READ									GPIO_SET_READ( HVPP_DATA7_PORT,HVPP_DATA7_BIT)
	#define HVPP_DATA7_OUT_0								GPIO_OUT_0(    HVPP_DATA7_PORT,HVPP_DATA7_BIT)
	#define HVPP_DATA7_OUT_1								GPIO_OUT_1(    HVPP_DATA7_PORT,HVPP_DATA7_BIT)
	#define HVPP_DATA7_OUT_C								GPIO_OUT_C(    HVPP_DATA7_PORT,HVPP_DATA7_BIT)

	//===˫����������(OEΪ��ʱ���)��device--->>>host---I/O
	#define HVPP_DATA_BUS_PORT								GPIOE
	#define HVPP_DATA_BUS_BIT								(LL_GPIO_PIN_0|LL_GPIO_PIN_1|LL_GPIO_PIN_2|LL_GPIO_PIN_3|LL_GPIO_PIN_4|LL_GPIO_PIN_5|LL_GPIO_PIN_6|LL_GPIO_PIN_7)
	#define HVPP_DATA_BUS_STATE								GPIO_GET_STATE(HVPP_DATA_BUS_PORT,HVPP_DATA_BUS_BIT)
	#define HVPP_DATA_BUS_WRITE								GPIO_SET_WRITE(HVPP_DATA_BUS_PORT,HVPP_DATA_BUS_BIT)
	#define HVPP_DATA_BUS_READ								GPIO_SET_READ( HVPP_DATA_BUS_PORT,HVPP_DATA_BUS_BIT)
	#define HVPP_DATA_BUS_VAL(val)							GPIO_L8BITS_OUT(HVPP_DATA_BUS_PORT,val)	

	//===����������ʹ���ź�
	#define HVPP_DATA_OE_PORT								GPIOB
	#define HVPP_DATA_OE_BIT								LL_GPIO_PIN_15
	#define HVPP_DATA_OE_STATE								GPIO_GET_STATE(HVPP_DATA_OE_PORT,HVPP_DATA_OE_BIT)
	#define HVPP_DATA_OE_WRITE								GPIO_SET_WRITE(HVPP_DATA_OE_PORT,HVPP_DATA_OE_BIT)
	#define HVPP_DATA_OE_READ								GPIO_SET_READ( HVPP_DATA_OE_PORT,HVPP_DATA_OE_BIT)
	#define HVPP_DATA_OE_OUT_0								GPIO_OUT_0(    HVPP_DATA_OE_PORT,HVPP_DATA_OE_BIT)
	#define HVPP_DATA_OE_OUT_1								GPIO_OUT_1(    HVPP_DATA_OE_PORT,HVPP_DATA_OE_BIT)
	#define HVPP_DATA_OE_OUT_C								GPIO_OUT_C(    HVPP_DATA_OE_PORT,HVPP_DATA_OE_BIT)

	//===����������ʹ�ܷ����ź�
	#define HVPP_DATA_DIR_PORT								GPIOB
	#define HVPP_DATA_DIR_BIT								LL_GPIO_PIN_14
	#define HVPP_DATA_DIR_STATE								GPIO_GET_STATE(HVPP_DATA_DIR_PORT,HVPP_DATA_DIR_BIT)
	#define HVPP_DATA_DIR_WRITE								GPIO_SET_WRITE(HVPP_DATA_DIR_PORT,HVPP_DATA_DIR_BIT)
	#define HVPP_DATA_DIR_READ								GPIO_SET_READ( HVPP_DATA_DIR_PORT,HVPP_DATA_DIR_BIT)
	#define HVPP_DATA_DIR_OUT_0								GPIO_OUT_0(    HVPP_DATA_DIR_PORT,HVPP_DATA_DIR_BIT)
	#define HVPP_DATA_DIR_OUT_1								GPIO_OUT_1(    HVPP_DATA_DIR_PORT,HVPP_DATA_DIR_BIT)
	#define HVPP_DATA_DIR_OUT_C								GPIO_OUT_C(    HVPP_DATA_DIR_PORT,HVPP_DATA_DIR_BIT)

	//===��ƽת��оƬ����������
	#define HVPP_DATA_BUS_DIR_TO_DEVICE						(HVPP_DATA_DIR_OUT_1,HVPP_DATA_OE_OUT_0)
	#define HVPP_DATA_BUS_DIR_TO_HOST						(HVPP_DATA_DIR_OUT_0,HVPP_DATA_OE_OUT_0)
	#define HVPP_DATA_BUS_DIR_TO_HZ							HVPP_DATA_OE_OUT_1
	
	//>>>===XA0,XA1��ϱ��빦��---��ʼ			
	#define	HVPP_XA_OUT_00									( HVPP_XA1_OUT_0,HVPP_XA0_OUT_0 )																						//---���ش洢����ַ
	#define	HVPP_XA_OUT_01									( HVPP_XA1_OUT_0,HVPP_XA0_OUT_1 )																						//---��������
	#define	HVPP_XA_OUT_10									( HVPP_XA1_OUT_1,HVPP_XA0_OUT_0 )																						//---��������
	#define	HVPP_XA_OUT_11									( HVPP_XA1_OUT_1,HVPP_XA0_OUT_1 )																						//---����ģʽ
	#define HVPP_XA_LOAD_ADDR								HVPP_XA_OUT_00
	#define HVPP_XA_LOAD_DATA								HVPP_XA_OUT_01
	#define HVPP_XA_LOAD_CMD								HVPP_XA_OUT_10
	#define HVPP_XA_LOAD_IDLE								HVPP_XA_OUT_11
	//<<<===XA0,XA1��ϱ��빦��---����

	//>>>===BS2,BS1��ϱ��빦��---��ʼ			
	#define	HVPP_BS_OUT_00									( HVPP_BS2_OUT_0,HVPP_BS1_OUT_0 )																						//---
	#define	HVPP_BS_OUT_01									( HVPP_BS2_OUT_0,HVPP_BS1_OUT_1 )																						//---
	#define	HVPP_BS_OUT_10									( HVPP_BS2_OUT_1,HVPP_BS1_OUT_0 )																						//---
	#define	HVPP_BS_OUT_11									( HVPP_BS2_OUT_1,HVPP_BS1_OUT_0 )																						//---
	#define	HVPP_BS_SELECT_ADDR_LOW							HVPP_BS_OUT_00																											//---ѡ���λ��ַ
	#define	HVPP_BS_SELECT_ADDR_HIGH						HVPP_BS_OUT_01																											//---ѡ���λ��ַ
	#define	HVPP_BS_SELECT_ADDR_EXTERN						HVPP_BS_OUT_10																											//---ѡ����չλ��ַ
	#define	HVPP_BS_SELECT_DATA_LOW							HVPP_BS_OUT_00																											//---ѡ���λ����
	#define	HVPP_BS_SELECT_DATA_HIGH						HVPP_BS_OUT_01																											//---ѡ���λ����
	//<<<===BS2,BS1��ϱ��빦��---����

	//>>>===����͵�ַ���صı���---��ʼ
	#define HVPP_ENABLE_CMD_LOAD							( HVPP_XA_LOAD_CMD,HVPP_BS_OUT_00 )																						//---�������
	#define HVPP_ENABLE_ADDR_LOAD_LOW						( HVPP_XA_LOAD_ADDR,HVPP_BS_SELECT_ADDR_LOW )																						//---��λ��ַ����
	#define HVPP_ENABLE_ADDR_LOAD_HIGH						( HVPP_XA_LOAD_ADDR,HVPP_BS_SELECT_ADDR_HIGH )																						//---��λ��ַ����														
	#define HVPP_ENABLE_ADDR_LOAD_EXTERN					( HVPP_XA_LOAD_ADDR,HVPP_BS_SELECT_ADDR_EXTERN )																						//---��չλ��ַ����	
	#define HVPP_ENABLE_DATA_LOAD_LOW						( HVPP_BS_SELECT_DATA_LOW,HVPP_XA_LOAD_DATA )																						//---��λ���ݼ���
	#define HVPP_ENABLE_DATA_LOAD_HIGH						( HVPP_BS_SELECT_DATA_HIGH,HVPP_XA_LOAD_DATA )																						//---��λ���ݼ���
	//<<<===����͵�ַ���صı���---����

	//===�ȴ�״̬�ȶ����ͺ�ʱ��
	#define HVPP_WAIT_STATE_STABLE							DELAY_NOP_COUNT(8)																										//---�ȴ�����ʱ�����ڣ��������ݵ��ȶ�

	//===�����ѹģʽ֮ǰ����ʼ�����ƶ�
	#define HVPP_CTRL_INIT_READ								( HVPP_CTRL_BUS_READ ,HVPP_CTRL_BUS_VAL(0x7F),HVPP_CTRL_DIR_TO_DEVICE )													//---�����ѹģʽ֮ǰ����ʼ�����ƶ�
	#define HVPP_CTRL_INIT_WRITE							( HVPP_CTRL_BUS_WRITE,HVPP_CTRL_BUS_VAL(0x36),HVPP_CTRL_DIR_TO_DEVICE )													//---�����ѹģʽ֮�󣬳�ʼ�����ƶ�

	//===���и�ѹ��DUT��Դ
	#define HVPP_DUT_POWER_ON								LM317_POWER_ON																											//---������Դ
	#define HVPP_DUT_POWER_HZ								LM317_POWER_HZ																											//---�ⲿ�ṩ��Դ�������Դ���ش��ڲ���ͨ״̬
	#define HVPP_DUT_POWER_OFF								LM317_POWER_OFF																											//---�رյ�Դ����Դ�����ͨ��MOS�ܶ�·����
	
	//===���и�ѹ��REST�Ĳ���
	#define HVPP_DUT_RST_TO_GND								RST_PORT_TO_GND																											//---RST�ӵ�
	#define HVPP_DUT_RST_TO_VCC								RST_PORT_TO_VCC																											//---RST�ӵ������Դ
	#define HVPP_DUT_RST_TO_12V								RST_PORT_TO_12V																											//---RST�ӵ���ѹ12V
	#define HVPP_DUT_RST_TO_HZ								RST_PORT_TO_HZ																											//---RST���ڸ���״̬����������Ҳ������
	
	//>>>===��ѹ�����������---��ʼ
	#define HVPP_CMD_CHIP_ERASE								0x80//(0b10000000)																												//---оƬ����
	#define HVPP_CMD_WRITE_CHIP_FUSE						0x40//(0b01000000)																												//---д��˿λ
	#define HVPP_CMD_WRITE_CHIP_LOCK						0x20//(0b00100000)																												//---д����λ
	#define HVPP_CMD_WRITE_FLASH							0x10//(0b00010000)																												//---дFLASH
	#define HVPP_CMD_WRITE_EEPROM							0x11//(0b00010001)																												//---дEEPROM
	#define HVPP_CMD_READ_ID_AND_CALIBRATION				0x08//(0b00001000)																												//---����ʶ�ֺ�У׼�ֽ�
	#define HVPP_CMD_READ_FUSE_AND_LOCK						0x04//(0b00000100)																												//---��ȡ��˿λ�ͼ���λ
	#define HVPP_CMD_READ_FLASH								0x02//(0b00000010)																												//---��ȡFLASH
	#define HVPP_CMD_READ_EEPROM							0x03//(0b00000011)																												//---��ȡEEPROM
	//<<<===��ѹ�����������---����

	//===�������ߵ�ģʽ
	#define HVPP_DATA_BUS_MODE_READ							0																														//---������ߴ��ڶ�ȡģʽ
	#define HVPP_DATA_BUS_MODE_WRITE						1																														//---�������ߴ���д��ģʽ
				
	//===�������ߵĶ�ȡģʽ	
	#define HVPP_DATA_BUS_READ_DIR							0																														//---�л��������ߵķ���Ϊ��ȡģʽ
	#define HVPP_DATA_BUS_READ_VAL							1																														//---��ȡ���������ϵ�����
			
	//===����ISP״̬���ֵ�ʱ��״̬
	#define HVPP_STATE_TIME_OUT_MS							500

	//===����ṹ��
	typedef struct _HVPP_HandleType						HVPP_HandleType;
	//===����ָ��ṹ��
	typedef struct _HVPP_HandleType						* pHVPP_HandleType;
	//===�ṹ�����
	struct _HVPP_HandleType
	{
		UINT8_T		msgState;																																						//---���״̬��0---����״̬��1---���״̬
		UINT8_T		msgHvFastMode;																																					//---�Ƿ�ʹ���ٱ��ģʽ��0---����ģʽ��1---����ģʽ
		UINT8_T		msgFactoryPattern;																																				//---�Ƿ���˹���ģʽ��0---δ�򿪹���ģʽ��1---�򿪹���ģʽ
		UINT8_T		msgSelfPower;																																					//---�ǲ����Լ�����0---�Լ����磬1---�ⲿ����
		UINT8_T		msgXtalPulseWidth;																																				//---XTAL�˿ڵ�ʱ�Ӹ���
		UINT8_T		msgHvCmd;																																						//---��ѹ������0---����ģʽ��1---����ģʽ
		UINT8_T		msgLoadCmd;																																						//---���и�ѹģʽ�£��Ƿ���������0---δ���أ�1--�Ѿ�����
		UINT8_T		msgDataBusState;																																				//---DATABus���ߵ�״̬��0---��ȡ״̬��1---д��״̬
		UINT8_T		msgWaitms;																																						//---���֮�����ʱ��������λ��ms
		UINT8_T		msgPollReady;																																					//---�Ƿ���ѯ׼�����źţ�0---����Ҫ��1---��Ҫ
		UINT8_T		msgEepromPageMode;																																				//---eeprom�Ƿ�֧��ҳ���ģʽ��0---��֧�֣�1---֧��
		UINT16_T	msgFlashPerPageWordSize;																																		//---Flash��ÿҳ����
		UINT16_T	msgEerpomPerPageByteSize;																																		//---Eeprom��ÿҳ�ֽ���
		UINT16_T	msgPageWordIndex;																																				//---Flash�����������
		UINT16_T	msgIntervalTime;																																				//---��ѯʱ����,��λ��ms
		UINT16_T	msgProgWRLus;																																					//---д��������
		UINT16_T	msgProgWRHus;																																					//---д��������
		UINT32_T	msgRecordTick;																																					//---��¼��ʱ�����
		UINT32_T	(*pMsgTimeTick)(void);																																			//---���ڳ�ʱ����
		void(*pMsgDelayus)(UINT32_T delay);																																			//---us��ʱ����
		void(*pMsgDelayms)(UINT32_T delay);																																			//---ms��ʱ����
	};
	
	//===������
	#define HVPP_TASK_ONE								pHvppDevice0																												//---����1
	#define HVPP_TASK_TWO								0																															//---����2
	#define HVPP_TASK_THREE								0																															//---����3

	//===�ⲿ���ú���
	extern HVPP_HandleType								g_HvppDevice0;
	extern pHVPP_HandleType							pHvppDevice0 ;

	//===��������
	UINT8_T HVPP_DATABUS_WRITE(HVPP_HandleType* HVPPx, UINT8_T val);
	UINT8_T HVPP_DATABUS_READ(HVPP_HandleType* HVPPx, UINT8_T isReadDir);
	UINT8_T HVPP_GPIO_Init(HVPP_HandleType* HVPPx);
	UINT8_T HVPP_GPIO_DeInit(HVPP_HandleType* HVPPx);
	void HVPP_XTAL_CLK(HVPP_HandleType* HVPPx, UINT8_T clkNum);
	void HVPP_XTAL_PULSE(HVPP_HandleType* HVPPx);
	void HVPP_AddWatchDevice0(void);
	void HVPP_WatchTask(HVPP_HandleType* HVPPx);
	UINT8_T HVPP_AddWatch(HVPP_HandleType* HVPPx);
	UINT8_T HVPP_RemoveWatch(HVPP_HandleType* HVPPx);
	UINT8_T HVPP_RefreshWatch(HVPP_HandleType* HVPPx);
	UINT8_T HVPP_SetIntervalTime(HVPP_HandleType* HVPPx, UINT16_T intervalTime);
	UINT8_T HVPP_GetIntervalTime(HVPP_HandleType* HVPPx);
	UINT8_T HVPP_Init(HVPP_HandleType* HVPPx, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void));
	UINT8_T HVPP_DeInit(HVPP_HandleType* HVPPx);
	UINT8_T HVPP_ProgModeEnter(HVPP_HandleType* HVPPx, UINT8_T pagel, UINT8_T xa1, UINT8_T xa0, UINT8_T bs1);
	UINT8_T HVPP_ProgModeExit(HVPP_HandleType* HVPPx);
	UINT8_T HVPP_EnterProg(HVPP_HandleType* HVPPx, UINT8_T hvModeCmd);
	UINT8_T HVPP_ExitProg(HVPP_HandleType* HVPPx);
	UINT8_T HVPP_ReadChipID(HVPP_HandleType* HVPPx, UINT8_T* pVal);
	UINT8_T HVPP_ReadChipCalibration(HVPP_HandleType* HVPPx, UINT8_T* pVal, UINT8_T length);
	UINT8_T HVPP_ReadChipFuse(HVPP_HandleType* HVPPx, UINT8_T* pVal, UINT8_T isNeedExternFuse);
	UINT8_T HVPP_ReadChipLock(HVPP_HandleType* HVPPx, UINT8_T* pVal);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*HVPP_CFG_H_ */
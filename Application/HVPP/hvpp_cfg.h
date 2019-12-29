#ifndef HVPP_CFG_H_
#define HVPP_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "gpio_task.h"
	//////////////////////////////////////////////////////////////////////////////////////

	//=============HVPPʹ�õĶ˿ں��ϵ��ʼ����״̬========================================
	//===HVPP_RDY_BSY	---����Ϊ���룬��������ѹ���̶�������
	//===HVPP_OE		---����Ϊ�����Ĭ���Ǹߵ�ƽ�������ŵ͵�ƽ��Ч
	//===HVPP_WR		---����Ϊ�����Ĭ���Ǹߵ�ƽ�������ŵ͵�ƽ��Ч
	//===HVPP_BS1		---����Ϊ�����
	//===HVPP_XA0		---����Ϊ�����Ĭ���Ǹߵ�ƽ����XA1�ĸߵ�ƽ���Ϊ����ģʽ
	//===HVPP_XA1		---����Ϊ�����Ĭ���Ǹߵ�ƽ����XA0�ĸߵ�ƽ���Ϊ����ģʽ
	//===HVPP_PAGEL		---����Ϊ�����
	//===HVPP_BS2		---����Ϊ�����
	//===HVPP_DATA		---����Ϊ���룬Ĭ����Ҫ��ȡ�ⲿ����
	//===================================================================================
	//===O---���æ��1---�ȴ������device--->>>host---O
	#define HVPP_RDY_BSY_PORT						GPIOC
	#define HVPP_RDY_BSY_BIT						LL_GPIO_PIN_15
	#define HVPP_RDY_BSY_STATE						GPIO_GET_STATE(HVPP_RDY_BSY_PORT,HVPP_RDY_BSY_BIT)
	#define HVPP_RDY_BSY_WRITE						GPIO_SET_WRITE(HVPP_RDY_BSY_PORT,HVPP_RDY_BSY_BIT)
	#define HVPP_RDY_BSY_READ						GPIO_SET_READ( HVPP_RDY_BSY_PORT,HVPP_RDY_BSY_BIT)
	#define HVPP_RDY_BSY_OUT_0						GPIO_OUT_0(    HVPP_RDY_BSY_PORT,HVPP_RDY_BSY_BIT)
	#define HVPP_RDY_BSY_OUT_1						GPIO_OUT_1(    HVPP_RDY_BSY_PORT,HVPP_RDY_BSY_BIT)
	#define HVPP_RDY_BSY_OUT_C						GPIO_OUT_C(    HVPP_RDY_BSY_PORT,HVPP_RDY_BSY_BIT)

	//===���ʹ�ܣ��͵�ƽ��Ч��device--->>>host---I
	#define HVPP_OE_PORT							GPIOE
	#define HVPP_OE_BIT								LL_GPIO_PIN_9
	#define HVPP_OE_STATE							GPIO_GET_STATE(HVPP_OE_PORT,HVPP_OE_BIT)
	#define HVPP_OE_WRITE							GPIO_SET_WRITE(HVPP_OE_PORT,HVPP_OE_BIT)
	#define HVPP_OE_READ							GPIO_SET_READ( HVPP_OE_PORT,HVPP_OE_BIT)
	#define HVPP_OE_OUT_0							GPIO_OUT_0(    HVPP_OE_PORT,HVPP_OE_BIT)
	#define HVPP_OE_OUT_1							GPIO_OUT_1(    HVPP_OE_PORT,HVPP_OE_BIT)
	#define HVPP_OE_OUT_C							GPIO_OUT_C(    HVPP_OE_PORT,HVPP_OE_BIT)

	//===д���壬�͵�ƽ��Ч��device--->>>host---I
	#define HVPP_WR_PORT							GPIOE
	#define HVPP_WR_BIT								LL_GPIO_PIN_10
	#define HVPP_WR_STATE							GPIO_GET_STATE(HVPP_WR_PORT,HVPP_WR_BIT)
	#define HVPP_WR_WRITE							GPIO_SET_WRITE(HVPP_WR_PORT,HVPP_WR_BIT)
	#define HVPP_WR_READ							GPIO_SET_READ( HVPP_WR_PORT,HVPP_WR_BIT)
	#define HVPP_WR_OUT_0							GPIO_OUT_0(    HVPP_WR_PORT,HVPP_WR_BIT)
	#define HVPP_WR_OUT_1							GPIO_OUT_1(    HVPP_WR_PORT,HVPP_WR_BIT)
	#define HVPP_WR_OUT_C							GPIO_OUT_C(    HVPP_WR_PORT,HVPP_WR_BIT)

	//===�ֽ�ѡ��1(0---ѡ����ֽڣ�1---ѡ����ֽ�)��device--->>>host---I
	#define HVPP_BS1_PORT							GPIOE
	#define HVPP_BS1_BIT							LL_GPIO_PIN_11
	#define HVPP_BS1_STATE							GPIO_GET_STATE(HVPP_BS1_PORT,HVPP_BS1_BIT)
	#define HVPP_BS1_WRITE							GPIO_SET_WRITE(HVPP_BS1_PORT,HVPP_BS1_BIT)
	#define HVPP_BS1_READ							GPIO_SET_READ( HVPP_BS1_PORT,HVPP_BS1_BIT)
	#define HVPP_BS1_OUT_0							GPIO_OUT_0(    HVPP_BS1_PORT,HVPP_BS1_BIT)
	#define HVPP_BS1_OUT_1							GPIO_OUT_1(    HVPP_BS1_PORT,HVPP_BS1_BIT)
	#define HVPP_BS1_OUT_C							GPIO_OUT_C(    HVPP_BS1_PORT,HVPP_BS1_BIT)

	//===XTAL����0��device--->>>host---I
	#define HVPP_XA0_PORT							GPIOE
	#define HVPP_XA0_BIT							LL_GPIO_PIN_12
	#define HVPP_XA0_STATE							GPIO_GET_STATE(HVPP_XA0_PORT,HVPP_XA0_BIT)
	#define HVPP_XA0_WRITE							GPIO_SET_WRITE(HVPP_XA0_PORT,HVPP_XA0_BIT)
	#define HVPP_XA0_READ							GPIO_SET_READ( HVPP_XA0_PORT,HVPP_XA0_BIT)
	#define HVPP_XA0_OUT_0							GPIO_OUT_0(    HVPP_XA0_PORT,HVPP_XA0_BIT)
	#define HVPP_XA0_OUT_1							GPIO_OUT_1(    HVPP_XA0_PORT,HVPP_XA0_BIT)
	#define HVPP_XA0_OUT_C							GPIO_OUT_C(    HVPP_XA0_PORT,HVPP_XA0_BIT)

	//===XTAL����1��device--->>>host---I
	#define HVPP_XA1_PORT							GPIOE
	#define HVPP_XA1_BIT							LL_GPIO_PIN_13
	#define HVPP_XA1_STATE							GPIO_GET_STATE(HVPP_XA1_PORT,HVPP_XA1_BIT)
	#define HVPP_XA1_WRITE							GPIO_SET_WRITE(HVPP_XA1_PORT,HVPP_XA1_BIT)
	#define HVPP_XA1_READ							GPIO_SET_READ( HVPP_XA1_PORT,HVPP_XA1_BIT)
	#define HVPP_XA1_OUT_0							GPIO_OUT_0(    HVPP_XA1_PORT,HVPP_XA1_BIT)
	#define HVPP_XA1_OUT_1							GPIO_OUT_1(    HVPP_XA1_PORT,HVPP_XA1_BIT)
	#define HVPP_XA1_OUT_C							GPIO_OUT_C(    HVPP_XA1_PORT,HVPP_XA1_BIT)

	//===���س���洢����EEPROM����ҳ��device--->>>host---I
	#define HVPP_PAGEL_PORT							GPIOE
	#define HVPP_PAGEL_BIT							LL_GPIO_PIN_14
	#define HVPP_PAGEL_STATE						GPIO_GET_STATE(HVPP_PAGEL_PORT,HVPP_PAGEL_BIT)
	#define HVPP_PAGEL_WRITE						GPIO_SET_WRITE(HVPP_PAGEL_PORT,HVPP_PAGEL_BIT)
	#define HVPP_PAGEL_READ							GPIO_SET_READ( HVPP_PAGEL_PORT,HVPP_PAGEL_BIT)
	#define HVPP_PAGEL_OUT_0						GPIO_OUT_0(    HVPP_PAGEL_PORT,HVPP_PAGEL_BIT)
	#define HVPP_PAGEL_OUT_1						GPIO_OUT_1(    HVPP_PAGEL_PORT,HVPP_PAGEL_BIT)
	#define HVPP_PAGEL_OUT_C						GPIO_OUT_C(    HVPP_PAGEL_PORT,HVPP_PAGEL_BIT)

	//===�ֽ�ѡ��2(0---ѡ����ֽڣ�1---ѡ��ڶ������ֽ�)��device--->>>host---I
	#define HVPP_BS2_PORT							GPIOE
	#define HVPP_BS2_BIT							LL_GPIO_PIN_8
	#define HVPP_BS2_STATE							GPIO_GET_STATE(DECA_CH_PORT,DECA_CH_BIT)
	#define HVPP_BS2_WRITE							GPIO_SET_WRITE(DECA_CH_PORT,DECA_CH_BIT)
	#define HVPP_BS2_READ							GPIO_SET_READ( DECA_CH_PORT,DECA_CH_BIT)
	#define HVPP_BS2_OUT_0							GPIO_OUT_0(    DECA_CH_PORT,DECA_CH_BIT)
	#define HVPP_BS2_OUT_1							GPIO_OUT_1(    DECA_CH_PORT,DECA_CH_BIT)
	#define HVPP_BS2_OUT_C							GPIO_OUT_C(    DECA_CH_PORT,DECA_CH_BIT)

	//===ʱ�����ţ�device--->>>host---I
	#define HVPP_XTAL_PORT							GPIOE
	#define HVPP_XTAL_BIT							LL_GPIO_PIN_15
	#define HVPP_XTAL_STATE							GPIO_GET_STATE(DECA_CH_PORT,DECA_CH_BIT)
	#define HVPP_XTAL_WRITE							GPIO_SET_WRITE(DECA_CH_PORT,DECA_CH_BIT)
	#define HVPP_XTAL_READ							GPIO_SET_READ( DECA_CH_PORT,DECA_CH_BIT)
	#define HVPP_XTAL_OUT_0							GPIO_OUT_0(    DECA_CH_PORT,DECA_CH_BIT)
	#define HVPP_XTAL_OUT_1							GPIO_OUT_1(    DECA_CH_PORT,DECA_CH_BIT)
	#define HVPP_XTAL_OUT_C							GPIO_OUT_C(    DECA_CH_PORT,DECA_CH_BIT)

	//===�������ʹ���ź�
	#define HVPP_CTRL_OE_PORT						GPIOD
	#define HVPP_CTRL_OE_BIT						LL_GPIO_PIN_4
	#define HVPP_CTRL_OE_STATE						GPIO_GET_STATE(HVPP_CTRL_OE_PORT,HVPP_CTRL_OE_BIT)
	#define HVPP_CTRL_OE_WRITE						GPIO_SET_WRITE(HVPP_CTRL_OE_PORT,HVPP_CTRL_OE_BIT)
	#define HVPP_CTRL_OE_READ						GPIO_SET_READ( HVPP_CTRL_OE_PORT,HVPP_CTRL_OE_BIT)
	#define HVPP_CTRL_OE_OUT_0						GPIO_OUT_0(    HVPP_CTRL_OE_PORT,HVPP_CTRL_OE_BIT)
	#define HVPP_CTRL_OE_OUT_1						GPIO_OUT_1(    HVPP_CTRL_OE_PORT,HVPP_CTRL_OE_BIT)
	#define HVPP_CTRL_OE_OUT_C						GPIO_OUT_C(    HVPP_CTRL_OE_PORT,HVPP_CTRL_OE_BIT)

	//===��ƽת��оƬ����������
	#define HVPP_CTRL_TO_DEVICE						HVPP_CTRL_OE_OUT_0					
	#define HVPP_CTRL_TO_HZ							HVPP_CTRL_OE_OUT_1

	//===˫����������Bit0(OEΪ��ʱ���)��device--->>>host---I/O
	#define HVPP_DATA0_PORT							GPIOE
	#define HVPP_DATA0_BIT							LL_GPIO_PIN_7
	#define HVPP_DATA0_STATE						GPIO_GET_STATE(HVPP_DATA0_PORT,HVPP_DATA0_BIT)
	#define HVPP_DATA0_WRITE						GPIO_SET_WRITE(HVPP_DATA0_PORT,HVPP_DATA0_BIT)
	#define HVPP_DATA0_READ							GPIO_SET_READ( HVPP_DATA0_PORT,HVPP_DATA0_BIT)
	#define HVPP_DATA0_OUT_0						GPIO_OUT_0(    HVPP_DATA0_PORT,HVPP_DATA0_BIT)
	#define HVPP_DATA0_OUT_1						GPIO_OUT_1(    HVPP_DATA0_PORT,HVPP_DATA0_BIT)
	#define HVPP_DATA0_OUT_C						GPIO_OUT_C(    HVPP_DATA0_PORT,HVPP_DATA0_BIT)

	//===˫����������Bit1(OEΪ��ʱ���)��device--->>>host---I/O
	#define HVPP_DATA1_PORT							GPIOE
	#define HVPP_DATA1_BIT							LL_GPIO_PIN_6
	#define HVPP_DATA1_STATE						GPIO_GET_STATE(HVPP_DATA1_PORT,HVPP_DATA1_BIT)
	#define HVPP_DATA1_WRITE						GPIO_SET_WRITE(HVPP_DATA1_PORT,HVPP_DATA1_BIT)
	#define HVPP_DATA1_READ							GPIO_SET_READ( HVPP_DATA1_PORT,HVPP_DATA1_BIT)
	#define HVPP_DATA1_OUT_0						GPIO_OUT_0(    HVPP_DATA1_PORT,HVPP_DATA1_BIT)
	#define HVPP_DATA1_OUT_1						GPIO_OUT_1(    HVPP_DATA1_PORT,HVPP_DATA1_BIT)
	#define HVPP_DATA1_OUT_C						GPIO_OUT_C(    HVPP_DATA1_PORT,HVPP_DATA1_BIT)

	//===˫����������Bit2(OEΪ��ʱ���)��device--->>>host---I/O
	#define HVPP_DATA2_PORT							GPIOE
	#define HVPP_DATA2_BIT							LL_GPIO_PIN_5
	#define HVPP_DATA2_STATE						GPIO_GET_STATE(HVPP_DATA2_PORT,HVPP_DATA2_BIT)
	#define HVPP_DATA2_WRITE						GPIO_SET_WRITE(HVPP_DATA2_PORT,HVPP_DATA2_BIT)
	#define HVPP_DATA2_READ							GPIO_SET_READ( HVPP_DATA2_PORT,HVPP_DATA2_BIT)
	#define HVPP_DATA2_OUT_0						GPIO_OUT_0(    HVPP_DATA2_PORT,HVPP_DATA2_BIT)
	#define HVPP_DATA2_OUT_1						GPIO_OUT_1(    HVPP_DATA2_PORT,HVPP_DATA2_BIT)
	#define HVPP_DATA2_OUT_C						GPIO_OUT_C(    HVPP_DATA2_PORT,HVPP_DATA2_BIT)

	//===˫����������Bit3(OEΪ��ʱ���)��device--->>>host---I/O
	#define HVPP_DATA3_PORT							GPIOE
	#define HVPP_DATA3_BIT							LL_GPIO_PIN_4
	#define HVPP_DATA3_STATE						GPIO_GET_STATE(HVPP_DATA3_PORT,HVPP_DATA3_BIT)
	#define HVPP_DATA3_WRITE						GPIO_SET_WRITE(HVPP_DATA3_PORT,HVPP_DATA3_BIT)
	#define HVPP_DATA3_READ							GPIO_SET_READ( HVPP_DATA3_PORT,HVPP_DATA3_BIT)
	#define HVPP_DATA3_OUT_0						GPIO_OUT_0(    HVPP_DATA3_PORT,HVPP_DATA3_BIT)
	#define HVPP_DATA3_OUT_1						GPIO_OUT_1(    HVPP_DATA3_PORT,HVPP_DATA3_BIT)
	#define HVPP_DATA3_OUT_C						GPIO_OUT_C(    HVPP_DATA3_PORT,HVPP_DATA3_BIT)

	//===˫����������Bit4(OEΪ��ʱ���)��device--->>>host---I/O
	#define HVPP_DATA4_PORT							GPIOE
	#define HVPP_DATA4_BIT							LL_GPIO_PIN_3
	#define HVPP_DATA4_STATE						GPIO_GET_STATE(HVPP_DATA4_PORT,HVPP_DATA4_BIT)
	#define HVPP_DATA4_WRITE						GPIO_SET_WRITE(HVPP_DATA4_PORT,HVPP_DATA4_BIT)
	#define HVPP_DATA4_READ							GPIO_SET_READ( HVPP_DATA4_PORT,HVPP_DATA4_BIT)
	#define HVPP_DATA4_OUT_0						GPIO_OUT_0(    HVPP_DATA4_PORT,HVPP_DATA4_BIT)
	#define HVPP_DATA4_OUT_1						GPIO_OUT_1(    HVPP_DATA4_PORT,HVPP_DATA4_BIT)
	#define HVPP_DATA4_OUT_C						GPIO_OUT_C(    HVPP_DATA4_PORT,HVPP_DATA4_BIT)

	//===˫����������Bit5(OEΪ��ʱ���)��device--->>>host---I/O
	#define HVPP_DATA5_PORT							GPIOE
	#define HVPP_DATA5_BIT							LL_GPIO_PIN_2
	#define HVPP_DATA5_STATE						GPIO_GET_STATE(HVPP_DATA5_PORT,HVPP_DATA5_BIT)
	#define HVPP_DATA5_WRITE						GPIO_SET_WRITE(HVPP_DATA5_PORT,HVPP_DATA5_BIT)
	#define HVPP_DATA5_READ							GPIO_SET_READ( HVPP_DATA5_PORT,HVPP_DATA5_BIT)
	#define HVPP_DATA5_OUT_0						GPIO_OUT_0(    HVPP_DATA5_PORT,HVPP_DATA5_BIT)
	#define HVPP_DATA5_OUT_1						GPIO_OUT_1(    HVPP_DATA5_PORT,HVPP_DATA5_BIT)
	#define HVPP_DATA5_OUT_C						GPIO_OUT_C(    HVPP_DATA5_PORT,HVPP_DATA5_BIT)

	//===˫����������Bit6(OEΪ��ʱ���)��device--->>>host---I/O
	#define HVPP_DATA6_PORT							GPIOE
	#define HVPP_DATA6_BIT							LL_GPIO_PIN_1
	#define HVPP_DATA6_STATE						GPIO_GET_STATE(HVPP_DATA6_PORT,HVPP_DATA6_BIT)
	#define HVPP_DATA6_WRITE						GPIO_SET_WRITE(HVPP_DATA6_PORT,HVPP_DATA6_BIT)
	#define HVPP_DATA6_READ							GPIO_SET_READ( HVPP_DATA6_PORT,HVPP_DATA6_BIT)
	#define HVPP_DATA6_OUT_0						GPIO_OUT_0(    HVPP_DATA6_PORT,HVPP_DATA6_BIT)
	#define HVPP_DATA6_OUT_1						GPIO_OUT_1(    HVPP_DATA6_PORT,HVPP_DATA6_BIT)
	#define HVPP_DATA6_OUT_C						GPIO_OUT_C(    HVPP_DATA6_PORT,HVPP_DATA6_BIT)

	//===˫����������Bit7(OEΪ��ʱ���)��device--->>>host---I/O
	#define HVPP_DATA7_PORT							GPIOE
	#define HVPP_DATA7_BIT							LL_GPIO_PIN_0
	#define HVPP_DATA7_STATE						GPIO_GET_STATE(HVPP_DATA7_PORT,HVPP_DATA7_BIT)
	#define HVPP_DATA7_WRITE						GPIO_SET_WRITE(HVPP_DATA7_PORT,HVPP_DATA7_BIT)
	#define HVPP_DATA7_READ							GPIO_SET_READ( HVPP_DATA7_PORT,HVPP_DATA7_BIT)
	#define HVPP_DATA7_OUT_0						GPIO_OUT_0(    HVPP_DATA7_PORT,HVPP_DATA7_BIT)
	#define HVPP_DATA7_OUT_1						GPIO_OUT_1(    HVPP_DATA7_PORT,HVPP_DATA7_BIT)
	#define HVPP_DATA7_OUT_C						GPIO_OUT_C(    HVPP_DATA7_PORT,HVPP_DATA7_BIT)

	//===˫����������(OEΪ��ʱ���)��device--->>>host---I/O
	#define HVPP_DATA_BUS_PORT						GPIOE
	#define HVPP_DATA_BUS_BIT						(LL_GPIO_PIN_0|LL_GPIO_PIN_2|LL_GPIO_PIN_3|LL_GPIO_PIN_4|LL_GPIO_PIN_5|LL_GPIO_PIN_6|LL_GPIO_PIN_7)
	#define HVPP_DATA_BUS_STATE						GPIO_GET_STATE(HVPP_DATA_BUS_PORT,HVPP_DATA_BUS_BIT)
	#define HVPP_DATA_BUS_WRITE						GPIO_SET_WRITE(HVPP_DATA_BUS_PORT,HVPP_DATA_BUS_BIT)
	#define HVPP_DATA_BUS_READ						GPIO_SET_READ( HVPP_DATA_BUS_PORT,HVPP_DATA_BUS_BIT)
	#define HVPP_DATA_BUS_VAL(val)					GPIO_L8BITS_OUT(val)	

	//===����������ʹ���ź�
	#define HVPP_DATA_OE_PORT						GPIOB
	#define HVPP_DATA_OE_BIT						LL_GPIO_PIN_15
	#define HVPP_DATA_OE_STATE						GPIO_GET_STATE(HVPP_DATA_OE_PORT,HVPP_DATA_OE_BIT)
	#define HVPP_DATA_OE_WRITE						GPIO_SET_WRITE(HVPP_DATA_OE_PORT,HVPP_DATA_OE_BIT)
	#define HVPP_DATA_OE_READ						GPIO_SET_READ( HVPP_DATA_OE_PORT,HVPP_DATA_OE_BIT)
	#define HVPP_DATA_OE_OUT_0						GPIO_OUT_0(    HVPP_DATA_OE_PORT,HVPP_DATA_OE_BIT)
	#define HVPP_DATA_OE_OUT_1						GPIO_OUT_1(    HVPP_DATA_OE_PORT,HVPP_DATA_OE_BIT)
	#define HVPP_DATA_OE_OUT_C						GPIO_OUT_C(    HVPP_DATA_OE_PORT,HVPP_DATA_OE_BIT)

	//===����������ʹ�ܷ����ź�
	#define HVPP_DATA_DIR_PORT						GPIOB
	#define HVPP_DATA_DIR_BIT						LL_GPIO_PIN_14
	#define HVPP_DATA_DIR_STATE						GPIO_GET_STATE(HVPP_DATA_DIR_PORT,HVPP_DATA_DIR_BIT)
	#define HVPP_DATA_DIR_WRITE						GPIO_SET_WRITE(HVPP_DATA_DIR_PORT,HVPP_DATA_DIR_BIT)
	#define HVPP_DATA_DIR_READ						GPIO_SET_READ( HVPP_DATA_DIR_PORT,HVPP_DATA_DIR_BIT)
	#define HVPP_DATA_DIR_OUT_0						GPIO_OUT_0(    HVPP_DATA_DIR_PORT,HVPP_DATA_DIR_BIT)
	#define HVPP_DATA_DIR_OUT_1						GPIO_OUT_1(    HVPP_DATA_DIR_PORT,HVPP_DATA_DIR_BIT)
	#define HVPP_DATA_DIR_OUT_C						GPIO_OUT_C(    HVPP_DATA_DIR_PORT,HVPP_DATA_DIR_BIT)

	//===��ƽת��оƬ����������
	#define HVPP_DATA_BUS_TO_DEVICE					(HVPP_DATA_DIR_OUT_1,HVPP_DATA_OE_OUT_0)
	#define HVPP_DATA_BUS_TO_HOST					(HVPP_DATA_DIR_OUT_0,HVPP_DATA_OE_OUT_0)
	#define HVPP_DATA_BUS_TO_HZ						HVPP_DATA_OE_OUT_1

	//>>>===XA0,XA1��ϱ��빦��---��ʼ
	#define HVPP_XA_LOAD_ADDR						( HVPP_XA1_OUT_0,HVPP_XA0_OUT_0 )				//---���ش洢����ַ
	#define HVPP_XA_LOAD_DATA						( HVPP_XA1_OUT_0,HVPP_XA0_OUT_1 )				//---��������
	#define HVPP_XA_LOAD_CMD						( HVPP_XA1_OUT_1,HVPP_XA0_OUT_0 )				//---��������
	#define HVPP_XA_LOAD_IDLE						( HVPP_XA1_OUT_1,HVPP_XA0_OUT_1 )				//---����ģʽ
	//<<<===XA0,XA1��ϱ��빦��---����
	
	//===��ѹ���ģʽ�Ľ���
	#define HVPP_ENTER_PROG_ENABLE_MODE(a,b,c,d)
	
	//>>>===��ѹ�����������---��ʼ
	#define HVPP_CMD_CHIP_ERASE						0B10000000										//---оƬ����
	#define HVPP_CMD_WRITE_CHIP_FUSE				0B01000000										//---д��˿λ
	#define HVPP_CMD_WRITE_CHIP_LOCK				0B00100000										//---д����λ
	#define HVPP_CMD_WRITE_FLASH					0B00010000										//---дFLASH
	#define HVPP_CMD_WRITE_EEPROM					0B00010001										//---дEEPROM
	#define HVPP_CMD_READ_ID_AND_CALIBRATION		0B00001000										//---����ʶ�ֺ�У׼�ֽ�
	#define HVPP_CMD_READ_FUSE_AND_LOCK				0B00000100										//---��ȡ��˿λ�ͼ���λ
	#define HVPP_CMD_READ_FLASH						0B00000010										//---��ȡFLASH
	#define HVPP_CMD_READ_EEPROM					0B00000011										//---��ȡEEPROM
	//<<<===��ѹ�����������---����

	//===�������ߵ�״̬
	#define HVPP_DATA_BUS_STATE_READ				0												//---������ߴ��ڶ�ȡ״̬
	#define HVPP_DATA_BUS_STATE_WRITE				1												//---�������ߴ���д��״̬
				
	//===����ṹ��
	typedef struct _HVPP_HandlerType				HVPP_HandlerType;
	//===����ָ��ṹ��
	typedef struct _HVPP_HandlerType				* pHVPP_HandlerType;
	//===�ṹ�����
	struct _HVPP_HandlerType
	{
		UINT8_T msgDataBusState;																	//---DATABus���ߵ�״̬��0---��ȡ״̬��1---д��״̬
		UINT32_T(*msgTimeTick)(void);																//---���ڳ�ʱ����
		void(*msgDelayus)(UINT32_T delay);															//---us��ʱ����
		void(*msgDelayms)(UINT32_T delay);															//---ms��ʱ����
	};
	
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*HVPP_CFG_H_ */
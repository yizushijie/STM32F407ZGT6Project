#ifndef ENCODE_CFG_H_
#define ENCODE_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include"complier_lib.h"
	#include "gpio_task.h"
	#include"timer_task.h"
	//////////////////////////////////////////////////////////////////////////////////////

	//===������ʹ�õĶ�ʱ��
	#define ENCODE_USE_TIMER							TIM2
	//===��������ʱ���ж�
	#define ENCODE_USE_TIMER_IRQ						TIM2_IRQn
	
	//===CH1�Ķ˿ڶ���---PA0
	#define ENCODE_CH1_PORT								GPIOA
	#define ENCODE_CH1_BIT								LL_GPIO_PIN_0
	#define ENCODE_CH1_WRITE							GPIO_SET_WRITE(	ENCODE_CH1_PORT,ENCODE_CH1_BIT)
	#define ENCODE_CH1_READ								GPIO_SET_READ(	ENCODE_CH1_PORT,ENCODE_CH1_BIT)
	#define ENCODE_CH1_STATE							GPIO_GET_STATE(	ENCODE_CH1_PORT,ENCODE_CH1_BIT)
	#define ENCODE_CH1_OUT_0							GPIO_OUT_0(		ENCODE_CH1_PORT,ENCODE_CH1_BIT)
	#define ENCODE_CH1_OUT_1							GPIO_OUT_1(		ENCODE_CH1_PORT,ENCODE_CH1_BIT)
	#define ENCODE_CH1_OUT_C							GPIO_OUT_C(		ENCODE_CH1_PORT,ENCODE_CH1_BIT)

	//===CH2�Ķ˿ڶ���---PA1
	#define ENCODE_CH2_PORT								GPIOA
	#define ENCODE_CH2_BIT								LL_GPIO_PIN_1
	#define ENCODE_CH2_WRITE							GPIO_SET_WRITE(	ENCODE_CH2_PORT,ENCODE_CH2_BIT)
	#define ENCODE_CH2_READ								GPIO_SET_READ(	ENCODE_CH2_PORT,ENCODE_CH2_BIT)
	#define ENCODE_CH2_STATE							GPIO_GET_STATE(	ENCODE_CH2_PORT,ENCODE_CH2_BIT)
	#define ENCODE_CH2_OUT_0							GPIO_OUT_0(		ENCODE_CH2_PORT,ENCODE_CH2_BIT)
	#define ENCODE_CH2_OUT_1							GPIO_OUT_1(		ENCODE_CH2_PORT,ENCODE_CH2_BIT)
	#define ENCODE_CH2_OUT_C							GPIO_OUT_C(		ENCODE_CH2_PORT,ENCODE_CH2_BIT)

	//===CH3�Ķ˿ڶ���---PA2
	#define ENCODE_CH3_PORT								GPIOA
	#define ENCODE_CH3_BIT								LL_GPIO_PIN_2
	#define ENCODE_CH3_WRITE							GPIO_SET_WRITE(	ENCODE_CH3_PORT,ENCODE_CH3_BIT)
	#define ENCODE_CH3_READ								GPIO_SET_READ(	ENCODE_CH3_PORT,ENCODE_CH3_BIT)
	#define ENCODE_CH3_STATE							GPIO_GET_STATE(	ENCODE_CH3_PORT,ENCODE_CH3_BIT)
	#define ENCODE_CH3_OUT_0							GPIO_OUT_0(		ENCODE_CH3_PORT,ENCODE_CH3_BIT)
	#define ENCODE_CH3_OUT_1							GPIO_OUT_1(		ENCODE_CH3_PORT,ENCODE_CH3_BIT)
	#define ENCODE_CH3_OUT_C							GPIO_OUT_C(		ENCODE_CH3_PORT,ENCODE_CH3_BIT)

	//===CH4�Ķ˿ڶ���---PA3
	#define ENCODE_CH4_PORT								GPIOA
	#define ENCODE_CH4_BIT								LL_GPIO_PIN_3
	#define ENCODE_CH4_WRITE							GPIO_SET_WRITE(	ENCODE_CH4_PORT,ENCODE_CH4_BIT)
	#define ENCODE_CH4_READ								GPIO_SET_READ(	ENCODE_CH4_PORT,ENCODE_CH4_BIT)
	#define ENCODE_CH4_STATE							GPIO_GET_STATE(	ENCODE_CH4_PORT,ENCODE_CH4_BIT)
	#define ENCODE_CH4_OUT_0							GPIO_OUT_0(		ENCODE_CH4_PORT,ENCODE_CH4_BIT)
	#define ENCODE_CH4_OUT_1							GPIO_OUT_1(		ENCODE_CH4_PORT,ENCODE_CH4_BIT)
	#define ENCODE_CH4_OUT_C							GPIO_OUT_C(		ENCODE_CH4_PORT,ENCODE_CH4_BIT)

	//===�������˿�����
	#define ENCODE_BUS_PORT								GPIOA
	#define ENCODE_BUS_BITS								( LL_GPIO_PIN_3|LL_GPIO_PIN_2|LL_GPIO_PIN_1|LL_GPIO_PIN_0 )
	#define ENCODE_BUS_MASK								0xFFF0
	#define ENCODE_BUS_OUT(val)							( ENCODE_BUS_PORT->ODR=(ENCODE_BUS_PORT->ODR&ENCODE_BUS_MASK)|(val&ENCODE_BUS_BITS) )
	
	//===����ṹ��
	typedef struct _EnCode_HandlerType		EnCode_HandlerType;

	//===����ṹ��ָ��
	typedef struct _EnCode_HandlerType		*pEnCode_HandlerType;

	//===����������ı���ṹ��
	struct _EnCode_HandlerType
	{
		UINT8_T codeLength;								// #1 ����PT2262����Ч�����볤
		UINT8_T codeMode;								// ����ģʽ 0��2262����,1:1KHz����;2:500Hz����
		UINT8_T codeVal[20];							// �������飬ֻ��2262��Ч
	};

	//===�������ĳ���
	#define GEN_CODE_FRAME_LENGTH						16		
	//===������֡��,���ֵΪ7
	#define GEN_CODE_FRAME_COUNT						3
	//===�����������ֽ�����
	#define	GEN_CODE_BYTE_OF_CYCLE_COUNT				( GEN_CODE_FRAME_COUNT*GEN_CODE_FRAME_LENGTH*8 )	

	//===������ͨ��1	---433M		С�ź�
	#define ENCODE_CH1_INDEX							0x01
	//===������ͨ��2	---4333M	���ź�
	#define ENCODE_CH2_INDEX							0x02
	//===������ͨ��3	---315M		�ź�
	#define ENCODE_CH3_INDEX							0x04
	//===������ͨ��4	---2xxM		�ź�	
	#define ENCODE_CH4_INDEX							0x08

	//===�������ı���ʱ��
	#define ENCODE_TIMER_BASE_US						500
	//===��ʱ���ķ�Ƶ����72MHzʱ�ӣ�ÿ500us����ж�һ�Σ�
	#define ENCODE_TIMER_ARR							( SYS_CLOCK_MHZ-1 )
	//===��ʱ��������װ��ֵ
	#define ENCODE_TIMER_RELOAD							( 500-1 )
	
	//===��������
	typedef enum
	{
		CMD_ENCODE_NONE				= 0,
		CMD_ENCODE_CHA_OPEN			= 1,				//��RF�ź�Դͨ��1
		CMD_ENCODE_CHA_CLOSE		= 2,				//�ر�RF�ź�Դͨ��1
		CMD_ENCODE_CHB_OPEN			= 3,				//��RF�ź�Դͨ��2
		CMD_ENCODE_CHB_CLOSE		= 4,				//�ر�RF�ź�Դͨ��2
		CMD_ENCODE_CHC_OPEN			= 5,				//��RF�ź�Դͨ��3
		CMD_ENCODE_CHC_CLOSE		= 6,				//�ر�RF�ź�Դͨ��3
		CMD_ENCODE_CHD_OPEN			= 7,				//��RF�ź�Դͨ��4
		CMD_ENCODE_CHD_CLOSE		= 8,				//�ر�RF�ź�Դͨ��5
		CMD_DECODE_RST				= 9,				//��λ�����״̬
		CMD_DECODE_READ				= 10,				//��ȡ�����״̬
		CMD_ENCODE_CHA_HIGH			= 11,				//�ź�Դͨ�������
		CMD_ENCODE_CHB_HIGH			= 12,				//�ź�Դͨ�������
		CMD_ENCODE_CHC_HIGH			= 13,				//�ź�Դͨ�������
		CMD_ENCODE_CHD_HIGH			= 14,				//�ź�Դͨ�������

	}RF_CMD_CODE;

	//===�����ź�Դ����������
	#define CMD_ENCODE				0xA1

	//===�ⲿ���ýӿ�
	extern VLTUINT8_T g_GenCodeChannelMask1;
	extern VLTUINT8_T g_GenCodeChannelMask2;
	//===��������
	void Encode_Init(void);
	void EnCode_IRQTask( void );
	void EnCode_SetChannel(UINT8_T chIndex, UINT8_T isEnCode, UINT8_T isHigh);

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*ENCODE_CFG_H_ */
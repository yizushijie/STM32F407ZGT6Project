#ifndef ADC_CFG_H_
#define ADC_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "delay_task.h"
	#include "gpio_task.h"
	//////////////////////////////////////////////////////////////////////////////////////
	///////PC0---ADCChannel10
	///////PC1---ADCChannel11
	///////PC2---ADCChannel12
	///////PC3---ADCChannel13
	///////ADC1��ADC3���ܷ���DMA����
	///////ADC���ֵ�������Ҫ���ݲ�ͬ����Ҫ���и��ģ���ͬ����Ŀ��Ҫ�����÷�ʽ��һ�£���Ҫ��������޸�
	#define  ADC_CHANNEL_NUM					1//2
	#define	 ADC_CHANNEL_SIZE					18
	#define  ADC_CHANNEL_MAX_SIZE				( ADC_CHANNEL_NUM*ADC_CHANNEL_SIZE )
	
	//===����ṹ��
	typedef struct _ADCASK_HandlerType			ADCASK_HandlerType;
	//===����ָ��ṹ��
	typedef struct _ADCASK_HandlerType			*pADCASK_HandlerType;
	//===�ṹ�����
	struct _ADCASK_HandlerType
	{
		UINT8_T  msgFlag;									//---0δת�� 1 ת�����
		UINT16_T msgAChannelVal;							//---ͨ��A��ֵ
		UINT16_T msgBChannelVal;							//---ͨ��B��ֵ
		UINT16_T msgADCConvVal[ADC_CHANNEL_MAX_SIZE];		//---���ݴ洢�Ļ�����
	};

	//===�ⲿ���ýӿ�
	extern ADCASK_HandlerType	g_ABChannelADC;
	extern pADCASK_HandlerType	pABChannelADC;
	extern ADCASK_HandlerType	g_CDChannelADC;
	extern pADCASK_HandlerType	pCDChannelADC;

	//===��������
	UINT8_T ADC_GPIO_Init(void);
	UINT8_T ADC_Clock(ADC_TypeDef *ADCx, UINT8_T isEnable);
	UINT8_T ADC_ADC1_Init(void);
	UINT8_T ADC_StartCalibration(ADC_TypeDef *ADCx);
	UINT8_T ADC_ADC1_DMA_Init(void);
	UINT8_T ADC_ADC1_DMA_Restart(void);
	UINT8_T ADC_ADC1_DMA_Stop(void);
	UINT8_T ADC_ADC3_Init(void);
	UINT8_T ADC_ADC3_DMA_Init(void);
	UINT8_T ADC_ADC3_DMA_Restart(void);
	UINT8_T ADC_ADC3_DMA_Stop(void);
	UINT8_T ADC_SoftStart(ADC_TypeDef *ADCx1, ADC_TypeDef *ADCx2, ADC_TypeDef *ADCx3);
	UINT8_T ADC_ADC1Task_Init(void);
	UINT8_T ADC_ADC3Task_Init(void);
	UINT8_T ADC_ADCTask_Init(void);
	UINT8_T ADC_ADC_Init(void);
	UINT8_T ADC_ADCTask_START(ADC_TypeDef *ADCx);
	UINT8_T ADC_ADCTask_STOP(ADC_TypeDef *ADCx);
	UINT8_T ADC_HandleChannelVal(ADCASK_HandlerType *ADCASKx);
	UINT16_T ADC_GetChipPower(void);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*ADC_CFG_H_ */

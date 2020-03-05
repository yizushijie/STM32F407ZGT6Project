#ifndef NTC_CFG_H_
#define NTC_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	//////////////////////////////////////////////////////////////////////////////////////
	#define NTC_SMP_RES					10																				//---NTC��������Ĵ�С
	#define	NTC_TO_VCC																									//---NTC������ڿ�����Դ��	
	#define NTC_ADC_FULL_RANGE			(float)4095.0																	//---ADC�������̶�Ӧ��������
	//===�ж�NTC����Ľӷ�
	#ifdef NTC_TO_VCC
		#define NTC_SMP_ADC(ntc)		(UINT16_T)(((NTC_SMP_RES*NTC_ADC_FULL_RANGE)/(ntc+NTC_SMP_RES)))				//---NTC��ֵ��ADC��ϵ
	#else
		#define NTC_SMP_ADC(ntc)		(UINT16_T)(((ntc*NTC_ADC_FULL_RANGE)/(ntc+NTC_SMP_RES)))						//---NTC��ֵ��ADC��ϵ
	#endif
	#define NTC_ADC_TABLE_MAX_SIZE		151																				//---NTC��Ķ����ֵ
	//===��������
	INT16_T NTC_GetTemp(UINT16_T adcVal);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*NTC_CFG_H_ */
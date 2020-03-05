#ifndef NTC_CFG_H_
#define NTC_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	//////////////////////////////////////////////////////////////////////////////////////
	#define NTC_SMP_RES					10																				//---NTC采样电阻的大小
	#define	NTC_TO_VCC																									//---NTC电阻接在靠近电源端	
	#define NTC_ADC_FULL_RANGE			(float)4095.0																	//---ADC的满量程对应的数字量
	//===判断NTC电阻的接法
	#ifdef NTC_TO_VCC
		#define NTC_SMP_ADC(ntc)		(UINT16_T)(((NTC_SMP_RES*NTC_ADC_FULL_RANGE)/(ntc+NTC_SMP_RES)))				//---NTC阻值与ADC关系
	#else
		#define NTC_SMP_ADC(ntc)		(UINT16_T)(((ntc*NTC_ADC_FULL_RANGE)/(ntc+NTC_SMP_RES)))						//---NTC阻值与ADC关系
	#endif
	#define NTC_ADC_TABLE_MAX_SIZE		151																				//---NTC表的对最大值
	//===函数定义
	INT16_T NTC_GetTemp(UINT16_T adcVal);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*NTC_CFG_H_ */
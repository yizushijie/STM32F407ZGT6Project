#ifndef DAC_CFG_H_
#define DAC_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "gpio_task.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===����DC�Ĳο���ѹ,��λ��΢��
	#define DAC_REF_POWER_UV						3300000UL
	//===ÿBIT��Ӧ�ĵ�ѹֵ
	#define DAC_BIT_POWER_UV						(UINT32_T)( (((float)DAC_REF_POWER_UV)/4096)+0.5 )
	//===����ͨ��1
	#define	DAC_CHANNEL_SELECT_1					1
	//===����ͨ��2
	#define	DAC_CHANNEL_SELECT_2					2
	//===����ȫ��ͨ��
	#define DAC_CHANNEL_SELECT_ALL					3
	//===ʹ��DAC�Ļ�����
	#define DAC_CHANNEL_ENABLE_BUFFER				1
	//===��ʹ��DAC�Ļ�����
	#define DAC_CHANNEL_DISABLE_BUFFER				0

	//===��������
	UINT8_T DAC_GPIO_Init(UINT8_T ch);
	UINT8_T DAC_Clock(UINT8_T isEnableid);
	UINT8_T DAC_DAC1_Init(UINT8_T isEnableBuffer);
	UINT8_T DAC_DAC2_Init(UINT8_T isEnableBuffer);
	UINT8_T DAC_Channel_Init(UINT8_T ch, UINT8_T isEnableBuffer);
	UINT8_T DAC_Init(UINT8_T ch, UINT8_T isEnableBuffer);
	UINT8_T DAC_ChannelUV(UINT8_T ch, UINT32_T volUV);
	UINT8_T DAC_ChannelMV(UINT8_T ch, UINT32_T volMV);
	UINT8_T DAC_ChannelV(UINT8_T ch, float volV);

	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*DAC_CFG_H_ */
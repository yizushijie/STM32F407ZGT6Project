#include "power_cfg.h"

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Power_Init(void)
{
	//---ʹ��GPIO��ʱ��
	#ifndef  USE_FULL_GPIO
	GPIOTask_Clock(DPSA_CTRH_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(DPSA_CTRL_PORT, PERIPHERAL_CLOCK_ENABLE);

	GPIOTask_Clock(DPSB_CTRH_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(DPSB_CTRL_PORT, PERIPHERAL_CLOCK_ENABLE);

	GPIOTask_Clock(DPSC_CTRH_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(DPSC_CTRL_PORT, PERIPHERAL_CLOCK_ENABLE);

	GPIOTask_Clock(DPSD_CTRH_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(DPSD_CTRL_PORT, PERIPHERAL_CLOCK_ENABLE);
	#endif

	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;						//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;				//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;			//---���ģʽ---�������
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;							//---����
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---�˿ڸ���ģʽ
#endif

	//---DPSA_CTRH_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DPSA_CTRH_BIT;
	LL_GPIO_Init(DPSA_CTRH_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DPSA_CTRH_PORT, DPSA_CTRH_BIT);

	//---DPSA_CTRL_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DPSA_CTRL_BIT;
	LL_GPIO_Init(DPSA_CTRL_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DPSA_CTRL_PORT, DPSA_CTRL_BIT);

	//---DPSB_CTRH_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DPSB_CTRH_BIT;
	LL_GPIO_Init(DPSB_CTRH_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DPSB_CTRH_PORT, DPSB_CTRH_BIT);

	//---DPSB_CTRL_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DPSB_CTRL_BIT;
	LL_GPIO_Init(DPSB_CTRL_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DPSB_CTRL_PORT, DPSB_CTRL_BIT);

	//---DPSC_CTRH_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DPSC_CTRH_BIT;
	LL_GPIO_Init(DPSC_CTRH_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DPSC_CTRH_PORT, DPSC_CTRH_BIT);

	//---DPSC_CTRL_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DPSC_CTRL_BIT;
	LL_GPIO_Init(DPSC_CTRL_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DPSC_CTRL_PORT, DPSC_CTRL_BIT);

	//---DPSD_CTRH_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DPSD_CTRH_BIT;
	LL_GPIO_Init(DPSD_CTRH_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DPSD_CTRH_PORT, DPSD_CTRH_BIT);

	//---DPSD_CTRL_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DPSD_CTRL_BIT;
	LL_GPIO_Init(DPSD_CTRL_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DPSD_CTRL_PORT, DPSD_CTRL_BIT);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		������Դ���ڸ���״̬
//////////////////////////////////////////////////////////////////////////////
void Power_DeInit(void)
{
	DPSA_POWER_HZ;
	DPSB_POWER_HZ;
	DPSC_POWER_HZ;
	DPSD_POWER_HZ;
}

//===LM317�����ѹ��ƫ��
UINT16_T g_Lm317LostPower= LM317_LOST_POWER_MV;

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T LM317_Init(UINT8_T isPowerON,UINT32_T volMV)
{
	//---ʹ��GPIO��ʱ��
	#ifndef  USE_FULL_GPIO
	GPIOTask_Clock(LM317_CTRH_PORT, PERIPHERAL_CLOCK_ENABLE);
	GPIOTask_Clock(LM317_CTRL_PORT, PERIPHERAL_CLOCK_ENABLE);
	#endif

	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;						//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;				//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;			//---���ģʽ---�������
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;							//---����
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---�˿ڸ���ģʽ
#endif

	//---DPSA_CTRH_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = LM317_CTRH_BIT;
	LL_GPIO_Init(LM317_CTRH_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(LM317_CTRH_PORT, LM317_CTRH_BIT);

	//---DPSA_CTRL_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = LM317_CTRL_BIT;
	LL_GPIO_Init(LM317_CTRL_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(LM317_CTRL_PORT, LM317_CTRL_BIT);
	
	//---����DAC�������ѹ
	LM317_PowerMV(volMV);
	//---У���Ƿ������ѹֵ
	if (isPowerON==1)
	{
		LM317_POWER_ON;
	}
	else
	{
		LM317_POWER_HZ;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T LM317_DeInit(void)
{
	LM317_POWER_HZ;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T LM317_PowerMV(UINT32_T volMV)
{
	volMV +=LM317_LOST_POWER_MV;
	if (volMV > LM317_MAX_POWER_MV)
	{
		volMV=LM317_MAX_POWER_MV;
	}
	else if (volMV < LM317_MIN_POWER_MV)
	{
		volMV = LM317_MIN_POWER_MV;
	}
	volMV -= LM317_BASE_POWER_MV;
	//---�˷ŷŴ�2��������DAC��ֵ����Ҫ���ڷŴ���
	volMV >>= 1;
	DACTask_ChannelMV(DAC_CHANNEL_SELECT_1, volMV);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T LM317_PowerV(float volV)
{
	return LM317_PowerMV((UINT32_T)(volV * 1000));
}
#include "hmc472_cfg.h"

//===�ź�ԴĬ�Ϲ���
UINT16_T g_GenCHAdBm = HMC472_GEN_CHA_DBM;
UINT16_T g_GenCHBdBm = HMC472_GEN_CHB_DBM;
UINT16_T g_GenCHCdBm = HMC472_GEN_CHC_DBM;
UINT16_T g_GenCHDdBm = HMC472_GEN_CHD_DBM;

//===�ź�Դ������˥��������
UINT16_T g_HMC472GenCHAdBm = 0;
UINT8_T  g_HMC472GenCHAPower = 0;
UINT16_T g_HMC472GenCHBdBm = 0;
UINT8_T  g_HMC472GenCHBPower = 0;
UINT16_T g_HMC472GenCHCdBm = 0;
UINT8_T  g_HMC472GenCHCPower = 0;
UINT16_T g_HMC472GenCHDdBm = 0;
UINT8_T  g_HMC472GenCHDPower = 0;

//===RF����˥����8ͨ������Ĺ���
UINT16_T g_HMC472RFCHAdBm = 0;
UINT8_T	 g_HMC472RFCHAPower = 0;
UINT16_T g_HMC472RFCHBdBm = 0;
UINT8_T	 g_HMC472RFCHBPower = 0;
UINT16_T g_HMC472RFCHCdBm = 0;
UINT8_T	 g_HMC472RFCHCPower = 0;
UINT16_T g_HMC472RFCHDdBm = 0;
UINT8_T	 g_HMC472RFCHDPower = 0;

UINT16_T g_HMC472RFCHEdBm = 0;
UINT8_T	 g_HMC472RFCHEPower = 0;
UINT16_T g_HMC472RFCHFdBm = 0;
UINT8_T	 g_HMC472RFCHFPower = 0;
UINT16_T g_HMC472RFCHGdBm = 0;
UINT8_T	 g_HMC472RFCHGPower = 0;
UINT16_T g_HMC472RFCHHdBm = 0;
UINT8_T	 g_HMC472RFCHHPower = 0;

//===RF������ʷֵ���Ĭ���������-75dBm
VLTUINT8_T g_RFGendBmA = 40;  //---95===75+20
VLTUINT8_T g_RFGendBmB = 30;  //---90===75+15
VLTUINT8_T g_RFGendBmC = 50;  //---100===75+25
VLTUINT8_T g_RFGendBmD = 20;  //---85===75+10 20190318 ���ӽ���СֵΪ-85dBm

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� ��ʼ��GPIO�Ķ˿�
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
void HMC472_GPIO_Init( void )
{
	//---ʹ��GPIO��ʱ��
	#ifndef  USE_FULL_GPIO
	GPIOTask_Clock( HMC472_V1_PORT, PERIPHERAL_CLOCK_ENABLE );
	GPIOTask_Clock( HMC472_V2_PORT, PERIPHERAL_CLOCK_ENABLE );
	GPIOTask_Clock( HMC472_V3_PORT, PERIPHERAL_CLOCK_ENABLE );
	GPIOTask_Clock( HMC472_V4_PORT, PERIPHERAL_CLOCK_ENABLE );
	GPIOTask_Clock( HMC472_V5_PORT, PERIPHERAL_CLOCK_ENABLE );
	GPIOTask_Clock( HMC472_V6_PORT, PERIPHERAL_CLOCK_ENABLE );

	GPIOTask_Clock( HMC472_GENA_PORT, PERIPHERAL_CLOCK_ENABLE );
	GPIOTask_Clock( HMC472_GENB_PORT, PERIPHERAL_CLOCK_ENABLE );
	GPIOTask_Clock( HMC472_GENC_PORT, PERIPHERAL_CLOCK_ENABLE );
	GPIOTask_Clock( HMC472_GEND_PORT, PERIPHERAL_CLOCK_ENABLE );

	GPIOTask_Clock( HMC472_RFA_PORT, PERIPHERAL_CLOCK_ENABLE );
	GPIOTask_Clock( HMC472_RFB_PORT, PERIPHERAL_CLOCK_ENABLE );
	GPIOTask_Clock( HMC472_RFC_PORT, PERIPHERAL_CLOCK_ENABLE );
	GPIOTask_Clock( HMC472_RFD_PORT, PERIPHERAL_CLOCK_ENABLE );

	GPIOTask_Clock( HMC472_RFE_PORT, PERIPHERAL_CLOCK_ENABLE );
	GPIOTask_Clock( HMC472_RFF_PORT, PERIPHERAL_CLOCK_ENABLE );
	GPIOTask_Clock( HMC472_RFG_PORT, PERIPHERAL_CLOCK_ENABLE );
	GPIOTask_Clock( HMC472_RFH_PORT, PERIPHERAL_CLOCK_ENABLE );
	#endif

	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;																																		//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;																																//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;																															//---���ģʽ---��©���
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;																																			//---����
#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;																																		//---�˿ڸ���ģʽ
#endif
	
	//---��ʼ��HMC472����������V1
	GPIO_InitStruct.Pin = HMC472_V1_BIT;
	LL_GPIO_Init( HMC472_V1_PORT, &GPIO_InitStruct );
	GPIO_OUT_1( HMC472_V1_PORT, HMC472_V1_BIT );

	//---��ʼ��HMC472����������V2
	GPIO_InitStruct.Pin = HMC472_V2_BIT;
	LL_GPIO_Init( HMC472_V2_PORT, &GPIO_InitStruct );
	GPIO_OUT_1( HMC472_V2_PORT, HMC472_V2_BIT );

	//---��ʼ��HMC472����������V3
	GPIO_InitStruct.Pin = HMC472_V3_BIT;
	LL_GPIO_Init( HMC472_V3_PORT, &GPIO_InitStruct );
	GPIO_OUT_1( HMC472_V3_PORT, HMC472_V3_BIT );

	//---��ʼ��HMC472����������V4
	GPIO_InitStruct.Pin = HMC472_V4_BIT;
	LL_GPIO_Init( HMC472_V4_PORT, &GPIO_InitStruct );
	GPIO_OUT_1( HMC472_V4_PORT, HMC472_V4_BIT );

	//---��ʼ��HMC472����������V5
	GPIO_InitStruct.Pin = HMC472_V5_BIT;
	LL_GPIO_Init( HMC472_V5_PORT, &GPIO_InitStruct );
	GPIO_OUT_1( HMC472_V5_PORT, HMC472_V5_BIT );

	//---��ʼ��HMC472����������V6
	GPIO_InitStruct.Pin = HMC472_V6_BIT;
	LL_GPIO_Init( HMC472_V6_PORT, &GPIO_InitStruct );
	GPIO_OUT_1( HMC472_V6_PORT, HMC472_V6_BIT );
	
	//---74HC573Dʹ�ܶ˿�����
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;																															//---���ģʽ---�������
	GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;																																		//---����

	GPIO_InitStruct.Pin = HMC472_GENA_BIT;
	LL_GPIO_Init( HMC472_GENA_PORT, &GPIO_InitStruct );
	GPIO_OUT_1( HMC472_GENA_PORT, HMC472_GENA_BIT );

	GPIO_InitStruct.Pin = HMC472_GENB_BIT;
	LL_GPIO_Init( HMC472_GENB_PORT, &GPIO_InitStruct );
	GPIO_OUT_1( HMC472_GENB_PORT, HMC472_GENB_BIT );
    
	GPIO_InitStruct.Pin = HMC472_GENC_BIT;
	LL_GPIO_Init( HMC472_GENC_PORT, &GPIO_InitStruct );
	GPIO_OUT_1( HMC472_GENC_PORT, HMC472_GENC_BIT );

	GPIO_InitStruct.Pin = HMC472_GEND_BIT;
	LL_GPIO_Init( HMC472_GEND_PORT, &GPIO_InitStruct );
	GPIO_OUT_1( HMC472_GEND_PORT, HMC472_GEND_BIT );

	GPIO_InitStruct.Pin = HMC472_RFA_BIT;
	LL_GPIO_Init( HMC472_RFA_PORT, &GPIO_InitStruct );
	GPIO_OUT_1( HMC472_RFA_PORT, HMC472_RFA_BIT );

	GPIO_InitStruct.Pin = HMC472_RFB_BIT;
	LL_GPIO_Init( HMC472_RFB_PORT, &GPIO_InitStruct );
	GPIO_OUT_1( HMC472_RFB_PORT, HMC472_RFB_BIT );

	GPIO_InitStruct.Pin = HMC472_RFC_BIT;
	LL_GPIO_Init( HMC472_RFC_PORT, &GPIO_InitStruct );
	GPIO_OUT_1( HMC472_RFC_PORT, HMC472_RFC_BIT );

	GPIO_InitStruct.Pin = HMC472_RFD_BIT;
	LL_GPIO_Init( HMC472_RFD_PORT, &GPIO_InitStruct );
	GPIO_OUT_1( HMC472_RFD_PORT, HMC472_RFD_BIT );

	GPIO_InitStruct.Pin = HMC472_RFE_BIT;
	LL_GPIO_Init( HMC472_RFE_PORT, &GPIO_InitStruct );
	GPIO_OUT_1( HMC472_RFE_PORT, HMC472_RFE_BIT );

	GPIO_InitStruct.Pin = HMC472_RFF_BIT;
	LL_GPIO_Init( HMC472_RFF_PORT, &GPIO_InitStruct );
	GPIO_OUT_1( HMC472_RFF_PORT, HMC472_RFF_BIT );

	GPIO_InitStruct.Pin = HMC472_RFG_BIT;
	LL_GPIO_Init( HMC472_RFG_PORT, &GPIO_InitStruct );
	GPIO_OUT_1( HMC472_RFG_PORT, HMC472_RFG_BIT );

	GPIO_InitStruct.Pin = HMC472_RFH_BIT;
	LL_GPIO_Init( HMC472_RFH_PORT, &GPIO_InitStruct );
	GPIO_OUT_1( HMC472_RFH_PORT, HMC472_RFH_BIT );	
	//---�ȴ��������
	DelayTask_us( 10 );
	//---��������
	H74C573_LATCH_DISABLE;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
void HMC472_Init( void )
{
	HMC472_GPIO_Init();
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ�����HMC472���������߿��ƣ����ڿ���˥���Ĳ��� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
void HMC472_DataBus( UINT8_T val )
{
	//---D0
	((val & 0x01) == 0) ? HMC472_V6_OUT_0 : HMC472_V6_OUT_1;
	//---D1
	((val & 0x02) == 0) ? HMC472_V5_OUT_0 : HMC472_V5_OUT_1;
	//---D2
	((val & 0x04) == 0) ? HMC472_V4_OUT_0 : HMC472_V4_OUT_1;
	//---D3
	((val & 0x08) == 0) ? HMC472_V3_OUT_0 : HMC472_V3_OUT_1;
	//---D4
	((val & 0x10) == 0) ? HMC472_V2_OUT_0 : HMC472_V2_OUT_1;
	//---D5
	((val & 0x20) == 0) ? HMC472_V1_OUT_0 : HMC472_V1_OUT_1;
}
///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� ����HMC�Ĳ�������
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
void HMC472_SetGain( UINT8_T val )
{
	switch (val)
	{
		case HMC472_NONE_DBM:
			HMC472_BUS_OUT( 0x3F );
			break;
		case HMC472_05_DBM:
			HMC472_BUS_OUT( 0x3E );
			break;
		case HMC472_10_DBM:
			HMC472_BUS_OUT( 0x3D );
			break;
		case HMC472_15_DBM:
			HMC472_BUS_OUT( 0x3C );
			break;
		case HMC472_20_DBM:
			HMC472_BUS_OUT( 0x3B );
			break;
		case HMC472_25_DBM:
			HMC472_BUS_OUT( 0x3A );
			break;
		case HMC472_30_DBM:
			HMC472_BUS_OUT( 0x39 );
			break;
		case HMC472_35_DBM:
			HMC472_BUS_OUT( 0x38 );
			break;
		case HMC472_40_DBM:
			HMC472_BUS_OUT( 0x37 );
			break;
		case HMC472_45_DBM:
			HMC472_BUS_OUT( 0x36 );
			break;
		case HMC472_50_DBM:
			HMC472_BUS_OUT( 0x35 );
			break;
		case HMC472_55_DBM:
			HMC472_BUS_OUT( 0x34 );
			break;
		case HMC472_60_DBM:
			HMC472_BUS_OUT( 0x33 );
			break;
		case HMC472_65_DBM:
			HMC472_BUS_OUT( 0x32 );
			break;
		case HMC472_70_DBM:
			HMC472_BUS_OUT( 0x31 );
			break;
		case HMC472_75_DBM:
			HMC472_BUS_OUT( 0x30 );
			break;
		case HMC472_80_DBM:
			HMC472_BUS_OUT( 0x2F );
			break;
		case HMC472_85_DBM:
			HMC472_BUS_OUT( 0x2E );
			break;
		case HMC472_90_DBM:
			HMC472_BUS_OUT( 0x2D );
			break;
		case HMC472_95_DBM:
			HMC472_BUS_OUT( 0x2C );
			break;
		case HMC472_100_DBM:
			HMC472_BUS_OUT( 0x2B );
			break;
		case HMC472_105_DBM:
			HMC472_BUS_OUT( 0x2A );
			break;
		case HMC472_110_DBM:
			HMC472_BUS_OUT( 0x29 );
			break;
		case HMC472_115_DBM:
			HMC472_BUS_OUT( 0x28 );
			break;
		case HMC472_120_DBM:
			HMC472_BUS_OUT( 0x27 );
			break;
		case HMC472_125_DBM:
			HMC472_BUS_OUT( 0x26 );
			break;
		case HMC472_130_DBM:
			HMC472_BUS_OUT( 0x25 );
			break;
		case HMC472_135_DBM:
			HMC472_BUS_OUT( 0x24 );
			break;
		case HMC472_140_DBM:
			HMC472_BUS_OUT( 0x23 );
			break;
		case HMC472_145_DBM:
			HMC472_BUS_OUT( 0x22 );
			break;
		case HMC472_150_DBM:
			HMC472_BUS_OUT( 0x21 );
			break;
		case HMC472_155_DBM:
			HMC472_BUS_OUT( 0x20 );
			break;
		case HMC472_160_DBM:
			HMC472_BUS_OUT( 0x1F );
			break;
		case HMC472_165_DBM:
			HMC472_BUS_OUT( 0x1E );
			break;
		case HMC472_170_DBM:
			HMC472_BUS_OUT( 0x1D );
			break;
		case HMC472_175_DBM:
			HMC472_BUS_OUT( 0x1C );
			break;
		case HMC472_180_DBM:
			HMC472_BUS_OUT( 0x1B );
			break;
		case HMC472_185_DBM:
			HMC472_BUS_OUT( 0x1A );
			break;
		case HMC472_190_DBM:
			HMC472_BUS_OUT( 0x19 );
			break;
		case HMC472_195_DBM:
			HMC472_BUS_OUT( 0x18 );
			break;
		case HMC472_200_DBM:
			HMC472_BUS_OUT( 0x17 );
			break;
		case HMC472_205_DBM:
			HMC472_BUS_OUT( 0x16 );
			break;
		case HMC472_210_DBM:
			HMC472_BUS_OUT( 0x15 );
			break;
		case HMC472_215_DBM:
			HMC472_BUS_OUT( 0x14 );
			break;
		case HMC472_220_DBM:
			HMC472_BUS_OUT( 0x13 );
			break;
		case HMC472_225_DBM:
			HMC472_BUS_OUT( 0x12 );
			break;
		case HMC472_230_DBM:
			HMC472_BUS_OUT( 0x11 );
			break;
		case HMC472_235_DBM:
			HMC472_BUS_OUT( 0x10 );
			break;
		case HMC472_240_DBM:
			HMC472_BUS_OUT( 0x0F );
			break;
		case HMC472_245_DBM:
			HMC472_BUS_OUT( 0x0E );
			break;
		case HMC472_250_DBM:
			HMC472_BUS_OUT( 0x0D );
			break;
		case HMC472_255_DBM:
			HMC472_BUS_OUT( 0x0C );
			break;
		case HMC472_260_DBM:
			HMC472_BUS_OUT( 0x0B );
			break;
		case HMC472_265_DBM:
			HMC472_BUS_OUT( 0x0A );
			break;
		case HMC472_270_DBM:
			HMC472_BUS_OUT( 0x09 );
			break;
		case HMC472_275_DBM:
			HMC472_BUS_OUT( 0x08 );
			break;
		case HMC472_280_DBM:
			HMC472_BUS_OUT( 0x07 );
			break;
		case HMC472_285_DBM:
			HMC472_BUS_OUT( 0x06 );
			break;
		case HMC472_290_DBM:
			HMC472_BUS_OUT( 0x05 );
			break;
		case HMC472_295_DBM:
			HMC472_BUS_OUT( 0x04 );
			break;
		case HMC472_300_DBM:
			HMC472_BUS_OUT( 0x03 );
			break;
		case HMC472_305_DBM:
			HMC472_BUS_OUT( 0x02 );
			break;
		case HMC472_310_DBM:
			HMC472_BUS_OUT( 0x01 );
			break;
		case HMC472_315_DBM:
			HMC472_BUS_OUT( 0x00 );
			break;
		default:
			HMC472_BUS_OUT( 0x3F );
			break;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC472_SetGenGain( UINT8_T genCh, UINT8_T gainVal )
{
	UINT8_T _return=0;
	//---��������ĵȼ�
	UINT16_T genGain = gainVal;
	genGain*=5;
	//---����˥������˥��ֵ
	HMC472_SetGain( gainVal );
	//---ѡ��RF�ź�Դ
	switch (genCh)
	{
		case HMC472_GEN_NONE:
			_return = 1;
			break;
		case HMC472_GEN_CHA:
			H74C573_GENA_LATCH_ENABLE;
			g_HMC472GenCHAdBm = genGain;
			g_HMC472GenCHAPower = gainVal;
			break;
		case HMC472_GEN_CHB:
			H74C573_GENB_LATCH_ENABLE;
			g_HMC472GenCHBdBm = genGain;
			g_HMC472GenCHBPower = gainVal;
			break;
		case HMC472_GEN_CHC:
			g_HMC472GenCHCdBm = genGain;
			g_HMC472GenCHCPower = gainVal;
			H74C573_GENC_LATCH_ENABLE;
			break;
		case HMC472_GEN_CHD:
			H74C573_GEND_LATCH_ENABLE;
			g_HMC472GenCHDdBm = genGain;
			g_HMC472GenCHDPower = gainVal;
			break;
		default:
			_return = 1;
			break;
	}
	//---�ȴ����ݼ��سɹ�
	DelayTask_us(10);
	//---��������
	H74C573_GEN_LATCH_DISABLE;
	
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC472_SetRFGain( UINT8_T rfCH, UINT8_T gainVal )
{
	UINT8_T _return = 0;	
	//---��������ĵȼ�
	UINT16_T rfGain = gainVal;
	//---�����ź�Դ����
	rfGain *= 5;
	//---����˥������˥��ֵ
	HMC472_SetGain( gainVal );
	//---ѡ��RF����ź�
	switch (rfCH)
	{
		case HMC472_RF_NONE:
			_return = 1;
			break;
		case HMC472_RF_CHA:
			H74C573_RFA_LATCH_ENABLE;
			g_HMC472RFCHAdBm = rfGain;
			g_HMC472RFCHAPower = gainVal;
			break;
		case HMC472_RF_CHB:
			H74C573_RFB_LATCH_ENABLE;
			g_HMC472RFCHBdBm = rfGain;
			g_HMC472RFCHBPower = gainVal;
			break;
		case HMC472_RF_CHC:
			H74C573_RFC_LATCH_ENABLE;
			g_HMC472RFCHCdBm = rfGain;
			g_HMC472RFCHCPower = gainVal;
			break;
		case HMC472_RF_CHD:
			H74C573_RFD_LATCH_ENABLE;
			g_HMC472RFCHDdBm = rfGain;
			g_HMC472RFCHDPower = gainVal;
			break;
		case HMC472_RF_CHE:
			H74C573_RFE_LATCH_ENABLE;
			g_HMC472RFCHEdBm = rfGain;
			g_HMC472RFCHEPower = gainVal;
			break;
		case HMC472_RF_CHF:
			H74C573_RFF_LATCH_ENABLE;
			g_HMC472RFCHFdBm = rfGain;
			g_HMC472RFCHFPower = gainVal;
			break;
		case HMC472_RF_CHG:
			H74C573_RFG_LATCH_ENABLE;
			g_HMC472RFCHGdBm = rfGain;
			g_HMC472RFCHGPower = gainVal;
			break;
		case HMC472_RF_CHH:
			H74C573_RFH_LATCH_ENABLE;
			g_HMC472RFCHHdBm = rfGain;
			g_HMC472RFCHHPower = gainVal;
			break;
		default:
			_return = 1;
			break;
	}
	//---�ȴ����ݼ��سɹ�
	DelayTask_us(10);
	//---��������
	H74C573_RF_LATCH_DISABLE;
	
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� ��ȡ�ź�Դ�Ĺ���
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT16_T HMC472_ReadGen( UINT8_T genCH )
{
	UINT16_T _return = 0;

	//---�����ź�Դ�Ĺ���
	switch (genCH)
	{
		case HMC472_GEN_NONE:
			_return = 0;
			break;
		case HMC472_GEN_CHA:
			_return = g_GenCHAdBm;
			break;
		case HMC472_GEN_CHB:
			_return = g_GenCHBdBm;
			break;
		case HMC472_GEN_CHC:
			_return = g_GenCHCdBm;
			break;
		case HMC472_GEN_CHD:
			_return = g_GenCHDdBm;
			break;
		default:
			_return = 0;
			break;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T  HMC472_SetGen(UINT8_T genCH, UINT16_T genVal )
{
	UINT8_T _return = 0;

	//---�����ź�Դ�Ĺ���
	switch (genCH)
	{
		case HMC472_GEN_NONE:
			_return = 1;
			break;
		case HMC472_GEN_CHA:
			 g_GenCHAdBm=genVal;
			break;
		case HMC472_GEN_CHB:
			g_GenCHBdBm=genVal;
			break;
		case HMC472_GEN_CHC:
			g_GenCHCdBm=genVal;
			break;
		case HMC472_GEN_CHD:
			g_GenCHDdBm=genVal;
			break;
		default:
			_return = 1;
			break;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� ��ȡ��һ��4ͨ����˥������
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT16_T HMC472_ReadHMC472Gen( UINT8_T genCH )
{
	UINT16_T _return = 0;

	//---�����ź�Դ�Ĺ���
	switch (genCH)
	{
		case HMC472_GEN_NONE:
			_return = 0;
			break;
		case HMC472_GEN_CHA:
			_return = g_HMC472GenCHAdBm;
			break;
		case HMC472_GEN_CHB:
			_return = g_HMC472GenCHBdBm;
			break;
		case HMC472_GEN_CHC:
			_return = g_HMC472GenCHCdBm;
			break;
		case HMC472_GEN_CHD:
			_return = g_HMC472GenCHDdBm;
			break;
		default:
			_return = 0;
			break;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� ��ȡ�ڶ���8ͨ����˥������
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT16_T HMC472_ReadHMC472RF(UINT8_T rfCH )
{
	UINT16_T _return = 0;
	//---ѡ��RF����ź�
	switch (rfCH)
	{
		case HMC472_RF_NONE:
			_return = 0;
			break;
		case HMC472_RF_CHA:
			_return = g_HMC472RFCHAdBm;
			break;
		case HMC472_RF_CHB:
			_return = g_HMC472RFCHBdBm;
			break;
		case HMC472_RF_CHC:
			_return = g_HMC472RFCHCdBm;
			break;
		case HMC472_RF_CHD:
			_return = g_HMC472RFCHDdBm;
			break;
		case HMC472_RF_CHE:
			_return = g_HMC472RFCHEdBm;
			break;
		case HMC472_RF_CHF:
			_return = g_HMC472RFCHFdBm;
			break;
		case HMC472_RF_CHG:
			_return = g_HMC472RFCHGdBm;
			break;
		case HMC472_RF_CHH:
			_return = g_HMC472RFCHHdBm;
			break;
		default:
			_return = 0;
			break;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� ��ȡ�ź�Դ����˵Ĺ���
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT16_T HMC472_ReadRFGen( UINT8_T genCH, UINT8_T rfCH )
{
	UINT16_T _return = 0;

	//---�����ź�Դ�Ĺ���
	switch (genCH)
	{
		case HMC472_GEN_NONE:
			_return = 0;
			break;
		case HMC472_GEN_CHA:
			_return = g_GenCHAdBm;
			_return += g_HMC472GenCHAdBm;
			break;
		case HMC472_GEN_CHB:
			_return = g_GenCHBdBm;
			_return += g_HMC472GenCHBdBm;
			break;
		case HMC472_GEN_CHC:
			_return = g_GenCHCdBm;
			_return += g_HMC472GenCHCdBm;
			break;
		case HMC472_GEN_CHD:
			_return = g_GenCHDdBm;
			_return += g_HMC472GenCHDdBm;
			break;
		default:
			_return = 0;
			break;
	}

	//---����ź�Դ���ʴ�����ֱ�ӷ���
	if (_return!=0)
	{
		//---ѡ��RF����ź�
		switch (rfCH)
		{
			case HMC472_RF_NONE:
				_return = 0;
				break;
			case HMC472_RF_CHA:
				_return+=g_HMC472RFCHAdBm ;
				break;
			case HMC472_RF_CHB:
				_return+=g_HMC472RFCHBdBm ;
				break;
			case HMC472_RF_CHC:
				_return+=g_HMC472RFCHCdBm ;
				break;
			case HMC472_RF_CHD:
				_return+=g_HMC472RFCHDdBm ;
				break;
			case HMC472_RF_CHE:
				_return+=g_HMC472RFCHEdBm ;
				break;
			case HMC472_RF_CHF:
				_return+=g_HMC472RFCHFdBm ;
				break;
			case HMC472_RF_CHG:
				_return+=g_HMC472RFCHGdBm ;
				break;
			case HMC472_RF_CHH:
				_return+=g_HMC472RFCHHdBm ;
				break;
			default:
				_return = 0;
				break;
		}
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� �����ź�Դ�������Ĺ���
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC472_SetRFGen( UINT8_T genCH,UINT8_T rfCH, UINT16_T rfGenPower )
{
	UINT8_T _return = OK_0;
	UINT8_T gainVal = 0;
	//---����źŵĹ���
	UINT16_T rfPower = 0;
	//---�����ź�Դ�Ĺ���
	switch (genCH)
	{
		case HMC472_GEN_NONE:
			rfPower = 0;
			break;
		case HMC472_GEN_CHA:
			rfPower = g_GenCHAdBm;
			rfPower += g_HMC472GenCHAdBm;
			break;
		case HMC472_GEN_CHB:
			rfPower = g_GenCHBdBm;
			rfPower += g_HMC472GenCHBdBm;
			break;
		case HMC472_GEN_CHC:
			rfPower = g_GenCHCdBm;
			rfPower += g_HMC472GenCHCdBm;
			break;
		case HMC472_GEN_CHD:
			rfPower = g_GenCHDdBm;
			rfPower += g_HMC472GenCHDdBm;
			break;
		default:
			rfPower = 0;
			break;
	}
	if (rfPower!=0)
	{
		//---����ڶ���˥������˥��ֵ
		if (rfGenPower>rfPower)
		{
			gainVal = (UINT8_T)( ( rfGenPower - rfPower ) / 5 );
		}
		else
		{
			gainVal = 0;
		}

		//---���õڶ�����˥��
		HMC472_SetRFGain( rfCH, gainVal );
	}
	else
	{
		_return = ERROR_2;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� �汾����
//////�������: 
//////�������: 
//////˵		���� 
//////////////////////////////////////////////////////////////////////////////
UINT8_T HMC472_GetVersion( UINT8_T *pVersion,UINT8_T length )
{
	UINT8_T _return = 0;
	if (length>=HMC472_GEN_VERSION_SIZE)
	{
		sprintf( (char *)pVersion, HMC472_GEN_VERSION );
		_return=HMC472_GEN_VERSION_SIZE;
	}
	return _return;
}
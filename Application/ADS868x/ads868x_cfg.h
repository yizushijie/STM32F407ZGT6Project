#ifndef ADS868X_CFG_H_
#define ADS868X_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "delay_task.h"
	#include "gpio_task.h"
	#include "spi_task.h"
	#include "kalman_filter.h"
	#include "systick_task.h"
	//////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////�Ĵ�������---��ʼ//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////
	//===����Ĵ���
	//===��������ǰ�Ĳ���ģʽ
	#define ADS868X_CMD_REG_NO_OP				0x0000
	//===�豸�����ڴ���ģʽ
	#define ADS868X_CMD_REG_STDBY				0x8200
	//===�豸�ѹرչ���
	#define ADS868X_CMD_REG_PWR_DN				0x8300
	//===�Ĵ�������ΪĬ��
	#define ADS868X_CMD_REG_RST					0x8500
	//===�����Զ�ģʽ�¸�λ
	#define ADS868X_CMD_REG_AUTO_RST			0xA000
	//===ͨ��0
	#define ADS868X_CMD_REG_MAN_CH_0			0xC000
	//===ͨ��1
	#define ADS868X_CMD_REG_MAN_CH_1			0xC400
	//===ͨ��2
	#define ADS868X_CMD_REG_MAN_CH_2			0xC800
	//===ͨ��3
	#define ADS868X_CMD_REG_MAN_CH_3			0xCC00
	//===ͨ��4
	#define ADS868X_CMD_REG_MAN_CH_4			0xD000
	//===ͨ��5
	#define ADS868X_CMD_REG_MAN_CH_5			0xD400
	//===ͨ��6
	#define ADS868X_CMD_REG_MAN_CH_6			0xD800
	//===ͨ��7
	#define ADS868X_CMD_REG_MAN_CH_7			0xDC00
	//===AUXͨ��
	#define ADS868X_CMD_REG_MAN_AUX				0xE000
	
	//===��̼Ĵ���
	//===�Զ�Squencing���ã�Ĭ��ֵΪ0xFF - BITXʹCHX
	#define ADS868X_PROG_REG_AUTO_SEQ_EN		0x01		//[FF]
	//===ͨ�����磻Ĭ��Ϊ0x00 - BITX��CHX�ϵ�
	#define ADS868X_PROG_REG_CH_PWR_DN			0x02		//[00]
	//����ѡ��Ĭ��Ϊ0x00;//�ջ���IDΪbit 7-6��ALARM����Ϊbit 4��SDO���ݸ�ʽΪbit 2-0λ
	#define ADS868X_PROG_REG_FEATURE_SELECT		0x03		//[00]

	//===����ͨ��0���뷶Χ��Ĭ��Ϊ0x00 -λ3-0ѡ��Χ
	#define ADS868X_PROG_REG_CH0_SET_RANGE		0x05		//[00]
	//===����ͨ��1���뷶Χ��Ĭ��Ϊ0x00 -λ3-0ѡ��Χ
	#define ADS868X_PROG_REG_CH1_SET_RANGE		0x06		//[00]
	//===����ͨ��2���뷶Χ��Ĭ��Ϊ0x00 -λ3-0ѡ��Χ
	#define ADS868X_PROG_REG_CH2_SET_RANGE		0x07		//[00]
	//===����ͨ��3���뷶Χ��Ĭ��Ϊ0x00 -λ3-0ѡ��Χ
	#define ADS868X_PROG_REG_CH3_SET_RANGE		0x08		//[00]
	//===����ͨ��4���뷶Χ��Ĭ��Ϊ0x00 -λ3-0ѡ��Χ
	#define ADS868X_PROG_REG_CH4_SET_RANGE		0x09		//[00]
	//===����ͨ��5���뷶Χ��Ĭ��Ϊ0x00 -λ3-0ѡ��Χ
	#define ADS868X_PROG_REG_CH5_SET_RANGE		0x0A		//[00]
	//===����ͨ��6���뷶Χ��Ĭ��Ϊ0x00 -λ3-0ѡ��Χ
	#define ADS868X_PROG_REG_CH6_SET_RANGE		0x0B		//[00]
	//===����ͨ��7���뷶Χ��Ĭ��Ϊ0x00 -λ3-0ѡ��Χ
	#define ADS868X_PROG_REG_CH7_SET_RANGE		0x0C		//[00]

	#define ADS868X_ALARM_OVERVIEW_TRIP_FLAG	0x10
	#define ADS868X_ALARM_CH0_CH3_TRIP_FLAG		0x11
	#define ADS868X_ALARM_CH0_CH3_ACTIVE_FLAG	0x12
	#define ADS868X_ALARM_CH4_CH7_TRIP_FLAG		0x13
	#define ADS868X_ALARM_CH4_CH7_ACTIVE_FLAG	0x14

	//===CH0
	#define ADS868X_PROG_REG_CH0_HS				0x15		//[00]
	#define ADS868X_PROG_REG_CH0_HT_MSB			0x16		//[FF]
	#define ADS868X_PROG_REG_CH0_HT_LSB			0x17		//[FF]
	#define ADS868X_PROG_REG_CH0_LT_MSB			0x18		//[00]
	#define ADS868X_PROG_REG_CH0_LT_LSB			0x19		//[00]
	
	//===CH1
	#define ADS868X_PROG_REG_CH1_HS				0x1A		//[00]
	#define ADS868X_PROG_REG_CH1_HT_MSB			0x1B		//[FF]
	#define ADS868X_PROG_REG_CH1_HT_LSB			0x1C		//[FF]
	#define ADS868X_PROG_REG_CH1_LT_MSB			0x1D		//[00]
	#define ADS868X_PROG_REG_CH1_LT_LSB			0x1E		//[00]
	
	//===CH2
	#define ADS868X_PROG_REG_CH2_HS				0x1F		//[00]
	#define ADS868X_PROG_REG_CH2_HT_MSB			0x20		//[FF]
	#define ADS868X_PROG_REG_CH2_HT_LSB			0x21		//[FF]
	#define ADS868X_PROG_REG_CH2_LT_MSB			0x22		//[00]
	#define ADS868X_PROG_REG_CH2_LT_LSB			0x23		//[00]
	
	//===CH3
	#define ADS868X_PROG_REG_CH3_HS				0x24		//[00]
	#define ADS868X_PROG_REG_CH3_HT_MSB			0x25		//[FF]
	#define ADS868X_PROG_REG_CH3_HT_LSB			0x26		//[FF]
	#define ADS868X_PROG_REG_CH3_LT_MSB			0x27		//[00]
	#define ADS868X_PROG_REG_CH3_LT_LSB			0x28		//[00]
	
	//===CH4
	#define ADS868X_PROG_REG_CH4_HS				0x29		//[00]
	#define ADS868X_PROG_REG_CH4_HT_MSB			0x2A		//[FF]
	#define ADS868X_PROG_REG_CH4_HT_LSB			0x2B		//[FF]
	#define ADS868X_PROG_REG_CH4_LT_MSB			0x2C		//[00]
	#define ADS868X_PROG_REG_CH4_LT_LSB			0x2D		//[00]
	
	//===CH5
	#define ADS868X_PROG_REG_CH5_HS				0x2E		//[00]
	#define ADS868X_PROG_REG_CH5_HT_MSB			0x2F		//[FF]
	#define ADS868X_PROG_REG_CH5_HT_LSB			0x30		//[FF]
	#define ADS868X_PROG_REG_CH5_LT_MSB			0x31		//[00]
	#define ADS868X_PROG_REG_CH5_LT_LSB			0x32		//[00]
	
	//===CH6
	#define ADS868X_PROG_REG_CH6_HS				0x33		//[00]
	#define ADS868X_PROG_REG_CH6_HT_MSB			0x34		//[FF]
	#define ADS868X_PROG_REG_CH6_HT_LSB			0x35		//[FF]
	#define ADS868X_PROG_REG_CH6_LT_MSB			0x36		//[00]
	#define ADS868X_PROG_REG_CH6_LT_LSB			0x37		//[00]
	
	//===CH7
	#define ADS868X_PROG_REG_CH7_HS				0x38		//[00]
	#define ADS868X_PROG_REG_CH7_HT_MSB			0x39		//[FF]
	#define ADS868X_PROG_REG_CH7_HT_LSB			0x3A		//[FF]
	#define ADS868X_PROG_REG_CH7_LT_MSB			0x3B		//[00]
	#define ADS868X_PROG_REG_CH7_LT_LSB			0x3C		//[00]
	
	//===�����ȡ
	#define ADS868X_CMD_READ_BACK				0x3F		//[00]
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////�Ĵ�������---����//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////���ò���---��ʼ///////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	
	//===ADC�����Ĳο���ѹ
	#define ADS868X_REF_POWER_UV				4096000
	//===���뷶Χ-2.5 / + 2.5 Vref��+/- 10.24V
	#define ADS868X_RANGE_10240MV_10240MV		0x00
	//===���뷶Χ-1.25 / + 1.25 Vref��+/- 5.12V
	#define ADS868X_RANGE_5120MV_5120MV			0x01
	//===���뷶Χ��-0.625 / 0.625 + Vref��+/- 2.56V
	#define ADS868X_RANGE_2560MV_2560MV			0x02
	//===���뷶Χ��2.5 Vref��10.24V
	#define ADS868X_RANGE_0MV_10240MV			0x05
	//===���뷶Χ��1.25 Vref��5.12V
	#define ADS868X_RANGE_0MV_5120MV			0x06
	//===ADC�Ĳ���ͨ����
	#define	ADS868X_CHANNEL_MAX					8	
	//===��β�����ȡ��ֵ
	#define ADS868X_N_SAMPLE_COUNT				12
	//===У��������ݵĸ���
	#if (ADS868X_N_SAMPLE_COUNT<9)
		#define ADS868X_N_SAMPLE_COUNT			9
	#endif

	//===����ADC��λ��
	#define ADS868X_ADC_SAMPLE_BITS				14
	//===ADC�ɼ����ݵ���Чλ��
	#define ADS868X_DATA_SAMPLE_BITS			( 16-ADS868X_ADC_SAMPLE_BITS )
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////���ò���---����////////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	

	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////�ṹ�嶨��---��ʼ//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	
	//===����ṹ��
	typedef struct _ADS868X_HandleType			ADS868X_HandleType;
	//===����ָ��ṹ��
	typedef	struct _ADS868X_HandleType			*pADS868X_HandleType;
	//===����ṹ��
	struct _ADS868X_HandleType
	{
		VLTUINT8_T  msgWaitms;																							//---�ȴ�ʱ��,��λ��ms
		VLTUINT8_T  msgInitRetryCount;																					//---��ʼ�����ԵĴ���
		VLTUINT8_T  msgReadyOK;																							//---�豸�Ƿ��ʼ���ɹ���0---��ʼ���ɹ���1---��ʼ��ʧ��
		VLTUINT8_T  msgChipID;																							//---�豸��ID��Ϣ
		VLTUINT8_T  msgAutoSeqEn;																						//---ͨ��AUTO_SEQ_EN������̽���豸�Ĵ���
		VLTUINT8_T  msgChannelPWRDN;																					//---ͨ������ģʽ
		VLTUINT8_T  msgFeature;																							//---�������ò���
		VLTUINT8_T  msgChannelMode[ADS868X_CHANNEL_MAX];																//---����װ��ģʽ,0---δѡ��ʹ�ܣ�1---ѡ��ʹ��
		VLTUINT8_T	msgPositive[ADS868X_CHANNEL_MAX];																	//---0---�����ݣ�1---�Ǹ�����2---����ֵ
		VLTUINT8_T  msgChannelRangeIsPositive[ADS868X_CHANNEL_MAX];														//---0---���������̣�1---��������
		VLTUINT8_T  msgChannelRange[ADS868X_CHANNEL_MAX];																//---ADͨ�������̲ο�
		volatile float    msgADCKP[ADS868X_CHANNEL_MAX];																//---ADC�����ı���ϵ��
		VLTUINT16_T msgADCDelta[ADS868X_CHANNEL_MAX];																	//---ADC�����ı�����ֵ
		VLTUINT32_T msgREFPowerUV;																						//---ADC�Ĳο���ѹ
		VLTUINT32_T msgChannelRangeBaseUVX1000[ADS868X_CHANNEL_MAX];													//---ADͨ����ÿ��BIT����ĵ�ѹֵ����λ��uv��ʮ��
		VLTUINT64_T msgChannelRangeFullUVX1000[ADS868X_CHANNEL_MAX];													//---ADͨ���������̵ĵ�ѹֵ����λ��uv��ʮ��
		VLTUINT32_T msgChannelNowADCResult[ADS868X_CHANNEL_MAX];														//---ADͨ���ĵ�ǰ�������
		VLTUINT32_T msgChannelOldADCResult[ADS868X_CHANNEL_MAX];														//---ADͨ������һ�β������
		VLTUINT32_T msgChannelPowerResult[ADS868X_CHANNEL_MAX];															//---ADͨ���Ĳ����ĵ�ѹ���
		SPI_HandleType		msgSPI;																						//---ʹ�õ�SPIģʽ
		GPIO_HandleType	msgHWRST;																						//---Ӳ����λ�ź�
		void(*pMsgDelayms)(UINT32_T delay);																				//---��ʱ����
	};
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////�ṹ�嶨��---����//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	

	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////���ú궨��---��ʼ//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	
	//===������
	#define ADS868X_TASK_ONE					pADS868XDevice0
	#define ADS868X_TASK_TWO					0
	#define ADS868X_TASK_THREE					0	
	////////////////////////////////////////////////////////////////////////////////////// 
	//////////////////////////���ú궨��---����//////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////////////////////////	
	
	//===�ⲿ���ýӿ�
	extern ADS868X_HandleType					g_ADS868XDevice0;
	extern pADS868X_HandleType					pADS868XDevice0;

	//===��������
	UINT8_T ADS868X_SPI_Init(ADS868X_HandleType* ADS868x, void(*pFuncDelayus)(UINT32_T delay), void(*pFuncDelayms)(UINT32_T delay), UINT32_T(*pFuncTimerTick)(void), UINT8_T isHW);
	UINT8_T ADS868X_SPI_WriteCommandReg(ADS868X_HandleType* ADS868x, UINT32_T cmd);
	UINT8_T ADS868X_SPI_WriteProgramReg(ADS868X_HandleType* ADS868x, UINT8_T addr, UINT8_T val);
	UINT8_T ADS868X_SPI_ReadProgramReg(ADS868X_HandleType* ADS868x, UINT8_T addr, UINT8_T* pVal);
	UINT8_T ADS868X_SPI_ReadCommandBack(ADS868X_HandleType* ADS868x, UINT8_T* pVal, UINT8_T isAutoInit);
	UINT8_T ADS868X_SPI_NO_OP(ADS868X_HandleType* ADS868x,UINT8_T isAutoInit);
	UINT8_T ADS868X_SPI_STDBY(ADS868X_HandleType* ADS868x,UINT8_T isAutoInit);
	UINT8_T ADS868X_SPI_PWRDN(ADS868X_HandleType* ADS868x,UINT8_T isAutoInit);
	UINT8_T ADS868X_SPI_Reset(ADS868X_HandleType* ADS868x,UINT8_T isAutoInit);
	UINT8_T ADS868X_SPI_AUTORST(ADS868X_HandleType* ADS868x, UINT8_T isAutoInit);
	UINT8_T ADS868X_SPI_ManualChannel(ADS868X_HandleType* ADS868x, UINT16_T manualCHCmd, UINT8_T isAutoInit);
	UINT8_T ADS868X_SPI_WriteChipID(ADS868X_HandleType* ADS868x, UINT8_T devid, UINT8_T isAutoInit);
	UINT8_T ADS868X_SPI_ReadChipID(ADS868X_HandleType* ADS868x, UINT8_T* pDevID, UINT8_T isAutoInit);
	UINT8_T ADS868X_SPI_CheckChipID(ADS868X_HandleType* ADS868x, UINT8_T isAutoInit);
	UINT8_T ADS868X_SPI_DetectionDevice(ADS868X_HandleType* ADS868x, UINT8_T isAutoInit);
	UINT8_T ADS868X_SPI_WriteAUTOSEQEN(ADS868X_HandleType* ADS868x, UINT8_T seq, UINT8_T isAutoInit);
	UINT8_T ADS868X_SPI_ReadAUTOSEQEN(ADS868X_HandleType* ADS868x, UINT8_T* pAutoSeqEn, UINT8_T isAutoInit);
	UINT8_T ADS868X_SPI_WriteChannelPWRDN(ADS868X_HandleType* ADS868x, UINT8_T ch, UINT8_T isAutoInit);
	UINT8_T ADS868X_SPI_ReadChannelPWRDN(ADS868X_HandleType* ADS868x, UINT8_T* pPWRDN, UINT8_T isAutoInit);
	UINT8_T ADS868X_SPI_WriteFeature(ADS868X_HandleType* ADS868x, UINT8_T feature, UINT8_T isAutoInit);
	UINT8_T ADS868X_SPI_ReadFeature(ADS868X_HandleType* ADS868x, UINT8_T* pFeature, UINT8_T isAutoInit);
	UINT8_T ADS868X_SPI_WriteChannelRange(ADS868X_HandleType* ADS868x, UINT8_T chReg, UINT8_T range, UINT8_T isAutoInit);
	UINT8_T ADS868X_SPI_ReadChannelRange(ADS868X_HandleType* ADS868x, UINT8_T chReg, UINT8_T* pRange, UINT8_T isAutoInit);
	UINT8_T ADS868X_SPI_ChannelRange(ADS868X_HandleType* ADS868x, UINT8_T chIndex);
	UINT8_T ADS868X_SPI_CalcChannelPower(ADS868X_HandleType* ADS868x, UINT8_T chIndex, UINT8_T isCalcDelta);
	UINT8_T ADS868X_SPI_GetAutoRSTResult(ADS868X_HandleType* ADS868x, UINT8_T chNum, UINT8_T isAutoInit);
	UINT8_T ADS868X_SPI_GetAutoRSTNSampleResult(ADS868X_HandleType* ADS868x, UINT8_T chNum, UINT8_T isAutoInit);
	UINT8_T ADS868X_SPI_GetManualChannelResult(ADS868X_HandleType* ADS868x, UINT16_T manualChannel, UINT8_T isAutoInit);
	UINT8_T ADS868X_SPI_GetManualChannelNSampleResult(ADS868X_HandleType* ADS868x, UINT16_T manualChannel, UINT8_T isAutoInit);
	UINT8_T ADS868X_SPI_CalibrationChannelErr(ADS868X_HandleType* ADS868x);
	UINT8_T ADS868X_SPI_ConfigInit(ADS868X_HandleType* ADS868x, UINT8_T isAutoInit);
	//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*ADS868X_CFG_H_ */
